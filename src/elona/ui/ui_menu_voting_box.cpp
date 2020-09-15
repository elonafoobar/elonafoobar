#include "ui_menu_voting_box.hpp"

#include "../game.hpp"
#include "../input_prompt.hpp"
#include "../world.hpp"



namespace elona
{
namespace ui
{

// list(0, n)  => ID
// list(1, n)  => ordering
// listn(0, n) => name
// listn(1, n) => vote count
bool UIMenuVotingBox::init()
{
    _can_vote_now = game_data.next_voting_time < game_data.date.hours();

    load_background_variants(4);
    gsel(0);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cs_bk = -1;

    txt(i18n::s.get("core.net.alias.message"));

    listmax = 0;
    list(0, listmax) = -999;
    list(1, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.net.alias.submit");
    ++listmax;

    for (const auto& poll : net_receive_polls())
    {
        list(0, listmax) = poll.id;
        list(1, listmax) = 0;
        listn(0, listmax) = poll.name;
        listn(1, listmax) = std::to_string(poll.vote_count);
        ++listmax;
    }

    if (_can_vote_now)
    {
        txt(i18n::s.get("core.net.alias.prompt"));
        for (int i = 0; i < listmax; ++i)
        {
            if (i == 0)
            {
                continue; // skip "Submit your alias".
            }
            // sort at random.
            list(1, i) = rnd(10000);
        }
        sort_list_and_listn_by_column1();
        if (listmax > pagesize)
        {
            listmax = pagesize;
        }
    }
    else
    {
        txt(i18n::s.get(
            "core.net.alias.cannot_vote_until",
            cnvdate(game_data.next_voting_time)));
        for (int i = 0; i < listmax; ++i)
        {
            if (i == 0)
            {
                continue; // skip "Submit your alias".
            }
            // sort by vote count in descending order.
            list(1, i) = 1000000 - list(1, i);
        }
        sort_list_and_listn_by_column1();
    }

    windowshadow = 1;

    return true;
}



void UIMenuVotingBox::update()
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



void UIMenuVotingBox::draw()
{
    ui_display_window(
        i18n::s.get("core.net.alias.title"),
        i18n::s.get("core.net.alias.hint") + strhint2 + strhint3,
        (windoww - 640) / 2 + inf_screenx,
        winposy(448),
        640,
        448);

    gmode(2, 50);
    gcopy_c(
        4,
        cmbg / 4 % 4 * 180,
        cmbg / 4 / 4 % 2 * 300,
        180,
        300,
        wx + ww / 3 * 2,
        wy + wh / 2,
        ww / 5 * 3,
        wh - 80);
    gmode(2);

    display_topic(i18n::s.get("core.net.alias.choice"), wx + 28, wy + 36);
    display_topic(i18n::s.get("core.net.alias.vote"), wx + 440, wy + 36);

    keyrange = 0;
    for (int i = 0; i < pagesize; ++i)
    {
        if (pagesize * page + i >= listmax)
        {
            break;
        }
        key_list(i) = key_select(i);
        ++keyrange;
        if (i % 2 == 0)
        {
            boxf(wx + 70, wy + 66 + i * 19, 540, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + i * 19 - 2, i);
    }

    gmode(2);
    font(14 - en * 2);
    cs_listbk();

    for (int i = 0; i < pagesize; ++i)
    {
        const auto idx = pagesize * page + i;
        if (idx >= listmax)
        {
            break;
        }
        if (idx != 0)
        {
            if (_can_vote_now)
            {
                mes(wx + 90,
                    wy + 66 + i * 19 + 2,
                    i18n::s.get("core.net.alias.selected"));
            }
            else
            {
                mes(wx + 90,
                    wy + 66 + i * 19 + 2,
                    i18n::s.get("core.net.alias.rank", idx));
            }
        }
        cs_list(cs == i, listn(0, idx), wx + 138, wy + 66 + i * 19 - 1);
        if (list(0, idx) != -999)
        {
            mes(wx + 462, wy + 66 + i * 19 + 2, listn(1, idx));
        }
    }

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



optional<UIMenuVotingBox::ResultType> UIMenuVotingBox::on_key(
    const std::string& action)
{
    if (const auto idx = get_selected_index())
    {
        const auto id = list(0, *idx);

        cs = i;
        Prompt prompt("core.net.alias");

        if (id == -999) // Register your name.
        {
            net_register_your_name();
            prompt.append("ok", snail::Key::key_y);
            prompt.query(promptx, prompty, 200);
            set_reinit();
            return none;
        }
        if (!_can_vote_now)
        {
            snd("core.fail1");
            txt(i18n::s.get("core.net.alias.need_to_wait"));
            set_reupdate();
            return none;
        }

        game_data.next_voting_time = game_data.date.hours() + 7 * 24; // 7 days
        txt(i18n::s.get("core.net.alias.i_like", listn(0, *idx)));
        txt(i18n::s.get("core.net.alias.you_vote"));
        net_send_vote(id);
        modrank(6, 100, 5);

        prompt.append("ok", snail::Key::key_y);
        prompt.query(promptx, prompty, 200);
        set_reinit();

        return ResultType::finish();
    }

    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
            return none;
        }
    }
    if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
            return none;
        }
    }
    if (action == "cancel")
    {
        return ResultType::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
