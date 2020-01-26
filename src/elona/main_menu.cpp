#include "main_menu.hpp"
#include "../util/fileutil.hpp"
#include "../util/strutil.hpp"
#include "../version.hpp"
#include "audio.hpp"
#include "browser.hpp"
#include "character_making.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "keybind/keybind.hpp"
#include "lua_env/mod_manager.hpp"
#include "macro.hpp"
#include "main_menu.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "ui/menu_cursor_history.hpp"
#include "ui/simple_prompt.hpp"
#include "ui/ui_menu_mods.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

struct Release
{
    Release(
        const std::string& version,
        const std::string& date,
        const std::string& content)
        : version(version)
        , date(date)
        , content(content)
    {
    }



    std::string title() const
    {
        return version + u8" (" + date + u8")";
    }



    std::string version;
    std::string date;
    std::string content;
};



struct Changelog
{
public:
    using iterator = std::vector<Release>::const_iterator;


    void load(const fs::path& changelog_path)
    {
        for (const auto& line : fileutil::read_by_line(changelog_path))
        {
            if (strutil::starts_with(line, u8"## "))
            {
                // ## [version] - date
                const auto open_bracket_pos = line.find('[');
                const auto closing_bracket_pos = line.find(']');
                const auto hyphen_bracket_pos = line.find('-');
                const auto version = line.substr(
                    open_bracket_pos + 1,
                    closing_bracket_pos - open_bracket_pos - 1);
                const auto date = line.substr(hyphen_bracket_pos + 2);
                releases.emplace_back(version, date, "");
            }
            else if (!releases.empty())
            {
                releases.back().content += line + '\n';
            }
        }
    }



    const Release& at(size_t index) const
    {
        return releases.at(index);
    }



    iterator begin() const
    {
        return std::begin(releases);
    }



    iterator end() const
    {
        return std::end(releases);
    }



private:
    // The first element is the latest. The last, the oldest.
    std::vector<Release> releases;
};



class ModCreatePrompt : public ui::SimplePrompt<ui::DummyResult>
{
public:
    ModCreatePrompt(const std::string& message)
        : ui::SimplePrompt<ui::DummyResult>(message)
    {
    }


protected:
    virtual optional<ui::DummyResult> update() override
    {
        await(g_config.general_wait());
        auto action = key_check();

        if (action != "")
        {
            return ui::DummyResult{};
        }

        return none;
    }
};

} // namespace



bool main_menu_loop()
{
    MainMenuResult result = main_menu_wrapper();
    bool finished = false;
    while (!finished)
    {
        switch (result)
        {
        case MainMenuResult::main_title_menu:
            result = main_menu_wrapper();
            break;
        case MainMenuResult::initialize_game: finished = true; break;
        case MainMenuResult::finish_elona:
            finish_elona();
            finished = true;
            break;
        default: assert(0); break;
        }
    }

    return result == MainMenuResult::initialize_game;
}



MainMenuResult main_title_menu()
{
    mode = 10;
    lomiaseaster = 0;

    play_music("core.mcOpening");

    cs = 0;
    cs_bk = -1;
    pagesize = 0;

    if (const auto cursor =
            ui::MenuCursorHistory::instance().restore("core.main_title_menu"))
    {
        cs = cursor->position();
    }

    load_background_variants(2);

    gmode(0);
    asset_load("title");
    draw("title", 0, 0, windoww, windowh);
    gmode(2);

    font(13 - en * 2);
    mes(20, 20, u8"Elona version 1.22  Developed by Noa"s, {255, 255, 255});

    mes(20,
        38,
        u8"  Variant foobar version "s + latest_version.short_string() +
            u8"  Developed by KI",
        {255, 255, 255});

    if (jp)
    {
        mes(20,
            56,
            u8"Contributor MSL / View the credits for more"s,
            {255, 255, 255});
    }
    else
    {
        mes(20,
            56,
            u8"Contributor f1r3fly, Sunstrike, Schmidt, Elvenspirit / View the credits for more"s,
            {255, 255, 255});
        mes(20, 76, u8"Omake/OO translator: Doorknob", {255, 255, 255});
        mes(20, 96, u8"Cutscenes translator: AnnaBannana", {255, 255, 255});
    }

    windowshadow = 1;
    ui_display_window(
        jp ? u8"冒険の道標" : u8"Starting Menu",
        strhint1,
        80,
        winposy(308, 1),
        320,
        355);
    cmbg = 4;
    x = ww / 5 * 4;
    y = wh - 80;
    gmode(2, 50);
    gcopy_c(
        2,
        cmbg / 2 * 180,
        cmbg % 2 * 300,
        180,
        300,
        wx + 160,
        wy + wh / 2,
        x,
        y);
    gmode(2);

    struct MainMenuItem
    {
        std::string subtitle;
        std::string title;
    };
    std::vector<MainMenuItem> items = {
        {u8"Restore an Adventurer",
         i18n::s.get("core.main_menu.title_menu.continue")},
        {u8"Generate an Adventurer",
         i18n::s.get("core.main_menu.title_menu.new")},
        {u8"Incarnate an Adventurer",
         i18n::s.get("core.main_menu.title_menu.incarnate")},
        {u8"About", i18n::s.get("core.main_menu.title_menu.about")},
        {u8"Options", i18n::s.get("core.main_menu.title_menu.options")},
        {u8"Mods", i18n::s.get("core.main_menu.title_menu.mods")},
        {u8"Exit", i18n::s.get("core.main_menu.title_menu.exit")},
    };

    keyrange = items.size();

    asset_load("deco_blend");
    gsel(0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);

    snail::Image water_ripple{filesystem::path("graphic/water_ripple.png")};

    std::vector<std::pair<int, Position>> ripple_source;
    std::vector<std::tuple<int, int, Position>> ripples;
    int frame = 0;

    while (true)
    {
        if (g_config.autodisable_numlock())
        {
            snail::Input::instance().disable_numlock();
        }

        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);

        if (g_config.title_effect())
        {
            if (frame % 20 == 0)
            {
                ripple_source.push_back(std::make_pair(
                    0,
                    Position{rnd(windoww - 20) + 10, rnd(windowh - 20) + 10}));
            }

            for (auto&& s : ripple_source)
            {
                if (s.first % 5 == 0)
                {
                    ripples.push_back(std::make_tuple(
                        0,
                        rnd(rnd(3) + 1),
                        Position{s.second.x - rnd(256) + rnd(256),
                                 s.second.y - rnd(256) + rnd(256)}));
                }
                ++s.first;
            }

            auto&& renderer = snail::Application::instance().get_renderer();
            for (auto&& r : ripples)
            {
                const auto t = std::get<0>(r);
                const auto kind = std::get<1>(r);
                const auto x = std::get<2>(r).x;
                const auto y = std::get<2>(r).y;
                const auto width = 1.5 * t;
                const auto height = width;
                gmode(2, 100 + rnd(6) * 20);
                renderer.render_image(
                    water_ripple,
                    256 * kind,
                    0,
                    256,
                    256,
                    x - width / 2,
                    y - height / 2,
                    width,
                    height);
                gmode(2);
                ++std::get<0>(r);
            }

            range::remove_erase_if(ripple_source, [](const auto& s) {
                return s.first >= 15 + 5 * rnd(3);
            });
            range::remove_erase_if(ripples, [](const auto& r) {
                return std::get<0>(r) >= rnd(rnd(256)) + rnd(256) + 64;
            });
        }

        cs_listbk();
        for (int cnt = 0; cnt < static_cast<int>(items.size()); ++cnt)
        {
            x = wx + 40;
            y = cnt * 35 + wy + 50;
            display_customkey(key_select(cnt), x, y);
            if (en)
            {
                font(14 - en * 2);
                cs_list(cs == cnt, items.at(cnt).title, x + 40, y + 1);
            }
            else
            {
                font(11 - en * 2);
                mes(x + 40, y - 4, items.at(cnt).subtitle);
                font(13 - en * 2);
                cs_list(cs == cnt, items.at(cnt).title, x + 40, y + 8);
            }
        }
        cs_bk = cs;

        redraw();

        int index{};
        cursor_check_ex(index);

        if (index != -1)
        {
            ui::MenuCursorHistory::instance().save(
                "core.main_title_menu", ui::MenuCursor{cs});
        }

        switch (index)
        {
        case -1: break;
        case 0: snd("core.ok1"); return MainMenuResult::main_menu_continue;
        case 1:
            snd("core.ok1");
            geneuse = "";
            return MainMenuResult::main_menu_new_game;
        case 2: snd("core.ok1"); return MainMenuResult::main_menu_incarnate;
        case 3: snd("core.ok1"); return MainMenuResult::main_menu_about;
        case 4:
            snd("core.ok1");
            show_option_menu();
            return MainMenuResult::main_title_menu;
        case 5: snd("core.ok1"); return MainMenuResult::main_menu_mods;
        case 6: snd("core.ok1"); return MainMenuResult::finish_elona;
        default: break;
        }

        ++frame;
    }
}



MainMenuResult main_menu_wrapper()
{
    // Start off in the title menu.
    MainMenuResult result = main_title_menu();
    bool finished = false;
    while (!finished)
    {
        switch (result)
        {
            // Main menu

        case MainMenuResult::main_menu_incarnate:
            result = main_menu_incarnate();
            break;
        case MainMenuResult::main_menu_continue:
            result = main_menu_continue();
            break;
        case MainMenuResult::main_menu_new_game:
            result = main_menu_new_game();
            break;
        case MainMenuResult::main_menu_about: result = main_menu_about(); break;
        case MainMenuResult::main_menu_about_changelogs:
            result = main_menu_about_changelogs();
            break;
        case MainMenuResult::main_menu_about_license:
            result = main_menu_about_license();
            break;
        case MainMenuResult::main_menu_about_credits:
            result = main_menu_about_credits();
            break;
        case MainMenuResult::main_menu_mods: result = main_menu_mods(); break;
        case MainMenuResult::main_menu_mods_list:
            result = main_menu_mods_list();
            break;
        case MainMenuResult::main_menu_mods_develop:
            result = main_menu_mods_develop();
            break;
        case MainMenuResult::main_title_menu:
            // Loop back to the start.
            result = MainMenuResult::main_title_menu;
            finished = true;
            break;

            // Character making

        case MainMenuResult::character_making_select_race:
            result = character_making_select_race();
            break;
        case MainMenuResult::character_making_select_sex:
            result = character_making_select_sex();
            break;
        case MainMenuResult::character_making_select_sex_looped:
            result = character_making_select_sex(false);
            break;
        case MainMenuResult::character_making_select_class:
            result = character_making_select_class();
            break;
        case MainMenuResult::character_making_select_class_looped:
            result = character_making_select_class(false);
            break;
        case MainMenuResult::character_making_role_attributes:
            result = character_making_role_attributes();
            break;
        case MainMenuResult::character_making_role_attributes_looped:
            result = character_making_role_attributes(false);
            break;
        case MainMenuResult::character_making_select_feats:
            result = character_making_select_feats();
            break;
        case MainMenuResult::character_making_select_alias:
            result = character_making_select_alias();
            break;
        case MainMenuResult::character_making_select_alias_looped:
            result = character_making_select_alias(false);
            break;
        case MainMenuResult::character_making_customize_appearance:
            result = character_making_customize_appearance();
            break;
        case MainMenuResult::character_making_final_phase:
            result = character_making_final_phase();
            break;

            // Finished initializing, start the game.

        case MainMenuResult::initialize_game:
            result = MainMenuResult::initialize_game;
            finished = true;
            break;
        case MainMenuResult::finish_elona:
            result = MainMenuResult::finish_elona;
            finished = true;
            break;
        default: assert(0); break;
        }
    }
    return result;
}



MainMenuResult main_menu_new_game()
{
    if (g_config.wizard())
    {
        game_data.wizard = 1;
    }
    if (geneuse != ""s)
    {
        load_gene_files();
    }
    rc = 0;
    mode = 1;
    cm = 1;
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    load_background_variants(2);
    asset_load("deco_cm");
    gsel(0);
    return MainMenuResult::character_making_select_race;
}



MainMenuResult main_menu_continue()
{
    int save_data_count = 0;
    int index = 0;
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 5;
    keyrange = 0;

    for (const auto& entry : filesystem::glob_dirs(filesystem::dirs::save()))
    {
        s = filepathutil::to_utf8_path(entry.path().filename());
        const auto header_filepath = filesystem::dirs::save(s) / u8"header.txt";
        if (!fs::exists(header_filepath))
        {
            continue;
        }

        // the number of bytes read by bload depends on the size of
        // the string passed in, so make it 100 bytes long.
        playerheader = std::string(100, '\0');
        bload(header_filepath, playerheader);

        list(0, save_data_count) = save_data_count;
        listn(0, save_data_count) = s;
        listn(1, save_data_count) = ""s + playerheader;
        key_list(save_data_count) = key_select(save_data_count);
        ++save_data_count;
    }
    listmax = save_data_count;

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
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

            clear_background_in_continue();
            ui_draw_caption(i18n::s.get("core.main_menu.continue.which_save"));
            windowshadow = 1;
        }

        ui_display_window(
            i18n::s.get("core.main_menu.continue.title"),
            i18n::s.get("core.main_menu.continue.key_hint") + strhint2 +
                strhint3b,
            (windoww - 440) / 2 + inf_screenx,
            winposy(288, 1),
            440,
            288);
        cs_listbk();
        keyrange = 0;
        for (int cnt = 0, cnt_end = pagesize; cnt < cnt_end; ++cnt)
        {
            index = pagesize * page + cnt;
            if (index >= listmax)
            {
                break;
            }
            x = wx + 20;
            y = cnt * 40 + wy + 50;
            display_key(x + 20, y - 2, cnt);
            font(11 - en * 2);
            mes(x + 48, y - 4, listn(0, index));
            font(13 - en * 2);
            cs_list(cs == cnt, listn(1, index), x + 48, y + 8);
            ++keyrange;
        }
        cs_bk = cs;
        if (save_data_count == 0)
        {
            font(14 - en * 2);
            mes(wx + 140,
                wy + 120,
                i18n::s.get("core.main_menu.continue.no_save"));
        }
        redraw();

        int cursor{};
        auto action = cursor_check_ex(cursor);

        p = -1;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            index = pagesize * page + cnt;
            if (index >= listmax)
            {
                break;
            }
            if (cursor == cnt)
            {
                p = list(0, index);
                break;
            }
        }
        if (p != -1)
        {
            playerid = listn(0, p);
            snd("core.ok1");
            mode = 3;
            return MainMenuResult::initialize_game;
        }
        if (ginfo(2) == 0)
        {
            if (save_data_count != 0)
            {
                if (getkey(snail::Key::backspace))
                {
                    p = list(0, cs);
                    playerid = listn(0, p);
                    ui_draw_caption(i18n::s.get(
                        "core.main_menu.continue.delete", playerid));
                    if (!yes_no())
                    {
                        return MainMenuResult::main_menu_continue;
                    }
                    ui_draw_caption(i18n::s.get(
                        "core.main_menu.continue.delete2", playerid));
                    if (yes_no())
                    {
                        snd("core.ok1");
                        ctrl_file(FileOperation::save_game_delete);
                    }
                    return MainMenuResult::main_menu_continue;
                }
            }
        }
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return MainMenuResult::main_title_menu;
        }
    }
}



MainMenuResult main_menu_incarnate()
{
    cs = 0;
    cs_bk = -1;
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gsel(0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);
    ui_draw_caption(i18n::s.get("core.main_menu.incarnate.which_gene"));
    keyrange = 0;
    listmax = 0;
    for (const auto& entry : filesystem::glob_dirs(filesystem::dirs::save()))
    {
        s = filepathutil::to_utf8_path(entry.path().filename());
        const auto gene_header_filepath =
            filesystem::dirs::save(s) / u8"gene_header.txt";
        if (!fs::exists(gene_header_filepath))
        {
            continue;
        }
        bload(gene_header_filepath, playerheader);
        list(0, listmax) = listmax;
        listn(0, listmax) = s;
        listn(1, listmax) = ""s + playerheader;
        key_list(listmax) = key_select(listmax);
        ++keyrange;
        ++listmax;
    }
    windowshadow = 1;

    while (1)
    {
        ui_display_window(
            i18n::s.get("core.main_menu.incarnate.title"),
            strhint3b,
            (windoww - 440) / 2 + inf_screenx,
            winposy(288, 1),
            440,
            288);
        cs_listbk();
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            x = wx + 20;
            y = cnt * 40 + wy + 50;
            display_key(x + 20, y - 2, cnt);
            font(11 - en * 2);
            mes(x + 48, y - 4, listn(0, cnt));
            font(13 - en * 2);
            cs_list(cs == cnt, listn(1, cnt), x + 48, y + 8);
        }
        cs_bk = cs;
        if (listmax == 0)
        {
            font(14 - en * 2);
            mes(wx + 140,
                wy + 120,
                i18n::s.get("core.main_menu.incarnate.no_gene"));
        }
        redraw();

        int cursor{};
        auto command = cursor_check_ex(cursor);

        p = -1;
        for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
        {
            if (cnt == cursor)
            {
                p = list(0, cnt);
                break;
            }
        }
        if (p != -1)
        {
            snd("core.ok1");
            geneuse = listn(0, p);
            playerid = listn(0, p);
            return MainMenuResult::main_menu_new_game;
        }
        if (command == "cancel")
        {
            return MainMenuResult::main_title_menu;
        }
    }
    return MainMenuResult::main_title_menu;
}



MainMenuResult main_menu_about()
{
    cs = 0;
    cs_bk = -1;
    keyrange = 5;
    listmax = 5;

    gmode(0);
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gmode(2);

    ui_draw_caption("Elona foobar " + latest_version.short_string());

    windowshadow = 1;
    ui_display_window(
        i18n::s.get("core.main_menu.about.title"),
        strhint3b,
        (windoww - 440) / 2 + inf_screenx,
        winposy(288, 1),
        440,
        288);

    s(0) = i18n::s.get("core.main_menu.about.vanilla_homepage");
    s(1) = i18n::s.get("core.main_menu.about.foobar_homepage");
    s(2) = i18n::s.get("core.main_menu.about.foobar_changelog");
    s(3) = i18n::s.get("core.main_menu.about.license");
    s(4) = i18n::s.get("core.main_menu.about.credits");

    gsel(0);

    while (true)
    {
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);

        cs_listbk();
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            const auto x = wx + 40;
            const auto y = cnt * 35 + wy + 50;
            display_key(x, y, cnt);
            font(14 - en * 2);
            cs_list(cs == cnt, s(cnt), x + 40, y + 1);
        }
        cs_bk = cs;

        redraw();

        int index{};
        auto action = cursor_check_ex(index);

        if (index == 0)
        {
            snd("core.ok1");
            if (jp)
            {
                open_browser("http://ylvania.org/jp");
            }
            else
            {
                open_browser("http://ylvania.org/en");
            }
        }
        if (index == 1)
        {
            snd("core.ok1");
            open_browser("https://elonafoobar.com");
        }
        if (index == 2)
        {
            snd("core.ok1");
            return MainMenuResult::main_menu_about_changelogs;
        }
        if (index == 3)
        {
            snd("core.ok1");
            return MainMenuResult::main_menu_about_license;
        }
        if (index == 4)
        {
            snd("core.ok1");
            return MainMenuResult::main_menu_about_credits;
        }

        if (action == "cancel")
        {
            return MainMenuResult::main_title_menu;
        }
    }
}



void main_menu_about_one_changelog(const Release& release)
{
    std::vector<std::string> changes;
    if (release.content.empty())
    {
        changes.push_back("");
    }
    else
    {
        const size_t text_width = 75 - en * 15;
        constexpr size_t lines_per_page = 16;

        std::vector<std::string> buffer;
        range::copy(
            strutil::split_lines(release.content), std::back_inserter(buffer));
        for (auto&& line : buffer)
        {
            // talk_conv only accepts single line text, so you need to split by
            // line.
            talk_conv(line, text_width);
        }
        size_t line_count = 0;
        for (const auto& lines : buffer)
        {
            for (const auto& line : strutil::split_lines(lines))
            {
                if (line_count == 0)
                {
                    changes.push_back(line + '\n');
                }
                else
                {
                    changes.back() += line + '\n';
                }
                ++line_count;
                if (line_count == lines_per_page)
                {
                    line_count = 0;
                }
            }
        }
    }
    pagemax = changes.size() - 1;

    page = 0;

    gmode(0);
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gmode(2);
    gsel(0);

    ui_draw_caption(i18n::s.get("core.main_menu.about_changelog.title"));

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh, 0, 0);
            gmode(2);

            cs_bk = -1;
            if (page < 0)
            {
                page = pagemax;
            }
            else if (page > pagemax)
            {
                page = 0;
            }

            windowshadow = 1;
        }

        ui_display_window(
            release.title(),
            strhint2 + strhint3b,
            (windoww - 600) / 2 + inf_screenx,
            winposy(425, 1),
            600,
            425);

        font(13);
        mes(wx + 20, wy + 30, changes.at(page));

        redraw();

        int cursor{};
        auto action = cursor_check_ex(cursor);
        (void)cursor;

        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return;
        }
    }
}



MainMenuResult main_menu_about_changelogs()
{
    int index = 0;
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 5;
    keyrange = 0;

    gmode(0);
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gmode(2);
    gsel(0);

    ui_draw_caption(i18n::s.get("core.main_menu.about_changelog.title"));

    Changelog changelog;
    if (jp)
    {
        changelog.load(filesystem::path("../CHANGELOG-jp.md"));
    }
    else
    {
        changelog.load(filesystem::path("../CHANGELOG.md"));
    }

    listmax = 0;
    for (const auto& release : changelog)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = release.title();
        key_list(listmax) = key_select(listmax);
        ++listmax;
    }

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh, 0, 0);
            gmode(2);

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

            windowshadow = 1;
        }

        ui_display_window(
            "",
            strhint2 + strhint3b,
            (windoww - 440) / 2 + inf_screenx,
            winposy(288, 1),
            440,
            288);
        cs_listbk();
        keyrange = 0;
        for (int cnt = 0, cnt_end = pagesize; cnt < cnt_end; ++cnt)
        {
            index = pagesize * page + cnt;
            if (index >= listmax)
            {
                break;
            }
            x = wx + 20;
            y = cnt * 40 + wy + 30;
            display_key(x + 20, y, cnt);
            font(13 - en * 2);
            cs_list(cs == cnt, listn(0, index), x + 48, y);
            ++keyrange;
        }
        cs_bk = cs;
        redraw();

        int cursor{};
        auto action = cursor_check_ex(cursor);

        p = -1;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            index = pagesize * page + cnt;
            if (index >= listmax)
            {
                break;
            }
            if (cursor == cnt)
            {
                p = list(0, index);
                break;
            }
        }
        if (p != -1)
        {
            snd("core.ok1");
            const auto page_save = page;
            const auto pagemax_save = pagemax;
            main_menu_about_one_changelog(changelog.at(p));
            page = page_save;
            pagemax = pagemax_save;
            init = true;
            continue;
        }
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return MainMenuResult::main_menu_about;
        }
    }
}



MainMenuResult main_menu_about_license()
{
    std::vector<std::string> license_text_lines;
    range::copy(
        fileutil::read_by_line(filesystem::path("../LICENSE.txt")),
        std::back_inserter(license_text_lines));

    std::vector<std::string> license_pages;

    if (license_text_lines.empty())
    {
        license_pages.push_back("");
    }
    else
    {
        // LICENSE.txt is always written in English
        const size_t text_width = 75 - 15;
        constexpr size_t lines_per_page = 16;

        for (auto&& line : license_text_lines)
        {
            // talk_conv only accepts single line text, so you need to split by
            // line.
            talk_conv(line, text_width);
        }
        size_t line_count = 0;
        for (const auto& lines : license_text_lines)
        {
            for (const auto& line : strutil::split_lines(lines))
            {
                if (line_count == 0)
                {
                    license_pages.push_back(line + '\n');
                }
                else
                {
                    license_pages.back() += line + '\n';
                }
                ++line_count;
                if (line_count == lines_per_page)
                {
                    line_count = 0;
                }
            }
        }
    }
    pagemax = license_pages.size() - 1;

    page = 0;

    gmode(0);
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gmode(2);
    gsel(0);

    ui_draw_caption(i18n::s.get("core.main_menu.about.license"));

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh, 0, 0);
            gmode(2);

            cs_bk = -1;
            if (page < 0)
            {
                page = pagemax;
            }
            else if (page > pagemax)
            {
                page = 0;
            }

            windowshadow = 1;
        }

        ui_display_window(
            "",
            strhint2 + strhint3b,
            (windoww - 600) / 2 + inf_screenx,
            winposy(425, 1),
            600,
            425);

        font(13 - 2); // LICENSE.txt is always written in English
        mes(wx + 20, wy + 30, license_pages.at(page));

        redraw();

        int cursor{};
        auto action = cursor_check_ex(cursor);
        (void)cursor;

        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return MainMenuResult::main_menu_about;
        }
    }
}



MainMenuResult main_menu_about_credits()
{
    std::vector<std::string> credits_text_lines;
    range::copy(
        fileutil::read_by_line(filesystem::path("../CREDITS.txt")),
        std::back_inserter(credits_text_lines));

    std::vector<std::string> credits_pages;

    if (credits_text_lines.empty())
    {
        credits_pages.push_back("");
    }
    else
    {
        // CREDITS.txt is always written in English
        const size_t text_width = 75 - 15;
        constexpr size_t lines_per_page = 16;

        for (auto&& line : credits_text_lines)
        {
            // talk_conv only accepts single line text, so you need to split by
            // line.
            talk_conv(line, text_width);
        }
        size_t line_count = 0;
        for (const auto& lines : credits_text_lines)
        {
            for (const auto& line : strutil::split_lines(lines))
            {
                if (line_count == 0)
                {
                    credits_pages.push_back(line + '\n');
                }
                else
                {
                    credits_pages.back() += line + '\n';
                }
                ++line_count;
                if (line_count == lines_per_page)
                {
                    line_count = 0;
                }
            }
        }
    }
    pagemax = credits_pages.size() - 1;

    page = 0;

    gmode(0);
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gmode(2);
    gsel(0);

    ui_draw_caption(i18n::s.get("core.main_menu.about.credits"));

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh, 0, 0);
            gmode(2);

            cs_bk = -1;
            if (page < 0)
            {
                page = pagemax;
            }
            else if (page > pagemax)
            {
                page = 0;
            }

            windowshadow = 1;
        }

        ui_display_window(
            "",
            strhint2 + strhint3b,
            (windoww - 600) / 2 + inf_screenx,
            winposy(425, 1),
            600,
            425);

        font(13 - 2); // CREDITS.txt is always written in English
        mes(wx + 20, wy + 30, credits_pages.at(page));

        redraw();

        int cursor{};
        auto action = cursor_check_ex(cursor);
        (void)cursor;

        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return MainMenuResult::main_menu_about;
        }
    }
}



MainMenuResult main_menu_mods()
{
    cs = 0;
    cs_bk = -1;
    keyrange = 2;
    listmax = 2;

    gmode(0);
    asset_load("void");
    draw("void", 0, 0, windoww, windowh);
    gmode(2);

    windowshadow = 1;
    ui_display_window(
        i18n::s.get("core.main_menu.mods.title"),
        strhint3b,
        (windoww - 440) / 2 + inf_screenx,
        winposy(288, 1),
        440,
        288);

    s(0) = i18n::s.get("core.main_menu.mods.menu.list");
    s(1) = i18n::s.get("core.main_menu.mods.menu.develop");

    gsel(0);

    while (true)
    {
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);

        cs_listbk();
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            const auto x = wx + 40;
            const auto y = cnt * 35 + wy + 50;
            display_key(x, y, cnt);
            font(14 - en * 2);
            cs_list(cs == cnt, s(cnt), x + 40, y + 1);
        }
        cs_bk = cs;

        redraw();

        int index{};
        auto action = cursor_check_ex(index);

        if (index == 0)
        {
            snd("core.ok1");
            return MainMenuResult::main_menu_mods_list;
        }
        if (index == 1)
        {
            snd("core.ok1");
            return MainMenuResult::main_menu_mods_develop;
        }

        if (action == "cancel")
        {
            return MainMenuResult::main_title_menu;
        }
    }
}



MainMenuResult main_menu_mods_list()
{
    ui::UIMenuMods().show();
    return MainMenuResult::main_menu_mods;
}



MainMenuResult main_menu_mods_develop()
{
    int template_count = 0;
    int index = 0;
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 16;
    keyrange = 0;

    std::vector<std::pair<std::string, semver::Version>> mod_id_and_versions;
    for (const auto& tmpl : lua::lua->get_mod_manager().get_templates())
    {
        list(0, template_count) = template_count;
        listn(0, template_count) = tmpl.id + " v" + tmpl.version.to_string();
        listn(1, template_count) = tmpl.name;
        mod_id_and_versions.emplace_back(tmpl.id, tmpl.version);
        key_list(template_count) = key_select(template_count);
        ++template_count;
    }
    listmax = template_count;

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
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

            clear_background_in_continue();
            ui_draw_caption(
                i18n::s.get("core.main_menu.mod_develop.lets_create"));
            windowshadow = 1;
        }

        ui_display_window(
            i18n::s.get("core.main_menu.mod_develop.title"),
            i18n::s.get("core.main_menu.mod_develop.key_hint") + strhint2 +
                strhint3b,
            (windoww - 440) / 2 + inf_screenx,
            winposy(288, 1),
            440,
            288);
        cs_listbk();
        keyrange = 0;
        for (int cnt = 0, cnt_end = pagesize; cnt < cnt_end; ++cnt)
        {
            index = pagesize * page + cnt;
            if (index >= listmax)
            {
                break;
            }
            x = wx + 20;
            y = cnt * 40 + wy + 50;
            display_key(x + 20, y - 2, cnt);
            font(11 - en * 2);
            mes(x + 48, y - 4, listn(0, index));
            font(13 - en * 2);
            cs_list(cs == cnt, listn(1, index), x + 48, y + 8);
            ++keyrange;
        }
        cs_bk = cs;
        if (template_count == 0)
        {
            font(14 - en * 2);
            mes(wx + 140,
                wy + 120,
                i18n::s.get("core.main_menu.mod_develop.no_template"));
        }
        redraw();

        int cursor{};
        auto action = cursor_check_ex(cursor);

        p = -1;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            index = pagesize * page + cnt;
            if (index >= listmax)
            {
                break;
            }
            if (cursor == cnt)
            {
                p = list(0, index);
                break;
            }
        }
        if (p != -1)
        {
            inputlog = "";
            const auto canceled = input_text_dialog(
                (windoww - 230) / 2 + inf_screenx, winposy(120), 10, true);
            if (!canceled && !inputlog(0).empty())
            {
                const auto new_mod_id = inputlog(0);
                if (!lua::is_valid_mod_id(new_mod_id))
                {
                    ModCreatePrompt(i18n::s.get(
                                        "core.main_menu.mod_develop.invalid_id",
                                        new_mod_id))
                        .query();
                }
                else if (lua::lua->get_mod_manager().exists(new_mod_id))
                {
                    ModCreatePrompt(
                        i18n::s.get(
                            "core.main_menu.mod_develop.exist", new_mod_id))
                        .query();
                }
                else
                {
                    lua::lua->get_mod_manager().create_mod_from_template(
                        new_mod_id,
                        mod_id_and_versions.at(p).first,
                        mod_id_and_versions.at(p).second);
                    snd("core.write1");
                    ModCreatePrompt(
                        i18n::s.get(
                            "core.main_menu.mod_develop.created", new_mod_id))
                        .query();
                }
                init = true;
                continue;
            }
            continue;
        }
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            return MainMenuResult::main_menu_mods;
        }
    }
}

} // namespace elona
