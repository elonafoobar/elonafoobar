#include "dmgheal.hpp"
#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "lua_env/lua_env.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "variables.hpp"



namespace elona
{


int prm_853;
int dmg_at_m141 = 0;



void healhp(int cc, int delta)
{
    cdata[cc].hp += delta;
    if (cdata[cc].hp > cdata[cc].max_hp)
    {
        cdata[cc].hp = cdata[cc].max_hp;
    }
}



void healmp(int cc, int delta)
{
    cdata[cc].mp += delta;
    if (cdata[cc].mp > cdata[cc].max_mp)
    {
        cdata[cc].mp = cdata[cc].max_mp;
    }
}



void healsp(int cc, int delta)
{
    cdata[cc].sp += delta;
    if (cdata[cc].sp > cdata[cc].max_sp)
    {
        cdata[cc].sp = cdata[cc].max_sp;
    }
}



int dmghp(int prm_853, int prm_854, int prm_855, int prm_856, int prm_857)
{
    int ele_at_m141 = 0;
    int r_at_m141 = 0;
    int dmglevel_at_m141 = 0;
    int f_at_m141 = 0;
    int se_at_m141 = 0;
    elona_vector1<int> p_at_m141;
    int exp_at_m141 = 0;
    bool is_player = false;
    elona::prm_853 = prm_853;
    ele_at_m141 = prm_856;
    if (txt3rd == 0)
    {
        is_player = prm_855 == 0;
    }
    else
    {
        is_player = false;
    }
    if (cdata[prm_853].state != 1)
    {
        end_dmghp();
        return 0;
    }
    dmg_at_m141 = prm_854 * (1 + (cdata[prm_853].furious > 0));
    if (prm_855 >= 0)
    {
        if (cdata[prm_855].furious > 0)
        {
            dmg_at_m141 *= 2;
        }
    }
    if (ele_at_m141 != 0 && ele_at_m141 < 61)
    {
        r_at_m141 = sdata(ele_at_m141, prm_853) / 50;
        if (r_at_m141 < 3)
        {
            dmg_at_m141 =
                dmg_at_m141 * 150 / clamp((r_at_m141 * 50 + 50), 40, 150);
        }
        else if (r_at_m141 < 10)
        {
            dmg_at_m141 = dmg_at_m141 * 100 / (r_at_m141 * 50 + 50);
        }
        else
        {
            dmg_at_m141 = 0;
        }
        dmg_at_m141 = dmg_at_m141 * 100 / (sdata(60, prm_853) / 2 + 50);
    }
    if (prm_855 == 0)
    {
        if (critical)
        {
            snd(3);
        }
        else
        {
            snd(2);
        }
    }
    if (cdata[prm_853].wet > 0)
    {
        if (ele_at_m141 == 50 || prm_855 == -9)
        {
            dmg_at_m141 = dmg_at_m141 / 3;
        }
        if (ele_at_m141 == 52)
        {
            dmg_at_m141 = dmg_at_m141 * 3 / 2;
        }
    }
    if (ele_at_m141)
    {
        if (ele_at_m141 != 60)
        {
            if (cdata[prm_853].is_immune_to_elemental_damage())
            {
                dmg_at_m141 = 0;
            }
        }
    }
    if (cdata[prm_853].is_metal())
    {
        dmg_at_m141 = rnd(dmg_at_m141 / 10 + 2);
    }
    if (cdata[prm_853].is_contracting_with_reaper())
    {
        if (cdata[prm_853].hp - dmg_at_m141 <= 0)
        {
            if (clamp(
                    25
                        + cdata[prm_853].buffs[buff_find(prm_853, 18)].power
                            / 17,
                    25,
                    80)
                >= rnd(100))
            {
                dmg_at_m141 *= -1;
            }
        }
    }
    if (cdata[prm_853].nullify_damage > 0)
    {
        if (cdata[prm_853].nullify_damage > rnd(100))
        {
            dmg_at_m141 = 0;
        }
    }
    if (ele_at_m141 == 658)
    {
        dmg_at_m141 = prm_854;
    }
    rtdmg = dmg_at_m141;

    if (prm_853 == 0 && cdata[0].god_id == core_god::opatos)
    {
        dmg_at_m141 = dmg_at_m141 * 90 / 100;
    }

    if (debug::voldemort && prm_853 == 0)
    {
        dmg_at_m141 = 0;
    }
    cdata[prm_853].hp -= dmg_at_m141;


    if (is_in_fov(prm_853))
    {
        add_damage_popup(std::to_string(dmg_at_m141), prm_853, {0, 0, 0});
    }


    if (ele_at_m141 == 56)
    {
        if (prm_855 >= 0)
        {
            if (dmg_at_m141 > 0)
            {
                healhp(
                    prm_855,
                    clamp(
                        rnd(dmg_at_m141 * (150 + prm_857 * 2) / 1000 + 10),
                        1,
                        cdata[prm_855].max_hp / 10 + rnd(5)));
            }
        }
    }
    if (prm_853 == 0)
    {
        gdata(30) = 0;
        if (cdata[prm_853].hp < 0)
        {
            if (event_id() != -1)
            {
                if (event_id() != 21)
                {
                    cdata[prm_853].hp = 1;
                }
            }
            if (gdata_current_map == 40)
            {
                cdata[prm_853].hp = 1;
            }
        }
    }
    if (dmg_at_m141 <= 0)
    {
        dmglevel_at_m141 = -1;
    }
    else
    {
        dmglevel_at_m141 = dmg_at_m141 * 6 / cdata[prm_853].max_hp;
    }
    if (cdata[prm_853].hp < 0)
    {
        if (prm_853 < 16)
        {
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (prm_853 == cnt)
                {
                    continue;
                }
                if (cdata[cnt].state != 1)
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
                txtef(9);
                txt(i18n::s.get("core.locale.damage.lay_hand", cdata[cnt]));
                txt(i18n::s.get("core.locale.damage.is_healed", cdata[prm_853]));
                cdata[prm_853].hp = cdata[prm_853].max_hp / 2;
                animode = 100 + prm_853;
                play_animation(19);
                snd(120);
                break;
            }
        }
        else if (cdata[prm_853].is_hung_on_sand_bag())
        {
            cdata[prm_853].hp = cdata[prm_853].max_hp;
        }
    }
    if (cdata[prm_853].hp >= 0)
    {
        if (dmglevel_at_m141 > 1)
        {
            spillblood(
                cdata[prm_853].position.x,
                cdata[prm_853].position.y,
                1 + rnd(2));
        }
        if (gdata(809) == 1)
        {
            txteledmg(0, is_player ? 0 : -1, prm_853, ele_at_m141);
            goto label_1369_internal;
        }
        if (dmglevel_at_m141 > 0)
        {
            if (cdata[prm_853].max_hp / 2 > cdata[prm_853].hp)
            {
                ++dmglevel_at_m141;
                if (cdata[prm_853].max_hp / 4 > cdata[prm_853].hp)
                {
                    ++dmglevel_at_m141;
                    if (cdata[prm_853].max_hp / 10 > cdata[prm_853].hp)
                    {
                        ++dmglevel_at_m141;
                    }
                }
            }
        }
        if (gdata(809) == 2)
        {
            txtcontinue();
            if (dmglevel_at_m141 == -1)
            {
                txt(i18n::s.get("core.locale.damage.levels.scratch", cdata[prm_853], is_player));
            }
            if (dmglevel_at_m141 == 0)
            {
                txtef(5);
                txt(i18n::s.get("core.locale.damage.levels.slightly", cdata[prm_853], is_player));
            }
            if (dmglevel_at_m141 == 1)
            {
                txtef(11);
                txt(i18n::s.get("core.locale.damage.levels.moderately", cdata[prm_853], is_player));
            }
            if (dmglevel_at_m141 == 2)
            {
                txtef(10);
                txt(i18n::s.get("core.locale.damage.levels.severely", cdata[prm_853], is_player));
            }
            if (dmglevel_at_m141 >= 3)
            {
                txtef(3);
                txt(i18n::s.get("core.locale.damage.levels.critically", cdata[prm_853], is_player));
            }
            rowact_check(prm_853);
            goto label_1369_internal;
        }
        if (dmglevel_at_m141 == 1)
        {
            if (is_in_fov(prm_853))
            {
                txtef(11);
                txt(i18n::s.get("core.locale.damage.reactions.screams", cdata[prm_853]));
            }
        }
        if (dmglevel_at_m141 == 2)
        {
            if (is_in_fov(prm_853))
            {
                txtef(10);
                txt(i18n::s.get("core.locale.damage.reactions.writhes_in_pain", cdata[prm_853]));
            }
        }
        if (dmglevel_at_m141 >= 3)
        {
            if (is_in_fov(prm_853))
            {
                txtef(3);
                txt(i18n::s.get("core.locale.damage.reactions.is_severely_hurt", cdata[prm_853]));
            }
        }
        if (dmg_at_m141 < 0)
        {
            if (cdata[prm_853].hp > cdata[prm_853].max_hp)
            {
                cdata[prm_853].hp = cdata[prm_853].max_hp;
            }
            if (is_in_fov(prm_853))
            {
                txtef(4);
                txt(i18n::s.get("core.locale.damage.is_healed", cdata[prm_853]));
            }
        }
    label_1369_internal:
        rowact_check(prm_853);
        if (cdata[prm_853].hp < cdata[prm_853].max_hp / 5)
        {
            if (prm_853 != 0)
            {
                if (cdata[prm_853].fear == 0)
                {
                    if (cdata[prm_853].is_immune_to_fear() == 0)
                    {
                        if (dmg_at_m141 * 100 / cdata[prm_853].max_hp + 10
                            > rnd(200))
                        {
                            f_at_m141 = 1;
                        }
                        else
                        {
                            f_at_m141 = 0;
                        }
                        if (prm_855 == 0)
                        {
                            if (trait(44))
                            {
                                f_at_m141 = 0;
                            }
                        }
                        if (f_at_m141)
                        {
                            cdata[prm_853].fear = rnd(20) + 5;
                            if (is_in_fov(prm_853))
                            {
                                txtef(4);
                                txt(i18n::s.get("core.locale.damage.runs_away_in_terror", cdata[prm_853]));
                            }
                        }
                    }
                }
            }
        }
        if (ele_at_m141)
        {
            if (ele_at_m141 == 59)
            {
                if (rnd(10) < prm_857 / 75 + 4)
                {
                    dmgcon(
                        prm_853,
                        status_ailment_t::blinded,
                        rnd(prm_857 / 3 * 2 + 1));
                }
                if (rnd(20) < prm_857 / 50 + 4)
                {
                    dmgcon(
                        prm_853,
                        status_ailment_t::paralyzed,
                        rnd(prm_857 / 3 * 2 + 1));
                }
                if (rnd(20) < prm_857 / 50 + 4)
                {
                    dmgcon(
                        prm_853,
                        status_ailment_t::confused,
                        rnd(prm_857 / 3 * 2 + 1));
                }
                if (rnd(20) < prm_857 / 50 + 4)
                {
                    dmgcon(
                        prm_853,
                        status_ailment_t::poisoned,
                        rnd(prm_857 / 3 * 2 + 1));
                }
                if (rnd(20) < prm_857 / 50 + 4)
                {
                    dmgcon(
                        prm_853,
                        status_ailment_t::sleep,
                        rnd(prm_857 / 3 * 2 + 1));
                }
            }
            if (ele_at_m141 == 52)
            {
                if (rnd(3 + (cdata[prm_853].quality >= 4) * 3) == 0)
                {
                    ++cdata[prm_853].paralyzed;
                }
            }
            if (ele_at_m141 == 53)
            {
                dmgcon(prm_853, status_ailment_t::blinded, rnd(prm_857 + 1));
            }
            if (ele_at_m141 == 58)
            {
                dmgcon(prm_853, status_ailment_t::paralyzed, rnd(prm_857 + 1));
            }
            if (ele_at_m141 == 54)
            {
                dmgcon(prm_853, status_ailment_t::confused, rnd(prm_857 + 1));
            }
            if (ele_at_m141 == 57)
            {
                dmgcon(prm_853, status_ailment_t::confused, rnd(prm_857 + 1));
            }
            if (ele_at_m141 == 55)
            {
                dmgcon(prm_853, status_ailment_t::poisoned, rnd(prm_857 + 1));
            }
            if (ele_at_m141 == 61)
            {
                dmgcon(prm_853, status_ailment_t::bleeding, rnd(prm_857 + 1));
            }
            if (ele_at_m141 == 62)
            {
                if (prm_853 == 0)
                {
                    modcorrupt(rnd(prm_857 + 1));
                }
            }
            if (ele_at_m141 == 63)
            {
                if (prm_853 == 0 || rnd(3) == 0)
                {
                    item_acid(prm_853, -1);
                }
            }
        }
        if ((ele_at_m141 == 50 || prm_855 == -9) && cdata[prm_853].wet == 0)
        {
            item_fire(prm_853, -1);
        }
        if (ele_at_m141 == 51)
        {
            item_cold(prm_853, -1);
        }
        if (cdata[prm_853].sleep != 0)
        {
            if (ele_at_m141 != 54 && ele_at_m141 != 58 && ele_at_m141 != 59)
            {
                cdata[prm_853].sleep = 0;
                txt(i18n::s.get("core.locale.damage.sleep_is_disturbed", cdata[prm_853]));
            }
        }
        if (prm_855 == 0)
        {
            hostileaction(0, prm_853);
            gdata(94) = prm_853;
        }
        if (prm_853 == 0)
        {
            if (cdata[prm_853].max_hp / 4 > cdata[prm_853].hp)
            {
                if (config::instance().sound)
                {
                    if (config::instance().heart == 1)
                    {
                        if (!CHECKPLAY(32))
                        {
                            snd(32);
                        }
                    }
                }
            }
        }
        if (cdata[prm_853].explodes())
        {
            if (rnd(3) == 0)
            {
                cdata[prm_853].will_explode_soon() = true;
                txtef(9);
                txt(i18n::s.get("core.locale.damage.explode_click"));
            }
        }
        if (cdata[prm_853].splits())
        {
            if (gdata(809) != 1)
            {
                if (dmg_at_m141 > cdata[prm_853].max_hp / 20 || rnd(10) == 0)
                {
                    if (mdata(6) != 1)
                    {
                        if (chara_copy(prm_853))
                        {
                            txt(i18n::s.get("core.locale.damage.splits", cdata[prm_853]));
                        }
                    }
                }
            }
        }
        if (cdata[prm_853].splits2())
        {
            if (gdata(809) != 1)
            {
                if (rnd(3) == 0)
                {
                    if (cdata[prm_853].confused == 0
                        && cdata[prm_853].dimmed == 0
                        && cdata[prm_853].poisoned == 0
                        && cdata[prm_853].paralyzed == 0
                        && cdata[prm_853].blind == 0)
                    {
                        if (mdata(6) != 1)
                        {
                            if (chara_copy(prm_853))
                            {
                                txt(i18n::s.get("core.locale.damage.splits", cdata[prm_853]));
                            }
                        }
                    }
                }
            }
        }
        if (cdata[prm_853].is_quick_tempered())
        {
            if (gdata(809) != 1)
            {
                if (cdata[prm_853].furious == 0)
                {
                    if (rnd(20) == 0)
                    {
                        if (is_in_fov(prm_853))
                        {
                            txtef(4);
                                txt(i18n::s.get("core.locale.damage.is_engulfed_in_fury", cdata[prm_853]));
                        }
                        cdata[prm_853].furious += rnd(30) + 15;
                    }
                }
            }
        }
        if (prm_855 >= 0)
        {
            f_at_m141 = 0;
            if (cdata[prm_853].relationship <= -3)
            {
                if (cdata[prm_855].original_relationship > -3)
                {
                    if (cdata[prm_853].hate == 0 || rnd(4) == 0)
                    {
                        f_at_m141 = 1;
                    }
                }
            }
            else if (cdata[prm_855].original_relationship <= -3)
            {
                if (cdata[prm_853].hate == 0 || rnd(4) == 0)
                {
                    f_at_m141 = 1;
                }
            }
            if (prm_855 != 0)
            {
                if (cdata[prm_855].enemy_id == prm_853)
                {
                    if (rnd(3) == 0)
                    {
                        f_at_m141 = 1;
                    }
                }
            }
            if (f_at_m141)
            {
                if (prm_853 != 0)
                {
                    cdata[prm_853].enemy_id = prm_855;
                    if (cdata[prm_853].hate == 0)
                    {
                        cdata[prm_853].emotion_icon = 218;
                        cdata[prm_853].hate = 20;
                    }
                    else
                    {
                        cdata[prm_853].hate += 2;
                    }
                }
            }
        }
    }

    {
        auto handle = lua::lua.get_handle_manager().get_chara_handle(cdata[prm_853]);
        lua::lua.get_event_manager().run_callbacks<lua::event_kind_t::character_damaged>(handle, dmg_at_m141);
    }

    if (cdata[prm_853].hp < 0)
    {
        se_at_m141 = eleinfo(ele_at_m141, 1);
        if (se_at_m141)
        {
            snd(se_at_m141, false, false);
        }
        txtef(3);
        if (prm_855 >= 0)
        {
            if (ele_at_m141)
            {
                if (prm_853 >= 16 && gdata(809) == 2)
                {
                    txtcontinue();
                    txteledmg(1, is_player, prm_853, ele_at_m141);
                }
                else
                {
                    txteledmg(2, is_player, prm_853, ele_at_m141);
                }
            }
            else
            {
                p_at_m141 = rnd(4);
                if (p_at_m141 == 0)
                {
                    if (prm_853 >= 16 && gdata(809) == 2)
                    {
                        txtcontinue();
                        txt(i18n::s.get("core.locale.death_by.chara.transformed_into_meat.active",
                                        cdata[prm_853], is_player));
                    }
                    else
                    {
                        txt(i18n::s.get("core.locale.death_by.chara.transformed_into_meat.passive",
                                        cdata[prm_853], is_player));
                    }
                }
                if (p_at_m141 == 1)
                {
                    if (prm_853 >= 16 && gdata(809) == 2)
                    {
                        txtcontinue();
                        txt(i18n::s.get("core.locale.death_by.chara.destroyed.active",
                                        cdata[prm_853], is_player));
                    }
                    else
                    {
                        txt(i18n::s.get("core.locale.death_by.chara.destroyed.passive",
                                        cdata[prm_853], is_player));
                    }
                }
                if (p_at_m141 == 2)
                {
                    if (prm_853 >= 16 && gdata(809) == 2)
                    {
                        txtcontinue();
                        txt(i18n::s.get("core.locale.death_by.chara.minced.active",
                                        cdata[prm_853], is_player));
                    }
                    else
                    {
                        txt(i18n::s.get("core.locale.death_by.chara.minced.passive",
                                        cdata[prm_853], is_player));
                    }
                }
                if (p_at_m141 == 3)
                {
                    if (prm_853 >= 16 && gdata(809) == 2)
                    {
                        txtcontinue();
                        txt(i18n::s.get("core.locale.death_by.chara.killed.active",
                                        cdata[prm_853], is_player));
                    }
                    else
                    {
                        txt(i18n::s.get("core.locale.death_by.chara.killed.passive",
                                        cdata[prm_853], is_player));
                    }
                }
            }
            ndeathcause = i18n::s.get("core.locale.death_by.chara.killed.passive",
                                      cdata[prm_855]);
        }
        else
        {
            if (prm_855 == -6)
            {
                dmgheal_death_by_backpack(cdata[prm_853]);
            }
            else
            {
                int death_kind = -prm_855;

                txt(i18n::s.get("core.locale.death_by.other._" +
                                std::to_string(death_kind) +
                                ".text",
                                cdata[prm_853]));
                if (prm_853 == 0)
                {
                    ndeathcause = i18n::s.get("core.locale.death_by.other._" +
                                              std::to_string(death_kind) +
                                              ".death_cause");
                }
            }
        }
        if (prm_855 == -9 || ele_at_m141 == 50)
        {
            mef_add(
                cdata[prm_853].position.x,
                cdata[prm_853].position.y,
                5,
                24,
                rnd(10) + 5,
                100,
                prm_855);
        }
        if (ele_at_m141 == 56)
        {
            if (prm_855 >= 0)
            {
                if (dmg_at_m141 > 0)
                {
                    healhp(cc, rnd(dmg_at_m141 * (200 + prm_857) / 1000 + 5));
                }
            }
        }
        if (gdata_mount != prm_853 || prm_853 == 0)
        {
            cell_removechara(
                cdata[prm_853].position.x, cdata[prm_853].position.y);
        }
        if (cdata[prm_853].character_role == 0)
        {
            cdata[prm_853].state = 0;
        }
        else if (cdata[prm_853].character_role == 13)
        {
            cdata[prm_853].state = 4;
            cdata[prm_853].time_to_revive = gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 24
                + rnd(12);
        }
        else
        {
            cdata[prm_853].state = 2;
            cdata[prm_853].time_to_revive = gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 48;
        }
        if (prm_853 != 0)
        {
            if (prm_853 < 16)
            {
                chara_mod_impression(prm_853, -10);
                cdata[prm_853].state = 6;
                cdata[prm_853].current_map = 0;
                if (cdata[prm_853].is_escorted() == 1)
                {
                    event_add(15, cdata[prm_853].id);
                    cdata[prm_853].state = 0;
                }
                if (cdata[prm_853].is_escorted_in_sub_quest() == 1)
                {
                    cdata[prm_853].state = 0;
                }
            }
        }
        if (prm_853 == 0)
        {
            cell_draw();
        }
        if (cdata[prm_853].breaks_into_debris())
        {
            if (is_in_fov(prm_853))
            {
                x = cdata[prm_853].position.x;
                y = cdata[prm_853].position.y;
                snd(45, false, false);
                animeblood(prm_853, 1, ele_at_m141);
            }
            spillfrag(cdata[prm_853].position.x, cdata[prm_853].position.y, 3);
        }
        else
        {
            snd(8 + rnd(2), false, false);
            animeblood(prm_853, 0, ele_at_m141);
            spillblood(cdata[prm_853].position.x, cdata[prm_853].position.y, 4);
        }
        if (prm_853 == 0)
        {
            ++gdata_death_count;
        }
        if (prm_853 == gdata(94))
        {
            gdata(94) = 0;
        }
        if (prm_855 >= 0)
        {
            if (prm_855 != 0)
            {
                chara_custom_talk(prm_855, 103);
            }
            exp_at_m141 = clamp(cdata[prm_853].level, 1, 200)
                    * clamp((cdata[prm_853].level + 1), 1, 200)
                    * clamp((cdata[prm_853].level + 2), 1, 200) / 20
                + 8;
            if (cdata[prm_853].level > cdata[prm_855].level)
            {
                exp_at_m141 /= 4;
            }
            if (cdata[prm_853].splits() || cdata[prm_853].splits2())
            {
                exp_at_m141 /= 20;
            }
            cdata[prm_855].experience += exp_at_m141;
            if (prm_855 == 0)
            {
                gdata_sleep_experience += exp_at_m141;
            }
            cdata[prm_855].hate = 0;
            if (prm_855 < 16)
            {
                cdata[prm_855].enemy_id = 0;
                cdata[0].enemy_id = 0;
                gdata(94) = 0;
            }
        }
        if (prm_853 != 0)
        {
            if (gdata_current_map != 35)
            {
                if (gdata_current_map != 42)
                {
                    if (cdata[prm_853].id == 2)
                    {
                        event_add(1);
                    }
                    if (cdata[prm_853].id == 141)
                    {
                        txtef(2);
                        txt(lang(
                            u8"愚者の魔石を手に入れた！"s,
                            u8"You obtain the fool's magic stone!"s));
                        snd(51);
                        gdata_magic_stone_of_fool = 1;
                    }
                    if (cdata[prm_853].id == 143)
                    {
                        txtef(2);
                        txt(lang(
                            u8"覇者の魔石を手に入れた！"s,
                            u8"You obtain the king's magic stone!"s));
                        snd(51);
                        gdata_magic_stone_of_king = 1;
                    }
                    if (cdata[prm_853].id == 144)
                    {
                        txtef(2);
                        txt(lang(
                            u8"賢者の魔石を手に入れた！"s,
                            u8"You obtain the sage's magic stone!"s));
                        snd(51);
                        gdata_magic_stone_of_sage = 1;
                    }
                    if (cdata[prm_853].id == 242)
                    {
                        if (gdata_novice_knight < 1000)
                        {
                            gdata_novice_knight = 2;
                            snd(44);
                            txtef(2);
                            txt(lang(
                                u8"ジャーナルが更新された。"s,
                                u8"Your journal has been updated."s));
                        }
                    }
                    if (cdata[prm_853].id == 257)
                    {
                        if (gdata_pyramid_trial < 1000)
                        {
                            gdata_pyramid_trial = 1000;
                            snd(44);
                            txtef(2);
                            txt(lang(
                                u8"ジャーナルが更新された。"s,
                                u8"Your journal has been updated."s));
                            txt(lang(
                                u8"クエストを達成した！"s,
                                u8"You have completed the quest!"s));
                            snd(51);
                        }
                    }
                    if (cdata[prm_853].id == 300)
                    {
                        if (gdata_minotaur_king < 1000)
                        {
                            gdata_minotaur_king = 2;
                            snd(44);
                            txtef(2);
                            txt(lang(
                                u8"ジャーナルが更新された。"s,
                                u8"Your journal has been updated."s));
                        }
                    }
                    if (cdata[prm_853].id == 318)
                    {
                        event_add(
                            27,
                            cdata[prm_853].position.x,
                            cdata[prm_853].position.y);
                    }
                    if (cdata[prm_853].id == 319)
                    {
                        ++gdata_kill_count_of_little_sister;
                        txtef(3);
                        txt(lang(
                            u8"リトルシスター殺害"s
                                + gdata_kill_count_of_little_sister
                                + u8"回、救出"s
                                + gdata_save_count_of_little_sister + u8"回。"s,
                            u8"You have saved little sister "s
                                + gdata_save_count_of_little_sister
                                + u8" times and killed "s
                                + gdata_kill_count_of_little_sister
                                + u8" times."s));
                    }
                    if (gdata_current_dungeon_level
                            == adata(10, gdata_current_map)
                        || gdata_current_map == 42)
                    {
                        if (adata(20, gdata_current_map) == prm_853
                            && cdata[prm_853].is_lord_of_dungeon() == 1)
                        {
                            event_add(5);
                        }
                    }
                    if (cdata[prm_853].id == 331)
                    {
                        if (rnd(4) == 0)
                        {
                            event_add(
                                28,
                                cdata[prm_853].position.x,
                                cdata[prm_853].position.y);
                        }
                    }
                    quest_check();
                }
                else if (gdata_current_map == 42)
                {
                    if (adata(20, gdata_current_map) == prm_853
                        && cdata[prm_853].is_lord_of_dungeon() == 1)
                    {
                        event_add(5);
                    }
                }
            }
        }
        if (prm_853 != 0)
        {
            ++npcmemory(0, cdata[prm_853].id);
            chara_custom_talk(prm_853, 102);
            if (prm_853 < 16)
            {
                txt(i18n::s.get("core.locale.damage.you_feel_sad"));
            }
        }
        if (cdata[prm_853].state == 0)
        {
            // Exclude town residents because they occupy character slots even
            // if they are dead.
            modify_crowd_density(prm_853, -1);
        }
        if (gdata_mount)
        {
            if (prm_853 == gdata_mount)
            {
                txt(i18n::s.get("core.locale.damage.get_off_corpse", cdata[prm_853]));
                ride_end();
            }
        }
        check_kill(prm_855, prm_853);
        catitem = 0;
        rollanatomy = 0;
        if (rnd(60) == 0)
        {
            rollanatomy = 1;
        }
        if (prm_855 >= 0)
        {
            if (cdata[prm_855].id == 260)
            {
                catitem = prm_855;
            }
            if (int(std::sqrt(sdata(161, prm_855))) > rnd(150))
            {
                rollanatomy = 1;
            }
            skillexp(161, prm_855, 10 + rollanatomy * 4);
        }
        rc = prm_853;
        character_drops_item();
        if (gdata_current_map == 40)
        {
            if (rnd(5) == 0)
            {
                snd(69);
            }
        }
        if (cdata[prm_853].is_death_master() == 1)
        {
            txt(i18n::s.get("core.locale.damage.death_word_breaks"));
            for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                p_at_m141 = cnt;
                for (int cnt = 0; cnt < 16; ++cnt)
                {
                    if (cdata[p_at_m141].buffs[cnt].id == 0)
                    {
                        break;
                    }
                    if (cdata[p_at_m141].buffs[cnt].id == 16)
                    {
                        buff_delete(p_at_m141, cnt);
                        --cnt;
                        continue;
                    }
                }
            }
        }
        if (prm_855 == 0)
        {
            if (gdata_catches_god_signal)
            {
                if (rnd(20) == 0)
                {
                    txtgod(cdata[0].god_id, 9);
                }
            }
        }
        end_dmghp();

        chara_killed(cdata[prm_853]);

        return 0;
    }
    end_dmghp();
    return 1;
}



void end_dmghp()
{
    if (cdata[prm_853].is_hung_on_sand_bag())
    {
        if (is_in_fov(prm_853))
        {
            txt(u8"("s + dmg_at_m141 + u8")"s + i18n::space_if_needed());
            if (rnd(20) == 0)
            {
                int picked = rnd(6);
                txt(i18n::s.get("core.locale.damage.sand_bag._" + std::to_string(picked)));
            }
        }
    }
    gdata(809) = 0;
    txt3rd = 0;
    return;
}



void dmgmp(int cc, int delta)
{
    cdata[cc].mp -= delta;
    if (cdata[cc].mp < -999999)
    {
        cdata[cc].mp = -999999;
    }
    if (cdata[cc].mp < 0)
    {
        gain_mana_capacity_experience(cc);
        int damage = -cdata[cc].mp * 400 / (100 + sdata(164, cc) * 10);
        if (cc == 0)
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
        txt(i18n::s.get("core.locale.damage.magic_reaction_hurts", cdata[cc]));
        dmghp(cc, damage, -2);
    }
}



void dmgsp(int cc, int delta)
{
    if (cc != 0 || debug::voldemort)
        return;

    if (cdata[cc].sp >= -100)
    {
        cdata[cc].sp -= delta;
    }
}



void healsan(int prm_862, int prm_863)
{
    cdata[prm_862].insanity -= prm_863;
    if (cdata[prm_862].insanity < 0)
    {
        cdata[prm_862].insanity = 0;
    }
    return;
}



void damage_insanity(int cc, int delta)
{
    if (cdata[cc].quality >= 4)
        return;

    int resistance = std::max(sdata(54, cc) / 50, 1);
    if (resistance > 10)
        return;

    delta /= resistance;
    if (cc < 16)
    {
        if (trait(166))
        {
            delta -= rnd(4);
        }
    }
    delta = std::max(delta, 0);
    cdata[cc].insanity += delta;
    if (rnd(10) == 0 || rnd(delta + 1) > 5 || rnd(cdata[cc].insanity + 1) > 50)
    {
        dmgcon(cc, status_ailment_t::insane, 100);
    }
}



bool actionsp(int cc, int sp)
{
    if (cc != 0 || debug::voldemort)
        return true;

    if (cdata[cc].sp < 50 && cdata[cc].sp < rnd(75))
    {
        dmgsp(cc, sp);
        return false;
    }
    dmgsp(cc, sp);
    return true;
}

void dmgheal_death_by_backpack(character& chara)
{
    int heaviest_item_index = -1;
    int heaviest_weight = 0;
    std::string heaviest_item_name;

    for (const auto& cnt : items(chara.index))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].weight > heaviest_weight)
        {
            heaviest_item_index = cnt;
            heaviest_weight = inv[cnt].weight;
        }
    }
    if (heaviest_item_index == -1)
    {
        heaviest_item_name = i18n::s.get("core.locale.death_by.other._6.backpack");
    }
    else
    {
        heaviest_item_name = itemname(heaviest_item_index);
    }
    txt(i18n::s.get("core.locale.death_by.other._6.text",
                    chara,
                    heaviest_item_name));
    if (chara.index == 0)
    {
        ndeathcause = i18n::s.get("core.locale.death_by.other._6.death_cause", heaviest_item_name);
    }
}


} // namespace elona
