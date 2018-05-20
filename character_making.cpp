#include "character_making.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "class.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "macro.hpp"
#include "main_menu.hpp"
#include "menu.hpp"
#include "race.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace
{
elona_vector1<std::string> cmrace;
std::string cmclass;
elona_vector1<int> cmstats;
elona_vector1<int> cmlock;
} // namespace



namespace elona
{



main_menu_result_t character_making_select_race()
{
    cs = 0;
    cs_bk = -1;
    pagesize = 16;
    page = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"やあ、待っていたよ。早速旅の支度をしようか。"s,
        u8"Welcome traveler, I've been looking for you."s);
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    listmax = 0;
    for (const auto& race : the_race_db.get_available_races(false))
    {
        listn(1, listmax) = race.get().id;
        list(0, listmax) = 0;
        ++listmax;
    }
    if (config::instance().extrarace)
    {
        for (const auto& race : the_race_db.get_available_races(true))
        {
            listn(1, listmax) = race.get().id;
            list(0, listmax) = 1;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        listn(0, cnt) = i18n::_(u8"race", listn(1, cnt), u8"name");
        if (list(0, cnt) == 1)
        {
            listn(0, cnt) = u8"(extra)"s + listn(0, cnt);
        }
    }
    windowshadow = 1;

    bool reset_page = true;
    while (1)
    {
        if (reset_page)
        {
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
            reset_page = false;
        }

        if (cs != cs_bk)
        {
            s(0) = lang(u8"種族の選択"s, u8"Race Selection"s);
            s(1) = strhint3b;
            display_window(
                (windoww - 680) / 2 + inf_screenx,
                winposy(500, 1) + 20,
                680,
                500);
            ++cmbg;
            x = ww / 5 * 2;
            y = wh - 80;
            gmode(4, 180, 300, 50);
            pos(wx + ww / 4, wy + wh / 2);
            grotate(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
            gmode(2);
            display_topic(
                lang(u8"選択できる種族"s, u8"Race"s), wx + 28, wy + 30);
            display_topic(
                lang(u8"種族の説明"s, u8"Detail"s), wx + 188, wy + 30);
            font(14 - en * 2);
            for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
            {
                p = page * pagesize + cnt;
                if (p >= listmax)
                {
                    break;
                }
                key_list(cnt) = key_select(cnt);
                keyrange = cnt + 1;
                display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
                cs_list(
                    cs == cnt, listn(0, p), wx + 64, wy + 66 + cnt * 19 - 1);
            }
            cs_bk = cs;
            pos(wx + 200, wy + 66);
            chara_delete(0);
            access_race_info(3, listn(1, page * pagesize + cs));
            access_race_info(11, listn(1, page * pagesize + cs));
            show_race_or_class_info(0, 0);
        }
        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        ELONA_GET_SELECTED_INDEX(p);
        if (p != -1)
        {
            cmrace(0) = listn(1, p);
            cmrace(1) = listn(0, p);
            access_race_info(11, cmrace);
            return main_menu_result_t::character_making_select_sex;
        }
        if (key == key_pageup)
        {
            if (pagemax != 0)
            {
                snd(1);
                ++page;
                reset_page = true;
                continue;
            }
        }
        if (key == key_pagedown)
        {
            if (pagemax != 0)
            {
                snd(1);
                --page;
                reset_page = true;
                continue;
            }
        }
        if (key == key_cancel)
        {
            return main_menu_result_t::main_title_menu;
        }
        if (getkey(snail::key::f1))
        {
            show_game_help();
            return main_menu_result_t::character_making_select_race;
        }
    }
}

main_menu_result_t character_making_select_sex(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd(102);
    }
    cs = 0;
    cs_bk = -1;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(u8"男性と女性に能力の違いはない。"s, u8"What's your gender?"s);
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    windowshadow = 1;

    while (1)
    {
        s(0) = lang(u8"性別の選択"s, u8"Gender Selection"s);
        s(1) = strhint3b;
        display_window(
            (windoww - 370) / 2 + inf_screenx, winposy(168, 1) - 20, 370, 168);
        x = ww / 2;
        y = wh - 60;
        gmode(4, 180, 300, 30);
        pos(wx + ww / 2, wy + wh / 2);
        grotate(2, 0, 0, 0, x, y);
        gmode(2);
        display_topic(lang(u8"性別の候補"s, u8"Gender"s), wx + 28, wy + 30);
        listn(0, 0) = cnven(i18n::_(u8"ui", u8"male"));
        listn(0, 1) = cnven(i18n::_(u8"ui", u8"female"));
        font(14 - en * 2);
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            key_list(cnt) = key_select(cnt);
            keyrange = cnt + 1;
            pos(wx + 38, wy + 66 + cnt * 19 - 2);
            gcopy(3, cnt * 24 + 72, 30, 24, 18);
            cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
        }
        cs_bk = cs;
        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        if (key == key_select(0))
        {
            cmsex = 0;
            return main_menu_result_t::character_making_select_class;
        }
        if (key == key_select(1))
        {
            cmsex = 1;
            return main_menu_result_t::character_making_select_class;
        }
        if (key == key_cancel)
        {
            return main_menu_result_t::main_menu_new_game;
        }
        if (getkey(snail::key::f1))
        {
            show_game_help();
            return main_menu_result_t::character_making_select_sex_looped;
        }
    }
}

main_menu_result_t character_making_select_class(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd(20);
    }
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"職業や種族は、初期の能力だけでなく、成長の方向性に影響するんだ。"s,
        u8"Your class and race determine growth rate of your skills and attributes."s);
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    listmax = 0;
    for (const auto& class_ : the_class_db.get_available_classes(false))
    {
        listn(1, listmax) = class_.get().id;
        ++listmax;
    }
    if (config::instance().extraclass)
    {
        for (const auto& class_ : the_class_db.get_available_classes(true))
        {
            listn(1, listmax) = class_.get().id;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        access_class_info(2, listn(1, cnt));
        listn(0, cnt) = classname;
    }
    windowshadow = 1;

    while (1)
    {
        if (cs != cs_bk)
        {
            s(0) = lang(u8"職業の選択"s, u8"Class Selection"s);
            s(1) = strhint3b;
            display_window(
                (windoww - 680) / 2 + inf_screenx,
                winposy(500, 1) + 20,
                680,
                500);
            ++cmbg;
            x = ww / 5 * 2;
            y = wh - 80;
            gmode(4, 180, 300, 50);
            pos(wx + ww / 4, wy + wh / 2);
            grotate(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
            gmode(2);
            display_topic(
                lang(u8"選択できる職業"s, u8"Class"s), wx + 28, wy + 30);
            display_topic(
                lang(u8"職業の説明"s, u8"Detail"s), wx + 188, wy + 30);
            font(14 - en * 2);
            for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
            {
                key_list(cnt) = key_select(cnt);
                keyrange = cnt + 1;
                display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
                if (jp)
                {
                    s = listn(0, cnt);
                }
                else
                {
                    s = cnven(listn(1, cnt));
                }
                cs_list(cs == cnt, s, wx + 64, wy + 66 + cnt * 19 - 1);
            }
            cs_bk = cs;
            pos(wx + 200, wy + 66);
            chara_delete(0);
            access_class_info(3, listn(1, cs));
            access_class_info(11, listn(1, cs));
            show_race_or_class_info(0, 1);
            redraw();
        }
        await(config::instance().wait1);
        key_check();
        cursor_check();
        ELONA_GET_SELECTED_INDEX(p);
        if (p != -1)
        {
            cmclass = listn(1, p);
            return main_menu_result_t::character_making_role_attributes;
        }
        if (key == key_cancel)
        {
            return main_menu_result_t::character_making_select_sex_looped;
        }
        if (getkey(snail::key::f1))
        {
            show_game_help();
            return main_menu_result_t::character_making_select_sex_looped;
        }
    }
}



main_menu_result_t character_making_role_attributes(bool advanced_to_next_menu)
{
    bool minimum{};
    if (advanced_to_next_menu)
    {
        snd(101);
        DIM2(cmlock, 10);
        cmlock(8) = 2;
    }

    bool init = true;
    while (1)
    {
        if (init)
        {
            cs = 0;
            cs_bk = -1;
            pagesize = 0;
            gmode(0);
            pos(0, 0);
            gcopy(4, 0, 0, windoww, windowh);
            gmode(2);
            s = lang(
                u8"死にたくないなら、ある程度の能力は必要だね。"s,
                u8"You should prepare well, if you want to survive long enough in Irva."s);
            draw_caption();
            font(13 - en * 2, snail::font_t::style_t::bold);
            pos(20, windowh - 20);
            mes(u8"Press F1 to show help."s);
            if (geneuse != ""s)
            {
                pos(20, windowh - 36);
                mes(u8"Gene from "s + geneuse);
            }
            chara_delete(0);
            access_race_info(3, cmrace);
            access_class_info(3, cmclass);
            cdata[rc].level = 1;
            for (int cnt = 10; cnt < 18; ++cnt)
            {
                if (cmlock(cnt - 10) == 0)
                {
                    if (minimum)
                    {
                        sdata.get(cnt, rc).original_level -=
                            sdata.get(cnt, rc).original_level / 2;
                    }
                    else
                    {
                        sdata.get(cnt, rc).original_level -=
                            rnd(sdata.get(cnt, rc).original_level / 2 + 1);
                    }
                    cmstats(cnt - 10) =
                        sdata.get(cnt, rc).original_level * 1000000
                        + sdata.get(cnt, rc).experience * 1000
                        + sdata.get(cnt, rc).potential;
                }
            }
            minimum = false;
            listmax = 0;
            list(0, 0) = 0;
            listn(0, 0) = lang(u8"リロール"s, u8"Reroll"s);
            ++listmax;
            list(0, 1) = 0;
            listn(0, 1) = lang(u8"決定"s, u8"Proceed"s);
            ++listmax;
            for (int cnt = 10; cnt < 18; ++cnt)
            {
                list(0, listmax) = cmstats(cnt - 10);
                listn(0, listmax) =
                    i18n::_(u8"ability", std::to_string(cnt), u8"name");
                ++listmax;
            }
            windowshadow = 1;
            init = false;
        }
        s(0) = lang(u8"能力のロール"s, u8"Attb Reroll"s);
        s(1) =
            strhint3b + key_mode2 + lang(u8" [最低値ロール]", u8" [Min Roll]");
        display_window(
            (windoww - 360) / 2 + inf_screenx, winposy(352, 1) - 20, 360, 352);
        x = 150;
        y = 240;
        gmode(4, 180, 300, 30);
        pos(wx + 85, wy + wh / 2);
        grotate(2, 0, 0, 0, x, y);
        gmode(2);
        display_topic(lang(u8"能力"s, u8"Attributes"s), wx + 28, wy + 30);
        font(12 + sizefix - en * 2);
        pos(wx + 175, wy + 52);
        mes(lang(
            u8"ロックされた能力は\n変化しません"s,
            u8"Locked items will\nnot change."s));
        font(13 - en * 2, snail::font_t::style_t::bold);
        pos(wx + 180, wy + 84);
        mes(lang(u8"残りロック: "s, u8"Locks left: "s) + cmlock(8));
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            key_list(cnt) = key_select(cnt);
            keyrange = cnt + 1;
            pos(wx + 38, wy + 66 + cnt * 23 - 2);
            gcopy(3, cnt * 24 + 72, 30, 24, 18);
            font(14 - en * 2);
            cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 23 - 1);
            font(15 - en * 2, snail::font_t::style_t::bold);
            if (cnt >= 2)
            {
                pos(wx + 198, wy + 76 + cnt * 23);
                gmode(2, inf_tiles, inf_tiles);
                grotate(1, (cnt - 2) * inf_tiles, 672, 0, inf_tiles, inf_tiles);
                pos(wx + 210, wy + 66 + cnt * 23);
                mes(""s + list(0, cnt) / 1000000);
                if (cmlock(cnt - 2) == 1)
                {
                    font(12 - en * 2, snail::font_t::style_t::bold);
                    pos(wx + 240, wy + 66 + cnt * 23 + 2);
                    color(20, 20, 140);
                    mes(u8"Locked!"s);
                    color(0, 0, 0);
                }
            }
        }
        cs_bk = cs;
        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        ELONA_GET_SELECTED_INDEX_THIS_PAGE(p);
        if (p != -1)
        {
            if (p == 0)
            {
                snd(103);
                init = true;
                continue;
            }
            if (p == 1)
            {
                return main_menu_result_t::
                    character_making_select_feats_and_alias;
            }
            if (cmlock(p - 2) != 0)
            {
                ++cmlock(8);
                cmlock(p - 2) = 0;
            }
            else if (cmlock(8) > 0)
            {
                cmlock(p - 2) = 1;
                --cmlock(8);
            }
            snd(20);
        }
        if (key == key_mode2)
        {
            minimum = true;
            snd(103);
            init = true;
            continue;
        }
        if (key == key_cancel)
        {
            return main_menu_result_t::character_making_select_class_looped;
        }
        if (getkey(snail::key::f1))
        {
            show_game_help();
            return main_menu_result_t::character_making_role_attributes_looped;
        }
    }
}

main_menu_result_t character_making_select_feats_and_alias(
    bool is_choosing_feat)
{
    if (is_choosing_feat)
    {
        gdata_acquirable_feat_count = 3;
        DIM2(trait, 500);
        DIM2(spact, 500);
        gain_race_feat();
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
        s = lang(
            u8"フィートとは、君の持っている有益な特徴だ。3つまで選べるよ。"s,
            u8"Choose your feats wisely."s);
        draw_caption();
        font(13 - en * 2, snail::font_t::style_t::bold);
        pos(20, windowh - 20);
        mes(u8"Press F1 to show help."s);
        if (geneuse != ""s)
        {
            pos(20, windowh - 36);
            mes(u8"Gene from "s + geneuse);
        }
        menu_result result = menu_feats();
        clear_background_in_character_making();
        if (result.pressed_f1)
        {
            return main_menu_result_t::character_making_select_feats_and_alias;
        }
        if (!result.succeeded)
        {
            return main_menu_result_t::character_making_role_attributes_looped;
        }
    }
    pagemax = 0;
    page = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"有名になると、名前とは別の通り名で呼ばれることがあるらしい。"s,
        u8"Choose your Alias."s);
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    windowshadow = 1;
    cs = 0;
    cs_bk = -1;
    list(0, 0) = -1;

    while (1)
    {
        if (cs != cs_bk)
        {
            s(0) = lang(u8"異名の選択"s, u8"Alias Selection"s);
            s(1) = strhint3b;
            display_window(
                (windoww - 400) / 2 + inf_screenx,
                winposy(458, 1) + 20,
                400,
                458);
            ++cmbg;
            x = ww / 3 * 2;
            y = wh - 80;
            gmode(4, 180, 300, 40);
            pos(wx + ww / 2, wy + wh / 2);
            grotate(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
            gmode(2);
            display_topic(
                lang(u8"異名の候補"s, u8"Alias List"s), wx + 28, wy + 30);
            font(14 - en * 2);
            for (int cnt = 0; cnt < 17; ++cnt)
            {
                key_list(cnt) = key_select(cnt);
                keyrange = cnt + 1;
                if (list(0, 0) == -1)
                {
                    if (gdata_wizard == 1)
                    {
                        listn(0, cnt) = u8"*Debug*"s;
                    }
                    else
                    {
                        listn(0, cnt) = random_title();
                    }
                }
                if (cnt == 0)
                {
                    listn(0, cnt) = lang(u8"リロール"s, u8"Reroll"s);
                }
                pos(wx + 38, wy + 66 + cnt * 19 - 2);
                gcopy(3, cnt * 24 + 72, 30, 24, 18);
                cs_list(
                    cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
            }
            cs_bk = cs;
            list(0, 0) = 0;
        }
        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        ELONA_GET_SELECTED_INDEX_THIS_PAGE(p);
        if (p != -1)
        {
            if (key == key_select(0))
            {
                list(0, 0) = -1;
                snd(103);
                cs_bk = -1;
            }
            else
            {
                cmaka = listn(0, p);
                return main_menu_result_t::character_making_final_phase;
            }
        }
        if (key == key_cancel)
        {
            return main_menu_result_t::character_making_select_feats_and_alias;
        }
        if (getkey(snail::key::f1))
        {
            show_game_help();
            return main_menu_result_t::
                character_making_select_feats_and_alias_looped;
        }
    }
}

main_menu_result_t character_making_final_phase()
{
    int cmportrait = 0;
    std::string cmname;
    pcc(15, 0) = 0;

    while (1)
    {
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
        s = lang(
            u8"君の見た目を知っておきたいな。まあ、後からいつでも変えられるけどね。"s,
            u8"What you look like? Don't worry, you can change them later."s);
        draw_caption();
        font(13 - en * 2, snail::font_t::style_t::bold);
        pos(20, windowh - 20);
        mes(u8"Press F1 to show help."s);
        if (geneuse != ""s)
        {
            pos(20, windowh - 36);
            mes(u8"Gene from "s + geneuse);
        }
        cdata[0].has_own_sprite() = true;
        int stat = change_appearance();
        if (stat == 0)
        {
            clear_background_in_character_making();
            character_making_select_feats_and_alias(false);
        }
        if (stat != -1)
        {
            break;
        }
        show_game_help();
        clear_background_in_character_making();
    }
    clear_background_in_character_making();
    cmportrait = cdata[rc].portrait;

    while (1)
    {
        snd(94);
        while (1)
        {
            gmode(0);
            pos(0, 0);
            gcopy(4, 0, 0, windoww, windowh);
            gmode(2);
            s = lang(
                u8"決定ｷｰを押すことで、生い立ちをリロールできる。"s,
                u8"Hit the enter key to reroll your personal history."s);
            draw_caption();
            chara_delete(0);
            access_race_info(3, cmrace);
            access_class_info(3, cmclass);
            cdatan(0, rc) = u8"????"s;
            cdatan(1, rc) = cmaka;
            cdata[rc].level = 1;
            for (int cnt = 10; cnt < 18; ++cnt)
            {
                sdata.get(cnt, rc).original_level =
                    cmstats(cnt - 10) / 1'000'000;
                sdata.get(cnt, rc).experience =
                    cmstats(cnt - 10) % 1'000'000 / 1'000;
                sdata.get(cnt, rc).potential = cmstats(cnt - 10) % 1'000;
            }
            initialize_character();
            initialize_pc_character();
            cdata[rc].portrait = cmportrait;
            create_pcpic(0, true);
            mode = 1;
            csctrl = 1;
            menucycle = 0;
            {
                menu_result result = menu_character_sheet();
                if (!result.succeeded)
                {
                    nowindowanime = 1;
                    clear_background_in_character_making();
                }
                else
                {
                    break;
                }
            }
        }
        gsel(2);
        pos(0, 0);
        gmode(0);
        gcopy(0, 0, 100, windoww, windowh - 100);
        gsel(0);
        clear_background_in_character_making();
        s = lang(u8"満足できたかな？"s, u8"Are you satisfied now?"s);
        draw_caption();
        ELONA_APPEND_PROMPT(lang(u8"はい"s, u8"Yes"s), u8"a"s, ""s + promptmax);
        ELONA_APPEND_PROMPT(
            lang(u8"いいえ"s, u8"No"s), u8"b"s, ""s + promptmax);
        ELONA_APPEND_PROMPT(
            lang(u8"最初から"s, u8"Restart"s), u8"c"s, ""s + promptmax);
        rtval = show_prompt(promptx, 240, 160);
        snd(20);
        if (rtval != 1 && rtval != -1)
        {
            break;
        }
    }
    if (rtval == 2)
    {
        nowindowanime = 0;
        return main_menu_result_t::main_menu_new_game;
    }
    gmode(0);
    pos(0, 100);
    gcopy(2, 0, 0, windoww, windowh - 100);
    gmode(2);
    s = lang(
        u8"最後の質問だ。君の名前は？"s, u8"Last question. What's your name?"s);
    draw_caption();

    while (1)
    {
        inputlog = "";
        input_text_dialog(
            (windoww - 230) / 2 + inf_screenx, winposy(120), 10, false, true);
        cmname = ""s + inputlog;
        if (cmname == ""s || cmname == u8" "s)
        {
            cmname = randomname();
        }
        playerid = u8"sav_"s + cmname;
        if (range::any_of(
                filesystem::dir_entries{filesystem::dir::save(),
                                        filesystem::dir_entries::type::dir},
                [&](const auto& entry) {
                    return filesystem::to_utf8_path(entry.path().filename())
                        == playerid;
                }))
        {
            gmode(0);
            pos(0, 100);
            gcopy(2, 0, 0, windoww, windowh - 100);
            gmode(2);
            s = lang(
                u8"あいにく、その名前の冒険者はすでに存在する。"s,
                u8"Sorry, but the name is already taken."s);
            draw_caption();
        }
        else
        {
            break;
        }
    }
    snd(101);
    cdatan(0, rc) = cmname;
    cdata[0].gold = 400 + rnd(200);
    if (geneuse != ""s)
    {
        get_inheritance();
    }
    else
    {
        for (int i = 0; i < 400; ++i)
        {
            mat(i) = 0;
        }
    }
    await(250);
    mode = 5;
    return main_menu_result_t::initialize_game;
}



void show_race_or_class_info(int CNT, int val0)
{
    if (val0 == 1)
    {
        chara_preparepic(ref1, CNT);
        pos(wx + 380, wy - chipc(3, ref1) + 60);
        gcopy(5, 0, 960, inf_tiles, chipc(3, ref1));
        chara_preparepic(ref2, CNT);
        pos(wx + 350, wy - chipc(3, ref1) + 60);
        gcopy(5, 0, 960, inf_tiles, chipc(3, ref1));
        pos(wx + 460, wy + 38);
        mes(lang(u8"種族: "s, u8"Race: "s) + cmrace(1));
    }
    else
    {
        gmode(4, chipc(2, ref1), chipc(3, ref1), 40);
        chara_preparepic(ref1, CNT);
        pos(wx + 480, wy + 96);
        grotate(5, 0, 960, 0, chipc(2, ref1) * 2, chipc(3, ref1) * 2);
        chara_preparepic(ref2, CNT);
        pos(wx + 350, wy + 96);
        grotate(5, 0, 960, 0, chipc(2, ref1) * 2, chipc(3, ref1) * 2);
        gmode(2);
    }
    font(14 - en * 2);
    tx = wx + 230;
    ty = wy + 62;
    talk_conv(buff, 60 + en * 2);
    pos(tx - 20, ty);
    mes(buff);
    font(14 - en * 2);
    tx = wx + 200;
    ty = wy + 166;
    display_topic(lang(u8"能力ボーナス"s, u8"Attribute Bonus"s), tx, ty);
    ty += 34;
    font(14 - en * 2);
    if (jp)
    {
        s(0) = u8"皆無"s;
        s(1) = u8"最高"s;
        s(2) = u8"理想的"s;
        s(3) = u8"高い"s;
        s(4) = u8"やや高い"s;
        s(5) = u8"普通"s;
        s(6) = u8"少し"s;
        s(7) = u8"微々"s;
    }
    if (en)
    {
        s(0) = u8"None"s;
        s(1) = u8"Best"s;
        s(2) = u8"Great"s;
        s(3) = u8"Good"s;
        s(4) = u8"Not bad"s;
        s(5) = u8"Normal"s;
        s(6) = u8"Little"s;
        s(7) = u8"Slight"s;
    }
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            if (cnt2 == 2)
            {
                if (cnt == 2)
                {
                    break;
                }
            }
            r = cnt2 * 3 + cnt + 10;
            p = 0;
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (sdata.get(r, 0).original_level > 13)
                {
                    p = 1;
                    color(0, 0, 200);
                    break;
                }
                if (sdata.get(r, 0).original_level > 11)
                {
                    p = 2;
                    color(0, 0, 200);
                    break;
                }
                if (sdata.get(r, 0).original_level > 9)
                {
                    p = 3;
                    color(0, 0, 150);
                    break;
                }
                if (sdata.get(r, 0).original_level > 7)
                {
                    p = 4;
                    color(0, 0, 150);
                    break;
                }
                if (sdata.get(r, 0).original_level > 5)
                {
                    p = 5;
                    color(0, 0, 0);
                    break;
                }
                if (sdata.get(r, 0).original_level > 3)
                {
                    p = 6;
                    color(150, 0, 0);
                    break;
                }
                if (sdata.get(r, 0).original_level > 0)
                {
                    p = 7;
                    color(200, 0, 0);
                    break;
                }
                color(120, 120, 120);
            }
            pos(cnt * 150 + tx + 13, ty + 7);
            gmode(2, inf_tiles, inf_tiles);
            grotate(
                1, (cnt2 * 3 + cnt) * inf_tiles, 672, 0, inf_tiles, inf_tiles);
            pos(cnt * 150 + tx + 32, ty);
            mes(strmid(
                    i18n::_(u8"ability", std::to_string(r), u8"name"),
                    0,
                    jp ? 6 : 3)
                + u8": "s + s(p));
            color(0, 0, 0);
        }
        ty += 16;
    }
    ty = wy + 260;
    display_topic(lang(u8"獲得技能"s, u8"Trained Skill"s), tx, ty);
    ty += 34;
    font(14 - en * 2);
    r = 0;
    s = lang(u8"武器の専門  "s, u8"Proficient in "s);
    for (int cnt = 100; cnt < 150; ++cnt)
    {
        if (sdata.get(cnt, 0).original_level != 0)
        {
            if (r != 0)
            {
                s += u8","s;
            }
            s += i18n::_(u8"ability", std::to_string(cnt), u8"name");
            ++r;
        }
    }
    if (r != 0)
    {
        pos(tx + 13, ty + 6);
        gmode(2, inf_tiles, inf_tiles);
        grotate(1, 0, 672, 0, inf_tiles, inf_tiles);
        pos(tx + 32, ty);
        mes(s);
        ty += 14;
    }
    for (int cnt = 150; cnt < 600; ++cnt)
    {
        if (sdata.get(cnt, 0).original_level != 0)
        {
            s = i18n::_(u8"ability", std::to_string(cnt), u8"name");
            if (jp)
            {
                lenfix(s, 12);
            }
            else
            {
                lenfix(s, 16);
            }
            pos(tx + 13, ty + 6);
            gmode(2, inf_tiles, inf_tiles);
            grotate(
                1,
                (the_ability_db[cnt]->related_basic_attribute - 10) * inf_tiles,
                672,
                0,
                inf_tiles,
                inf_tiles);
            s(1) = i18n::_(u8"ability", std::to_string(cnt), u8"description");
            if (en)
            {
                if (strlen_u(s(1)) > 45)
                {
                    s(1) = strmid(s(1), 0, 42) + u8"..."s;
                }
            }
            pos(tx + 32, ty);
            mes(s + s(1));
            ty += 14;
        }
    }
    return;
}

} // namespace elona
