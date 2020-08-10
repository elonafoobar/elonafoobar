#pragma once

#include <tuple>

#include "../concepts.hpp"



namespace elona::serialization
{

namespace detail
{

template <typename Tuple, typename Archive, size_t... Indice>
void visit(Tuple& value, Archive& ar, std::index_sequence<Indice...>)
{
    using swallow = std::initializer_list<int>;
    (void)swallow{(ar(std::get<Indice>(value)), 0)...};
}

} // namespace detail



template <typename Archive, typename... Types>
void serialize(std::tuple<Types...>& value, Archive& ar)
{
    constexpr size_t tuple_size = std::tuple_size_v<std::tuple<Types...>>;
    detail::visit(value, ar, std::make_index_sequence<tuple_size>());
}

} // namespace elona::serialization
