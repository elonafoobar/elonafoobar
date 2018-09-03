#include "lua_enums.hpp"

namespace elona
{
namespace lua
{

namespace LuaEnums
{
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

EnumMap<CurseState> CurseStateTable{"CurseState",
                                   {
                                       {"Doomed", CurseState::doomed},
                                       {"Cursed", CurseState::cursed},
                                       {"None", CurseState::none},
                                       {"Blessed", CurseState::blessed},
                                   }};

EnumMap<IdentifyState> IdentifyStateTable{
    "IdentifyState",
    {
        {"Unidentified", IdentifyState::unidentified},
        {"Partly", IdentifyState::partly_identified},
        {"Almost", IdentifyState::almost_identified},
        {"Completely", IdentifyState::completely_identified},
    }};

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

EnumMap<TileKind> TileKindTable{"TileKind",
                               {
                                   {"Normal", TileKind::normal},
                                   {"Wall", TileKind::wall},
                                   {"Tunnel", TileKind::tunnel},
                                   {"Room", TileKind::room},
                                   {"Fog", TileKind::fog},
                               }};


// TODO: convert the following to enum class.
EnumMap<int> GenderTable{"Gender",
                     {
                         {"Random", -1},
                         {"Male", 0},
                         {"Female", 1},
                     }};

EnumMap<int> RelationTable{"Relation",
                       {
                           {"Aggressive", -3},
                           {"Nonaggressive", -2},
                           {"Unconcerned", -1},
                           {"Neutral", 0},
                           {"Friend", 10},
                       }};

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

    DamageSourceTable.bind(Enums);
    ColorIndexTable.bind(Enums);
    CurseStateTable.bind(Enums);
    IdentifyStateTable.bind(Enums);
    StatusAilmentTable.bind(Enums);
    ElementTable.bind(Enums);
    TileKindTable.bind(Enums);
    GenderTable.bind(Enums);
    RelationTable.bind(Enums);
    CharaFlagTable.bind(Enums);
}

} // namespace lua
} // namespace elona
