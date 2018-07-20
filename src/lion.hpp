#pragma once
#include <boost/flyweight.hpp>
#include <unordered_map>
#include <sstream>
#include <vector>
#include "filesystem.hpp"
#include "lib/noncopyable.hpp"
#include "hcl.hpp"
#include "log.hpp"
#include "optional.hpp"
#include "thirdparty/ordered_map/ordered_map.h"

namespace elona
{
namespace lion
{

typedef std::string inner_id;
typedef boost::flyweight<inner_id> id;

template <typename>
struct lion_db_traits;


template <class T>
class lion_db : public lib::noncopyable
{
    using traits_type = lion_db_traits<T>;

public:
    using id_type = id;
    using data_type = typename traits_type::data_type;
    using spec_type = typename traits_type::spec_type;
    using map_type = std::unordered_map<id_type, data_type>;

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

    virtual const std::string identifier() const { return traits_type::identifier; }


    void load(const fs::path& file)
    {
        if (fs::exists(file))
        {
            data_files.push_back(file);
        }
        else
        {
            ELONA_LOG("No such data file " << file.string());
        }
    }


    void reify(hcl::Value object, const std::string& file = "[string]")
    {
        hcl::Value base = hclutil::skip_sections(object,
                                                 {identifier()},
                                                 file);
        std::string id_base = scope + "." + identifier();

        if (!base.is<hcl::Object>())
        {
            throw hcl_error(file, "\"" + identifier() + "\""
                            + "was not declared as an object.");
        }

        for (const auto& value : base.as<hcl::Object>())
        {
            // Would be better served by expected<V, E>, but boost doesn't have it.
            if (!value.second.is<hcl::Object>())
            {
                ELONA_LOG("Item was not object: " <<
                          identifier() << "." << value.first);
            }
            if (!spec.validate(value))
            {
                ELONA_LOG("Validation failed for " <<
                          identifier() << "." << value.first);
            }
            optional<data_type> data = static_cast<T&>(*this).convert(value.second.as<hcl::Object>());
            if (data == none)
            {
                ELONA_LOG("Conversion failed for " <<
                          identifier() << "." << value.first);
            }
            else
            {
                id id(id_base + "." + value.first);
                if (storage.find(id) != storage.end())
                {
                    ELONA_LOG("Duplicate ID found for " << id.get());
                }
                else
                {
                    storage.emplace(id, *data);
                }
            }
        }
    }


    void reify(std::string hcl)
    {
        std::istringstream ss(hcl);
        hcl::Value value = hclutil::parse(ss);
        reify(value);
    }

    void reify_all()
    {
        for (const fs::path& file : data_files)
        {
            hcl::Value object = hclutil::load(file);
            reify(object);
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


    optional_ref<data_type> operator[](const inner_id& inner_id) const
    {
        return (*this)[id(inner_id)];
    }


protected:
    std::string scope;
    std::vector<fs::path> data_files;
    spec_type spec;
    map_type storage;
};

} // namespace lion
} // namespace elona
