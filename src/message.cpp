#include <ctype.h>
#include <iomanip>
#include <sstream>
#include "audio.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "map.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{
size_t message_width{};
bool fix_text_color;
int p_at_txtfunc = 0;
} // namespace elona



namespace
{

bool will_continue_sentence = 0;



void msg_write(std::string& message)
{
    constexpr const auto musical_note = u8"♪";

    for (auto pos = strutil::find_widthwise(message, musical_note);
         pos.first != std::string::npos;
         pos = strutil::find_widthwise(message, musical_note))
    {
        auto bytewise_pos = pos.first;
        auto widthwise_pos = pos.second;

        const auto symbol_type = elona::stoi(
            message.substr(bytewise_pos + std::strlen(musical_note), 1));
        if (jp && symbol_type == 0)
        {
            break;
        }
        message = message.substr(0, bytewise_pos) + u8"  "
            + message.substr(
                  bytewise_pos + std::strlen(musical_note)
                  + (symbol_type != 0));
        elona::pos(
            (message_width + widthwise_pos) * inf_mesfont / 2 + inf_msgx + 7
                + en * 3,
            (inf_msgline - 1) * inf_msgspace + inf_msgy + 5);
        gmode(2);
        gcopy(3, 600 + symbol_type * 24, 360, 16, 16);
    }

    elona::color(tcol_at_txtfunc(0), tcol_at_txtfunc(1), tcol_at_txtfunc(2));
    elona::pos(
        message_width * inf_mesfont / 2 + inf_msgx + 6,
        (inf_msgline - 1) * inf_msgspace + inf_msgy + 5);
    font(inf_mesfont - en * 2);
    gmode(0, 255);
    mes(message);
    elona::color(0, 0, 0);
}



void clear_log_panel()
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
}

} // namespace



namespace elona
{

void txtcontinue()
{
    will_continue_sentence = true;
}



void anime_halt()
{
    key = "";
    objprm(0, ""s);
    keylog = "";
    gmode(0);
    gsel(3);
    pos(672, 504);
    gcopy(0, x_at_txtfunc, y_at_txtfunc, 120, 24);
    gsel(0);
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        await(Config::instance().wait1 / 3);
        draw(
            "label_more",
            x_at_txtfunc,
            y_at_txtfunc + 12 - cnt,
            120,
            cnt * 2 + 1);
        redraw();
    }
    wait_key_pressed(true);
    snd("core.ok1");
    for (int cnt = 0; cnt < 7; ++cnt)
    {
        await(Config::instance().wait1 / 3);
        pos(x_at_txtfunc, y_at_txtfunc);
        gcopy(3, 672, 504, 120, 24);
        if (cnt != 6)
        {
            draw(
                "label_more",
                x_at_txtfunc,
                y_at_txtfunc + cnt * 2,
                120,
                22 - cnt * 4);
        }
        redraw();
    }
    gmode(2);
}



void msg_halt()
{
    x_at_txtfunc = windoww - 120;
    y_at_txtfunc = windowh - 22;
    anime_halt();
    screenupdate = -1;
    update_screen();
}



void help_halt()
{
    x_at_txtfunc = wx + dx - 140;
    y_at_txtfunc = wy + dy - 1;
    anime_halt();
}



void txtef(ColorIndex color)
{
    txtef(static_cast<int>(color) % 21);
}



void txtef(int prm_308)
{
    tcol_at_txtfunc(0) = 255 - c_col(0, prm_308);
    tcol_at_txtfunc(1) = 255 - c_col(1, prm_308);
    tcol_at_txtfunc(2) = 255 - c_col(2, prm_308);

    fix_text_color = prm_308 == 5;
}



void msg_newline()
{
    clear_log_panel();

    message_width = 0;
    ++msgline;
    if (msgline >= inf_maxlog)
    {
        msgline -= inf_maxlog;
    }
    msg(msgline % inf_maxlog) = "";
    p_at_txtfunc = (windoww - inf_msgx) / 192;
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
}



void txtnew()
{
    if (tnew == 0)
    {
        if (strlen_u(msg(msgline % inf_maxlog)) > 4)
        {
            msg_newline();
            message_width = 2;
        }
    }
}



void msg_clear()
{
    msgtemp = "";
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        msg_newline();
    }
}



void txt_conv()
{
    if (msgtemp(0).empty())
        return;

    if (tcopy)
    {
        tcopy = 0;
        txtcopy = msgtemp(0);
    }

    if (tnew == 1)
    {
        if (!msg(msgline % inf_maxlog).empty())
        {
            msg_newline();
            tnew = 0;
            if (Config::instance().msgtrans)
            {
                p_at_txtfunc = (windoww - inf_msgx) / 192;
                gmode(4, Config::instance().msgtrans * 20);
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
            if (Config::instance().msgaddtime)
            {
                std::stringstream ss;
                ss << "[" << std::setw(2) << std::setfill('0')
                   << game_data.date.minute << "] ";
                msgtemp(0) = ss.str() + msgtemp(0);
            }
            else
            {
                message_width = 2;
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

    if (jp)
    {
        if (msgtemp(0).find(u8"「") != std::string::npos)
        {
            if (!fix_text_color)
            {
                tcol_at_txtfunc(0) = 210;
                tcol_at_txtfunc(1) = 250;
                tcol_at_txtfunc(2) = 160;
            }
        }

        size_t width{};
        while (1)
        {
            width = strlen_u(msgtemp(0));
            if (message_width + 4 > inf_maxmsglen && !msgtemp(0).empty())
            {
                msg_newline();
            }
            if (message_width + width > inf_maxmsglen)
            {
                size_t len{};
                size_t wdt{};
                while (1)
                {
                    const auto byte = strutil::byte_count(msgtemp(0)[len]);
                    wdt += byte == 1 ? 1 : 2;
                    len += byte;
                    if (wdt + message_width > inf_maxmsglen)
                    {
                        if (wdt + message_width > inf_maxmsglen + 2)
                        {
                            break;
                        }
                        if (!strutil::starts_with(msgtemp(0), u8"。", len)
                            && !strutil::starts_with(msgtemp(0), u8"、", len)
                            && !strutil::starts_with(msgtemp(0), u8"」", len)
                            && !strutil::starts_with(msgtemp(0), u8"』", len)
                            && !strutil::starts_with(msgtemp(0), u8"！", len)
                            && !strutil::starts_with(msgtemp(0), u8"？", len)
                            && !strutil::starts_with(msgtemp(0), u8"…", len))
                        {
                            break;
                        }
                    }
                }
                if (len >= msgtemp(0).size())
                    len = msgtemp(0).size();
                auto m = msgtemp(0).substr(0, len);
                msg(msgline % inf_maxlog) += m;
                msg_write(m);
                msgtemp(0) = msgtemp(0).substr(len);
                if (msgtemp(0).empty() || msgtemp(0) == u8" ")
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
        message_width += width;
    }
    else
    {
        if (will_continue_sentence)
        {
            will_continue_sentence = false;
        }
        else
        {
            if (strutil::contains(msgtemp(0), u8"\""))
            {
                if (!fix_text_color)
                {
                    tcol_at_txtfunc(0) = 210;
                    tcol_at_txtfunc(1) = 250;
                    tcol_at_txtfunc(2) = 160;
                }
            }
            msgtemp(0)[0] = std::toupper(msgtemp(0)[0]);
        }
        msgtemp(0) += u8" ";
        while (1)
        {
            p_at_txtfunc = instr(msgtemp(0), 0, u8" ") + 1;
            if (p_at_txtfunc == 0)
            {
                break;
            }
            if (message_width + p_at_txtfunc > inf_maxmsglen)
            {
                msg_newline();
                continue;
            }
            auto mst = strmid(msgtemp(0), 0, p_at_txtfunc);
            msg(msgline % inf_maxlog) += mst;
            msg_write(mst);
            message_width += p_at_txtfunc;
            msgtemp(0) = strmid(
                msgtemp(0), p_at_txtfunc, msgtemp(0).size() - p_at_txtfunc);
        }
        msg(msgline % inf_maxlog) += msgtemp(0);
        msg_write(msgtemp(0));
        message_width += msgtemp(0).size();
    }

    fix_text_color = false;
}



std::string name(int cc)
{
    if (cc == 0)
    {
        return i18n::s.get("core.locale.chara.you");
    }
    if (is_in_fov(cdata[cc]) == 0)
    {
        return i18n::s.get("core.locale.chara.something");
    }
    if (cdata.player().blind != 0
        || (cdata[cc].is_invisible() == 1
            && cdata.player().can_see_invisible() == 0 && cdata[cc].wet == 0))
    {
        return i18n::s.get("core.locale.chara.something");
    }
    if (en)
    {
        const char first = cdatan(0, cc)[0];
        if (first == '\"' || first == '<')
        {
            return cdatan(0, cc);
        }
        if (cdata[cc].has_own_name() == 0)
        {
            return u8"the "s + cdatan(0, cc);
        }
    }
    return cdatan(0, cc);
}

} // namespace elona
