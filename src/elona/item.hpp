#pragma once

#include <bitset>
#include <memory>
#include <vector>
#include "../util/range.hpp"
#include "consts.hpp"
#include "data/types/type_item.hpp"
#include "enums.hpp"
#include "position.hpp"
#include "shared_id.hpp"


#define ELONA_OTHER_INVENTORIES_INDEX 1320
#define ELONA_ITEM_ON_GROUND_INDEX 5080
#define ELONA_MAX_ITEMS 5480


namespace elona
{


/// @putit
struct Enchantment
{
    /// @putit
    int id = 0;

    /// @putit
    int power = 0;

    bool operator==(const Enchantment& other) const noexcept
    {
        return id == other.id && power == other.power;
    }


#include "_putit/enchantment.cpp"
};



/// @putit
struct Item
{
private:
    using FlagSet = std::bitset<32>;


public:
    Item();

    // Index of this item into the global cdata array.
    // Used for communicating with legacy code that takes integer index
    // arguments. New code should pass Item& instead. Not serialized; set on
    // creation and load.
    int index = -1;

private:
    /// @putit
    int number_ = 0;

public:
    /// @putit
    int value = 0;

    /// @putit
    int image = 0;

    /// @putit
    ItemId id = ItemId::none;

    /// @putit
    Quality quality = Quality::none;

    /// @putit
    Position position;

    /// @putit
    int weight = 0;

    /// @putit
    IdentifyState identify_state = IdentifyState::unidentified;

    /// @putit
    int count = 0;

    /// @putit
    int dice_x = 0;

    /// @putit
    int dice_y = 0;

    /// @putit
    int damage_bonus = 0;

    /// @putit
    int hit_bonus = 0;

    /// @putit
    int dv = 0;

    /// @putit
    int pv = 0;

    /// @putit
    int skill = 0;

    /// @putit
    CurseState curse_state = CurseState::none;

    /// @putit
    int body_part = 0;

    /// @putit
    int function = 0;

    /// @putit
    int enhancement = 0;

    /// @putit
    int own_state = 0;

    /// @putit
    int color = 0;

    /// @putit
    int subname = 0;

    /// @putit
    int material = 0;

    /// @putit
    int param1 = 0;

    /// @putit
    int param2 = 0;

    /// @putit
    int param3 = 0;

    /// @putit
    int param4 = 0;

    /// @putit
    int difficulty_of_identification = 0;

    /// @putit
    int turn = 0;

private:
    /// @putit
    FlagSet _flags;

public:
    /// @putit
    std::vector<Enchantment> enchantments;


    void clear();

    bool almost_equals(const Item& other, bool ignore_position) const;

    // for identifying the type of a Lua reference
    static std::string lua_type()
    {
        return "LuaItem";
    }

    int number() const
    {
        return number_;
    }

    void set_number(int number_);
    void modify_number(int delta);
    void remove();

    SharedId new_id() const
    {
        return *the_item_db.get_id_from_legacy(itemid2int(this->id));
    }


#define ELONA_ITEM_DEFINE_FLAG_ACCESSOR(name, n) \
    bool name() const \
    { \
        return _flags[n]; \
    } \
    FlagSet::reference name() \
    { \
        return _flags[n]; \
    }

    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_acidproof, 1)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_fireproof, 2)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(has_charge, 4)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_precious, 5)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_aphrodisiac, 6)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(has_cooldown_time, 7)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_blessed_by_ehekatl, 8)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_stolen, 9)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_alive, 10)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_quest_target, 12)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_marked_as_no_drop, 13)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_poisoned, 14)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_eternal_force, 15)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_showroom_only, 16)
    ELONA_ITEM_DEFINE_FLAG_ACCESSOR(is_handmade, 17)

#undef ELONA_ITEM_DEFINE_FLAG_ACCESSOR


#include "_putit/item.cpp"


    static void copy(const Item& from, Item& to)
    {
        const auto index_save = to.index;
        to = from;
        to.index = index_save;
    }


private:
    static void refresh();

    Item(const Item&) = default;
    Item(Item&&) = default;
    Item& operator=(const Item&) = default;
    Item& operator=(Item&&) = default;
};



struct InventorySlice
{
    using iterator = std::vector<Item>::iterator;

    InventorySlice(const iterator& begin, const iterator& end)
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



struct Character;


struct Inventory
{
    Inventory();


    Item& operator[](int index)
    {
        return storage[index];
    }


    InventorySlice all()
    {
        return {std::begin(storage), std::end(storage)};
    }


    InventorySlice pc()
    {
        return {std::begin(storage), std::begin(storage) + 200};
    }


    InventorySlice ground()
    {
        return {std::begin(storage) + ELONA_ITEM_ON_GROUND_INDEX,
                std::begin(storage) + ELONA_ITEM_ON_GROUND_INDEX + 400};
    }


    InventorySlice map_local()
    {
        return {std::begin(storage) + ELONA_OTHER_INVENTORIES_INDEX,
                std::end(storage)};
    }


    InventorySlice for_chara(const Character& chara);

    InventorySlice by_index(int index);



private:
    std::vector<Item> storage;
};


extern Inventory inv;



IdentifyState item_identify(Item& item, IdentifyState level);
IdentifyState item_identify(Item& item, int power);

std::vector<std::reference_wrapper<Item>> itemlist(int owner, int id);
void itemname_additional_info();

void item_checkknown(Item& item);
int inv_compress(int);
void item_copy(int = 0, int = 0);
void item_acid(const Character& owner, int item_index = -1);
void item_delete(Item& item);
void item_exchange(int = 0, int = 0);
void item_modify_num(Item&, int);
void item_set_num(Item&, int);
void itemturn(Item& item);
optional_ref<Item>
itemfind(int inventory_id, int matcher, int matcher_type = 0);
int itemusingfind(const Item& item, bool disallow_pc = false);

enum class ItemFindLocation
{
    player_inventory,
    ground,
    player_inventory_and_ground,
};
optional_ref<Item> item_find(
    int matcher,
    int matcher_type = 0,
    ItemFindLocation = ItemFindLocation::player_inventory_and_ground);

int item_separate(int);
bool item_stack(int inventory_id, Item& base_item, bool show_message = false);
void item_dump_desc(const Item&);

bool item_fire(int owner, optional_ref<Item> burned_item = none);
void mapitem_fire(int x, int y);
bool item_cold(int owner, optional_ref<Item> destroyed_item = none);
void mapitem_cold(int x, int y);

// TODO unsure how these are separate from item
int inv_find(int = 0, int = 0);
Item& get_random_inv(int owner);
int inv_getfreeid(int = 0);
int inv_getowner(int = 0);
int inv_sum(int = 0);
int inv_weight(int = 0);
bool inv_getspace(int);
int inv_getfreeid_force();

void remain_make(Item& remain, const Character& chara);


void item_drop(Item& item_in_inventory, int num, bool building_shelter = false);
void item_build_shelter(Item& shelter);


enum class ItemDescriptionType : int
{
    normal = 0, // rgb(0, 0, 0)
    raises_skill = 1, // rgb(0, 100, 0)
    raises_stat = 2, // rgb(0, 0, 100)
    raises_resist = 3, // rgb(80, 100, 0)
    enchantment = 4, // rgb(80, 50, 0)
    weapon_info = 5, // rgb(0, 0, 0)
    armor_info = 6, // rgb(0, 0, 0)
    text = 7, // rgb(0, 0, 0)
    maintains_skill = 8, // rgb(0, 100, 100)
    negative_effect = 9, // rgb(180, 0, 0)

    small_font = -1,
    small_font_italic = -2,
};

size_t item_load_desc(const Item& item);


int iequiploc(const Item& item);

void item_db_set_basic_stats(Item& item, int legacy_id);
bool item_db_is_offerable(Item& item, int legacy_id);
void item_db_get_description(Item& item, int legacy_id);
void item_db_get_charge_level(const Item& item, int legacy_id);
void item_db_set_full_stats(Item& item, int legacy_id);
void item_db_on_read(Item& item, int legacy_id);
void item_db_on_zap(Item& item, int legacy_id);
void item_db_on_drink(Item& item, int legacy_id);


std::vector<int> item_get_inheritance(const Item& item);

} // namespace elona
