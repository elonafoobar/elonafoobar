#include "elona.hpp"
#include "item_db.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{


void label_0481()
{
    weighted_random_sampler<int> sampler;

    for (const auto& data : the_item_db)
    {
        if (data.level > objlv)
            continue;
        if (fltselect != data.fltselect)
            continue;
        if (flttypemajor != 0 && flttypemajor != data.category)
            continue;
        if (flttypeminor != 0 && flttypeminor != data.subcategory)
            continue;
        if (filtermax != 0)
        {
            // FIXME: use std::all_of
            bool ok = true;
            for (int i = 0; i < filtermax; ++i)
            {
                if (filter_item(data.id).find(filtern(i)) == std::string::npos)
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                continue;
        }
        sampler.add(
            data.id,
            data.rarity
                    / (1000 + std::abs(data.level - objlv) * data.coefficient)
                + 1);
    }

    dbid = sampler.get().value_or(25);
}



} // namespace elona
