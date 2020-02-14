#pragma once

#include <algorithm>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

#include "../thirdparty/xoshiro256//xoshiro256.hpp"
#include "optional.hpp"

// DO NOT use `std::uniform_int_distribution` because its algorithm is
// implementation-defined. Always use this
// `boostrandom::uniform_int_distribution`.
#include "../thirdparty/boostrandom/uniform_int_distribution.hpp"



namespace elona
{

namespace detail
{
extern xoshiro256::xoshiro256_engine engine;
} // namespace detail



// Reset random seed to the global seed.
void randomize();



inline void randomize(int seed)
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
    using Dist = boostrandom::uniform_int_distribution<Integer>;
    return Dist{Integer{0}, std::max(Integer{0}, max - 1)}(detail::engine);
}



// [0, M) where M is min { max, 32768 }
// Vanilla-compatible rnd() function. HSP rnd() returns [0, 32768). The upper
// limit comes from RAND_MAX in C lang.
template <
    typename Integer,
    std::enable_if_t<std::is_integral<Integer>::value, std::nullptr_t> =
        nullptr>
inline Integer rnd_capped(Integer max)
{
    return rnd(std::min<Integer>(max, 32768));
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



template <typename Range1, typename Distance, typename Range2 = Range1>
Range2 sampled(const Range1& range, Distance n)
{
    using std::back_inserter;
    Range2 result;
    sample(range, back_inserter(result), n);
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
