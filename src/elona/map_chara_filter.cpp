#include "area.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "data/types/type_map.hpp"
#include "game.hpp"
#include "lua_env/enums/enums.hpp"
#include "map.hpp"
#include "quest.hpp"
#include "randomgen.hpp"
#include "variables.hpp"



namespace elona
{

static void _chara_filter_quest()
{
    if (game()->executing_immediate_quest_type >= 1000)
    {
        flt(calcobjlv(quest_data.immediate().difficulty + 1),
            calcfixlv(Quality::bad));
    }
    if (game()->executing_immediate_quest_type == 1006)
    {
        fltn(u8"wild"s);
        objlv = clamp(objlv / 4, 1, 8);
    }
}

static void _chara_filter_nefia()
{
    flt(calcobjlv(game()->current_dungeon_level), calcfixlv(Quality::bad));
}

static void _process_chara_filter(const lua::WrappedFunction& chara_filter)
{
    sol::optional<sol::table> result = chara_filter.call_with_result(
        static_cast<sol::optional<sol::table>>(sol::nullopt));
    int objlv_ = 0;
    Quality fixlv_ = Quality::none;
    int dbid_ = 0;
    std::string fltn_ = "";
    int fltselect_ = 0;
    int flttypemajor_ = 0;

    if (!result)
    {
        return;
    }

    lua::ConfigTable opts(*result);

    if (auto it = opts.optional<int>("objlv"))
    {
        objlv_ = *it;
    }
    if (auto it = opts.optional<int>("level"))
    {
        objlv_ = calcobjlv(*it);
    }
    if (auto it = opts.optional<Quality>("fixlv"))
    {
        fixlv_ = *it;
    }
    if (auto it = opts.optional<Quality>("quality"))
    {
        fixlv_ = calcfixlv(*it);
    }
    if (auto it = opts.optional<std::string>("id"))
    {
        auto chara_data = the_character_db[data::InstanceId{*it}];
        if (chara_data)
        {
            dbid_ = chara_data->integer_id;
        }
        else
        {
            txt("No such character for map character filter: " + *it,
                Message::color{ColorIndex::red});
        }
    }
    if (auto it = opts.optional<std::string>("fltn"))
    {
        fltn_ = *it;
    }
    if (auto it = opts.optional<int>("fltselect"))
    {
        fltselect_ = *it;
    }
    if (auto it = opts.optional<int>("flttypemajor"))
    {
        flttypemajor_ = *it;
    }

    flt(objlv_, fixlv_);
    dbid = dbid_;
    fltselect = fltselect_;
    flttypemajor = flttypemajor_;

    if (fltn_ != "")
    {
        fltn(fltn_);
    }
}

void map_set_chara_generation_filter()
{
    dbid = 0;

    if (game()->current_map == mdata_t::MapId::quest)
    {
        _chara_filter_quest();
        return;
    }

    int map_id = area_data[game()->current_map].id;
    auto mapdef_data = the_mapdef_db[map_id];
    if (mapdef_data && mapdef_data->chara_filter)
    {
        auto& chara_filter = *mapdef_data->chara_filter;
        _process_chara_filter(chara_filter);
        return;
    }

    if (mdata_t::is_nefia(map_data.type))
    {
        _chara_filter_nefia();
        return;
    }

    flt(calcobjlv(cdata.player().level), calcfixlv(Quality::bad));
}


} // namespace elona
