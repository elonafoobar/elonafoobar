#include "../../../audio.hpp"
#include "../../../character.hpp"
#include "../../../message.hpp"
#include "../../../trait.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for working with traits.
 * Currently only the player can have traits.
 */
namespace elona::lua::api::modules::module_Trait
{

/**
 * @luadoc level
 *
 * Obtains the player's level in a trait. It may be negative if the
 * trait is harmful.
 *
 * @tparam num trait_id the trait id
 * @treturn[1] num the player's trait level
 * @treturn[2] nil
 */
sol::optional<int> Trait_level(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::cdata.player().traits().level(
        *the_trait_db.get_id_from_integer(trait_id));
}



/**
 * @luadoc min
 *
 * Obtains the minimum possible level of a trait.
 *
 * @tparam num trait_id the trait id
 * @treturn[1] num the trait's minimum level.
 * @treturn[2] nil
 */
sol::optional<int> Trait_min(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(1);
}



/**
 * @luadoc max
 *
 * Obtains the maximum possible level of a trait.
 *
 * @tparam num trait_id the trait id
 * @treturn[1] num the trait's maximum level.
 * @treturn[2] nil
 */
sol::optional<int> Trait_max(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(2);
}



/**
 * @luadoc set
 *
 * Sets the level of a trait, bounded within its min and max.
 *
 * @tparam num trait_id the trait id
 * @tparam num level the new trait level
 */
void Trait_set(int trait_id, int level)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (elona::cdata.player().traits().level(
            *the_trait_db.get_id_from_integer(trait_id)) < level &&
        elona::cdata.player().traits().level(
            *the_trait_db.get_id_from_integer(trait_id)) < elona::traitref(2) &&
        traitrefn(0) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(0), elona::Message::color{ColorIndex::green});
    }
    else if (
        elona::cdata.player().traits().level(
            *the_trait_db.get_id_from_integer(trait_id)) > level &&
        elona::cdata.player().traits().level(
            *the_trait_db.get_id_from_integer(trait_id)) > elona::traitref(1) &&
        traitrefn(1) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(1), elona::Message::color{ColorIndex::red});
    }
    elona::cdata.player().traits().set_level(
        *the_trait_db.get_id_from_integer(trait_id),
        clamp(level, elona::traitref(1), elona::traitref(2)));
    chara_refresh(cdata.player());
}



/**
 * @luadoc modify
 *
 * Modifies the level of a trait, bounded within its min and max.
 *
 * @tparam num trait_id the trait id
 * @tparam num delta the amount to change the trait level by
 */
void Trait_modify(int trait_id, int delta)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (delta > 0 &&
        elona::cdata.player().traits().level(
            *the_trait_db.get_id_from_integer(trait_id)) < elona::traitref(2) &&
        traitrefn(0) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(0), elona::Message::color{ColorIndex::green});
    }
    else if (
        delta < 0 &&
        elona::cdata.player().traits().level(
            *the_trait_db.get_id_from_integer(trait_id)) > elona::traitref(1) &&
        traitrefn(1) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(1), elona::Message::color{ColorIndex::red});
    }
    elona::cdata.player().traits().set_level(
        *the_trait_db.get_id_from_integer(trait_id),
        clamp(
            elona::cdata.player().traits().level(
                *the_trait_db.get_id_from_integer(trait_id)) +
                delta,
            elona::traitref(1),
            elona::traitref(2)));
    chara_refresh(cdata.player());
}



/**
 * @luadoc progress_ether_disease_stage
 *
 * Modifies this character's ether corruption.
 *
 * @tparam LuaCharacter chara
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void Trait_progress_ether_disease_stage(Character& chara, lua_int delta)
{
    elona::trait_progress_ether_disease_stage(chara, delta);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("level", Trait_level);
    ELONA_LUA_API_BIND_FUNCTION("min", Trait_min);
    ELONA_LUA_API_BIND_FUNCTION("max", Trait_max);
    ELONA_LUA_API_BIND_FUNCTION("set", Trait_set);
    ELONA_LUA_API_BIND_FUNCTION("modify", Trait_modify);
    ELONA_LUA_API_BIND_FUNCTION("progress_ether_disease_stage", Trait_progress_ether_disease_stage);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Trait
