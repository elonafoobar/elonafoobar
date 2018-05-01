#include "buff.hpp"
#include "cat.hpp"

#include <iostream>

using namespace elona;


namespace elona
{


buff_db the_buff_db;


buff_db::buff_db()
{
    storage.emplace(
        0,
        buff_data{0,
                  LUA_REFNIL,
                  buff_data::type_t::buff,
                  LUA_REFNIL,
                  LUA_REFNIL}); // dummy
}


void buff_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load buff data");

    ELONA_CAT_DB_FIELD_INTEGER(type_, 0);
    ELONA_CAT_DB_FIELD_REF(duration);
    ELONA_CAT_DB_FIELD_REF(on_refresh);

    cat::ref self = luaL_ref(L, LUA_REGISTRYINDEX);
    // Dummy; after calling this function, the caller pop one value from the Lua
    // stack.
    lua_pushnil(L);

    storage.emplace(
        std::stoi(id), // TODO
        buff_data{
            std::stoi(id),
            self,
            buff_data::type_t(type_),
            duration,
            on_refresh,
        });
}


} // namespace elona
