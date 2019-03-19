#include "console.hpp"
#include <sstream>
#include <boost/algorithm/string/predicate.hpp>
#include "../../snail/application.hpp"
#include "../../snail/blend_mode.hpp"
#include "../../snail/input.hpp"
#include "../../util/strutil.hpp"
#include "../config/config.hpp"
#include "../filesystem.hpp"
#include "../input.hpp"
#include "../macro.hpp"
#include "../putit.hpp"
#include "../ui.hpp"
#include "../variables.hpp"
#include "api_manager.hpp"
#include "lua_env.hpp"
#include "mod_manager.hpp"



namespace
{

constexpr const char* prompt_primary = "> ";
constexpr const char* prompt_secondary = ">> ";
constexpr const char* eof_mark = "<eof>";

constexpr int max_scrollback_count = 1000;



std::string _version_string()
{
    return u8"ver."s + latest_version.short_string() + " (" +
        latest_version.revision + ") OS: " + latest_version.platform +
        ", timestamp: " + latest_version.timestamp;
}

} // namespace



namespace elona
{
namespace lua
{

Console::Console(LuaEnv* lua)
    : _buf(max_scrollback_count)
    , _input_history(max_scrollback_count)
    , _lua(lua)
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

    print(u8"Elona_foobar debug console");
    print(_version_string());
}



void Console::init_environment()
{
    auto core = _lua->get_api_manager().get_core_api_table();
    _console_mod = _lua->get_mod_manager().create_mod("console", none, false);

    // Automatically import APIs from "core" into the environment.
    for (const auto& kvp : core)
    {
        _console_mod->env.raw_set(kvp.first, kvp.second);
    }

    // inspect = require("inspect")
    auto inspect = lua->get_state()->script_file(filepathutil::to_utf8_path(
        filesystem::dir::data() / "script" / "kernel" / "inspect.lua"));
    _console_mod->env.raw_set("inspect", inspect);

    // Add ability to reload user/script/console.lua.
    _console_mod->env.raw_set("reload", [this]() {
        if (run_userscript())
        {
            print("Reloaded console environment.");
        }
    });
    _console_mod->env.raw_set("dump", [this]() {
        std::stringstream ss;
        putit::JsonOArchive::save(ss, cdata.player());
        ss << std::endl;
        putit::JsonOArchive::save(ss, inv[0]);
        print(ss.str());
    });
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
    auto result = _lua->get_state()->safe_script_file(
        filepathutil::to_utf8_path(
            filesystem::dir::user_script() / "console.lua"),
        _console_mod->env);

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
    return _is_multiline ? prompt_secondary : prompt_primary;
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


/// Returns true if the Lua input is complete and was executed.
bool Console::interpret_lua(const std::string& input)
{
    if (input.empty())
    {
        return _is_multiline;
    }

    bool multiline_ended = true;

    // Print errors to the console instead of throwing.
    auto handler = [this, &multiline_ended](
                       lua_State*, sol::protected_function_result pfr) {
        multiline_ended = lua_error_handler(pfr);
        return pfr;
    };

    // First, try prepending "return" to the statement, ignoring errors.
    auto result = lua::lua->get_state()->safe_script(
        u8"return " + input, _console_mod->env, sol::script_pass_on_error);

    // If that fails, execute the original statement.
    if (!result.valid())
    {
        result = lua::lua->get_state()->safe_script(
            input, _console_mod->env, handler);
    }

    if (result.valid())
    {
        // Bypass read-only metatable on mod environment
        _console_mod->env.raw_set("_LAST_RESULT", result.get<sol::object>());

        if (result.get<sol::object>() == sol::lua_nil)
        {
            print("nil");
        }
        else
        {
            auto as_string = _lua->get_state()->safe_script(
                "return inspect(_LAST_RESULT)", _console_mod->env);

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

    assert(_console_mod);

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
                if (interpret_lua(_multiline_input))
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

} // namespace lua
} // namespace elona
