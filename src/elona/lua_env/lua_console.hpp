#pragma once

#include <queue>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>
#include "../../thirdparty/sol2/sol.hpp"



namespace elona
{
namespace lua
{

class LuaEnv;
struct ModInfo;



class LuaConsole
{
public:
    typedef boost::circular_buffer<std::string> buffer;

    explicit LuaConsole(LuaEnv*);

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


private:
    void set_constants(int char_width, int char_height, int width, int height);

    static bool is_incomplete_lua_line(const sol::error& error);
    void print_single_line(const std::string& line);
    bool lua_error_handler(const sol::protected_function_result& pfr);
    bool interpret_lua(const std::string&);
    void input_loop();
    void read_line();
    void add_line(std::string);
    const char* prompt() const;

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

    ModInfo* _console_mod;

    LuaEnv* _lua;
};

} // namespace lua
} // namespace elona
