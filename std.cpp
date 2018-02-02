#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <regex>
#include <sstream>


#include "sdl/application.hpp"
#include "sdl/input.hpp"

#include "elona.hpp"
#include "variables.hpp"


using namespace snail;


namespace
{
template <typename... Args>
void LOG(Args&&... args)
{
    std::cerr << std::setw(10) << ::SDL_GetTicks();
    using swallow = std::initializer_list<int>;
    (void)swallow{((void)(std::cerr << ' ' << std::forward<Args>(args)), 0)...};
    std::cerr << std::endl;
}



Key hspkey2snailkey(int hsp_key)
{
    switch (hsp_key)
    {
    case 8: return Key::backspace;
    case 12: return Key::none; // Maybe one of the keypad keys.
    case 13: return Key::enter;
    case 16: return Key::shift;
    case 17: return Key::ctrl;
    case 18: return Key::alt;
    case 27: return Key::escape;
    case 32: return Key::space;
    case 33: return Key::pageup;
    case 34: return Key::pagedown;
    case 35: return Key::end;
    case 36: return Key::home;
    case 38: return Key::up;
    case 40: return Key::down;
    case 45: return Key::none; // Maybe one of the keypad keys.
    case 48: return Key::key_0;
    case 49: return Key::key_1;
    case 50: return Key::key_2;
    case 51: return Key::key_3;
    case 52: return Key::key_4;
    case 53: return Key::key_5;
    case 54: return Key::key_6;
    case 55: return Key::key_7;
    case 56: return Key::key_8;
    case 57: return Key::key_9;
    case 65: return Key::key_a;
    case 66: return Key::key_b;
    case 67: return Key::key_c;
    case 68: return Key::key_d;
    case 69: return Key::key_e;
    case 70: return Key::key_f;
    case 71: return Key::key_g;
    case 72: return Key::key_h;
    case 73: return Key::key_i;
    case 74: return Key::key_j;
    case 75: return Key::key_k;
    case 76: return Key::key_l;
    case 77: return Key::key_m;
    case 78: return Key::key_n;
    case 79: return Key::key_o;
    case 80: return Key::key_p;
    case 81: return Key::key_q;
    case 82: return Key::key_r;
    case 83: return Key::key_s;
    case 84: return Key::key_t;
    case 85: return Key::key_u;
    case 86: return Key::key_v;
    case 87: return Key::key_w;
    case 88: return Key::key_x;
    case 89: return Key::key_y;
    case 90: return Key::key_z;
    case 96: return Key::keypad_0;
    case 97: return Key::keypad_1;
    case 98: return Key::keypad_2;
    case 99: return Key::keypad_3;
    case 100: return Key::keypad_4;
    case 101: return Key::keypad_5;
    case 102: return Key::keypad_6;
    case 103: return Key::keypad_7;
    case 104: return Key::keypad_8;
    case 105: return Key::keypad_9;
    case 112: return Key::f1;
    case 113: return Key::f2;
    case 114: return Key::f3;
    case 115: return Key::f4;
    case 116: return Key::f5;
    case 117: return Key::f6;
    case 118: return Key::f7;
    case 119: return Key::f8;
    case 120: return Key::f9;
    case 122: return Key::f11;
    case 123: return Key::f12;
    default: assert(0);
    }
}


char hspkey2char(int hsp_key)
{
    switch (hsp_key)
    {
    case 13: return '\n';
    case 32: return ' ';
    case 48: return '0';
    case 49: return '1';
    case 50: return '2';
    case 51: return '3';
    case 52: return '4';
    case 53: return '5';
    case 54: return '6';
    case 55: return '7';
    case 56: return '8';
    case 57: return '9';
    case 65: return 'a';
    case 66: return 'b';
    case 67: return 'c';
    case 68: return 'd';
    case 69: return 'e';
    case 70: return 'f';
    case 71: return 'g';
    case 72: return 'h';
    case 73: return 'i';
    case 74: return 'j';
    case 75: return 'k';
    case 76: return 'l';
    case 77: return 'm';
    case 78: return 'n';
    case 79: return 'o';
    case 80: return 'p';
    case 81: return 'q';
    case 82: return 'r';
    case 83: return 's';
    case 84: return 't';
    case 85: return 'u';
    case 86: return 'v';
    case 87: return 'w';
    case 88: return 'x';
    case 89: return 'y';
    case 90: return 'z';
    case 96: return '0';
    case 97: return '1';
    case 98: return '2';
    case 99: return '3';
    case 100: return '4';
    case 101: return '5';
    case 102: return '6';
    case 103: return '7';
    case 104: return '8';
    case 105: return '9';
    default: assert(0);
    }
}



// UTF-8
size_t byte_count(uint8_t c)
{
    if (c >= 0x00 && c <= 0x7F)
        return 1;
    else if (c >= 0xc2 && c <= 0xdf)
        return 2;
    else if (c >= 0xe0 && c <= 0xef)
        return 3;
    else if (c >= 0xf0 && c <= 0xf7)
        return 4;
    else if (c >= 0xf8 && c <= 0xfb)
        return 5;
    else if (c >= 0xfc && c <= 0xfd)
        return 6;
    else
        return 1;
}


} // namespace



namespace elona
{
namespace detail
{
struct TexBuffer
{
    ::SDL_Texture* texture = nullptr;
    int tex_width = 32;
    int tex_height = 32;
    Color color{0, 0, 0, 255};
    int x = 0;
    int y = 0;
    int width = 32;
    int height = 32;
    int mode = 2;
};


int current_buffer;
std::vector<TexBuffer> tex_buffers;
::SDL_Texture* tmp_buffer;

TexBuffer& current_tex_buffer()
{
    return tex_buffers[current_buffer];
}



void set_blend_mode()
{
    switch (current_tex_buffer().mode)
    {
    case 0:
    case 1:
        Application::instance().renderer().set_blend_mode(BlendMode::none);
        break;
    case 2:
    case 3:
        Application::instance().renderer().set_blend_mode(BlendMode::blend);
        break;
    case 4:
        Application::instance().renderer().set_blend_mode(BlendMode::blend);
        break;
    case 5:
        Application::instance().renderer().set_blend_mode(BlendMode::add);
        break;
    case 6:
        Application::instance().renderer().set_blend_mode(BlendMode::blend);
        break;
    default: break;
    }
}



} // namespace detail



namespace mesbox_detail
{
struct MessageBox
{
    MessageBox(std::string& buffer)
        : buffer(buffer)
    {
    }


    void update()
    {
        auto c = to_char(Keyboard::instance().get_pressed_key());
        if (c)
        {
            // TODO capslock
            if (Keyboard::instance().is_pressed_exactly(Key::shift))
            {
                c = std::toupper(c);
            }
            if (c == '\n')
            {
                buffer += "\r\n";
            }
            else
            {
                buffer += c;
            }
        }
    }


private:
    std::string& buffer;
};

std::vector<std::unique_ptr<MessageBox>> message_boxes;

} // namespace mesbox_detail



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



int abs(int x)
{
    return x > 0 ? x : -x;
}


double atan(int y, int x)
{
    return std::atan2(static_cast<double>(y), static_cast<double>(x));
}



namespace await_detail
{
uint32_t last_await;
}


void await(int msec)
{
    Application::instance().proc_event();
    for (auto&& b : mesbox_detail::message_boxes)
    {
        if (b)
        {
            b->update();
        }
    }

    const auto now = ::SDL_GetTicks();
    if (await_detail::last_await == 0)
    {
        await_detail::last_await = now;
    }
    const auto delta = now - await_detail::last_await;
    if (msec > delta)
    {
        ::SDL_Delay(msec - delta);
    }
    await_detail::last_await = now;
}


// CANNOT BE IMPLEMENTED
void axobj(int, const std::string&, int, int)
{
}


void bcopy(const fs::path& from, const fs::path& to)
{
    LOG("copy", from, to);
    fs::copy_file(from, to, fs::copy_options::overwrite_existing);
}

// fullscreen
void bgscr(int window_id, int width, int height, int, int)
{
}



void boxf(int x1, int y1, int x2, int y2)
{
    if (detail::current_tex_buffer().color.r == 0
        && detail::current_tex_buffer().color.g == 0
        && detail::current_tex_buffer().color.b == 0)
    {
        Application::instance().renderer().set_blend_mode(BlendMode::none);
        Application::instance().renderer().set_draw_color({0, 0, 0, 0});
    }
    Application::instance().renderer().fill_rect(x1, y1, x2 - x1, y2 - y1);
}

void boxf()
{
    if (detail::current_tex_buffer().color.r == 0
        && detail::current_tex_buffer().color.g == 0
        && detail::current_tex_buffer().color.b == 0)
    {
        Application::instance().renderer().set_blend_mode(BlendMode::none);
        Application::instance().renderer().set_draw_color({0, 0, 0, 0});
    }
    Application::instance().renderer().clear();
}


void bload(const fs::path& filename, std::string& data, int size, int)
{
    LOG("bload", filename);

    if (size == 0)
    {
        size = data.size();
    }
    std::unique_ptr<char[]> buf{new char[size]};
    std::ifstream in{filename, std::ios::binary};
    if (!in)
    {
        LOG("Failed");
        throw 0;
    }
    size = in.readsome(buf.get(), size);
    data = {buf.get(), static_cast<size_t>(size)};
}

void bload(const fs::path& filename, int& data, int size, int)
{
    LOG("bload", filename);

    std::unique_ptr<char[]> buf{new char[size]};
    std::ifstream in{filename, std::ios::binary};
    if (!in)
    {
        LOG("Failed");
        throw 0;
    }
    size = in.readsome(buf.get(), size);
    data = *reinterpret_cast<int*>(buf.get());
}

void bload(const fs::path& filename, elona_vector1<int>& data, int size, int)
{
    LOG("bload", filename);

    if (size == 0)
    {
        size = data.size() * sizeof(int);
    }
    std::unique_ptr<char[]> buf{new char[size]};
    std::ifstream in{filename, std::ios::binary};
    if (!in)
    {
        LOG("Failed");
        throw 0;
    }
    size = in.readsome(buf.get(), size);
    for (int i = 0; i < length(data); ++i)
    {
        data(i) = reinterpret_cast<int*>(buf.get())[i];
        size -= sizeof(int);
        if (size == 0)
            return;
    }
}


void bsave(const fs::path& filename, const std::string& data)
{
    LOG("bsave", filename);

    std::ofstream out{filename, std::ios::binary};
    if (!out)
    {
        LOG("Failed");
        throw 0;
    }
    out.write(reinterpret_cast<const char*>(data.c_str()), std::size(data));
}


void bsave(const fs::path& filename, int data)
{
    LOG("bsave", filename);

    std::ofstream out{filename, std::ios::binary};
    out.write(reinterpret_cast<const char*>(&data), sizeof(data));
}


void bsave(const fs::path& filename, elona_vector1<int>& data)
{
    LOG("bsave", filename);

    std::ofstream out{filename, std::ios::binary};
    for (int i = 0; i < std::size(data); ++i)
    {
        out.write(reinterpret_cast<const char*>(&data(i)), sizeof(int));
    }
}


void buffer(int window_id, int width, int height)
{
    LOG("buffer", window_id, width, height);
    if (window_id >= std::size(detail::tex_buffers))
    {
        detail::tex_buffers.resize(window_id + 1);
    }
    if (auto texture = detail::tex_buffers[window_id].texture)
    {
        int img_width;
        int img_height;
        snail::detail::enforce_sdl(
            ::SDL_QueryTexture(texture, NULL, NULL, &img_width, &img_height));
        if (width == img_width && height == img_height)
        {
            gsel(window_id);
            Application::instance().renderer().clear();
            return;
        }
        else
        {
            ::SDL_DestroyTexture(detail::tex_buffers[window_id].texture);
        }
    }
    detail::tex_buffers[window_id] = {
        snail::detail::enforce_sdl(::SDL_CreateTexture(
            Application::instance().renderer().ptr(),
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_TARGET,
            width,
            height)),
        width,
        height,
    };

    Application::instance().register_finalizer(
        [ptr = detail::tex_buffers[window_id].texture]() {
            ::SDL_DestroyTexture(ptr);
        });

    const auto save = Application::instance().renderer().get_render_target();
    Application::instance().renderer().set_render_target(
        detail::tex_buffers[window_id].texture);
    Application::instance().renderer().set_draw_color({0, 0, 0, 0});
    Application::instance().renderer().clear();
    Application::instance().renderer().set_render_target(save);

    gsel(window_id);
}

void chgdisp(int, int width, int height)
{
}


void clrobj(int)
{
}


// Shift-JIS -> Unicode
void cnvstow(std::string& out, const std::string& source)
{
    out = source;
}

void color(int r, int g)
{
    color(r, g, 0);
}

void color(int r, int g, int b)
{
    detail::current_tex_buffer().color = {
        static_cast<uint8_t>(std::clamp(r, 0, 255)),
        static_cast<uint8_t>(std::clamp(g, 0, 255)),
        static_cast<uint8_t>(std::clamp(b, 0, 255)),
        detail::current_tex_buffer().color.a,
    };
    Application::instance().renderer().set_draw_color(
        detail::current_tex_buffer().color);
}

void color(int v)
{
    color(v, 0, 0);
}



void delcom(int)
{
}

void elona_delete(const fs::path& filename)
{
    LOG("delete", filename);
    fs::remove_all(filename);
}

int dialog(const std::string& message, int)
{
    return 0;
}

// TODO
std::string dirinfo(int n)
{
    return ".";
    // switch (n)
    // {
    // case 0:
    //     return "dir_cur";
    // case 1:
    //     return "dir_exe";
    // case 2:
    //     return "dir_win";
    // case 3:
    //     return "dir_sys";
    // case 4:
    //     return "dir_cmdline";
    // default:
    //     assert(0);
    // }
}


double elona_double(const std::string& s)
{
    return std::stod(s);
}

double elona_double(int n)
{
    return static_cast<double>(n);
}


void exec(const std::string&, int)
{
}


void exist(const fs::path& filename)
{
    if (fs::exists(filename) && !fs::is_directory(filename))
    {
        strsize = fs::file_size(filename);
    }
    else
    {
        strsize = -1;
    }
}


double expf(double x)
{
    return std::exp(x);
}


namespace font_detail
{
std::unordered_map<int, Font> font_cache;
}

void font(const std::string& name, int size, int style)
{
    if (auto i = font_detail::font_cache.find(size);
        i != std::end(font_detail::font_cache))
    {
        Application::instance().renderer().set_font(i->second);
    }
    else
    {
        const auto [i_, _] = font_detail::font_cache.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(size),
            std::forward_as_tuple(
                "font/APJapanesefontT.ttf", size, Font::Style::regular));
        Application::instance().renderer().set_font(i_->second);
    }
}

void gcopy(int window_id, int src_x, int src_y, int src_width, int src_height)
{
    detail::set_blend_mode();
    snail::detail::enforce_sdl(::SDL_SetTextureAlphaMod(
        detail::tex_buffers[window_id].texture,
        detail::current_tex_buffer().color.a));

    if (window_id == detail::current_buffer)
    {
        src_width =
            src_width == 0 ? detail::current_tex_buffer().width : src_width,
        src_height =
            src_height == 0 ? detail::current_tex_buffer().height : src_height,
        Application::instance().renderer().set_render_target(
            detail::tmp_buffer);
        if (window_id < 10)
        {
            Application::instance().renderer().set_blend_mode(BlendMode::none);
            Application::instance().renderer().set_draw_color({0, 0, 0, 0});
        }
        else
        {
            const auto save = Application::instance().renderer().blend_mode();
            Application::instance().renderer().set_blend_mode(BlendMode::none);
            Application::instance().renderer().set_draw_color({0, 0, 0, 0});
            Application::instance().renderer().set_blend_mode(save);
        }
        Application::instance().renderer().clear();
        Application::instance().renderer().render_image(
            detail::tex_buffers[window_id].texture,
            src_x,
            src_y,
            src_width,
            src_height,
            0,
            0);
        gsel(window_id);
        Application::instance().renderer().render_image(
            detail::tmp_buffer,
            0,
            0,
            src_width,
            src_height,
            detail::current_tex_buffer().x,
            detail::current_tex_buffer().y);
        return;
    }

    Application::instance().renderer().render_image(
        detail::tex_buffers[window_id].texture,
        src_x,
        src_y,
        src_width == 0 ? detail::current_tex_buffer().width : src_width,
        src_height == 0 ? detail::current_tex_buffer().height : src_height,
        detail::current_tex_buffer().x,
        detail::current_tex_buffer().y);
}

void getkey(int& out, int key)
{
    out = Keyboard::instance().is_pressed(hspkey2snailkey(key));
}

void getstr(
    std::string& out,
    const std::string& source,
    int offset,
    char delimiter,
    int limit)
{
    auto pos = source.find(delimiter, offset);
    if (pos == std::string::npos)
    {
        pos = source.find('\n', offset);
    }
    if (pos == std::string::npos)
    {
        pos = std::size(source);
    }
    if (pos >= offset)
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

int ginfo(int type)
{
    switch (type)
    {
    case 0: return 0; // mouse x
    case 1: return 0; // mouse y
    case 2: return 0; // active window id
    case 3: return detail::current_buffer; // target window id
    case 4: return 0; // window x1
    case 5: return 0; // window y1
    case 6: return 800; // window x2
    case 7: return 600; // window y2
    case 8: return 0; // window scroll x
    case 9: return 0; // window scroll y
    case 10: return 800; // window width
    case 11: return 600; // window height
    case 12:
        return detail::current_tex_buffer().tex_width; // window client width
    case 13:
        return detail::current_tex_buffer().tex_height; // window client height
    case 14: return 0; // font width
    case 15: return 0; // font height
    case 16: return detail::current_tex_buffer().color.r; // current color r
    case 17: return detail::current_tex_buffer().color.g; // current color g
    case 18: return detail::current_tex_buffer().color.b; // current color b
    case 19: return 0; // color mode
    case 20: return 0; // resolution x
    case 21: return 0; // resolution y
    case 22: return detail::current_tex_buffer().x; // current position x
    case 23: return detail::current_tex_buffer().y; // current position y
    default: assert(0);
    }
}


void gmode(int mode, int width, int height, int alpha)
{
    detail::current_tex_buffer().mode = mode;
    detail::set_blend_mode();

    detail::current_tex_buffer().width = width;
    detail::current_tex_buffer().height = height;
    detail::current_tex_buffer().color.a = std::clamp(alpha, 0, 255);
}

template <typename T>
constexpr T rad2deg(T rad)
{
    return rad * 180.0 / 3.14159265358979323846264;
}

void grotate2(
    int window_id,
    int src_x,
    int src_y,
    double angle,
    int dst_width,
    int dst_height)
{
    detail::set_blend_mode();
    snail::detail::enforce_sdl(::SDL_SetTextureAlphaMod(
        detail::tex_buffers[window_id].texture,
        detail::current_tex_buffer().color.a));

    if (window_id == detail::current_buffer)
    {
        assert(0);
    }

    ::SDL_Rect src_rect{
        src_x,
        src_y,
        detail::current_tex_buffer().width == -1
            ? dst_width
            : detail::current_tex_buffer().width,
        detail::current_tex_buffer().height == -1
            ? dst_height
            : detail::current_tex_buffer().height,
    };
    ::SDL_Rect dst_rect{
        detail::current_tex_buffer().x - dst_width / 2,
        detail::current_tex_buffer().y - dst_height / 2,
        dst_width,
        dst_height,
    };

    switch (Application::instance().renderer().blend_mode())
    {
    case BlendMode::none:
        snail::detail::enforce_sdl(::SDL_SetTextureBlendMode(
            detail::tex_buffers[window_id].texture, ::SDL_BLENDMODE_NONE));
        break;
    case BlendMode::blend:
        snail::detail::enforce_sdl(::SDL_SetTextureBlendMode(
            detail::tex_buffers[window_id].texture, ::SDL_BLENDMODE_BLEND));
        break;
    case BlendMode::add:
        snail::detail::enforce_sdl(::SDL_SetTextureBlendMode(
            detail::tex_buffers[window_id].texture, ::SDL_BLENDMODE_ADD));
        break;
    }
    snail::detail::enforce_sdl(::SDL_RenderCopyEx(
        Application::instance().renderer().ptr(),
        detail::tex_buffers[window_id].texture,
        &src_rect,
        &dst_rect,
        rad2deg(angle),
        nullptr,
        ::SDL_FLIP_NONE));
}

void grotate(
    int window_id,
    int src_x,
    int src_y,
    double angle,
    int dst_width,
    int dst_height)
{
    if (angle != 0)
    {
        grotate2(window_id, src_x, src_y, angle, dst_width, dst_height);
        return;
    }

    detail::set_blend_mode();
    snail::detail::enforce_sdl(::SDL_SetTextureAlphaMod(
        detail::tex_buffers[window_id].texture,
        detail::current_tex_buffer().color.a));

    if (window_id == detail::current_buffer)
    {
        Application::instance().renderer().set_render_target(
            detail::tmp_buffer);
        if (window_id < 10)
        {
            Application::instance().renderer().set_blend_mode(BlendMode::none);
            Application::instance().renderer().set_draw_color({0, 0, 0, 0});
        }
        else
        {
            const auto save = Application::instance().renderer().blend_mode();
            Application::instance().renderer().set_blend_mode(BlendMode::none);
            Application::instance().renderer().set_draw_color({0, 0, 0, 0});
            Application::instance().renderer().set_blend_mode(save);
        }
        Application::instance().renderer().clear();
        Application::instance().renderer().render_image(
            detail::tex_buffers[window_id].texture,
            src_x,
            src_y,
            detail::current_tex_buffer().width == -1
                ? dst_width
                : detail::current_tex_buffer().width,
            detail::current_tex_buffer().height == -1
                ? dst_height
                : detail::current_tex_buffer().height,
            0,
            0,
            dst_width,
            dst_height);

        gsel(window_id);
        Application::instance().renderer().render_image(
            detail::tmp_buffer,
            0,
            0,
            dst_width,
            dst_height,
            detail::current_tex_buffer().x - dst_width / 2,
            detail::current_tex_buffer().y - dst_height / 2);
        return;
    }

    Application::instance().renderer().render_image(
        detail::tex_buffers[window_id].texture,
        src_x,
        src_y,
        detail::current_tex_buffer().width == -1
            ? dst_width
            : detail::current_tex_buffer().width,
        detail::current_tex_buffer().height == -1
            ? dst_height
            : detail::current_tex_buffer().height,
        detail::current_tex_buffer().x - dst_width / 2,
        detail::current_tex_buffer().y - dst_height / 2,
        dst_width,
        dst_height);
}

void gsel(int window_id)
{
    detail::current_buffer = window_id;
    Application::instance().renderer().set_render_target(
        detail::current_tex_buffer().texture);
}

void gzoom(
    int dst_width,
    int dst_height,
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int mode)
{
    Application::instance().renderer().set_blend_mode(BlendMode::none);
    snail::detail::enforce_sdl(
        ::SDL_SetTextureAlphaMod(detail::tex_buffers[window_id].texture, 255));

    if (window_id == detail::current_buffer)
    {
        Application::instance().renderer().set_render_target(
            detail::tmp_buffer);
        if (window_id < 10)
        {
            Application::instance().renderer().set_blend_mode(BlendMode::none);
            Application::instance().renderer().set_draw_color({0, 0, 0, 0});
        }
        else
        {
            const auto save = Application::instance().renderer().blend_mode();
            Application::instance().renderer().set_blend_mode(BlendMode::none);
            Application::instance().renderer().set_draw_color({0, 0, 0, 0});
            Application::instance().renderer().set_blend_mode(save);
        }
        Application::instance().renderer().clear();
        Application::instance().renderer().render_image(
            detail::tex_buffers[window_id].texture,
            src_x,
            src_y,
            src_width,
            src_height,
            0,
            0,
            dst_width,
            dst_height);
        gsel(window_id);
        Application::instance().renderer().render_image(
            detail::tmp_buffer,
            0,
            0,
            dst_width,
            dst_height,
            detail::current_tex_buffer().x,
            detail::current_tex_buffer().y);
        return;
    }

    Application::instance().renderer().render_image(
        detail::tex_buffers[window_id].texture,
        src_x,
        src_y,
        src_width,
        src_height,
        detail::current_tex_buffer().x,
        detail::current_tex_buffer().y,
        dst_width,
        dst_height);
}


int instr(const std::string& str, size_t pos, const std::string pattern)
{
    if (pattern == "\n")
    {
        return instr(str, pos, "\r");
    }
    const auto ret = str.find(pattern, pos);
    return ret == std::string::npos ? -1 : static_cast<int>(ret - pos);
}

int elona_int(double x)
{
    return static_cast<int>(x);
}

int elona_int(const std::string& s)
{
    try
    {
        return std::stoi(s);
    }
    catch (...)
    {
        return 0;
    }
}



size_t length(const std::string& str)
{
    return std::size(str);
}


int limit(int x, int min, int max)
{
    return std::clamp(x, min, max);
}

void line(int x1, int y1, int x2, int y2)
{
    Application::instance().renderer().render_line(x1, y1, x2, y2);
}

void line(int x, int y)
{
    line(detail::current_tex_buffer().x, detail::current_tex_buffer().y, x, y);
    detail::current_tex_buffer().x = x;
    detail::current_tex_buffer().y = y;
}



double logf(double x)
{
    return std::log(x);
}



void memcpy(
    elona_vector2<int>& src,
    int src_i,
    int src_j,
    elona_vector2<int>& dst,
    int dst_i,
    int dst_j,
    size_t size)
{
    const auto len = length(src);
    const auto len2 = length2(src);
    auto count = size;
    for (int i = 0; i < len2; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            src(src_j + j, src_i + i) = dst(dst_j + j, dst_i + i);
            count -= sizeof(int);
            if (count == 0)
                return;
        }
    }
}


// void memexpand(void* memory, size_t size)
// {
// }

// void memfile(void* buf)
// {
// }


void mes(const std::string& text)
{
    if (std::size(text) >= 25 /* TODO */)
    {
        Application::instance().renderer().render_multiline_text(
            text,
            detail::current_tex_buffer().x,
            detail::current_tex_buffer().y,
            detail::current_tex_buffer().color);
    }
    else
    {
        Application::instance().renderer().render_text(
            text,
            detail::current_tex_buffer().x,
            detail::current_tex_buffer().y,
            detail::current_tex_buffer().color);
    }
}

void mes(int n)
{
    mes(std::to_string(n));
}

void mesbox(
    std::string& buffer,
    int width,
    int height,
    int style,
    int max_input_size)
{
    mesbox_detail::message_boxes.emplace_back(
        std::make_unique<mesbox_detail::MessageBox>(buffer));
}

void mkdir(const fs::path& path)
{
    LOG("mkdir", path);
    fs::create_directory(path);
}

void mmload(const std::string& file, int id, int mode)
{
}

void mmplay(int id)
{
}

void mmstop()
{
}


// // Special function
// void mref()
// {
// }



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
    return std::size(split_lines(str));
}


struct io_error : public std::runtime_error
{
    io_error(const std::string& message)
        : std::runtime_error(message)
    {
    }
};


} // namespace notemanip


void noteadd(const std::string& text, int index, int overwrite)
{
    assert(overwrite == 0 || overwrite == 1);

    if (!notemanip::buffer)
        return;

    auto lines = notemanip::split_lines(*notemanip::buffer);

    if (index == -1)
    {
        index = std::size(lines);
    }

    if (index >= std::size(lines))
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


void notedel(size_t index)
{
    if (!notemanip::buffer)
        return;

    const auto lines = notemanip::split_lines(*notemanip::buffer);
    notemanip::buffer->clear();
    for (int i = 0; i < std::size(lines); ++i)
    {
        if (i != index)
        {
            *notemanip::buffer += lines[i] + '\n';
        }
    }
}

void noteget(std::string& out, size_t index)
{
    if (!notemanip::buffer)
    {
        out = "";
        return;
    }

    const auto lines = notemanip::split_lines(*notemanip::buffer);
    if (index >= std::size(lines))
    {
        out = "";
    }
    else
    {
        out = lines[index];
    }
}

int noteinfo(int mode)
{
    assert(mode == 0);
    return notemanip::buffer ? notemanip::count(*notemanip::buffer) : 0;
}

void noteload(const fs::path& filename)
{
    LOG("noteload", filename);

    std::ifstream in{filename};
    if (!in)
        throw notemanip::io_error{u8"Not found "s + filename.u8string()};

    std::string str;
    notemanip::buffer->clear();
    while (std::getline(in, str))
    {
        *notemanip::buffer += str + '\n';
    }
}

void notesave(const fs::path& filename)
{
    LOG("notesave", filename);

    if (!notemanip::buffer)
        return;

    std::ofstream out{filename};
    if (!out)
        throw notemanip::io_error{u8"Cannot open "s + filename.u8string()};

    out << *notemanip::buffer;
}

int notesel(std::string& buf)
{
    notemanip::buffer = &buf;
    return noteinfo(0);
}

void noteunsel()
{
    notemanip::buffer = nullptr;
}



void objmode(int, int)
{
}

void objprm(int, const std::string&)
{
}

void objsel(int)
{
}


// Peek 1byte.
std::uint8_t peek(const std::string& str, size_t index)
{
    return str[index];
}

std::uint8_t peek(elona_vector1<int> v, size_t index)
{
    return v(index);
}



void pget(int x, int y)
{
}

void picload(const fs::path& filename, int mode)
{
    try
    {
        std::optional<Color> keycolor = Color{0, 0, 0};
        if (filename.u8string().find("pcc") != std::string::npos)
        {
            keycolor = {43, 133, 133};
        }
        if (filename.u8string().find("bg") != std::string::npos)
        {
            keycolor = std::nullopt;
        }
        BasicImage img{filename, keycolor};
        if (mode == 0)
        {
            buffer(detail::current_buffer, img.width(), img.height());
            LOG("picload 0", filename);
        }
        else
        {
            LOG("picload 1", filename);
        }
        const auto save = Application::instance().renderer().blend_mode();
        Application::instance().renderer().set_blend_mode(BlendMode::none);
        Application::instance().renderer().render_image(
            img,
            detail::current_tex_buffer().x,
            detail::current_tex_buffer().y);
        Application::instance().renderer().set_blend_mode(save);
    }
    catch (...)
    {
        LOG("picload", "Failed to load", filename);
    }
}

void poke(std::string& str, size_t index, char c)
{
    str[index] = c;
}

void poke(std::string& str, size_t index, const std::string& s)
{
    poke(str, index, s[0]);
}

void pos(int x, int y)
{
    detail::current_tex_buffer().x = x;
    detail::current_tex_buffer().y = y;
}


namespace rnd_detail
{
std::mt19937 random_engine{std::random_device{}()};
// For exrand
std::mt19937 random_engine2{std::random_device{}()};

} // namespace rnd_detail


void randomize(std::random_device::result_type seed)
{
    rnd_detail::random_engine.seed(seed);
}

int rnd(int n)
{
    std::uniform_int_distribution<> dist{0,
                                         std::clamp(n - 1, 0, (1 << 16) - 1)};
    return dist(rnd_detail::random_engine);
}



void redraw(int n)
{
    if (n != 1)
        return;
    const auto save = Application::instance().renderer().get_render_target();
    Application::instance().renderer().set_render_target(nullptr);
    Application::instance().renderer().set_draw_color(Color{0, 0, 0, 255});
    Application::instance().renderer().clear();
    Application::instance().renderer().render_image(
        detail::tex_buffers[0].texture, 0, 0);
    Application::instance().renderer().present();
    Application::instance().renderer().set_render_target(save);
}

void screen(int window_id, int width, int height, int mode, int x, int y)
{
}

double sqrt(double x)
{
    return std::sqrt(x);
}

void stick(int& out, int allow_repeat_keys)
{
    auto check_key_pressed = [allow_repeat_keys](
                                 int n, Key key, bool is_modifier) {
        if ((1 << n) & allow_repeat_keys)
        {
            if (is_modifier)
                return (1 << n) * Keyboard::instance().is_pressed_exactly(key);
            else
                return (1 << n) * Keyboard::instance().is_pressed(key);
        }
        else
        {
            return (1 << n) * Keyboard::instance().was_pressed_just_now(key);
        }
    };

    out = 0;

    out += check_key_pressed(0, Key::left, false);
    out += check_key_pressed(1, Key::up, false);
    out += check_key_pressed(2, Key::right, false);
    out += check_key_pressed(3, Key::down, false);
    out += check_key_pressed(4, Key::space, false);
    out += check_key_pressed(5, Key::enter, false);
    out += check_key_pressed(6, Key::ctrl, true);
    out += check_key_pressed(7, Key::escape, false);
    // out += check_key_pressed(8,  /* Mouse left */,  false);
    // out += check_key_pressed(9,  /* Mouse right */, false);
    out += check_key_pressed(10, Key::tab, false);
}


std::string elona_str(int n)
{
    return std::to_string(n);
}


size_t strlen_u(const std::string& str)
{
    int ret = 0;
    for (int i = 0; i < std::size(str);)
    {
        const auto byte = byte_count(static_cast<uint8_t>(str[i]));
        ret += byte == 1 ? 1 : 2;
        i += byte;
    }
    return ret;
}

std::string strmid(const std::string& source, int pos, int length)
{
    const auto src_len = std::size(source);
    if (pos == -1)
    {
        // n characters from right to left.
        length = std::min(static_cast<decltype(src_len)>(length), src_len);
        return source.substr(src_len - length, length);
    }
    else if (pos >= src_len)
    {
        return "";
    }
    else if (pos + length >= src_len)
    {
        return source.substr(pos, std::string::npos);
    }
    else
    {
        return source.substr(pos, length);
    }
}

void title(const std::string& title_str)
{
    LOG("SDL_Init");
    Application::instance().initialize(800, 600, title_str);
    detail::tmp_buffer = snail::detail::enforce_sdl(::SDL_CreateTexture(
        Application::instance().renderer().ptr(),
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_TARGET,
        1000,
        1000));
    Application::instance().register_finalizer(
        []() { ::SDL_DestroyTexture(detail::tmp_buffer); });
    Keyboard::instance().set_key_repeat(5, 0);
    Application::instance().register_finalizer(
        [&]() { font_detail::font_cache.clear(); });
    buffer(0, 800, 600);
}

// // Special function
// void varptr()
// {
// }

void width(int width, int height, int, int)
{
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



// imported functions


void exrand_randomize(std::random_device::result_type seed)
{
    rnd_detail::random_engine2.seed(seed);
}

void exrand_rnd(int& result, int max)
{
    if (max <= 0)
    {
        result = 0;
    }
    else
    {
        result = std::uniform_int_distribution<>{
            0, max - 1}(rnd_detail::random_engine2);
    }
}

void func_1(const std::string&, int)
{
}

void xnotesel(std::string&)
{
}


void xnoteadd(const std::string&)
{
}



// FIXME:
// The texture which created with SDL_TEXTUREACCESS_TARGET cannot be
// locked/unlocked.
namespace gf_detail
{
::SDL_Rect rect;
void* pixels;
int pitch;


template <typename F>
void map(F f)
{
    // const auto texture =
    // Application::instance().renderer().get_render_target(); const auto format
    // = snail::detail::enforce_sdl(
    //         ::SDL_AllocFormat(::SDL_MasksToPixelFormatEnum(32, 0, 0, 0, 0)));
    //
    // auto pixels = reinterpret_cast<uint32_t*>(gf_detail::pixels);
    // int pixel_count = gf_detail::pitch / 4 * gf_detail::rect.h;
    //
    // for (int i = 0; i < pixel_count; ++i)
    // {
    //     uint8_t r_;
    //     uint8_t g_;
    //     uint8_t b_;
    //     ::SDL_GetRGB(pixels[i], format, &r_, &g_, &b_);
    //     pixels[i] = ::SDL_MapRGB(format, f(r_, r), f(g_, r), f(b_, r));
    // }
    //
    // ::SDL_UnlockTexture(texture);
}

} // namespace gf_detail

void gfini(int width, int height)
{
    // gf_detail::rect = {detail::current_tex_buffer().x,
    // detail::current_tex_buffer().y, width, height}; const auto texture =
    // Application::instance().renderer().get_render_target();
    // ::SDL_LockTexture(texture, &gf_detail::rect, &gf_detail::pixels,
    // &gf_detail::pitch); LOG("gfini", gf_detail::pitch, gf_detail::rect.h);
}

void gfdec(int r, int g, int b)
{
    // gf_detail::map([](uint8_t v_, int v)
    //     {
    //         v = std::min(v, static_cast<int>(v_));
    //         v_ -= v;
    //         return v_;
    //     });
}

void gfdec2(int r, int g, int b)
{
    // gf_detail::map([](uint8_t v_, int v)
    //     {
    //         v = std::min(v, static_cast<int>(v_) - 1);
    //         v_ -= v;
    //         return v_;
    //     });
}

void gfinc(int r, int g, int b)
{
    // gf_detail::map([](uint8_t v_, int v)
    //     {
    //         v = std::min(v, 255 - static_cast<int>(v_));
    //         v_ -= v;
    //         return v_;
    //     });
}

void ematan(int, int, int)
{
}


int aplsel(const std::string&)
{
    return 0;
}

int aplobj(const std::string&, int)
{
    return 0;
}

void apledit(int, int, int)
{
}

void func_2(int, int, int, int, int, int)
{
}


namespace gzip_detail
{
std::fstream file;
}



void memcpy_(
    std::string& dst,
    std::string& src,
    int size,
    int dst_offset,
    int src_offset)
{
    for (int i = 0; i < size; ++i)
    {
        dst[i + dst_offset] = src[i + src_offset];
    }
}



void zOpen(int&, const fs::path& filename, int mode, int)
{
    if (mode == 1) // Write
    {
        LOG("zOpen/w", filename);
        gzip_detail::file.open(filename, std::ios::out | std::ios::binary);
    }
    else // Read
    {
        LOG("zOpen/r", filename);
        gzip_detail::file.open(filename, std::ios::in | std::ios::binary);
    }
    if (!gzip_detail::file)
    {
        LOG("Failed");
        throw 0;
    }
}



void zWrite(elona_vector1<int>& data, int, int size)
{
    LOG("zWrite", size);

    for (int i = 0; i < length(data); ++i)
    {
        gzip_detail::file.write(
            reinterpret_cast<const char*>(&data(i)), sizeof(int));
        size -= sizeof(int);
        if (size == 0)
            return;
    }
}


void zWrite(elona_vector2<int>& data, int, int size)
{
    LOG("zWrite", size);

    for (int j = 0; j < data.j_size(); ++j)
    {
        for (int i = 0; i < data.i_size(); ++i)
        {
            gzip_detail::file.write(
                reinterpret_cast<const char*>(&data(i, j)), sizeof(int));
            size -= sizeof(int);
            if (size == 0)
                return;
        }
    }
}


void zWrite(elona_vector2<int>& data, int, int size, int offset)
{
    LOG("zWrite", size);

    for (int j = offset; j < data.j_size(); ++j)
    {
        for (int i = 0; i < data.i_size(); ++i)
        {
            gzip_detail::file.write(
                reinterpret_cast<const char*>(&data(i, j)), sizeof(int));
            size -= sizeof(int);
            if (size == 0)
                return;
        }
    }
}


void zWrite(elona_vector3<int>& data, int, int size)
{
    LOG("zWrite", size);

    for (int k = 0; k < data.k_size(); ++k)
    {
        for (int j = 0; j < data.j_size(); ++j)
        {
            for (int i = 0; i < data.i_size(); ++i)
            {
                gzip_detail::file.write(
                    reinterpret_cast<const char*>(&data(i, j, k)), sizeof(int));
                size -= sizeof(int);
                if (size == 0)
                    return;
            }
        }
    }
}


void zWrite(elona_vector1<std::string>& data, int, int size)
{
    LOG("zWrite", size);

    for (int i = 0; i < length(data); ++i)
    {
        gzip_detail::file.write(
            reinterpret_cast<const char*>(data(i).c_str()), std::size(data(i)));
        size -= std::size(data(i)) * sizeof(char);
        if (size == 0)
            return;
    }
}



void zRead(elona_vector1<int>& data, int, int size)
{
    LOG("zRead", size);

    std::unique_ptr<char[]> buf{new char[size]};
    size = gzip_detail::file.readsome(buf.get(), size);
    for (int i = 0; i < length(data); ++i)
    {
        data(i) = reinterpret_cast<int*>(buf.get())[i];
        size -= sizeof(int);
        if (size == 0)
            return;
    }
}


void zRead(elona_vector2<int>& data, int, int size)
{
    LOG("zRead/int[][]", size, data.j_size(), data.i_size());
    std::unique_ptr<char[]> buf{new char[size]};
    size = gzip_detail::file.readsome(buf.get(), size);
    for (int j = 0; j < data.j_size(); ++j)
    {
        for (int i = 0; i < data.i_size(); ++i)
        {
            data(i, j) =
                reinterpret_cast<int*>(buf.get())[i + j * data.i_size()];
            size -= sizeof(int);
            if (size == 0)
                return;
        }
    }
}


void zRead(elona_vector2<int>& data, int, int size, int offset)
{
    LOG("zRead/int[][]", size, data.j_size(), data.i_size(), offset);

    std::unique_ptr<char[]> buf{new char[size]};
    size = gzip_detail::file.readsome(buf.get(), size);
    for (int j = offset; j < data.j_size(); ++j)
    {
        for (int i = 0; i < data.i_size(); ++i)
        {
            data(i, j) = reinterpret_cast<int*>(
                buf.get())[i + (j - offset) * data.i_size()];
            size -= sizeof(int);
            if (size == 0)
                return;
        }
    }
}


void zRead(elona_vector3<int>& data, int, int size)
{
    LOG("zRead", size);

    std::unique_ptr<char[]> buf{new char[size]};
    size = gzip_detail::file.readsome(buf.get(), size);
    for (int k = 0; k < data.k_size(); ++k)
    {
        for (int j = 0; j < data.j_size(); ++j)
        {
            for (int i = 0; i < data.i_size(); ++i)
            {
                data(i, j, k) = reinterpret_cast<int*>(buf.get())
                    [i + j * data.i_size() + k * data.i_size() * data.j_size()];
                size -= sizeof(int);
                if (size == 0)
                    return;
            }
        }
    }
}


void zRead(elona_vector1<std::string>& data, int, int size)
{
    LOG("zRead", size);

    std::unique_ptr<char[]> buf{new char[size]};
    size = gzip_detail::file.readsome(buf.get(), size);
    data(0) = {buf.get(), static_cast<size_t>(size)};
}



void zClose(int)
{
    LOG("zClose");
    gzip_detail::file.close();
}

void GetOpenFileNameA()
{
}


void GetSaveFileNameA()
{
}

int DSINIT()
{
    return 0;
}

void DSEND()
{
}

void DSRELEASE(int)
{
}


void DSLOADFNAME(const std::string& filename, int id)
{
}

void DSPLAY(int, int)
{
}

void DSSTOP(int)
{
}

void DSSETVOLUME(int, int)
{
}


int DSGETMASTERVOLUME()
{
    return 100;
}

int CHECKPLAY(int id)
{
    return 0;
}

int DMINIT()
{
    return 0;
}

void DMEND()
{
}


void DMLOADFNAME(const std::string&, int)
{
}

void DMPLAY(int, int)
{
}

void DMSTOP()
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

void HMMBITON(int& x, int n)
{
    x |= 1 << n;
}

void HMMBITOFF(int& x, int n)
{
    x &= ~(1 << n);
}

int HMMBITCHECK(int x, int n)
{
    return x & (1 << n) ? 1 : 0;
}


int sockopen(int, const std::string&, int)
{
    return 0;
}

void sockclose()
{
}

int sockget(const std::string&, int)
{
    return 0;
}

int sockput(const std::string&)
{
    return 0;
}

void netinit()
{
}


void netexec(int&)
{
}

void neterror(const std::string&)
{
}

void neturl(const std::string&)
{
}

void netdlname(const std::string&)
{
}

void netrequest(const std::string&)
{
}


void GetLastError()
{
}

int CreateMutexA(int, int, const std::string&)
{
    return 42; // Any positive number.
}


void CloseHandle(int)
{
}

int func_3()
{
    return 0;
}


int LCMapStringA(int, int, const std::string&, int, const std::string&, int)
{
    return 0;
}


int GetUserDefaultLCID()
{
    return 0;
}

void water_getimage()
{
}


void water_setripple(int, int, int, int)
{
}

void water_calc()
{
}

void water_draw()
{
}


void AppendMenuA()
{
}

void CheckMenuRadioItem()
{
}

void CreateMenu()
{
}


void CreatePopupMenu()
{
}

void DrawMenuBar()
{
}

void SetMenu()
{
}


void keybd_event(int, int, int)
{
}

void GetKeyboardState(elona_vector1<int>&)
{
}

void timeBeginPeriod(int)
{
}


void timeEndPeriod()
{
}

int timeGetTime()
{
    return ::SDL_GetTicks();
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



void onkey_0()
{
}


void onkey_1()
{
}


void end()
{
    std::exit(0);
}



int talk_conv_jp(std::string& text, int max_line_length)
{
    max_line_length *= 1.5;

    std::string rest{text};
    text.clear();

    while (1)
    {
        const auto len = std::size(rest);
        if (len < max_line_length)
        {
            text += rest;
            return n;
        }
        size_t line_length = 0;
        while (line_length <= len)
        {
            line_length += byte_count(static_cast<uint8_t>(rest[line_length]));
            if (line_length > max_line_length)
            {
                // m = strmid(rest, line_length, 2);
                // if (false
                //         || m == u8"。"s
                //         || m == u8"、"s
                //         || m == u8"」"s
                //         || m == u8"』"s
                //         || m == u8"！"s
                //         || m == u8"？"s
                //         || m == u8"…"s)
                // {
                //     line_length += 2;
                // }
                text += rest.substr(0, line_length) + '\n';
                ++n;
                if (std::size(rest) > line_length)
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
            if (line_length + p + 1 > max_line_length)
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



void rm_crlf(std::string& str)
{
    std::string ret;
    for (const auto& c : str)
    {
        if (c != '\n' && c != '\r')
        {
            ret += c;
        }
    }
    str = ret;
}


} // namespace elona
