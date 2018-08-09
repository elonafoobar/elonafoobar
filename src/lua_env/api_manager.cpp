#include "lua_api/lua_api.hpp"
#include "lua_env.hpp"

#include "../ability.hpp"
#include "../dmgheal.hpp"
#include "../status_ailment.hpp"

#include <iterator>

/***
 * See doc/api for the API documentation.
 * Be sure to update it if you change anything here.
 * LDoc is completely broken when it comes to parsing C++.
 */
namespace elona
{
namespace lua
{

/***
 * Methods on usertype classes.
 *
 * The below methods do not take handles as a first argument, because
 * handles can transparently pass their underlying C++ references to
 * them.
 */

namespace LuaCharacter
{
void damage_hp(character&, int);
void damage_hp_source(character&, int, damage_source_t);
void damage_hp_chara(character&, int, lua_character_handle handle);
void apply_ailment(character&, status_ailment_t, int);
bool recruit_as_ally(character&);
void set_flag(character&, int, bool);
void gain_skill(character&, int, int);
void gain_skill_stock(character&, int, int, int);
void gain_skill_exp(character&, int, int);
void modify_trait(character&, int, int);
void modify_resistance(character&, int, int);
} // namespace LuaCharacter

void LuaCharacter::damage_hp(character& self, int amount)
{
    LuaCharacter::damage_hp_source(self, amount, damage_source_t::unseen_hand);
}

void LuaCharacter::damage_hp_source(
    character& self,
    int amount,
    damage_source_t source)
{
    elona::damage_hp(self, amount, static_cast<int>(source));
}

void LuaCharacter::damage_hp_chara(
    character& self,
    int amount,
    lua_character_handle handle)
{
    auto& other = lua::lua->get_handle_manager().get_ref<character>(handle);
    elona::damage_hp(self, amount, other.index);
}

void LuaCharacter::apply_ailment(
    character& self,
    status_ailment_t ailment,
    int power)
{
    assert(power > 0);
    elona::dmgcon(self.index, ailment, power);
}

bool LuaCharacter::recruit_as_ally(character& self)
{
    // can't use Chara methods because they take a handle...
    // TODO: DRY (would need to be far-reaching)
    if (self.state() == character::state_t::empty
        || (self.index != 0 && self.index <= 16) || self.index == 0)
    {
        return false;
    }
    elona::rc = self.index;
    return new_ally_joins() == 1;
}

void LuaCharacter::set_flag(character& self, int flag, bool value)
{
    if (flag < 5 || flag > 991 || (flag > 32 && flag < 960))
    {
        return;
    }
    self._flags[flag] = value ? 1 : 0;
}

void LuaCharacter::gain_skill(character& self, int skill, int initial_level)
{
    LuaCharacter::gain_skill_stock(self, skill, initial_level, 0);
}

void LuaCharacter::gain_skill_stock(
    character& self,
    int skill,
    int initial_level,
    int initial_stock)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::chara_gain_skill(self, skill, initial_level, initial_stock);
}

void LuaCharacter::gain_skill_exp(character& self, int skill, int amount)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::chara_gain_fixed_skill_exp(self, skill, amount);
}



void LuaCharacter::modify_resistance(character& self, int element, int delta)
{
    elona::resistmod(self.index, element, delta);
}



/***
 * Set up usertype tables in Sol so we can call methods with them.
 */
void init_usertypes(lua_env& lua)
{
    lua.get_state()->new_usertype<position_t>(
        "LuaPosition",
        sol::constructors<position_t(), position_t(int, int)>(),
        "x",
        &position_t::x,
        "y",
        &position_t::y);
    lua.get_state()->new_usertype<character>(
        character::lua_type(),
        "lua_type",
        &character::lua_type,
        "damage_hp",
        sol::overload(
            &LuaCharacter::damage_hp,
            &LuaCharacter::damage_hp_source,
            &LuaCharacter::damage_hp_chara),
        "apply_ailment",
        &LuaCharacter::apply_ailment,
        "recruit_as_ally",
        &LuaCharacter::recruit_as_ally,
        "set_flag",
        &LuaCharacter::set_flag,
        "gain_skill",
        sol::overload(
            &LuaCharacter::gain_skill, &LuaCharacter::gain_skill_stock),
        "gain_skill_exp",
        &LuaCharacter::gain_skill_exp,
        "modify_resistance",
        &LuaCharacter::modify_resistance,
        "hp",
        sol::readonly(&character::hp),
        "max_hp",
        sol::readonly(&character::max_hp),
        "mp",
        sol::readonly(&character::mp),
        "max_mp",
        sol::readonly(&character::max_mp),
        "sp",
        sol::readonly(&character::sp),
        "max_sp",
        sol::readonly(&character::max_sp),
        "shop_rank",
        &character::shop_rank,
        "character_role",
        &character::character_role,
        "index",
        sol::readonly(&character::index),
        "id",
        sol::readonly(&character::id),
        "position",
        &character::position,
        "name",
        sol::property([](character& c) { return elona::cdatan(0, c.index); }),
        "experience",
        &character::experience);
    lua.get_state()->new_usertype<item>(
        item::lua_type(),
        "lua_type",
        &item::lua_type,
        "set_number",
        &item::set_number,
        "curse_state",
        &item::curse_state,
        "identify_state",
        &item::identification_state,
        "index",
        sol::readonly(&item::index),
        "position",
        &item::position,
        "number",
        sol::property([](item& i) { return i.number(); }),
        "id",
        &item::id,
        "count",
        &item::count,
        "name",
        sol::property([](item& i) { return elona::itemname(i.index); }),
        "subname",
        &item::subname,
        "param1",
        &item::param1,
        "param2",
        &item::param2);
}


api_manager::api_manager(lua_env* lua)
{
    this->lua = lua;
    this->api_env = sol::environment(
        *(this->lua->get_state()),
        sol::create,
        this->lua->get_state()->globals());

    // Bind the API tables at e.g. Elona["core"]["Chara"]
    sol::table Elona = api_env.create_named("Elona");
    sol::table core = Elona.create_named("core");

    LuaApi::bind(core);

    // register usertypes globally, so the handle manager can get at them.
    init_usertypes(*lua);

    // TODO hack to bind position_t constructor, because otherwise
    // there would be no way of creating a position_t from a mod.
    Elona["core"]["LuaPosition"] = (*lua->get_state())["LuaPosition"];
}

bool api_manager::is_loaded()
{
    bool loaded = api_env["_LOADED"];
    return loaded;
}

sol::optional<sol::table> api_manager::try_find_api(
    const std::string& module_namespace,
    const std::string& module_name) const
{
    sol::optional<sol::table> table = api_env["Elona"][module_namespace];
    if (!table)
    {
        return sol::nullopt;
    }
    sol::optional<sol::table> result = (*table)[module_name];

    return result;
}

void api_manager::add_api(
    const std::string& module_namespace,
    sol::table& module_table)
{
    if (api_env["Elona"][module_namespace] == sol::lua_nil)
    {
        api_env["Elona"][module_namespace] = lua->get_state()->create_table();
    }

    sol::table api_table = api_env["Elona"][module_namespace].get<sol::table>();
    for (const auto& pair : module_table)
    {
        if (!pair.first.is<std::string>())
        {
            throw sol::error(
                "Error loading mod " + module_namespace
                + ": Mod API tables must only have string keys.");
        }
        api_table[pair.first.as<std::string>()] = pair.second;
    }
}

int api_manager::get_enum_value(
    const std::string& enum_name,
    const std::string& variant) const
{
    sol::optional<sol::table> Enums = try_find_api("core", "Enums");
    if (!Enums)
        throw std::runtime_error(
            "Enum table not loaded in API manager (" + enum_name + "." + variant
            + ")");

    sol::optional<sol::table> enum_table = (*Enums)[enum_name];

    if (!enum_table)
        throw std::runtime_error("No such enum \"" + enum_name + "\"");

    sol::optional<int> enum_value = (*enum_table)[variant];

    if (!enum_value)
        throw std::runtime_error(
            "No such enum value \"" + variant + "\" for enum \"" + enum_name
            + "\"");

    return *enum_value;
}

void api_manager::load_lua_support_libraries(lua_env& lua)
{
    // Don't load the support libraries again if they're already
    // loaded, because all the tables will be read-only.
    if (is_loaded())
    {
        return;
    }

    auto result = lua.get_state()->safe_script_file(
        filesystem::make_preferred_path_in_utf8(
            filesystem::dir::data() / "lua" / "init.lua"),
        api_env);

    if (!result.valid())
    {
        sol::error err = result;
        std::string what = err.what();
        ELONA_LOG(what);
        throw std::runtime_error("Failed initializing Lua support libraries.");
    }
}

void api_manager::lock()
{
    lua->get_state()->safe_script(
        R"(
Elona = Elona.core.ReadOnly.make_read_only(Elona)
)",
        api_env);
}

sol::table api_manager::bind(lua_env& lua)
{
    return lua.get_state()->create_table_with(
        "require",
        sol::overload(
            [&lua](const std::string& parent, const std::string& module) {
                sol::optional<sol::table> result = sol::nullopt;
                result = lua.get_api_manager().try_find_api(parent, module);
                return result;
            },

            // If no mod name is provided, assume it is "core".
            [&lua](const std::string& module) {
                sol::optional<sol::table> result = sol::nullopt;
                result = lua.get_api_manager().try_find_api("core", module);
                return result;
            }));
}

void api_manager::set_on(lua_env& lua)
{
    lua.get_state()->set("Elona", bind(lua));
}

sol::table api_manager::get_master_api_table()
{
    return api_env["Elona"];
}

sol::table api_manager::get_api_table()
{
    return api_env["Elona"]["core"];
}

} // namespace elona
} // namespace elona
