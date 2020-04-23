#pragma once

#include "optional.hpp"



namespace elona
{

struct Character;
struct Item;
enum class TurnResult;



void rowact_check(Character& chara);
void rowact_item(const Item& item);

void activity_handle_damage(Character& chara);
optional<TurnResult> activity_proc(Character& chara);

void activity_perform(Character& performer, const Item& instrument);
void activity_sex(Character& chara_a, optional_ref<Character> chara_b);
void activity_blending();
void activity_eating(Character& eater, Item& food);
void activity_eating_finish(Character& eater, Item& food);
void activity_others(Character& doer, optional_ref<Item> activity_item);

void spot_fishing(Character& fisher, optional_ref<Item> rod);
void spot_material(Character& chara);
void spot_digging(Character& chara);
void spot_mining_or_wall(Character& chara);
TurnResult do_dig_after_sp_check(Character& chara);
void matdelmain(int material_id, int amount = 1);
void matgetmain(int material_id, int amount = 1, int spot_type = 0);


void start_stealing(Character& thief, Item& steal_target);
void sleep_start(optional_ref<Item> bed);

} // namespace elona
