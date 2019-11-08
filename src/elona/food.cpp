#include "food.hpp"
#include "../util/strutil.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "trait.hpp"
#include "variables.hpp"



namespace
{

void _food_gets_rotten(int chara_idx, int food_idx)
{
    auto& food = inv[food_idx];

    if (food.material != 35)
    {
        return;
    }
    if (food.param3 <= 0)
    {
        return; // Has already been rotten.
    }
    if (food.param3 > game_data.date.hours())
    {
        return; // The expiration date has not come yet.
    }
    if (food.own_state > 0)
    {
        return; // On the field.
    }

    // Is it corpse(s) on a dryrock?
    if (chara_idx == -1 && food.id == ItemId::corpse &&
        chip_data.for_cell(food.position.x, food.position.y).kind == 1)
    {
        if (game_data.weather != 0)
        {
            return;
        }
        txt(i18n::s.get(
            "core.misc.corpse_is_dried_"
            "up",
            food));
        food.param3 = game_data.date.hours() + 2160;
        food.image = 337;
        food.id = ItemId::jerky;
        food.param1 = 0;
        food.param2 = 5;
        cell_refresh(food.position.x, food.position.y);
        return;
    }

    if (0 <= chara_idx && chara_idx < 16)
    {
        txt(i18n::s.get("core.misc.get_rotten", food));
    }

    food.param3 = -1;
    food.image = 336;

    if (chara_idx == -1)
    {
        cell_refresh(food.position.x, food.position.y);
    }

    if (chara_idx == 0 && cdata.player().god_id == core_god::kumiromi)
    {
        if (rnd(3) == 0)
        {
            txt(i18n::s.get("core.misc.extract_seed", food));
            const auto seed_num = rnd(food.number()) + 1;
            food.modify_number(-food.number());
            flt(calcobjlv(cdata.player().level));
            flttypeminor = 58500;
            itemcreate(0, 0, -1, -1, seed_num);
        }
    }
}

} // namespace



namespace elona
{

int cieat = 0;
int nutrition = 0;
int fdmax = 0;
elona_vector2<int> fdlist;



void show_eating_message()
{
    if (cdata[cc].nutrition >= 12000)
    {
        txt(i18n::s.get("core.food.eating_message.bloated"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 10000)
    {
        txt(i18n::s.get("core.food.eating_message.satisfied"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 5000)
    {
        txt(i18n::s.get("core.food.eating_message.normal"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 2000)
    {
        txt(i18n::s.get("core.food.eating_message.hungry"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 1000)
    {
        txt(i18n::s.get("core.food.eating_message.very_hungry"),
            Message::color{ColorIndex::green});
    }
    else
    {
        txt(i18n::s.get("core.food.eating_message.starving"),
            Message::color{ColorIndex::green});
    }
}



void eat_rotten_food()
{
    if (cdata[cc].can_digest_rotten_food() == 1)
    {
        txt(i18n::s.get("core.food.not_affected_by_rotten", cdata[cc]));
        return;
    }
    fdmax = 0;
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 10;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 11;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 17;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 16;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 12;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 13;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 14;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 15;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    nutrition = 1000;
    status_ailment_damage(cdata[cc], StatusAilment::paralyzed, 100);
    status_ailment_damage(cdata[cc], StatusAilment::confused, 200);
}



void cure_anorexia(Character& cc)
{
    if (!cc.has_anorexia())
        return;

    cc.has_anorexia() = false;
    if (is_in_fov(cc) || cc.index < 16)
    {
        txt(i18n::s.get("core.food.anorexia.recovers_from", cc));
        snd("core.offer1");
    }
}



void chara_vomit(Character& cc)
{
    ++cc.anorexia_count;

    if (is_in_fov(cc))
    {
        snd("core.vomit");
        txt(i18n::s.get("core.food.vomits", cc));
    }

    if (cc.is_pregnant())
    {
        cc.is_pregnant() = false;
        if (is_in_fov(cc))
        {
            txt(i18n::s.get("core.food.spits_alien_children", cc));
        }
    }

    // Lose food buff.
    for (size_t i = 0; i < cc.buffs.size();)
    {
        if (cc.buffs[i].id == 0)
        {
            break;
        }
        if (the_buff_db[cc.buffs[i].id]->type == BuffType::food)
        {
            buff_delete(cc, i);
        }
        else
        {
            ++i;
        }
    }

    // Vomit.
    if (map_data.type != mdata_t::MapType::world_map)
    {
        auto p = 2;
        for (const auto& item : inv.ground())
        {
            if (item.number() > 0)
            {
                if (item.id == ItemId::vomit)
                {
                    ++p;
                }
            }
        }
        if (rnd(p * p * p) == 0 || cc.index == 0)
        {
            flt();
            if (itemcreate(-1, 704, cc.position.x, cc.position.y, 0))
            {
                if (cc.index != 0)
                {
                    inv[ci].subname = charaid2int(cc.id);
                }
            }
        }
    }

    if (cc.has_anorexia())
    {
        chara_gain_fixed_skill_exp(cc, 10, -50);
        chara_gain_fixed_skill_exp(cc, 11, -75);
        chara_gain_fixed_skill_exp(cc, 17, -100);
    }
    else
    {
        if ((cc.index < 16 && cc.anorexia_count > 10) ||
            (cc.index >= 16 && rnd(4) == 0))
        {
            if (rnd(5) == 0)
            {
                cc.has_anorexia() = true;
                if (is_in_fov(cc))
                {
                    txt(i18n::s.get("core.food.anorexia.develops", cc));
                    snd("core.offer1");
                }
            }
        }
    }

    status_ailment_damage(cc, StatusAilment::dimmed, 100);
    modify_weight(cc, -(1 + rnd(5)));
    if (cc.nutrition <= 0)
    {
        damage_hp(cc, 9999, -3);
    }
    cc.nutrition -= 3000;
}



void eatstatus(CurseState curse_state, int eater)
{
    if (cdata[eater].state() != Character::State::alive)
        return;

    if (is_cursed(curse_state))
    {
        cdata[eater].nutrition -= 1500;
        if (is_in_fov(cdata[eater]))
        {
            txt(i18n::s.get("core.food.eat_status.bad", cdata[eater]));
        }
        chara_vomit(cdata[eater]);
    }
    else if (curse_state == CurseState::blessed)
    {
        if (is_in_fov(cdata[eater]))
        {
            txt(i18n::s.get("core.food.eat_status.good", cdata[eater]));
        }
        if (rnd(5) == 0)
        {
            buff_add(cdata[eater], "core.luck", 100, 500 + rnd(500));
        }
        heal_insanity(cdata[eater], 2);
    }
}



void chara_anorexia(Character& cc)
{
    if (cc.has_anorexia())
    {
        chara_vomit(cc);
    }
}



void get_sick_if_cursed(CurseState curse_state, Character& drinker)
{
    if (!is_cursed(curse_state))
        return;

    if (is_in_fov(drinker))
    {
        txt(i18n::s.get("core.food.eat_status.cursed_drink", drinker));
    }
    status_ailment_damage(drinker, StatusAilment::sick, 200);
}



void get_hungry(Character& cc)
{
    if ((trait(158) && rnd(3) == 0) || debug::voldemort)
        return;

    int p = cc.nutrition / 1000;
    cc.nutrition -= 8;
    if (cc.nutrition / 1000 != p)
    {
        if (p == 1)
        {
            msgalert = 1;
            txt(i18n::s.get("core.food.hunger_status.starving"));
        }
        else if (p == 2)
        {
            msgalert = 1;
            txt(i18n::s.get("core.food.hunger_status.very_hungry"));
        }
        else if (p == 5)
        {
            msgalert = 1;
            txt(i18n::s.get("core.food.hunger_status.hungry"));
        }
        refresh_speed(cc);
    }
}



void cook()
{
    snd("core.cook1");
    item_separate(ci);
    s = itemname(ci);
    p = rnd(sdata(184, cc) + 6) + rnd((inv[cooktool].param1 / 50 + 1));
    if (p > sdata(184, cc) / 5 + 7)
    {
        p = sdata(184, cc) / 5 + 7;
    }
    p = rnd(p + 1);
    if (p > 3)
    {
        p = rnd(p(0));
    }
    if (sdata(184, cc) >= 5)
    {
        if (p < 3)
        {
            if (rnd(4) == 0)
            {
                p = 3;
            }
        }
    }
    if (sdata(184, cc) >= 10)
    {
        if (p < 3)
        {
            if (rnd(3) == 0)
            {
                p = 3;
            }
        }
    }
    p += inv[cooktool].param1 / 100;
    if (p > 9)
    {
        p = 9;
    }
    if (p < 1)
    {
        p = 1;
    }
    make_dish(ci, p);
    txt(i18n::s.get("core.food.cook", s(0), inv[cooktool], inv[ci]));
    item_stack(0, ci, 1);
    int rank = inv[ci].param2;
    if (rank > 2)
    {
        chara_gain_skill_exp(cdata[cc], 184, 30 + rank * 5);
    }
    refresh_burden_state();
}



void make_dish(int ingredient, int type)
{
    inv[ingredient].image = picfood(type, inv[ingredient].param1 / 1000);
    inv[ingredient].weight = 500;
    inv[ingredient].param2 = type;
    if (inv[ingredient].material == 35 && inv[ingredient].param3 >= 0)
    {
        inv[ingredient].param3 = game_data.date.hours() + 72;
    }
}



void apply_general_eating_effect(int cieat)
{
    tc = cc;
    DIM3(fdlist, 2, 10);
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        fdlist(0, cnt) = 0;
        fdlist(1, cnt) = 0;
    }
    nutrition = 2500;
    if (the_item_db[itemid2int(inv[ci].id)]->is_cargo)
    {
        nutrition += 2500;
    }
    fdmax = 0;
    i = inv[ci].param1 / 1000;
    if (i == 1)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (i == 8)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 2)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 3)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 7)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        nutrition = 2800;
    }
    if (i == 4)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 6)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 3000;
    }
    if (i == 5)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 60;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (the_item_db[itemid2int(inv[ci].id)]->category == 57000)
    {
        nutrition = nutrition * (100 + inv[ci].param2 * 15) / 100;
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        if (fdlist(1, cnt) > 0)
        {
            if (inv[ci].param2 < 3)
            {
                fdlist(1, cnt) = fdlist(1, cnt) / 2;
            }
            else
            {
                fdlist(1, cnt) =
                    fdlist(1, cnt) * (50 + inv[ci].param2 * 20) / 100;
            }
        }
        else if (inv[ci].param2 < 3)
        {
            fdlist(1, cnt) =
                fdlist(1, cnt) * ((3 - inv[ci].param2) * 100 + 100) / 100;
        }
        else
        {
            fdlist(1, cnt) = fdlist(1, cnt) * 100 / (inv[ci].param2 * 50);
        }
    }
    if (cc == 0)
    {
        p = inv[ci].param1 / 1000;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (cc == 0)
            {
                if (trait(41))
                {
                    if (inv[ci].id == ItemId::corpse)
                    {
                        s = chara_db_get_filter(int2charaid(inv[ci].subname));
                        if (strutil::contains(s(0), u8"/man/"))
                        {
                            txt(i18n::s.get(
                                "core.food.effect.human.delicious"));
                            break;
                        }
                    }
                }
            }
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    txt(i18n::s.get("core.food.effect.rotten"));
                    break;
                }
            }
            if (inv[ci].param2 == 0)
            {
                if (p == 1)
                {
                    txt(i18n::s.get("core.food.effect.raw_meat"));
                    break;
                }
                if (p == 7)
                {
                    txt(i18n::s.get("core.food.effect.powder"));
                    break;
                }
                if (p == 5)
                {
                    txt(i18n::s.get("core.food.effect.raw"));
                    break;
                }
                txt(i18n::s.get("core.food.effect.boring"));
                break;
            }
            if (inv[ci].param2 < 3)
            {
                txt(i18n::s.get("core.food.effect.quality.bad"));
                break;
            }
            if (inv[ci].param2 < 5)
            {
                txt(i18n::s.get("core.food.effect.quality.so_so"));
                break;
            }
            if (inv[ci].param2 < 7)
            {
                txt(i18n::s.get("core.food.effect.quality.good"));
                break;
            }
            if (inv[ci].param2 < 9)
            {
                txt(i18n::s.get("core.food.effect.quality.great"));
                break;
            }
            txt(i18n::s.get("core.food.effect.quality.delicious"));
        }
    }
    else if (inv[ci].material == 35)
    {
        if (inv[ci].param3 < 0)
        {
            txt(i18n::s.get("core.food.effect.raw_glum", cdata[cc]));
        }
    }
    if (inv[ci].id == ItemId::curaria)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        nutrition = 2500;
        if (cc == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.curaria"),
                Message::color{ColorIndex::green});
        }
    }
    if (inv[ci].id == ItemId::morgia)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 900;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cdata[cc], 10, 2);
        modify_potential(cdata[cc], 11, 2);
        if (cc == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.morgia"),
                Message::color{ColorIndex::green});
        }
    }
    if (inv[ci].id == ItemId::mareilon)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cdata[cc], 16, 2);
        modify_potential(cdata[cc], 15, 2);
        if (cc == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.mareilon"),
                Message::color{ColorIndex::green});
        }
    }
    if (inv[ci].id == ItemId::spenseweed)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 750;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        modify_potential(cdata[cc], 12, 2);
        modify_potential(cdata[cc], 13, 2);
        nutrition = 500;
        if (cc == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.spenseweed"),
                Message::color{ColorIndex::green});
        }
    }
    if (inv[ci].id == ItemId::alraunia)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 850;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cdata[cc], 17, 2);
        modify_potential(cdata[cc], 14, 2);
        if (cc == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.alraunia"),
                Message::color{ColorIndex::green});
        }
    }
    if (inv[ci].id == ItemId::stomafillia)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 20000;
    }
    if (inv[ci].id == ItemId::fortune_cookie)
    {
        nutrition = 750;
    }
    if (cc == 0)
    {
        if (inv[ci].material == 35)
        {
            if (inv[ci].param3 < 0)
            {
                eat_rotten_food();
            }
        }
    }
    if (inv[ci].id == ItemId::corpse)
    {
        s = chara_db_get_filter(int2charaid(inv[ci].subname));
        if (cc == 0)
        {
            if (strutil::contains(s(0), u8"/man/"))
            {
                if (trait(41))
                {
                    txt(i18n::s.get("core.food.effect.human.like"));
                }
                else
                {
                    txt(i18n::s.get("core.food.effect.human.dislike"));
                    damage_insanity(cdata[cc], 15);
                    status_ailment_damage(
                        cdata[cc], StatusAilment::insane, 150);
                    if (trait(41) == 0)
                    {
                        if (rnd(5) == 0)
                        {
                            trait_get_info(0, 41);
                            txt(traitrefn(0),
                                Message::color{ColorIndex::green});
                            trait(41) = 1;
                        }
                    }
                }
            }
            else if (trait(41))
            {
                txt(i18n::s.get(
                    "core.food.effect.human.would_have_rather_eaten"));
                nutrition = nutrition * 2 / 3;
            }
        }
    }
    if (inv[ci].id == ItemId::corpse ||
        ((inv[ci].id == ItemId::jerky || inv[ci].id == ItemId::egg) &&
         rnd(3) == 0))
    {
        chara_db_invoke_eating_effect(int2charaid(inv[ci].subname));
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        i = 100;
        if (cdata[cc].nutrition >= 5000)
        {
            p = (cdata[cc].nutrition - 5000) / 25;
            i = i * 100 / (100 + p);
        }
        if (cc != 0)
        {
            i = 1500;
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    i = 500;
                }
            }
        }
        if (i > 0)
        {
            chara_gain_skill_exp(
                cdata[cc], fdlist(0, cnt), fdlist(1, cnt) * i / 100);
        }
    }
    if (inv[ci].curse_state == CurseState::blessed)
    {
        nutrition = nutrition * 150 / 100;
    }
    if (is_cursed(inv[ci].curse_state))
    {
        nutrition = nutrition * 50 / 100;
    }
    cdata[cc].nutrition += nutrition;
    if (nutrition >= 3000)
    {
        if (rnd(10) == 0 || cdata[cc].nutrition >= 12000)
        {
            modify_weight(
                cdata[cc],
                rnd(3) + 1,
                cdata[cc].nutrition >= 20000 &&
                    rnd(30000 / std::max(1, cdata[cc].nutrition) + 2) == 0);
        }
    }
    if (cdata[cc].id == CharaId::cute_fairy)
    {
        if (nutrition >= 2000)
        {
            int cibk = ci;
            flt(calcobjlv(cdata[cc].level));
            flttypeminor = 58500;
            itemcreate(-1, 0, cdata[cc].position.x, cdata[cc].position.y, 0);
            txt(i18n::s.get("core.food.effect.bomb_fish", cdata[cc], inv[ci]),
                Message::color{ColorIndex::cyan});
            ci = cibk;
        }
    }
    if (inv[ci].id == ItemId::corpse)
    {
        if (inv[ci].subname == 319)
        {
            txt(i18n::s.get("core.food.effect.little_sister", cdata[cc]),
                Message::color{ColorIndex::green});
            if (rnd(sdata.get(2, cc).original_level *
                        sdata.get(2, cc).original_level +
                    1) < 2000)
            {
                chara_gain_fixed_skill_exp(cdata[cc], 2, 1000);
            }
            if (rnd(sdata.get(3, cc).original_level *
                        sdata.get(3, cc).original_level +
                    1) < 2000)
            {
                chara_gain_fixed_skill_exp(cdata[cc], 3, 1000);
            }
            for (int cnt = 100; cnt < 400; ++cnt)
            {
                if (!the_ability_db[cnt] ||
                    the_ability_db[cnt]->related_basic_attribute == 0 ||
                    sdata.get(cnt, cc).original_level == 0)
                {
                    continue;
                }
                modify_potential(cdata[cc], cnt, rnd(10) + 1);
            }
        }
    }
    if (inv[ci].id == ItemId::kagami_mochi)
    {
        txt(i18n::s.get("core.food.effect.hero_cheese"));
        chara_gain_fixed_skill_exp(cdata[cc], 19, 2000);
    }
    if (inv[ci].id == ItemId::rabbits_tail)
    {
        chara_gain_fixed_skill_exp(cdata[cc], 19, 1000);
    }
    if (inv[ci].id == ItemId::happy_apple)
    {
        chara_gain_fixed_skill_exp(cdata[cc], 19, 20000);
    }
    if (inv[ci].id == ItemId::hero_cheese)
    {
        chara_gain_fixed_skill_exp(cdata[cc], 2, 3000);
    }
    if (inv[ci].id == ItemId::magic_fruit)
    {
        chara_gain_fixed_skill_exp(cdata[cc], 3, 3000);
    }
    if (inv[ci].id == ItemId::fortune_cookie)
    {
        if (cc < 16)
        {
            txt(i18n::s.get("core.food.effect.fortune_cookie", cdata[cc]));
            read_talk_file(u8"%COOKIE2");
            if (inv[ci].curse_state == CurseState::blessed ||
                (inv[ci].curse_state == CurseState::none && rnd(2)))
            {
                read_talk_file(u8"%COOKIE1");
            }
            txt(""s + buff, Message::color{ColorIndex::orange});
        }
    }
    if (inv[ci].id == ItemId::sisters_love_fueled_lunch)
    {
        txt(i18n::s.get(
            "core.food.effect.sisters_love_fueled_lunch", cdata[cc]));
        heal_insanity(cdata[cc], 30);
    }
    if (inv[ci].is_poisoned())
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.food.effect.poisoned.text", cdata[cc]));
            txt(i18n::s.get("core.food.effect.poisoned.dialog"));
        }
        damage_hp(cdata[cc], rnd(250) + 250, -4);
        if (cdata[cc].state() != Character::State::alive)
        {
            if (cc != 0)
            {
                if (cdata[cc].relationship >= 0)
                {
                    modify_karma(cdata.player(), -1);
                }
            }
            return;
        }
    }
    if (inv[ci].is_aphrodisiac())
    {
        if (cc == 0)
        {
            txt(i18n::s.get("core.food.effect.spiked.self"));
        }
        else
        {
            txt(i18n::s.get("core.food.effect.spiked.other", cdata[cc]),
                Message::color{ColorIndex::cyan});
            cdata[cc].emotion_icon = 317;
            chara_modify_impression(cdata[cc], 30);
            modify_karma(cdata.player(), -10);
            lovemiracle(cc);
        }
        status_ailment_damage(cdata[cc], StatusAilment::dimmed, 500);
        cdata[cc].emotion_icon = 317;
    }
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[ci].enchantments[cnt].id;
        if (enc == 36)
        {
            p = rnd(inv[ci].enchantments[cnt].power / 50 + 1) + 1;
            heal_sp(cdata[cc], p);
            continue;
        }
        if (enc == 38)
        {
            p = rnd(inv[ci].enchantments[cnt].power / 25 + 1) + 1;
            heal_mp(cdata[cc], p / 5);
            continue;
        }
        if (enc == 37)
        {
            event_add(18, cc);
            continue;
        }
        if (enc == 40)
        {
            if (game_data.left_turns_of_timestop == 0)
            {
                txt(i18n::s.get("core.action.time_stop.begins", cdata[cc]),
                    Message::color{ColorIndex::cyan});
                game_data.left_turns_of_timestop =
                    inv[ci].enchantments[cnt].power / 100 + 1 + 1;
                continue;
            }
        }
        const auto enc2 = enc / 10000;
        if (enc2 != 0)
        {
            enc = enc % 10000;
            if (enc2 == 1)
            {
                if (is_in_fov(cdata[cc]))
                {
                    if (inv[ci].enchantments[cnt].power / 50 + 1 >= 0)
                    {
                        txt(i18n::s.get(
                            "core.food.effect.ability.develops",
                            cdata[cc],
                            i18n::s.get_m(
                                "ability",
                                the_ability_db.get_id_from_legacy(enc)->get(),
                                "name")));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.food.effect.ability.deteriorates",
                            cdata[cc],
                            i18n::s.get_m(
                                "ability",
                                the_ability_db.get_id_from_legacy(enc)->get(),
                                "name")));
                    }
                }
                chara_gain_skill_exp(
                    cdata[cc],
                    enc,
                    (inv[ci].enchantments[cnt].power / 50 + 1) * 100 *
                        (1 + (cc != 0) * 5));
                continue;
            }
            if (enc2 == 6)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get_enum_property(
                        "core.buff", enc + 10, "apply", cdata[cc]));
                }

                int legacy_id = 20 + (enc - 10);
                auto buff_id = the_buff_db.get_id_from_legacy(legacy_id);
                assert(buff_id);

                buff_add(
                    cdata[cc],
                    *buff_id,
                    (inv[ci].enchantments[cnt].power / 50 + 1) * 5 *
                        (1 + (cc != 0) * 2),
                    2000);

                continue;
            }
        }
    }
    eatstatus(inv[cieat].curse_state, cc);
}



std::string
foodname(int type, const std::string& ingredient_, int rank, int character_id)
{
    std::string ingredient = ingredient_;
    if (type == 1 || type == 8)
    {
        // Food created from character drops (meat and eggs)
        if (character_id == 0)
        {
            ingredient = i18n::s.get_enum_property(
                "core.food.names", "default_origin", type);
        }
        else
        {
            ingredient = chara_db_get_name(int2charaid(character_id));
        }
    }
    else if (type == 5 || type == 7)
    {
        // Food that always always has a default origin (bread and noodles)
        ingredient = i18n::s.get_enum_property(
            "core.food.names", "default_origin", type);
    }
    else if (ingredient == ""s)
    {
        // No ingredient name was provided
        ingredient = i18n::s.get_enum_property(
            "core.food.names", "default_origin", type);
    }

    if ((type < 1 || type > 8) || (rank < 1 || rank > 9))
    {
        return ingredient;
    }
    else
    {
        return i18n::s.get_enum_property(
            "core.food.names", type, "_" + std::to_string(rank), ingredient);
    }
}



void foods_get_rotten()
{
    for (int j = 0; j < ELONA_MAX_CHARACTERS + 1; ++j)
    {
        int chara = j;
        if (j == ELONA_MAX_CHARACTERS)
        {
            chara = -1; // On the ground.
        }
        else if (cdata[chara].state() == Character::State::empty)
        {
            continue;
        }

        for (const auto& item : inv.by_index(chara))
        {
            if (item.number() == 0)
            {
                continue;
            }
            _food_gets_rotten(chara, item.index);
        }
    }
}

} // namespace elona
