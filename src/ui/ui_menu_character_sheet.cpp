#include "ui_menu_character_sheet.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../character.hpp"
#include "../character_status.hpp"
#include "../class.hpp"
#include "../draw.hpp"
#include "../enchantment.hpp"
#include "../map.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

/*
        game_data.tracked_skills(0 - 10) => tracked skills
        (ctrl +f for [TRACKING])
*/

static void _load_skill_list(CharacterSheetOperation op)
{
    for (int cnt = 150; cnt < 400; ++cnt)
    {
        f = 0;
        if (sdata(cnt, cc) != 0)
        {
            f = 1;
            if (op == CharacterSheetOperation::train_skill)
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

static void _load_weapon_proficiency_list(CharacterSheetOperation op)
{
    for (int cnt = 100; cnt < 150; ++cnt)
    {
        f = 0;
        if (op != CharacterSheetOperation::learn_skill)
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
}

static void _load_resistances_list()
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

static void _load_list_skill_category(CharacterSheetOperation op)
{
    list(0, listmax) = -1;
    list(1, listmax) = 20000;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.chara_sheet.category.skill");
    ++listmax;
    if (op == CharacterSheetOperation::learn_skill)
    {
        map_get_trainer_skills();
    }
    else
    {
        _load_skill_list(op);
    }
}

static void _load_list_proficiency_category(CharacterSheetOperation op)
{
    list(0, listmax) = -1;
    list(1, listmax) = 30000;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.chara_sheet.category.weapon_proficiency");
    ++listmax;
    _load_weapon_proficiency_list(op);

    if (op != CharacterSheetOperation::train_skill
        && op != CharacterSheetOperation::learn_skill)
    {
        _load_resistances_list();
    }
}

static void _load_list(CharacterSheetOperation op)
{
    _load_list_skill_category(op);
    _load_list_proficiency_category(op);

    sort_list_by_column1();
}

static void _load_portrait()
{
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
    if (cdata[cc].portrait < 0)
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
}

bool UIMenuCharacterSheet::init()
{
    page = 0;
    pagesize = 16;
    listmax = 0;
    cs = 0;
    if (_operation != CharacterSheetOperation::investigate_ally)
    {
        cc = 0;
    }
    curmenu = 0;
    if (_operation == CharacterSheetOperation::train_skill
        || _operation == CharacterSheetOperation::learn_skill)
    {
        page = 1;
    }

    _load_list(_operation);

    gsel(7);
    picload(filesystem::dir::graphic() / u8"ie_sheet.bmp");
    gsel(0);
    wx = (windoww - 700) / 2 + inf_screenx;
    wy = winposy(400) - 10;
    ww = 700;
    wh = 400;
    s = i18n::s.get("core.locale.ui.chara_sheet.title.default");
    if (_operation == CharacterSheetOperation::train_skill)
    {
        s = i18n::s.get("core.locale.ui.chara_sheet.title.training");
    }
    if (_operation == CharacterSheetOperation::learn_skill)
    {
        s = i18n::s.get("core.locale.ui.chara_sheet.title.learning");
    }
    if (_operation != CharacterSheetOperation::character_making)
    {
        snd(94);
    }
    window_animation(wx, wy, ww, wh, 9, 4);

    _load_portrait();

    gsel(0);
    if (!_returned_from_portrait)
    {
        gmode(6, 80);
        pos(wx + 4, wy + 4);
        gcopy(7, 0, 0, 700, 400);
        gmode(2);
    }
    if (_operation == CharacterSheetOperation::train_skill)
    {
        txtnew();
        txt(i18n::s.get("core.locale.ui.chara_sheet.train_which_skill"));
    }
    _returned_from_portrait = false;

    return true;
}

static void _draw_title(CharacterSheetOperation op)
{
    std::string title = "";
    std::string strhint6 = i18n::s.get("core.locale.ui.hint.portrait");

    switch (op)
    {
    case CharacterSheetOperation::normal:
        if (page == 0)
        {
            title = i18n::s.get("core.locale.ui.chara_sheet.hint.hint")
                + strhint6 + strhint2 + strhint3;
        }
        else
        {
            title = i18n::s.get("core.locale.ui.chara_sheet.hint.spend_bonus")
                + strhint2 + strhint3;
        }
        break;
    case CharacterSheetOperation::character_making:
        title = i18n::s.get("core.locale.ui.chara_sheet.hint.reroll") + strhint6
            + i18n::s.get("core.locale.ui.chara_sheet.hint.confirm");
        break;
    case CharacterSheetOperation::train_skill:
        if (page == 0)
        {
            title = strhint6 + strhint2 + strhint3;
        }
        else
        {
            title = i18n::s.get("core.locale.ui.chara_sheet.hint.train_skill")
                + strhint2 + strhint3;
        }
        break;
    case CharacterSheetOperation::learn_skill:
        if (page == 0)
        {
            title = strhint6 + strhint2 + strhint3;
        }
        else
        {
            title = i18n::s.get("core.locale.ui.chara_sheet.hint.learn_skill")
                + strhint2 + strhint3;
        }
        break;
    case CharacterSheetOperation::investigate_ally:
        if (page == 0)
        {
            title = i18n::s.get("core.locale.ui.chara_sheet.hint.blessing_info")
                + strhint6 + strhint2 + strhint3;
        }
        else
        {
            title = strhint2 + strhint3;
        }
        break;
    }

    if (op != CharacterSheetOperation::character_making)
    {
        if (page != 0)
        {
            title += ""s + key_mode2 + u8" ["s
                + i18n::s.get("core.locale.ui.chara_sheet.hint.track_skill")
                + u8"]"s;
        }
    }

    color(0, 0, 0);
    show_title(title);
}

void UIMenuCharacterSheet::update()
{
    if (_operation != CharacterSheetOperation::character_making)
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
    if (_operation == CharacterSheetOperation::character_making)
    {
        // Don't allow moving to skills list during character
        // creation.
        pagemax = 0;
    }

    _draw_title(_operation);
}

static void _draw_window(bool show_bonus)
{
    s = "";
    if (show_bonus && page != 0)
    {
        s = i18n::s.get(
            "core.locale.ui.chara_sheet.you_can_spend_bonus",
            cdata[cc].skill_bonus);
    }
    display_window2(
        (windoww - 700) / 2 + inf_screenx, winposy(400) - 10, 700, 400, 7);
}


static void _draw_first_page_topics()
{
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.attributes"),
        wx + 28,
        wy + 122);
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.combat_rolls"),
        wx + 400,
        wy + 253);
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.history"), wx + 28, wy + 273);
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.blessing_and_hex"),
        wx + 400,
        wy + 122);
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.extra_info"),
        wx + 220,
        wy + 273);
}

static void _draw_portrait_face()
{
    if (cdata[cc].portrait >= 0)
    {
        int portrait_id = cdata[cc].sex * 64 + cdata[cc].portrait;
        boxf(wx + 560, wy + 27, 80, 112, snail::Color{0, 0, 0, 255});
        pos(wx + 560, wy + 27);
        gcopy(4, portrait_id % 16 * 48, portrait_id / 16 * 72, 48, 72, 80, 112);
    }
    else
    {
        const auto filepath = filesystem::dir::user() / u8"graphic"
            / (u8"face"s + std::abs(cdata[cc].portrait + 1) + u8".bmp");
        if (cdata[cc].portrait != -1)
        {
            if (fs::exists(filepath))
            {
                boxf(wx + 560, wy + 27, 80, 112, snail::Color{0, 0, 0, 255});
                pos(wx + 560, wy + 27);
                gcopy(4, 0, 0, 80, 112, 80, 112);
            }
        }
    }
    window2(wx + 557, wy + 23, 87, 120, 1, 10);
}

static void _draw_portrait_sprite()
{
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
}

static void _draw_first_page_portrait()
{
    _draw_portrait_face();
    _draw_portrait_sprite();
}

static void _draw_first_page_text_exp()
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
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
}

static void _draw_first_page_text_personal()
{
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
}

static void _draw_first_page_text_attribute()
{
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
}

static void _draw_first_page_text_time()
{
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
}

static void _draw_first_page_text_weight()
{
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
}

static void _draw_first_page_text_level()
{
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
}

static void _draw_first_page_text_name()
{
    s(0) = cdatan(0, cc);
    s(1) = cdatan(1, cc);
    s(2) = cnven(i18n::_(u8"race", cdatan(2, cc), u8"name"));
    access_class_info(2, cdatan(3, cc));
    s(4) = cnven(classname);
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
}

static void _draw_attribute_level(int cnt)
{
    std::string level =
        u8"("s + sdata.get(10 + cnt, cc).original_level + u8")"s;
    if (encfind(cc, 60010 + cnt) != -1)
    {
        level += u8"*"s;
    }
    pos(wx + 92, wy + 151 + cnt * 15);
    color(20, 10, 0);
    mes(""s + sdata((10 + cnt), cc));
    color(0, 0, 0);
    pos(wx + 124, wy + 151 + cnt * 15);
    color(20, 10, 0);
    mes(level);
    color(0, 0, 0);
}

static void _draw_attribute_potential(int cnt)
{
    int potential = sdata.get(10 + cnt, cc).potential;
    pos(wx + 176, wy + 152 + cnt * 15);
    if (potential >= 200)
    {
        color(20, 10, 0);
        mes(u8"Superb"s);
        color(0, 0, 0);
        return;
    }
    if (potential >= 150)
    {
        color(20, 10, 0);
        mes(u8"Great"s);
        color(0, 0, 0);
        return;
    }
    if (potential >= 100)
    {
        color(20, 10, 0);
        mes(u8"Good"s);
        color(0, 0, 0);
        return;
    }
    if (potential >= 50)
    {
        color(20, 10, 0);
        mes(u8"Bad"s);
        color(0, 0, 0);
        return;
    }
    mes(u8"Hopeless"s);
    color(0, 0, 0);
}

static void _draw_attribute(int cnt)
{
    _draw_attribute_level(cnt);
    _draw_attribute_potential(cnt);
}

static void _draw_first_page_attributes()
{
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        _draw_attribute(cnt);
    }
}

static void _draw_first_page_weapon_info()
{
    append_accuracy_info(0);
    tc = cc;
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
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
}

static void _draw_first_page_text_fame()
{
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
}

static void _draw_first_page_stats_fame()
{
    s(0) =
        ""s + sdata(2, cc) + u8"("s + sdata.get(2, cc).original_level + u8")"s;
    s(1) =
        ""s + sdata(3, cc) + u8"("s + sdata.get(3, cc).original_level + u8")"s;
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
}

static void _draw_first_page_stats_time()
{
    s(0) = i18n::s.get(
        "core.locale.ui.chara_sheet.time.turn_counter", game_data.play_turns);
    s(1) = i18n::s.get(
        "core.locale.ui.chara_sheet.time.days_counter", game_data.play_days);
    s(2) = ""s + game_data.kill_count;
    s(3) = ""s
        + cnvplaytime(
               (game_data.play_time + timeGetTime() / 1000 - time_begin));
    s(4) = "";
    s(5) = "";
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        pos(wx + 80, wy + 299 + cnt * 15);
        mes(s(cnt));
    }
}

static void _draw_first_page_stats_weight()
{
    s(0) = ""s + cnvweight(game_data.cargo_weight);
    s(1) = cnvweight(game_data.current_cart_limit);
    s(2) =
        cnvweight(cdata[cc].sum_of_equipment_weight) + u8" "s + cnveqweight(cc);
    s(3) = i18n::s.get(
        "core.locale.ui.chara_sheet.weight.level_counter",
        cnvrank(game_data.deepest_dungeon_level));
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        pos(wx + 287 + en * 14, wy + 299 + cnt * 15);
        mes(s(cnt));
    }
}

static void _draw_first_page_buffs(int& _cs_buff, int& _cs_buffmax)
{
    _cs_buffmax = 0;
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        x = wx + 430 + cnt / 3 * 40;
        y = wy + 151 + cnt % 3 * 32;
        if (cdata[cc].buffs[cnt].id == 0)
        {
            gmode(4, 120);
            elona::draw("buff_icon_none", x, y);
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

    std::string buff_desc;

    if (_cs_buffmax != 0)
    {
        const auto duration = calc_buff_duration(
            cdata[cc].buffs[_cs_buff].id, cdata[cc].buffs[_cs_buff].power);
        const auto description = get_buff_description(
            cdata[cc].buffs[_cs_buff].id, cdata[cc].buffs[_cs_buff].power);
        buff_desc = ""s
            + i18n::_(u8"buff",
                      std::to_string(cdata[cc].buffs[_cs_buff].id),
                      u8"name")
            + u8": "s + cdata[cc].buffs[_cs_buff].turns
            + i18n::s.get("core.locale.ui.chara_sheet.buff.duration", duration)
            + description;
    }
    else
    {
        buff_desc =
            i18n::s.get("core.locale.ui.chara_sheet.buff.is_not_currently");
    }

    font(13 - en * 2);
    pos(wx + 108, wy + 366);
    mes(buff_desc);
    font(11 + sizefix * 2 - en * 2, snail::Font::Style::bold);
    color(20, 10, 0);
    pos(wx + 70, wy + 369 - en * 3);
    mes(i18n::s.get("core.locale.ui.chara_sheet.buff.hint") + ":");
    color(0, 0, 0);
}

static void _draw_first_page(int& _cs_buff, int& _cs_buffmax)
{
    keyrange = 0;
    key_list = key_enter;

    _draw_first_page_topics();
    _draw_first_page_portrait();

    _draw_first_page_text_exp();
    _draw_first_page_text_personal();
    _draw_first_page_text_attribute();
    _draw_first_page_text_time();
    _draw_first_page_text_weight();
    _draw_first_page_text_level();
    _draw_first_page_text_name();

    _draw_first_page_attributes();

    _draw_first_page_text_fame();

    _draw_first_page_stats_fame();

    _draw_first_page_weapon_info();

    _draw_first_page_stats_time();
    _draw_first_page_stats_weight();

    _draw_first_page_buffs(_cs_buff, _cs_buffmax);
}

static void _draw_other_pages_topics()
{
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.skill.name"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.skill.level") + "("
            + i18n::s.get("core.locale.ui.chara_sheet.skill.potential") + ")",
        wx + 182,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.chara_sheet.skill.detail"),
        wx + 320,
        wy + 36);
}

static void _draw_other_pages_keys()
{
    keyrange = 0;
    int item_count = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * (page - 1) + cnt;
        if (index >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;

        int list_item = list(0, index);

        if (list_item < 0)
        {
            item_count = 1;
            continue;
        }
        ++item_count;
        if (list_item < 100)
        {
            x = 52;
            dx = 18;
        }
        else
        {
            x = 70;
            dx = 0;
        }
        if (item_count % 2 == 0)
        {
            boxf(wx + x, wy + 66 + cnt * 19, 595 + dx, 18, {12, 14, 16, 16});
        }
        if (list_item < 100)
        {
            continue;
        }
        display_key(wx + 58, wy + 64 + cnt * 19, cnt);
    }
}

static void _draw_other_pages()
{
    _draw_other_pages_topics();
    _draw_other_pages_keys();
}


static void _draw_skill_icon(int cnt, int list_item)
{
    int icon;

    if (list_item < 100)
    {
        x = 54;
        icon = 10;
    }
    else
    {
        x = 84;
        icon = the_ability_db[list_item]->related_basic_attribute - 10;
    }

    pos(wx + 38, wy + 75 + cnt * 19);
    gmode(2);
    gcopy_c(1, icon * inf_tiles, 672, inf_tiles, inf_tiles);
}

static bool _is_resistance(int skill)
{
    return skill >= 50 && skill < 100;
}

static void _draw_skill_name(int cnt, int skill_id)
{
    std::string skill_name =
        i18n::_(u8"ability", std::to_string(skill_id), u8"name");

    if (_is_resistance(skill_id))
    {
        skill_name = i18n::s.get(
            "core.locale.ui.chara_sheet.skill.resist", cnven(skill_name));
    }

    // [TRACKING] Shows the star in the (c) menu
    for (int cnt = 0;
         cnt < (elona::Config::instance().allow_enhanced_skill ? 10 : 3);
         ++cnt)
    {
        if (game_data.tracked_skills.at(cnt) == cc * 10000 + skill_id)
        {
            skill_name = u8"*"s + skill_name;
        }
    }

    cs_list(cs == cnt, skill_name, wx + x, wy + 66 + cnt * 19 - 1);
}

static void _draw_skill_power(int cnt, int skill_id)
{
    int power;
    std::string desc = "";

    if (_is_resistance(skill_id))
    {
        power = clamp(sdata(skill_id, cc) / 50, 0, 6);
        desc = i18n::_(u8"ui", u8"resistance", u8"_"s + power);
    }
    else
    {
        desc = ""s + sdata.get(skill_id, cc).original_level + u8"."s
            + std::to_string(1000 + sdata.get(skill_id, cc).experience % 1000)
                  .substr(1);
        if (sdata.get(skill_id, cc).original_level != sdata(skill_id, cc))
        {
            power =
                sdata(skill_id, cc) - sdata.get(skill_id, cc).original_level;
        }
        desc += u8"("s + sdata.get(skill_id, cc).potential + u8"%)"s;
    }

    pos(wx + 280 - strlen_u(desc) * 7, wy + 66 + cnt * 19 + 2);
    mes(desc);
}

static void _draw_skill_desc(int cnt, int skill_id)
{
    pos(wx + 330, wy + 66 + cnt * 19 + 2);
    mes(i18n::_(u8"ability", std::to_string(skill_id), u8"description"));
}

static void _draw_skill_train_cost(int cnt, int skill_id, bool is_training)
{
    std::string train_cost;

    if (is_training)
    {
        train_cost = ""s + calctraincost(skill_id, cc) + u8"p "s;
    }
    else
    {
        train_cost = ""s + calclearncost(skill_id, cc) + u8"p "s;
    }
    pos(wx + 322 - strlen_u(train_cost) * 7, wy + 66 + cnt * 19 + 2);
    mes(train_cost);
}

static bool _has_enchantment(int cc, int skill_id)
{
    return sdata.get(skill_id, cc).original_level != sdata(skill_id, cc);
}

static void _draw_skill_enchantment_power(int cnt, int skill_id)
{
    skill_id = sdata(skill_id, cc) - sdata.get(skill_id, cc).original_level;
    if (skill_id >= 50)
    {
        skill_id = skill_id / 50;
    }
    else
    {
        skill_id = skill_id / 5;
    }
    std::string enchantment_level = enchantment_print_level(skill_id);
    pos(wx + 282, wy + 66 + cnt * 19 + 2);
    mes(enchantment_level);
}

static void _draw_skill_entry(int cnt, int skill_id, CharacterSheetOperation op)
{
    _draw_skill_icon(cnt, skill_id);
    _draw_skill_name(cnt, skill_id);
    _draw_skill_power(cnt, skill_id);
    _draw_skill_desc(cnt, skill_id);

    if (op == CharacterSheetOperation::train_skill
        || op == CharacterSheetOperation::learn_skill)
    {
        bool is_training = op == CharacterSheetOperation::train_skill;
        _draw_skill_train_cost(cnt, skill_id, is_training);
    }
    else if (_has_enchantment(cc, skill_id))
    {
        _draw_skill_enchantment_power(cnt, skill_id);
    }
}

static void _draw_text_entry(int cnt, const std::string& text)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    cs_list(cs == cnt, text, wx + 88, wy + 66 + cnt * 19);
    font(14 - en * 2);
}

static void _draw_other_page_single_list_entry(
    int cnt,
    int list_item,
    const std::string& text,
    CharacterSheetOperation op)
{
    if (list_item >= 0)
    {
        _draw_skill_entry(cnt, list_item, op);
    }
    else
    {
        _draw_text_entry(cnt, text);
    }
}

static void _draw_other_page_list_entries(CharacterSheetOperation op)
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * (page - 1) + cnt;
        if (index >= listmax)
        {
            break;
        }

        int list_item = list(0, index);
        const std::string& text = listn(0, index);
        _draw_other_page_single_list_entry(cnt, list_item, text, op);
    }
    cs_bk = cs;
}

void UIMenuCharacterSheet::draw()
{
    cs_bk = -1;
    bool show_bonus = _operation == CharacterSheetOperation::normal;
    _draw_window(show_bonus);

    if (page == 0)
    {
        _draw_first_page(_cs_buff, _cs_buffmax);
    }
    else
    {
        _draw_other_pages();
    }
    if (page > 0)
    {
        _draw_other_page_list_entries(_operation);
    }
}

static void _track_skill(int skill_id)
{
    int tracked_skill_index = 0;
    int max_tracked_skills =
        elona::Config::instance().allow_enhanced_skill ? 10 : 3;

    for (int cnt = 0; cnt < max_tracked_skills; ++cnt)
    {
        if (game_data.tracked_skills.at(cnt) % 10000 == 0)
        {
            tracked_skill_index = cnt;
        }
        if (game_data.tracked_skills.at(cnt) == cc * 10000 + skill_id)
        {
            tracked_skill_index = cnt;
            skill_id = 0;
            break;
        }
    }
    game_data.tracked_skills.at(tracked_skill_index) = cc * 10000 + skill_id;
    snd(20);
}

static void _apply_skill_bonus(int csskill_)
{
    --cdata.player().skill_bonus;
    snd(19);
    chara_gain_skill_exp(cdata[cc], csskill_, 400, 2, 1000);
    modify_potential(
        cdata[cc],
        csskill_,
        clamp(15 - sdata.get(csskill_, cc).potential / 15, 2, 15));
}

optional<UIMenuCharacterSheet::ResultType> UIMenuCharacterSheet::on_key(
    const std::string& action)
{
    if (page == 0)
    {
        if (action == "portrait")
        {
            if (cc < 16)
            {
                change_appearance();
                if (_operation != CharacterSheetOperation::character_making)
                {
                    nowindowanime = 1;
                }
                _returned_from_portrait = true;
                set_reinit();
                return none;
            }
        }
        else if (action == "north")
        {
            --_cs_buff;
            if (_cs_buff < 0)
            {
                _cs_buff = _cs_buffmax - 1;
            }
            set_reupdate();
            return none;
        }
        else if (action == "south")
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

    if (_operation == CharacterSheetOperation::character_making)
    {
        if (action == "enter")
        {
            snd(103);
            return UIMenuCharacterSheet::Result::cancel();
        }
        if (action == "cancel")
        {
            return UIMenuCharacterSheet::Result::finish(
                UIMenuCompositeCharacterResult{false});
        }
        return none;
    }
    else
    {
        // [TRACKING] Stores which skill id is to be tracked
        if (action == "switch_mode_2" && page > 0)
        {
            int index = pagesize * (page - 1) + cs;
            int skill_id = list(0, index);

            if (skill_id != -1)
            {
                _track_skill(skill_id);
            }
        }
    }

    int skill_id = -1;
    if (auto selected = get_selected_index_this_page())
    {
        skill_id = list(0, pagesize * (page - 1) + *selected);
    }
    if (skill_id != -1)
    {
        if (_operation != CharacterSheetOperation::investigate_ally)
        {
            if (_operation == CharacterSheetOperation::train_skill
                || _operation == CharacterSheetOperation::learn_skill)
            {
                screenupdate = -1;
                update_screen();
                tc = tcbk;
                return UIMenuCharacterSheet::Result::finish(
                    UIMenuCompositeCharacterResult{skill_id});
            }
            if (cdata.player().skill_bonus < 1 || skill_id < 0
                || skill_id < 100)
            {
                set_reupdate();
                return none;
            }
            if (sdata.get(skill_id, 0).original_level == 0)
            {
                snd(27);
                set_reupdate();
                return none;
            }

            _apply_skill_bonus(skill_id);

            render_hud();
            set_reupdate();
        }
    }
    else if (action == "next_page")
    {
        ++page;
        snd(1);
        set_reupdate();
    }
    else if (action == "previous_page")
    {
        --page;
        snd(1);
        set_reupdate();
    }
    else if (action == "cancel")
    {
        menucycle = 0;
        if (_operation == CharacterSheetOperation::normal)
        {
            update_screen();
        }
        else
        {
            screenupdate = -1;
            update_screen();
            tc = tcbk;
        }
        return UIMenuCharacterSheet::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
