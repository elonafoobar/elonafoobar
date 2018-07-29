#include "serial_manager.hpp"
#include "lua_env.hpp"
#include "../filesystem.hpp"
#include "../putit.hpp"

namespace elona
{
namespace lua
{

namespace
{

static std::string get_table_name(mod_save_t type)
{
    std::string table_name;
    if (type == mod_save_t::global)
        table_name = "global";
    else if (type == mod_save_t::map_local)
        table_name = "map_local";

    return table_name;
}

} // namespace

serial_manager::serial_manager(lua_env* lua)
{
    lua_ = lua;
    serial_env = sol::environment(*(lua_->get_state()), sol::create);

    // Allow the resolution of handles when loading.
    // serial_env["Handle"] = lua_->get_handle_manager().get_handle_env();

    // Load the Lua chunk for saving/loading data.
    lua_->get_state()->safe_script(
        R"(Serial = require "serial")", serial_env);
}

void serial_manager::save_mod_store_data(const fs::path& output_path, mod_save_t type)
{
    std::ofstream out{output_path.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Error: fail to write "
            + filesystem::make_preferred_path_in_utf8(output_path));
    }
    putit::binary_oarchive ar{out};

    auto& mod_mgr = lua_->get_mod_manager();
    unsigned mod_count = static_cast<unsigned>(mod_mgr.mods.size());
    ar.save(mod_count);

    for (auto& pair : mod_mgr.mods)
    {
        // putit will save the size of each string, so no need to
        // serialize them here.
        std::string name = pair.first;
        ar.save(name);

        std::string table_name = get_table_name(type);
        sol::table data = pair.second->env["Store"][table_name].get<sol::table>();
        save(data, ar);
    }
}

void serial_manager::load_mod_store_data(const fs::path& input_path, mod_save_t type)
{
    std::ifstream in{input_path.native(), std::ios::binary};
    if (in.fail())
    {
        throw std::runtime_error(
            u8"Error: fail to read "s
            + filesystem::make_preferred_path_in_utf8(input_path));
    }
    putit::binary_iarchive ar{in};

    auto& mod_mgr = lua_->get_mod_manager();
    unsigned mod_count;
    ar.load(mod_count);

    for (unsigned i = 0; i < mod_count; i++)
    {
        std::string mod_name;
        ar.load(mod_name);

        auto val = mod_mgr.mods.find(mod_name);
        if (val == mod_mgr.mods.end())
        {
            // Skip this piece of data.
            std::string raw_data;
            ar.load(raw_data);

            continue;
        }
        mod_info* mod = val->second.get();

        std::string table_name = get_table_name(type);
        sol::table data = mod->env["Store"][table_name].get<sol::table>();
        load(data, ar);
    }
}

void serial_manager::save(sol::table& data, putit::binary_oarchive& ar)
{
    serial_env["_TO_SERIALIZE"] = data;
    auto result = lua_->get_state()->safe_script(R"(return Serial.save(_TO_SERIALIZE))", serial_env);
    serial_env["_TO_SERIALIZE"] = sol::lua_nil;

    if (result.valid())
    {
        std::string dump = result.get<std::string>();
        ar.save(dump);
    }
    else
    {
        sol::error err = result;
        throw err;
    }
}

void serial_manager::load(sol::table& data, putit::binary_iarchive& ar)
{
    std::string raw_data;
    ar.load(raw_data);

    serial_env["_TO_DESERIALIZE"] = raw_data;
    auto result = lua_->get_state()->safe_script(R"(return Serial.load(_TO_DESERIALIZE))", serial_env);
    serial_env["_TO_DESERIALIZE"] = sol::lua_nil;

    if (result.valid())
    {
        data = result.get<sol::table>();
    }
    else
    {
        sol::error err = result;
        throw err;
    }
}

} // namespace lua
} // namespace elona
