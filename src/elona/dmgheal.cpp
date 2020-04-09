#include "dmgheal.hpp"

#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "element.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/interface.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/lua_event_calc_character_damage.hpp"
#include "lua_env/lua_event/lua_event_character_damaged.hpp"
#include "lua_env/lua_event/lua_event_character_killed.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "message.hpp"
#include "optional.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "variables.hpp"



namespace
{


int dmg_at_m141 = 0;



void end_dmghp(const Character& victim)
{
    if (victim.is_hung_on_sand_bag())
    {
        if (is_in_fov(victim))
        {
            txt(u8"("s + dmg_at_m141 + u8")"s + i18n::space_if_needed());
            if (rnd(20) == 0)
            {
                int picked = rnd(6);
                txt(i18n::s.get_enum("core.damage.sand_bag", picked, victim));
            }
        }
    }
    game_data.proc_damage_events_flag = 0;
    txt3rd = 0;
}



void dmgheal_death_by_backpack(Character& chara)
{
    optional_ref<Item> heaviest_item;
    int heaviest_weight = 0;

    for (auto&& item : inv.for_chara(chara))
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (item.weight > heaviest_weight)
        {
            heaviest_item = item;
            heaviest_weight = item.weight;
        }
    }

    std::string heaviest_item_name;
    if (heaviest_item)
    {
        heaviest_item_name = itemname(*heaviest_item);
    }
    else
    {
        heaviest_item_name =
            i18n::s.get_enum_property("core.death_by.other", "backpack", 6);
    }

    txt(i18n::s.get_enum_property(
        "core.death_by.other", "text", 6, chara, heaviest_item_name));
    if (chara.index == 0)
    {
        ndeathcause = i18n::s.get_enum_property(
            "core.death_by.other", "death_cause", 6, heaviest_item_name);
    }
}



/**
 * Calculates the new state to set the character to at the end of damage_hp().
 */
Character::State dmgheal_set_death_status(Character& victim)
{
    Character::State new_state = victim.state();

    if (victim.character_role == 0)
    {
        new_state = Character::State::empty;
    }
    else if (victim.character_role == 13)
    {
        new_state = Character::State::adventurer_dead;
        victim.time_to_revive = game_data.date.hours() + 24 + rnd(12);
    }
    else
    {
        new_state = Character::State::villager_dead;
        victim.time_to_revive = game_data.date.hours() + 48;
    }

    if (victim.index != 0)
    {
        if (victim.index < 16)
        {
            new_state = Character::State::pet_dead;
            chara_modify_impression(victim, -10);
            victim.current_map = 0;
            if (victim.is_escorted() == 1)
            {
                event_add(15, charaid2int(victim.id));
                new_state = Character::State::empty;
            }
            if (victim.is_escorted_in_sub_quest() == 1)
            {
                new_state = Character::State::empty;
            }
        }
    }

    return new_state;
}



} // namespace



namespace elona
{



int damage_hp(
    Character& victim,
    int amount,
    int damage_source,
    int element,
    int element_power)
{
    int damage_level = 0;
    elona_vector1<int> p_at_m141;
    int gained_exp = 0;
    bool attacker_is_player = false;

    optional_ref<Character> attacker = none;
    if (damage_source >= 0)
    {
        attacker = cdata[damage_source];
    }

    if (txt3rd == 0)
    {
        attacker_is_player = damage_source == 0;
    }
    else
    {
        attacker_is_player = false;
    }
    if (victim.state() != Character::State::alive)
    {
        end_dmghp(victim);
        return 0;
    }
    dmg_at_m141 = amount * (1 + (victim.furious > 0));
    if (attacker)
    {
        if (attacker->furious > 0)
        {
            dmg_at_m141 *= 2;
        }
    }
    if (element != 0 && element < 61)
    {
        int resistance = sdata(element, victim.index) / 50;
        if (resistance < 3)
        {
            dmg_at_m141 =
                dmg_at_m141 * 150 / clamp((resistance * 50 + 50), 40, 150);
        }
        else if (resistance < 10)
        {
            dmg_at_m141 = dmg_at_m141 * 100 / (resistance * 50 + 50);
        }
        else
        {
            dmg_at_m141 = 0;
        }
        dmg_at_m141 = dmg_at_m141 * 100 / (sdata(60, victim.index) / 2 + 50);
    }
    if (attacker_is_player)
    {
        if (critical)
        {
            snd_at("core.atk2", victim.position);
        }
        else
        {
            snd_at("core.atk1", victim.position);
        }
    }
    if (victim.wet > 0)
    {
        if (element == 50 || damage_source == -9)
        {
            dmg_at_m141 = dmg_at_m141 / 3;
        }
        if (element == 52)
        {
            dmg_at_m141 = dmg_at_m141 * 3 / 2;
        }
    }
    if (element)
    {
        if (element != 60)
        {
            if (victim.is_immune_to_elemental_damage())
            {
                dmg_at_m141 = 0;
            }
        }
    }
    if (victim.is_metal())
    {
        dmg_at_m141 = rnd_capped(dmg_at_m141 / 10 + 2);
    }
    if (victim.is_contracting_with_reaper())
    {
        if (victim.hp - dmg_at_m141 <= 0)
        {
            if (clamp(
                    25 + buff_find(victim, "core.contingency")->power / 17,
                    25,
                    80) >= rnd(100))
            {
                dmg_at_m141 *= -1;
            }
        }
    }
    if (victim.nullify_damage > 0)
    {
        if (victim.nullify_damage > rnd(100))
        {
            dmg_at_m141 = 0;
        }
    }
    if (element == 658)
    {
        dmg_at_m141 = amount;
    }
    rtdmg = dmg_at_m141;

    if (victim.index == 0 && cdata.player().god_id == core_god::opatos)
    {
        dmg_at_m141 = dmg_at_m141 * 90 / 100;
    }

    if (debug::voldemort && victim.index == 0)
    {
        dmg_at_m141 = 0;
    }

    auto result =
        lua::lua->get_event_manager().trigger(lua::CalcCharacterDamageEvent(
            victim, dmg_at_m141, element, damage_source));
    if (auto damage = result.optional<int>("damage"))
    {
        dmg_at_m141 = *damage;
    }
    else if (result.blocked())
    {
        return 1;
    }

    victim.hp -= dmg_at_m141;

    lua::lua->get_event_manager().trigger(lua::CharacterDamagedEvent(
        victim, dmg_at_m141, element, damage_source));

    if (is_in_fov(victim))
    {
        const auto color_id = element_color_id(element);
        const auto r = static_cast<uint8_t>(255 - c_col(0, color_id));
        const auto g = static_cast<uint8_t>(255 - c_col(1, color_id));
        const auto b = static_cast<uint8_t>(255 - c_col(2, color_id));
        add_damage_popup(std::to_string(dmg_at_m141), victim.index, {r, g, b});
    }


    if (element == 56)
    {
        if (attacker)
        {
            if (dmg_at_m141 > 0)
            {
                heal_hp(
                    *attacker,
                    clamp(
                        rnd_capped(
                            dmg_at_m141 * (150 + element_power * 2) / 1000 +
                            10),
                        1,
                        attacker->max_hp / 10 + rnd(5)));
            }
        }
    }
    if (victim.index == 0)
    {
        if (victim.hp < 0)
        {
            if (event_has_pending_events() && event_processing_event() != 21)
            {
                victim.hp = 1;
            }
            if (game_data.current_map == mdata_t::MapId::pet_arena)
            {
                victim.hp = 1;
            }
        }
    }
    if (dmg_at_m141 <= 0)
    {
        damage_level = -1;
    }
    else
    {
        damage_level = dmg_at_m141 * 6 / victim.max_hp;
    }
    if (victim.hp < 0)
    {
        if (victim.index < 16)
        {
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (victim.index == cnt)
                {
                    continue;
                }
                if (cdata[cnt].state() != Character::State::alive)
                {
                    continue;
                }
                if (cdata[cnt].has_lay_hand() == 0)
                {
                    continue;
                }
                if (cdata[cnt].is_lay_hand_available() == 0)
                {
                    continue;
                }
                cdata[cnt].is_lay_hand_available() = false;
                txt(i18n::s.get("core.damage.lay_hand", cdata[cnt]),
                    Message::color{ColorIndex::cyan});
                txt(i18n::s.get("core.damage.is_healed", victim));
                victim.hp = victim.max_hp / 2;
                animode = 100 + victim.index;
                MiracleAnimation().play();
                snd("core.pray2");
                break;
            }
        }
        else if (victim.is_hung_on_sand_bag())
        {
            victim.hp = victim.max_hp;
        }
    }
    if (victim.hp >= 0)
    {
        if (damage_level > 1)
        {
            spillblood(victim.position.x, victim.position.y, 1 + rnd(2));
        }
        if (damage_level > 0)
        {
            if (victim.max_hp / 2 > victim.hp)
            {
                ++damage_level;
                if (victim.max_hp / 4 > victim.hp)
                {
                    ++damage_level;
                    if (victim.max_hp / 10 > victim.hp)
                    {
                        ++damage_level;
                    }
                }
            }
        }
        if (game_data.proc_damage_events_flag == 1)
        {
            txteledmg(0, attacker_is_player ? 0 : -1, victim.index, element);
        }
        else if (game_data.proc_damage_events_flag == 2)
        {
            Message::instance().continue_sentence();
            if (damage_level == -1)
            {
                txt(i18n::s.get(
                    "core.damage.levels.scratch", victim, attacker_is_player));
            }
            if (damage_level == 0)
            {
                txt(i18n::s.get(
                        "core.damage.levels.slightly",
                        victim,
                        attacker_is_player),
                    Message::color{ColorIndex::orange});
            }
            if (damage_level == 1)
            {
                txt(i18n::s.get(
                        "core.damage.levels.moderately",
                        victim,
                        attacker_is_player),
                    Message::color{ColorIndex::gold});
            }
            if (damage_level == 2)
            {
                txt(i18n::s.get(
                        "core.damage.levels.severely",
                        victim,
                        attacker_is_player),
                    Message::color{ColorIndex::light_red});
            }
            if (damage_level >= 3)
            {
                txt(i18n::s.get(
                        "core.damage.levels.critically",
                        victim,
                        attacker_is_player),
                    Message::color{ColorIndex::red});
            }
            rowact_check(victim);
        }
        else
        {
            if (damage_level == 1)
            {
                if (is_in_fov(victim))
                {
                    txt(i18n::s.get("core.damage.reactions.screams", victim),
                        Message::color{ColorIndex::gold});
                }
            }
            if (damage_level == 2)
            {
                if (is_in_fov(victim))
                {
                    txt(i18n::s.get(
                            "core.damage.reactions.writhes_in_pain", victim),
                        Message::color{ColorIndex::light_red});
                }
            }
            if (damage_level >= 3)
            {
                if (is_in_fov(victim))
                {
                    txt(i18n::s.get(
                            "core.damage.reactions.is_severely_hurt", victim),
                        Message::color{ColorIndex::red});
                }
            }
            if (dmg_at_m141 < 0)
            {
                if (victim.hp > victim.max_hp)
                {
                    victim.hp = victim.max_hp;
                }
                if (is_in_fov(victim))
                {
                    txt(i18n::s.get("core.damage.is_healed", victim),
                        Message::color{ColorIndex::blue});
                }
            }
        }

        rowact_check(victim);
        if (victim.hp < victim.max_hp / 5)
        {
            if (victim.index != 0)
            {
                if (victim.fear == 0)
                {
                    bool runs_away = false;
                    if (victim.is_immune_to_fear() == 0)
                    {
                        if (dmg_at_m141 * 100 / victim.max_hp + 10 > rnd(200))
                        {
                            runs_away = true;
                        }
                        else
                        {
                            runs_away = false;
                        }
                        if (attacker_is_player)
                        {
                            if (trait(44)) // Gentle Face
                            {
                                runs_away = false;
                            }
                        }
                        if (runs_away)
                        {
                            victim.fear = rnd(20) + 5;
                            if (is_in_fov(victim))
                            {
                                txt(i18n::s.get(
                                        "core.damage.runs_away_in_terror",
                                        victim),
                                    Message::color{ColorIndex::blue});
                            }
                        }
                    }
                }
            }
        }
        if (element)
        {
            if (element == 59)
            {
                if (rnd(10) < element_power / 75 + 4)
                {
                    status_ailment_damage(
                        victim,
                        StatusAilment::blinded,
                        rnd_capped(element_power / 3 * 2 + 1));
                }
                if (rnd(20) < element_power / 50 + 4)
                {
                    status_ailment_damage(
                        victim,
                        StatusAilment::paralyzed,
                        rnd_capped(element_power / 3 * 2 + 1));
                }
                if (rnd(20) < element_power / 50 + 4)
                {
                    status_ailment_damage(
                        victim,
                        StatusAilment::confused,
                        rnd_capped(element_power / 3 * 2 + 1));
                }
                if (rnd(20) < element_power / 50 + 4)
                {
                    status_ailment_damage(
                        victim,
                        StatusAilment::poisoned,
                        rnd_capped(element_power / 3 * 2 + 1));
                }
                if (rnd(20) < element_power / 50 + 4)
                {
                    status_ailment_damage(
                        victim,
                        StatusAilment::sleep,
                        rnd_capped(element_power / 3 * 2 + 1));
                }
            }
            if (element == 52)
            {
                if (rnd(3 + (victim.quality >= Quality::miracle) * 3) == 0)
                {
                    ++victim.paralyzed;
                }
            }
            if (element == 53)
            {
                status_ailment_damage(
                    victim,
                    StatusAilment::blinded,
                    rnd_capped(element_power + 1));
            }
            if (element == 58)
            {
                status_ailment_damage(
                    victim,
                    StatusAilment::paralyzed,
                    rnd_capped(element_power + 1));
            }
            if (element == 54)
            {
                status_ailment_damage(
                    victim,
                    StatusAilment::confused,
                    rnd_capped(element_power + 1));
            }
            if (element == 57)
            {
                status_ailment_damage(
                    victim,
                    StatusAilment::confused,
                    rnd_capped(element_power + 1));
            }
            if (element == 55)
            {
                status_ailment_damage(
                    victim,
                    StatusAilment::poisoned,
                    rnd_capped(element_power + 1));
            }
            if (element == 61)
            {
                status_ailment_damage(
                    victim,
                    StatusAilment::bleeding,
                    rnd_capped(element_power + 1));
            }
            if (element == 62)
            {
                if (victim.index == 0)
                {
                    modify_ether_disease_stage(rnd_capped(element_power + 1));
                }
            }
            if (element == 63)
            {
                if (victim.index == 0 || rnd(3) == 0)
                {
                    item_acid(victim);
                }
            }
        }
        if ((element == 50 || damage_source == -9) && victim.wet == 0)
        {
            item_fire(victim.index);
        }
        if (element == 51)
        {
            item_cold(victim.index);
        }
        if (victim.sleep != 0)
        {
            if (element != 54 && element != 58 && element != 59)
            {
                victim.sleep = 0;
                txt(i18n::s.get("core.damage.sleep_is_disturbed", victim));
            }
        }
        if (attacker_is_player)
        {
            hostileaction(0, victim.index);
            game_data.chara_last_attacked_by_player = victim.index;
        }
        if (victim.index == 0)
        {
            if (g_config.sound())
            {
                if (g_config.heartbeat())
                {
                    int threshold =
                        config_get_integer("core.screen.heartbeat_threshold");
                    if (victim.hp < victim.max_hp * (threshold * 0.01))
                    {
                        if (!CHECKPLAY(32))
                        {
                            snd("core.Heart1");
                        }
                    }
                }
            }
        }
        if (victim.explodes())
        {
            if (rnd(3) == 0)
            {
                victim.will_explode_soon() = true;
                txt(i18n::s.get("core.damage.explode_click"),
                    Message::color{ColorIndex::cyan});
            }
        }
        if (victim.splits())
        {
            if (game_data.proc_damage_events_flag != 1)
            {
                if (dmg_at_m141 > victim.max_hp / 20 || rnd(10) == 0)
                {
                    if (map_data.type != mdata_t::MapType::world_map)
                    {
                        if (chara_copy(victim) != -1)
                        {
                            txt(i18n::s.get("core.damage.splits", victim));
                        }
                    }
                }
            }
        }
        if (victim.splits2())
        {
            if (game_data.proc_damage_events_flag != 1)
            {
                if (rnd(3) == 0)
                {
                    if (victim.confused == 0 && victim.dimmed == 0 &&
                        victim.poisoned == 0 && victim.paralyzed == 0 &&
                        victim.blind == 0)
                    {
                        if (map_data.type != mdata_t::MapType::world_map)
                        {
                            if (chara_copy(victim) != -1)
                            {
                                txt(i18n::s.get("core.damage.splits", victim));
                            }
                        }
                    }
                }
            }
        }
        if (victim.is_quick_tempered())
        {
            if (game_data.proc_damage_events_flag != 1)
            {
                if (victim.furious == 0)
                {
                    if (rnd(20) == 0)
                    {
                        if (is_in_fov(victim))
                        {
                            txt(i18n::s.get(
                                    "core.damage.is_engulfed_in_fury", victim),
                                Message::color{ColorIndex::blue});
                        }
                        victim.furious += rnd(30) + 15;
                    }
                }
            }
        }
        if (attacker)
        {
            bool apply_hate = false;
            if (victim.relationship <= -3)
            {
                if (attacker->original_relationship > -3)
                {
                    if (victim.hate == 0 || rnd(4) == 0)
                    {
                        apply_hate = true;
                    }
                }
            }
            else if (attacker->original_relationship <= -3)
            {
                if (victim.hate == 0 || rnd(4) == 0)
                {
                    apply_hate = true;
                }
            }
            if (!attacker_is_player)
            {
                if (attacker->enemy_id == victim.index)
                {
                    if (rnd(3) == 0)
                    {
                        apply_hate = true;
                    }
                }
            }
            if (apply_hate)
            {
                if (victim.index != 0)
                {
                    victim.enemy_id = attacker->index;
                    if (victim.hate == 0)
                    {
                        victim.emotion_icon = 218;
                        victim.hate = 20;
                    }
                    else
                    {
                        victim.hate += 2;
                    }
                }
            }
        }
    }

    if (victim.hp < 0)
    {
        if (auto se = sound_id_for_element(element))
        {
            snd_at(*se, victim.position, false, false);
        }
        Message::instance().txtef(ColorIndex::red);
        if (attacker)
        {
            if (element)
            {
                if (victim.index >= 16 &&
                    game_data.proc_damage_events_flag == 2)
                {
                    Message::instance().continue_sentence();
                    txteledmg(1, attacker_is_player, victim.index, element);
                }
                else
                {
                    txteledmg(2, attacker_is_player, victim.index, element);
                }
            }
            else
            {
                int death_type = rnd(4);
                if (death_type == 0)
                {
                    if (victim.index >= 16 &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        txt(i18n::s.get(
                            "core.death_by.chara.transformed_into_meat.active",
                            victim,
                            attacker_is_player));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.transformed_into_meat.passive",
                            victim,
                            attacker_is_player));
                    }
                }
                if (death_type == 1)
                {
                    if (victim.index >= 16 &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        txt(i18n::s.get(
                            "core.death_by.chara.destroyed.active",
                            victim,
                            attacker_is_player));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.destroyed.passive",
                            victim,
                            attacker_is_player));
                    }
                }
                if (death_type == 2)
                {
                    if (victim.index >= 16 &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        txt(i18n::s.get(
                            "core.death_by.chara.minced.active",
                            victim,
                            attacker_is_player));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.minced.passive",
                            victim,
                            attacker_is_player));
                    }
                }
                if (death_type == 3)
                {
                    if (victim.index >= 16 &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        txt(i18n::s.get(
                            "core.death_by.chara.killed.active",
                            victim,
                            attacker_is_player));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.killed.passive",
                            victim,
                            attacker_is_player));
                    }
                }
            }
            ndeathcause =
                i18n::s.get("core.death_by.chara.death_cause", *attacker);
        }
        else
        {
            if (damage_source == -6)
            {
                dmgheal_death_by_backpack(victim);
            }
            else
            {
                int death_kind = -damage_source;

                txt(i18n::s.get_enum_property(
                    "core.death_by.other", "text", death_kind, victim));
                if (victim.index == 0)
                {
                    ndeathcause = i18n::s.get_enum_property(
                        "core.death_by.other", "death_cause", death_kind);
                }
            }
        }
        if (damage_source == -9 || element == 50)
        {
            mef_add(
                victim.position.x,
                victim.position.y,
                5,
                24,
                rnd(10) + 5,
                100,
                damage_source);
        }
        if (element == 56)
        {
            if (attacker)
            {
                if (dmg_at_m141 > 0)
                {
                    heal_hp(
                        *attacker,
                        rnd_capped(
                            dmg_at_m141 * (200 + element_power) / 1000 + 5));
                }
            }
        }
        if (game_data.mount != victim.index || victim.index == 0)
        {
            cell_removechara(victim.position.x, victim.position.y);
        }

        Character::State new_state = dmgheal_set_death_status(victim);
        victim.set_state(new_state);

        if (victim.breaks_into_debris())
        {
            if (is_in_fov(victim))
            {
                x = victim.position.x;
                y = victim.position.y;
                snd_at("core.crush1", victim.position, false, false);
                animeblood(victim.index, 1, element);
            }
            spillfrag(victim.position.x, victim.position.y, 3);
        }
        else
        {
            sound_kill(victim.position);
            animeblood(victim.index, 0, element);
            spillblood(victim.position.x, victim.position.y, 4);
        }
        if (victim.index == 0)
        {
            ++game_data.death_count;
        }
        if (victim.index == game_data.chara_last_attacked_by_player)
        {
            game_data.chara_last_attacked_by_player = 0;
        }
        if (attacker)
        {
            if (!attacker_is_player)
            {
                chara_custom_talk(attacker->index, 103);
            }
            gained_exp = clamp(victim.level, 1, 200) *
                    clamp((victim.level + 1), 1, 200) *
                    clamp((victim.level + 2), 1, 200) / 20 +
                8;
            if (victim.level > attacker->level)
            {
                gained_exp /= 4;
            }
            if (victim.splits() || victim.splits2())
            {
                gained_exp /= 20;
            }
            attacker->experience += gained_exp;
            if (attacker_is_player)
            {
                game_data.sleep_experience += gained_exp;
            }
            attacker->hate = 0;
            if (attacker->index < 16)
            {
                attacker->enemy_id = 0;
                cdata.player().enemy_id = 0;
                game_data.chara_last_attacked_by_player = 0;
            }
        }
        if (victim.index != 0)
        {
            if (game_data.current_map != mdata_t::MapId::show_house)
            {
                if (game_data.current_map != mdata_t::MapId::the_void)
                {
                    if (victim.id == CharaId::zeome)
                    {
                        event_add(1);
                    }
                    if (victim.id == CharaId::issizzle)
                    {
                        txt(i18n::s.get("core.scenario.obtain_stone.fool"),
                            Message::color{ColorIndex::green});
                        snd("core.complete1");
                        game_data.quest_flags.magic_stone_of_fool = 1;
                    }
                    if (victim.id == CharaId::wynan)
                    {
                        txt(i18n::s.get("core.scenario.obtain_stone.king"),
                            Message::color{ColorIndex::green});
                        snd("core.complete1");
                        game_data.quest_flags.magic_stone_of_king = 1;
                    }
                    if (victim.id == CharaId::quruiza)
                    {
                        txt(i18n::s.get("core.scenario.obtain_stone.sage"),
                            Message::color{ColorIndex::green});
                        snd("core.complete1");
                        game_data.quest_flags.magic_stone_of_sage = 1;
                    }
                    if (victim.id == CharaId::rodlob)
                    {
                        if (game_data.quest_flags.novice_knight < 1000)
                        {
                            game_data.quest_flags.novice_knight = 2;
                            quest_update_journal_msg();
                        }
                    }
                    if (victim.id == CharaId::tuwen)
                    {
                        if (game_data.quest_flags.pyramid_trial < 1000)
                        {
                            game_data.quest_flags.pyramid_trial = 1000;
                            quest_update_journal_msg();
                            txt(i18n::s.get("core.quest.completed"));
                            snd("core.complete1");
                        }
                    }
                    if (victim.id == CharaId::ungaga)
                    {
                        if (game_data.quest_flags.minotaur_king < 1000)
                        {
                            game_data.quest_flags.minotaur_king = 2;
                            quest_update_journal_msg();
                        }
                    }
                    if (victim.id == CharaId::big_daddy)
                    {
                        event_add(27, victim.position.x, victim.position.y);
                    }
                    if (victim.id == CharaId::little_sister)
                    {
                        ++game_data.quest_flags.kill_count_of_little_sister;
                        txt(i18n::s.get(
                                "core.talk.unique.strange_scientist.saved_count",
                                game_data.quest_flags
                                    .save_count_of_little_sister,
                                game_data.quest_flags
                                    .kill_count_of_little_sister),
                            Message::color{ColorIndex::red});
                    }
                    if (game_data.current_dungeon_level ==
                            area_data[game_data.current_map].deepest_level ||
                        game_data.current_map == mdata_t::MapId::the_void)
                    {
                        if (area_data[game_data.current_map]
                                    .has_been_conquered == victim.index &&
                            victim.is_lord_of_dungeon() == 1)
                        {
                            event_add(5);
                        }
                    }
                    if (victim.id == CharaId::ehekatl)
                    {
                        if (rnd(4) == 0)
                        {
                            event_add(28, victim.position.x, victim.position.y);
                        }
                    }
                    quest_check();
                }
                else if (game_data.current_map == mdata_t::MapId::the_void)
                {
                    if (area_data[game_data.current_map].has_been_conquered ==
                            victim.index &&
                        victim.is_lord_of_dungeon() == 1)
                    {
                        event_add(5);
                    }
                }
            }
        }
        if (victim.index != 0)
        {
            ++npcmemory(0, charaid2int(victim.id));
            chara_custom_talk(victim.index, 102);
            if (victim.index < 16)
            {
                txt(i18n::s.get("core.damage.you_feel_sad"));
            }
        }
        if (victim.state() == Character::State::empty)
        {
            // Exclude town residents because they occupy character slots even
            // if they are dead.
            modify_crowd_density(victim.index, -1);
        }
        if (game_data.mount)
        {
            if (victim.index == game_data.mount)
            {
                txt(i18n::s.get("core.damage.get_off_corpse", victim));
                ride_end();
            }
        }
        check_kill(damage_source, victim.index);
        catitem = 0;
        rollanatomy = 0;
        if (rnd(60) == 0)
        {
            rollanatomy = 1;
        }
        if (attacker)
        {
            if (attacker->id == CharaId::black_cat)
            {
                catitem = attacker->index;
            }
            if (int(std::sqrt(sdata(161, attacker->index))) > rnd(150))
            {
                rollanatomy = 1;
            }
            chara_gain_skill_exp(*attacker, 161, 10 + rollanatomy * 4);
        }
        rc = victim.index;
        character_drops_item();
        if (game_data.current_map == mdata_t::MapId::pet_arena)
        {
            if (rnd(5) == 0)
            {
                snd("core.cheer");
            }
        }
        if (victim.is_death_master() == 1)
        {
            txt(i18n::s.get("core.damage.death_word_breaks"));
            for (int chara_index = 0; chara_index < ELONA_MAX_CHARACTERS;
                 ++chara_index)
            {
                if (cdata[chara_index].state() != Character::State::alive)
                {
                    continue;
                }
                for (int buff_index = 0; buff_index < 16; ++buff_index)
                {
                    if (cdata[chara_index].buffs[buff_index].id == 0)
                    {
                        break;
                    }
                    if (cdata[chara_index].buffs[buff_index].id == 16)
                    {
                        buff_delete(cdata[chara_index], buff_index);
                        --buff_index;
                        continue;
                    }
                }
            }
        }
        if (attacker_is_player)
        {
            if (game_data.catches_god_signal)
            {
                if (rnd(20) == 0)
                {
                    txtgod(cdata.player().god_id, 9);
                }
            }
        }

        lua::lua->get_event_manager().trigger(lua::CharacterKilledEvent(
            victim, dmg_at_m141, element, damage_source));

        end_dmghp(victim);

        return 0;
    }
    end_dmghp(victim);
    return 1;
}



void heal_hp(Character& cc, int delta)
{
    cc.hp += delta;
    if (cc.hp > cc.max_hp)
    {
        cc.hp = cc.max_hp;
    }
}



void damage_mp(Character& cc, int delta)
{
    cc.mp -= delta;
    if (cc.mp < -999999)
    {
        cc.mp = -999999;
    }
    if (cc.mp < 0)
    {
        chara_gain_exp_mana_capacity(cc);
        auto damage = -cc.mp * 400 / (100 + sdata(164, cc.index) * 10);
        if (cc.index == 0)
        {
            if (trait(156) == 1)
            {
                damage /= 2;
            }
        }
        else
        {
            damage /= 5;
            if (damage < 10)
                return;
        }
        txt(i18n::s.get("core.damage.magic_reaction_hurts", cc));
        damage_hp(cc, damage, -2);
    }
}



void heal_mp(Character& cc, int delta)
{
    cc.mp += delta;
    if (cc.mp > cc.max_mp)
    {
        cc.mp = cc.max_mp;
    }
}



bool action_sp(Character& cc, int sp)
{
    if (cc.index != 0 || debug::voldemort)
        return true;

    damage_sp(cc, sp);
    return cc.sp >= 50 || cc.sp >= rnd(75);
}



void damage_sp(Character& cc, int delta)
{
    if (cc.index != 0 || debug::voldemort)
        return;

    if (cc.sp >= -100)
    {
        cc.sp -= delta;
    }
}



void heal_sp(Character& cc, int delta)
{
    cc.sp += delta;
    if (cc.sp > cc.max_sp)
    {
        cc.sp = cc.max_sp;
    }
}



void damage_insanity(Character& cc, int delta)
{
    if (cc.quality >= Quality::miracle)
        return;

    int resistance = std::max(sdata(54, cc.index) / 50, 1);
    if (resistance > 10)
        return;

    delta /= resistance;
    if (cc.index < 16)
    {
        if (trait(166))
        {
            delta -= rnd(4);
        }
    }
    delta = std::max(delta, 0);
    cc.insanity += delta;
    if (rnd(10) == 0 || rnd_capped(delta + 1) > 5 ||
        rnd_capped(cc.insanity + 1) > 50)
    {
        status_ailment_damage(cc, StatusAilment::insane, 100);
    }
}



void heal_insanity(Character& cc, int delta)
{
    cc.insanity -= delta;
    if (cc.insanity < 0)
    {
        cc.insanity = 0;
    }
}



void character_drops_item()
{
    if (rc == 0)
    {
        if (game_data.executing_immediate_quest_type != 0)
        {
            return;
        }
        for (auto&& item : inv.for_chara(cdata[rc]))
        {
            if (item.number() == 0)
            {
                continue;
            }
            if (map_data.refresh_type == 0)
            {
                if (item.body_part != 0)
                {
                    continue;
                }
                if (item.is_precious())
                {
                    continue;
                }
                if (rnd(3))
                {
                    continue;
                }
            }
            else if (rnd(5))
            {
                continue;
            }
            if (the_item_db[itemid2int(item.id)]->is_cargo)
            {
                if (map_data.type != mdata_t::MapType::world_map &&
                    map_data.type != mdata_t::MapType::player_owned &&
                    map_data.type != mdata_t::MapType::town &&
                    map_data.type != mdata_t::MapType::field &&
                    map_data.type != mdata_t::MapType::shelter &&
                    map_data.type != mdata_t::MapType::guild)
                {
                    continue;
                }
                else if (rnd(2))
                {
                    continue;
                }
            }
            f = 0;
            if (item.body_part != 0)
            {
                if (rnd(10))
                {
                    f = 1;
                }
                if (item.curse_state == CurseState::blessed)
                {
                    if (rnd(2))
                    {
                        f = 1;
                    }
                }
                if (is_cursed(item.curse_state))
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
                if (item.curse_state == CurseState::doomed)
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
            }
            else if (item.identify_state == IdentifyState::completely)
            {
                if (rnd(4))
                {
                    f = 1;
                }
            }
            if (f)
            {
                continue;
            }
            if (item.body_part != 0)
            {
                cdata[rc].body_parts[item.body_part - 100] =
                    cdata[rc].body_parts[item.body_part - 100] / 10000 * 10000;
                item.body_part = 0;
            }
            f = 0;
            if (!item.is_precious())
            {
                if (rnd(4) == 0)
                {
                    f = 1;
                }
                if (item.curse_state == CurseState::blessed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 0;
                    }
                }
                if (is_cursed(item.curse_state))
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
                if (item.curse_state == CurseState::doomed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
            }
            if (f)
            {
                item.remove();
                continue;
            }
            item.position.x = cdata[rc].position.x;
            item.position.y = cdata[rc].position.y;
            if (!item_stack(-1, item).stacked)
            {
                const auto slot = inv_getfreeid(-1);
                if (slot == -1)
                {
                    break;
                }
                item_copy(item, inv[slot]);
                inv[slot].own_state = -2;
            }
            item.remove();
        }
        cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
        create_pcpic(cdata.player());
        return;
    }
    else
    {
        if (rc < 16)
        {
            if (cdata[rc].has_own_sprite() == 1)
            {
                create_pcpic(cdata[rc]);
            }
        }
        if (cdata[rc].relationship == 10)
        {
            return;
        }
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (cdata[rc].id == CharaId::tourist)
        {
            return;
        }
        if (cdata[rc].id == CharaId::palmian_elite_soldier)
        {
            return;
        }
    }
    if (cdata[rc].is_contracting())
    {
        return;
    }
    if (cdata[rc].splits() || cdata[rc].splits2())
    {
        if (rnd(6))
        {
            return;
        }
    }
    for (auto&& item : inv.for_chara(cdata[rc]))
    {
        if (item.number() == 0)
        {
            continue;
        }
        f = 0;
        if (cdata[rc].character_role == 20)
        {
            break;
        }
        if (item.quality > Quality::miracle || item.id == ItemId::platinum_coin)
        {
            f = 1;
        }
        if (rnd(30) == 0)
        {
            f = 1;
        }
        if (cdata[rc].quality >= Quality::miracle)
        {
            if (rnd(2) == 0)
            {
                f = 1;
            }
        }
        if (cdata[rc].character_role == 13)
        {
            if (rnd(5))
            {
                f = 0;
            }
        }
        if (game_data.current_map == mdata_t::MapId::arena)
        {
            if (rnd(4))
            {
                f = 0;
            }
        }
        if (item.quality == Quality::special)
        {
            f = 1;
        }
        if (item.is_quest_target())
        {
            f = 1;
        }
        if (f == 0)
        {
            continue;
        }
        if (catitem != 0 && !item.is_blessed_by_ehekatl() &&
            is_equipment(the_item_db[itemid2int(item.id)]->category) &&
            item.quality >= Quality::great)
        {
            if (rnd(3))
            {
                txt(i18n::s.get(
                        "core.misc.black_cat_licks", cdata[catitem], item),
                    Message::color{ColorIndex::cyan});
                item.is_blessed_by_ehekatl() = true;
                reftype = (int)the_item_db[itemid2int(item.id)]->category;
                enchantment_add(
                    item,
                    enchantment_generate(enchantment_gen_level(rnd(4))),
                    enchantment_gen_p());
                animeload(8, rc);
            }
        }
        if (item.body_part != 0)
        {
            cdata[rc].body_parts[item.body_part - 100] =
                cdata[rc].body_parts[item.body_part - 100] / 10000 * 10000;
            item.body_part = 0;
        }
        item.position.x = cdata[rc].position.x;
        item.position.y = cdata[rc].position.y;
        itemturn(item);
        if (!item_stack(-1, item).stacked)
        {
            const auto slot = inv_getfreeid(-1);
            if (slot == -1)
            {
                break;
            }
            item_copy(item, inv[slot]);
        }
        item.remove();
    }
    if (cdata[rc].quality >= Quality::miracle || rnd(20) == 0 ||
        cdata[rc].drops_gold() == 1 || rc < 16)
    {
        if (cdata[rc].gold > 0)
        {
            flt();
            itemcreate_extra_inv(
                54,
                cdata[rc].position,
                cdata[rc].gold / (1 + 3 * (cdata[rc].drops_gold() == 0)));
            cdata[rc].gold -=
                cdata[rc].gold / (1 + 3 * (cdata[rc].drops_gold() == 0));
        }
    }

    switch (class_get_item_type(data::InstanceId{cdatan(3, rc)}))
    {
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 7:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 3:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 4:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 5:
        if (rnd(50) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    }

    switch (chara_db_get_item_type(cdata[rc].id))
    {
    case 3:
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 62000;
            flttypeminor = 0;
            if (const auto item =
                    itemcreate_extra_inv(0, cdata[rc].position, 0))
            {
                remain_make(*item, cdata[rc]);
            }
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 62000;
            flttypeminor = 0;
            if (const auto item =
                    itemcreate_extra_inv(0, cdata[rc].position, 0))
            {
                remain_make(*item, cdata[rc]);
            }
        }
        break;
    case 6:
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 32000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 34000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 4:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    case 5:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(15) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate_extra_inv(0, cdata[rc].position, 0);
        }
        break;
    }

    if (rnd(40) == 0)
    {
        p = 0;
        flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
        flttypemajor = 62000;
        flttypeminor = 0;
        if (const auto item = itemcreate_extra_inv(0, cdata[rc].position, 0))
        {
            remain_make(*item, cdata[rc]);
        }
    }
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
        return;
    }
    if (game_data.current_map != mdata_t::MapId::arena &&
        cdata[rc].character_role != 20)
    {
        if (rnd(175) == 0 || cdata[rc].quality == Quality::special || 0 ||
            (cdata[rc].quality == Quality::miracle && rnd(2) == 0) ||
            (cdata[rc].quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            if (const auto item =
                    itemcreate_extra_inv(504, cdata[rc].position, 0))
            {
                item->param1 = cdata[rc].image;
                item->subname = charaid2int(cdata[rc].id);
                cell_refresh(item->position.x, item->position.y);
            }
        }
        if (rnd(175) == 0 || cdata[rc].quality == Quality::special || 0 ||
            (cdata[rc].quality == Quality::miracle && rnd(2) == 0) ||
            (cdata[rc].quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            if (const auto item =
                    itemcreate_extra_inv(503, cdata[rc].position, 0))
            {
                item->param1 = cdata[rc].image;
                item->subname = charaid2int(cdata[rc].id);
                cell_refresh(item->position.x, item->position.y);
            }
        }
    }
    if (cdata[rc].character_role == 1010)
    {
        flt();
        if (const auto item = itemcreate_extra_inv(361, cdata[rc].position, 0))
        {
            item->param1 = cdata[rc].shop_store_id;
            item->own_state = 2;
        }
    }
    if (rollanatomy == 1 || cdata[rc].quality >= Quality::miracle || 0 ||
        cdata[rc].is_livestock() == 1 || 0)
    {
        flt();
        if (const auto item = itemcreate_extra_inv(204, cdata[rc].position, 0))
        {
            remain_make(*item, cdata[rc]);
            if (cdata[rc].is_livestock() == 1)
            {
                if (sdata(161, 0) != 0)
                {
                    item->modify_number(
                        rnd(1 + (sdata(161, 0) > cdata[rc].level)));
                }
            }
        }
    }

    // ../../runtime/mod/core/api/impl/chara_drop.lua
    lua::call("core.Impl.chara_drop.drop_from_chara", lua::handle(cdata[rc]));

    cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
    if (cdata[rc].character_role == 13)
    {
        supply_new_equipment();
    }
}



void check_kill(int killer_chara_index, int victim_chara_index)
{
    int p_at_m137 = 0;
    if (game_data.current_map == mdata_t::MapId::pet_arena ||
        game_data.current_map == mdata_t::MapId::show_house ||
        game_data.current_map == mdata_t::MapId::arena)
    {
        return;
    }
    p_at_m137 = 0;
    if (killer_chara_index >= 0)
    {
        if (killer_chara_index == 0 ||
            cdata[killer_chara_index].relationship >= 10)
        {
            if (victim_chara_index >= 16)
            {
                ++game_data.kill_count;
                if (cdata[victim_chara_index].id ==
                    int2charaid(game_data.guild.fighters_guild_target))
                {
                    if (game_data.guild.fighters_guild_quota > 0)
                    {
                        --game_data.guild.fighters_guild_quota;
                    }
                }
                if (cdata[victim_chara_index].original_relationship >= 0)
                {
                    p_at_m137 = -2;
                }
                if (cdata[victim_chara_index].id == CharaId::rich_person)
                {
                    p_at_m137 = -15;
                }
                if (cdata[victim_chara_index].id == CharaId::noble_child)
                {
                    p_at_m137 = -10;
                }
                if (cdata[victim_chara_index].id == CharaId::tourist)
                {
                    p_at_m137 = -5;
                }
                if ((cdata[victim_chara_index].character_role >= 1000 &&
                     cdata[victim_chara_index].character_role < 2000) ||
                    cdata[victim_chara_index].character_role == 2003)
                {
                    p_at_m137 = -10;
                }
                if (cdata[victim_chara_index].character_role == 13)
                {
                    chara_modify_impression(cdata[victim_chara_index], -25);
                }
            }
        }
        if (cdata[killer_chara_index].relationship >= 10)
        {
            if (killer_chara_index != 0)
            {
                if (cdata[killer_chara_index].impression < 200)
                {
                    if (rnd(2))
                    {
                        chara_modify_impression(cdata[killer_chara_index], 1);
                        cdata[killer_chara_index].emotion_icon = 317;
                    }
                }
                else if (rnd(10) == 0)
                {
                    chara_modify_impression(cdata[killer_chara_index], 1);
                    cdata[killer_chara_index].emotion_icon = 317;
                }
            }
        }
    }
    if (p_at_m137 != 0)
    {
        modify_karma(cdata.player(), p_at_m137);
    }
}



void heal_both_rider_and_mount()
{
    int subloop = 0;
    subloop = 1;
    if (game_data.mount != 0)
    {
        if (tc == game_data.mount || tc == 0)
        {
            subloop = 2;
            if (tc == game_data.mount)
            {
                tc(1) = 0;
            }
            else
            {
                tc(1) = game_data.mount;
            }
        }
    }
    for (int cnt = 0, cnt_end = (subloop); cnt < cnt_end; ++cnt)
    {
        const auto amount = roll(dice1, dice2, bonus);
        heal_hp(cdata[tc(cnt)], amount);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::fear);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::poisoned, 50);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::confused, 50);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::dimmed, 30);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::bleeding, 20);
        heal_insanity(cdata[tc(cnt)], 1);
        if (is_in_fov(cdata[tc(cnt)]))
        {
            add_damage_popup(std::to_string(amount), tc(cnt), {127, 255, 127});
        }
    }
}



void heal_completely()
{
    cdata[tc].poisoned = 0;
    cdata[tc].sleep = 0;
    cdata[tc].confused = 0;
    cdata[tc].blind = 0;
    cdata[tc].paralyzed = 0;
    cdata[tc].choked = 0;
    cdata[tc].dimmed = 0;
    cdata[tc].drunk = 0;
    cdata[tc].bleeding = 0;
    game_data.continuous_active_hours = 0;
    cdata[tc].hp = cdata[tc].max_hp;
    cdata[tc].mp = cdata[tc].max_mp;
    cdata[tc].sp = cdata[tc].max_sp;
}

} // namespace elona
