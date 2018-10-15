#include "../thirdparty/hayai/hayai.hpp"

#include <cassert>
#include "../character.hpp"
#include "../init.hpp"
#include "../lua_env/lua_env.hpp"
#include "util.hpp"

using namespace elona;

// BENCHMARK(Database, BenchInitializeCharaLion, 3, 1)
// {
//     lua::lua.reset(new lua::lua_env());
//     lua::lua->get_mod_manager().load_mods(filesystem::dir::mods());
//     const fs::path data_path = filesystem::dir::mods() / "core" / "data";
//     character_db_ex db;
//
//     auto chara_table =
//         initialize_single_lion_db("chara", data_path / "chara.hcl");
//     db.initialize(chara_table);
// }

BENCHMARK(Database, BenchInitializeLion, 3, 1)
{
    lua::lua.reset(new lua::LuaEnv());
    lua::lua->get_mod_manager().load_mods(filesystem::dir::mods());
    initialize_lua_data();
}

BENCHMARK(Database, BenchInitializeCat, 3, 1)
{
    initialize_cat_db();
}
