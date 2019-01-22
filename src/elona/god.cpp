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
#include "lua_env/lua_api/lua_api_item.hpp"
#include "macro.hpp"
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
        message =
            i18n::s.get_m_optional("locale.god", id, "random").get_value_or("");
        break;
    case 9:
        message =
            i18n::s.get_m_optional("locale.god", id, "kill").get_value_or("");
        break;
    case 10:
        message =
            i18n::s.get_m_optional("locale.god", id, "night").get_value_or("");
        break;
    case 11:
        message = i18n::s.get_m_optional("locale.god", id, "welcome")
                      .get_value_or("");
        break;
    case 5:
        message = i18n::s.get_m_optional("locale.god", id, "believe")
                      .get_value_or("");
        break;
    case 1:
        message =
            i18n::s.get_m_optional("locale.god", id, "betray").get_value_or("");
        break;
    case 2:
        message = i18n::s.get_m_optional("locale.god", id, "take_over")
                      .get_value_or("");
        break;
    case 3:
        message = i18n::s.get_m_optional("locale.god", id, "fail_to_take_over")
                      .get_value_or("");
        break;
    case 4:
        message =
            i18n::s.get_m_optional("locale.god", id, "offer").get_value_or("");
        break;
    case 6:
        message = i18n::s.get_m_optional("locale.god", id, "receive_gift")
                      .get_value_or("");
        break;
    case 7:
        message =
            i18n::s.get_m_optional("locale.god", id, "ready_to_receive_gift")
                .get_value_or("");
        break;
    case 8:
        message =
            i18n::s.get_m_optional("locale.god", id, "ready_to_receive_gift2")
                .get_value_or("");
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
        txt(i18n::s.get("core.locale.god.indifferent"));
        return;
    }

    // Modify the piety.
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        amount /= 10;
    }
    cdata.player().piety_point += amount;
}



void set_npc_religion()
{
    if (cdata[tc].god_id != core_god::eyth || cdata[tc].has_learned_words() ||
        tc == 0)
    {
        return;
    }
    randomize(game_data.random_seed + game_data.current_map);
    cdata[tc].god_id = core_god::int2godid(rnd(8));
    randomize();
    if (cdata[tc].god_id == core_god::eyth || rnd(4) == 0)
    {
        cdata[tc].has_learned_words() = true;
    }
}



void apply_god_blessing(int cc)
{
    auto god_data = the_god_db[cdata[cc].god_id];
    if (!god_data)
    {
        return;
    }

    auto piety_point = cdata[cc].piety_point;
    auto faith_level = sdata(181, 0);

    for (const auto& pair : god_data->skills)
    {
        int skill_id = pair.first;
        lua::WrappedFunction func = pair.second;

        if (sdata(skill_id, cc) > 0)
        {
            sdata(skill_id, cc) +=
                func.call_with_result(0, piety_point, faith_level);
        }
    }
}



void god_proc_switching_penalty()
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
                    "core.locale.god.enraged", god_name(cdata.player().god_id)),
                Message::color{ColorIndex::purple});
            txtgod(cdata.player().god_id, 1);
            redraw();
            efid = 622;
            efp = 10000;
            tc = 0;
            magic();
            snd("core.punish1");
            mode = 0;
            await(Config::instance().animation_wait * 20);
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
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.locale.god.switch.unbeliever"),
            Message::color{ColorIndex::orange});
    }
    else
    {
        animode = 100;
        MiracleAnimation().play();
        snd("core.complete1");
        txt(i18n::s.get(
                "core.locale.god.switch.follower",
                god_name(cdata.player().god_id)),
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


static void _create_faith_reward_servant()
{
    bool no_more_servants = false;
    int servant_count = 0;

    for (int cnt = 1; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::empty)
        {
            if (cdatan(2, cnt) == u8"core.servant"s)
            {
                ++servant_count;
                if (servant_count >= 2)
                {
                    no_more_servants = true;
                    txt(i18n::s.get("core.locale.god.pray.servant.no_more"));
                    break;
                }
            }
        }
    }
    if (!no_more_servants)
    {
        if (chara_get_free_slot_ally() == 0)
        {
            no_more_servants = true;
            txt(i18n::s.get("core.locale.god.pray.servant.party_is_full"));
        }
    }
    if (no_more_servants)
    {
        txt(i18n::s.get("core.locale.god.pray.servant.prompt_decline"));
        rtval = yes_no(promptx, prompty, 160);
        if (rtval == 0)
        {
            ++game_data.god_rank;
        }
        return TurnResult::turn_end;
    }

    auto god_data = the_god_db[cdata[cc].god_id];
    assert(god_data);

    auto chara = the_chara_db[god_data->servant];
    if (!chara)
    {
        txt("Cannot find character ID '"s + god_data->servant.get() + "'."s,
            Message::color(ColorIndex::red));
        return;
    }

    txt(i18n::s.get("core.locale.god.pray.servant.desc"),
        Message::color{ColorIndex::blue});

    flt();
    dbid = chara->id;

    novoidlv = 1;
    chara_create(56, dbid, -3, 0);
    rc = 56;
    new_ally_joins();
}

static void _create_faith_reward_gemstone()
{
    auto god_data = the_god_db[cdata[cc].god_id];
    assert(god_data);

    for (int i = 0; i < god_data->items.size(); i++)
    {
        sol::object item_proto_obj = god_data->items[i];
        if (sol::object != sol::lua_nil && item_proto.is<sol::table>)
        {
            lua::ConfigTable item_proto = item_proto_obj.as<lua::ConfigTable>();

            auto only_once = item_proto.optional_or<bool>("_only_once", false);

            if (only_once)
            {
                auto id = item_proto.optional<std::string>("id");
                auto item = the_item_db[*id];
                if (item)
                {
                    if (only_once && itemmemory(1, item->id))
                    {
                        continue;
                    }
                }
                else
                {
                    txt("Cannot find item ID '"s + *id + "'."s,
                        Message::color(ColorIndex::red));
                }
            }

            lua::LuaApiItem::create(
                cdata.player().position, item_proto.storage);
        }
    }

    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
}

static void _create_faith_reward_artifact()
{
    auto god_data = the_god_db[cdata[cc].god_id];
    assert(god_data);

    auto item = the_item_db[god_data->artifact];
    if (!item)
    {
        txt("Cannot find item ID '"s + god_data->artifact.get() + "'."s,
            Message::color(ColorIndex::red));
        return;
    }

    flt();
    dbid = item->id;
    if (itemmemory(1, dbid))
    {
        dbid = 621;
    }

    itemcreate(
        -1, dbid, cdata.player().position.x, cdata.player().position.y, 0);

    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
}

TurnResult do_pray()
{
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.locale.god.pray.do_not_believe"));
        return TurnResult::turn_end;
    }
    Message::instance().linebreak();
    txt(i18n::s.get("core.locale.god.pray.prompt"));
    if (!yes_no())
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    txt(i18n::s.get(
        "core.locale.god.pray.you_pray_to", god_name(cdata.player().god_id)));
    if (cdata.player().piety_point < 200 || cdata.player().praying_point < 1000)
    {
        txt(i18n::s.get(
            "core.locale.god.pray.indifferent",
            god_name(cdata.player().god_id)));
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
            _create_faith_reward_servant();
        }
        if (game_data.god_rank == 3)
        {
            _create_faith_reward_gemstone();
        }
        if (game_data.god_rank == 5)
        {
            _create_faith_reward_artifact();
        }
        ++game_data.god_rank;
    }
    return TurnResult::turn_end;
}



std::string god_name(const GodId& id)
{
    if (id == core_god::eyth)
    {
        return i18n::s.get_m("locale.god", "core.eyth", "name");
    }
    else
    {
        return i18n::s.get_m("locale.god", id, "name");
    }
}



std::string god_name(int legacy_god_id)
{
    return god_name(core_god::int2godid(legacy_god_id));
}



bool god_is_offerable(const Item& item)
{
    auto god_data = the_god_db[cdata.player().god_id];
    if (!god_data)
    {
        return false;
    }

    auto id = the_item_db.get_id_from_legacy(item.id);
    if (!id)
    {
        return false;
    }

    return god_data->offerings.find(id) != god_data->offerings.end();
}

} // namespace elona
