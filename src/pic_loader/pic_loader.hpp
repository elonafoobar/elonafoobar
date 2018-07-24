#pragma once
#include "../filesystem.hpp"
#include "../lib/noncopyable.hpp"
#include "../optional.hpp"
#include "../shared_id.hpp"
#include "extent.hpp"
#include <cassert>
#include <climits>
#include <unordered_map>

namespace elona
{
class pic_loader : public lib::noncopyable
{
public:
    struct skyline
    {
        int x;
        int y;
        int w;

        inline int left() const { return x; }
        inline int top() const { return y; }
        inline int right() const { return x + w - 1; }
    };

    struct buffer_info
    {
        buffer_info(int width, int height) : width(width), height(height) {}

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

                if (skyline.w >= remain)
                {
                    return extent{x, y, w, h};
                }

                assert(remain > skyline.w);
                remain -= skyline.w;
            }

            return none;
        }

        void merge_all()
        {
            for (size_t i = 1; i < skylines.size(); i++)
            {
                skyline& prev = skylines[i-1];
                skyline& now = skylines[i];

                if (prev.y == now.y)
                {
                    prev.w += now.w;
                    skylines.erase(skylines.begin() + i);
                    i -= 1;
                }
            }
        }

        void split(size_t index, const extent& extent)
        {
            skyline sl{extent.right(), extent.bottom() + 1, extent.left()};
            assert(sl.right() <= width);
            assert(sl.top() <= height);

            skylines.insert(skylines.begin() + index, sl);

            for (size_t i = index + 1; i < skylines.size(); i++)
            {
                skyline& prev = skylines[i-1];
                skyline& now = skylines[i];

                assert(prev.left() <= now.left());

                if (now.left() <= prev.right())
                {
                    int shrink_amount = prev.right() - now.left() + 1;
                    if (now.w <= shrink_amount)
                    {
                        skylines.erase(skylines.begin() + i);
                    }
                    else
                    {
                        now.x += shrink_amount;
                        now.w -= shrink_amount;
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        optional<std::pair<size_t, extent>> find(int w, int h)
        {
            int bottom = UINT_MAX;
            int width = UINT_MAX;
            optional<size_t> index = none;
            extent ext{0, 0, 0, 0};

            for (size_t i = 0; i < skylines.size(); i++)
            {
                if (auto e = fits(i, w, h))
                {
                    skyline& skyline = skylines[i];
                    if (e->bottom() < bottom || (e->bottom() == bottom && skyline.w < width))
                    {
                        bottom = e->bottom();
                        width = skyline.w;
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

        int width;
        int height;
        std::vector<skyline> skylines;
    };

    using id_type = shared_id;
    using map_type = std::unordered_map<id_type, extent>;
    typedef int page_index;

    void clear();

    void load(const fs::path&, const id_type&, page_index);
    void add_predefined_extents(const fs::path&, const map_type&, page_index);

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
    void add_buffer(page_index index) { add_buffer(index, 1024, 1024); }
    void add_buffer(page_index, int, int);

    std::unordered_map<page_index, std::vector<buffer_info>> buffers;
    map_type storage;

};
} // namespace elona
