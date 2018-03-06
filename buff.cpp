#include "buff.hpp"
#include "cat.hpp"

using namespace elona;


namespace
{


int define(lua_State* L, std::unordered_map<int, buff_data>& storage)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(L, -1, #name); \
    int name = luaL_checkinteger(L, -1); \
    lua_pop(L, 1);
#define FIELD_R(name) \
    lua_getfield(L, -1, #name); \
    cat::ref name = luaL_ref(L, LUA_REGISTRYINDEX);

    FIELD_I(type_);
    FIELD_R(duration);
    FIELD_R(on_refresh);

#undef FIELD_I
#undef FIELD_R

    cat::ref self = luaL_ref(L, LUA_REGISTRYINDEX);

    storage.emplace(
        std::stoi(id), // TODO
        buff_data{
            std::stoi(id),
            self,
            buff_data::type_t(type_),
            duration,
            on_refresh,
        });

    return 0;
}


} // namespace


namespace elona
{


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



void buff_db::initialize()
{
    cat::global.load(fs::u8path(u8"../data/buff.lua"));

    lua_getglobal(cat::global.ptr(), u8"buff");
    lua_getfield(cat::global.ptr(), -1, u8"__storage__");
    lua_pushnil(cat::global.ptr());
    while (lua_next(cat::global.ptr(), -2))
    {
        define(cat::global.ptr(), storage);
    }
    lua_pop(cat::global.ptr(), 2);
}



} // namespace elona
