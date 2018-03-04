#include "ability.hpp"
#include "cat.hpp"
#include "range.hpp"

using namespace elona;



namespace
{



int define(lua_State* L, std::unordered_map<int, ability_data>& storage)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(L, -1, #name); \
    int name = luaL_checkinteger(L, -1); \
    lua_pop(L, 1);

    FIELD_I(related_basic_attribute);
    FIELD_I(sdataref1);
    FIELD_I(cost);
    FIELD_I(sdataref3);
    FIELD_I(sdataref4);

#undef FIELD_I

    storage.emplace(
        std::stoi(id), // TODO
        ability_data{
            std::stoi(id),
            related_basic_attribute,
            sdataref1,
            cost,
            sdataref3,
            sdataref4,
        });

    return 0;
}


} // namespace



namespace elona
{



void ability_db::initialize()
{
    cat::global.load(fs::u8path(u8"../data/ability.lua"));

    lua_getglobal(cat::global.ptr(), u8"ability");
    lua_getfield(cat::global.ptr(), -1, u8"__storage__");
    lua_pushnil(cat::global.ptr());
    while (lua_next(cat::global.ptr(), -2))
    {
        define(cat::global.ptr(), storage);
        lua_pop(cat::global.ptr(), 1);
    }
    lua_pop(cat::global.ptr(), 2);

    storage[0] = {};
}



const ability_data& ability_db::operator[](int id) const
{
    const auto itr = storage.find(id);
    if (itr == std::end(storage))
        return storage.at(0);
    else
        return itr->second;
}



skill_data::skill_data()
    : storage(245, std::vector<ability>(600))
{
}



void skill_data::clear(int cc)
{
    range::fill(storage[cc], ability{});
}



void skill_data::copy(int tc, int cc)
{
    range::copy(storage[cc], std::begin(storage[tc]));
}



} // namespace elona
