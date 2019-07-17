#include "casino.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "casino_card.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config/config.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "random.hpp"
#include "save.hpp"
#include "tcg.hpp"
#include "ui.hpp"


namespace elona
{

elona_vector1<int> atxpic;
int atxap;
int txtadvmsgfix;
elona_vector1<int> mattile;

void casino_dealer()
{
    begintempinv();
    atxthrough = 0;
    atxpic = 0;
    snd("core.pop3");
    mode = 9;
    atxbg = u8"bg13"s;
    atxbgbk = "";
    SDIM3(atxinfon, 80, 5);
    if (atxid == 1)
    {
        txt(i18n::s.get("core.casino.talk_to_dealer"));
        play_music("core.mcCasino");
        casino_wrapper();
        return;
    }
    casino_acquire_items();
}



void casino_choose_card()
{
    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            key = "";
            keylog = "";
            screenupdate = -1;
            update_screen();
            for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
            {
                noteget(s, cnt);
                snail::Color text_color{0, 0, 0};
                if (strmid(s, 0, 1) == u8"@"s)
                {
                    s(1) = strmid(s, 1, 2);
                    s = strmid(s, 3, s(0).size() - 3);
                    font(16 - en * 2);
                    if (s(1) == u8"BL"s)
                    {
                        text_color = snail::Color{130, 130, 250};
                    }
                    else if (s(1) == u8"GR"s)
                    {
                        text_color = snail::Color{130, 250, 130};
                    }
                    else if (s(1) == u8"QM"s)
                    {
                        text_color = snail::Color{0, 100, 0};
                    }
                    else
                    {
                        text_color = snail::Color{250, 240, 230};
                    }
                }
                else
                {
                    font(16 - en * 2);
                    text_color = snail::Color{250, 240, 230};
                }
                mes(170, cnt * 20 + 120 + txtadvmsgfix, s, text_color);
            }
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
            gsel(2);
            gmode(0);
            gcopy(0, 0, 0, windoww, windowh, 0, 0);
            gsel(0);
            gmode(2);
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
            }
            casino_adv_draw_mat();
        }

        x(0) = 170;
        x(1) = 400;
        y(0) = noteinfo() * 20 + 120 + txtadvmsgfix + 16;
        y(1) = 20 * listmax;
        gmode(0);
        gcopy(2, x, y, x(1), y(1), x, y);
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
            display_key(
                170, noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20, cnt);
            s = listn(0, p);
            cs_list(
                cs == cnt,
                s,
                200,
                noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20,
                0,
                {240, 240, 240});
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        auto action = get_selected_item(rtval);
        if (chatesc != -1)
        {
            if (action == "cancel")
            {
                snd("core.click1");
                rtval = chatesc;
            }
        }
        if (rtval != -1)
        {
            snd("core.click1");
            casino_fade_in_choices();
            atxpic = 0;
            return;
        }
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
    }
}

void casino_adv_draw_mat()
{
    casino_prepare_choice_graphic();
    if (mattile != -1)
    {
        mattile = rnd(mattile(2)) + mattile(1);
    }
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        x(0) = 170;
        x(1) = 300;
        y(0) = noteinfo() * 20 + 120 + txtadvmsgfix + 16;
        y(1) = 20 * listmax;
        gmode(0);
        gcopy(2, x - 50, y - 50, 100 + x(1), y(1) + 100, x - 50, y - 50);
        if (cnt == 11)
        {
            break;
        }
        gmode(2, cnt * 25);
        gcopy_c(2, 0, 0, x(1), y(1), x + x(1) / 2 - 10 + cnt, y + y(1) / 2);
        if (atxpic != 0)
        {
            x(0) = 345;
            x(1) = atxpic(2) + 120;
            y(0) = 170;
            y(1) = atxpic(3);
            gmode(0);
            gcopy(
                2,
                x - atxpic(2) / 2,
                y - atxpic(3) / 2,
                x(1),
                y(1),
                x - atxpic(2) / 2,
                y - atxpic(3) / 2);
            gmode(2);
            double p_double;
            if (cnt == 10)
            {
                p_double = 0;
            }
            else
            {
                p_double = 0.6222 * cnt;
            }
            p(1) = 1;
            if (atxpic == 2)
            {
                p(1) = 5;
            }
            grotate(
                p(1),
                atxpic(1) % 33 * 32,
                atxpic(1) / 33 * 32,
                inf_tiles,
                inf_tiles,
                x,
                y,
                cnt * (atxpic(2) / 10),
                cnt * (atxpic(3) / 10),
                p_double);
        }
        if (mattile != -1)
        {
            int cnt2 = cnt;
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                x(0) = cnt * 250 + 170;
                x(1) = 96;
                y(0) = 120;
                y(1) = 96;
                gmode(0);
                gcopy(2, x, y, x(1), y(1), x, y);
                gmode(2);
                gcopy_c(
                    1,
                    mattile % 33 * 32,
                    mattile / 33 * 32,
                    inf_tiles,
                    inf_tiles,
                    x + x(1) / 2,
                    y + y(1) / 2,
                    cnt2 * 9,
                    cnt2 * 9);
            }
        }
        await(20);
        redraw();
    }
    gmode(2);
    atxpic = 0;
}

void casino_fade_in_choices()
{
    casino_prepare_choice_graphic();
    for (int cnt = 0; cnt < 11; ++cnt)
    {
        x = 170;
        y(0) = noteinfo() * 20 + 120 + txtadvmsgfix + 16;
        y(1) = 20 * listmax;
        gmode(0);
        gcopy(2, x - 50, y - 50, 100 + x(1), y(1) + 100, x - 50, y - 50);
        gmode(2, 250 - cnt * 25);
        gcopy_c(2, 0, 0, x(1), y(1), x + x(1) / 2 - 2 * cnt, y + y(1) / 2);
        await(15);
        redraw();
    }
}

void casino_prepare_choice_graphic()
{
    x(1) = 300;
    cs = -1;
    boxf(170, noteinfo() * 20 + 120 + txtadvmsgfix + 16, x(1), 20 * listmax);
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
        display_key(
            170, noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20, cnt);
        s = listn(0, p);
        gmode(2);
        cs_list(
            cs == cnt,
            s,
            200,
            noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20,
            0,
            {240, 240, 240});
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    gsel(2);
    gmode(0);
    gcopy(
        0,
        170,
        noteinfo() * 20 + 120 + txtadvmsgfix + 16,
        x(1),
        20 * listmax,
        0,
        0);
    gsel(0);
    gmode(2);
    cs = 0;
}

void casino_acquire_items()
{
    mtilefilecur = -1;
    draw_prepare_map_chips();
    const auto have_any_rewards = range::any_of(
        inv.ground(), [](const auto& item) { return item.number() != 0; });
    if (have_any_rewards)
    {
        if (cdata.player().hp >= 0)
        {
            txt(i18n::s.get("core.casino.can_acquire"));
            screenupdate = -1;
            update_screen();
            invsubroutine = 1;
            invctrl(0) = 22;
            invctrl(1) = 0;
            ctrl_inventory();
        }
    }
    mode = 0;
    atxid = 0;
    exittempinv();
    await(100);
    snd("core.pop3");
    play_music();
}



void casino_wrapper()
{
    bool finished = false;
    while (!finished)
    {
        finished = casino_start();
    }
}

bool casino_start()
{
    bool finished = false;
    atxbg = u8"bg14"s;
    mattile = -1;
    atxinfon(0) = i18n::s.get("core.casino.window.title");
    atxinit();
    noteadd(i18n::s.get_enum("core.casino.window.desc", 0));
    noteadd(i18n::s.get_enum("core.casino.window.desc", 1));
    noteadd(i18n::s.get_enum("core.casino.window.desc", 2));
    if (game_data.used_casino_once == 0)
    {
        noteadd(""s);
        noteadd(i18n::s.get_enum("core.casino.window.first", 0));
        noteadd(i18n::s.get_enum("core.casino.window.first", 1));
        game_data.used_casino_once = 1;
        snd("core.get3");
        mat(1) += 10;
        noteadd(
            "@BL" + i18n::s.get("core.casino.you_get", 10, matname(1), mat(1)));
    }
    atxinfon(1) = i18n::s.get("core.casino.chips_left", mat(1));
    atxinfon(2) = "";
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.casino.window.choices.leave");
    ++listmax;
    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.casino.window.choices.blackjack");
    ++listmax;
    chatesc = 0;
    txtadvmsgfix = 0;
    txtadvscreenupdate = 1;
    casino_choose_card();
    if (rtval == 0)
    {
        casino_acquire_items();
        return true;
    }
    else if (rtval == 1)
    {
        while (!finished)
        {
            finished = casino_blackjack();
        }
        return false;
    }
    return true;
}

bool casino_blackjack()
{
    int stake = 0;
    int winrow = 0;
    int cardround = 0;
    int winner = 0;
    atxinit();
    noteadd(i18n::s.get_enum("core.casino.blackjack.desc", 0));
    noteadd(i18n::s.get_enum("core.casino.blackjack.desc", 1));
    noteadd(i18n::s.get_enum("core.casino.blackjack.desc", 2));
    noteadd(i18n::s.get_enum("core.casino.blackjack.desc", 3));
    atxinfon(1) = i18n::s.get("core.casino.chips_left", mat(1));
    atxinfon(2) = "";
    if (mat(1) <= 0)
    {
        noteadd(""s);
        noteadd(i18n::s.get("core.casino.blackjack.no_chips"));
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.casino.blackjack.choices.quit");
    ++listmax;
    if (mat(1) >= 1)
    {
        list(0, listmax) = 1;
        listn(0, listmax) = i18n::s.get("core.casino.blackjack.choices.bet", 1);
        ++listmax;
    }
    if (mat(1) >= 5)
    {
        list(0, listmax) = 5;
        listn(0, listmax) = i18n::s.get("core.casino.blackjack.choices.bet", 5);
        ++listmax;
    }
    if (mat(1) >= 20)
    {
        list(0, listmax) = 20;
        listn(0, listmax) =
            i18n::s.get("core.casino.blackjack.choices.bet", 20);
        ++listmax;
    }
    chatesc = 0;
    txtadvmsgfix = 0;
    txtadvscreenupdate = 1;
    casino_choose_card();
    if (rtval == 0)
    {
        return true;
    }
    stake = rtval;
    winrow = 0;
    cardround = 0;
    save_set_autosave();
    for (int cnt = 0;; ++cnt)
    {
        screenupdate = -1;
        update_screen();
        atxinit();
        if (cnt == 0)
        {
            mat(1) -= stake;
            noteadd(
                i18n::s.get("core.casino.you_lose", stake, matname(1), mat(1)));
        }
        if (cardround == 0)
        {
            initcard(60, 160);
            cardplayerinit(2, 5);
            cardplayeradd(0, 220, 124);
            cardplayeradd(1, 220, 240);
        }
        font(14 - en * 2, snail::Font::Style::bold);
        mes(152,
            154,
            i18n::s.get("core.casino.blackjack.game.dealer"),
            {255, 255, 255});
        mes(152,
            270,
            i18n::s.get("core.casino.blackjack.game.you"),
            {255, 255, 255});
        showcardpile();
        showcardholder();
        showcard();
        if (cardround == 0)
        {
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                int stat = servecard(cnt % 2);
                if (cnt != 2)
                {
                    opencard2(stat);
                }
            }
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (cpcardnum(0) >= 5)
                {
                    break;
                }
                if (cpscore(0) < cpscore(1) || cpscore(0) - rnd(5) <= 11)
                {
                    int stat = servecard(0);
                    opencard2(stat);
                    --cnt;
                    continue;
                }
            }
        }
        noteadd(
            i18n::s.get("core.casino.blackjack.game.your_hand", cpscore(1)));
        if (cardround == -1)
        {
            noteadd(i18n::s.get(
                "core.casino.blackjack.game.dealers_hand", cpscore(0)));
            winner = -1;
            if (cpscore(0) <= 21)
            {
                if (cpscore(1) > 21 || cpscore(0) > cpscore(1))
                {
                    winner = 0;
                }
            }
            if (cpscore(1) <= 21)
            {
                if (cpscore(0) > 21 || cpscore(1) > cpscore(0))
                {
                    winner = 1;
                }
            }
            if (winner == -1)
            {
                noteadd(i18n::s.get("core.casino.blackjack.game.result.draw"));
            }
            if (winner == 0)
            {
                noteadd(i18n::s.get("core.casino.blackjack.game.result.lose"));
            }
            if (winner == 1)
            {
                noteadd(i18n::s.get("core.casino.blackjack.game.result.win"));
            }
        }
        atxinfon(1) = i18n::s.get("core.casino.chips_left", mat(1));
        atxinfon(2) = i18n::s.get("core.casino.blackjack.game.bets", stake) +
            " " + i18n::s.get("core.casino.blackjack.game.wins", winrow);
        if (cardround == -1)
        {
            if (winner == 1)
            {
                ++winrow;
            }
            if (winner != 0)
            {
                list(0, listmax) = 0;
                listn(0, listmax) = i18n::s.get(
                    "core.casino.blackjack.game.result.choices.next_"
                    "round");
                ++listmax;
            }
            if (winner == 0)
            {
                list(0, listmax) = 0;
                listn(0, listmax) = i18n::s.get(
                    "core.casino.blackjack.game.result.choices.leave");
                ++listmax;
            }
            chatesc = -1;
            txtadvmsgfix = 240;
            txtadvscreenupdate = 0;
            casino_choose_card();
            if (winner == 0)
            {
                break;
            }
            cardround = 0;
            continue;
        }
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.casino.blackjack.game.choices.stay");
        ++listmax;
        if (pileremain() > 10)
        {
            if (cpcardnum(1) < 5)
            {
                list(0, listmax) = 1;
                listn(0, listmax) =
                    i18n::s.get("core.casino.blackjack.game.choices.hit");
                ++listmax;
            }
            list(0, listmax) = 2;
            listn(0, listmax) = i18n::s.get(
                "core.casino.blackjack.game.choices.cheat", sdata(12, 0));
            ++listmax;
        }
        chatesc = -1;
        txtadvmsgfix = 240;
        txtadvscreenupdate = 0;
        casino_choose_card();
        if (rtval == 0)
        {
            opencard2(cpblackcard(0));
            cardround = -1;
            continue;
        }
        if (rtval == 1)
        {
            int stat = servecard(1);
            p = stat;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                if (cpscore(1) >= 22)
                {
                    if (pileremain() > 10)
                    {
                        if (rnd(sdata(19, 0)) > 40)
                        {
                            txt(
                                i18n::s.get("core.casino.blackjack.game."
                                            "bad_feeling"));
                            trashcard(p);
                            int stat = servecard(1);
                            p = stat;
                        }
                    }
                }
            }
            opencard2(p);
        }
        if (rtval == 2)
        {
            trashcard(lastcard(1));
            int stat = servecard(1);
            opencard2(stat);
            p = 20;
            if (stake == 5)
            {
                p = 40;
            }
            if (stake == 20)
            {
                p = 60;
            }
            if (rnd(sdata(12, 0)) < rnd(p(0)))
            {
                atxinit();
                noteadd(i18n::s.get("core.casino.blackjack.game.cheat.dialog"));
                atxinfon(1) = i18n::s.get("core.casino.chips_left", mat(1));
                atxinfon(2) =
                    i18n::s.get("core.casino.blackjack.game.bets", stake) +
                    " " +
                    i18n::s.get("core.casino.blackjack.game.wins", winrow);
                winrow = 0;
                txt(i18n::s.get("core.casino.blackjack.game.cheat.text"));
                modify_karma(cdata.player(), -5);
                list(0, listmax) = 0;
                listn(0, listmax) =
                    i18n::s.get("core.casino.blackjack.game.cheat.response");
                ++listmax;
                chatesc = -1;
                txtadvmsgfix = 0;
                txtadvscreenupdate = 1;
                casino_choose_card();
                break;
            }
        }
        ++cardround;
    }
    if (winrow > 0)
    {
        atxinit();
        noteadd(i18n::s.get("core.casino.blackjack.game.total_wins", winrow));
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            Quality quality = Quality::good;
            if (winrow > 2)
            {
                quality = Quality::great;
            }
            if (winrow > 7)
            {
                if (stake >= 5)
                {
                    quality = Quality::miracle;
                }
            }
            if (winrow > 15)
            {
                if (stake >= 20)
                {
                    quality = Quality::godly;
                }
            }
            flt(calcobjlv(rnd(stake + winrow * 2) + winrow * 3 / 2 + stake / 2),
                quality);
            flttypemajor = choice(fsetwear);
            itemcreate(-1, 0, -1, -1, 0);
            if (inv[ci].number() == 0)
            {
                --cnt;
                continue;
            }
        }
        snd("core.get3");
        noteadd(
            "@GR" + i18n::s.get("core.casino.blackjack.game.loot", inv[ci]));
        if (winrow > 3)
        {
            // Potion of cure corruption
            if (winrow + 1 > rnd(10))
            {
                flt();
                itemcreate(-1, 559, -1, -1, 0);
                snd("core.get3");
                noteadd(
                    "@GR" +
                    i18n::s.get("core.casino.blackjack.game.loot", inv[ci]));
            }
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.casino.blackjack.game.leave");
        ++listmax;
        chatesc = 0;
        txtadvmsgfix = 0;
        txtadvscreenupdate = 1;
        casino_choose_card();
        winrow = 0;
    }
    return true;
}

} // namespace elona
