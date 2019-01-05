#pragma once

#include <bitset>
#include <memory>
#include <vector>
#include "../util/range.hpp"
#include "enums.hpp"
#include "position.hpp"
#include "putit.hpp"


namespace elona
{


// FIXME
struct Enchantment
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.
    int id = 0;
    int power = 0;

    bool operator==(const Enchantment& other) const noexcept
    {
        return id == other.id && power == other.power;
    }


    template <typename Archive>
    void serialize(Archive& ar)
    {
        // WARNING: Changing this will break save compatibility!
        ar(id);
        ar(power);
    }
};


struct Item
{
private:
    using FlagSet = std::bitset<32>;


public:
    Item();

    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.

    // Index of this item into the global cdata array.
    // Used for communicating with legacy code that takes integer index
    // arguments. New code should pass Item& instead. Not serialized; set on
    // creation and load.
    int index = -1;

    int value = 0;
    int image = 0;
    int id = 0;
    Quality quality = Quality::none;
    Position position;
    int weight = 0;
    IdentifyState identification_state = IdentifyState::unidentified;
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

    std::vector<Enchantment> enchantments;


    void clear();

    bool almost_equals(const Item& other, bool ignore_position);

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


    template <
        typename Archive,
        std::enable_if_t<
            std::is_base_of<putit::IArchiveBase, Archive>::value,
            std::nullptr_t> = nullptr>
    void serialize(Archive& ar)
    {
        // WARNING: Changing this will break save compatibility!
        ar(number_);
        ar(value);
        ar(image);
        ar(id);
        ar(quality);
        ar(position);
        ar(weight);
        ar(identification_state);
        ar(count);
        ar(dice_x);
        ar(dice_y);
        ar(damage_bonus);
        ar(hit_bonus);
        ar(dv);
        ar(pv);
        ar(skill);
        ar(curse_state);
        ar(body_part);
        ar(function);
        ar(enhancement);
        ar(own_state);
        ar(color);
        ar(subname);
        ar(material);
        ar(param1);
        ar(param2);
        ar(param3);
        ar(param4);
        ar(difficulty_of_identification);
        ar(turn);
        {
            uint32_t tmp;
            ar(tmp);
            _flags = tmp;
        }
        range::for_each(
            enchantments, [&](auto&& enchantment) { ar(enchantment); });
    }


    template <
        typename Archive,
        std::enable_if_t<
            std::is_base_of<putit::OArchiveBase, Archive>::value,
            std::nullptr_t> = nullptr>
    void serialize(Archive& ar)
    {
        // WARNING: Changing this will break save compatibility!
        ar(number_);
        ar(value);
        ar(image);
        ar(id);
        ar(quality);
        ar(position);
        ar(weight);
        ar(identification_state);
        ar(count);
        ar(dice_x);
        ar(dice_y);
        ar(damage_bonus);
        ar(hit_bonus);
        ar(dv);
        ar(pv);
        ar(skill);
        ar(curse_state);
        ar(body_part);
        ar(function);
        ar(enhancement);
        ar(own_state);
        ar(color);
        ar(subname);
        ar(material);
        ar(param1);
        ar(param2);
        ar(param3);
        ar(param4);
        ar(difficulty_of_identification);
        ar(turn);
        {
            auto tmp = static_cast<uint32_t>(_flags.to_ulong());
            ar(tmp);
        }
        range::for_each(
            enchantments, [&](auto&& enchantment) { ar(enchantment); });
    }


    static void copy(const Item& from, Item& to)
    {
        const auto index_save = to.index;
        to = from;
        to.index = index_save;
    }


private:
    static void refresh();
    int number_ = 0;

    FlagSet _flags;

    Item(const Item&) = default;
    Item(Item&&) = default;
    Item& operator=(const Item&) = default;
    Item& operator=(Item&&) = default;
};



struct Inventory
{
    Inventory();


    Item& operator[](int index)
    {
        return storage[index];
    }


private:
    std::vector<Item> storage;
};


extern Inventory inv;


struct Character;



IdentifyState item_identify(Item& ci, IdentifyState level);
IdentifyState item_identify(Item& ci, int power);

range::iota<int> items(int owner);
std::vector<int> itemlist(int owner, int id);
void itemname_additional_info();

void item_checkknown(int = 0);
int inv_compress(int);
void item_copy(int = 0, int = 0);
void item_acid(const Character& owner, int ci = -1);
void item_delete(int);
void item_exchange(int = 0, int = 0);
void item_modify_num(Item&, int);
void item_set_num(Item&, int);
void itemturn(int = 0);
int itemfind(int = 0, int = 0, int = 0);
int itemusingfind(int, bool = false);
int item_find(int = 0, int = 0, int = 0);
int item_separate(int);
int item_stack(int = 0, int = 0, int = 0);
void item_dump_desc(const Item&);

bool item_fire(int owner, int ci = -1);
void mapitem_fire(int x, int y);
bool item_cold(int owner, int ci = -1);
void mapitem_cold(int x, int y);

// TODO unsure how these are separate from item
int inv_find(int = 0, int = 0);
int get_random_inv(int owner);
int inv_getfreeid(int = 0);
int inv_getowner(int = 0);
int inv_sum(int = 0);
int inv_weight(int = 0);
bool inv_getspace(int);
int inv_getfreeid_force();


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

void item_load_desc(int ci, int& p);

} // namespace elona
