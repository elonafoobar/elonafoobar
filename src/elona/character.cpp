#include "character.hpp"
#include <cassert>
#include <type_traits>
#include "../util/fileutil.hpp"
#include "../util/range.hpp"
#include "../util/strutil.hpp"
#include "ability.hpp"
#include "area.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "elona.hpp"
#include "equipment.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "race.hpp"
#include "random.hpp"
#include "trait.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{

int chara_create_internal()
{
    if (rc == -1)
    {
        rc = chara_get_free_slot();
        if (rc == -1)
        {
            rc = 56;
            return 0;
        }
    }
    chara_delete(rc);
    cequipment = 0;
    if (rc == 0)
    {
        p = 10;
    }
    else
    {
        p = 4;
    }
    if (dbid == -1)
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
        dbmode = 1;
        get_random_npc_id();
        if (dbid == 0)
        {
            if (fltselect == 2 || fixlv == Quality::special)
            {
                fixlv = Quality::miracle;
            }
            flt(objlv + 10, fixlv);
            dbmode = 1;
            get_random_npc_id();
        }
    }
    else if (dbid == 343)
    {
        if (usernpcmax > 0)
        {
            cdata[rc].cnpc_id = rnd(usernpcmax);
        }
    }

    cm = 1;
    cmshade = 0;
    ++npcmemory(1, dbid);
    if (dbid == 323)
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
            dbmode = 1;
            get_random_npc_id();
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
    if (dbid == 343)
    {
        // Vanila-copatible CNPC is not supported now.
    }
    else
    {
        dbmode = 3;
        access_character_info();
    }
    if (cmshade)
    {
        cdatan(0, rc) = i18n::s.get("core.locale.chara.job.shade");
        cdata[rc].image = 280;
    }
    cdata[rc].quality = static_cast<Quality>(fixlv);
    cdata[rc].index = rc;
    initialize_character();

    rtval = rc;
    return 1;
}



bool is_in_map(const Position& position)
{
    const auto x = position.x;
    const auto y = position.y;
    return 0 <= x && x < map_data.width && 0 <= y && y < map_data.height;
}



Position get_random_position(const Position& base_position, int n)
{
    return {base_position.x - rnd(n) + rnd(n),
            base_position.y - rnd(n) + rnd(n)};
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
            if (chipm(7, cell_data.at(x, y).feats % 1000) & 4)
            {
                continue;
            }
        }
        if (cell_data.at(x, y).chara_index_plus_one == 0)
        {
            if (!(chipm(7, cell_data.at(x, y).chip_id_actual) & 4))
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
    for (auto&& cc : cdata.others())
    {
        if (cc.state() == Character::State::alive && cc.character_role == 0)
        {
            slots.push_back(cc.index);
        }
    }

    if (slots.empty())
    {
        // FIXME: do not throw exception.
        throw std::runtime_error("chara_get_free_slot_force() failed");
    }

    ret = choice(slots);
    // Force to destroy the character in `ret`.
    chara_vanquish(ret);
    return ret;
}



bool can_place_character_at(const Position& position, bool allow_stairs)
{
    // Out of range
    if (position.x < 0 || map_data.width <= position.x || position.y < 0 ||
        map_data.height <= position.y)
        return false;

    // Wall
    if (chipm(7, cell_data.at(position.x, position.y).chip_id_actual) & 4)
        return false;

    // There is someone.
    if (cell_data.at(position.x, position.y).chara_index_plus_one != 0)
        return false;

    if (cell_data.at(position.x, position.y).feats != 0)
    {
        // There is an object which prevents from walking through.
        if (chipm(7, cell_data.at(position.x, position.y).feats % 1000) & 4)
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
    Character& cc,
    optional<Position> position,
    bool enemy_respawn)
{
    int x;
    int y;

    for (int i = 0;; ++i)
    {
        if (i == 99)
        {
            if (cc.index >= 57)
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
                if (cc.index != 0)
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
                    if (chipm(7, cell_data.at(x, y).chip_id_actual) & 4)
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

        if (can_place_character_at({x, y}, cc.index == 0 || position))
        {
            break;
        }
    }

    // Do place character.
    cc.initial_position = cc.position = {x, y};
    cell_data.at(x, y).chara_index_plus_one = cc.index + 1;

    return true; // placed successfully.
}



void failed_to_place_character(Character& cc)
{
    if (cc.index < 16)
    {
        cc.set_state(Character::State::pet_in_other_map);
        txt(i18n::s.get("core.locale.chara.place_failure.ally", cc));
    }
    else
    {
        txt(i18n::s.get("core.locale.chara.place_failure.other", cc));
        cc.set_state(Character::State::empty);
        // Exclude town residents because they occupy character slots even
        // if they are dead.
        modify_crowd_density(cc.index, -1);
    }
    if (cc.character_role != 0)
    {
        cc.set_state(Character::State::villager_dead);
    }
    if (cc.character_role == 13)
    {
        cc.set_state(Character::State::adventurer_dead);
        cc.time_to_revive = game_data.date.hours() + 24 + rnd(12);
    }
}

} // namespace



namespace elona
{

CData cdata;


elona_vector1<std::string> usertxt;



Character::Character()
    : growth_buffs(10)
    , body_parts(30)
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



bool chara_place()
{
    if (rc == -1)
        return false;

    if (rc == 56)
    {
        cdata[rc].set_state(Character::State::empty);
        return false;
    }

    if (game_data.mount != 0 && game_data.mount == rc)
    {
        cdata[rc].position = cdata.player().position;
        return true;
    }

    const auto success = chara_place_internal(
        cdata[rc],
        cxinit >= 0 ? optional<Position>({cxinit, cyinit}) : none,
        cxinit == -2);
    if (!success)
    {
        failed_to_place_character(cdata[rc]);
    }

    return success;
}



void initialize_character()
{
    if (mode != 1)
    {
        chara_add_quality_parens();
    }
    cdata[rc].interest = 100;
    cdata[rc].impression = 50;
    cdata[rc].vision_distance = 14;
    if (cdata[rc].id == 205)
    {
        cdata[rc].image = rnd(33) * 2 + cdata[rc].sex + 1;
    }
    if (rc == 0)
    {
        cdata[rc].nutrition = 9000;
    }
    else
    {
        cdata[rc].nutrition = 5000 + rnd(4000);
    }
    cdata[rc].height = cdata[rc].height + rnd((cdata[rc].height / 5 + 1)) -
        rnd((cdata[rc].height / 5 + 1));
    cdata[rc].weight =
        cdata[rc].height * cdata[rc].height * (rnd(6) + 18) / 10000;
    update_required_experience(cdata[rc]);
    chara_init_common_skills(cdata[rc]);
    if (cdata[rc].portrait == "__random__")
    {
        const auto index = std::to_string(1 + rnd(32));
        const auto man_or_woman = cdata[rc].sex ? "woman" : "man";
        cdata[rc].portrait = "core."s + man_or_woman + index;
    }
    cdata[rc].personality = rnd(4);
    cdata[rc].talk_type = rnd(7);
    supply_initial_equipments();
    chara_refresh(rc);
    modify_crowd_density(rc, 1);
    cdata[rc].hp = cdata[rc].max_hp;
    cdata[rc].mp = cdata[rc].max_mp;
    cdata[rc].sp = cdata[rc].max_sp;
    if (rc == 0)
    {
        game_data.initial_cart_limit = 80000;
        game_data.current_cart_limit = game_data.initial_cart_limit;
    }
    if (cdata[rc].has_lay_hand())
    {
        cdata[rc].is_lay_hand_available() = true;
    }

    cdata[rc].set_state(Character::State::alive);

    cm = 0;
}



int chara_create(int slot, int chara_id, int x, int y)
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
    if (chara_id == 0)
    {
        dbid = -1;
    }
    else
    {
        dbid = chara_id;
    }
    rc = slot;
    int stat = chara_create_internal();
    initlv = 0;
    voidlv = 0;
    if (stat == 1)
    {
        if (rc == 56)
        {
            cdata[rc].set_state(Character::State::empty);
            --npcmemory(1, cdata[rc].id.to_integer());
            return 1;
        }
        if (rc != 0)
        {
            if (x != -1)
            {
                success = chara_place();
            }
        }
    }
    else
    {
        rc = 56;
        return 0;
    }

    return success ? 1 : 0;
}



void chara_refresh(int cc)
{
    int rp = 0;
    int rp2 = 0;
    int rp3 = 0;
    if (cc == 0)
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
        sdata(cnt, cc) = sdata.get(cnt, cc).original_level;
    }
    if (cc == 0)
    {
        cdata[cc].clear_flags();
        if (trait(161) != 0)
        {
            for (int i = 0; i < 30; ++i)
            {
                if (cdata[cc].body_parts[i] % 10000 == 0)
                {
                    continue;
                }
                rp = cdata[cc].body_parts[i] % 10000 - 1;
                if (inv[rp].weight >= 1000)
                {
                    cdata[cc].body_parts[i] =
                        cdata[cc].body_parts[i] / 10000 * 10000;
                    inv[rp].body_part = 0;
                }
            }
        }
    }
    else if (cdata[cc].id == 343)
    {
        for (size_t i = 0; i < 32 * 30; ++i)
        {
            cdata[cc]._flags[i] =
                userdata(40 + i / (8 * sizeof(int)), cdata[cc].cnpc_id) &
                (1 << (i % (8 * sizeof(int))));
        }
    }
    else
    {
        for (size_t i = 0; i < 32 * 30; ++i)
        {
            cdata[cc]._flags[i] =
                the_character_db[cdata[cc].id.get()]->_flags[i];
        }
    }
    for (auto&& growth_buff : cdata[cc].growth_buffs)
    {
        growth_buff = 0;
    }
    cdata[cc].dv = 0;
    cdata[cc].pv = 0;
    cdata[cc].hit_bonus = 0;
    cdata[cc].damage_bonus = 0;
    cdata[cc].equipment_type = 0;
    attacknum = 0;
    cdata[cc].rate_to_pierce = 0;
    cdata[cc].rate_of_critical_hit = 0;
    cdata[cc].curse_power = 0;
    cdata[cc].extra_attack = 0;
    cdata[cc].extra_shot = 0;
    cdata[cc].sum_of_equipment_weight = 0;
    cdata[cc].decrease_physical_damage = 0;
    cdata[cc].nullify_damage = 0;
    cdata[cc].cut_counterattack = 0;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata[cc].body_parts[i] % 10000 == 0)
        {
            continue;
        }
        rp = cdata[cc].body_parts[i] % 10000 - 1;
        cdata[cc].sum_of_equipment_weight += inv[rp].weight;
        if (inv[rp].skill == 168)
        {
            if (!(cdata[cc].equipment_type & 1))
            {
                cdata[cc].equipment_type += 1;
            }
        }
        cdata[cc].dv += inv[rp].dv;
        cdata[cc].pv += inv[rp].pv;
        if (inv[rp].dice_x == 0)
        {
            cdata[cc].hit_bonus += inv[rp].hit_bonus;
            cdata[cc].damage_bonus += inv[rp].damage_bonus;
            cdata[cc].pv += inv[rp].enhancement * 2 +
                (inv[rp].curse_state == CurseState::blessed) * 2;
        }
        else if (cdata[cc].body_parts[i] / 10000 == 5)
        {
            ++attacknum;
        }
        if (inv[rp].curse_state == CurseState::cursed)
        {
            cdata[cc].curse_power += 20;
        }
        if (inv[rp].curse_state == CurseState::doomed)
        {
            cdata[cc].curse_power += 100;
        }
        if (inv[rp].material == 8)
        {
            if (cc == 0)
            {
                game_data.ether_disease_speed += 5;
            }
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[rp].enchantments[cnt].id == 0)
            {
                break;
            }
            rp2 = inv[rp].enchantments[cnt].id;
            if (rp2 >= 10000)
            {
                rp3 = rp2 % 10000;
                rp2 = rp2 / 10000;
                if (rp2 == 1)
                {
                    sdata(rp3, cc) += inv[rp].enchantments[cnt].power / 50 + 1;
                    continue;
                }
                if (rp2 == 2)
                {
                    sdata(rp3, cc) += inv[rp].enchantments[cnt].power / 2;
                    if (sdata(rp3, cc) < 0)
                    {
                        sdata(rp3, cc) = 1;
                    }
                    continue;
                }
                if (rp2 == 3)
                {
                    if (sdata.get(rp3, cc).original_level != 0)
                    {
                        sdata(rp3, cc) +=
                            inv[rp].enchantments[cnt].power / 50 + 1;
                        if (sdata(rp3, cc) < 1)
                        {
                            sdata(rp3, cc) = 1;
                        }
                    }
                    continue;
                }
            }
            else
            {
                if (rp2 == 56)
                {
                    if (cc == 0)
                    {
                        game_data.catches_god_signal = 1;
                        continue;
                    }
                }
                if (rp2 == 59)
                {
                    if (cc == 0)
                    {
                        game_data.reveals_religion = 1;
                        continue;
                    }
                }
                if (rp2 == 29)
                {
                    sdata(18, cc) += inv[rp].enchantments[cnt].power / 50 + 1;
                    if (cc == 0)
                    {
                        game_data.seven_league_boot_effect +=
                            inv[rp].enchantments[cnt].power / 8;
                        continue;
                    }
                }
                if (rp2 == 32)
                {
                    cdata[cc].is_floating() = true;
                    continue;
                }
                if (rp2 == 35)
                {
                    cdata[cc].can_see_invisible() = true;
                    continue;
                }
                if (rp2 == 23)
                {
                    cdata[cc].is_immune_to_blindness() = true;
                    continue;
                }
                if (rp2 == 24)
                {
                    cdata[cc].is_immune_to_paralyzation() = true;
                    continue;
                }
                if (rp2 == 25)
                {
                    cdata[cc].is_immune_to_confusion() = true;
                    continue;
                }
                if (rp2 == 26)
                {
                    cdata[cc].is_immune_to_fear() = true;
                    continue;
                }
                if (rp2 == 27)
                {
                    cdata[cc].is_immune_to_sleep() = true;
                    continue;
                }
                if (rp2 == 28)
                {
                    cdata[cc].is_immune_to_poison() = true;
                    continue;
                }
                if (rp2 == 42)
                {
                    cdata[cc].can_digest_rotten_food() = true;
                    continue;
                }
                if (rp2 == 41)
                {
                    cdata[cc].is_protected_from_thieves() = true;
                    continue;
                }
                if (rp2 == 55)
                {
                    cdata[cc].cures_bleeding_quickly() = true;
                    continue;
                }
                if (rp2 == 52)
                {
                    cdata[cc].decrease_physical_damage +=
                        inv[rp].enchantments[cnt].power / 40 + 5;
                    continue;
                }
                if (rp2 == 53)
                {
                    cdata[cc].nullify_damage +=
                        inv[rp].enchantments[cnt].power / 60 + 3;
                    continue;
                }
                if (rp2 == 54)
                {
                    cdata[cc].cut_counterattack +=
                        inv[rp].enchantments[cnt].power / 5;
                    continue;
                }
                if (rp2 == 44)
                {
                    cdata[cc].rate_of_critical_hit +=
                        inv[rp].enchantments[cnt].power / 50;
                    continue;
                }
                if (rp2 == 39)
                {
                    cdata[cc].rate_to_pierce +=
                        inv[rp].enchantments[cnt].power / 50;
                    continue;
                }
                if (rp2 == 50)
                {
                    cdata[cc].extra_attack +=
                        inv[rp].enchantments[cnt].power / 15;
                    continue;
                }
                if (rp2 == 51)
                {
                    cdata[cc].extra_shot +=
                        inv[rp].enchantments[cnt].power / 15;
                    cdata[cc].extra_shot = 100;
                    continue;
                }
                if (rp2 == 21 || rp2 == 45 || rp2 == 46 || rp2 == 47)
                {
                    cdata[cc].has_cursed_equipments() = true;
                    continue;
                }
                if (cc == 0)
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
            sdata(cnt, 56) = sdata.get(cnt, cc).original_level;
            if (sdata(cnt, 56) != sdata(cnt, cc))
            {
                rp = sdata(cnt, cc) - sdata(cnt, 56);
                cnvbonus(cnt, rp);
            }
        }
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (cdata[cc].attr_adjs[cnt] != 0)
        {
            if (cdata[cc].quality >= Quality::miracle)
            {
                if (cdata[cc].attr_adjs[cnt] <
                    sdata.get(10 + cnt, cc).original_level / 5)
                {
                    cdata[cc].attr_adjs[cnt] =
                        sdata.get(10 + cnt, cc).original_level / 5;
                }
            }
            sdata(10 + cnt, cc) += cdata[cc].attr_adjs[cnt];
        }
        if (sdata(10 + cnt, cc) < 1)
        {
            sdata(10 + cnt, cc) = 1;
        }
    }
    if (cc == 0)
    {
        apply_god_blessing(cc);
        for (int cnt = 0; cnt < 217; ++cnt)
        {
            if (trait(cnt) != 0)
            {
                trait_get_info(1, cnt);
            }
        }
    }
    if (cdata[cc].equipment_type & 1)
    {
        if (cdata[cc].pv > 0)
        {
            cdata[cc].pv =
                cdata[cc].pv * (120 + int(std::sqrt(sdata(168, cc))) * 2) / 100;
        }
    }
    else if (attacknum == 1)
    {
        cdata[cc].equipment_type += 2;
    }
    else if (attacknum != 0)
    {
        cdata[cc].equipment_type += 4;
    }
    cdata[cc].max_mp =
        clamp(
            ((sdata(16, cc) * 2 + sdata(15, cc) + sdata(14, cc) / 3) *
                 cdata[cc].level / 25 +
             sdata(16, cc)),
            1,
            1000000) *
        sdata(3, cc) / 100;
    cdata[cc].max_hp =
        clamp(
            ((sdata(11, cc) * 2 + sdata(10, cc) + sdata(15, cc) / 3) *
                 cdata[cc].level / 25 +
             sdata(11, cc)),
            1,
            1000000) *
            sdata(2, cc) / 100 +
        5;
    cdata[cc].max_sp =
        100 + (sdata(15, cc) + sdata(11, cc)) / 5 + trait(24) * 8;
    if (cdata[cc].max_mp < 1)
    {
        cdata[cc].max_mp = 1;
    }
    if (cdata[cc].max_hp < 1)
    {
        cdata[cc].max_hp = 1;
    }
    if (cc >= ELONA_MAX_PARTY_CHARACTERS || false)
    {
        cdata[cc].dv = cdata[cc].level / 2 +
            cdata[cc].dv * cdata[cc].dv_correction_value / 100 +
            cdata[cc].dv_correction_value - 100;
        cdata[cc].pv = cdata[cc].level +
            (cdata[cc].pv + cdata[cc].level / 2 +
             cdata[cc].pv_correction_value / 25) *
                cdata[cc].pv_correction_value / 100;
        if (cdata[cc].quality == Quality::great)
        {
            cdata[cc].max_hp = cdata[cc].max_hp * 3 / 2;
        }
        if (cdata[cc].quality >= Quality::miracle)
        {
            cdata[cc].max_hp = cdata[cc].max_hp * 5;
        }
    }
    else
    {
        cdata[cc].max_hp += 10;
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        rp = cdata[cc].buffs[cnt].id;
        if (rp == 0)
        {
            break;
        }
        apply_buff(cc, rp, cdata[cc].buffs[cnt].power);
    }
    if (cdata[cc].equipment_type & 4)
    {
        cdata[cc].extra_attack += int(std::sqrt(sdata(166, cc))) * 3 / 2 + 4;
    }
    if (sdata(186, cc))
    {
        cdata[cc].rate_of_critical_hit += int(std::sqrt(sdata(186, cc))) + 2;
    }
    if (cdata[cc].rate_of_critical_hit > 30)
    {
        cdata[cc].hit_bonus += (cdata[cc].rate_of_critical_hit - 30) * 2;
        cdata[cc].rate_of_critical_hit = 30;
    }
    refresh_burden_state();
    refresh_speed(cdata[cc]);
    cdata[cc].needs_refreshing_status() = false;

    auto handle = lua::lua->get_handle_manager().get_handle(cdata[cc]);
    if (handle != sol::lua_nil)
    {
        lua::lua->get_event_manager()
            .run_callbacks<lua::EventKind::character_refreshed>(handle);
    }
}



int relationbetween(int c1, int c2)
{
    if (cdata[c1].relationship >= -2)
    {
        if (cdata[c2].relationship <= -3)
        {
            return -3;
        }
    }
    else if (cdata[c2].relationship >= -2)
    {
        return -3;
    }
    return 0;
}



int chara_find(int id)
{
    for (auto&& i : cdata.others())
    {
        if (i.state() != Character::State::villager_dead)
        {
            if (i.state() != Character::State::alive)
            {
                continue;
            }
        }
        if (i.id == id)
        {
            return i.index;
        }
    }
    return 0;
}



int chara_find_ally(int id)
{
    for (int i = 0; i < 16; ++i)
    {
        if (cdata[i].state() != Character::State::alive)
        {
            continue;
        }
        if (cdata[i].id == id)
        {
            return i;
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


int chara_custom_talk(int cc, int talk_type)
{
    std::vector<std::string> talk_file_buffer;

    bool use_external_file = false;

    if (cdata[cc].has_custom_talk())
    {
        const auto filepath =
            filesystem::dir::user() / u8"talk" / cdatan(4, cc);
        if (!fs::exists(filepath))
            return 0;
        range::copy(
            fileutil::read_by_line(filepath),
            std::back_inserter(talk_file_buffer));
        use_external_file = true;
    }
    else if (cdata[cc].id == 343)
    {
        talk_file_buffer = strutil::split_lines(usertxt(cdata[cc].cnpc_id));
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

        tag += u8"," + i18n::s.get("core.locale.meta.tag");
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

    if (cdata[cc].can_talk != 0)
    {
        dbid = cdata[cc].id.to_integer();
        dbmode = talk_type;
        access_character_info();
        return 1;
    }
    return 0;
}



std::string chara_refstr(int id, int info_type)
{
    dbmode = 16;
    dbid = id;
    dbspec = info_type;
    access_character_info();
    return refstr;
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



void chara_modify_impression(Character& cc, int delta)
{
    int level1 = chara_impression_level(cc.impression);
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
    cc.impression += delta;
    int level2 = chara_impression_level(cc.impression);
    if (level1 > level2)
    {
        txt(i18n::s.get(
                "core.locale.chara.impression.lose",
                cc,
                i18n::s.get_enum("core.locale.ui.impression", level2)),
            Message::color{ColorIndex::purple});
    }
    else if (level2 > level1)
    {
        if (cc.relationship != -3)
        {
            txt(i18n::s.get(
                    "core.locale.chara.impression.gain",
                    cc,
                    i18n::s.get_enum("core.locale.ui.impression", level2)),
                Message::color{ColorIndex::green});
        }
    }
}



void chara_vanquish(int cc)
{
    if (cc == 0)
        return;

    if (cc == game_data.mount)
    {
        ride_end();
    }
    else if (
        cdata[cc].state() == Character::State::alive ||
        cdata[cc].state() == Character::State::servant_being_selected)
    {
        cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
            .chara_index_plus_one = 0;
    }
    cdata[cc].set_state(Character::State::empty);
    cdata[cc].character_role = 0;
    if (cdata[cc].shop_store_id != 0)
    {
        const auto storage_filename = filepathutil::u8path(
            "shop"s + std::to_string(cdata[cc].shop_store_id) + ".s2");
        const auto storage_filepath = filesystem::dir::tmp() / storage_filename;
        tmpload(storage_filename);
        if (fs::exists(storage_filepath))
        {
            fs::remove(storage_filepath);
            Save::instance().remove(storage_filepath.filename());
        }
        cdata[cc].shop_store_id = 0;
    }
    quest_check();
    modify_crowd_density(cc, 1);
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
    for (int i = 0; i < 10; ++i)
    {
        cdatan(i, slot) = cdatan(i, source.index);
    }
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
    for (size_t i = 0; i < destination.body_parts.size(); ++i)
    {
        destination.body_parts[i] = destination.body_parts[i] / 10000 * 10000;
    }

    // Increase crowd density.
    modify_crowd_density(slot, 1);
    // Increase the generation counter.
    ++npcmemory(1, destination.id.to_integer());

    return slot;
}



void chara_killed(Character& chara)
{
    auto handle = lua::lua->get_handle_manager().get_handle(chara);
    lua::lua->get_event_manager()
        .run_callbacks<lua::EventKind::character_killed>(handle);

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



void chara_delete(int cc)
{
    if (cc != -1)
    {
        chara_remove(cdata[cc]);
    }

    for (const auto& cnt : items(cc))
    {
        inv[cnt].remove();
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cdatan(cnt, cc) = "";
    }
    sdata.clear(cc);
    cdata[cc].clear();
}



void chara_relocate(
    Character& source,
    optional<int> destination_slot,
    CharaRelocationMode mode)
{
    if (source.index == game_data.mount)
    {
        ride_end();
        source.position = cdata.player().position;
    }

    const auto slot =
        destination_slot ? *destination_slot : chara_get_free_slot_force();
    auto& destination = cdata[slot];

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

    // Copy `source`'s inventory to `destination`.
    const auto tmp = inv_getheader(source.index);
    const auto invhead = tmp.first;
    const auto invrange = tmp.second;
    int p = invhead;
    for (const auto& cnt : items(slot))
    {
        if (cnt == invrange)
        {
            break;
        }
        if (cc == source.index)
        {
            if (ci == p)
            {
                ci = cnt;
            }
        }
        Item::copy(inv[p], inv[cnt]);
        inv[p].clear();
        inv[cnt].body_part = 0;
        ++p;
    }

    // Clear some fields which should not be copied.
    source.item_which_will_be_used = 0;
    source.is_livestock() = false;

    // Copy from `source` to `destination` and clear `source`
    sdata.copy(slot, source.index);
    sdata.clear(source.index);

    Character::copy(source, destination);
    source.clear();

    if (mode == CharaRelocationMode::normal)
    {
        // Relocate the corresponding Lua reference, if it exists. It may
        // not always exist, since if the mode is "change" the
        // source's state will be empty. If the source's state is empty, the
        // destination slot will instead be set to empty as well.
        lua::lua->get_handle_manager().relocate_handle<Character>(
            source, destination, slot);
    }
    else
    {
        // Clear the source's handle, as it is now invalid. Preserve the handle
        // that exists in the slot already.
        lua::lua->get_handle_manager().remove_chara_handle_run_callbacks(
            source);
    }

    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cdatan(cnt, slot) = cdatan(cnt, source.index);
        cdatan(cnt, source.index) = "";
    }

    // Unequip all gears.
    for (size_t i = 0; i < destination.body_parts.size(); ++i)
    {
        destination.body_parts[i] = destination.body_parts[i] / 10000 * 10000;
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
            .chara_index_plus_one = slot + 1;
    }
    else
    {
        if (source.index != 56)
        {
            cell_data.at(destination.position.x, destination.position.y)
                .chara_index_plus_one = slot + 1;
        }
        else
        {
            rc = slot;
            destination.set_state_raw(Character::State::alive);
            cxinit = cdata.player().position.x;
            cyinit = cdata.player().position.y;
            chara_place();
        }
        destination.enemy_id = 0;
        destination.hate = 0;
    }

    // Lose resistance.
    if (slot < 16)
    {
        for (int element = 50; element < 61; ++element)
        {
            auto resistance = 100;
            if (sdata.get(element, slot).original_level >= 500 ||
                sdata.get(element, slot).original_level <= 100)
            {
                resistance = sdata.get(element, slot).original_level;
            }
            if (resistance > 500)
            {
                resistance = 500;
            }
            sdata.get(element, slot).original_level = resistance;
            sdata.get(element, slot).experience = 0;
            sdata.get(element, slot).potential = 0;
        }
    }

    rc = slot;
    wear_most_valuable_equipment_for_all_body_parts();
    chara_refresh(slot);

    if (slot < 57)
    {
        modify_crowd_density(source.index, -1);
    }
    if (source.index < 57)
    {
        modify_crowd_density(slot, 1);
    }
}



void chara_set_item_which_will_be_used(Character& cc)
{
    int category = the_item_db[inv[ci].id]->category;
    if (category == 57000 || category == 52000 || category == 53000)
    {
        cc.item_which_will_be_used = ci;
    }
}



int chara_armor_class(const Character& cc)
{
    if (cc.sum_of_equipment_weight >= 35000)
    {
        return 169;
    }
    else if (cc.sum_of_equipment_weight >= 15000)
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
    const auto breed_power_base =
        the_race_db[cdatan(2, chara.index)]->breed_power;
    return breed_power_base * 100 / (100 + chara.level * 5);
}



bool belong_to_same_team(const Character& c1, const Character& c2)
{
    return (c1.relationship >= 0 && c2.relationship >= 0) ||
        (c1.relationship == -1 && c2.relationship == -1) ||
        (c1.relationship <= -2 && c2.relationship <= -2);
}



void chara_add_quality_parens()
{
    if (fixlv == Quality::miracle)
    {
        cdatan(0, rc) =
            i18n::s.get("core.locale.chara.quality.miracle", cdatan(0, rc));
        cdata[rc].level = cdata[rc].level * 10 / 8;
    }
    else if (fixlv == Quality::godly)
    {
        cdatan(0, rc) =
            i18n::s.get("core.locale.chara.quality.godly", cdatan(0, rc));
        cdata[rc].level = cdata[rc].level * 10 / 6;
    }
}

} // namespace elona
