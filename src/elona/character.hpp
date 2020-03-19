#pragma once

#include <bitset>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../util/range.hpp"
#include "consts.hpp"
#include "data/types/type_character.hpp"
#include "god.hpp"
#include "lua_env/wrapped_function.hpp"
#include "position.hpp"
#include "serialization/macros.hpp"


#define ELONA_MAX_CHARACTERS 245
#define ELONA_MAX_PARTY_CHARACTERS 57
#define ELONA_MAX_OTHER_CHARACTERS 188



namespace elona
{

struct Item;



struct Buff
{
    int id = 0;
    int power = 0;
    int turns = 0;



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Buff");

        ELONA_SERIALIZATION_STRUCT_FIELD(*this, id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, power);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, turns);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
};



struct Activity
{
    enum class Type : int
    {
        none,
        eat,
        read,
        travel,
        sleep,
        dig_wall,
        perform,
        fish,
        search_material,
        dig_ground,
        others,
        sex,
        blend,
    };

    Type type = Activity::Type::none;
    int turn = 0;
    int item = 0;


    bool is_doing_nothing() const
    {
        return type == Activity::Type::none;
    }


    bool is_doing_something() const
    {
        return !is_doing_nothing();
    }


    explicit operator bool() const
    {
        return is_doing_something();
    }


    void finish()
    {
        type = Activity::Type::none;
        turn = 0;
        item = 0;
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Activity");

        ELONA_SERIALIZATION_STRUCT_FIELD(*this, type);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, turn);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, item);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
};



struct Character
{
    enum class State : int
    {
        empty = 0,
        alive = 1,
        villager_dead = 2,
        adventurer_in_other_map = 3,
        adventurer_dead = 4,
        adventurer_empty = 5,
        pet_dead = 6,
        pet_waiting = 7,
        pet_in_other_map =
            8, // Ally failed to be placed/not participating in arena
        pet_moving_to_map = 9, // Set on pets before leaving map, restored to
                               // "alive" after initialize
        servant_being_selected = 10,
    };

    Character();

    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.

    // Index of this character into the global cdata array.
    // Used for communicating with legacy code that takes integer index
    // arguments. New code should pass Character& instead. Not serialized; set
    // on creation and load.
    int index = -1;

private:
    Character::State state_ = Character::State::empty;

public:
    Position position;
    Position next_position;
    int time_to_revive = 0;
    int vision_flag = 0;
    int image = 0;
    int sex = 0;
    int relationship = 0;
    int turn_cost = 0;
    int current_speed = 0;
    int item_which_will_be_used = 0;
    std::string portrait;
    int interest = 0;
    int time_interest_revive = 0;
    int personality = 0;
    int impression = 0;
    int talk_type = 0;
    int height = 0;
    int weight = 0;
    int birth_year = 0;
    int nutrition = 0;
    int can_talk = 0;
    Quality quality = Quality::none;
    int turn = 0;
    CharaId id = CharaId::none;
    int vision_distance = 0;
    int enemy_id = 0;
    int gold = 0;
    int platinum_coin = 0;
    int equipment_type = 0;
    int melee_attack_type = 0;
    int fame = 0;
    int experience = 0;
    int required_experience = 0;
    int speed_percentage = 0;
    int level = 0;
    int speed_percentage_in_next_turn = 0;
    int skill_bonus = 0;
    int total_skill_bonus = 0;
    int inventory_weight = 0;
    int max_inventory_weight = 0;
    int inventory_weight_type = 0;
    int max_level = 0;
    int karma = 0;
    int hp = 0;
    int max_hp = 0;
    int sp = 0;
    int max_sp = 0;
    int mp = 0;
    int max_mp = 0;
    int heal_value_per_nether_attack = 0;
    GodId god_id;
    int piety_point = 0;
    int praying_point = 0;
    int sum_of_equipment_weight = 0;
    int special_attack_type = 0;
    int rate_to_pierce = 0;
    int rate_of_critical_hit = 0;
    int speed_correction_value = 0;
    int original_relationship = 0;
    int pv = 0;
    int dv = 0;
    int hit_bonus = 0;
    int damage_bonus = 0;
    int pv_correction_value = 0;
    int dv_correction_value = 0;
    int damage_reaction_info = 0;
    int emotion_icon = 0;
    int current_map = 0;
    int current_dungeon_level = 0;
    int related_quest_id = 0;
    int direction = 0;
    int period_of_contract = 0;
    int hire_count = 0;
    int insanity = 0;
    int curse_power = 0;
    int extra_attack = 0;
    int extra_shot = 0;
    int decrease_physical_damage = 0;
    int nullify_damage = 0;
    int cut_counterattack = 0;
    int anorexia_count = 0;
    Activity activity;
    int stops_activity_if_damaged = 0;
    int quality_of_performance = 0;
    int tip_gold = 0;
    int character_role = 0;
    int shop_rank = 0;
    int activity_target = 0;
    int shop_store_id = 0;
    int time_to_restore = 0;
    int cnpc_id = 0;
    Position initial_position;
    int hate = 0;
    int ai_calm = 0;
    int ai_move = 0;
    int ai_dist = 0;
    int ai_act_sub_freq = 0;
    int ai_heal = 0;
    int element_of_unarmed_attack = 0;
    int poisoned = 0;
    int sleep = 0;
    int paralyzed = 0;
    int blind = 0;
    int confused = 0;
    int fear = 0;
    int dimmed = 0;
    int drunk = 0;
    int bleeding = 0;
    int wet = 0;
    int insane = 0;
    int sick = 0;
    int gravity = 0;
    int choked = 0;
    int furious = 0;
    std::vector<int> growth_buffs;
    std::vector<int> body_parts;
    std::vector<int> normal_actions;
    std::vector<int> special_actions;
    std::vector<Buff> buffs;
    std::vector<int> attr_adjs;
    std::bitset<sizeof(int) * 8 * 50> _flags;
    int _156 = 0;
    int _203 = 0;
    Position target_position;



    void clear();
    void clear_flags();


    // for identifying the type of a Lua reference
    static std::string lua_type()
    {
        return "LuaCharacter";
    }

    bool is_dead()
    {
        return state_ == Character::State::empty ||
            state_ == Character::State::pet_dead ||
            state_ == Character::State::villager_dead ||
            state_ == Character::State::adventurer_dead;
    }

    Character::State state() const
    {
        return state_;
    }

    /**
     * Sets the state of this character. If the state transitions from "empty"
     * to any other state, the corresponding Lua handle will be created or
     * regenerated.
     */
    void set_state(Character::State);

    /**
     * Sets the state of this character without causing any handles to be
     * modified. Only to be used in internal character management functions
     * (relocation) where handles are manually copied or relocated.
     */
    void set_state_raw(Character::State new_state)
    {
        state_ = new_state;
    }


    data::InstanceId new_id() const
    {
        return *the_character_db.get_id_from_legacy(charaid2int(this->id));
    }


    ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS


    static void copy(const Character& from, Character& to)
    {
        const auto index_save = to.index;
        to = from;
        to.index = index_save;
    }



private:
    Character(const Character&) = default;
    Character(Character&&) = default;
    Character& operator=(const Character&) = default;
    Character& operator=(Character&&) = default;



public:
    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Character");

        ELONA_SERIALIZATION_STRUCT_FIELD_WITH_NAME(*this, "state", state_);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, position);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, next_position);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, time_to_revive);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, vision_flag);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, image);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, sex);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, relationship);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, turn_cost);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, current_speed);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, item_which_will_be_used);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, portrait);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, interest);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, time_interest_revive);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, personality);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, impression);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, talk_type);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, height);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, weight);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, birth_year);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, nutrition);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, can_talk);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, quality);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, turn);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, vision_distance);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, enemy_id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, gold);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, platinum_coin);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, equipment_type);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, melee_attack_type);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, fame);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, experience);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, required_experience);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, speed_percentage);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, level);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, speed_percentage_in_next_turn);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, skill_bonus);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, total_skill_bonus);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, inventory_weight);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, max_inventory_weight);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, inventory_weight_type);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, max_level);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, karma);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, hp);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, max_hp);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, sp);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, max_sp);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, mp);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, max_mp);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, heal_value_per_nether_attack);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, god_id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, piety_point);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, praying_point);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, sum_of_equipment_weight);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, special_attack_type);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, rate_to_pierce);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, rate_of_critical_hit);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, speed_correction_value);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, original_relationship);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, pv);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, dv);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, hit_bonus);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, damage_bonus);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, pv_correction_value);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, dv_correction_value);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, damage_reaction_info);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, emotion_icon);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, current_map);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, current_dungeon_level);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, related_quest_id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, direction);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, period_of_contract);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, hire_count);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, insanity);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, curse_power);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, extra_attack);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, extra_shot);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, decrease_physical_damage);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, nullify_damage);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, cut_counterattack);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, anorexia_count);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, activity);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, stops_activity_if_damaged);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, quality_of_performance);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, tip_gold);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, character_role);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, shop_rank);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, activity_target);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, shop_store_id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, time_to_restore);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, cnpc_id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, initial_position);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, hate);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, ai_calm);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, ai_move);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, ai_dist);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, ai_act_sub_freq);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, ai_heal);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, element_of_unarmed_attack);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, poisoned);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, sleep);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, paralyzed);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, blind);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, confused);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, fear);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, dimmed);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, drunk);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, bleeding);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, wet);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, insane);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, sick);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, gravity);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, choked);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, furious);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, growth_buffs);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, body_parts);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, normal_actions);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, special_actions);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, buffs);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, attr_adjs);
        ELONA_SERIALIZATION_STRUCT_FIELD_WITH_NAME(*this, "flags", _flags);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, _156);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, _203);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, target_position);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
};



struct CDataSlice
{
    using iterator = std::vector<Character>::iterator;

    CDataSlice(const iterator& begin, const iterator& end)
        : _begin(begin)
        , _end(end)
    {
    }

    iterator begin()
    {
        return _begin;
    }

    iterator end()
    {
        return _end;
    }

private:
    const iterator _begin;
    const iterator _end;
};



struct CData
{
    CData();


    Character& operator[](int index)
    {
        return storage[index];
    }


    Character& player()
    {
        return (*this)[0];
    }


    Character& tmp()
    {
        return (*this)[56];
    }



    CDataSlice all()
    {
        return {std::begin(storage), std::end(storage)};
    }


    CDataSlice pets()
    {
        return {std::begin(storage) + 1, std::begin(storage) + 16};
    }


    CDataSlice pc_and_pets()
    {
        return {std::begin(storage), std::begin(storage) + 16};
    }


    CDataSlice adventurers()
    {
        return {std::begin(storage) + 16, std::begin(storage) + 56};
    }


    CDataSlice others()
    {
        return {std::begin(storage) + 57, std::end(storage)};
    }



private:
    std::vector<Character> storage;
};


extern CData cdata;

int chara_create(int = 0, int = 0, int = 0, int = 0);
void initialize_character();
bool chara_place();


enum class CharaRelocationMode
{
    normal,
    change,
};


/**
 * Relocate `source` to `destination_slot`. `source` character will be
 * destroyed.
 * @param source The relocated character.
 * @param destination_slot The slot of the character relocated from `source`. If
 * you specify `none`, find an empty slot in cdata.others().
 */
void chara_relocate(
    Character& source,
    optional<int> destination_slot,
    CharaRelocationMode mode = CharaRelocationMode::normal);

void chara_refresh(int);


/**
 * Copy `source` character to a new slot.
 * @param source The character copied from.
 * @return the character slot copied to if `source` was successfully copied;
 * otherwise, -1.
 */
int chara_copy(const Character& source);

void chara_delete(int = 0);
void chara_remove(Character&);
void chara_vanquish(int = 0);
void chara_killed(Character&);

enum class CharaFindLocation
{
    allies,
    others
};

int chara_find(data::InstanceId chara_id);
int chara_find(int id);
int chara_find_ally(int id);
int chara_get_free_slot();
int chara_get_free_slot_ally();
bool chara_unequip(Item& item);
int chara_custom_talk(int = 0, int = 0);
int chara_impression_level(int = 0);
void chara_modify_impression(Character& cc, int delta);
void chara_set_item_which_will_be_used(Character& chara, const Item& item);
int chara_armor_class(const Character& cc);
int chara_breed_power(const Character&);

void chara_add_quality_parens();

bool belong_to_same_team(const Character& c1, const Character& c2);

TurnResult proc_movement_event();
void chara_clear_status_effects();
void chara_clear_status_effects_b();
void revive_character();
void do_chara_revival();
void chara_set_revived_status();
void revive_player();
int new_ally_joins();
void refresh_burden_state();
void go_hostile();
void get_pregnant();
void wet(int = 0, int = 0);
void hostileaction(int = 0, int = 0);
void turn_aggro(int = 0, int = 0, int = 0);
void ride_begin(int = 0);
void ride_end();
void make_sound(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void incognitobegin();
void incognitoend();
void initialize_pc_character();
void lost_body_part(int);
void lovemiracle(int = 0);
void monster_respawn();
void move_character();
void proc_negative_enchantments(Character& chara);
void proc_pregnant();
void wake_up();
int try_to_perceive_npc(int);

} // namespace elona



#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS
#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR
