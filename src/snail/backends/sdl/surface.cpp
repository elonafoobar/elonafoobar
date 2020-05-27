#include "../../surface.hpp"

#include "../../../util/fileutil.hpp"



namespace elona
{
namespace snail
{

void Surface::save(const fs::path& filepath)
{
    const auto ext = filepath.extension();

    if (ext == ".bmp" || ext == ".BMP")
    {
        detail::enforce_sdl(
            SDL_SaveBMP(ptr(), filepathutil::to_utf8_path(filepath).c_str()));
    }
    else if (ext == ".png" || ext == ".PNG")
    {
        detail::enforce_img(
            IMG_SavePNG(ptr(), filepathutil::to_utf8_path(filepath).c_str()));
    }
    else if (ext == ".jpg" || ext == ".JPG" || ext == ".jpeg" || ext == ".JPEG")
    {
        detail::enforce_img(IMG_SaveJPG(
            ptr(), filepathutil::to_utf8_path(filepath).c_str(), 80));
    }
    else if (ext.empty())
    {
        throw std::runtime_error{
            "File extension is required to determine image file format."};
    }
    else
    {
        throw std::runtime_error{
            "Unknown image file format: " + filepathutil::to_utf8_path(ext)};
    }
}

} // namespace snail
} // namespace elona
