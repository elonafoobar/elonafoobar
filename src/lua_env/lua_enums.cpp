#include "lua_enums.hpp"

namespace elona
{
namespace lua
{

enum_map<damage_source_t> DamageSource{{
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

enum_map<color_index_t> Color{{
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

enum_map<identification_state_t> IdentifyState{{
    {"Unidentified", identification_state_t::unidentified},
    {"Partly", identification_state_t::partly_identified},
    {"Almost", identification_state_t::almost_identified},
    {"Completely", identification_state_t::completely_identified},
}};

enum_map<status_ailment_t> StatusAilment{{
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

enum_map<element_t> Element{{
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

enum_map<tile_kind_t> TileKind{{
    {"Normal", tile_kind_t::normal},
    {"Wall", tile_kind_t::wall},
    {"Tunnel", tile_kind_t::tunnel},
    {"Room", tile_kind_t::room},
    {"Fog", tile_kind_t::fog},
}};


} // namespace lua

} // namespace elona
