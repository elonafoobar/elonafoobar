#include "calc.hpp"
#include "gdata.hpp"
#include "variables.hpp"

namespace elona
{

static void _chara_filter_cyber_dome()
{
    flt(calcobjlv(10), calcfixlv(Quality::bad));
    fltn(u8"sf"s);
}

static bool _chara_filter_town_yowyn()
{
    if (rnd(2))
    {
        dbid = 269;
        return true;
    }

    return false;
}

static bool _chara_filter_town_noyel()
{
    if (rnd(3) == 0)
    {
        dbid = 270;
        return true;
    }

    return false;
}

static bool _chara_filter_town_noyel()
{
    if (rnd(3) == 0)
    {
        dbid = 271;
        return true;
    }
    else if (rnd(2) == 0)
    {
        dbid = 335;
        return true;
    }

    return false;
}

static bool _chara_filter_town_lumiest()
{
    if (rnd(3) == 0)
    {
        dbid = 272;
        return true;
    }

    return false;
}

static bool _chara_filter_town_vernis()
{
    if (rnd(2))
    {
        dbid = 273;
        return true;
    }

    return false;
}

static bool _chara_filter_town_palmia()
{
    if (rnd(3) == 0)
    {
        dbid = 274;
        return true;
    }

    return false;
}

static bool chara_filter_town_normal()
{
    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        if (_chara_filter_town_yowyn())
        {
            return true;
        }
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (_chara_filter_town_noyel())
        {
            return true;
        }
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        if (_chara_filter_town_derphy())
        {
            return true;
        }
    }
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        if (_chara_filter_town_lumiest())
        {
            return true;
        }
    }
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        if (_chara_filter_town_vernis())
        {
            return true;
        }
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        if (_chara_filter_town_palmia())
        {
            return true;
        }
    }

    return false;
}

static void _chara_filter_town_dungeon()
{
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        if (game_data.current_dungeon_level == 3)
        {
            dbid = 289;
        }
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        if (game_data.current_dungeon_level == 3)
        {
            dbid = 293;
        }
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        if (game_data.current_dungeon_level == 3)
        {
            dbid = 295;
        }
    }
}

static void _chara_filter_town()
{
    flt(calcobjlv(10), calcfixlv(Quality::bad));
    fltselect = 5;

    if (game_data.current_dungeon_level == 1)
    {
        if (_chara_filter_town_normal())
        {
            return;
        }
    }

    _chara_filter_town_dungeon();
}

static void _chara_filter_lesimas()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    if (game_data.current_dungeon_level < 4)
    {
        if (objlv > 5)
        {
            objlv = 5;
        }
    }
}

static void _chara_filter_the_void()
{
    flt(calcobjlv(game_data.current_dungeon_level % 50 + 5),
        calcfixlv(Quality::bad));
}

static void _chara_filter_dragons_nest()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
}

static void _chara_filter_crypt_of_the_damned()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    fltn(u8"undead"s);
}

static void _chara_filter_tower_of_fire()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    fltn(u8"fire"s);
}

static void _chara_filter_ancient_castle()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    if (rnd(2) == 0)
    {
        fltn(u8"man"s);
    }
}

static void _chara_filter_pyramid()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    flttypemajor = 13;
}

static void _chara_filter_lumiest_graveyard()
{
    flt(calcobjlv(20), calcfixlv(Quality::bad));
    fltselect = 4;
}

static void _chara_filter_quest()
{
    if (game_data.executing_immediate_quest_type >= 1000)
    {
        flt(calcobjlv(quest_data.immediate().difficulty + 1),
            calcfixlv(Quality::bad));
    }
    if (game_data.executing_immediate_quest_type == 1006)
    {
        fltn(u8"wild"s);
        objlv = clamp(objlv / 4, 1, 8);
    }
}

static void _chara_filter_yeeks_nest()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    if (rnd(2))
    {
        fltn(u8"yeek"s);
    }
}

static void _chara_filter_minotaurs_nest()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
    if (rnd(2))
    {
        fltn(u8"mino"s);
    }
}

static void _chara_filter_nefia()
{
    flt(calcobjlv(game_data.current_dungeon_level), calcfixlv(Quality::bad));
}

static void _chara_filter_museum_shop()
{
    flt(calcobjlv(100), calcfixlv(Quality::bad));
    if (rnd(1))
    {
        fltselect = 5;
    }
    else
    {
        fltselect = 7;
    }
}

void map_set_chara_generation_filter()
{
    dbid = 0;
    if (game_data.current_map == mdata_t::MapId::cyber_dome)
    {
        _chara_filter_cyber_dome();
        return;
    }
    if (map_data.is_town_or_guild())
    {
        _chara_filter_town();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::lesimas)
    {
        _chara_filter_lesimas();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::the_void)
    {
        _chara_filter_the_void();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::dragons_nest)
    {
        _chara_filter_dragons_nest();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::crypt_of_the_damned)
    {
        _chara_filter_crypt_of_the_damned();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::tower_of_fire)
    {
        _chara_filter_tower_of_fire();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::ancient_castle)
    {
        _chara_filter_ancient_castle();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::pyramid)
    {
        _chara_filter_pyramid();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::lumiest_graveyard
        || game_data.current_map == mdata_t::MapId::truce_ground)
    {
        _chara_filter_lumiest_graveyard();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::quest)
    {
        _chara_filter_quest();
        return;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::yeeks_nest)
    {
        _chara_filter_yeeks_nest();
        return;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::minotaurs_nest)
    {
        _chara_filter_minotaurs_nest();
        return;
    }
    if (mdata_t::is_nefia(map_data.type))
    {
        _chara_filter_nefia();
        return;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::museum
        || area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        _chara_filter_museum_shop();
        return;
    }
    flt(calcobjlv(cdata.player().level), calcfixlv(Quality::bad));
}


} // namespace elona
