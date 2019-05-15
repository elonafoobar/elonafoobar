#pragma once
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <boost/iostreams/filtering_stream.hpp>

#include "../filesystem.hpp"
#include "../shared_id.hpp"
#include "foobar_map.hpp"

namespace elona
{
namespace fmp
{

namespace bio = boost::iostreams;

class MapLoader
{
public:
    static FoobarMap load(const fs::path&);

private:
    FoobarMap do_load(const fs::path&);

    std::string read_string();
    int read_int();
    bool read_bool();
    char read_char();
    SharedId read_mapped_name();
    FoobarMap::Properties read_properties();
    FoobarMap::Property read_property();
    std::vector<SharedId> read_tiles();
    std::vector<FoobarMap::Layer> read_layers();
    FoobarMap::Layer read_layer();
    FoobarMap::Object read_object();

    bio::filtering_stream<bio::input> _in;

    FoobarMap _map;
};

} // namespace fmp
} // namespace elona
