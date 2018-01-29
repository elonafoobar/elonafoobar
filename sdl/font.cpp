#include "font.hpp"
#include <tuple>
#include <unordered_map>

using namespace snail;




Font::Font(const std::string& filepath, int size, Style style)
    : _filepath(filepath)
    , _size(size)
    , _style(style)
    , _ptr(detail::enforce_ttf(::TTF_OpenFont(filepath.c_str(), size)), ::TTF_CloseFont)
{
    ::TTF_SetFontStyle(ptr(), static_cast<int>(style));
}
