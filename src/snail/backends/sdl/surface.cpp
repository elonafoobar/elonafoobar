#include "../../surface.hpp"

#include "../../../util/fileutil.hpp"



namespace elona
{
namespace snail
{

void Surface::save(const fs::path& filepath)
{
    const auto ext = filepath.extension().to_u8string();

    if (ext == ".bmp" || ext == ".BMP")
    {
        detail::enforce_sdl(SDL_SaveBMP(ptr(), filepath.to_u8string().c_str()));
    }
    else if (ext == ".png" || ext == ".PNG")
    {
        detail::enforce_img(IMG_SavePNG(ptr(), filepath.to_u8string().c_str()));
    }
    else if (ext == ".jpg" || ext == ".JPG" || ext == ".jpeg" || ext == ".JPEG")
    {
        detail::enforce_img(
            IMG_SaveJPG(ptr(), filepath.to_u8string().c_str(), 80));
    }
    else if (ext.empty())
    {
        throw std::runtime_error{
            "File extension is required to determine image file format."};
    }
    else
    {
        throw std::runtime_error{"Unknown image file format: " + ext};
    }
}

} // namespace snail
} // namespace elona
