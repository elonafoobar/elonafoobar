#include "font.hpp"
#include <tuple>
#include <unordered_map>


namespace elona
{
namespace snail
{



font_t::font_t(const fs::path& filepath, int size, style_t style)
    : _filepath(filepath)
    , _size(size)
    , _style(style)
    , _ptr(
          detail::enforce_ttf(
              ::TTF_OpenFont(filesystem::to_utf8_path(filepath).c_str(), size)),
          ::TTF_CloseFont)
{
    ::TTF_SetFontStyle(ptr(), static_cast<int>(style));
}



} // namespace snail
} // namespace elona
