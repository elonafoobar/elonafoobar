#include "god.hpp"

#include <iostream>

#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "magic.hpp"
#include "message.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

void txtgod(const GodId& id, int type)
{
    if (id == core_god::eyth)
    {
        return;
    }

    std::string message;
    switch (type)
    {
    case 12:
        message = i18n::s.get_m_optional("god", id, "random").value_or("");
        break;
    case 9:
        message = i18n::s.get_m_optional("god", id, "kill").value_or("");
        break;
    case 10:
        message = i18n::s.get_m_optional("god", id, "night").value_or("");
        break;
    case 11:
        message = i18n::s.get_m_optional("god", id, "welcome").value_or("");
        break;
    case 5:
        message = i18n::s.get_m_optional("god", id, "believe").value_or("");
        break;
    case 1:
        message = i18n::s.get_m_optional("god", id, "betray").value_or("");
        break;
    case 2:
        message = i18n::s.get_m_optional("god", id, "take_over").value_or("");
        break;
    case 3:
        message =
            i18n::s.get_m_optional("god", id, "fail_to_take_over").value_or("");
        break;
    case 4:
        message = i18n::s.get_m_optional("god", id, "offer").value_or("");
        break;
    case 6:
        message =
            i18n::s.get_m_optional("god", id, "receive_gift").value_or("");
        break;
    case 7:
        message = i18n::s.get_m_optional("god", id, "ready_to_receive_gift")
                      .value_or("");
        break;
    case 8:
        message = i18n::s.get_m_optional("god", id, "ready_to_receive_gift2")
                      .value_or("");
        break;
    default: assert(0);
    }

    txt(message, Message::color{ColorIndex::orange});
}



void god_modify_piety(int amount)
{
    // Check the degree of the piety.
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

    // Faith skill is not enough.
    if (sdata(181, 0) * 100 < cdata.player().piety_point)
    {
        txt(i18n::s.get("core.god.indifferent"));
        return;
    }

    // Modify the piety.
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        amount /= 10;
    }
    cdata.player().piety_point += amount;
}



void set_npc_religion(Character& chara)
{
    if (chara.god_id != core_god::eyth || chara.has_learned_words() ||
        chara.index == 0)
    {
        return;
    }
    randomize(game_data.random_seed + game_data.current_map);
    chara.god_id = core_god::int2godid(rnd(8));
    randomize();
    if (chara.god_id == core_god::eyth || rnd(4) == 0)
    {
        chara.has_learned_words() = true;
    }
}



void god_apply_blessing(Character& believer)
{
    const auto P = believer.piety_point;
    const auto F = sdata(181, believer.index);

    if (believer.god_id == core_god::mani)
    {
        if (sdata(12, believer.index) > 0)
        {
            sdata(12, believer.index) += clamp(P / 400, 1, 8 + F / 10);
        }
        if (sdata(13, believer.index) > 0)
        {
            sdata(13, believer.index) += clamp(P / 300, 1, 14 + F / 10);
        }
        if (sdata(154, believer.index) > 0)
        {
            sdata(154, believer.index) += clamp(P / 500, 1, 8 + F / 10);
        }
        if (sdata(110, believer.index) > 0)
        {
            sdata(110, believer.index) += clamp(P / 250, 1, 18 + F / 10);
        }
        if (sdata(159, believer.index) > 0)
        {
            sdata(159, believer.index) += clamp(P / 350, 1, 8 + F / 10);
        }
        if (sdata(158, believer.index) > 0)
        {
            sdata(158, believer.index) += clamp(P / 250, 1, 16 + F / 10);
        }
        if (sdata(176, believer.index) > 0)
        {
            sdata(176, believer.index) += clamp(P / 300, 1, 10 + F / 10);
        }
        if (sdata(179, believer.index) > 0)
        {
            sdata(179, believer.index) += clamp(P / 350, 1, 12 + F / 10);
        }
    }
    if (believer.god_id == core_god::lulwy)
    {
        if (sdata(13, believer.index) > 0)
        {
            sdata(13, believer.index) += clamp(P / 450, 1, 10 + F / 10);
        }
        if (sdata(18, believer.index) > 0)
        {
            sdata(18, believer.index) += clamp(P / 350, 1, 30 + F / 10);
        }
        if (sdata(108, believer.index) > 0)
        {
            sdata(108, believer.index) += clamp(P / 350, 1, 16 + F / 10);
        }
        if (sdata(109, believer.index) > 0)
        {
            sdata(109, believer.index) += clamp(P / 450, 1, 12 + F / 10);
        }
        if (sdata(157, believer.index) > 0)
        {
            sdata(157, believer.index) += clamp(P / 450, 1, 12 + F / 10);
        }
        if (sdata(174, believer.index) > 0)
        {
            sdata(174, believer.index) += clamp(P / 550, 1, 8 + F / 10);
        }
    }
    if (believer.god_id == core_god::itzpalt)
    {
        if (sdata(16, believer.index) > 0)
        {
            sdata(16, believer.index) += clamp(P / 300, 1, 18 + F / 10);
        }
        if (sdata(155, believer.index) > 0)
        {
            sdata(155, believer.index) += clamp(P / 350, 1, 15 + F / 10);
        }
        if (sdata(50, believer.index) > 0)
        {
            sdata(50, believer.index) += clamp(P / 50, 1, 200 + F / 10);
        }
        if (sdata(51, believer.index) > 0)
        {
            sdata(51, believer.index) += clamp(P / 50, 1, 200 + F / 10);
        }
        if (sdata(52, believer.index) > 0)
        {
            sdata(52, believer.index) += clamp(P / 50, 1, 200 + F / 10);
        }
    }
    if (believer.god_id == core_god::ehekatl)
    {
        if (sdata(17, believer.index) > 0)
        {
            sdata(17, believer.index) += clamp(P / 250, 1, 20 + F / 10);
        }
        if (sdata(19, believer.index) > 0)
        {
            sdata(19, believer.index) += clamp(P / 100, 1, 50 + F / 10);
        }
        if (sdata(173, believer.index) > 0)
        {
            sdata(173, believer.index) += clamp(P / 300, 1, 15 + F / 10);
        }
        if (sdata(164, believer.index) > 0)
        {
            sdata(164, believer.index) += clamp(P / 350, 1, 17 + F / 10);
        }
        if (sdata(185, believer.index) > 0)
        {
            sdata(185, believer.index) += clamp(P / 300, 1, 12 + F / 10);
        }
        if (sdata(158, believer.index) > 0)
        {
            sdata(158, believer.index) += clamp(P / 450, 1, 8 + F / 10);
        }
    }
    if (believer.god_id == core_god::opatos)
    {
        if (sdata(10, believer.index) > 0)
        {
            sdata(10, believer.index) += clamp(P / 450, 1, 11 + F / 10);
        }
        if (sdata(11, believer.index) > 0)
        {
            sdata(11, believer.index) += clamp(P / 350, 1, 16 + F / 10);
        }
        if (sdata(168, believer.index) > 0)
        {
            sdata(168, believer.index) += clamp(P / 350, 1, 15 + F / 10);
        }
        if (sdata(153, believer.index) > 0)
        {
            sdata(153, believer.index) += clamp(P / 300, 1, 16 + F / 10);
        }
        if (sdata(163, believer.index) > 0)
        {
            sdata(163, believer.index) += clamp(P / 350, 1, 12 + F / 10);
        }
        if (sdata(174, believer.index) > 0)
        {
            sdata(174, believer.index) += clamp(P / 450, 1, 8 + F / 10);
        }
    }
    if (believer.god_id == core_god::jure)
    {
        if (sdata(15, believer.index) > 0)
        {
            sdata(15, believer.index) += clamp(P / 300, 1, 16 + F / 10);
        }
        if (sdata(154, believer.index) > 0)
        {
            sdata(154, believer.index) += clamp(P / 250, 1, 18 + F / 10);
        }
        if (sdata(155, believer.index) > 0)
        {
            sdata(155, believer.index) += clamp(P / 400, 1, 10 + F / 10);
        }
        if (sdata(161, believer.index) > 0)
        {
            sdata(161, believer.index) += clamp(P / 400, 1, 9 + F / 10);
        }
        if (sdata(184, believer.index) > 0)
        {
            sdata(184, believer.index) += clamp(P / 450, 1, 8 + F / 10);
        }
        if (sdata(174, believer.index) > 0)
        {
            sdata(174, believer.index) += clamp(P / 400, 1, 10 + F / 10);
        }
        if (sdata(164, believer.index) > 0)
        {
            sdata(164, believer.index) += clamp(P / 400, 1, 12 + F / 10);
        }
    }
    if (believer.god_id == core_god::kumiromi)
    {
        if (sdata(13, believer.index) > 0)
        {
            sdata(13, believer.index) += clamp(P / 400, 1, 8 + F / 10);
        }
        if (sdata(12, believer.index) > 0)
        {
            sdata(12, believer.index) += clamp(P / 350, 1, 12 + F / 10);
        }
        if (sdata(14, believer.index) > 0)
        {
            sdata(14, believer.index) += clamp(P / 250, 1, 16 + F / 10);
        }
        if (sdata(180, believer.index) > 0)
        {
            sdata(180, believer.index) += clamp(P / 300, 1, 12 + F / 10);
        }
        if (sdata(178, believer.index) > 0)
        {
            sdata(178, believer.index) += clamp(P / 350, 1, 10 + F / 10);
        }
        if (sdata(177, believer.index) > 0)
        {
            sdata(177, believer.index) += clamp(P / 350, 1, 9 + F / 10);
        }
        if (sdata(150, believer.index) > 0)
        {
            sdata(150, believer.index) += clamp(P / 350, 1, 8 + F / 10);
        }
    }
}



void god_proc_switching_penalty(const GodId& new_religion)
{
    if (rtval == 0)
    {
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh - inf_verh, 0, 0);
        gmode(2);
        render_hud();
        redraw();
        if (cdata.player().god_id != core_god::eyth)
        {
            mode = 9;
            txt(i18n::s.get(
                    "core.god.enraged", god_name(cdata.player().god_id)),
                Message::color{ColorIndex::purple});
            txtgod(cdata.player().god_id, 1);
            redraw();
            efid = 622;
            efp = 10000;
            magic(cdata.player(), cdata.player());
            snd("core.punish1");
            mode = 0;
            await(g_config.animation_wait() * 20);
        }
        cdata.player().god_id = new_religion;
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
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.god.switch.unbeliever"),
            Message::color{ColorIndex::orange});
    }
    else
    {
        MiracleAnimation(MiracleAnimation::Mode::target_one, cdata.player())
            .play();
        snd("core.complete1");
        txt(i18n::s.get(
                "core.god.switch.follower", god_name(cdata.player().god_id)),
            Message::color{ColorIndex::orange});
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
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.god.pray.do_not_believe"));
        return TurnResult::turn_end;
    }
    Message::instance().linebreak();
    txt(i18n::s.get("core.god.pray.prompt"));
    if (!yes_no())
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    txt(i18n::s.get(
        "core.god.pray.you_pray_to", god_name(cdata.player().god_id)));
    if (cdata.player().piety_point < 200 || cdata.player().praying_point < 1000)
    {
        txt(i18n::s.get(
            "core.god.pray.indifferent", god_name(cdata.player().god_id)));
        return TurnResult::turn_end;
    }
    MiracleAnimation(MiracleAnimation::Mode::target_one, cdata.player()).play();
    snd("core.pray2");
    efid = 1120;
    efp = 100;
    magic(cdata.player(), cdata.player());
    efid = 451;
    efp = 200;
    magic(cdata.player(), cdata.player());
    cdata.player().praying_point = 0;
    cdata.player().piety_point = cdata.player().piety_point * 85 / 100;
    if (game_data.god_rank % 2 == 1)
    {
        txtgod(cdata.player().god_id, 6);
        if (game_data.god_rank == 1)
        {
            f = 0;
            p = 0;
            for (const auto& ally : cdata.allies())
            {
                if (ally.state() != Character::State::empty)
                {
                    if (cdatan(2, ally.index) == u8"core.servant"s)
                    {
                        ++p;
                        if (p >= 2)
                        {
                            f = 1;
                            txt(i18n::s.get("core.god.pray.servant.no_more"));
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
                    txt(i18n::s.get("core.god.pray.servant.party_is_full"));
                }
            }
            if (f)
            {
                txt(i18n::s.get("core.god.pray.servant.prompt_decline"));
                if (yes_no())
                {
                    ++game_data.god_rank;
                }
                return TurnResult::turn_end;
            }
            flt();
            int chara_id = 0;
            if (cdata.player().god_id == core_god::mani)
            {
                chara_id = 262;
                txt(i18n::s.get("core.god.pray.servant.desc.mani"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().god_id == core_god::lulwy)
            {
                chara_id = 263;
                txt(i18n::s.get("core.god.pray.servant.desc.lulwy"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().god_id == core_god::itzpalt)
            {
                chara_id = 264;
                txt(i18n::s.get("core.god.pray.servant.desc.itzpalt"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().god_id == core_god::ehekatl)
            {
                chara_id = 260;
                txt(i18n::s.get("core.god.pray.servant.desc.ehekatl"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().god_id == core_god::opatos)
            {
                chara_id = 265;
                txt(i18n::s.get("core.god.pray.servant.desc.opatos"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().god_id == core_god::jure)
            {
                chara_id = 266;
                txt(i18n::s.get("core.god.pray.servant.desc.jure"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().god_id == core_god::kumiromi)
            {
                chara_id = 261;
                txt(i18n::s.get("core.god.pray.servant.desc.kumiromi"),
                    Message::color{ColorIndex::blue});
            }
            novoidlv = 1;
            chara_create(56, chara_id, -3, 0);
            new_ally_joins(cdata.tmp());
        }
        if (game_data.god_rank == 3)
        {
            flt();
            int item_id = 0;
            if (cdata.player().god_id == core_god::lulwy)
            {
                item_id = 680;
            }
            if (cdata.player().god_id == core_god::jure)
            {
                item_id = 681;
            }
            if (cdata.player().god_id == core_god::kumiromi)
            {
                item_id = 682;
            }
            if (cdata.player().god_id == core_god::mani)
            {
                item_id = 683;
            }
            if (item_id != 0)
            {
                if (itemmemory(1, item_id))
                {
                    item_id = 559;
                }
                itemcreate_extra_inv(item_id, cdata.player().position, 0);
            }
            else
            {
                nostack = 1;
                if (const auto item =
                        itemcreate_extra_inv(672, cdata.player().position, 0))
                {
                    if (cdata.player().god_id == core_god::itzpalt)
                    {
                        item->param1 = 165;
                    }
                    if (cdata.player().god_id == core_god::ehekatl)
                    {
                        item->param1 = 163;
                    }
                    if (cdata.player().god_id == core_god::opatos)
                    {
                        item->param1 = 164;
                    }
                }
            }
            if (cdata.player().god_id == core_god::jure)
            {
                flt();
                nostack = 1;
                if (const auto item =
                        itemcreate_extra_inv(672, cdata.player().position, 0))
                {
                    item->param1 = 166;
                }
            }
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        if (game_data.god_rank == 5)
        {
            flt();
            int item_id = 0;
            if (cdata.player().god_id == core_god::mani)
            {
                item_id = 674;
            }
            if (cdata.player().god_id == core_god::lulwy)
            {
                item_id = 673;
            }
            if (cdata.player().god_id == core_god::itzpalt)
            {
                item_id = 676;
            }
            if (cdata.player().god_id == core_god::ehekatl)
            {
                item_id = 678;
            }
            if (cdata.player().god_id == core_god::opatos)
            {
                item_id = 679;
            }
            if (cdata.player().god_id == core_god::jure)
            {
                item_id = 677;
            }
            if (cdata.player().god_id == core_god::kumiromi)
            {
                item_id = 675;
            }
            if (itemmemory(1, item_id))
            {
                item_id = 621;
            }
            itemcreate_extra_inv(item_id, cdata.player().position, 0);
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        ++game_data.god_rank;
    }
    return TurnResult::turn_end;
}



std::string god_name(const GodId& id)
{
    if (id == core_god::eyth)
    {
        return i18n::s.get_m("god", "core.eyth", "name");
    }
    else
    {
        return i18n::s.get_m("god", id, "name");
    }
}



std::string god_name(int legacy_god_id)
{
    return god_name(core_god::int2godid(legacy_god_id));
}



void god_fail_to_take_over_penalty()
{
    efid = 1114;
    efp = 500;
    magic(cdata.player(), cdata.player());
    if (rnd(2))
    {
        efid = 622;
        efp = 250;
        magic(cdata.player(), cdata.player());
        snd("core.punish1");
    }
    if (rnd(2))
    {
        efid = 1106;
        efp = 100;
        magic(cdata.player(), cdata.player());
    }
}

} // namespace elona
