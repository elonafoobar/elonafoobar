#pragma once

#include <vector>

#include "optional.hpp"



namespace elona
{

template <typename T>
struct elona_vector2;

enum class TurnResult;
struct Character;



struct Quest
{
    /**
     * 0 if empty.
     */
    int client_chara_index{};

    int originating_map_id{};

    int deadline_hours{};

    /**
     * TODO: enum class
     *
     * 0    - do not show
     * 1001 - hunt
     * 1002 - deliver
     * 1003 - cook
     * 1004 - supply
     * 1006 - harvest
     * 1007 - escort
     * 1008 - conquer
     * 1009 - party
     * 1010 - huntex
     * 1011 - collect
     */
    int id{};

    /**
     * Used only for escort quests.
     *
     * 0 - hard (assassin)
     * 1 - moderate (poison)
     * 2 - normal (delivery)
     */
    int escort_difficulty{};

    /**
     * For hunting quests, target character level is determined as follows.
     *
     * hunt   - difficulty * 10 / 6
     * huntex - difficulty * 3 / 2
     */
    int difficulty{};

    int reward_gold{};

    /**
     * If < 10000:
     * 1 - equipment
     * 2 - magical goods
     * 3 - armor
     * 4 - weapons
     * 5 - ores
     * 6 - furnitures (but no code path?)
     *
     * If <= 10000, acts as flttypemajor
     */
    int reward_item_id{};

    /**
     * 0: not taken
     * 1: accepted
     * 3: complete
     */
    int progress{};

    /**
     * If -1, deadline is immediate
     */
    int deadline_days{};

    /**
     * Target character for quests like "collect" (person bragging about item)
     *
     * Also may point to the quest giver.
     */
    int target_chara_index{};

    /**
     * Used for "deliver", "supply" and "collect".
     */
    int target_item_id{};

    /**
     * cook    - food type
     * harvest - required weight
     * escort  - destination map id
     * party   - required points
     * huntex  - target character id
     */
    int extra_info_1{};

    /**
     * cook    - food rank
     * harvest - weight delivered so far
     * escort  - escorted character id
     * party   - points so far
     */
    int extra_info_2{};

    /**
     * If a character has a related quest and this flag is set on the quest, the
     * emotion icon for the character will indicate they are the package
     * recipient.
     */
    int delivery_has_package_flag{};



    /**
     * Moves this struct's fields into `qdata` so they can be serialized, for
     * compatibility. To be called before serializing `qdata`.
     */
    void pack_to(elona_vector2<int>& legacy_qdata, int quest_id);


    /**
     * Moves `qdata` fields into this struct. To be called after deserializing
     * `qdata`.
     */
    void unpack_from(elona_vector2<int>& legacy_qdata, int quest_id);
};



struct QuestData
{
    static constexpr size_t quest_size = 500;

    QuestData()
        : quests(quest_size)
    {
    }

    Quest& operator[](int i)
    {
        return quests.at(static_cast<size_t>(i));
    }



    Quest& immediate();


    // Helper method to pack all quests to `qdata`.
    void pack_to(elona_vector2<int>& legacy_qdata);


    // Helper method to unpack all quests from `qdata`.
    void unpack_from(elona_vector2<int>& legacy_qdata);


private:
    std::vector<Quest> quests;
};



extern QuestData quest_data;



void quest_on_map_initialize();
void quest_place_target();
bool quest_targets_remaining();
void quest_set_data(int quest_idx, optional_ref<const Character> client, int);
void quest_refresh_list();
void quest_update_journal_msg();

void quest_check();
void quest_check_all_for_failed();
void quest_update_main_quest_journal();
void quest_all_targets_killed();
void quest_failed(optional<int> quest_idx, int);
void quest_complete(int quest_idx);
bool quest_is_return_forbidden();
void quest_enter_map();
void quest_exit_map();
void quest_team_victorious();
TurnResult quest_pc_died_during_immediate_quest();

bool quest_generate(int quest_idx);

} // namespace elona
