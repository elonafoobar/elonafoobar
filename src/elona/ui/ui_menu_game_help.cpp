#include "ui_menu_game_help.hpp"

#include "../../util/fileutil.hpp"
#include "../../util/strutil.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../keybind/keybind.hpp"



namespace elona
{
namespace ui
{

bool UIMenuGameHelp::init()
{
    // pre - notesel init
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;
    if (mode != 1)
    {
        load_background_variants(4);
        gsel(0);
    }
    else
    {
        cs = 3;
        cs_bk2 = cs;
    }

    list(0, 0) = 0 /* dummy */;
    listn(0, 0) = i18n::s.get("core.ui.manual.keys.list");
    ++listmax;

    _help.load(
        lua::resolve_path_for_mod("<core>/locale/<LANGUAGE>/lazy/manual.txt"));

    for (const auto& section : _help.section_headings())
    {
        list(0, listmax) = listmax - 1;
        listn(0, listmax) = section;
        ++listmax;
    }

    windowshadow = 1;

    update();

    return true;
}



void UIMenuGameHelp::_draw_key_list()
{
    const auto x = wx + 188;
    const auto y = wy + 6;
    const auto desc_font_size = 13 - en * 2;
    const auto key_font_size = 15 - en * 2;

    struct KeyDescPair
    {
        std::string key;
        std::string desc;
    };

    {
        // Section "Item"
        display_topic(
            i18n::s.get("core.ui.manual.keys.item.title"), x + 18, y + 30);

        std::vector<KeyDescPair> keys{
            {keybind_get_bound_key_name("get"),
             i18n::s.get("core.ui.manual.keys.item.get")},
            {keybind_get_bound_key_name("read"),
             i18n::s.get("core.ui.manual.keys.item.read")},
            {keybind_get_bound_key_name("drop"),
             i18n::s.get("core.ui.manual.keys.item.drop")},
            {keybind_get_bound_key_name("zap"),
             i18n::s.get("core.ui.manual.keys.item.zap")},
            {keybind_get_bound_key_name("inventory"),
             i18n::s.get("core.ui.manual.keys.item.examine")},
            {keybind_get_bound_key_name("use"),
             i18n::s.get("core.ui.manual.keys.item.tool")},
            {keybind_get_bound_key_name("wear"),
             i18n::s.get("core.ui.manual.keys.item.wear_wield")},
            {keybind_get_bound_key_name("dip"),
             i18n::s.get("core.ui.manual.keys.item.blend")},
            {keybind_get_bound_key_name("eat"),
             i18n::s.get("core.ui.manual.keys.item.eat")},
            {keybind_get_bound_key_name("throw"),
             i18n::s.get("core.ui.manual.keys.item.throw")},
            {keybind_get_bound_key_name("drink"),
             i18n::s.get("core.ui.manual.keys.item.quaff")},
            {keybind_get_bound_key_name("ammo"),
             i18n::s.get("core.ui.manual.keys.item.ammo")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 58 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 57 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Section "Action"
    {
        display_topic(
            i18n::s.get("core.ui.manual.keys.action.title"), x + 18, y + 142);

        std::vector<KeyDescPair> keys{
            {keybind_get_bound_key_name("search"),
             i18n::s.get("core.ui.manual.keys.action.search")},
            {keybind_get_bound_key_name("target"),
             i18n::s.get("core.ui.manual.keys.action.target")},
            {keybind_get_bound_key_name("cast"),
             i18n::s.get("core.ui.manual.keys.action.cast")},
            {keybind_get_bound_key_name("fire"),
             i18n::s.get("core.ui.manual.keys.action.fire")},
            {keybind_get_bound_key_name("interact"),
             i18n::s.get("core.ui.manual.keys.action.interact")},
            {keybind_get_bound_key_name("skill"),
             i18n::s.get("core.ui.manual.keys.action.apply")},
            {keybind_get_bound_key_name("go_down"),
             i18n::s.get("core.ui.manual.keys.action.go_down")},
            {keybind_get_bound_key_name("bash"),
             i18n::s.get("core.ui.manual.keys.action.bash")},
            {keybind_get_bound_key_name("go_up"),
             i18n::s.get("core.ui.manual.keys.action.go_up")},
            {keybind_get_bound_key_name("dig"),
             i18n::s.get("core.ui.manual.keys.action.dig")},
            {keybind_get_bound_key_name("wait"),
             i18n::s.get("core.ui.manual.keys.action.wait")},
            {keybind_get_bound_key_name("open"),
             i18n::s.get("core.ui.manual.keys.action.open")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 170 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 169 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Section "Info"
    {
        display_topic(
            i18n::s.get("core.ui.manual.keys.info.title"), x + 18, y + 256);

        std::vector<KeyDescPair> keys{
            {keybind_get_bound_key_name("chara_info"),
             i18n::s.get("core.ui.manual.keys.info.chara")},
            {keybind_get_bound_key_name("message_log"),
             i18n::s.get("core.ui.manual.keys.info.log")},
            {keybind_get_bound_key_name("journal"),
             i18n::s.get("core.ui.manual.keys.info.journal")},
            {keybind_get_bound_key_name("material"),
             i18n::s.get("core.ui.manual.keys.info.material")},
            {keybind_get_bound_key_name("help"),
             i18n::s.get("core.ui.manual.keys.info.help")},
            {keybind_get_bound_key_name("trait"),
             i18n::s.get("core.ui.manual.keys.info.feat")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 284 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 283 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Section "Other"
    {
        display_topic(
            i18n::s.get("core.ui.manual.keys.other.title"), x + 18, y + 328);

        std::vector<KeyDescPair> keys{
            {keybind_get_bound_key_name("save"),
             i18n::s.get("core.ui.manual.keys.other.save")},
            {keybind_get_bound_key_name("close"),
             i18n::s.get("core.ui.manual.keys.other.close")},
            {keybind_get_bound_key_name("pray"),
             i18n::s.get("core.ui.manual.keys.other.pray")},
            {keybind_get_bound_key_name("give"),
             i18n::s.get("core.ui.manual.keys.other.give")},
            {keybind_get_bound_key_name("offer"),
             i18n::s.get("core.ui.manual.keys.other.offer")},
        };

        int index = 0;
        for (const auto& pair : keys)
        {
            font(desc_font_size);
            mes(x + 38 + index % 2 * 290, y + 356 + index / 2 * 14, pair.desc);
            font(key_font_size);
            mes(x + 248 + index % 2 * 290, y + 355 + index / 2 * 14, pair.key);
            ++index;
        }
    }

    // Misc.
    // TODO: support key bindings!
    const auto misc_keys = u8"F9 "s +
        i18n::s.get("core.ui.manual.keys.other.hide_interface") + u8"  F11 " +
        i18n::s.get("core.ui.manual.keys.other.export_chara_sheet") +
        u8"  F12 " + i18n::s.get("core.ui.manual.keys.other.console");
    font(desc_font_size);
    mes(x + 38, y + 408, misc_keys);
}



void UIMenuGameHelp::_draw_regular_pages()
{
    const auto& topic = listn(0, pagesize * page_bk + cs_bk2);
    display_topic(topic, wx + 206, wy + 36);

    font(14 - en * 2);
    const auto section_index = list(0, pagesize * page_bk + cs_bk2);
    int y = wy + 60;
    for (const auto& line : _help.get_section(section_index))
    {
        const auto ny = gmes(line, wx + 216, y, 510, {30, 30, 30}, false).y;
        y = ny;
    }
}



void UIMenuGameHelp::_draw_navigation_menu()
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
        const auto& section = listn(0, p);
        cs_list(cs == cnt, section, wx + 66, wy + 66 + cnt * 19 - 1);
    }

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



void UIMenuGameHelp::_draw_background_vignette(int id, int type)
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



void UIMenuGameHelp::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;

    _redraw = true;
}


void UIMenuGameHelp::_draw_window()
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
        u8"Elona In-Game Help",
        strhint2 + strhint3b,
        (windoww - 780) / 2 + inf_screenx,
        y,
        780,
        496);
    display_topic(i18n::s.get("core.ui.manual.topic"), wx + 34, wy + 36);

    _draw_background_vignette(page % 5, mode == 1 ? 2 : 4);
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

    // Draws the first page, key lists, in a specific way
    if (cs_bk2 == 0 && page_bk == 0)
        _draw_key_list();
    else
        _draw_regular_pages();
}



void UIMenuGameHelp::draw()
{
    if (_redraw)
    {
        _draw_window();
        _draw_navigation_menu();
        _redraw = false;
    }
}



optional<UIMenuGameHelp::ResultType> UIMenuGameHelp::on_key(
    const std::string& action)
{
    // Key selection
    if (auto selected = get_selected_index_this_page())
    {
        cs = *selected;
        snd("core.ok1");
        page_bk = page;
        cs_bk2 = cs;
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
        return UIMenuGameHelp::ResultType::finish();
    }
    return none;
}



void UIMenuGameHelp::GameHelp::load(const fs::path& filepath)
{
    constexpr const char* section_marker = u8"{}";

    for (const auto& line : fileutil::read_by_line(filepath))
    {
        const auto section_marker_pos = line.find(section_marker);
        if (section_marker_pos != std::string::npos)
        {
            _section_headings.emplace_back(line, section_marker_pos + 3);
            _sections.emplace_back();
        }
        else
        {
            if (_sections.empty())
            {
                continue; // Skip this line.
            }
            _sections.back().push_back(line);
        }
    }
}

} // namespace ui
} // namespace elona
