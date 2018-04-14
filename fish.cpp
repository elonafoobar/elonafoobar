#include "fish.hpp"
#include <string>
#include "cat.hpp"

using namespace elona;



namespace elona
{


fish_db the_fish_db;


void fish_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

    ELONA_CAT_DB_FIELD_BOOLEAN(no_generate, false);
    ELONA_CAT_DB_FIELD_INTEGER(rank, 0);
    ELONA_CAT_DB_FIELD_INTEGER(rarity, 0);
    ELONA_CAT_DB_FIELD_INTEGER(difficulty, 0);
    ELONA_CAT_DB_FIELD_INTEGER(weight, 1);
    ELONA_CAT_DB_FIELD_INTEGER(value, 1);
    ELONA_CAT_DB_FIELD_INTEGER(item_id, 618);

    storage.emplace(
        std::stoi(id), // TODO
        fish_data{
            std::stoi(id),
            no_generate,
            rank,
            rarity,
            difficulty,
            weight,
            value,
            item_id,
        });
}



} // namespace elona
