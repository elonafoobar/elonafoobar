#pragma once

#include <cstdint>
#include <map>
#include <vector>



namespace json5
{

using null_type = std::nullptr_t;
using boolean_type = bool;
using integer_type = int64_t;
using number_type = double;
using string_type = std::string;

template <typename T>
using array_container_type = std::vector<T>;

template <typename K, typename V>
using object_container_type = std::map<K, V>;

} // namespace json5
