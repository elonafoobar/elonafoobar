#include "console.hpp"

#include <regex>
#include <sstream>
#include <boost/algorithm/string/predicate.hpp>
#include "../../snail/application.hpp"
#include "../../snail/blend_mode.hpp"
#include "../../snail/input.hpp"
#include "../../spider/http.hpp"
#include "../../util/strutil.hpp"
#include "../ability.hpp"
#include "../character.hpp"
#include "../config/config.hpp"
#include "../debug.hpp"
#include "../filesystem.hpp"
#include "../input.hpp"
#include "../item.hpp"
#include "../macro.hpp"
#include "../putit.hpp"
#include "../text.hpp"
#include "../ui.hpp"
#include "../variables.hpp"
#include "api_manager.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

namespace
{

constexpr const char* prompt_normal = "> ";
constexpr const char* prompt_lua_primary = "lua> ";
constexpr const char* prompt_lua_secondary = "lua>> ";
constexpr const char* eof_mark = "<eof>";

constexpr int max_scrollback_count = 1000;

constexpr const char* _lua_var_commands = u8"COMMANDS";
constexpr const char* _namespace_builtin = u8"_BUILTIN_";



std::string _version_string()
{
    return u8"ver."s + latest_version.short_string() + " (" +
        latest_version.revision + ") OS: " + latest_version.platform +
        ", timestamp: " + latest_version.timestamp;
}

} // namespace



Console::Console(LuaEnv& lua)
    : LuaSubmodule(lua)
    , _buf(max_scrollback_count)
    , _input_history(max_scrollback_count)
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
        size.width, size.height, windoww, static_cast<int>(0.35 * windowh));

    print(u8"Elona foobar <Unknown Shell>");
    print(_version_string());
}



void Console::init_environment()
{
    auto core = lua().get_api_manager().get_core_api_table();

    // Automatically import APIs from "core" into the environment.
    for (const auto& kvp : core)
    {
        env().raw_set(kvp.first, kvp.second);
    }

    env().raw_set(
        "__USH__",
        safe_script_file(
            filesystem::dirs::data() / "script" / "kernel" / "ush.lua"));

    env().create_named(_lua_var_commands);

    // Overrides print().
    env().raw_set("print", [this](const std::string& msg) { print(msg); });

    // Inject environment.
    env()["__USH__"]["init"](env());

    _init_builtin_lua_functions();
    _init_builtin_commands();
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
    _max_chars = (_width / _char_width) - 1;
    _max_lines = static_cast<size_t>(_height / _char_height);
}



/// Returns true on success.
bool Console::run_userscript()
{
    auto result =
        safe_script_file(filesystem::dirs::user_script() / "console.lua");

    if (!result.valid())
    {
        sol::error err = result;
        print("Error running console script: "s + err.what());
        return false;
    }

    return true;
}



void Console::print_single_line(const std::string& line)
{
    if (line.empty())
    {
        return;
    }

    int max_chars = _max_chars;
    size_t last_index = 0;
    size_t cut_index = strutil::utf8_cut_index(line, max_chars);

    while (cut_index != line.size())
    {
        _buf.push_back(line.substr(last_index, cut_index));
        last_index = cut_index;
        max_chars += _max_chars;
        cut_index = strutil::utf8_cut_index(line, max_chars);
    }

    _buf.push_back(line.substr(last_index, cut_index));
}



void Console::print(const std::string& message)
{
    if (message.empty())
    {
        return;
    }

    for (const auto& line : strutil::split_lines(message))
    {
        print_single_line(line);
    }
}



void Console::draw()
{
    if (!_enabled)
    {
        return;
    }

    // Background
    snail::Application::instance().get_renderer().set_blend_mode(
        snail::BlendMode::blend);
    snail::Application::instance().get_renderer().set_draw_color(
        {17, 17, 65, 192});
    snail::Application::instance().get_renderer().fill_rect(
        0, 0, _width, _height);

    // Text
    size_t n = std::min((_max_lines - 1) + _pos, _buf.size());
    int i = 0;
    for (auto it = _buf.end() - n; it < _buf.end() - _pos; it++)
    {
        font(14 - en * 2);
        mes(4, _char_height * i, *it, {255, 255, 255});

        i++;
    }

    // Cursor
    if (_focused)
    {
        font(14 - en * 2);
        mes(4,
            _char_height * (_max_lines - 1),
            prompt() + _input + (_cursor_visible ? u8"|" : ""),
            {255, 255, 255});
    }

    // Scrollback counter
    if (_pos > 0)
    {
        const auto line_count = std::to_string(_pos + _max_lines) + "/" +
            std::to_string(_buf.size());
        font(14 - en * 2);
        mes(windoww - (line_count.size() * _char_width),
            0,
            line_count,
            {255, 255, 255});
    }
}



bool Console::is_incomplete_lua_line(const sol::error& error)
{
    return boost::algorithm::ends_with(error.what(), eof_mark);
}



const char* Console::prompt() const
{
    if (_in_lua_mode)
    {
        return _is_multiline ? prompt_lua_secondary : prompt_lua_primary;
    }
    else
    {
        return prompt_normal;
    }
}



bool Console::lua_error_handler(const sol::protected_function_result& pfr)
{
    bool multiline_ended = true;

    if (pfr.status() == sol::call_status::syntax)
    {
        sol::error error = pfr;
        if (is_incomplete_lua_line(error))
        {
            _is_multiline = true;
            multiline_ended = false;
        }
        else
        {
            std::string mes = "Error: "s + error.what();
            print(mes);
        }
    }
    else
    {
        sol::error error = pfr;
        std::string mes = "Error: "s + error.what();
        print(mes);
    }

    return multiline_ended;
}



/// Returns true if the input is complete and was executed.
bool Console::interpret(const std::string& input)
{
    if (input.empty())
    {
        return _is_multiline;
    }

    if (_in_lua_mode)
    {
        return interpret_lua(input);
    }
    else
    {
        return interpret_command(input);
    }
}



/// Returns true if the input is complete and was executed. Currently, this
/// functin always returns true.
bool Console::interpret_command(const std::string& input)
{
    env()["__USH__"]["run"](input);
    update_slight();
    return true;
}



/// Returns true if the Lua input is complete and was executed.
bool Console::interpret_lua(const std::string& input)
{
    bool multiline_ended = true;

    // Print errors to the console instead of throwing.
    auto handler = [this, &multiline_ended](
                       lua_State*, sol::protected_function_result pfr) {
        multiline_ended = lua_error_handler(pfr);
        return pfr;
    };

    // First, try prepending "return" to the statement, ignoring errors.
    auto result = safe_script(u8"return " + input, sol::script_pass_on_error);

    // If that fails, execute the original statement.
    if (!result.valid())
    {
        result = safe_script(input, handler);
    }

    if (result.valid())
    {
        // Bypass read-only metatable on mod environment
        env().raw_set("_LAST_RESULT", result.get<sol::object>());

        if (result.get<sol::object>() == sol::lua_nil)
        {
            print("nil");
        }
        else
        {
            auto as_string = safe_script("return inspect(_LAST_RESULT)");

            if (as_string.valid())
            {
                print(as_string.get<std::string>());
            }
            else
            {
                print("<Unknown result>");
            }
        }
    }
    else if (multiline_ended)
    {
        print("<Unknown result>");
    }

    update_slight();

    return multiline_ended;
}



void Console::grab_input()
{
    using namespace snail;

    bool reenable = false;
    int frame = 0;
    int history_index = -1;

    if (!_enabled)
    {
        _enabled = true;
        reenable = true;
    }

    _focused = true;
    _cursor_visible = true;
    inputlog = "";
    _input = "";
    notesel(inputlog);
    mesbox(inputlog, true);

    auto pressed = [](Key key, ModKey modifiers = ModKey::none) {
        if (modifiers == ModKey::none)
        {
            return Input::instance().is_pressed(
                key, Config::instance().key_wait);
        }
        else
        {
            return Input::instance().is_pressed(
                       key, Config::instance().key_wait) &&
                (Input::instance().modifiers() & modifiers) != ModKey::none;
        }
    };

    while (_focused)
    {
        ++frame;
        if (Config::instance().screen_refresh_wait > 0 &&
            frame % Config::instance().screen_refresh_wait == 0)
        {
            ++scrturn;
            ui_render_from_screensync();
        }
        if (frame % 30 == 0)
        {
            _cursor_visible = !_cursor_visible;
        }

        noteget(_input, 0);

        await(Config::instance().general_wait);
        key_check(KeyWaitDelay::walk_run);

        if (keyhalt)
        {
            continue;
        }

        if (_last_size != _input.size())
        {
            _pos = 0;
        }

        if (getkey(Key::escape) || pressed(Key::key_d, ModKey::ctrl))
        {
            _focused = false;
        }
        else if (pressed(Key::up) || pressed(Key::key_p, ModKey::ctrl))
        {
            if (_input_history.size() > 0)
            {
                if (history_index == -1 ||
                    static_cast<size_t>(history_index) <
                        _input_history.size() - 1)
                {
                    ++history_index;
                    _input = _input_history.at(
                        _input_history.size() - history_index - 1);
                    inputlog = _input;
                }
            }
        }
        else if (pressed(Key::down) || pressed(Key::key_n, ModKey::ctrl))
        {
            if (_input_history.size() > 0)
            {
                if (history_index > 0)
                {
                    --history_index;
                    _input = _input_history.at(
                        _input_history.size() - history_index - 1);
                    inputlog = _input;
                }
            }
        }
        else if (pressed(Key::pageup))
        {
            if (_buf.size() >= _max_lines)
            {
                if (_pos + _max_lines > _buf.size() - _max_lines + 1)
                {
                    _pos = _buf.size() - _max_lines + 1;
                }
                else
                {
                    _pos += _max_lines;
                }
            }
            else
            {
                _pos = 0;
            }
        }
        else if (pressed(Key::pagedown))
        {
            if (_pos < _max_lines)
            {
                _pos = 0;
            }
            else
            {
                _pos -= _max_lines;
            }
        }
        else if (pressed(Key::key_c, ModKey::ctrl))
        {
            print(prompt() + _input);
            _multiline_input = "";
            _is_multiline = false;
            inputlog = "";
            _input = "";
            _pos = 0;
        }
        else if (getkey(Key::enter))
        {
            strutil::remove_line_ending(_input);
            _multiline_input += _input;
            if (_input != "")
            {
                print(prompt() + _input);
                if (interpret(_multiline_input))
                {
                    _multiline_input = "";
                    _is_multiline = false;
                }
                else
                {
                    _multiline_input += "\n";
                    _is_multiline = true;
                }
                _input_history.push_back(_input);
                history_index = -1;
            }
            inputlog = "";
            _input = "";
            _pos = 0;

            keyhalt = 1;
        }
        _last_size = _input.size();
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
    env()["__USH__"]["register"](mod_id, name, callback);
}



sol::object Console::run(const std::string& cmdline)
{
    return env()["__USH__"]["run"](cmdline);
}



void Console::_init_builtin_lua_functions()
{
    // Table for built-in Lua functions.
    sol::table funcs = _command_table()[_namespace_builtin];

    auto inspect = safe_script_file(
        filesystem::dirs::data() / "script" / "kernel" / "inspect.lua");
    funcs["inspect"] = inspect;

    funcs["dump"] = [this]() {
        std::stringstream ss;
        putit::JsonOArchive::save(ss, cdata.player());
        ss << std::endl;
        putit::JsonOArchive::save(ss, inv[0]);
        print(ss.str());
    };

    funcs["hello_world"] = []() { return "Hello, World!"; };

    funcs["lua"] = [this]() {
        _in_lua_mode = true;
        print(u8"Lua mode activated.");
    };

    funcs["exit_lua"] = [this]() {
        _in_lua_mode = false;
        print(u8"Lua mode inactivated.");
    };

    funcs["reload"] = [this]() {
        if (run_userscript())
        {
            print("Reloaded console environment.");
        }
    };

    funcs["ls"] = [this]() {
        std::vector<std::string> mods;
        range::transform(
            lua().get_mod_manager().calculate_loading_order(),
            std::back_inserter(mods),
            [](const auto& mod_id) { return mod_id; });
        range::sort(mods);

        sol::table ret = env().create();
        for (const auto& mod : mods)
        {
            ret.add(mod);
        }
        return ret;
    };

    funcs["wizard"] = [this]() {
        if (game_data.wizard)
            return;

        game_data.wizard = 1;
        cdatan(1, 0) = "*Debug*";
        print("Wizard mode activated.");
        print("Please get on Ylva Express on Platform 9 ¾.");
    };

    funcs["voldemort"] = [this]() {
        if (debug::voldemort)
            return;

        if (!game_data.wizard)
        {
            game_data.wizard = 1;
            print("Wizard mode activated.");
        }
        debug::voldemort = true;
        for (int i = 400; i < 467; ++i)
        {
            if (i != 426 && i != 427)
            {
                chara_gain_skill(cdata.player(), i, 100, 10000);
            }
        }
        cdatan(1, 0) = "*You-Know-Who*";
        print("I AM LORD VOLDEMORT.");
    };

    funcs["muggle"] = [this]() {
        debug::voldemort = false;
        game_data.wizard = 0;
        cdatan(1, 0) = random_title(RandomTitleType::character);
        print("Wizard mode inactivated.");
        print("I am perfectly normal, thank you very much.");
    };

    funcs["httpget"] = [this](const std::string& url) {
        spider::http::Request req{spider::http::Verb::GET, url};
        req.send(
            [this](const auto& res) { print(res.body); },
            [this](const auto& err) { print(err.what()); });
    };

    // Map functions stored in COMMANDS._BUILTIN_ to global.
    for (auto&& pair : funcs)
    {
        env()[pair.first] = pair.second;
    }
}



void Console::_init_builtin_commands()
{
    // Map functions stored in _BUILTIN_ to commands.
    sol::table funcs = _command_table()[_namespace_builtin];

    for (auto&& kvp : funcs)
    {
        const auto& name = kvp.first.as<std::string>();
        sol::protected_function callback = kvp.second;
        register_(_namespace_builtin, name, callback);
    }
}



sol::table Console::_command_table()
{
    return env()[_lua_var_commands];
}

} // namespace lua
} // namespace elona
