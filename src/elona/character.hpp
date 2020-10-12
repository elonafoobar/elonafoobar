#pragma once

#include <bitset>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../util/range.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "body_part.hpp"
#include "buff.hpp"
#include "consts.hpp"
#include "data/types/type_character.hpp"
#include "eobject/eobject.hpp"
#include "lua_env/wrapped_function.hpp"
#include "position.hpp"
#include "spact.hpp"
#include "spell.hpp"
#include "time.hpp"
#include "trait.hpp"



#define ELONA_MAX_CHARACTERS 245
#define ELONA_MAX_PARTY_CHARACTERS 57
#define ELONA_MAX_OTHER_CHARACTERS 188



namespace elona
{

struct Item;
struct Inventory;
using InventoryRef = Inventory*;



struct CombatStyle
{
public:
    bool unarmed() const noexcept
    {
        return _inner == 0;
    }


    bool shield() const noexcept
    {
        return _inner & 1;
    }


    bool two_hand() const noexcept
    {
        return _inner & 2;
    }


    bool dual_wield() const noexcept
    {
        return _inner & 4;
    }



    void reset() noexcept
    {
        _inner = 0;
    }


    void set_unarmed() noexcept
    {
        reset();
    }


    void set_shield() noexcept
    {
        _inner |= 1;
    }


    void set_two_hand() noexcept
    {
        _inner |= 2;
    }


    void set_dual_wield() noexcept
    {
        _inner |= 4;
    }



private:
    int _inner{};
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

    ObjId obj_id;

private:
    Character::State state_ = Character::State::empty;

public:
    /// Character's current position.
    Position position{};

    /// Character's next position.
    Position next_position{};

    /// Character's initial position.
    Position initial_position{};

    /// Character ID
    CharaId id = CharaId::none;

    /// FOV flag
    lua_int fov_flag{};

    /// FOV range. It is a diameter in tiles.
    lua_int fov_range{};

    /// Image
    lua_int image{};

    /// Portrait
    data::InstanceId portrait{};

    /// Gender
    lua_int sex{};

    /// When the character revives.
    time::Instant revival_time{};

    /// Relationship to the player
    Relationship relationship{};

    /// Original relationship to the player
    Relationship original_relationship{};

    /// Interest to the player.
    lua_int interest{};

    /// When `interest` is reset.
    time::Instant interest_reset_time{};

    /// Personality
    lua_int personality{};

    /// Talk type
    lua_int talk_type{};

    /// Impression to the player.
    lua_int impression{};

    /// Height (in cm)
    lua_int height{};

    /// Weight (in kg)
    lua_int weight{};

    /// Birthday. Because Date class does not have default constructor (both
    /// month of 0th and day of 0th are invalid), a dummy value is assgiend
    /// until character initialization completes. The dummy value is the
    /// birthday of the green-haired Elea.
    /// http://elonagather.wiki.fc2.com/wiki/%E4%B8%BB%E8%A6%81%E3%81%AA%E4%BA%BA%E7%89%A9
    time::Date birthday{493, 12, 26};

    /// Hunger
    lua_int nutrition{};

    /// Quality
    Quality quality{};

    /// Turns
    lua_int turns{};

    /// Gold
    lua_int gold{};

    /// Platinum
    lua_int platinum{};

    /// Combat style
    CombatStyle combat_style{};

    /// Fame
    lua_int fame{};

    /// Karma
    lua_int karma{};

    /// Current level
    lua_int level{};

    /// Maximum level
    lua_int max_level{};

    /// Experience
    lua_int experience{};

    /// Required experience to the next level
    lua_int required_experience{};

    lua_int turn_cost{};
    lua_int current_speed{};
    lua_int speed_percentage{};
    lua_int speed_percentage_in_next_turn{};
    lua_int speed_correction_value{};

    /// Current skill bonus
    lua_int skill_bonus{};

    /// Total amount of skill bonuses which the character earned ever.
    lua_int total_skill_bonus{};

    /// Inventory weight
    lua_int inventory_weight{};

    /// Maximum inventory weight
    lua_int max_inventory_weight{};

    /// Equipment weight
    lua_int equipment_weight{};

    /// Burden state
    lua_int burden_state{};

    /// Current HP, hit point
    lua_int hp{};

    /// Maximum HP, hit point
    lua_int max_hp{};

    /// Current MP, mana point
    lua_int mp{};

    /// Maximum MP, mana point
    lua_int max_mp{};

    /// Current SP, stamina point
    lua_int sp{};

    /// Maximum SP, stamina point
    lua_int max_sp{};

    /// Religion
    data::InstanceId religion;

    /// Piety point
    lua_int piety_point{};

    /// Prayer point
    lua_int prayer_point{};

    /// PV, protection value
    lua_int pv{};

    /// PV bonus
    lua_int pv_bonus{};

    // DV, defense value
    lua_int dv{};

    /// DV bonus
    lua_int dv_bonus{};

    /// Hit bonus
    lua_int hit_bonus{};

    /// Damage bonus
    lua_int damage_bonus{};

    OptionalItemRef ai_item;

    lua_int can_talk{};
    lua_int enemy_id{};
    lua_int melee_attack_type{};
    lua_int heal_value_per_nether_attack{};
    lua_int special_attack_type{};
    lua_int rate_to_pierce{};
    lua_int rate_of_critical_hit{};
    lua_int damage_reaction_info{};
    lua_int emotion_icon{};
    lua_int current_map{};
    lua_int current_dungeon_level{};
    lua_int related_quest_id{};
    lua_int direction{};
    time::Instant hire_limit_time{};
    lua_int hire_count{};
    lua_int insanity{};
    lua_int curse_power{};
    lua_int extra_attack{};
    lua_int extra_shot{};
    lua_int decrease_physical_damage{};
    lua_int nullify_damage{};
    lua_int cut_counterattack{};
    lua_int anorexia_count{};
    Activity activity;
    lua_int quality_of_performance{};
    lua_int tip_gold{};
    Role role = Role::none;
    lua_int shop_rank{};
    lua_int activity_target{};
    lua_int shop_store_id{};
    time::Instant shop_restock_time{};
    lua_int cnpc_id{};
    lua_int hate{};
    lua_int ai_calm{};
    lua_int ai_move{};
    lua_int ai_dist{};
    lua_int ai_act_sub_freq{};
    lua_int ai_heal{};
    lua_int element_of_unarmed_attack{};
    lua_int poisoned{};
    lua_int sleep{};
    lua_int paralyzed{};
    lua_int blind{};
    lua_int confused{};
    lua_int fear{};
    lua_int dimmed{};
    lua_int drunk{};
    lua_int bleeding{};
    lua_int wet{};
    lua_int insane{};
    lua_int sick{};
    lua_int gravity{};
    lua_int choked{};
    lua_int furious{};
    std::vector<int> growth_buffs;
    BodyPartList body_parts;
    std::vector<int> normal_actions;
    std::vector<int> special_actions;
    BuffList buffs;
    std::vector<int> attr_adjs;
    std::bitset<sizeof(int) * 8 * 50> _flags;
    int _156{};
    int _203{};
    Position target_position;


    /// Death count
    lua_int death_count;

    /// Kill count
    lua_int kill_count;


    std::string name;
    std::string alias;
    data::InstanceId race;
    data::InstanceId class_;
    std::string talk;

    InventoryRef inventory();



private:
    SkillData _skills;

    /// Spell stocks
    SpellStockTable _spell_stocks;

    /// Spacts
    SpactTable _spacts;

    /// All traits (feats, ether diseases and mutations) the character has.
    TraitLevelTable _traits;


public:
    Ability& get_skill(int id)
    {
        return _skills.get(id);
    }


    const Ability& get_skill(int id) const
    {
        return _skills.get(id);
    }


    SpellStockTable& spell_stocks() noexcept
    {
        return _spell_stocks;
    }


    const SpellStockTable& spell_stocks() const noexcept
    {
        return _spell_stocks;
    }


    SpactTable& spacts() noexcept
    {
        return _spacts;
    }


    const SpactTable& spacts() const noexcept
    {
        return _spacts;
    }



    TraitLevelTable& traits() noexcept
    {
        return _traits;
    }


    const TraitLevelTable& traits() const noexcept
    {
        return _traits;
    }



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
        return *the_character_db.get_id_from_integer(charaid2int(this->id));
    }



    bool is_player() const;
    bool is_ally() const;
    bool is_player_or_ally() const;
    bool is_adventurer() const;
    bool is_global() const;
    bool is_map_local() const;



    ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS


    static void copy(const Character& from, Character& to)
    {
        const auto index_save = to.index;
        to = from;
        to.index = index_save;
    }



    bool operator==(const Character& other) const noexcept
    {
        return this == &other;
    }


    bool operator!=(const Character& other) const noexcept
    {
        return this != &other;
    }



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


    CDataSlice allies()
    {
        return {std::begin(storage) + 1, std::begin(storage) + 16};
    }


    CDataSlice player_and_allies()
    {
        return {std::begin(storage), std::begin(storage) + 16};
    }


    CDataSlice adventurers()
    {
        return {std::begin(storage) + 16, std::begin(storage) + 55};
    }


    CDataSlice others()
    {
        return {std::begin(storage) + 57, std::end(storage)};
    }



private:
    std::vector<Character> storage;
};


extern CData cdata;

optional_ref<Character> chara_create(int slot, int chara_id, int x, int y);
void initialize_character(Character& chara);
bool chara_place(Character& chara);


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
    optional_ref<Character> destination_slot,
    CharaRelocationMode mode = CharaRelocationMode::normal);

void chara_refresh(Character& chara);


/**
 * Copy `source` character to a new slot.
 * @param source The character copied from.
 * @return the character slot copied to if `source` was successfully copied;
 * otherwise, -1.
 */
int chara_copy(const Character& source);

void chara_delete(Character& chara);
void chara_vanquish(Character& chara);
void chara_killed(Character&);

enum class CharaFindLocation
{
    allies,
    others
};

optional_ref<Character> chara_find(data::InstanceId chara_id);
int chara_find_ally(int id);
int chara_get_free_slot();
int chara_get_free_slot_ally();
bool chara_unequip(const ItemRef& item);
bool chara_custom_talk(Character& speaker, int talk_type);
int chara_impression_level(int = 0);
void chara_modify_impression(Character& chara, int delta);
void chara_set_ai_item(Character& chara, ItemRef item);
int chara_armor_class(const Character& chara);
int chara_breed_power(const Character&);

void chara_add_quality_parens(Character& chara);

bool belong_to_same_team(const Character& c1, const Character& c2);

TurnResult proc_movement_event(Character& chara);
void chara_clear_status_effects(Character& chara);
void chara_clear_status_effects_b(Character& chara);
void revive_character(Character& chara);
void do_chara_revival(Character& chara);
void chara_set_revived_status(Character& chara);
void revive_player(Character& chara);
optional_ref<Character> new_ally_joins(Character& new_ally);
void refresh_burden_state();
void go_hostile();
void get_pregnant(Character& chara);
void chara_get_wet(Character& chara, int turns);
void chara_act_hostile_action(Character& attacker, Character& target);
void turn_aggro(Character& chara, Character& target, int hate);
void ride_begin(int = 0);
void ride_end();
void make_sound(
    Character& source_chara,
    int distance_threshold,
    int waken,
    bool may_make_angry);
void incognitobegin();
void incognitoend();
void initialize_pc_character();
void lovemiracle(Character& chara);
void monster_respawn();
void move_character(Character& chara);
void proc_negative_enchantments(Character& chara);
void proc_pregnant(Character& chara);
void wake_up();
bool try_to_perceive_npc(const Character& chara, const Character& enemy);
Relationship relation_between(const Character& a, const Character& b);

} // namespace elona



#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS
#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR
