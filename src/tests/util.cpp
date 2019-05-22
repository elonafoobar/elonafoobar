#include "../thirdparty/catch2/catch.hpp"

#include "../elona/config/config.hpp"
#include "../elona/enums.hpp"
#include "../elona/i18n.hpp"
#include "../elona/init.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/export_manager.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/variables.hpp"
#include "tests.hpp"

namespace elona
{
namespace testing
{

void set_english()
{
    Config::instance().set("core.language.language", "en");
    elona::jp = 0;
    elona::en = 1;
    initialize_i18n();
    set_item_info();
}

void set_japanese()
{
    Config::instance().set("core.language.language", "jp");
    elona::jp = 1;
    elona::en = 0;
    initialize_i18n();
    set_item_info();
}

void normalize_item(Item& i)
{
    i.quality = Quality::great;
    i.curse_state = CurseState::none;
    i.identification_state = IdentifyState::completely_identified;
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
    REQUIRE_SOME(itemcreate(-1, id, 0, 0, number));
    int index = elona::ci;
    normalize_item(elona::inv[index]);
    std::string name = itemname(index, number, prefix ? 0 : 1);
    item_delete(index);
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
    REQUIRE_SOME(itemcreate(-1, id, 0, 0, number));
    normalize_item(elona::inv[elona::ci]);
    return elona::inv[elona::ci];
}

void invalidate_item(Item& item)
{
    int old_index = item.index;
    int old_id = item.id;
    int old_x = item.position.x;
    int old_y = item.position.y;

    // Delete the item and create new ones until the index is taken again.
    item_delete(old_index);
    do
    {
        REQUIRE_SOME(itemcreate(-1, old_id, old_x, old_y, 3));
    } while (elona::ci != old_index);
}

void invalidate_chara(Character& chara)
{
    int old_index = chara.index;
    int old_id = chara.id;
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
    lua.get_mod_manager().load_mods(filesystem::dir::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        mod_id,
        "\
local Exports = {}\
\
function Exports." +
            callback_signature + "\n" + callback_body + R"(
end

return {
    Exports = Exports
}
)"));
    lua.get_export_manager().register_all_exports();
}

} // namespace testing
} // namespace elona
