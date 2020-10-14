#pragma once

#include <unordered_map>

#include "../util/mathutil.hpp"
#include "data/id.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;



/**
 * Records one blending recipe's memory.
 */
struct BlendingRecipeMemory
{
    /// Read count
    lua_int read_count{};

#if 0
    /// Extension data
    lua_table ext{};
#endif
};



/**
 * A table of @ref BlendingRecipeMemory indexed by blending recipe ID. It
 * delays creation of entries until the first assignment.
 */
struct BlendingRecipeMemoryTable
{
    /**
     * Gets the read count of @a id.
     *
     * @param id The blending recipe ID
     * @return The number of blending recipes you have read ever
     */
    lua_int read_count(data::InstanceId id) const noexcept
    {
        if (const auto itr = _memories.find(id); itr != _memories.end())
        {
            return itr->second.read_count;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Sets the read count of @a id with the given @a new_read_count. If @a
     * new_read_count is negative, the read count is set to zero.
     */
    void set_read_count(data::InstanceId id, lua_int new_read_count)
    {
        if (new_read_count == 0 && _memories.find(id) == _memories.end())
            return;

        _memories[id].read_count = std::max(new_read_count, lua_int{0});
    }



    /**
     * Increments the read count of @a id.
     */
    void increment_read_count(data::InstanceId id)
    {
        mathutil::saturating_inc(_memories[id].read_count);
    }



private:
    std::unordered_map<data::InstanceId, BlendingRecipeMemory> _memories;
};

} // namespace elona
