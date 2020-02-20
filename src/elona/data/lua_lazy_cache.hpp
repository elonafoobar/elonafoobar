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
#include "../log.hpp"
#include "../lua_env/config_table.hpp"
#include "../lua_env/data_table.hpp"
#include "../optional.hpp"
#include "../shared_id.hpp"
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
struct LuaLazyCacheTraits;



template <typename T>
class LuaLazyCache : public lib::noncopyable
{
public:
    using Traits = LuaLazyCacheTraits<T>;
    using DataType = typename Traits::DataType;
    using IdType = decltype(DataType::id);
    using MapType = std::unordered_map<IdType, DataType>;
    using ErrorMapType = std::unordered_map<IdType, std::string>;
    using KeysIterator = lib::map_key_iterator<MapType, IdType>;
    using ValuesIterator = lib::map_value_iterator<MapType, DataType>;



    LuaLazyCache() = default;



    void initialize(lua::DataTable data)
    {
        _data = data;
    }



    // NOTE: To iterate all values, they all have to be loaded from Lua first by
    // calling load_all().

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



    void load_all()
    {
        auto it = _data.get_table(Traits::type_id);
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



    optional_ref<DataType> operator[](const std::string& inner_id)
    {
        return (*this)[IdType(inner_id)];
    }



    optional_ref<DataType> operator[](const char* inner_id)
    {
        return (*this)[IdType(std::string(inner_id))];
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



    const DataType& ensure(const std::string& inner_id)
    {
        return this->ensure(IdType(inner_id));
    }



    const DataType& ensure(const char* inner_id)
    {
        return this->ensure(IdType(std::string(inner_id)));
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
        optional<sol::table> instance = _data.raw(Traits::type_id, id);
        if (!instance)
        {
            return none;
        }

        // Allocate equivalent native structure from Lua data.
        try
        {
            auto config = lua::ConfigTable(*instance, id);
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
};



template <typename T>
class LuaLazyCacheWithLegacyIdTable : public LuaLazyCache<T>
{
private:
    using Self = LuaLazyCacheWithLegacyIdTable;
    using Super = LuaLazyCache<T>;


public:
    using Traits = typename Super::Traits;
    using DataType = typename Super::DataType;
    using IdType = typename Super::IdType;
    using MapType = typename Super::MapType;
    using ErrorMapType = typename Super::ErrorMapType;
    using KeysIterator = typename Super::KeysIterator;
    using ValuesIterator = typename Super::ValuesIterator;

    using LegacyIdType = decltype(DataType::legacy_id);
    using LegacyMapType = std::unordered_map<LegacyIdType, IdType>;



    optional<IdType> get_id_from_legacy(const LegacyIdType& legacy_id)
    {
        static_assert(Traits::has_legacy_id, "DB does not support legacy ID.");

        const auto itr = _by_legacy_id.find(legacy_id);
        if (itr != std::end(_by_legacy_id))
            return itr->second;

        return retrieve_legacy_id_from_lua(legacy_id);
    }



    using Super::operator[]; // Don't hide overload super class has.

    optional_ref<DataType> operator[](const LegacyIdType& legacy_id)
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

    const DataType& ensure(const LegacyIdType& legacy_id)
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



protected:
    LegacyMapType _by_legacy_id;



private:
    optional<IdType> retrieve_legacy_id_from_lua(const LegacyIdType& legacy_id)
    {
        optional<std::string> it =
            Super::_data.by_legacy(Traits::type_id, legacy_id);

        if (it)
        {
            IdType id(*it);
            _by_legacy_id.emplace(legacy_id, id);
            return id;
        }

        return none;
    }
};


} // namespace data
} // namespace elona



#define ELONA_DEFINE_LUA_DB(ClassName, DataTypeName, name) \
    class ClassName; \
    namespace data \
    { \
    template <> \
    struct LuaLazyCacheTraits<ClassName> \
    { \
        using DataType = DataTypeName; \
        static const constexpr bool has_legacy_id = \
            detail::has_legacy_id_v<DataTypeName>; \
        static const constexpr char* type_id = name; \
    }; \
    } \
    class ClassName \
        : public std::conditional_t< \
              data::LuaLazyCacheTraits<ClassName>::has_legacy_id, \
              data::LuaLazyCacheWithLegacyIdTable<ClassName>, \
              data::LuaLazyCache<ClassName>> \
    { \
    public: \
        ClassName() = default; \
        DataTypeName convert(const lua::ConfigTable&, const std::string&); \
    };

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
