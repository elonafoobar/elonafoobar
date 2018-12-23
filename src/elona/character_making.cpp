#include "character_making.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "class.hpp"
#include "config/config.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
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
} // namespace



namespace elona
{

static void _draw_background_and_caption(const I18NKey& key)
{
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get(key);
    draw_caption();
}

void character_making_draw_background(const I18NKey& key)
{
    _draw_background_and_caption(key);

    font(13 - en * 2, snail::Font::Style::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
}

MainMenuResult character_making_select_race()
{
    auto result = ui::UIMenuCharamakeRace().show();

    if (result.canceled)
    {
        return MainMenuResult::main_title_menu;
    }
    else if (!result.value)
    {
        return MainMenuResult::character_making_select_race;
    }
    else
    {
        auto value = *result.value;
        cmrace(0) = value.race_id;
        cmrace(1) = value.race_name;
        access_race_info(11, cmrace);
        return MainMenuResult::character_making_select_sex;
    }
}

MainMenuResult character_making_select_sex(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd("core.spell");
    }

    auto result = ui::UIMenuCharamakeGender().show();

    if (result.canceled)
    {
        return MainMenuResult::main_menu_new_game;
    }
    else if (!result.value)
    {
        return MainMenuResult::character_making_select_sex_looped;
    }
    else
    {
        cmsex = *result.value;
        return MainMenuResult::character_making_select_class;
    }
}

MainMenuResult character_making_select_class(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd("core.ok1");
    }

    auto result = ui::UIMenuCharamakeClass(cmrace(1)).show();

    if (result.canceled)
    {
        return MainMenuResult::character_making_select_sex_looped;
    }
    else if (!result.value)
    {
        return MainMenuResult::character_making_select_class_looped;
    }
    else
    {
        cmclass = *result.value;
        return MainMenuResult::character_making_role_attributes;
    }
}



MainMenuResult character_making_role_attributes(bool advanced_to_next_menu)
{
    if (advanced_to_next_menu)
    {
        snd("core.skill");
        DIM2(cmlock, 10);
        cmlock(8) = 2;
    }

    auto result =
        ui::UIMenuCharamakeAttributes(cmrace(0), cmclass, cmstats, cmlock)
            .show();

    if (result.canceled)
    {
        return MainMenuResult::character_making_select_class_looped;
    }
    else if (!result.value)
    {
        return MainMenuResult::character_making_role_attributes_looped;
    }
    else
    {
        auto stats = *result.value;

        // elona_vector1 has no copy assignment operator. Trying to
        // assign to one will assign to the 0th element, as in HSP.
        for (size_t i = 0; i < stats.size(); i++)
        {
            cmstats(i) = stats(i);
        }

        return MainMenuResult::character_making_select_feats;
    }
}

MainMenuResult character_making_select_feats()
{
    game_data.acquirable_feat_count = 3;
    DIM2(trait, 500);
    DIM2(spact, 500);
    gain_race_feat();

    character_making_draw_background(
        "core.locale.chara_making.select_feats.caption");

    MenuResult result = menu_feats_character_making();
    clear_background_in_character_making();

    if (result.pressed_f1)
    {
        return MainMenuResult::character_making_select_feats;
    }
    else if (!result.succeeded)
    {
        return MainMenuResult::character_making_role_attributes_looped;
    }

    return MainMenuResult::character_making_select_alias;
}

MainMenuResult character_making_select_alias(bool advanced_to_next_menu)
{
    bool restore_previous_alias = !advanced_to_next_menu;
    optional<std::string> previous_alias = none;

    if (restore_previous_alias)
    {
        previous_alias = cmaka;
    }

    auto result = ui::UIMenuCharamakeAlias(previous_alias).show();

    if (result.canceled)
    {
        return MainMenuResult::character_making_select_feats;
    }
    else if (!result.value)
    {
        return MainMenuResult::character_making_select_alias_looped;
    }
    else
    {
        cmaka = *result.value;
        return MainMenuResult::character_making_customize_appearance;
    }
}

MainMenuResult character_making_customize_appearance()
{
    pcc(15, 0) = 0;

    if (cdata.player().portrait == "")
    {
        // TODO: if neither "core.woman1" nor "core.man1" exists, what happens?
        cdata.player().portrait =
            cdata.player().sex ? "core.woman1" : "core.man1";
    }

    while (true)
    {
        character_making_draw_background(
            "core.locale.chara_making.customize_appearance.caption");

        cdata.player().has_own_sprite() = true;
        int stat = change_appearance();
        if (stat == 0)
        {
            clear_background_in_character_making();
            return MainMenuResult::character_making_select_alias_looped;
        }
        if (stat != -1)
        {
            break;
        }
        show_game_help();
        clear_background_in_character_making();
    }
    clear_background_in_character_making();

    return MainMenuResult::character_making_final_phase;
}

static void _reroll_character()
{
    const auto portrait_save = cdata[rc].portrait;

    chara_delete(0);
    access_race_info(3, cmrace);
    access_class_info(3, cmclass);
    cdatan(0, rc) = u8"????"s;
    cdatan(1, rc) = cmaka;
    cdata[rc].level = 1;
    for (int cnt = 10; cnt < 18; ++cnt)
    {
        sdata.get(cnt, rc).original_level = cmstats(cnt - 10) / 1'000'000;
        sdata.get(cnt, rc).experience = cmstats(cnt - 10) % 1'000'000 / 1'000;
        sdata.get(cnt, rc).potential = cmstats(cnt - 10) % 1'000;
    }
    initialize_character();
    initialize_pc_character();
    cdata[rc].portrait = portrait_save;
    create_pcpic(0);
}

static int _prompt_satisfied()
{
    gsel(2);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 100, windoww, windowh - 100);
    gsel(0);
    clear_background_in_character_making();
    s = i18n::s.get(
        "core.locale.chara_making.final_screen.are_you_satisfied.prompt");
    draw_caption();

    Prompt prompt("core.locale.chara_making.final_screen.are_you_satisfied");
    prompt.append("yes", snail::Key::key_a);
    prompt.append("no", snail::Key::key_b);
    prompt.append("restart", snail::Key::key_c);
    prompt.append("go_back", snail::Key::key_d);
    int result = prompt.query(promptx, 240, 160);

    snd("core.ok1");

    return result;
}

static bool _validate_save_path(const std::string& playerid)
{
    if (range::any_of(
            filesystem::dir_entries(
                filesystem::dir::save(), filesystem::DirEntryRange::Type::all),
            [&](const auto& entry) {
                return filepathutil::to_utf8_path(entry.path().filename()) ==
                    playerid;
            }))
    {
        return false;
    }

    return true;
}

MainMenuResult character_making_final_phase()
{
    std::string cmname;

    while (true)
    {
        snd("core.chara");
        while (true)
        {
            _draw_background_and_caption(
                "core.locale.chara_making.final_screen.caption");

            _reroll_character();

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

        rtval = _prompt_satisfied();

        if (rtval != -1 && rtval != 1)
        {
            break;
        }
    }
    if (rtval == 2)
    {
        nowindowanime = 0;
        return MainMenuResult::main_menu_new_game;
    }
    else if (rtval == 3)
    {
        nowindowanime = 0;
        clear_background_in_character_making();
        load_background_variants(2);
        return MainMenuResult::character_making_customize_appearance;
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
            return MainMenuResult::character_making_final_phase;
        }

        cmname = ""s + inputlog;
        if (cmname == ""s || cmname == u8" "s)
        {
            cmname = randomname();
        }

        playerid = fs::unique_path().string();

        if (_validate_save_path(playerid))
        {
            break;
        }
        else
        {
            gmode(0);
            pos(0, 100);
            gcopy(2, 0, 0, windoww, windowh - 100);
            gmode(2);
            s = i18n::s.get(
                "core.locale.chara_making.final_screen.name_is_already_"
                "taken");
            draw_caption();
        }
    }

    snd("core.skill");
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

    cdata.player().index = 0;

    mode = 5;
    return MainMenuResult::initialize_game;
}



void draw_race_or_class_info()
{
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
            "core.locale.chara_making.select_race.race_info.attribute_"
            "bonus",
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
                    i18n::s.get_m(
                        "locale.ability",
                        the_ability_db.get_id_from_legacy(r)->get(),
                        "name"),
                    0,
                    jp ? 6 : 3) +
                u8": "s + s(p));
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
            s += i18n::s.get_m(
                "locale.ability",
                the_ability_db.get_id_from_legacy(cnt)->get(),
                "name");
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
            s = i18n::s.get_m(
                "locale.ability",
                the_ability_db.get_id_from_legacy(cnt)->get(),
                "name");
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
            s(1) = i18n::s
                       .get_m_optional(
                           "locale.ability",
                           the_ability_db.get_id_from_legacy(cnt)->get(),
                           "description")
                       .get_value_or("");
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
}

} // namespace elona
