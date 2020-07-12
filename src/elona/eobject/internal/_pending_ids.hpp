#pragma once

#include <utility>
#include <vector>



namespace elona::eobject
{

template <typename T>
struct OptionalRef;

struct Id;



namespace internal
{

// TODO: avoid using a global state.
template <typename T>
inline std::vector<std::pair<OptionalRef<T>*, Id>> _pending_ids;

} // namespace internal

} // namespace elona::eobject
