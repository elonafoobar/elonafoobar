#include "story_quest.hpp"

#include "game.hpp"



namespace elona
{

lua_int story_quest_progress(data::InstanceId id)
{
    return game()->story_quests.progress(id);
}



void story_quest_set_progress(data::InstanceId id, lua_int new_progress)
{
    game()->story_quests.set_progress(id, new_progress);
}



void story_quest_add_progress(data::InstanceId id, lua_int progress)
{
    story_quest_set_progress(id, story_quest_progress(id) + progress);
}



template <typename T>
T story_quest_get_ext(data::InstanceId id, std::string_view field_name)
{
    return game()->story_quests.get_ext<T>(id, field_name);
}


// explicit template instantiation
template bool story_quest_get_ext<bool>(data::InstanceId, std::string_view);
template lua_int story_quest_get_ext<lua_int>(
    data::InstanceId,
    std::string_view);



template <typename T>
void story_quest_set_ext(
    data::InstanceId id,
    std::string_view field_name,
    T&& new_value)
{
    game()->story_quests.set_ext(id, field_name, std::forward<T>(new_value));
}


// explicit template instantiation
template void
story_quest_set_ext<bool>(data::InstanceId, std::string_view, bool&&);
template void
story_quest_set_ext<lua_int>(data::InstanceId, std::string_view, lua_int&&);



void story_quest_add_ext(
    data::InstanceId id,
    std::string_view field_name,
    lua_int change)
{
    const auto old = story_quest_get_ext<lua_int>(id, field_name);
    story_quest_set_ext(id, field_name, old + change);
}

} // namespace elona
