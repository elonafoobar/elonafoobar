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

void normalize_item(Item& i)
{
    i.quality = Quality::great;
    i.curse_state = CurseState::none;
    i.identify_state = IdentifyState::completely;
    i.material = 34;
    i.quality = Quality::bad;
    i.dv = 0;
    i.pv = 0;
    i.count = 1;
    i.dice_x = 0;
    i.dice_y = 0;
    i.damage_bonus = 0;
    i.hit_bonus = 0;
    i.subname = 0;
    i.enchantments.clear();
}

std::string test_itemname(int id, int number, bool prefix)
{
    REQUIRE_SOME(itemcreate_extra_inv(id, 0, 0, number));
    int index = elona::ci;
    normalize_item(elona::inv[index]);
    std::string name = itemname(index, number, prefix ? 0 : 1);
    item_delete(inv[index]);
    return name;
}

Character& create_chara(int id, int x, int y)
{
    elona::fixlv = Quality::none;
    REQUIRE(chara_create(-1, id, x, y));
    return elona::cdata[elona::rc];
}

Item& create_item(int id, int number)
{
    REQUIRE_SOME(itemcreate_extra_inv(id, 0, 0, number));
    normalize_item(elona::inv[elona::ci]);
    return elona::inv[elona::ci];
}

void invalidate_item(Item& item)
{
    int old_index = item.index;
    int old_id = itemid2int(item.id);
    int old_x = item.position.x;
    int old_y = item.position.y;

    // Delete the item and create new ones until the index is taken again.
    item_delete(inv[old_index]);
    do
    {
        REQUIRE_SOME(itemcreate_extra_inv(old_id, old_x, old_y, 3));
    } while (elona::ci != old_index);
}

void invalidate_chara(Character& chara)
{
    int old_index = chara.index;
    int old_id = charaid2int(chara.id);
    int old_x = chara.position.x;
    int old_y = chara.position.y;

    // Delete the character and create new ones until the index is taken again.
    chara_delete(chara.index);
    do
    {
        REQUIRE(chara_create(-1, old_id, old_x, old_y));
    } while (elona::rc != old_index);
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

api:add(exports)
)"));

    lua.get_export_manager().register_all_exports();
}

} // namespace testing
} // namespace elona
