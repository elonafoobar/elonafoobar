#include "pic_loader.hpp"
#include "../elona.hpp"
#include "../hcl.hpp"
#include "../snail/application.hpp"
#include "../snail/color.hpp"

namespace elona
{

namespace
{

static void copy_image(snail::basic_image& img, const extent& ext)
{
    const auto save =
        snail::application::instance().get_renderer().blend_mode();
    snail::application::instance().get_renderer().set_blend_mode(
        snail::blend_mode_t::none);
    snail::application::instance().get_renderer().render_image(
        img, ext.x, ext.y, ext.width, ext.height);
    snail::application::instance().get_renderer().set_blend_mode(save);
}

static void copy_image_cropped(
    snail::basic_image& img,
    const extent& source,
    const extent& dest)
{
    const auto save =
        snail::application::instance().get_renderer().blend_mode();
    snail::application::instance().get_renderer().set_blend_mode(
        snail::blend_mode_t::none);
    snail::application::instance().get_renderer().render_image_crop(
        img, source.x, source.y, source.width, source.height, dest.x, dest.y);
    snail::application::instance().get_renderer().set_blend_mode(save);
}

} // namespace


void pic_loader::clear_storage_and_buffers()
{
    for (const auto& buffer : buffers)
    {
        elona::buffer(buffer.buffer_id, 1, 1);
    }

    buffers.clear();
    storage.clear();
}

void pic_loader::load(
    const fs::path& image_file,
    const id_type& id,
    page_type type)
{
    snail::basic_image img{image_file, snail::color{0, 0, 0}};
    extent ext{0, 0, 0, 0};

    size_t i = 0;
    while (true)
    {
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

        if (i == buffers.size())
        {
            add_buffer(type);
        }
    }

    // Render the sprite to the region of the buffer that was found.
    gsel(ext.buffer);
    pos(ext.x, ext.y);

    copy_image(img, ext);

    // Store the buffer region for later lookup.
    storage[id] = ext;
}

void pic_loader::add_predefined_extents(
    const fs::path& atlas_file,
    const map_type& extents,
    page_type type)
{
    snail::basic_image img{atlas_file, snail::color{0, 0, 0}};

    // Add a new buffer for this atlas. The assumption is that all the
    // defined sprites will fit on this buffer. This assumption might
    // not hold in the degenerate case, but for the atlases used
    // (character.bmp, image.bmp) there is still a good amount of
    // unused space to hold any potential overflow.
    buffer_info& info = add_buffer(type, img.width(), img.height());
    gsel(info.buffer_id);

    for (auto& pair : extents)
    {
        // Get the source loaded from a definition file.
        const extent& source = pair.second;

        assert(source.right() < img.width());
        assert(source.bottom() < img.height());

        // Find a region on a buffer to place the sprite.
        auto found = info.find(source.width, source.height);
        assert(found);

        size_t skyline_index = found->first;
        extent& dest = found->second;
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

pic_loader::buffer_info& pic_loader::add_buffer(page_type type, int w, int h)
{
    int new_buffer_index;
    size_t buffer_info_index = buffers.size();

    assert(buffer_info_index < 10);

    new_buffer_index = 10 + buffer_info_index;
    buffers.emplace_back(type, new_buffer_index, w, h);

    buffer(new_buffer_index, w, h);

    return buffers.at(buffer_info_index);
}

} // namespace elona
