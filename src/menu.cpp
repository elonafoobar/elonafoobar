#include "menu.hpp"
#include <iostream>
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "command.hpp"
#include "config.hpp"
#include "db_item.hpp"
#include "defines.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "macro.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "variables.hpp"

#include "ui/ui_menu_adventurers.hpp"
#include "ui/ui_menu_alias.hpp"
#include "ui/ui_menu_book.hpp"
#include "ui/ui_menu_character_sheet.hpp"
#include "ui/ui_menu_ctrl_ally.hpp"
#include "ui/ui_menu_feats.hpp"
#include "ui/ui_menu_game_help.hpp"
#include "ui/ui_menu_god.hpp"
#include "ui/ui_menu_hire.hpp"
#include "ui/ui_menu_item_desc.hpp"
#include "ui/ui_menu_npc_tone.hpp"
#include "ui/ui_menu_quest_board.hpp"
#include "ui/ui_menu_scene.hpp"
#include "ui/ui_menu_skills.hpp"
#include "ui/ui_menu_spell_writer.hpp"
#include "ui/ui_menu_spells.hpp"

#include "ui/ui_menu_composite_character.hpp"
#include "ui/ui_menu_composite_message.hpp"

namespace elona
{

void text_set()
{
    strhint1 = i18n::s.get("core.locale.ui.hint.cursor");
    strhint2 = ""s + key_pageup + u8","s + key_pagedown
        + i18n::s.get("core.locale.ui.hint.page");
    strhint3 = i18n::s.get("core.locale.ui.hint.close");
    strhint3b = i18n::s.get("core.locale.ui.hint.back");
    strhint4 = i18n::s.get("core.locale.ui.hint.enter");
    strhint5 =
        ""s + key_identify + i18n::s.get("core.locale.ui.hint.known_info");
    strhint5b = ""s + key_mode + i18n::s.get("core.locale.ui.hint.mode");
    strhint7 = i18n::s.get("core.locale.ui.hint.shortcut");

    SDIM4(_melee, 20, 3, 8);
    if (jp)
    {
        _melee(0, 0) = u8"殴って"s;
        _melee(1, 0) = u8"殴られた。"s;
        _melee(2, 0) = u8"手"s;
    }
    else
    {
        _melee(0, 0) = u8"punch"s;
        _melee(1, 0) = u8"punch"s;
        _melee(2, 0) = u8"hand"s;
    }
    if (jp)
    {
        _melee(0, 3) = u8"噛み付いて"s;
        _melee(1, 3) = u8"噛み付かれた。"s;
        _melee(2, 3) = u8"牙"s;
    }
    else
    {
        _melee(0, 3) = u8"bite"s;
        _melee(1, 3) = u8"bite"s;
        _melee(2, 3) = u8"fang"s;
    }
    if (jp)
    {
        _melee(0, 4) = u8"睨んで"s;
        _melee(1, 4) = u8"睨まれた。"s;
        _melee(2, 4) = u8"眼"s;
    }
    else
    {
        _melee(0, 4) = u8"gaze"s;
        _melee(1, 4) = u8"gaze"s;
        _melee(2, 4) = u8"eye"s;
    }
    if (jp)
    {
        _melee(0, 1) = u8"引っ掻き"s;
        _melee(1, 1) = u8"引っ掻かれた。"s;
        _melee(2, 1) = u8"爪"s;
    }
    else
    {
        _melee(0, 1) = u8"claw"s;
        _melee(1, 1) = u8"claw"s;
        _melee(2, 1) = u8"claw"s;
    }
    if (jp)
    {
        _melee(0, 5) = u8"刺し"s;
        _melee(1, 5) = u8"刺された。"s;
        _melee(2, 5) = u8"針"s;
    }
    else
    {
        _melee(0, 5) = u8"sting"s;
        _melee(1, 5) = u8"sting"s;
        _melee(2, 5) = u8"needle"s;
    }
    if (jp)
    {
        _melee(0, 6) = u8"触って"s;
        _melee(1, 6) = u8"触られた。"s;
        _melee(2, 6) = u8"手"s;
    }
    else
    {
        _melee(0, 6) = u8"touch"s;
        _melee(1, 6) = u8"touch"s;
        _melee(2, 6) = u8"hand"s;
    }
    if (jp)
    {
        _melee(0, 7) = u8"胞子を撒き散らし"s;
        _melee(1, 7) = u8"胞子を飛ばされた。"s;
        _melee(2, 7) = u8"胞子"s;
    }
    else
    {
        _melee(0, 7) = u8"attack"s;
        _melee(1, 7) = u8"attack"s;
        _melee(2, 7) = u8"spore"s;
    }
    randcolor(0) = 0;
    randcolor(1) = 4;
    randcolor(2) = 2;
    randcolor(3) = 5;
    randcolor(4) = 6;
    _randcolor(0) = 0;
    _randcolor(1) = 2;
    _randcolor(2) = 4;
    _randcolor(3) = 5;
    _randcolor(4) = 6;
    _randcolor(5) = 3;
    homepage = lang(
        u8"http://homepage3.nifty.com/rfish/index.html"s,
        u8"http://homepage3.nifty.com/rfish/index_e.html"s);
    strblank = lang("", u8" "s);
}

void show_quick_menu()
{
    int tx, ty;

    // On Android, draw the menu in the center of the screen.
    // Otherwise, it would be obscured by the keypad in landscape
    // mode.
    if (defines::is_android)
    {
        tx = (windoww / 2) - 100;
        ty = (windowh / 2) - 100;
    }
    else
    {
        tx = 50;
        ty = windowh - 255;
    }

    page = quickpage;
    listmax = 0;
    snd(5);
    cs = -1;
label_2698:
    listmax = 0;
    if (page == 3)
    {
        page = 2;
    }
    if (page == -1)
    {
        page = 0;
    }
    if (page == 0)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.help");
        listn(1, listmax) = key_help;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.log");
        listn(1, listmax) = key_msglog;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.chara");
        listn(1, listmax) = key_charainfo;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.journal");
        listn(1, listmax) = key_journal;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
    }
    if (page == 1)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.wear");
        listn(1, listmax) = key_wear;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.rest");
        listn(1, listmax) = key_rest;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.spell");
        listn(1, listmax) = key_cast;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.skill");
        listn(1, listmax) = key_skill;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.fire");
        listn(1, listmax) = key_fire;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.dig");
        listn(1, listmax) = key_dig;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
    }
    if (page == 2)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.pray");
        listn(1, listmax) = key_pray;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.ammo");
        listn(1, listmax) = key_ammo;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.interact");
        listn(1, listmax) = key_interact;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = i18n::s.get("core.locale.ui.quick_menu.bash");
        listn(1, listmax) = key_bash;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
        list(0, listmax) = listmax;
        listn(0, listmax) = "";
        listn(1, listmax) = u8"aaa"s;
        ++listmax;
    }
    s(0) = i18n::s.get("core.locale.ui.quick_menu.info");
    s(1) = i18n::s.get("core.locale.ui.quick_menu.action");
    s(2) = i18n::s.get("core.locale.ui.quick_menu.etc");
    s(3) = u8"null"s;
    p = page - 1;
    if (p == -1)
    {
        p = 3;
    }
    listn(0, 0) = s(p);
    listn(0, 4) = s(page);
    p = page + 1;
    if (p == 3)
    {
        p = 3;
    }
    listn(0, 8) = s(p);
    t = 0;
label_2699_internal:
    font(12 + sizefix - en * 2);
    x(0) = 25;
    x(1) = 50;
    x(2) = 50;
    x(3) = 100;
    x(4) = 100;
    x(5) = 100;
    x(6) = 150;
    x(7) = 150;
    x(8) = 175;
    y(0) = 50;
    y(1) = 15;
    y(2) = 85;
    y(3) = 0;
    y(4) = 50;
    y(5) = 100;
    y(6) = 15;
    y(7) = 85;
    y(8) = 50;
    s = u8"○コマンド"s;
    gmode(2);
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        p = cnt;
        if (listn(0, p) == u8"null"s)
        {
            continue;
        }
        if (cnt == 0 || cnt == 4 || cnt == 8)
        {
            draw("quickmenu_submenu", x(cnt) + tx, y(cnt) + ty);
        }
        else
        {
            draw("quickmenu_action", x(cnt) + tx, y(cnt) + ty);
        }
        gmode(4, (t + cnt) % 10 * (t + cnt) % 10 * 12 * ((t + cnt) % 50 < 10));
        if (cs == cnt)
        {
            gmode(5, 140);
        }
        if (cnt == 0 || cnt == 4 || cnt == 8)
        {
            draw("quickmenu_submenu", x(cnt) + tx, y(cnt) + ty);
        }
        else
        {
            draw("quickmenu_action", x(cnt) + tx, y(cnt) + ty);
        }
        gmode(2);
        s = listn(0, p);
        bmes(s, x(cnt) + tx + 25 - strlen_u(s) * 3, y(cnt) + ty + 19);
    }
    ++t;
    redraw();
    await(config::instance().wait1);
    key_check(key_wait_delay_t::none);
    if (key == key_north)
    {
        key = listn(1, 3);
        cs = 3;
    }
    if (key == key_south)
    {
        key = listn(1, 5);
        cs = 5;
    }
    if (key == key_west)
    {
        cs = 0;
    }
    if (key == key_east)
    {
        cs = 8;
    }
    if (key == key_northwest)
    {
        key = listn(1, 1);
        cs = 1;
    }
    if (key == key_northeast)
    {
        key = listn(1, 6);
        cs = 6;
    }
    if (key == key_southwest)
    {
        key = listn(1, 2);
        cs = 2;
    }
    if (key == key_southeast)
    {
        key = listn(1, 7);
        cs = 7;
    }
    if (key == key_cancel)
    {
        cs = -1;
        snd(5);
        key = "";
        goto label_2700_internal;
        return;
    }
    if (key != ""s)
    {
        if (cs == -1)
        {
            snd(5);
            key = "";
            goto label_2700_internal;
            return;
        }
        if (key == key_enter)
        {
            key = listn(1, cs);
            goto label_2700_internal;
            return;
        }
    }
    if (key == ""s || cs == 1 || cs == 6 || cs == 2 || cs == 7)
    {
        if (cs != -1)
        {
            key = listn(1, cs);
            goto label_2700_internal;
            return;
        }
    }
    goto label_2699_internal;
label_2700_internal:
    if (cs == 0 || key == key_northeast)
    {
        cs = -1;
        snd(5);
        --page;
        screenupdate = -1;
        update_screen();
        goto label_2698;
    }
    if (cs == 8 || key == key_northwest)
    {
        cs = -1;
        snd(5);
        ++page;
        screenupdate = -1;
        update_screen();
        goto label_2698;
    }
    quickpage = page;
    cs = 0;
    update_screen();
    quickkeywait = 1;
    return;
}

void show_ex_help()
{
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_help.bmp", 1);
    gsel(0);
    page = 0;
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"exhelp.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, u8"%"s + ghelp + u8","s + lang(u8"JP"s, u8"EN"s));
    if (p == -1)
    {
        dialog(
            u8"help index not found %"s + ghelp + u8","s
            + lang(u8"JP"s, u8"EN"s));
        return;
    }
    buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    notedel(0);
    if (noteinfo() == 0)
    {
        return;
    }
    snd(53);
    while (1)
    {
        gmode(2);
        dx = 480;
        dy = 175;
        window2((windoww - dx) / 2 + inf_screenx, winposy(dy), dx, dy, 4, 0);
        wx = (windoww - dx) / 2 + inf_screenx;
        wy = winposy(dy);
        window2(
            (windoww - 325) / 2 + inf_screenx, winposy(dy) + 6, 325, 32, 0, 1);
        pos(wx + 5, wy + 4);
        gcopy(3, 960, 96, 48, 48);
        pos(wx + dx - 55, wy + 4);
        gcopy(3, 960, 96, 48, 48);
        pos(wx + 10, wy + 42);
        gcopy(3, 960, 144, 96, 120);
        font(16 - en * 2, snail::font_t::style_t::bold);
        bmes(
            i18n::s.get("core.locale.ui.exhelp.title"),
            wx + 142,
            wy + 13,
            {255, 245, 235},
            {80, 60, 50});
        tx = wx + 120;
        ty = wy + 55;
        font(15 - en * 2);
        {
            int y = ty;
            int cnt = 0;
            for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
            {
                noteget(s, page);
                ++page;
                if (page > noteinfo() || s == ""s)
                {
                    break;
                }
                color(30, 30, 30);
                const auto ny = gmes(s, tx, y, 330, {30, 30, 30}, true).y;
                color(0, 0, 0);
                y = ny;
            }
        }
        gmode(2);
        redraw();
        help_halt();
        if (page >= noteinfo())
        {
            break;
        }
    }
    return;
}

void show_game_help()
{
    ui::ui_menu_game_help().show();
}

turn_result_t show_journal()
{
    ui::ui_menu_composite_message(ui::ui_menu_composite_message::index::journal)
        .show();
    return turn_result_t::pc_turn_user_error;
}

turn_result_t show_message_log()
{
    ui::ui_menu_composite_message(
        ui::ui_menu_composite_message::index::message_log)
        .show();
    return turn_result_t::pc_turn_user_error;
}

turn_result_t show_chat_history()
{
    ui::ui_menu_composite_message(
        ui::ui_menu_composite_message::index::chat_history)
        .show();
    return turn_result_t::pc_turn_user_error;
}

void load_showroom_user_info()
{
    notesel(headtemp);
    noteget(s, 1);
    username = ""s + s;
    noteget(s, 5);
    usermsg = ""s + s;
    noteget(s, 6);
    userrelation = elona::stoi(s(0));
    return;
}

int cnvjkey(const std::string& prm_1092)
{
    int p_at_m198 = 0;
    p_at_m198 = -2;
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        if (prm_1092 == jkey(cnt))
        {
            p_at_m198 = cnt;
            break;
        }
    }
    return p_at_m198 + 1;
}

turn_result_t play_scene()
{
    auto result = ui::ui_menu_scene().show();

    if (result.canceled)
    {
        return turn_result_t::pc_turn_user_error;
    }
    else
    {
        return turn_result_t::play_scene;
    }
}


static turn_result_t _show_skill_spell_menu(size_t menu_index)
{
    auto result = ui::ui_menu_composite_skills(menu_index).show();

    if (result.canceled || !result.value)
    {
        return turn_result_t::pc_turn_user_error;
    }

    if (result.value->type() == typeid(ui::ui_menu_skills_result))
    {
        efid = boost::get<ui::ui_menu_skills_result>(*result.value).effect_id;
        return do_cast_command();
    }
    else
    {
        efid = boost::get<ui::ui_menu_spells_result>(*result.value).effect_id;
        return do_use_magic();
    }
}

turn_result_t show_spell_list()
{
    return _show_skill_spell_menu(ui::ui_menu_composite_skills::index::spells);
}

turn_result_t show_skill_list()
{
    return _show_skill_spell_menu(ui::ui_menu_composite_skills::index::skills);
}


void draw_spell_power_entry(int skill_id)
{
    s = "";
    if (the_ability_db[skill_id]->sdataref1 / 1000 == 1)
    {
        p = the_ability_db[skill_id]->sdataref1 % 1000;
        const auto duration =
            calc_buff_duration(p, calcspellpower(skill_id, cc));
        const auto description =
            get_buff_description(p, calcspellpower(skill_id, cc));
        s = ""s + duration + i18n::s.get("core.locale.ui.spell.turn_counter")
            + description;
        return;
    }
    const auto damage =
        calc_skill_damage(skill_id, cc, calcspellpower(skill_id, cc));
    if (damage)
    {
        dice1 = damage->dice_x;
        dice2 = damage->dice_y;
        bonus = damage->damage_bonus;
        ele = damage->element;
        elep = damage->element_power;
        if (cc == 0)
        {
            if (trait(165) != 0)
            {
                if (ele == 50 || ele == 51 || ele == 52)
                {
                    dice2 = dice2 * 125 / 100;
                }
            }
        }
        if (dice1 != 0)
        {
            s += ""s + dice1 + u8"d"s + dice2;
            if (bonus != 0)
            {
                if (bonus > 0)
                {
                    s += u8"+"s + bonus;
                }
                else
                {
                    s += bonus;
                }
            }
        }
        else if (skill_id == 461)
        {
            s += ""s + clamp(bonus, 1, 100) + u8"%"s;
        }
        else
        {
            s += i18n::s.get("core.locale.ui.spell.power") + bonus;
        }
        s += u8" "s;
    }
    s += i18n::_(u8"ability", std::to_string(skill_id), u8"description");
    return;
}

menu_result menu_character_sheet_cycle()
{
    return {false, false, turn_result_t::none};
}

menu_result menu_character_sheet()
{
    bool returned_from_portrait = false;
    menu_result m_result = {false, false, turn_result_t::none};

    while (true)
    {
        auto result =
            ui::ui_menu_character_sheet(csctrl, returned_from_portrait).show();
        returned_from_portrait = false;

        if (result.canceled)
        {
            if (csctrl == 0)
            {
                m_result.turn_result = turn_result_t::pc_turn_user_error;
            }
            else
            {
                m_result.succeeded = false;
            }
            return m_result;
        }

        if (*result.value == false)
        {
            break;
        }
        else
        {
            returned_from_portrait = true;
        }
    }
    m_result.succeeded = true;
    return m_result;
}

menu_result menu_equipment()
{
    menu_result m_result = {false, false, turn_result_t::none};

    auto result = ui::ui_menu_composite_character(
                      ui::ui_menu_composite_character::index::equipment)
                      .show();

    m_result.turn_result = turn_result_t::pc_turn_user_error;
    return m_result;
}

menu_result menu_materials()
{
    ui::ui_menu_composite_character(
        ui::ui_menu_composite_character::index::materials)
        .show();
    return {false, false, turn_result_t::pc_turn_user_error};
}

void set_pcc_info(int val0)
{
    rtval = -2;
    if (page == 0)
    {
        if (val0 == 0)
        {
            rtval = -2;
        }
        if (val0 == 1)
        {
            rtval(0) = 100;
            rtval(1) = 0;
            rtval(2) = cdata[cc].portrait;
        }
        if (val0 == 2)
        {
            rtval(0) = 1;
            rtval(1) = 0;
            rtval(2) = pcc(1, cc) % 1000;
            rtvaln = u8"hair"s;
        }
        if (val0 == 3)
        {
            rtval(0) = 10;
            rtval(1) = 0;
            rtval(2) = pcc(10, cc) % 1000;
            rtvaln = u8"subhair"s;
        }
        if (val0 == 4)
        {
            rtval(0) = 1;
            rtval(1) = 1;
            rtval(2) = pcc(1, cc) / 1000;
        }
        if (val0 == 5)
        {
            rtval(0) = 15;
            rtval(1) = 0;
            rtval(2) = pcc(15, cc) % 1000;
            rtvaln = u8"body"s;
        }
        if (val0 == 6)
        {
            rtval(0) = 9;
            rtval(1) = 0;
            rtval(2) = pcc(9, cc) % 1000;
            rtvaln = u8"cloth"s;
        }
        if (val0 == 7)
        {
            rtval(0) = 7;
            rtval(1) = 0;
            rtval(2) = pcc(7, cc) % 1000;
            rtvaln = u8"pants"s;
        }
        if (val0 == 8)
        {
            rtval = -1;
            rtvaln = "";
        }
        if (val0 == 9)
        {
            if (cc != 0)
            {
                rtval(0) = 101;
                rtval(1) = 0;
                rtval(2) = cdata[cc].has_own_sprite();
            }
            else
            {
                rtval(0) = 16;
                rtval(1) = 0;
                rtval(2) = pcc(16, cc) % 1000;
                rtvaln = u8"ride"s;
            }
        }
    }
    else
    {
        if (val0 == 0)
        {
            rtval(0) = 15;
            rtval(1) = 1;
            rtval(2) = pcc(15, cc) / 1000;
        }
        if (val0 == 1)
        {
            rtval(0) = 9;
            rtval(1) = 1;
            rtval(2) = pcc(9, cc) / 1000;
        }
        if (val0 == 2)
        {
            rtval(0) = 7;
            rtval(1) = 1;
            rtval(2) = pcc(7, cc) / 1000;
        }
        if (val0 == 3)
        {
            rtval(0) = 11;
            rtval(1) = 0;
            rtval(2) = pcc(11, cc) % 1000;
            rtvaln = u8"etc"s;
        }
        if (val0 == 4)
        {
            rtval(0) = 12;
            rtval(1) = 0;
            rtval(2) = pcc(12, cc) % 1000;
            rtvaln = u8"etc"s;
        }
        if (val0 == 5)
        {
            rtval(0) = 13;
            rtval(1) = 0;
            rtval(2) = pcc(13, cc) % 1000;
            rtvaln = u8"etc"s;
        }
        if (val0 == 6)
        {
            rtval(0) = 14;
            rtval(1) = 0;
            rtval(2) = pcc(14, cc) % 1000;
            rtvaln = u8"eye"s;
        }
        if (val0 == 7)
        {
            rtval = -1;
            rtvaln = "";
        }
    }
    return;
}

int change_appearance()
{
    create_pcpic(cc, false);
    page = 0;
    pagesize = 19;
    cs = 0;
    cs_bk = -1;
    ww = 380;
    wh = 340;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    snd(97);
    window_animation(wx, wy, ww, wh, 9, 7);
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
    buffer(7, 800, 112);
    boxf();
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        const auto filepath = filesystem::dir::user() / u8"graphic"
            / (u8"face"s + (cnt + 1) + u8".bmp");
        if (fs::exists(filepath))
        {
            pos(cnt * 80, 0);
            picload(filepath, 1);
        }
    }
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_mirror.bmp", 1);
    gsel(0);
    windowshadow = 1;
label_2040_internal:
    listmax = 0;
    if (page == 0)
    {
        s(0) = i18n::s.get("core.locale.ui.appearance.basic.done");
        s(1) = i18n::s.get("core.locale.ui.appearance.basic.portrait");
        s(2) = i18n::s.get("core.locale.ui.appearance.basic.hair");
        s(3) = i18n::s.get("core.locale.ui.appearance.basic.sub_hair");
        s(4) = i18n::s.get("core.locale.ui.appearance.basic.hair_color");
        s(5) = i18n::s.get("core.locale.ui.appearance.basic.body");
        s(6) = i18n::s.get("core.locale.ui.appearance.basic.cloth");
        s(7) = i18n::s.get("core.locale.ui.appearance.basic.pants");
        s(8) = i18n::s.get("core.locale.ui.appearance.basic.set_detail");
        if (cc != 0)
        {
            s(9) = i18n::s.get("core.locale.ui.appearance.basic.custom");
        }
        else
        {
            s(9) = i18n::s.get("core.locale.ui.appearance.basic.riding");
        }
        p = 9 + (cc != 0) + (cc == 0) * (gdata_mount != 0);
    }
    else
    {
        s(0) = i18n::s.get("core.locale.ui.appearance.detail.body_color");
        s(1) = i18n::s.get("core.locale.ui.appearance.detail.cloth_color");
        s(2) = i18n::s.get("core.locale.ui.appearance.detail.pants_color");
        s(3) = i18n::s.get("core.locale.ui.appearance.detail.etc_1");
        s(4) = i18n::s.get("core.locale.ui.appearance.detail.etc_2");
        s(5) = i18n::s.get("core.locale.ui.appearance.detail.etc_3");
        s(6) = i18n::s.get("core.locale.ui.appearance.detail.eyes");
        s(7) = i18n::s.get("core.locale.ui.appearance.detail.set_basic");
        p = 8;
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        list(0, cnt) = cnt;
        listn(0, cnt) = s(cnt);
        ++listmax;
    }
    keyrange = 0;
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_enter;
        ++keyrange;
    }
label_2041_internal:
    pagesize = 0;
    s(0) = i18n::s.get("core.locale.ui.appearance.basic.title");
    s(1) = i18n::s.get("core.locale.ui.appearance.hint");
    display_window(
        (windoww - 380) / 2 + inf_screenx, winposy(340) - 12, 380, 340);
    pagesize = listmax;
    display_topic(
        i18n::s.get("core.locale.ui.appearance.basic.category"),
        wx + 34,
        wy + 36);
    pos(wx + ww - 40, wy);
    gcopy(3, 960, 96, 48, 120);
    ++i;
    if (i % 100 < 45)
    {
        f = i % 16;
    }
    else
    {
        ++f;
    }
    window2(wx + 234, wy + 71, 88, 120, 1, 1);
    if (cs == 1 && page == 0)
    {
        if (cdata[cc].portrait >= 0)
        {
            p = cdata[cc].sex * 64 + cdata[cc].portrait;
            pos(wx + 238, wy + 75);
            gcopy(4, p % 16 * 48, p / 16 * 72, 48, 72, 80, 112);
        }
        else if (cdata[cc].portrait != -1)
        {
            pos(wx + 238, wy + 75);
            gcopy(
                7,
                std::abs((cdata[cc].portrait + 2)) * 80,
                0,
                80,
                112,
                80,
                112);
        }
    }
    else if (cdata[cc].has_own_sprite() == 1)
    {
        pos(wx + 280, wy + 130);
        gmode(2);
        gcopy_c(20 + cc, f / 4 % 4 * 32, f / 16 % 4 * 48, 32, 48, 48, 80);
    }
    else
    {
        draw_chara(cdata[cc], wx + 280, wy + 130);
    }
    gmode(2);
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        if (p >= listmax)
        {
            break;
        }
        set_pcc_info(cnt);
        s = listn(0, p);
        if (rtval >= 0)
        {
            if (rtval(2) >= 0)
            {
                s += u8" "s + rtval(2);
            }
            else if (rtval(2) == -1)
            {
                s += u8" N/A"s;
            }
            else
            {
                s += u8" u"s + (std::abs(rtval(2)) - 1);
            }
        }
        cs_list(cs == cnt, s, wx + 60, wy + 66 + cnt * 21 - 1, 0);
        if (rtval != -2)
        {
            pos(wx + 30, wy + 66 + cnt * 21 - 5);
            gcopy(3, 312, 336, 24, 24);
            pos(wx + 175, wy + 66 + cnt * 21 - 5);
            gcopy(3, 336, 336, 24, 24);
        }
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    set_pcc_info(cs);
    p = 0;
    if (rtval == -2)
    {
        if (key == key_enter)
        {
            create_pcpic(cc, true);
            return 1;
        }
        if (key == key_pageup || key == key_pagedown)
        {
            key = ""s;
        }
    }
    else if (key == key_enter)
    {
        key = key_pageup;
    }
    if (rtval == -1)
    {
        if (key == key_pageup || key == key_pagedown)
        {
            snd(5);
            if (page == 0)
            {
                page = 1;
            }
            else
            {
                page = 0;
                cs = 8;
            }
            goto label_2040_internal;
        }
    }
    if (key == key_pageup)
    {
        snd(5);
        if (rtval == 100)
        {
            if (cdata[cc].portrait < 31)
            {
                ++cdata[cc].portrait;
            }
            goto label_2041_internal;
        }
        if (rtval == 101)
        {
            cdata[cc].has_own_sprite() = true;
            goto label_2041_internal;
        }
        if (rtval(1) == 0)
        {
            if (fs::exists(
                    filesystem::dir::graphic()
                    / (u8"pcc_"s + rtvaln + u8"_" + (pcc(rtval, cc) % 1000 + 1)
                       + u8".bmp")))
            {
                ++pcc(rtval, cc);
                p = 1;
            }
        }
        else if (pcc(rtval, cc) / 1000 < 21)
        {
            pcc(rtval, cc) += 1000;
            p = 1;
        }
    }
    if (key == key_pagedown)
    {
        snd(5);
        if (rtval == 100)
        {
            if (cdata[cc].portrait > -10)
            {
                --cdata[cc].portrait;
            }
            goto label_2041_internal;
        }
        if (rtval == 101)
        {
            cdata[cc].has_own_sprite() = false;
            goto label_2041_internal;
        }
        if (rtval(1) == 0)
        {
            if ((pcc(rtval, cc) % 1000 == 1 && rtval != 15)
                || fs::exists(
                       filesystem::dir::graphic()
                       / (u8"pcc_"s + rtvaln + u8"_"s
                          + (pcc(rtval, cc) % 1000 - 1) + u8".bmp"s)))
            {
                --pcc(rtval, cc);
                p = 1;
            }
        }
        else if (pcc(rtval, cc) / 1000 > 0)
        {
            pcc(rtval, cc) -= 1000;
            p = 1;
        }
    }
    create_pcpic(cc, false);
    if (key == key_cancel)
    {
        create_pcpic(cc, true);
        return 0;
    }
    if (mode == 1)
    {
        if (getkey(snail::key::f1))
        {
            return -1;
        }
    }
    goto label_2041_internal;
}

int change_appearance_equipment()
{
    create_pcpic(cc, true);
    snd(26);
    page = 0;
    pagesize = 18;
    cs = 0;
    cs_bk = -1;
    windowshadow = 1;
    listmax = 0;
    s(0) = i18n::s.get("core.locale.ui.appearance.equipment.done");
    s(1) = i18n::s.get("core.locale.ui.appearance.equipment.chest");
    s(2) = i18n::s.get("core.locale.ui.appearance.equipment.leg");
    s(3) = i18n::s.get("core.locale.ui.appearance.equipment.belt");
    s(4) = i18n::s.get("core.locale.ui.appearance.equipment.glove");
    s(5) = i18n::s.get("core.locale.ui.appearance.equipment.mantle");
    p = 6;
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        list(0, cnt) = cnt;
        listn(0, cnt) = s(cnt);
        ++listmax;
    }
    keyrange = 0;
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_enter;
        ++keyrange;
    }

    while (1)
    {
        pagesize = 0;
        s(0) = i18n::s.get("core.locale.ui.appearance.equipment.title");
        s(1) = i18n::s.get("core.locale.ui.appearance.hint");
        display_window(
            (windoww - 360) / 2 + inf_screenx, winposy(289) - 12, 360, 289);
        s = i18n::s.get("core.locale.ui.appearance.equipment.part");
        pagesize = listmax;
        display_topic(s, wx + 34, wy + 36);
        ++i;
        if (i % 100 < 45)
        {
            f = i % 16;
        }
        else
        {
            ++f;
        }
        window2(wx + 234, wy + 60, 88, 120, 1, 1);
        pos(wx + 280, wy + 120);
        gmode(2);
        gcopy_c(20 + cc, f / 4 % 4 * 32, f / 16 % 4 * 48, 32, 48, 48, 80);
        gmode(2);
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            if (p >= listmax)
            {
                break;
            }
            s = listn(0, p);
            if (cnt != 0)
            {
                if (pcc(20 + cnt - 1, cc) == 0)
                {
                    s += u8"On"s;
                }
                else
                {
                    s += u8"Off"s;
                }
                pos(wx + 30, wy + 66 + cnt * 21 - 5);
                gcopy(3, 312, 336, 24, 24);
                pos(wx + 175, wy + 66 + cnt * 21 - 5);
                gcopy(3, 336, 336, 24, 24);
            }
            cs_list(cs == cnt, s, wx + 60, wy + 66 + cnt * 21 - 1, 0);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        if (cs != 0)
        {
            if (key == key_enter)
            {
                key = key_pageup;
            }
            if (key == key_pageup || key == key_pagedown)
            {
                if (pcc(20 + cs - 1, cc) == 0)
                {
                    pcc(20 + cs - 1, cc) = 1;
                }
                else
                {
                    pcc(20 + cs - 1, cc) = 0;
                }
                create_pcpic(cc, true);
                snd(5);
            }
        }
        if ((cs == 0 && key == key_enter) || key == key_cancel)
        {
            snd(20);
            create_pcpic(cc, true);
            return 1;
        }
    }
}

void append_accuracy_info(int val0)
{
    p(1) = 0;
    p(2) = 0;
    attackskill = 106;
    ammo = -1;
    attacknum = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 10)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            continue;
        }
        cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        if (inv[cw].dice_x > 0)
        {
            attackskill = inv[cw].skill;
            ++p(1);
            s(1) =
                i18n::s.get("core.locale.ui.chara_sheet.damage.melee") + p(1);
            ++attacknum;
            show_weapon_dice(val0);
        }
    }
    if (attackskill == 106)
    {
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.damage.unarmed");
        show_weapon_dice(val0);
    }
    attacknum = 0;
    int stat = can_do_ranged_attack();
    if (stat == 1)
    {
        s(1) = i18n::s.get("core.locale.ui.chara_sheet.damage.dist");
        show_weapon_dice(val0);
    }
    return;
}

void show_weapon_dice(int val0)
{
    tc = cc;
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    color(20, 10, 0);
    if (val0 == 0)
    {
        pos(wx + 590, wy + 281 + p(2) * 16);
        mes(i18n::s.get("core.locale.ui.chara_sheet.damage.hit"));
        pos(wx + 417, wy + 281 + p(2) * 16);
        mes(s(1));
    }
    color(0, 0, 0);
    attackrange = 0;
    if (the_item_db[inv[cw].id]->category == 24000) // TODO coupling
    {
        attackrange = 1;
    }
    attackvar = 0;
    int tohit = calc_accuracy(false);
    dmg = calcattackdmg(1);
    font(14 - en * 2);
    s(2) = ""s + dmgmulti;
    s = ""s + tohit + u8"%"s;
    if (val0 == 0)
    {
        pos(wx + 625 - en * 8, wy + 279 + p(2) * 16);
        mes(s);
    }
    else
    {
        s(3) = s;
    }
    s = ""s + dice1 + u8"d"s + dice2 + cnvfix(dmgfix) + u8" x"s
        + strmid(
              s(2),
              0,
              3 + (elona::stoi(s(2)) >= 10) + (elona::stoi(s(2)) >= 100));
    if (val0 == 0)
    {
        pos(wx + 460 + en * 8, wy + 279 + p(2) * 16);
        mes(s);
    }
    else
    {
        noteadd(s(1) + "   : " + fixtxt(s(3), 12) + " " + fixtxt(s, 20));
    }
    ++p(2);
    return;
}

menu_result menu_feats()
{
    ui::ui_menu_composite_character(
        ui::ui_menu_composite_character::index::feats)
        .show();

    update_screen();
    return {false, false, turn_result_t::pc_turn_user_error};
}

menu_result menu_feats_character_making()
{
    menu_result m_result = {false, false, turn_result_t::none};

    auto result =
        ui::ui_menu_feats(true, ui::ui_menu_feats::operation::character_making)
            .show();

    if (result.canceled)
    {
        m_result.succeeded = false;
    }
    else if (result.value && *result.value == false)
    {
        m_result.pressed_f1 = true;
    }
    else if (result.value && *result.value == true)
    {
        m_result.succeeded = true;
    }

    return m_result;
}

static turn_result_t _visit_quest_giver(int quest_index)
{
    // TODO move the below somewhere else to decouple quest_teleport
    tc = qdata(0, quest_index);
    rq = quest_index;
    client = tc;
    efid = 619;
    magic();
    tc = client;
    if (cdata.player().state() == character::state_t::alive)
    {
        quest_teleport = true;
        talk_to_npc();
    }
    if (chatteleport == 1)
    {
        chatteleport = 0;
        return turn_result_t::exit_map;
    }
    return turn_result_t::turn_end;
}

turn_result_t show_quest_board()
{
    if (config::instance().extrahelp)
    {
        if (gdata(204) == 0)
        {
            if (mode == 0)
            {
                if (cdata.player().continuous_action_turn == 0)
                {
                    gdata(204) = 1;
                    ghelp = 4;
                    show_ex_help();
                    screenupdate = -1;
                    update_screen();
                }
            }
        }
    }

    auto result = ui::ui_menu_quest_board().show();

    if (result.canceled)
    {
        return turn_result_t::turn_end;
    }

    int quest_index = *result.value;
    return _visit_quest_giver(quest_index);
}

int show_hire_menu(hire_operation operation)
{
    auto result = ui::ui_menu_hire(operation).show();

    if (result.canceled)
    {
        return -1;
    }
    else
    {
        return *result.value;
    }
}

int show_spell_writer_menu()
{
    ui::ui_menu_spell_writer().show();

    return -1;
}

void list_adventurers()
{
    ui::ui_menu_adventurers().show();
}

int select_alias(int val0)
{
    auto result = ui::ui_menu_alias(val0).show();

    if (result.canceled)
    {
        return 0;
    }

    if (val0 == 3)
    {
        return result.value->seed;
    }
    else
    {
        cmaka = result.value->alias;
        return 1;
    }
}

void show_city_chart()
{
label_22711:
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    snd(99);
    curmenu = 0;
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_politics.bmp", 1);
    gsel(0);
    fillbg(3, 960, 96, 128, 128);
    render_hud();
    drawmenu(3);
    windowshadow = 1;
    city = adata(28, gdata_current_map);
    lv = 0;
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_2272_internal:
    s(0) = i18n::s.get("core.locale.ui.city_chart.title");
    s(1) = strhint3b;
    display_window((windoww - 580) / 2 + inf_screenx, winposy(400), 580, 400);
    keyrange = 0;
    int j0 = 0;
    int n = 0;
    cs_listbk();
    if (adata(28, gdata_current_map) == 0 || gdata_current_dungeon_level != 1)
    {
        font(14 - en * 2);
        pos(wx + 40, wy + 50);
        mes(i18n::s.get("core.locale.ui.city_chart.no_economy"));
    }
    else
    {
        display_topic(
            i18n::s.get(
                "core.locale.ui.city_chart.chart",
                mapname(adata(16, gdata_current_map))),
            wx + 40,
            wy + 34);
        for (int cnt = 0;; ++cnt)
        {
            if (pochart(j0, n, lv) == 0 || cnt == 0)
            {
                if (cnt != 0)
                {
                    ++n;
                }
                j0 = 0;
                i = 0;
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    if (pochart(cnt, n, lv) != 0)
                    {
                        ++i;
                    }
                }
                if (i == 0)
                {
                    break;
                }
                y = wy + 70 + n * 55;
            }
            x = wx + (ww - 70) / (i + 1) * (j0 + 1);
            pos(x - 26, y - 3);
            gcopy(3, 960, 288, 144, 24);
            p = pochart(j0, n, lv);
            key_list(cnt) = key_select(cnt);
            ++keyrange;
            display_key(x - 30, y + 21, cnt);
            font(12 + sizefix - en * 2);
            bmes(cnven(popostname(p)), x - 2, y + jp * 2);
            font(14 - en * 2);
            if (podata(0 + cnt, city) == 0)
            {
                s = i18n::s.get("core.locale.ui.city_chart.empty");
            }
            cs_list(cs == cnt, s, x - 2, y + 20);
            ++j0;
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (p != -1)
    {
        return;
    }
    if (menucycle == 1)
    {
        if (key == key_next || key == key_prev)
        {
            p = curmenu;
            if (key == key_next)
            {
                ++curmenu;
                if (curmenu > 2)
                {
                    curmenu = 0;
                }
            }
            if (key == key_prev)
            {
                --curmenu;
                if (curmenu < 0)
                {
                    curmenu = 2;
                }
            }
            key = "";
            if (p != curmenu)
            {
                screenupdate = -1;
                update_screen();
                if (curmenu == 0)
                {
                    goto label_22711;
                }
                if (curmenu == 1)
                {
                    show_economy_window();
                    return;
                }
                if (curmenu == 2)
                {
                    show_politics_window();
                    return;
                }
            }
        }
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_22711;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_22711;
        }
    }
    if (key == key_cancel)
    {
        update_screen();
        return;
    }
    goto label_2272_internal;
}

void showeconomy(
    int prm_1086,
    int prm_1087,
    const std::string& prm_1088,
    int prm_1089,
    int prm_1090)
{
    int p_at_m195 = 0;
    pos(prm_1086, prm_1087);
    mes(prm_1088);
    pos(prm_1086 + 130, prm_1087);
    mes(""s + prm_1089);
    p_at_m195 = prm_1089 - prm_1090;
    if (p_at_m195 >= 0)
    {
        color(0, 0, 150);
    }
    else
    {
        color(150, 0, 0);
    }
    pos(prm_1086 + 130 + ginfo(14) + 12, prm_1087);
    mes(u8"("s + p_at_m195 + u8")"s);
    color(0, 0, 0);
    return;
}

void show_economy_window()
{
    curmenu = 1;
    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 1;
    listmax = 2;
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_politics.bmp", 1);
    gsel(0);
    fillbg(3, 960, 96, 128, 128);
    render_hud();
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"ie_scroll.bmp");
    gsel(0);
    windowshadow = 1;
    snd(92);
    drawmenu(3);
    city = 1;
    ww = 540;
    wh = 440;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
label_2277_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_2278_internal:
    s = strhint2 + strhint3b;
    showscroll(s, wx, wy, ww, wh);
    font(14 - en * 2);
    if (adata(28, gdata_current_map) == 0 || gdata_current_dungeon_level != 1)
    {
        pos(wx + 40, wy + 60);
        mes(i18n::s.get("core.locale.ui.city_chart.no_economy"));
    }
    else
    {
        if (page == 0)
        {
            display_topic(
                i18n::s.get("core.locale.ui.economy.information"),
                wx + 65,
                wy + 50);
            display_topic(
                i18n::s.get("core.locale.ui.economy.finance"),
                wx + 65,
                wy + 150);
            font(14 - en * 2);
            x = wx + 50;
            y = wy + 80;
            showeconomy(
                x,
                y,
                i18n::s.get("core.locale.ui.economy.population"),
                podata(100, city),
                podata(101, city));
            x = wx + 50;
            y = wy + 180;
            showeconomy(
                x,
                y,
                i18n::s.get("core.locale.ui.economy.basic_tax") + u8" ("s
                    + gdata(820) + u8"%)"s,
                podata(102, city),
                podata(103, city));
            showeconomy(
                x,
                y + 16,
                i18n::s.get("core.locale.ui.economy.excise_tax") + u8" ("s
                    + podata(150, city) + u8"%)"s,
                podata(104, city),
                podata(105, city));
        }
        if (page == 1)
        {
            display_topic(
                i18n::s.get("core.locale.ui.economy.population_detail"),
                wx + 65,
                wy + 50);
            display_topic(
                i18n::s.get("core.locale.ui.economy.finance_detail"),
                wx + 65,
                wy + 200);
            font(14 - en * 2);
        }
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    if (menucycle == 1)
    {
        if (key == key_next || key == key_prev)
        {
            p = curmenu;
            if (key == key_next)
            {
                ++curmenu;
                if (curmenu > 2)
                {
                    curmenu = 0;
                }
            }
            if (key == key_prev)
            {
                --curmenu;
                if (curmenu < 0)
                {
                    curmenu = 2;
                }
            }
            key = "";
            if (p != curmenu)
            {
                screenupdate = -1;
                update_screen();
                if (curmenu == 0)
                {
                    show_city_chart();
                    return;
                }
                if (curmenu == 1)
                {
                    show_economy_window();
                    return;
                }
                if (curmenu == 2)
                {
                    show_politics_window();
                    return;
                }
            }
        }
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_2277_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_2277_internal;
        }
    }
    if (key != ""s)
    {
        update_screen();
        return;
    }
    goto label_2278_internal;
}

void show_politics_window()
{
    // TODO: untranslated
    listmax = 0;
    page = 0;
    pagesize = 13;
    cs = 0;
    cs_bk = -1;
    curmenu = 2;
    city = adata(28, gdata_current_map);
    list(0, listmax) = 1;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.politics.name", mapname(gdata(815)));
    ++listmax;
    if (mdata_map_type != mdata_t::map_type_t::town)
    {
        goto label_2281_internal;
    }
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.politics.taxes", podata(150, city));
    ++listmax;
    p = rnd(1000);
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.politics.well_pollution", p(0));
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.locale.ui.politics.lawless");
    ++listmax;
label_2281_internal:
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_politics.bmp", 1);
    gsel(0);
    fillbg(3, 960, 96, 128, 128);
    render_hud();
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"ie_scroll.bmp");
    gsel(0);
    windowshadow = 1;
    snd(92);
    drawmenu(3);
    city = 1;
    ww = 480;
    wh = 400;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
label_2282_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_2283_internal:
    s = strhint2 + strhint3b;
    showscroll(s, wx, wy, ww, wh);
    display_topic(i18n::s.get("core.locale.ui.politics.law"), wx + 65, wy + 45);
    font(12 + sizefix - en * 2);
    pos(wx + 185, wy + 52);
    mes(i18n::s.get("core.locale.ui.politics.global"));
    if (mdata_map_type == mdata_t::map_type_t::town)
    {
        pos(wx + 285, wy + 52);
        mes(i18n::s.get(
            "core.locale.ui.politics.law_of", mapname(gdata_current_map)));
    }
    pos(wx + 155, wy + 46);
    gmode(2);
    gcopy(3, 312, 360, 24, 24);
    pos(wx + 255, wy + 46);
    gmode(2);
    gcopy(3, 288, 360, 24, 24);
    font(14 - en * 2);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 74, wy + 76 + cnt * 19, 365, 18, {12, 14, 16, 16});
        }
        display_key(wx + 72, wy + 76 + cnt * 19 - 2, cnt);
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        s = listn(0, p);
        cs_list(cs == cnt, s, wx + 100, wy + 76 + cnt * 19 - 1, 0, 0);
        pos(wx + 42, wy + 68 + cnt * 19 + 2);
        gmode(2);
        gcopy(3, 288 + list(0, p) * 24, 360, 24, 24);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (menucycle == 1)
    {
        if (key == key_next || key == key_prev)
        {
            p = curmenu;
            if (key == key_next)
            {
                ++curmenu;
                if (curmenu > 2)
                {
                    curmenu = 0;
                }
            }
            if (key == key_prev)
            {
                --curmenu;
                if (curmenu < 0)
                {
                    curmenu = 2;
                }
            }
            key = "";
            if (p != curmenu)
            {
                screenupdate = -1;
                update_screen();
                if (curmenu == 0)
                {
                    show_city_chart();
                    return;
                }
                if (curmenu == 1)
                {
                    show_economy_window();
                    return;
                }
                if (curmenu == 2)
                {
                    show_politics_window();
                    return;
                }
            }
        }
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_2282_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_2282_internal;
        }
    }
    if (key == key_cancel)
    {
        update_screen();
        return;
    }
    goto label_2283_internal;
}

void begin_to_believe_god(int god_id)
{
    bool already_believing = !cdata.player().god_id.empty();

    auto result = ui::ui_menu_god(god_id, already_believing).show();

    if (!result.canceled && result.value)
    {
        rtval = *result.value;
        god_proc_switching_penalty();
    }
}


void house_board_update_screen()
{
    screenupdate = -1;
    update_screen();
}



int ctrl_ally(ctrl_ally_operation operation)
{
    auto result = ui::ui_menu_ctrl_ally(operation).show();

    if (!result.canceled && result.value)
    {
        return *result.value;
    }
    else
    {
        return -1;
    }
}



void screen_analyze_self()
{
    // TODO: untranslated
    if (rc < 0)
    {
        rc = tc;
        if (rc < 0)
        {
            rc = 0;
        }
    }
    listmax = 0;
    page = 0;
    pagesize = 14;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    snd(26);
    buff = "";
    notesel(buff);
    chara_delete(56);
    cdata.tmp().piety_point = cdata.player().piety_point;
    cdata.tmp().god_id = cdata.player().god_id;
    for (int cnt = 0; cnt < 600; ++cnt)
    {
        sdata(cnt, rc) = 1;
    }
    apply_god_blessing(56);
    if (!cdata.player().god_id.empty())
    {
        buff += u8"<title1>◆ "s
            + i18n::_(u8"god", cdata.player().god_id, u8"name")
            + u8"による能力の恩恵<def>\n"s;
        for (int cnt = 0; cnt < 600; ++cnt)
        {
            p = sdata(cnt, rc) - 1;
            cnvbonus(cnt, p);
        }
    }
    refreshmode = 1;
    chara_refresh(0);
    refreshmode = 0;
    buff += u8"\n"s;
    buff += u8"<title1>◆ 特徴と特殊状態による能力の恩恵<def>\n"s;
    listmax = noteinfo();
label_1965_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
    s(0) = lang(u8"自己の分析", u8"Analyze Self");
    s(1) = strhint2 + strhint3b;
    display_window((windoww - 400) / 2 + inf_screenx, winposy(448), 400, 448);
    s = lang(u8"分析結果", u8"Analysis Result");
    display_topic(s, wx + 28, wy + 36);
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        noteget(s, p);
        pos(wx + 54, wy + 66 + cnt * 19 + 2);
        gmes(s, wx, wy + 66 + cnt * 19 + 2, 600, {30, 30, 30}, false);
    }
    redraw();
label_1966_internal:
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    p = -1;
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1965_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1965_internal;
        }
    }
    if (key == key_cancel)
    {
        return;
    }
    goto label_1966_internal;
}

int change_npc_tone()
{
    auto result = ui::ui_menu_npc_tone().show();

    if (result.canceled)
    {
        return -1;
    }

    snd(20);
    txt(i18n::s.get(
        "core.locale.action.interact.change_tone.is_somewhat_different",
        cdata[tc]));

    if (result.value)
    {
        cdata[tc].has_custom_talk() = true;
        cdatan(4, tc) = *result.value;
    }
    else
    {
        cdata[tc].has_custom_talk() = false;
        cdatan(4, tc) = "";
    }

    return 1;
}



void show_book_window()
{
    ui::ui_menu_book(inv[ci].param1).show();
}


void item_show_description()
{
    if (ci < 0)
    {
        dialog(i18n::s.get("core.locale.item.desc.window.error"));
        return;
    }

    ui::ui_menu_item_desc(inv[ci]).show();

    returnfromidentify = 1;
}


} // namespace elona
