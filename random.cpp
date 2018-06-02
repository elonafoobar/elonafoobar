#include "random.hpp"



namespace elona
{
namespace detail
{
std::mt19937 engine{std::random_device{}()};
} // namespace detail
} // namespace elona
