#include "ui_menu_journal.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../character.hpp"
#include "../i18n.hpp"
#include "../quest.hpp"

namespace elona
{
namespace ui
{

bool UIMenuJournal::init()
{
    curmenu = 1;
    page = 99;
    pagesize = 40;
    cs = 0;
    cc = 0;
    keyrange = 0;
    key_list(0) = key_enter;
    buff = newsbuff;
    if (newsbuff == ""s)
    {
        buff = u8"No news"s;
    }
    notesel(buff);
    noteadd(u8" - News - "s, 0);
    noteadd(""s, 1);
    if (noteinfo() / (pagesize / 2) % 2 == 1)
    {
        for (int cnt = 0, cnt_end = (pagesize / 2); cnt < cnt_end; ++cnt)
        {
            noteadd(""s, 2);
        }
    }
    page = noteinfo() / pagesize;
    for (int cnt = 0,
             cnt_end = cnt + (pagesize / 2 - noteinfo() % (pagesize / 2));
         cnt < cnt_end;
         ++cnt)
    {
        noteadd(""s);
    }
    noteadd(u8" - Quest - "s);
    noteadd(""s);
    quest_update_main_quest_journal();
    for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (qdata(8, cnt) == 0)
        {
            continue;
        }
        rq = cnt;
        quest_set_data(2);
    }
    append_subquest_journal(0);
    for (int cnt = 0,
             cnt_end = cnt + (pagesize / 2 - noteinfo() % (pagesize / 2));
         cnt < cnt_end;
         ++cnt)
    {
        noteadd(""s);
    }
    noteadd(u8" - Quest Item - "s);
    noteadd(""s);
    append_quest_item_journal();
    for (int cnt = 0,
             cnt_end = cnt + (pagesize / 2 - noteinfo() % (pagesize / 2));
         cnt < cnt_end;
         ++cnt)
    {
        noteadd(""s);
    }
    gold = 0;
    p = clamp(cdata.player().fame / 10, 100, 25000);
    if (cdata.player().fame >= 25000)
    {
        p += (cdata.player().fame - 25000) / 100;
    }
    gold += p;
    noteadd(u8" - Title & Ranking - "s);
    noteadd(""s);
    noteadd(
        i18n::s.get("core.locale.ui.journal.rank.fame") + ": "
        + cdata.player().fame);
    noteadd(""s);
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        if (gdata(120 + cnt) < 10000)
        {
            noteadd(
                ""s + ranktitle(cnt) + u8" Rank."s + gdata((120 + cnt)) / 100);
            s = i18n::s.get("core.locale.ui.journal.rank.pay", calcincome(cnt));
            gold += calcincome(cnt);
            if (cnt != 3 && cnt != 4 && cnt != 5 && cnt != 8)
            {
                s += i18n::s.get(
                    "core.locale.ui.journal.rank.deadline", gdata(140 + cnt));
            }
            noteadd(s);
            noteadd(""s);
        }
    }
    noteadd(i18n::s.get(
        "core.locale.ui.journal.rank.arena",
        gdata(802),
        cnvrank(gdata_ex_arena_level)));
    noteadd(""s);
    for (int cnt = 0,
             cnt_end = cnt + (pagesize / 2 - noteinfo() % (pagesize / 2));
         cnt < cnt_end;
         ++cnt)
    {
        noteadd(""s);
    }
    noteadd(u8" - Income & Expense - "s);
    noteadd(""s);
    noteadd(i18n::s.get("core.locale.ui.journal.income.salary.title"));
    noteadd(i18n::s.get("core.locale.ui.journal.income.salary.sum", gold));
    noteadd(""s);
    noteadd(i18n::s.get("core.locale.ui.journal.income.bills.title"));
    noteadd(i18n::s.get(
        "core.locale.ui.journal.income.bills.labor", game_data.cost_to_hire));
    noteadd(i18n::s.get(
        "core.locale.ui.journal.income.bills.maintenance", calccostbuilding()));
    noteadd(
        i18n::s.get("core.locale.ui.journal.income.bills.tax", calccosttax()));
    noteadd(i18n::s.get(
        "core.locale.ui.journal.income.bills.sum",
        (game_data.cost_to_hire + calccostbuilding() + calccosttax())));
    noteadd(""s);
    noteadd(i18n::s.get(
        "core.locale.ui.journal.income.bills.unpaid", game_data.left_bill));
    for (int cnt = 0,
             cnt_end = cnt + (pagesize / 2 - noteinfo() % (pagesize / 2));
         cnt < cnt_end;
         ++cnt)
    {
        noteadd(""s);
    }
    noteadd(u8" - Completed Quests - "s);
    noteadd(""s);
    append_subquest_journal(1);
    listmax = noteinfo();
    show_title(strhint2 + strhint3);
    wx = (windoww - 736) / 2 + inf_screenx;
    wy = winposy(448);
    snd(59);
    window_animation(wx, wy, 736, 448, 9, 4);

    return true;
}

void UIMenuJournal::update()
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
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"book.bmp", 1);
    gsel(0);
    pos(wx, wy);
    gcopy(4, 0, 0, 736, 448);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        x = wx + 80 + cnt / 20 * 306;
        y = wy + 45 + cnt % 20 * 16;
        noteget(s, p);
        if (strmid(s, 0, 1) == u8"@"s)
        {
            s(1) = strmid(s, 1, 2);
            s = strmid(s, 3, s(0).size() - 3);
            font(10 + en - en * 2, snail::Font::Style::bold);
            color(0, 0, 200);
            if (s(1) == u8"QL"s)
            {
                color(100, 100, 0);
            }
            if (s(1) == u8"QC"s)
            {
                color(0, 100, 100);
            }
            if (s(1) == u8"QM"s)
            {
                color(0, 100, 0);
            }
            if (s(1) == u8"RE"s)
            {
                color(100, 0, 0);
                font(12 + sizefix - en * 2);
            }
            if (s(1) == u8"BL"s)
            {
                color(0, 0, 100);
                font(12 + sizefix - en * 2);
            }
        }
        else
        {
            font(12 + sizefix - en * 2);
        }
        pos(x, y);
        mes(s);
        color(0, 0, 0);
        if (p % 20 == 0)
        {
            font(12 + sizefix - en * 2, snail::Font::Style::bold);
            pos(x + 90, y + 330);
            mes(u8"- "s + (p / 20 + 1) + u8" -"s);
            if (p % 40 == 20)
            {
                if (page < pagemax)
                {
                    pos(x + 200, y + 330);
                    mes(u8"(more)"s);
                }
            }
        }
    }
}

void UIMenuJournal::draw()
{
}

optional<UIMenuJournal::ResultType> UIMenuJournal::on_key(
    const std::string& key)
{
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(71);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(71);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel || key == key_enter)
    {
        menucycle = 0;
        update_screen();
        return UIMenuJournal::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
