#include "ui_menu_journal.hpp"

#include "../audio.hpp"
#include "../building.hpp"
#include "../calc.hpp"
#include "../character.hpp"
#include "../data/types/type_asset.hpp"
#include "../draw.hpp"
#include "../game.hpp"
#include "../i18n.hpp"
#include "../quest.hpp"



namespace elona
{
namespace ui
{

bool UIMenuJournal::init()
{
    page = 99;
    pagesize = 40;
    cs = 0;
    keyrange = 0;
    key_list(0) = keybind_get_bound_key_name("enter");
    if (game()->adventurer_logs.empty())
    {
        buff = u8"No news"s;
    }
    else
    {
        buff = "";
        for (const auto& log : game()->adventurer_logs)
        {
            buff += log.headline + log.content + "\n";
        }
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
    for (int cnt = 0, cnt_end = (game()->number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (quest_data[cnt].progress == 0)
        {
            continue;
        }
        quest_set_data(cnt, none, 2);
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
    int gold = 0;
    p = clamp(cdata.player().fame / 10, 100, 25000);
    if (cdata.player().fame >= 25000)
    {
        p += (cdata.player().fame - 25000) / 100;
    }
    gold += p;
    noteadd(u8" - Title & Ranking - "s);
    noteadd(""s);
    noteadd(
        i18n::s.get("core.ui.journal.rank.fame") + ": " + cdata.player().fame);
    noteadd(""s);
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        if (game()->ranks.at(cnt) < 10000)
        {
            noteadd(
                ""s + ranktitle(cnt) + u8" Rank."s +
                game()->ranks.at(cnt) / 100);
            s = i18n::s.get("core.ui.journal.rank.pay", calcincome(cnt));
            gold += calcincome(cnt);
            if (cnt != 3 && cnt != 4 && cnt != 5 && cnt != 8)
            {
                s += i18n::s.get(
                    "core.ui.journal.rank.deadline",
                    game()->rank_deadlines.at(cnt));
            }
            noteadd(s);
            noteadd(""s);
        }
    }
    noteadd(i18n::s.get(
        "core.ui.journal.rank.arena",
        game()->ex_arena_wins,
        cnvrank(game()->ex_arena_highest_level)));
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
    noteadd(i18n::s.get("core.ui.journal.income.salary.title"));
    noteadd(i18n::s.get("core.ui.journal.income.salary.sum", gold));
    noteadd(""s);
    noteadd(i18n::s.get("core.ui.journal.income.bills.title"));
    noteadd(i18n::s.get(
        "core.ui.journal.income.bills.labor", game()->cost_to_hire));
    noteadd(i18n::s.get(
        "core.ui.journal.income.bills.maintenance", calccostbuilding()));
    noteadd(i18n::s.get("core.ui.journal.income.bills.tax", calccosttax()));
    noteadd(i18n::s.get(
        "core.ui.journal.income.bills.sum",
        (game()->cost_to_hire + calccostbuilding() + calccosttax())));
    noteadd(""s);
    noteadd(
        i18n::s.get("core.ui.journal.income.bills.unpaid", game()->left_bills));
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
    const auto& info = get_image_info("core.book");
    wx = (windoww - info.width) / 2 + inf_screenx;
    wy = winposy(info.height);
    snd("core.book1");
    window_animation(wx, wy, info.width, info.height, 9, 4);

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
    asset_load("core.book");
    gsel(0);
    elona::draw("core.book", wx, wy);
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
        snail::Color text_color{0, 0, 0};
        if (strmid(s, 0, 1) == u8"@"s)
        {
            s(1) = strmid(s, 1, 2);
            s = strmid(s, 3, s(0).size() - 3);
            font(10 + en - en * 2, snail::Font::Style::bold);
            if (s(1) == u8"QL"s)
            {
                text_color = snail::Color{100, 100, 0};
            }
            else if (s(1) == u8"QC"s)
            {
                text_color = snail::Color{0, 100, 100};
            }
            else if (s(1) == u8"QM"s)
            {
                text_color = snail::Color{0, 100, 0};
            }
            else if (s(1) == u8"RE"s)
            {
                text_color = snail::Color{100, 0, 0};
                font(12 + sizefix - en * 2);
            }
            else if (s(1) == u8"BL"s)
            {
                text_color = snail::Color{0, 0, 100};
                font(12 + sizefix - en * 2);
            }
            else
            {
                text_color = snail::Color{0, 0, 200};
            }
        }
        else
        {
            font(12 + sizefix - en * 2);
        }
        mes(x, y, s, text_color);
        if (p % 20 == 0)
        {
            font(12 + sizefix - en * 2, snail::Font::Style::bold);
            mes(x + 90, y + 330, u8"- "s + (p / 20 + 1) + u8" -"s);
            if (p % 40 == 20)
            {
                if (page < pagemax)
                {
                    mes(x + 200, y + 330, u8"(more)"s);
                }
            }
        }
    }
}

void UIMenuJournal::draw()
{
}

optional<UIMenuJournal::ResultType> UIMenuJournal::on_key(
    const std::string& action)
{
    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.card1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.card1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel" || action == "enter")
    {
        menucycle = 0;
        update_screen();
        return UIMenuJournal::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
