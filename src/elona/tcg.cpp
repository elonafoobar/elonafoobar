#include "tcg.hpp"

#include "audio.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_asset.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "keybind/keybind.hpp"
#include "random.hpp"
#include "save_fs.hpp"
#include "variables.hpp"



namespace elona
{



elona_vector2<int> card_at_tcg;
int cp_at_tcg = 0;
int tp_at_tcg = 0;
int cl_at_tcg = 0;
int tl_at_tcg = 0;
int ch_at_tcg = 0;
int th_at_tcg = 0;
int ct_at_tcg = 0;
elona_vector1<std::string> s_at_tcg;
elona_vector1<std::string> domname_at_tcg;
elona_vector1<std::string> cdrefn_at_tcg;
elona_vector2<int> clist_at_tcg;
elona_vector1<int> clistmax_at_tcg;
int cnt2_at_tcg = 0;
elona_vector1<int> p_at_tcg;
int maxcard_at_tcg = 0;
int f_at_tcg = 0;
int i_at_tcg = 0;
elona_vector1<std::string> helpmsg_at_tcg;
int cursor_at_tcg = 0;
int cs_at_tcg = 0;
int csline_at_tcg = 0;
elona_vector2<int> dlist_at_tcg;
int dsc_at_tcg = 0;
elona_vector1<std::string> carddetailn_at_tcg;
elona_vector1<int> x_at_tcg;
elona_vector1<int> y_at_tcg;
int basex_at_tcg = 0;
int basey_at_tcg = 0;
elona_vector1<int> holderix_at_tcg;
int holderspace_at_tcg = 0;
elona_vector1<int> holderiy_at_tcg;
elona_vector2<int> cpdata_at_tcg;
int c_at_tcg = 0;
int cc_at_tcg = 0;
int phase_at_tcg = 0;
int selectmode_at_tcg = 0;
int cfg_chaintime = 0;
int chainx_at_tcg = 0;
int chainy_at_tcg = 0;
int efllistmax_at_tcg = 0;
elona_vector2<int> efllist_at_tcg;
elona_vector2<std::string> cardn_at_tcg;
int spotspace_at_tcg = 0;
elona_vector1<int> spotiy_at_tcg;
int n_at_tcg = 0;
elona_vector1<int> gravesum_at_tcg;
elona_vector2<int> gravelist_at_tcg;
elona_vector1<int> cpx_at_tcg;
elona_vector1<int> cpy_at_tcg;
elona_vector1<int> deckix_at_tcg;
elona_vector1<int> deckiy_at_tcg;
int sac_at_tcg = 0;
elona_vector1<int> landix_at_tcg;
elona_vector1<int> landsum_at_tcg;
int landspace_at_tcg = 0;
elona_vector1<int> landiy_at_tcg;
elona_vector2<int> landlist_at_tcg;
int spellused_at_tcg = 0;
int stack_at_tcg = 0;
elona_vector2<int> cardstack_at_tcg;
int attacktarget_at_tcg = 0;
int chainmode_at_tcg = 0;
int player_at_tcg = 0;
int aiblock_at_tcg = 0;
elona_vector1<int> act_at_tcg;
elona_vector1<int> deckmode_at_tcg;
std::string deckrefn_at_tcg;
int turn_at_tcg = 0;
int cardmode_at_tcg = 0;
elona_vector2<int> elist_at_tcg;
elona_vector1<std::string> phasen_at_tcg;
int basew_at_tcg = 0;
int baseh_at_tcg = 0;
elona_vector1<int> graveix_at_tcg;
elona_vector1<int> graveiy_at_tcg;
int gravespace_at_tcg = 0;
elona_vector1<int> domain_at_tcg;
int curdeck = 0;
int decksizebk_at_tcg = 0;
int rtval_at_tcg = 0;
int cslinebk_at_tcg = 0;
int cfmax_at_tcg = 0;
int ccf_at_tcg = 0;
elona_vector1<int> cflist_at_tcg;
elona_vector1<std::string> cfname_at_tcg;
int page_at_tcg = 0;
int dlistmax_at_tcg = 0;
int chaincontinue_at_tcg = 0;
int emax_at_tcg = 0;



int cdbit(int bitflag_id, int card_index)
{
    return (card_at_tcg(30, card_index) & (1 << bitflag_id)) ? 1 : 0;
}



void cdbitmod(int bitflag_id, int card_index, int on_or_off)
{
    if (on_or_off)
    {
        card_at_tcg(30, card_index) |= (1 << bitflag_id);
    }
    else
    {
        card_at_tcg(30, card_index) &= ~(1 << bitflag_id);
    }
}



void cpflip()
{
    if (cp_at_tcg == 1)
    {
        cp_at_tcg = 0;
        tp_at_tcg = 1;
        cl_at_tcg = 1;
        tl_at_tcg = 3;
        ch_at_tcg = 0;
        th_at_tcg = 3;
    }
    else
    {
        cp_at_tcg = 1;
        tp_at_tcg = 0;
        cl_at_tcg = 2;
        tl_at_tcg = 1;
        ch_at_tcg = 3;
        th_at_tcg = 0;
    }
}



void cpisme()
{
    if (ct_at_tcg == 0)
    {
        cp_at_tcg = 0;
        tp_at_tcg = 1;
        cl_at_tcg = 1;
        tl_at_tcg = 3;
        ch_at_tcg = 0;
        th_at_tcg = 3;
    }
    else
    {
        cp_at_tcg = 1;
        tp_at_tcg = 0;
        cl_at_tcg = 2;
        tl_at_tcg = 1;
        ch_at_tcg = 3;
        th_at_tcg = 0;
    }
}



void cpisenemy()
{
    if (ct_at_tcg == 0)
    {
        cp_at_tcg = 1;
        tp_at_tcg = 0;
        cl_at_tcg = 2;
        tl_at_tcg = 1;
        ch_at_tcg = 3;
        th_at_tcg = 0;
    }
    else
    {
        cp_at_tcg = 0;
        tp_at_tcg = 1;
        cl_at_tcg = 1;
        tl_at_tcg = 3;
        ch_at_tcg = 0;
        th_at_tcg = 3;
    }
}



std::string cnvrare(int rarity)
{
    s_at_tcg = "";
    for (int cnt = 0, cnt_end = (clamp(5 - rarity / 20, 1, 5)); cnt < cnt_end;
         ++cnt)
    {
        s_at_tcg += u8"*"s;
    }
    return s_at_tcg;
}



std::pair<int, std::string> card_ref(int id, CardInfo& card_info)
{
    card_info.cardrefattack = 0;
    card_info.cardrefcost = 0;
    card_info.cardrefdomain = 0;
    card_info.cardrefhp = 0;
    card_info.cardrefn = "";
    card_info.cardrefpic = 0;
    card_info.cardrefrare = 0;
    card_info.cardrefskill = 0;
    card_info.cardrefskillcost = 0;
    card_info.cardreftype = 0;
    card_info.cardrefrace = "";
    get_card_info(id, card_info);

    if (card_info.cardreftype == 0)
    {
        card_info.cardreftype = 10;
        card_info.cardrefdomain = 4;
    }

    int cardrefbg{};
    std::string card_desc = card_info.cardrefn;
    if (card_info.cardreftype == 10)
    {
        cardrefbg = card_info.cardrefdomain;
        card_desc += " <" + i18n::s.get("core.tcg.card.creature") + ">  " +
            i18n::s.get("core.tcg.card.race") + ":" + card_info.cardrefrace +
            u8"  Hp:"s + card_info.cardrefhp + u8"  Atk:"s +
            card_info.cardrefattack;
    }
    if (card_info.cardreftype == 30)
    {
        cardrefbg = 6;
        card_desc += " <" + i18n::s.get("core.tcg.card.land") + ">";
    }
    if (card_info.cardreftype == 20)
    {
        cardrefbg = 5;
        card_desc += " <" + i18n::s.get("core.tcg.card.spell") + ">";
    }
    card_desc += "  " + i18n::s.get("core.tcg.card.domain") + ":" +
        domname_at_tcg(card_info.cardrefdomain);
    card_desc += "  " + i18n::s.get("core.tcg.card.rare") + ":" +
        cnvrare(card_info.cardrefrare);
    if (card_info.cardrefskill != 0)
    {
        s_at_tcg = "";
        if (card_info.cardreftype == 10)
        {
            s_at_tcg += i18n::s.get("core.tcg.card.skill") + ":";
        }
        s_at_tcg += cdrefn_at_tcg(card_info.cardrefskill);
        talk_conv(s_at_tcg, 95);
        card_desc += u8"\n"s + s_at_tcg;
    }

    return std::make_pair(cardrefbg, card_desc);
}



void makecardlist()
{
    int lmax_at_tcg = 0;
    int c1_at_tcg = 0;
    int c2_at_tcg = 0;
    DIM3(clist_at_tcg, 10, 4);
    DIM2(clistmax_at_tcg, 4);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        cnt2_at_tcg = cnt;
        lmax_at_tcg = 0;
        if (cnt == 0)
        {
            p_at_tcg = 0;
        }
        else
        {
            p_at_tcg = 3;
        }
        for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
        {
            if (card_at_tcg(1, cnt) != cnt2_at_tcg)
            {
                continue;
            }
            if (card_at_tcg(0, cnt) != 2)
            {
                continue;
            }
            clist_at_tcg(lmax_at_tcg, p_at_tcg) = cnt;
            ++lmax_at_tcg;
        }
        clist_at_tcg(lmax_at_tcg, p_at_tcg) = -1;
        clistmax_at_tcg(p_at_tcg) = lmax_at_tcg;
        lmax_at_tcg = 0;
        if (cnt == 0)
        {
            p_at_tcg = 1;
        }
        else
        {
            p_at_tcg = 2;
        }
        for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
        {
            if (card_at_tcg(1, cnt) != cnt2_at_tcg)
            {
                continue;
            }
            if (card_at_tcg(0, cnt) != 1)
            {
                continue;
            }
            clist_at_tcg(lmax_at_tcg, p_at_tcg) = cnt;
            ++lmax_at_tcg;
        }
        clist_at_tcg(lmax_at_tcg, p_at_tcg) = -1;
        clistmax_at_tcg(p_at_tcg) = lmax_at_tcg;
    }
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        p_at_tcg = cnt;
        while (1)
        {
            f_at_tcg = 0;
            for (int cnt = 0, cnt_end = (clistmax_at_tcg(p_at_tcg));
                 cnt < cnt_end;
                 ++cnt)
            {
                c1_at_tcg = clist_at_tcg(cnt, p_at_tcg);
                c2_at_tcg = clist_at_tcg(cnt + 1, p_at_tcg);
                if (c2_at_tcg == -1)
                {
                    continue;
                }
                if (card_at_tcg(4, c2_at_tcg) < card_at_tcg(4, c1_at_tcg))
                {
                    i_at_tcg = clist_at_tcg(cnt, p_at_tcg);
                    clist_at_tcg(cnt, p_at_tcg) =
                        clist_at_tcg(cnt + 1, p_at_tcg);
                    clist_at_tcg(cnt + 1, p_at_tcg) = i_at_tcg;
                    f_at_tcg = 1;
                    break;
                }
            }
            if (f_at_tcg == 0)
            {
                break;
            }
        }
    }
    tcg_proc_ai_elist();
}



void cardhelp(const std::string& help_message, int help_duration = 0)
{
    int helpdur_at_tcg = 0;
    int dur_at_tcg = 0;
    if (helpdur_at_tcg > 1)
    {
        if (help_duration == 0)
        {
            --helpdur_at_tcg;
            return;
        }
    }
    if (help_duration == 0)
    {
        dur_at_tcg = 1;
    }
    else
    {
        dur_at_tcg = help_duration;
    }
    helpmsg_at_tcg = help_message;
    helpdur_at_tcg = dur_at_tcg;
}



void tcgdrawcard(int card_index, int prm_995)
{
    int selected_at_tcg = 0;
    selected_at_tcg = 0;
    if (prm_995 == 0)
    {
        if (cursor_at_tcg)
        {
            if (cs_at_tcg != -1)
            {
                if (clist_at_tcg(cs_at_tcg, csline_at_tcg) == card_index)
                {
                    selected_at_tcg = 1;
                }
            }
        }
    }
    else if (card_index == dlist_at_tcg(0, dsc_at_tcg))
    {
        selected_at_tcg = 1;
    }
    if (selected_at_tcg)
    {
        gmode(2);
        gcopy(
            7,
            168,
            144,
            82,
            106,
            card_at_tcg(2, card_index) - 5,
            card_at_tcg(3, card_index) - 5);
        if (0 || cdbit(1, card_index) == 1 || card_at_tcg(1, card_index) == 0)
        {
            cardhelp(carddetailn_at_tcg(card_index));
        }
        else
        {
            cardhelp(""s);
        }
    }
    for (int cnt = 0, cnt_end = (1 + (selected_at_tcg == 1)); cnt < cnt_end;
         ++cnt)
    {
        x_at_tcg = card_at_tcg(2, card_index);
        y_at_tcg = card_at_tcg(3, card_index);
        if (cnt == 1)
        {
            if (card_at_tcg(6, card_index) != 0)
            {
                break;
            }
            x_at_tcg = basex_at_tcg + 20;
            y_at_tcg = basey_at_tcg + 490;
            gmode(2, 140);
            gcopy(7, 168, 144, 82, 106, x_at_tcg - 6, y_at_tcg - 6);
        }
        gmode(2);
        if (card_at_tcg(6, card_index) == 2)
        {
            gmode(2, card_at_tcg(7, card_index) * 15);
        }
        if (cdbit(1, card_index) == 1 ||
            (card_at_tcg(1, card_index) == 0 && cnt == 1))
        {
            if (card_at_tcg(17, card_index) > 0)
            {
                gcopy(
                    7,
                    72 + card_at_tcg(19, card_index) * 72,
                    0,
                    72,
                    96,
                    x_at_tcg,
                    y_at_tcg);
                p_at_tcg = card_at_tcg(17, card_index) % 1000;
                auto rect = chara_preparepic(card_at_tcg(17, card_index));
                gcopy(
                    rect->buffer,
                    0,
                    960,
                    rect->width,
                    rect->height,
                    x_at_tcg + 13,
                    y_at_tcg + 32 - chara_chips[p_at_tcg].offset_y +
                        rect->height / 6);
            }
            else
            {
                p_at_tcg = std::abs(card_at_tcg(17, card_index));
                gcopy(
                    2,
                    p_at_tcg % 22 * 72,
                    p_at_tcg / 22 * 96,
                    72,
                    96,
                    x_at_tcg,
                    y_at_tcg);
            }
            if (card_at_tcg(9, card_index) == 10)
            {
                gcopy(7, 48, 96, 36, 26, x_at_tcg + 39, y_at_tcg - 8);
                mes(x_at_tcg + 56 - (card_at_tcg(12, card_index) > 9) * 4 - en,
                    y_at_tcg - 1 - en,
                    std::to_string(card_at_tcg(12, card_index)),
                    {255, 255, 255});
                gcopy(7, 0, 96, 36, 26, x_at_tcg - 3, y_at_tcg - 8);
                mes(x_at_tcg + 11 - (card_at_tcg(11, card_index) > 9) * 4 - en,
                    y_at_tcg - 1 - en,
                    std::to_string(card_at_tcg(11, card_index)),
                    {255, 255, 255});
                if (card_at_tcg(13, card_index) != 0)
                {
                    gcopy(
                        7, 144, 96, 36, 26, x_at_tcg + 39, y_at_tcg + 78 - en);
                    mes(x_at_tcg + 56 - en,
                        y_at_tcg + 86 - en,
                        std::to_string(card_at_tcg(20, card_index)),
                        {255, 255, 255});
                }
            }
            if (card_at_tcg(10, card_index) != 0)
            {
                gcopy(7, 96, 96, 36, 26, x_at_tcg - 3, y_at_tcg + 78);
                mes(x_at_tcg + 11 - (card_at_tcg(10, card_index) > 9) * 4 - en,
                    y_at_tcg + 86 - en,
                    std::to_string(card_at_tcg(10, card_index)),
                    {255, 255, 255});
            }
        }
        else
        {
            gcopy(7, 0, 0, 72, 96, x_at_tcg, y_at_tcg);
        }
        if (cnt == 0)
        {
            if (card_at_tcg(0, card_index) == 1)
            {
                if (cdbit(1, card_index))
                {
                    if (card_at_tcg(9, card_index) == 10)
                    {
                        if (card_at_tcg(14, card_index) == -1)
                        {
                            gcopy(7, 288, 120, 24, 24, x_at_tcg, y_at_tcg + 18);
                        }
                        if (card_at_tcg(14, card_index) == -2)
                        {
                            gcopy(7, 312, 120, 24, 24, x_at_tcg, y_at_tcg + 18);
                        }
                        if (card_at_tcg(14, card_index) == -3)
                        {
                            gcopy(7, 264, 120, 24, 24, x_at_tcg, y_at_tcg + 18);
                        }
                        if (card_at_tcg(14, card_index) == -4)
                        {
                            gcopy(7, 240, 120, 24, 24, x_at_tcg, y_at_tcg + 18);
                        }
                    }
                }
            }
        }
    }
}



void tcgdraw()
{
    int t_at_tcg = 0;
    int anime_at_tcg = 0;
    int chaintime_at_tcg = 0;
    elona_vector2<int> star_at_tcg;
    int screenupdate_at_tcg = 0;

    while (1)
    {
        ++t_at_tcg;
        tcg_draw_deck_editor();
        anime_at_tcg = 0;
        font(12 + en - en * 2);
        gmode(2);
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            x_at_tcg = holderix_at_tcg(cnt) - holderspace_at_tcg;
            y_at_tcg = holderiy_at_tcg(cnt);
            gcopy(7, 96, 144, 72, 96, x_at_tcg, y_at_tcg);
            mes(x_at_tcg + 14,
                y_at_tcg + 75,
                ""s + cpdata_at_tcg(7, cnt) + u8"/"s + cpdata_at_tcg(8, cnt),
                {255, 255, 255});
        }
        font(13 + en - en * 2);
        for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
        {
            c_at_tcg = maxcard_at_tcg - cnt - 1;
            if (cc_at_tcg != 0)
            {
                if (c_at_tcg == 0)
                {
                    c_at_tcg = cc_at_tcg;
                }
                else if (c_at_tcg == cc_at_tcg)
                {
                    c_at_tcg = 0;
                }
            }
            if (card_at_tcg(0, c_at_tcg) <= 0)
            {
                if (card_at_tcg(7, c_at_tcg) == 0)
                {
                    continue;
                }
            }
            if (card_at_tcg(0, c_at_tcg) == 4)
            {
                continue;
            }
            if (card_at_tcg(2, c_at_tcg) != card_at_tcg(4, c_at_tcg) ||
                card_at_tcg(3, c_at_tcg) != card_at_tcg(5, c_at_tcg) ||
                card_at_tcg(7, c_at_tcg) > 0)
            {
                anime_at_tcg = 1;
                p_at_tcg = 0;
                if (card_at_tcg(2, c_at_tcg) != card_at_tcg(4, c_at_tcg))
                {
                    p_at_tcg =
                        (card_at_tcg(4, c_at_tcg) - card_at_tcg(2, c_at_tcg)) /
                        6;
                    if (card_at_tcg(2, c_at_tcg) > card_at_tcg(4, c_at_tcg))
                    {
                        --p_at_tcg;
                    }
                    else
                    {
                        ++p_at_tcg;
                    }
                }
                card_at_tcg(2, c_at_tcg) += p_at_tcg;
                p_at_tcg = 0;
                if (card_at_tcg(3, c_at_tcg) != card_at_tcg(5, c_at_tcg))
                {
                    p_at_tcg =
                        (card_at_tcg(5, c_at_tcg) - card_at_tcg(3, c_at_tcg)) /
                        6;
                    if (card_at_tcg(3, c_at_tcg) > card_at_tcg(5, c_at_tcg))
                    {
                        --p_at_tcg;
                    }
                    else
                    {
                        ++p_at_tcg;
                    }
                }
                card_at_tcg(3, c_at_tcg) += p_at_tcg;
                if (card_at_tcg(7, c_at_tcg) > 0)
                {
                    --card_at_tcg(7, c_at_tcg);
                }
            }
            tcgdrawcard(c_at_tcg);
        }
        font(14 - en * 2);
        gmode(2);
        if (cursor_at_tcg)
        {
            if (cs_at_tcg == -1)
            {
                if (phase_at_tcg == 2)
                {
                    if (selectmode_at_tcg == 0)
                    {
                        cardhelp(i18n::s.get("core.tcg.end_main_phase"));
                    }
                    else
                    {
                        cardhelp(i18n::s.get("core.tcg.no_blocker"));
                    }
                }
                gcopy(
                    7,
                    168,
                    144,
                    82,
                    106,
                    holderix_at_tcg - holderspace_at_tcg - 5,
                    holderiy_at_tcg - 5);
            }
        }
        if (chaintime_at_tcg > 0)
        {
            if (chaintime_at_tcg == cfg_chaintime)
            {
                DIM3(star_at_tcg, 2, 10);
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    star_at_tcg(0, cnt) = rnd(72) - 32;
                    star_at_tcg(1, cnt) = rnd(40) - 32;
                }
            }
            if (chaintime_at_tcg > 5)
            {
                gmode(5, clamp(chaintime_at_tcg * 3 - 40, 0, 255));
                cnt2_at_tcg = 0;
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    gcopy(
                        7,
                        64 * clamp((17 - chaintime_at_tcg / 3), 0, 8),
                        416,
                        64,
                        64,
                        chainx_at_tcg + star_at_tcg(0, cnt),
                        chainy_at_tcg + star_at_tcg(1, cnt));
                    star_at_tcg(1, cnt) += 2;
                }
            }
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                p_at_tcg = (t_at_tcg / 4 + cnt) % 7;
                boxl(
                    chainx_at_tcg - p_at_tcg,
                    chainy_at_tcg - p_at_tcg,
                    72,
                    96,
                    {static_cast<uint8_t>(p_at_tcg * 20),
                     static_cast<uint8_t>(25 + p_at_tcg * 20),
                     static_cast<uint8_t>(60 + p_at_tcg * 20)});
            }
        }
        for (int cnt = 0, cnt_end = (efllistmax_at_tcg); cnt < cnt_end; ++cnt)
        {
            if (efllist_at_tcg(4, cnt) <= 0)
            {
                continue;
            }
            --efllist_at_tcg(4, cnt);
            if (efllist_at_tcg(0, cnt) == 1)
            {
                font(20 - en * 2, snail::Font::Style::bold);
                mes(efllist_at_tcg(5, cnt) + 11,
                    efllist_at_tcg(6, cnt) + efllist_at_tcg(4, cnt) / 3 + 21,
                    std::to_string(std::abs(efllist_at_tcg(1, cnt))));
                mes(efllist_at_tcg(5, cnt) + 10,
                    efllist_at_tcg(6, cnt) + efllist_at_tcg(4, cnt) / 3 + 20,
                    std::to_string(std::abs(efllist_at_tcg(1, cnt))),
                    {255, 100, 100});
                font(13 - en * 2);
                gmode(5, (efllist_at_tcg(4, cnt) - 30) * 8);
                gcopy(
                    7,
                    64 * clamp((10 - (efllist_at_tcg(4, cnt) - 30) / 3), 0, 8),
                    360,
                    48,
                    64,
                    efllist_at_tcg(5, cnt) - 12,
                    efllist_at_tcg(6, cnt) + 10);
            }
            if (efllist_at_tcg(0, cnt) == 2)
            {
                font(20 - en * 2, snail::Font::Style::bold);
                mes(efllist_at_tcg(2, cnt) + 31,
                    efllist_at_tcg(3, cnt) + efllist_at_tcg(4, cnt) / 3 + 26,
                    std::to_string(std::abs(efllist_at_tcg(1, cnt))));
                mes(efllist_at_tcg(2, cnt) + 30,
                    efllist_at_tcg(3, cnt) + efllist_at_tcg(4, cnt) / 3 + 25,
                    std::to_string(std::abs(efllist_at_tcg(1, cnt))),
                    {100, 100, 255});
                font(13 - en * 2);
                gmode(5, (efllist_at_tcg(4, cnt) - 30) * 8);
                gcopy(
                    7,
                    64 * clamp((10 - (efllist_at_tcg(4, cnt) - 30) / 3), 0, 8),
                    416,
                    64,
                    64,
                    efllist_at_tcg(5, cnt),
                    efllist_at_tcg(6, cnt) + 24);
                gcopy(
                    7,
                    64 * clamp((10 - (efllist_at_tcg(4, cnt) - 30) / 3), 0, 8),
                    416,
                    64,
                    64,
                    efllist_at_tcg(2, cnt),
                    efllist_at_tcg(3, cnt) + 24);
            }
        }
        gmode(2);
        if (screenupdate_at_tcg == -1)
        {
            screenupdate_at_tcg = 0;
            return;
        }
        else
        {
            await(15);
            redraw();
        }
        if (anime_at_tcg == 0)
        {
            return;
        }
    }
}



void efllistadd(
    int prm_996,
    int prm_997,
    int prm_998,
    int prm_999,
    int prm_1000,
    int prm_1001)
{
    for (int cnt = 0, cnt_end = (efllistmax_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (efllist_at_tcg(4, cnt) <= 0)
        {
            efllist_at_tcg(0, cnt) = prm_996;
            efllist_at_tcg(1, cnt) = prm_997;
            if (prm_996 == 1)
            {
                efllist_at_tcg(4, cnt) = 60;
                efllist_at_tcg(5, cnt) = prm_998 + rnd(30);
                efllist_at_tcg(6, cnt) = prm_999 + rnd(20);
            }
            if (prm_996 == 2)
            {
                efllist_at_tcg(4, cnt) = 60;
                efllist_at_tcg(5, cnt) = prm_998;
                efllist_at_tcg(6, cnt) = prm_999;
                efllist_at_tcg(2, cnt) = prm_1000;
                efllist_at_tcg(3, cnt) = prm_1001;
            }
            break;
        }
    }
}



int create_card(int card_index, int card_id)
{
    CardInfo card_info;
    const auto bg_and_desc = card_ref(card_id, card_info);
    card_at_tcg(18, card_index) = card_id;
    card_at_tcg(9, card_index) = card_info.cardreftype;
    card_at_tcg(10, card_index) = card_info.cardrefcost;
    card_at_tcg(16, card_index) = card_info.cardrefhp;
    card_at_tcg(11, card_index) = card_info.cardrefattack;
    card_at_tcg(13, card_index) = card_info.cardrefskill;
    card_at_tcg(17, card_index) = card_info.cardrefpic;
    card_at_tcg(19, card_index) = bg_and_desc.first;
    carddetailn_at_tcg(card_index) = bg_and_desc.second;
    cardn_at_tcg(0, card_index) = card_info.cardrefrace;
    card_at_tcg(20, card_index) = card_info.cardrefskillcost;
    card_at_tcg(23, card_index) = card_info.cardrefdomain;
    return card_index;
}



void cardpos(int player_index, int card_index)
{
    int l_at_tcg = 0;
    int spotlistmax_at_tcg = 0;
    elona_vector1<int> spotlist_at_tcg;
    int x2_at_tcg = 0;
    if (player_index == 0)
    {
        l_at_tcg = 1;
    }
    else
    {
        l_at_tcg = 2;
    }
    p_at_tcg = -1;
    spotlistmax_at_tcg = clistmax_at_tcg(l_at_tcg);
    for (int cnt = 0, cnt_end = (spotlistmax_at_tcg); cnt < cnt_end; ++cnt)
    {
        spotlist_at_tcg(cnt) = clist_at_tcg(cnt, l_at_tcg);
        if (p_at_tcg == -1)
        {
            if (card_at_tcg(9, clist_at_tcg(cnt, l_at_tcg)) != 10)
            {
                p_at_tcg = cnt;
            }
        }
    }
    if (card_index != -1)
    {
        if (p_at_tcg != -1)
        {
            for (int cnt = 0, cnt_end = (spotlistmax_at_tcg - p_at_tcg);
                 cnt < cnt_end;
                 ++cnt)
            {
                spotlist_at_tcg(spotlistmax_at_tcg - cnt) =
                    spotlist_at_tcg(spotlistmax_at_tcg - cnt - 1);
            }
            spotlist_at_tcg(p_at_tcg) = card_index;
        }
        else
        {
            spotlist_at_tcg(spotlistmax_at_tcg) = card_index;
        }
        ++spotlistmax_at_tcg;
    }
    x2_at_tcg = spotspace_at_tcg;
    x_at_tcg = basex_at_tcg + 466 - spotlistmax_at_tcg * x2_at_tcg / 2;
    for (int cnt = 0, cnt_end = (spotlistmax_at_tcg); cnt < cnt_end; ++cnt)
    {
        p_at_tcg = spotlist_at_tcg(cnt);
        card_at_tcg(4, p_at_tcg) = x_at_tcg + cnt * x2_at_tcg;
        card_at_tcg(5, p_at_tcg) = spotiy_at_tcg(player_index);
    }
}



void gravecard(int card_index)
{
    if (card_at_tcg(0, card_index) == 1)
    {
        for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
        {
            if (card_at_tcg(0, cnt) != 1)
            {
                continue;
            }
            if (card_at_tcg(1, cnt) != card_at_tcg(1, card_index))
            {
                continue;
            }
            if (card_at_tcg(2, cnt) > card_at_tcg(2, card_index))
            {
                card_at_tcg(4, cnt) -= spotspace_at_tcg;
            }
        }
    }
    card_at_tcg(0, card_index) = -2;
    ++cpdata_at_tcg(8, card_at_tcg(1, card_index));
    n_at_tcg = card_at_tcg(1, card_index);
    if (gravesum_at_tcg(n_at_tcg) > 2)
    {
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            gravelist_at_tcg(cnt, n_at_tcg) =
                gravelist_at_tcg(cnt + 1, n_at_tcg);
        }
        gravelist_at_tcg(2, n_at_tcg) = card_index;
    }
    else
    {
        gravelist_at_tcg(gravesum_at_tcg(n_at_tcg), n_at_tcg) = card_index;
        ++gravesum_at_tcg(n_at_tcg);
    }
    makecardlist();
    cardpos(card_at_tcg(1, card_index), -1);
    tcg_update_mana();
}



void dmgcard(int card_index, int damage_amount)
{
    if (damage_amount > 0)
    {
        snd("core.atk1");
    }
    efllistadd(
        1,
        -damage_amount,
        card_at_tcg(2, card_index),
        card_at_tcg(3, card_index));
    card_at_tcg(12, card_index) -= damage_amount;
    if (card_at_tcg(12, card_index) < 0)
    {
        card_at_tcg(12, card_index) = 0;
    }
    if (card_at_tcg(12, card_index) <= 0)
    {
        card_at_tcg(6, card_index) = 2;
        card_at_tcg(7, card_index) = 18;
        tcgdraw();
        gravecard(card_index);
    }
}



void dmgplayer(int player_index, int damage_amount)
{
    if (damage_amount > 0)
    {
        snd("core.atk1");
    }
    efllistadd(
        1, -damage_amount, cpx_at_tcg(player_index), cpy_at_tcg(player_index));
    cpdata_at_tcg(4, player_index) -= damage_amount;
    if (cpdata_at_tcg(4, player_index) < 0)
    {
        cpdata_at_tcg(4, player_index) = 0;
    }
}



void delbottomcard(int player_index)
{
    int delcard_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != player_index)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) == 2)
        {
            card_at_tcg(4, cnt) -= holderspace_at_tcg;
            if (card_at_tcg(4, cnt) < holderix_at_tcg(player_index))
            {
                card_at_tcg(6, cnt) = 2;
                card_at_tcg(7, cnt) = 18;
                delcard_at_tcg = cnt;
            }
        }
    }
    tcgdraw();
    gravecard(delcard_at_tcg);
}



int gameover()
{
    if (cpdata_at_tcg(4, 1) <= 0)
    {
        return 2;
    }
    if (cpdata_at_tcg(4, 0) <= 0)
    {
        return 1;
    }
    return 0;
}



int getholdersum(int player_index)
{
    p_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != player_index)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) == 2)
        {
            ++p_at_tcg;
        }
    }
    return p_at_tcg;
}



int getspotsum(int player_index)
{
    p_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != player_index)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) == 1)
        {
            ++p_at_tcg;
        }
    }
    return p_at_tcg;
}



int getdecksum(int player_index)
{
    p_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != player_index)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) == -1)
        {
            ++p_at_tcg;
        }
    }
    return p_at_tcg;
}



int cardcandeclareattack(int card_index)
{
    if (card_at_tcg(0, card_index) != 1)
    {
        return 0;
    }
    if (card_at_tcg(9, card_index) != 10)
    {
        return 0;
    }
    if (cdbit(0, card_index))
    {
        return 0;
    }
    return 1;
}



int cardcanblock(int card_index)
{
    if (card_at_tcg(0, card_index) != 1)
    {
        return 0;
    }
    if (card_at_tcg(9, card_index) != 10)
    {
        return 0;
    }
    if (cdbit(0, card_index))
    {
        if (card_at_tcg(14, card_index) != -4)
        {
            return 0;
        }
    }
    return 1;
}



int cardcanuseskill(int card_index)
{
    if (card_at_tcg(0, card_index) != 1)
    {
        return 0;
    }
    if (card_at_tcg(9, card_index) != 10)
    {
        return 0;
    }
    if (cdbit(0, card_index))
    {
        return 0;
    }
    if (card_at_tcg(20, card_index) == 0)
    {
        return 0;
    }
    if (card_at_tcg(20, card_index) >
        cpdata_at_tcg(5, card_at_tcg(1, card_index)))
    {
        return 0;
    }
    return 1;
}



void getrandomcard(int player_index)
{
    if (getdecksum(player_index) == 0)
    {
        cpdata_at_tcg(4, player_index) = 0;
        return;
    }
    p_at_tcg = getholdersum(player_index);

    while (1)
    {
        c_at_tcg = rnd(maxcard_at_tcg);
        if (card_at_tcg(0, c_at_tcg) == -1)
        {
            if (card_at_tcg(1, c_at_tcg) == player_index)
            {
                break;
            }
        }
    }

    card_at_tcg(0, c_at_tcg) = 2;
    card_at_tcg(1, c_at_tcg) = player_index;
    card_at_tcg(2, c_at_tcg) = deckix_at_tcg(player_index);
    card_at_tcg(3, c_at_tcg) = deckiy_at_tcg(player_index);
    card_at_tcg(4, c_at_tcg) =
        holderix_at_tcg(player_index) + p_at_tcg * holderspace_at_tcg;
    card_at_tcg(5, c_at_tcg) = holderiy_at_tcg(player_index);
    card_at_tcg(6, c_at_tcg) = 0;
    card_at_tcg(7, c_at_tcg) = 0;
    card_at_tcg(12, c_at_tcg) = card_at_tcg(16, c_at_tcg);
    --cpdata_at_tcg(7, player_index);
    if (player_index == 0)
    {
        cdbitmod(1, c_at_tcg, 1);
    }
    else
    {
        cdbitmod(1, c_at_tcg, 0);
    }
    if (getholdersum(player_index) > 7)
    {
        delbottomcard(player_index);
    }
    makecardlist();
}



void saccard(int card_index, int player_index)
{
    snd("core.feat");
    ++sac_at_tcg;
    if (player_index == 0)
    {
        cardhelp(i18n::s.get("core.tcg.sacrifice.you"), 40);
    }
    else
    {
        cardhelp(i18n::s.get("core.tcg.sacrifice.opponent"), 40);
    }
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != player_index)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) != 2)
        {
            continue;
        }
        if (card_at_tcg(2, cnt) <= card_at_tcg(2, card_index))
        {
            continue;
        }
        card_at_tcg(4, cnt) -= holderspace_at_tcg;
    }
    ++cpdata_at_tcg(6, player_index);
    ++cpdata_at_tcg(5, player_index);
    int card_id = 500 + card_at_tcg(23, card_index) * 2 + rnd(2);
    CardInfo card_info;
    card_ref(card_id, card_info);
    create_card(card_index, card_id);
    cdbitmod(1, card_index, 1);
    card_at_tcg(4, card_index) = landix_at_tcg(player_index) +
        landsum_at_tcg(player_index) *
            clamp(
                (landspace_at_tcg - landsum_at_tcg(player_index) / 2),
                4,
                landspace_at_tcg);
    card_at_tcg(5, card_index) = landiy_at_tcg(player_index);
    landlist_at_tcg(landsum_at_tcg(player_index), player_index) = card_index;
    ++landsum_at_tcg(player_index);
    tcgdraw();
    makecardlist();
    card_at_tcg(0, card_index) = 4;
    makecardlist();
    tcg_update_mana();
    efllistadd(
        2,
        1,
        card_at_tcg(2, card_index),
        card_at_tcg(3, card_index),
        cpx_at_tcg(player_index),
        cpy_at_tcg(player_index));
}



void opencard(int card_index)
{
    snd("core.card1");
    cdbitmod(1, card_index, 1);
    tcgdraw();
}



void tcg_show_refs()
{
    SDIM3(cdrefn_at_tcg, 50, 4);
    p_at_tcg = 0;
    cdrefn_at_tcg(p_at_tcg) = i18n::s.get("core.tcg.ref.choose_one_card");
    p_at_tcg = 2;
    cdrefn_at_tcg(p_at_tcg) = i18n::s.get("core.tcg.ref.draws_two_cards");
    p_at_tcg = 3;
    cdrefn_at_tcg(p_at_tcg) = i18n::s.get("core.tcg.ref.return_creature");
}



void actionproc()
{
    int ac_at_tcg = 0;
    int ap_at_tcg = 0;
    int tc_at_tcg = 0;
    spellused_at_tcg = 0;

    while (1)
    {
        if (stack_at_tcg > 0)
        {
            cc_at_tcg = cardstack_at_tcg(0, stack_at_tcg - 1);
            if (spellused_at_tcg == 0)
            {
                if (cardstack_at_tcg(1, stack_at_tcg - 1) == -1)
                {
                    if (cp_at_tcg == 0)
                    {
                        card_at_tcg(5, cc_at_tcg) -= 25;
                    }
                    else
                    {
                        card_at_tcg(5, cc_at_tcg) += 25;
                    }
                    card_at_tcg(14, cc_at_tcg) = -1;
                    cdbitmod(0, cc_at_tcg, 1);
                    tcgdraw();
                    attacktarget_at_tcg = -1;
                    cpisenemy();
                    chainmode_at_tcg = 1;
                    if (cp_at_tcg == player_at_tcg)
                    {
                        cs_at_tcg = -1;
                        for (int cnt = 0,
                                 cnt_end = cnt + (clistmax_at_tcg(cl_at_tcg));
                             cnt < cnt_end;
                             ++cnt)
                        {
                            c_at_tcg = clist_at_tcg(cnt, cl_at_tcg);
                            if (cdbit(0, c_at_tcg) == 0 ||
                                card_at_tcg(14, c_at_tcg) == -4)
                            {
                                cs_at_tcg = cnt;
                                csline_at_tcg = cl_at_tcg;
                                break;
                            }
                        }
                        selectmode_at_tcg = 1;
                        tcg_prompt_action();
                        selectmode_at_tcg = -1;
                    }
                    else
                    {
                        aiblock_at_tcg = 1;
                        tcg_proc_ai();
                        aiblock_at_tcg = 0;
                    }
                    chainmode_at_tcg = 0;
                    if (spellused_at_tcg)
                    {
                        continue;
                    }
                }
            }
        }
        --stack_at_tcg;
        if (stack_at_tcg < 0)
        {
            tcg_clear_stack();
            return;
        }
        ac_at_tcg = cardstack_at_tcg(0, stack_at_tcg);
        act_at_tcg = cardstack_at_tcg(1, stack_at_tcg);
        ap_at_tcg = cardstack_at_tcg(2, stack_at_tcg);
        if (ap_at_tcg != cp_at_tcg)
        {
            cpflip();
        }
        if (cardstack_at_tcg(1, stack_at_tcg) == -3)
        {
            act_at_tcg = card_at_tcg(13, ac_at_tcg);
            card_at_tcg(14, ac_at_tcg) = -3;
        }
        if (card_at_tcg(0, ac_at_tcg) != 1)
        {
            continue;
        }
        switch (act_at_tcg)
        {
        case -1:
            tc_at_tcg = attacktarget_at_tcg;
            if (tc_at_tcg != -1)
            {
                card_at_tcg(14, tc_at_tcg) = -2;
                cdbitmod(0, tc_at_tcg, 1);
                if (cp_at_tcg == 0)
                {
                    card_at_tcg(5, tc_at_tcg) += 25;
                }
                else
                {
                    card_at_tcg(5, tc_at_tcg) -= 25;
                }
                tcgdraw();
                dmgcard(tc_at_tcg, card_at_tcg(11, ac_at_tcg));
                dmgcard(ac_at_tcg, card_at_tcg(11, tc_at_tcg));
                if (cp_at_tcg == 0)
                {
                    card_at_tcg(5, tc_at_tcg) -= 25;
                }
                else
                {
                    card_at_tcg(5, tc_at_tcg) += 25;
                }
            }
            else
            {
                dmgplayer(tp_at_tcg, card_at_tcg(11, ac_at_tcg));
            }
            if (cp_at_tcg == 0)
            {
                card_at_tcg(5, ac_at_tcg) += 25;
            }
            else
            {
                card_at_tcg(5, ac_at_tcg) -= 25;
            }
            tcgdraw();
            break;
        case 2:
            getrandomcard(ap_at_tcg);
            tcgdraw();
            getrandomcard(ap_at_tcg);
            tcgdraw();
            break;
        case 1:
            deckmode_at_tcg = 1;
            deckrefn_at_tcg = cardn_at_tcg(0, ac_at_tcg);
            tcg_draw_menu();
            break;
        case 0:
            deckmode_at_tcg = 2;
            tcg_draw_menu();
            break;
        }

        if (card_at_tcg(9, ac_at_tcg) == 20)
        {
            card_at_tcg(6, ac_at_tcg) = 2;
            card_at_tcg(7, ac_at_tcg) = 18;
            tcgdraw();
            gravecard(ac_at_tcg);
        }
    }
}



void tcg_clear_stack()
{
    stack_at_tcg = 0;
}



int putcard(int card_index, int player_index)
{
    if (getspotsum(player_index) >= 8)
    {
        if (player_index == player_at_tcg)
        {
            snd("core.fail1");
            cardhelp(i18n::s.get("core.tcg.put.field_full"), 40);
        }
        return -1;
    }
    if (card_at_tcg(10, card_index) > cpdata_at_tcg(5, player_index))
    {
        if (player_index == player_at_tcg)
        {
            snd("core.fail1");
            cardhelp(i18n::s.get("core.tcg.put.not_enough_mana"), 40);
        }
        return -3;
    }
    cpdata_at_tcg(5, player_index) -= card_at_tcg(10, card_index);
    if (player_index == 0)
    {
        card_at_tcg(5, card_index) -= 25;
    }
    else
    {
        card_at_tcg(5, card_index) += 25;
    }
    tcgdraw();
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != player_index)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) != 2)
        {
            continue;
        }
        if (card_at_tcg(2, cnt) <= card_at_tcg(2, card_index))
        {
            continue;
        }
        card_at_tcg(4, cnt) -= holderspace_at_tcg;
    }
    if (card_at_tcg(9, card_index) == 30)
    {
        cdbitmod(1, card_index, 1);
        card_at_tcg(4, card_index) = landix_at_tcg(player_index) +
            landsum_at_tcg(player_index) *
                clamp(
                    (landspace_at_tcg - landsum_at_tcg(player_index) / 2),
                    4,
                    landspace_at_tcg);
        card_at_tcg(5, card_index) = landiy_at_tcg(player_index);
        landlist_at_tcg(landsum_at_tcg(player_index), player_index) =
            card_index;
        ++landsum_at_tcg(player_index);
        tcgdraw();
        makecardlist();
        card_at_tcg(0, card_index) = 4;
        makecardlist();
        tcg_update_mana();
        return 1;
    }
    p_at_tcg = getspotsum(player_index);
    card_at_tcg(0, card_index) = 1;
    cdbitmod(1, card_index, 0);
    card_at_tcg(22, card_index) = 0;
    card_at_tcg(14, card_index) = -4;
    cdbitmod(0, card_index, 1);
    cardpos(player_index, card_index);
    tcgdraw();
    makecardlist();
    opencard(card_index);
    return 1;
}



void tcgdrawbg()
{
    const auto& info = get_image_info("core.deco_card_a");

    gmode(0);
    for (int cnt = 0, cnt_end = (windowh / info.height + 1); cnt < cnt_end;
         ++cnt)
    {
        cnt2_at_tcg = cnt;
        for (int cnt = 0, cnt_end = (windoww / info.width + 1); cnt < cnt_end;
             ++cnt)
        {
            gcopy(
                info.window_id,
                info.x,
                info.y,
                info.width,
                info.height,
                windoww - (cnt + 1) * info.width,
                windowh - (cnt2_at_tcg + 1) * info.height);
        }
    }
    gmode(2);
}



void tcginit()
{
    elona_vector1<int> spotix_at_tcg;
    turn_at_tcg = 0;
    efllistmax_at_tcg = 10;
    cardmode_at_tcg = 0;
    tcg_show_refs();
    DIM3(card_at_tcg, 50, maxcard_at_tcg);
    SDIM4(cardn_at_tcg, 16, 2, maxcard_at_tcg);
    DIM3(cpdata_at_tcg, 20, 2);
    DIM3(efllist_at_tcg, 10, efllistmax_at_tcg);
    DIM3(elist_at_tcg, 10, 23);
    DIM2(gravesum_at_tcg, 2);
    DIM2(landsum_at_tcg, 2);
    DIM3(landlist_at_tcg, maxcard_at_tcg, 2);
    DIM3(cardstack_at_tcg, 5, 100);
    DIM3(gravelist_at_tcg, 4, 2);
    SDIM3(carddetailn_at_tcg, 200, maxcard_at_tcg);
    SDIM1(helpmsg_at_tcg);
    DIM2(deck, 1000);
    SDIM3(domname_at_tcg, 20, 10);
    phasen_at_tcg(0) = u8"Begin"s;
    phasen_at_tcg(1) = u8"Draw"s;
    phasen_at_tcg(2) = u8"Main"s;
    phasen_at_tcg(3) = u8"End"s;
    phasen_at_tcg(4) = "";
    domname_at_tcg(0) = i18n::s.get("core.tcg.domain.lulwy");
    domname_at_tcg(1) = i18n::s.get("core.tcg.domain.kumiromi");
    domname_at_tcg(2) = i18n::s.get("core.tcg.domain.yacatect");
    domname_at_tcg(3) = i18n::s.get("core.tcg.domain.jure");
    domname_at_tcg(4) = i18n::s.get("core.tcg.domain.mani");
    chainx_at_tcg = 0;
    chainy_at_tcg = 0;
    cfg_chaintime = 50;
    basew_at_tcg = 800;
    baseh_at_tcg = 600;
    basex_at_tcg = (windoww - basew_at_tcg) / 2;
    basey_at_tcg = (windowh - baseh_at_tcg) / 2;
    graveix_at_tcg(0) = basex_at_tcg + 638;
    graveix_at_tcg(1) = basex_at_tcg + 638;
    graveiy_at_tcg(0) = basey_at_tcg + 315;
    graveiy_at_tcg(1) = basey_at_tcg + 125;
    gravespace_at_tcg = 22;
    landix_at_tcg(0) = basex_at_tcg + 150;
    landix_at_tcg(1) = basex_at_tcg + 150;
    landiy_at_tcg(0) = basey_at_tcg + 315;
    landiy_at_tcg(1) = basey_at_tcg + 125;
    landspace_at_tcg = 22;
    spotix_at_tcg(0) = basex_at_tcg + 138;
    spotix_at_tcg(1) = basex_at_tcg + 138;
    spotiy_at_tcg(0) = basey_at_tcg + 290;
    spotiy_at_tcg(1) = basey_at_tcg + 150;
    spotspace_at_tcg = 80;
    holderix_at_tcg(0) = basex_at_tcg + 222;
    holderix_at_tcg(1) = basex_at_tcg + 222;
    holderiy_at_tcg(0) = basey_at_tcg + 420;
    holderiy_at_tcg(1) = basey_at_tcg + 20;
    holderspace_at_tcg = 80;
    deckix_at_tcg(0) = basex_at_tcg + 800;
    deckix_at_tcg(1) = basex_at_tcg + 800;
    deckiy_at_tcg(0) = basey_at_tcg + 420;
    deckiy_at_tcg(1) = basey_at_tcg + 20;
    selectmode_at_tcg = -1;
    asset_load("core.deco_card");
    asset_load("core.interface2");
    gsel(2);
    picload(filesystem::dirs::graphic() / u8"card0.bmp", 0, 0, false);
    asset_load("core.bg_card");
    tcg_prepare_cnt2();
    tcgdrawbg();
}



int calcstartcard(int player_index)
{
    return 6 - (cpdata_at_tcg(9, player_index) > 2) -
        (cpdata_at_tcg(9, player_index) > 3) -
        (cpdata_at_tcg(9, player_index) > 4);
}



void calcstartattb(int player_index)
{
    cpdata_at_tcg(4, player_index) = 40 - cpdata_at_tcg(9, player_index) * 5;
    cpdata_at_tcg(6, player_index) = 0;
}



void calcdomain()
{
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        DIM2(domain_at_tcg, 5);
        p_at_tcg = cnt;
        cpdata_at_tcg(9, p_at_tcg) = 0;
        for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
        {
            if (card_at_tcg(1, cnt) != p_at_tcg)
            {
                continue;
            }
            if (domain_at_tcg(card_at_tcg(23, cnt)) == 0)
            {
                domain_at_tcg(card_at_tcg(23, cnt)) = 1;
            }
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (domain_at_tcg(cnt))
            {
                ++cpdata_at_tcg(9, p_at_tcg);
            }
        }
        calcstartattb(p_at_tcg);
    }
}



void calcdecksize()
{
    int cardsize_at_tcg = 0;
    game_data.tcg_decks.at(curdeck) = 0;
    cardsize_at_tcg = 0;
    cpdata_at_tcg(9, 0) = 0;
    DIM2(domain_at_tcg, 5);
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        cardsize_at_tcg += card(0, cnt);
        if (deck(card_at_tcg(18, cnt)) == 0)
        {
            continue;
        }
        game_data.tcg_decks.at(curdeck) += deck(card_at_tcg(18, cnt));
        domain_at_tcg(card_at_tcg(23, cnt)) = 1;
    }
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        if (domain_at_tcg(cnt))
        {
            ++cpdata_at_tcg(9, 0);
        }
    }
    calcstartattb(0);
}



void tcgdeck()
{
    maxcard_at_tcg = 1000;
    tcginit();
    cardmode_at_tcg = 1;
    i_at_tcg = 0;
    for (int cnt = 0; cnt < 1000; ++cnt)
    {
        if (card(0, cnt) == 0)
        {
            continue;
        }
        create_card(i_at_tcg, cnt);
        card_at_tcg(0, i_at_tcg) = -1;
        card_at_tcg(1, i_at_tcg) = 0;
        ++i_at_tcg;
    }

    while (1)
    {
        tcgdrawbg();
        s_at_tcg(0) = i18n::s.get("core.tcg.deck.color.white");
        s_at_tcg(1) = i18n::s.get("core.tcg.deck.color.blue");
        s_at_tcg(2) = i18n::s.get("core.tcg.deck.color.silver");
        s_at_tcg(3) = i18n::s.get("core.tcg.deck.color.red");
        s_at_tcg(4) = i18n::s.get("core.tcg.deck.color.black");

        Prompt prompt;
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            s_at_tcg(cnt) = i18n::s.get("core.tcg.deck.name", s_at_tcg(cnt));
            if (save_fs_exists(fs::u8path(u8"deck_"s + cnt + u8".s2")))
            {
                if (game_data.tcg_decks.at(cnt) != 30)
                {
                    s_at_tcg(cnt) += u8" (NG "s + game_data.tcg_decks.at(cnt) +
                        u8"/"s + 30 + u8")"s;
                }
                if (game_data.tcg_used_deck == cnt)
                {
                    s_at_tcg(cnt) += u8" [Use]"s;
                }
            }
            else
            {
                s_at_tcg(cnt) += " (" + i18n::s.get("core.tcg.deck.new") + ")";
            }
            prompt.append(s_at_tcg(cnt));
        }
        rtval = prompt.query(basex_at_tcg + 400, basey_at_tcg + 230, 300);
        if (rtval == -1)
        {
            break;
        }
        DIM2(deck, 1000);
        curdeck = rtval;
        if (save_fs_exists(fs::u8path(u8"deck_"s + curdeck + u8".s2")))
        {
            Prompt prompt;
            prompt.append(i18n::s.get("core.tcg.deck.choices.edit"));
            prompt.append(i18n::s.get("core.tcg.deck.choices.set_as_main"));
            rtval = prompt.query(400, basey_at_tcg + 230, 240);

            if (rtval == -1)
            {
                continue;
            }
            if (rtval == 1)
            {
                game_data.tcg_used_deck = curdeck;
                continue;
            }
            if (rtval == 0)
            {
                ctrl_file_deck_read(fs::u8path(u8"deck_"s + curdeck + u8".s2"));
            }
        }
        decksizebk_at_tcg = game_data.tcg_decks.at(curdeck);
        snd("core.wear");
        calcdecksize();
        deckmode_at_tcg(0) = 0;
        deckmode_at_tcg(1) = rtval_at_tcg;
        tcg_draw_menu();
    }
}



void tcgmain()
{
    int rp_at_tcg = 0;
    maxcard_at_tcg = 80;
    tcginit();
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        rp_at_tcg = cnt;
        cpx_at_tcg(cnt) = basex_at_tcg + 23;
        cpy_at_tcg(cnt) = basey_at_tcg + 236 - cnt * 120;
        cpdata_at_tcg(4, cnt) = 30;
        cpdata_at_tcg(8, cnt) = 0;
        cpdata_at_tcg(7, cnt) = 30;
        for (int cnt = 0; cnt < 30; ++cnt)
        {
            cc_at_tcg = rp_at_tcg * 40 + cnt;
            int card_id = rnd(1000);
            CardInfo card_info;
            card_ref(card_id, card_info);
            if (card_info.cardrefcost == 0)
            {
                --cnt;
                continue;
            }
            create_card(cc_at_tcg, card_id);
            card_at_tcg(0, cc_at_tcg) = -1;
            card_at_tcg(1, cc_at_tcg) = rp_at_tcg;
        }
    }
    calcdomain();
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        cp_at_tcg = cnt;
        for (int cnt = 0, cnt_end = (calcstartcard(cnt)); cnt < cnt_end; ++cnt)
        {
            getrandomcard(cp_at_tcg);
        }
    }
    ct_at_tcg = 0;
    player_at_tcg = -1;

    while (1)
    {
        cpisme();
        tcg_phase_one();
        if (gameover())
        {
            tcg_game_over();
            return;
        }
        tcg_phase_two();
        if (gameover())
        {
            tcg_game_over();
            return;
        }
        tcg_phase_three();
        if (gameover())
        {
            tcg_game_over();
            return;
        }
        tcg_phase_four();
        if (ct_at_tcg == 0)
        {
            ct_at_tcg = 1;
        }
        else
        {
            ct_at_tcg = 0;
        }
    }
}



void tcg_game_over()
{
}



void tcg_phase_one()
{
    phase_at_tcg = 0;
    ++turn_at_tcg;
    tcgdraw();
    await(50);
    sac_at_tcg = 0;
    cpdata_at_tcg(5, cp_at_tcg) = cpdata_at_tcg(6, cp_at_tcg);
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(0, cnt) != 1)
        {
            continue;
        }
        if (card_at_tcg(1, cnt) != cp_at_tcg)
        {
            continue;
        }
        ++card_at_tcg(22, cnt);
        card_at_tcg(14, cnt) = 0;
        card_at_tcg(12, cnt) = card_at_tcg(16, cnt);
        cdbitmod(0, cnt, 0);
    }
}



void tcg_phase_two()
{
    phase_at_tcg = 1;
    tcgdraw();
    await(50);
    getrandomcard(cp_at_tcg);
    tcgdraw();
}



void tcg_phase_three()
{
    phase_at_tcg = 2;
    tcgdraw();
    await(50);
    if (cp_at_tcg == player_at_tcg)
    {
        selectmode_at_tcg = 0;
        tcg_prompt_action();
    }
    else
    {
        selectmode_at_tcg = -1;
        tcg_proc_ai();
    }
}



void tcg_phase_four()
{
    phase_at_tcg = 3;
    if (cp_at_tcg == player_at_tcg)
    {
        selectmode_at_tcg = 0;
    }
    else
    {
        selectmode_at_tcg = -1;
    }
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        tcgdraw();
    }
}



void csfix()
{
    if (clistmax_at_tcg(csline_at_tcg) == 0)
    {
        if (csline_at_tcg != 0)
        {
            cs_at_tcg = -1;
            csline_at_tcg = 0;
        }
    }
    if (cs_at_tcg == -1)
    {
        if (csline_at_tcg != 0)
        {
            cs_at_tcg = 0;
        }
    }
    if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
    {
        if (csline_at_tcg == 0)
        {
            cs_at_tcg = -1;
        }
        else
        {
            cs_at_tcg = 0;
        }
    }
    if (cs_at_tcg < -1)
    {
        cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
    }
}



void cslineup()
{
    cslinebk_at_tcg = csline_at_tcg;
    while (1)
    {
        ++csline_at_tcg;
        if (csline_at_tcg == 4)
        {
            break;
        }
        if (clistmax_at_tcg(csline_at_tcg) != 0)
        {
            break;
        }
    }
    if (csline_at_tcg == 4)
    {
        csline_at_tcg = 0;
    }
    if (csline_at_tcg == 0)
    {
        cs_at_tcg = -1;
    }
    else
    {
        cs_at_tcg = 0;
    }
    if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
    {
        cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
    }
}



void cslinedown()
{
    cslinebk_at_tcg = csline_at_tcg;
    if (csline_at_tcg == 0)
    {
        csline_at_tcg = 4;
    }
    while (1)
    {
        --csline_at_tcg;
        if (csline_at_tcg == -1)
        {
            break;
        }
        if (clistmax_at_tcg(csline_at_tcg) != 0)
        {
            break;
        }
    }
    if (csline_at_tcg == -1)
    {
        csline_at_tcg = 0;
    }
    if (csline_at_tcg == 0)
    {
        cs_at_tcg = -1;
    }
    else
    {
        cs_at_tcg = 0;
    }
    if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
    {
        cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
    }
}



void tcg_update_mana()
{
    elona_vector1<int> mana_at_tcg;
    int m_at_tcg = 0;
    asset_load("core.bg_card");
    gmode(2);
    font(14 - en * 2);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        gmode(0);
        cnt2_at_tcg = cnt;
        DIM2(mana_at_tcg, 10);
        for (int cnt = 0, cnt_end = (landsum_at_tcg(cnt2_at_tcg));
             cnt < cnt_end;
             ++cnt)
        {
            x_at_tcg = landix_at_tcg(cnt2_at_tcg) +
                cnt *
                    clamp(
                        (landspace_at_tcg - landsum_at_tcg(cnt2_at_tcg) / 2),
                        4,
                        landspace_at_tcg);
            y_at_tcg = landiy_at_tcg(cnt2_at_tcg);
            m_at_tcg = landlist_at_tcg(cnt, cnt2_at_tcg);
            n_at_tcg = std::abs(card_at_tcg(17, m_at_tcg));
            ++mana_at_tcg(card_at_tcg(23, m_at_tcg));
            gcopy(
                2,
                n_at_tcg % 22 * 72,
                n_at_tcg / 22 * 96,
                72,
                96,
                x_at_tcg,
                y_at_tcg);
        }
        y_at_tcg = landiy_at_tcg(cnt2_at_tcg) + (cnt == 0) * 80;
        x_at_tcg = landix_at_tcg(cnt2_at_tcg) - 16;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            if (mana_at_tcg(cnt) == 0)
            {
                continue;
            }
            gcopy(7, cnt * 12, 126, 12, 18, x_at_tcg - 15, y_at_tcg - 2);
            mes(x_at_tcg,
                y_at_tcg,
                std::to_string(mana_at_tcg(cnt)),
                {255, 255, 255});
            if (cnt2_at_tcg == 0)
            {
                y_at_tcg -= 20;
            }
            else
            {
                y_at_tcg += 20;
            }
        }
        for (int cnt = 0, cnt_end = (gravesum_at_tcg(cnt2_at_tcg));
             cnt < cnt_end;
             ++cnt)
        {
            x_at_tcg = graveix_at_tcg(cnt2_at_tcg) + cnt * gravespace_at_tcg;
            y_at_tcg = graveiy_at_tcg(cnt2_at_tcg);
            m_at_tcg = gravelist_at_tcg(cnt, cnt2_at_tcg);
            if (card_at_tcg(17, m_at_tcg) > 0)
            {
                gmode(2);
                gcopy(
                    7,
                    72 + card_at_tcg(19, m_at_tcg) * 72,
                    0,
                    72,
                    96,
                    x_at_tcg,
                    y_at_tcg);
                n_at_tcg = card_at_tcg(17, m_at_tcg) % 1000;
                auto rect = chara_preparepic(card_at_tcg(17, m_at_tcg));
                gsel(4);
                gcopy(
                    rect->buffer,
                    0,
                    960,
                    rect->width,
                    rect->height,
                    x_at_tcg + 13,
                    y_at_tcg + 32 - chara_chips[n_at_tcg].offset_y +
                        rect->height / 6);
            }
            else
            {
                gmode(0);
                n_at_tcg = std::abs(card_at_tcg(17, m_at_tcg));
                gcopy(
                    2,
                    n_at_tcg % 22 * 72,
                    n_at_tcg / 22 * 96,
                    72,
                    96,
                    x_at_tcg,
                    y_at_tcg);
            }
        }
    }
    gsel(0);
}



void tcg_draw_selection()
{
    font(12 + en - en * 2);
    gmode(2);
    for (int cnt = 0, cnt_end = (cfmax_at_tcg); cnt < cnt_end; ++cnt)
    {
        x_at_tcg = basex_at_tcg + 180 + cnt * 80;
        y_at_tcg = basey_at_tcg + 26 + (ccf_at_tcg == cnt) * 3;
        p_at_tcg = cflist_at_tcg(cnt);
        snail::Color text_color{0, 0, 0};
        if (ccf_at_tcg == cnt)
        {
            gmode(2);
            text_color = snail::Color{255, 255, 255};
        }
        else
        {
            gmode(2, 120);
            text_color = snail::Color{200, 200, 200};
        }
        gcopy(7, 360, 96, 79, 20, x_at_tcg, y_at_tcg);
        gmode(2);
        mes(x_at_tcg + 10, y_at_tcg + 4, cfname_at_tcg(p_at_tcg), text_color);
        if (ccf_at_tcg == cnt)
        {
            gcopy(7, 288, 96, 24, 24, x_at_tcg + 65, y_at_tcg - 5);
        }
    }
    font(13 + en - en * 2);
    for (int cnt = 0; cnt < 24; ++cnt)
    {
        p_at_tcg = page_at_tcg * 8 + cnt;
        if (p_at_tcg >= dlistmax_at_tcg)
        {
            break;
        }
        c_at_tcg = dlist_at_tcg(0, p_at_tcg);
        i_at_tcg = card_at_tcg(18, c_at_tcg);
        x_at_tcg = basex_at_tcg + 144 + cnt % 8 * 80;
        y_at_tcg = basey_at_tcg + 70 + cnt / 8 * 150;
        if (deckmode_at_tcg == 0)
        {
            if (deck(i_at_tcg) != 0)
            {
                s_at_tcg = ""s + deck(i_at_tcg);
            }
            else
            {
                s_at_tcg = "";
            }
            s_at_tcg += u8"("s + card(0, i_at_tcg) + u8")"s;
            mes(x_at_tcg + 1, y_at_tcg + 111, s_at_tcg);
            const auto text_color = deck(i_at_tcg) != 0
                ? snail::Color{150, 255, 150}
                : snail::Color{200, 200, 200};
            mes(x_at_tcg, y_at_tcg + 110, s_at_tcg, text_color);
        }
        card_at_tcg(2, c_at_tcg) = x_at_tcg;
        card_at_tcg(3, c_at_tcg) = y_at_tcg;
        tcgdrawcard(c_at_tcg, 1);
    }
    font(13 - en * 2);
    mes(basex_at_tcg + 160,
        basey_at_tcg + 510,
        keybind_get_bound_key_name("northeast") + "," +
            keybind_get_bound_key_name("northwest") +
            i18n::s.get("core.tcg.select.hint"),
        {255, 255, 255});
    mes(basex_at_tcg + 700,
        basey_at_tcg + 510,
        u8"Page "s + dsc_at_tcg / 8 / 3 + u8"/"s +
            (dlistmax_at_tcg - 1) / 8 / 3,
        {255, 255, 255});
}



void tcg_draw_deck_editor()
{
    gmode(0);
    draw("core.bg_card", basex_at_tcg, basey_at_tcg);
    font(13 - en * 2);
    gmode(2);
    if (cardmode_at_tcg != 0 || ct_at_tcg == player_at_tcg)
    {
        gcopy(7, 360, 120, 88, 84, basex_at_tcg + 20, basey_at_tcg + 22);
    }
    else
    {
        gcopy(7, 456, 120, 88, 84, basex_at_tcg + 20, basey_at_tcg + 22);
    }
    if (cardmode_at_tcg == 0)
    {
        mes(basex_at_tcg + 39, basey_at_tcg + 58, u8"Turn "s + turn_at_tcg);
        mes(basex_at_tcg + 38,
            basey_at_tcg + 57,
            u8"Turn "s + turn_at_tcg,
            {255, 255, 255});
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            x_at_tcg = cpx_at_tcg(cnt);
            y_at_tcg = cpy_at_tcg(cnt);
            gcopy(7, 264, 144, 72, 120, x_at_tcg, y_at_tcg);
            s_at_tcg = ""s + cpdata_at_tcg(4, cnt);
            mes(x_at_tcg + 36 - strlen_u(s_at_tcg) * 3,
                y_at_tcg + 9 - en,
                s_at_tcg,
                {255, 255, 255});
            if (cnt != player_at_tcg)
            {
                s_at_tcg = u8"?/"s + cpdata_at_tcg(6, cnt);
            }
            else
            {
                s_at_tcg = ""s + cpdata_at_tcg(5, cnt) + u8"/"s +
                    cpdata_at_tcg(6, cnt);
            }
            mes(x_at_tcg + 36 - strlen_u(s_at_tcg) * 3,
                y_at_tcg + 95 - en,
                s_at_tcg,
                {255, 255, 255});
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (cnt - 1 == phase_at_tcg)
            {
                gcopy(
                    7,
                    360,
                    216,
                    106,
                    18,
                    basex_at_tcg + 4,
                    basey_at_tcg + 370 + cnt * 20);
            }
            if (cnt == 0)
            {
                if (ct_at_tcg == player_at_tcg)
                {
                    mes(basex_at_tcg + 36,
                        basey_at_tcg + 373 + cnt * 20,
                        u8"Player"s,
                        {150, 150, 255});
                }
                else
                {
                    mes(basex_at_tcg + 36,
                        basey_at_tcg + 373 + cnt * 20,
                        u8"Opponent"s,
                        {255, 150, 150});
                }
            }
            else
            {
                mes(basex_at_tcg + 36,
                    basey_at_tcg + 373 + cnt * 20,
                    phasen_at_tcg(cnt - 1),
                    {215, 215, 215});
            }
        }
    }
    else
    {
        mes(basex_at_tcg + 41, basey_at_tcg + 53, u8"Deck\n Editor"s);
        mes(basex_at_tcg + 40,
            basey_at_tcg + 52,
            u8"Deck\n Editor"s,
            {255, 255, 255});
        const auto text_color = game_data.tcg_decks.at(curdeck) != 30
            ? snail::Color{255, 100, 100}
            : snail::Color{100, 255, 100};
        mes(basex_at_tcg + 24,
            basey_at_tcg + 120,
            u8"Deck "s + game_data.tcg_decks.at(curdeck) + u8"/"s + 30,
            text_color);
        mes(basex_at_tcg + 24,
            basey_at_tcg + 140,
            u8"Life "s + cpdata_at_tcg(4, 0),
            {215, 215, 215});
        mes(basex_at_tcg + 24,
            basey_at_tcg + 160,
            u8"Mana "s + cpdata_at_tcg(6, 0),
            {215, 215, 215});
        mes(basex_at_tcg + 24,
            basey_at_tcg + 180,
            u8"Card "s + calcstartcard(0),
            {215, 215, 215});
        mes(basex_at_tcg + 24,
            basey_at_tcg + 220,
            u8"Domain * "s + cpdata_at_tcg(9, 0),
            {215, 215, 215});
        s_at_tcg = "";
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (domain_at_tcg(cnt))
            {
                s_at_tcg += ""s + domname_at_tcg(cnt) + u8"\n"s;
            }
        }
        mes(basex_at_tcg + 24, basey_at_tcg + 240, s_at_tcg);
    }
    font(12 + en - en * 2);
    mes(basex_at_tcg + 146,
        basey_at_tcg + 545,
        helpmsg_at_tcg,
        {215, 215, 215});
}



void tcg_prepare_cnt2()
{
    gmode(2, 180);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        cnt2_at_tcg = cnt;
    }
    gsel(0);
}



void tcg_update_page()
{
    if (dsc_at_tcg < 0)
    {
        dsc_at_tcg = dlistmax_at_tcg - 1;
    }
    if (dsc_at_tcg >= dlistmax_at_tcg)
    {
        dsc_at_tcg = 0;
    }
    if (dsc_at_tcg >= (page_at_tcg + 3) * 8)
    {
        page_at_tcg = dsc_at_tcg / 8;
    }
    if (dsc_at_tcg < page_at_tcg * 8)
    {
        page_at_tcg = dsc_at_tcg / 8;
    }
    page_at_tcg = page_at_tcg - page_at_tcg % 3;
}



void tcg_draw_menu()
{
    asset_load("core.bg_card");
    gsel(0);
    DIM3(dlist_at_tcg, 2, 400);
    DIM2(cflist_at_tcg, 10);
    SDIM3(cfname_at_tcg, 16, 10);
    cfname_at_tcg(0) = i18n::s.get("core.tcg.menu.list");
    cfname_at_tcg(1) = i18n::s.get("core.tcg.menu.deck");
    cfname_at_tcg(2) = domname_at_tcg(0);
    cfname_at_tcg(3) = domname_at_tcg(1);
    cfname_at_tcg(4) = domname_at_tcg(2);
    cfname_at_tcg(5) = domname_at_tcg(3);
    cfname_at_tcg(6) = domname_at_tcg(4);
    cflist_at_tcg = 0;
    cfmax_at_tcg = 1;
    ccf_at_tcg = 0;
    if (deckmode_at_tcg == 0)
    {
        cflist_at_tcg(0) = 1;
        cflist_at_tcg(1) = 2;
        cflist_at_tcg(2) = 3;
        cflist_at_tcg(3) = 4;
        cflist_at_tcg(4) = 5;
        cflist_at_tcg(5) = 6;
        cfmax_at_tcg = 6;
    }

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            dlistmax_at_tcg = 0;
            dsc_at_tcg = 0;
            for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
            {
                if (card_at_tcg(0, cnt) != -1)
                {
                    continue;
                }
                if (card_at_tcg(1, cnt) != cp_at_tcg)
                {
                    continue;
                }
                if (cflist_at_tcg(ccf_at_tcg) == 1)
                {
                    if (deck(card_at_tcg(18, cnt)) == 0)
                    {
                        continue;
                    }
                }
                if (cflist_at_tcg(ccf_at_tcg) >= 2)
                {
                    if (cflist_at_tcg(ccf_at_tcg) <= 6)
                    {
                        if (card_at_tcg(23, cnt) !=
                            cflist_at_tcg(ccf_at_tcg) - 2)
                        {
                            continue;
                        }
                    }
                }
                if (deckmode_at_tcg == 1)
                {
                    if (cardn_at_tcg(0, cnt) != deckrefn_at_tcg)
                    {
                        continue;
                    }
                }
                if (deckmode_at_tcg == 1 || deckmode_at_tcg == 2)
                {
                    f_at_tcg = 0;
                    cnt2_at_tcg = cnt;
                    for (int cnt = 0, cnt_end = (dlistmax_at_tcg);
                         cnt < cnt_end;
                         ++cnt)
                    {
                        c_at_tcg = dlist_at_tcg(0, cnt);
                        if (card_at_tcg(18, c_at_tcg) ==
                            card_at_tcg(18, cnt2_at_tcg))
                        {
                            f_at_tcg = 1;
                            break;
                        }
                    }
                    if (f_at_tcg)
                    {
                        continue;
                    }
                }
                cdbitmod(1, cnt, 1);
                dlist_at_tcg(0, dlistmax_at_tcg) = cnt;
                ++dlistmax_at_tcg;
            }
            while (1)
            {
                f_at_tcg = 0;
                if (dlistmax_at_tcg == 0)
                {
                    break;
                }
                for (int cnt = 0, cnt_end = (dlistmax_at_tcg - 1);
                     cnt < cnt_end;
                     ++cnt)
                {
                    p_at_tcg(0) =
                        card_at_tcg(10, dlist_at_tcg(0, cnt)) * 10000 +
                        card_at_tcg(18, dlist_at_tcg(0, cnt));
                    p_at_tcg(1) =
                        card_at_tcg(10, dlist_at_tcg(0, (cnt + 1))) * 10000 +
                        card_at_tcg(18, dlist_at_tcg(0, (cnt + 1)));
                    if (p_at_tcg > p_at_tcg(1))
                    {
                        f_at_tcg = 1;
                        p_at_tcg(0) = dlist_at_tcg(0, cnt);
                        p_at_tcg(1) = dlist_at_tcg(1, cnt);
                        dlist_at_tcg(0, cnt) = dlist_at_tcg(0, cnt + 1);
                        dlist_at_tcg(1, cnt) = dlist_at_tcg(1, cnt + 1);
                        dlist_at_tcg(0, cnt + 1) = p_at_tcg;
                        dlist_at_tcg(1, cnt + 1) = p_at_tcg(1);
                    }
                }
                if (f_at_tcg == 0)
                {
                    break;
                }
            }
            tcg_update_page();
        }

        tcg_draw_deck_editor();
        tcg_draw_selection();
        redraw();
        await(30);
        auto action = key_check();
        if (action == "next_menu")
        {
            ++ccf_at_tcg;
            snd("core.cursor1");
            if (ccf_at_tcg >= cfmax_at_tcg)
            {
                ccf_at_tcg = 0;
            }
            init = true;
            continue;
        }
        if (action == "previous_menu")
        {
            --ccf_at_tcg;
            snd("core.cursor1");
            if (ccf_at_tcg < 0)
            {
                ccf_at_tcg = cfmax_at_tcg - 1;
            }
            init = true;
            continue;
        }
        if (action == "west")
        {
            --dsc_at_tcg;
            snd("core.cursor1");
        }
        if (action == "east")
        {
            ++dsc_at_tcg;
            snd("core.cursor1");
        }
        if (action == "south")
        {
            dsc_at_tcg += 8;
            snd("core.cursor1");
        }
        if (action == "north")
        {
            dsc_at_tcg -= 8;
            snd("core.cursor1");
        }
        tcg_update_page();
        if (action == "enter")
        {
            if (dlistmax_at_tcg == 0)
            {
                continue;
            }
            if (deckmode_at_tcg == 0)
            {
                if (card_at_tcg(9, dlist_at_tcg(0, dsc_at_tcg)) == 10)
                {
                    if (card_at_tcg(10, dlist_at_tcg(0, dsc_at_tcg)) == 0)
                    {
                        snd("core.fail1");
                        cardhelp(
                            i18n::s.get("core.tcg.card_not_available"), 40);
                        continue;
                    }
                }

                while (true)
                {
                    calcdecksize();
                    tcg_draw_deck_editor();
                    tcg_draw_selection();
                    act_at_tcg(0) = 0;
                    act_at_tcg(1) = 0;
                    act_at_tcg(2) = 0;
                    cc_at_tcg = dlist_at_tcg(0, dsc_at_tcg);
                    if (deck(card_at_tcg(18, cc_at_tcg)) <
                        card(0, card_at_tcg(18, cc_at_tcg)))
                    {
                        act_at_tcg(0) = 1;
                    }
                    if (deck(card_at_tcg(18, cc_at_tcg)) != 0)
                    {
                        act_at_tcg(1) = 1;
                    }
                    if (act_at_tcg(0) == 0)
                    {
                        if (act_at_tcg(1) == 0)
                        {
                            snd("core.fail1");
                            break;
                        }
                    }
                    tcg_update_selection();
                    if (f_at_tcg == 0)
                    {
                        if (act_at_tcg(0))
                        {
                            ++deck(card_at_tcg(18, cc_at_tcg));
                            snd("core.card1");
                            continue;
                        }
                    }
                    if (f_at_tcg == 1)
                    {
                        if (act_at_tcg(1))
                        {
                            --deck(card_at_tcg(18, cc_at_tcg));
                            snd("core.card1");
                            continue;
                        }
                    }
                    break;
                }

                calcdecksize();
                continue;
            }
            rtval_at_tcg = dlist_at_tcg(0, dsc_at_tcg);
            rtval_at_tcg = 1;
            tcg_draw_background();
            return;
        }
        if (action == "cancel")
        {
            if (deckmode_at_tcg == 0)
            {
                Prompt prompt("core.tcg.menu");
                prompt.append("save_and_exit");
                prompt.append("just_exit");
                rtval =
                    prompt.query(basex_at_tcg + 420, basey_at_tcg + 230, 240);

                if (rtval == 0)
                {
                    ctrl_file_deck_write(
                        fs::u8path(u8"deck_"s + curdeck + u8".s2"));
                }
                else
                {
                    game_data.tcg_decks.at(curdeck) = decksizebk_at_tcg;
                }
                if (rtval == -1)
                {
                    continue;
                }
            }
            rtval_at_tcg = 0;
            tcg_draw_background();
            return;
        }
    }
}



int tcg_draw_background()
{
    asset_load("core.bg_card");
    tcg_prepare_cnt2();
    return rtval_at_tcg;
}



void tcg_prompt_action()
{
    if (selectmode_at_tcg == 0)
    {
        cs_at_tcg = -1;
        csline_at_tcg = 0;
    }
    if (selectmode_at_tcg == 1)
    {
        if (cs_at_tcg == -1)
        {
            csline_at_tcg = 0;
        }
        else
        {
            csline_at_tcg = 1;
        }
    }

    while (1)
    {
        tcgdraw();
        cursor_at_tcg = 1;
        await(15);
        auto action = key_check();
        if (action == "east")
        {
            ++cs_at_tcg;
            snd("core.cursor1");
            if (cs_at_tcg == 0)
            {
                if (clistmax_at_tcg(csline_at_tcg) == 0)
                {
                    cslineup();
                }
            }
            csfix();
        }
        if (action == "west")
        {
            --cs_at_tcg;
            snd("core.cursor1");
            if (cs_at_tcg == -1)
            {
                if (csline_at_tcg != 0)
                {
                    cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
                }
            }
            if (cs_at_tcg == -2)
            {
                if (clistmax_at_tcg(csline_at_tcg) == 0)
                {
                    cslinedown();
                }
            }
            csfix();
        }
        if (action == "north")
        {
            cslineup();
            snd("core.cursor1");
            csfix();
        }
        if (action == "south")
        {
            cslinedown();
            snd("core.cursor1");
            csfix();
        }
        if (action == "enter")
        {
            if (cs_at_tcg == -1)
            {
                tcg_clear_cursor();
                return;
            }
            act_at_tcg(0) = 0;
            act_at_tcg(1) = 0;
            act_at_tcg(2) = 0;
            s_at_tcg = "";
            cc_at_tcg = clist_at_tcg(cs_at_tcg, csline_at_tcg);
            if (csline_at_tcg == 0)
            {
                if (card_at_tcg(10, cc_at_tcg) <= cpdata_at_tcg(5, cp_at_tcg))
                {
                    if (card_at_tcg(9, cc_at_tcg) == 20 ||
                        selectmode_at_tcg == 0)
                    {
                        act_at_tcg(0) = 1;
                        s_at_tcg += i18n::s.get("core.tcg.action.put") + "\n";
                    }
                }
                if (sac_at_tcg == 0)
                {
                    if (selectmode_at_tcg == 0)
                    {
                        act_at_tcg(1) = 1;
                        s_at_tcg +=
                            i18n::s.get("core.tcg.action.sacrifice") + "\n";
                    }
                }
            }
            if (csline_at_tcg == 1)
            {
                if (selectmode_at_tcg == 0)
                {
                    if (card_at_tcg(14, cc_at_tcg) != -1)
                    {
                        if (cardcandeclareattack(cc_at_tcg))
                        {
                            act_at_tcg(0) = 1;
                            s_at_tcg +=
                                i18n::s.get("core.tcg.action.declare_attack") +
                                "\n";
                        }
                    }
                }
                if (selectmode_at_tcg == 1)
                {
                    if (cardcanblock(cc_at_tcg))
                    {
                        act_at_tcg(0) = 1;
                        s_at_tcg += i18n::s.get("core.tcg.action.block") + "\n";
                    }
                }
                if (cardcanuseskill(cc_at_tcg))
                {
                    act_at_tcg(2) = 1;
                    s_at_tcg += i18n::s.get("core.tcg.action.use_skill") + "\n";
                }
            }
            f_at_tcg = 0;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                if (act_at_tcg(cnt) != 0)
                {
                    f_at_tcg = 1;
                    break;
                }
            }
            if (f_at_tcg == 0)
            {
                snd("core.fail1");
                cardhelp(
                    i18n::s.get("core.tcg.action.no_action_available"), 40);
                continue;
            }
            snd("core.click1");
            cardhelp(s_at_tcg, 10);
            tcgdraw();
            tcg_update_selection();
            cc_at_tcg = clist_at_tcg(cs_at_tcg, csline_at_tcg);
            if (f_at_tcg == -1)
            {
                continue;
            }
            if (act_at_tcg(f_at_tcg) == 0)
            {
                continue;
            }
            if (csline_at_tcg == 1)
            {
                if (f_at_tcg == 0)
                {
                    if (selectmode_at_tcg == 1)
                    {
                        attacktarget_at_tcg = cc_at_tcg;
                        tcg_clear_cursor();
                        return;
                    }
                    cardstack_at_tcg(0, stack_at_tcg) = cc_at_tcg;
                    cardstack_at_tcg(1, stack_at_tcg) = -1;
                    cardstack_at_tcg(2, stack_at_tcg) = cp_at_tcg;
                    ++stack_at_tcg;
                    actionproc();
                    if (gameover())
                    {
                        tcg_clear_cursor();
                        return;
                    }
                    if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
                    {
                        cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
                    }
                    csfix();
                    continue;
                }
                if (f_at_tcg == 1)
                {
                    card_at_tcg(14, cc_at_tcg) = 0;
                }
                if (f_at_tcg == 2)
                {
                    cardstack_at_tcg(0, stack_at_tcg) = cc_at_tcg;
                    cardstack_at_tcg(1, stack_at_tcg) = -3;
                    cardstack_at_tcg(2, stack_at_tcg) = cp_at_tcg;
                    ++stack_at_tcg;
                    if (chainmode_at_tcg)
                    {
                        chaincontinue_at_tcg = 1;
                        spellused_at_tcg = 1;
                        tcg_clear_cursor();
                        return;
                    }
                    actionproc();
                    if (gameover())
                    {
                        tcg_clear_cursor();
                        return;
                    }
                }
                if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
                {
                    cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
                }
                csfix();
                continue;
            }
            if (f_at_tcg == 1)
            {
                cursor_at_tcg = 0;
                saccard(cc_at_tcg, cp_at_tcg + (csline_at_tcg == 3));
                if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
                {
                    cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
                }
                csfix();
                continue;
            }
            if (f_at_tcg == 0)
            {
                cursor_at_tcg = 0;
                putcard(cc_at_tcg, cp_at_tcg + (csline_at_tcg == 3));
                if (gameover())
                {
                    tcg_clear_cursor();
                    return;
                }
                if (card_at_tcg(9, cc_at_tcg) == 20)
                {
                    cardstack_at_tcg(0, stack_at_tcg) = cc_at_tcg;
                    cardstack_at_tcg(1, stack_at_tcg) = -3;
                    cardstack_at_tcg(2, stack_at_tcg) = cp_at_tcg;
                    ++stack_at_tcg;
                    if (chainmode_at_tcg)
                    {
                        chaincontinue_at_tcg = 1;
                        spellused_at_tcg = 1;
                        tcg_clear_cursor();
                        return;
                    }
                    actionproc();
                }
                if (gameover())
                {
                    tcg_clear_cursor();
                    return;
                }
            }
            if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
            {
                cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
            }
            csfix();
        }
        if (action == "cancel" || key_escape)
        {
            tcg_clear_cursor();
            return;
        }
        if (action == "tcg_surrender") // TODO
        {
            Prompt prompt;
            prompt.append("core.tcg.action.surrender");

            rtval = prompt.query(basex_at_tcg + 420, basey_at_tcg + 230, 200);
            if (rtval == 0)
            {
                cpdata_at_tcg(4, 0) = 0;
                cursor_at_tcg = 0;
                return;
            }
        }
    }
}



void tcg_clear_cursor()
{
    cursor_at_tcg = 0;
}



void tcg_update_selection()
{
    p_at_tcg = 0;
    i_at_tcg = 0;
    f_at_tcg = 1;

    while (1)
    {
        ++p_at_tcg;
        i_at_tcg += f_at_tcg;
        if (i_at_tcg > 30)
        {
            f_at_tcg = -1;
        }
        else if (i_at_tcg < 0)
        {
            f_at_tcg = 1;
        }
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            x_at_tcg(cnt) = card_at_tcg(2, cc_at_tcg) + 20;
            if (cnt == 0)
            {
                y_at_tcg(cnt) =
                    card_at_tcg(3, cc_at_tcg) - clamp(p_at_tcg * 3, 0, 16);
            }
            if (cnt == 1)
            {
                y_at_tcg(cnt) =
                    card_at_tcg(3, cc_at_tcg) + 60 + clamp(p_at_tcg * 3, 0, 16);
            }
            if (cnt == 2)
            {
                y_at_tcg(cnt) = card_at_tcg(3, cc_at_tcg) + 30;
            }
            gmode(0);
            gsel(7);
            gcopy(0, x_at_tcg(cnt), y_at_tcg(cnt), 36, 36, cnt * 48, 264);
            gsel(0);
            if (act_at_tcg(cnt) == 0)
            {
                continue;
            }
            gmode(2, clamp(p_at_tcg * 30 + 20, 0, 255));
            gcopy(7, 192, 96, 36, 36, x_at_tcg(cnt), y_at_tcg(cnt));
            gmode(2, 50 + i_at_tcg * 2);
            gcopy(
                7,
                336 + (cnt == 2) * 12,
                96 + cnt % 2 * 24,
                12,
                12,
                x_at_tcg(cnt) + 13,
                y_at_tcg(cnt) + 11);
        }
        redraw();
        gmode(0);
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            if (act_at_tcg(cnt) == 0)
            {
                continue;
            }
            gcopy(7, cnt * 48, 264, 36, 36, x_at_tcg(cnt), y_at_tcg(cnt));
        }
        await(15);
        auto action = key_check();
        if (action == "north")
        {
            f_at_tcg = 0;
            tcg_card_selected();
            return;
        }
        if (action == "south")
        {
            f_at_tcg = 1;
            tcg_card_selected();
            return;
        }
        if (action == "enter")
        {
            f_at_tcg = 2;
            tcg_card_selected();
            return;
        }
        if (action != ""s)
        {
            f_at_tcg = -1;
            tcg_card_selected();
            return;
        }
    }
}



void tcg_card_selected()
{
}



void tcg_proc_ai_elist()
{
    emax_at_tcg = 0;
    for (int cnt = 0, cnt_end = (clistmax_at_tcg(ch_at_tcg)); cnt < cnt_end;
         ++cnt)
    {
        if (aiblock_at_tcg)
        {
            break;
        }
        c_at_tcg = clist_at_tcg(cnt, ch_at_tcg);
        p_at_tcg = 10;
        if (card_at_tcg(9, c_at_tcg) == 10)
        {
            p_at_tcg = 20;
            p_at_tcg -= std::abs(
                cpdata_at_tcg(6, cp_at_tcg) - card_at_tcg(10, c_at_tcg));
        }
        if (card_at_tcg(13, c_at_tcg) == 2)
        {
            p_at_tcg = (5 - getholdersum(cp_at_tcg)) * 20;
        }
        elist_at_tcg(0, emax_at_tcg) = p_at_tcg;
        elist_at_tcg(1, emax_at_tcg) = c_at_tcg;
        elist_at_tcg(2, emax_at_tcg) = -5;
        ++emax_at_tcg;
    }
    if (aiblock_at_tcg == 0)
    {
        for (int cnt = 0, cnt_end = (clistmax_at_tcg(cl_at_tcg)); cnt < cnt_end;
             ++cnt)
        {
            c_at_tcg = clist_at_tcg(cnt, cl_at_tcg);
            p_at_tcg = 0;
            p_at_tcg = rnd(40);
            if (cardcandeclareattack(c_at_tcg))
            {
                elist_at_tcg(0, emax_at_tcg) = p_at_tcg;
                elist_at_tcg(1, emax_at_tcg) = c_at_tcg;
                elist_at_tcg(2, emax_at_tcg) = -1;
                ++emax_at_tcg;
            }
        }
    }
    else
    {
        for (int cnt = 0, cnt_end = (clistmax_at_tcg(cl_at_tcg)); cnt < cnt_end;
             ++cnt)
        {
            c_at_tcg = clist_at_tcg(cnt, cl_at_tcg);
            p_at_tcg = 0;
            p_at_tcg = rnd(40);
            if (cardcanblock(c_at_tcg))
            {
                elist_at_tcg(0, emax_at_tcg) = p_at_tcg;
                elist_at_tcg(1, emax_at_tcg) = c_at_tcg;
                elist_at_tcg(2, emax_at_tcg) = -2;
                ++emax_at_tcg;
            }
        }
    }
    if (emax_at_tcg == 0)
    {
        return;
    }
    while (1)
    {
        f_at_tcg = 0;
        for (int cnt = 0, cnt_end = (emax_at_tcg - 1); cnt < cnt_end; ++cnt)
        {
            if (elist_at_tcg(0, cnt) < elist_at_tcg(0, cnt + 1))
            {
                cnt2_at_tcg = cnt;
                for (int cnt = 0; cnt < 3; ++cnt)
                {
                    p_at_tcg(cnt) = elist_at_tcg(cnt, cnt2_at_tcg + 1);
                    elist_at_tcg(cnt, cnt2_at_tcg + 1) =
                        elist_at_tcg(cnt, cnt2_at_tcg);
                    elist_at_tcg(cnt, cnt2_at_tcg) = p_at_tcg(cnt);
                }
                f_at_tcg = 1;
                break;
            }
        }
        if (f_at_tcg == 0)
        {
            break;
        }
    }
}



int tcg_try_sacrifice()
{
    if (sac_at_tcg > 0)
    {
        return 0;
    }
    if (getholdersum(cp_at_tcg) <= cpdata_at_tcg(6, cp_at_tcg) / 4 + 1)
    {
        if (rnd(4))
        {
            return 0;
        }
    }
    f_at_tcg = 0;
    p_at_tcg(1) = 50;
    for (int cnt = 0, cnt_end = (emax_at_tcg); cnt < cnt_end; ++cnt)
    {
        c_at_tcg = elist_at_tcg(1, cnt);
        p_at_tcg = elist_at_tcg(0, cnt);
        if (card_at_tcg(0, c_at_tcg) != 2)
        {
            continue;
        }
        if (card_at_tcg(13, c_at_tcg) == 2)
        {
            p_at_tcg = 40;
        }
        if (p_at_tcg < p_at_tcg(1))
        {
            p_at_tcg(1) = p_at_tcg;
            cc_at_tcg = c_at_tcg;
            f_at_tcg = 1;
        }
    }
    if (f_at_tcg)
    {
        saccard(cc_at_tcg, cp_at_tcg);
        tcgdraw();
        return 1;
    }
    return 0;
}



void tcg_proc_ai()
{
    int ec_at_tcg = 0;

    bool init = true;
    while (1)
    {
        if (init)
        {
            spellused_at_tcg = 0;
            const auto input = stick();
            if (input != StickKey::none)
            {
                cpdata_at_tcg(4, 0) = 0;
            }
            tcg_proc_ai_elist();
            ec_at_tcg = 0;
            init = false;
        }
        if (gameover())
        {
            tcg_proc_ai_sacrifice();
            return;
        }
        if (ec_at_tcg >= emax_at_tcg)
        {
            tcg_proc_ai_sacrifice();
            return;
        }
        if (elist_at_tcg(0, ec_at_tcg) <= 0)
        {
            tcg_proc_ai_sacrifice();
            return;
        }
        cc_at_tcg = elist_at_tcg(1, ec_at_tcg);
        if (elist_at_tcg(2, ec_at_tcg) == -5)
        {
            if (card_at_tcg(10, cc_at_tcg) <= cpdata_at_tcg(5, cp_at_tcg))
            {
                putcard(cc_at_tcg, cp_at_tcg);
                if (gameover())
                {
                    tcg_proc_ai_sacrifice();
                    return;
                }
                if (card_at_tcg(9, cc_at_tcg) == 20)
                {
                    cardstack_at_tcg(0, stack_at_tcg) = cc_at_tcg;
                    cardstack_at_tcg(1, stack_at_tcg) = -3;
                    cardstack_at_tcg(2, stack_at_tcg) = cp_at_tcg;
                    ++stack_at_tcg;
                    if (chainmode_at_tcg)
                    {
                        chaincontinue_at_tcg = 1;
                        spellused_at_tcg = 1;
                        tcg_proc_ai_sacrifice();
                        return;
                    }
                    actionproc();
                }
                init = true;
                break;
            }
            else
            {
                int stat = tcg_try_sacrifice();
                if (stat == 1)
                {
                    init = true;
                    break;
                }
            }
        }
        if (elist_at_tcg(2, ec_at_tcg) == -1)
        {
            cardstack_at_tcg(0, stack_at_tcg) = cc_at_tcg;
            cardstack_at_tcg(1, stack_at_tcg) = -1;
            cardstack_at_tcg(2, stack_at_tcg) = cp_at_tcg;
            ++stack_at_tcg;
            actionproc();
        }
        if (elist_at_tcg(2, ec_at_tcg) == -2)
        {
            attacktarget_at_tcg = cc_at_tcg;
            tcg_proc_ai_sacrifice();
            return;
        }
        ++ec_at_tcg;
    }
}



void tcg_proc_ai_sacrifice()
{
    if (aiblock_at_tcg == 0)
    {
        if (sac_at_tcg == 0)
        {
            int stat = tcg_try_sacrifice();
            if (stat == 1)
            {
                tcg_proc_ai();
                return;
            }
        }
    }
    if (gameover())
    {
        return;
    }
}



} // namespace elona
