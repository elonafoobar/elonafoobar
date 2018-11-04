#include "message.hpp"
#include <ctype.h>
#include <iomanip>
#include <sstream>
#include "audio.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "map.hpp"
#include "message_log.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace detail
{

std::vector<LogObserver*> observers;

} // namespace detail



MessageLog message_log;



LogObserver::~LogObserver()
{
    unsubscribe_log(this);
}



void subscribe_log(LogObserver* observer)
{
    assert(observer != nullptr);

    detail::observers.push_back(observer);
}



void unsubscribe_log(LogObserver* observer)
{
    const auto itr = std::find(
        std::begin(detail::observers), std::end(detail::observers), observer);
    if (itr == std::end(detail::observers))
    {
        return;
    }

    detail::observers.erase(itr);
}



void anime_halt(int x_at_txtfunc, int y_at_txtfunc)
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
    anime_halt(windoww - 120, windowh - 22);
    screenupdate = -1;
    update_screen();
}



void help_halt()
{
    anime_halt(wx + dx - 140, wy + dy - 1);
}



void Message::msg_append_begin(const std::string& first)
{
    _msg_newline();
    msgtemp = first;
}



void Message::msg_append(const std::string& msg)
{
    msgtemp += msg;
}



void Message::msg_append_end()
{
    _txt_conv();
}



void Message::linebreak()
{
    if (!_new_turn && strlen_u(msg[msgline % inf_maxlog]) > 4)
    {
        _msg_newline();
        message_width = 2;
    }
}



void Message::clear()
{
    msgtemp.clear();
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        _msg_newline();
    }
}



void Message::_msg_write(std::string& message)
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

    elona::color(text_color.r, text_color.g, text_color.b);
    pos(message_width * inf_mesfont / 2 + inf_msgx + 6,
        (inf_msgline - 1) * inf_msgspace + inf_msgy + 5);
    font(inf_mesfont - en * 2);
    gmode(0, 255);
    mes(message);
    elona::color(0, 0, 0);

    if (message_log.lines.empty())
    {
        message_log.lines.emplace_back();
    }
    message_log.lines.back().spans.emplace_back(message, text_color);
}



void Message::_msg_newline()
{
    message_log.lines.emplace_back();

    message_width = 0;
    ++msgline;
    if (msgline >= inf_maxlog)
    {
        msgline -= inf_maxlog;
    }
    msg[msgline % inf_maxlog] = "";

    gmode(0);
    pos(inf_msgx, inf_msgy + 5);
    gcopy(
        0,
        inf_msgx,
        inf_msgy + 5 + inf_msgspace,
        windoww - inf_msgx,
        inf_msgspace * 3 + en * 3);

    int p_at_txtfunc = (windoww - inf_msgx) / 192;
    for (int cnt = 0, cnt_end = (p_at_txtfunc + 1); cnt < cnt_end; ++cnt)
    {
        int x_at_txtfunc;
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
    msgtempprev.clear();
}



void Message::_txt_conv()
{
    if (msgtemp.empty())
    {
        return;
    }

    for (auto&& observer : detail::observers)
    {
        if (observer)
        {
            observer->update(msgtemp);
        }
    }

    if (_new_turn && !msg[msgline % inf_maxlog].empty())
    {
        _msg_newline();
        _new_turn = false;
        if (Config::instance().message_transparency)
        {
            int p_at_txtfunc = (windoww - inf_msgx) / 192;
            gmode(4, Config::instance().message_transparency * 20);
            for (int i = 0; i < p_at_txtfunc + 1; ++i)
            {
                int x_at_txtfunc;
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
        if (Config::instance().message_add_timestamps)
        {
            std::stringstream ss;
            ss << "[" << std::setw(2) << std::setfill('0')
               << game_data.date.minute << "] ";
            msgtemp = ss.str() + msgtemp;
        }
        else
        {
            message_width = 2;
        }
    }

    if (show_only_once)
    {
        if (msgtempprev == msgtemp)
        {
            return;
        }
        msgtempprev = msgtemp;
        show_only_once = false;
    }

    if (jp)
    {
        if (msgtemp.find(u8"「") != std::string::npos)
        {
            if (!fix_text_color)
            {
                text_color = {210, 250, 160, 255};
            }
        }

        size_t width{};
        while (1)
        {
            width = strlen_u(msgtemp);
            if (message_width + 4 > inf_maxmsglen && !msgtemp.empty())
            {
                _msg_newline();
            }
            if (message_width + width > inf_maxmsglen)
            {
                size_t len{};
                size_t wdt{};
                while (1)
                {
                    const auto byte = strutil::byte_count(msgtemp[len]);
                    wdt += byte == 1 ? 1 : 2;
                    len += byte;
                    if (wdt + message_width > inf_maxmsglen)
                    {
                        if (wdt > 1 && strmid(msgtemp, wdt - 2, 3) == u8"♪1")
                        {
                            ++wdt;
                            break;
                        }
                        if (wdt + message_width > inf_maxmsglen + 2)
                        {
                            break;
                        }
                        if (!strutil::starts_with(msgtemp, u8"。", len)
                            && !strutil::starts_with(msgtemp, u8"、", len)
                            && !strutil::starts_with(msgtemp, u8"」", len)
                            && !strutil::starts_with(msgtemp, u8"』", len)
                            && !strutil::starts_with(msgtemp, u8"！", len)
                            && !strutil::starts_with(msgtemp, u8"？", len)
                            && !strutil::starts_with(msgtemp, u8"…", len)
                            && !strutil::starts_with(msgtemp, u8"♪", len)
                            && !strutil::starts_with(msgtemp, u8"♪1", len))
                        {
                            break;
                        }
                    }
                }
                if (len >= msgtemp.size())
                {
                    len = msgtemp.size();
                }
                auto m = msgtemp.substr(0, len);
                msg[msgline % inf_maxlog] += m;
                _msg_write(m);
                msgtemp = msgtemp.substr(len);
                if (msgtemp.empty() || msgtemp == u8" ")
                {
                    break;
                }
                _msg_newline();
                continue;
            }
            break;
        }
        msg[msgline % inf_maxlog] += msgtemp;
        _msg_write(msgtemp);
        message_width += width;
    }
    else
    {
        if (_continue_sentence)
        {
            _continue_sentence = false;
        }
        else
        {
            if (strutil::contains(msgtemp, u8"\""))
            {
                if (!fix_text_color)
                {
                    text_color = {210, 250, 160, 255};
                }
            }
            msgtemp[0] = std::toupper(msgtemp[0]);
        }
        msgtemp += u8" ";
        while (1)
        {
            int p_at_txtfunc = instr(msgtemp, 0, u8" ") + 1;
            if (p_at_txtfunc == 0)
            {
                break;
            }
            if (message_width + p_at_txtfunc > inf_maxmsglen)
            {
                _msg_newline();
                continue;
            }
            auto mst = strmid(msgtemp, 0, p_at_txtfunc);
            msg[msgline % inf_maxlog] += mst;
            _msg_write(mst);
            message_width += p_at_txtfunc;
            msgtemp =
                strmid(msgtemp, p_at_txtfunc, msgtemp.size() - p_at_txtfunc);
        }
        msg[msgline % inf_maxlog] += msgtemp;
        _msg_write(msgtemp);
        message_width += msgtemp.size();
    }

    fix_text_color = false;
}



void Message::_txt_internal(std::vector<std::string> args)
{
    msgtemp = choice(args);
    _txt_conv();
    text_color = {255, 255, 255, 255};
}



void Message::txtef(ColorIndex color)
{
    const auto color_int =
        static_cast<int>(static_cast<ColorIndex>(color)) % 21;
    text_color = {static_cast<uint8_t>(255 - c_col(0, color_int)),
                  static_cast<uint8_t>(255 - c_col(1, color_int)),
                  static_cast<uint8_t>(255 - c_col(2, color_int)),
                  255};
    fix_text_color = color_int == 5;
}

} // namespace elona
