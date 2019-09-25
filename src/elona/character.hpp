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


#define ELONA_MAX_CHARACTERS 245
#define ELONA_MAX_PARTY_CHARACTERS 57
#define ELONA_MAX_OTHER_CHARACTERS 188


namespace elona
{

/// @putit
struct Buff
{
    /// @putit
    int id = 0;

    /// @putit
    int power = 0;

    /// @putit
    int turns = 0;


#include "_putit/buff.cpp"
};



/// @putit
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

    /// @putit
    Type type = Activity::Type::none;

    /// @putit
    int turn = 0;

    /// @putit
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


#include "_putit/activity.cpp"
};



/// @putit
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
    /// @putit
    Character::State state_ = Character::State::empty;

public:
    /// @putit
    Position position;

    /// @putit
    Position next_position;

    /// @putit
    int time_to_revive = 0;

    /// @putit
    int vision_flag = 0;

    /// @putit
    int image = 0;

    /// @putit
    int sex = 0;

    /// @putit
    int relationship = 0;

    /// @putit
    int turn_cost = 0;

    /// @putit
    int current_speed = 0;

    /// @putit
    int item_which_will_be_used = 0;

    /// @putit
    std::string portrait;

    /// @putit
    int interest = 0;

    /// @putit
    int time_interest_revive = 0;

    /// @putit
    int personality = 0;

    /// @putit
    int impression = 0;

    /// @putit
    int talk_type = 0;

    /// @putit
    int height = 0;

    /// @putit
    int weight = 0;

    /// @putit
    int birth_year = 0;

    /// @putit
    int nutrition = 0;

    /// @putit
    int can_talk = 0;

    /// @putit
    Quality quality = Quality::none;

    /// @putit
    int turn = 0;

    /// @putit
    CharaId id = CharaId::none;

    /// @putit
    int vision_distance = 0;

    /// @putit
    int enemy_id = 0;

    /// @putit
    int gold = 0;

    /// @putit
    int platinum_coin = 0;

    /// @putit
    int equipment_type = 0;

    /// @putit
    int melee_attack_type = 0;

    /// @putit
    int fame = 0;

    /// @putit
    int experience = 0;

    /// @putit
    int required_experience = 0;

    /// @putit
    int speed_percentage = 0;

    /// @putit
    int level = 0;

    /// @putit
    int speed_percentage_in_next_turn = 0;

    /// @putit
    int skill_bonus = 0;

    /// @putit
    int total_skill_bonus = 0;

    /// @putit
    int inventory_weight = 0;

    /// @putit
    int max_inventory_weight = 0;

    /// @putit
    int inventory_weight_type = 0;

    /// @putit
    int max_level = 0;

    /// @putit
    int karma = 0;

    /// @putit
    int hp = 0;

    /// @putit
    int max_hp = 0;

    /// @putit
    int sp = 0;

    /// @putit
    int max_sp = 0;

    /// @putit
    int mp = 0;

    /// @putit
    int max_mp = 0;

    /// @putit
    int heal_value_per_nether_attack = 0;

    /// @putit
    GodId god_id;

    /// @putit
    int piety_point = 0;

    /// @putit
    int praying_point = 0;

    /// @putit
    int sum_of_equipment_weight = 0;

    /// @putit
    int special_attack_type = 0;

    /// @putit
    int rate_to_pierce = 0;

    /// @putit
    int rate_of_critical_hit = 0;

    /// @putit
    int speed_correction_value = 0;

    /// @putit
    int original_relationship = 0;

    /// @putit
    int pv = 0;

    /// @putit
    int dv = 0;

    /// @putit
    int hit_bonus = 0;

    /// @putit
    int damage_bonus = 0;

    /// @putit
    int pv_correction_value = 0;

    /// @putit
    int dv_correction_value = 0;

    /// @putit
    int damage_reaction_info = 0;

    /// @putit
    int emotion_icon = 0;

    /// @putit
    int current_map = 0;

    /// @putit
    int current_dungeon_level = 0;

    /// @putit
    int related_quest_id = 0;

    /// @putit
    int direction = 0;

    /// @putit
    int period_of_contract = 0;

    /// @putit
    int hire_count = 0;

    /// @putit
    int insanity = 0;

    /// @putit
    int curse_power = 0;

    /// @putit
    int extra_attack = 0;

    /// @putit
    int extra_shot = 0;

    /// @putit
    int decrease_physical_damage = 0;

    /// @putit
    int nullify_damage = 0;

    /// @putit
    int cut_counterattack = 0;

    /// @putit
    int anorexia_count = 0;

    /// @putit
    Activity activity;

    /// @putit
    int stops_activity_if_damaged = 0;

    /// @putit
    int quality_of_performance = 0;

    /// @putit
    int tip_gold = 0;

    /// @putit
    int character_role = 0;

    /// @putit
    int shop_rank = 0;

    /// @putit
    int activity_target = 0;

    /// @putit
    int shop_store_id = 0;

    /// @putit
    int time_to_restore = 0;

    /// @putit
    int cnpc_id = 0;

    /// @putit
    Position initial_position;

    /// @putit
    int hate = 0;

    /// @putit
    int ai_calm = 0;

    /// @putit
    int ai_move = 0;

    /// @putit
    int ai_dist = 0;

    /// @putit
    int ai_act_sub_freq = 0;

    /// @putit
    int ai_heal = 0;

    /// @putit
    int element_of_unarmed_attack = 0;

    /// @putit
    int poisoned = 0;

    /// @putit
    int sleep = 0;

    /// @putit
    int paralyzed = 0;

    /// @putit
    int blind = 0;

    /// @putit
    int confused = 0;

    /// @putit
    int fear = 0;

    /// @putit
    int dimmed = 0;

    /// @putit
    int drunk = 0;

    /// @putit
    int bleeding = 0;

    /// @putit
    int wet = 0;

    /// @putit
    int insane = 0;

    /// @putit
    int sick = 0;

    /// @putit
    int gravity = 0;

    /// @putit
    int choked = 0;

    /// @putit
    int furious = 0;

    /// @putit
    std::vector<int> growth_buffs;

    /// @putit
    std::vector<int> body_parts;

    /// @putit
    std::vector<int> normal_actions;

    /// @putit
    std::vector<int> special_actions;

    /// @putit
    std::vector<Buff> buffs;

    /// @putit
    std::vector<int> attr_adjs;

    /// @putit
    std::bitset<sizeof(int) * 8 * 50> _flags;

    /// @putit
    int _156 = 0;

    /// @putit
    int _203 = 0;

    /// @putit
    int _205 = 0;

    /// @putit
    int _206 = 0;

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

    SharedId new_id() const
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



#include "_putit/character.cpp"


private:
    Character(const Character&) = default;
    Character(Character&&) = default;
    Character& operator=(const Character&) = default;
    Character& operator=(Character&&) = default;
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

int chara_find(const std::string& chara_id);
int chara_find(int id);
int chara_find_ally(int id);
int chara_get_free_slot();
int chara_get_free_slot_ally();
bool chara_unequip(int);
int chara_custom_talk(int = 0, int = 0);
int chara_impression_level(int = 0);
void chara_modify_impression(Character& cc, int delta);
void chara_set_item_which_will_be_used(Character& cc);
int chara_armor_class(const Character& cc);
int chara_breed_power(const Character&);

void chara_add_quality_parens();

bool belong_to_same_team(const Character& c1, const Character& c2);


} // namespace elona



#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS
#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR
