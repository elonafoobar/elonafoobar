#include "casino_card.hpp"
#include "audio.hpp"
#include "draw.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace
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



enum class Suit
{
    spades,
    hearts,
    diamonds,
    clubs,
    joker,
};


void showcard2(int prm_425, bool show_rank = true)
{
    const auto rank = card_at_cardcontrol(0, prm_425);
    const auto suit = static_cast<Suit>(card_at_cardcontrol(1, prm_425));
    const auto is_closed = card_at_cardcontrol(2, prm_425) == 1;
    const auto x = card_at_cardcontrol(3, prm_425);
    const auto y = card_at_cardcontrol(4, prm_425);

    gmode(2);
    if (is_closed)
    {
        // Card's back.
        pos(x, y);
        gcopy(3, 736, 216, 64, 96);
    }
    else
    {
        // Card's face.
        pos(x, y);
        gcopy(3, 672, 216, 64, 96);

        if (show_rank)
        {
            gmode(4, 220);
            snail::Color rank_color{0, 0, 0};
            optional_ref<Extent> rect;
            switch (suit)
            {
            case Suit::spades:
                rect = draw_get_rect_chara(168); // slime
                rank_color = {140, 140, 255, 255};
                break;
            case Suit::hearts:
                rect = draw_get_rect_chara(211); // black cat
                rank_color = {255, 140, 140, 255};
                break;
            case Suit::diamonds:
                rect = draw_get_rect_chara(241); // skeleton
                rank_color = {240, 240, 240, 255};
                break;
            case Suit::clubs:
                rect = draw_get_rect_chara(223); // armor
                rank_color = {140, 255, 140, 255};
                break;
            case Suit::joker:
                rect = draw_get_rect_chara(413); // ehekatl
                rank_color = {250, 250, 105, 255};
                break;
            }
            pos(x + 32 - rect->width / 2, y + 88 - rect->height);
            gcopy(rect->buffer, rect->x, rect->y, rect->width, rect->height);

            gmode(4, 220);
            pos(x + 8, y + 16);
            gcopy(3, 864 + static_cast<int>(suit) * 24, 533, 24, 32);
            pos(x + 32, y + 16);
            gcopy(3, 864 + (rank - 1) * 24, 565, 24, 32);
            gmode(2);
        }
        else
        {
            font(12 - en * 2);
        }
    }
}


} // namespace



namespace elona
{


void cardplayerinit(int prm_417, int prm_418)
{
    DIM3(cardplayer_at_cardcontrol, 100, prm_417);
    cardplayermax_at_cardcontrol = prm_417;
    cardholdermax_at_cardcontrol = prm_418;
}

void cardplayeradd(int prm_419, int prm_420, int prm_421)
{
    cardplayer_at_cardcontrol(1, prm_419) = prm_420;
    cardplayer_at_cardcontrol(2, prm_419) = prm_421;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cardplayer_at_cardcontrol(10 + cnt, prm_419) = -1;
    }
}

void initcard(int prm_422, int prm_423, int)
{
    pilex_at_cardcontrol = prm_422;
    piley_at_cardcontrol = prm_423;
    DIM3(card_at_cardcontrol, 6, 53);
    cardmax_at_cardcontrol = 52;
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
    font(16 - en * 2, snail::Font::Style::bold);
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
        if (card_at_cardcontrol(5, cnt) == -1 ||
            card_at_cardcontrol(5, cnt) == -2)
        {
            continue;
        }
        showcard2(cnt);
    }
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
    dx_at_cardcontrol = pilex_at_cardcontrol -
        cardplayer_at_cardcontrol(1, prm_427) - p_at_cardcontrol * 88;
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
    snd("core.card1");
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
        gmode(2);
        gcopy_c(3, 736, 216, 64, 96, 64 - cnt * 14, 96);
        await(10);
        redraw();
    }
    card_at_cardcontrol(2, prm_428) = 0;
    showcard2(prm_428, !prm_429);
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
        gmode(2);
        if (cnt == 20)
        {
            redraw();
            break;
        }
        pos(card_at_cardcontrol(3, prm_430) + 32,
            card_at_cardcontrol(4, prm_430) + 48);
        grotate(
            3, 736, 216, 64, 96, 64 - cnt * 3, 96 - cnt * 4, 0.015 * cnt * cnt);
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
            if (cardplayer_at_cardcontrol(10 + cnt, p_at_cardcontrol) ==
                prm_430)
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
