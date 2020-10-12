#include "console.hpp"

#include <sstream>

#include "../../snail/application.hpp"
#include "../../snail/blend_mode.hpp"
#include "../../snail/input.hpp"
#include "../../spider/http.hpp"
#include "../../util/strutil.hpp"
#include "../character.hpp"
#include "../character_status.hpp"
#include "../config.hpp"
#include "../debug.hpp"
#include "../filesystem.hpp"
#include "../input.hpp"
#include "../item.hpp"
#include "../serialization/serialization.hpp"
#include "../skill.hpp"
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
    auto term = env().create_named("term");
    term.set_function(
        "print", [this](const std::string& s) { _term.print(s); });
    term.set_function(
        "println", [this](const std::string& s) { _term.println(s); });
    term.set_function("delete_line", [this]() { _term.delete_line(); });
    term.set_function(
        "set_input", [this](const std::string& s) { _input = s; });

    env()["shell"] = env()["kernel"]["USH"]["new_shell"](term);
    env()["shell"]["inject_core_api"](
        lua().get_api_manager().get_core_api_table());
    env()["shell"]["register_commands"]();
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

    _enabled = true;

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

    _enabled = false;
}



sol::object Console::run(const std::string& cmdline)
{
    return env()["shell"]["run"](cmdline);
}



void Console::print(const std::string& str)
{
    _term.println(str);
}



sol::object Console::get_history()
{
    return env()["shell"]["get_history"]();
}

} // namespace lua
} // namespace elona
