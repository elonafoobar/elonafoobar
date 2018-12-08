#include "pic_loader.hpp"
#include "../../snail/application.hpp"
#include "../../snail/color.hpp"
#include "../elona.hpp"
#include "../hcl.hpp"

namespace elona
{

namespace
{

static void copy_image(snail::BasicImage& img, const Extent& ext)
{
    const auto save =
        snail::Application::instance().get_renderer().blend_mode();
    snail::Application::instance().get_renderer().set_blend_mode(
        snail::BlendMode::none);
    snail::Application::instance().get_renderer().render_image(
        img, ext.x, ext.y, ext.width, ext.height);
    snail::Application::instance().get_renderer().set_blend_mode(save);
}

static void copy_image_cropped(
    snail::BasicImage& img,
    const Extent& source,
    const Extent& dest)
{
    const auto save =
        snail::Application::instance().get_renderer().blend_mode();
    snail::Application::instance().get_renderer().set_blend_mode(
        snail::BlendMode::none);
    snail::Application::instance().get_renderer().render_image_crop(
        img, source.x, source.y, source.width, source.height, dest.x, dest.y);
    snail::Application::instance().get_renderer().set_blend_mode(save);
}

} // namespace


void PicLoader::clear()
{
    for (const auto& buffer : buffers)
    {
        elona::buffer(buffer.buffer_id, 1, 1);
    }

    buffers.clear();
    storage.clear();
}

void PicLoader::load(
    const fs::path& image_file,
    const IdType& id,
    PageType type)
{
    snail::BasicImage img{image_file, snail::Color{0, 0, 0}};
    Extent ext{0, 0, 0, 0};

    size_t i = 0;
    while (true)
    {
        if (i == buffers.size())
        {
            add_buffer(type);
        }

        auto& info = buffers.at(i);
        i += 1;

        if (info.type != type)
        {
            continue;
        }

        // Try to find an available buffer location to pack this
        // sprite.
        if (auto pair = info.find(img.width(), img.height()))
        {
            size_t skyline_index = pair->first;
            ext = pair->second;
            ext.buffer = info.buffer_id;

            // Update the sprite packing information.
            info.insert_extent(skyline_index, ext);

            break;
        }
    }

    // Render the sprite to the region of the buffer that was found.
    gsel(ext.buffer);
    pos(ext.x, ext.y);

    copy_image(img, ext);

    // Store the buffer region for later lookup.
    storage[id] = ext;
}

void PicLoader::add_predefined_extents(
    const fs::path& atlas_file,
    const MapType& extents,
    PageType type)
{
    snail::BasicImage img{atlas_file, snail::Color{0, 0, 0}};

    // Add a new buffer for this atlas. The assumption is that all the
    // defined sprites will fit on this buffer. This assumption might
    // not hold in the degenerate case, but for the atlases used
    // (character.bmp, image.bmp) there is still a good amount of
    // unused space to hold any potential overflow.
    BufferInfo& info = add_buffer(type, img.width(), img.height());
    gsel(info.buffer_id);

    for (auto& pair : extents)
    {
        // Get the source loaded from a definition file.
        const Extent& source = pair.second;

        assert(source.right() < img.width());
        assert(source.bottom() < img.height());

        // Find a region on a buffer to place the sprite.
        auto found = info.find(source.width, source.height);
        assert(found);

        size_t skyline_index = found->first;
        Extent& dest = found->second;
        dest.buffer = info.buffer_id;
        dest.frame_width = source.frame_width;

        // Update the sprite packing information.
        info.insert_extent(skyline_index, dest);

        // Render the defined portion of the image onto the buffer.
        copy_image_cropped(img, source, dest);

        // Store the buffer region for later lookup.
        storage[pair.first] = dest;
    }
}

PicLoader::BufferInfo& PicLoader::add_buffer(PageType type, int w, int h)
{
    int new_buffer_index;
    size_t buffer_info_index = buffers.size();

    assert(buffer_info_index < 10);

    new_buffer_index = 10 + buffer_info_index;
    buffers.emplace_back(type, new_buffer_index, w, h);

    buffer(new_buffer_index, w, h);

    return buffers.back();
}

} // namespace elona
