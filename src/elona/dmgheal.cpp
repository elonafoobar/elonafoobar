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
#include "inventory.hpp"
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
    OptionalItemRef heaviest_item;
    int heaviest_weight = 0;

    for (const auto& item : g_inv.for_chara(chara))
    {
        if (item->weight > heaviest_weight)
        {
            heaviest_item = item;
            heaviest_weight = item->weight;
        }
    }

    std::string heaviest_item_name;
    if (heaviest_item)
    {
        heaviest_item_name = itemname(heaviest_item.unwrap());
    }
    else
    {
        heaviest_item_name =
            i18n::s.get_enum_property("core.death_by.other", "backpack", 6);
    }

    txt(i18n::s.get_enum_property(
        "core.death_by.other", "text", 6, chara, heaviest_item_name));
    if (chara.is_player())
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

    if (victim.role == Role::none)
    {
        new_state = Character::State::empty;
    }
    else if (victim.role == Role::adventurer)
    {
        new_state = Character::State::adventurer_dead;
        victim.time_to_revive = game_data.date.hours() + 24 + rnd(12);
    }
    else
    {
        new_state = Character::State::villager_dead;
        victim.time_to_revive = game_data.date.hours() + 48;
    }

    if (victim.is_ally())
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

    optional_ref<Character> attacker = none;
    if (damage_source >= 0)
    {
        attacker = cdata[damage_source];
    }

    // E.g., the case that the casted spell is the subject.
    // It controls 3rd-person singular present 's' in English message.
    const bool damage_statements_subject_is_noncharacter = txt3rd == 1;

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
        int resistance = victim.get_skill(element).level / 50;
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
        dmg_at_m141 = dmg_at_m141 * 100 / (victim.get_skill(60).level / 2 + 50);
    }
    if (attacker && attacker->is_player())
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

    if (victim.is_player() && cdata.player().god_id == core_god::opatos)
    {
        dmg_at_m141 = dmg_at_m141 * 90 / 100;
    }

    if (debug_has_wizard_flag("core.wizard.no_hp_damage") && victim.is_player())
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
    if (victim.is_player())
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
        if (victim.is_player_or_ally())
        {
            for (auto&& chara : cdata.player_and_allies())
            {
                if (victim == chara)
                {
                    continue;
                }
                if (chara.state() != Character::State::alive)
                {
                    continue;
                }
                if (chara.has_lay_hand() == 0)
                {
                    continue;
                }
                if (chara.is_lay_hand_available() == 0)
                {
                    continue;
                }
                chara.is_lay_hand_available() = false;
                txt(i18n::s.get("core.damage.lay_hand", chara),
                    Message::color{ColorIndex::cyan});
                txt(i18n::s.get("core.damage.is_healed", victim));
                victim.hp = victim.max_hp / 2;
                MiracleAnimation(MiracleAnimation::Mode::target_one, victim)
                    .play();
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
            txteledmg(0, none, victim, element);
        }
        else if (game_data.proc_damage_events_flag == 2)
        {
            Message::instance().continue_sentence();
            assert(attacker);
            if (damage_level == -1)
            {
                if (damage_statements_subject_is_noncharacter)
                {
                    txt(i18n::s.get(
                        "core.damage.levels.scratch.by_spell", victim));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.damage.levels.scratch.by_chara",
                        victim,
                        *attacker));
                }
            }
            if (damage_level == 0)
            {
                if (damage_statements_subject_is_noncharacter)
                {
                    txt(i18n::s.get(
                            "core.damage.levels.slightly.by_spell", victim),
                        Message::color{ColorIndex::orange});
                }
                else
                {
                    txt(i18n::s.get(
                            "core.damage.levels.slightly.by_chara",
                            victim,
                            *attacker),
                        Message::color{ColorIndex::orange});
                }
            }
            if (damage_level == 1)
            {
                if (damage_statements_subject_is_noncharacter)
                {
                    txt(i18n::s.get(
                            "core.damage.levels.moderately.by_spell", victim),
                        Message::color{ColorIndex::gold});
                }
                else
                {
                    txt(i18n::s.get(
                            "core.damage.levels.moderately.by_chara",
                            victim,
                            *attacker),
                        Message::color{ColorIndex::gold});
                }
            }
            if (damage_level == 2)
            {
                if (damage_statements_subject_is_noncharacter)
                {
                    txt(i18n::s.get(
                            "core.damage.levels.severely.by_spell", victim),
                        Message::color{ColorIndex::light_red});
                }
                else
                {
                    txt(i18n::s.get(
                            "core.damage.levels.severely.by_chara",
                            victim,
                            *attacker),
                        Message::color{ColorIndex::light_red});
                }
            }
            if (damage_level >= 3)
            {
                if (damage_statements_subject_is_noncharacter)
                {
                    txt(i18n::s.get(
                            "core.damage.levels.critically.by_spell", victim),
                        Message::color{ColorIndex::red});
                }
                else
                {
                    txt(i18n::s.get(
                            "core.damage.levels.critically.by_chara",
                            victim,
                            *attacker),
                        Message::color{ColorIndex::red});
                }
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
            if (!victim.is_player())
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
                        if (attacker && attacker->is_player())
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
                if (victim.is_player())
                {
                    modify_ether_disease_stage(rnd_capped(element_power + 1));
                }
            }
            if (element == 63)
            {
                if (victim.is_player() || rnd(3) == 0)
                {
                    item_acid(victim);
                }
            }
        }
        if ((element == 50 || damage_source == -9) && victim.wet == 0)
        {
            item_fire(g_inv.for_chara(victim));
        }
        if (element == 51)
        {
            item_cold(g_inv.for_chara(victim));
        }
        if (victim.sleep != 0)
        {
            if (element != 54 && element != 58 && element != 59)
            {
                victim.sleep = 0;
                txt(i18n::s.get("core.damage.sleep_is_disturbed", victim));
            }
        }
        if (attacker && attacker->is_player())
        {
            chara_act_hostile_action(cdata.player(), victim);
            game_data.chara_last_attacked_by_player = victim.index;
        }
        if (victim.is_player())
        {
            if (g_config.sound())
            {
                if (g_config.heartbeat())
                {
                    int threshold =
                        config_get<int>("core.screen.heartbeat_threshold");
                    if (victim.hp < victim.max_hp * (threshold * 0.01))
                    {
                        snd("core.Heart1");
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
            if (!attacker->is_player())
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
                if (!victim.is_player())
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
                if (!victim.is_player_or_ally() &&
                    game_data.proc_damage_events_flag == 2)
                {
                    Message::instance().continue_sentence();
                    if (damage_statements_subject_is_noncharacter)
                    {
                        txteledmg(1, none, victim, element);
                    }
                    else
                    {
                        txteledmg(1, *attacker, victim, element);
                    }
                }
                else
                {
                    txteledmg(2, none, victim, element);
                }
            }
            else
            {
                int death_type = rnd(4);
                if (death_type == 0)
                {
                    if (!victim.is_player_or_ally() &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        if (damage_statements_subject_is_noncharacter)
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.transformed_into_meat.active.by_spell",
                                victim));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.transformed_into_meat.active.by_chara",
                                victim,
                                *attacker));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.transformed_into_meat.passive",
                            victim));
                    }
                }
                if (death_type == 1)
                {
                    if (!victim.is_player_or_ally() &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        if (damage_statements_subject_is_noncharacter)
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.destroyed.active.by_spell",
                                victim));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.destroyed.active.by_chara",
                                victim,
                                *attacker));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.destroyed.passive", victim));
                    }
                }
                if (death_type == 2)
                {
                    if (!victim.is_player_or_ally() &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        if (damage_statements_subject_is_noncharacter)
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.minced.active.by_spell",
                                victim));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.minced.active.by_chara",
                                victim,
                                *attacker));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.minced.passive", victim));
                    }
                }
                if (death_type == 3)
                {
                    if (!victim.is_player_or_ally() &&
                        game_data.proc_damage_events_flag == 2)
                    {
                        Message::instance().continue_sentence();
                        if (damage_statements_subject_is_noncharacter)
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.killed.active.by_spell",
                                victim));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.death_by.chara.killed.active.by_chara",
                                victim,
                                *attacker));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.death_by.chara.killed.passive", victim));
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
                if (victim.is_player())
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
        if (game_data.mount != victim.index || victim.is_player())
        {
            cell_removechara(victim.position);
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
                animeblood(victim, 1, element);
            }
            spillfrag(victim.position.x, victim.position.y, 3);
        }
        else
        {
            sound_kill(victim.position);
            animeblood(victim, 0, element);
            spillblood(victim.position.x, victim.position.y, 4);
        }
        if (victim.is_player())
        {
            ++game_data.death_count;
        }
        if (victim.index == game_data.chara_last_attacked_by_player)
        {
            game_data.chara_last_attacked_by_player = 0;
        }
        if (attacker)
        {
            if (!attacker->is_player())
            {
                chara_custom_talk(*attacker, 103);
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
            if (attacker->is_player())
            {
                game_data.sleep_experience += gained_exp;
            }
            attacker->hate = 0;
            if (attacker->is_player_or_ally())
            {
                attacker->enemy_id = 0;
                cdata.player().enemy_id = 0;
                game_data.chara_last_attacked_by_player = 0;
            }
        }
        if (!victim.is_player())
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
        if (!victim.is_player())
        {
            ++npcmemory(0, charaid2int(victim.id));
            chara_custom_talk(victim, 102);
            if (victim.is_player_or_ally())
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
        check_kill(attacker, victim);
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
            if (int(std::sqrt(attacker->get_skill(161).level)) > rnd(150))
            {
                rollanatomy = 1;
            }
            chara_gain_skill_exp(*attacker, 161, 10 + rollanatomy * 4);
        }
        character_drops_item(victim);
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
            for (auto&& chara : cdata.all())
            {
                if (chara.state() != Character::State::alive)
                {
                    continue;
                }
                for (int buff_index = 0; buff_index < 16; ++buff_index)
                {
                    if (chara.buffs[buff_index].id == 0)
                    {
                        break;
                    }
                    if (chara.buffs[buff_index].id == 16)
                    {
                        buff_delete(chara, buff_index);
                        --buff_index;
                        continue;
                    }
                }
            }
        }
        if (attacker && attacker->is_player())
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



void heal_hp(Character& chara, int delta)
{
    chara.hp += delta;
    if (chara.hp > chara.max_hp)
    {
        chara.hp = chara.max_hp;
    }
}



void damage_mp(Character& chara, int delta)
{
    chara.mp -= delta;
    if (chara.mp < -999999)
    {
        chara.mp = -999999;
    }
    if (chara.mp < 0)
    {
        chara_gain_exp_mana_capacity(chara);
        auto damage = -chara.mp * 400 / (100 + chara.get_skill(164).level * 10);
        if (chara.is_player())
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
        txt(i18n::s.get("core.damage.magic_reaction_hurts", chara));
        damage_hp(chara, damage, -2);
    }
}



void heal_mp(Character& chara, int delta)
{
    chara.mp += delta;
    if (chara.mp > chara.max_mp)
    {
        chara.mp = chara.max_mp;
    }
}



bool action_sp(Character& chara, int sp)
{
    if (!chara.is_player())
        return true;
    if (debug_has_wizard_flag("core.wizard.no_sp_damage"))
        return true;

    damage_sp(chara, sp);
    return chara.sp >= 50 || chara.sp >= rnd(75);
}



void damage_sp(Character& chara, int delta)
{
    if (!chara.is_player())
        return;
    if (debug_has_wizard_flag("core.wizard.no_sp_damage"))
        return;

    if (chara.sp >= -100)
    {
        chara.sp -= delta;
    }
}



void heal_sp(Character& chara, int delta)
{
    chara.sp += delta;
    if (chara.sp > chara.max_sp)
    {
        chara.sp = chara.max_sp;
    }
}



void damage_insanity(Character& chara, int delta)
{
    if (chara.quality >= Quality::miracle)
        return;

    int resistance = std::max(chara.get_skill(54).level / 50, 1);
    if (resistance > 10)
        return;

    delta /= resistance;
    if (chara.is_player_or_ally())
    {
        if (trait(166))
        {
            delta -= rnd(4);
        }
    }
    delta = std::max(delta, 0);
    chara.insanity += delta;
    if (rnd(10) == 0 || rnd_capped(delta + 1) > 5 ||
        rnd_capped(chara.insanity + 1) > 50)
    {
        status_ailment_damage(chara, StatusAilment::insane, 100);
    }
}



void heal_insanity(Character& chara, int delta)
{
    chara.insanity -= delta;
    if (chara.insanity < 0)
    {
        chara.insanity = 0;
    }
}



void character_drops_item(Character& victim)
{
    if (victim.is_player())
    {
        if (game_data.executing_immediate_quest_type != 0)
        {
            return;
        }
        for (const auto& item : g_inv.for_chara(victim))
        {
            if (map_data.refresh_type == 0)
            {
                if (item->body_part != 0)
                {
                    continue;
                }
                if (item->is_precious())
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
            if (the_item_db[item->id]->is_cargo)
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
            if (item->body_part != 0)
            {
                if (rnd(10))
                {
                    f = 1;
                }
                if (item->curse_state == CurseState::blessed)
                {
                    if (rnd(2))
                    {
                        f = 1;
                    }
                }
                if (is_cursed(item->curse_state))
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
                if (item->curse_state == CurseState::doomed)
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
            }
            else if (item->identify_state == IdentifyState::completely)
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
            if (item->body_part != 0)
            {
                victim.equipment_slots[item->body_part - 100].unequip();
                item->body_part = 0;
            }
            f = 0;
            if (!item->is_precious())
            {
                if (rnd(4) == 0)
                {
                    f = 1;
                }
                if (item->curse_state == CurseState::blessed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 0;
                    }
                }
                if (is_cursed(item->curse_state))
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
                if (item->curse_state == CurseState::doomed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
            }
            if (f)
            {
                item->remove();
                continue;
            }
            item->set_position(victim.position);
            item->set_position(victim.position);
            if (!inv_stack(g_inv.ground(), item).stacked)
            {
                const auto slot = inv_make_free_slot_force(g_inv.ground());
                const auto dropped_item =
                    item_separate(item, slot, item->number());
                dropped_item->own_state = OwnState::lost;
            }
        }
        cell_refresh(victim.position.x, victim.position.y);
        create_pcpic(cdata.player());
        return;
    }
    else
    {
        if (victim.is_player_or_ally())
        {
            if (victim.has_own_sprite() == 1)
            {
                create_pcpic(victim);
            }
        }
        if (victim.relationship == 10)
        {
            return;
        }
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (victim.id == CharaId::tourist)
        {
            return;
        }
        if (victim.id == CharaId::palmian_elite_soldier)
        {
            return;
        }
    }
    if (victim.is_contracting())
    {
        return;
    }
    if (victim.splits() || victim.splits2())
    {
        if (rnd(6))
        {
            return;
        }
    }
    for (const auto& item : g_inv.for_chara(victim))
    {
        f = 0;
        if (victim.role == Role::user)
        {
            break;
        }
        if (item->quality > Quality::miracle ||
            item->id == "core.platinum_coin")
        {
            f = 1;
        }
        if (rnd(30) == 0)
        {
            f = 1;
        }
        if (victim.quality >= Quality::miracle)
        {
            if (rnd(2) == 0)
            {
                f = 1;
            }
        }
        if (victim.role == Role::adventurer)
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
        if (item->quality == Quality::special)
        {
            f = 1;
        }
        if (item->is_quest_target())
        {
            f = 1;
        }
        if (f == 0)
        {
            continue;
        }
        if (catitem != 0 && !item->is_blessed_by_ehekatl() &&
            is_equipment(the_item_db[item->id]->category) &&
            item->quality >= Quality::great)
        {
            if (rnd(3))
            {
                txt(i18n::s.get(
                        "core.misc.black_cat_licks", cdata[catitem], item),
                    Message::color{ColorIndex::cyan});
                item->is_blessed_by_ehekatl() = true;
                reftype = (int)the_item_db[item->id]->category;
                enchantment_add(
                    item,
                    enchantment_generate(enchantment_gen_level(rnd(4))),
                    enchantment_gen_p());
                animeload(8, victim);
            }
        }
        if (item->body_part != 0)
        {
            victim.equipment_slots[item->body_part - 100].unequip();
            item->body_part = 0;
        }
        item->set_position(victim.position);
        itemturn(item);
        if (!inv_stack(g_inv.ground(), item).stacked)
        {
            const auto slot = inv_make_free_slot_force(g_inv.ground());
            item_separate(item, slot, item->number());
        }
    }
    if (victim.quality >= Quality::miracle || rnd(20) == 0 ||
        victim.drops_gold() == 1 || victim.is_player_or_ally())
    {
        if (victim.gold > 0)
        {
            flt();
            itemcreate_map_inv(
                54,
                victim.position,
                victim.gold / (1 + 3 * (victim.drops_gold() == 0)));
            victim.gold -= victim.gold / (1 + 3 * (victim.drops_gold() == 0));
        }
    }

    switch (class_get_item_type(victim.class_))
    {
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 7:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 3:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 4:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 5:
        if (rnd(50) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    }

    switch (chara_db_get_item_type(victim.id))
    {
    case 3:
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 62000;
            flttypeminor = 0;
            if (const auto item = itemcreate_map_inv(0, victim.position, 0))
            {
                remain_make(item.unwrap(), victim);
            }
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 62000;
            flttypeminor = 0;
            if (const auto item = itemcreate_map_inv(0, victim.position, 0))
            {
                remain_make(item.unwrap(), victim);
            }
        }
        break;
    case 6:
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 32000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 34000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 4:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    case 5:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(15) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate_map_inv(0, victim.position, 0);
        }
        break;
    }

    if (rnd(40) == 0)
    {
        p = 0;
        flt(calcobjlv(victim.level), calcfixlv(Quality::bad));
        flttypemajor = 62000;
        flttypeminor = 0;
        if (const auto item = itemcreate_map_inv(0, victim.position, 0))
        {
            remain_make(item.unwrap(), victim);
        }
    }
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        cell_refresh(victim.position.x, victim.position.y);
        return;
    }
    if (game_data.current_map != mdata_t::MapId::arena &&
        victim.role != Role::user)
    {
        if (rnd(175) == 0 || victim.quality == Quality::special || 0 ||
            (victim.quality == Quality::miracle && rnd(2) == 0) ||
            (victim.quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            if (const auto item = itemcreate_map_inv(504, victim.position, 0))
            {
                item->param1 = victim.image;
                item->subname = charaid2int(victim.id);
            }
        }
        if (rnd(175) == 0 || victim.quality == Quality::special || 0 ||
            (victim.quality == Quality::miracle && rnd(2) == 0) ||
            (victim.quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            if (const auto item = itemcreate_map_inv(503, victim.position, 0))
            {
                item->param1 = victim.image;
                item->subname = charaid2int(victim.id);
            }
        }
    }
    if (victim.role == Role::wandering_vendor)
    {
        flt();
        if (const auto item = itemcreate_map_inv(361, victim.position, 0))
        {
            item->param1 = victim.shop_store_id;
            item->own_state = OwnState::shop;
        }
    }
    if (rollanatomy == 1 || victim.quality >= Quality::miracle || 0 ||
        victim.is_livestock() == 1 || 0)
    {
        flt();
        if (const auto item = itemcreate_map_inv(204, victim.position, 0))
        {
            remain_make(item.unwrap(), victim);
            if (victim.is_livestock() == 1)
            {
                if (cdata.player().get_skill(161).level != 0)
                {
                    item->modify_number(rnd(
                        1 +
                        (cdata.player().get_skill(161).level > victim.level)));
                }
            }
        }
    }

    // ../../runtime/mod/core/api/impl/chara_drop.lua
    lua::call("core.Impl.chara_drop.drop_from_chara", lua::handle(victim));

    cell_refresh(victim.position.x, victim.position.y);
    if (victim.role == Role::adventurer)
    {
        supply_new_equipment(victim);
    }
}



void check_kill(optional_ref<Character> killer_chara, Character& victim)
{
    if (game_data.current_map == mdata_t::MapId::pet_arena ||
        game_data.current_map == mdata_t::MapId::show_house ||
        game_data.current_map == mdata_t::MapId::arena)
    {
        return;
    }
    if (!killer_chara)
    {
        return;
    }

    int karma = 0;
    if (killer_chara->is_player() || killer_chara->relationship >= 10)
    {
        if (!victim.is_player_or_ally())
        {
            ++game_data.kill_count;
            if (victim.id == int2charaid(game_data.guild.fighters_guild_target))
            {
                if (game_data.guild.fighters_guild_quota > 0)
                {
                    --game_data.guild.fighters_guild_quota;
                }
            }
            if (victim.original_relationship >= 0)
            {
                karma = -2;
            }
            if (victim.id == CharaId::rich_person)
            {
                karma = -15;
            }
            if (victim.id == CharaId::noble_child)
            {
                karma = -10;
            }
            if (victim.id == CharaId::tourist)
            {
                karma = -5;
            }
            if (is_shopkeeper(victim.role))
            {
                karma = -10;
            }
            if (victim.role == Role::adventurer)
            {
                chara_modify_impression(victim, -25);
            }
        }
    }
    if (killer_chara->relationship >= 10)
    {
        if (!killer_chara->is_player())
        {
            if (killer_chara->impression < 200)
            {
                if (rnd(2))
                {
                    chara_modify_impression(*killer_chara, 1);
                    killer_chara->emotion_icon = 317;
                }
            }
            else if (rnd(10) == 0)
            {
                chara_modify_impression(*killer_chara, 1);
                killer_chara->emotion_icon = 317;
            }
        }
    }
    if (karma != 0)
    {
        modify_karma(cdata.player(), karma);
    }
}



void heal_both_rider_and_mount(Character& target)
{
    std::vector<std::reference_wrapper<Character>> targets;
    targets.push_back(std::ref(target));
    if (game_data.mount != 0)
    {
        if (target.index == game_data.mount || target.is_player())
        {
            if (target.index == game_data.mount)
            {
                targets.push_back(std::ref(cdata.player()));
            }
            else
            {
                targets.push_back(std::ref(cdata[game_data.mount]));
            }
        }
    }

    for (auto&& target_rw : targets)
    {
        auto&& target = target_rw.get();
        const auto amount = roll(dice1, dice2, bonus);
        heal_hp(target, amount);
        status_ailment_heal(target, StatusAilment::fear);
        status_ailment_heal(target, StatusAilment::poisoned, 50);
        status_ailment_heal(target, StatusAilment::confused, 50);
        status_ailment_heal(target, StatusAilment::dimmed, 30);
        status_ailment_heal(target, StatusAilment::bleeding, 20);
        heal_insanity(target, 1);
        if (is_in_fov(target))
        {
            add_damage_popup(
                std::to_string(amount), target.index, {127, 255, 127});
        }
    }
}



void heal_completely(Character& target)
{
    target.poisoned = 0;
    target.sleep = 0;
    target.confused = 0;
    target.blind = 0;
    target.paralyzed = 0;
    target.choked = 0;
    target.dimmed = 0;
    target.drunk = 0;
    target.bleeding = 0;
    game_data.continuous_active_hours = 0;
    target.hp = target.max_hp;
    target.mp = target.max_mp;
    target.sp = target.max_sp;
}

} // namespace elona
