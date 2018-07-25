#pragma once

#include <string>
#include "blend_mode.hpp"
#include "color.hpp"
#include "detail/sdl.hpp"
#include "font.hpp"
#include "image.hpp"
#include "rect.hpp"
#include "size.hpp"
#include "window.hpp"
#include "../lib/noncopyable.hpp"


namespace elona
{
namespace snail
{



class renderer : public lib::noncopyable
{
public:
    enum flag_t
    {
        none = 0,
        software = SDL_RENDERER_SOFTWARE,
        accelerated = SDL_RENDERER_ACCELERATED,
        present_vsync = SDL_RENDERER_PRESENTVSYNC,
        target_texture = SDL_RENDERER_TARGETTEXTURE,
    };


    enum class text_alignment_t
    {
        left,
        center,
        right,
    };


    enum class text_baseline_t
    {
        top,
        middle,
        bottom,
    };

    ~renderer();

    text_alignment_t text_alignment() const noexcept
    {
        return _text_alignment;
    }


    void set_text_alignment(text_alignment_t text_alignment)
    {
        _text_alignment = text_alignment;
    }


    text_baseline_t text_baseline() const noexcept
    {
        return _text_baseline;
    }


    void set_text_baseline(text_baseline_t text_baseline)
    {
        _text_baseline = text_baseline;
    }


    bool has_font()
    {
        return _font.ptr() != nullptr;
    }


    const font_t& font() const noexcept
    {
        return _font;
    }


    void set_font(const font_t& font)
    {
        _font = font;
    }


    blend_mode_t blend_mode() const noexcept
    {
        return _blend_mode;
    }

    void set_blend_mode(blend_mode_t blend_mode);

    void set_draw_color(const color&);

    ::SDL_Texture* render_target();

    void set_render_target(::SDL_Texture* texture);


    ::SDL_Renderer* ptr();


    renderer(window& target_window, int flag);


    void clear();
    void present();
    void render_point(int x, int y);
    void fill_rect(int x, int y, int width, int height);
    rect render_text(
        const std::string& text,
        int x,
        int y,
        const color& text_color = palette::black,
        double scale = 1.0);
    rect render_text_with_shadow(
        const std::string& text,
        int x,
        int y,
        const color& text_color = palette::white,
        const color& shadow_color = palette::black,
        double scale = 1.0);
    rect render_multiline_text(
        const std::string& text,
        int x,
        int y,
        const color& text_color = palette::black);
    size calculate_text_size(const std::string& text);
    void render_line(int start_x, int start_y, int end_x, int end_y);
    void render_image(image_base& image, int dst_x, int dst_y);
    void render_image(
        image_base& image,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height);
    void render_image(
        image_base& image,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y);
    void render_image(
        image_base& image,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height);
    void render_image(::SDL_Texture* image, int dst_x, int dst_y);
    void render_image(
        ::SDL_Texture* image,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height);
    void render_image(
        ::SDL_Texture* image,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y);
    void render_image(
        ::SDL_Texture* image,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height);


    void render_image_crop(
        image_base& image,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y);
    void render_image_crop(
        ::SDL_Texture* image,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y);

private:
    text_alignment_t _text_alignment = text_alignment_t::left;
    text_baseline_t _text_baseline = text_baseline_t::top;
    font_t _font;
    blend_mode_t _blend_mode = blend_mode_t::blend;
};



} // namespace snail
} // namespace elona
