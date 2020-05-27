#pragma once

#include <queue>
#include <string>
#include <vector>

#include "../../thirdparty/sol2/sol.hpp"
#include "../optional.hpp"
#include "lua_submodule.hpp"
#include "term.hpp"



namespace elona
{
namespace lua
{

struct ModEnv;



/**
 * Elona foobar in-game console.
 *
 * All console commands and Lua functions are performed in an isolated
 * environment (pseudo-mod "_console_"), so that no side-effect happends to the
 * game. Commands have own "namespace", usually the mod ID where the command is
 * registered. There are two special namespaces, "_builtin_" and "_console_".
 * "_builtin_" is a namespace for all built-in commands defined from C++ code,
 * "console.cpp". "_console_" is a namespace for user-defined commands which
 * are defined via the console. Registered commands are stored in "COMMANDS"
 * table. You can access any commands like this
 * "COMMANDS[namespace][command_name]".
 */
class Console : public LuaSubmodule
{
public:
    explicit Console(LuaEnv&);

    void init_constants();
    void init_environment();

    void draw();
    void print(const std::string&);
    void grab_input();


    void register_(
        const std::string& mod_id,
        const std::string& name,
        sol::protected_function callback);

    sol::object run(const std::string& cmdline);



private:
    term::Term _term;

    // Assumes the font is monospaced.
    int _char_width = 10;
    int _char_height = 14;

    bool _enabled = false;
    int _width = 800;
    int _height = 250;
    std::string _input;
    bool _cursor_visible = true;



    void set_constants(int char_width, int char_height, int width, int height);
    void register_builtin_commands();
};

} // namespace lua
} // namespace elona
