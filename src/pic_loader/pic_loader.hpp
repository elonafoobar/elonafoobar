#pragma once
#include <cassert>
#include <climits>
#include <unordered_map>
#include "../filesystem.hpp"
#include "../lib/noncopyable.hpp"
#include "../optional.hpp"
#include "../shared_id.hpp"
#include "../snail/image.hpp"
#include "extent.hpp"

namespace elona
{

/***
 * Loads images from a variety of different image sources and packs
 * them to fit inside the global texture buffers allocated by HSP's
 * buffer() using the skyline packing algorithm. It provides a uniform
 * interface for accessing sprite locations by an ID lookup. This
 * allows players to add new character/image sprites without being
 * constrained by the predefined image locations of the original
 * texture atlases.
 *
 * NOTE: Currently only allocates up to 10 buffers for holding packed
 * sprites, past which it will assert. The range of buffers is laid
 * out as follows:
 *
 * - 0: render target
 * - 1: items
 * - 2: interface in casino/tcg
 * - 3: general interface
 * - 4: interface backgrounds
 * - 5: characters (deprecated, now managed by this class)
 * - 6: map tiles
 * - 7: event window backgrounds
 * - 8: message panel
 * - 9: continuous action (activity) image
 * - 10-19: this class
 * - 20+: PCC sprites (used to be 10+). Texture id is chara.index + 20
 */
class pic_loader : public lib::noncopyable
{
public:
    enum class page_type
    {
        character,
        item
    };
    struct skyline
    {
        skyline(int x, int y, int width)
            : x(x)
            , y(y)
            , width(width)
        {
        }

        int x;
        int y;
        int width;

        inline int left() const
        {
            return x;
        }
        inline int top() const
        {
            return y;
        }
        inline int right() const
        {
            return x + width - 1;
        }
    };

    /***
     * Represents a single buffer allocated by a call to buffer().
     * Holds information about available space for packing sprites.
     */
    struct buffer_info
    {
        buffer_info(
            pic_loader::page_type type,
            int buffer_id,
            int width,
            int height)
            : type(type)
            , buffer_id(buffer_id)
            , width(width)
            , height(height)
        {
            skylines.emplace_back(0, 0, width);
        }

        optional<extent> fits(int w, int h, size_t index) const
        {
            int remain = w;
            int x = skylines.at(index).x;
            int y = 0;

            for (size_t i = index; i < skylines.size(); i++)
            {
                const skyline& skyline = skylines[i];
                y = std::max(y, skyline.y);

                if (x >= width || y >= height)
                {
                    return none;
                }

                if (skyline.width >= remain)
                {
                    return extent{x, y, w, h};
                }

                assert(remain > skyline.width);
                remain -= skyline.width;
            }

            return none;
        }

        void insert_extent(size_t index, const extent& extent)
        {
            split(index, extent);
            merge_all();
        }

        optional<std::pair<size_t, extent>> find(int w, int h)
        {
            int bottom = INT_MAX;
            int width = INT_MAX;
            optional<size_t> index = none;
            extent ext{0, 0, 0, 0};

            for (size_t i = 0; i < skylines.size(); i++)
            {
                if (auto e = fits(w, h, i))
                {
                    skyline& skyline = skylines[i];
                    if (e->bottom() < bottom
                        || (e->bottom() == bottom && skyline.width < width))
                    {
                        bottom = e->bottom();
                        width = skyline.width;
                        index = i;
                        ext = *e;
                    }
                }
            }

            if (index)
            {
                return std::make_pair(*index, ext);
            }
            else
            {
                return none;
            }
        }

    private:
        void merge_all()
        {
            for (size_t i = 1; i < skylines.size(); i++)
            {
                skyline& prev = skylines[i - 1];
                skyline& now = skylines[i];

                if (prev.y == now.y)
                {
                    prev.width += now.width;
                    skylines.erase(skylines.begin() + i);
                    i -= 1;
                }
            }
        }

        void split(size_t index, const extent& extent)
        {
            skyline sl{extent.left(), extent.bottom() + 1, extent.width};
            assert(sl.right() <= width);
            assert(sl.top() <= height);

            skylines.insert(skylines.begin() + index, sl);

            for (size_t i = index + 1; i < skylines.size(); i++)
            {
                skyline& prev = skylines[i - 1];
                skyline& now = skylines[i];

                assert(prev.left() <= now.left());

                if (now.left() <= prev.right())
                {
                    int shrink_amount = prev.right() - now.left() + 1;
                    if (now.width <= shrink_amount)
                    {
                        skylines.erase(skylines.begin() + i);
                    }
                    else
                    {
                        now.x += shrink_amount;
                        now.width -= shrink_amount;
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

    public:
        pic_loader::page_type type;
        int buffer_id;
        int width;
        int height;

    private:
        std::vector<skyline> skylines;
    };

    using id_type = shared_id;
    using map_type = std::unordered_map<id_type, extent>;

    void clear_storage_and_buffers();

    /***
     * Loads a single sprite into a buffer of the provided type into
     * which it will fit. May allocate a new buffer if none are found.
     */
    void load(const fs::path&, const id_type&, page_type);

    /***
     * Loads a map of rectangular extents indexed by an ID
     * ("core.chara_sprite.<xxx>", etc.) using a map file.
     *
     * This does not copy the atlas image directly to a buffer, but
     * instead copies the individual texture regions of the atlas into
     * potentially multiple buffers. The reason is that it's difficult
     * to add the known locations of sprites to the structs with
     * skyline information, which expect the available texture regions
     * to have been split or merged by previous texture region
     * insertions.
     */
    void add_predefined_extents(const fs::path&, const map_type&, page_type);

    optional_ref<extent> operator[](const id_type& id) const
    {
        const auto itr = storage.find(id);
        if (itr == std::end(storage))
            return none;
        else
            return itr->second;
    }

    optional_ref<extent> operator[](const std::string& inner_id) const
    {
        return (*this)[shared_id(inner_id)];
    }

private:
    buffer_info& add_buffer(page_type type)
    {
        return add_buffer(type, 1024, 1024);
    }
    buffer_info& add_buffer(page_type, int, int);

    std::vector<buffer_info> buffers;
    map_type storage;
};
} // namespace elona
