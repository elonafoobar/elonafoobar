#pragma once

#include <type_traits>
#include <unordered_map>
#include <vector>

#include "../../thirdparty/ordered_map/ordered_map.h"
#include "../../thirdparty/sol2/sol.hpp"
#include "../../util/map_key_iterator.hpp"
#include "../../util/map_value_iterator.hpp"
#include "../../util/noncopyable.hpp"
#include "../filesystem.hpp"
#include "../i18n.hpp"
#include "../log.hpp"
#include "../lua_env/config_table.hpp"
#include "../lua_env/data_table.hpp"
#include "../optional.hpp"
#include "common.hpp"



namespace elona
{
namespace data
{

namespace detail
{

template <typename T, typename = void>
struct has_legacy_id : public std::false_type
{
};


template <typename T>
struct has_legacy_id<T, decltype((void)T::legacy_id)> : public std::true_type
{
};


// If T::legacy_id exists, it becomes true; otherwise false.
template <typename T>
constexpr bool has_legacy_id_v = has_legacy_id<T>::value;

} // namespace detail



template <typename>
struct DatabaseTraits;



template <typename T>
class BaseDatabase : public lib::noncopyable
{
public:
    using Traits = DatabaseTraits<T>;
    using DataType = typename Traits::DataType;
    using IdType = decltype(DataType::id);
    using MapType = std::unordered_map<IdType, DataType>;
    using ErrorMapType = std::unordered_map<IdType, std::string>;
    using KeysIterator = lib::map_key_iterator<MapType, IdType>;
    using ValuesIterator = lib::map_value_iterator<MapType, DataType>;



    BaseDatabase() = default;



    void initialize(lua::DataTable data)
    {
        _data = data;
        load_all();
    }



    typename MapType::const_iterator begin() const
    {
        return std::begin(_storage);
    }



    typename MapType::const_iterator end() const
    {
        return std::end(_storage);
    }



    KeysIterator keys() const
    {
        return KeysIterator(_storage);
    }



    ValuesIterator values() const
    {
        return ValuesIterator(_storage);
    }



    optional<std::string> error(const IdType& id)
    {
        auto it = _errors.find(id);
        if (it == _errors.end())
            return none;

        return it->second;
    }



    optional_ref<DataType> operator[](const IdType& id)
    {
        const auto itr = _storage.find(id);
        if (itr != std::end(_storage))
            return itr->second;

        return retrieve_from_lua(id);
    }



    const DataType& ensure(const IdType& id)
    {
        auto data = (*this)[id];

        if (!data)
        {
            throw sol::error{"No data entry with ID \"" + id.get() +
                             "\" of type \"" + Traits::type_id + "\" exists."};
        }

        return *data;
    }



    template <typename... Args>
    std::string
    get_text(const IdType& id, const I18NKey& property_name, Args&&... args)
    {
        return i18n::s.get_data_text(
            PrototypeId{Traits::type_id},
            id,
            property_name,
            std::forward<Args>(args)...);
    }



    template <typename... Args>
    optional<std::string> get_text_optional(
        const IdType& id,
        const I18NKey& property_name,
        Args&&... args)
    {
        return i18n::s.get_data_text_optional(
            PrototypeId{Traits::type_id},
            id,
            property_name,
            std::forward<Args>(args)...);
    }



protected:
    lua::DataTable _data;
    MapType _storage;
    ErrorMapType _errors;



private:
    optional_ref<DataType> retrieve_from_lua(const IdType& id)
    {
        if (_errors.find(id) != _errors.end())
        {
            return none;
        }

        // Look in root "data" table for definition.
        auto instance = _data.raw(PrototypeId{Traits::type_id}, id);
        if (!instance)
        {
            return none;
        }

        // Allocate equivalent native structure from Lua data.
        try
        {
            auto config = lua::ConfigTable(*instance, id.get());
            DataType converted =
                static_cast<T&>(*this).convert(config, id.get());

            _storage.emplace(id, converted);
        }
        catch (const std::exception& e)
        {
            using namespace std::literals::string_literals;

            std::string message = "Error initializing "s + Traits::type_id +
                data_id_separator + id.get() + ": " + e.what();
            ELONA_WARN("lua.data") << message;
            std::cerr << message << std::endl;

            _errors.emplace(id, e.what());
            return none;
        }

        return _storage[id];
    }



    void load_all()
    {
        auto it = _data.get_table(data::PrototypeId{Traits::type_id});
        if (!it)
            return;

        for (const auto& pair : *it)
        {
            IdType id(pair.first.template as<std::string>());
            if ((*this)[id])
                continue;

            retrieve_from_lua(id);
        }
    }
};



template <typename T>
class BaseDatabaseWithLegacyIdTable : public BaseDatabase<T>
{
private:
    using Self = BaseDatabaseWithLegacyIdTable;
    using Super = BaseDatabase<T>;


public:
    using Traits = typename Super::Traits;
    using DataType = typename Super::DataType;
    using IdType = typename Super::IdType;
    using MapType = typename Super::MapType;
    using ErrorMapType = typename Super::ErrorMapType;
    using KeysIterator = typename Super::KeysIterator;
    using ValuesIterator = typename Super::ValuesIterator;

    using LegacyMapType = std::unordered_map<int, IdType>;



    optional<IdType> get_id_from_legacy(int legacy_id)
    {
        static_assert(Traits::has_legacy_id, "DB does not support legacy ID.");

        const auto itr = _by_legacy_id.find(legacy_id);
        if (itr != std::end(_by_legacy_id))
            return itr->second;

        return retrieve_legacy_id_from_lua(legacy_id);
    }



    using Super::operator[]; // Don't hide overload super class has.

    optional_ref<DataType> operator[](int legacy_id)
    {
        if (const auto id = get_id_from_legacy(legacy_id))
        {
            return (*this)[*id];
        }
        else
        {
            return none;
        }
    }



    using Super::ensure; // Don't hide overload super class has.

    const DataType& ensure(int legacy_id)
    {
        const auto id = get_id_from_legacy(legacy_id);

        if (!id)
        {
            throw sol::error{"No data entry with legacy ID \"" +
                             std::to_string(legacy_id) + "\" of type \"" +
                             Traits::type_id + "\" exists."};
        }

        return this->ensure(*id);
    }



    using Super::get_text; // Don't hide overload super class has.

    template <typename... Args>
    std::string
    get_text(int legacy_id, const I18NKey& property_name, Args&&... args)
    {
        const auto id = *get_id_from_legacy(legacy_id);
        return i18n::s.get_data_text(
            PrototypeId{Traits::type_id},
            id,
            property_name,
            std::forward<Args>(args)...);
    }



    using Super::get_text_optional; // Don't hide overload super class has.

    template <typename... Args>
    optional<std::string> get_text_optional(
        int legacy_id,
        const I18NKey& property_name,
        Args&&... args)
    {
        const auto id = *get_id_from_legacy(legacy_id);
        return i18n::s.get_data_text_optional(
            PrototypeId{Traits::type_id},
            id,
            property_name,
            std::forward<Args>(args)...);
    }



protected:
    LegacyMapType _by_legacy_id;



private:
    optional<IdType> retrieve_legacy_id_from_lua(int legacy_id)
    {
        if (const auto new_id =
                Super::_data.by_legacy(PrototypeId{Traits::type_id}, legacy_id))
        {
            _by_legacy_id.emplace(legacy_id, *new_id);
            return *new_id;
        }
        else
        {
            return none;
        }
    }
};


} // namespace data
} // namespace elona



#define ELONA_DEFINE_LUA_DB(ClassName, DataTypeName, name) \
    class ClassName; \
    namespace data \
    { \
    template <> \
    struct DatabaseTraits<ClassName> \
    { \
        using DataType = DataTypeName; \
        static const constexpr bool has_legacy_id = \
            detail::has_legacy_id_v<DataTypeName>; \
        static const constexpr char* type_id = name; \
    }; \
    } \
    class ClassName \
        : public std::conditional_t< \
              data::DatabaseTraits<ClassName>::has_legacy_id, \
              data::BaseDatabaseWithLegacyIdTable<ClassName>, \
              data::BaseDatabase<ClassName>> \
    { \
    public: \
        ClassName() = default; \
        DataTypeName convert(const lua::ConfigTable&, const std::string&); \
    };

#define DATA_LEGACY_ID() \
    const auto legacy_id = data.optional_or<int>("legacy_id", -1);
#define DATA_REQ(name, type) type name = data.required<type>(#name);
#define DATA_REQ_FUNC(name) \
    sol::protected_function name##_ = \
        data.required<sol::protected_function>(#name); \
    lua::WrappedFunction name(id, name##_);
#define DATA_OPT_OR(name, type, def) \
    type name = data.optional_or<type>(#name, def);
#define DATA_OPT(name, type) optional<type> name = data.optional<type>(#name);
#define DATA_OPT_FUNC(name) \
    optional<sol::protected_function> name##_ = \
        data.optional<sol::protected_function>(#name); \
    optional<lua::WrappedFunction> name = none; \
    if (name##_) \
    { \
        name = lua::WrappedFunction(id, *name##_); \
    }
#define DATA_VEC(name, type) std::vector<type> name = data.vector<type>(#name);
#define DATA_TABLE(name, keytype, valuetype) \
    std::unordered_map<keytype, valuetype> name = \
        data.unordered_map<keytype, valuetype>(#name);
#define DATA_ENUM(name, type, table, def) \
    type name = data.enum_or<type>(#name, lua::LuaEnums::table, def);
