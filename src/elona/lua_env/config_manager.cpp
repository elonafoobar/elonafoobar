#include "config_manager.hpp"

#include "../filesystem.hpp"



namespace elona
{
namespace lua
{

ConfigManager::ConfigManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    _impl = env()["kernel"]["Config"];
}



void ConfigManager::load_schema(
    std::istream& in,
    const std::string& filename,
    const std::string& mod_id)
{
    std::string s{
        std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
    _impl["load_schema"](s, filename, mod_id);
}



void ConfigManager::load_options(std::istream& in, const std::string& filename)
{
    std::string s{
        std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
    _impl["load_options"](s, filename);
}



void ConfigManager::save(const fs::path& config_path)
{
    std::ofstream out{config_path.native()};
    if (!out)
    {
        throw std::runtime_error{
            u8"Failed to open: " + config_path.to_u8string()};
    }

    const std::string serialized_config = _impl["serialize"]();
    out << serialized_config;
}



void ConfigManager::clear()
{
    _impl["clear"]();
}



void ConfigManager::inject_enum(
    const std::string& key,
    const std::vector<std::string>& enum_,
    const std::string& default_value)
{
    sol::table enum_tbl = env().create();
    for (const auto& e : enum_)
    {
        enum_tbl[enum_tbl.size() + 1] = e;
    }
    _impl["inject_enum"](key, enum_tbl, default_value);
}



bool ConfigManager::is_section(const std::string& key)
{
    return _impl["is_section"](key);
}



bool ConfigManager::is_boolean_option(const std::string& key)
{
    return _impl["is_boolean_option"](key);
}



bool ConfigManager::is_integer_option(const std::string& key)
{
    return _impl["is_integer_option"](key);
}



bool ConfigManager::is_string_option(const std::string& key)
{
    return _impl["is_string_option"](key);
}



bool ConfigManager::is_enum_option(const std::string& key)
{
    return _impl["is_enum_option"](key);
}



int ConfigManager::get_min(const std::string& key)
{
    return _impl["get_min"](key);
}



int ConfigManager::get_max(const std::string& key)
{
    return _impl["get_max"](key);
}



int ConfigManager::get_step(const std::string& key)
{
    return _impl["get_step"](key);
}



sol::table ConfigManager::get_enum(const std::string& key)
{
    return _impl["get_enum"](key);
}



sol::table ConfigManager::get_children_keys(const std::string& key)
{
    return _impl["get_children_keys"](key);
}



bool ConfigManager::is_hidden(const std::string& key)
{
    return _impl["is_hidden"](key);
}

} // namespace lua
} // namespace elona
