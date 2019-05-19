#pragma once
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../filesystem.hpp"
#include "../../thirdparty/zstr/zstr.hpp"
#include "../shared_id.hpp"
#include "foobar_map.hpp"

namespace elona
{
namespace fmp
{

class MapLoader
{
public:
    FoobarMap load(const fs::path&);

private:
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

    std::unique_ptr<zstr::ifstream> _in;

    FoobarMap _map;
};

} // namespace fmp
} // namespace elona
