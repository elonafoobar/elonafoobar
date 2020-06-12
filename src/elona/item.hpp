#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include "../util/range.hpp"
#include "consts.hpp"
#include "data/types/type_item.hpp"
#include "enums.hpp"
#include "position.hpp"
#include "serialization/macros.hpp"
#include "shared_id.hpp"


#define ELONA_OTHER_INVENTORIES_INDEX 1320
#define ELONA_ITEM_ON_GROUND_INDEX 5080
#define ELONA_MAX_ITEMS 5480


namespace elona
{


struct Enchantment
{
    int id = 0;
    int power = 0;

    bool operator==(const Enchantment& other) const noexcept
    {
        return id == other.id && power == other.power;
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Enchantment");

        ELONA_SERIALIZATION_STRUCT_FIELD(*this, id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, power);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
};



struct Inventory;



struct Item
{
private:
    using FlagSet = std::bitset<32>;


    // Index of this item into the global cdata array.
    // Used for communicating with legacy code that takes integer index
    // arguments. New code should pass Item& instead. Not serialized; set on
    // creation and load.
    int _index = -1;

    friend Inventory;

public:
    Item();

    int index() const noexcept
    {
        return _index;
    }

private:
    int number_ = 0;

public:
    int value = 0;
    int image = 0;
    ItemId id = ItemId::none;
    Quality quality = Quality::none;
    Position position;
    int weight = 0;
    IdentifyState identify_state = IdentifyState::unidentified;
    int count = 0;
    int dice_x = 0;
    int dice_y = 0;
    int damage_bonus = 0;
    int hit_bonus = 0;
    int dv = 0;
    int pv = 0;
    int skill = 0;
    CurseState curse_state = CurseState::none;
    int body_part = 0;
    int function = 0;
    int enhancement = 0;
    int own_state = 0;
    int color = 0;
    int subname = 0;
    int material = 0;
    int param1 = 0;
    int param2 = 0;
    int param3 = 0;
    int param4 = 0;
    int difficulty_of_identification = 0;
    int turn = 0;

private:
    FlagSet _flags;

public:
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


    data::InstanceId new_id() const
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



    bool operator==(const Item& other) const noexcept
    {
        return this == &other;
    }


    bool operator!=(const Item& other) const noexcept
    {
        return !(*this == other);
    }



    static void copy(const Item& from, Item& to)
    {
        const auto index_save = to._index;
        to = from;
        to._index = index_save;
    }


private:
    Item(const Item&) = default;
    Item(Item&&) = default;
    Item& operator=(const Item&) = default;
    Item& operator=(Item&&) = default;



public:
    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Item");

        ELONA_SERIALIZATION_STRUCT_FIELD_WITH_NAME(*this, "number", number_);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, value);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, image);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, id);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, quality);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, position);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, weight);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, identify_state);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, count);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, dice_x);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, dice_y);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, damage_bonus);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, hit_bonus);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, dv);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, pv);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, skill);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, curse_state);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, body_part);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, function);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, enhancement);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, own_state);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, color);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, subname);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, material);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, param1);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, param2);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, param3);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, param4);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, difficulty_of_identification);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, turn);
        ELONA_SERIALIZATION_STRUCT_FIELD_WITH_NAME(*this, "flags", _flags);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, enchantments);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
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
        return {
            std::begin(storage) + ELONA_ITEM_ON_GROUND_INDEX,
            std::begin(storage) + ELONA_ITEM_ON_GROUND_INDEX + 400};
    }


    InventorySlice map_local()
    {
        return {
            std::begin(storage) + ELONA_OTHER_INVENTORIES_INDEX,
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

void item_checkknown(Item& item);
Item& inv_compress(int owner);

/**
 * Copy @a src to @a dst.
 * @param src the source
 * @param dst the destination
 */
void item_copy(Item& src, Item& dst);

void item_acid(const Character& owner, optional_ref<Item> item = none);

/**
 * Swap the content of @a a and @a b. If they points to the same object, does
 * nothing.
 * @param a one item
 * @param b another item
 */
void item_exchange(Item& a, Item& b);

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

/**
 * Separate @a item's stack.
 * @param item the item to separate
 */
Item& item_separate(Item& stacked_item);

struct ItemStackResult
{
    // If `stacked` is false, `stacked_item` is set to `base_item`.
    bool stacked;
    Item& stacked_item;
};
ItemStackResult
item_stack(int inventory_id, Item& base_item, bool show_message = false);

void item_dump_desc(Item&);

bool item_fire(int owner, optional_ref<Item> burned_item = none);
void mapitem_fire(optional_ref<Character> arsonist, int x, int y);
bool item_cold(int owner, optional_ref<Item> destroyed_item = none);
void mapitem_cold(int x, int y);

// TODO unsure how these are separate from item
bool inv_find(ItemId id, int owner);
Item& get_random_inv(int owner);

optional_ref<Item> inv_get_free_slot(int inventory_id);

int inv_getowner(const Item& item);
int inv_sum(int = 0);
int inv_weight(int = 0);
bool inv_getspace(int);

Item& inv_get_free_slot_force(int inventory_id);

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
void item_db_on_read(Character& reader, Item& item, int legacy_id);
void item_db_on_zap(Item& item, int legacy_id);
void item_db_on_drink(Character& chara, optional_ref<Item> item, int legacy_id);


std::vector<int> item_get_inheritance(const Item& item);


void auto_identify();
void begintempinv();
void exittempinv();
bool cargocheck(const Item& item);
Item& item_convert_artifact(
    Item& artifact,
    bool ignore_external_container = false);
void damage_by_cursed_equipments(Character& chara);
void dipcursed(Item& item);
int efstatusfix(int = 0, int = 0, int = 0, int = 0);
void equip_melee_weapon(Character& chara);
std::pair<int, int> inv_getheader(int);
optional_ref<Item> mapitemfind(const Position& pos, ItemId id);
std::string itemname(Item& item, int number = 0, bool with_article = true);

} // namespace elona
