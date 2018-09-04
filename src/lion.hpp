#pragma once
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "filesystem.hpp"
#include "hcl.hpp"
#include "lib/noncopyable.hpp"
#include "log.hpp"
#include "optional.hpp"
#include "shared_id.hpp"
#include "thirdparty/ordered_map/ordered_map.h"
#include "thirdparty/sol2/sol.hpp"

using namespace std::literals::string_literals;

namespace elona
{

namespace lua
{
class LuaEnv;
extern std::unique_ptr<LuaEnv> lua;
} // namespace lua

namespace lion
{

template <typename>
struct LionDBTraits;


template <class T>
class LionDB : public lib::noncopyable
{
public:
    using TraitsType = LionDBTraits<T>;
    using IdType = SharedId;
    using LegacyIdType = typename TraitsType::LegacyIdType;
    using DataType = typename TraitsType::DataType;
    using MapType = std::unordered_map<IdType, DataType>;
    using LegacyMapType = std::unordered_map<LegacyIdType, IdType>;

    LionDB()
        : scope("core")
    {
    }

    struct iterator
    {
    private:
        using base_iterator_type = typename MapType::const_iterator;

    public:
        using value_type = const DataType;
        using difference_type = typename base_iterator_type::difference_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category =
            typename base_iterator_type::iterator_category;


        iterator(const typename MapType::const_iterator& itr)
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
        typename MapType::const_iterator itr;
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
        by_legacy_id.clear();
    }

    void initialize(sol::table table)
    {
        initialize(table, *lua::lua.get());
    }

    void initialize(sol::table root_table, lua::LuaEnv& lua)
    {
        using namespace std::chrono;
        steady_clock::time_point begin = steady_clock::now();

        // Read tables of this format:
        // root_table[mod_name][data_id]
        for (const auto& root_pair : root_table)
        {
            // root_table[core]
            sol::table data_for_mod = root_pair.second.as<sol::table>();

            initialize_for_mod(data_for_mod, lua);
        }

        steady_clock::time_point end = steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
                .count();
        ELONA_LOG(
            "[LION ("s << TraitsType::datatype_name << ")] Elements: "s
                       << storage.size() << ", time: "s << time << "ms"s);
    }

    optional_ref<IdType> get_id_from_legacy(
        const LegacyIdType& legacy_id) const
    {
        const auto itr = by_legacy_id.find(legacy_id);
        if (itr == std::end(by_legacy_id))
            return none;
        else
            return itr->second;
    }

    optional_ref<DataType> operator[](const IdType& id) const
    {
        const auto itr = storage.find(id);
        if (itr == std::end(storage))
            return none;
        else
            return itr->second;
    }


    optional_ref<DataType> operator[](const std::string& inner_id) const
    {
        return (*this)[SharedId(inner_id)];
    }


    optional_ref<DataType> operator[](const LegacyIdType& legacy_id) const
    {
        if (const auto id = get_id_from_legacy(legacy_id))
            return (*this)[**id];
        else
            return none;
    }

private:
    void initialize_for_mod(sol::table data_for_mod, lua::LuaEnv& lua)
    {
        for (const auto& pair : data_for_mod)
        {
            sol::table data = pair.second.as<sol::table>();
            std::string id_string = data["_full_id"];
            IdType id(id_string);

            initialize_single(id, data, lua);
        }
    }

    void
    initialize_single(const IdType& id, sol::table data, lua::LuaEnv& lua)
    {
        DataType converted = static_cast<T&>(*this).convert(id, data, lua);

        auto it = by_legacy_id.find(converted.id);
        if (it != by_legacy_id.end())
        {
            throw std::runtime_error(
                id.get() + ": Legacy id already exists: "s
                + std::to_string(converted.id) + " -> "s + it->second.get());
        }

        by_legacy_id.emplace(converted.id, id);
        storage.emplace(id, converted);
    }

protected:
    std::string scope;
    MapType storage;
    LegacyMapType by_legacy_id;
};

/**
 * Converts a tags list into a filter for use with flt().
 *
 * @param data data table
 * @param id member field inside data table containing a string list
 * (["man", "slime"])
 *
 * @return the filter list ("/man/slime/")
 */
std::string convert_tags(const sol::table& data, const std::string& id);

template <typename T>
static optional<std::vector<T>> convert_vector(
    const sol::table& data,
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


#define ELONA_LION_DEFINE_DB(ClassName, data, legacy_id, name) \
    class ClassName; \
    namespace lion \
    { \
    template <> \
    struct LionDBTraits<ClassName> \
    { \
        using DataType = data; \
        using LegacyIdType = legacy_id; \
        static constexpr const char* datatype_name = name; \
    }; \
    } \
    class ClassName : public lion::LionDB<ClassName> \
    { \
    public: \
        ClassName() = default; \
        data convert(const std::string&, const sol::table&, lua::LuaEnv&); \
    };


#define ELONA_LION_DB_FIELD(name, type, default_value) \
    type name; \
    { \
        sol::optional<type> value_ = data[#name]; \
        if (value_) \
        { \
            name = *value_; \
        } \
        else \
        { \
            name = default_value; \
        } \
    }

#define ELONA_LION_DB_FIELD_REQUIRED(name, type) \
    type name; \
    { \
        sol::optional<type> value_ = data[#name]; \
        if (value_) \
        { \
            name = *value_; \
        } \
        else \
        { \
            throw std::runtime_error(id_ + ": No such field " + #name); \
        } \
    }

#define ELONA_LION_DB_FIELD_ENUM(name, type, EnumMap, default_value) \
    type name; \
    { \
        sol::optional<std::string> value_ = data[#name]; \
        if (value_) \
        { \
            name = lua::LuaEnums::EnumMap.get_from_string( \
                *value_, default_value); \
        } \
        else \
        { \
            name = default_value; \
        } \
    }

#define ELONA_LION_DB_FIELD_CALLBACK(name) \
    optional<std::string> name = none; \
    { \
        sol::optional<std::string> function_name_ = data[#name]; \
        if (function_name_) \
        { \
            name = *function_name_; \
            if (!lua.get_export_manager().has_function(*function_name_)) \
            { \
                throw std::runtime_error( \
                    "Error loading " + id_ + "." + #name \
                    + ": No such callback named " + *function_name_); \
            } \
        } \
    }


} // namespace lion
} // namespace elona
