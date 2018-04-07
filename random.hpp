#pragma once

#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include "optional.hpp"



namespace elona
{



namespace detail
{

inline std::mt19937 random_engine{std::random_device{}()};
// For exrand
inline std::mt19937 random_engine2{std::random_device{}()};

} // namespace detail



template <typename T, typename Weight = int>
struct weighted_random_sampler
{
    void add(const T& value, const Weight& weight)
    {
        sum += weight;
        candidates.emplace_back(value, sum);
    }


    optional<T> get()
    {
        if (std::empty(candidates))
            return none;
        if (sum == 0)
            return none;

        std::uniform_int_distribution<Weight> dist{0, sum - 1};
        int n = dist(detail::random_engine2);
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
    Weight sum = 0;
    std::vector<std::pair<T, Weight>> candidates;
};



template <typename Range>
auto choice(const Range& range)
{
    assert(!std::empty(range));

    std::uniform_int_distribution<size_t> dist{0, std::size(range) - 1};
    auto itr = std::begin(range);
    std::advance(itr, dist(detail::random_engine));
    return *itr;
}



template <typename Range, typename Iterator, typename Distance>
Iterator sample(const Range& range, Iterator result, Distance n)
{
    using std::begin, std::end;
    std::sample(begin(range), end(range), result, n, detail::random_engine);
    return result;
}



} // namespace elona
