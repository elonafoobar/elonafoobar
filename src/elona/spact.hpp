#pragma once

#include <unordered_set>

#include "data/id.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;



/**
 * A set of spacts that one can use.
 */
struct SpactTable
{
    /**
     * True if the character has @a id; otherwise, false
     */
    bool has(data::InstanceId id) const noexcept
    {
        return _spacts.find(id) != _spacts.end();
    }



    /**
     * Gain the given spact of @a id.
     *
     * @param id The spact ID
     */
    void gain(data::InstanceId id)
    {
        _spacts.emplace(id);
    }



    /**
     * Lose the given spact of @a id.
     *
     * @param id The spact ID
     */
    void lose(data::InstanceId id)
    {
        _spacts.erase(id);
    }



    /**
     * Lose all spacts.
     */
    void clear()
    {
        _spacts.clear();
    }



    // for integration with legacy codebase.
    void pack_to(elona_vector1<int>& legacy_spact) const;
    void unpack_from(elona_vector1<int>& legacy_spact);



private:
    std::unordered_set<data::InstanceId> _spacts;
};

} // namespace elona
