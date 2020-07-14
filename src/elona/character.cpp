#include "character.hpp"

#include <cassert>

#include <type_traits>

#include "../util/fileutil.hpp"
#include "../util/range.hpp"
#include "../util/strutil.hpp"
#include "ability.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "command.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_buff.hpp"
#include "data/types/type_item.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/character_instance_event.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "race.hpp"
#include "random.hpp"
#include "randomgen.hpp"
#include "status_ailment.hpp"
#include "text.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int _calc_chara_generation_rate(const CharacterData& data)
{
    const auto R = data.rarity;
    const auto D = std::abs(data.level - objlv);
    const auto C = data.coefficient;

    return R / (500 + D * C) + 1;
}



int _get_random_npc_id()
{
    WeightedRandomSampler<int> sampler;

    for (const auto& data : the_character_db.values())
    {
        if (data.level > objlv)
            continue;
        if (fltselect != data.fltselect)
            continue;
        if (fltselect == 2 && npcmemory(1, data.legacy_id) != 0)
            continue;
        if (flttypemajor != 0 && flttypemajor != data.category)
            continue;
        if (!fltnrace(0).empty() && fltnrace(0) != data.race_id.get())
            continue;
        if (filtermax != 0)
        {
            // FIXME: use std::all_of
            bool ok = true;
            for (int i = 0; i < filtermax; ++i)
            {
                if (data.filter.find(filtern(i)) == std::string::npos)
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                continue;
        }
        sampler.add(data.legacy_id, _calc_chara_generation_rate(data));
    }

    return sampler.get().value_or(0);
}



optional<int> chara_create_internal(int slot, int chara_id)
{
    if (slot == -1)
    {
        slot = chara_get_free_slot();
        if (slot == -1)
        {
            return none;
        }
    }
    chara_delete(slot);
    if (slot == 0)
    {
        p = 10;
    }
    else
    {
        p = 4;
    }
    if (chara_id == -1)
    {
        if (fltselect == 0 && filtermax == 0 && fltnrace(0).empty())
        {
            if (fixlv == Quality::great)
            {
                if (rnd(20) == 0)
                {
                    fltselect = 2;
                }
            }
            if (fixlv == Quality::miracle)
            {
                if (rnd(10) == 0)
                {
                    fltselect = 2;
                }
            }
        }
        chara_id = _get_random_npc_id();
        if (chara_id == 0)
        {
            if (fltselect == 2 || fixlv == Quality::special)
            {
                fixlv = Quality::miracle;
            }
            flt(objlv + 10, fixlv);
            chara_id = _get_random_npc_id();
        }
    }

    cm = slot + 1;
    cmshade = 0;
    ++npcmemory(1, chara_id);
    if (chara_id == 323)
    {
        if (rnd(5))
        {
            objlv *= 2;
            if (fixlv >= Quality::miracle)
            {
                fixlv = Quality::great;
            }
            cmshade = 1;
            flt(objlv, fixlv);
            chara_id = _get_random_npc_id();
        }
    }
    if (game_data.current_map == mdata_t::MapId::the_void)
    {
        if (!novoidlv)
        {
            voidlv = game_data.current_dungeon_level / 50 * 50;
        }
    }
    novoidlv = 0;
    if (chara_id == 343)
    {
        // Vanila-copatible CNPC is not supported now.
    }
    else
    {
        chara_db_set_stats(cdata[slot], int2charaid(chara_id));
    }
    if (cmshade)
    {
        cdata[slot].name = i18n::s.get("core.chara.job.shade");
        cdata[slot].image = 280;
    }
    cdata[slot].quality = static_cast<Quality>(fixlv);
    cdata[slot].index = slot;
    initialize_character(cdata[slot]);

    rtval = slot;
    return slot;
}



bool is_in_map(const Position& position)
{
    const auto x = position.x;
    const auto y = position.y;
    return 0 <= x && x < map_data.width && 0 <= y && y < map_data.height;
}



Position get_random_position(const Position& base_position, int n)
{
    return {
        base_position.x - rnd(n) + rnd(n), base_position.y - rnd(n) + rnd(n)};
}



optional<Position> get_free_space(
    const Position& base_position,
    int number_of_trials)
{
    for (int i = 0; i < number_of_trials; ++i)
    {
        const auto pos = get_random_position(base_position, 2);
        const auto x = pos.x;
        const auto y = pos.y;
        if (!is_in_map(pos))
        {
            continue;
        }
        if (cell_data.at(x, y).feats != 0)
        {
            if (chip_data.for_feat(x, y).effect & 4)
            {
                continue;
            }
        }
        if (cell_data.at(x, y).chara_index_plus_one == 0)
        {
            if (!(chip_data.for_cell(x, y).effect & 4))
            {
                return pos;
            }
        }
    }

    return none;
}



int chara_get_free_slot_force()
{
    int ret = chara_get_free_slot();
    if (ret != -1)
    {
        return ret;
    }

    std::vector<int> slots;
    for (auto&& chara : cdata.others())
    {
        if (chara.state() == Character::State::alive &&
            chara.role == Role::none)
        {
            slots.push_back(chara.index);
        }
    }

    if (slots.empty())
    {
        // FIXME: do not throw exception.
        throw std::runtime_error("chara_get_free_slot_force() failed");
    }

    ret = choice(slots);
    // Force to destroy the character in `ret`.
    chara_vanquish(cdata[ret]);
    return ret;
}



bool can_place_character_at(const Position& position, bool allow_stairs)
{
    // Out of range
    if (position.x < 0 || map_data.width <= position.x || position.y < 0 ||
        map_data.height <= position.y)
        return false;

    // Wall
    if (chip_data.for_cell(position.x, position.y).effect & 4)
        return false;

    // There is someone.
    if (cell_data.at(position.x, position.y).chara_index_plus_one != 0)
        return false;

    if (cell_data.at(position.x, position.y).feats != 0)
    {
        // There is an object which prevents from walking through.
        if (chip_data.for_feat(position.x, position.y).effect & 4)
            return false;

        cell_featread(position.x, position.y);
        // Upstairs/downstairs.
        if (feat(1) == 11 || feat(1) == 10)
        {
            if (!allow_stairs)
            {
                return false;
            }
        }
    }

    return true;
}



bool chara_place_internal(
    Character& chara,
    optional<Position> position,
    bool enemy_respawn)
{
    int x;
    int y;

    for (int i = 0;; ++i)
    {
        if (i == 99)
        {
            if (chara.index >= 57)
            {
                // Give up.
                return false;
            }
        }
        if (i > 99)
        {
            if (map_data.width == 0)
            {
                return false;
            }
            y = (i - 100) / map_data.width;
            x = (i - 100) % map_data.width;
            if (y >= map_data.height)
            {
                if (chara.index != 0)
                {
                    return false;
                }
                else
                {
                    // Make the cell placable.
                    x = rnd(map_data.width);
                    y = rnd(map_data.height);
                    // FIXME: I refered to oor, but I think it is not perfect.
                    // Break wall.
                    if (chip_data.for_cell(x, y).effect & 4)
                    {
                        cell_data.at(x, y).chip_id_actual = tile_tunnel;
                    }
                    // Delete someone there.
                    // TODO: Work around. Need delete him/her *completely*.
                    if (cell_data.at(x, y).chara_index_plus_one != 0)
                    {
                        cell_data.at(x, y).chara_index_plus_one = 0;
                    }
                    if (cell_data.at(x, y).feats != 0)
                    {
                        cell_featread(x, y);
                        if (feat(1) == 21)
                        {
                            // Open closed doors.
                            cell_featset(x, y, tile_dooropen, 20, 0, -1);
                        }
                        else if (feat(1) == 22)
                        {
                            // Reveal hidden path.
                            cell_data.at(x, y).feats = 0;
                        }
                    }
                    assert(can_place_character_at({x, y}, true));
                }
            }
        }
        else
        {
            if (position)
            {
                x = position->x + rnd(i + 1) - rnd(i + 1);
                y = position->y + rnd(i + 1) - rnd(i + 1);
            }
            else
            {
                x = rnd(map_data.width - 4) + 2;
                y = rnd(map_data.height - 4) + 2;
            }
            if (enemy_respawn && i < 20)
            {
                const auto threshold = cdata.player().vision_distance / 2;
                if (std::abs(cdata.player().position.x - x) <= threshold &&
                    std::abs(cdata.player().position.y - x) <= threshold)
                {
                    // Too close
                    continue;
                }
            }
        }

        if (can_place_character_at({x, y}, chara.index == 0 || position))
        {
            break;
        }
    }

    // Do place character.
    chara.initial_position = chara.position = {x, y};
    cell_data.at(x, y).chara_index_plus_one = chara.index + 1;

    return true; // placed successfully.
}



void failed_to_place_character(Character& chara)
{
    if (chara.index < 16)
    {
        chara.set_state(Character::State::pet_in_other_map);
        txt(i18n::s.get("core.chara.place_failure.ally", chara));
    }
    else
    {
        txt(i18n::s.get("core.chara.place_failure.other", chara));
        chara.set_state(Character::State::empty);
        // Exclude town residents because they occupy character slots even
        // if they are dead.
        modify_crowd_density(chara.index, -1);
    }
    if (chara.role != Role::none)
    {
        chara.set_state(Character::State::villager_dead);
    }
    if (chara.role == Role::adventurer)
    {
        chara.set_state(Character::State::adventurer_dead);
        chara.time_to_revive = game_data.date.hours() + 24 + rnd(12);
    }
}

} // namespace



int traveldone = 0;



// see command.cpp
extern int refdiff;



CData cdata;


elona_vector1<std::string> usertxt;



Character::Character()
    : growth_buffs(10)
    , equipment_slots(30)
    , buffs(16)
    , attr_adjs(10)
{
}


void Character::set_state(Character::State new_state)
{
    bool was_alive = !this->is_dead();
    bool was_empty = this->state_ == Character::State::empty;

    if (was_empty && new_state != Character::State::empty)
    {
        // Clean up any stale handles that may have been left over from a
        // character in the same index being removed.
        lua::lua->get_handle_manager().remove_chara_handle_run_callbacks(*this);
    }

    this->state_ = new_state;

    if (was_alive && this->is_dead())
    {
        chara_killed(*this);
    }

    if (was_empty && this->state_ != Character::State::empty)
    {
        lua::lua->get_handle_manager().create_chara_handle_run_callbacks(*this);
    }
    else if (!was_empty && this->state_ == Character::State::empty)
    {
        chara_remove(*this);
    }
}


void Character::clear()
{
    copy({}, *this);
}


void Character::clear_flags()
{
    for (size_t i = 0; i < 32 * 30; ++i)
    {
        _flags[i] = false;
    }
}


CData::CData()
    : storage(ELONA_MAX_CHARACTERS)
{
    for (size_t i = 0; i < storage.size(); ++i)
    {
        storage[i].index = static_cast<int>(i);
    }
}



bool chara_place(Character& chara)
{
    if (chara.index == cdata.tmp().index)
    {
        chara.set_state(Character::State::empty);
        return false;
    }

    if (game_data.mount != 0 && game_data.mount == chara.index)
    {
        chara.position = cdata.player().position;
        return true;
    }

    const auto success = chara_place_internal(
        chara,
        cxinit >= 0 ? optional<Position>({cxinit, cyinit}) : none,
        cxinit == -2);
    if (!success)
    {
        failed_to_place_character(chara);
    }

    return success;
}



void initialize_character(Character& chara)
{
    if (mode != 1)
    {
        chara_add_quality_parens(chara);
    }
    chara.interest = 100;
    chara.impression = 50;
    chara.vision_distance = 14;
    if (chara.id == CharaId::maid)
    {
        chara.image = rnd(33) * 2 + chara.sex + 1;
    }
    if (chara.index == 0)
    {
        chara.nutrition = 9000;
    }
    else
    {
        chara.nutrition = 5000 + rnd(4000);
    }
    chara.height = chara.height + rnd_capped((chara.height / 5 + 1)) -
        rnd_capped((chara.height / 5 + 1));
    chara.weight = chara.height * chara.height * (rnd(6) + 18) / 10000;
    update_required_experience(chara);
    chara_init_common_skills(chara);
    if (chara.portrait == "__random__")
    {
        const auto index = std::to_string(1 + rnd(32));
        const auto man_or_woman = chara.sex ? "woman" : "man";
        chara.portrait = "core."s + man_or_woman + index;
    }
    chara.personality = rnd(4);
    chara.talk_type = rnd(7);
    supply_initial_equipments(chara);
    chara_refresh(chara);
    modify_crowd_density(chara.index, 1);
    chara.hp = chara.max_hp;
    chara.mp = chara.max_mp;
    chara.sp = chara.max_sp;
    if (chara.index == 0)
    {
        game_data.initial_cart_limit = 80000;
        game_data.current_cart_limit = game_data.initial_cart_limit;
    }
    if (chara.has_lay_hand())
    {
        chara.is_lay_hand_available() = true;
    }

    chara.set_state(Character::State::alive);

    cm = 0;
}



optional_ref<Character> chara_create(int slot, int chara_id, int x, int y)
{
    bool success = false;

    if (x == -3)
    {
        cxinit = -1;
        cyinit = -1;
    }
    else
    {
        cxinit = x;
        cyinit = y;
    }
    const auto result =
        chara_create_internal(slot, chara_id == 0 ? -1 : chara_id);
    initlv = 0;
    voidlv = 0;
    if (result)
    {
        if (*result == 56)
        {
            cdata[*result].set_state(Character::State::empty);
            --npcmemory(1, charaid2int(cdata[*result].id));
            return cdata.tmp();
        }
        if (*result != 0)
        {
            if (x != -1)
            {
                success = chara_place(cdata[*result]);
            }
        }
    }
    else
    {
        return none;
    }

    if (success)
    {
        return cdata[*result];
    }
    else
    {
        return none;
    }
}



void chara_refresh(Character& chara)
{
    int rp2 = 0;
    int rp3 = 0;
    if (chara.index == 0)
    {
        game_data.seven_league_boot_effect = 0;
        game_data.ether_disease_speed = 0;
        game_data.protects_from_etherwind = 0;
        game_data.protects_from_bad_weather = 0;
        game_data.light = 70;
        game_data.catches_god_signal = 0;
        game_data.reveals_religion = 0;
    }
    for (int cnt = 0; cnt < 600; ++cnt)
    {
        sdata(cnt, chara.index) = sdata.get(cnt, chara.index).original_level;
    }
    if (chara.index == 0)
    {
        chara.clear_flags();
        if (trait(161) != 0)
        {
            for (auto&& equipment_slot : chara.equipment_slots)
            {
                if (!equipment_slot.equipment)
                {
                    continue;
                }
                if (equipment_slot.equipment->weight >= 1000)
                {
                    equipment_slot.equipment->body_part = 0;
                    equipment_slot.unequip();
                }
            }
        }
    }
    else if (chara.id == CharaId::user)
    {
        // Vanilla-compatible CNPC is not supported now.
    }
    else
    {
        for (size_t i = 0; i < 32 * 30; ++i)
        {
            chara._flags[i] =
                the_character_db[charaid2int(chara.id)]->_flags[i];
        }
    }
    for (auto&& growth_buff : chara.growth_buffs)
    {
        growth_buff = 0;
    }
    chara.dv = 0;
    chara.pv = 0;
    chara.hit_bonus = 0;
    chara.damage_bonus = 0;
    chara.combat_style.reset();
    attacknum = 0;
    chara.rate_to_pierce = 0;
    chara.rate_of_critical_hit = 0;
    chara.curse_power = 0;
    chara.extra_attack = 0;
    chara.extra_shot = 0;
    chara.sum_of_equipment_weight = 0;
    chara.decrease_physical_damage = 0;
    chara.nullify_damage = 0;
    chara.cut_counterattack = 0;

    for (const auto& equipment_slot : chara.equipment_slots)
    {
        if (!equipment_slot.equipment)
        {
            continue;
        }
        const auto equipment = equipment_slot.equipment;
        chara.sum_of_equipment_weight += equipment->weight;
        if (equipment->skill == 168)
        {
            chara.combat_style.set_shield();
        }
        chara.dv += equipment->dv;
        chara.pv += equipment->pv;
        if (equipment->dice_x == 0)
        {
            chara.hit_bonus += equipment->hit_bonus;
            chara.damage_bonus += equipment->damage_bonus;
            chara.pv += equipment->enhancement * 2 +
                (equipment->curse_state == CurseState::blessed) * 2;
        }
        else if (equipment_slot.type == 5)
        {
            ++attacknum;
        }
        if (equipment->curse_state == CurseState::cursed)
        {
            chara.curse_power += 20;
        }
        if (equipment->curse_state == CurseState::doomed)
        {
            chara.curse_power += 100;
        }
        if (equipment->material == 8)
        {
            if (chara.index == 0)
            {
                game_data.ether_disease_speed += 5;
            }
        }

        for (const auto& enchantment : equipment->enchantments)
        {
            if (enchantment.id == 0)
            {
                break;
            }
            rp2 = enchantment.id;
            if (rp2 >= 10000)
            {
                rp3 = rp2 % 10000;
                rp2 = rp2 / 10000;
                if (rp2 == 1)
                {
                    sdata(rp3, chara.index) += enchantment.power / 50 + 1;
                    continue;
                }
                if (rp2 == 2)
                {
                    sdata(rp3, chara.index) += enchantment.power / 2;
                    if (sdata(rp3, chara.index) < 0)
                    {
                        sdata(rp3, chara.index) = 1;
                    }
                    continue;
                }
                if (rp2 == 3)
                {
                    if (sdata.get(rp3, chara.index).original_level != 0)
                    {
                        sdata(rp3, chara.index) += enchantment.power / 50 + 1;
                        if (sdata(rp3, chara.index) < 1)
                        {
                            sdata(rp3, chara.index) = 1;
                        }
                    }
                    continue;
                }
            }
            else
            {
                if (rp2 == 56)
                {
                    if (chara.index == 0)
                    {
                        game_data.catches_god_signal = 1;
                        continue;
                    }
                }
                if (rp2 == 59)
                {
                    if (chara.index == 0)
                    {
                        game_data.reveals_religion = 1;
                        continue;
                    }
                }
                if (rp2 == 29)
                {
                    sdata(18, chara.index) += enchantment.power / 50 + 1;
                    if (chara.index == 0)
                    {
                        game_data.seven_league_boot_effect +=
                            enchantment.power / 8;
                        continue;
                    }
                }
                if (rp2 == 32)
                {
                    chara.is_floating() = true;
                    continue;
                }
                if (rp2 == 35)
                {
                    chara.can_see_invisible() = true;
                    continue;
                }
                if (rp2 == 23)
                {
                    chara.is_immune_to_blindness() = true;
                    continue;
                }
                if (rp2 == 24)
                {
                    chara.is_immune_to_paralyzation() = true;
                    continue;
                }
                if (rp2 == 25)
                {
                    chara.is_immune_to_confusion() = true;
                    continue;
                }
                if (rp2 == 26)
                {
                    chara.is_immune_to_fear() = true;
                    continue;
                }
                if (rp2 == 27)
                {
                    chara.is_immune_to_sleep() = true;
                    continue;
                }
                if (rp2 == 28)
                {
                    chara.is_immune_to_poison() = true;
                    continue;
                }
                if (rp2 == 42)
                {
                    chara.can_digest_rotten_food() = true;
                    continue;
                }
                if (rp2 == 41)
                {
                    chara.is_protected_from_thieves() = true;
                    continue;
                }
                if (rp2 == 55)
                {
                    chara.cures_bleeding_quickly() = true;
                    continue;
                }
                if (rp2 == 52)
                {
                    chara.decrease_physical_damage +=
                        enchantment.power / 40 + 5;
                    continue;
                }
                if (rp2 == 53)
                {
                    chara.nullify_damage += enchantment.power / 60 + 3;
                    continue;
                }
                if (rp2 == 54)
                {
                    chara.cut_counterattack += enchantment.power / 5;
                    continue;
                }
                if (rp2 == 44)
                {
                    chara.rate_of_critical_hit += enchantment.power / 50;
                    continue;
                }
                if (rp2 == 39)
                {
                    chara.rate_to_pierce += enchantment.power / 50;
                    continue;
                }
                if (rp2 == 50)
                {
                    chara.extra_attack += enchantment.power / 15;
                    continue;
                }
                if (rp2 == 51)
                {
                    chara.extra_shot += enchantment.power / 15;
                    chara.extra_shot = 100;
                    continue;
                }
                if (rp2 == 21 || rp2 == 45 || rp2 == 46 || rp2 == 47)
                {
                    chara.has_cursed_equipments() = true;
                    continue;
                }
                if (chara.index == 0)
                {
                    if (rp2 == 30)
                    {
                        game_data.protects_from_etherwind = 1;
                        continue;
                    }
                    if (rp2 == 31)
                    {
                        game_data.protects_from_bad_weather = 1;
                        continue;
                    }
                }
            }
        }
    }

    if (refreshmode == 1)
    {
        buff += u8"\n"s;
        buff += u8"<title1>◆ 装備による能力の修正<def>\n"s;
        for (int cnt = 0; cnt < 600; ++cnt)
        {
            sdata(cnt, 56) = sdata.get(cnt, chara.index).original_level;
            if (sdata(cnt, 56) != sdata(cnt, chara.index))
            {
                cnvbonus(cnt, sdata(cnt, chara.index) - sdata(cnt, 56));
            }
        }
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (chara.attr_adjs[cnt] != 0)
        {
            if (chara.quality >= Quality::miracle)
            {
                if (chara.attr_adjs[cnt] <
                    sdata.get(10 + cnt, chara.index).original_level / 5)
                {
                    chara.attr_adjs[cnt] =
                        sdata.get(10 + cnt, chara.index).original_level / 5;
                }
            }
            sdata(10 + cnt, chara.index) += chara.attr_adjs[cnt];
        }
        if (sdata(10 + cnt, chara.index) < 1)
        {
            sdata(10 + cnt, chara.index) = 1;
        }
    }
    if (chara.index == 0)
    {
        god_apply_blessing(chara);
        for (int cnt = 0; cnt < 217; ++cnt)
        {
            if (trait(cnt) != 0)
            {
                trait_get_info(1, cnt);
            }
        }
    }
    if (chara.combat_style.shield())
    {
        if (chara.pv > 0)
        {
            chara.pv = chara.pv *
                (120 + int(std::sqrt(sdata(168, chara.index))) * 2) / 100;
        }
    }
    else if (attacknum == 1)
    {
        chara.combat_style.set_two_hand();
    }
    else if (attacknum != 0)
    {
        chara.combat_style.set_dual_wield();
    }
    chara.max_mp = clamp(
                       ((sdata(16, chara.index) * 2 + sdata(15, chara.index) +
                         sdata(14, chara.index) / 3) *
                            chara.level / 25 +
                        sdata(16, chara.index)),
                       1,
                       1000000) *
        sdata(3, chara.index) / 100;
    chara.max_hp = clamp(
                       ((sdata(11, chara.index) * 2 + sdata(10, chara.index) +
                         sdata(15, chara.index) / 3) *
                            chara.level / 25 +
                        sdata(11, chara.index)),
                       1,
                       1000000) *
            sdata(2, chara.index) / 100 +
        5;
    chara.max_sp = 100 + (sdata(15, chara.index) + sdata(11, chara.index)) / 5 +
        trait(24) * 8;
    if (chara.max_mp < 1)
    {
        chara.max_mp = 1;
    }
    if (chara.max_hp < 1)
    {
        chara.max_hp = 1;
    }
    if (chara.index >= ELONA_MAX_PARTY_CHARACTERS || false)
    {
        chara.dv = chara.level / 2 +
            chara.dv * chara.dv_correction_value / 100 +
            chara.dv_correction_value - 100;
        chara.pv = chara.level +
            (chara.pv + chara.level / 2 + chara.pv_correction_value / 25) *
                chara.pv_correction_value / 100;
        if (chara.quality == Quality::great)
        {
            chara.max_hp = chara.max_hp * 3 / 2;
        }
        if (chara.quality >= Quality::miracle)
        {
            chara.max_hp = chara.max_hp * 5;
        }
    }
    else
    {
        chara.max_hp += 10;
    }
    for (auto&& buff : chara.buffs)
    {
        if (buff.id == 0)
        {
            break;
        }
        buff_apply(chara, *the_buff_db.get_id_from_legacy(buff.id), buff.power);
    }
    if (chara.combat_style.dual_wield())
    {
        chara.extra_attack +=
            int(std::sqrt(sdata(166, chara.index))) * 3 / 2 + 4;
    }
    if (sdata(186, chara.index))
    {
        chara.rate_of_critical_hit +=
            int(std::sqrt(sdata(186, chara.index))) + 2;
    }
    if (chara.rate_of_critical_hit > 30)
    {
        chara.hit_bonus += (chara.rate_of_critical_hit - 30) * 2;
        chara.rate_of_critical_hit = 30;
    }
    refresh_burden_state();
    refresh_speed(chara);
    chara.needs_refreshing_status() = false;

    lua::lua->get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_refreshed", chara));
}



int relation_between(const Character& a, const Character& b)
{
    if (a.relationship >= -2)
    {
        if (b.relationship <= -3)
        {
            return -3;
        }
    }
    else if (b.relationship >= -2)
    {
        return -3;
    }
    return 0;
}



optional_ref<Character> chara_find(data::InstanceId chara_id)
{
    // Note: if `chara_id` not found, `ensure()` throws an exception.
    int legacy_id = the_character_db.ensure(chara_id).legacy_id;

    for (auto&& chara : cdata.others())
    {
        if (chara.state() != Character::State::villager_dead)
        {
            if (chara.state() != Character::State::alive)
            {
                continue;
            }
        }
        if (chara.id == int2charaid(legacy_id))
        {
            return chara;
        }
    }
    return none;
}



int chara_find_ally(int id)
{
    for (auto&& ally : cdata.allies())
    {
        if (ally.state() != Character::State::alive)
        {
            continue;
        }
        if (ally.id == int2charaid(id))
        {
            return ally.index;
        }
    }
    return -1;
}



int chara_get_free_slot()
{
    for (auto&& i : cdata.others())
    {
        if (i.state() == Character::State::empty)
        {
            return i.index;
        }
    }
    return -1;
}



int chara_get_free_slot_ally()
{
    const auto max_allies = clamp(sdata(17, 0) / 5 + 1, 2, 15);
    for (int i = 1; i < max_allies + 1; ++i)
    {
        if (cdata[i].state() != Character::State::empty)
        {
            continue;
        }
        return i;
    }
    return 0;
}


int chara_custom_talk(int chara_index, int talk_type)
{
    std::vector<std::string> talk_file_buffer;

    bool use_external_file = false;

    if (cdata[chara_index].has_custom_talk())
    {
        const auto filepath =
            filesystem::dirs::user() / u8"talk" / cdata[chara_index].talk;
        if (!fs::exists(filepath))
            return 0;
        range::copy(
            fileutil::read_by_line(filepath),
            std::back_inserter(talk_file_buffer));
        use_external_file = true;
    }
    else if (cdata[chara_index].id == CharaId::user)
    {
        talk_file_buffer =
            strutil::split_lines(usertxt(cdata[chara_index].cnpc_id));
        use_external_file = true;
    }

    if (use_external_file)
    {
        std::string tag;
        switch (talk_type)
        {
        case 101: tag = u8"%txtAggro"s; break;
        case 103: tag = u8"%txtKilled"s; break;
        case 102: tag = u8"%txtDead"s; break;
        case 104: tag = u8"%txtWelcome"s; break;
        case 100: tag = u8"%txtCalm"s; break;
        case 106: tag = u8"%txtDialog"s; break;
        default: assert(0);
        }

        tag += u8"," + i18n::s.get("core.meta.tag");
        const auto start_text = range::find_if(
            talk_file_buffer,
            [&](const auto& line) { return strutil::contains(line, tag); });
        if (start_text == std::end(talk_file_buffer))
        {
            throw std::runtime_error(u8"Error: fail to load custom talk");
        }
        const auto end_text = std::find_if(
            std::next(start_text),
            std::end(talk_file_buffer),
            [](const auto& line) { return strutil::contains(line, u8"%"); });
        if (end_text == std::end(talk_file_buffer))
        {
            throw std::runtime_error(u8"Error: fail to load custom talk");
        }

        // Example:
        // %txtDialog,EN                              <- start_text
        // Elona foobar is one of the Elona variants.
        // Elona is one of the rogue-like games.
        // %END                                       <- end_text
        const auto number_of_lines_plus_1 = std::distance(start_text, end_text);
        if (number_of_lines_plus_1 == 1)
        {
            throw std::runtime_error(u8"Error: fail to load custom talk");
        }
        else
        {
            std::vector<std::string> lines;
            std::copy(
                std::next(start_text), end_text, std::back_inserter(lines));
            const auto line = lines[rnd(int(lines.size()))];
            if (!line.empty())
            {
                if (talk_type == 106)
                {
                    buff = line;
                }
                else
                {
                    txt(line, Message::color{ColorIndex::cyan});
                }
            }
        }
        return 1;
    }

    if (talk_type == 106)
        return 0;

    if (cdata[chara_index].can_talk != 0)
    {
        chara_db_get_talk(cdata[chara_index].id, talk_type);
        return 1;
    }
    return 0;
}



int chara_impression_level(int impression)
{
    if (impression < 10)
        return 0;
    if (impression < 25)
        return 1;
    if (impression < 40)
        return 2;
    if (impression < 75)
        return 3;
    if (impression < 100)
        return 4;
    if (impression < 150)
        return 5;
    if (impression < 200)
        return 6;
    if (impression < 300)
        return 7;
    else
        return 8;
}



void chara_modify_impression(Character& chara, int delta)
{
    int level1 = chara_impression_level(chara.impression);
    if (delta >= 0)
    {
        delta = delta * 100 / (50 + level1 * level1 * level1);
        if (delta == 0)
        {
            if (level1 < rnd(10))
            {
                delta = 1;
            }
        }
    }
    chara.impression += delta;
    int level2 = chara_impression_level(chara.impression);
    if (level1 > level2)
    {
        txt(i18n::s.get(
                "core.chara.impression.lose",
                chara,
                i18n::s.get_enum("core.ui.impression", level2)),
            Message::color{ColorIndex::purple});
    }
    else if (level2 > level1)
    {
        if (chara.relationship != -3)
        {
            txt(i18n::s.get(
                    "core.chara.impression.gain",
                    chara,
                    i18n::s.get_enum("core.ui.impression", level2)),
                Message::color{ColorIndex::green});
        }
    }
}



void chara_vanquish(Character& chara)
{
    if (chara.index == 0)
        return;

    if (chara.index == game_data.mount)
    {
        ride_end();
    }
    else if (
        chara.state() == Character::State::alive ||
        chara.state() == Character::State::servant_being_selected)
    {
        cell_data.at(chara.position.x, chara.position.y).chara_index_plus_one =
            0;
    }
    chara.set_state(Character::State::empty);
    chara.role = Role::none;
    if (chara.shop_store_id != 0)
    {
        const auto storage_filename = filepathutil::u8path(
            "shop"s + std::to_string(chara.shop_store_id) + ".s2");
        const auto storage_filepath =
            filesystem::dirs::tmp() / storage_filename;
        tmpload(storage_filename);
        if (fs::exists(storage_filepath))
        {
            fs::remove(storage_filepath);
            Save::instance().remove(storage_filepath.filename());
        }
        chara.shop_store_id = 0;
    }
    modify_crowd_density(chara.index, -1);
}



int chara_copy(const Character& source)
{
    // Find empty slot.
    const auto slot = chara_get_free_slot();
    if (slot == -1)
    {
        return -1;
    }
    auto& destination = cdata[slot];

    // Find free space.
    const auto pos = get_free_space(source.position, 4);
    if (!pos)
    {
        return -1;
    }
    const auto x = pos->x;
    const auto y = pos->y;

    if (source.state() != Character::State::empty)
    {
        // Clean up any stale handles that may have been left over from a
        // character in the same index being removed.
        lua::lua->get_handle_manager().remove_chara_handle_run_callbacks(
            cdata[slot]);
    }

    // Delete completely the previous character in `slot`.
    chara_delete(slot);

    // Copy from `source` to `destination`.
    Character::copy(source, destination);
    sdata.copy(slot, source.index);
    lua::lua->get_handle_manager().create_chara_handle_run_callbacks(
        destination);

    // Place `destination` to the found free space.
    cell_data.at(x, y).chara_index_plus_one = slot + 1;
    destination.position = *pos;

    // Reset some fields which should not be copied.
    destination.impression = 0;
    destination.gold = 0;
    destination.original_relationship = -3;
    destination.has_own_sprite() = false;
    destination.is_livestock() = false;
    destination.is_married() = false;
    destination.is_ridden() = false;
    destination.needs_refreshing_status() = true;
    destination.is_hung_on_sand_bag() = false;

    // Unequip all gears.
    for (auto&& equipment_slot : destination.equipment_slots)
    {
        equipment_slot.unequip();
    }

    // Increase crowd density.
    modify_crowd_density(slot, 1);
    // Increase the generation counter.
    ++npcmemory(1, charaid2int(destination.id));

    return slot;
}



void chara_killed(Character& chara)
{
    if (chara.state() == Character::State::empty)
    {
        // This character slot is invalid, and can be overwritten by newly
        // created characters at any time. Defer removing its handle until a new
        // character is created in its slot.
    }
    else if (
        chara.state() == Character::State::villager_dead ||
        chara.state() == Character::State::adventurer_dead ||
        chara.state() == Character::State::pet_dead)
    {
        // This character revives.
    }
    else
    {
        assert(0);
    }
}



void chara_remove(Character& chara)
{
    chara.set_state(Character::State::empty);
}



void chara_delete(int chara_index)
{
    if (chara_index != -1)
    {
        chara_remove(cdata[chara_index]);
    }

    for (const auto& item : g_inv.for_chara(cdata[chara_index]))
    {
        item->remove();
    }
    sdata.clear(chara_index);
    cdata[chara_index].clear();
}



void chara_relocate(
    Character& source,
    optional_ref<Character> destination_slot,
    CharaRelocationMode mode)
{
    if (source.index == game_data.mount)
    {
        ride_end();
        source.position = cdata.player().position;
    }

    auto& destination = destination_slot ? *destination_slot
                                         : cdata[chara_get_free_slot_force()];

    // Backups for changing
    Position position;
    Position initial_position;
    int relationship;
    int original_relationship;
    int hate;
    int enemy_id;
    int hp;
    if (mode == CharaRelocationMode::change)
    {
        position = destination.position;
        initial_position = destination.initial_position;
        relationship = destination.relationship;
        original_relationship = destination.original_relationship;
        hate = destination.hate;
        enemy_id = destination.enemy_id;
        hp = destination.hp;
    }

    // Move all items in `source`'s inventory to `destination`'s.
    Inventory::move_all(g_inv.for_chara(source), g_inv.for_chara(destination));

    // Clear some fields which should not be copied.
    source.ai_item = nullptr;
    source.is_livestock() = false;

    // Copy from `source` to `destination` and clear `source`
    sdata.copy(destination.index, source.index);
    sdata.clear(source.index);

    Character::copy(source, destination);
    source.clear();

    if (mode == CharaRelocationMode::normal)
    {
        // Relocate the corresponding Lua reference, if it exists. It may
        // not always exist, since if the mode is "change" the
        // source's state will be empty. If the source's state is empty, the
        // destination slot will instead be set to empty as well.
        lua::lua->get_handle_manager().relocate_handle(source, destination);
    }
    else
    {
        // Clear the source's handle, as it is now invalid. Preserve the handle
        // that exists in the slot already.
        lua::lua->get_handle_manager().remove_chara_handle_run_callbacks(
            source);
    }

    // Unequip all gears.
    for (auto&& equipment_slot : destination.equipment_slots)
    {
        equipment_slot.unequip();
    }

    if (mode == CharaRelocationMode::change)
    {
        // Set the destination as "alive" without altering any handle state,
        // since a valid handle was just moved into the destination's index and
        // it shouldn't be regenerated.
        destination.set_state_raw(Character::State::alive);

        destination.position = position;
        destination.initial_position = initial_position;
        destination.relationship = relationship;
        destination.original_relationship = original_relationship;
        destination.hate = hate;
        destination.enemy_id = enemy_id;
        destination.hp = hp;
        cell_data.at(destination.position.x, destination.position.y)
            .chara_index_plus_one = destination.index + 1;
    }
    else
    {
        if (source.index != 56)
        {
            cell_data.at(destination.position.x, destination.position.y)
                .chara_index_plus_one = destination.index + 1;
        }
        else
        {
            destination.set_state_raw(Character::State::alive);
            cxinit = cdata.player().position.x;
            cyinit = cdata.player().position.y;
            chara_place(destination);
        }
        destination.enemy_id = 0;
        destination.hate = 0;
    }

    // Lose resistance.
    if (destination.index < 16)
    {
        for (int element = 50; element < 61; ++element)
        {
            auto resistance = 100;
            if (sdata.get(element, destination.index).original_level >= 500 ||
                sdata.get(element, destination.index).original_level <= 100)
            {
                resistance =
                    sdata.get(element, destination.index).original_level;
            }
            if (resistance > 500)
            {
                resistance = 500;
            }
            sdata.get(element, destination.index).original_level = resistance;
            sdata.get(element, destination.index).experience = 0;
            sdata.get(element, destination.index).potential = 0;
        }
    }

    wear_most_valuable_equipment_for_all_body_parts(destination);
    chara_refresh(destination);

    modify_crowd_density(destination.index, 1);
    modify_crowd_density(source.index, -1);
}



void chara_set_ai_item(Character& chara, ItemRef item)
{
    const auto category = the_item_db[itemid2int(item->id)]->category;
    if (category == ItemCategory::food || category == ItemCategory::potion ||
        category == ItemCategory::scroll)
    {
        chara.ai_item = item;
    }
}



int chara_armor_class(const Character& chara)
{
    if (chara.sum_of_equipment_weight >= 35000)
    {
        return 169;
    }
    else if (chara.sum_of_equipment_weight >= 15000)
    {
        return 170;
    }
    else
    {
        return 171;
    }
}



int chara_breed_power(const Character& chara)
{
    const auto breed_power_base = the_race_db[chara.race]->breed_power;
    return breed_power_base * 100 / (100 + chara.level * 5);
}



bool belong_to_same_team(const Character& c1, const Character& c2)
{
    return (c1.relationship >= 0 && c2.relationship >= 0) ||
        (c1.relationship == -1 && c2.relationship == -1) ||
        (c1.relationship <= -2 && c2.relationship <= -2);
}



void chara_add_quality_parens(Character& chara)
{
    if (fixlv == Quality::miracle)
    {
        chara.name = i18n::s.get("core.chara.quality.miracle", chara.name);
        chara.level = chara.level * 10 / 8;
    }
    else if (fixlv == Quality::godly)
    {
        chara.name = i18n::s.get("core.chara.quality.godly", chara.name);
        chara.level = chara.level * 10 / 6;
    }
}



void initialize_pc_character()
{
    cdata.player().quality = Quality::good;
    cdata.player().relationship = 10;
    cdata.player().original_relationship = 10;
    cdata.player().has_own_sprite() = true;
    flt();
    if (const auto item = itemcreate_player_inv(333, 0))
    {
        item->set_number(8);
    }
    flt();
    if (const auto item = itemcreate_player_inv(233, 0))
    {
        item->set_number(4);
    }
    flt();
    if (const auto item = itemcreate_player_inv(31, 0))
    {
        item->set_number(2);
    }
    if (sdata(150, 0) == 0)
    {
        flt();
        if (const auto item = itemcreate_player_inv(68, 0))
        {
            item->set_number(3);
        }
    }
    if (cdata.player().class_ == "core.pianist")
    {
        flt();
        itemcreate_player_inv(88, 0);
    }
    if (cdata.player().class_ == "core.farmer")
    {
        flt();
        itemcreate_player_inv(256, 0);
    }
    if (cdata.player().class_ == "core.wizard" ||
        cdata.player().class_ == "core.warmage")
    {
        flt();
        itemcreate_player_inv(116, 0);
        flt();
        if (const auto item = itemcreate_player_inv(257, 0))
        {
            item->set_number(3);
        }
    }
    if (cdata.player().class_ == "core.priest")
    {
        flt();
        if (const auto item = itemcreate_player_inv(249, 0))
        {
            item->set_number(3);
        }
        flt();
        itemcreate_player_inv(378, 0);
    }
    gain_race_feat();
    cdata.player().skill_bonus = 5 + trait(154);
    cdata.player().total_skill_bonus = 5 + trait(154);
    for (const auto& item : g_inv.pc())
    {
        item->identify_state = IdentifyState::completely;
    }
    chara_refresh(cdata.player());
}



void go_hostile()
{
    for (auto&& chara : cdata.others())
    {
        if (chara.role == Role::guard || chara.role == Role::shop_guard ||
            chara.role == Role::wandering_vendor)
        {
            chara.relationship = -3;
            chara.hate = 80;
            chara.emotion_icon = 218;
        }
    }
}



void ride_begin(int mount)
{
    txt(i18n::s.get(
        "core.magic.mount.mount.execute",
        cdata[mount],
        cdata[mount].current_speed));
    cdata[mount].is_ridden() = true;
    cell_data.at(cdata[mount].position.x, cdata[mount].position.y)
        .chara_index_plus_one = 0;
    game_data.mount = mount;
    create_pcpic(cdata.player());
    cdata[game_data.mount].activity.finish();
    refresh_speed(cdata[game_data.mount]);
    txt(""s + cdata[mount].current_speed + u8") "s);
    if (cdata[game_data.mount].is_suitable_for_mount())
    {
        txt(i18n::s.get("core.magic.mount.mount.suitable"));
    }
    else if (cdata[game_data.mount].is_unsuitable_for_mount())
    {
        txt(i18n::s.get("core.magic.mount.mount.unsuitable"));
    }
}



void ride_end()
{
    int mount = game_data.mount;
    cdata[mount].is_ridden() = false;
    cdata[mount].activity.finish();
    game_data.mount = 0;
    create_pcpic(cdata.player());
    refresh_speed(cdata[mount]);
}



void turn_aggro(int chara_index, int target_index, int hate)
{
    if (target_index < 16)
    {
        cdata[chara_index].relationship = -3;
    }
    cdata[chara_index].hate = hate;
    cdata[chara_index].emotion_icon = 218;
    cdata[chara_index].enemy_id = target_index;
}



void make_sound(
    int source_x,
    int source_y,
    int distance_threshold,
    int waken,
    int may_make_angry,
    int source_chara_index)
{
    for (int cnt = 1; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (dist(source_x, source_y, cdata[cnt].position) < distance_threshold)
        {
            if (rnd(waken) == 0)
            {
                if (cdata[cnt].sleep != 0)
                {
                    cdata[cnt].sleep = 0;
                    if (is_in_fov(cdata[cnt]))
                    {
                        txt(i18n::s.get("core.misc.sound.waken", cdata[cnt]));
                    }
                    cdata[cnt].emotion_icon = 221;
                    if (may_make_angry)
                    {
                        if (rnd(500) == 0)
                        {
                            if (is_in_fov(cdata[cnt]))
                            {
                                txt(i18n::s.get(
                                        "core.misc.sound.get_anger",
                                        cdata[cnt]),
                                    Message::color{ColorIndex::cyan});
                                txt(i18n::s.get(
                                    "core.misc.sound.can_no_longer_stand"));
                            }
                            turn_aggro(cnt, source_chara_index, 80);
                        }
                    }
                }
            }
        }
    }
}



void hostileaction(int chara_index1, int chara_index2)
{
    if (chara_index1 >= 16 || chara_index2 == 0)
    {
        return;
    }
    if (cdata[chara_index2].relationship != -3)
    {
        cdata[chara_index2].emotion_icon = 418;
    }
    if (cdata[chara_index2].relationship == 10)
    {
        txt(i18n::s.get(
                "core.misc.hostile_action.glares_at_you", cdata[chara_index2]),
            Message::color{ColorIndex::purple});
    }
    else
    {
        if (cdata[chara_index2].relationship == 0)
        {
            modify_karma(cdata.player(), -2);
        }
        if (cdata[chara_index2].id == CharaId::ebon)
        {
            if (game_data.released_fire_giant == 0)
            {
                txt(i18n::s.get(
                        "core.misc.hostile_action.glares_at_you",
                        cdata[chara_index2]),
                    Message::color{ColorIndex::purple});
                return;
            }
        }
        if (cdata[chara_index2].relationship > -2)
        {
            txt(i18n::s.get(
                    "core.misc.hostile_action.glares_at_you",
                    cdata[chara_index2]),
                Message::color{ColorIndex::purple});
            cdata[chara_index2].relationship = -2;
        }
        else
        {
            if (cdata[chara_index2].relationship != -3)
            {
                txt(i18n::s.get(
                        "core.misc.hostile_action.gets_furious",
                        cdata[chara_index2]),
                    Message::color{ColorIndex::purple});
            }
            cdata[chara_index2].relationship = -3;
            cdata[chara_index2].hate = 80;
            cdata[chara_index2].enemy_id = chara_index1;
        }
        chara_custom_talk(chara_index2, 101);
    }
    if (cdata[chara_index2].is_livestock() == 1)
    {
        if (rnd(50) == 0)
        {
            txt(i18n::s.get("core.misc.hostile_action.get_excited"),
                Message::color{ColorIndex::red});
            for (auto&& cnt : cdata.all())
            {
                if (cnt.is_livestock() == 1)
                {
                    cnt.enemy_id = 0;
                    cnt.hate = 20;
                    cnt.emotion_icon = 318;
                }
            }
        }
    }
    cdata[chara_index2].activity.finish();
}



void wake_up()
{
    if (game_data.date.hour >= 7 && game_data.date.hour <= 22)
    {
        for (auto&& cnt : cdata.others())
        {
            if (cnt.sleep > 0)
            {
                if (rnd(10))
                {
                    cnt.sleep = 0;
                }
            }
        }
    }
}



void incognitobegin()
{
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (cdata[cnt].role == Role::wandering_vendor)
        {
            continue;
        }
        if (cdata[cnt].role == Role::shop_guard)
        {
            continue;
        }
        if (cdata[cnt].original_relationship >= -2)
        {
            if (cdata[cnt].relationship <= -2)
            {
                cdata[cnt].hate = 0;
                cdata[cnt].relationship = cdata[cnt].original_relationship;
                cdata[cnt].emotion_icon = 221;
            }
        }
    }
}



void incognitoend()
{
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (cdata[cnt].role == Role::guard)
        {
            if (cdata.player().karma < -30)
            {
                cdata[cnt].relationship = -3;
                cdata[cnt].hate = 80;
                cdata[cnt].emotion_icon = 218;
            }
        }
    }
}



void wet(int chara_index, int turns)
{
    cdata[chara_index].wet += turns;
    if (is_in_fov(cdata[chara_index]))
    {
        txt(i18n::s.get("core.misc.wet.gets_wet", cdata[chara_index]));
        if (cdata[chara_index].is_invisible())
        {
            txt(i18n::s.get("core.misc.wet.is_revealed", cdata[chara_index]));
        }
    }
}



void refresh_burden_state()
{
    cdata.player().inventory_weight = clamp(inv_weight(0), 0, 20000000) *
        (100 - trait(201) * 10 + trait(205) * 20) / 100;
    cdata.player().max_inventory_weight =
        sdata(10, 0) * 500 + sdata(11, 0) * 250 + sdata(153, 0) * 2000 + 45000;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight * 2)
        {
            cdata.player().inventory_weight_type = 4;
            break;
        }
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight)
        {
            cdata.player().inventory_weight_type = 3;
            break;
        }
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight / 4 * 3)
        {
            cdata.player().inventory_weight_type = 2;
            break;
        }
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight / 2)
        {
            cdata.player().inventory_weight_type = 1;
            break;
        }
        cdata.player().inventory_weight_type = 0;
    }
    refresh_speed(cdata.player());
}



void revive_character(Character& chara)
{
    do_chara_revival(chara);
    cxinit = cdata.player().position.x;
    cyinit = cdata.player().position.y;
    chara_place(chara);
    chara.current_map = 0;
    snd("core.pray1");
    txt(i18n::s.get("core.misc.resurrect", chara.name, chara),
        Message::color{ColorIndex::orange});
}



void do_chara_revival(Character& chara)
{
    chara_set_revived_status(chara);
    chara_clear_status_effects(chara);
}



void chara_clear_status_effects_b(Character& chara)
{
    chara_clear_status_effects(chara);
}



void chara_set_revived_status(Character& chara)
{
    chara.will_explode_soon() = false;
    chara.is_sentenced_daeth() = false;
    chara.is_pregnant() = false;
    chara.is_contracting_with_reaper() = false;
    chara.has_anorexia() = false;
    chara.hp = chara.max_hp / 3;
    chara.mp = chara.max_mp / 3;
    chara.sp = chara.max_sp / 3;
    chara.insanity = 0;
    chara.current_map = 0;
    chara.relationship = chara.original_relationship;
    chara.nutrition = 8000;
    chara.set_state(Character::State::alive);
}



void chara_clear_status_effects(Character& chara)
{
    chara.is_contracting_with_reaper() = false;
    chara.activity.finish();
    chara.poisoned = 0;
    chara.sleep = 0;
    chara.confused = 0;
    chara.blind = 0;
    chara.paralyzed = 0;
    chara.choked = 0;
    chara.furious = 0;
    chara.dimmed = 0;
    chara.drunk = 0;
    chara.bleeding = 0;
    chara.gravity = 0;
    chara.ai_item = nullptr;
    chara.hate = 0;
    chara.enemy_id = 0;
    chara.sick = 0;
    chara.emotion_icon = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        chara.attr_adjs[cnt] = 0;
    }
    if (chara.buffs[0].id != 0)
    {
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (chara.buffs[cnt].id == 0)
            {
                break;
            }
            if (chara.buffs[cnt].id == 13)
            {
                continue;
            }
            buff_delete(chara, cnt);
            --cnt;
            continue;
        }
    }
    chara_refresh(chara);
}



void revive_player(Character& chara)
{
    do_chara_revival(chara);
    if (chara.index == 0)
    {
        game_data.is_returning_or_escaping = 0;
        traveldone = 0;
        if (game_data.executing_immediate_quest_type == 0)
        {
            event_add(6);
        }
    }
    if (chara.role == Role::guard)
    {
        p = rnd(5) + 1;
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            r2 = 1;
            gain_level(chara);
        }
    }
    if (chara.id == CharaId::bard)
    {
        chara_gain_fixed_skill_exp(chara, 183, 1000);
    }
    chara_refresh(chara);
}



void proc_pregnant(Character& chara)
{
    if (rnd(15) == 0)
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.misc.pregnant.pats_stomach", chara));
            txt(i18n::s.get("core.misc.pregnant.something_is_wrong"));
        }
    }
    if (map_data.type != mdata_t::MapType::world_map)
    {
        if (rnd(30) == 0)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                    "core.misc.pregnant.something_breaks_out", chara));
            }
            chara.bleeding += 15;
            flt();
            initlv = chara.level / 2 + 1;
            novoidlv = 1;
            if (const auto alien =
                    chara_create(-1, 330, chara.position.x, chara.position.y))
            {
                if (strlen_u(chara.name) > 10 ||
                    instr(
                        chara.name,
                        0,
                        i18n::s.get("core.chara.job.alien.child")) != -1)
                {
                    alien->name = i18n::s.get("core.chara.job.alien.alien_kid");
                }
                else
                {
                    alien->name = i18n::s.get(
                        "core.chara.job.alien.child_of", chara.name);
                }
            }
        }
    }
}



void proc_one_equipment_with_negative_enchantments(
    Character& chara,
    const ItemRef& equipment)
{
    for (const auto& enc : equipment->enchantments)
    {
        if (enc.id == 0)
            break;

        switch (enc.id)
        {
        case 21:
            if (map_data.type != mdata_t::MapType::world_map)
            {
                if (rnd(25) < clamp(std::abs(enc.power) / 50, 1, 25))
                {
                    efid = 408;
                    magic(chara, chara);
                }
            }
            break;
        case 45:
            if (rnd(4) == 0)
            {
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get("core.misc.curse.blood_sucked", chara),
                        Message::color{ColorIndex::purple});
                }
                chara.bleeding += std::abs(enc.power) / 25 + 3;
            }
            break;
        case 46:
            if (rnd(20) == 0)
            {
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                            "core.misc.curse.experience_reduced", chara),
                        Message::color{ColorIndex::purple});
                }
                chara.experience -= chara.required_experience /
                        (300 - clamp(std::abs(enc.power) / 2, 0, 50)) +
                    rnd(100);
                if (chara.experience < 0)
                {
                    chara.experience = 0;
                }
            }
            break;
        case 47:
            if (map_data.type != mdata_t::MapType::world_map &&
                map_data.type != mdata_t::MapType::player_owned)
            {
                if (rnd(50) < clamp(std::abs(enc.power) / 50, 1, 50))
                {
                    if (is_in_fov(chara))
                    {
                        txt(i18n::s.get("core.misc.curse.creature_summoned"),
                            Message::color{ColorIndex::purple});
                    }
                    for (int _i = 0, n = 1 + rnd(3); _i < n; ++_i)
                    {
                        flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                            calcfixlv(Quality::bad));
                        chara_create(-1, 0, chara.position.x, chara.position.y);
                    }
                }
            }
            break;
        default: break;
        }
    }
}



void proc_negative_enchantments(Character& chara)
{
    for (const auto& [_type, equipment] : chara.equipment_slots)
    {
        if (!equipment)
        {
            continue;
        }
        proc_one_equipment_with_negative_enchantments(
            chara, equipment.unwrap());
    }
}



void lovemiracle(int chara_index)
{
    if (rnd(2) || chara_index == 0)
    {
        return;
    }
    txt(i18n::s.get("core.misc.love_miracle.uh"),
        Message::color{ColorIndex::cyan});
    flt();
    if (rnd(2))
    {
        if (const auto item =
                itemcreate_extra_inv(573, cdata[chara_index].position, 0))
        {
            item->subname = charaid2int(cdata[chara_index].id);
            item->weight = cdata[chara_index].weight * 10 + 250;
            item->value = clamp(
                cdata[chara_index].weight * cdata[chara_index].weight / 10000,
                200,
                40000);
        }
    }
    else
    {
        if (const auto item =
                itemcreate_extra_inv(574, cdata[chara_index].position, 0))
        {
            item->subname = charaid2int(cdata[chara_index].id);
        }
    }
    snd("core.atk_elec");
    animeload(15, cdata[chara_index]);
}



void get_pregnant(Character& chara)
{
    if (enchantment_find(chara, 48))
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.misc.pregnant.pukes_out", chara));
        }
        return;
    }
    if (chara.is_pregnant() == 0)
    {
        txt(i18n::s.get("core.misc.pregnant.gets_pregnant", chara),
            Message::color{ColorIndex::orange});
        animeload(8, chara);
        chara.is_pregnant() = true;
    }
}



void monster_respawn()
{
    if (area_data[game_data.current_map].is_museum_or_shop())
    {
        if (game_data.crowd_density < map_data.max_crowd_density / 2)
        {
            if (rnd(2) == 0)
            {
                map_set_chara_generation_filter();
                chara_create(-1, dbid, -2, 0);
            }
        }
    }
    if (map_data.max_crowd_density == 0)
    {
        return;
    }
    if (game_data.crowd_density < map_data.max_crowd_density / 4)
    {
        if (rnd(2) == 0)
        {
            map_set_chara_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    if (game_data.crowd_density < map_data.max_crowd_density / 2)
    {
        if (rnd(4) == 0)
        {
            map_set_chara_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    if (game_data.crowd_density < map_data.max_crowd_density)
    {
        if (rnd(8) == 0)
        {
            map_set_chara_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
}



bool move_character_internal(Character& chara)
{
    if (g_config.scroll())
    {
        if (chara.index == 0)
        {
            ui_scroll_screen();
        }
    }

    cell_data.at(chara.position.x, chara.position.y).chara_index_plus_one = 0;
    chara.position = chara.next_position;
    cell_data.at(chara.next_position.x, chara.next_position.y)
        .chara_index_plus_one = chara.index + 1;

    if (chara.index == 0 && game_data.mount != 0)
    {
        cdata[game_data.mount].position = cdata.player().position;
    }

    auto movx = chara.position.x;
    auto movy = chara.position.y;

    if (cell_data.at(movx, movy).feats == 0)
        return false;

    cell_featread(movx, movy);
    if (feat(1) != 14)
        return false;

    if (feat(2) == 7)
    {
        if ((chara.is_floating() && chara.gravity == 0) ||
            chara.is_immune_to_mine())
        {
            return false;
        }
    }
    if (feat(0) != tile_trap && chara.index == 0)
    {
        if (try_to_reveal(chara))
        {
            refx = movx;
            refy = movy;
            discover_trap();
            feat(0) = tile_trap;
        }
    }
    refdiff = 100 + game_data.current_dungeon_level * 3;
    if (feat(0) == tile_trap)
    {
        refdiff = refdiff / 3;
        if (chara.index == 0)
        {
            if (sdata(175, chara.index) != 0)
            {
                if (try_to_disarm_trap(chara))
                {
                    disarm_trap(chara, movx, movy);
                    return false;
                }
                else
                {
                    txt(i18n::s.get("core.action.move.trap.disarm.fail"));
                }
            }
        }
    }

    if (can_evade_trap(chara))
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.action.move.trap.evade", chara));
        }
        if (chara.index == 0)
        {
            refx = movx;
            refy = movy;
            discover_trap();
        }
    }
    else
    {
        if (chara.index == 0)
        {
            refx = movx;
            refy = movy;
            discover_trap();
            snd("core.trap1");
        }
        efsource = 5;
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.action.move.trap.activate.text", chara));
        }

        if (feat(2) == 0)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.action.move.trap.activate.spears.text"));
            }
            if (chara.is_floating() && chara.gravity == 0)
            {
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.action.move.trap.activate.spears.target_floating",
                        chara));
                }
            }
            else
            {
                damage_hp(
                    chara,
                    rnd_capped(game_data.current_dungeon_level * 2 + 10),
                    -1);
            }
        }
        if (feat(2) == 1)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.action.move.trap.activate.poison"));
            }
            status_ailment_damage(
                chara,
                StatusAilment::poisoned,
                100 + game_data.current_dungeon_level * 2);
        }
        if (feat(2) == 2)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.action.move.trap.activate.sleep"));
            }
            status_ailment_damage(
                chara,
                StatusAilment::sleep,
                100 + game_data.current_dungeon_level * 2);
        }
        if (feat(2) == 3)
        {
            cell_featset(movx, movy, 0);
            if (enchantment_find(chara, 22))
            {
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get("core.magic.teleport.prevented"));
                }
                return false;
            }
            for (int _i = 0; _i < 200; ++_i)
            {
                chara.next_position.x = rnd(map_data.width - 2) + 1;
                chara.next_position.y = rnd(map_data.height - 2) + 1;
                cell_check(chara.next_position.x, chara.next_position.y);
                if (cellaccess == 1)
                {
                    if (is_in_fov(chara))
                    {
                        snd("core.teleport1");
                        txt(i18n::s.get(
                            "core.magic.teleport.disappears", chara));
                    }
                    chara.activity.finish();
                    update_screen();
                    break;
                }
            }
            return true;
        }
        if (feat(2) == 4)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.action.move.trap.activate.blind"));
            }
            status_ailment_damage(
                chara,
                StatusAilment::blinded,
                100 + game_data.current_dungeon_level * 2);
        }
        if (feat(2) == 5)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.action.move.trap.activate.confuse"));
            }
            status_ailment_damage(
                chara,
                StatusAilment::confused,
                100 + game_data.current_dungeon_level * 2);
        }
        if (feat(2) == 6)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.action.move.trap.activate.paralyze"));
            }
            status_ailment_damage(
                chara,
                StatusAilment::paralyzed,
                100 + game_data.current_dungeon_level * 2);
        }
        if (feat(2) == 7)
        {
            txt(i18n::s.get("core.action.move.trap.activate.mine"),
                Message::color{ColorIndex::cyan});
            BallAnimation({movx, movy}, 0, BallAnimation::Type::ball, ele)
                .play();
            cell_featset(movx, movy, 0);
            damage_hp(chara, 100 + rnd(200), -1);
        }
        efsource = 0;
    }

    return false;
}



void move_character(Character& chara)
{
    while (move_character_internal(chara))
        ;
}



void lost_body_part(int chara_index)
{
    for (auto&& equipment_slot : cdata[chara_index].equipment_slots)
    {
        if (equipment_slot.type == body)
        {
            if (!equipment_slot.equipment)
            {
                continue;
            }
            equipment_slot.equipment->body_part = 0;
            equipment_slot.unequip();
        }
    }
}



TurnResult proc_movement_event(Character& chara)
{
    auto result = lua::lua->get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_moved", chara));
    if (result.blocked())
    {
        return TurnResult::turn_end;
    }

    if (chara.is_ridden())
    {
        return TurnResult::turn_end;
    }
    dx = chara.next_position.x;
    dy = chara.next_position.y;
    if (chara.index < 16)
    {
        if (chara.index != 0)
        {
            if (dx != chara.position.x)
            {
                if (chara.position.x > dx)
                {
                    chara.direction = 1;
                }
                else
                {
                    chara.direction = 2;
                }
            }
            if (dy != chara.position.y)
            {
                if (chara.position.y > dy)
                {
                    chara.direction = 3;
                }
                else
                {
                    chara.direction = 0;
                }
            }
        }
    }
    if (cell_data.at(dx, dy).feats != 0)
    {
        cell_featread(dx, dy);
        if (feat(1) == 21)
        {
            return try_to_open_locked_door(chara);
        }
        if (feat(1) == 30)
        {
            x = dx;
            y = dy;
            return do_bash(chara);
        }
    }
    if (cell_data.at(chara.position.x, chara.position.y).mef_index_plus_one !=
        0)
    {
        bool turn_ended = mef_proc_from_movement(chara);
        if (turn_ended)
        {
            return TurnResult::turn_end;
        }
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (chara.index == 0)
        {
            if (traveldone == 0)
            {
                map_global_proc_travel_events(chara);
                keybd_wait = 1;
                return TurnResult::turn_end;
            }
            else
            {
                traveldone = 0;
            }
        }
    }
    move_character(chara);
    p = cell_data.at(chara.position.x, chara.position.y).chip_id_actual;
    if (chip_data[p].kind == 3)
    {
        if (chip_data[p].kind2 == 5)
        {
            heal_insanity(chara, 1);
        }
        addefmap(chara.position.x, chara.position.y, 1, 3);
        if (chara.wet == 0)
        {
            wet(chara.index, 20);
        }
    }
    sense_map_feats_on_move(chara);
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (chara.index == 0)
        {
            encounter = 0;
            game_data.stood_world_map_tile =
                cell_data.at(chara.position.x, chara.position.y).chip_id_actual;
            if (cell_data.at(chara.position.x, chara.position.y).feats == 0)
            {
                p = cell_data.at(chara.position.x, chara.position.y)
                        .chip_id_actual;
                if (rnd(30) == 0)
                {
                    encounter = 1;
                }
                if (game_data.weather == 4)
                {
                    if (rnd(10) == 0)
                    {
                        encounter = 1;
                    }
                }
                if (game_data.weather == 1)
                {
                    if (rnd(13) == 0)
                    {
                        encounter = 1;
                    }
                }
                if (33 <= p && p < 66)
                {
                    if (rnd(2) == 0)
                    {
                        encounter = 0;
                    }
                    if (rnd(100) == 0)
                    {
                        encounter = 2;
                    }
                }
                if (rnd_capped(
                        220 + cdata.player().level * 10 -
                        clamp(
                            game_data.cargo_weight * 150 /
                                (game_data.current_cart_limit + 1),
                            0,
                            (210 + cdata.player().level * 10))) == 0)
                {
                    encounter = 4;
                }
                if (rnd(20) == 0)
                {
                    for (int cnt = 0; cnt < 5; ++cnt)
                    {
                        rq = game_data.taken_quests.at(cnt);
                        if (quest_data[rq].id == 1007)
                        {
                            if (quest_data[rq].progress == 1)
                            {
                                if (quest_data[rq].escort_difficulty == 0)
                                {
                                    if (quest_data[rq].target_chara_index < 2)
                                    {
                                        encounter = 3;
                                        encounterref = rq;
                                        ++quest_data[rq].target_chara_index;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (encounter == 4)
            {
                encounterlv = cdata.player().fame / 1000;
                if (encounterlv == 0)
                {
                    encounterlv = 1;
                }
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            if (encounter == 3)
            {
                txt(i18n::s.get("core.misc.caught_by_assassins"));
                msg_halt();
                game_data.previous_map2 = game_data.current_map;
                game_data.previous_dungeon_level =
                    game_data.current_dungeon_level;
                game_data.previous_x = cdata.player().position.x;
                game_data.previous_y = cdata.player().position.y;
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            if (encounter == 2)
            {
                encounterlv = 10 + rnd(100);
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            if (encounter == 1)
            {
                p = dist_town();
                encounterlv = p * 3 / 2 - 10;
                if (cdata.player().level <= 5)
                {
                    encounterlv /= 2;
                }
                if (33 <= cell_data.at(chara.position.x, chara.position.y)
                              .chip_id_actual &&
                    cell_data.at(chara.position.x, chara.position.y)
                            .chip_id_actual < 66)
                {
                    encounterlv /= 2;
                }
                else if (game_data.weather == 1)
                {
                    encounterlv = encounterlv * 3 / 2 + 10;
                }
                if (encounterlv < 0)
                {
                    encounterlv = 1;
                }
                auto valn =
                    i18n::s.get(
                        "core.action.move.global.ambush.distance_from_nearest_town",
                        p(0)) +
                    " " +
                    i18n::s.get(
                        "core.action.move.global.ambush.enemy_strength");
                for (int cnt = 0; cnt < 1; ++cnt)
                {
                    if (encounterlv < 5)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.putit");
                        break;
                    }
                    if (encounterlv < 10)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.orc");
                        break;
                    }
                    if (encounterlv < 20)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.grizzly_bear");
                        break;
                    }
                    if (encounterlv < 30)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.drake");
                        break;
                    }
                    if (encounterlv < 40)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.lich");
                        break;
                    }
                    valn += i18n::s.get(
                        "core.action.move.global.ambush.rank.dragon");
                }
                valn += u8")"s;
                txt(i18n::s.get("core.action.move.global.ambush.text") + valn);
                msg_halt();
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            encounter = 0;
        }
    }
    return TurnResult::turn_end;
}



optional_ref<Character> new_ally_joins(Character& new_ally)
{
    const auto slot_index = chara_get_free_slot_ally();
    if (slot_index == 0)
    {
        txt(i18n::s.get("core.action.ally_joins.party_full"));
        return none;
    }
    auto& slot = cdata[slot_index];

    chara_relocate(new_ally, slot);
    slot.relationship = 10;
    slot.original_relationship = 10;
    slot.role = Role::none;
    slot.is_quest_target() = false;
    slot.is_not_attacked_by_enemy() = false;
    slot.is_hung_on_sand_bag() = false;
    slot.is_temporary() = false;
    slot.only_christmas() = false;
    snd("core.pray1");
    txt(i18n::s.get("core.action.ally_joins.success", slot),
        Message::color{ColorIndex::orange});
    return slot;
}

} // namespace elona
