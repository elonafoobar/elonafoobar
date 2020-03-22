#pragma once

#include "../lua_enums.hpp"



namespace elona
{

enum class DamageSource;
enum class ColorIndex;
enum class CurseState;
enum class IdentifyState;
enum class StatusAilment;
enum class Element;
enum class TileKind;
enum class Quality;
enum class BuffType;
namespace mdata_t
{
enum class MapType;
}
enum class CharaFindLocation;
enum class ItemFindLocation;
enum class ControlAllyOperation;
enum class RandomTitleType;
enum class WishMatchType;
enum class WishHook;



namespace lua
{

/**
 * @luadoc
 *
 * Enumerations for various data types. All enum variants take the
 * name of the variant as a string for its value. This means that
 * anywhere an enum value is required, you can pass a string with its
 * name.
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
extern EnumMap<int> RelationshipTable;
extern EnumMap<int> CharaFlagTable;
extern EnumMap<int> TraitTypeTable;
extern EnumMap<CharaFindLocation> CharaFindLocationTable;
extern EnumMap<ItemFindLocation> ItemFindLocationTable;
extern EnumMap<ControlAllyOperation> ControlAllyOperationTable;
extern EnumMap<RandomTitleType> RandomTitleTypeTable;
extern EnumMap<WishMatchType> WishMatchTypeTable;
extern EnumMap<WishHook> WishHookTable;

} // namespace LuaEnums

} // namespace lua
} // namespace elona
