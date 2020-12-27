#include "character_making.hpp"

#include "audio.hpp"
#include "character.hpp"
#include "class.hpp"
#include "config.hpp"
#include "data/types/type_skill.hpp"
#include "draw.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "lua_env/lua_env.hpp"
#include "main_menu.hpp"
#include "menu.hpp"
#include "race.hpp"
#include "random.hpp"
#include "save.hpp"
#include "skill.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "ui/ui_menu_charamake_alias.hpp"
#include "ui/ui_menu_charamake_attributes.hpp"
#include "ui/ui_menu_charamake_class.hpp"
#include "ui/ui_menu_charamake_gender.hpp"
#include "ui/ui_menu_charamake_race.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

data::InstanceId cmrace;
data::InstanceId cmclass;
std::string cmaka;
elona_vector1<int> cmstats;
elona_vector1<int> cmlock;

} // namespace



static void _draw_background_and_caption(const I18NKey& key)
{
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);
    ui_draw_caption(i18n::s.get(key));
}

void character_making_draw_background(const I18NKey& key)
{
    _draw_background_and_caption(key);

    font(13 - en * 2, snail::Font::Style::bold);
    mes(20, windowh - 20, u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        mes(20, windowh - 36, u8"Gene from "s + geneuse);
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
        cmrace = value.race_id;
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

    auto result = ui::UIMenuCharamakeClass(cmrace).show();

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
        cmclass = result.value->class_id;
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

    const auto result =
        ui::UIMenuCharamakeAttributes(cmrace, cmclass, cmstats, cmlock).show();

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
            cmstats(i) = stats.at(i);
        }

        return MainMenuResult::character_making_select_feats;
    }
}

MainMenuResult character_making_select_feats()
{
    cdata.player().acquirable_feats = 3;
    cdata.player().traits().clear();
    cdata.player().spacts().clear();
    gain_race_feat();

    character_making_draw_background("core.chara_making.select_feats.caption");

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
        cdata.player().portrait = cdata.player().sex
            ? data::InstanceId{"core.woman1"}
            : data::InstanceId{"core.man1"};
    }

    while (true)
    {
        character_making_draw_background(
            "core.chara_making.customize_appearance.caption");

        cdata.player().has_own_sprite() = true;
        switch (menu_change_appearance(cdata.player()))
        {
        case ChangeAppearanceResult::proceed:
            clear_background_in_character_making();
            return MainMenuResult::character_making_final_phase;
        case ChangeAppearanceResult::canceled:
            clear_background_in_character_making();
            return MainMenuResult::character_making_select_alias_looped;
        case ChangeAppearanceResult::show_help:
            show_game_help();
            clear_background_in_character_making();
            break;
        }
    }
}



static void _reroll_character()
{
    const auto portrait_save = cdata.player().portrait;

    chara_delete(cdata.player());
    race_init_chara(cdata.player(), cmrace);
    class_init_chara(cdata.player(), cmclass);
    cdata.player().name = u8"????"s;
    cdata.player().alias = cmaka;
    cdata.player().level = 1;
    for (int cnt = 10; cnt < 18; ++cnt)
    {
        const auto id = *the_skill_db.get_id_from_integer(cnt);
        cdata.player().skills().set_base_level(
            id, cmstats(cnt - 10) / 1'000'000);
        cdata.player().skills().set_experience(
            id, cmstats(cnt - 10) % 1'000'000 / 1'000);
        cdata.player().skills().set_potential(id, cmstats(cnt - 10) % 1'000);
    }
    initialize_character(cdata.player());
    initialize_pc_character();
    cdata.player().portrait = portrait_save;
    create_pcpic(cdata.player());
}



static int _prompt_satisfied()
{
    gsel(2);
    gmode(0);
    gcopy(0, 0, 100, windoww, windowh - 100, 0, 0);
    gsel(0);
    clear_background_in_character_making();
    ui_draw_caption(
        i18n::s.get("core.chara_making.final_screen.are_you_satisfied.prompt"));

    Prompt prompt("core.chara_making.final_screen.are_you_satisfied");
    prompt.append("yes", snail::Key::key_a);
    prompt.append("no", snail::Key::key_b);
    prompt.append("restart", snail::Key::key_c);
    prompt.append("go_back", snail::Key::key_d);
    int result = prompt.query(promptx, 240, 160);

    snd("core.ok1");

    return result;
}

// Returns unused directory name like "profile/<profile name>/save/save_<N>"
// where "N" is a sequential number starting with 1.
static std::string get_new_save_dir_name()
{
    for (int i = 1;; ++i)
    {
        const auto dir_name = "save_" + std::to_string(i);
        if (!fs::exists(filesystem::dirs::save() / fs::u8path(dir_name)))
        {
            return dir_name;
        }
    }
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
                "core.chara_making.final_screen.caption");

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
    gcopy(2, 0, 0, windoww, windowh - 100, 0, 100);
    gmode(2);
    ui_draw_caption(
        i18n::s.get("core.chara_making.final_screen.what_is_your_name"));

    inputlog = "";
    bool canceled =
        input_text_dialog((windoww - 230) / 2 + inf_screenx, winposy(120), 10);
    if (canceled)
    {
        return MainMenuResult::character_making_final_phase;
    }

    cmname = ""s + inputlog;
    if (cmname == ""s || cmname == u8" "s)
    {
        cmname = random_name();
    }

    playerid = get_new_save_dir_name();

    snd("core.skill");
    cdata.player().name = cmname;
    cdata.player().gold = 400 + rnd(200);

    if (geneuse != ""s)
    {
        save_get_inheritance();
    }
    else
    {
        game()->crafting_materials.clear();
    }

    cdata.player().index = 0;

    mode = 5;
    return MainMenuResult::initialize_game;
}



void draw_race_or_class_info(const std::string& description)
{
    {
        std::string tmp = description;
        talk_conv(tmp, 60 + en * 2);
        font(14 - en * 2);
        mes(wx + 210, wy + 62, tmp);
    }

    font(14 - en * 2);
    tx = wx + 200;
    ty = wy + 166;
    display_topic(
        i18n::s.get(
            "core.chara_making.select_race.race_info.attribute_bonus.text"),
        tx,
        ty);
    ty += 34;
    font(14 - en * 2);
    for (int cnt = 0; cnt < 8; cnt++)
    {
        s(cnt) = i18n::s.get_enum(
            "core.chara_making.select_race.race_info.attribute_bonus", cnt);
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
            snail::Color text_color{0, 0, 0};
            if (cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 13)
            {
                p = 1;
                text_color = snail::Color{0, 0, 200};
            }
            else if (
                cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 11)
            {
                p = 2;
                text_color = snail::Color{0, 0, 200};
            }
            else if (
                cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 9)
            {
                p = 3;
                text_color = snail::Color{0, 0, 150};
            }
            else if (
                cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 7)
            {
                p = 4;
                text_color = snail::Color{0, 0, 150};
            }
            else if (
                cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 5)
            {
                p = 5;
                text_color = snail::Color{0, 0, 0};
            }
            else if (
                cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 3)
            {
                p = 6;
                text_color = snail::Color{150, 0, 0};
            }
            else if (
                cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(r)) > 0)
            {
                p = 7;
                text_color = snail::Color{200, 0, 0};
            }
            else
            {
                p = 0;
                text_color = snail::Color{120, 120, 120};
            }
            gmode(2);
            gcopy_c(
                1,
                (cnt2 * 3 + cnt) * inf_tiles,
                672,
                inf_tiles,
                inf_tiles,
                cnt * 150 + tx + 13,
                ty + 7);
            mes(cnt * 150 + tx + 32,
                ty,
                strutil::take_by_width(
                    the_skill_db.get_text(r, "name"), jp ? 6 : 3) +
                    u8": "s + s(p),
                text_color);
        }
        ty += 16;
    }
    ty = wy + 260;
    display_topic(
        i18n::s.get(
            "core.chara_making.select_race.race_info.trained_skill.text"),
        tx,
        ty);
    ty += 34;
    font(14 - en * 2);
    r = 0;
    s = i18n::s.get(
        "core.chara_making.select_race.race_info.trained_skill.proficient_in");
    for (int cnt = 100; cnt < 150; ++cnt)
    {
        if (cdata.player().skills().base_level(
                *the_skill_db.get_id_from_integer(cnt)) != 0)
        {
            if (r != 0)
            {
                s += u8","s;
            }
            s += the_skill_db.get_text(cnt, "name");
            ++r;
        }
    }
    if (r != 0)
    {
        gmode(2);
        gcopy_c(1, 0, 672, inf_tiles, inf_tiles, tx + 13, ty + 6);
        mes(tx + 32, ty, s);
        ty += 14;
    }
    for (int cnt = 150; cnt < 600; ++cnt)
    {
        if (!the_skill_db.get_id_from_integer(cnt))
            continue;

        if (cdata.player().skills().base_level(
                *the_skill_db.get_id_from_integer(cnt)) != 0)
        {
            s = the_skill_db.get_text(cnt, "name");
            if (jp)
            {
                lenfix(s, 12);
            }
            else
            {
                lenfix(s, 16);
            }
            gmode(2);
            gcopy_c(
                1,
                (the_skill_db[cnt]->related_basic_attribute - 10) * inf_tiles,
                672,
                inf_tiles,
                inf_tiles,
                tx + 13,
                ty + 6);
            s(1) =
                the_skill_db.get_text_optional(cnt, "description").value_or("");
            if (en)
            {
                if (strlen_u(s(1)) > 45)
                {
                    s(1) = strutil::take_by_width(s(1), 42) + u8"..."s;
                }
            }
            mes(tx + 32, ty, s + s(1));
            ty += 14;
        }
    }
}

} // namespace elona
