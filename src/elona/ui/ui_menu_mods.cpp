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

static int _wrap_text(std::string& text, int max_line_length)
{
    std::string rest{text};
    text.clear();
    int n{};

    while (1)
    {
        const auto len = rest.size();
        if (int(len) < max_line_length)
        {
            text += rest;
            return n;
        }
        size_t byte_length = 0;
        size_t width_length = 0;
        while (width_length <= len)
        {
            const auto bytes = strutil::byte_count(rest[byte_length]);
            const auto char_width = bytes == 1 ? 1 : 2;

            byte_length += bytes;
            width_length += char_width;

            if (int(width_length) > max_line_length)
            {
                text += rest.substr(0, byte_length) + '\n';
                ++n;
                if (rest.size() > byte_length)
                {
                    rest = rest.substr(byte_length);
                }
                else
                {
                    rest = "";
                }
                break;
            }
        }
    }
}

bool UIMenuMods::init()
{
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = -1;
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
        const auto& name = mod->second->manifest.name;

        if (lua::ModManager::mod_name_is_reserved(name))
            continue;

        ModDescription mod_desc{
            name + "(" + mod->second->manifest.version.to_string() + ")",
            mod->second->manifest,
            static_cast<bool>(
                lua::lua->get_mod_manager().get_enabled_version(name))};

        _mod_descriptions.emplace_back(mod_desc);
        listmax++;
    }

    windowshadow = 1;

    update();

    return true;
}


optional<UIMenuMods::ModDescription> UIMenuMods::_find_enabled_mod(
    const std::string& name)
{
    for (const auto& desc : _mod_descriptions)
    {
        if (desc.enabled && desc.manifest.name == name)
            return desc;
    }
    return none;
}

void UIMenuMods::_build_description()
{
    _description_pages.clear();
    _desc_page = 0;

    const auto& desc = _mod_descriptions.at(pagesize * page + cs);

    auto readme_path =
        filesystem::dir::for_mod(desc.manifest.name) / "README.txt";
    if (!fs::exists(readme_path))
    {
        // TODO
        _description_pages.push_back(
            i18n::s.get("core.locale.main_menu.mods.no_readme"));
        return;
    }

    std::vector<std::string> description_lines;
    range::copy(
        fileutil::read_by_line(readme_path),
        std::back_inserter(description_lines));

    if (description_lines.empty())
    {
        // TODO
        _description_pages.push_back(
            i18n::s.get("core.locale.main_menu.mods.no_readme"));
        return;
    }

    const size_t text_width = 70;
    constexpr size_t lines_per_page = 20;

    for (auto&& line : description_lines)
    {
        _wrap_text(line, text_width);
    }
    size_t line_count = 0;
    for (const auto& lines : description_lines)
    {
        if (lines == "")
        {
            _description_pages.back() += '\n';
        }
        for (const auto& line : strutil::split_lines(lines))
        {
            if (line_count == 0)
            {
                _description_pages.push_back(line + '\n');
            }
            else
            {
                _description_pages.back() += line + '\n';
            }
            ++line_count;
            if (line_count == lines_per_page)
            {
                line_count = 0;
            }
        }
    }
}


void UIMenuMods::_draw_mod_page()
{
    const auto& desc = _mod_descriptions.at(pagesize * page + cs);

    display_topic(desc.display_name, wx + 206, wy + 36);

    int y = wy + 60;

    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.name") + ":<def> " +
            desc.manifest.name,
        wx + 216,
        y,
        380,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.author") + ":<def> " +
            desc.manifest.author,
        wx + 216,
        y + 16,
        380,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.version") + ":<def> " +
            desc.manifest.version.to_string(),
        wx + 216,
        y + 32,
        380,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.description") +
            ":<def> " + desc.manifest.description,
        wx + 216,
        y + 48,
        380,
        {30, 30, 30},
        false);

    window2(wx + 216 + 386 + 12 - 4, y - 36 - 4, 128 + 8, 128 + 8, 1, 1);
    boxf(wx + 216 + 386 + 12, y - 36, 128, 128, {0, 0, 0});
    mes(wx + 216 + 366 + 64 + 6, y - 36 + 64 - 7, "(image)", {255, 255, 255});

    display_topic(
        "README (" + std::to_string(_desc_page + 1) + "/" +
            _description_pages.size() + ")",
        wx + 206,
        wy + 160);

    font(14 - en * 2);
    mes(wx + 216, wy + 184, _description_pages.at(_desc_page));
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
        const auto& desc = _mod_descriptions.at(p);
        snail::Color color = {0, 0, 0};
        if (desc.enabled)
        {
            color = {0, 0, 255};
        }

        auto name = desc.display_name;
        cutname(name, 17);

        cs_list(cs == cnt, name, wx + 66, wy + 66 + cnt * 19 - 1, 0, color);
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
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;

    if (page_bk != page || cs_bk != cs)
    {
        _build_description();
    }

    cs_bk = -1;
    page_bk = page;

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
        i18n::s.get("core.locale.main_menu.mods.title"),
        strhint2 + strhint3b + " " + key_prev + ","s + key_next + " " +
            i18n::s.get("core.locale.main_menu.mods.hint_readme_page"),
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
        auto& desc = _mod_descriptions.at(pagesize * page + cs);
        if (cs_bk == cs)
        {
            snd("core.ok1");
            desc.enabled = !desc.enabled;
        }
        else
        {
            snd("core.pop1");
        }
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
    if (action == "next_menu")
    {
        if (_description_pages.size() != 0)
        {
            snd("core.pop1");
            _desc_page = (_desc_page + 1) % _description_pages.size();
            set_reupdate();
        }
    }
    if (action == "previous_menu")
    {
        if (_description_pages.size() != 0)
        {
            snd("core.pop1");
            _desc_page = (_desc_page - 1) % _description_pages.size();
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
