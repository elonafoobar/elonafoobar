#include "gdata.hpp"
#include "variables.hpp"

namespace elona
{

static void _trainer_skills_yowyn()
{
    dblist(0, dbmax) = 154;
    ++dbmax;
    dblist(0, dbmax) = 162;
    ++dbmax;
    dblist(0, dbmax) = 184;
    ++dbmax;
    dblist(0, dbmax) = 176;
    ++dbmax;
    dblist(0, dbmax) = 177;
    ++dbmax;
    dblist(0, dbmax) = 180;
    ++dbmax;
    dblist(0, dbmax) = 301;
    ++dbmax;
    dblist(0, dbmax) = 167;
    ++dbmax;
    dblist(0, dbmax) = 153;
    ++dbmax;
}

static void _trainer_skills_vernis()
{
    dblist(0, dbmax) = 178;
    ++dbmax;
    dblist(0, dbmax) = 154;
    ++dbmax;
    dblist(0, dbmax) = 184;
    ++dbmax;
    dblist(0, dbmax) = 163;
    ++dbmax;
    dblist(0, dbmax) = 182;
    ++dbmax;
    dblist(0, dbmax) = 185;
    ++dbmax;
    dblist(0, dbmax) = 158;
    ++dbmax;
}

static void _trainer_skills_palmia()
{
    dblist(0, dbmax) = 151;
    ++dbmax;
    dblist(0, dbmax) = 150;
    ++dbmax;
    dblist(0, dbmax) = 161;
    ++dbmax;
    dblist(0, dbmax) = 179;
    ++dbmax;
    dblist(0, dbmax) = 301;
    ++dbmax;
    dblist(0, dbmax) = 156;
    ++dbmax;
    dblist(0, dbmax) = 160;
    ++dbmax;
    dblist(0, dbmax) = 172;
    ++dbmax;
    dblist(0, dbmax) = 178;
    ++dbmax;
}

static void _trainer_skills_noyel()
{
    dblist(0, dbmax) = 181;
    ++dbmax;
    dblist(0, dbmax) = 150;
    ++dbmax;
    dblist(0, dbmax) = 162;
    ++dbmax;
    dblist(0, dbmax) = 184;
    ++dbmax;
    dblist(0, dbmax) = 182;
    ++dbmax;
    dblist(0, dbmax) = 155;
    ++dbmax;
    dblist(0, dbmax) = 153;
    ++dbmax;
}

static void _trainer_skills_lumiest()
{
    if (game_data.current_dungeon_level == 1)
    {
        dblist(0, dbmax) = 172;
        ++dbmax;
        dblist(0, dbmax) = 154;
        ++dbmax;
        dblist(0, dbmax) = 150;
        ++dbmax;
        dblist(0, dbmax) = 174;
        ++dbmax;
        dblist(0, dbmax) = 185;
        ++dbmax;
        dblist(0, dbmax) = 171;
        ++dbmax;
        dblist(0, dbmax) = 160;
        ++dbmax;
        dblist(0, dbmax) = 167;
        ++dbmax;
    }
    if (game_data.current_dungeon_level == 3)
    {
        dblist(0, dbmax) = 172;
        ++dbmax;
        dblist(0, dbmax) = 165;
        ++dbmax;
        dblist(0, dbmax) = 155;
        ++dbmax;
        dblist(0, dbmax) = 164;
        ++dbmax;
        dblist(0, dbmax) = 178;
        ++dbmax;
        dblist(0, dbmax) = 188;
        ++dbmax;
        dblist(0, dbmax) = 171;
        ++dbmax;
        dblist(0, dbmax) = 187;
        ++dbmax;
    }
}

static void _trainer_skills_derphy()
{
    if (game_data.current_dungeon_level == 1)
    {
        dblist(0, dbmax) = 158;
        ++dbmax;
        dblist(0, dbmax) = 157;
        ++dbmax;
        dblist(0, dbmax) = 170;
        ++dbmax;
        dblist(0, dbmax) = 171;
        ++dbmax;
        dblist(0, dbmax) = 176;
        ++dbmax;
        dblist(0, dbmax) = 174;
        ++dbmax;
        dblist(0, dbmax) = 183;
        ++dbmax;
        dblist(0, dbmax) = 163;
        ++dbmax;
    }
    if (game_data.current_dungeon_level == 3)
    {
        dblist(0, dbmax) = 300;
        ++dbmax;
        dblist(0, dbmax) = 175;
        ++dbmax;
        dblist(0, dbmax) = 158;
        ++dbmax;
        dblist(0, dbmax) = 157;
        ++dbmax;
        dblist(0, dbmax) = 189;
        ++dbmax;
    }
}

static void _trainer_skills_port_kapul()
{
    if (game_data.current_dungeon_level == 1)
    {
        dblist(0, dbmax) = 156;
        ++dbmax;
        dblist(0, dbmax) = 160;
        ++dbmax;
        dblist(0, dbmax) = 183;
        ++dbmax;
        dblist(0, dbmax) = 185;
        ++dbmax;
        dblist(0, dbmax) = 174;
        ++dbmax;
        dblist(0, dbmax) = 151;
        ++dbmax;
    }
    if (game_data.current_dungeon_level == 3)
    {
        dblist(0, dbmax) = 153;
        ++dbmax;
        dblist(0, dbmax) = 166;
        ++dbmax;
        dblist(0, dbmax) = 167;
        ++dbmax;
        dblist(0, dbmax) = 169;
        ++dbmax;
        dblist(0, dbmax) = 152;
        ++dbmax;
        dblist(0, dbmax) = 189;
        ++dbmax;
        dblist(0, dbmax) = 168;
        ++dbmax;
        dblist(0, dbmax) = 186;
        ++dbmax;
    }
}

void map_get_trainer_skills()
{
    int dbmax = 0;

    dblist(0, dbmax) = 159;
    ++dbmax;
    dblist(0, dbmax) = 173;
    ++dbmax;

    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        _trainer_skills_yowyn();
    }
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        _trainer_skills_yowyn();
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        _trainer_skills_palmia();
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        _trainer_skills_noyel();
    }
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        _trainer_skills_lumiest();
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        _trainer_skills_derphy();
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        _trainer_skills_port_kapul();
    }

    for (int cnt = 0, cnt_end = (dbmax); cnt < cnt_end; ++cnt)
    {
        p = dblist(0, cnt);
        f = 0;
        if (sdata.get(p, cc).original_level == 0)
        {
            if (the_ability_db[p]->related_basic_attribute != 0)
            {
                f = 1;
            }
        }
        if (f)
        {
            list(0, listmax) = p;
            list(1, listmax) =
                the_ability_db[p]->related_basic_attribute + 21000;
            ++listmax;
        }
    }
}


} // namespace elona
