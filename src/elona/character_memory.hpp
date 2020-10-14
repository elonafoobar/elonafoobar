#pragma once

#include <unordered_map>

#include "../util/mathutil.hpp"
#include "data/id.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector2;



/**
 * Records one character's memory.
 */
struct CharacterMemory
{
    /// Generate count
    lua_int generate_count{};

    /// Kill count
    lua_int kill_count{};

#if 0
    /// Extension data
    lua_table ext{};
#endif
};



/**
 * A table of @ref CharacterMemory indexed by character ID. It delays
 * creation of entries until the first assignment.
 */
struct CharacterMemoryTable
{
    /**
     * Gets the generation count of @a id.
     *
     * @param id The character ID
     * @return The number of characters generated ever
     */
    lua_int generate_count(data::InstanceId id) const noexcept
    {
        if (const auto itr = _memories.find(id); itr != _memories.end())
        {
            return itr->second.generate_count;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Increments the generation count of @a id.
     */
    void increment_generate_count(data::InstanceId id)
    {
        mathutil::saturating_inc(_memories[id].generate_count);
    }



    /**
     * Decrements the generation count of @a id.
     */
    void decrement_generate_count(data::InstanceId id)
    {
        mathutil::saturating_dec(_memories[id].generate_count, lua_int{0});
    }



    /**
     * Gets the kill count of @a id.
     *
     * @param id The character ID
     * @return The number of characters killed ever
     */
    lua_int kill_count(data::InstanceId id) const noexcept
    {
        if (const auto itr = _memories.find(id); itr != _memories.end())
        {
            return itr->second.kill_count;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Increments the kill count of @a id.
     */
    void increment_kill_count(data::InstanceId id)
    {
        mathutil::saturating_inc(_memories[id].kill_count);
    }



    /**
     * Decrements the kill count of @a id.
     */
    void decrement_kill_count(data::InstanceId id)
    {
        mathutil::saturating_dec(_memories[id].kill_count, lua_int{0});
    }



private:
    std::unordered_map<data::InstanceId, CharacterMemory> _memories;
};

} // namespace elona
