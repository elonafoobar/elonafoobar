#include "tinted_buffers.hpp"
#include <iostream>
#include "../draw.hpp"
#include "../elona.hpp"
#include "pic_loader.hpp"

namespace elona
{

/**
 * Allocates a corresponding buffer for @ref buffer_id for tinting.
 */
void TintedBuffers::reserve_tinted_buffer(int buffer_id)
{
    assert(_current_index < max_buffers);

    const auto tinted_buffer = _current_index + 10 + PicLoader::max_buffers;
    _buffer_mapping.emplace(buffer_id, TintedBufferInfo{tinted_buffer});
    _current_index++;

    gsel(buffer_id);
    const auto width = ginfo(12);
    const auto height = ginfo(13);

    buffer(tinted_buffer, width, height);
}

void TintedBuffers::clear()
{
    for (const auto& pair : _buffer_mapping)
    {
        buffer(pair.second.buffer, 1, 1);
    }
    _buffer_mapping.clear();
    _current_index = 0;
}

/**
 * Tints an entire buffer corresponding to @a buffer_id. A tinted buffer
 * must be reserved for @a buffer_id first with @ref reserve_tinted_copy.
 *
 * Modifies the selected buffer with @ref gsel.
 *
 * Will not copy any textures if @a color is the same as the last call to @a
 * tint on this buffer. Returns true if the copy was performed.
 */
bool TintedBuffers::tint(int buffer_id, snail::Color color, bool force)
{
    auto it = _buffer_mapping.find(buffer_id);
    if (it == _buffer_mapping.end())
    {
        throw std::runtime_error(
            "Attempted to tint buffer " + std::to_string(buffer_id) +
            ", but no tinted buffer was reserved first.");
    }
    auto tinted_buffer = it->second;

    // Prevent unneccessary texture copies.
    if (color == tinted_buffer.last_tint && !force)
    {
        return false;
    }
    tinted_buffer.last_tint = color;

    gsel(tinted_buffer.buffer);
    const auto width = ginfo(12);
    const auto height = ginfo(13);

    set_color_mod(color.r, color.g, color.b, buffer_id);
    gcopy(buffer_id, 0, 0, width, height, 0, 0);
    set_color_mod(255, 255, 255, buffer_id);

    return true;
}

} // namespace elona
