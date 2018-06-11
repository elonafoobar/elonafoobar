#pragma once

#include <string>
#include <vector>
#include <queue>
#include <boost/circular_buffer.hpp>


namespace elona
{


namespace debug
{

class console_t
{
public:
    typedef boost::circular_buffer<std::string> buffer;
    static constexpr int max_lines = 100;

    console_t()
    {
        buf_ = buffer(max_lines);
        input_history_ = buffer(max_lines);
    }

    void toggle() { enabled_ = !enabled_; }
    void set_char_width(int char_width) { char_width_ = char_width; }
    void set_char_height(int char_height) { char_height_ = char_height; }
    void set_width(int width) { width_ = width; }
    void set_height(int height) { height_ = height; }
    void set_max_chars() { max_chars_ = (width_ / char_width_) - 1; }
    void set_max_lines() { max_lines_ = height_ / char_height_; }
    bool just_exited() { return just_exited_; }
    void end_just_exited() { just_exited_ = false; }

    void draw();
    void log(const std::string&);
    void grab_input();

private:
    void input_loop();
    void read_line();
    void add_line(std::string);

    // Assumes the font is monospaced.
    int char_width_ = 10;
    int char_height_ = 14;

    bool enabled_ = false;
    bool focused_ = false;
    bool just_exited_ = false;
    int width_ = 800;
    int height_ = 250;
    int max_chars_ = 0;
    int max_lines_ = 0;
    int pos_ = 0;
    buffer buf_;
    buffer input_history_;
    std::string input_;
};

extern bool voldemort;
extern console_t console;
}


} // namespace elona
