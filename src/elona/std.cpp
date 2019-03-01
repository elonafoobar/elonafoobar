#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <regex>
#include <sstream>


#include "../snail/android.hpp"
#include "../snail/application.hpp"
#include "../snail/hsp.hpp"
#include "../snail/window.hpp"

#include "../util/fps_counter.hpp"
#include "../util/strutil.hpp"
#include "config/config.hpp"
#include "defines.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "log.hpp"
#include "macro.hpp"
#include "save.hpp"
#include "variables.hpp"
#ifdef ELONA_OS_WINDOWS
#include <windows.h> // MessageBoxA
#endif

namespace
{



size_t read_binary(std::istream& in, size_t size, char* buffer)
{
    assert(in);

    std::fill_n(buffer, size, 0);
    in.read(buffer, size);
    if (in.eof())
    {
        in.clear();
    }

    assert(in);

    return size;
}



std::pair<std::unique_ptr<char[]>, size_t> read_binary(
    std::istream& in,
    size_t size)
{
    std::unique_ptr<char[]> buf{new char[size]};
    return {std::move(buf), read_binary(in, size, buf.get())};
}



} // namespace


namespace elona
{



std::string operator+(const std::string& lhs, int rhs)
{
    return lhs + std::to_string(rhs);
}



std::string operator+(
    elona_vector1<std::string>& lhs,
    elona_vector1<std::string>& rhs)
{
    return lhs(0) + rhs(0);
}



std::string operator+(const std::string& lhs, elona_vector1<std::string>& rhs)
{
    return lhs + rhs(0);
}



std::string operator+(elona_vector1<std::string>& lhs, int rhs)
{
    return lhs(0) + std::to_string(rhs);
}



std::string operator+(elona_vector1<std::string>& lhs, const std::string& rhs)
{
    return lhs(0) + rhs;
}


/**
 * Polls for input and waits @a msec milliseconds.
 */
void await(int msec)
{
    snail::hsp::await(msec);

    // On Android, potentially quicksave if SDL detects that the app's
    // focus was lost and the player is being queried for input in
    // pc_turn().
    if (defines::is_android &&
        snail::Application::instance().was_focus_lost_just_now())
    {
        if (player_queried_for_input &&
            Config::instance().get<bool>("core.config.android.quicksave") &&
            !std::uncaught_exception())
        {
            ELONA_LOG("gui") << "Focus lost, quicksaving game.";
            snail::android::toast(
                i18n::s.get("core.locale.ui.save_on_suspend"),
                snail::android::ToastLength::long_length);
            save_game();
        }
    }
}


/**
 * Draws a filled box.
 */
void boxf(int x, int y, int width, int height, const snail::Color& color)
{
    snail::hsp::boxf(x, y, width, height, color);
}



void boxf()
{
    snail::hsp::boxf({0, 0, 0, 0});
}


/**
 * Draws a line box.
 */
void boxl(int x, int y, int width, int height, const snail::Color& color)
{
    const auto x2 = x + width;
    const auto y2 = y + height;
    line(x, y, x2, y, color);
    line(x2, y, x2, y2, color);
    line(x2, y2, x, y2, color);
    line(x, y2, x, y, color);
}



void bload(const fs::path& filename, std::string& data, int size, int)
{
    if (size == 0)
    {
        size = data.size();
    }
    std::ifstream in{filename.native(), std::ios::binary};
    if (!in)
    {
        throw std::runtime_error(
            u8"Error: fail to read " +
            filepathutil::make_preferred_path_in_utf8(filename));
    }
    auto buf = read_binary(in, size).first;
    data = std::string{buf.get(), static_cast<size_t>(size)};

    // Trim trailing NUL bytes from the string that was read.
    data.erase(std::remove(data.begin(), data.end(), '\0'), data.end());
}



void bload(const fs::path& filename, int& data, int size, int)
{
    std::ifstream in{filename.native(), std::ios::binary};
    if (!in)
    {
        throw std::runtime_error(
            u8"Error: fail to read " +
            filepathutil::make_preferred_path_in_utf8(filename));
    }
    auto buf = read_binary(in, size).first;
    data = *reinterpret_cast<int*>(buf.get());
}



void bload(const fs::path& filename, elona_vector1<int>& data, int size, int)
{
    if (size == 0)
    {
        size = data.size() * sizeof(int);
    }
    std::ifstream in{filename.native(), std::ios::binary};
    if (!in)
    {
        throw std::runtime_error(
            u8"Error: fail to read " +
            filepathutil::make_preferred_path_in_utf8(filename));
    }
    auto buf = read_binary(in, size).first;
    for (size_t i = 0; i < data.size(); ++i)
    {
        data(i) = reinterpret_cast<int*>(buf.get())[i];
        size -= sizeof(int);
        if (size == 0)
            return;
    }
}



void bsave(const fs::path& filename, const std::string& data)
{
    std::ofstream out{filename.native(), std::ios::binary};
    if (!out)
    {
        throw std::runtime_error(
            u8"Error: fail to write " +
            filepathutil::make_preferred_path_in_utf8(filename));
    }
    out.write(reinterpret_cast<const char*>(data.c_str()), data.size());
}



void bsave(const fs::path& filename, int data)
{
    std::ofstream out{filename.native(), std::ios::binary};
    out.write(reinterpret_cast<const char*>(&data), sizeof(data));
}



void bsave(const fs::path& filename, elona_vector1<int>& data)
{
    std::ofstream out{filename.native(), std::ios::binary};
    for (size_t i = 0; i < data.size(); ++i)
    {
        out.write(reinterpret_cast<const char*>(&data(i)), sizeof(int));
    }
}


/**
 * Creates a new window buffer with the specified width and height at index @a
 * window_id.
 */
void buffer(int window_id, int width, int height)
{
    snail::hsp::buffer(window_id, width, height);
}



#if defined(ELONA_OS_WINDOWS)
std::wstring get_utf16(const std::string& str)
{
    if (str.empty())
        return std::wstring();
    int sz = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), 0, 0);
    std::wstring res(sz, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &res[0], sz);
    return res;
}

int dialog_windows(const std::string& message, int option)
{
    UINT type = MB_ICONINFORMATION;
    int ret = 0;
    if (option == 1 || option == 3)
    {
        type = MB_ICONWARNING;
    }
    std::wstring message_wstr = get_utf16(message);
    switch (option)
    {
    case 0: // Info, OK
    case 1: // Warning, OK
        MessageBoxW(NULL, message_wstr.c_str(), L"Message", MB_OK | type);
        return DIALOG_OK;
    case 2: // Info, Yes/No
    case 3: // Warning, Yes/No
        ret = MessageBoxW(
            NULL, message_wstr.c_str(), L"Message", MB_YESNO | type);
        if (ret == IDYES)
        {
            return DIALOG_YES;
        }
        else
        {
            return DIALOG_NO;
        }
    case 16: // Open file dialog
    case 17: // Save as dialog
    case 32: // Color selection
    case 33: // Color selection with matrix
    default: return 0;
    }
}
#elif defined(ELONA_OS_MACOS)
int dialog_macos(const std::string& message, int option)
{
    (void)option;
    std::cout << message << std::endl;
    return 1;
}
#endif

/**
 * Opens a dialog box. Returns @ref DIALOG_YES (6) or @ref DIALOG_NO (7).
 * Supported values of @a option:
 * - 0: Info, OK
 * - 1: Warning, OK
 * - 2: Info, Yes/No
 * - 3: Warning, Yes/No
 */
int dialog(const std::string& message, int option)
{
#if defined(ELONA_OS_WINDOWS)
    return dialog_windows(message, option);
#elif defined(ELONA_OS_MACOS)
    return dialog_macos(message, option);
#else
    UNUSED(option);
    std::cout << message << std::endl;
    return 0;
#endif
}


/**
 * Selects the size and style of the font configured in the game's config file
 * for use with @ref mes.
 */
void font(int size, snail::Font::Style style)
{
    snail::hsp::font(
        size,
        style,
        filesystem::path(u8"font") /
            filepathutil::u8path(Config::instance().font_filename));
}


/**
 * Copy from source window to the currently selected window with offset.
 */
void gcopy(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y)
{
    snail::hsp::gcopy(
        window_id, src_x, src_y, src_width, src_height, dst_x, dst_y, -1, -1);
}



/**
 * Copy from source window to the currently selected window with offset and
 * stretching.
 */
void gcopy(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    snail::hsp::gcopy(
        window_id,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x,
        dst_y,
        dst_width,
        dst_height);
}



/**
 * Copy from source window to the currently selected window, centered.
 */
void gcopy_c(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y)
{
    gcopy_c(
        window_id,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x,
        dst_y,
        src_width,
        src_height);
}



/**
 * Copy from source window to the currently selected window, centered, with
 * stretching.
 */
void gcopy_c(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    snail::hsp::gcopy(
        window_id,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x - dst_width / 2,
        dst_y - dst_height / 2,
        dst_width,
        dst_height);
}


/**
 * Returns true if @a key is pressed.
 */
bool getkey(snail::Key key)
{
    return snail::Input::instance().is_pressed(key);
}


/**
 * Obtains a substring delimited by @a delimiter in @a source at offset @a
 * offset and copies it to @a out. If the delimiter is not found, the substring
 * will be delimited by the next newline found, if there are any,  or the length
 * of the string.
 */
void getstr(
    std::string& out,
    const std::string& source,
    int offset,
    char delimiter,
    int limit)
{
    UNUSED(limit);
    auto pos = source.find(delimiter, offset);
    if (pos == std::string::npos)
    {
        pos = source.find('\n', offset);
    }
    if (pos == std::string::npos)
    {
        pos = source.size();
    }
    if (pos >= size_t(offset))
    {
        const auto length = pos - offset;
        strsize = length + 1; // Includes the delimiter.
        out = source.substr(offset, length);
    }
    else
    {
        strsize = 0;
        out = "";
    }
}


/**
 * Obtains information about the graphics system. Supported values for @a type
 * are 0-23, but only some are implemented. Implemented values for @a type are
 * as follows:
 * - 3: Selected window ID.
 * - 6: Application window width.
 * - 7: Application window height.
 * - 10: Application window width.
 * - 11: Application window height.
 * - 12: Selected window width.
 * - 13: Selected window height.
 * - 22: Draw position X.
 * - 23: Draw position Y.
 */
int ginfo(int type)
{
    return snail::hsp::ginfo(type);
}


/**
 * Sets the drawing mode to use when copying images between windows. @a alpha
 * controls the amount of transparency images are copied with.
 *
 * Supported values for @a mode are as follows (others are ignored):
 * - 0: Normal.
 * - 2: Blend.
 * - 5: Add.
 */
void gmode(int mode, int alpha)
{
    snail::hsp::gmode(mode, alpha);
}



/**
 * Copy from source window to the currently selected window with rotation.
 */
void grotate(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    double angle)
{
    snail::hsp::grotate(
        window_id, src_x, src_y, src_width, src_height, dst_x, dst_y, angle);
}



/**
 * Copy from source window to the currently selected window with stretching and
 * rotation.
 */
void grotate(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height,
    double angle)
{
    snail::hsp::grotate(
        window_id,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x,
        dst_y,
        dst_width,
        dst_height,
        angle);
}


/**
 * Select the window to operate on with functions like @ref gcopy.
 */
void gsel(int window_id)
{
    snail::hsp::gsel(window_id);
}


/**
 * Returns the position in @a str where @a pattern is found relative from @a pos
 * in the string. Returns -1 if @a pattern is not found.
 */
int instr(const std::string& str, size_t pos, const std::string pattern)
{
    if (pattern == "\n")
    {
        return instr(str, pos, "\r");
    }
    const auto ret = str.find(pattern, pos);
    return ret == std::string::npos ? -1 : static_cast<int>(ret - pos);
}


/**
 * Attemps to convert @a s to a string using @ref std::stoi, Returns 0 on
 * invalid input.
 */
int stoi(const std::string& s)
{
    try
    {
        return std::stoi(s);
    }
    catch (std::invalid_argument&)
    {
        return 0;
    }
    catch (std::out_of_range&)
    {
        return 0;
    }
}


/**
 * Draws a line.
 */
void line(int x1, int y1, int x2, int y2, const snail::Color& color)
{
    snail::hsp::line(x1, y1, x2, y2, color);
}


/**
 * Draws a string.
 */
void mes(int x, int y, const std::string& text, const snail::Color& color)
{
    snail::hsp::mes(x, y, text, color);
}


/**
 * Sets @a buffer to receive text by pushing a new message box onto the message
 * box stack. All key input will be redirected to @a buffer as a string.
 * Multiple message boxes can be pushed, and the state of text for each will be
 * saved.
 *
 * If @a text is true, enable text editing behavior.
 * - Escape will output '\t' (a tab character)
 * - Backspace will erase text in @a buffer.
 * - CTRL-V will paste text from the clipboard.
 *
 * To stop redirecting text to @a buffer, call @ref onkey_0.
 */
void mesbox(std::string& buffer, bool text)
{
    snail::hsp::mesbox(buffer, Config::instance().key_wait, text);
}



void mmload(const fs::path& filepath, int id, int mode)
{
    UNUSED(filepath);
    UNUSED(id);
    UNUSED(mode);
}



void mmplay(int id)
{
    UNUSED(id);
}



void mmstop()
{
}



namespace notemanip
{
std::string* buffer = nullptr;


std::vector<std::string> split_lines(const std::string& str)
{
    std::vector<std::string> lines;
    std::istringstream ss{str};
    std::string buf;
    while (std::getline(ss, buf))
    {
        lines.push_back(buf);
    }
    return lines;
}



size_t count(const std::string& str)
{
    return split_lines(str).size();
}



} // namespace notemanip

/**
 * Inserts the text @a text to the current note buffer at line number @a index.
 * If @a overwrite is true, overwrite the line instead of inserting it.
 *
 * @a text could contain multiple newlines, meaning multiple lines could be
 * added.
 */
void noteadd(const std::string& text, int index, int overwrite)
{
    assert(overwrite == 0 || overwrite == 1);

    if (!notemanip::buffer)
        return;

    auto lines = notemanip::split_lines(*notemanip::buffer);

    if (index == -1)
    {
        index = lines.size();
    }
    else if (size_t(index) >= lines.size())
    {
        lines.resize(index + 1);
    }

    if (overwrite)
    {
        lines[index] = text;
    }
    else
    {
        auto itr = std::begin(lines);
        std::advance(itr, index);
        lines.insert(itr, text);
    }

    notemanip::buffer->clear();
    std::for_each(
        std::begin(lines), std::end(lines), [](const std::string& line) {
            notemanip::buffer->append(line + '\n');
        });
}


/**
 * Deletes the line at @a index in the current note buffer.
 */
void notedel(size_t index)
{
    if (!notemanip::buffer)
        return;

    const auto lines = notemanip::split_lines(*notemanip::buffer);
    notemanip::buffer->clear();
    for (size_t i = 0; i < lines.size(); ++i)
    {
        if (i != index)
        {
            *notemanip::buffer += lines[i] + '\n';
        }
    }
}


/**
 * Gets the line at @a index in the current note buffer and copies it to @a out,
 * or an empty string if out of range.
 */
void noteget(std::string& out, size_t index)
{
    if (!notemanip::buffer)
    {
        out = "";
        return;
    }

    const auto lines = notemanip::split_lines(*notemanip::buffer);
    if (index >= lines.size())
    {
        out = "";
    }
    else
    {
        out = lines[index];
    }
}



/**
 * Returns the number of lines in the current note buffer.
 */
int noteinfo()
{
    return notemanip::buffer ? notemanip::count(*notemanip::buffer) : 0;
}


/**
 * Sets @a buf as the current note buffer. Returns the number of lines in the
 * new buffer.
 */
int notesel(std::string& buf)
{
    notemanip::buffer = &buf;
    return noteinfo();
}


/**
 * Clears the current note buffer.
 */
void noteunsel()
{
    notemanip::buffer = nullptr;
}



void objprm(int, const std::string&)
{
}



void pget(int x, int y)
{
    UNUSED(x);
    UNUSED(y);
}



/**
 * Loads @a filepath, an image file, and renders it to the currently selected
 * window. if @a create_buffer is true, create a new buffer and render to it
 * instead.
 */
void picload(const fs::path& filepath, int x, int y, bool create_buffer)
{
    optional<snail::Color> keycolor = snail::Color{0, 0, 0};
    if (filepathutil::to_utf8_path(filepath).find(u8"pcc") != std::string::npos)
    {
        keycolor = snail::Color(43, 133, 133);
    }
    if (filepathutil::to_utf8_path(filepath).find(u8"bg") != std::string::npos)
    {
        keycolor = none;
    }
    snail::Image img{filepath, keycolor};
    snail::hsp::picload(img, x, y, create_buffer);
}



static std::string _make_fps_string()
{
    std::ostringstream ss;
    double ms = lib::g_fps_counter.ms();
    double fps = lib::g_fps_counter.fps();
    ss << std::setprecision(2) << std::fixed << std::right << std::setfill(' ')
       << "fps: " << std::setw(8) << fps << " ms: " << std::setw(8) << ms;
    return ss.str();
}

static void _draw_fps()
{
    static std::string fps_str;

    if (!snail::Application::instance().get_renderer().has_font())
    {
        return;
    }

    if (lib::g_fps_counter.want_report())
    {
        fps_str = _make_fps_string();
    }

    // Global font is modified, so it has to be restored directly after.
    const auto& fontbk = snail::Application::instance().get_renderer().font();
    const auto fontbk_size = fontbk.size();
    const auto fontbk_style = fontbk.style();

    // Since this particular implementation tracks FPS across every possible
    // place where things get redrawn, a background rectangle is needed to
    // prevent drawing over already-drawn text if the background is not
    // cleared between each redraw.
    boxf(4, 4, strlen_u(fps_str) * 7 + 2, 14 - en * 2 + 2, {0, 0, 0, 255});
    font(13 - en * 2);
    mes(5, 5, fps_str, {255, 255, 255});

    font(fontbk_size, fontbk_style);

    lib::g_fps_counter.count();
}

/**
 * Renders window buffer 0 to the application window.
 */
void redraw()
{
    if (Config::instance().get<bool>("core.config.foobar.show_fps"))
    {
        _draw_fps();
    }

    snail::hsp::redraw();
}


/**
 * Returns a bitmask of @a StickKey indicating keys pressed.
 */
StickKey stick(StickKey allow_repeat_keys)
{
    const auto& input = snail::Input::instance();

    auto is_enabled = [](StickKey n, StickKey flag) {
        return (n & flag) == flag;
    };

    auto check_key_pressed = [&](StickKey n, auto&& key) {
        if (is_enabled(allow_repeat_keys, n))
        {
            return input.is_pressed(key) ? n : StickKey::none;
        }
        else
        {
            return input.was_pressed_just_now(key) ? n : StickKey::none;
        }
    };

    StickKey ret = StickKey::none;

    ret |= check_key_pressed(StickKey::left, snail::Key::left);
    ret |= check_key_pressed(StickKey::up, snail::Key::up);
    ret |= check_key_pressed(StickKey::right, snail::Key::right);
    ret |= check_key_pressed(StickKey::down, snail::Key::down);
    ret |= check_key_pressed(StickKey::space, snail::Key::space);
    ret |= check_key_pressed(StickKey::enter, snail::Key::enter);
    ret |= check_key_pressed(StickKey::enter, snail::Key::keypad_enter);
    ret |= check_key_pressed(StickKey::ctrl, snail::Key::ctrl);
    ret |= check_key_pressed(StickKey::escape, snail::Key::escape);
    ret |= check_key_pressed(StickKey::mouse_left, snail::Mouse::Button::left);
    ret |=
        check_key_pressed(StickKey::mouse_right, snail::Mouse::Button::right);
    ret |= check_key_pressed(StickKey::tab, snail::Key::tab);

    if (allow_repeat_keys ==
        (StickKey::left | StickKey::up | StickKey::right | StickKey::down))
    {
        if (is_enabled(allow_repeat_keys, StickKey::left) ||
            is_enabled(allow_repeat_keys, StickKey::right))
        {
            ret |= input.is_pressed(snail::Key::up) ? StickKey::up
                                                    : StickKey::none;
            ret |= input.is_pressed(snail::Key::down) ? StickKey::down
                                                      : StickKey::none;
        }
        if (is_enabled(allow_repeat_keys, StickKey::up) ||
            is_enabled(allow_repeat_keys, StickKey::down))
        {
            ret |= input.is_pressed(snail::Key::left) ? StickKey::left
                                                      : StickKey::none;
            ret |= input.is_pressed(snail::Key::right) ? StickKey::right
                                                       : StickKey::none;
        }
    }

    mousex = input.mouse().x();
    mousey = input.mouse().y();

    return ret;
}


/**
 * Returns the number of UTF-8 codepoints contained in @a str.
 */
size_t strlen_u(const std::string& str)
{
    int ret = 0;
    for (size_t i = 0; i < str.size();)
    {
        const auto byte = strutil::byte_count(str[i]);
        ret += byte == 1 ? 1 : 2;
        i += byte;
    }
    return ret;
}


/**
 * Returns @a length characters of @a source starting at @a pos.
 *
 * If @a pos is -1, return @a length characters from right to left starting at
 * the end of the string.
 */
std::string strmid(const std::string& source, int pos, int length)
{
    const auto src_len = source.size();
    if (pos == -1)
    {
        // n characters from right to left.
        length = std::min(size_t(length), src_len);
        return source.substr(src_len - length, length);
    }
    else if (pos >= int(src_len))
    {
        return "";
    }
    else if (pos + length >= int(src_len))
    {
        return source.substr(pos, std::string::npos);
    }
    else
    {
        return source.substr(pos, length);
    }
}


/**
 * Initializes the application window.
 */
void title(
    const std::string& title_str,
    const std::string& display_mode,
    snail::Window::FullscreenMode fullscreen_mode)
{
    snail::hsp::title(title_str, display_mode, fullscreen_mode);
}



int wpeek(int x, size_t index)
{
    if (index == 0)
    {
        return x >> 16;
    }
    else
    {
        assert(index == 2);
        return x & 0xffff;
    }
}



void wpoke(int& x, size_t index, int y)
{
    if (index == 0)
    {
        x = wpeek(x, 2) + (y << 16);
    }
    else
    {
        assert(index == 2);
        x = (wpeek(x, 0) << 16) + y;
    }
}


/**
 * Sets the color modifier of copy operations between windows.
 */
void set_color_mod(int r, int g, int b, int window_id)
{
    snail::hsp::set_color_mod(r, g, b, window_id);
}



void ematan(int, int, int)
{
}



void apledit(int& out, int kind, int column_no)
{
    UNUSED(column_no);

    if (kind == 0)
    {
        // Current position of cursor
        out = static_cast<int>(inputlog(0).length());
    }
    else if (kind == 1)
    {
        // Total number of columns
    }
    else if (kind == 2)
    {
        // Number of characters at column "column_no"
    }
}



void func_2(int, int, int, int, int, int)
{
}



void DIINIT()
{
}



int DIGETJOYNUM()
{
    return 0;
}



void DIGETJOYSTATE(int, int)
{
}



int HMMBITCHECK(int x, int n)
{
    return x & (1 << n) ? 1 : 0;
}



int timeGetTime()
{
    return snail::hsp::timeGetTime();
}



int ImmGetContext(int)
{
    return 0;
}



void ImmReleaseContext(int, int)
{
}



void ImmSetOpenStatus(int, int)
{
}



int ImmGetOpenStatus(int)
{
    return 0;
}


/**
 * Pops a message box from the stack of message boxes, returning key input to
 * the next message box on the stack. After calling @ref mesbox, call this
 * function to stop redirecting text.
 */
void onkey_0()
{
    snail::hsp::onkey_0();
}



int talk_conv_jp(std::string& text, int max_line_length)
{
    max_line_length *= 1.5;

    std::string rest{text};
    text.clear();
    int n{};

    while (1)
    {
        const auto len = rest.size();
        if (int(len) < max_line_length)
        {
            text += rest;
            return n;
        }
        size_t line_length = 0;
        while (line_length <= len)
        {
            line_length += strutil::byte_count(rest[line_length]);
            if (int(line_length) > max_line_length)
            {
                if (rest.size() > line_length)
                {
                    const auto m = rest.substr(line_length);
                    for (const auto& period_like : {
                             u8"。",
                             u8"、",
                             u8"」",
                             u8"』",
                             u8"！",
                             u8"？",
                             u8"…",
                             u8"♪",
                             u8"♪1",
                         })
                    {
                        if (strutil::starts_with(m, period_like))
                        {
                            line_length += std::strlen(period_like);
                            break;
                        }
                    }
                }

                text += rest.substr(0, line_length) + '\n';
                ++n;
                if (rest.size() > line_length)
                {
                    rest = rest.substr(line_length);
                }
                else
                {
                    rest = "";
                }
                break;
            }
        }
    }
}



// Assumes that `text` insists of only ASCII codes.
int talk_conv_en(std::string& text, int max_line_length)
{
    int n = 0;

    std::string rest{text};
    text.clear();
    while (1)
    {
        int line_length = 0;
        while (1)
        {
            const auto p = rest.find(' ');
            if (p == std::string::npos)
            {
                text += rest;
                return n;
            }
            if (int(line_length + p + 1) > max_line_length)
            {
                text.back() = '\n';
                ++n;
                break;
            }
            text += rest.substr(0, p + 1);
            line_length += p + 1;
            rest = rest.substr(p + 1);
        }
    }
}



int talk_conv(std::string& text, int max_line_length)
{
    if (jp)
    {
        return talk_conv_jp(text, max_line_length);
    }
    else
    {
        return talk_conv_en(text, max_line_length);
    }
}



} // namespace elona
