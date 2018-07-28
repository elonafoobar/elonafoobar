#pragma once
#include <unordered_map>
#include <sstream>
#include <vector>
#include "filesystem.hpp"
#include "hcl.hpp"
#include "shared_id.hpp"
#include "lib/noncopyable.hpp"
#include "log.hpp"
#include "optional.hpp"
#include "thirdparty/ordered_map/ordered_map.h"
#include "thirdparty/sol2/sol.hpp"

namespace elona
{

namespace lua
{
class lua_env;
extern std::unique_ptr<lua_env> lua;
}

namespace lion
{

template <typename>
struct lion_db_traits;


template <class T>
class lion_db : public lib::noncopyable
{
public:
    using traits_type = lion_db_traits<T>;
    using id_type = shared_id;
    using legacy_id_type = typename traits_type::legacy_id_type;
    using data_type = typename traits_type::data_type;
    using map_type = std::unordered_map<id_type, data_type>;
    using legacy_map_type = std::unordered_map<legacy_id_type, id_type>;

    lion_db() : scope("core") {}

    struct iterator
    {
    private:
        using base_iterator_type = typename map_type::const_iterator;

    public:
        using value_type = const data_type;
        using difference_type = typename base_iterator_type::difference_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category =
            typename base_iterator_type::iterator_category;


        iterator(const typename map_type::const_iterator& itr)
            : itr(itr)
        {
        }

        reference operator*() const
        {
            return itr->second;
        }

        pointer operator->() const
        {
            return itr.operator->();
        }

        void operator++()
        {
            ++itr;
        }

        bool operator!=(const iterator& other) const
        {
            return itr != other.itr;
        }

    private:
        typename map_type::const_iterator itr;
    };



    iterator begin() const
    {
        return iterator{std::begin(storage)};
    }

    iterator end() const
    {
        return iterator{std::end(storage)};
    }

    void clear()
    {
        storage.clear();
    }

    void initialize(sol::table table)
    {
        initialize(table, *lua::lua.get());
    }

    void initialize(sol::table table, lua::lua_env& lua)
    {
        std::string prefix = "core." + std::string(traits_type::datatype_name);
        for (const auto& pair : table) {
            std::string id = pair.first.as<std::string>();
            sol::table data = pair.second.as<sol::table>();

            data_type converted = static_cast<T&>(*this).convert(id, data, lua);
            id_type the_id(prefix + "." + id);

            by_legacy_id.emplace(converted.id, the_id);
            storage.emplace(the_id, converted);
        }
    }


    optional_ref<data_type> operator[](const id_type& id) const
    {
        const auto itr = storage.find(id);
        if (itr == std::end(storage))
            return none;
        else
            return itr->second;
    }


    optional_ref<data_type> operator[](const std::string& inner_id) const
    {
        return (*this)[shared_id(inner_id)];
    }


    optional_ref<data_type> operator[](const legacy_id_type& legacy_id) const
    {
        const auto itr = by_legacy_id.find(legacy_id);
        if (itr == std::end(by_legacy_id))
            return none;
        else
            return (*this)[itr->second];
    }


protected:
    std::string scope;
    map_type storage;
    legacy_map_type by_legacy_id;
};


template <typename T>
static optional<std::vector<T>> convert_vector(const sol::table& data,
                                               const std::string& name)
{
    sol::optional<sol::table> value = data[name];

    if (value)
    {
        std::vector<T> result;
        for (const auto& kvp : *value)
        {
            T v = kvp.second.as<T>();
            result.push_back(v);
        }
        return result;
    }
    else
    {
        return none;
    }
}


#define ELONA_LION_DB_FIELD(name, type, default_value)  \
    type name;                                          \
    {                                                   \
        sol::optional<type> value = data[#name];        \
        if (value)                                      \
        {                                               \
            name = *value;                              \
        }                                               \
        else                                            \
        {                                               \
            name = default_value;                       \
        }                                               \
    }                                                   \

#define ELONA_LION_DB_FIELD_REQUIRED(name, type)                        \
    type name;                                                          \
    {                                                                   \
        sol::optional<type> value = data[#name];                        \
        if (value)                                                      \
        {                                                               \
            name = *value;                                              \
        }                                                               \
        else                                                            \
        {                                                               \
            throw std::runtime_error(id_ + ": No such field " + #name); \
        }                                                               \
    }                                                                   \

#define ELONA_LION_DB_FIELD_ENUM(name, enum_type, default_value)        \
    int name;                                                           \
    {                                                                   \
        std::string variant;                                            \
        sol::optional<std::string> value = data[#name];                 \
        if (value)                                                      \
        {                                                               \
            variant = *value;                                           \
        }                                                               \
        else                                                            \
        {                                                               \
            variant = default_value;                                    \
        }                                                               \
        name = lua.get_api_manager().get_enum_value(enum_type, variant); \
    }                                                                   \

#define ELONA_LION_DB_FIELD_CALLBACK(name)                              \
    optional<std::string> name = none;                                  \
    {                                                                   \
        sol::optional<std::string> function_name = data[#name];         \
        if (function_name)                                              \
        {                                                               \
            name = *function_name;                                      \
            if (!lua.get_export_manager().has_function(*function_name)) \
            {                                                           \
                throw std::runtime_error("Error loading " + id_ + "." + #name + ": No such callback named " + *function_name); \
            }                                                           \
        }                                                               \
    }                                                                   \


} // namespace lion
} // namespace elona
