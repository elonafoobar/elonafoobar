#pragma once

#include <unordered_map>

#include "../util/mathutil.hpp"
#include "data/id.hpp"
#include "enums.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector2;



/**
 * Records one item's memory.
 */
struct ItemMemory
{
    /// Generate count
    lua_int generate_count{};

    /// Identify state
    IdentifyState identify_state{};

    /// Whether the item has been decoded (for spellbooks only)
    bool is_decoded{};

    // TODO: move it to spellbook writer's field.
    bool _is_reserved{};

#if 0
    /// Extension data
    lua_table ext{};
#endif
};



/**
 * A table of @ref ItemMemory indexed by item ID. It delays creation of entries
 * until the first assignment.
 */
struct ItemMemoryTable
{
    /**
     * Gets the generation count of @a id.
     *
     * @param id The item ID
     * @return The number of items generated ever
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
     * Gets the identify state of @a id.
     *
     * @param id The item ID
     * @return The identify state of the item
     */
    IdentifyState identify_state(data::InstanceId id) const noexcept
    {
        if (const auto itr = _memories.find(id); itr != _memories.end())
        {
            return itr->second.identify_state;
        }
        else
        {
            return IdentifyState::unidentified;
        }
    }



    /**
     * Set an identify state for @a id.
     *
     * @param id The item ID
     */
    void set_identify_state(data::InstanceId id, IdentifyState new_state)
    {
        _memories[id].identify_state = new_state;
    }



    /**
     * Returns whether the item has been decoded. (for spellbooks only)
     *
     * @param id The item ID
     * @return True if the spellbook has been decoded.
     */
    bool is_decoded(data::InstanceId id) const noexcept
    {
        if (const auto itr = _memories.find(id); itr != _memories.end())
        {
            return itr->second.is_decoded;
        }
        else
        {
            return false;
        }
    }



    /**
     * Set is_decoded flag of @a id with the given @a value.
     *
     * @param id The item ID
     * @param value True if the item is decoded.
     */
    void set_decoded(data::InstanceId id, bool value)
    {
        _memories[id].is_decoded = value;
    }



    bool _is_reserved(data::InstanceId id) const noexcept
    {
        if (const auto itr = _memories.find(id); itr != _memories.end())
        {
            return itr->second._is_reserved;
        }
        else
        {
            return false;
        }
    }

    void _set_reserved(data::InstanceId id, bool value)
    {
        _memories[id]._is_reserved = value;
    }



    // for integration with legacy codebase.
    void pack_to(elona_vector2<int>& legacy_itemmemory) const;
    void unpack_from(elona_vector2<int>& legacy_itemmemory);



private:
    std::unordered_map<data::InstanceId, ItemMemory> _memories;
};

} // namespace elona
