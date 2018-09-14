#pragma once

#include <algorithm>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>
#include "optional.hpp"



namespace elona
{


namespace detail
{
extern std::mt19937 engine;
} // namespace detail



// TODO: pass more proper seed
// This function is called very frequently in a certain circumstances.
// In general, std::random_device is slower than other generators.
inline void randomize(
    std::random_device::result_type seed = std::random_device{}())
{
    detail::engine.seed(seed);
}



// [0, max)
template <
    typename Integer,
    std::enable_if_t<std::is_integral<Integer>::value, std::nullptr_t> =
        nullptr>
inline Integer rnd(Integer max)
{
    return std::uniform_int_distribution<Integer>{
        Integer{0}, std::max(Integer{0}, max - 1)}(detail::engine);
}



template <typename Range>
auto choice(const Range& range)
{
    // std::initializer_list does not have empty() for some reason.
    assert(range.size() != 0);

    auto itr = std::begin(range);
    std::advance(itr, rnd(range.size()));
    return *itr;
}



template <typename Range, typename Iterator, typename Distance>
Iterator sample(const Range& range, Iterator result, Distance n)
{
    using std::begin;
    using std::end;
    auto copy = range;
    std::shuffle(begin(copy), end(copy), detail::engine);
    std::copy_n(begin(copy), n, result);
    return result;
}



template <typename T>
struct WeightedRandomSampler
{
    void add(const T& value, int weight)
    {
        sum += weight;
        candidates.emplace_back(value, sum);
    }


    optional<T> get()
    {
        if (candidates.empty())
            return none;
        if (sum == 0)
            return none;

        const int n = rnd(sum);
        for (const auto& candidate : candidates)
        {
            if (candidate.second > n)
            {
                return candidate.first;
            }
        }

        return none;
    }


private:
    int sum{};
    std::vector<std::pair<T, int>> candidates;
};



} // namespace elona
