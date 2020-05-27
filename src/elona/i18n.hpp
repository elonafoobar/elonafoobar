#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../thirdparty/sol2/sol.hpp"
#include "../util/strutil.hpp"
#include "data/id.hpp"
#include "filesystem.hpp"
#include "lua_env/i18n_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "optional.hpp"



using namespace std::literals::string_literals;

namespace elona
{

using I18NKey = std::string;



namespace i18n
{

std::string space_if_needed();



class Store
{
public:
    Store() = default;
    ~Store() = default;



    void init();

    // For testing use.
    void load_from_string(const std::string& src, const std::string& mod_id);



    template <typename... Args>
    [[nodiscard]] std::string get(const I18NKey& key, Args&&... args)
    {
        if (const auto ret = get_optional(key, std::forward<Args>(args)...))
        {
            return *ret;
        }
        else
        {
            return "<Unknown ID: " + key + ">";
        }
    }



    template <typename... Args>
    [[nodiscard]] optional<std::string> get_optional(
        const I18NKey& key,
        Args&&... args)
    {
        if (const auto ret = lua::lua->get_i18n_manager().get_optional(
                key, std::forward<Args>(args)...))
        {
            return *ret;
        }
        else
        {
            return none;
        }
    }



    // Convenience methods for cases like "core.element._<enum index>.name"

    template <typename... Args>
    [[nodiscard]] std::string
    get_enum(const I18NKey& key, int index, Args&&... args)
    {
        return get(
            key + "._" + std::to_string(index), std::forward<Args>(args)...);
    }



    template <typename... Args>
    [[nodiscard]] optional<std::string>
    get_enum_optional(const I18NKey& key, int index, Args&&... args)
    {
        return get_optional(
            key + "._" + std::to_string(index), std::forward<Args>(args)...);
    }



    template <typename... Args>
    [[nodiscard]] std::string get_enum_property(
        const std::string& key_head,
        const std::string& key_tail,
        int index,
        Args&&... args)
    {
        return get(
            key_head + "._" + std::to_string(index) + "." + key_tail,
            std::forward<Args>(args)...);
    }



    template <typename... Args>
    [[nodiscard]] optional<std::string> get_enum_property_optional(
        const std::string& key_head,
        const std::string& key_tail,
        int index,
        Args&&... args)
    {
        return get_optional(
            key_head + "._" + std::to_string(index) + "." + key_tail,
            std::forward<Args>(args)...);
    }



    // Returns string list. If the value associated with `key` is a scalar,
    // returns 1-size list which contains the value. If `key` does not exist,
    // returns empty list.
    template <typename... Args>
    [[nodiscard]] std::vector<std::string> get_list(const I18NKey& key)
    {
        return lua::lua->get_i18n_manager().get_list(key);
    }



    // Get data-associated text.
    template <typename... Args>
    [[nodiscard]] std::string get_data_text(
        data::PrototypeId data_prototype_id,
        data::InstanceId data_instance_id,
        const I18NKey& property_name,
        Args&&... args)
    {
        if (const auto ret = get_data_text_optional(
                data_prototype_id,
                data_instance_id,
                property_name,
                std::forward<Args>(args)...))
        {
            return *ret;
        }
        else
        {
            return "<Unknown ID: " + data_prototype_id.get() + "#" +
                data_instance_id.get() + "." + property_name + ">";
        }
    }



    // Get data-associated text if exists.
    template <typename... Args>
    [[nodiscard]] optional<std::string> get_data_text_optional(
        data::PrototypeId data_prototype_id,
        data::InstanceId data_instance_id,
        const I18NKey& property_name,
        Args&&... args)
    {
        if (const auto ret =
                lua::lua->get_i18n_manager().get_data_text_optional(
                    data_prototype_id.get() + "#" + data_instance_id.get() +
                        "." + property_name,
                    std::forward<Args>(args)...))
        {
            return *ret;
        }
        else
        {
            return none;
        }
    }



    // for testing
    template <typename... Args>
    [[nodiscard]] std::string format(const I18NKey& fmt, Args&&... args)
    {
        return lua::lua->get_i18n_manager().format(
            fmt, std::forward<Args>(args)...);
    }



private:
    void load_from_stream(
        std::istream& in,
        const std::string& filepath,
        const std::string& mod_id);
};



inline i18n::Store s;

} // namespace i18n
} // namespace elona
