#include "crafting_material.hpp"

#include "audio.hpp"
#include "data/types/type_crafting_material.hpp"
#include "i18n.hpp"
#include "message.hpp"
#include "variables.hpp"



namespace elona
{

void crafting_material_gain(data::InstanceId id, int amount, int spot_type)
{
    const auto integer_id = the_crafting_material_db.ensure(id).integer_id;

    mat(integer_id) += amount;
    snd("core.alert1");

    std::string verb;
    switch (spot_type)
    {
    case 0: verb = i18n::s.get("core.activity.material.get_verb.get"); break;
    case 1: verb = i18n::s.get("core.activity.material.get_verb.dig_up"); break;
    case 2:
        verb = i18n::s.get("core.activity.material.get_verb.fish_up");
        break;
    case 3:
        verb = i18n::s.get("core.activity.material.get_verb.harvest");
        break;
    case 5: verb = i18n::s.get("core.activity.material.get_verb.find"); break;
    default: verb = i18n::s.get("core.activity.material.get_verb.get"); break;
    }

    txt(i18n::s.get(
            "core.activity.material.get",
            verb,
            amount,
            the_crafting_material_db.get_text(id, "name")) +
            u8"("s + mat(integer_id) + u8") "s,
        Message::color{ColorIndex::blue});
}



void crafting_material_lose(data::InstanceId id, int amount)
{
    const auto integer_id = the_crafting_material_db.ensure(id).integer_id;

    mat(integer_id) -= amount;
    txt(i18n::s.get(
        "core.activity.material.lose",
        the_crafting_material_db.get_text(id, "name"),
        amount));
    txt(i18n::s.get("core.activity.material.lose_total", mat(integer_id)),
        Message::color{ColorIndex::blue});
}



data::InstanceId
crafting_material_select_random_id(int level, int rarity, int spot_type)
{
    const data::InstanceId default_result = "core.garbage";

    std::vector<data::InstanceId> ids;
    for (const auto& [id, _] : the_crafting_material_db)
    {
        ids.push_back(id);
    }

    for (int i = 0; i < 500; ++i) // try 500 times
    {
        const auto id = choice(ids);
        if (id == default_result)
        {
            continue;
        }
        const auto& data = the_crafting_material_db.ensure(id);
        if (i % 10 == 0)
        {
            ++level;
            ++rarity;
        }
        if (level < data.level)
        {
            continue;
        }
        if (rarity < data.rarity)
        {
            continue;
        }
        bool match_spot{};
        for (const auto& s : data.spots)
        {
            if (s == spot_type || s == 18)
            {
                match_spot = true;
                break;
            }
        }
        if (!match_spot)
        {
            continue;
        }
        if (rnd(data.rarity) == 0)
        {
            return id;
        }
    }
    return default_result;
}

} // namespace elona
