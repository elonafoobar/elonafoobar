#include "buff.hpp"
#include "cat.hpp"

using namespace elona;


namespace
{


// FIXME: DO NOT USE A GLOBAL VARIABLE!
std::unordered_map<int, buff_data>* storage_ptr;


int define(lua_State* state)
{
    int argc = lua_gettop(state);
    if (argc != 2)
        throw 0;

    const char* id = luaL_checklstring(state, 1, nullptr);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(state, 2, #name); \
    int name = luaL_checkinteger(state, -1); \
    lua_pop(state, 1);

    FIELD_I(type_);

#undef FIELD_I

    storage_ptr->emplace(
        std::stoi(id), // TODO
        buff_data{
            std::stoi(id),
            buff_data::type_t(type_),
        });

    return 0;
}


} // namespace


namespace elona
{


buff_db::buff_db()
{
    storage.emplace(0, buff_data{0, buff_data::type_t::buff}); // dummy
}



void buff_db::initialize()
{
    cat::global.register_function("Buff", &define);
    storage_ptr = &storage;
    cat::global.load(fs::u8path(u8"../data/buff.lua"));
    storage_ptr = nullptr;
}



} // namespace elona
