#include "debug.hpp"
#include "config.hpp"
#include "input.hpp"
#include "snail/application.hpp"
#include "snail/blend_mode.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{
namespace debug
{

void console_t::log(const std::string& message)
{
    if (message.size() == 0)
    {
        return;
    }

    int max_chars = max_chars_;
    size_t last_index = 0;
    size_t cut_index = utf8_cut_index(message, max_chars);

    while (cut_index != message.size())
    {
        buf_.push_back(message.substr(last_index, cut_index));
        last_index = cut_index;
        max_chars += max_chars_;
        cut_index = utf8_cut_index(message, max_chars);
    }

    buf_.push_back(message.substr(last_index, cut_index));
}

void console_t::draw()
{
    if (!enabled_)
    {
        return;
    }

    snail::application::instance().get_renderer().set_blend_mode(
        snail::blend_mode_t::blend);
    snail::application::instance().get_renderer().set_draw_color(
        {17, 17, 65, 192});
    snail::application::instance().get_renderer().fill_rect(
        0,
        0,
        width_,
        height_);

    elona::color(255, 255, 255);

    size_t n = std::min(static_cast<size_t>(max_lines_ - (focused_ ? 1 : 0)), buf_.size());
    int i = 0;
    for(auto it = buf_.end() - n; it < buf_.end(); it++)
    {
        elona::pos(
            4,
            char_height_ * i);
        font(inf_mesfont - en * 2);
        mes(*it);

        i++;
    }

    if (focused_)
    {
        elona::pos(
            4,
            char_height_ * (max_lines_ - 1));
        font(inf_mesfont - en * 2);
        mes(u8">> "s + input_);
    }

    elona::color(0, 0, 0);
}

void console_t::grab_input()
{
    bool reenable = false;
    int frame = 0;

    if (!enabled_)
    {
        enabled_ = true;
        reenable = true;
    }

    focused_ = true;
    inputlog = "";
    input_ = "";
    notesel(inputlog);
    mesbox(inputlog, true);

    while (focused_)
    {
        ++frame;
        if (frame % config::instance().scrsync == 1)
        {
            ++scrturn;
            label_1420();
        }

        noteget(input_, 0);

        await(config::instance().wait1);
        key_check(0);

        if (getkey(snail::key::escape))
        {
            focused_ = false;
        }
        else if (getkey(snail::key::enter))
        {
            rm_crlf(input_);
            log(input_);
            inputlog = "";
            input_ = "";
        }
    }

    onkey_0();
    just_exited_ = true;

    if (reenable)
    {
        enabled_ = false;
    }
}

bool voldemort = false;
console_t console;

} // namespace debug
} // namespace elona
