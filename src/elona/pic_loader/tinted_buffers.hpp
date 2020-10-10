#pragma once

#include <unordered_map>

#include "../../snail/color.hpp"
#include "../../util/noncopyable.hpp"
#include "../optional.hpp"



namespace elona
{

/**
 * Tracks tinted copies of other HSP buffers. Used to allow easily modifying the
 * entire tile map of dynamically loaded tiles for the time of day coloring.
 *
 * Occupies buffers slots 30-39 for now.
 */
class TintedBuffers : lib::noncopyable
{
private:
    struct TintedBufferInfo
    {
        TintedBufferInfo(int buffer)
            : buffer(buffer)
            , last_tint(0, 0, 0, 0)
        {
        }

        int buffer;
        snail::Color last_tint;
    };

public:
    static constexpr int max_buffers = 10;

    void clear();

    void reserve_tinted_buffer(int buffer_id);

    bool tint(int buffer_id, snail::Color color, bool force = false);

    optional<int> get_tinted_buffer(int buffer_id)
    {
        auto it = _buffer_mapping.find(buffer_id);
        if (it != _buffer_mapping.end())
            return it->second.buffer;
        return none;
    }

private:
    std::unordered_map<int, TintedBufferInfo> _buffer_mapping;
    int _current_index{};
};

} // namespace elona
