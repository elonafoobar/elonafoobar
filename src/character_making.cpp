#include "character_making.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "class.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "lua_env/lua_env.hpp"
#include "macro.hpp"
#include "main_menu.hpp"
#include "menu.hpp"
#include "race.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

#include "ui/ui_menu_charamake_alias.hpp"
#include "ui/ui_menu_charamake_attributes.hpp"
#include "ui/ui_menu_charamake_class.hpp"
#include "ui/ui_menu_charamake_gender.hpp"
#include "ui/ui_menu_charamake_race.hpp"


namespace
{
elona_vector1<std::string> cmrace;
std::string cmclass;
elona_vector1<int> cmstats;
elona_vector1<int> cmlock;
elona_vector1<int> alias_lock;
} // namespace



namespace elona
{



main_menu_result_t character_making_select_race()
{
    auto result = ui::ui_menu_charamake_race().show();

    if (result.canceled)
    {
        return main_menu_result_t::main_title_menu;
    }
    else if (!result.value)
    {
        return main_menu_result_t::character_making_select_race;
    }
    else
    {
        int race_id = *result.value;
        cmrace(0) = listn(1, race_id);
        cmrace(1) = listn(0, race_id);
        access_race_info(11, cmrace);
        return main_menu_result_t::character_making_select_sex;
    }
}

main_menu_result_t character_making_select_sex(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd(102);
    }

    auto result = ui::ui_menu_charamake_gender().show();

    if (result.canceled)
    {
        return main_menu_result_t::main_menu_new_game;
    }
    else if (!result.value)
    {
        return main_menu_result_t::character_making_select_sex_looped;
    }
    else
    {
        cmsex = *result.value;
        return main_menu_result_t::character_making_select_class;
    }
}

main_menu_result_t character_making_select_class(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd(20);
    }

    auto result = ui::ui_menu_charamake_class().show();

    if (result.canceled)
    {
        return main_menu_result_t::character_making_select_sex_looped;
    }
    else if (!result.value)
    {
        return main_menu_result_t::character_making_select_class_looped;
    }
    else
    {
        cmclass = *result.value;
        return main_menu_result_t::character_making_role_attributes;
    }
}



main_menu_result_t character_making_role_attributes(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd(101);
        DIM2(cmlock, 10);
        cmlock(8) = 2;
    }

    auto result = ui::ui_menu_charamake_attributes(cmstats, cmlock).show();

    if (result.canceled)
    {
        return main_menu_result_t::character_making_select_class_looped;
    }
    else if (!result.value)
    {
        return main_menu_result_t::character_making_role_attributes_looped;
    }
    else
    {
        cmstats = *result.value;
        return main_menu_result_t::character_making_select_feats;
    }
}

main_menu_result_t character_making_select_feats()
{
    gdata_acquirable_feat_count = 3;
    DIM2(trait, 500);
    DIM2(spact, 500);
    gain_race_feat();
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.select_feats.caption");
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }

    menu_result result = menu_feats_character_making();
    clear_background_in_character_making();

    if (result.pressed_f1)
    {
        return main_menu_result_t::character_making_select_feats;
    }
    else if (!result.succeeded)
    {
        return main_menu_result_t::character_making_role_attributes_looped;
    }

    return main_menu_result_t::character_making_select_alias;
}

main_menu_result_t character_making_select_alias(bool advanced_to_next_menu)
{
    bool restore_previous_alias = !advanced_to_next_menu;
    optional<std::string> previous_alias = none;

    if (advanced_to_next_menu)
    {
        DIM2(alias_lock, 18);
    }

    if (restore_previous_alias)
    {
        previous_alias = cmaka;
    }

    auto result =
        ui::ui_menu_charamake_alias(previous_alias, alias_lock).show();

    if (result.canceled)
    {
        return main_menu_result_t::character_making_select_feats;
    }
    else if (!result.value)
    {
        return main_menu_result_t::character_making_select_alias_looped;
    }
    else
    {
        cmaka = *result.value;
        return main_menu_result_t::character_making_customize_appearance;
    }
}

main_menu_result_t character_making_customize_appearance()
{
    pcc(15, 0) = 0;

    while (true)
    {
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
        s = i18n::s.get(
            "core.locale.chara_making.customize_appearance.caption");
        draw_caption();
        font(13 - en * 2, snail::font_t::style_t::bold);
        pos(20, windowh - 20);
        mes(u8"Press F1 to show help."s);
        if (geneuse != ""s)
        {
            pos(20, windowh - 36);
            mes(u8"Gene from "s + geneuse);
        }
        cdata.player().has_own_sprite() = true;
        int stat = change_appearance();
        if (stat == 0)
        {
            clear_background_in_character_making();
            return main_menu_result_t::character_making_select_alias_looped;
        }
        if (stat != -1)
        {
            break;
        }
        show_game_help();
        clear_background_in_character_making();
    }
    clear_background_in_character_making();

    return main_menu_result_t::character_making_final_phase;
}

main_menu_result_t character_making_final_phase()
{
    std::string cmname;
    int cmportrait = cdata[rc].portrait;

    while (true)
    {
        snd(94);
        while (true)
        {
            gmode(0);
            pos(0, 0);
            gcopy(4, 0, 0, windoww, windowh);
            gmode(2);
            s = i18n::s.get("core.locale.chara_making.final_screen.caption");
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
            menucycle = 0;
            {
                bool confirmed = menu_character_sheet_character_making();
                if (confirmed)
                {
                    break;
                }
                else
                {
                    nowindowanime = 1;
                    clear_background_in_character_making();
                }
            }
        }
        gsel(2);
        pos(0, 0);
        gmode(0);
        gcopy(0, 0, 100, windoww, windowh - 100);
        gsel(0);
        clear_background_in_character_making();
        s = i18n::s.get(
            "core.locale.chara_making.final_screen.are_you_satisfied.prompt");
        draw_caption();
        ELONA_APPEND_PROMPT(
            i18n::s.get(
                "core.locale.chara_making.final_screen.are_you_satisfied.yes"),
            u8"a"s,
            ""s + promptmax);
        ELONA_APPEND_PROMPT(
            i18n::s.get(
                "core.locale.chara_making.final_screen.are_you_satisfied.no"),
            u8"b"s,
            ""s + promptmax);
        ELONA_APPEND_PROMPT(
            i18n::s.get("core.locale.chara_making.final_screen.are_you_"
                        "satisfied.restart"),
            u8"c"s,
            ""s + promptmax);
        ELONA_APPEND_PROMPT(
            i18n::s.get("core.locale.chara_making.final_screen.are_you_"
                        "satisfied.go_back"),
            u8"d"s,
            ""s + promptmax);
        rtval = show_prompt(promptx, 240, 160);
        snd(20);
        if (rtval != -1 && rtval != 1)
        {
            break;
        }
    }
    if (rtval == 2)
    {
        nowindowanime = 0;
        return main_menu_result_t::main_menu_new_game;
    }
    else if (rtval == 3)
    {
        nowindowanime = 0;
        clear_background_in_character_making();
        load_background_variants(2);
        return main_menu_result_t::character_making_customize_appearance;
    }
    gmode(0);
    pos(0, 100);
    gcopy(2, 0, 0, windoww, windowh - 100);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.final_screen.what_is_your_name");
    draw_caption();

    while (true)
    {
        inputlog = "";
        bool canceled = input_text_dialog(
            (windoww - 230) / 2 + inf_screenx, winposy(120), 10, true);
        if (canceled)
        {
            return main_menu_result_t::character_making_final_phase;
        }
        cmname = ""s + inputlog;
        if (cmname == ""s || cmname == u8" "s)
        {
            cmname = randomname();
        }
        playerid = fs::unique_path().string();
        if (range::any_of(
                filesystem::dir_entries{filesystem::dir::save(),
                                        filesystem::dir_entries::type::all},
                [&](const auto& entry) {
                    return filesystem::to_utf8_path(entry.path().filename())
                        == playerid;
                }))
        {
            gmode(0);
            pos(0, 100);
            gcopy(2, 0, 0, windoww, windowh - 100);
            gmode(2);
            s = i18n::s.get(
                "core.locale.chara_making.final_screen.name_is_already_taken");
            draw_caption();
        }
        else
        {
            break;
        }
    }
    snd(101);
    cdatan(0, rc) = cmname;
    cdata.player().gold = 400 + rnd(200);
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
    mode = 5;
    cdata.player().index = 0;
    return main_menu_result_t::initialize_game;
}



void show_race_or_class_info(int val0)
{
    if (val0 == 1)
    {
        {
            auto rect = chara_preparepic(ref1);
            pos(wx + 380, wy - rect->height + 60);
            gcopy(rect->buffer, 0, 960, inf_tiles, rect->height);
        }
        {
            auto rect = chara_preparepic(ref2);
            pos(wx + 350, wy - rect->height + 60);
            gcopy(rect->buffer, 0, 960, inf_tiles, rect->height);
        }
        pos(wx + 460, wy + 38);
        mes(i18n::s.get("core.locale.chara_making.select_race.race_info.race")
            + u8": "s + cmrace(1));
    }
    else
    {
        {
            // male
            draw_chara(ref1, wx + 480, wy + 96, 2, 40);
        }
        {
            // female
            draw_chara(ref2, wx + 350, wy + 96, 2, 40);
        }
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
    display_topic(
        i18n::s.get("core.locale.chara_making.select_race.race_info.attribute_"
                    "bonus.text"),
        tx,
        ty);
    ty += 34;
    font(14 - en * 2);
    for (int cnt = 0; cnt < 8; cnt++)
    {
        s(cnt) = i18n::s.get_enum(
            "core.locale.chara_making.select_race.race_info.attribute_bonus",
            cnt);
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
            gmode(2);
            gcopy_c(1, (cnt2 * 3 + cnt) * inf_tiles, 672, inf_tiles, inf_tiles);
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
    display_topic(
        i18n::s.get("core.locale.chara_making.select_race.race_info.trained_"
                    "skill.text"),
        tx,
        ty);
    ty += 34;
    font(14 - en * 2);
    r = 0;
    s = i18n::s.get(
        "core.locale.chara_making.select_race.race_info.trained_skill."
        "proficient_in");
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
        gmode(2);
        gcopy_c(1, 0, 672, inf_tiles, inf_tiles);
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
            gmode(2);
            gcopy_c(
                1,
                (the_ability_db[cnt]->related_basic_attribute - 10) * inf_tiles,
                672,
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
