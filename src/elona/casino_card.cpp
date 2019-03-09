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


void showcard2(int card_index, bool show_rank = true)
{
    const auto rank = card_at_cardcontrol(0, card_index);
    const auto suit = static_cast<Suit>(card_at_cardcontrol(1, card_index));
    const auto is_closed = card_at_cardcontrol(2, card_index) == 1;
    const auto x = card_at_cardcontrol(3, card_index);
    const auto y = card_at_cardcontrol(4, card_index);

    gmode(2);
    if (is_closed)
    {
        draw("card_back", x, y);
    }
    else
    {
        draw("card_front", x, y);

        if (show_rank)
        {
            gmode(2, 220);
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
            set_color_mod(
                rank_color.r, rank_color.g, rank_color.b, rect->buffer);
            gcopy(
                rect->buffer,
                rect->x,
                rect->y,
                rect->width,
                rect->height,
                x + 32 - rect->width / 2,
                y + 88 - rect->height);
            set_color_mod(255, 255, 255, rect->buffer);

            gmode(2, 220);
            draw_indexed("card_suit", x + 8, y + 16, static_cast<int>(suit));
            draw_indexed("card_rank", x + 32, y + 16, rank - 1);
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

void cardplayerinit(int player_max, int holder_max)
{
    DIM3(cardplayer_at_cardcontrol, 100, player_max);
    cardplayermax_at_cardcontrol = player_max;
    cardholdermax_at_cardcontrol = holder_max;
}



void cardplayeradd(int player_id, int x, int y)
{
    cardplayer_at_cardcontrol(1, player_id) = x;
    cardplayer_at_cardcontrol(2, player_id) = y;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cardplayer_at_cardcontrol(10 + cnt, player_id) = -1;
    }
}



void initcard(int x, int y, int)
{
    pilex_at_cardcontrol = x;
    piley_at_cardcontrol = y;
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
    draw("card_pile", pilex_at_cardcontrol - 8, piley_at_cardcontrol - 8);
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



int servecard(int player_id)
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
        if (cardplayer_at_cardcontrol(10 + cnt, player_id) == -1)
        {
            p_at_cardcontrol = cnt;
            break;
        }
    }
    dx_at_cardcontrol = pilex_at_cardcontrol -
        cardplayer_at_cardcontrol(1, player_id) - p_at_cardcontrol * 88;
    dy_at_cardcontrol =
        piley_at_cardcontrol - cardplayer_at_cardcontrol(2, player_id);
    card_at_cardcontrol(5, cardid_at_cardcontrol) = player_id;
    cardplayer_at_cardcontrol(10 + p_at_cardcontrol, player_id) =
        cardid_at_cardcontrol;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (cnt != 0)
        {
            draw(
                "card_scratch",
                card_at_cardcontrol(3, cardid_at_cardcontrol),
                card_at_cardcontrol(4, cardid_at_cardcontrol));
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
        asset_copy_from(
            0,
            card_at_cardcontrol(3, cardid_at_cardcontrol),
            card_at_cardcontrol(4, cardid_at_cardcontrol),
            "card_scratch");

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
            draw("card_pile", dx_at_cardcontrol - 8, dy_at_cardcontrol - 8);
        }
    }
}



int opencard2(int card_index, int player_id)
{
    if (player_id == 1)
    {
        if (card_at_cardcontrol(2, card_index) == 0)
        {
            return card_index;
        }
    }
    snd("core.card1");
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (player_id == 0)
        {
            draw(
                "card_pile",
                card_at_cardcontrol(3, card_index) - 8,
                card_at_cardcontrol(4, card_index) - 8);
        }
        else
        {
            gcopy(
                4,
                card_at_cardcontrol(3, card_index) - wx - 4,
                card_at_cardcontrol(4, card_index) - wy - 4,
                80,
                112,
                card_at_cardcontrol(3, card_index),
                card_at_cardcontrol(4, card_index));
        }
        gmode(2);
        draw_centered(
            "card_back",
            card_at_cardcontrol(3, card_index) + 32,
            card_at_cardcontrol(4, card_index) + 48,
            64 - cnt * 14,
            96);
        await(10);
        redraw();
    }
    card_at_cardcontrol(2, card_index) = 0;
    showcard2(card_index, !player_id);
    redraw();
    return card_index;
}



int trashcard(int card_index)
{
    for (int cnt = 0; cnt < 21; ++cnt)
    {
        draw(
            "card_pile",
            card_at_cardcontrol(3, card_index) - 8,
            card_at_cardcontrol(4, card_index) - 8);
        gmode(2);
        if (cnt == 20)
        {
            redraw();
            break;
        }
        draw_rotated(
            "card_back",
            card_at_cardcontrol(3, card_index) + 32,
            card_at_cardcontrol(4, card_index) + 48,
            64 - cnt * 3,
            96 - cnt * 4,
            0.015 * cnt * cnt);
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
                card_index)
            {
                cardplayer_at_cardcontrol(10 + cnt, p_at_cardcontrol) = -1;
            }
        }
    }
    return card_index;
}



int cpscore(int player_id)
{
    int ace_at_cardcontrol = 0;
    i_at_cardcontrol = 0;
    ace_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        c_at_cardcontrol = cardplayer_at_cardcontrol(10 + cnt, player_id);
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



int lastcard(int player_id)
{
    c_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        if (cardplayer_at_cardcontrol(10 + cnt, player_id) == -1)
        {
            break;
        }
        c_at_cardcontrol = cardplayer_at_cardcontrol(10 + cnt, player_id);
    }
    return c_at_cardcontrol;
}



int cpblackcard(int player_id)
{
    c_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        c_at_cardcontrol = cardplayer_at_cardcontrol(10 + cnt, player_id);
        if (card_at_cardcontrol(2, c_at_cardcontrol) == 1)
        {
            break;
        }
    }
    return c_at_cardcontrol;
}



int cpcardnum(int player_id)
{
    c_at_cardcontrol = 0;
    for (int cnt = 0, cnt_end = (cardholdermax_at_cardcontrol); cnt < cnt_end;
         ++cnt)
    {
        if (cardplayer_at_cardcontrol(10 + cnt, player_id) != -1)
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
