#include "ui_menu_character_sheet.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_character_sheet::init()
{
    page = 0;
    pagesize = 16;
    listmax = 0;
    cs = 0;
    if (_csctrl != 4)
    {
        cc = 0;
    }
    csskill = -1;
    curmenu = 0;
    if (_csctrl == 2 || _csctrl == 3)
    {
        page = 1;
    }
    list(0, listmax) = -1;
    list(1, listmax) = 20000;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.chara_sheet.category.skill");
    ++listmax;
    if (_csctrl == 3)
    {
        trainer_get_gainable_skills();
    }
    else
    {
        for (int cnt = 150; cnt < 400; ++cnt)
        {
            f = 0;
            if (sdata(cnt, cc) != 0)
            {
                f = 1;
                if (_csctrl == 2)
                {
                    if (sdata.get(cnt, cc).original_level == 0)
                    {
                        f = 0;
                    }
                }
            }
            if (f)
            {
                list(0, listmax) = cnt;
                list(1, listmax) =
                    the_ability_db[cnt]->related_basic_attribute + 21000;
                ++listmax;
            }
        }
    }
    list(0, listmax) = -1;
    list(1, listmax) = 30000;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.chara_sheet.category.weapon_proficiency");
    ++listmax;
    for (int cnt = 100; cnt < 150; ++cnt)
    {
        f = 0;
        if (_csctrl != 3)
        {
            if (sdata(cnt, cc) != 0)
            {
                f = 1;
            }
        }
        else if (sdata(cnt, cc) == 0)
        {
            if (the_ability_db[cnt])
            {
                f = 1;
            }
        }
        if (f)
        {
            list(0, listmax) = cnt;
            list(1, listmax) =
                the_ability_db[cnt]->related_basic_attribute + 31000;
            ++listmax;
        }
    }
    if (_csctrl != 2 && _csctrl != 3)
    {
        list(0, listmax) = -1;
        list(1, listmax) = 40000;
        listn(0, listmax) =
            i18n::s.get("core.locale.ui.chara_sheet.category.resistance");
        ++listmax;
        for (int cnt = 50; cnt < 100; ++cnt)
        {
            if (sdata(cnt, cc) != 0)
            {
                list(0, listmax) = cnt;
                list(1, listmax) =
                    the_ability_db[cnt]->related_basic_attribute + 41000;
                ++listmax;
            }
        }
    }
    sort_list_by_column1();
    gsel(7);
    picload(filesystem::dir::graphic() / u8"ie_sheet.bmp");
    gsel(0);
    wx = (windoww - 700) / 2 + inf_screenx;
    wy = winposy(400) - 10;
    ww = 700;
    wh = 400;
    s = i18n::s.get("core.locale.ui.chara_sheet.title.default");
    if (_csctrl == 2)
    {
        s = i18n::s.get("core.locale.ui.chara_sheet.title.training");
    }
    if (_csctrl == 3)
    {
        s = i18n::s.get("core.locale.ui.chara_sheet.title.learning");
    }
    drawmenu(0);
    if (mode != 1)
    {
        snd(94);
    }
    window_animation(wx, wy, ww, wh, 9, 4);
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
    if (cdata[cc].portrait < 0) // TODO coupling
    {
        const auto filepath = filesystem::dir::user() / u8"graphic"
            / (u8"face"s + std::abs(cdata[cc].portrait + 1) + u8".bmp");
        if (cdata[cc].portrait != -1)
        {
            if (fs::exists(filepath))
            {
                pos(0, 0);
                picload(filepath, 1);
            }
        }
    }
    gsel(0);
    if (_returned_from_portrait == 0)
    {
        gmode(6, 80);
        pos(wx + 4, wy + 4);
        gcopy(7, 0, 0, 700, 400);
        gmode(2);
    }
    if (_csctrl == 2)
    {
        txtnew();
        txt(i18n::s.get("core.locale.ui.chara_sheet.train_which_skill"));
    }
    _returned_from_portrait = 0;
}

void ui_menu_character_sheet::update()
{
    if (_csctrl != 1)
    {
        display_msg(inf_tiles + inf_screeny);
    }
    pagemax = (listmax - 1) / pagesize + 1;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
    if (_csctrl == 1)
    {
        pagemax = 0;
    }
    cs_bk = -1;
    if (_csctrl == 0)
    {
        if (page == 0)
        {
            s = i18n::s.get("core.locale.ui.chara_sheet.hint.hint") + strhint6
                + strhint2 + strhint3;
        }
        else
        {
            s = i18n::s.get("core.locale.ui.chara_sheet.hint.spend_bonus")
                + strhint2 + strhint3;
        }
    }
    if (_csctrl == 1)
    {
        s = i18n::s.get("core.locale.ui.chara_sheet.hint.reroll") + strhint6
            + i18n::s.get("core.locale.ui.chara_sheet.hint.confirm");
    }
    if (_csctrl == 2)
    {
        if (page == 0)
        {
            s = strhint6 + strhint2 + strhint3;
        }
        else
        {
            s = i18n::s.get("core.locale.ui.chara_sheet.hint.train_skill")
                + strhint2 + strhint3;
        }
    }
    if (_csctrl == 3)
    {
        if (page == 0)
        {
            s = strhint6 + strhint2 + strhint3;
        }
        else
        {
            s = i18n::s.get("core.locale.ui.chara_sheet.hint.learn_skill")
                + strhint2 + strhint3;
        }
    }
    if (_csctrl == 4)
    {
        if (page == 0)
        {
            s = i18n::s.get("core.locale.ui.chara_sheet.hint.blessing_info")
                + strhint6 + strhint2 + strhint3;
        }
        else
        {
            s = strhint2 + strhint3;
        }
    }
    if (_csctrl != 1)
    {
        if (page != 0)
        {
            s += ""s + key_mode2 + u8" ["s
                + i18n::s.get("core.locale.ui.chara_sheet.hint.track_skill")
                + u8"]"s;
        }
    }
    color(0, 0, 0);
    show_title(s);
}

void ui_menu_character_sheet::draw()
{
    s = "";
    if (_csctrl == 0)
    {
        if (page != 0)
        {
            s = i18n::s.get(
                "core.locale.ui.chara_sheet.you_can_spend_bonus",
                cdata[cc].skill_bonus);
        }
    }
    display_window2(
        (windoww - 700) / 2 + inf_screenx, winposy(400) - 10, 700, 400, 7);
    if (page == 0)
    {
        keyrange = 0;
        key_list = key_enter;
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.attributes"),
            wx + 28,
            wy + 122);
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.combat_rolls"),
            wx + 400,
            wy + 253);
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.history"),
            wx + 28,
            wy + 273);
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.blessing_and_hex"),
            wx + 400,
            wy + 122);
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.extra_info"),
            wx + 220,
            wy + 273);
        if (cdata[cc].portrait >= 0)
        {
            p = cdata[cc].sex * 64 + cdata[cc].portrait;
            pos(wx + 560, wy + 27);
            gcopy(4, p % 16 * 48, p / 16 * 72, 48, 72, 80, 112);
        }
        else
        {
            const auto filepath = filesystem::dir::user() / u8"graphic"
                / (u8"face"s + std::abs(cdata[cc].portrait + 1) + u8".bmp");
            if (cdata[cc].portrait != -1)
            {
                if (fs::exists(filepath))
                {
                    pos(wx + 560, wy + 27);
                    gcopy(4, 0, 0, 80, 112, 80, 112);
                }
            }
        }
        window2(wx + 557, wy + 23, 87, 120, 1, 10);
        if (cdata[cc].has_own_sprite() == 1)
        {
            pos(wx + 596 + 22, wy + 86 + 24);
            gmode(2);
            gcopy_c(20 + cc, 32, 0, 32, 48, 24, 40);
        }
        else
        {
            draw_chara_scale_height(cdata[cc], wx + 596 + 22, wy + 86 + 24);
        }
        font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
        s(0) = i18n::s.get("core.locale.ui.chara_sheet.exp.level");
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.exp.exp");
        s(2) = i18n::s.get("core.locale.ui.chara_sheet.exp.next_level");
        s(3) = i18n::s.get("core.locale.ui.chara_sheet.exp.god");
        s(4) = i18n::s.get("core.locale.ui.chara_sheet.exp.guild");
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            pos(wx + 355, wy + 46 + cnt * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        s(0) = i18n::s.get("core.locale.ui.chara_sheet.personal.name");
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.personal.aka");
        s(2) = i18n::s.get("core.locale.ui.chara_sheet.personal.race");
        s(3) = i18n::s.get("core.locale.ui.chara_sheet.personal.sex");
        s(4) = i18n::s.get("core.locale.ui.chara_sheet.personal.class");
        s(5) = i18n::s.get("core.locale.ui.chara_sheet.personal.age");
        s(6) = i18n::s.get("core.locale.ui.chara_sheet.personal.height");
        s(7) = i18n::s.get("core.locale.ui.chara_sheet.personal.weight");
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            pos(wx + 30 + cnt / 4 * 190, wy + 61 + cnt % 4 * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            pos(wx + 37, wy + 157 + cnt * 15);
            gmode(2);
            gcopy_c(1, cnt * inf_tiles, 672, inf_tiles, inf_tiles);
            pos(wx + 54, wy + 151 + cnt * 15);
            color(20, 10, 0);
            mes(i18n::_(u8"ui", u8"attribute", u8"_"s + cnt));
            color(0, 0, 0);
        }
        s(0) = i18n::s.get("core.locale.ui.chara_sheet.attribute.life");
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.attribute.mana");
        s(2) = i18n::s.get("core.locale.ui.chara_sheet.attribute.sanity");
        s(3) = i18n::s.get("core.locale.ui.chara_sheet.attribute.speed");
        s(4) = "";
        s(5) = i18n::s.get("core.locale.ui.chara_sheet.attribute.fame");
        s(6) = i18n::s.get("core.locale.ui.chara_sheet.attribute.karma");
        s(7) = "";
        s(8) = i18n::s.get("core.locale.ui.chara_sheet.attribute.melee");
        s(9) = i18n::s.get("core.locale.ui.chara_sheet.attribute.shoot");
        s(10) = "";
        s(11) = "";
        s(12) = "";
        s(13) = "";
        s(14) = "";
        s(15) = "";
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            pos(wx + 255, wy + 151 + cnt * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        s(0) = i18n::s.get("core.locale.ui.chara_sheet.time.turns");
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.time.days");
        s(2) = i18n::s.get("core.locale.ui.chara_sheet.time.kills");
        s(3) = i18n::s.get("core.locale.ui.chara_sheet.time.time");
        s(4) = "";
        s(5) = "";
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            pos(wx + 32, wy + 301 + cnt * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        s(0) = i18n::s.get("core.locale.ui.chara_sheet.weight.cargo_weight");
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.weight.cargo_limit");
        s(2) = i18n::s.get("core.locale.ui.chara_sheet.weight.equip_weight");
        s(3) = i18n::s.get("core.locale.ui.chara_sheet.weight.deepest_level");
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            pos(wx + 224, wy + 301 + cnt * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        font(14 - en * 2);
        s(0) = ""s + cdata[cc].level;
        s(1) = ""s + cdata[cc].experience;
        s(2) = ""s + cdata[cc].required_experience;
        s(3) = i18n::_(u8"god", cdata[cc].god_id, u8"name");
        s(4) = guildname();
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            pos(wx + 410 + en * 5, wy + 45 + cnt * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        s(0) = cdatan(0, cc);
        s(1) = cdatan(1, cc);
        s(2) = cnven(lang(
            ""s + i18n::_(u8"race", cdatan(2, cc), u8"name"), cdatan(2, cc)));
        access_class_info(2, cdatan(3, cc));
        s(4) = cnven(lang(""s + classname, cdatan(3, cc)));
        if (cdata[cc].sex == 0)
        {
            s(3) = cnven(i18n::_(u8"ui", u8"male"));
        }
        else
        {
            s(3) = cnven(i18n::_(u8"ui", u8"female"));
        }
        s(5) = ""s + calcage(cc) + u8" "s
            + i18n::s.get("core.locale.ui.chara_sheet.personal.age_counter");
        s(6) = ""s + cdata[cc].height + u8" cm"s;
        s(7) = ""s + cdata[cc].weight + u8" kg"s;
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            pos(wx + 68 + cnt / 4 * 190 + en * ((cnt > 3) * 12),
                wy + 60 + cnt % 4 * 15);
            color(20, 10, 0);
            mes(s(cnt));
            color(0, 0, 0);
        }
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            s = u8"("s + sdata.get(10 + cnt, cc).original_level + u8")"s;
            if (encfind(cc, 60010 + cnt) != -1)
            {
                s += u8"*"s;
            }
            pos(wx + 92, wy + 151 + cnt * 15);
            color(20, 10, 0);
            mes(""s + sdata((10 + cnt), cc));
            color(0, 0, 0);
            pos(wx + 124, wy + 151 + cnt * 15);
            color(20, 10, 0);
            mes(s);
            color(0, 0, 0);
            p = sdata.get(10 + cnt, cc).potential;
            pos(wx + 176, wy + 152 + cnt * 15);
            if (p >= 200)
            {
                color(20, 10, 0);
                mes(u8"Superb"s);
                color(0, 0, 0);
                continue;
            }
            if (p >= 150)
            {
                color(20, 10, 0);
                mes(u8"Great"s);
                color(0, 0, 0);
                continue;
            }
            if (p >= 100)
            {
                color(20, 10, 0);
                mes(u8"Good"s);
                color(0, 0, 0);
                continue;
            }
            if (p >= 50)
            {
                color(20, 10, 0);
                mes(u8"Bad"s);
                color(0, 0, 0);
                continue;
            }
            mes(u8"Hopeless"s);
            color(0, 0, 0);
        }
        s(0) = ""s + sdata(2, cc) + u8"("s + sdata.get(2, cc).original_level
            + u8")"s;
        s(1) = ""s + sdata(3, cc) + u8"("s + sdata.get(3, cc).original_level
            + u8")"s;
        s(2) = ""s + cdata[cc].insanity;
        s(3) = ""s + cdata[cc].current_speed + u8"("s
            + sdata.get(18, cc).original_level + u8")"s;
        s(4) = "";
        s(5) = ""s + cdata[cc].fame;
        s(6) = ""s + cdata[cc].karma;
        s(7) = "";
        s(8) = "";
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            color(20, 10, 0);
            pos(wx + 310, wy + 151 + cnt * 15);
            mes(s(cnt));
            color(0, 0, 0);
        }
        append_accuracy_info(0);
        tc = cc;
        font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
        color(20, 10, 0);
        pos(wx + 417, wy + 281 + p(2) * 16);
        mes(i18n::s.get("core.locale.ui.chara_sheet.damage.protect"));
        color(0, 0, 0);
        color(20, 10, 0);
        pos(wx + 590 - en * 16, wy + 281 + p(2) * 16);
        mes(i18n::s.get("core.locale.ui.chara_sheet.damage.evade"));
        color(0, 0, 0);
        attackskill = 106;
        int evade = calc_evasion(tc);
        prot = calcattackdmg(2);
        font(14 - en * 2);
        pos(wx + 460 + en * 8, wy + 279 + p(2) * 16);
        mes(""s + (100 - 10000 / (prot + 100)) + u8"% + "s + protdice1 + u8"d"s
            + protdice2);
        pos(wx + 625 - en * 8, wy + 279 + p(2) * 16);
        mes(""s + evade + u8"%"s);
        ++p(2);
        s(0) = i18n::s.get(
            "core.locale.ui.chara_sheet.time.turn_counter", gdata_play_turns);
        s(1) = i18n::s.get(
            "core.locale.ui.chara_sheet.time.days_counter", gdata_play_days);
        s(2) = ""s + gdata_kill_count;
        s(3) = ""s
            + cnvplaytime(
                   (gdata_play_time + timeGetTime() / 1000 - time_begin));
        s(4) = "";
        s(5) = "";
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            pos(wx + 80, wy + 299 + cnt * 15);
            mes(s(cnt));
        }
        s(0) = ""s + cnvweight(gdata_cargo_weight);
        s(1) = cnvweight(gdata_current_cart_limit);
        s(2) = cnvweight(cdata[cc].sum_of_equipment_weight) + u8" "s
            + cnveqweight(cc);
        s(3) = i18n::s.get(
            "core.locale.ui.chara_sheet.weight.level_counter",
            cnvrank(gdata_deepest_dungeon_level));
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            pos(wx + 287 + en * 14, wy + 299 + cnt * 15);
            mes(s(cnt));
        }
        _cs_buffmax = 0;
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            x = wx + 430 + cnt / 3 * 40;
            y = wy + 151 + cnt % 3 * 32;
            if (cdata[cc].buffs[cnt].id == 0)
            {
                gmode(4, 120);
                draw("buff_icon_none", x, y);
                gmode(2);
                continue;
            }
            ++_cs_buffmax;
            pos(x, y);
            gcopy(5, cdata[cc].buffs[cnt].id * 32, 1120, 32, 32);
            if (_cs_buff == cnt)
            {
                boxf(x, y, 32, 32, {200, 200, 255, 63});
            }
        }
        if (_cs_buffmax != 0)
        {
            const auto duration = calc_buff_duration(
                cdata[cc].buffs[_cs_buff].id, cdata[cc].buffs[_cs_buff].power);
            const auto description = get_buff_description(
                cdata[cc].buffs[_cs_buff].id, cdata[cc].buffs[_cs_buff].power);
            s = ""s
                + i18n::_(
                      u8"buff",
                      std::to_string(cdata[cc].buffs[_cs_buff].id),
                      u8"name")
                + u8": "s + cdata[cc].buffs[_cs_buff].turns
                + i18n::s.get(
                      "core.locale.ui.chara_sheet.buff.duration", duration)
                + description;
        }
        else
        {
            s = i18n::s.get("core.locale.ui.chara_sheet.buff.is_not_currently");
        }
        font(13 - en * 2);
        pos(wx + 108, wy + 366);
        mes(s);
        font(11 + sizefix * 2 - en * 2, snail::font_t::style_t::bold);
        color(20, 10, 0);
        pos(wx + 70, wy + 369 - en * 3);
        mes(i18n::s.get("core.locale.ui.chara_sheet.buff.hint") + ":");
        color(0, 0, 0);
    }
    else
    {
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.skill.name"),
            wx + 28,
            wy + 36);
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.skill.level") + "("
                + i18n::s.get("core.locale.ui.chara_sheet.skill.potential")
                + ")",
            wx + 182,
            wy + 36);
        display_topic(
            i18n::s.get("core.locale.ui.chara_sheet.skill.detail"),
            wx + 320,
            wy + 36);
        keyrange = 0;
        p(1) = 0;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * (page - 1) + cnt;
            if (p >= listmax)
            {
                break;
            }
            key_list(cnt) = key_select(cnt);
            ++keyrange;
            if (list(0, p) < 0)
            {
                p(1) = 1;
                continue;
            }
            ++p(1);
            if (list(0, p) < 100)
            {
                x = 52;
                dx = 18;
            }
            else
            {
                x = 70;
                dx = 0;
            }
            if (p(1) % 2 == 0)
            {
                boxf(
                    wx + x, wy + 66 + cnt * 19, 595 + dx, 18, {12, 14, 16, 16});
            }
            if (list(0, p) < 100)
            {
                continue;
            }
            display_key(wx + 58, wy + 64 + cnt * 19, cnt);
        }
    }
    if (page > 0)
    {
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * (page - 1) + cnt;
            if (p >= listmax)
            {
                break;
            }
            if (list(0, p) >= 0)
            {
                i = list(0, p);
                if (i < 100)
                {
                    x = 54;
                    p(1) = 10;
                }
                else
                {
                    x = 84;
                    p(1) = the_ability_db[i]->related_basic_attribute - 10;
                }
                pos(wx + 38, wy + 75 + cnt * 19);
                gmode(2);
                gcopy_c(1, p(1) * inf_tiles, 672, inf_tiles, inf_tiles);
                s = i18n::_(u8"ability", std::to_string(i), u8"name");
                if (i >= 50 && i < 100)
                {
                    s = i18n::s.get(
                        "core.locale.ui.chara_sheet.skill.resist", cnven(s));
                }
                for (int cnt = 0; cnt < 3; ++cnt)
                {
                    if (gdata(750 + cnt) == cc * 10000 + i)
                    {
                        s = u8"*"s + s;
                    }
                }
                cs_list(cs == cnt, s, wx + x, wy + 66 + cnt * 19 - 1);
                if (list(0, p) >= 50 && list(0, p) < 100)
                {
                    p(1) = clamp(sdata(list(0, p), cc) / 50, 0, 6);
                    s = i18n::_(u8"ui", u8"resistance", u8"_"s + p(1));
                }
                else
                {
                    s = ""s + sdata.get(i, cc).original_level + u8"."s
                        + std::to_string(
                              1000
                              + sdata.get(list(0, p), cc).experience % 1000)
                              .substr(1);
                    if (sdata.get(i, cc).original_level != sdata(i, cc))
                    {
                        p(1) = sdata(i, cc) - sdata.get(i, cc).original_level;
                    }
                    s += u8"("s + sdata.get(i, cc).potential + u8"%)"s;
                }
                pos(wx + 280 - strlen_u(s) * 7, wy + 66 + cnt * 19 + 2);
                mes(s);
                pos(wx + 330, wy + 66 + cnt * 19 + 2);
                mes(i18n::_(u8"ability", std::to_string(i), u8"description"));
                if (_csctrl == 2 || _csctrl == 3)
                {
                    if (_csctrl == 2)
                    {
                        s = ""s + calctraincost(i, cc) + u8"p "s;
                    }
                    else
                    {
                        s = ""s + calclearncost(i, cc) + u8"p "s;
                    }
                    pos(wx + 322 - strlen_u(s) * 7, wy + 66 + cnt * 19 + 2);
                    mes(s);
                }
                else if (sdata.get(i, cc).original_level != sdata(i, cc))
                {
                    i = sdata(i, cc) - sdata.get(i, cc).original_level;
                    if (list(0, p) >= 50)
                    {
                        i = i / 50;
                    }
                    else
                    {
                        i = i / 5;
                    }
                    s = enchantment_print_level(i);
                    pos(wx + 282, wy + 66 + cnt * 19 + 2);
                    mes(s);
                }
            }
            else
            {
                font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
                cs_list(cs == cnt, listn(0, p), wx + 88, wy + 66 + cnt * 19);
                font(14 - en * 2);
            }
        }
        cs_bk = cs;
    }
}

optional<ui_menu_character_sheet::result_type> ui_menu_character_sheet::on_key(
    const std::string& key)
{
    if (page == 0)
    {
        if (key == u8"p"s)
        {
            if (cc < 16)
            {
                change_appearance();
                if (mode != 1)
                {
                    nowindowanime = 1;
                }
                _returned_from_portrait = 1;
                return ui_menu_character_sheet::result::finish(true);
            }
        }
        else if (key == key_north)
        {
            --_cs_buff;
            if (_cs_buff < 0)
            {
                _cs_buff = _cs_buffmax - 1;
            }
            set_reupdate();
            return none;
        }
        else if (key == key_south)
        {
            ++_cs_buff;
            if (_cs_buff >= _cs_buffmax)
            {
                _cs_buff = 0;
            }
            set_reupdate();
            return none;
        }
    }
    else if (_csctrl != 1)
    {
        if (key == key_mode2)
        {
            for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
            {
                i = list(0, pagesize * (page - 1) + cs);
                break;
            }
            if (i != -1)
            {
                p = 750;
                for (int cnt = 750; cnt < 753; ++cnt)
                {
                    if (gdata(cnt) % 10000 == 0)
                    {
                        p = cnt;
                    }
                    if (gdata(cnt) == cc * 10000 + i)
                    {
                        p = cnt;
                        i = 0;
                        break;
                    }
                }
                gdata(p) = cc * 10000 + i;
                snd(20);
            }
        }
    }
    else if (_csctrl == 1)
    {
        if (key == key_enter)
        {
            snd(103);
            return ui_menu_character_sheet::result::cancel();
        }
        if (key == key_cancel)
        {
            return ui_menu_character_sheet::result::finish();
        }
        return none;
    }
    p = -1;
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = list(0, pagesize * (page - 1) + cnt);
            break;
        }
    }
    if (p != -1)
    {
        if (_csctrl != 4)
        {
            csskill = p;
            if (_csctrl == 2 || _csctrl == 3)
            {
                screenupdate = -1;
                update_screen();
                tc = tcbk;
                return ui_menu_character_sheet::result::cancel();
            }
            if (cdata.player().skill_bonus < 1 || p < 0 || p < 100)
            {
                set_reupdate();
                return none;
            }
            if (sdata.get(csskill, 0).original_level == 0)
            {
                snd(27);
                set_reupdate();
                return none;
            }
            --cdata.player().skill_bonus;
            snd(19);
            chara_gain_skill_exp(cdata[cc], csskill, 400, 2, 1000);
            modify_potential(
                cdata[cc],
                csskill,
                clamp(15 - sdata.get(csskill, cc).potential / 15, 2, 15));
            render_hud();
            set_reupdate();
        }
    }
    else if (key == key_pageup)
    {
        ++page;
        snd(1);
        set_reupdate();
    }
    else if (key == key_pagedown)
    {
        --page;
        snd(1);
        set_reupdate();
    }
    else if (key == key_cancel)
    {
        menucycle = 0;
        if (_csctrl == 0)
        {
            update_screen();
        }
        else
        {
            screenupdate = -1;
            update_screen();
            tc = tcbk;
        }
        return ui_menu_character_sheet::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
