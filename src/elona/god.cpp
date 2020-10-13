#include "god.hpp"

#include <iostream>

#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/interface.hpp"
#include "magic.hpp"
#include "message.hpp"
#include "random.hpp"
#include "skill.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

data::InstanceId god_get_random_god_or_eyth()
{
    return data::InstanceId{lua::call_with_result(
        "core.God.get_random_god_or_eyth", std::string{})};
}



void txtgod(data::InstanceId id, int type)
{
    if (id == "")
    {
        return;
    }

    std::string message;
    switch (type)
    {
    case 12:
        message = i18n::s.get_data_text_optional("core.god", id, "random")
                      .value_or("");
        break;
    case 9:
        message =
            i18n::s.get_data_text_optional("core.god", id, "kill").value_or("");
        break;
    case 10:
        message = i18n::s.get_data_text_optional("core.god", id, "night")
                      .value_or("");
        break;
    case 11:
        message = i18n::s.get_data_text_optional("core.god", id, "welcome")
                      .value_or("");
        break;
    case 5:
        message = i18n::s.get_data_text_optional("core.god", id, "believe")
                      .value_or("");
        break;
    case 1:
        message = i18n::s.get_data_text_optional("core.god", id, "betray")
                      .value_or("");
        break;
    case 2:
        message = i18n::s.get_data_text_optional("core.god", id, "take_over")
                      .value_or("");
        break;
    case 3:
        message =
            i18n::s.get_data_text_optional("core.god", id, "fail_to_take_over")
                .value_or("");
        break;
    case 4:
        message = i18n::s.get_data_text_optional("core.god", id, "offer")
                      .value_or("");
        break;
    case 6:
        message = i18n::s.get_data_text_optional("core.god", id, "receive_gift")
                      .value_or("");
        break;
    case 7:
        message =
            i18n::s
                .get_data_text_optional("core.god", id, "ready_to_receive_gift")
                .value_or("");
        break;
    case 8:
        message = i18n::s
                      .get_data_text_optional(
                          "core.god", id, "ready_to_receive_gift2")
                      .value_or("");
        break;
    default: assert(0);
    }

    txt(message, Message::color{ColorIndex::orange});
}



void god_add_piety(Character& chara, lua_int amount)
{
    lua::call("core.God.add_piety", lua::handle(chara), amount);
}



void set_npc_religion(Character& chara)
{
    if (chara.religion != "" || chara.has_learned_words() || chara.is_player())
    {
        return;
    }
    randomize(game()->random_seed + game()->current_map);
    chara.religion = god_get_random_god_or_eyth();
    randomize();
    if (chara.religion == "" || rnd(4) == 0)
    {
        chara.has_learned_words() = true;
    }
}



void god_apply_blessing(Character& believer)
{
    lua::call("core.God.apply_blessing", lua::handle(believer));
}



void god_proc_switching_penalty(data::InstanceId new_religion)
{
    if (rtval == 0)
    {
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh - inf_verh, 0, 0);
        gmode(2);
        render_hud();
        redraw();
        if (cdata.player().religion != "")
        {
            mode = 9;
            txt(i18n::s.get(
                    "core.god.enraged", god_get_name(cdata.player().religion)),
                Message::color{ColorIndex::purple});
            txtgod(cdata.player().religion, 1);
            redraw();
            efid = 622;
            efp = 10000;
            magic(cdata.player(), cdata.player());
            snd("core.punish1");
            mode = 0;
            await(g_config.animation_wait() * 20);
        }
        lua::call(
            "core.God.switch_religion",
            lua::handle(cdata.player()),
            new_religion);
        msg_halt();
    }
    chara_refresh(cdata.player());
}



TurnResult do_pray()
{
    if (cdata.player().religion == "")
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
        "core.god.pray.you_pray_to", god_get_name(cdata.player().religion)));
    if (cdata.player().piety_point < 200 || cdata.player().prayer_point < 1000)
    {
        txt(i18n::s.get(
            "core.god.pray.indifferent",
            god_get_name(cdata.player().religion)));
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
    cdata.player().prayer_point = 0;
    cdata.player().piety_point = cdata.player().piety_point * 85 / 100;
    if (cdata.player().piety_rank % 2 == 1)
    {
        txtgod(cdata.player().religion, 6);
        if (cdata.player().piety_rank == 1)
        {
            f = 0;
            p = 0;
            for (const auto& ally : cdata.allies())
            {
                if (ally.state() != Character::State::empty)
                {
                    if (ally.race == "core.servant")
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
                    ++cdata.player().piety_rank;
                }
                return TurnResult::turn_end;
            }
            flt();
            int chara_id = 0;
            if (cdata.player().religion == "core.mani")
            {
                chara_id = 262;
                txt(i18n::s.get("core.god.pray.servant.desc.mani"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().religion == "core.lulwy")
            {
                chara_id = 263;
                txt(i18n::s.get("core.god.pray.servant.desc.lulwy"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().religion == "core.itzpalt")
            {
                chara_id = 264;
                txt(i18n::s.get("core.god.pray.servant.desc.itzpalt"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().religion == "core.ehekatl")
            {
                chara_id = 260;
                txt(i18n::s.get("core.god.pray.servant.desc.ehekatl"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().religion == "core.opatos")
            {
                chara_id = 265;
                txt(i18n::s.get("core.god.pray.servant.desc.opatos"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().religion == "core.jure")
            {
                chara_id = 266;
                txt(i18n::s.get("core.god.pray.servant.desc.jure"),
                    Message::color{ColorIndex::blue});
            }
            if (cdata.player().religion == "core.kumiromi")
            {
                chara_id = 261;
                txt(i18n::s.get("core.god.pray.servant.desc.kumiromi"),
                    Message::color{ColorIndex::blue});
            }
            novoidlv = 1;
            chara_create(56, chara_id, -3, 0);
            new_ally_joins(cdata.tmp());
        }
        if (cdata.player().piety_rank == 3)
        {
            flt();
            int item_id = 0;
            if (cdata.player().religion == "core.lulwy")
            {
                item_id = 680;
            }
            if (cdata.player().religion == "core.jure")
            {
                item_id = 681;
            }
            if (cdata.player().religion == "core.kumiromi")
            {
                item_id = 682;
            }
            if (cdata.player().religion == "core.mani")
            {
                item_id = 683;
            }
            if (item_id != 0)
            {
                if (game()->item_memories.generate_count(
                        *the_item_db.get_id_from_integer(item_id)) != 0)
                {
                    item_id = 559;
                }
                itemcreate_map_inv(item_id, cdata.player().position, 0);
            }
            else
            {
                nostack = 1;
                if (const auto item =
                        itemcreate_map_inv(672, cdata.player().position, 0))
                {
                    if (cdata.player().religion == "core.itzpalt")
                    {
                        item->param1 = 165;
                    }
                    if (cdata.player().religion == "core.ehekatl")
                    {
                        item->param1 = 163;
                    }
                    if (cdata.player().religion == "core.opatos")
                    {
                        item->param1 = 164;
                    }
                }
            }
            if (cdata.player().religion == "core.jure")
            {
                flt();
                nostack = 1;
                if (const auto item =
                        itemcreate_map_inv(672, cdata.player().position, 0))
                {
                    item->param1 = 166;
                }
            }
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        if (cdata.player().piety_rank == 5)
        {
            flt();
            int item_id = 0;
            if (cdata.player().religion == "core.mani")
            {
                item_id = 674;
            }
            if (cdata.player().religion == "core.lulwy")
            {
                item_id = 673;
            }
            if (cdata.player().religion == "core.itzpalt")
            {
                item_id = 676;
            }
            if (cdata.player().religion == "core.ehekatl")
            {
                item_id = 678;
            }
            if (cdata.player().religion == "core.opatos")
            {
                item_id = 679;
            }
            if (cdata.player().religion == "core.jure")
            {
                item_id = 677;
            }
            if (cdata.player().religion == "core.kumiromi")
            {
                item_id = 675;
            }
            if (game()->item_memories.generate_count(
                    *the_item_db.get_id_from_integer(item_id)) != 0)
            {
                item_id = 621;
            }
            itemcreate_map_inv(item_id, cdata.player().position, 0);
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        ++cdata.player().piety_rank;
    }
    return TurnResult::turn_end;
}



std::string god_get_name(data::InstanceId id)
{
    return lua::call_with_result("core.God.get_name", id.get(), ""s);
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



bool god_is_offerable(const ItemRef& offering, Character& believer)
{
    return lua::call_with_result(
        "core.God.is_offerable", false, offering, lua::handle(believer));
}

} // namespace elona
