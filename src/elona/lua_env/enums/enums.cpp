#include "enums.hpp"

#include "../../character.hpp"
#include "../../element.hpp"
#include "../../enums.hpp"
#include "../../item.hpp"
#include "../../map_cell.hpp"
#include "../../mdata.hpp"
#include "../../menu.hpp"
#include "../../status_ailment.hpp"
#include "../../text.hpp"
#include "../../wish.hpp"



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
        {"trap", DamageSource::trap},
        {"overcasting", DamageSource::overcasting},
        {"starvation", DamageSource::starvation},
        {"poisoning", DamageSource::poisoning},
        {"curse", DamageSource::curse},
        {"backpack_weight", DamageSource::backpack_weight},
        {"fall_from_stairs", DamageSource::fall_from_stairs},
        {"audience", DamageSource::audience},
        {"burn", DamageSource::burn},
        {"adventuring", DamageSource::adventuring},
        {"unseen_hand", DamageSource::unseen_hand},
        {"food_poisoning", DamageSource::food_poisoning},
        {"blood_loss", DamageSource::blood_loss},
        {"ether_disease", DamageSource::ether_disease},
        {"acid", DamageSource::acid},
        {"shatter", DamageSource::shatter},
        {"atomic_bomb", DamageSource::atomic_bomb},
        {"iron_maiden", DamageSource::iron_maiden},
        {"guillotine", DamageSource::guillotine},
        {"hanging", DamageSource::hanging},
        {"mochi", DamageSource::mochi},
    }};


/**
 * @luadoc
 *
 * A set of colors.
 */
EnumMap<ColorIndex> ColorIndexTable{
    "Color",
    {
        {"none", ColorIndex::none},
        {"white", ColorIndex::white},
        {"green", ColorIndex::green},
        {"red", ColorIndex::red},
        {"blue", ColorIndex::blue},
        {"orange", ColorIndex::orange},
        {"yellow", ColorIndex::yellow},
        {"grey", ColorIndex::grey},
        {"purple", ColorIndex::purple},
        {"cyan", ColorIndex::cyan},
        {"light_red", ColorIndex::light_red},
        {"gold", ColorIndex::gold},
        {"white2", ColorIndex::white2},
        {"light_brown", ColorIndex::light_brown},
        {"dark_green", ColorIndex::dark_green},
        {"light_grey", ColorIndex::light_grey},
        {"pale_red", ColorIndex::pale_red},
        {"light_blue", ColorIndex::light_blue},
        {"light_purple", ColorIndex::light_purple},
        {"light_green", ColorIndex::light_green},
        {"yellow_green", ColorIndex::yellow_green},
        {"random_furniture", ColorIndex::random_furniture},
        {"random_seeded", ColorIndex::random_seeded},
        {"random_any", ColorIndex::random_any},
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
                                        {"doomed", CurseState::doomed},
                                        {"cursed", CurseState::cursed},
                                        {"none", CurseState::none},
                                        {"blessed", CurseState::blessed},
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
        {"unidentified", IdentifyState::unidentified},
        {"partly", IdentifyState::partly},
        {"almost", IdentifyState::almost},
        {"completely", IdentifyState::completely},
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
        {"blinded", StatusAilment::blinded},
        {"confused", StatusAilment::confused},
        {"paralyzed", StatusAilment::paralyzed},
        {"poisoned", StatusAilment::poisoned},
        {"sleep", StatusAilment::sleep},
        {"fear", StatusAilment::fear},
        {"dimmed", StatusAilment::dimmed},
        {"bleeding", StatusAilment::bleeding},
        {"drunk", StatusAilment::drunk},
        {"insane", StatusAilment::insane},
        {"sick", StatusAilment::sick},
    }};

/**
 * @luadoc
 *
 * A type of elemental damage.
 */
EnumMap<Element> ElementTable{"Element",
                              {
                                  {"fire", Element::fire},
                                  {"cold", Element::cold},
                                  {"lightning", Element::lightning},
                                  {"darkness", Element::darkness},
                                  {"mind", Element::mind},
                                  {"poison", Element::poison},
                                  {"nether", Element::nether},
                                  {"sound", Element::sound},
                                  {"nerve", Element::nerve},
                                  {"chaos", Element::chaos},
                                  {"magic", Element::magic},
                                  {"cut", Element::cut},
                                  {"ether", Element::ether},
                                  {"acid", Element::acid},
                                  {"vorpal", Element::vorpal},
                              }};


/**
 * @luadoc
 *
 * A kind of tile to be used with <code>Map.generate_tile</code>.
 * @see Map.generate_tile
 */
EnumMap<TileKind> TileKindTable{"TileKind",
                                {
                                    {"normal", TileKind::normal},
                                    {"wall", TileKind::wall},
                                    {"tunnel", TileKind::tunnel},
                                    {"room", TileKind::room},
                                    {"fog", TileKind::fog},
                                }};

/**
 * @luadoc
 *
 * The quality of randomly generated equipment.
 */
EnumMap<Quality> QualityTable{"Quality",
                              {
                                  {"none", Quality::none},
                                  {"bad", Quality::bad},
                                  {"good", Quality::good},
                                  {"great", Quality::great},
                                  {"miracle", Quality::miracle},
                                  {"godly", Quality::godly},
                                  {"special", Quality::special},
                              }};

/**
 * @luadoc
 *
 * The type of a buff. Food buffs are lost when vomiting. Hex buffs can be
 * removed with Holy Light/Vanquish Hex, and can be resisted.
 */
EnumMap<BuffType> BuffTypeTable{"Buff",
                                {
                                    {"buff", BuffType::buff},
                                    {"hex", BuffType::hex},
                                    {"food", BuffType::food},
                                }};

/**
 * @luadoc
 *
 * The type of a map.
 */
EnumMap<mdata_t::MapType> MapTypeTable{
    "MapType",
    {
        {"world_map", mdata_t::MapType::world_map},
        {"guild", mdata_t::MapType::guild},
        {"town", mdata_t::MapType::town},
        {"field", mdata_t::MapType::field},
        {"player_owned", mdata_t::MapType::player_owned},
        {"shelter", mdata_t::MapType::shelter},
        {"temporary", mdata_t::MapType::temporary},
        {"dungeon", mdata_t::MapType::dungeon},
        {"dungeon_tower", mdata_t::MapType::dungeon_tower},
        {"dungeon_forest", mdata_t::MapType::dungeon_forest},
        {"dungeon_castle", mdata_t::MapType::dungeon_castle},
    }};

/**
 * @luadoc
 *
 * Determines how the player should be spawned in a map when entering it for the
 * first time.
 */
EnumMap<int> MapEntranceTypeTable{"MapEntranceType",
                                  {
                                      {"stair_up", 1},
                                      {"stair_down", 2},
                                      {"custom", 3},
                                      {"center", 4},
                                      {"random", 5},
                                      {"world_map_pos", 6},
                                      {"specified", 7},
                                      {"south", 8},
                                  }};

/**
 * @luadoc
 *
 * Indicates which map tile atlas to use for a map.
 */
EnumMap<int> MapTilesetTable{"MapTileset",
                             {
                                 {"normal", 1},
                                 {"world_map", 2},
                             }};

// TODO: convert the following to enum class.

/**
 * @luadoc
 *
 * Possible genders of a character.
 */
EnumMap<int> GenderTable{"Gender",
                         {
                             {"random", -1},
                             {"male", 0},
                             {"female", 1},
                         }};

/**
 * @luadoc
 *
 * Relationship of a character to the player.
 */
EnumMap<int> RelationshipTable{"Relationship",
                               {
                                   {"aggressive", -3},
                                   {"nonaggressive", -2},
                                   {"unconcerned", -1},
                                   {"neutral", 0},
                                   {"friend", 10},
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
        {"is_floating", 5},
        {"is_invisible", 6},
        {"can_see_invisible", 7},
        {"is_immune_to_confusion", 8},
        {"is_immune_to_blindness", 9},
        {"is_immune_to_fear", 10},
        {"is_immune_to_sleep", 11},
        {"is_immune_to_paralyzation", 12},
        {"is_immune_to_poison", 13},
        {"can_digest_rotten_food", 14},
        {"is_protected_from_thieves", 15},
        {"is_incognito", 16},
        {"drops_gold", 17},
        {"explodes", 18},
        {"is_death_master", 19},
        {"can_cast_rapid_magic", 20},
        {"has_lay_hand", 21},
        {"is_suitable_for_mount", 22},
        {"splits", 23},
        {"has_cursed_equipments", 24},
        {"is_unsuitable_for_mount", 25},
        {"is_immune_to_elemental_damage", 26},
        {"splits2", 27},
        {"is_metal", 28},
        {"cures_bleeding_quickly", 29},
        {"has_power_bash", 30},
        {"is_immune_to_mine", 31},
        {"is_quick_tempered", 32},

        // _mutable flags
        {"is_livestock", 960},
        {"is_married", 961},
        {"has_made_gene", 962},
        {"is_escorted", 963},
        {"is_temporary", 964},
        {"is_silent", 965},
        {"has_been_used_stethoscope", 966},
        {"has_own_sprite", 967},
        {"is_leashed", 968},
        {"is_contracting", 969},
        {"is_quest_target", 970},
        {"is_escorted_in_sub_quest", 971},
        {"will_explode_soon", 972},
        {"is_sentenced_daeth", 973},
        {"is_lay_hand_available", 974},
        {"is_ridden", 975},
        {"is_lord_of_dungeon", 976},
        {"has_own_name", 977},
        {"is_pregnant", 978},
        {"is_not_attacked_by_enemy", 979},
        {"is_contracting_with_reaper", 980},
        {"needs_refreshing_status", 981},
        {"visited_just_now", 982},
        {"breaks_into_debris", 983},
        {"is_best_friend", 984},
        {"is_hung_on_sand_bag", 985},
        {"has_anorexia", 986},
        {"was_passed_item_by_you_just_now", 987},
        {"cures_mp_frequently", 988},
        {"has_custom_talk", 989},
        {"has_learned_words", 990},
        {"only_christmas", 991},
    }};



/**
 * @luadoc
 *
 * The types of traits available.
 */
EnumMap<int> TraitTypeTable{"TraitType",
                            {
                                {"feat", 0},
                                {"mutation", 1},
                                {"nature", 2},
                                {"ether_disease", 3},
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
        {"allies", CharaFindLocation::allies},
        {"others", CharaFindLocation::others},
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
        {"player_inventory", ItemFindLocation::player_inventory},
        {"ground", ItemFindLocation::ground},
        {"player_inventory_and_ground",
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
        {"call_back", ControlAllyOperation::call_back},
        {"sell", ControlAllyOperation::sell},
        {"pet_arena", ControlAllyOperation::pet_arena},
        {"staying", ControlAllyOperation::staying},
        {"investigate", ControlAllyOperation::investigate},
        {"gene_engineer", ControlAllyOperation::gene_engineer},
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
        {"character", RandomTitleType::character},
        {"weapon", RandomTitleType::weapon},
        {"party", RandomTitleType::party},
        {"living_weapon", RandomTitleType::living_weapon},
    }};

/**
 * @luadoc
 *
 * Match type to use with Wish.match.
 * @see Wish.match
 */
EnumMap<WishMatchType> WishMatchTypeTable{
    "WishMatchType",
    {
        {"prefix", WishMatchType::prefix},
        {"suffix", WishMatchType::suffix},
        {"include", WishMatchType::include},
        {"perfect", WishMatchType::perfect},
    }};

/**
 * @luadoc
 *
 * Wish hook point to use with Wish.add.
 * @see Wish.add
 */
EnumMap<WishHook> WishHookTable{
    "WishHook",
    {
        {"first", WishHook::first},
        {"before_vanilla_special", WishHook::before_vanilla_special},
        {"after_vanilla_special", WishHook::after_vanilla_special},
        {"before_vanilla_item", WishHook::before_vanilla_item},
        {"after_vanilla_item", WishHook::after_vanilla_item},
        {"before_vanilla_skill", WishHook::before_vanilla_skill},
        {"after_vanilla_skill", WishHook::after_vanilla_skill},
        {"last", WishHook::last},
    }};

} // namespace LuaEnums

} // namespace lua
} // namespace elona
