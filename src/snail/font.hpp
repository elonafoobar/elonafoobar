#pragma once

#include <memory>
#include <string>
#include "../filesystem.hpp"
#include "detail/sdl.hpp"


namespace elona
{
namespace snail
{


struct font_t
{
    enum class style_t
    {
        regular = TTF_STYLE_NORMAL,
        bold = TTF_STYLE_BOLD,
        italic = TTF_STYLE_ITALIC,
        underline = TTF_STYLE_UNDERLINE,
        strikeThrough = TTF_STYLE_STRIKETHROUGH,
    };


    const fs::path& filepath() const noexcept
    {
        return _filepath;
    }


    int size() const noexcept
    {
        return _size;
    }


    style_t style() const noexcept
    {
        return _style;
    }


    ::TTF_Font* ptr() noexcept
    {
        return _ptr.get();
    }


    font_t() = default;
    font_t(
        const fs::path& filepath,
        int size,
        style_t style = style_t::regular);
    font_t(const font_t&) = default;
    font_t(font_t&&) = default;
    font_t& operator=(const font_t&) = default;
    font_t& operator=(font_t&&) = default;


    virtual ~font_t() = default;


private:
    fs::path _filepath;
    int _size;
    style_t _style;
    std::shared_ptr<::TTF_Font> _ptr;
};



inline font_t::style_t operator|(font_t::style_t lhs, font_t::style_t rhs)
{
    return font_t::style_t(int(lhs) | int(rhs));
}


} // namespace snail
} // namespace elona
