#pragma once

#include <string>
#include <vector>
#include "../filesystem.hpp"
#include "data_table.hpp"
#include "lua_submodule.hpp"



namespace elona
{
namespace lua
{

struct ModEnv;



/***
 * Stores arbitrary data as Lua tables in a naive object database
 * manner. Intended for immutable definitions of things like
 * characters and items. Not as efficient performance-wise when
 * accessed from C++ as compared to C++-level data structures (due to
 * the overhead of crossing the Lua boundary and type checking).
 * Rebuilt on startup and kept in memory. If memory usage becomes an
 * issue then data could be serialized in a Lua-readable format, or
 * stored in an actual database like SQLite.
 */
class DataManager : public LuaSubmodule
{
public:
    explicit DataManager(LuaEnv& lua);

    void clear();

    void init_from_mods();

    DataTable& get()
    {
        return _data;
    }



private:
    void _init_from_mod(ModEnv& mod);

    DataTable _data;
};

} // namespace lua
} // namespace elona
