#include "../../../types/skill.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::SkillTable)



/**
 * @luadoc
 *
 * A table from skill ID to skill data.
 */
namespace elona::lua::api::classes::class_LuaSkillTable
{

void bind(sol::state& lua)
{
    auto LuaSkillTable =
        lua.new_usertype<SkillTable>("LuaSkillTable", sol::no_constructor);

    LuaSkillTable.set_function(
        "level", [](const SkillTable& self, data::InstanceId id) {
            return self.level(id);
        });

    LuaSkillTable.set_function(
        "set_level",
        [](const SkillTable& self, data::InstanceId id, lua_int new_value) {
            return self.set_level(id, new_value);
        });

    LuaSkillTable.set_function(
        "add_level",
        [](const SkillTable& self, data::InstanceId id, lua_int delta) {
            return self.add_level(id, delta);
        });

    LuaSkillTable.set_function(
        "base_level", [](const SkillTable& self, data::InstanceId id) {
            return self.base_level(id);
        });

    LuaSkillTable.set_function(
        "set_base_level",
        [](const SkillTable& self, data::InstanceId id, lua_int new_value) {
            return self.set_base_level(id, new_value);
        });

    LuaSkillTable.set_function(
        "add_base_level",
        [](const SkillTable& self, data::InstanceId id, lua_int delta) {
            return self.add_base_level(id, delta);
        });

    LuaSkillTable.set_function(
        "experience", [](const SkillTable& self, data::InstanceId id) {
            return self.experience(id);
        });

    LuaSkillTable.set_function(
        "set_experience",
        [](const SkillTable& self, data::InstanceId id, lua_int new_value) {
            return self.set_experience(id, new_value);
        });

    LuaSkillTable.set_function(
        "add_experience",
        [](const SkillTable& self, data::InstanceId id, lua_int delta) {
            return self.add_experience(id, delta);
        });

    LuaSkillTable.set_function(
        "potential", [](const SkillTable& self, data::InstanceId id) {
            return self.potential(id);
        });

    LuaSkillTable.set_function(
        "set_potential",
        [](const SkillTable& self, data::InstanceId id, lua_int new_value) {
            return self.set_potential(id, new_value);
        });

    LuaSkillTable.set_function(
        "add_potential",
        [](const SkillTable& self, data::InstanceId id, lua_int delta) {
            return self.add_potential(id, delta);
        });

    LuaSkillTable.set_function("clear_all_boosts", [](const SkillTable& self) {
        self.clear_all_boosts();
    });
}

} // namespace elona::lua::api::classes::class_LuaSkillTable
