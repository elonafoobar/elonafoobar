#include "fish.hpp"
#include "character.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "message.hpp"
#include "variables.hpp"



namespace elona
{

void fish_get(int legacy_fish_id)
{
    flt();
    itemcreate(0, the_fish_db[legacy_fish_id]->item_id, -1, -1, 0);
    inv[ci].subname = legacy_fish_id;
    inv[ci].value = the_fish_db[legacy_fish_id]->value;
    inv[ci].weight = the_fish_db[legacy_fish_id]->weight;
    txt(i18n::s.get("core.activity.fishing.get", inv[ci]));
    item_stack(0, ci, 1);
}



int fish_select_at_random()
{
    const auto bait = inv[cdata.player().activity.item].param4;
    WeightedRandomSampler<int> sampler;
    for (const auto& fish : the_fish_db.values())
    {
        if (fish.no_generate)
        {
            continue;
        }
        const auto bait_rank =
            clamp(bait + (rnd(5) == 0) - (rnd(5) == 0), 0, 5);
        if (fish.rank != bait_rank)
        {
            continue;
        }
        sampler.add(fish.legacy_id, fish.rarity);
    }

    return sampler.get().get_value_or(1);
}

} // namespace elona
