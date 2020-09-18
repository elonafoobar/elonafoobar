#pragma once

#include "eobject/forward.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;
struct Item;
enum class TurnResult;



void rowact_check(Character& chara);
void rowact_item(const ItemRef& item);

void activity_handle_damage(Character& chara);
optional<TurnResult> activity_proc(Character& chara);

void activity_perform(Character& performer, ItemRef instrument);
void activity_sex(Character& chara_a, optional_ref<Character> chara_b);
void activity_blending();
void activity_eating(Character& eater, const ItemRef& food);
void activity_eating_finish(Character& eater, const ItemRef& food);
void activity_others(Character& doer, const OptionalItemRef& activity_item);

void spot_fishing(Character& fisher, OptionalItemRef rod);
void spot_material(Character& chara);
void spot_digging(Character& chara);
void spot_mining_or_wall(Character& chara);
TurnResult do_dig_after_sp_check(Character& chara);


void start_stealing(Character& thief, ItemRef steal_target);
void sleep_start(const OptionalItemRef& bed);

} // namespace elona
