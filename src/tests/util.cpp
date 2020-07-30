#include "../elona/config.hpp"
#include "../elona/enums.hpp"
#include "../elona/i18n.hpp"
#include "../elona/init.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/api_manager.hpp"
#include "../elona/lua_env/export_manager.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/set_item_info.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"



namespace elona
{
namespace testing
{

void set_english()
{
    config_set_string("core.language.language", "en");
    elona::jp = 0;
    elona::en = 1;
    initialize_i18n();
    set_item_info();
}

void set_japanese()
{
    config_set_string("core.language.language", "jp");
    elona::jp = 1;
    elona::en = 0;
    initialize_i18n();
    set_item_info();
}

void normalize_item(const ItemRef& i)
{
    i->quality = Quality::great;
    i->curse_state = CurseState::none;
    i->identify_state = IdentifyState::completely;
    i->material = 34;
    i->quality = Quality::bad;
    i->dv = 0;
    i->pv = 0;
    i->count = 1;
    i->dice_x = 0;
    i->dice_y = 0;
    i->damage_bonus = 0;
    i->hit_bonus = 0;
    i->subname = 0;
    i->enchantments.clear();
}

std::string test_itemname(int id, int number, bool prefix)
{
    const auto item = itemcreate_map_inv(id, 0, 0, number);
    REQUIRE_SOME(item);
    normalize_item(item.unwrap());
    std::string name = itemname(item.unwrap(), number, prefix);
    item->remove();
    item->clear();
    return name;
}

Character& create_chara(int id, int x, int y)
{
    elona::fixlv = Quality::none;
    const auto chara = chara_create(-1, id, x, y);
    REQUIRE_SOME(chara);
    return *chara;
}

ItemRef create_item(int id, int number)
{
    const auto item_opt = itemcreate_map_inv(id, 0, 0, number);
    REQUIRE_SOME(item_opt);
    const auto item = item_opt.unwrap();
    normalize_item(item);
    return item;
}

void invalidate_item(const ItemRef& item)
{
    const Item* old_address = item.get_raw_ptr();
    int old_id = itemid2int(item->id);
    const auto [old_x, old_y] = item->pos();

    // Delete the item and create new ones until the index is taken again.
    item->remove();
    item->clear();
    while (true)
    {
        const auto new_item = itemcreate_map_inv(old_id, old_x, old_y, 3);
        REQUIRE_SOME(new_item);
        if (new_item.unwrap().get_raw_ptr() != old_address)
        {
            break;
        }
    }
}

void invalidate_chara(Character& chara)
{
    int old_index = chara.index;
    int old_id = charaid2int(chara.id);
    int old_x = chara.position.x;
    int old_y = chara.position.y;

    // Delete the character and create new ones until the index is taken again.
    chara_delete(chara.index);
    while (true)
    {
        const auto new_chara = chara_create(-1, old_id, old_x, old_y);
        REQUIRE_SOME(new_chara);
        if (new_chara->index != old_index)
        {
            break;
        }
    }
}

void register_lua_function(
    lua::LuaEnv& lua,
    std::string mod_id,
    std::string callback_signature,
    std::string callback_body)
{
    lua.load_mods();

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_testing_mod_from_script(mod_id, ""));
    REQUIRE_NOTHROW(lua.get_api_manager().load_script(
        mod_id,
        "\
local exports = {}\
\
function exports." +
            callback_signature + "\n" + callback_body + R"(
end

ELONA.api:add(exports)
)"));

    lua.get_export_manager().register_all_exports();
}

} // namespace testing
} // namespace elona
