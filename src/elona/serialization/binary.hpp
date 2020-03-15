#pragma once

#include <fstream>

#include "../filesystem.hpp"
#include "binary/iarchive.hpp"
#include "binary/oarchive.hpp"



namespace elona::serialization::binary
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



template <typename T>
void load(std::istream& in, T& value)
{
    IArchive ar{in};
    ar(value);
}



template <typename T>
void load(const fs::path& path, T& value)
{
    std::ifstream in{path.native()};
    load(in, value);
}

} // namespace elona::serialization::binary
