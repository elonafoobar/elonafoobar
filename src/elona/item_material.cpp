#include "item_material.hpp"



namespace elona
{

namespace
{

std::vector<std::vector<data::InstanceId>> leather_table = {
    /* clang-format off */
    { "core.cloth", "core.leather",  "core.chain",    "core.zylon",        "core.dawn_cloth",    },
    { "core.silk",  "core.scale",    "core.platinum", "core.gold",         "core.griffon_scale", },
    { "core.paper", "core.glass",    "core.pearl",    "core.spirit_cloth", "core.rubynus",       },
    { "core.bone",  "core.obsidian", "core.mithril",  "core.dragon_scale", "core.ether",         },
    /* clang-format on */
};



std::vector<std::vector<data::InstanceId>> metal_table = {
    /* clang-format off */
    { "core.bronze", "core.iron",     "core.steel",    "core.chrome",     "core.titanium", },
    { "core.lead",   "core.silver",   "core.platinum", "core.crystal",    "core.diamond",  },
    { "core.mica",   "core.glass",    "core.pearl",    "core.emerald",    "core.rubynus",  },
    { "core.coral",  "core.obsidian", "core.mithril",  "core.adamantium", "core.ether",    },
    /* clang-format on */
};

} // namespace



data::InstanceId item_material_lookup_leather(int x, int y)
{
    return leather_table.at(x).at(y);
}



data::InstanceId item_material_lookup_metal(int x, int y)
{
    return metal_table.at(x).at(y);
}

} // namespace elona
