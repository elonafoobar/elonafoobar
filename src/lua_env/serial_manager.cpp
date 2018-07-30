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

static std::pair<int, int> get_start_end_indices(const std::string& kind,
                                                 mod_save_t save_type)
{
    if (kind == character::lua_type())
    {
        switch (save_type)
        {
        case mod_save_t::global:
            return {0, ELONA_MAX_PARTY_CHARACTERS - 1};
        case mod_save_t::map_local:
            return {ELONA_MAX_PARTY_CHARACTERS, ELONA_MAX_CHARACTERS};
        }
    }
    else if (kind == item::lua_type())
    {
        switch (save_type)
        {
        case mod_save_t::global:
            return {0, ELONA_ITEM_ON_GROUND_INDEX - 1};
        case mod_save_t::map_local:
            return {ELONA_ITEM_ON_GROUND_INDEX, ELONA_MAX_ITEMS};
        }
    }

    assert(false);
    return {0, 0};
}

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
    serial_env = sol::environment(*(lua_->get_state()),
                                  sol::create,
                                  lua_->get_state()->globals());

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
        std::string mod_name = pair.first;
        ar.save(mod_name);

        std::cout << "SAVE DATA: " << mod_name << std::endl;

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

        std::cout << "LOAD DATA: " << mod_name << std::endl;

        auto val = mod_mgr.mods.find(mod_name);
        if (val == mod_mgr.mods.end())
        {
            // Skip this piece of data.
            std::cerr << "WARNING: skipping mod store loading as mod wasn't loaded: " << mod_name << std::endl;
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
        std::cout << dump.size() << std::endl;
        std::cout << "SAVED" << std::endl;
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
    std::cout << raw_data.size() << std::endl;
    std::cout << "LOADING" << std::endl;


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

void serial_manager::save_handles_inner(const fs::path& output_path,
                                        mod_save_t save_type,
                                        const std::string& kind)
{
    std::ofstream out{output_path.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Error: fail to write "
            + filesystem::make_preferred_path_in_utf8(output_path));
    }
    putit::binary_oarchive ar{out};

    int index_start, index_end;
    std::tie (index_start, index_end) = get_start_end_indices(kind, save_type);

    std::cout << "HANDLE SAVE " << static_cast<int>(save_type) << " " << output_path.string() << std::endl;

    auto handles = lua_->get_handle_manager().get_handle_range(kind, index_start, index_end);
    save(handles, ar);
    handles = sol::lua_nil;
}

void serial_manager::load_handles_inner(const fs::path& input_path,
                                              mod_save_t save_type,
                                              const std::string& kind)
{
    std::ifstream in{input_path.native(), std::ios::binary};
    if (in.fail())
    {
        throw std::runtime_error(
            u8"Error: fail to read "s
            + filesystem::make_preferred_path_in_utf8(input_path));
    }
    putit::binary_iarchive ar{in};

    int index_start, index_end;
    std::tie (index_start, index_end) = get_start_end_indices(kind, save_type);

    std::cout << "HANDLE LOAD " << static_cast<int>(save_type) << input_path.string() << std::endl;

    sol::table handles = lua_->get_state()->create_table();
    load(handles, ar);
    lua_->get_handle_manager().clear_handle_range(kind, index_start, index_end);
    lua_->get_handle_manager().merge_handles(kind, handles);
    handles = sol::lua_nil;
}

} // namespace lua
} // namespace elona
