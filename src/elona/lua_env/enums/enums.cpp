#include "enums.hpp"

namespace elona
{
namespace lua
{

/**
 * NOTE: The declaration style of the enum tables here is important for
 * documentation generation purposes. They must be defined as initializer lists.
 */
namespace LuaEnums
{

/**
 * @luadoc
 *
 * A source of damage to be used with <code>LuaCharacter.damage_hp</code>.
 */
EnumMap<DamageSource> DamageSourceTable{
    "DamageSource",
    {
        {"Trap", DamageSource::trap},
        {"Overcasting", DamageSource::overcasting},
        {"Starvation", DamageSource::starvation},
        {"Poisoning", DamageSource::poisoning},
        {"Curse", DamageSource::curse},
        {"BackpackWeight", DamageSource::backpack_weight},
        {"FallFromStairs", DamageSource::fall_from_stairs},
        {"Audience", DamageSource::audience},
        {"Burn", DamageSource::burn},
        {"Adventuring", DamageSource::adventuring},
        {"UnseenHand", DamageSource::unseen_hand},
        {"FoodPoisoning", DamageSource::food_poisoning},
        {"BloodLoss", DamageSource::blood_loss},
        {"EtherDisease", DamageSource::ether_disease},
        {"Acid", DamageSource::acid},
        {"Shatter", DamageSource::shatter},
        {"AtomicBomb", DamageSource::atomic_bomb},
        {"IronMaiden", DamageSource::iron_maiden},
        {"Guillotine", DamageSource::guillotine},
        {"Hanging", DamageSource::hanging},
        {"Mochi", DamageSource::mochi},
    }};


/**
 * @luadoc
 *
 * A set of colors.
 */
EnumMap<ColorIndex> ColorIndexTable{
    "Color",
    {
        {"None", ColorIndex::none},
        {"White", ColorIndex::white},
        {"Green", ColorIndex::green},
        {"Red", ColorIndex::red},
        {"Blue", ColorIndex::blue},
        {"Orange", ColorIndex::orange},
        {"Yellow", ColorIndex::yellow},
        {"Grey", ColorIndex::grey},
        {"Purple", ColorIndex::purple},
        {"Cyan", ColorIndex::cyan},
        {"LightRed", ColorIndex::light_red},
        {"Gold", ColorIndex::gold},
        {"White2", ColorIndex::white2},
        {"LightBrown", ColorIndex::light_brown},
        {"DarkGreen", ColorIndex::dark_green},
        {"LightGrey", ColorIndex::light_grey},
        {"PaleRed", ColorIndex::pale_red},
        {"LightBlue", ColorIndex::light_blue},
        {"LightPurple", ColorIndex::light_purple},
        {"LightGreen", ColorIndex::light_green},
        {"YellowGreen", ColorIndex::yellow_green},
        {"RandomFurniture", ColorIndex::random_furniture},
        {"RandomSeeded", ColorIndex::random_seeded},
        {"RandomAny", ColorIndex::random_any},
    }};


/**
 * @luadoc
 *
 * The curse state of an item.
 * @usage local item = Item.create(10, 10, "core.putitoro", 3)
 * item.curse_state = "Blessed"
 */
EnumMap<CurseState> CurseStateTable{"CurseState",
                                    {
                                        {"Doomed", CurseState::doomed},
                                        {"Cursed", CurseState::cursed},
                                        {"None", CurseState::none},
                                        {"Blessed", CurseState::blessed},
                                    }};


/**
 * @luadoc
 *
 * The identify state of an item.
 * @usage local item = Item.create(10, 10, "core.putitoro", 3)
 * item.identify_state = "Completely"
 */
EnumMap<IdentifyState> IdentifyStateTable{
    "IdentifyState",
    {
        {"Unidentified", IdentifyState::unidentified},
        {"Partly", IdentifyState::partly_identified},
        {"Almost", IdentifyState::almost_identified},
        {"Completely", IdentifyState::completely_identified},
    }};


/**
 * @luadoc
 *
 * A status effect applicable to a character.
 * @see LuaCharacter.apply_ailment
 */
EnumMap<StatusAilment> StatusAilmentTable{
    "StatusAilment",
    {
        {"Blinded", StatusAilment::blinded},
        {"Confused", StatusAilment::confused},
        {"Paralyzed", StatusAilment::paralyzed},
        {"Poisoned", StatusAilment::poisoned},
        {"Sleep", StatusAilment::sleep},
        {"Fear", StatusAilment::fear},
        {"Dimmed", StatusAilment::dimmed},
        {"Bleeding", StatusAilment::bleeding},
        {"Drunk", StatusAilment::drunk},
        {"Insane", StatusAilment::insane},
        {"Sick", StatusAilment::sick},
    }};

/**
 * @luadoc
 *
 * A type of elemental damage.
 */
EnumMap<Element> ElementTable{"Element",
                              {
                                  {"Fire", Element::fire},
                                  {"Cold", Element::cold},
                                  {"Lightning", Element::lightning},
                                  {"Darkness", Element::darkness},
                                  {"Mind", Element::mind},
                                  {"Poison", Element::poison},
                                  {"Nether", Element::nether},
                                  {"Sound", Element::sound},
                                  {"Nerve", Element::nerve},
                                  {"Chaos", Element::chaos},
                                  {"Magic", Element::magic},
                                  {"Cut", Element::cut},
                                  {"Ether", Element::ether},
                                  {"Acid", Element::acid},
                              }};


/**
 * @luadoc
 *
 * A kind of tile to be used with <code>Map.generate_tile</code>.
 * @see Map.generate_tile
 */
EnumMap<TileKind> TileKindTable{"TileKind",
                                {
                                    {"Normal", TileKind::normal},
                                    {"Wall", TileKind::wall},
                                    {"Tunnel", TileKind::tunnel},
                                    {"Room", TileKind::room},
                                    {"Fog", TileKind::fog},
                                }};

/**
 * @luadoc
 *
 * The quality of randomly generated equipment.
 */
EnumMap<Quality> QualityTable{"Quality",
                              {
                                  {"None", Quality::none},
                                  {"Bad", Quality::bad},
                                  {"Good", Quality::good},
                                  {"Great", Quality::great},
                                  {"Miracle", Quality::miracle},
                                  {"Godly", Quality::godly},
                                  {"Special", Quality::special},
                              }};

/**
 * @luadoc
 *
 * The type of a buff. Food buffs are lost when vomiting. Hex buffs can be
 * removed with Holy Light/Vanquish Hex, and can be resisted.
 */
EnumMap<BuffType> BuffTypeTable{"Buff",
                                {
                                    {"Buff", BuffType::buff},
                                    {"Hex", BuffType::hex},
                                    {"Food", BuffType::food},
                                }};

/**
 * @luadoc
 *
 * The type of a map.
 */
EnumMap<mdata_t::MapType> MapTypeTable{
    "MapType",
    {
        {"WorldMap", mdata_t::MapType::world_map},
        {"Guild", mdata_t::MapType::guild},
        {"Town", mdata_t::MapType::town},
        {"Field", mdata_t::MapType::field},
        {"PlayerOwned", mdata_t::MapType::player_owned},
        {"Shelter", mdata_t::MapType::shelter},
        {"Temporary", mdata_t::MapType::temporary},
        {"Dungeon", mdata_t::MapType::dungeon},
        {"DungeonTower", mdata_t::MapType::dungeon_tower},
        {"DungeonForest", mdata_t::MapType::dungeon_forest},
        {"DungeonCastle", mdata_t::MapType::dungeon_castle},
    }};

/**
 * @luadoc
 *
 * Determines how the player should be spawned in a map when entering it for the
 * first time.
 */
EnumMap<int> MapEntranceTypeTable{"MapEntranceType",
                                  {
                                      {"StairUp", 1},
                                      {"StairDown", 2},
                                      {"Custom", 3},
                                      {"Center", 4},
                                      {"Random", 5},
                                      {"WorldMapPos", 6},
                                      {"Specified", 7},
                                      {"South", 8},
                                  }};

/**
 * @luadoc
 *
 * Indicates which map tile atlas to use for a map.
 */
EnumMap<int> MapTilesetTable{"MapTileset",
                             {
                                 {"Normal", 1},
                                 {"WorldMap", 2},
                             }};

// TODO: convert the following to enum class.

/**
 * @luadoc
 *
 * Possible genders of a character.
 */
EnumMap<int> GenderTable{"Gender",
                         {
                             {"Random", -1},
                             {"Male", 0},
                             {"Female", 1},
                         }};

/**
 * @luadoc
 *
 * Relationship of a character to the player.
 */
EnumMap<int> RelationTable{"Relation",
                           {
                               {"Aggressive", -3},
                               {"Nonaggressive", -2},
                               {"Unconcerned", -1},
                               {"Neutral", 0},
                               {"Friend", 10},
                           }};


/**
 * @luadoc
 *
 * A flag that can be set on a character. The first 32 flags (up to
 * <code>IsQuickTempered</code>) are "intrinsic" and will be reset
 * when the character is refreshed.
 * @see LuaCharacter.set_flag
 */
EnumMap<int> CharaFlagTable{
    "CharaFlag",
    {
        // Intrinsic flags (reset on every character refresh)
        {"IsFloating", 5},
        {"IsInvisible", 6},
        {"CanSeeInvisible", 7},
        {"IsImmuneToConfusion", 8},
        {"IsImmuneToBlindness", 9},
        {"IsImmuneToFear", 10},
        {"IsImmuneToSleep", 11},
        {"IsImmuneToParalyzation", 12},
        {"IsImmuneToPoison", 13},
        {"CanDigestRottenFood", 14},
        {"IsProtectedFromThieves", 15},
        {"IsIncognito", 16},
        {"DropsGold", 17},
        {"Explodes", 18},
        {"IsDeathMaster", 19},
        {"CanCastRapidMagic", 20},
        {"HasLayHand", 21},
        {"IsSuitableForMount", 22},
        {"Splits", 23},
        {"HasCursedEquipments", 24},
        {"IsUnsuitableForMount", 25},
        {"IsImmuneToElementalDamage", 26},
        {"Splits2", 27},
        {"IsMetal", 28},
        {"CuresBleedingQuickly", 29},
        {"HasPowerBash", 30},
        {"IsImmuneToMine", 31},
        {"IsQuickTempered", 32},

        // Mutable flags
        {"IsLivestock", 960},
        {"IsMarried", 961},
        {"HasMadeGene", 962},
        {"IsEscorted", 963},
        {"IsTemporary", 964},
        {"IsSilent", 965},
        {"HasBeenUsedStethoscope", 966},
        {"HasOwnSprite", 967},
        {"IsLeashed", 968},
        {"IsContracting", 969},
        {"IsQuestTarget", 970},
        {"IsEscortedInSubQuest", 971},
        {"WillExplodeSoon", 972},
        {"IsSentencedDaeth", 973},
        {"IsLayHandAvailable", 974},
        {"IsRidden", 975},
        {"IsLordOfDungeon", 976},
        {"HasOwnName", 977},
        {"IsPregnant", 978},
        {"IsNotAttackedByEnemy", 979},
        {"IsContractingWithReaper", 980},
        {"NeedsRefreshingStatus", 981},
        {"VisitedJustNow", 982},
        {"BreaksIntoDebris", 983},
        {"IsBestFriend", 984},
        {"IsHungOnSandBag", 985},
        {"HasAnorexia", 986},
        {"WasPassedItemByYouJustNow", 987},
        {"CuresMpFrequently", 988},
        {"HasCustomTalk", 989},
        {"HasLearnedWords", 990},
        {"OnlyChristmas", 991},
    }};



/**
 * @luadoc
 *
 * The types of traits available.
 */
EnumMap<int> TraitTypeTable{"TraitType",
                            {
                                {"Feat", 0},
                                {"Mutation", 1},
                                {"Nature", 2},
                                {"EtherDisease", 3},
                            }};

/**
 * @luadoc
 *
 * Location to search for characters using Chara.find.
 * @see Chara.find
 */
EnumMap<CharaFindLocation> CharaFindLocationTable{
    "CharaFindLocation",
    {
        {"Allies", CharaFindLocation::allies},
        {"Others", CharaFindLocation::others},
    }};

/**
 * @luadoc
 *
 * Location to search for items using Item.find.
 * @see Item.find
 */
EnumMap<ItemFindLocation> ItemFindLocationTable{
    "ItemFindLocation",
    {
        {"PlayerInventory", ItemFindLocation::player_inventory},
        {"Ground", ItemFindLocation::ground},
        {"PlayerInventoryAndGround",
         ItemFindLocation::player_inventory_and_ground},
    }};

/**
 * @luadoc
 *
 * Operation to use with Input.choose_ally.
 * @see Input.choose_ally
 */
EnumMap<ControlAllyOperation> ControlAllyOperationTable{
    "ControlAllyOperation",
    {
        {"CallBack", ControlAllyOperation::call_back},
        {"Sell", ControlAllyOperation::sell},
        {"PetArena", ControlAllyOperation::pet_arena},
        {"Staying", ControlAllyOperation::staying},
        {"Investigate", ControlAllyOperation::investigate},
        {"GeneEngineer", ControlAllyOperation::gene_engineer},
    }};

/**
 * @luadoc
 *
 * Title type to use with World.random_title.
 * @see World.random_title
 */
EnumMap<RandomTitleType> RandomTitleTypeTable{
    "RandomTitleType",
    {
        {"Character", RandomTitleType::character},
        {"Weapon", RandomTitleType::weapon},
        {"Party", RandomTitleType::party},
        {"LivingWeapon", RandomTitleType::living_weapon},
    }};

} // namespace LuaEnums

void LuaEnums::bind(sol::table& core)
{
    sol::table Enums = core.create_named("Enums");

    DamageSourceTable.bind(Enums);
    ColorIndexTable.bind(Enums);
    CurseStateTable.bind(Enums);
    IdentifyStateTable.bind(Enums);
    StatusAilmentTable.bind(Enums);
    ElementTable.bind(Enums);
    TileKindTable.bind(Enums);
    MapTypeTable.bind(Enums);
    MapEntranceTypeTable.bind(Enums);
    MapTilesetTable.bind(Enums);
    GenderTable.bind(Enums);
    RelationTable.bind(Enums);
    CharaFlagTable.bind(Enums);
    QualityTable.bind(Enums);
    TraitTypeTable.bind(Enums);
    CharaFindLocationTable.bind(Enums);
    ItemFindLocationTable.bind(Enums);
    ControlAllyOperationTable.bind(Enums);
    RandomTitleTypeTable.bind(Enums);
}

} // namespace lua
} // namespace elona
