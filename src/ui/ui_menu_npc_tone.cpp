#include "ui_menu_npc_tone.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

const constexpr int _default_tone_index = -999;

static int _load_talk_entries()
{
    int _listmax = 0;

    list(0, 0) = _default_tone_index;
    listn(0, 0) =
        i18n::s.get("core.locale.action.interact.change_tone.default_tone");

    ++_listmax;
    const auto base_dir = filesystem::dir::user() / u8"talk";
    for (const auto& entry : filesystem::dir_entries(
             base_dir,
             filesystem::DirEntryRange::Type::file,
             std::regex{u8R"(.*\.txt)"}))
    {
        list(0, _listmax) = _listmax;
        listn(0, _listmax) =
            filesystem::to_utf8_path(fs::relative(entry.path(), base_dir));
        ++_listmax;
    }

    return _listmax;
}

bool UIMenuNPCTone::init()
{
    load_background_variants(4);
    gsel(0);
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    windowshadow = 1;

    listmax = _load_talk_entries();

    return true;
}

void UIMenuNPCTone::update()
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
}

void UIMenuNPCTone::draw()
{
    s(0) = i18n::s.get("core.locale.action.interact.change_tone.title");
    s(1) = i18n::s.get("core.locale.action.interact.change_tone.hint")
        + strhint2 + strhint3;
    display_window((windoww - 500) / 2 + inf_screenx, winposy(400), 500, 400);

    x = ww / 5 * 3;
    y = wh - 80;
    pos(wx + ww / 3 * 2, wy + wh / 2);
    gmode(4, 50);
    gcopy_c(4, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);

    gmode(2);
    display_topic(
        i18n::s.get("core.locale.action.interact.change_tone.tone_title"),
        wx + 28,
        wy + 36);

    keyrange = 0;

    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 66 + cnt * 19, ww - 100, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
    }

    gmode(2);
    font(14 - en * 2);
    cs_listbk();

    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        s = ""s + listn(0, p);
        cs_list(cs == cnt, s, wx + 138, wy + 66 + cnt * 19 - 1);
    }

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<UIMenuNPCTone::ResultType> UIMenuNPCTone::on_key(
    const std::string& action)
{
    p = -1;
    // ELONA_GET_SELECTED_ITEM(p, cs = i);

    // if (_index != -1)
    // {
    //     cs = _index;
    //     p = list(0, pagesize * page + _index);
    // }

    if (auto selected = get_selected_item())
    {
        cs = _index;
        if (*selected == _default_tone_index)
        {
            return UIMenuNPCTone::ResultType::finish();
        }
        else
        {
            std::string chosen = listn(0, *selected);
            return UIMenuNPCTone::ResultType::finish(chosen);
        }
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        return UIMenuNPCTone::ResultType::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
