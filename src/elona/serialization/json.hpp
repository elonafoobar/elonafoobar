#pragma once

#include <fstream>

#include "../filesystem.hpp"
// #include "json/iarchive.hpp" Not implemented yet
#include "json/oarchive.hpp"



namespace elona::serialization::json
{

template <typename T>
void save(std::ostream& out, T& value)
{
    OArchive ar{out};
    ar(value);
}



template <typename T>
void save(const fs::path& path, T& value)
{
    std::ofstream out{path.native()};
    save(out, value);
}

} // namespace elona::serialization::json
