#pragma once

#include "data/id.hpp"
#include "eobject/eobject.hpp"
#include "optional.hpp"
#include "typedefs.hpp"



namespace elona
{

struct Character;
struct Item;
enum class TurnResult;



struct Activity
{
    /// ID
    data::InstanceId id{};

    /// Left turns
    lua_int turns{};

    /// Whether the activity is interrupted (mainly by enemy's attack).
    bool is_interrupted{};

    /// TODO
    OptionalItemRef item{};

#if 0
    /// Extension data
    lua_table ext{};
#endif


    explicit operator bool() const
    {
        return id != "";
    }


    void finish()
    {
        id = "";
        turns = 0;
        is_interrupted = false;
        item = nullptr;
    }
};



void rowact_check(Character& chara);
void rowact_item(const ItemRef& item);

void activity_handle_damage(Character& chara);
optional<TurnResult> activity_proc(Character& chara);

void activity_perform(Character& performer, ItemRef instrument);
void activity_sex(Character& chara_a, optional_ref<Character> chara_b);
void activity_blending();
void activity_eating(Character& eater, const ItemRef& food);
void activity_eating_finish(Character& eater, const ItemRef& food);
void activity_sleep(Character& doer, const OptionalItemRef& bed);
void activity_build_shelter(Character& doer, const ItemRef& shelter);
void activity_enter_shelter(Character& doer, const ItemRef& shelter);
void activity_harvest(Character& doer, const ItemRef& crop);
void activity_study(Character& doer, const ItemRef& textbook);
void activity_steal(Character& doer, const ItemRef& steal_target);

void spot_fishing(Character& fisher, OptionalItemRef rod);
void spot_material(Character& chara);
void spot_digging(Character& chara);
void spot_mining_or_wall(Character& chara);
TurnResult do_dig_after_sp_check(Character& chara);

void sleep_start(const OptionalItemRef& bed);

} // namespace elona
