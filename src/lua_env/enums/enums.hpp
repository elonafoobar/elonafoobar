#pragma once
#include "../../element.hpp"
#include "../../enums.hpp"
#include "../../map_cell.hpp"
#include "../../mdata.hpp"
#include "../../status_ailment.hpp"
#include "../lua_enums.hpp"

namespace elona
{
namespace lua
{
namespace LuaEnums
{
extern EnumMap<DamageSource> DamageSourceTable;
extern EnumMap<ColorIndex> ColorIndexTable;
extern EnumMap<CurseState> CurseStateTable;
extern EnumMap<IdentifyState> IdentifyStateTable;
extern EnumMap<StatusAilment> StatusAilmentTable;
extern EnumMap<Element> ElementTable;
extern EnumMap<TileKind> TileKindTable;
extern EnumMap<mdata_t::MapType> MapTypeTable;
extern EnumMap<int> MapEntranceTypeTable;
extern EnumMap<int> MapTilesetTable;
extern EnumMap<int> GenderTable;
extern EnumMap<int> RelationTable;
extern EnumMap<int> CharaFlagTable;

void bind(sol::table&);
} // namespace LuaEnums

} // namespace lua
} // namespace elona
