#pragma once

#include <map>
#include <set>
#include <vector>

template <typename Value>
class TopologicalSorter
{
private:
    struct Data
    {
        size_t dependencies_left = 0;
        std::set<Value> dependents;
    };

    std::map<Value, Data> _map;

public:
    /// Represents (sorted items, items in a cycle)
    using Result = std::pair<std::vector<Value>, std::vector<Value>>;

    void add(const Value& value)
    {
        if (_map.find(value) == std::end(_map))
        {
            _map[value] = Data{};
        }
    }

    /**
     * Adds an edge from (value -> dependency). If either do not exist in the
     * sorter, they will be added automatically.
     */
    void add_dependency(const Value& value, const Value& dependency)
    {
        if (value == dependency)
            return;

        add(value);
        add(dependency);

        // Add the value as a dependent in the dependency, to know which values
        // are leaves in the graph (and are sorted first).
        auto& dependents = _map[dependency].dependents;

        if (dependents.find(value) == std::end(dependents))
        {
            dependents.insert(value);

            _map[value].dependencies_left++;
        }
    }

    /**
     * @return a pair containing (sorted items, items in a cycle)
     */
    Result sort()
    {
        std::vector<Value> sorted;
        std::vector<Value> in_cycle;

        // Create a working copy of the graph, since it is mutated in place.
        std::map<Value, Data> map{_map};

        // Place all nodes with no dependencies first in the sorted list.
        for (const auto& pair : map)
        {
            const auto& value = pair.first;
            const auto& data = pair.second;

            if (data.dependencies_left == 0)
            {
                sorted.push_back(value);
            }
        }

        // Find nodes whose dependencies are all already sorted, and add each
        // one to the sorted list incrementally.
        for (size_t index = 0; index < sorted.size(); index++)
        {
            auto& dependents = map[sorted[index]].dependents;

            for (const auto& dependent : dependents)
            {
                auto& data = map[dependent];

                data.dependencies_left--;

                if (data.dependencies_left == 0)
                {
                    sorted.push_back(dependent);
                }
            }
        }

        // Any remaining nodes were part of a cycle.
        for (const auto& pair : map)
        {
            const auto& value = pair.first;
            const auto& data = pair.second;

            if (data.dependencies_left != 0)
            {
                in_cycle.push_back(value);
            }
        }

        return std::make_pair(sorted, in_cycle);
    }
};
