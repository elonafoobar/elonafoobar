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

/**
 * @luadoc
 *
 * Enumerations for various data types. All enum variants take the
 * name of the variant as a string for its value. This means that
 * anywhere an enum value is required, you can pass a string with its
 * name instead of using the <code>Enums</code> table.
 */
namespace LuaEnums
{
extern EnumMap<DamageSource> DamageSourceTable;
extern EnumMap<ColorIndex> ColorIndexTable;
extern EnumMap<CurseState> CurseStateTable;
extern EnumMap<IdentifyState> IdentifyStateTable;
extern EnumMap<StatusAilment> StatusAilmentTable;
extern EnumMap<Element> ElementTable;
extern EnumMap<TileKind> TileKindTable;
extern EnumMap<Quality> QualityTable;
extern EnumMap<BuffType> BuffTypeTable;
extern EnumMap<mdata_t::MapType> MapTypeTable;
extern EnumMap<int> MapEntranceTypeTable;
extern EnumMap<int> MapTilesetTable;
extern EnumMap<int> GenderTable;
extern EnumMap<int> RelationTable;
extern EnumMap<int> CharaFlagTable;
extern EnumMap<int> TraitTypeTable;

void bind(sol::table&);
} // namespace LuaEnums

} // namespace lua
} // namespace elona
