#pragma once

#include <memory>
#include <string>
#include "detail/sdl.hpp"


namespace snail
{
struct Font
{
    enum class Style
    {
        regular = TTF_STYLE_NORMAL,
        bold = TTF_STYLE_BOLD,
        italic = TTF_STYLE_ITALIC,
        underline = TTF_STYLE_UNDERLINE,
        strikeThrough = TTF_STYLE_STRIKETHROUGH,
    };



    const std::string& filepath() const noexcept
    {
        return _filepath;
    }


    int size() const noexcept
    {
        return _size;
    }


    Style style() const noexcept
    {
        return _style;
    }


    ::TTF_Font* ptr() noexcept
    {
        return _ptr.get();
    }


    Font(const std::string& filepath, int size, Style style = Style::regular);
    Font(const Font&) = default;
    Font(Font&&) = default;
    Font& operator=(const Font&) = default;
    Font& operator=(Font&&) = default;


    virtual ~Font() = default;


private:
    std::string _filepath;
    int _size;
    Style _style;
    std::shared_ptr<::TTF_Font> _ptr;
};


} // namespace snail
