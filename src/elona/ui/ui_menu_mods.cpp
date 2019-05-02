#include "ui_menu_mods.hpp"

#include "../../util/fileutil.hpp"
#include "../../util/strutil.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../lua_env/mod_manager.hpp"



namespace elona
{
namespace ui
{

bool UIMenuMods::init()
{
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;

    asset_load("void");
    ::draw("void", 0, 0, windoww, windowh);
    load_background_variants(2);
    gsel(0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);

    for (const auto& mod : lua::lua->get_mod_manager().all_mods())
    {
        if (mod->second->manifest.name == "_CONSOLE_")
            continue;

        ModDescription mod_desc{mod->second->manifest.name + "(" +
                                    mod->second->manifest.version.to_string() +
                                    ")",
                                mod->second->manifest,
                                mod->second->enabled};

        mod_descriptions.emplace_back(mod_desc);
        listmax++;
    }

    windowshadow = 1;

    update();

    return true;
}



void UIMenuMods::_draw_mod_page()
{
    const auto& desc = mod_descriptions.at(pagesize * page + cs);

    display_topic(desc.display_name, wx + 206, wy + 36);

    font(14 - en * 2);
    int y = wy + 60;

    gmes(
        "<b>Name<def>: " + desc.manifest.name,
        wx + 216,
        y,
        380,
        {30, 30, 30},
        false);
    gmes(
        "<b>Author:<def> " + desc.manifest.author,
        wx + 216,
        y + 16,
        380,
        {30, 30, 30},
        false);
    gmes(
        "<b>Version:<def> " + desc.manifest.version.to_string(),
        wx + 216,
        y + 32,
        380,
        {30, 30, 30},
        false);
    gmes(
        "<b>Description:<def> " + desc.manifest.description,
        wx + 216,
        y + 48,
        380,
        {30, 30, 30},
        false);

    window2(wx + 216 + 386 + 12 - 4, y - 36 - 4, 128 + 8, 128 + 8, 1, 1);
    boxf(wx + 216 + 386 + 12, y - 36, 128, 128, {0, 0, 0});

    display_topic("Description", wx + 206, wy + 160);

    y = wy + 184;

    auto readme_path =
        filesystem::dir::for_mod(desc.manifest.name) / "README.md";
    if (fs::exists(readme_path))
    {
        std::vector<std::string> credits_text_lines;
        range::copy(
            fileutil::read_by_line(readme_path),
            std::back_inserter(credits_text_lines));
        const size_t text_width = 75 - 28;
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
            if (lines == "")
            {
                y = gmes(lines, wx + 216, y, 510, {30, 30, 30}, false).y;
            }
            for (const auto& line : strutil::split_lines(lines))
            {
                const auto ny =
                    gmes(line, wx + 216, y, 510, {30, 30, 30}, false).y;
                ++line_count;
                if (line_count == lines_per_page)
                {
                    return;
                    line_count = 0;
                }
                y = ny;
            }
        }
    }
    else
    {
        gmes(
            "(No description available.)",
            wx + 216,
            y,
            510,
            {30, 30, 30},
            false);
    }
}



void UIMenuMods::_draw_navigation_menu()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        const auto& desc = mod_descriptions.at(p);
        snail::Color color = {0, 0, 0};
        if (desc.enabled)
        {
            color = {0, 0, 255};
        }

        cs_list(
            cs == cnt,
            desc.display_name,
            wx + 66,
            wy + 66 + cnt * 19 - 1,
            0,
            color);
    }

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



void UIMenuMods::_draw_background_vignette(int id, int type)
{
    cmbg = id;
    x = ww / 5 * 2;
    y = wh - 80;
    gmode(2, 50);
    gcopy_c(
        type,
        cmbg % 4 * 180,
        cmbg / 4 % 2 * 300,
        180,
        300,
        wx + ww / 4,
        wy + wh / 2,
        x,
        y);
    gmode(2);
}



void UIMenuMods::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;

    _redraw = true;
}



void UIMenuMods::_draw_window()
{
    int y;
    if (mode == 1)
    {
        y = winposy(496, 1);
    }
    else
    {
        y = winposy(496) - 24;
    }
    ui_display_window(
        u8"Mod List",
        strhint2 + strhint3b,
        (windoww - 780) / 2 + inf_screenx,
        y,
        780,
        580);
    display_topic(i18n::s.get("core.locale.ui.manual.topic"), wx + 34, wy + 36);

    _draw_background_vignette(page % 5, 2);
    keyrange = 0;

    // Moves and refresh cursor
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
            break;
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
    }

    _draw_mod_page();
}



void UIMenuMods::draw()
{
    if (_redraw)
    {
        _draw_window();
        _draw_navigation_menu();
        _redraw = false;
    }
}



optional<UIMenuMods::ResultType> UIMenuMods::on_key(const std::string& action)
{
    // Key selection
    if (auto selected = get_selected_index_this_page())
    {
        cs = *selected;
        snd("core.ok1");
        auto& desc = mod_descriptions.at(pagesize * page + cs_bk);
        desc.enabled = !desc.enabled;
        set_reupdate();
    }

    if (cs != cs_bk)
    {
        set_reupdate();
    }

    // Page changes
    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }

    // Closing menu
    if (action == "cancel")
    {
        return UIMenuMods::ResultType::finish();
    }
    return none;
}

} // namespace ui
} // namespace elona
