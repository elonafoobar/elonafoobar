#include "item.hpp"

#include <iostream>
#include <limits>
#include <type_traits>

#include "../util/strutil.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "blending.hpp"
#include "building.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "data/types/type_ability.hpp"
#include "data/types/type_fish.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_item_material.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/item_instance_event.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "message.hpp"
#include "random.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"

static std::string lang(const std::string& a, const std::string& b)
{
    return jp ? a : b;
}


namespace elona
{


AllInventory g_inv;

int ci_at_m138 = 0;
int p_at_m138 = 0;
int max_at_m138 = 0;
int ti_at_m138 = 0;
elona_vector1<int> list_at_m138;
int f_at_m138 = 0;
int a_at_m138 = 0;


Item::Item()
    : enchantments(15)
{
}



void Item::clear()
{
    copy({}, *this);
}



bool Item::almost_equals(const Item& other, bool ignore_position) const
{
    /* clang-format off */
    return
        // number() == other.number() &&
        value == other.value &&
        image == other.image &&
        id == other.id &&
        // quality == other.quality &&
        (ignore_position || position() == other.position()) &&
        weight == other.weight &&
        identify_state == other.identify_state &&
        charges == other.charges &&
        dice == other.dice &&
        hit_bonus == other.hit_bonus &&
        dv == other.dv &&
        pv == other.pv &&
        skill == other.skill &&
        curse_state == other.curse_state &&
        body_part == other.body_part &&
        function == other.function &&
        bonus_value == other.bonus_value &&
        own_state == other.own_state &&
        tint == other.tint &&
        subname == other.subname &&
        material == other.material &&
        param1 == other.param1 &&
        param2 == other.param2 &&
        param3 == other.param3 &&
        param4 == other.param4 &&
        identify_level == other.identify_level &&
        // turn == other.turn &&
        is_acidproof == other.is_acidproof &&
        is_fireproof == other.is_fireproof &&
        is_coldproof == other.is_coldproof &&
        is_precious == other.is_precious &&
        has_charges == other.has_charges &&
        has_cooldown_time == other.has_cooldown_time &&
        is_aphrodisiac == other.is_aphrodisiac &&
        is_poisoned == other.is_poisoned &&
        is_blessed_by_ehekatl == other.is_blessed_by_ehekatl &&
        is_stolen == other.is_stolen &&
        is_quest_target == other.is_quest_target &&
        is_no_drop == other.is_no_drop &&
        is_alive == other.is_alive &&
        is_eternal_force == other.is_eternal_force &&
        is_handmade == other.is_handmade &&
        is_showroom_only == other.is_showroom_only &&
        range::equal(enchantments, other.enchantments);
    /* clang-format on */
}



Inventory::Inventory(size_t inventory_size, int inventory_id)
    : _storage(inventory_size)
    , _inventory_id(inventory_id)
    , _capacity(inventory_size)
{
    // Please uncomment the next line for testing dynamically-sized inventory.
    // set_capacity(none);
}



bool Inventory::has_free_slot() const
{
    for (const auto& item : _storage)
    {
        if (!item)
        {
            return true;
        }
    }
    return false;
}



optional<InventorySlot> Inventory::get_free_slot()
{
    size_t i = 0;
    for (const auto& item : _storage)
    {
        if (!item)
        {
            return InventorySlot{i};
        }
        ++i;
    }
    return none;
}



void Inventory::clear()
{
    for (auto&& item : _storage)
    {
        if (item)
        {
            item->_number = 0;
            item->obj_id = ObjId::nil();
            item->_inventory = nullptr;

            item = nullptr;
        }
    }
}



void Inventory::exchange(const ItemRef& a, const ItemRef& b)
{
    if (a == b)
        return;

    const auto inv_a = a->inventory();
    const auto slot_a = a->slot();
    const auto inv_b = b->inventory();
    const auto slot_b = b->slot();

    std::swap(
        inv_a->_storage.at(static_cast<size_t>(slot_a)),
        inv_b->_storage.at(static_cast<size_t>(slot_b)));
    a->_inventory = inv_b;
    b->_inventory = inv_a;
    a->_slot = slot_b;
    b->_slot = slot_a;
    // TODO cell_refresh
}



ItemRef Inventory::create(InventorySlot slot)
{
    assert(!at(slot));

    const auto new_item = eobject::Pool<Item>::instance().create();
    new_item->_inventory = this;
    new_item->_slot = slot;
    _storage.at(static_cast<size_t>(slot)) = new_item;

    return new_item;
}



void Inventory::move_all(Inventory& src, Inventory& dst)
{
    if (&src == &dst)
        return;

    const auto prev_size = src._storage.size();
    dst._storage = std::move(src._storage);
    src._storage.clear();
    src._storage.resize(prev_size);

    size_t i = 0;
    for (const auto& item : dst._storage)
    {
        if (item)
        {
            item->_inventory = &dst;
            item->_slot = static_cast<InventorySlot>(i);
            item->body_part = 0;
        }
        ++i;
    }

    // TODO
    // _capacity
    // cell_refresh()
    // src.size() != dst.size()
}



void Inventory::set_capacity(optional<size_t> new_capacity)
{
    _capacity = new_capacity;
    // TODO
}



AllInventory::AllInventory()
{
    _inventories.emplace_back(200, 0);
    for (size_t i = 1; i < 245; ++i)
    {
        _inventories.emplace_back(20, static_cast<int>(i));
    }
    _inventories.emplace_back(400, -1);
    _inventories.emplace_back(400, 255);
}



ItemRef AllInventory::operator[](int index)
{
    const auto inv_id = static_cast<int>(index >> 18) - 1;
    const auto idx = index - ((inv_id + 1) << 18);
    return by_index(inv_id)->at(static_cast<InventorySlot>(idx)).unwrap();
}



InventoryRef AllInventory::ground()
{
    auto itr = _inventories.end();
    --itr;
    --itr;
    return &*itr;
}



InventoryRef AllInventory::tmp()
{
    return &_inventories.back();
}



InventoryRef AllInventory::for_chara(const Character& chara)
{
    return &_inventories.at(chara.index);
}



InventoryRef AllInventory::by_index(int index)
{
    if (index == -1)
    {
        return ground();
    }
    else if (index == 255)
    {
        return tmp();
    }
    else
    {
        return for_chara(cdata[index]);
    }
}



AllInventory::iterator_pair_type AllInventory::all()
{
    return {_inventories.begin(), _inventories.end()};
}



AllInventory::iterator_pair_type AllInventory::global()
{
    auto end = _inventories.begin();
    std::advance(end, 57);
    return {_inventories.begin(), end};
}



AllInventory::iterator_pair_type AllInventory::map_local()
{
    auto begin = _inventories.begin();
    std::advance(begin, 57);
    auto end = _inventories.end();
    --end;
    return {begin, end};
}



elona_vector1<int> p_at_m57;
std::string s_;
int skip_ = 0;



template <typename F>
OptionalItemRef item_find_internal(ItemFindLocation location_type, F predicate)
{
    switch (location_type)
    {
    case ItemFindLocation::player_inventory:
        return inv_find_last_match(inv_player(), predicate);
    case ItemFindLocation::ground:
        return inv_find_last_match(inv_map(), predicate);
    case ItemFindLocation::player_inventory_and_ground: {
        const auto a = inv_find_last_match(inv_map(), predicate);
        const auto b = inv_find_last_match(inv_player(), predicate);
        return b ? b : a;
    }
    default: assert(0); return nullptr;
    }
}



OptionalItemRef item_find(data::InstanceId id, ItemFindLocation location_type)
{
    return item_find_internal(location_type, [&](const auto& item, auto& inv) {
        if (inv_get_owner(inv).is_map())
        {
            if (item->position() != cdata.player().position)
            {
                return false;
            }
        }
        return item->id == id;
    });
}



OptionalItemRef item_find(ItemCategory category, ItemFindLocation location_type)
{
    return item_find_internal(location_type, [&](const auto& item, auto& inv) {
        if (inv_get_owner(inv).is_map())
        {
            if (item->position() != cdata.player().position)
            {
                return false;
            }
        }
        return the_item_db[item->id]->category == category;
    });
}



int itemusingfind(const ItemRef& item, bool disallow_pc)
{
    for (auto&& chara : cdata.all())
    {
        if (chara.state() != Character::State::alive)
        {
            continue;
        }
        if (chara.activity && chara.activity.type != Activity::Type::sex &&
            chara.activity.turn > 0 && chara.activity.item == item)
        {
            if (!disallow_pc || !chara.is_player())
            {
                return chara.index;
            }
        }
    }
    return -1; // Not found
}



OptionalItemRef itemfind(const InventoryRef& inv, data::InstanceId id)
{
    return inv_find(inv, [&](const auto& item) { return item->id == id; });
}



OptionalItemRef itemfind(const InventoryRef& inv, int subcategory)
{
    return inv_find(inv, [&](const auto& item) {
        return the_item_db[item->id]->subcategory == subcategory;
    });
}



OptionalItemRef mapitemfind(const Position& pos, data::InstanceId id)
{
    for (const auto& item : *inv_map())
    {
        if (item->id == id && item->position() == pos)
        {
            return item;
        }
    }
    return nullptr; // Not found
}



void cell_refresh(int x, int y)
{
    if (mode == 6 || mode == 9)
        return;
    if (x < 0 || map_data.width <= x || y < 0 || map_data.height <= y)
        return;

    cell_data.at(x, y).light = 0;

    std::array<OptionalItemRef, Cell::ItemInfo::max_stacks> items;
    for (auto& i : items)
        i = nullptr;

    size_t number_of_items = 0;
    for (const auto& item : *inv_map())
    {
        if (item->position() == Position{x, y})
        {
            if (number_of_items < items.size())
            {
                items.at(number_of_items) = item;
            }
            ++number_of_items;
            if (ilight(the_item_db[item->id]->integer_id) != 0)
            {
                cell_data.at(x, y).light =
                    ilight(the_item_db[item->id]->integer_id);
            }
        }
    }
    if (number_of_items <= Cell::ItemInfo::max_stacks)
    {
        range::sort(items, [](const auto& i1, const auto& i2) {
            const auto t1 = i1
                ? i1->turn
                : std::numeric_limits<decltype(Item::turn)>::max();
            const auto t2 = i2
                ? i2->turn
                : std::numeric_limits<decltype(Item::turn)>::max();
            return t1 < t2;
        });
    }

    std::array<int, Cell::ItemInfo::max_stacks> item_indice_plus_one;
    for (size_t i = 0; i < item_indice_plus_one.size(); ++i)
    {
        if (items[i])
        {
            // TODO phantom ref
            item_indice_plus_one[i] = static_cast<int>(items[i]->slot()) + 1;
        }
        else
        {
            item_indice_plus_one[i] = 0;
        }
    }
    cell_data.at(x, y).item_info_actual.set(
        item_indice_plus_one, number_of_items);
}



void itemturn(const ItemRef& item)
{
    ++game_data.item_turns;
    if (game_data.item_turns < 0)
    {
        game_data.item_turns = 1;
    }
    item->turn = game_data.item_turns;
}



ItemRef item_separate(
    const ItemRef& item,
    const InventoryRef& inv,
    InventorySlot slot,
    lua_int number)
{
    const auto dst = item_copy(item, inv, slot);
    item->modify_number(-number);
    dst->set_number(number);
    return dst;
}



ItemRef
item_copy(const ItemRef& item, const InventoryRef& inv, InventorySlot slot)
{
    assert(!inv->at(slot));
    assert(item->number() != 0);

    const auto dst = inv->create(slot);
    Item::copy(*item.get_raw_ptr(), *dst.get_raw_ptr());
    dst->set_number(item->number());
    dst->on_create();
    return dst;
}



int Item::global_index() const noexcept
{
    const auto inv_id = inventory()->inventory_id() + 1;
    const auto idx = static_cast<size_t>(slot());
    return (inv_id << 18) + idx;
}



void Item::remove()
{
    set_number(0);
}



void Item::modify_number(lua_int delta)
{
    set_number(_number + delta);
}



void Item::set_number(lua_int new_number)
{
    new_number = std::max(new_number, lua_int{0});
    if (_number == new_number)
        return;

    auto inv_owner = inv_get_owner(inventory());
    const auto inv_owner_chara = inv_owner.as_character();
    const auto needs_cell_refresh =
        inv_owner.is_map() && (_number == 0 || new_number == 0);
    const auto needs_refresh_burden_state =
        inv_owner_chara && inv_owner_chara->index;

    if (_number == 0)
    {
        _number = new_number;
        on_create();
    }
    else
    {
        _number = new_number;
        if (_number == 0)
        {
            on_remove();
        }
    }

    if (needs_cell_refresh)
    {
        // Refresh the cell the item is on if it's on the ground.
        cell_refresh(position().x, position().y);
    }
    else if (needs_refresh_burden_state)
    {
        // Refresh the player's burden state if the item is in their
        // inventory.
        refresh_burden_state();
    }
}



void Item::set_position(const Position& new_pos)
{
    if (_position == new_pos)
        return;

    _position = new_pos;
}



void Item::on_create()
{
    const auto item_ref = inventory()->at(_slot).unwrap();
    obj_id = ObjId::generate();
    ItemIdTable::instance().add(item_ref);
    lua::lua->get_event_manager().trigger(
        lua::ItemInstanceEvent("core.item_created", item_ref));
}



void Item::on_remove()
{
    const auto item_ref = inventory()->at(_slot).unwrap();
    lua::lua->get_event_manager().trigger(
        lua::ItemInstanceEvent("core.item_removed", item_ref));
    ItemIdTable::instance().remove(obj_id);
    obj_id = ObjId::nil();

    inventory()->remove(_slot);
    _inventory = nullptr;
}



ItemRef item_separate(const ItemRef& stacked_item)
{
    if (stacked_item->number() <= 1)
    {
        return stacked_item;
    }

    auto slot_opt = inv_make_free_slot(stacked_item->inventory());
    if (!slot_opt)
    {
        slot_opt = inv_make_free_slot(inv_map());
        if (!slot_opt)
        {
            stacked_item->set_number(1);
            txt(i18n::s.get("core.item.something_falls_and_disappears"));
            return stacked_item;
        }
    }
    const auto slot = *slot_opt;
    const auto dst = item_separate(
        stacked_item,
        stacked_item->inventory(),
        slot,
        stacked_item->number() - 1);

    if (item_is_on_ground(dst))
    {
        if (const auto owner = item_get_owner(stacked_item).as_character())
        {
            stacked_item->set_position(owner->position);
        }
        dst->set_position(stacked_item->position());
        itemturn(dst);
        cell_refresh(dst->position().x, dst->position().y);
        if (!item_is_on_ground(stacked_item))
        {
            txt(i18n::s.get("core.item.something_falls_from_backpack"));
        }
        refresh_burden_state();
    }

    return dst;
}



bool chara_unequip(const ItemRef& item)
{
    if (item->body_part == 0)
        return false;

    int body_part = item->body_part;
    if (const auto owner = item_get_owner(item).as_character())
    {
        owner->equipment_slots[body_part - 100].unequip();
        item->body_part = 0;
        return true;
    }
    else
    {
        return false;
    }
}



IdentifyState item_identify(const ItemRef& item, IdentifyState level)
{
    if (level == IdentifyState::almost &&
        !is_equipment(the_item_db[item->id]->category))
    {
        level = IdentifyState::completely;
    }
    if (item->identify_state >= level)
    {
        idtresult = IdentifyState::unidentified;
        return idtresult;
    }
    item->identify_state = level;
    if (item->identify_state >= IdentifyState::partly)
    {
        itemmemory(0, the_item_db[item->id]->integer_id) = 1;
    }
    idtresult = level;
    return idtresult;
}



IdentifyState item_identify(const ItemRef& item, int power)
{
    return item_identify(
        item,
        power >= item->identify_level ? IdentifyState::completely
                                      : IdentifyState::unidentified);
}



void item_checkknown(const ItemRef& item)
{
    if (itemmemory(0, the_item_db[item->id]->integer_id) &&
        item->identify_state == IdentifyState::unidentified)
    {
        item_identify(item, IdentifyState::partly);
    }
}



void itemname_additional_info(const ItemRef& item)
{
    if (item->id == "core.kitty_bank")
    {
        s_ += i18n::s.get_enum("core.item.kitty_bank_rank", item->param2);
    }
    if (item->id == "core.bait")
    {
        s_ += lang(
            ""s + i18n::s.get_enum("core.item.bait_rank", item->param1),
            u8" <"s + i18n::s.get_enum("core.item.bait_rank", item->param1) +
                u8">"s);
    }
    if (item->id == "core.ancient_book")
    {
        if (jp)
        {
            if (item->param2 != 0)
            {
                s_ += u8"解読済みの"s;
            }
        }
        if (item->identify_state == IdentifyState::completely)
        {
            s_ += lang(
                u8"《"s +
                    i18n::s.get_enum(
                        "core.item.ancient_book_title", item->param1) +
                    u8"》という題名の"s,
                u8" titled <"s +
                    i18n::s.get_enum(
                        "core.item.ancient_book_title", item->param1) +
                    u8">"s);
        }
    }
    if (item->id == "core.recipe")
    {
        if (item->param1 == 0)
        {
            s_ += lang(u8"もう使えない"s, u8" which cannot be used anymore"s);
        }
        else if (item->subname == 0)
        {
            s_ += lang(u8"カスタム"s, ""s);
        }
        else
        {
            s_ += lang(
                u8"《"s + blending_get_recipe_name(item->subname) + u8"》の"s,
                u8" of <"s + blending_get_recipe_name(item->subname) + u8">"s);
        }
    }

    auto category = the_item_db[item->id]->category;

    if (category == ItemCategory::book)
    {
        if (item->id == "core.textbook")
        {
            s_ += lang(
                u8"《"s + the_ability_db.get_text(item->param1, "name") +
                    u8"》という題名の"s,
                u8" titled <Art of "s +
                    the_ability_db.get_text(item->param1, "name") + u8">"s);
        }
        else if (item->id == "core.book_of_rachel")
        {
            s_ += lang(u8"第"s, u8" of Rachel No."s) + item->param2 +
                lang(u8"巻目の"s, ""s);
        }
        else if (item->id == "core.book_b")
        {
            s_ += lang(
                u8"《"s + booktitle(item->param1) + u8"》という題名の"s,
                u8" titled <"s + booktitle(item->param1) + u8">"s);
        }
    }
    if (category == ItemCategory::altar)
    {
        if (item->param1 != 0)
        {
            s_ += lang(
                god_name(item->param1) + u8"の"s,
                u8" <"s + god_name(item->param1) + u8">"s);
        }
    }
    if (category == ItemCategory::food)
    {
        if (item->param1 != 0)
        {
            if (item->param2 != 0)
            {
                skip_ = 1;
                if (item->id == "core.fish_a")
                {
                    s_ = s_ +
                        foodname(
                             item->param1 / 1000,
                             the_fish_db.get_text(item->subname, "name"),
                             item->param2,
                             item->subname);
                }
                else
                {
                    s_ =
                        s_ +
                        foodname(
                            item->param1 / 1000,
                            ioriginalnameref(the_item_db[item->id]->integer_id),
                            item->param2,
                            item->subname);
                }
                return;
            }
        }
        if (item->own_state == OwnState::crop)
        {
            s_ += lang(""s, u8" grown "s) +
                i18n::s.get_enum("core.ui.weight", item->subname) +
                lang(u8"育った"s, ""s);
        }
    }
    if (item->subname != 0)
    {
        if (item->id == "core.fish_a" || item->id == "core.fish_b")
        {
            if (item->subname < 0 || item->subname >= 100)
            {
                s_ += u8"/bugged/"s;
                return;
            }
            s_ += the_fish_db.get_text(item->subname, "name");
        }
        else if (
            category == ItemCategory::food ||
            category == ItemCategory::bodyparts ||
            item->id == "core.figurine" || item->id == "core.card" ||
            item->id == "core.shit" || item->id == "core.bottle_of_milk")
        {
            if (item->subname < 0 || item->subname >= 800)
            {
                s_ += u8"/bugged/"s;
                return;
            }
            if (item->own_state != OwnState::crop)
            {
                s_ += lang(""s, u8" of "s) +
                    chara_db_get_name(int2charaid(item->subname));
                if (jp)
                {
                    s_ += u8"の"s;
                }
            }
        }
        if (category == ItemCategory::furniture)
        {
            if (jp)
            {
                if (item->subname >= 12)
                {
                    item->subname = 0;
                }
                else
                {
                    s_ += i18n::s.get_enum("core.ui.furniture", item->subname);
                }
            }
        }
        if (item->id == "core.deed")
        {
            s_ += lang(""s, u8" of "s) +
                i18n::s.get_enum("core.ui.home", item->param1) +
                lang(u8"の"s, ""s);
        }
        if (item->id == "core.bill")
        {
            s_ += lang(
                ""s + item->subname + u8"goldの"s,
                u8" <"s + item->subname + u8" gp>"s);
        }
        if (item->id == "core.vomit")
        {
            if (item->subname < 0 || item->subname >= 800)
            {
                s_ += u8"/bugged/"s;
                return;
            }
            s_ += lang(
                ""s + chara_db_get_name(int2charaid(item->subname)) + u8"の"s,
                u8" of "s + chara_db_get_name(int2charaid(item->subname)));
        }
    }
    if (item->id == "core.secret_treasure")
    {
        if (item->param1 == 169)
        {
            s_ += lang(u8"善人の"s, u8" of saint"s);
        }
        if (item->param1 == 162)
        {
            s_ += lang(u8"悪人の"s, u8" of wicked"s);
        }
        if (item->param1 == 163)
        {
            s_ += lang(u8"エヘカトルの"s, u8" of Ehekatl"s);
        }
        if (item->param1 == 164)
        {
            s_ += lang(u8"オパートスの"s, u8" of Opatos"s);
        }
        if (item->param1 == 165)
        {
            s_ += lang(u8"イツパロトルの"s, u8" of Itzpalt"s);
        }
        if (item->param1 == 166)
        {
            s_ += lang(u8"ジュアの"s, u8" of Jure"s);
        }
    }
}



std::string itemname(const ItemRef& item, lua_int number, bool with_article)
{
    std::string s2_;
    std::string s3_;
    int alpha_ = 0;
    std::string s4_;
    elona_vector1<std::string> buf_;
    if (the_item_db[item->id]->integer_id >= maxitemid - 2 ||
        static_cast<size_t>(the_item_db[item->id]->integer_id) >
            ioriginalnameref.size())
    {
        return i18n::s.get("core.item.unknown_item");
    }
    item_checkknown(item);
    if (number == 0)
    {
        number = item->number();
    }
    const auto category = the_item_db[item->id]->category;
    if (jp)
    {
        if (number > 1)
        {
            s2_ = u8"個の"s;
            if (category == ItemCategory::armor)
            {
                s2_ = u8"着の"s;
            }
            if (category == ItemCategory::spellbook ||
                category == ItemCategory::book)
            {
                if (item->id == "core.recipe")
                {
                    s2_ = u8"枚の"s;
                }
                else
                {
                    s2_ = u8"冊の"s;
                }
            }
            if (category == ItemCategory::melee_weapon)
            {
                s2_ = u8"本の"s;
            }
            if (category == ItemCategory::potion)
            {
                s2_ = u8"服の"s;
            }
            if (category == ItemCategory::scroll)
            {
                s2_ = u8"巻の"s;
            }
            if (category == ItemCategory::boots ||
                category == ItemCategory::gloves)
            {
                s2_ = u8"対の"s;
            }
            if (category == ItemCategory::gold_piece ||
                category == ItemCategory::platinum_coin ||
                item->id == "core.small_medal" ||
                item->id == "core.music_ticket" ||
                item->id == "core.token_of_friendship")
            {
                s2_ = u8"枚の"s;
            }
            if (item->id == "core.fish_a")
            {
                s2_ = u8"匹の"s;
            }
            s_ = ""s + number + s2_;
        }
        else
        {
            s_ = "";
        }
        if (item->identify_state == IdentifyState::completely)
        {
            switch (item->curse_state)
            {
            case CurseState::doomed:
                s_ += i18n::s.get("core.ui.curse_state.doomed");
                break;
            case CurseState::cursed:
                s_ += i18n::s.get("core.ui.curse_state.cursed");
                break;
            case CurseState::none: break;
            case CurseState::blessed:
                s_ += i18n::s.get("core.ui.curse_state.blessed");
                break;
            }
        }
    }
    else
    {
        s_ = "";
        if (item->identify_state == IdentifyState::completely)
        {
            switch (item->curse_state)
            {
            case CurseState::doomed:
                s_ = i18n::s.get("core.ui.curse_state.doomed") + u8" "s;
                break;
            case CurseState::cursed:
                s_ = i18n::s.get("core.ui.curse_state.cursed") + u8" "s;
                break;
            case CurseState::none: break;
            case CurseState::blessed:
                s_ = i18n::s.get("core.ui.curse_state.blessed") + u8" "s;
                break;
            }
        }
        if (irandomname(the_item_db[item->id]->integer_id) == 1 &&
            item->identify_state == IdentifyState::unidentified)
        {
            s2_ = "";
        }
        else
        {
            s2_ = ""s + ioriginalnameref2(the_item_db[item->id]->integer_id);
            if (strutil::contains(
                    ioriginalnameref(the_item_db[item->id]->integer_id),
                    u8"with"))
            {
                s3_ = "";
            }
            else if (strutil::contains(
                         ioriginalnameref(the_item_db[item->id]->integer_id),
                         u8"for testing"))
            {
                s3_ = "";
            }
            else
            {
                s3_ = u8"of";
            }
            if (item->identify_state != IdentifyState::unidentified &&
                s2_ == "")
            {
                if (item->weight < 0)
                {
                    s2_ = u8"cargo";
                }
                if (category == ItemCategory::boots ||
                    category == ItemCategory::gloves)
                {
                    s2_ = u8"pair";
                }
            }
            if (category == ItemCategory::food && item->param1 != 0 &&
                item->param2 != 0)
            {
                s2_ = u8"dish";
            }
        }
        if (s2_ != ""s)
        {
            if (!s3_.empty())
            {
                s3_ += " ";
            }
            if (number > 1)
            {
                if (s2_ == "variety")
                {
                    s_ = ""s + number + u8" " + s_ + u8"variety " + s3_;
                }
                else if (s2_ == "dish")
                {
                    s_ = ""s + number + u8" " + s_ + u8"dishes " + s3_;
                }
                else
                {
                    s_ = ""s + number + u8" " + s_ + s2_ + u8"s " + s3_;
                }
            }
            else
            {
                s_ = s_ + s2_ + u8" " + s3_;
            }
        }
        else if (number > 1)
        {
            s_ = ""s + number + u8" " + s_;
        }
    }
    if (item->material == "core.raw" && item->param3 < 0)
    {
        if (jp)
        {
            s_ += u8"腐った"s;
        }
        else
        {
            s_ += u8"rotten "s;
        }
    }
    if (en)
    {
        if (category == ItemCategory::food && item->param1 != 0 &&
            item->param2 != 0)
        {
            skip_ = 1;
        }
        if (item->subname != 0 && category == ItemCategory::furniture)
        {
            if (item->subname >= 12)
            {
                item->subname = 0;
            }
            else
            {
                s_ += i18n::s.get_enum("core.ui.furniture", item->subname) +
                    u8" "s;
            }
        }
        if (item->id == "core.ancient_book" && item->param2 != 0)
        {
            s_ += u8"undecoded "s;
        }
        if (item->id == "core.recipe" && item->subname == 0)
        {
            s_ += u8"custom "s;
        }
    }
    if (item->id == "core.material_kit")
    {
        s_ += ""s + the_item_material_db.get_text(item->material, "name") +
            lang(u8"製の"s, u8" "s);
    }
    if (jp)
    {
        itemname_additional_info(item);
    }
    if (category == ItemCategory::furniture && item->material != "")
    {
        if (jp)
        {
            s_ += ""s + the_item_material_db.get_text(item->material, "name") +
                u8"細工の"s;
        }
        else
        {
            s_ += ""s + the_item_material_db.get_text(item->material, "name") +
                u8"work "s;
        }
    }
    if (item->id == "core.gift")
    {
        s_ += i18n::s.get_enum("core.item.gift_rank", item->param4) +
            i18n::space_if_needed();
    }
    if (skip_ != 1)
    {
        alpha_ = 0;
        if (item->identify_state == IdentifyState::completely &&
            is_equipment(category))
        {
            if (item->is_eternal_force)
            {
                alpha_ = 1;
                s_ += lang(u8"エターナルフォース"s, u8"eternal force"s) +
                    i18n::space_if_needed();
            }
            else
            {
                if (item->subname >= 10000)
                {
                    if (item->subname < 20000)
                    {
                        if (jp)
                        {
                            s_ += egoname(item->subname - 10000) +
                                i18n::space_if_needed();
                        }
                    }
                    else if (item->subname < 40000)
                    {
                        s_ += egominorn(item->subname - 20000) +
                            i18n::space_if_needed();
                    }
                }
                if (item->quality != Quality::special)
                {
                    if (item->quality >= Quality::miracle)
                    {
                        s_ += the_item_material_db.get_text(
                                  item->material, "alias") +
                            i18n::space_if_needed();
                    }
                    else
                    {
                        s_ += the_item_material_db.get_text(
                                  item->material, "name") +
                            i18n::space_if_needed();
                        if (jp)
                        {
                            if (/* TODO is_katakana */ false)
                            {
                                alpha_ = 1;
                            }
                            else
                            {
                                s_ += u8"の"s;
                            }
                        }
                    }
                }
            }
        }
        if (item->identify_state == IdentifyState::unidentified)
        {
            s_ += iknownnameref(the_item_db[item->id]->integer_id);
        }
        else if (item->identify_state != IdentifyState::completely)
        {
            if (item->quality < Quality::miracle || !is_equipment(category))
            {
                s_ += ioriginalnameref(the_item_db[item->id]->integer_id);
            }
            else
            {
                s_ += iknownnameref(the_item_db[item->id]->integer_id);
            }
        }
        else if (item->quality == Quality::special || item->is_precious)
        {
            if (jp)
            {
                s_ = u8"★"s + s_ +
                    ioriginalnameref(the_item_db[item->id]->integer_id);
            }
            else
            {
                s_ += ioriginalnameref(the_item_db[item->id]->integer_id);
            }
        }
        else
        {
            if (item->quality >= Quality::miracle && jp)
            {
                s_ = u8"☆"s + s_;
            }
            if (alpha_ == 1 && jp)
            {
                s_ += ialphanameref(the_item_db[item->id]->integer_id);
            }
            else
            {
                s_ += ioriginalnameref(the_item_db[item->id]->integer_id);
            }
            if (en && is_equipment(category) && item->subname >= 10000 &&
                item->subname < 20000)
            {
                s_ += u8" "s + egoname((item->subname - 10000));
            }
            if (item->subname >= 40000)
            {
                randomize(item->subname - 40000);
                if (item->quality == Quality::miracle)
                {
                    s_ += i18n::space_if_needed() +
                        i18n::s.get(
                            "core.item.miracle_paren",
                            random_title(RandomTitleType::weapon));
                }
                else
                {
                    s_ += i18n::space_if_needed() +
                        i18n::s.get(
                            "core.item.godly_paren",
                            random_title(RandomTitleType::weapon));
                }
                randomize();
            }
        }
    }
    if (en)
    {
        if (with_article)
        {
            if (item->identify_state == IdentifyState::completely &&
                (item->quality >= Quality::miracle && is_equipment(category)))
            {
                s_ = u8"the "s + s_;
            }
            else if (number == 1)
            {
                s4_ = strmid(s_, 0, 1);
                if (s4_ == u8"a"s || s4_ == u8"o"s || s4_ == u8"i"s ||
                    s4_ == u8"u"s || s4_ == u8"e"s)
                {
                    s_ = u8"an "s + s_;
                }
                else
                {
                    s_ = u8"a "s + s_;
                }
            }
        }
        if (s2_ == "" && item->id != "core.fish_a" && number > 1)
        {
            switch (s_.back())
            {
            case 'f':
                if (strutil::ends_with(s_, "staff"))
                {
                    s_ = s_.substr(0, s_.size() - 2) + "ves"; // staff -> staves
                }
                else
                {
                    s_ =
                        s_.substr(0, s_.size() - 1) + "ves"; // shelf -> shelves
                }
                break;
            case 's':
                if (!strutil::ends_with(s_, "stairs"))
                {
                    s_ += "es"; // upstairs -> upstairs / dress -> dresses
                }
                break;
            case 'y':
                if (strutil::ends_with(s_, "key") ||
                    strutil::ends_with(s_, "toy"))
                {
                    s_ += "s"; // key -> keys / toy -> toys
                }
                else
                {
                    s_ = s_.substr(0, s_.size() - 1) +
                        "ies"; // cherry -> cherries
                }
                break;
            case 'o':
                if (strutil::ends_with(s_, "tomato") ||
                    strutil::ends_with(s_, "potato"))
                {
                    s_ += "es"; // tomato -> tomatoes / potato -> potatoes
                }
                else
                {
                    s_ += "s"; // piano -> pianos
                }
                break;
            case 'x':
                s_ += "es"; // box -> boxes
                break;
            case 'h':
                if (strutil::ends_with(s_, "sh"))
                {
                    s_ += "es"; // dish -> dishes
                }
                else if (strutil::ends_with(s_, "ch"))
                {
                    s_ += "es"; // torch -> torches
                }
                else
                {
                    s_ += "s";
                }
                break;
            default: s_ += "s"; break;
            }
        }
        itemname_additional_info(item);
    }
    if (item->identify_state == IdentifyState::completely)
    {
        if (item->bonus_value != 0)
        {
            s_ += ""s + cnvfix(item->bonus_value) + u8" "s;
        }
        if (item->has_charges)
        {
            s_ += i18n::s.get("core.item.charges", item->charges);
        }
        if (item->dice.rolls != 0 || item->hit_bonus != 0 ||
            item->dice.bonus != 0)
        {
            s_ += u8" ("s;
            if (item->dice.rolls != 0)
            {
                s_ += ""s + item->dice.rolls + u8"d"s + item->dice.faces;
                if (item->dice.bonus != 0)
                {
                    if (item->dice.bonus > 0)
                    {
                        s_ += u8"+"s + item->dice.bonus;
                    }
                    else
                    {
                        s_ += ""s + item->dice.bonus;
                    }
                }
                s_ += u8")"s;
                if (item->hit_bonus != 0)
                {
                    s_ += u8"("s + item->hit_bonus + u8")"s;
                }
            }
            else
            {
                s_ +=
                    ""s + item->hit_bonus + u8","s + item->dice.bonus + u8")"s;
            }
        }
        if (item->dv != 0 || item->pv != 0)
        {
            s_ += u8" ["s + item->dv + u8","s + item->pv + u8"]"s;
        }
    }
    if (en && (item->id == "core.wallet" || item->id == "core.suitcase"))
    {
        s_ += u8"(Lost property)"s;
    }
    if (item->id == "core.fishing_pole" && item->charges != 0)
    {
        s_ += lang(
            u8"("s + i18n::s.get_enum("core.item.bait_rank", item->param4) +
                u8"残り"s + item->charges + u8"匹)"s,
            u8"("s + item->charges + u8" "s +
                i18n::s.get_enum("core.item.bait_rank", item->param4) + u8")"s);
    }
    if (item->id == "core.monster_ball")
    {
        if (item->subname == 0)
        {
            s_ += lang(u8" Lv"s, u8" Level "s) + item->param2 +
                lang(u8" (空)"s, u8"(Empty)"s);
        }
        else
        {
            s_ += u8" ("s + chara_db_get_name(int2charaid(item->subname)) +
                u8")"s;
        }
    }
    if (item->id == "core.small_gamble_chest")
    {
        s_ += lang(u8" Lv"s, u8" Level "s) + item->param2;
    }
    if (item->identify_state == IdentifyState::almost && is_equipment(category))
    {
        s_ += u8" ("s +
            cnven(i18n::s.get_enum(
                u8"core.ui.quality", static_cast<int>(item->quality))) +
            u8")"s;
        if (jp)
        {
            s_ += u8"["s +
                the_item_material_db.get_text(item->material, "name") +
                u8"製]"s;
        }
        else
        {
            s_ += u8"["s +
                cnven(the_item_material_db.get_text(item->material, "name")) +
                u8"]"s;
        }
        if (item->curse_state == CurseState::cursed)
        {
            s_ += i18n::s.get("core.item.approximate_curse_state.cursed");
        }
        if (item->curse_state == CurseState::doomed)
        {
            s_ += i18n::s.get("core.item.approximate_curse_state.doomed");
        }
    }
    if (category == ItemCategory::chest)
    {
        if (item->id == "core.shopkeepers_trunk")
        {
            s_ += lang(u8"(移動時消滅)"s, u8"(Temporal)"s);
        }
        else if (item->charges == 0)
        {
            if (item->param1 == 0)
            {
                s_ += lang(u8"(空っぽ)"s, u8"(Empty)"s);
            }
        }
    }
    if (category == ItemCategory::cargo && item->param2 != 0)
    {
        s_ += lang(
            u8"(仕入れ値 "s + item->param2 + u8"g)"s,
            u8"(Buying price: "s + item->param2 + u8")"s);
    }
    if (item->is_aphrodisiac)
    {
        s_ += lang(u8"(媚薬混入)"s, u8"(Aphrodisiac)"s);
    }
    if (item->is_poisoned)
    {
        s_ += lang(u8"(毒物混入)"s, u8"(Poisoned)"s);
    }
    if (item->has_cooldown_time && game_data.date.hours() < item->charges)
    {
        s_ += lang(
            u8"("s + (item->charges - game_data.date.hours()) + u8"時間)"s,
            u8"(Next: "s + (item->charges - game_data.date.hours()) + u8"h.)"s);
    }
    if (item->id == "core.shelter" && item->charges != 0)
    {
        s_ += lang(u8" シリアルNo."s, u8" serial no."s) + item->charges;
    }
    if (item->id == "core.disc")
    {
        s_ += u8" <BGM"s + item->param1 + u8">"s;
    }
    if (strlen_u(s_) > 66)
    {
        s_ = zentohan(s_);
    }
    skip_ = 0;
    return s_;
}



void remain_make(const ItemRef& remain, const Character& chara)
{
    remain->subname = charaid2int(chara.id);
    remain->tint = chara.image / 1000;

    if (remain->id == "core.corpse")
    {
        remain->weight = 250 * (chara.weight + 100) / 100 + 500;
        remain->value = remain->weight / 5;
    }
    else
    {
        remain->weight = 20 * (chara.weight + 500) / 500;
        remain->value = chara.level * 40 + 600;
        if (the_character_db[charaid2int(chara.id)]->rarity / 1000 < 20 &&
            chara.original_relationship < -1)
        {
            remain->value *= clamp(
                4 - the_character_db[charaid2int(chara.id)]->rarity / 1000 / 5,
                1,
                5);
        }
    }
}



void item_dump_desc(const ItemRef& item)
{
    reftype = (int)the_item_db[item->id]->category;

    item_db_get_charge_level(item, the_item_db[item->id]->integer_id);
    item_db_get_description(item, the_item_db[item->id]->integer_id);

    p = item_load_desc(item);

    listmax = p;
    pagemax = (listmax - 1) / pagesize;
}



void item_acid(const Character& owner, OptionalItemRef item)
{
    if (!item)
    {
        for (const auto& equipment_slot : owner.equipment_slots)
        {
            if (!equipment_slot)
            {
                break;
            }
            if (!equipment_slot.equipment)
            {
                continue;
            }
            if (equipment_slot.equipment->bonus_value >= -3)
            {
                if (rnd(30) == 0)
                {
                    item = equipment_slot.equipment;
                    break;
                }
            }
        }
        if (!item)
        {
            return;
        }
    }

    if (!is_equipment(the_item_db[item->id]->category))
    {
        return;
    }

    if (item->is_acidproof)
    {
        txt(i18n::s.get("core.item.acid.immune", owner, item.unwrap()));
    }
    else
    {
        txt(i18n::s.get("core.item.acid.damaged", owner, item.unwrap()),
            Message::color{ColorIndex::purple});
        --item->bonus_value;
    }
}



bool item_fire(const InventoryRef& inv, const OptionalItemRef& burned_item)
{
    OptionalItemRef blanket;
    std::vector<ItemRef> list;
    if (burned_item)
    {
        list.emplace_back(burned_item.unwrap());
    }

    auto inv_owner = inv_get_owner(inv);
    if (const auto owner = inv_owner.as_character())
    {
        if (owner->get_skill(50).level / 50 >= 6 ||
            owner->quality >= Quality::miracle)
        {
            return false;
        }
        for (const auto& item : *inv)
        {
            if (item->id == "core.fireproof_blanket")
            {
                if (!blanket)
                {
                    blanket = item;
                }
                continue;
            }
            if (!burned_item)
            {
                list.emplace_back(item);
            }
        }
    }

    if (list.empty())
    {
        return false;
    }

    bool burned{};

    for (int _i = 0; _i < 3; ++_i)
    {
        const auto item = choice(list);
        if (item->number() <= 0)
        {
            continue;
        }
        rowact_item(item);
        if (item->is_fireproof || item->is_precious)
        {
            continue;
        }

        const auto category = the_item_db[item->id]->category;
        if (category == ItemCategory::food && item->param2 == 0)
        {
            if (inv_owner.is_map())
            {
                if (is_in_fov(item->position()))
                {
                    txt(i18n::s.get(
                            "core.item.item_on_the_ground_get_broiled", item),
                        Message::color{ColorIndex::gold});
                }
            }
            else
            {
                assert(inv_owner.is_character());
                if (is_in_fov(*inv_owner.as_character()))
                {
                    txt(i18n::s.get(
                            "core.item.item_on_the_ground_get_broiled",
                            item,
                            *inv_owner.as_character()),
                        Message::color{ColorIndex::gold});
                }
            }
            make_dish(item, rnd(5) + 1);
            burned = true;
            continue;
        }

        if (category == ItemCategory::chest || category == ItemCategory::tool ||
            category == ItemCategory::gold_piece ||
            item->quality >= Quality::miracle)
        {
            continue;
        }

        if (item->body_part != 0)
        {
            if (rnd(2))
            {
                continue;
            }
        }

        if (category != ItemCategory::rod && category != ItemCategory::tree &&
            category != ItemCategory::book &&
            category != ItemCategory::scroll &&
            category != ItemCategory::spellbook)
        {
            if (rnd(4))
            {
                continue;
            }
            if (inv_owner.is_character())
            {
                if (rnd(4))
                {
                    continue;
                }
            }
        }

        if (blanket)
        {
            assert(inv_owner.is_character());
            item_separate(blanket.unwrap());
            if (is_in_fov(*inv_owner.as_character()))
            {
                txt(i18n::s.get(
                    "core.item.fireproof_blanket_protects_item",
                    blanket.unwrap(),
                    *inv_owner.as_character()));
            }
            if (blanket->charges > 0)
            {
                --blanket->charges;
            }
            else if (rnd(20) == 0)
            {
                blanket->modify_number(-1);
                if (is_in_fov(*inv_owner.as_character()))
                {
                    txt(i18n::s.get(
                        "core.item.fireproof_blanket_turns_to_dust",
                        blanket.unwrap()));
                }
                break;
            }
            continue;
        }

        int p_ = rnd_capped(item->number()) / 2 + 1;
        if (const auto owner = inv_owner.as_character())
        {
            if (item->body_part != 0)
            {
                if (is_in_fov(*owner))
                {
                    txt(i18n::s.get(
                            "core.item.item_someone_equips_turns_to_dust",
                            itemname(item, p_),
                            p_,
                            *owner),
                        Message::color{ColorIndex::purple});
                }
                owner->equipment_slots[item->body_part - 100].unequip();
                item->body_part = 0;
                chara_refresh(*owner);
            }
            else if (is_in_fov(*owner))
            {
                txt(i18n::s.get(
                        "core.item.someones_item_turns_to_dust",
                        itemname(item, p_, false),
                        p_,
                        *owner),
                    Message::color{ColorIndex::purple});
            }
        }
        else if (is_in_fov(item->position()))
        {
            txt(i18n::s.get(
                    "core.item.item_on_the_ground_turns_to_dust",
                    itemname(item, p_),
                    p_),
                Message::color{ColorIndex::purple});
        }
        item->modify_number(-p_);
        burned = true;
    }

    refresh_burden_state();
    return burned;
}



void mapitem_fire(optional_ref<Character> arsonist, int x, int y)
{
    if (cell_data.at(x, y).item_info_actual.is_empty())
    {
        return;
    }

    OptionalItemRef burned_item;
    for (const auto& item : *inv_map())
    {
        if (item->position() == Position{x, y})
        {
            burned_item = item;
            break;
        }
    }
    if (burned_item)
    {
        const auto burned = item_fire(inv_map(), burned_item);
        if (burned)
        {
            if (cell_data.at(x, y).mef_index_plus_one == 0)
            {
                mef_add(
                    x,
                    y,
                    5,
                    24,
                    rnd(10) + 5,
                    100,
                    arsonist ? arsonist->index : -1);
            }
        }
    }
}



bool item_cold(const InventoryRef& inv, const OptionalItemRef& destroyed_item)
{
    OptionalItemRef blanket;
    std::vector<ItemRef> list;
    if (destroyed_item)
    {
        list.emplace_back(destroyed_item.unwrap());
    }

    auto inv_owner = inv_get_owner(inv);
    if (const auto owner = inv_owner.as_character())
    {
        if (owner->get_skill(51).level / 50 >= 6 ||
            owner->quality >= Quality::miracle)
        {
            return false;
        }
        for (const auto& item : *inv)
        {
            if (item->id == "core.coldproof_blanket")
            {
                if (!blanket)
                {
                    blanket = item;
                }
                continue;
            }
            if (!destroyed_item)
            {
                list.emplace_back(item);
            }
        }
    }
    if (list.empty())
    {
        return false;
    }

    bool broken{};
    for (int _i = 0; _i < 2; ++_i)
    {
        const auto item = choice(list);
        if (item->number() <= 0)
        {
            continue;
        }
        rowact_item(item);
        if (item->is_precious)
        {
            continue;
        }

        const auto category = the_item_db[item->id]->category;
        if (category == ItemCategory::chest || category == ItemCategory::tool ||
            category == ItemCategory::gold_piece)
        {
            continue;
        }
        if (item->quality >= Quality::miracle || item->body_part != 0)
        {
            continue;
        }
        if (category != ItemCategory::potion)
        {
            if (rnd(30))
            {
                continue;
            }
        }
        if (blanket)
        {
            assert(inv_owner.is_character());
            item_separate(blanket.unwrap());
            if (is_in_fov(*inv_owner.as_character()))
            {
                txt(i18n::s.get(
                    "core.item.coldproof_blanket_protects_item",
                    blanket.unwrap(),
                    *inv_owner.as_character()));
            }
            if (blanket->charges > 0)
            {
                --blanket->charges;
            }
            else if (rnd(20) == 0)
            {
                blanket->modify_number(-1);
                if (is_in_fov(*inv_owner.as_character()))
                {
                    txt(i18n::s.get(
                        "core.item.coldproof_blanket_is_broken_to_pieces",
                        blanket.unwrap()));
                }
                break;
            }
            continue;
        }
        int p_ = rnd_capped(item->number()) / 2 + 1;
        if (const auto owner = inv_owner.as_character())
        {
            if (is_in_fov(*owner))
            {
                txt(i18n::s.get(
                        "core.item.someones_item_breaks_to_pieces",
                        itemname(item, p_, false),
                        p_,
                        *owner),
                    Message::color{ColorIndex::purple});
            }
        }
        else if (is_in_fov(item->position()))
        {
            txt(i18n::s.get(
                    "core.item.item_on_the_ground_breaks_to_pieces",
                    itemname(item, p_),
                    p_),
                Message::color{ColorIndex::purple});
        }
        item->modify_number(-p_);
        broken = true;
    }

    refresh_burden_state();
    return broken;
}



void mapitem_cold(int x, int y)
{
    if (cell_data.at(x, y).item_info_actual.is_empty())
    {
        return;
    }
    OptionalItemRef destroyed_item;
    for (const auto& item : *inv_map())
    {
        if (item->position() == Position{x, y})
        {
            destroyed_item = item;
            break;
        }
    }
    if (destroyed_item)
    {
        item_cold(inv_map(), destroyed_item);
    }
}



ItemOwner item_get_owner(const ItemRef& item)
{
    return inv_get_owner(item->inventory());
}



bool item_is_on_ground(const ItemRef& item)
{
    return item_get_owner(item).is_map();
}



void item_drop(
    const ItemRef& item_in_inventory,
    lua_int num,
    bool building_shelter)
{
    const auto slot = inv_make_free_slot_force(inv_map());
    const auto dropped_item =
        item_separate(item_in_inventory, inv_map(), slot, num);
    dropped_item->set_position(cdata.player().position);
    itemturn(dropped_item);

    if (building_shelter)
    {
        dropped_item->own_state = OwnState::shelter;
        dropped_item->charges = game_data.next_shelter_serial_id + 100;
        ++game_data.next_shelter_serial_id;
    }
    else
    {
        snd("core.drop1");
        txt(i18n::s.get("core.action.drop.execute", itemname(dropped_item)));
    }

    if (dropped_item->id == "core.bottle_of_water") // Water
    {
        if (const auto altar = item_find(ItemCategory::altar))
        {
            // The altar is your god's.
            if (core_god::int2godid(altar->param1) == cdata.player().god_id)
            {
                if (dropped_item->curse_state != CurseState::blessed)
                {
                    snd("core.pray1");
                    dropped_item->curse_state = CurseState::blessed;
                    txt(i18n::s.get("core.action.drop.water_is_blessed"),
                        Message::color{ColorIndex::green});
                }
            }
        }
    }

    const auto stacked_item = inv_stack(inv_map(), dropped_item).stacked_item;

    refresh_burden_state();
    cell_refresh(stacked_item->position().x, stacked_item->position().y);
    screenupdate = -1;
    update_screen();

    if (area_data[game_data.current_map].id == mdata_t::MapId::museum)
    {
        if (mode == 0)
        {
            update_museum();
        }
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        if (mode == 0)
        {
            building_update_home_rank();
        }
    }
    if (stacked_item->id == "core.campfire")
    {
        map_data.play_campfire_sound = 1;
        play_music();
    }
}



void item_build_shelter(const ItemRef& shelter)
{
    item_drop(shelter, 1, true);
}



int iequiploc(const ItemRef& item)
{
    switch (the_item_db[item->id]->category)
    {
    case ItemCategory::helm: return 1;
    case ItemCategory::necklace: return 2;
    case ItemCategory::cloak: return 3;
    case ItemCategory::armor: return 4;
    case ItemCategory::melee_weapon: return 5;
    case ItemCategory::shield: return 5;
    case ItemCategory::ring: return 6;
    case ItemCategory::gloves: return 7;
    case ItemCategory::boots: return 9;
    case ItemCategory::ranged_weapon: return 10;
    case ItemCategory::ammo: return 11;
    case ItemCategory::belt: return 8;
    default: return 0;
    }
}



std::vector<int> item_get_inheritance(const ItemRef& item)
{
    std::vector<int> result;

    randomize(item->turn + 1);
    for (int _i = 0; _i < 10; ++_i)
    {
        const auto enc_index = rnd(15);
        if (enc_index == 0)
            continue;
        if (item->enchantments[enc_index].id == 0)
            continue;

        const auto exists = range::find(result, enc_index) != std::end(result);
        if (exists)
            continue;

        if (item->enchantments[enc_index].power < 0 ||
            static_cast<int>(result.size()) < rnd(4))
        {
            result.push_back(enc_index);
        }
    }
    randomize();

    return result;
}



void auto_identify()
{
    if (cdata.player().confused != 0 || cdata.player().sleep != 0 ||
        cdata.player().paralyzed != 0 || cdata.player().choked != 0)
    {
        return;
    }

    for (const auto& item : *inv_player())
    {
        if (item->identify_state == IdentifyState::completely)
        {
            continue;
        }
        if (!is_equipment(the_item_db[item->id]->category))
        {
            continue;
        }

        const auto skill = cdata.player().get_skill(13).level +
            cdata.player().get_skill(162).level * 5;
        const auto difficulty = 1500 + item->identify_level * 5;
        if (skill > rnd(difficulty * 5))
        {
            const auto prev_name = itemname(item);
            item_identify(item, IdentifyState::completely);
            itemmemory(0, the_item_db[item->id]->integer_id) = 1;
            if (!g_config.hide_autoidentify())
            {
                txt(i18n::s.get(
                    "core.misc.identify.fully_identified", prev_name, item));
            }
            chara_gain_skill_exp(cdata.player(), 162, 50);
        }
        if (item->identify_state <= IdentifyState::partly)
        {
            if (skill > rnd(difficulty))
            {
                if (!g_config.hide_autoidentify())
                {
                    txt(i18n::s.get(
                        "core.misc.identify.almost_identified",
                        item,
                        i18n::s.get_enum(
                            u8"core.ui.quality",
                            static_cast<int>(item->quality))));
                }
                item_identify(item, IdentifyState::almost);
                chara_gain_skill_exp(cdata.player(), 162, 50);
            }
        }
    }
}



bool cargocheck(const ItemRef& item)
{
    if (!the_item_db[item->id]->is_cargo)
        return true;

    if (map_data.type != mdata_t::MapType::world_map &&
        map_data.type != mdata_t::MapType::player_owned &&
        map_data.type != mdata_t::MapType::town &&
        map_data.type != mdata_t::MapType::field &&
        map_data.type != mdata_t::MapType::shelter &&
        map_data.type != mdata_t::MapType::guild)
    {
        txt(i18n::s.get("core.ui.inv.cannot_use_cargo_items"),
            Message::only_once{true});
        snd("core.fail1");
        return false;
    }
    else
    {
        return true;
    }
}



ItemRef item_convert_artifact(
    const ItemRef& artifact,
    bool ignore_map_inventory)
{
    if (!is_equipment(the_item_db[artifact->id]->category))
    {
        return artifact; // is not an equipment.
    }
    if (artifact->quality != Quality::special)
    {
        return artifact; // is not a unique artifact.
    }
    if (artifact->body_part != 0)
    {
        return artifact; // is equipped.
    }

    bool found = false;
    for (auto&& chara : cdata.player_and_allies())
    {
        if (chara.state() == Character::State::empty)
        {
            continue;
        }
        for (const auto& item : *chara.inventory())
        {
            if (item->id == artifact->id && item != artifact)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }
    }
    if (!found && !ignore_map_inventory)
    {
        for (const auto& item : *inv_map())
        {
            if (item->id == artifact->id && item != artifact)
            {
                found = true;
                break;
            }
        }
    }
    if (!found)
    {
        return artifact; // is unique.
    }

    // Save some properties to avoid use-after-free.
    const auto original_item_name = itemname(artifact);
    const auto artifact_id = artifact->id;
    const auto artifact_pos = artifact->position();
    const auto artifact_inv = artifact->inventory();

    artifact->remove();

    while (true)
    {
        flt(the_item_db[artifact_id]->level, Quality::miracle);
        flttypeminor = the_item_db[artifact_id]->subcategory;
        if (const auto converted_item =
                itemcreate(artifact_inv, 0, artifact_pos, 0))
        {
            if (converted_item->quality != Quality::special)
            {
                txt(i18n::s.get(
                    "core.misc.artifact_regeneration",
                    original_item_name,
                    converted_item.unwrap()));
                return converted_item.unwrap();
            }
            else
            {
                converted_item->remove();
            }
        }
    }
}



void damage_by_cursed_equipments(Character& chara)
{
    if (rnd(4) == 0)
    {
        damage_hp(chara, chara.hp * (5 + chara.curse_power / 5) / 100, -5);
        return;
    }
    if (map_data.type != mdata_t::MapType::world_map)
    {
        if (rnd(10 - clamp(chara.curse_power / 10, 0, 9)) == 0)
        {
            efid = 408;
            magic(chara, chara);
            return;
        }
    }
    if (rnd(10) == 0)
    {
        if (chara.gold > 0)
        {
            p = rnd_capped(chara.gold) / 100 + rnd(10) + 1;
            if (p > chara.gold)
            {
                p = chara.gold;
            }
            chara.gold -= p;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.misc.curse.gold_stolen", chara),
                    Message::color{ColorIndex::purple});
            }
            return;
        }
    }
}



void dipcursed(const ItemRef& item)
{
    if (the_item_db[item->id]->category == ItemCategory::food)
    {
        if (item->material == "core.raw")
        {
            txt(i18n::s.get("core.action.dip.rots", item));
            item->param3 = -1;
            item->image = 336;
        }
        else
        {
            txt(i18n::s.get("core.action.dip.unchanged", item));
        }
    }
    else if (is_equipment(the_item_db[item->id]->category))
    {
        --item->bonus_value;
        txt(i18n::s.get("core.action.dip.rusts", item));
        if (const auto owner = item_get_owner(item).as_character())
        {
            chara_refresh(*owner);
        }
    }
    else
    {
        txt(i18n::s.get("core.common.nothing_happens"));
    }
}



int efstatusfix(int doomed, int cursed, int none, int blessed)
{
    switch (efstatus)
    {
    case CurseState::doomed: return doomed;
    case CurseState::cursed: return cursed;
    case CurseState::none: return none;
    case CurseState::blessed: return blessed;
    default: assert(0); return none;
    }
}



void equip_melee_weapon(Character& chara)
{
    attacknum = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (chara.equipment_slots[cnt].type != 5)
        {
            continue;
        }
        if (!chara.equipment_slots[cnt].equipment)
        {
            continue;
        }
        const auto weapon = chara.equipment_slots[cnt].equipment.unwrap();
        if (weapon->dice.rolls == 0)
        {
            continue;
        }
        ++attacknum;
        if (chara.combat_style.two_hand())
        {
            if (weapon->weight >= 4000)
            {
                txt(i18n::s.get(
                    "core.action.equip.two_handed.fits_well", weapon));
            }
            else
            {
                txt(i18n::s.get(
                    "core.action.equip.two_handed.too_light", weapon));
            }
        }
        if (chara.combat_style.dual_wield())
        {
            if (attacknum == 1)
            {
                if (weapon->weight >= 4000)
                {
                    txt(i18n::s.get(
                        "core.action.equip.two_handed.too_heavy", weapon));
                }
            }
            else if (weapon->weight > 1500)
            {
                txt(i18n::s.get(
                    "core.action.equip.two_handed.too_heavy_other_hand",
                    weapon));
            }
        }
        if (chara.is_player())
        {
            if (game_data.mount != 0)
            {
                if (weapon->weight >= 4000)
                {
                    txt(i18n::s.get(
                        "core.action.equip.two_handed.too_heavy_when_riding",
                        weapon));
                }
            }
        }
    }
}

} // namespace elona
