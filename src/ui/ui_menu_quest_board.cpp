#include "ui_menu_quest_board.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../quest.hpp"
#include "../snail/color.hpp"

namespace elona
{
namespace ui
{

static bool _should_display_quest(int cnt)
{
    if (qdata(1, cnt) != gdata_current_map)
    {
        return false;
    }
    if (qdata(3, cnt) == 0)
    {
        return false;
    }
    if (qdata(8, cnt) != 0)
    {
        return false;
    }
    rc = qdata(0, cnt);
    if (cdata[rc].state() != Character::State::alive)
    {
        return false;
    }

    return true;
}

static void _populate_quest_list()
{
    quest_refresh_list();

    for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (_should_display_quest(cnt))
        {
            list(0, listmax) = cnt;
            list(1, listmax) = qdata(5, cnt);
            ++listmax;
        }
    }

    sort_list_by_column1();
}

static void _draw_background()
{
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_board.bmp", 1);
    gsel(0);
    gsel(4);
    fillbg(3, 960, 96, 128, 128);
    ww = 560;
    int h = 140;
    wh = h * 4;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        y = wy + cnt * 120;
        window(wx + 4, y + 4, ww, h, true);
        window(wx, y, ww, h);
        pos(wx + 20, y + 8);
        gcopy(3, 960, 240, 48, 84);
    }
    render_hud();
    gsel(0);
}

bool UIMenuQuestBoard::init()
{
    listmax = 0;
    page = 0;
    pagesize = 4;
    cs = 0;
    cc = 0;
    cs_bk = -1;

    _populate_quest_list();

    if (listmax == 0)
    {
        txt(i18n::s.get("core.locale.ui.board.no_new_notices"));
        return false;
    }

    _draw_background();

    return true;
}

void UIMenuQuestBoard::update()
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

static void _draw_window()
{
    s(0) = i18n::s.get("core.locale.ui.board.title");
    s(1) = strhint2 + strhint3b;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, inf_ver);
    gmode(2);
    font(16 - en * 2);
    bmes(u8"Page "s + (page + 1) + u8"/"s + (pagemax + 1), wx + ww + 20, wy);
}

static void _draw_key(int cnt)
{
    boxf(wx + 70, y, 460, 18, {12, 14, 16, 16});
    display_key(wx + 70, y - 2, cnt);
}

static void _draw_keys()
{
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        y = wy + cnt * 120 + 20;
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        _draw_key(cnt);
    }
}

static snail::Color _get_quest_difficulty_color(
    int player_level,
    int quest_difficulty)
{
    if (player_level * 2 < quest_difficulty)
    {
        return {205, 0, 0};
    }
    else if (player_level * 3 / 2 < quest_difficulty)
    {
        return {140, 80, 0};
    }
    else if (player_level < quest_difficulty)
    {
        return {0, 0, 205};
    }
    else
    {
        return {0, 155, 0};
    }
}

static void _draw_list_entry_title(int cnt, const std::string& title)
{
    font(14 - en * 2);
    cs_list(cs == cnt, title, wx + 96, y - 1, 19);
}

static void _draw_list_entry_date(const std::string& date_text)
{
    std::string quest_date = u8"("s + date_text + u8")"s;
    pos(wx + 344, y + 2);
    mes(quest_date);
}

static void _draw_list_entry_giver_name(int chara_index)
{
    std::string name = cdatan(0, chara_index);
    cutname(name, 20);
    pos(wx + 392, y + 2);
    mes(name);
}

static void _draw_list_entry_difficulty(
    int quest_difficulty,
    int difficulty_stars)
{
    auto col =
        _get_quest_difficulty_color(cdata.player().level, quest_difficulty);
    color(col.r, col.g, col.b);

    if (difficulty_stars < 11)
    {
        dy = 0;
        if (difficulty_stars > 5)
        {
            font(10 - en * 2);
            dy = -3;
        }
        for (int cnt = 0, cnt_end = (difficulty_stars); cnt < cnt_end; ++cnt)
        {
            pos(wx + 270 + cnt % 5 * 13, y + dy + cnt / 5 * 8 + 2);
            mes(i18n::s.get("core.locale.ui.board.difficulty"));
        }
    }
    else
    {
        pos(wx + 270, y + 2);
        mes(i18n::s.get(
            "core.locale.ui.board.difficulty_counter", difficulty_stars));
    }
}

static void _draw_list_entry_desc()
{
    talk_conv(buff, 70);
    color(0, 0, 0);
    font(13 - en * 2);
    pos(wx + 20, y + 20);
    mes(buff);
}

static void _draw_list_entry(int cnt, int rq, int tc)
{
    quest_set_data(0);
    int quest_difficulty = qdata(5, rq) / 5 + 1;
    p(1) = 14;

    _draw_list_entry_title(cnt, s(3));
    _draw_list_entry_date(nquestdate);
    _draw_list_entry_giver_name(tc);


    _draw_list_entry_difficulty(qdata(5, rq), quest_difficulty);
    _draw_list_entry_desc();
}

static void _draw_list_entries()
{
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        y = wy + cnt * 120 + 20;
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }

        rq = list(0, index);
        tc = qdata(0, rq);

        _draw_list_entry(cnt, rq, tc);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuQuestBoard::draw()
{
    _draw_window();
    _draw_keys();
    _draw_list_entries();
}

optional<UIMenuQuestBoard::ResultType> UIMenuQuestBoard::on_key(
    const std::string& key)
{
    int _p;

    ELONA_GET_SELECTED_ITEM(_p, 0);

    if (_p != -1)
    {
        txtnew();
        txt(i18n::s.get("core.locale.ui.board.do_you_meet"));
        ELONA_YES_NO_PROMPT();
        rtval = show_prompt(promptx, prompty, 160);
        if (rtval != 0)
        {
            set_reupdate();
            return none;
        }
        return UIMenuQuestBoard::Result::finish(_p);
    }
    else if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel)
    {
        return UIMenuQuestBoard::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
