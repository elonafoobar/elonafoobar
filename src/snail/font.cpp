#include "font.hpp"
#include <tuple>
#include <unordered_map>


namespace elona
{
namespace snail
{



Font::Font(const fs::path& filepath, int size, Style style)
    : _filepath(filepath)
    , _size(size)
    , _style(style)
    , _ptr(
          detail::enforce_ttf(::TTF_OpenFont(filepath.string().c_str(), size)),
          ::TTF_CloseFont)
{
    ::TTF_SetFontStyle(ptr(), static_cast<int>(style));
}



} // namespace snail
} // namespace elona
