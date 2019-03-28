#include "lua_api_action.hpp"
#include "../../../util/temp_index_setter.hpp"
#include "../../audio.hpp"
#include "../../character.hpp"
#include "../../dialog.hpp"
#include "../../enums.hpp"
#include "../../item.hpp"
#include "../../ui.hpp"
#include "../enums/enums.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{



EnumString LuaApiAction::talk_to(LuaCharacterHandle speaker)
{
    auto& speaker_ref =
        lua::lua->get_handle_manager().get_ref<Character>(speaker);

    auto data = the_character_db.ensure(speaker_ref.id);
    if (data.dialog_id)
    {
        if (!talk_setup_variables(speaker_ref))
        {
            return LuaEnums::TurnResultTable.convert_to_string(
                TurnResult::turn_end);
        }

        talk_start();

        dialog_start(speaker_ref, *data.dialog_id);

        talk_end();
    }
    else
    {
        talk_to_npc(speaker_ref);
    }

    auto result = TurnResult::turn_end;

    if (chatteleport == 1)
    {
        chatteleport = 0;
        result = TurnResult::exit_map;
    }

    return LuaEnums::TurnResultTable.convert_to_string(result);
}

/**
 * @luadoc talk_to
 *
 * Starts a conversation with a character.
 * @tparam LuaCharacter speaker Character who will speak.
 * @tparam[opt] string dialog Dialog ID to use. Defaults to the one in the
 * character's definition. If the character has no dialog, the normal talk
 * options will be shown instead.
 * @treturn TurnResult
 */
EnumString LuaApiAction::talk_to_with_data(
    LuaCharacterHandle speaker,
    const std::string& dialog)
{
    auto& speaker_ref =
        lua::lua->get_handle_manager().get_ref<Character>(speaker);

    if (!talk_setup_variables(speaker_ref))
    {
        return LuaEnums::TurnResultTable.convert_to_string(
            TurnResult::turn_end);
    }
    talk_start();

    dialog_start(speaker_ref, dialog);

    talk_end();

    auto result = TurnResult::turn_end;

    if (chatteleport == 1)
    {
        chatteleport = 0;
        result = TurnResult::exit_map;
    }

    return LuaEnums::TurnResultTable.convert_to_string(result);
}

/**
 * @luadoc
 *
 * Makes a character melee attack another.
 * @tparam LuaCharacter attacker
 * @tparam LuaCharacter target
 * @treturn TurnResult
 */
EnumString LuaApiAction::melee_attack(
    LuaCharacterHandle attacker,
    LuaCharacterHandle target)
{
    auto& attacker_ref =
        lua::lua->get_handle_manager().get_ref<Character>(attacker);
    auto& target_ref =
        lua::lua->get_handle_manager().get_ref<Character>(target);
    TempIndexSetter<int> set_cc(cc, attacker_ref.index);
    TempIndexSetter<int> set_tc(tc, target_ref.index);

    try_to_melee_attack();

    return LuaEnums::TurnResultTable.convert_to_string(TurnResult::turn_end);
}

/**
 * @luadoc
 *
 * Opens the inventory screen for a character.
 * @tparam LuaCharacter target
 * @treturn TurnResult
 */
EnumString LuaApiAction::manage_inventory(LuaCharacterHandle target)
{
    auto& target_ref =
        lua::lua->get_handle_manager().get_ref<Character>(target);
    TempIndexSetter<int> set(tc, target_ref.index);

    auto result = try_interact_with_npc();

    return LuaEnums::TurnResultTable.convert_to_string(result);
}

/**
 * @luadoc
 *
 * Opens the give screen for a character. In this menu you cannot take back
 * items.
 * @tparam LuaCharacter target
 * @treturn TurnResult
 */
EnumString LuaApiAction::give_item(LuaCharacterHandle target)
{
    auto& target_ref =
        lua::lua->get_handle_manager().get_ref<Character>(target);
    TempIndexSetter<int> set(tc, target_ref.index);

    invctrl = 10;
    snd("core.inv");
    MenuResult mr = ctrl_inventory();
    assert(mr.turn_result != TurnResult::none);

    return LuaEnums::TurnResultTable.convert_to_string(mr.turn_result);
}

/**
 * @luadoc
 *
 * Opens the menu for changing a character's tone.
 * @tparam LuaCharacter target
 * @treturn TurnResult
 */
EnumString LuaApiAction::change_tone(LuaCharacterHandle target)
{
    auto& target_ref =
        lua::lua->get_handle_manager().get_ref<Character>(target);
    TempIndexSetter<int> set(tc, target_ref.index);

    elona::change_npc_tone();
    elona::screenupdate = -1;
    elona::update_screen();

    return LuaEnums::TurnResultTable.convert_to_string(
        TurnResult::pc_turn_user_error);
}

/**
 * @luadoc
 *
 * Opens the menu for changing a character's appearance.
 * @tparam LuaCharacter target
 * @treturn TurnResult
 */
EnumString LuaApiAction::change_appearance(LuaCharacterHandle target)
{
    auto& target_ref =
        lua::lua->get_handle_manager().get_ref<Character>(target);
    TempIndexSetter<int> set(cc, target_ref.index);

    gsel(0);
    elona::change_appearance();
    elona::screenupdate = -1;
    elona::update_screen();

    return LuaEnums::TurnResultTable.convert_to_string(
        TurnResult::pc_turn_user_error);
}

/**
 * @luadoc
 *
 * Opens the investigation screen for a character.
 * @tparam LuaCharacter target
 * @treturn TurnResult
 */
EnumString LuaApiAction::show_investigate_screen(LuaCharacterHandle target)
{
    auto& target_ref =
        lua::lua->get_handle_manager().get_ref<Character>(target);

    snd("core.pop2");
    int ccbk = cc;
    cc = target_ref.index;
    menu_character_sheet_investigate();
    cc = ccbk;
    elona::screenupdate = -1;
    elona::update_screen();

    return LuaEnums::TurnResultTable.convert_to_string(
        TurnResult::pc_turn_user_error);
}

void LuaApiAction::bind(sol::table& api_table)
{
    api_table.set_function(
        "talk_to",
        sol::overload(LuaApiAction::talk_to, LuaApiAction::talk_to_with_data));
    LUA_API_BIND_FUNCTION(api_table, LuaApiAction, melee_attack);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAction, manage_inventory);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAction, give_item);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAction, change_tone);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAction, change_appearance);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAction, show_investigate_screen);
}

} // namespace lua
} // namespace elona
