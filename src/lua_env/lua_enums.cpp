#include "lua_enums.hpp"

namespace elona
{
namespace lua
{

namespace LuaEnums
{
enum_map<damage_source_t> DamageSource{
    "DamageSource",
    {
        {"Trap", damage_source_t::trap},
        {"Overcasting", damage_source_t::overcasting},
        {"Starvation", damage_source_t::starvation},
        {"Poisoning", damage_source_t::poisoning},
        {"Curse", damage_source_t::curse},
        {"BackpackWeight", damage_source_t::backpack_weight},
        {"FallFromStairs", damage_source_t::fall_from_stairs},
        {"Audience", damage_source_t::audience},
        {"Burn", damage_source_t::burn},
        {"Adventuring", damage_source_t::adventuring},
        {"UnseenHand", damage_source_t::unseen_hand},
        {"FoodPoisoning", damage_source_t::food_poisoning},
        {"BloodLoss", damage_source_t::blood_loss},
        {"EtherDisease", damage_source_t::ether_disease},
        {"Acid", damage_source_t::acid},
        {"Shatter", damage_source_t::shatter},
        {"AtomicBomb", damage_source_t::atomic_bomb},
        {"IronMaiden", damage_source_t::iron_maiden},
        {"Guillotine", damage_source_t::guillotine},
        {"Hanging", damage_source_t::hanging},
        {"Mochi", damage_source_t::mochi},
    }};

enum_map<color_index_t> Color{
    "Color",
    {
        {"None", color_index_t::none},
        {"White", color_index_t::white},
        {"Green", color_index_t::green},
        {"Red", color_index_t::red},
        {"Blue", color_index_t::blue},
        {"Orange", color_index_t::orange},
        {"Yellow", color_index_t::yellow},
        {"Grey", color_index_t::grey},
        {"Purple", color_index_t::purple},
        {"Cyan", color_index_t::cyan},
        {"LightRed", color_index_t::light_red},
        {"Gold", color_index_t::gold},
        {"White2", color_index_t::white2},
        {"LightBrown", color_index_t::light_brown},
        {"DarkGreen", color_index_t::dark_green},
        {"LightGrey", color_index_t::light_grey},
        {"PaleRed", color_index_t::pale_red},
        {"LightBlue", color_index_t::light_blue},
        {"LightPurple", color_index_t::light_purple},
        {"LightGreen", color_index_t::light_green},
        {"YellowGreen", color_index_t::yellow_green},
        {"RandomFurniture", color_index_t::random_furniture},
        {"RandomSeeded", color_index_t::random_seeded},
        {"RandomAny", color_index_t::random_any},
    }};

enum_map<curse_state_t> CurseState{"CurseState",
                                   {
                                       {"Doomed", curse_state_t::doomed},
                                       {"Cursed", curse_state_t::cursed},
                                       {"None", curse_state_t::none},
                                       {"Blessed", curse_state_t::blessed},
                                   }};

enum_map<identification_state_t> IdentifyState{
    "IdentifyState",
    {
        {"Unidentified", identification_state_t::unidentified},
        {"Partly", identification_state_t::partly_identified},
        {"Almost", identification_state_t::almost_identified},
        {"Completely", identification_state_t::completely_identified},
    }};

enum_map<status_ailment_t> StatusAilment{
    "StatusAilment",
    {
        {"Blinded", status_ailment_t::blinded},
        {"Confused", status_ailment_t::confused},
        {"Paralyzed", status_ailment_t::paralyzed},
        {"Poisoned", status_ailment_t::poisoned},
        {"Sleep", status_ailment_t::sleep},
        {"Fear", status_ailment_t::fear},
        {"Dimmed", status_ailment_t::dimmed},
        {"Bleeding", status_ailment_t::bleeding},
        {"Drunk", status_ailment_t::drunk},
        {"Insane", status_ailment_t::insane},
        {"Sick", status_ailment_t::sick},
    }};

enum_map<element_t> Element{"Element",
                            {
                                {"Fire", element_t::fire},
                                {"Cold", element_t::cold},
                                {"Lightning", element_t::lightning},
                                {"Darkness", element_t::darkness},
                                {"Mind", element_t::mind},
                                {"Poison", element_t::poison},
                                {"Nether", element_t::nether},
                                {"Sound", element_t::sound},
                                {"Nerve", element_t::nerve},
                                {"Chaos", element_t::chaos},
                                {"Magic", element_t::magic},
                                {"Cut", element_t::cut},
                                {"Ether", element_t::ether},
                                {"Acid", element_t::acid},
                            }};

enum_map<tile_kind_t> TileKind{"TileKind",
                               {
                                   {"Normal", tile_kind_t::normal},
                                   {"Wall", tile_kind_t::wall},
                                   {"Tunnel", tile_kind_t::tunnel},
                                   {"Room", tile_kind_t::room},
                                   {"Fog", tile_kind_t::fog},
                               }};


// TODO: convert the following to enum class.
enum_map<int> Gender{"Gender",
                     {
                         {"Random", -1},
                         {"Male", 0},
                         {"Female", 1},
                     }};

enum_map<int> Relation{"Relation",
                       {
                           {"Aggressive", -3},
                           {"Nonaggressive", -2},
                           {"Unconcerned", -1},
                           {"Neutral", 0},
                           {"Friend", 10},
                       }};

enum_map<int> CharaFlag{
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
        {"DoesNotSearchEnemy", 979},
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

} // namespace LuaEnums

void LuaEnums::bind(sol::table& core)
{
    sol::table Enums = core.create_named("Enums");

    DamageSource.bind(Enums);
    Color.bind(Enums);
    CurseState.bind(Enums);
    IdentifyState.bind(Enums);
    StatusAilment.bind(Enums);
    Element.bind(Enums);
    TileKind.bind(Enums);
    Gender.bind(Enums);
    Relation.bind(Enums);
    CharaFlag.bind(Enums);
}

} // namespace lua
} // namespace elona
