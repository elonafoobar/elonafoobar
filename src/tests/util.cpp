#include "../thirdparty/catch2/catch.hpp"

#include "../enums.hpp"
#include "../i18n.hpp"
#include "../init.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../variables.hpp"
#include "tests.hpp"

namespace elona
{
namespace testing
{

void set_english()
{
    elona::jp = 0;
    elona::en = 1;
    initialize_i18n();
    set_item_info();
}

void set_japanese()
{
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
    REQUIRE(itemcreate(-1, id, 0, 0, number) == 1);
    int index = elona::ci;
    normalize_item(elona::inv[index]);
    std::string name = itemname(index, number, prefix ? 0 : 1);
    item_delete(index);
    return name;
}

Item& create_item(int id, int number)
{
    REQUIRE(itemcreate(-1, id, 0, 0, number) == 1);
    normalize_item(elona::inv[elona::ci]);
    return elona::inv[elona::ci];
}

Character& create_chara(int id, int x, int y)
{
    elona::fixlv = Quality::none;
    REQUIRE(chara_create(-1, id, x, y));
    return elona::cdata[elona::rc];
}

void register_lua_function(
    lua::LuaEnv& lua,
    std::string mod_name,
    std::string callback_signature,
    std::string callback_body,
    std::string setup)
{
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(mod_name, R"(
local Exports = {}

function Exports.)" + callback_signature + "\n" + callback_body + R"(
end

)" + setup + R"(
return {
    Exports = Exports
}
)"));
    lua.get_export_manager().register_all_exports();
}

} // namespace testing
} // namespace elona
