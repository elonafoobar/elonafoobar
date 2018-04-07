#include "ability.hpp"
#include "cat.hpp"
#include "range.hpp"

using namespace elona;



namespace elona
{


ability_db the_ability_db;
skill_data sdata;


void ability_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

    ELONA_CAT_DB_FIELD_INTEGER(related_basic_attribute, 0);
    ELONA_CAT_DB_FIELD_INTEGER(sdataref1, 0);
    ELONA_CAT_DB_FIELD_INTEGER(cost, 0);
    ELONA_CAT_DB_FIELD_INTEGER(sdataref3, 0);
    ELONA_CAT_DB_FIELD_INTEGER(sdataref4, 0);

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
