#include "random_event.hpp"

#include <cassert>

#include "ability.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "message.hpp"
#include "net.hpp"
#include "optional.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace
{



struct RandomEvent
{
    int id;
    int luck_threshold;


    bool is_evadable(int luck) const
    {
        return luck_threshold != 0 && rnd_capped(luck + 1) > luck_threshold;
    }
};



std::vector<int> fsetremain{
    25000,
    57000,
    57000,
    77000,
    53000,
    52000,
    57000,
};



optional<RandomEvent> generate_random_event_in_sleep()
{
    int id = 0;
    int luck_threshold = 0;

    if (cdata.player().god_id != core_god::eyth)
    {
        if (rnd(12) == 0)
        {
            id = 18;
        }
    }
    if (rnd(80) == 0)
    {
        id = 4;
        luck_threshold = 120;
    }
    if (rnd(20) == 0)
    {
        id = 3;
    }
    if (rnd(25) == 0)
    {
        id = 2;
    }
    if (rnd(100) == 0)
    {
        id = 5;
        luck_threshold = 65;
    }
    if (rnd(20) == 0)
    {
        id = 6;
    }
    if (rnd(20) == 0)
    {
        id = 7;
    }
    if (rnd(250) == 0)
    {
        if (inv_getfreeid(0) != -1)
        {
            id = 19;
        }
    }
    if (rnd(10000) == 0)
    {
        if (inv_getfreeid(0) != -1)
        {
            id = 21;
        }
    }
    if (rnd(70) == 0)
    {
        id = 8;
        luck_threshold = 40;
    }
    if (rnd(200) == 0)
    {
        id = 20;
    }
    if (rnd(50) == 0)
    {
        id = 23;
    }
    if (rnd(300) == 0)
    {
        id = 24;
    }
    if (rnd(90) == 0)
    {
        id = 22;
        luck_threshold = 70;
    }

    if (id == 0)
    {
        return none;
    }
    else
    {
        return RandomEvent{id, luck_threshold};
    }
}



optional<RandomEvent> generate_random_event()
{
    int id = 0;
    int luck_threshold = 0;

    if (gspd < 10)
    {
        return none;
    }
    if (dbg_skipevent)
    {
        return none;
    }
    if (mode == 12)
    {
        return none;
    }
    if (mode == 9)
    {
        return generate_random_event_in_sleep();
    }
    if (map_data.type != mdata_t::MapType::world_map)
    {
        if (cdata.player().activity)
        {
            return none;
        }
    }
    if (map_data.type == mdata_t::MapType::player_owned)
    {
        return none;
    }
    if (rnd(30) == 0)
    {
        id = 17;
    }
    if (rnd(25) == 0)
    {
        id = 16;
    }
    if (rnd(25) == 0)
    {
        id = 12;
    }
    if (rnd(50) == 0)
    {
        id = 9;
    }
    if (rnd(80) == 0)
    {
        id = 14;
    }
    if (rnd(50) == 0)
    {
        id = 8;
        luck_threshold = 40;
    }
    if (rnd(80) == 0)
    {
        id = 13;
        luck_threshold = 45;
    }
    if (map_data.type == mdata_t::MapType::town)
    {
        if (rnd(25) == 0)
        {
            id = 15;
            luck_threshold = 80;
        }
    }
    else if (map_data.type == mdata_t::MapType::world_map)
    {
        if (rnd(40))
        {
            return none;
        }
    }
    else
    {
        if (rnd(25) == 0)
        {
            id = 10;
        }
        if (rnd(25) == 0)
        {
            id = 11;
        }
    }

    if (id == 0)
    {
        return none;
    }
    else
    {
        return RandomEvent{id, luck_threshold};
    }
}



void run_random_event(RandomEvent event)
{
    assert(event.id != 0);

    cc = 0;
    tc = 0;
    listmax = 0;

    if (event.is_evadable(sdata(19, 0)))
    {
        // Default to "Avoiding Misfortune" if Luck is good enough.
        event.id = 1;
    }

    data::InstanceId event_bg;

    switch (event.id)
    {
    case 15:
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            p = rnd(game_data.crowd_density + 1) + 57;
            if (p >= ELONA_MAX_CHARACTERS)
            {
                --cnt;
                continue;
            }
            if (cdata[p].state() == Character::State::alive)
            {
                txt(i18n::s.get_enum_property(
                    "core.event.popup", "scream", 15, cdata[p]));
                damage_hp(cdata[p], 99999, -11);
                break;
            }
        }
        listmax = 1;
        event_bg = u8"bg_re9";
        break;
    case 14:
        listmax = 2;
        event_bg = u8"bg_re10";
        break;
    case 13:
        cdata.player().nutrition -= 5000;
        listmax = 1;
        event_bg = u8"bg_re10";
        break;
    case 1:
        listmax = 1;
        event_bg = u8"bg_re8";
        break;
    case 24:
        efid = 1113;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 18:
        chara_gain_skill_exp(cdata.player(), 181, 1000, 6, 1000);
        listmax = 1;
        event_bg = u8"bg_re12";
        break;
    case 12:
        efid = 1117;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re3";
        break;
    case 23:
        efid = 1117;
        efp = 200;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re3";
        break;
    case 10:
        listmax = 2;
        event_bg = u8"bg_re3";
        break;
    case 4:
        snd("core.curse2");
        efid = 1118;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re5";
        break;
    case 22:
        snd("core.curse2");
        efid = 454;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re2";
        break;
    case 19:
        flt();
        if (const auto item = itemcreate_player_inv(621, 0))
        {
            txt(i18n::s.get("core.common.you_put_in_your_backpack", *item));
        }
        listmax = 1;
        event_bg = u8"bg_re15";
        break;
    case 20:
        buff_add(cdata[tc], "elona.luck", 777, 1500);
        listmax = 1;
        event_bg = u8"bg_re12";
        break;
    case 21:
        flt();
        if (const auto item = itemcreate_player_inv(721, 0))
        {
            txt(i18n::s.get("core.common.you_put_in_your_backpack", *item));
        }
        listmax = 1;
        event_bg = u8"bg_re15";
        net_send_news("ehekatl");
        break;
    case 5:
        if (trait(42))
        {
            txt(i18n::s.get_enum_property("core.event.popup", "no_effect", 5));
        }
        else
        {
            f = 0;
            tc = 0;
            for (int i = 0; i < 30; ++i)
            {
                if (cdata[tc].body_parts[i] % 10000 == 0)
                {
                    continue;
                }
                else
                {
                    f = 1;
                }
            }
            if (f)
            {
                efid = 1114;
                efp = 200;
                magic();
            }
            else if (!event_has_pending_events())
            {
                event_add(26);
            }
        }
        listmax = 1;
        event_bg = u8"bg_re5";
        break;
    case 8:
        p = rnd_capped(cdata.player().gold / 8 + 1);
        if (cdata.player().is_protected_from_thieves())
        {
            p = 0;
        }
        if (p > 0)
        {
            txt(i18n::s.get_enum_property(
                "core.event.popup", "you_lose", 8, p(0)));
            cdata.player().gold -= p;
        }
        else
        {
            txt(i18n::s.get_enum_property("core.event.popup", "no_effect", 8));
        }
        listmax = 1;
        event_bg = u8"bg_re9";
        break;
    case 11:
        listmax = 2;
        event_bg = u8"bg_re7";
        break;
    case 2:
        efid = 1104;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re6";
        break;
    case 3:
        efid = 1119;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 6:
        chara_gain_skill_exp(cdata.player(), 154, 1000);
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 7:
        chara_gain_skill_exp(cdata.player(), 155, 1000);
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 9:
        earn_platinum(cdata.player(), 1);
        listmax = 1;
        event_bg = u8"bg_re1";
        break;
    case 16:
        p = rnd_capped(cdata.player().gold / 10 + 1000) + 1;
        earn_gold(cdata.player(), p);
        txt(i18n::s.get_enum_property(
            "core.event.popup", "you_pick_up", 16, p(0)));
        listmax = 1;
        event_bg = u8"bg_re1";
        break;
    case 17:
        efid = 451;
        efp = 800;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re11";
        break;
    }

    std::vector<std::string> choices;
    for (int i = 0; i < listmax; ++i)
    {
        choices.push_back(i18n::s.get_enum_property(
            "core.event.popup", "choices._" + std::to_string(i), event.id));
    }
    int result = show_random_event_window(
        i18n::s.get_enum_property("core.event.popup", "title", event.id),
        i18n::s.get_enum_property("core.event.popup", "text", event.id),
        choices,
        event_bg);

    switch (event.id)
    {
    case 14:
        if (result == 0)
        {
            cdata.player().nutrition = 15000;
            txt(i18n::s.get("core.talk.npc.innkeeper.eat.results"));
            show_eating_message();
            chara_anorexia(cdata.player());
        }
        break;
    case 10:
        if (result == 0)
        {
            for (int cnt = 0, cnt_end = (1 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = choice(fsetremain);
                itemcreate_extra_inv(0, cdata.player().position, 0);
            }
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        break;
    case 11:
        if (result == 0)
        {
            txt(i18n::s.get_enum_property("core.event.popup", "loot", 11));
            modify_karma(cdata.player(), -2);
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(0, calcfixlv(Quality::good));
                if (rnd(3) == 0)
                {
                    flttypemajor = fsetwear(rnd(fsetwear.size()));
                }
                else
                {
                    flttypemajor = choice(fsetremain);
                }
                itemcreate_extra_inv(0, cdata.player().position, 0);
            }
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        else
        {
            txt(i18n::s.get_enum_property("core.event.popup", "bury", 11));
            modify_karma(cdata.player(), 5);
        }
    }

    cc = 0;
    load_activity_animation();
}



} // namespace



namespace elona
{



void proc_random_event()
{
    if (auto e = generate_random_event())
    {
        run_random_event(*e);
    }
}



int show_random_event_window(
    const std::string& title,
    const std::string& text,
    const std::vector<std::string> choices,
    data::InstanceId background_image_id)
{
    assert(!choices.empty());

    if (g_config.skip_random_event_popups() && choices.size() == 1)
    {
        // Skip this event.
        snd("core.pop4");
        txt(text);
        txt(i18n::s.get("core.event.popup.skip", choices[0]));
        return -1;
    }


    buff = text;
    listmax = 0;
    for (const auto& choice : choices)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = choice;
        ++listmax;
    }


    input_halt_input(HaltInput::force);
    cs = 0;
    page = 0;
    pagemax = 0;
    pagesize = 16;
    cs_bk = -1;
    if (listmax <= 1)
    {
        chatesc = 0;
    }
    else
    {
        chatesc = -1;
    }
    gmode(0);
    asset_load(background_image_id);
    tx = ginfo(12);
    ty = ginfo(13);
    gsel(0);
    snd("core.pop4");
    dx = tx + 36;
    talk_conv(buff, (dx - 80) / (7 - en) - en * 4);
    notesel(buff);
    dy = ty + noteinfo() * 15 + 80 + listmax * 20;

    while (1)
    {
        gmode(2);
        window(
            (windoww - dx) / 2 + inf_screenx + 4,
            winposy(dy) - 12,
            dx,
            dy,
            true);
        window((windoww - dx) / 2 + inf_screenx, winposy(dy) - 16, dx, dy);
        wx = (windoww - dx) / 2 + inf_screenx;
        wy = winposy(dy);
        gmode(0);
        gcopy(7, 0, 0, tx, ty, wx + 12, wy + 6);
        gmode(2);
        boxl(wx + 12, wy + 6, tx, ty, {240, 230, 220});
        font(14 - en * 2);
        bmes(
            i18n::s.get("core.event.popup.title", title),
            wx + 40,
            wy + vfix + 16,
            {245, 235, 225},
            {30, 20, 10});
        mes(wx + 24, wy + ty + vfix + 20, buff, {30, 30, 30});
        keyrange = 0;
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            key_list(cnt) = key_select(cnt);
            ++keyrange;
        }
        font(14 - en * 2);
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            i = list(0, p);
            display_key(wx + 30, wy + dy + cnt * 20 - listmax * 20 - 52, cnt);
            q = listn(0, p);
            cs_list(
                cs == cnt, q, wx + 60, wy + dy + cnt * 20 - listmax * 20 - 52);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        auto action = get_selected_item(rtval);
        if (chatesc != -1)
        {
            if (action == "cancel")
            {
                snd("core.click1");
                rtval = chatesc;
            }
        }
        if (rtval != -1)
        {
            snd("core.click1");
            return rtval;
        }
    }
}



} // namespace elona
