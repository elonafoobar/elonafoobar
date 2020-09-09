#include "data/types/type_asset.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "ui.hpp"

namespace elona
{

/**
 * Loads the asset in @a id to its configured window and position. The asset
 * should have a configured file path with the image file of the asset. If it
 * has no image, this function does nothing.
 *
 * If the file is valid, the current window is changed to the window configured
 * in the asset.
 */
const AssetData& asset_load(data::InstanceId id)
{
    const auto& info = get_image_info(id);

    if (info.load_type == AssetLoadType::Buffer)
    {
        buffer(info.window_id, info.width, info.height);
    }

    if (!info.file)
    {
        return info;
    }

    bool new_buffer = info.load_type == AssetLoadType::BufferDeferred;

    gsel(info.window_id);
    picload(*info.file, info.x, info.y, new_buffer);

    return info;
}



void init_assets()
{
    for (const auto& pair : the_asset_db)
    {
        const auto& name = pair.first;
        const auto& data = pair.second;
        if (data.load_type == AssetLoadType::Buffer)
        {
            asset_load(name);
        }
    }

    for (const auto& pair : the_asset_db)
    {
        const auto& name = pair.first;
        const auto& data = pair.second;
        if (data.file && data.load_type == AssetLoadType::Startup)
        {
            asset_load(name);
        }
    }
}


/**
 * Draws an asset.
 */
void draw(data::InstanceId id, int x, int y)
{
    const auto& info = get_image_info(id);

    gcopy(info.window_id, info.x, info.y, info.width, info.height, x, y);
}



/**
 * Draws an asset with stretching.
 */
void draw(data::InstanceId id, int x, int y, int width, int height)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x,
        info.y,
        info.width,
        info.height,
        x,
        y,
        width,
        height);
}



/**
 * Draws an asset, centered, with stretching.
 */
void draw_centered(data::InstanceId id, int x, int y, int width, int height)
{
    const auto& info = get_image_info(id);

    gcopy_c(
        info.window_id,
        info.x,
        info.y,
        info.width,
        info.height,
        x,
        y,
        width,
        height);
}



/**
 * Draws an asset with variant @a index out of multiple parts aligned
 * horizontally.
 */
void draw_indexed(data::InstanceId id, int x, int y, int index_x)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x + info.width * (index_x % info.count_x),
        info.y,
        info.width,
        info.height,
        x,
        y);
}



/**
 * Draws an asset with variant @a index out of multiple parts aligned
 * horizontally and vertically.
 */
void draw_indexed(data::InstanceId id, int x, int y, int index_x, int index_y)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x + info.width * (index_x % info.count_x),
        info.y + info.height * (index_y % info.count_y),
        info.width,
        info.height,
        x,
        y);
}



/**
 * Draws an asset with variant @a index out of multiple parts aligned
 * horizontally and vertically with rotation.
 */
void draw_indexed_rotated(
    data::InstanceId id,
    int x,
    int y,
    int index_x,
    int index_y,
    double angle)
{
    const auto& info = get_image_info(id);

    grotate(
        info.window_id,
        info.x + info.width * (index_x % info.count_x),
        info.y + info.height * (index_y % info.count_y),
        info.width,
        info.height,
        x,
        y,
        angle);
}



/**
 * Draws a region of an asset.
 */
void draw_region(data::InstanceId id, int x, int y, int width)
{
    const auto& info = get_image_info(id);

    gcopy(info.window_id, info.x, info.y, width, info.height, x, y);
}



/**
 * Draws a region of an asset.
 */
void draw_region(data::InstanceId id, int x, int y, int width, int height)
{
    const auto& info = get_image_info(id);

    gcopy(info.window_id, info.x, info.y, width, height, x, y);
}



/**
 * Draws a region of an asset.
 */
void draw_region(
    data::InstanceId id,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x + offset_x,
        info.y + offset_y,
        width,
        height,
        x,
        y);
}



/**
 * Draws a region of an asset with stretching.
 */
void draw_region(
    data::InstanceId id,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height,
    int dst_width,
    int dst_height)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x + offset_x,
        info.y + offset_y,
        width,
        height,
        x,
        y,
        dst_width,
        dst_height);
}



/**
 * Draws a region of an asset, centered, with stretching.
 */
void draw_region_centered(
    data::InstanceId id,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height,
    int dst_width,
    int dst_height)
{
    const auto& info = get_image_info(id);

    gcopy_c(
        info.window_id,
        info.x + offset_x,
        info.y + offset_y,
        width,
        height,
        x,
        y,
        dst_width,
        dst_height);
}



/**
 * Draws a region of an asset rotated.
 */
void draw_region_rotated(
    data::InstanceId id,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height,
    double angle)
{
    const auto& info = get_image_info(id);

    grotate(
        info.window_id,
        info.x + offset_x,
        info.y + offset_y,
        width,
        height,
        x,
        y,
        angle);
}



/**
 * Draws an asset with variable width starting from the right.
 */
void draw_bar(
    data::InstanceId id,
    int x,
    int y,
    int dst_width,
    int dst_height,
    int width)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x + info.width - width,
        info.y,
        width % info.width,
        info.height,
        x,
        y,
        dst_width,
        dst_height);
}



/**
 * Draws an asset with variable width starting from the top.
 */
void draw_bar_vert(
    data::InstanceId id,
    int x,
    int y,
    int dst_width,
    int dst_height,
    int height)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x,
        info.y + info.height - height,
        info.width,
        height % info.height,
        x,
        y,
        dst_width,
        dst_height);
}



/**
 * Draws an indexed region of an asset in units of tile width/height.
 */
void draw_indexed_region(
    data::InstanceId id,
    int x,
    int y,
    int index_x,
    int index_y,
    int count_x,
    int count_y)
{
    const auto& info = get_image_info(id);

    gcopy(
        info.window_id,
        info.x + index_x * info.width,
        info.y + index_y * info.height,
        count_x * info.width,
        count_y * info.height,
        x,
        y);
}



/**
 * Draws an asset with rotation.
 */
void draw_rotated(data::InstanceId id, int center_x, int center_y, double angle)
{
    const auto& info = get_image_info(id);

    grotate(
        info.window_id,
        info.x,
        info.y,
        info.width,
        info.height,
        center_x,
        center_y,
        3.14159265 / 180 * angle);
}



/**
 * Draws an asset with stretching and rotation.
 */
void draw_rotated(
    data::InstanceId id,
    int center_x,
    int center_y,
    int width,
    int height,
    double angle)
{
    const auto& info = get_image_info(id);

    grotate(
        info.window_id,
        info.x,
        info.y,
        info.width,
        info.height,
        center_x,
        center_y,
        width,
        height,
        3.14159265 / 180 * angle);
}



/**
 * Fills the background of the currently selected window with the asset in @a
 * id.
 */
void draw_bg(data::InstanceId id)
{
    const auto& info = get_image_info(id);

    fillbg(info.window_id, info.x, info.y, info.width, info.height);
}



/**
 * Copies the image at @a window_id, [@a x, @a y] into the region defined by the
 * asset at @a id.
 *
 * Typically used when editing scratch regions of a window.
 */
void asset_copy_from(int window_id, int x, int y, data::InstanceId id)
{
    const auto& info = get_image_info(id);

    gsel(info.window_id);
    gcopy(window_id, x, y, info.width, info.height, info.x, info.y);
}



/**
 * Copies the image at @a window_id, [@a x, @a y] into the region defined by the
 * asset at @a id.
 *
 * Typically used when editing scratch regions of a window.
 */
void asset_copy_from(
    int window_id,
    int x,
    int y,
    int width,
    int height,
    data::InstanceId id)
{
    const auto& info = get_image_info(id);

    gsel(info.window_id);
    gcopy(window_id, x, y, width, height, info.x, info.y);
}



/**
 * Obtains the window and region data for the asset in @a id. Throws if the
 * asset does not exist.
 */
const AssetData& get_image_info(data::InstanceId id)
{
    // TODO: Instead of throwing, log once and return a default.
    auto data = the_asset_db[id];
    if (!data)
        throw std::runtime_error{u8"Unknown asset ID: "s + id.get()};
    return *data;
}

} // namespace elona
