#include "ctrl_file.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "input.hpp"
#include "macro.hpp"
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
int cardrefbg = 0;
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
int a_at_tcg = 0;
int chaincontinue_at_tcg = 0;
int emax_at_tcg = 0;



int cdbit(int prm_985, int prm_986)
{
    return HMMBITCHECK(card_at_tcg(30 + prm_985 / 32, prm_986), prm_985 % 32);
}



void cdbitmod(int prm_987, int prm_988, int prm_989)
{
    if (prm_989 == 0)
    {
        HMMBITOFF(card_at_tcg(30 + prm_987 / 32, prm_988), prm_987 % 32);
        return;
    }
    HMMBITON(card_at_tcg(30 + prm_987 / 32, prm_988), prm_987 % 32);
    return;
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
    return;
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
    return;
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
    return;
}



std::string cnvrare(int prm_990)
{
    s_at_tcg = "";
    for (int cnt = 0, cnt_end = (clamp(5 - prm_990 / 20, 1, 5)); cnt < cnt_end;
         ++cnt)
    {
        s_at_tcg += u8"*"s;
    }
    return s_at_tcg;
}



int card_ref(int prm_991)
{
    cardrefcost = 0;
    cardrefhp = 0;
    cardrefattack = 0;
    cardrefskill = 0;
    cardrefdomain = 0;
    cardrefrare = 100;
    dbid = prm_991;
    get_card_info();
    if (cardreftype == 0)
    {
        cardreftype = 10;
        cardrefdomain = 4;
    }
    rtvaln = cardrefn;
    if (cardreftype == 10)
    {
        cardrefbg = cardrefdomain;
        rtvaln += lang(u8" <クリーチャー>"s, u8" <Creature>"s)
            + lang(u8"  種族:"s, u8"  Race:"s) + cardrefrace + u8"  Hp:"s
            + cardrefhp + u8"  Atk:"s + cardrefattack;
    }
    if (cardreftype == 30)
    {
        cardrefbg = 6;
        rtvaln += lang(u8" <土地>"s, u8" <Land>"s);
    }
    if (cardreftype == 20)
    {
        cardrefbg = 5;
        rtvaln += lang(u8" <スペル>"s, u8" <Spell>"s);
    }
    rtvaln +=
        lang(u8"  ドメイン:"s, u8"  Domain:"s) + domname_at_tcg(cardrefdomain);
    rtvaln += lang(u8"  レア度:"s, u8"  Rare:"s) + cnvrare(cardrefrare);
    if (cardrefskill != 0)
    {
        s_at_tcg = "";
        if (cardreftype == 10)
        {
            s_at_tcg += lang(u8"スキル:"s, u8"Skill:"s);
        }
        s_at_tcg += cdrefn_at_tcg(cardrefskill);
        talk_conv(s_at_tcg, 95);
        rtvaln += u8"\n"s + s_at_tcg;
    }
    return dbid;
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
    label_1844();
    return;
}



void cardhelp(const std::string& prm_992, int prm_993)
{
    int helpdur_at_tcg = 0;
    int dur_at_tcg = 0;
    if (helpdur_at_tcg > 1)
    {
        if (prm_993 == 0)
        {
            --helpdur_at_tcg;
            return;
        }
    }
    if (prm_993 == 0)
    {
        dur_at_tcg = 1;
    }
    else
    {
        dur_at_tcg = prm_993;
    }
    helpmsg_at_tcg = prm_992;
    helpdur_at_tcg = dur_at_tcg;
    return;
}



void tcgdrawcard(int prm_994, int prm_995)
{
    int selected_at_tcg = 0;
    selected_at_tcg = 0;
    if (prm_995 == 0)
    {
        if (cursor_at_tcg)
        {
            if (cs_at_tcg != -1)
            {
                if (clist_at_tcg(cs_at_tcg, csline_at_tcg) == prm_994)
                {
                    selected_at_tcg = 1;
                }
            }
        }
    }
    else if (prm_994 == dlist_at_tcg(0, dsc_at_tcg))
    {
        selected_at_tcg = 1;
    }
    if (selected_at_tcg)
    {
        gmode(2);
        pos(card_at_tcg(2, prm_994) - 5, card_at_tcg(3, prm_994) - 5);
        gcopy(7, 168, 144, 82, 106);
        if (0 || cdbit(1, prm_994) == 1 || card_at_tcg(1, prm_994) == 0)
        {
            cardhelp(carddetailn_at_tcg(prm_994));
        }
        else
        {
            cardhelp(""s);
        }
    }
    for (int cnt = 0, cnt_end = (1 + (selected_at_tcg == 1)); cnt < cnt_end;
         ++cnt)
    {
        x_at_tcg = card_at_tcg(2, prm_994);
        y_at_tcg = card_at_tcg(3, prm_994);
        if (cnt == 1)
        {
            if (card_at_tcg(6, prm_994) != 0)
            {
                break;
            }
            x_at_tcg = basex_at_tcg + 20;
            y_at_tcg = basey_at_tcg + 490;
            gmode(6, -1, -1, 140);
            pos(x_at_tcg - 6, y_at_tcg - 6);
            gcopy(7, 168, 144, 82, 106);
        }
        gmode(2);
        if (card_at_tcg(6, prm_994) == 2)
        {
            gmode(4, -1, -1, card_at_tcg(7, prm_994) * 15);
        }
        pos(x_at_tcg, y_at_tcg);
        if (cdbit(1, prm_994) == 1
            || (card_at_tcg(1, prm_994) == 0 && cnt == 1))
        {
            if (card_at_tcg(17, prm_994) > 0)
            {
                gcopy(7, 72 + card_at_tcg(19, prm_994) * 72, 0, 72, 96);
                p_at_tcg = card_at_tcg(17, prm_994) % 1000;
                chara_preparepic(p_at_tcg, card_at_tcg(17, prm_994) / 1000);
                pos(x_at_tcg + 13,
                    y_at_tcg + 32 - chipc(4, p_at_tcg)
                        + chipc(3, p_at_tcg) / 6);
                gcopy(5, 0, 960, chipc(2, p_at_tcg), chipc(3, p_at_tcg));
            }
            else
            {
                p_at_tcg = std::abs(card_at_tcg(17, prm_994));
                pos(x_at_tcg, y_at_tcg);
                gcopy(2, p_at_tcg % 22 * 72, p_at_tcg / 22 * 96, 72, 96);
            }
            color(255, 255, 255);
            if (card_at_tcg(9, prm_994) == 10)
            {
                pos(x_at_tcg + 39, y_at_tcg - 8);
                gcopy(7, 48, 96, 36, 26);
                pos(x_at_tcg + 56 - (card_at_tcg(12, prm_994) > 9) * 4 - en,
                    y_at_tcg - 1 - en);
                mes(card_at_tcg(12, prm_994));
                pos(x_at_tcg - 3, y_at_tcg - 8);
                gcopy(7, 0, 96, 36, 26);
                pos(x_at_tcg + 11 - (card_at_tcg(11, prm_994) > 9) * 4 - en,
                    y_at_tcg - 1 - en);
                mes(card_at_tcg(11, prm_994));
                if (card_at_tcg(13, prm_994) != 0)
                {
                    pos(x_at_tcg + 39, y_at_tcg + 78 - en);
                    gcopy(7, 144, 96, 36, 26);
                    pos(x_at_tcg + 56 - en, y_at_tcg + 86 - en);
                    mes(card_at_tcg(20, prm_994));
                }
            }
            if (card_at_tcg(10, prm_994) != 0)
            {
                pos(x_at_tcg - 3, y_at_tcg + 78);
                gcopy(7, 96, 96, 36, 26);
                pos(x_at_tcg + 11 - (card_at_tcg(10, prm_994) > 9) * 4 - en,
                    y_at_tcg + 86 - en);
                mes(card_at_tcg(10, prm_994));
            }
            color(0, 0, 0);
        }
        else
        {
            gcopy(7, 0, 0, 72, 96);
        }
        if (cnt == 0)
        {
            if (card_at_tcg(0, prm_994) == 1)
            {
                if (cdbit(1, prm_994))
                {
                    if (card_at_tcg(9, prm_994) == 10)
                    {
                        if (card_at_tcg(14, prm_994) == -1)
                        {
                            pos(x_at_tcg, y_at_tcg + 18);
                            gcopy(7, 288, 120, 24, 24);
                        }
                        if (card_at_tcg(14, prm_994) == -2)
                        {
                            pos(x_at_tcg, y_at_tcg + 18);
                            gcopy(7, 312, 120, 24, 24);
                        }
                        if (card_at_tcg(14, prm_994) == -3)
                        {
                            pos(x_at_tcg, y_at_tcg + 18);
                            gcopy(7, 264, 120, 24, 24);
                        }
                        if (card_at_tcg(14, prm_994) == -4)
                        {
                            pos(x_at_tcg, y_at_tcg + 18);
                            gcopy(7, 240, 120, 24, 24);
                        }
                    }
                }
            }
        }
    }
    return;
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
        label_1825();
        anime_at_tcg = 0;
        font(12 + en - en * 2);
        color(255, 255, 255);
        gmode(2);
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            x_at_tcg = holderix_at_tcg(cnt) - holderspace_at_tcg;
            y_at_tcg = holderiy_at_tcg(cnt);
            pos(x_at_tcg, y_at_tcg);
            gcopy(7, 96, 144, 72, 96);
            pos(x_at_tcg + 14, y_at_tcg + 75);
            mes(""s + cpdata_at_tcg(7, cnt) + u8"/"s + cpdata_at_tcg(8, cnt));
        }
        color(0, 0, 0);
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
            if (card_at_tcg(2, c_at_tcg) != card_at_tcg(4, c_at_tcg)
                || card_at_tcg(3, c_at_tcg) != card_at_tcg(5, c_at_tcg)
                || card_at_tcg(7, c_at_tcg) > 0)
            {
                anime_at_tcg = 1;
                p_at_tcg = 0;
                if (card_at_tcg(2, c_at_tcg) != card_at_tcg(4, c_at_tcg))
                {
                    p_at_tcg =
                        (card_at_tcg(4, c_at_tcg) - card_at_tcg(2, c_at_tcg))
                        / 6;
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
                        (card_at_tcg(5, c_at_tcg) - card_at_tcg(3, c_at_tcg))
                        / 6;
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
        color(255, 255, 255);
        gmode(2);
        if (cursor_at_tcg)
        {
            if (cs_at_tcg == -1)
            {
                if (phase_at_tcg == 2)
                {
                    if (selectmode_at_tcg == 0)
                    {
                        cardhelp(lang(
                            u8"メインフェイズを終了する。"s,
                            u8"End your main phase."s));
                    }
                    else
                    {
                        cardhelp(lang(u8"ブロックしない。"s, u8"No blocker."s));
                    }
                }
                pos(holderix_at_tcg - holderspace_at_tcg - 5,
                    holderiy_at_tcg - 5);
                gcopy(7, 168, 144, 82, 106);
            }
        }
        color(0, 0, 0);
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
                gmode(5, -1, -1, clamp(chaintime_at_tcg * 3 - 40, 0, 255));
                cnt2_at_tcg = 0;
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    pos(chainx_at_tcg + star_at_tcg(0, cnt),
                        chainy_at_tcg + star_at_tcg(1, cnt));
                    gcopy(
                        7,
                        64 * clamp((17 - chaintime_at_tcg / 3), 0, 8),
                        416,
                        64,
                        64);
                    star_at_tcg(1, cnt) += 2;
                }
            }
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                p_at_tcg = (t_at_tcg / 4 + cnt) % 7;
                color(p_at_tcg * 20, 25 + p_at_tcg * 20, 60 + p_at_tcg * 20);
                boxl(
                    chainx_at_tcg - p_at_tcg,
                    chainy_at_tcg - p_at_tcg,
                    chainx_at_tcg + 72 + p_at_tcg,
                    chainy_at_tcg + 96 + p_at_tcg);
                color(0, 0, 0);
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
                font(20 - en * 2, snail::font_t::style_t::bold);
                pos(efllist_at_tcg(5, cnt) + 11,
                    efllist_at_tcg(6, cnt) + efllist_at_tcg(4, cnt) / 3 + 21);
                mes(std::abs(efllist_at_tcg(1, cnt)));
                color(255, 100, 100);
                pos(efllist_at_tcg(5, cnt) + 10,
                    efllist_at_tcg(6, cnt) + efllist_at_tcg(4, cnt) / 3 + 20);
                mes(std::abs(efllist_at_tcg(1, cnt)));
                color(0, 0, 0);
                font(13 - en * 2);
                gmode(5, -1, -1, (efllist_at_tcg(4, cnt) - 30) * 8);
                pos(efllist_at_tcg(5, cnt) - 12, efllist_at_tcg(6, cnt) + 10);
                gcopy(
                    7,
                    64 * clamp((10 - (efllist_at_tcg(4, cnt) - 30) / 3), 0, 8),
                    360,
                    48,
                    64);
            }
            if (efllist_at_tcg(0, cnt) == 2)
            {
                font(20 - en * 2, snail::font_t::style_t::bold);
                pos(efllist_at_tcg(2, cnt) + 31,
                    efllist_at_tcg(3, cnt) + efllist_at_tcg(4, cnt) / 3 + 26);
                mes(std::abs(efllist_at_tcg(1, cnt)));
                color(100, 100, 255);
                pos(efllist_at_tcg(2, cnt) + 30,
                    efllist_at_tcg(3, cnt) + efllist_at_tcg(4, cnt) / 3 + 25);
                mes(std::abs(efllist_at_tcg(1, cnt)));
                color(0, 0, 0);
                font(13 - en * 2);
                gmode(5, -1, -1, (efllist_at_tcg(4, cnt) - 30) * 8);
                pos(efllist_at_tcg(5, cnt), efllist_at_tcg(6, cnt) + 24);
                gcopy(
                    7,
                    64 * clamp((10 - (efllist_at_tcg(4, cnt) - 30) / 3), 0, 8),
                    416,
                    64,
                    64);
                pos(efllist_at_tcg(2, cnt), efllist_at_tcg(3, cnt) + 24);
                gcopy(
                    7,
                    64 * clamp((10 - (efllist_at_tcg(4, cnt) - 30) / 3), 0, 8),
                    416,
                    64,
                    64);
            }
        }
        gmode(2);
        if (screenupdate_at_tcg == -1)
        {
            screenupdate_at_tcg = 0;
            label_1773();
            return;
        }
        else
        {
            await(15);
            redraw();
        }
        if (anime_at_tcg == 0)
        {
            label_1773();
            return;
        }
    }
}



void label_1773()
{
    return;
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
    return;
}



int create_card(int prm_1002, int prm_1003)
{
    int stat = card_ref(prm_1003);
    card_at_tcg(18, prm_1002) = stat;
    card_at_tcg(9, prm_1002) = cardreftype;
    card_at_tcg(10, prm_1002) = cardrefcost;
    card_at_tcg(16, prm_1002) = cardrefhp;
    card_at_tcg(11, prm_1002) = cardrefattack;
    card_at_tcg(13, prm_1002) = cardrefskill;
    card_at_tcg(17, prm_1002) = cardrefpic;
    card_at_tcg(19, prm_1002) = cardrefbg;
    carddetailn_at_tcg(prm_1002) = rtvaln;
    cardn_at_tcg(0, prm_1002) = cardrefrace;
    card_at_tcg(20, prm_1002) = cardrefskillcost;
    card_at_tcg(23, prm_1002) = cardrefdomain;
    return prm_1002;
}



void cardpos(int prm_1004, int prm_1005)
{
    int l_at_tcg = 0;
    int spotlistmax_at_tcg = 0;
    elona_vector1<int> spotlist_at_tcg;
    int x2_at_tcg = 0;
    if (prm_1004 == 0)
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
    if (prm_1005 != -1)
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
            spotlist_at_tcg(p_at_tcg) = prm_1005;
        }
        else
        {
            spotlist_at_tcg(spotlistmax_at_tcg) = prm_1005;
        }
        ++spotlistmax_at_tcg;
    }
    x2_at_tcg = spotspace_at_tcg;
    x_at_tcg = basex_at_tcg + 466 - spotlistmax_at_tcg * x2_at_tcg / 2;
    for (int cnt = 0, cnt_end = (spotlistmax_at_tcg); cnt < cnt_end; ++cnt)
    {
        p_at_tcg = spotlist_at_tcg(cnt);
        card_at_tcg(4, p_at_tcg) = x_at_tcg + cnt * x2_at_tcg;
        card_at_tcg(5, p_at_tcg) = spotiy_at_tcg(prm_1004);
    }
    return;
}



void gravecard(int prm_1006)
{
    if (card_at_tcg(0, prm_1006) == 1)
    {
        for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
        {
            if (card_at_tcg(0, cnt) != 1)
            {
                continue;
            }
            if (card_at_tcg(1, cnt) != card_at_tcg(1, prm_1006))
            {
                continue;
            }
            if (card_at_tcg(2, cnt) > card_at_tcg(2, prm_1006))
            {
                card_at_tcg(4, cnt) -= spotspace_at_tcg;
            }
        }
    }
    card_at_tcg(0, prm_1006) = -2;
    ++cpdata_at_tcg(8, card_at_tcg(1, prm_1006));
    n_at_tcg = card_at_tcg(1, prm_1006);
    if (gravesum_at_tcg(n_at_tcg) > 2)
    {
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            gravelist_at_tcg(cnt, n_at_tcg) =
                gravelist_at_tcg(cnt + 1, n_at_tcg);
        }
        gravelist_at_tcg(2, n_at_tcg) = prm_1006;
    }
    else
    {
        gravelist_at_tcg(gravesum_at_tcg(n_at_tcg), n_at_tcg) = prm_1006;
        ++gravesum_at_tcg(n_at_tcg);
    }
    makecardlist();
    cardpos(card_at_tcg(1, prm_1006), -1);
    label_1823();
    return;
}



void dmgcard(int prm_1007, int prm_1008)
{
    if (prm_1008 > 0)
    {
        snd(2);
    }
    efllistadd(
        1, -prm_1008, card_at_tcg(2, prm_1007), card_at_tcg(3, prm_1007));
    card_at_tcg(12, prm_1007) -= prm_1008;
    if (card_at_tcg(12, prm_1007) < 0)
    {
        card_at_tcg(12, prm_1007) = 0;
    }
    if (card_at_tcg(12, prm_1007) <= 0)
    {
        card_at_tcg(6, prm_1007) = 2;
        card_at_tcg(7, prm_1007) = 18;
        tcgdraw();
        gravecard(prm_1007);
    }
    return;
}



void dmgplayer(int prm_1009, int prm_1010)
{
    if (prm_1010 > 0)
    {
        snd(2);
    }
    efllistadd(1, -prm_1010, cpx_at_tcg(prm_1009), cpy_at_tcg(prm_1009));
    cpdata_at_tcg(4, prm_1009) -= prm_1010;
    if (cpdata_at_tcg(4, prm_1009) < 0)
    {
        cpdata_at_tcg(4, prm_1009) = 0;
    }
    return;
}



void delbottomcard(int prm_1011)
{
    int delcard_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != prm_1011)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) == 2)
        {
            card_at_tcg(4, cnt) -= holderspace_at_tcg;
            if (card_at_tcg(4, cnt) < holderix_at_tcg(prm_1011))
            {
                card_at_tcg(6, cnt) = 2;
                card_at_tcg(7, cnt) = 18;
                delcard_at_tcg = cnt;
            }
        }
    }
    tcgdraw();
    gravecard(delcard_at_tcg);
    return;
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



int getholdersum(int prm_1012)
{
    p_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != prm_1012)
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



int getspotsum(int prm_1013)
{
    p_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != prm_1013)
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



int getdecksum(int prm_1014)
{
    p_at_tcg = 0;
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != prm_1014)
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



int cardcandeclareattack(int prm_1015)
{
    if (card_at_tcg(0, prm_1015) != 1)
    {
        return 0;
    }
    if (card_at_tcg(9, prm_1015) != 10)
    {
        return 0;
    }
    if (cdbit(0, prm_1015))
    {
        return 0;
    }
    return 1;
}



int cardcanblock(int prm_1016)
{
    if (card_at_tcg(0, prm_1016) != 1)
    {
        return 0;
    }
    if (card_at_tcg(9, prm_1016) != 10)
    {
        return 0;
    }
    if (cdbit(0, prm_1016))
    {
        if (card_at_tcg(14, prm_1016) != -4)
        {
            return 0;
        }
    }
    return 1;
}



int cardcanuseskill(int prm_1017)
{
    if (card_at_tcg(0, prm_1017) != 1)
    {
        return 0;
    }
    if (card_at_tcg(9, prm_1017) != 10)
    {
        return 0;
    }
    if (cdbit(0, prm_1017))
    {
        return 0;
    }
    if (card_at_tcg(20, prm_1017) == 0)
    {
        return 0;
    }
    if (card_at_tcg(20, prm_1017) > cpdata_at_tcg(5, card_at_tcg(1, prm_1017)))
    {
        return 0;
    }
    return 1;
}



void getrandomcard(int prm_1018)
{
    if (getdecksum(prm_1018) == 0)
    {
        cpdata_at_tcg(4, prm_1018) = 0;
        return;
    }
    p_at_tcg = getholdersum(prm_1018);

    while (1)
    {
        c_at_tcg = rnd(maxcard_at_tcg);
        if (card_at_tcg(0, c_at_tcg) == -1)
        {
            if (card_at_tcg(1, c_at_tcg) == prm_1018)
            {
                break;
            }
        }
    }

    card_at_tcg(0, c_at_tcg) = 2;
    card_at_tcg(1, c_at_tcg) = prm_1018;
    card_at_tcg(2, c_at_tcg) = deckix_at_tcg(prm_1018);
    card_at_tcg(3, c_at_tcg) = deckiy_at_tcg(prm_1018);
    card_at_tcg(4, c_at_tcg) =
        holderix_at_tcg(prm_1018) + p_at_tcg * holderspace_at_tcg;
    card_at_tcg(5, c_at_tcg) = holderiy_at_tcg(prm_1018);
    card_at_tcg(6, c_at_tcg) = 0;
    card_at_tcg(7, c_at_tcg) = 0;
    card_at_tcg(12, c_at_tcg) = card_at_tcg(16, c_at_tcg);
    --cpdata_at_tcg(7, prm_1018);
    if (prm_1018 == 0)
    {
        cdbitmod(1, c_at_tcg, 1);
    }
    else
    {
        cdbitmod(1, c_at_tcg, 0);
    }
    if (getholdersum(prm_1018) > 7)
    {
        delbottomcard(prm_1018);
    }
    makecardlist();
    return;
}



void saccard(int prm_1019, int prm_1020)
{
    snd(96);
    ++sac_at_tcg;
    if (prm_1020 == 0)
    {
        cardhelp(lang(u8"カードを捧げた。"s, u8"You sacrifice the card."s), 40);
    }
    else
    {
        cardhelp(
            lang(
                u8"相手はカードを捧げた。"s,
                u8"The opponent sacrifices the card."s),
            40);
    }
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != prm_1020)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) != 2)
        {
            continue;
        }
        if (card_at_tcg(2, cnt) <= card_at_tcg(2, prm_1019))
        {
            continue;
        }
        card_at_tcg(4, cnt) -= holderspace_at_tcg;
    }
    ++cpdata_at_tcg(6, prm_1020);
    ++cpdata_at_tcg(5, prm_1020);
    int stat = card_ref(500 + card_at_tcg(23, prm_1019) * 2 + rnd(2));
    create_card(prm_1019, stat);
    cdbitmod(1, prm_1019, 1);
    card_at_tcg(4, prm_1019) = landix_at_tcg(prm_1020)
        + landsum_at_tcg(prm_1020)
            * clamp(
                  (landspace_at_tcg - landsum_at_tcg(prm_1020) / 2),
                  4,
                  landspace_at_tcg);
    card_at_tcg(5, prm_1019) = landiy_at_tcg(prm_1020);
    landlist_at_tcg(landsum_at_tcg(prm_1020), prm_1020) = prm_1019;
    ++landsum_at_tcg(prm_1020);
    tcgdraw();
    makecardlist();
    card_at_tcg(0, prm_1019) = 4;
    makecardlist();
    label_1823();
    efllistadd(
        2,
        1,
        card_at_tcg(2, prm_1019),
        card_at_tcg(3, prm_1019),
        cpx_at_tcg(prm_1020),
        cpy_at_tcg(prm_1020));
    return;
}



void opencard(int prm_1021)
{
    snd(71);
    cdbitmod(1, prm_1021, 1);
    tcgdraw();
    return;
}



void label_1793()
{
    SDIM3(cdrefn_at_tcg, 50, 4);
    p_at_tcg = 0;
    cdrefn_at_tcg(p_at_tcg) = lang(
        u8"自分のデッキからカードを1枚選び受け取る。"s,
        u8"Player chooses and receives 1 card from his deck."s);
    p_at_tcg = 2;
    cdrefn_at_tcg(p_at_tcg) = lang(
        u8"プレイヤーはカードを2枚ドローする。"s, u8"Player draws 2 cards."s);
    p_at_tcg = 3;
    cdrefn_at_tcg(p_at_tcg) = lang(
        u8"場のクリーチャー1体を選択し、所有者の手札に戻す。"s,
        u8"Return target creature to its owner's hand."s);
    return;
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
                            if (cdbit(0, c_at_tcg) == 0
                                || card_at_tcg(14, c_at_tcg) == -4)
                            {
                                cs_at_tcg = cnt;
                                csline_at_tcg = cl_at_tcg;
                                break;
                            }
                        }
                        selectmode_at_tcg = 1;
                        label_1836();
                        selectmode_at_tcg = -1;
                    }
                    else
                    {
                        aiblock_at_tcg = 1;
                        label_18462();
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
            label_1802();
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
            label_1828();
            break;
        case 0:
            deckmode_at_tcg = 2;
            label_1828();
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



void label_1802()
{
    stack_at_tcg = 0;
    return;
}



int putcard(int prm_1024, int prm_1025)
{
    if (getspotsum(prm_1025) >= 8)
    {
        if (prm_1025 == player_at_tcg)
        {
            snd(27);
            cardhelp(
                lang(u8"これ以上は場に出せない。"s, u8"Your field is full."s),
                40);
        }
        return -1;
    }
    if (card_at_tcg(10, prm_1024) > cpdata_at_tcg(5, prm_1025))
    {
        if (prm_1025 == player_at_tcg)
        {
            snd(27);
            cardhelp(
                lang(u8"マナが足りない。"s, u8"You don't have enough mana."s),
                40);
        }
        return -3;
    }
    cpdata_at_tcg(5, prm_1025) -= card_at_tcg(10, prm_1024);
    if (prm_1025 == 0)
    {
        card_at_tcg(5, prm_1024) -= 25;
    }
    else
    {
        card_at_tcg(5, prm_1024) += 25;
    }
    tcgdraw();
    for (int cnt = 0, cnt_end = (maxcard_at_tcg); cnt < cnt_end; ++cnt)
    {
        if (card_at_tcg(1, cnt) != prm_1025)
        {
            continue;
        }
        if (card_at_tcg(0, cnt) != 2)
        {
            continue;
        }
        if (card_at_tcg(2, cnt) <= card_at_tcg(2, prm_1024))
        {
            continue;
        }
        card_at_tcg(4, cnt) -= holderspace_at_tcg;
    }
    if (card_at_tcg(9, prm_1024) == 30)
    {
        cdbitmod(1, prm_1024, 1);
        card_at_tcg(4, prm_1024) = landix_at_tcg(prm_1025)
            + landsum_at_tcg(prm_1025)
                * clamp(
                      (landspace_at_tcg - landsum_at_tcg(prm_1025) / 2),
                      4,
                      landspace_at_tcg);
        card_at_tcg(5, prm_1024) = landiy_at_tcg(prm_1025);
        landlist_at_tcg(landsum_at_tcg(prm_1025), prm_1025) = prm_1024;
        ++landsum_at_tcg(prm_1025);
        tcgdraw();
        makecardlist();
        card_at_tcg(0, prm_1024) = 4;
        makecardlist();
        label_1823();
        return 1;
    }
    p_at_tcg = getspotsum(prm_1025);
    card_at_tcg(0, prm_1024) = 1;
    cdbitmod(1, prm_1024, 0);
    card_at_tcg(22, prm_1024) = 0;
    card_at_tcg(14, prm_1024) = -4;
    cdbitmod(0, prm_1024, 1);
    cardpos(prm_1025, prm_1024);
    tcgdraw();
    makecardlist();
    opencard(prm_1024);
    return 1;
}



void tcgdrawbg()
{
    int w_at_tcg = 0;
    int h_at_tcg = 0;
    x_at_tcg = 960;
    y_at_tcg = 96;
    w_at_tcg = 128;
    h_at_tcg = 128;
    gmode(0);
    for (int cnt = 0, cnt_end = (windowh / h_at_tcg + 1); cnt < cnt_end; ++cnt)
    {
        cnt2_at_tcg = cnt;
        for (int cnt = 0, cnt_end = (windoww / w_at_tcg + 1); cnt < cnt_end;
             ++cnt)
        {
            pos(windoww - (cnt + 1) * w_at_tcg,
                windowh - (cnt2_at_tcg + 1) * h_at_tcg);
            gcopy(3, x_at_tcg, y_at_tcg, w_at_tcg, h_at_tcg);
        }
    }
    gmode(2);
    return;
}



void tcginit()
{
    elona_vector1<int> spotix_at_tcg;
    turn_at_tcg = 0;
    efllistmax_at_tcg = 10;
    cardmode_at_tcg = 0;
    label_1793();
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
    SDIM1(cardrefn);
    SDIM1(helpmsg_at_tcg);
    DIM2(deck, 1000);
    SDIM3(domname_at_tcg, 20, 10);
    phasen_at_tcg(0) = u8"Begin"s;
    phasen_at_tcg(1) = u8"Draw"s;
    phasen_at_tcg(2) = u8"Main"s;
    phasen_at_tcg(3) = u8"End"s;
    phasen_at_tcg(4) = "";
    domname_at_tcg(0) = lang(u8"ルルウィ"s, u8"Lulwy"s);
    domname_at_tcg(1) = lang(u8"クミロミ"s, u8"Kumiromi"s);
    domname_at_tcg(2) = lang(u8"ヤカテクト"s, u8"Yacatect"s);
    domname_at_tcg(3) = lang(u8"ジュア"s, u8"Jure"s);
    domname_at_tcg(4) = lang(u8"マニ"s, u8"etc"s);
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
    gsel(3);
    pos(960, 96);
    picload(filesystem::path(u8"./graphic/deco_card.bmp"), 1);
    gsel(7);
    picload(filesystem::path(u8"./graphic/interface2.bmp"));
    gsel(2);
    pos(0, 0);
    picload(filesystem::path(u8"./graphic/card0.bmp"), 1);
    gsel(4);
    pos(0, 0);
    picload(filesystem::path(u8"./graphic/bg_card.bmp"), 1);
    label_1826();
    tcgdrawbg();
    return;
}



int calcstartcard(int prm_1026)
{
    return 6 - (cpdata_at_tcg(9, prm_1026) > 2)
        - (cpdata_at_tcg(9, prm_1026) > 3) - (cpdata_at_tcg(9, prm_1026) > 4);
}



void calcstartattb(int prm_1027)
{
    cpdata_at_tcg(4, prm_1027) = 40 - cpdata_at_tcg(9, prm_1027) * 5;
    cpdata_at_tcg(6, prm_1027) = 0;
    return;
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
    return;
}



void calcdecksize()
{
    int cardsize_at_tcg = 0;
    gdata(830 + curdeck) = 0;
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
        gdata(830 + curdeck) += deck(card_at_tcg(18, cnt));
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
    return;
}



void tcgdeck()
{
    std::string file_at_tcg;
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
        s_at_tcg(0) = lang(u8"白"s, u8"White"s);
        s_at_tcg(1) = lang(u8"青"s, u8"Blue"s);
        s_at_tcg(2) = lang(u8"銀"s, u8"Silver"s);
        s_at_tcg(3) = lang(u8"赤"s, u8"Red"s);
        s_at_tcg(4) = lang(u8"黒"s, u8"Black"s);
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            s_at_tcg(cnt) += lang(u8"のデッキ"s, u8" Deck"s);
            file_at_tcg = filesystem::path(u8"./tmp/deck_"s).generic_string()
                + cnt + u8".s2"s;
            if (!fs::exists(file_at_tcg))
            {
                s_at_tcg(cnt) += lang(u8" (新規作成)"s, u8" (New)"s);
            }
            else
            {
                if (gdata(830 + cnt) != 30)
                {
                    s_at_tcg(cnt) +=
                        u8" (NG "s + gdata((830 + cnt)) + u8"/"s + 30 + u8")"s;
                }
                if (gdata(813) == cnt)
                {
                    s_at_tcg(cnt) += u8" [Use]"s;
                }
            }
            ELONA_APPEND_PROMPT(s_at_tcg(cnt), u8"null"s, ""s + promptmax);
        }
        rtval = show_prompt(basex_at_tcg + 400, basey_at_tcg + 230, 300);
        if (rtval == -1)
        {
            break;
        }
        DIM2(deck, 1000);
        curdeck = rtval;
        if (fs::exists(filesystem::path(u8"./tmp/deck_"s + curdeck + u8".s2")))
        {
            ELONA_APPEND_PROMPT(
                lang(u8"デッキの構築"s, u8"Edit Deck"s),
                u8"null"s,
                ""s + promptmax);
            ELONA_APPEND_PROMPT(
                lang(u8"メインデッキに設定"s, u8"Set as Main Deck"s),
                u8"null"s,
                ""s + promptmax);
            rtval = show_prompt(400, basey_at_tcg + 230, 240);
            if (rtval == -1)
            {
                continue;
            }
            if (rtval == 1)
            {
                gdata(813) = curdeck;
                continue;
            }
            if (rtval == 0)
            {
                ctrl_file(24);
            }
        }
        decksizebk_at_tcg = gdata(830 + curdeck);
        snd(95);
        calcdecksize();
        deckmode_at_tcg(0) = 0;
        deckmode_at_tcg(1) = rtval_at_tcg;
        label_1828();
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
            int stat = card_ref(rnd(1000));
            if (cardrefcost == 0)
            {
                --cnt;
                continue;
            }
            create_card(cc_at_tcg, stat);
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
        label_1816();
        if (gameover())
        {
            label_1815();
            return;
        }
        label_1817();
        if (gameover())
        {
            label_1815();
            return;
        }
        label_1818();
        if (gameover())
        {
            label_1815();
            return;
        }
        label_1819();
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



void label_1815()
{
    return;
}



void label_1816()
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
    return;
}



void label_1817()
{
    phase_at_tcg = 1;
    tcgdraw();
    await(50);
    getrandomcard(cp_at_tcg);
    tcgdraw();
    return;
}



void label_1818()
{
    phase_at_tcg = 2;
    tcgdraw();
    await(50);
    if (cp_at_tcg == player_at_tcg)
    {
        selectmode_at_tcg = 0;
        label_1836();
    }
    else
    {
        selectmode_at_tcg = -1;
        label_18462();
    }
    return;
}



void label_1819()
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
    return;
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
    return;
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
    return;
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
    return;
}



void label_1823()
{
    elona_vector1<int> mana_at_tcg;
    int m_at_tcg = 0;
    gsel(4);
    pos(0, 0);
    picload(filesystem::path(u8"./graphic/bg_card.bmp"), 1);
    gmode(2);
    font(14 - en * 2);
    color(255, 255, 255);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        gmode(0);
        cnt2_at_tcg = cnt;
        DIM2(mana_at_tcg, 10);
        for (int cnt = 0, cnt_end = (landsum_at_tcg(cnt2_at_tcg));
             cnt < cnt_end;
             ++cnt)
        {
            x_at_tcg = landix_at_tcg(cnt2_at_tcg)
                + cnt
                    * clamp(
                          (landspace_at_tcg - landsum_at_tcg(cnt2_at_tcg) / 2),
                          4,
                          landspace_at_tcg);
            y_at_tcg = landiy_at_tcg(cnt2_at_tcg);
            m_at_tcg = landlist_at_tcg(cnt, cnt2_at_tcg);
            n_at_tcg = std::abs(card_at_tcg(17, m_at_tcg));
            ++mana_at_tcg(card_at_tcg(23, m_at_tcg));
            pos(x_at_tcg, y_at_tcg);
            gcopy(2, n_at_tcg % 22 * 72, n_at_tcg / 22 * 96, 72, 96);
        }
        y_at_tcg = landiy_at_tcg(cnt2_at_tcg) + (cnt == 0) * 80;
        x_at_tcg = landix_at_tcg(cnt2_at_tcg) - 16;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            if (mana_at_tcg(cnt) == 0)
            {
                continue;
            }
            pos(x_at_tcg - 15, y_at_tcg - 2);
            gcopy(7, cnt * 12, 126, 12, 18);
            pos(x_at_tcg, y_at_tcg);
            mes(mana_at_tcg(cnt));
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
                pos(x_at_tcg, y_at_tcg);
                gcopy(7, 72 + card_at_tcg(19, m_at_tcg) * 72, 0, 72, 96);
                n_at_tcg = card_at_tcg(17, m_at_tcg) % 1000;
                chara_preparepic(n_at_tcg, card_at_tcg(17, m_at_tcg) / 1000);
                gsel(4);
                pos(x_at_tcg + 13,
                    y_at_tcg + 32 - chipc(4, n_at_tcg)
                        + chipc(3, n_at_tcg) / 6);
                gcopy(5, 0, 960, chipc(2, n_at_tcg), chipc(3, n_at_tcg));
            }
            else
            {
                gmode(0);
                n_at_tcg = std::abs(card_at_tcg(17, m_at_tcg));
                pos(x_at_tcg, y_at_tcg);
                gcopy(2, n_at_tcg % 22 * 72, n_at_tcg / 22 * 96, 72, 96);
            }
        }
    }
    color(0, 0, 0);
    gsel(0);
    return;
}



void label_1824()
{
    font(12 + en - en * 2);
    gmode(2);
    for (int cnt = 0, cnt_end = (cfmax_at_tcg); cnt < cnt_end; ++cnt)
    {
        x_at_tcg = basex_at_tcg + 180 + cnt * 80;
        y_at_tcg = basey_at_tcg + 26 + (ccf_at_tcg == cnt) * 3;
        p_at_tcg = cflist_at_tcg(cnt);
        color(0, 0, 0);
        if (ccf_at_tcg == cnt)
        {
            gmode(4, -1, -1, 255);
            color(255, 255, 255);
        }
        else
        {
            gmode(4, -1, -1, 120);
            color(200, 200, 200);
        }
        pos(x_at_tcg, y_at_tcg);
        gcopy(7, 360, 96, 79, 20);
        gmode(2);
        pos(x_at_tcg + 10, y_at_tcg + 4);
        mes(cfname_at_tcg(p_at_tcg));
        color(0, 0, 0);
        if (ccf_at_tcg == cnt)
        {
            pos(x_at_tcg + 65, y_at_tcg - 5);
            gcopy(7, 288, 96, 24, 24);
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
            pos(x_at_tcg + 1, y_at_tcg + 111);
            mes(s_at_tcg);
            if (deck(i_at_tcg) != 0)
            {
                color(150, 255, 150);
            }
            else
            {
                color(200, 200, 200);
            }
            pos(x_at_tcg, y_at_tcg + 110);
            mes(s_at_tcg);
            color(0, 0, 0);
        }
        card_at_tcg(2, c_at_tcg) = x_at_tcg;
        card_at_tcg(3, c_at_tcg) = y_at_tcg;
        tcgdrawcard(c_at_tcg, 1);
    }
    font(13 - en * 2);
    color(255, 255, 255);
    pos(basex_at_tcg + 160, basey_at_tcg + 510);
    mes(lang(
        ""s + key_next + u8","s + key_prev
            + u8",Tab [フィルター切替]  決定ｷｰ [カード選択]  ｷｬﾝｾﾙｷｰ [終了]"s,
        ""s + key_next + u8","s + key_prev
            + u8" [Change Filter]  Enter [Select]  Cancel [Exit]"s));
    pos(basex_at_tcg + 700, basey_at_tcg + 510);
    mes(u8"Page "s + dsc_at_tcg / 8 / 3 + u8"/"s
        + (dlistmax_at_tcg - 1) / 8 / 3);
    color(0, 0, 0);
    return;
}



void label_1825()
{
    gmode(0);
    pos(basex_at_tcg, basey_at_tcg);
    gcopy(4, 0, 0, basew_at_tcg, baseh_at_tcg);
    font(13 - en * 2);
    gmode(2);
    pos(basex_at_tcg + 20, basey_at_tcg + 22);
    if (cardmode_at_tcg != 0 || ct_at_tcg == player_at_tcg)
    {
        gcopy(7, 360, 120, 88, 84);
    }
    else
    {
        gcopy(7, 456, 120, 88, 84);
    }
    if (cardmode_at_tcg == 0)
    {
        pos(basex_at_tcg + 39, basey_at_tcg + 58);
        mes(u8"Turn "s + turn_at_tcg);
        color(255, 255, 255);
        pos(basex_at_tcg + 38, basey_at_tcg + 57);
        mes(u8"Turn "s + turn_at_tcg);
        color(0, 0, 0);
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            x_at_tcg = cpx_at_tcg(cnt);
            y_at_tcg = cpy_at_tcg(cnt);
            pos(x_at_tcg, y_at_tcg);
            gcopy(7, 264, 144, 72, 120);
            s_at_tcg = ""s + cpdata_at_tcg(4, cnt);
            pos(x_at_tcg + 36 - strlen_u(s_at_tcg) * 3, y_at_tcg + 9 - en);
            mes(s_at_tcg);
            if (cnt != player_at_tcg)
            {
                s_at_tcg = u8"?/"s + cpdata_at_tcg(6, cnt);
            }
            else
            {
                s_at_tcg = ""s + cpdata_at_tcg(5, cnt) + u8"/"s
                    + cpdata_at_tcg(6, cnt);
            }
            pos(x_at_tcg + 36 - strlen_u(s_at_tcg) * 3, y_at_tcg + 95 - en);
            mes(s_at_tcg);
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (cnt - 1 == phase_at_tcg)
            {
                pos(basex_at_tcg + 4, basey_at_tcg + 370 + cnt * 20);
                gcopy(7, 360, 216, 106, 18);
            }
            pos(basex_at_tcg + 36, basey_at_tcg + 373 + cnt * 20);
            if (cnt == 0)
            {
                if (ct_at_tcg == player_at_tcg)
                {
                    color(150, 150, 255);
                    mes(u8"Player"s);
                    color(0, 0, 0);
                }
                else
                {
                    color(255, 150, 150);
                    mes(u8"Opponent"s);
                    color(0, 0, 0);
                }
            }
            else
            {
                color(215, 215, 215);
                mes(phasen_at_tcg(cnt - 1));
                color(0, 0, 0);
            }
        }
    }
    else
    {
        pos(basex_at_tcg + 41, basey_at_tcg + 53);
        mes(u8"Deck\n Editor"s);
        color(255, 255, 255);
        pos(basex_at_tcg + 40, basey_at_tcg + 52);
        mes(u8"Deck\n Editor"s);
        color(0, 0, 0);
        if (gdata(830 + curdeck) != 30)
        {
            color(255, 100, 100);
        }
        else
        {
            color(100, 255, 100);
        }
        pos(basex_at_tcg + 24, basey_at_tcg + 120);
        mes(u8"Deck "s + gdata((830 + curdeck)) + u8"/"s + 30);
        color(0, 0, 0);
        color(215, 215, 215);
        pos(basex_at_tcg + 24, basey_at_tcg + 140);
        mes(u8"Life "s + cpdata_at_tcg(4, 0));
        pos(basex_at_tcg + 24, basey_at_tcg + 160);
        mes(u8"Mana "s + cpdata_at_tcg(6, 0));
        pos(basex_at_tcg + 24, basey_at_tcg + 180);
        mes(u8"Card "s + calcstartcard(0));
        pos(basex_at_tcg + 24, basey_at_tcg + 220);
        mes(u8"Domain * "s + cpdata_at_tcg(9, 0));
        color(0, 0, 0);
        s_at_tcg = "";
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (domain_at_tcg(cnt))
            {
                s_at_tcg += ""s + domname_at_tcg(cnt) + u8"\n"s;
            }
        }
        pos(basex_at_tcg + 24, basey_at_tcg + 240);
        mes(s_at_tcg);
    }
    font(12 + en - en * 2);
    pos(basex_at_tcg + 146, basey_at_tcg + 545);
    mes(helpmsg_at_tcg);
    return;
}



void label_1826()
{
    gmode(4, -1, -1, 180);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        cnt2_at_tcg = cnt;
    }
    gsel(0);
    return;
}



void label_1827()
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
    return;
}



void label_1828()
{
    gsel(4);
    pos(0, 0);
    picload(filesystem::path(u8"./graphic/bg_card.bmp"), 1);
    gsel(0);
    DIM3(dlist_at_tcg, 2, 400);
    DIM2(cflist_at_tcg, 10);
    SDIM3(cfname_at_tcg, 16, 10);
    cfname_at_tcg(0) = lang(u8"候補"s, u8"List"s);
    cfname_at_tcg(1) = lang(u8"デッキ"s, u8"Deck"s);
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
label_1829_internal:
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
                if (card_at_tcg(23, cnt) != cflist_at_tcg(ccf_at_tcg) - 2)
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
            for (int cnt = 0, cnt_end = (dlistmax_at_tcg); cnt < cnt_end; ++cnt)
            {
                c_at_tcg = dlist_at_tcg(0, cnt);
                if (card_at_tcg(18, c_at_tcg) == card_at_tcg(18, cnt2_at_tcg))
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
        for (int cnt = 0, cnt_end = (dlistmax_at_tcg - 1); cnt < cnt_end; ++cnt)
        {
            p_at_tcg(0) = card_at_tcg(10, dlist_at_tcg(0, cnt)) * 10000
                + card_at_tcg(18, dlist_at_tcg(0, cnt));
            p_at_tcg(1) = card_at_tcg(10, dlist_at_tcg(0, (cnt + 1))) * 10000
                + card_at_tcg(18, dlist_at_tcg(0, (cnt + 1)));
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
    label_1827();
label_1830_internal:
    label_1825();
    label_1824();
    redraw();
    await(30);
    key_check();
    if (key == key_next)
    {
        ++ccf_at_tcg;
        snd(5);
        if (ccf_at_tcg >= cfmax_at_tcg)
        {
            ccf_at_tcg = 0;
        }
        goto label_1829_internal;
    }
    if (key == key_prev)
    {
        --ccf_at_tcg;
        snd(5);
        if (ccf_at_tcg < 0)
        {
            ccf_at_tcg = cfmax_at_tcg - 1;
        }
        goto label_1829_internal;
    }
    if (key == key_west)
    {
        --dsc_at_tcg;
        snd(5);
    }
    if (key == key_east)
    {
        ++dsc_at_tcg;
        snd(5);
    }
    if (key == key_south)
    {
        dsc_at_tcg += 8;
        snd(5);
    }
    if (key == key_north)
    {
        dsc_at_tcg -= 8;
        snd(5);
    }
    label_1827();
    if (key == key_enter)
    {
        if (dlistmax_at_tcg == 0)
        {
            goto label_1830_internal;
        }
        if (deckmode_at_tcg == 0)
        {
            if (card_at_tcg(9, dlist_at_tcg(0, dsc_at_tcg)) == 10)
            {
                if (card_at_tcg(10, dlist_at_tcg(0, dsc_at_tcg)) == 0)
                {
                    snd(27);
                    cardhelp(
                        lang(
                            u8"未実装のカード"s,
                            u8"The card isn't available in this version."s),
                        40);
                    goto label_1830_internal;
                }
            }
        label_1831_internal:
            calcdecksize();
            label_1825();
            label_1824();
            act_at_tcg(0) = 0;
            act_at_tcg(1) = 0;
            act_at_tcg(2) = 0;
            cc_at_tcg = dlist_at_tcg(0, dsc_at_tcg);
            if (deck(card_at_tcg(18, cc_at_tcg))
                < card(0, card_at_tcg(18, cc_at_tcg)))
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
                    snd(27);
                    goto label_1833_internal;
                }
            }
            label_1840();
            if (f_at_tcg == 0)
            {
                if (act_at_tcg(0))
                {
                    ++deck(card_at_tcg(18, cc_at_tcg));
                    snd(71);
                    goto label_1831_internal;
                }
            }
            if (f_at_tcg == 1)
            {
                if (act_at_tcg(1))
                {
                    --deck(card_at_tcg(18, cc_at_tcg));
                    snd(71);
                    goto label_1831_internal;
                }
            }
            goto label_1833_internal;
            goto label_1831_internal;
        label_1833_internal:
            calcdecksize();
            goto label_1830_internal;
        }
        rtval_at_tcg = dlist_at_tcg(0, dsc_at_tcg);
        rtval_at_tcg = 1;
        label_1835();
        return;
    }
    if (key == key_cancel)
    {
        if (deckmode_at_tcg == 0)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"セーブして終了"s, u8"Save & Exit"s),
                u8"null"s,
                ""s + promptmax);
            ELONA_APPEND_PROMPT(
                lang(u8"セーブしないで終了"s, u8"Just Exit"s),
                u8"null"s,
                ""s + promptmax);
            rtval = show_prompt(basex_at_tcg + 420, basey_at_tcg + 230, 240);
            if (rtval == 0)
            {
                ctrl_file(
                    23, filesystem::path(u8"./tmp/deck_"s + curdeck + u8".s2"));
            }
            else
            {
                gdata(830 + curdeck) = decksizebk_at_tcg;
            }
            if (rtval == -1)
            {
                goto label_1830_internal;
            }
        }
        rtval_at_tcg = 0;
        label_1835();
        return;
    }
    goto label_1830_internal;
}



int label_1835()
{
    gsel(4);
    pos(0, 0);
    picload(filesystem::path(u8"./graphic/bg_card.bmp"), 1);
    label_1826();
    return rtval_at_tcg;
}



void label_1836()
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
        stick(a_at_tcg);
        key_check();
        if (key == key_east)
        {
            ++cs_at_tcg;
            snd(5);
            if (cs_at_tcg == 0)
            {
                if (clistmax_at_tcg(csline_at_tcg) == 0)
                {
                    cslineup();
                }
            }
            csfix();
        }
        if (key == key_west)
        {
            --cs_at_tcg;
            snd(5);
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
        if (key == key_north)
        {
            cslineup();
            snd(5);
            csfix();
        }
        if (key == key_south)
        {
            cslinedown();
            snd(5);
            csfix();
        }
        if (key == key_enter)
        {
            if (cs_at_tcg == -1)
            {
                label_1839();
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
                    if (card_at_tcg(9, cc_at_tcg) == 20
                        || selectmode_at_tcg == 0)
                    {
                        act_at_tcg(0) = 1;
                        s_at_tcg += lang(
                            u8"↑   カードを出す。\n"s,
                            u8"UP: Put the card.\n"s);
                    }
                }
                if (sac_at_tcg == 0)
                {
                    if (selectmode_at_tcg == 0)
                    {
                        act_at_tcg(1) = 1;
                        s_at_tcg += lang(
                            u8"↓   カードを捧げてマナを得る(1ターンに1回)。\n"s,
                            u8"Down: Sacrifice the card.\n"s);
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
                            s_at_tcg += lang(
                                u8"↑   攻撃を宣言する。\n"s,
                                u8"UP: Declare an attack.\n"s);
                        }
                    }
                }
                if (selectmode_at_tcg == 1)
                {
                    if (cardcanblock(cc_at_tcg))
                    {
                        act_at_tcg(0) = 1;
                        s_at_tcg +=
                            lang(u8"↑   ブロックする。\n"s, u8"UP: Block.\n"s);
                    }
                }
                if (cardcanuseskill(cc_at_tcg))
                {
                    act_at_tcg(2) = 1;
                    s_at_tcg += lang(
                        u8"決定 スキルを使用する。\n"s,
                        u8"ENTER: Use the skill.\n"s);
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
                snd(27);
                cardhelp(
                    lang(
                        u8"可能な行動はない。"s,
                        u8"There is no action available."s),
                    40);
                continue;
            }
            snd(40);
            cardhelp(s_at_tcg, 10);
            tcgdraw();
            label_1840();
            cc_at_tcg = clist_at_tcg(cs_at_tcg, csline_at_tcg);
            key = "";
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
                        label_1839();
                        return;
                    }
                    cardstack_at_tcg(0, stack_at_tcg) = cc_at_tcg;
                    cardstack_at_tcg(1, stack_at_tcg) = -1;
                    cardstack_at_tcg(2, stack_at_tcg) = cp_at_tcg;
                    ++stack_at_tcg;
                    actionproc();
                    if (gameover())
                    {
                        label_1839();
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
                        label_1839();
                        return;
                    }
                    actionproc();
                    if (gameover())
                    {
                        label_1839();
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
                    label_1839();
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
                        label_1839();
                        return;
                    }
                    actionproc();
                }
                if (gameover())
                {
                    label_1839();
                    return;
                }
            }
            if (cs_at_tcg >= clistmax_at_tcg(csline_at_tcg))
            {
                cs_at_tcg = clistmax_at_tcg(csline_at_tcg) - 1;
            }
            csfix();
        }
        if (key == key_cancel || key_escape)
        {
            label_1839();
            return;
        }
        if (key == u8"s"s)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"降参する"s, u8"Surrender"s),
                u8"null"s,
                ""s + promptmax);
            rtval = show_prompt(basex_at_tcg + 420, basey_at_tcg + 230, 200);
            if (rtval == 0)
            {
                cpdata_at_tcg(4, 0) = 0;
                cursor_at_tcg = 0;
                return;
            }
        }
    }
}



void label_1839()
{
    cursor_at_tcg = 0;
    return;
}



void label_1840()
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
            pos(cnt * 48, 264);
            gcopy(0, x_at_tcg(cnt), y_at_tcg(cnt), 36, 36);
            gsel(0);
            if (act_at_tcg(cnt) == 0)
            {
                continue;
            }
            gmode(4, 0, 0, clamp(p_at_tcg * 30 + 20, 0, 255));
            pos(x_at_tcg(cnt), y_at_tcg(cnt));
            gcopy(7, 192, 96, 36, 36);
            gmode(4, 0, 0, 50 + i_at_tcg * 2);
            pos(x_at_tcg(cnt) + 13, y_at_tcg(cnt) + 11);
            gcopy(7, 336 + (cnt == 2) * 12, 96 + cnt % 2 * 24, 12, 12);
        }
        redraw();
        gmode(0);
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            if (act_at_tcg(cnt) == 0)
            {
                continue;
            }
            pos(x_at_tcg(cnt), y_at_tcg(cnt));
            gcopy(7, cnt * 48, 264, 36, 36);
        }
        await(15);
        key_check();
        if (key == key_north)
        {
            f_at_tcg = 0;
            label_1842();
            return;
        }
        if (key == key_south)
        {
            f_at_tcg = 1;
            label_1842();
            return;
        }
        if (key == key_enter)
        {
            f_at_tcg = 2;
            label_1842();
            return;
        }
        if (key != ""s)
        {
            f_at_tcg = -1;
            label_1842();
            return;
        }
    }
}



void label_1842()
{
    return;
}



void label_1844()
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
    return;
}



int label_1845()
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



void label_18462()
{
    int ec_at_tcg = 0;

    bool init = true;
    while (1)
    {
        if (init)
        {
            spellused_at_tcg = 0;
            stick(a_at_tcg);
            if (a_at_tcg)
            {
                cpdata_at_tcg(4, 0) = 0;
            }
            label_1844();
            ec_at_tcg = 0;
            init = false;
        }
        if (gameover())
        {
            label_1848();
            return;
        }
        if (ec_at_tcg >= emax_at_tcg)
        {
            label_1848();
            return;
        }
        if (elist_at_tcg(0, ec_at_tcg) <= 0)
        {
            label_1848();
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
                    label_1848();
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
                        label_1848();
                        return;
                    }
                    actionproc();
                }
                init = true;
                break;
            }
            else
            {
                int stat = label_1845();
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
            label_1848();
            return;
        }
        ++ec_at_tcg;
    }
}



void label_1848()
{
    if (aiblock_at_tcg == 0)
    {
        if (sac_at_tcg == 0)
        {
            int stat = label_1845();
            if (stat == 1)
            {
                label_18462();
                return;
            }
        }
    }
    if (gameover())
    {
        return;
    }
    return;
}



} // namespace elona
