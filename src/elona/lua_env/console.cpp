#include "console.hpp"

#include <sstream>

#include "../../snail/application.hpp"
#include "../../snail/blend_mode.hpp"
#include "../../snail/input.hpp"
#include "../../spider/http.hpp"
#include "../../util/strutil.hpp"
#include "../ability.hpp"
#include "../character.hpp"
#include "../character_status.hpp"
#include "../config.hpp"
#include "../debug.hpp"
#include "../filesystem.hpp"
#include "../input.hpp"
#include "../item.hpp"
#include "../serialization/serialization.hpp"
#include "../text.hpp"
#include "../ui.hpp"
#include "../variables.hpp"
#include "../wish.hpp"
#include "api_manager.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

Console::Console(LuaEnv& lua)
    : LuaSubmodule(lua)
{
}



void Console::init_constants()
{
    auto size =
        snail::Application::instance().get_renderer().calculate_text_size("a");

    if (size.width == 0)
    {
        size.width = 10;
        size.height = 14;
    }
    set_constants(
        size.width, size.height, windoww, static_cast<int>(0.8 * windowh));

    env()["shell"]["welcome"]();
}



void Console::init_environment()
{
    {
        auto term = env().create_named("term");
        term.set_function(
            "print", [this](const std::string& s) { _term.print(s); });
        term.set_function(
            "println", [this](const std::string& s) { _term.println(s); });
        term.set_function("delete_line", [this]() { _term.delete_line(); });
        term.set_function(
            "set_input", [this](const std::string& s) { _input = s; });
    }

    register_builtin_commands();

    env().raw_set(
        "shell",
        safe_script_file(
            filesystem::dirs::data() / "script" / "kernel" / "ush.lua"));
    env()["shell"]["inject_core_api"](
        lua().get_api_manager().get_core_api_table());
    env()["shell"]["register_builtins"]();
}



void Console::set_constants(
    int char_width,
    int char_height,
    int width,
    int height)
{
    _char_width = char_width;
    _char_height = char_height;
    _width = width;
    _height = height;

    const auto num_lines = static_cast<size_t>(_height / _char_height);
    const auto num_columns = (_width / _char_width) - 1;
    _term.set_size(num_lines, num_columns);
}



void Console::draw()
{
    if (!_enabled)
        return;

    auto& renderer = snail::Application::instance().get_renderer();

    // Background
    renderer.set_blend_mode(snail::BlendMode::blend);
    renderer.set_draw_color({17, 17, 65, 192});
    renderer.fill_rect(0, 0, _width, _height);

    // Text
    font(14 - en * 2);
    int i = 0;
    for (const auto& line : _term.lines_display())
    {
        const auto x = 4;
        const auto y = _char_height * i;
        const snail::Color text_color = {255, 255, 255};
        mes(x, y, line, text_color);

        ++i;
    }

    // Cursor
    if (_cursor_visible)
    {
        if (const auto cursor = _term.cursor_display())
        {
            const auto x = 4 + _char_width * cursor->column;
            const auto y = _char_height * cursor->line;
            const snail::Color cursor_color = {191, 191, 191};
            renderer.set_draw_color(cursor_color);
            renderer.fill_rect(x + 1, y + 1, _char_width - 2, _char_height - 2);
        }
    }
}



void Console::grab_input()
{
    using namespace snail;

    bool reenable = false;

    if (!_enabled)
    {
        _enabled = true;
        reenable = true;
    }

    _input = "";
    mesbox(_input, true);

    auto pressed = [](Key key, ModKey modifiers = ModKey::none) {
        if (modifiers == ModKey::none)
        {
            return Input::instance().is_pressed(key, g_config.key_wait());
        }
        else
        {
            return Input::instance().is_pressed(key, g_config.key_wait()) &&
                (Input::instance().modifiers() & modifiers) != ModKey::none;
        }
    };

    int frame = 0;
    while (true)
    {
        env()["shell"]["prompt"]();

        if (getkey(Key::escape) || pressed(Key::key_d, ModKey::ctrl))
        {
            break;
        }
        else if (pressed(Key::up) || pressed(Key::key_p, ModKey::ctrl))
        {
            env()["shell"]["history_prev"]();
        }
        else if (pressed(Key::down) || pressed(Key::key_n, ModKey::ctrl))
        {
            env()["shell"]["history_next"]();
        }
        else if (pressed(Key::pageup))
        {
            _term.scroll_page_by(-1);
        }
        else if (pressed(Key::pagedown))
        {
            _term.scroll_page_by(1);
        }
        else if (pressed(Key::key_c, ModKey::ctrl))
        {
            env()["shell"]["interrupt"]();
        }
        else if (getkey(Key::enter))
        {
            env()["shell"]["enter"]();
            update_slight();
            input_halt_input(HaltInput::force);
        }
        else
        {
            env()["shell"]["send_input"](strutil::remove_line_ending(_input));
        }

        if (g_config.screen_refresh_wait() > 0 &&
            frame % g_config.screen_refresh_wait() == 0)
        {
            ++scrturn;
            ui_render_from_screensync();
        }
        if (frame % 30 == 0)
        {
            _cursor_visible = !_cursor_visible;
        }

        await(g_config.general_wait());
        ++frame;
    }

    onkey_0();

    if (reenable)
    {
        _enabled = false;
    }
}



void Console::register_(
    const std::string& mod_id,
    const std::string& name,
    sol::protected_function callback)
{
    env()["shell"]["register"](mod_id, name, callback);
}



sol::object Console::run(const std::string& cmdline)
{
    return env()["shell"]["run"](cmdline);
}



void Console::register_builtin_commands()
{
    auto builtin_commands = env().create_named("builtin_commands");

    builtin_commands.set_function("dump", [this]() {
        std::stringstream ss;
        serialization::json::save(ss, cdata.player());
        ss << std::endl;
        serialization::json::save(ss, inv[0]);
        _term.println(ss.str());
        std::cerr << ss.str() << std::endl;
    });

    builtin_commands.set_function("ls", [this]() {
        const auto& mod_mgr = lua().get_mod_manager();
        auto mods = mod_mgr.sorted_mods();
        range::sort(mods);
        for (const auto& mod : mods)
        {
            const auto version = mod_mgr.get_enabled_version(mod)->to_string();
            _term.println(mod + " v" + version);
        }
    });

    builtin_commands.set_function("wizard", [this]() {
        if (game_data.wizard)
            return;

        game_data.wizard = 1;
        cdatan(1, 0) = "*Debug*";
        _term.println("Wizard mode activated.");
    });

    builtin_commands.set_function("voldemort", [this]() {
        if (debug::voldemort)
            return;

        if (!game_data.wizard)
        {
            game_data.wizard = 1;
            _term.println("Wizard mode activated.");
        }
        debug::voldemort = true;
        cdatan(1, 0) = "*You-Know-Who*";
        _term.println("I AM LORD VOLDEMORT.");
    });

    builtin_commands.set_function("muggle", [this]() {
        if (!game_data.wizard)
            return;

        debug::voldemort = false;
        game_data.wizard = 0;
        cdatan(1, 0) = random_title(RandomTitleType::character);
        _term.println("Wizard mode inactivated.");
    });

    builtin_commands.set_function(
        "wish",
        [this](sol::optional<std::string> wish, sol::optional<std::string> n) {
            if (!game_data.wizard)
            {
                _term.println("Activate wizard mode to run the command.");
                return;
            }
            int num = elona::stoi(n.value_or("1"));
            if (num < 1)
            {
                num = 1;
            }
            for (int _i = 0; _i < num; ++_i)
            {
                what_do_you_wish_for(
                    wish ? optional<std::string>{*wish}
                         : optional<std::string>{});
            }
        });

    builtin_commands.set_function("gain_spell", [this]() {
        if (!game_data.wizard)
        {
            _term.println("Activate wizard mode to run the command.");
            return;
        }
        for (int i = 400; i < 467; ++i)
        {
            if (i != 426 && i != 427)
            {
                chara_gain_skill(cdata.player(), i, 100, 10000);
            }
        }
    });

    builtin_commands.set_function("gain_spact", [this]() {
        if (!game_data.wizard)
        {
            _term.println("Activate wizard mode to run the command.");
            return;
        }
        for (int i = 0; i < 61; ++i)
        {
            spact(i) = 1;
        }
    });

    builtin_commands.set_function(
        "gain_exp", [this](sol::optional<std::string> exp) {
            if (!game_data.wizard)
            {
                _term.println("Activate wizard mode to run the command.");
                return;
            }
            int exp_ = elona::stoi(exp.value_or("1000000000"));
            cdata.player().experience += exp_;
            gain_level(cdata.player());
        });

    builtin_commands.set_function(
        "gain_fame", [this](sol::optional<std::string> fame) {
            if (!game_data.wizard)
            {
                _term.println("Activate wizard mode to run the command.");
                return;
            }
            int fame_ = elona::stoi(fame.value_or("1000000"));
            cdata.player().fame += fame_;
        });
}

} // namespace lua
} // namespace elona
