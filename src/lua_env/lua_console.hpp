#pragma once

#include "../thirdparty/sol2/sol.hpp"
#include "lua_env.hpp"
#include <string>
#include <vector>
#include <queue>
#include <boost/circular_buffer.hpp>

namespace elona
{
namespace lua
{

class lua_env;

static const std::string PROMPT_PRIMARY = ">";
static const std::string PROMPT_SECONDARY = ">>";
static const std::string EOF_MARK = "<eof>";

class lua_console
{
public:
    typedef boost::circular_buffer<std::string> buffer;
    static constexpr int max_buffer_size = 100;

    explicit lua_console(lua_env*);

    void bind_api();

    void toggle() { enabled_ = !enabled_; }
    void setup_constants(int char_width, int char_height, int width, int height)
    {
        char_width_ = char_width;
        char_height_ = char_height;
        width_ = width;
        height_ = height;
        max_chars_ = (width_ / char_width_) - 1;
        max_lines_ = static_cast<size_t>(height_ / char_height_);
    }
    bool just_exited() { return just_exited_; }
    void end_just_exited() { just_exited_ = false; }

    void draw();
    void print(const std::string&);
    void grab_input();

private:
    static bool is_incomplete_lua_line(const sol::error& error);
    void print_single_line(const std::string& line);
    bool lua_error_handler(const std::string&, const sol::protected_function_result);
    bool interpret_lua(const std::string&);
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
    size_t max_lines_ = 0;
    size_t pos_ = 0;
    size_t last_size_ = 0;
    buffer buf_;
    buffer input_history_;
    std::string input_;
    std::string multiline_input_;
    bool is_multiline_ = false;
    bool cursor_visible_ = false;

    sol::environment console_env_;

    lua_env* lua_;
};

} // namespace lua
} // namespace elona
