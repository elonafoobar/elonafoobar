#pragma once

#include <string_view>
#include <unordered_map>

#include "data/id.hpp"
#include "lua_env/lua_env.hpp"
#include "typedefs.hpp"



namespace elona
{

/**
 * One story quest's progress and extra parameters.
 */
struct StoryQuest
{
    /// Quest progress
    lua_int progress{};

    /// Extension data
    lua_table ext{};
};



/**
 * All story quests.
 */
struct StoryQuestTable
{
    /**
     * Gets the progress of the story quest of @a id.
     *
     * @param id The story quest ID
     * @return The progress of the story quest
     */
    lua_int progress(data::InstanceId id) const noexcept
    {
        if (const auto itr = _quests.find(id); itr != _quests.end())
        {
            return itr->second.progress;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Sets the progress of the story quest of @a id with the given @a
     * new_progress. If @a new_progress is negative, the progress is set to
     * zero.
     *
     * @param id The story quest ID
     * @param new_progress The new progress of the story quest
     */
    void set_progress(data::InstanceId id, lua_int new_progress)
    {
        if (new_progress == 0 && _quests.find(id) == _quests.end())
            return;

        _quests[id].progress = std::max(new_progress, lua_int{0});
    }



    /**
     * Get ext table's field of the story quest @a id.
     *
     * @param id The story quest ID
     * @param field_name The field name of ext to get
     * @return The ext field
     */
    template <typename T>
    T get_ext(data::InstanceId id, std::string_view field_name)
    {
        if (const auto itr = _quests.find(id); itr != _quests.end())
        {
            if (const auto ret =
                    itr->second.ext.get<sol::optional<T>>(field_name))
            {
                return *ret;
            }
            else
            {
                return T{};
            }
        }
        else
        {
            return T{};
        }
    }



    /**
     * Set ext table's field of the story quest @a id.
     *
     * @param id The story quest ID
     * @param field_name The field name of ext to set
     * @param new_value The new value to be set
     */
    template <typename T>
    void
    set_ext(data::InstanceId id, std::string_view field_name, T&& new_value)
    {
        auto& entry = _quests[id];
        if (entry.ext == sol::lua_nil)
        {
            entry.ext = lua::lua->get_state()->create_table();
        }

        entry.ext.set(field_name, std::forward<T>(new_value));
    }



private:
    std::unordered_map<data::InstanceId, StoryQuest> _quests;
};



/* Shorthand functions */

lua_int story_quest_progress(data::InstanceId id);
void story_quest_set_progress(data::InstanceId id, lua_int new_progress);
void story_quest_add_progress(data::InstanceId id, lua_int progress);

template <typename T>
T story_quest_get_ext(data::InstanceId id, std::string_view field_name);

template <typename T>
void story_quest_set_ext(
    data::InstanceId id,
    std::string_view field_name,
    T&& new_value);

void story_quest_add_ext(
    data::InstanceId id,
    std::string_view field_name,
    lua_int change);

} // namespace elona
