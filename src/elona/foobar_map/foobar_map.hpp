#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <boost/variant.hpp>

#include "../optional.hpp"
#include "../shared_id.hpp"

namespace elona
{
namespace fmp
{

/**
 * A map interchange format intended to be converted to the internal map
 * representation.
 */
struct FoobarMap
{
    using MappedId = int;
    using Mapping = std::unordered_map<MappedId, SharedId>;
    using Property = boost::variant<int, std::string, bool>;

    struct Properties
    {
    public:
        using StorageType = std::unordered_map<std::string, Property>;
        using iterator = StorageType::iterator;
        using const_iterator = StorageType::const_iterator;

        iterator begin()
        {
            return storage.begin();
        }

        iterator end()
        {
            return storage.end();
        }

        const_iterator begin() const
        {
            return storage.begin();
        }

        const_iterator end() const
        {
            return storage.end();
        }

        Property& operator[](const std::string& key)
        {
            return storage[key];
        }

        template <typename T>
        T get(const std::string& key)
        {
            return boost::get<T>(storage.at(key));
        }

        template <typename T>
        optional<T> get_optional(const std::string& key)
        {
            const auto it = storage.find(key);
            if (it == storage.end())
                return none;
            try
            {
                return boost::get<T>(it->second);
            }
            catch (std::exception& e)
            {
                return none;
            }
        }

        template <typename T>
        T get_or(const std::string& key, T default_value)
        {
            const auto it = storage.find(key);
            if (it == storage.end())
                return default_value;
            try
            {
                return boost::get<T>(it->second);
            }
            catch (std::exception& e)
            {
                return default_value;
            }
        }

    private:
        StorageType storage;
    };

    enum class PropertyType
    {
        int_type = 0,
        bool_type = 1,
        string_type = 2,
    };

    struct Object
    {
        SharedId data_type;
        SharedId data_id;
        std::string name;
        int x;
        int y;
        Properties props;
        Properties tile_props;
    };

    struct Layer
    {
        enum class Type
        {
            tile = 0,
            object = 1,
            group = 2,
            image = 3
        };

        int id;
        Type type;
        std::string name;
        Properties props;

        // for group layers
        std::vector<int> child_layers;

        // for object layers
        std::vector<Object> objects;
    };

    int version;
    std::vector<std::string> mods;
    Mapping ids_to_names;
    Properties props;
    int width;
    int height;
    std::vector<SharedId> tiles;
    std::vector<Layer> layers;
};

} // namespace fmp
} // namespace elona
