#include "module_Chara.hpp"

#include "../../../character.hpp"
#include "../../../map.hpp"
#include "../../../randomgen.hpp"
#include "../../enums/enums.hpp"
#include "../../interface.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Checks if a character is alive.
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is alive
 */
bool LuaApiChara::is_alive(
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
 * @luadoc
 *
 * Checks if a character is the player (has index 0).
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is the player
 */
bool LuaApiChara::is_player(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    return chara_ref.index == 0;
}

/**
 * @luadoc
 *
 * Checks if a character is a member of the player's party (has index < 16)
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is in the player's party
 */
bool LuaApiChara::is_ally(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    return !LuaApiChara::is_player(chara) && chara_ref.index < 16;
}

/**
 * @luadoc
 *
 * Returns the number of other characters in the current map.
 */
int LuaApiChara::count()
{
    return game_data.crowd_density;
}

/**
 * @luadoc
 *
 * Returns a reference to the player. They might not be alive.
 * @treturn LuaCharacter (mut) a reference to the player
 */
sol::optional<LuaCharacterHandle> LuaApiChara::player()
{
    return LuaApiChara::get(0);
}

/**
 * @luadoc
 *
 * Returns the character at the given index.
 * @treturn[1] LuaCharacter
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> LuaApiChara::get(int index)
{
    if (index < 0 || index >= ELONA_MAX_CHARACTERS)
    {
        return sol::nullopt;
    }

    return lua::handle(elona::cdata[index]);
}

sol::optional<LuaCharacterHandle> LuaApiChara::create_random(
    const Position& position)
{
    return LuaApiChara::create_random_xy(position.x, position.y);
}


/**
 * @luadoc create
 *
 * Attempts to create a randomly generated character at a given position.
 * Returns the character if creation succeeded, nil otherwise.
 * @tparam LuaPosition position (const) position to create the character at
 * @treturn[1] LuaCharacter the created character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> LuaApiChara::create_random_xy(int x, int y)
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

/**
 * @luadoc create
 *
 * Attempts to create a character at a given position.
 * Returns the character if creation succeeded, nil otherwise.
 * @tparam LuaPosition position (const) position to create the character at
 * @tparam string id the character prototype ID
 * @treturn[1] LuaCharacter the created character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> LuaApiChara::create_from_id(
    const Position& position,
    const std::string& id)
{
    return LuaApiChara::create_from_id_xy(position.x, position.y, id);
}

sol::optional<LuaCharacterHandle>
LuaApiChara::create_from_id_xy(int x, int y, const std::string& id)
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

sol::optional<LuaCharacterHandle> LuaApiChara::generate_from_map()
{
    return LuaApiChara::generate_from_map_xy(-3, 0);
}

sol::optional<LuaCharacterHandle> LuaApiChara::generate_from_map_pos(
    const Position& pos)
{

    return LuaApiChara::generate_from_map_xy(pos.x, pos.y);
}

sol::optional<LuaCharacterHandle> LuaApiChara::generate_from_map_xy(
    int x,
    int y)
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

sol::optional<LuaCharacterHandle> LuaApiChara::generate_from_map_id_pos(
    const Position& pos,
    const std::string& id)
{

    return LuaApiChara::generate_from_map_id_xy(pos.x, pos.y, id);
}

sol::optional<LuaCharacterHandle>
LuaApiChara::generate_from_map_id_xy(int x, int y, const std::string& id)
{
    map_set_chara_generation_filter();

    return LuaApiChara::create_from_id_xy(x, y, id);
}

/**
 * @luadoc
 *
 * Obtains the number of times the character type has been killed.
 * @tparam string id the character prototype ID
 */
int LuaApiChara::kill_count(const std::string& id)
{
    auto data = the_character_db[data::InstanceId{id}];
    if (!data)
    {
        return 0;
    }
    return npcmemory(0, data->legacy_id);
}


/**
 * @luadoc
 *
 * Attempts to find a character with the given prototype ID.
 * @tparam string id Prototype ID to search
 * @tparam[opt] CharaFindLocation location Location to search in (defaults to
 * others)
 * @treturn[1] LuaCharacter the found character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> LuaApiChara::find(
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
 * @luadoc
 *
 * Returns true if the player can recruit more allies, taking Charisma into
 * account.
 * @treturn bool
 */
bool LuaApiChara::can_recruit_allies()
{
    return chara_get_free_slot_ally() != 0;
}


/**
 * @luadoc
 *
 * Removes a character from the player's party, if they are an ally.
 * @tparam LuaCharacter ally
 */
void LuaApiChara::remove_from_party(LuaCharacterHandle ally)
{
    if (!LuaApiChara::is_ally(ally))
    {
        return;
    }

    auto& chara_ref = lua::ref<Character>(ally);
    chara_relocate(chara_ref, none);
}

void LuaApiChara::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, is_alive);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, is_player);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, is_ally);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, count);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, get);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, player);
    api_table.set_function(
        "create",
        sol::overload(
            LuaApiChara::create_random,
            LuaApiChara::create_random_xy,
            LuaApiChara::create_from_id,
            LuaApiChara::create_from_id_xy));
    api_table.set_function(
        "generate_from_map",
        sol::overload(
            LuaApiChara::generate_from_map,
            LuaApiChara::generate_from_map_pos,
            LuaApiChara::generate_from_map_xy,
            LuaApiChara::generate_from_map_id_pos,
            LuaApiChara::generate_from_map_id_xy));
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, kill_count);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, find);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, can_recruit_allies);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, remove_from_party);
}

} // namespace lua
} // namespace elona
