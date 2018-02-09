#include "trait.hpp"
#include "cat.hpp"
#include "range.hpp"

using namespace elona;



namespace
{


// FIXME: DO NOT USE A GLOBAL VARIABLE!
std::unordered_map<int, trait_data>* storage_ptr;


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
    int name = luaL_checkinteger(state, -1);

#undef FIELD_I

    storage_ptr->emplace(
        std::stoi(id), // TODO
        trait_data{
            std::stoi(id),
        });

    return 0;
}


} // namespace



namespace elona
{



trait_db::trait_db()
{
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    cat::register_function(state, "define", &define);
    storage_ptr = &storage;
    cat::load(state, fs::u8path(u8"../data/trait.lua"));
    storage_ptr = nullptr;
    lua_close(state);

    storage[0] = {};
}



const trait_data& trait_db::operator[](int id) const
{
    const auto itr = storage.find(id);
    if (itr == std::end(storage))
        return storage.at(0);
    else
        return itr->second;
}


} // namespace elona
