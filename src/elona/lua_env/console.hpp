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
 * environment, so that no side-effect happends to the game. Console commands
 * are defined as Data instances. Defineds commands are stored in "COMMANDS"
 * table. You can access any commands like this
 * "COMMANDS[namespace..command_name]".
 */
class Console : public LuaSubmodule
{
public:
    explicit Console(LuaEnv&);

    void init_constants();
    void init_environment();

    void draw();
    void grab_input();


    sol::object run(const std::string& cmdline);
    void print(const std::string&);
    sol::object get_history();



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
};

} // namespace lua
} // namespace elona
