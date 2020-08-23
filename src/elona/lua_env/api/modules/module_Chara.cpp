#include "../../../character.hpp"
#include "../../../map.hpp"
#include "../../../randomgen.hpp"
#include "../../enums/enums.hpp"
#include "../../interface.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for working with characters.
 */
namespace elona::lua::api::modules::module_Chara
{

/**
 * @luadoc is_alive
 *
 * Checks if a character is alive.
 *
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is alive
 */
bool Chara_is_alive(
// `libclang`, invoked from `tools/docgen`, fails to parse this parameter
//  for some reason.
#ifndef ELONA_DOCGEN
    sol::optional<LuaCharacterHandle> chara
#else
    int chara
#endif
)
{
    // `libclang`, invoked from `tools/docgen`, fails to parse this function's
    // body for some reason.
#ifndef ELONA_DOCGEN
    if (!chara)
    {
        return false;
    }

    auto chara_ref = lua::ref_opt<Character>(*chara);
    if (!chara_ref)
    {
        return false;
    }

    return chara_ref->state() == Character::State::alive;
#endif
}



/**
 * @luadoc is_player
 *
 * Checks if a character is the player.
 *
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is the player
 */
bool Chara_is_player(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    return chara_ref.is_player();
}



/**
 * @luadoc is_ally
 *
 * Checks if a character is a member of the player's party.
 *
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is in the player's party
 */
bool Chara_is_ally(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    return chara_ref.is_ally();
}



/**
 * @luadoc count
 *
 * Returns the number of other characters in the current map.
 */
int Chara_count()
{
    return game_data.crowd_density;
}



/**
 * @luadoc get
 *
 * Returns the character at the given index.
 *
 * @treturn[1] LuaCharacter
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> Chara_get(int index)
{
    if (index < 0 || index >= ELONA_MAX_CHARACTERS)
    {
        return sol::nullopt;
    }

    return lua::handle(elona::cdata[index]);
}



/**
 * @luadoc player
 *
 * Returns a reference to the player. They might not be alive.
 *
 * @treturn LuaCharacter (mut) a reference to the player
 */
sol::optional<LuaCharacterHandle> Chara_player()
{
    return Chara_get(0);
}



/**
 * @luadoc create
 *
 * Attempts to create a randomly generated character at a given position.
 * Returns the character if creation succeeded, nil otherwise.
 *
 * @tparam LuaPosition position (const) position to create the character at
 * @treturn[1] LuaCharacter the created character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> Chara_create_random_xy(int x, int y)
{
    elona::flt();
    if (const auto chara = elona::chara_create(-1, 0, x, y))
    {
        return lua::handle(*chara);
    }
    else
    {
        return sol::nullopt;
    }
}



sol::optional<LuaCharacterHandle> Chara_create_random(const Position& position)
{
    return Chara_create_random_xy(position.x, position.y);
}



sol::optional<LuaCharacterHandle>
Chara_create_from_id_xy(int x, int y, const std::string& id)
{
    auto data = the_character_db.ensure(data::InstanceId{id});

    if (const auto chara = elona::chara_create(-1, data.legacy_id, x, y))
    {
        return lua::handle(*chara);
    }
    else
    {
        return sol::nullopt;
    }
}



/**
 * @luadoc create
 *
 * Attempts to create a character at a given position.
 * Returns the character if creation succeeded, nil otherwise.
 *
 * @tparam LuaPosition position (const) position to create the character at
 * @tparam string id the character prototype ID
 * @treturn[1] LuaCharacter the created character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> Chara_create_from_id(
    const Position& position,
    const std::string& id)
{
    return Chara_create_from_id_xy(position.x, position.y, id);
}



sol::optional<LuaCharacterHandle> Chara_generate_from_map_xy(int x, int y)
{
    map_set_chara_generation_filter();
    if (const auto chara = elona::chara_create(-1, dbid, x, y))
    {
        return lua::handle(*chara);
    }
    else
    {
        return sol::nullopt;
    }
}



sol::optional<LuaCharacterHandle> Chara_generate_from_map()
{
    return Chara_generate_from_map_xy(-3, 0);
}



sol::optional<LuaCharacterHandle> Chara_generate_from_map_pos(
    const Position& pos)
{

    return Chara_generate_from_map_xy(pos.x, pos.y);
}



sol::optional<LuaCharacterHandle>
Chara_generate_from_map_id_xy(int x, int y, const std::string& id)
{
    map_set_chara_generation_filter();

    return Chara_create_from_id_xy(x, y, id);
}



sol::optional<LuaCharacterHandle> Chara_generate_from_map_id_pos(
    const Position& pos,
    const std::string& id)
{

    return Chara_generate_from_map_id_xy(pos.x, pos.y, id);
}



/**
 * @luadoc kill_count
 *
 * Obtains the number of times the character type has been killed.
 *
 * @tparam string id the character prototype ID
 */
int Chara_kill_count(const std::string& id)
{
    auto data = the_character_db[data::InstanceId{id}];
    if (!data)
    {
        return 0;
    }
    return npcmemory(0, data->legacy_id);
}



/**
 * @luadoc find
 *
 * Attempts to find a character with the given prototype ID.
 *
 * @tparam string id Prototype ID to search
 * @tparam[opt] CharaFindLocation location Location to search in (defaults to
 * others)
 * @treturn[1] LuaCharacter the found character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> Chara_find(
    const std::string& id,
    sol::optional<EnumString> location)
{
    auto data = the_character_db[data::InstanceId{id}];
    if (!data)
    {
        return sol::nullopt;
    }

    auto location_value = CharaFindLocation::others;
    if (location)
    {
        location_value =
            LuaEnums::CharaFindLocationTable.ensure_from_string(*location);
    }

    if (location_value == CharaFindLocation::allies)
    {
        int result = chara_find_ally(data->legacy_id);

        if (result == -1)
        {
            return sol::nullopt;
        }
        return lua::handle(elona::cdata[result]);
    }
    else
    {
        if (const auto result = chara_find(data->id))
        {
            return lua::handle(*result);
        }
        else
        {
            return sol::nullopt;
        }
    }
}



/**
 * @luadoc can_recruit_allies
 *
 * Returns true if the player can recruit more allies, taking Charisma into
 * account.
 *
 * @treturn bool
 */
bool Chara_can_recruit_allies()
{
    return chara_get_free_slot_ally() != 0;
}



/**
 * @luadoc remove_from_party
 *
 * Removes a character from the player's party, if they are an ally.
 *
 * @tparam LuaCharacter ally
 */
void Chara_remove_from_party(LuaCharacterHandle ally)
{
    if (!Chara_is_ally(ally))
    {
        return;
    }

    auto& chara_ref = lua::ref<Character>(ally);
    chara_relocate(chara_ref, none);
}



/**
 * @luadoc all
 *
 * Returns iterable object containing all characters.
 *
 * @treturn table A sequential table containing all characters.
 */
sol::table Chara_all(sol::this_state state)
{
    sol::state_view L = state;

    sol::table ret = L.create_table();
    for (auto& chara : cdata.all())
    {
        ret.add(lua::handle(chara));
    }
    return ret;
}



/**
 * @luadoc non_allies
 *
 * Returns iterable object containing characters except for you and your allies.
 *
 * @treturn table A sequential table containing characters except for you and
 * your allies.
 */
sol::table Chara_non_allies(sol::this_state state)
{
    sol::state_view L = state;

    sol::table ret = L.create_table();
    for (auto& chara : cdata.adventurers())
    {
        ret.add(lua::handle(chara));
    }
    for (auto& chara : cdata.others())
    {
        ret.add(lua::handle(chara));
    }
    return ret;
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("is_alive", Chara_is_alive);
    ELONA_LUA_API_BIND_FUNCTION("is_player", Chara_is_player);
    ELONA_LUA_API_BIND_FUNCTION("is_ally", Chara_is_ally);
    ELONA_LUA_API_BIND_FUNCTION("count", Chara_count);
    ELONA_LUA_API_BIND_FUNCTION("get", Chara_get);
    ELONA_LUA_API_BIND_FUNCTION("player", Chara_player);
    ELONA_LUA_API_BIND_FUNCTION("create", Chara_create_random, Chara_create_random_xy, Chara_create_from_id, Chara_create_from_id_xy);
    ELONA_LUA_API_BIND_FUNCTION("generate_from_map", Chara_generate_from_map, Chara_generate_from_map_pos, Chara_generate_from_map_xy, Chara_generate_from_map_id_pos, Chara_generate_from_map_id_xy);
    ELONA_LUA_API_BIND_FUNCTION("kill_count", Chara_kill_count);
    ELONA_LUA_API_BIND_FUNCTION("find", Chara_find);
    ELONA_LUA_API_BIND_FUNCTION("can_recruit_allies", Chara_can_recruit_allies);
    ELONA_LUA_API_BIND_FUNCTION("remove_from_party", Chara_remove_from_party);
    ELONA_LUA_API_BIND_FUNCTION("all", Chara_all);
    ELONA_LUA_API_BIND_FUNCTION("non_allies", Chara_non_allies);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Chara
