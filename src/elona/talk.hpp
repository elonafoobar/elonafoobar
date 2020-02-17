#pragma once
#include <string>

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
void talk_to_npc();
void talk_to_npc(Character& chara);
void talk_end();
bool talk_setup_variables(Character& chara);
void talk_reset_variables();
void talk_window_init(std::string& text);
std::string talk_get_speaker_name(const Character& chara);

void talk_window_show(
    optional<const std::string&> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest);

int talk_window_query();
int talk_window_query(const Character& chara);
int talk_window_query(
    optional<const std::string&> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest);

int talk_guide_quest_client();

TalkResult talk_more();
TalkResult talk_sleeping();
TalkResult talk_busy();
TalkResult talk_ignored();
TalkResult talk_house_visitor();
TalkResult talk_game_begin();

void talk_wrapper(TalkResult);
TalkResult talk_npc();
TalkResult talk_unique();

} // namespace elona
