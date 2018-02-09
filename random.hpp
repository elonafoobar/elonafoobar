#pragma once

#include <optional>
#include <random>
#include <utility>
#include <vector>



namespace elona
{



template <typename T, typename Weight = int>
struct weighted_random_sampler
{
    void add(const T& value, const Weight& weight)
    {
        sum += weight;
        candidates.emplace_back(value, sum);
    }


    std::optional<T> get()
    {
        if (std::empty(candidates))
            return std::nullopt;
        if (sum == 0)
            return std::nullopt;

        // FIXME: use global random engine.
        std::mt19937 random_engine{std::random_device{}()};
        std::uniform_int_distribution<Weight> dist{0, sum - 1};
        int n = dist(random_engine);
        for (const auto& candidate : candidates)
        {
            if (candidate.second > n)
            {
                return candidate.first;
            }
        }

        return std::nullopt;
    }


private:
    Weight sum = 0;
    std::vector<std::pair<T, Weight>> candidates;
};



template <typename Range>
auto choice(const Range& range)
{
    assert(!std::empty(range));

    // FIXME: use global random engine.
    std::mt19937 random_engine{std::random_device{}()};
    std::uniform_int_distribution<size_t> dist{0, std::size(range) - 1};
    auto itr = std::begin(range);
    std::advance(itr, dist(random_engine));
    return *itr;
}



} // namespace elona
