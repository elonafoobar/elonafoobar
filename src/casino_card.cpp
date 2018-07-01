#include "casino_card.hpp"
#include "audio.hpp"
#include "draw.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

int dx_at_cardcontrol = 0;
int dy_at_cardcontrol = 0;
int c_at_cardcontrol = 0;
int cardmax_at_cardcontrol = 0;
int cardplayermax_at_cardcontrol = 0;
int cardholdermax_at_cardcontrol = 0;
elona_vector2<int> card_at_cardcontrol;
int pilex_at_cardcontrol = 0;
int piley_at_cardcontrol = 0;
elona_vector2<int> cardplayer_at_cardcontrol;
elona_vector1<int> i_at_cardcontrol;
elona_vector1<int> p_at_cardcontrol;

void cardplayerinit(int prm_417, int prm_418)
{
    DIM3(cardplayer_at_cardcontrol, 100, prm_417);
    cardplayermax_at_cardcontrol = prm_417;
    cardholdermax_at_cardcontrol = prm_418;
    return;
}

void cardplayeradd(int prm_419, int prm_420, int prm_421)
{
    cardplayer_at_cardcontrol(1, prm_419) = prm_420;
    cardplayer_at_cardcontrol(2, prm_419) = prm_421;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cardplayer_at_cardcontrol(10 + cnt, prm_419) = -1;
    }
    return;
}

void initcard(int prm_422, int prm_423, int)
{
    pilex_at_cardcontrol = prm_422;
    piley_at_cardcontrol = prm_423;
    DIM3(card_at_cardcontrol, 6, 53);
    cardmax_at_cardcontrol = 53;
    if (nojoker == 1)
    {
        cardmax_at_cardcontrol = 52;
    }
    for (int cnt = 0, cnt_end = (cardmax_at_cardcontrol); cnt < cnt_end; ++cnt)
    {
        card_at_cardcontrol(0, cnt) = cnt % 13 + 1;
        card_at_cardcontrol(1, cnt) = cnt / 13;
        card_at_cardcontrol(2, cnt) = 1;
        if (cnt == 52)
        {
            card_at_cardcontrol(1, cnt) = 4;
        }
        card_at_cardcontrol(5, cnt) = -1;
    }
    for (int cnt = 0; cnt < 200; ++cnt)
    {
        i_at_cardcontrol(0) = rnd(cardmax_at_cardcontrol);
        i_at_cardcontrol(1) = rnd(cardmax_at_cardcontrol);
        p_at_cardcontrol(0) = card_at_cardcontrol(0, i_at_cardcontrol);
        p_at_cardcontrol(1) = card_at_cardcontrol(1, i_at_cardcontrol);
        card_at_cardcontrol(0, i_at_cardcontrol) =
            card_at_cardcontrol(0, i_at_cardcontrol(1));
        card_at_cardcontrol(1, i_at_cardcontrol) =
            card_at_cardcontrol(1, i_at_cardcontrol(1));
        card_at_cardcontrol(0, i_at_cardcontrol(1)) = p_at_cardcontrol;
        card_at_cardcontrol(1, i_at_cardcontrol(1)) = p_at_cardcontrol(1);
    }
    return;
}

void showcard2(int prm_425, int prm_426)
{
    elona_vector1<int> col_at_cardcontrol;
    std::string s_at_cardcontrol;
    int tx_at_cardcontrol = 0;
    font(43 - en * 2, snail::font_t::style_t::bold);
    gmode(2, 64, 96);
    pos(card_at_cardcontrol(3, prm_425), card_at_cardcontrol(4, prm_425));
    if (card_at_cardcontrol(2, prm_425) == 1)
    {
        gcopy(3, 736, 216, 64, 96);
    }
    else
    {
        gcopy(3, 672, 216, 64, 96);
        if (prm_426 == 0)
        {
            gmode(4, inf_tiles, inf_tiles, 220);
            if (card_at_cardcontrol(1, prm_425) == 0)
            {
                pos(card_at_cardcontrol(3, prm_425) + 32,
                    card_at_cardcontrol(4, prm_425) + 36);
                gmode(4, inf_tiles, inf_tiles, 220);
                gcopy_c(5, 144, 240, inf_tiles, inf_tiles, 64, 104);
                col_at_cardcontrol(0) = 140;
                col_at_cardcontrol(1) = 140;
                col_at_cardcontrol(2) = 255;
            }
            if (card_at_cardcontrol(1, prm_425) == 1)
            {
                pos(card_at_cardcontrol(3, prm_425) + 32,
                    card_at_cardcontrol(4, prm_425) + 40);
                gmode(4, inf_tiles, inf_tiles, 220);
                gcopy_c(5, 1104, 288, inf_tiles, inf_tiles, 64, 104);
                col_at_cardcontrol(0) = 255;
                col_at_cardcontrol(1) = 140;
                col_at_cardcontrol(2) = 140;
            }
            if (card_at_cardcontrol(1, prm_425) == 2)
            {
                pos(card_at_cardcontrol(3, prm_425) + 32,
                    card_at_cardcontrol(4, prm_425) + 50);
                gmode(4, inf_tiles, inf_tiles, 220);
                gcopy_c(5, 480, 336, inf_tiles, inf_tiles, 64, 84);
                col_at_cardcontrol(0) = 240;
                col_at_cardcontrol(1) = 240;
                col_at_cardcontrol(2) = 240;
            }
            if (card_at_cardcontrol(1, prm_425) == 3)
            {
                pos(card_at_cardcontrol(3, prm_425) + 28,
                    card_at_cardcontrol(4, prm_425) + 48);
                gmode(4, inf_tiles, inf_tiles, 220);
                gcopy_c(5, 1200, 288, inf_tiles, inf_tiles, 64, 80);
                col_at_cardcontrol(0) = 140;
                col_at_cardcontrol(1) = 255;
                col_at_cardcontrol(2) = 140;
            }
            if (card_at_cardcontrol(1, prm_425) == 4)
            {
                pos(card_at_cardcontrol(3, prm_425) + 28,
                    card_at_cardcontrol(4, prm_425) + 44);
                gmode(4, inf_tiles, inf_tiles, 220);
                gcopy_c(5, 1296, 336, inf_tiles, inf_tiles, 72, 86);
                col_at_cardcontrol(0) = 250;
                col_at_cardcontrol(1) = 250;
                col_at_cardcontrol(2) = 105;
            }
            gmode(2);
            s_at_cardcontrol = std::to_string(card_at_cardcontrol(0, prm_425));
            tx_at_cardcontrol = 2;
            if (card_at_cardcontrol(0, prm_425) == 1)
            {
                s_at_cardcontrol = u8"A"s;
                tx_at_cardcontrol = 3;
            }
            if (card_at_cardcontrol(0, prm_425) == 11)
            {
                s_at_cardcontrol = u8"J"s;
                tx_at_cardcontrol = 13;
            }
            if (card_at_cardcontrol(0, prm_425) == 12)
            {
                s_at_cardcontrol = u8"Q"s;
                tx_at_cardcontrol = 14;
            }
            if (card_at_cardcontrol(0, prm_425) == 13)
            {
                s_at_cardcontrol = u8"K"s;
                tx_at_cardcontrol = 14;
            }
            if (card_at_cardcontrol(1, prm_425) == 4)
            {
                s_at_cardcontrol = u8"Jo"s;
                tx_at_cardcontrol = -12;
            }
            bmes(
                s_at_cardcontrol,
                card_at_cardcontrol(3, prm_425) + 18
                    - (card_at_cardcontrol(0, prm_425) >= 10) * 12
                    + tx_at_cardcontrol,
                card_at_cardcontrol(4, prm_425) + 28,
                {static_cast<uint8_t>(col_at_cardcontrol(0)),
                 static_cast<uint8_t>(col_at_cardcontrol(1)),
                 static_cast<uint8_t>(col_at_cardcontrol(2))},
                {10, 10, 10});
        }
        else
        {
            font(12 - en * 2);
        }
    }
    return;
}

void showcardpile()
{
    int pilestack_at_cardcontrol = 0;
    pos(pilex_at_cardcontrol - 8, piley_at_cardcontrol - 8);
    gcopy(3, 528, 216, 80, 112);
    pilestack_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardmax_at_cardcontrol); cnt < cnt_end; ++cnt)
    {
        if (card_at_cardcontrol(5, cnt) == -1)
        {
            ++pilestack_at_cardcontrol;
            if (pilestack_at_cardcontrol > 7)
            {
                continue;
            }
            card_at_cardcontrol(3, cnt) =
                pilex_at_cardcontrol - pilestack_at_cardcontrol;
            card_at_cardcontrol(4, cnt) =
                piley_at_cardcontrol - pilestack_at_cardcontrol;
            showcard2(cnt);
        }
    }
    font(16 - en * 2, snail::font_t::style_t::bold);
    bmes(
        u8"X "s + pilestack_at_cardcontrol,
        pilex_at_cardcontrol + 8,
        piley_at_cardcontrol + 70,
        {240, 240, 240},
        {10, 10, 10});
}



void showcard()
{
    showcardpile();
    for (int cnt = 0, cnt_end = (cardmax_at_cardcontrol); cnt < cnt_end; ++cnt)
    {
        if (card_at_cardcontrol(5, cnt) == -1
            || card_at_cardcontrol(5, cnt) == -2)
        {
            continue;
        }
        showcard2(cnt);
    }
    return;
}

int servecard(int prm_427)
{
    int cardid_at_cardcontrol = 0;
    cardid_at_cardcontrol = -1;
    for (int cnt = 0, cnt_end = (cardmax_at_cardcontrol); cnt < cnt_end; ++cnt)
    {
        if (card_at_cardcontrol(5, cnt) == -1)
        {
            cardid_at_cardcontrol = cnt;
            break;
        }
    }
    if (cardid_at_cardcontrol == -1)
    {
        return 0;
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (cardplayer_at_cardcontrol(10 + cnt, prm_427) == -1)
        {
            p_at_cardcontrol = cnt;
            break;
        }
    }
    dx_at_cardcontrol = pilex_at_cardcontrol
        - cardplayer_at_cardcontrol(1, prm_427) - p_at_cardcontrol * 88;
    dy_at_cardcontrol =
        piley_at_cardcontrol - cardplayer_at_cardcontrol(2, prm_427);
    card_at_cardcontrol(5, cardid_at_cardcontrol) = prm_427;
    cardplayer_at_cardcontrol(10 + p_at_cardcontrol, prm_427) =
        cardid_at_cardcontrol;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (cnt != 0)
        {
            pos(card_at_cardcontrol(3, cardid_at_cardcontrol),
                card_at_cardcontrol(4, cardid_at_cardcontrol));
            gcopy(3, 608, 216, 64, 96);
        }
        card_at_cardcontrol(3, cardid_at_cardcontrol) =
            pilex_at_cardcontrol - dx_at_cardcontrol / 10 * cnt;
        if (cnt == 9)
        {
            card_at_cardcontrol(3, cardid_at_cardcontrol) =
                pilex_at_cardcontrol - dx_at_cardcontrol;
        }
        card_at_cardcontrol(4, cardid_at_cardcontrol) =
            piley_at_cardcontrol - dy_at_cardcontrol / 10 * cnt;
        if (cnt == 9)
        {
            card_at_cardcontrol(4, cardid_at_cardcontrol) =
                piley_at_cardcontrol - dy_at_cardcontrol;
        }
        gmode(0);
        gsel(3);
        pos(608, 216);
        gcopy(
            0,
            card_at_cardcontrol(3, cardid_at_cardcontrol),
            card_at_cardcontrol(4, cardid_at_cardcontrol),
            64,
            96);
        gsel(0);
        gmode(2);
        showcard2(cardid_at_cardcontrol);
        showcardpile();
        await(10);
        redraw();
    }
    return cardid_at_cardcontrol;
}

void showcardholder()
{
    for (int cnt = 0, cnt_end = (cardplayermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        p_at_cardcontrol = cnt;
        for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol);
             cnt < cnt_end;
             ++cnt)
        {
            dx_at_cardcontrol =
                cardplayer_at_cardcontrol(1, p_at_cardcontrol) + cnt * 88;
            dy_at_cardcontrol = cardplayer_at_cardcontrol(2, p_at_cardcontrol);
            pos(dx_at_cardcontrol - 8, dy_at_cardcontrol - 8);
            gcopy(3, 528, 216, 80, 112);
        }
    }
    return;
}

int opencard2(int prm_428, int prm_429)
{
    if (prm_429 == 1)
    {
        if (card_at_cardcontrol(2, prm_428) == 0)
        {
            return prm_428;
        }
    }
    snd(71);
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (prm_429 == 0)
        {
            pos(card_at_cardcontrol(3, prm_428) - 8,
                card_at_cardcontrol(4, prm_428) - 8);
            gcopy(3, 528, 216, 80, 112);
        }
        else
        {
            pos(card_at_cardcontrol(3, prm_428),
                card_at_cardcontrol(4, prm_428));
            gcopy(
                4,
                card_at_cardcontrol(3, prm_428) - wx - 4,
                card_at_cardcontrol(4, prm_428) - wy - 4,
                80,
                112);
        }
        pos(card_at_cardcontrol(3, prm_428) + 32,
            card_at_cardcontrol(4, prm_428) + 48);
        gmode(2, 64, 96);
        gcopy_c(3, 736, 216, 64, 96, 64 - cnt * 14, 96);
        await(10);
        redraw();
    }
    card_at_cardcontrol(2, prm_428) = 0;
    showcard2(prm_428, prm_429);
    redraw();
    return prm_428;
}

int trashcard(int prm_430)
{
    for (int cnt = 0; cnt < 21; ++cnt)
    {
        pos(card_at_cardcontrol(3, prm_430) - 8,
            card_at_cardcontrol(4, prm_430) - 8);
        gcopy(3, 528, 216, 80, 112);
        gmode(2, 64, 96);
        if (cnt == 20)
        {
            redraw();
            break;
        }
        pos(card_at_cardcontrol(3, prm_430) + 32,
            card_at_cardcontrol(4, prm_430) + 48);
        grotate(3, 736, 216, 0.015 * cnt * cnt, 64 - cnt * 3, 96 - cnt * 4);
        await(10);
        redraw();
    }
    for (int cnt = 0, cnt_end = (cardplayermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        p_at_cardcontrol = cnt;
        for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol);
             cnt < cnt_end;
             ++cnt)
        {
            if (cardplayer_at_cardcontrol(10 + cnt, p_at_cardcontrol)
                == prm_430)
            {
                cardplayer_at_cardcontrol(10 + cnt, p_at_cardcontrol) = -1;
            }
        }
    }
    return prm_430;
}

int cpscore(int prm_431)
{
    int ace_at_cardcontrol = 0;
    i_at_cardcontrol = 0;
    ace_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        c_at_cardcontrol = cardplayer_at_cardcontrol(10 + cnt, prm_431);
        if (c_at_cardcontrol == -1)
        {
            break;
        }
        c_at_cardcontrol = card_at_cardcontrol(0, c_at_cardcontrol);
        if (c_at_cardcontrol >= 10)
        {
            c_at_cardcontrol = 10;
        }
        if (c_at_cardcontrol == 1)
        {
            ++ace_at_cardcontrol;
            c_at_cardcontrol = 11;
        }
        i_at_cardcontrol += c_at_cardcontrol;
    }
    for (int cnt = 0, cnt_end = (ace_at_cardcontrol); cnt < cnt_end; ++cnt)
    {
        if (i_at_cardcontrol > 21)
        {
            i_at_cardcontrol -= 10;
        }
    }
    return i_at_cardcontrol;
}

int lastcard(int prm_432)
{
    c_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        if (cardplayer_at_cardcontrol(10 + cnt, prm_432) == -1)
        {
            break;
        }
        c_at_cardcontrol = cardplayer_at_cardcontrol(10 + cnt, prm_432);
    }
    return c_at_cardcontrol;
}

int cpblackcard(int prm_433)
{
    c_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        c_at_cardcontrol = cardplayer_at_cardcontrol(10 + cnt, prm_433);
        if (card_at_cardcontrol(2, c_at_cardcontrol) == 1)
        {
            break;
        }
    }
    return c_at_cardcontrol;
}

int cpcardnum(int prm_434)
{
    c_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        if (cardplayer_at_cardcontrol(10 + cnt, prm_434) != -1)
        {
            ++c_at_cardcontrol;
        }
    }
    return c_at_cardcontrol;
}

int pileremain()
{
    p_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardmax_at_cardcontrol); cnt < cnt_end; ++cnt)
    {
        if (card_at_cardcontrol(5, cnt) == -1)
        {
            ++p_at_cardcontrol;
        }
    }
    return p_at_cardcontrol;
}

} // namespace elona
