#pragma once

#include <queue>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>
#include "../../thirdparty/sol2/sol.hpp"
#include "../optional.hpp"



namespace elona
{
namespace lua
{

class LuaEnv;
struct ModInfo;



/**
 * Elona foobar in-game console.
 *
 * All console commands and Lua functions are performed in an isolated
 * environment (mod "console"), so that no side-effect happends to the game.
 * Commands have own "namespace", usually the mod name where the command is
 * registered. There are two special namespaces, "_BUILTIN_" and "_CONSOLE_".
 * "_BUILTIN_" is, you know, a namespace for all built-in commands defined from
 * C++ code, "console.cpp". "_CONSOLE_" is a namespace for user-defined
 * commands which are defined via the console. Registered commands are stored
 * in "COMMANDS" table. You can access any commands like this
 * "COMMANDS[namespace][command_name]" in Lua mode.
 */
class Console
{
public:
    typedef boost::circular_buffer<std::string> buffer;

    explicit Console(LuaEnv*);

    void init_constants();
    void init_environment();

    void toggle()
    {
        _enabled = !_enabled;
    }

    bool run_userscript();

    void draw();
    void print(const std::string&);
    void grab_input();


    void register_(
        const std::string& mod_name,
        const std::string& name,
        sol::protected_function callback);

    sol::object run(const std::string& cmdline);



private:
    void set_constants(int char_width, int char_height, int width, int height);

    static bool is_incomplete_lua_line(const sol::error& error);
    void print_single_line(const std::string& line);
    bool lua_error_handler(const sol::protected_function_result& pfr);
    bool interpret(const std::string& input);
    bool interpret_lua(const std::string& input);
    bool interpret_command(const std::string& input);
    void input_loop();
    void read_line();
    void add_line(std::string);
    const char* prompt() const;

    sol::environment _env();
    sol::table _command_table();

    void _init_builtin_lua_functions();
    void _init_builtin_commands();


    // Assumes the font is monospaced.
    int _char_width = 10;
    int _char_height = 14;

    bool _enabled = false;
    bool _focused = false;
    int _width = 800;
    int _height = 250;
    int _max_chars = 0;
    size_t _max_lines = 0;
    size_t _pos = 0;
    size_t _last_size = 0;
    buffer _buf;
    buffer _input_history;
    std::string _input;
    std::string _multiline_input;
    bool _is_multiline = false;
    bool _cursor_visible = false;

    bool _in_lua_mode = false;

    ModInfo* _console_mod;

    LuaEnv* _lua;
};

} // namespace lua
} // namespace elona
