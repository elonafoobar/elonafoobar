#pragma once

#include <string>

#include "data/id.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;



enum class TalkResult
{
    talk_npc,
    talk_unique,
    talk_quest_giver,
    talk_house_visitor,
    talk_sleeping,
    talk_busy,
    talk_ignored,
    talk_finish_escort,
    talk_game_begin,
    talk_more,
    talk_end
};

void talk_start();
void talk_to_npc(Character& chara);
void talk_end();
bool talk_setup_variables(Character& chara);
void talk_reset_variables();
void talk_window_init(std::string& text);
std::string talk_get_speaker_name(const Character& chara);

void talk_window_show(
    optional<data::InstanceId> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest);

int talk_window_query(const Character& chara);
int talk_window_query(
    optional<data::InstanceId> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest);

int talk_guide_quest_client();

TalkResult talk_more(Character& speaker);
TalkResult talk_sleeping(Character& speaker);
TalkResult talk_busy(Character& speaker);
TalkResult talk_ignored(Character& speaker);
TalkResult talk_house_visitor(Character& speaker);
TalkResult talk_game_begin(Character& initial_speaker);

void talk_wrapper(Character& speaker, TalkResult initial);
TalkResult talk_npc(Character& speaker);
TalkResult talk_unique(Character& speaker);

} // namespace elona
