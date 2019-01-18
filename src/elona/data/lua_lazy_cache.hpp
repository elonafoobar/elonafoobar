#pragma once
#include <unordered_map>
#include <vector>
#include "../../thirdparty/ordered_map/ordered_map.h"
#include "../../thirdparty/sol2/sol.hpp"
#include "../../util/noncopyable.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"
#include "../lua_env/config_table.hpp"
#include "../lua_env/data_table.hpp"
#include "../optional.hpp"
#include "../shared_id.hpp"

using namespace std::literals::string_literals;

namespace elona
{

namespace data
{

template <typename>
struct LuaLazyCacheTraits;


template <class T>
class LuaLazyCache : public lib::noncopyable
{
public:
    using Traits = LuaLazyCacheTraits<T>;
    using IdType = SharedId;
    using LegacyIdType = int;
    using DataType = typename Traits::DataType;
    using MapType = std::unordered_map<IdType, DataType>;
    using LegacyMapType = std::unordered_map<LegacyIdType, IdType>;
    using ErrorMapType = std::unordered_map<IdType, std::string>;

    LuaLazyCache()
    {
    }

    void initialize(lua::DataTable data)
    {
        _data = data;
    }

    // NOTE: To iterate all values, they all have to be loaded from Lua first by
    // calling load_all().
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
        return iterator{std::begin(_storage)};
    }

    iterator end() const
    {
        return iterator{std::end(_storage)};
    }

    void load_all()
    {
        sol::optional<sol::table> it = _data.storage["raw"][Traits::type_id];
        if (!it)
        {
            return;
        }

        for (const auto& pair : *it)
        {
            SharedId id(pair.first.as<std::string>());
            if ((*this)[id])
                continue;

            retrieve_from_lua(id);
        }
    }

    void clear()
    {
        _storage.clear();
        _by_legacy_id.clear();
    }


    optional<std::string> error(const IdType& id)
    {
        auto it = _errors.find(id);
        if (it == _errors.end())
            return none;

        return it->second;
    }

    optional<SharedId> get_id_from_legacy(const LegacyIdType& legacy_id)
    {
        if (!Traits::need_legacy_id)
        {
            return none;
        }

        const auto itr = _by_legacy_id.find(legacy_id);
        if (itr != std::end(_by_legacy_id))
            return itr->second;

        return retrieve_legacy_id_from_lua(legacy_id);
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

    optional_ref<DataType> operator[](const LegacyIdType& legacy_id)
    {
        if (const auto id = get_id_from_legacy(legacy_id))
            return (*this)[*id];
        else
            return none;
    }

private:
    optional<IdType> retrieve_legacy_id_from_lua(const LegacyIdType& legacy_id)
    {
        optional<std::string> it = _data.by_legacy(Traits::type_id, legacy_id);

        if (it)
        {
            IdType id(*it);
            _by_legacy_id.emplace(legacy_id, id);
            return id;
        }

        return none;
    }

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
            std::string message = "Error initializing "s + Traits::type_id +
                ":" + id.get() + ": " + e.what();
            ELONA_WARN() << message;
            std::cerr << message << std::endl;

            _errors.emplace(id, e.what());
            return none;
        }

        return _storage[id];
    }

protected:
    lua::DataTable _data;
    MapType _storage;
    LegacyMapType _by_legacy_id;
    ErrorMapType _errors;
};
} // namespace data
} // namespace elona

#define ELONA_DEFINE_LUA_DB(ClassName, DataTypeName, legacy_id, name) \
    class ClassName; \
    namespace data \
    { \
    template <> \
    struct LuaLazyCacheTraits<ClassName> \
    { \
        using DataType = DataTypeName; \
        static const constexpr bool need_legacy_id = legacy_id; \
        static const constexpr char* type_id = name; \
    }; \
    } \
    class ClassName : public data::LuaLazyCache<ClassName> \
    { \
    public: \
        ClassName() = default; \
        DataTypeName convert(const lua::ConfigTable&, const std::string&); \
    };

#define DATA_REQ(name, type) type name = data.required<type>(#name);
#define DATA_OPT_OR(name, type, def) \
    type name = data.optional_or<type>(#name, def);
#define DATA_OPT(name, type) optional<type> name = data.optional<type>(#name);
#define DATA_VEC(name, type) std::vector<type> name = data.vector<type>(#name);
#define DATA_TABLE(name, keytype, valuetype) \
    std::unordered_map<keytype, valuetype> name = \
        data.unordered_map<keytype, valuetype>(#name);
#define DATA_ENUM(name, type, table, def) \
    type name = data.enum_or<type>(#name, lua::LuaEnums::table, def);
