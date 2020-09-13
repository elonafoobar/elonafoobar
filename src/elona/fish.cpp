#include "fish.hpp"

#include "character.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "message.hpp"
#include "variables.hpp"



namespace elona
{

void fish_get(int integer_fish_id)
{
    flt();
    if (const auto item =
            itemcreate_player_inv(the_fish_db[integer_fish_id]->item_id, 0))
    {
        item->subname = integer_fish_id;
        item->value = the_fish_db[integer_fish_id]->value;
        item->weight = the_fish_db[integer_fish_id]->weight;
        txt(i18n::s.get("core.activity.fishing.get", item.unwrap()));
        inv_stack(inv_player(), item.unwrap(), true);
    }
}



int fish_select_at_random(int bait)
{
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
        sampler.add(fish.integer_id, fish.rarity);
    }

    return sampler.get().value_or(1);
}

} // namespace elona
