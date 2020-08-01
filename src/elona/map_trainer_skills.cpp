#include "ability.hpp"
#include "character.hpp"
#include "data/types/type_ability.hpp"
#include "gdata.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

const std::vector<int> _yowyn = {
    154,
    162,
    184,
    176,
    177,
    180,
    301,
    167,
    153,
};

const std::vector<int> _vernis = {
    178,
    154,
    184,
    163,
    182,
    185,
    158,
};

const std::vector<int> _palmia{
    151,
    150,
    161,
    179,
    301,
    156,
    160,
    172,
    178,
};

const std::vector<int> _noyel{
    181,
    150,
    162,
    184,
    182,
    155,
    153,
};

const std::vector<int> _lumiest = {
    172,
    154,
    150,
    174,
    185,
    171,
    160,
    167,
};

const std::vector<int> _mages_guild = {
    172,
    165,
    155,
    164,
    178,
    188,
    171,
    187,
};

const std::vector<int> _derphy = {
    158,
    157,
    170,
    171,
    176,
    174,
    183,
    163,
};

const std::vector<int> _thieves_guild = {
    300,
    175,
    158,
    157,
    189,
};

const std::vector<int> _port_kapul = {
    156,
    160,
    183,
    185,
    174,
    151,
};

const std::vector<int> _fighters_guild = {
    153,
    166,
    167,
    169,
    152,
    189,
    168,
    186,
};

} // namespace



void map_get_trainer_skills(const Character& chara)
{
    const auto append = [](std::vector<int>& lhs, const std::vector<int>& rhs) {
        lhs.insert(lhs.end(), rhs.begin(), rhs.end());
    };

    std::vector<int> skills{159, 173};

    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        append(skills, _yowyn);
    }
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        append(skills, _vernis);
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        append(skills, _palmia);
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        append(skills, _noyel);
    }
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        if (game_data.current_dungeon_level == 1)
        {
            append(skills, _lumiest);
        }
        else if (game_data.current_dungeon_level == 3)
        {
            append(skills, _mages_guild);
        }
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        if (game_data.current_dungeon_level == 1)
        {
            append(skills, _derphy);
        }
        else if (game_data.current_dungeon_level == 3)
        {
            append(skills, _thieves_guild);
        }
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        if (game_data.current_dungeon_level == 1)
        {
            append(skills, _port_kapul);
        }
        else if (game_data.current_dungeon_level == 3)
        {
            append(skills, _fighters_guild);
        }
    }

    for (const auto& skill_id : skills)
    {
        if (chara.get_skill(skill_id).base_level == 0)
        {
            list(0, listmax) = skill_id;
            list(1, listmax) =
                the_ability_db[skill_id]->related_basic_attribute + 21000;
            ++listmax;
        }
    }
}

} // namespace elona
