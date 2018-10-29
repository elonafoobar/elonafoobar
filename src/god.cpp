#include "god.hpp"
#include <iostream>
#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "message.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{


GodDB the_god_db;


void txtgod(const GodId& id, int type)
{
    if (id.empty())
        return;

    std::string message;
    switch (type)
    {
    case 12: message = i18n::_(u8"god", id, u8"random"); break;
    case 9: message = i18n::_(u8"god", id, u8"kill"); break;
    case 10: message = i18n::_(u8"god", id, u8"night"); break;
    case 11: message = i18n::_(u8"god", id, u8"welcome"); break;
    case 5: message = i18n::_(u8"god", id, u8"believe"); break;
    case 1: message = i18n::_(u8"god", id, u8"betray"); break;
    case 2: message = i18n::_(u8"god", id, u8"take_over"); break;
    case 3: message = i18n::_(u8"god", id, u8"fail_to_take_over"); break;
    case 4: message = i18n::_(u8"god", id, u8"offer"); break;
    case 6: message = i18n::_(u8"god", id, u8"receive_gift"); break;
    case 7: message = i18n::_(u8"god", id, u8"ready_to_receive_gift"); break;
    case 8: message = i18n::_(u8"god", id, u8"ready_to_receive_gift2"); break;
    default: assert(0);
    }

    txtef(5);
    if (type == 6)
    {
    }
    txt(message);
}



int modpiety(int prm_1035)
{
    if (game_data.god_rank == 4)
    {
        if (cdata.player().piety_point >= 4000)
        {
            ++game_data.god_rank;
            txtgod(cdata.player().god_id, 8);
        }
    }
    if (game_data.god_rank == 2)
    {
        if (cdata.player().piety_point >= 2500)
        {
            ++game_data.god_rank;
            txtgod(cdata.player().god_id, 7);
        }
    }
    if (game_data.god_rank == 0)
    {
        if (cdata.player().piety_point >= 1500)
        {
            ++game_data.god_rank;
            txtgod(cdata.player().god_id, 7);
        }
    }
    if (sdata(181, 0) * 100 < cdata.player().piety_point)
    {
        txt(i18n::s.get("core.locale.god.indifferent"));
        return 0;
    }
    cdata.player().piety_point += prm_1035
        / (1 + (game_data.current_map == mdata_t::MapId::show_house) * 9);
    return 1;
}



void set_npc_religion()
{
    if (!cdata[tc].god_id.empty() || cdata[tc].has_learned_words() || tc == 0)
    {
        return;
    }
    randomize(game_data.random_seed + game_data.current_map);
    cdata[tc].god_id = core_god::int2godid(rnd(8));
    randomize();
    if (cdata[tc].god_id.empty() || rnd(4) == 0)
    {
        cdata[tc].has_learned_words() = true;
    }
}



void apply_god_blessing(int cc)
{
    if (cdata[cc].god_id == core_god::mani)
    {
        if (sdata(12, cc) > 0)
        {
            sdata(12, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(13, cc) > 0)
        {
            sdata(13, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 14 + sdata(181, 0) / 10);
        }
        if (sdata(154, cc) > 0)
        {
            sdata(154, cc) +=
                clamp(cdata[cc].piety_point / 500, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(110, cc) > 0)
        {
            sdata(110, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 18 + sdata(181, 0) / 10);
        }
        if (sdata(159, cc) > 0)
        {
            sdata(159, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(158, cc) > 0)
        {
            sdata(158, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(176, cc) > 0)
        {
            sdata(176, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(179, cc) > 0)
        {
            sdata(179, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 12 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::lulwy)
    {
        if (sdata(13, cc) > 0)
        {
            sdata(13, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(18, cc) > 0)
        {
            sdata(18, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 30 + sdata(181, 0) / 10);
        }
        if (sdata(108, cc) > 0)
        {
            sdata(108, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(109, cc) > 0)
        {
            sdata(109, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(157, cc) > 0)
        {
            sdata(157, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(174, cc) > 0)
        {
            sdata(174, cc) +=
                clamp(cdata[cc].piety_point / 550, 1, 8 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::itzpalt)
    {
        if (sdata(16, cc) > 0)
        {
            sdata(16, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 18 + sdata(181, 0) / 10);
        }
        if (sdata(155, cc) > 0)
        {
            sdata(155, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 15 + sdata(181, 0) / 10);
        }
        if (sdata(50, cc) > 0)
        {
            sdata(50, cc) +=
                clamp(cdata[cc].piety_point / 50, 1, 200 + sdata(181, 0) / 10);
        }
        if (sdata(51, cc) > 0)
        {
            sdata(51, cc) +=
                clamp(cdata[cc].piety_point / 50, 1, 200 + sdata(181, 0) / 10);
        }
        if (sdata(52, cc) > 0)
        {
            sdata(52, cc) +=
                clamp(cdata[cc].piety_point / 50, 1, 200 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::ehekatl)
    {
        if (sdata(17, cc) > 0)
        {
            sdata(17, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 20 + sdata(181, 0) / 10);
        }
        if (sdata(19, cc) > 0)
        {
            sdata(19, cc) +=
                clamp(cdata[cc].piety_point / 100, 1, 50 + sdata(181, 0) / 10);
        }
        if (sdata(173, cc) > 0)
        {
            sdata(173, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 15 + sdata(181, 0) / 10);
        }
        if (sdata(164, cc) > 0)
        {
            sdata(164, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 17 + sdata(181, 0) / 10);
        }
        if (sdata(185, cc) > 0)
        {
            sdata(185, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(158, cc) > 0)
        {
            sdata(158, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 8 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::opatos)
    {
        if (sdata(10, cc) > 0)
        {
            sdata(10, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 11 + sdata(181, 0) / 10);
        }
        if (sdata(11, cc) > 0)
        {
            sdata(11, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(168, cc) > 0)
        {
            sdata(168, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 15 + sdata(181, 0) / 10);
        }
        if (sdata(153, cc) > 0)
        {
            sdata(153, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(163, cc) > 0)
        {
            sdata(163, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(174, cc) > 0)
        {
            sdata(174, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 8 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::jure)
    {
        if (sdata(15, cc) > 0)
        {
            sdata(15, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(154, cc) > 0)
        {
            sdata(154, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 18 + sdata(181, 0) / 10);
        }
        if (sdata(155, cc) > 0)
        {
            sdata(155, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(161, cc) > 0)
        {
            sdata(161, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 9 + sdata(181, 0) / 10);
        }
        if (sdata(184, cc) > 0)
        {
            sdata(184, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(174, cc) > 0)
        {
            sdata(174, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(164, cc) > 0)
        {
            sdata(164, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 12 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::kumiromi)
    {
        if (sdata(13, cc) > 0)
        {
            sdata(13, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(12, cc) > 0)
        {
            sdata(12, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(14, cc) > 0)
        {
            sdata(14, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(180, cc) > 0)
        {
            sdata(180, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(178, cc) > 0)
        {
            sdata(178, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(177, cc) > 0)
        {
            sdata(177, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 9 + sdata(181, 0) / 10);
        }
        if (sdata(150, cc) > 0)
        {
            sdata(150, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 8 + sdata(181, 0) / 10);
        }
    }
}



void god_proc_switching_penalty()
{
    if (rtval == 0)
    {
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh - inf_verh);
        gmode(2);
        render_hud();
        redraw();
        if (!cdata.player().god_id.empty())
        {
            mode = 9;
            txtef(8);
            txt(i18n::s.get(
                "core.locale.god.enraged",
                i18n::_(u8"god", cdata.player().god_id, u8"name")));
            txtgod(cdata.player().god_id, 1);
            redraw();
            efid = 622;
            efp = 10000;
            tc = 0;
            magic();
            snd("core.punish1");
            mode = 0;
            await(Config::instance().animewait * 20);
        }
        cdata.player().god_id = core_god::int2godid(inv[ci].param1);
        switch_religion();
        msg_halt();
    }
    chara_refresh(0);
}



void switch_religion()
{
    cdata.player().piety_point = 0;
    cdata.player().praying_point = 500;
    game_data.god_rank = 0;
    spact(23) = 0;
    spact(24) = 0;
    spact(25) = 0;
    if (cdata.player().god_id.empty())
    {
        txtef(5);
        txt(i18n::s.get("core.locale.god.switch.unbeliever"));
    }
    else
    {
        animode = 100;
        MiracleAnimation().play();
        snd("core.complete1");
        txtef(5);
        txt(i18n::s.get(
            "core.locale.god.switch.follower",
            i18n::_(u8"god", cdata.player().god_id, u8"name")));
        if (cdata.player().god_id == core_god::itzpalt)
        {
            spact(24) = 1;
        }
        if (cdata.player().god_id == core_god::jure)
        {
            spact(23) = 1;
        }
        if (cdata.player().god_id == core_god::lulwy)
        {
            spact(25) = 1;
        }
        txtgod(cdata.player().god_id, 5);
    }
}



TurnResult do_pray()
{
    if (cdata.player().god_id.empty())
    {
        txt(i18n::s.get("core.locale.god.pray.do_not_believe"));
        return TurnResult::turn_end;
    }
    txtnew();
    txt(i18n::s.get("core.locale.god.pray.prompt"));
    rtval = yes_or_no(promptx, prompty, 160);
    if (rtval != 0)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    txt(i18n::s.get(
        "core.locale.god.pray.you_pray_to",
        i18n::_(u8"god", cdata.player().god_id, u8"name")));
    if (cdata.player().piety_point < 200 || cdata.player().praying_point < 1000)
    {
        i18n::s.get(
            "core.locale.god.pray.indifferent",
            i18n::_(u8"god", cdata.player().god_id, u8"name"));
        return TurnResult::turn_end;
    }
    animode = 100;
    MiracleAnimation().play();
    snd("core.pray2");
    efid = 1120;
    efp = 100;
    tc = 0;
    magic();
    efid = 451;
    efp = 200;
    tc = 0;
    magic();
    cdata.player().praying_point = 0;
    cdata.player().piety_point = cdata.player().piety_point * 85 / 100;
    if (game_data.god_rank % 2 == 1)
    {
        txtgod(cdata.player().god_id, 6);
        if (game_data.god_rank == 1)
        {
            f = 0;
            p = 0;
            for (int cnt = 1; cnt < 16; ++cnt)
            {
                if (cdata[cnt].state() != Character::State::empty)
                {
                    if (cdatan(2, cnt) == u8"servant"s)
                    {
                        ++p;
                        if (p >= 2)
                        {
                            f = 1;
                            txt(i18n::s.get(
                                "core.locale.god.pray.servant.no_more"));
                            break;
                        }
                    }
                }
            }
            if (f == 0)
            {
                if (chara_get_free_slot_ally() == 0)
                {
                    f = 1;
                    txt(i18n::s.get(
                        "core.locale.god.pray.servant.party_is_full"));
                }
            }
            if (f)
            {
                txt(i18n::s.get("core.locale.god.pray.servant.prompt_decline"));
                rtval = yes_or_no(promptx, prompty, 160);
                if (rtval == 0)
                {
                    ++game_data.god_rank;
                }
                return TurnResult::turn_end;
            }
            flt();
            dbid = 0;
            txtef(4);
            if (cdata.player().god_id == core_god::mani)
            {
                dbid = 262;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.mani"));
            }
            if (cdata.player().god_id == core_god::lulwy)
            {
                dbid = 263;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.lulwy"));
            }
            if (cdata.player().god_id == core_god::itzpalt)
            {
                dbid = 264;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.itzpalt"));
            }
            if (cdata.player().god_id == core_god::ehekatl)
            {
                dbid = 260;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.ehekatl"));
            }
            if (cdata.player().god_id == core_god::opatos)
            {
                dbid = 265;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.opatos"));
            }
            if (cdata.player().god_id == core_god::jure)
            {
                dbid = 266;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.jure"));
            }
            if (cdata.player().god_id == core_god::kumiromi)
            {
                dbid = 261;
                txt(i18n::s.get("core.locale.god.pray.servant.desc.kumiromi"));
            }
            novoidlv = 1;
            chara_create(56, dbid, -3, 0);
            rc = 56;
            new_ally_joins();
        }
        if (game_data.god_rank == 3)
        {
            flt();
            dbid = 0;
            if (cdata.player().god_id == core_god::lulwy)
            {
                dbid = 680;
            }
            if (cdata.player().god_id == core_god::jure)
            {
                dbid = 681;
            }
            if (cdata.player().god_id == core_god::kumiromi)
            {
                dbid = 682;
            }
            if (cdata.player().god_id == core_god::mani)
            {
                dbid = 683;
            }
            if (dbid != 0)
            {
                if (itemmemory(1, dbid))
                {
                    dbid = 559;
                }
                itemcreate(
                    -1,
                    dbid,
                    cdata.player().position.x,
                    cdata.player().position.y,
                    0);
            }
            else
            {
                nostack = 1;
                itemcreate(
                    -1,
                    672,
                    cdata.player().position.x,
                    cdata.player().position.y,
                    0);
                if (cdata.player().god_id == core_god::itzpalt)
                {
                    inv[ci].param1 = 165;
                }
                if (cdata.player().god_id == core_god::ehekatl)
                {
                    inv[ci].param1 = 163;
                }
                if (cdata.player().god_id == core_god::opatos)
                {
                    inv[ci].param1 = 164;
                }
            }
            if (cdata.player().god_id == core_god::jure)
            {
                flt();
                nostack = 1;
                itemcreate(
                    -1,
                    672,
                    cdata.player().position.x,
                    cdata.player().position.y,
                    0);
                inv[ci].param1 = 166;
            }
            txt(i18n::s.get(
                "core.locale.common.something_is_put_on_the_ground"));
        }
        if (game_data.god_rank == 5)
        {
            flt();
            dbid = 0;
            if (cdata.player().god_id == core_god::mani)
            {
                dbid = 674;
            }
            if (cdata.player().god_id == core_god::lulwy)
            {
                dbid = 673;
            }
            if (cdata.player().god_id == core_god::itzpalt)
            {
                dbid = 676;
            }
            if (cdata.player().god_id == core_god::ehekatl)
            {
                dbid = 678;
            }
            if (cdata.player().god_id == core_god::opatos)
            {
                dbid = 679;
            }
            if (cdata.player().god_id == core_god::jure)
            {
                dbid = 677;
            }
            if (cdata.player().god_id == core_god::kumiromi)
            {
                dbid = 675;
            }
            if (itemmemory(1, dbid))
            {
                dbid = 621;
            }
            itemcreate(
                -1,
                dbid,
                cdata.player().position.x,
                cdata.player().position.y,
                0);
            txt(i18n::s.get(
                "core.locale.common.something_is_put_on_the_ground"));
        }
        ++game_data.god_rank;
    }
    return TurnResult::turn_end;
}



} // namespace elona
