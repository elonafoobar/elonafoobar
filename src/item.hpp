#pragma once

#include <memory>
#include <vector>
#include "enums.hpp"
#include "position.hpp"
#include "range.hpp"


namespace elona
{


// FIXME
struct enc_t
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.
    int id = 0;
    int power = 0;

    bool operator==(const enc_t& other) const noexcept
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


struct item
{
    item();

    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.

    // Index of this item into the global cdata array.
    // Used for communicating with legacy code that takes integer index
    // arguments. New code should pass item& instead. Not serialized; set on
    // creation and load.
    int index = -1;

    int value = 0;
    int image = 0;
    int id = 0;
    int quality = 0;
    position_t position;
    int weight = 0;
    identification_state_t identification_state =
        identification_state_t::unidentified;
    int count = 0;
    int dice_x = 0;
    int dice_y = 0;
    int damage_bonus = 0;
    int hit_bonus = 0;
    int dv = 0;
    int pv = 0;
    int skill = 0;
    curse_state_t curse_state = curse_state_t::none;
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

    int flags = 0;

    std::vector<enc_t> enchantments;


    void clear();

    bool almost_equals(const item& other, bool ignore_position);

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


    template <typename Archive>
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
        ar(flags);
        range::for_each(
            enchantments, [&](auto&& enchantment) { ar(enchantment); });
    }


    static void copy(const item& from, item& to)
    {
        const auto index_save = to.index;
        to = from;
        to.index = index_save;
    }


private:
    static void refresh();
    int number_ = 0;


    item(const item&) = default;
    item(item&&) = default;
    item& operator=(const item&) = default;
    item& operator=(item&&) = default;
};



struct inventory
{
    inventory();


    item& operator[](int index)
    {
        return storage[index];
    }


private:
    std::vector<item> storage;
};


extern inventory inv;


struct character;



int ibit(size_t type, int ci);
void ibitmod(size_t type, int ci, int on);


identification_state_t item_identify(item& ci, identification_state_t level);
identification_state_t item_identify(item& ci, int power);

range::iota<int> items(int owner);
std::vector<int> itemlist(int owner, int id);
void itemname_additional_info();

void item_checkknown(int = 0);
int inv_compress(int);
void item_copy(int = 0, int = 0);
void item_acid(const character& owner, int ci = -1);
void item_delete(int);
void item_exchange(int = 0, int = 0);
void item_modify_num(item&, int);
void item_set_num(item&, int);
void itemturn(int = 0);
int itemfind(int = 0, int = 0, int = 0);
int itemusingfind(int, bool = false);
int item_find(int = 0, int = 0, int = 0);
int item_separate(int);
int item_stack(int = 0, int = 0, int = 0);
void item_dump_desc(const item&);

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


enum desc_entry_t : int
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
