#include "character.hpp"
#include "elona.hpp"
#include "map.hpp"
#include "variables.hpp"



namespace elona
{


int msglen = 0;
int tcontinue_at_txtfunc = 0;
int tcolfix_at_txtfunc = 0;
int p_at_txtfunc = 0;


void key_check(int prm_299)
{
    int key_ctrl = 0;
    int p_at_m19 = 0;
    int a_at_m19 = 0;
    int f_at_m19 = 0;
    int j_at_m19 = 0;
    int prevjoy_at_m19 = 0;
    int b_at_m19 = 0;
    std::string keyactive_at_m19;
    int scon_at_m19 = 0;
    if (ginfo(2) == 0)
    {
        objsel(0);
    }
    else
    {
        key = "";
        objprm(0, ""s);
        keylog = "";
        await(100);
        return;
    }
    if (msgalert == 1)
    {
        if (cfg_alert > 1)
        {
            for (int i = 0; i < cfg_alert; ++i)
            {
                await(10);
                bool any_key_pressed = false;

                if (getkey(snail::key::space) || getkey(snail::key::enter))
                {
                    any_key_pressed = true;
                }
                else
                {
                    for (int i = 0; i < 26; ++i)
                    {
                        if (getkey(snail::key(int(snail::key::key_a) + i)))
                        {
                            any_key_pressed = true;
                            break;
                        }
                    }
                    for (int i = 0; i < 10; ++i)
                    {
                        if (getkey(snail::key(int(snail::key::key_0) + i)))
                        {
                            any_key_pressed = true;
                            break;
                        }
                    }
                }
                if (!any_key_pressed)
                {
                    break;
                }
            }
            msgalert = 0;
            keylog = "";
            objprm(0, ""s);
        }
    }
    key = "";
    if (keylog != ""s)
    {
        keylog = strmid(keylog, 0, 1);
        if (keylog(0)[0] == '\n')
        {
            keylog = key_enter;
        }
        key = keylog;
        keylog = "";
        objprm(0, ""s);
    }
    mousel = 0;
    f_at_m19 = 0;
    key_tab = 0;
    key_escape = 0;
    stick(p_at_m19, 15);
    if (p_at_m19 != 0)
    {
        if (p_at_m19 == 128)
        {
            if (keywait == 0)
            {
                key = key_cancel;
                key_escape = 1;
            }
        }
        if (p_at_m19 == 1024)
        {
            key_tab = 1;
            key = key_next;
        }
    }
    else
    {
        if (getkey(snail::key::home))
        {
            p_at_m19 = 3;
        }
        if (getkey(snail::key::pageup))
        {
            p_at_m19 = 6;
        }
        if (getkey(snail::key::end))
        {
            p_at_m19 = 9;
        }
        if (getkey(snail::key::pagedown))
        {
            p_at_m19 = 12;
        }
    }
    if (getkey(snail::key::ctrl))
    {
        key_ctrl = 1;
    }
    else
    {
        key_ctrl = 0;
    }
    if (getkey(snail::key::alt))
    {
        key_alt = 1;
    }
    else
    {
        key_alt = 0;
    }
    if (getkey(snail::key::shift))
    {
        keybd_wait = 100000;
        key_shift = 1;
        if (keywait == 0)
        {
            key = key_cancel;
            keywait = 1;
        }
    }
    else
    {
        keywait = 0;
        key_shift = 0;
    }
    if (cfg_joypad)
    {
        j_at_m19 = 0;
        DIGETJOYSTATE(j_at_m19, 0);
        if (HMMBITCHECK(j_at_m19, 0))
        {
            p_at_m19 += 2;
        }
        if (HMMBITCHECK(j_at_m19, 1))
        {
            p_at_m19 += 8;
        }
        if (HMMBITCHECK(j_at_m19, 2))
        {
            p_at_m19 += 1;
        }
        if (HMMBITCHECK(j_at_m19, 3))
        {
            p_at_m19 += 4;
        }
        a_at_m19 = 0;
        for (int cnt = 0; cnt < 12; ++cnt)
        {
            if (HMMBITCHECK(j_at_m19, 4 + cnt))
            {
                a_at_m19 = 1;
                if (jkey(cnt) == key_alter)
                {
                    key_alt = 1;
                }
                if (jkey(cnt) == key_cancel)
                {
                    key_shift = 1;
                    if (p_at_m19 != 0)
                    {
                        keybd_wait = 100000;
                    }
                }
                if (prevjoy_at_m19 != cnt)
                {
                    key = jkey(cnt);
                    prevjoy_at_m19 = cnt;
                    if (key == key_esc)
                    {
                        key = key_cancel;
                        key_escape = 1;
                    }
                    if (prm_299 == 0)
                    {
                        b_at_m19 = 0;
                        if (key == key_fire)
                        {
                            key = key_northeast;
                            b_at_m19 = 1;
                        }
                        if (key == key_target)
                        {
                            key = key_northwest;
                            b_at_m19 = 1;
                        }
                        if (key == key_get)
                        {
                            key = key_northeast;
                            b_at_m19 = 1;
                        }
                        if (key == key_alter)
                        {
                            key = key_northwest;
                            b_at_m19 = 1;
                        }
                        if (b_at_m19 == 0 && key != key_enter
                            && key != key_cancel && key != key_esc)
                        {
                            key = key_identify;
                        }
                    }
                }
            }
        }
        if (a_at_m19 == 0)
        {
            prevjoy_at_m19 = -1;
        }
        else if (prm_299 == 2)
        {
            return;
        }
    }
    if (quickkeywait)
    {
        if (p_at_m19 != 0)
        {
            return;
        }
        else
        {
            quickkeywait = 0;
        }
    }
    if (keybd_wait >= 100000)
    {
        if (key_shift == 0)
        {
            keybd_wait = 1000;
        }
    }
    if (p_at_m19 == 1)
    {
        if (key_alt == 0)
        {
            key = key_west;
            f_at_m19 = 1;
        }
    }
    if (p_at_m19 == 2)
    {
        if (key_alt == 0)
        {
            key = key_north;
            f_at_m19 = 1;
        }
    }
    if (p_at_m19 == 4)
    {
        if (key_alt == 0)
        {
            key = key_east;
            f_at_m19 = 1;
        }
    }
    if (p_at_m19 == 8)
    {
        if (key_alt == 0)
        {
            key = key_south;
            f_at_m19 = 1;
        }
    }
    if (p_at_m19 == 3)
    {
        key = key_northwest;
        f_at_m19 = 1;
    }
    if (p_at_m19 == 6)
    {
        key = key_northeast;
        f_at_m19 = 1;
    }
    if (p_at_m19 == 9)
    {
        key = key_southwest;
        f_at_m19 = 1;
    }
    if (p_at_m19 == 12)
    {
        key = key_southeast;
        f_at_m19 = 1;
    }
    if (prm_299 == 2)
    {
        return;
    }
    if (f_at_m19)
    {
        if (keyactive_at_m19 != key)
        {
            keyactive_at_m19 = key;
        }
        if (keybd_wait == 0)
        {
            keyactive_at_m19 = key;
        }
        if (prm_299 == 1)
        {
            if (keybd_attacking != 0)
            {
                if (keybd_wait % cfg_attackwait != 0)
                {
                    key = ""s;
                }
            }
            else if (cfg_scroll == 0)
            {
                if (keybd_wait < cfg_walkwait * cfg_startrun)
                {
                    if (keybd_wait % cfg_walkwait != 0)
                    {
                        key = "";
                    }
                }
                else
                {
                    running = 1;
                    if (keybd_wait < 100000)
                    {
                        if (keybd_wait % cfg_runwait != 0)
                        {
                            key = ""s;
                        }
                    }
                }
            }
            else if (p_at_m19 == 0)
            {
                if (keybd_wait < 10)
                {
                    if (keybd_wait != 0)
                    {
                        key = ""s;
                    }
                }
            }
            else if (keybd_wait > cfg_startrun)
            {
                if (cfg_runscroll == 0)
                {
                    if (keybd_wait % cfg_runwait != 0)
                    {
                        key = "";
                    }
                }
                running = 1;
            }
        }
        else if (keybd_wait < 14)
        {
            if (keybd_wait != 0 && keybd_wait != 7)
            {
                key = "";
            }
        }
        else if (keybd_wait < 1000)
        {
            if (keybd_wait % 2 != 1)
            {
                key = ""s;
            }
        }
        ++keybd_wait;
    }
    else
    {
        keybd_wait = 0;
        keybd_attacking = 0;
        running = 0;
        keyactive_at_m19 = "";
    }
    for (int i = 0; i < 10; ++i)
    {
        if (getkey(snail::key(int(snail::key::key_0) + i)))
        {
            key = u8"sc";
            sc = i;
            if (key_shift == 1 || key_ctrl == 1)
            {
                sc += 10;
            }
            keybd_event(i, 0, 2);
            scon_at_m19 = 1;
        }
    }
    if (scon_at_m19)
    {
        key = u8"sc"s;
        scon_at_m19 = 0;
        keylog = "";
        objprm(0, ""s);
        return;
    }
    if (keyhalt != 0)
    {
        if (key != ""s || keybd_wait != 0)
        {
            key = "";
        }
        else
        {
            keyhalt = 0;
        }
    }
    return;
}



void keyrelease()
{
    while (1)
    {
        await(30);
        int result{};
        stick(result, 768);
        if (result == 0)
        {
            key_check();
            if (key == ""s)
            {
                break;
            }
        }
    }
}



void press(bool only_enter_of_cancel)
{
    while (1)
    {
        await(20);
        key_check();
        if (only_enter_of_cancel)
        {
            if (key == key_enter || key == key_cancel)
            {
                break;
            }
        }
        else
        {
            if (key != ""s)
            {
                break;
            }
        }
    }
    keyhalt = 1;
}



void bmes(const std::string& prm_301, int prm_302, int prm_303, int prm_304)
{
    int pos_x_at_m21 = 0;
    int pos_y_at_m21 = 0;
    elona_vector1<int> mes_color_at_m21;
    int mes_y_at_m21 = 0;
    pos_x_at_m21 = ginfo(22);
    pos_y_at_m21 = ginfo(23);
    mes_color_at_m21(0) = prm_302;
    mes_color_at_m21(1) = prm_303;
    mes_color_at_m21(2) = prm_304;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        mes_y_at_m21 = cnt + pos_y_at_m21 - 1;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            pos(pos_x_at_m21 - 1 + cnt, mes_y_at_m21);
            mes(prm_301);
        }
    }
    color(mes_color_at_m21(0), mes_color_at_m21(1), mes_color_at_m21(2));
    pos(pos_x_at_m21, pos_y_at_m21);
    mes(prm_301);
    color(0, 0, 0);
    return;
}



void msg_write(std::string& prm_307)
{
    int msglen_ = jp ? msglen / 1.5 : msglen;
    int mp_at_txtfunc = 0;
    int mark_at_txtfunc = 0;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        mp_at_txtfunc = instr(prm_307, 0, u8"♪"s);
        if (mp_at_txtfunc != -1)
        {
            mark_at_txtfunc =
                elona::stoi(strmid(prm_307, mp_at_txtfunc + 2, 1));
            if (jp)
            {
                if (mark_at_txtfunc == 0)
                {
                    break;
                }
            }
            prm_307 = strmid(prm_307, 0, mp_at_txtfunc) + u8"  "s
                + strmid(prm_307,
                         (mp_at_txtfunc + 2 + (mark_at_txtfunc != 0)),
                         9999);
            pos((msglen_ + mp_at_txtfunc) * inf_mesfont / 2 + inf_msgx + 7
                    + en * 3,
                (inf_msgline - 1) * inf_msgspace + inf_msgy + 5);
            gmode(2);
            gcopy(3, 600 + mark_at_txtfunc * 24, 360, 16, 16);
            --cnt;
            continue;
        }
    }
    color(tcol_at_txtfunc(0), tcol_at_txtfunc(1), tcol_at_txtfunc(2));
    pos(msglen_ * inf_mesfont / 2 + inf_msgx + 6,
        (inf_msgline - 1) * inf_msgspace + inf_msgy + 6);
    font(lang(cfg_font1, cfg_font2), inf_mesfont - en * 2, 0);
    mes(prm_307);
    color(0, 0, 0);
    return;
}



void txtmore()
{
    return;
}



void txtcontinue()
{
    tcontinue_at_txtfunc = 1;
    return;
}



void anime_halt()
{
    key = "";
    objprm(0, ""s);
    keylog = "";
    redraw(0);
    gmode(0);
    gsel(3);
    pos(672, 504);
    gcopy(0, x_at_txtfunc, y_at_txtfunc, 120, 24);
    gsel(0);
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        redraw(0);
        await(10);
        pos(x_at_txtfunc, y_at_txtfunc + 12 - cnt);
        gzoom(120, cnt * 2 + 1, 3, 552, 504, 120, 22);
        redraw(1);
    }
    press(true);
    snd(20);
    for (int cnt = 0; cnt < 7; ++cnt)
    {
        redraw(0);
        await(10);
        pos(x_at_txtfunc, y_at_txtfunc);
        gcopy(3, 672, 504, 120, 24);
        if (cnt != 6)
        {
            pos(x_at_txtfunc, y_at_txtfunc + cnt * 2);
            gzoom(120, 22 - cnt * 4, 3, 552, 504, 120, 22);
        }
        redraw(1);
    }
    redraw(0);
    gmode(2);
    return;
}



void msg_halt()
{
    x_at_txtfunc = windoww - 120;
    y_at_txtfunc = windowh - 22;
    anime_halt();
    screenupdate = -1;
    update_screen();
    return;
}



void help_halt()
{
    x_at_txtfunc = wx + dx - 140;
    y_at_txtfunc = wy + dy - 1;
    anime_halt();
    return;
}



void txtef(int prm_308)
{
    tcol_at_txtfunc(0) = 255 - c_col(0, prm_308);
    tcol_at_txtfunc(1) = 255 - c_col(1, prm_308);
    tcol_at_txtfunc(2) = 255 - c_col(2, prm_308);
    if (prm_308 == 5)
    {
        tcolfix_at_txtfunc = 1;
    }
    else
    {
        tcolfix_at_txtfunc = 0;
    }
    return;
}



void msg_newlog()
{
    gsel(8);
    gmode(0);
    pos(0, msgline % inf_maxlog * inf_msgspace);
    gcopy(
        0,
        inf_msgx,
        inf_msgy + 5 + inf_msgspace * 3 + en * 3,
        windoww - inf_msgx,
        inf_msgspace);
    gsel(0);
    return;
}



void msg_newline()
{
    msg_newlog();
    msglen = 0;
    ++msgline;
    if (msgline >= inf_maxlog)
    {
        msgline -= inf_maxlog;
    }
    msg(msgline % inf_maxlog) = "";
    p_at_txtfunc = (windoww - inf_msgx) / 192;
    redraw(0);
    gmode(0);
    pos(inf_msgx, inf_msgy + 5);
    gcopy(
        0,
        inf_msgx,
        inf_msgy + 5 + inf_msgspace,
        windoww - inf_msgx,
        inf_msgspace * 3 + en * 3);
    for (int cnt = 0, cnt_end = (p_at_txtfunc + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == p_at_txtfunc)
        {
            x_at_txtfunc = (windoww - inf_msgx) % 192;
        }
        else
        {
            x_at_txtfunc = 192;
        }
        pos(cnt * 192 + inf_msgx, inf_msgy + 5 + inf_msgspace * 3 + en * 2);
        gcopy(
            3,
            496,
            536 + msgline % 4 * inf_msgspace,
            x_at_txtfunc,
            inf_msgspace);
    }
    gmode(2);
    msgtempprev = "";
    return;
}



void txtnew()
{
    if (tnew == 0)
    {
        if (strlen_u(msg(msgline % inf_maxlog)) > 4)
        {
            msg_newline();
            msglen = 2;
        }
    }
    return;
}



void msg_clear()
{
    msgtemp = "";
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        msg_newline();
    }
    return;
}



void txt_conv()
{
    redraw(0);

    if (std::empty(msgtemp(0)))
        return;

    if (tcopy)
    {
        tcopy = 0;
        txtcopy = msgtemp(0);
    }

    if (tnew == 1)
    {
        if (!std::empty(msg(msgline % inf_maxlog)))
        {
            msg_newline();
            tnew = 0;
            if (cfg_msgtrans)
            {
                p_at_txtfunc = (windoww - inf_msgx) / 192;
                redraw(0);
                gmode(4, -1, -1, cfg_msgtrans * 20);
                for (int i = 0; i < p_at_txtfunc + 1; ++i)
                {
                    if (i == p_at_txtfunc)
                    {
                        x_at_txtfunc = (windoww - inf_msgx) % 192;
                    }
                    else
                    {
                        x_at_txtfunc = 192;
                    }
                    pos(i * 192 + inf_msgx, inf_msgy + 5);
                    gcopy(3, 496, 536, x_at_txtfunc, inf_msgspace * 3);
                }
            }
            if (cfg_msgaddtime)
            {
                msgtemp(0) = u8"["s + gdata_minute + u8"] " + msgtemp(0);
            }
            else
            {
                msglen = 2;
            }
        }
    }

    if (msgdup != 0)
    {
        if (msgtempprev == msgtemp(0))
            return;
        msgtempprev = msgtemp(0);
        msgdup = 0;
    }

    int inf_maxmsglen_ = inf_maxmsglen * 1.5;

    if (jp)
    {
        if (msgtemp(0).find(u8"「") != std::string::npos)
        {
            if (tcolfix_at_txtfunc == 0)
            {
                tcol_at_txtfunc(0) = 210;
                tcol_at_txtfunc(1) = 250;
                tcol_at_txtfunc(2) = 160;
            }
            else
            {
                tcolfix_at_txtfunc = 0;
            }
        }

        int len = 0;
        while (1)
        {
            len = std::size(msgtemp(0));
            if (msglen + 4 > inf_maxmsglen_ && !std::empty(msgtemp(0)))
            {
                msg_newline();
            }
            if (msglen + len > inf_maxmsglen_)
            {
                int p2 = 0;
                while (1)
                {
                    const uint8_t c = msgtemp(0)[p2];
                    if (c <= 0x7F)
                        p2 += 1;
                    else if (c >= 0xc2 && c <= 0xdf)
                        p2 += 2;
                    else if (c >= 0xe0 && c <= 0xef)
                        p2 += 3;
                    else if (c >= 0xf0 && c <= 0xf7)
                        p2 += 4;
                    else if (c >= 0xf8 && c <= 0xfb)
                        p2 += 5;
                    else if (c >= 0xfc && c <= 0xfd)
                        p2 += 6;
                    else
                        p2 += 1;
                    if (p2 + msglen > inf_maxmsglen_)
                    {
                        if (p2 + msglen > inf_maxmsglen_ + 2)
                        {
                            break;
                        }
                        const auto m = strmid(msgtemp(0), p2, 3);
                        if (m != u8"。" && m != u8"、" && m != u8"」"
                            && m != u8"』" && m != u8"！" && m != u8"？"
                            && m != u8"…")
                        {
                            break;
                        }
                    }
                }
                auto m = strmid(msgtemp(0), 0, p2);
                msg(msgline % inf_maxlog) += m;
                msg_write(m);
                msgtemp(0) = strmid(msgtemp(0), p2, len - p2);
                if (std::empty(msgtemp(0)) || msgtemp(0) == u8" ")
                {
                    break;
                }
                msg_newline();
                continue;
            }
            break;
        }
        msg(msgline % inf_maxlog) += msgtemp(0);
        msg_write(msgtemp(0));
        msglen += len;
    }
    else
    {
        if (tcontinue_at_txtfunc == 0)
        {
            if (strutil::contains(msgtemp(0), u8"\""))
            {
                if (tcolfix_at_txtfunc == 0)
                {
                    tcol_at_txtfunc(0) = 210;
                    tcol_at_txtfunc(1) = 250;
                    tcol_at_txtfunc(2) = 160;
                }
                else
                {
                    tcolfix_at_txtfunc = 0;
                }
            }
            msgtemp(0)[0] = std::toupper(msgtemp(0)[0]);
        }
        else
        {
            tcontinue_at_txtfunc = 0;
        }
        msgtemp(0) += u8" ";
        while (1)
        {
            await();
            p_at_txtfunc = instr(msgtemp(0), 0, u8" ") + 1;
            if (p_at_txtfunc == 0)
            {
                break;
            }
            if (msglen + p_at_txtfunc > inf_maxmsglen)
            {
                msg_newline();
                continue;
            }
            auto mst = strmid(msgtemp(0), 0, p_at_txtfunc);
            msg(msgline % inf_maxlog) += mst;
            msg_write(mst);
            msglen += p_at_txtfunc;
            msgtemp(0) = strmid(
                msgtemp(0), p_at_txtfunc, std::size(msgtemp(0)) - p_at_txtfunc);
        }
        msg(msgline % inf_maxlog) += msgtemp(0);
        msg_write(msgtemp(0));
        msglen += std::size(msgtemp(0));
    }
}



std::string name(int cc)
{
    if (cc == 0)
    {
        return lang(u8"あなた"s, u8"you"s);
    }
    if (is_in_fov(cc) == 0)
    {
        return lang(u8"何か"s, u8"something"s);
    }
    if (cdata[0].blind != 0
        || (cbit(6, cc) == 1 && cbit(7, 0) == 0
            && cdata[cc].wet == 0))
    {
        return lang(u8"何か"s, u8"something"s);
    }
    if (en)
    {
        const char first = cdatan(0, cc)[0];
        if (first == u8'\"' || first == u8'<')
        {
            return cdatan(0, cc);
        }
        if (cbit(977, cc) == 0)
        {
            return u8"the "s + cdatan(0, cc);
        }
    }
    return cdatan(0, cc);
}



std::string aln(int cc)
{
    if (cc == 0)
    {
        return "";
    }
    if (is_in_fov(cc) == 0)
    {
        return u8"それは";
    }
    return cdatan(0, cc) + u8"は";
}



std::string npcn(int cc)
{
    if (cc == 0)
    {
        return "";
    }
    if (is_in_fov(cc) == 0)
    {
        return u8"それは";
    }
    return cdatan(0, cc) + u8"は";
}



std::string _s(int cc, int need_e)
{
    if (cc < 0 || cc >= 245)
    {
        if (need_e)
        {
            return u8"es"s;
        }
        else
        {
            return u8"s"s;
        }
    }
    if (cc == 0)
    {
        return "";
    }
    if (need_e)
    {
        return u8"es"s;
    }
    else
    {
        return u8"s"s;
    }
}



std::string _s2(int n)
{
    if (n > 1)
    {
        return "";
    }
    else
    {
        return u8"s"s;
    }
}



std::string is2(int n)
{
    if (n > 1)
    {
        return u8"are"s;
    }
    else
    {
        return u8"is"s;
    }
}



std::string is(int cc)
{
    if (cc < 0 || cc >= 245)
    {
        return u8"is"s;
    }
    if (cc == 0)
    {
        return u8"are"s;
    }
    return u8"is"s;
}



std::string have(int cc)
{
    if (cc < 0 || cc >= 245)
    {
        return u8"has"s;
    }
    if (cc == 0)
    {
        return u8"have"s;
    }
    return u8"has"s;
}



std::string does(int n)
{
    if (n == 1)
    {
        return u8"do"s;
    }
    else
    {
        return u8"does"s;
    }
}



std::string he(int cc, int prm_321)
{
    if (prm_321)
    {
        if (jp)
        {
            if (cdata[cc].sex == 0)
            {
                return u8"彼"s;
            }
            else
            {
                return u8"彼女"s;
            }
        }
        if (cdata[cc].sex == 0)
        {
            return u8"he"s;
        }
        else
        {
            return u8"she"s;
        }
    }
    if (cc < 0 || cc >= 245)
    {
        return u8"it"s;
    }
    if (is_in_fov(cc) == 0)
    {
        return u8"it"s;
    }
    if (cc == 0)
    {
        return u8"you"s;
    }
    if (cdata[cc].sex == 0)
    {
        return u8"he"s;
    }
    return u8"she"s;
}



std::string his(int cc, int prm_323)
{
    if (prm_323)
    {
        if (jp)
        {
            if (cc == 0)
            {
                return u8"あなたの"s;
            }
            else if (cdata[cc].sex == 0)
            {
                return u8"彼の"s;
            }
            else
            {
                return u8"彼女の"s;
            }
        }
        if (cc == 0)
        {
            return u8"your"s;
        }
        else if (cdata[cc].sex == 0)
        {
            return u8"his"s;
        }
        else
        {
            return u8"her"s;
        }
    }
    if (cc < 0 || cc >= 245)
    {
        return u8"its"s;
    }
    if (is_in_fov(cc) == 0)
    {
        return u8"its"s;
    }
    if (cc == 0)
    {
        return u8"your"s;
    }
    if (cdata[cc].sex == 0)
    {
        return u8"his"s;
    }
    return u8"her"s;
}



std::string him(int cc, int prm_325)
{
    if (prm_325)
    {
        if (jp)
        {
            if (cdata[cc].sex == 0)
            {
                return u8"彼"s;
            }
            else
            {
                return u8"彼女"s;
            }
        }
        if (cdata[cc].sex == 0)
        {
            return u8"him"s;
        }
        else
        {
            return u8"her"s;
        }
    }
    if (cc < 0 || cc >= 245)
    {
        return u8"it"s;
    }
    if (is_in_fov(cc) == 0)
    {
        return u8"it"s;
    }
    if (cc == 0)
    {
        return u8"yourself"s;
    }
    if (cdata[cc].sex == 0)
    {
        return u8"him"s;
    }
    return u8"her"s;
}



std::string your(int x)
{
    if (x < 0 || x >= 245)
    {
        return u8"'s"s;
    }
    if (x == 0)
    {
        return u8"r"s;
    }
    return u8"'s"s;
}



std::string yourself(int x)
{
    if (x < 0 || x >= 245)
    {
        return u8"itself"s;
    }
    if (is_in_fov(x) == 0)
    {
        return u8"itself"s;
    }
    if (x == 0)
    {
        return u8"yourself"s;
    }
    if (cdata[x].sex == 0)
    {
        return u8"himself"s;
    }
    return u8"herself"s;
}



void txt_check()
{
    txtvalid = (cc > 0 && is_in_fov(cc)) || cc == 0 ? 0 : -1;
}



void stxt(int cc, const std::string& str)
{
    if (cc == 0 || (is_in_fov(cc) && cdata[0].blind == 0))
    {
        txt(str);
    }
}



} // namespace elona
