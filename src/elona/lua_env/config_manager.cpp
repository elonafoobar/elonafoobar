#include "config_manager.hpp"

#include "../filesystem.hpp"



namespace elona
{
namespace lua
{

namespace LuaApiJSON5
{
std::pair<sol::object, sol::optional<std::string>> parse(
    const std::string& source,
    sol::this_state state);
std::string stringify(sol::object value, sol::table opts);
} // namespace LuaApiJSON5



ConfigManager::ConfigManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    env().set_function("json5_parse", LuaApiJSON5::parse);
    env().set_function("json5_stringify", LuaApiJSON5::stringify);

    const auto impl_filepath =
        filesystem::dirs::data() / "script" / "kernel" / "config.lua";
    _impl = safe_script_file(impl_filepath);
}



void ConfigManager::load_schema(
    std::istream& in,
    const std::string& filename,
    SharedId mod_id)
{
    std::string s{
        std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
    _impl["load_schema"](s, filename, mod_id.get());
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
            u8"Failed to open: " +
            filepathutil::make_preferred_path_in_utf8(config_path)};
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
