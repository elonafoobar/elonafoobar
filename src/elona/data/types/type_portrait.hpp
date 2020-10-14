#pragma once

#include "../../../util/natural_order_comparator.hpp"
#include "../../pic_loader/extent.hpp"
#include "../base_database.hpp"



namespace elona
{

struct PortraitData
{
    data::InstanceId id;
    data::FullyQualifiedId key;
    Extent rect;
    optional<fs::path> filepath;
};



ELONA_DEFINE_LUA_DB(_PortraitDBBase, PortraitData, "core.portrait")



class PortraitDB : public _PortraitDBBase
{
public:
    /**
     * Takes a portrait ID, and returns the next one. If `current` does not
     * exist in the storage, returns `current` itself. Portrait IDs are sorted
     * in lexicographical order (depending on `operator<()` for two
     * `std::string`s).
     */
    data::InstanceId get_next_portrait(data::InstanceId current);

    /**
     * Takes a portrait ID, and returns the previous one. If `current` does not
     * exist in the storage, returns `current` itself. Portrait IDs are sorted
     * in lexicographical order (depending on `operator<()` for two
     * `std::string`s).
     */
    data::InstanceId get_previous_portrait(data::InstanceId current);

    void cache_sorted_portrait_table();


private:
    std::set<std::string, lib::natural_order_comparator> sorted_portrait_table;
};



extern PortraitDB the_portrait_db;

} // namespace elona
