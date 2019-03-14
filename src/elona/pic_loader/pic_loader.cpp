#include "pic_loader.hpp"
#include "../../snail/application.hpp"
#include "../../snail/color.hpp"
#include "../elona.hpp"
#include "../hcl.hpp"



namespace
{

constexpr int _displayed_portrait_width = 80;
constexpr int _displayed_portrait_height = 112;
constexpr int _portrait_grid_column = 16;
constexpr int _portrait_grid_row = 8;



static void copy_image(snail::Image& img, const Extent& ext)
{
    const auto save =
        snail::Application::instance().get_renderer().blend_mode();
    snail::Application::instance().get_renderer().set_blend_mode(
        snail::BlendMode::none);
    snail::Application::instance().get_renderer().render_image(
        img, ext.x, ext.y, ext.width, ext.height);
    snail::Application::instance().get_renderer().set_blend_mode(save);
}



static void
copy_image_cropped(snail::Image& img, const Extent& source, const Extent& dest)
{
    const auto save =
        snail::Application::instance().get_renderer().blend_mode();
    snail::Application::instance().get_renderer().set_blend_mode(
        snail::BlendMode::none);
    snail::Application::instance().get_renderer().render_image_crop(
        img, source.x, source.y, source.width, source.height, dest.x, dest.y);
    snail::Application::instance().get_renderer().set_blend_mode(save);
}



// FIXME: refactor this dirty hack.
static void
copy_image_portrait(snail::Image& img, const Extent& source, const Extent& dest)
{
    auto& renderer = snail::Application::instance().get_renderer();
    const auto save = renderer.blend_mode();

    boxf(dest.x, dest.y, dest.width, dest.height, snail::Color{0, 0, 0});
    renderer.set_blend_mode(snail::BlendMode::blend);
    renderer.render_image(
        img,
        source.x,
        source.y,
        source.width,
        source.height,
        dest.x,
        dest.y,
        dest.width,
        dest.height);
    renderer.set_blend_mode(save);
}

} // namespace



namespace elona
{

void PicLoader::clear()
{
    for (const auto& buffer : buffers)
    {
        elona::buffer(buffer.buffer_id, 1, 1);
    }

    buffers.clear();
    storage.clear();
}

std::pair<Extent, size_t> PicLoader::find_extent(
    int width,
    int height,
    PageType type,
    size_t& info_index,
    // TODO: move out
    int buffer_width,
    int buffer_height)
{
    Extent ext{0, 0, 0, 0};

    auto check =
        [this, &ext, &type, &width, &height, &buffer_width, &buffer_height](
            size_t index) -> optional<size_t> {
        if (index == buffers.size())
        {
            add_buffer(type, buffer_width, buffer_height);
        }

        auto& info = buffers.at(index);

        if (info.type != type)
        {
            return none;
        }

        // Try to find an available buffer location to pack this
        // sprite.
        if (auto pair = info.find(width, height))
        {
            size_t skyline_index = pair->first;
            ext = pair->second;
            ext.buffer = info.buffer_id;

            return skyline_index;
        }

        return none;
    };

    optional<size_t> skyline_index = check(info_index);
    if (skyline_index)
    {
        return {ext, *skyline_index};
    }

    size_t i = 0;
    while (true)
    {
        if (i == info_index)
        {
            i += 1;
            continue;
        }

        skyline_index = check(i);
        if (skyline_index)
        {
            break;
        }

        i += 1;
    }

    info_index = i;

    return {ext, *skyline_index};
}

void PicLoader::load(
    const fs::path& image_file,
    const IdType& id,
    PageType type)
{
    snail::Image img{image_file, snail::Color{0, 0, 0}};
    Extent ext{0, 0, 0, 0};

    auto it = storage.find(id);
    if (it != storage.end())
    {
        ext = it->second;
    }
    else
    {
        size_t info_index = 0;
        size_t skyline_index;
        std::tie(ext, skyline_index) = find_extent(
            img.width(), img.height(), type, info_index, 1024, 1024);

        // Update the sprite packing information.
        auto& info = buffers.at(info_index);
        info.insert_extent(skyline_index, ext);
    }

    // Render the sprite to the region of the buffer that was found.
    gsel(ext.buffer);

    copy_image(img, ext);

    // Store the buffer region for later lookup.
    storage[id] = ext;
}

void PicLoader::add_predefined_extents(
    const fs::path& atlas_file,
    const MapType& extents,
    PageType type)
{
    snail::Image img{atlas_file, snail::Color{0, 0, 0}};
    int i = 0;

    // Add a new buffer for this atlas. The assumption is that all the
    // defined sprites will fit on this buffer. This assumption might
    // not hold in the degenerate case, but for the atlases used
    // (character.bmp, image.bmp) there is still a good amount of
    // unused space to hold any potential overflow.

    size_t info_index = 0;
    for (auto& pair : extents)
    {
        // Get the source loaded from a definition file.
        const Extent& source = pair.second;
        Extent dest{0, 0, 0, 0};

        auto it = storage.find(pair.first);
        if (it != storage.end())
        {
            dest = it->second;
            info_index = dest.buffer - max_buffers;
        }
        else
        {
            assert(source.right() < img.width());
            assert(source.bottom() < img.height());

            // Find a region on a buffer to place the sprite.

            // FIXME: refactor this dirty hack.
            int width = source.width;
            int height = source.height;
            if (type == PageType::portrait)
            {
                width = _displayed_portrait_width;
                height = _displayed_portrait_height;
            }

            size_t skyline_index;
            std::tie(dest, skyline_index) = find_extent(
                width, height, type, info_index, img.width(), img.height());
            dest.frame_width = source.frame_width;

            // Update the sprite packing information.
            auto& info = buffers.at(info_index);
            info.insert_extent(skyline_index, dest);

            // Store the buffer region for later lookup.
            storage[pair.first] = dest;
        }

        gsel(dest.buffer);
        // std::cerr << i << " copy " << atlas_file.native() << " " <<
        // dest.buffer
        //           << " " << source.x << " " << source.y << " " <<
        //           source.width
        //           << " " << source.height << " " << dest.x << " " << dest.y
        //           << std::endl;
        i++;


        // Render the defined portion of the image onto the buffer.
        if (type == PageType::portrait)
        {
            copy_image_portrait(img, source, dest);
        }
        else
        {
            copy_image_cropped(img, source, dest);
        }
    }
}

PicLoader::BufferInfo& PicLoader::add_buffer(PageType type, int w, int h)
{
    int new_buffer_index;
    size_t buffer_info_index = buffers.size();

    std::cerr << "add buffer " << w << " " << h << std::endl;
    assert(buffer_info_index < max_buffers);

    new_buffer_index = max_buffers + buffer_info_index;
    buffers.emplace_back(type, new_buffer_index, w, h);

    buffer(new_buffer_index, w, h);

    return buffers.back();
}

} // namespace elona
