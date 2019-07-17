#include "ui_menu_mods.hpp"

#include "../../util/fileutil.hpp"
#include "../../util/strutil.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../lua_env/mod_manager.hpp"
#include "simple_prompt.hpp"
#include "ui_menu_mod_info.hpp"



namespace elona
{
namespace ui
{

bool UIMenuMods::init()
{
    snd("core.pop2");

    _is_download = false;
    _load_mods();

    update();

    return true;
}


class DownloadModsInitPrompt : public SimplePrompt<DummyResult>
{
public:
    DownloadModsInitPrompt(std::string message)
        : SimplePrompt(message)
    {
    }

protected:
    optional<DummyResult> update() override
    {
        await(Config::instance().general_wait);
        auto action = key_check();

        if (action != ""s)
        {
            return DummyResult{};
        }

        return none;
    }
};


void UIMenuMods::_load_mods()
{
    // Redraw background as topic size can change, leaving marks
    asset_load("void");
    ::draw("void", 0, 0, windoww, windowh);
    gsel(0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);

    _mod_descriptions.clear();

    listmax = 0;
    page = 0;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = -1;
    cs_bk2 = 0;
    pagesize = 18;

    windowshadow = 1;

    if (_is_download)
    {
        draw();
        DownloadModsInitPrompt(
            i18n::s.get("core.main_menu.mod_list.download.failed"))
            .query();
        _is_download = false;
        _load_mods();
    }
    else
    {
        for (const auto& mod : lua::lua->get_mod_manager().all_mods())
        {
            const auto& id = mod->second->manifest.id;

            if (lua::ModManager::mod_id_is_reserved(id))
                continue;

            ModDescription mod_desc{
                mod->second->manifest,
                static_cast<bool>(
                    lua::lua->get_mod_manager().get_enabled_version(id))};

            _mod_descriptions.emplace_back(mod_desc);
            listmax++;
        }
    }
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
    auto hint = ""s + key_enter + " " +
        i18n::s.get("core.main_menu.mod_list.hint.toggle") + "  " +
        key_identify + " " + i18n::s.get("core.main_menu.mod_list.hint.info");

    if (_is_download)
    {
        hint += "  " + key_mode + " " +
            i18n::s.get("core.main_menu.mod_list.hint.installed");
    }
    else
    {
        hint += "  " + key_mode + " " +
            i18n::s.get("core.main_menu.mod_list.hint.download");
    }


    std::string title;
    if (_is_download)
    {
        title = i18n::s.get("core.main_menu.mod_list.title.download");
    }
    else
    {
        title = i18n::s.get("core.main_menu.mod_list.title.installed");
    }

    ui_display_window(
        title,
        strhint2 + strhint3b + hint,
        (windoww - 730) / 2 + inf_screenx,
        winposy(510, 1),
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
        i18n::s.get("core.main_menu.mod_list.info.name"), wx + 46, wy + 36);
    display_topic(
        i18n::s.get("core.main_menu.mod_list.info.version"), wx + 255, wy + 36);
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
            desc.manifest.name,
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
    if (action == "identify")
    {
        const auto& desc = _mod_descriptions.at(pagesize * page + cs);

        int cs_prev = cs;
        int page_prev = page;
        int listmax_prev = listmax;
        int pagesize_prev = pagesize;

        lib::scope_guard restore([&]() {
            cs = cs_prev;
            page_prev = page;
            listmax = listmax_prev;
            pagesize = pagesize_prev;
        });

        UIMenuModInfo(desc).show();

        set_reupdate();
    }
    if (action == "switch_mode")
    {
        cs = 0;
        _is_download = !_is_download;
        _load_mods();
        set_reupdate();
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
