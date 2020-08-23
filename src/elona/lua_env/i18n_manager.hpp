#pragma once

#include "../eobject/forward.hpp"
#include "../optional.hpp"
#include "lua_submodule.hpp"



namespace elona
{

struct Item;
struct Character;



namespace lua
{

struct ModEnv;



class I18NManager : public LuaSubmodule
{
public:
    explicit I18NManager(LuaEnv&);

    void register_function(
        const std::string& language,
        const std::string& name,
        sol::protected_function function);

    void load(ModEnv& mod);
    void load_string(const std::string& src, ModEnv& mod);

    template <typename... Args>
    sol::optional<std::string> get_optional(
        const std::string& key,
        Args&&... args)
    {
        using swallow = std::initializer_list<int>;
        auto lua_args = lua_state()->create_table();
        (void)swallow{(add_arg(lua_args, std::forward<Args>(args)), 0)...};
        return env()["get_optional"](key, lua_args);
    }

    template <typename... Args>
    sol::optional<std::string> get_data_text_optional(
        const std::string& key,
        Args&&... args)
    {
        using swallow = std::initializer_list<int>;
        auto lua_args = lua_state()->create_table();
        (void)swallow{(add_arg(lua_args, std::forward<Args>(args)), 0)...};
        return env()["get_data_text_optional"](key, lua_args);
    }

    std::vector<std::string> get_list(const std::string& key)
    {
        sol::optional<std::vector<std::string>> ret = env()["get_list"](key);
        if (ret)
        {
            return *ret;
        }
        else
        {
            return {};
        }
    }


    // for testing
    template <typename... Args>
    std::string format(const std::string& fmt, Args&&... args)
    {
        using swallow = std::initializer_list<int>;
        auto lua_args = lua_state()->create_table();
        (void)swallow{(add_arg(lua_args, std::forward<Args>(args)), 0)...};
        return env()["format"](fmt, lua_args);
    }


private:
    template <
        typename T,
        std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> =
            nullptr>
    void add_arg(sol::table args, T value)
    {
        args.add(value);
    }

    void add_arg(sol::table args, const char* value)
    {
        args.add(value);
    }

    void add_arg(sol::table args, const std::string& value)
    {
        args.add(value);
    }

    void add_arg(sol::table args, sol::object value)
    {
        args.add(value);
    }


    void add_arg(sol::table args, const ItemRef& value);
    void add_arg(sol::table args, const Character& value);
};

} // namespace lua
} // namespace elona
