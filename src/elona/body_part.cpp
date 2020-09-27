#include "body_part.hpp"

#include "character.hpp"
#include "character_status.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "message.hpp"



namespace elona
{

namespace
{

// TODO: support user-deined parts
data::InstanceId get_random_body_part()
{
    if (rnd(7) == 0)
        return "core.neck";
    else if (rnd(9) == 0)
        return "core.back";
    else if (rnd(8) == 0)
        return "core.hand";
    else if (rnd(4) == 0)
        return "core.ring";
    else if (rnd(6) == 0)
        return "core.arm";
    else if (rnd(5) == 0)
        return "core.waist";
    else if (rnd(5) == 0)
        return "core.leg";
    else
        return "core.head";
}

} // namespace



bool body_part_has_empty_slot(const Character& chara)
{
    constexpr size_t max_body_parts = 30; // TODO

    return chara.body_parts.size() < max_body_parts;
}



void body_part_gain_new_slot(Character& chara, bool show_message)
{
    if (!body_part_has_empty_slot(chara))
    {
        refresh_speed_correction_value(chara); // needed?
        return;
    }

    const auto body_part_id = get_random_body_part();
    chara.body_parts.add(body_part_id);
    if (show_message)
    {
        txt(i18n::s.get(
            "core.chara_status.gain_new_body_part",
            chara,
            i18n::s.get_data_text("core.body_part", body_part_id, "name")));
    }

    refresh_speed_correction_value(chara);
}



void body_part_make_unequippable(
    Character& chara,
    data::InstanceId body_part_id)
{
    for (auto&& body_part : chara.body_parts)
    {
        if (body_part.id == body_part_id)
        {
            if (body_part.is_equip())
            {
                body_part.equipment()->equipped_slot = lua_index::nil();
            }
            body_part.make_unequippable();
        }
    }
}



void body_part_make_equippable(Character& chara, data::InstanceId body_part_id)
{
    for (auto&& body_part : chara.body_parts)
    {
        if (body_part.id == body_part_id)
        {
            if (body_part.is_unequippable())
            {
                body_part.make_equippable();
            }
        }
    }
}

} // namespace elona
