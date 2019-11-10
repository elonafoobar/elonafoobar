#pragma once

#include "../shared_id.hpp"
#include "lua_submodule.hpp"



namespace elona
{
namespace lua
{

/**
 * Stores all the configuration.
 */
class ConfigManager : public LuaSubmodule
{
public:
    explicit ConfigManager(LuaEnv&);



    /// Load configuration schema from @a in.
    void
    load_schema(std::istream& in, const std::string& filename, SharedId mod_id);

    /// Load configuration from @a in.
    void load_options(std::istream& in, const std::string& filename);

    /// Save the current configuration to @a config_path.
    void save(const fs::path& config_path);

    /// Clear all configuration.
    void clear();



    template <typename T>
    void set(const std::string& key, const T& value)
    {
        _impl["set"](key, value);
    }


    template <typename T>
    T get(const std::string& key)
    {
        auto value = get<sol::object>(key);
        return value.as<T>(); // TODO exception handling
    }



    template <typename T>
    void bind_setter(const std::string& key, void (*setter)(const T&))
    {
        _impl["bind_setter"](key, setter);
    }



    void inject_enum(
        const std::string& key,
        const std::vector<std::string>& enum_,
        const std::string& default_value);



    /* For building config menu. See config_menu.cpp. */

    bool is_section(const std::string& key);
    bool is_boolean_option(const std::string& key);
    bool is_integer_option(const std::string& key);
    bool is_string_option(const std::string& key);
    bool is_enum_option(const std::string& key);

    int get_min(const std::string& key);
    int get_max(const std::string& key);
    int get_step(const std::string& key);
    sol::table get_enum(const std::string& key);
    sol::table get_children_keys(const std::string& key);

    bool is_hidden(const std::string& key);



private:
    sol::table _impl;
};



template <>
inline sol::object ConfigManager::get(const std::string& key)
{
    return _impl["get"](key);
}

} // namespace lua
} // namespace elona
