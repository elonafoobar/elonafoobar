#include "ui_menu_quest_board.hpp"

#include "../../snail/color.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../message.hpp"
#include "../quest.hpp"

namespace elona
{
namespace ui
{

static bool _should_display_quest(int cnt)
{
    if (quest_data[cnt].originating_map_id != game_data.current_map)
    {
        return false;
    }
    if (quest_data[cnt].id == 0)
    {
        return false;
    }
    if (quest_data[cnt].progress != 0)
    {
        return false;
    }
    if (cdata[quest_data[cnt].client_chara_index].state() !=
        Character::State::alive)
    {
        return false;
    }

    return true;
}

static void _populate_quest_list()
{
    quest_refresh_list();

    for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (_should_display_quest(cnt))
        {
            list(0, listmax) = cnt;
            list(1, listmax) = quest_data[cnt].difficulty;
            ++listmax;
        }
    }

    sort_list_by_column1();
}

void UIMenuQuestBoard::_draw_background()
{
    asset_load("core.deco_board");
    gsel(0);
    gsel(4);
    draw_bg("core.deco_board_a");
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
        elona::draw("core.deco_board_b", wx + 20, y + 8);
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
    cs_bk = -1;

    _populate_quest_list();

    if (listmax == 0)
    {
        txt(i18n::s.get("core.ui.board.no_new_notices"));
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

void UIMenuQuestBoard::_draw_window()
{
    s(0) = i18n::s.get("core.ui.board.title");
    s(1) = strhint2 + strhint3b;
    gmode(0);
    gcopy(4, 0, 0, windoww, inf_ver, 0, 0);
    gmode(2);
    font(16 - en * 2);
    bmes(u8"Page "s + (page + 1) + u8"/"s + (pagemax + 1), wx + ww + 20, wy);
}

void UIMenuQuestBoard::_draw_key(int cnt)
{
    boxf(wx + 70, y, 460, 18, {12, 14, 16, 16});
    display_key(wx + 70, y - 2, cnt);
}

void UIMenuQuestBoard::_draw_keys()
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

void UIMenuQuestBoard::_draw_list_entry_title(int cnt, const std::string& title)
{
    font(14 - en * 2);
    cs_list(cs == cnt, title, wx + 96, y - 1, 19);
}

void UIMenuQuestBoard::_draw_list_entry_date(const std::string& date_text)
{
    std::string quest_date = u8"("s + date_text + u8")"s;
    mes(wx + 344, y + 2, quest_date);
}

void UIMenuQuestBoard::_draw_list_entry_giver_name(int chara_index)
{
    const auto name = strutil::take_by_width(cdata[chara_index].name, 20);
    mes(wx + 392, y + 2, name);
}

void UIMenuQuestBoard::_draw_list_entry_difficulty(
    int quest_difficulty,
    int difficulty_stars)
{
    const auto col =
        _get_quest_difficulty_color(cdata.player().level, quest_difficulty);

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
            mes(wx + 270 + cnt % 5 * 13,
                y + dy + cnt / 5 * 8 + 2,
                i18n::s.get("core.ui.board.difficulty"),
                col);
        }
    }
    else
    {
        mes(wx + 270,
            y + 2,
            i18n::s.get("core.ui.board.difficulty_counter", difficulty_stars),
            col);
    }
}

void UIMenuQuestBoard::_draw_list_entry_desc()
{
    talk_conv(buff, 70);
    font(13 - en * 2);
    mes(wx + 20, y + 20, buff);
}

void UIMenuQuestBoard::_draw_list_entry(int cnt, int rq, int giver_index)
{
    quest_set_data(cdata[giver_index], 0);
    int quest_difficulty = quest_data[rq].difficulty / 5 + 1;
    p(1) = 14;

    _draw_list_entry_title(cnt, s(3));
    _draw_list_entry_date(nquestdate);
    _draw_list_entry_giver_name(giver_index);


    _draw_list_entry_difficulty(quest_data[rq].difficulty, quest_difficulty);
    _draw_list_entry_desc();
}

void UIMenuQuestBoard::_draw_list_entries()
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
        _draw_list_entry(cnt, rq, quest_data[rq].client_chara_index);
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
    const std::string& action)
{
    if (auto selected = get_selected_item())
    {
        Message::instance().linebreak();
        txt(i18n::s.get("core.ui.board.do_you_meet"));
        if (!yes_no())
        {
            set_reupdate();
            return none;
        }
        return UIMenuQuestBoard::Result::finish(*selected);
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        return UIMenuQuestBoard::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
