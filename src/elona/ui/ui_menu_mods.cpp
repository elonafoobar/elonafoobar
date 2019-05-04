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
    page_bk = -1;
    cs_bk2 = 0;

    asset_load("void");
    ::draw("void", 0, 0, windoww, windowh);
    gsel(0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);

    for (const auto& mod : lua::lua->get_mod_manager().all_mods())
    {
        const auto& name = mod->second->manifest.id;

        if (lua::ModManager::mod_id_is_reserved(name))
            continue;

        ModDescription mod_desc{
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


optional<ModDescription> UIMenuMods::_find_enabled_mod(const std::string& name)
{
    for (const auto& desc : _mod_descriptions)
    {
        if (desc.enabled && desc.manifest.id == name)
            return desc;
    }
    return none;
}



void UIMenuMods::update()
{
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;

    cs_bk = -1;
    page_bk = page;

    _redraw = true;
}



void UIMenuMods::_draw_key(int cnt, int index)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 57, wy + 66 + cnt * 19, 640, 18, {12, 14, 16, 16});
    }

    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}



void UIMenuMods::_draw_window()
{
    int y;
    y = winposy(466) - 24;
    ui_display_window(
        i18n::s.get("core.locale.main_menu.mods.title"),
        strhint2 + strhint3b + " " + key_prev + ","s + key_next + " " +
            i18n::s.get("core.locale.main_menu.mods.hint_readme_page"),
        (windoww - 730) / 2 + inf_screenx,
        y,
        730,
        530);

    // Moves and refresh cursor
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
            break;
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        _draw_key(cnt, index);
    }

    display_topic(
        i18n::s.get("core.locale.main_menu.mods.name"), wx + 46, wy + 36);
    display_topic(
        i18n::s.get("core.locale.main_menu.mods.version"), wx + 255, wy + 36);
}



void UIMenuMods::_draw_mod_list()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }
        const auto& desc = _mod_descriptions.at(index);
        snail::Color text_color = {0, 0, 0};
        if (desc.enabled)
        {
            text_color = {0, 0, 255};
        }

        cs_list(
            cs == cnt,
            desc.manifest.id,
            wx + 84,
            wy + 66 + cnt * 19 - 1,
            0,
            text_color);
        mes(wx + 270,
            wy + 66 + cnt * 19 - 1,
            desc.manifest.version.to_string(),
            {0, 0, 0});
    }

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



void UIMenuMods::draw()
{
    if (_redraw)
    {
        _draw_window();
        _draw_mod_list();
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

    // Closing menu
    if (action == "cancel")
    {
        return UIMenuMods::ResultType::finish();
    }
    return none;
}

} // namespace ui
} // namespace elona
