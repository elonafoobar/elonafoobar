#include "ability.hpp"
#include "range.hpp"


namespace elona
{



skill_data::skill_data()
    : storage(245, std::vector<ability>(600))
{
}



void skill_data::clear(int cc)
{
    range::fill(storage[cc], ability{});
}



void skill_data::copy(int tc, int cc)
{
    range::copy(storage[cc], std::begin(storage[tc]));
}



// Serialize the entire data from offset
std::unique_ptr<char[]> skill_data::serialize(int offset) const
{
    std::unique_ptr<char[]> buf{
        new char[(std::size(storage) - offset) * sizeof(int) * 1200]};
    std::fill(
        buf.get(),
        buf.get() + (std::size(storage) - offset) * sizeof(int) * 1200,
        0);
    for (size_t i = offset; i < std::size(storage); ++i)
    {
        for (size_t j = 0; j < 1200; ++j)
        {
            int value;
            if (j < 600)
            {
                value = storage[i][j].current_level;
            }
            else
            {
                value = storage[i][j - 600].original_level * 1'000'000
                    + storage[i][j - 600].experience * 1'000
                    + storage[i][j - 600].potential;
            }
            *reinterpret_cast<int*>(
                buf.get() + (i - offset) * sizeof(int) * 1200
                + j * sizeof(int)) = value;
        }
    }
    return std::move(buf);
}



void skill_data::deserialize(
    std::unique_ptr<char[]> raw_data,
    int size,
    int offset)
{
    for (size_t i = size_t(offset);; ++i)
    {
        for (size_t j = 0; j < 1200; ++j)
        {
            int value = *reinterpret_cast<int*>(
                raw_data.get() + (i - offset) * sizeof(int) * 1200
                + j * sizeof(int));
            if (j < 600)
            {
                storage[i][j].current_level = value;
            }
            else
            {
                storage[i][j - 600].original_level = value / 1'000'000;
                storage[i][j - 600].experience = value % 1'000'000 / 1'000;
                storage[i][j - 600].potential = value % 1'000;
            }
        }

        size -= 1200 * sizeof(int);
        if (size == 0)
            return;
    }
}


} // namespace elona
