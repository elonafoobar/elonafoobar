#include "area.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "data/types/type_map.hpp"
#include "gdata.hpp"
#include "lua_env/enums/enums.hpp"
#include "map.hpp"
#include "quest.hpp"
#include "variables.hpp"

namespace elona
{

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
    if (auto it = opts.optional<std::string>("fixlv"))
    {
        fixlv_ =
            lua::LuaEnums::QualityTable.get_from_string(*it, Quality::none);
    }
    if (auto it = opts.optional<std::string>("quality"))
    {
        fixlv_ = calcfixlv(
            lua::LuaEnums::QualityTable.get_from_string(*it, Quality::none));
    }
    if (auto it = opts.optional<std::string>("id"))
    {
        auto chara_data = the_character_db[*it];
        if (chara_data)
        {
            dbid_ = chara_data->id;
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

    if (game_data.current_map == mdata_t::MapId::quest)
    {
        _chara_filter_quest();
        return;
    }

    auto mapdef_data = the_mapdef_db[game_data.current_map];
    if (mapdef_data && mapdef_data->chara_filter)
    {
        auto& chara_filter = *mapdef_data->chara_filter;
        _process_chara_filter(chara_filter);
        return;
    }

    flt(calcobjlv(cdata.player().level), calcfixlv(Quality::bad));
}


} // namespace elona
