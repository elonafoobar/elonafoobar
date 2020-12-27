#include "quest.hpp"

#include "activity.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "crafting_material.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "food.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "save.hpp"
#include "skill.hpp"
#include "text.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

namespace
{

int quest_gen_scale_by_level(const Quest& quest, int factor)
{
    const auto D = quest.difficulty;
    const auto L = cdata.player().level;

    const auto k = (D + 3) * 100 + rnd_capped(D * 30 + 200) + 400;
    const auto n = (k * factor / 100) * 100 / (100 + D * 2 / 3);

    if (quest.id == 1011 || quest.id == 1003 || quest.id == 1004 ||
        quest.id == 1002)
    {
        return n;
    }

    if (L >= D)
    {
        return n * 100 / (100 + (L - D) * 10);
    }
    else
    {
        return n * (100 + clamp((D - L) / 5 * 25, 0, 200)) / 100;
    }
}

} // namespace



QuestData quest_data;



Quest& QuestData::immediate()
{
    return quest_data[game()->executing_immediate_quest];
}



int rewardfix = 0;



bool quest_is_return_forbidden()
{
    for (const auto& quest_idx : game()->taken_quests)
    {
        if (quest_data[quest_idx].progress == 1)
        {
            if (quest_data[quest_idx].id == 1007 ||
                quest_data[quest_idx].id == 1002)
            {
                return true;
            }
        }
    }
    return false;
}



void quest_place_target()
{
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() == Character::State::alive)
        {
            cnt.is_quest_target() = true;
            cnt.relationship = Relationship::enemy;
        }
    }
}



bool quest_targets_remaining()
{
    for (auto&& chara : cdata.others())
    {
        if (chara.state() == Character::State::alive)
        {
            if (chara.is_quest_target())
            {
                return true;
            }
        }
    }
    return false;
}



void quest_check()
{
    if (game()->current_map == mdata_t::MapId::vernis)
    {
        if (game()->current_dungeon_level == 3)
        {
            if (!quest_targets_remaining())
            {
                if (story_quest_progress("core.putit_attacks") < 2)
                {
                    story_quest_set_progress("core.putit_attacks", 2);
                    quest_update_journal_msg();
                }
            }
        }
        if (game()->current_dungeon_level == 4)
        {
            if (!quest_targets_remaining())
            {
                if (story_quest_progress("core.thieves_hideout") < 2)
                {
                    story_quest_set_progress("core.thieves_hideout", 2);
                    quest_update_journal_msg();
                }
            }
        }
        if (game()->current_dungeon_level == 5)
        {
            if (!quest_targets_remaining())
            {
                if (story_quest_progress("core.nightmare") < 3)
                {
                    story_quest_set_progress("core.nightmare", 3);
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (game()->current_map == mdata_t::MapId::yowyn)
    {
        if (game()->current_dungeon_level == 3)
        {
            if (!quest_targets_remaining())
            {
                if (story_quest_progress("core.cat_house") < 2)
                {
                    story_quest_set_progress("core.cat_house", 2);
                    quest_update_journal_msg();
                }
            }
        }
        if (game()->current_dungeon_level == 4)
        {
            if (!quest_targets_remaining())
            {
                if (story_quest_progress("core.defense_line") < 3)
                {
                    story_quest_set_progress("core.defense_line", 3);
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (game()->current_map == mdata_t::MapId::lumiest)
    {
        if (game()->current_dungeon_level == 20)
        {
            if (!quest_targets_remaining())
            {
                if (story_quest_progress("core.sewer_sweeping") < 2)
                {
                    story_quest_set_progress("core.sewer_sweeping", 2);
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (game()->executing_immediate_quest_type == 0)
    {
        return;
    }
    if (game()->executing_immediate_quest_status != 3)
    {
        if (game()->executing_immediate_quest_show_hunt_remain == 1)
        {
            size_t remaining_monsters{};
            for (auto&& chara : cdata.others())
            {
                if (chara.state() == Character::State::alive)
                {
                    ++remaining_monsters;
                }
            }
            if (remaining_monsters == 0)
            {
                deferred_event_add("core.quest_all_target_killed");
            }
            else
            {
                txt(i18n::s.get(
                        "core.quest.hunt.remaining", remaining_monsters),
                    Message::color{ColorIndex::blue});
            }
        }
        if (game()->executing_immediate_quest_type == 1008)
        {
            if (!chara_find(
                    the_character_db[quest_data.immediate().extra_info_1]->id))
            {
                deferred_event_add("core.quest_all_target_killed");
            }
        }
    }
}



void quest_set_data(
    int quest_idx,
    optional_ref<const Character> client,
    int val0)
{
    auto& quest = quest_data[quest_idx];

    randomize(quest.client_chara_index + 1);
    s(6) = "";
    s(5) = i18n::s.get("core.quest.info.gold_pieces", quest.reward_gold);
    if (quest.reward_item_id != 0)
    {
        if (quest.reward_item_id < 10000)
        {
            s(5) += i18n::s.get("core.quest.info.and") +
                i18n::s.get_enum("core.ui.reward", quest.reward_item_id);
        }
        else
        {
            s(5) += i18n::s.get("core.quest.info.and") +
                fltname(quest.reward_item_id);
        }
    }
    if (quest.deadline_days == -1)
    {
        nquestdate = i18n::s.get("core.quest.info.no_deadline");
    }
    else
    {
        nquestdate = i18n::s.get("core.quest.info.days", quest.deadline_days);
    }
    if (quest.id == 1006)
    {
        s = u8"%HARVEST"s;
        parse_quest_board_text(val0);
        s(10) = ""s + cnvweight(quest.extra_info_1);
        s(11) = mapname(quest.originating_map_id);
        s(4) = i18n::s.get("core.quest.info.harvest.text", s(10));
        if (game()->executing_immediate_quest == quest_idx)
        {
            s(4) += i18n::s.get(
                "core.quest.info.now", cnvweight(quest.extra_info_2));
        }
        s(6) = s(4);
    }
    if (quest.id == 1009)
    {
        s = u8"%PARTY"s;
        parse_quest_board_text(val0);
        s(10) = i18n::s.get("core.quest.info.party.points", quest.extra_info_1);
        s(11) = mapname(quest.originating_map_id);
        s(4) = i18n::s.get("core.quest.info.party.text", s(10));
        if (game()->executing_immediate_quest == quest_idx)
        {
            s(4) += i18n::s.get("core.quest.info.now", quest.extra_info_2);
        }
        s(6) = s(4);
    }
    if (quest.id == 1007)
    {
        s = u8"%ESCORT,"s + quest.escort_difficulty;
        parse_quest_board_text(val0);
        s(11) = ""s + mapname(quest.extra_info_1);
        s(4) = i18n::s.get("core.quest.info.escort.text", s(11));
        s(6) = s(4);
    }
    if (quest.id == 1001)
    {
        s = u8"%HUNT"s;
        parse_quest_board_text(val0);
        s(4) = i18n::s.get("core.quest.info.hunt.text");
        s(6) = s(4);
    }
    if (quest.id == 1004)
    {
        s = u8"%SUPPLY"s;
        parse_quest_board_text(val0);
        s(4) = cnvarticle(cnvitemname(quest.target_item_id));
        s(6) = i18n::s.get("core.quest.info.supply.text", s(4));
    }
    if (quest.id == 1002)
    {
        s = u8"%DELIVER,"s + quest.extra_info_1;
        parse_quest_board_text(val0);
        s(10) = cnvarticle(cnvitemname(quest.target_item_id));
        s(11) = ""s +
            mapname(quest_data[quest.target_chara_index].originating_map_id);
        s(12) = ""s + qname(quest.target_chara_index);
        if (iorgweight(quest.target_item_id) > 50000)
        {
            s(10) += i18n::s.get("core.quest.info.heavy");
        }
        s(4) = i18n::s.get("core.quest.info.deliver.text", s(10), s(11), s(12));
        s(6) = s(4) + i18n::s.get("core.quest.info.deliver.deliver");
    }
    if (quest.id == 1003)
    {
        s = u8"%COOK,"s + quest.extra_info_1;
        if (rnd(6) == 0)
        {
            s = u8"%COOK,GENERAL"s;
        }
        parse_quest_board_text(val0);
        s(4) =
            cnvarticle(foodname(quest.extra_info_1, ""s, quest.extra_info_2));
        s(6) = i18n::s.get("core.quest.info.supply.text", s(4));
    }
    if (quest.id == 1008)
    {
        s = u8"%CONQUER"s;
        parse_quest_board_text(val0);
        s(4) = chara_db_get_name(
            *the_character_db.get_id_from_integer(quest.extra_info_1));
        if (quest.extra_info_1 == 343)
        {
            s(4) = i18n::s.get("core.quest.info.conquer.unknown_monster");
        }
        s(10) = ""s + quest.difficulty * 10 / 6;
        s(6) = i18n::s.get("core.quest.info.conquer.text", s(4));
    }
    if (quest.id == 1010)
    {
        s = u8"%HUNTEX"s;
        parse_quest_board_text(val0);
        s(4) = chara_db_get_name(
            *the_character_db.get_id_from_integer(quest.extra_info_1));
        s(10) = ""s + quest.difficulty * 3 / 2;
        s(6) = i18n::s.get("core.quest.info.huntex.text");
    }
    if (quest.id == 1011)
    {
        s = u8"%COLLECT"s;
        parse_quest_board_text(val0);
        s(10) = cnvarticle(cnvitemname(quest.target_item_id));
        s(11) = ""s + mapname(quest.originating_map_id);
        if (game()->current_map == quest.originating_map_id &&
            game()->current_dungeon_level == 1)
        {
            s(12) = cdata[quest.target_chara_index].name;
        }
        else
        {
            s(12) = i18n::s.get("core.quest.info.collect.target", s(11));
        }
        if (iorgweight(quest.target_item_id) > 50000)
        {
            s(10) += i18n::s.get("core.quest.info.heavy");
        }
        s(4) = i18n::s.get("core.quest.info.collect.text", s(10), s(12));
        s(6) = s(4);
    }
    text_replace_tags_in_quest_text(client);
    if (val0 == 1)
    {
        assert(client);
        buff = i18n::s.get("core.quest.giver.have_something_to_ask", *client) +
            buff;
        if (quest.deadline_days != -1)
        {
            buff += i18n::s.get(
                "core.quest.giver.days_to_perform",
                quest.deadline_days,
                *client);
        }
        buff += i18n::s.get("core.quest.giver.how_about_it", *client);
    }
    if (val0 == 2)
    {
        if (quest.progress == 3)
        {
            buff += u8"@QC["s + i18n::s.get("core.quest.journal.complete") +
                u8"]"s + s(3) + u8"\n"s;
        }
        else
        {
            buff += u8"@QL["s + i18n::s.get("core.quest.journal.job") +
                u8"] "s + s(3) + u8"\n"s;
        }
        buff += i18n::s.get("core.quest.journal.client") + qname(quest_idx) +
            u8"\n"s;
        buff += i18n::s.get("core.quest.journal.location") +
            mapname(quest.originating_map_id) + u8"\n"s;
        buff += i18n::s.get("core.quest.journal.deadline");
        if (quest.deadline_days != -1)
        {
            buff += i18n::s.get("core.quest.journal.remaining");
        }
        buff += nquestdate + u8"\n"s;
        s(5) = i18n::s.get("core.quest.journal.reward") + s(5);
        talk_conv(s(5), 40 - en * 10);
        buff += s(5) + u8"\n"s;
        s(4) = i18n::s.get("core.quest.journal.detail");
        if (quest.progress == 3)
        {
            s(4) += i18n::s.get("core.quest.journal.report_to_the_client");
        }
        else
        {
            s(4) += s(6);
        }
        talk_conv(s(4), 40 - en * 10);
        buff += s(4) + u8"\n"s;
    }
    if (val0 == 3)
    {
        assert(client);
        buff = i18n::s.get("core.quest.giver.complete.done_well", *client);
        if (elona::stoi(s(5)) != 0)
        {
            txt(i18n::s.get(
                "core.quest.giver.complete.take_reward", s(5), *client));
        }
        if (quest.id == 1006)
        {
            if (quest.extra_info_1 * 125 / 100 < quest.extra_info_2)
            {
                buff += i18n::s.get(
                    "core.quest.giver.complete.extra_coins", *client);
            }
        }
        if (quest.id == 1009)
        {
            if (quest.extra_info_1 * 150 / 100 < quest.extra_info_2)
            {
                buff += i18n::s.get(
                    "core.quest.giver.complete.music_tickets", *client);
            }
        }
    }
    randomize();
}



void quest_on_map_initialize()
{
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() == Character::State::empty)
        {
            continue;
        }
        if (cnt.role == Role::none)
        {
            continue;
        }
        if (cnt.quality == Quality::special)
        {
            continue;
        }
        if (cnt.role == Role::other)
        {
            continue;
        }
        i = -1;
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (quest_data[cnt].client_chara_index == 0)
            {
                i = cnt;
                break;
            }
        }
        int cnt2 = cnt.index;
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (quest_data[cnt].client_chara_index == cnt2)
            {
                if (quest_data[cnt].originating_map_id == game()->current_map)
                {
                    i = -1;
                    break;
                }
            }
        }
        if (i == -1)
        {
            break;
        }
        quest_data[i].client_chara_index = cnt.index;
        quest_data[i].originating_map_id = game()->current_map;
        qname(i) = cnt.name;
        cnt.related_quest_id = i + 1;
        game()->number_of_existing_quests = i + 1;
    }
}



void quest_refresh_list()
{
    for (int cnt = 0, cnt_end = (game()->number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (quest_data[cnt].client_chara_index == 0)
        {
            continue;
        }
        if (quest_data[cnt].originating_map_id != game()->current_map)
        {
            continue;
        }
        if (quest_data[cnt].progress == 0)
        {
            if (quest_data[cnt].refresh_time <= game_now())
            {
                const auto generated = quest_generate(cnt);
                if (generated)
                {
                    quest_data[cnt].reward_gold =
                        quest_gen_scale_by_level(quest_data[cnt], rewardfix);
                }
            }
        }
    }
}



void quest_update_journal_msg()
{
    snd("core.write1");
    txt(i18n::s.get("core.quest.journal_updated"),
        Message::color{ColorIndex::green});
}



bool quest_generate(int quest_idx)
{
    auto& quest = quest_data[quest_idx];

    quest.id = 0;
    quest.progress = 0;
    quest.refresh_time =
        game_now() + time::Duration::from_days(rnd(3) + 1) + 1_hour;
    quest.reward_item_id = 0;

    if (rnd(3) == 0)
    {
        return false;
    }

    if (rnd(14) == 0)
    {
        optional<int> target_chara_index;
        optional<int> target_item_id;
        for (int _i = 0; _i < 300; ++_i)
        {
            const auto chara_index =
                rnd(ELONA_MAX_OTHER_CHARACTERS) + ELONA_MAX_PARTY_CHARACTERS;
            if (chara_index == quest.client_chara_index)
            {
                continue;
            }
            if (cdata[chara_index].state() != Character::State::alive)
            {
                continue;
            }
            if (cdata[chara_index].relationship != Relationship::friendly ||
                (cdata[chara_index].role != Role::citizen &&
                 cdata[chara_index].role != Role::guard))
            {
                continue;
            }
            flt(40, Quality::good);
            flttypemajor = choice(fsetcollect);
            if (const auto item =
                    itemcreate_chara_inv(cdata[chara_index], 0, 0))
            {
                target_chara_index = chara_index;
                target_item_id = the_item_db[item->id]->integer_id;
                item->is_quest_target = true;
                break;
            }
            else
            {
                break;
            }
        }
        if (target_chara_index)
        {
            quest.target_chara_index = *target_chara_index;
            quest.target_item_id = *target_item_id;
            quest.originating_map_id = game()->current_map;
            rewardfix = 60;
            quest.reward_item_id = 5;
            quest.id = 1011;
            quest.escort_difficulty = 0;
            quest.deadline_days = rnd(3) + 2;
            quest.difficulty = cdata[*target_chara_index].level / 3;
            return true;
        }
        else
        {
            return false;
        }
    }

    if (cdata.player().fame >= 30000)
    {
        if (rnd(13) == 0)
        {
            quest.difficulty = rnd_capped(cdata.player().level + 10) +
                rnd_capped(cdata.player().fame / 2500 + 1);
            quest.difficulty =
                roundmargin(quest.difficulty, cdata.player().level);
            const auto min_level = clamp(quest.difficulty / 7, 5, 30);
            for (int _i = 0; _i < 50; ++_i)
            {
                flt(quest.difficulty, Quality::good);
                const auto chara = chara_create(56, "", -3, 0);
                if (cmshade)
                {
                    continue;
                }
                if (chara->level < min_level)
                {
                    continue;
                }
                break;
            }
            quest.extra_info_1 =
                the_character_db.ensure(cdata.tmp().id).integer_id;
            quest.refresh_time =
                game_now() + time::Duration::from_days(rnd(6) + 2) + 1_hour;
            quest.reward_item_id = 0;
            quest.id = 1010;
            quest.escort_difficulty = 0;
            quest.reward_item_id = 5;
            quest.deadline_days = -1;
            rewardfix = 140;
            return true;
        }
    }

    if (cdata.player().fame >= 50000)
    {
        if (rnd(20) == 0)
        {
            quest.difficulty = rnd_capped(cdata.player().level + 10) +
                rnd_capped(cdata.player().fame / 2500 + 1);
            quest.difficulty =
                roundmargin(quest.difficulty, cdata.player().level);
            const auto min_level = clamp(quest.difficulty / 4, 5, 30);
            for (int _i = 0; _i < 50; ++_i)
            {
                flt(quest.difficulty, Quality::good);
                const auto chara = chara_create(56, "", -3, 0);
                if (cmshade)
                {
                    continue;
                }
                if (chara->level < min_level)
                {
                    continue;
                }
                break;
            }
            quest.extra_info_1 =
                the_character_db.ensure(cdata.tmp().id).integer_id;
            quest.refresh_time =
                game_now() + time::Duration::from_days(rnd(6) + 2) + 1_hour;
            quest.reward_item_id = 0;
            quest.id = 1008;
            quest.escort_difficulty = 0;
            quest.reward_item_id = 1;
            quest.deadline_days = -1;
            rewardfix = 175;
            return true;
        }
    }

    if (rnd(11) == 0)
    {
        quest.refresh_time =
            game_now() + time::Duration::from_days(rnd(6) + 2) + 1_hour;
        quest.id = 1007;
        quest.escort_difficulty = rnd(3);
        quest.target_chara_index = 0;
        quest.reward_item_id = 5;
        while (true)
        {
            quest.extra_info_1 = choice(asettown);
            if (quest.extra_info_1 != game()->current_map)
            {
                break;
            }
        }
        const auto destination_map = quest.extra_info_1;
        if (quest.escort_difficulty == 0)
        {
            rewardfix = 140 +
                dist(
                    area_data[game()->current_map].position,
                    area_data[destination_map].position) *
                    2;
            quest.deadline_days = rnd(8) + 6;
            quest.difficulty = clamp(
                rnd_capped(cdata.player().level + 10) +
                    rnd_capped(cdata.player().fame / 500 + 1) + 1,
                1,
                80);
        }
        if (quest.escort_difficulty == 1)
        {
            rewardfix = 130 +
                dist(
                    area_data[game()->current_map].position,
                    area_data[destination_map].position) *
                    2;
            quest.deadline_days = rnd(5) + 2;
            quest.difficulty = clamp(rewardfix / 10 + 1, 1, 40);
        }
        if (quest.escort_difficulty == 2)
        {
            rewardfix = 80 +
                dist(
                    area_data[game()->current_map].position,
                    area_data[destination_map].position) *
                    2;
            quest.deadline_days = rnd(8) + 6;
            quest.difficulty = clamp(rewardfix / 20 + 1, 1, 40);
        }
        if (quest.extra_info_1 == 33 ||
            game()->current_map == mdata_t::MapId::noyel)
        {
            rewardfix = rewardfix * 180 / 100;
        }
        return true;
    }

    if (rnd(23) == 0 ||
        (game()->current_map == mdata_t::MapId::palmia && rnd(8) == 0))
    {
        quest.difficulty = clamp(
            lua_int{rnd_capped(
                cdata.player().skills().level("core.performer") + 10)},
            lua_int(
                1.5 *
                std::sqrt(cdata.player().skills().level("core.performer"))) +
                1,
            cdata.player().fame / 1000 + 10);
        quest.refresh_time =
            game_now() + time::Duration::from_days(rnd(6) + 2) + 1_hour;
        quest.reward_item_id = 0;
        quest.id = 1009;
        quest.escort_difficulty = 0;
        quest.reward_item_id = 0;
        quest.extra_info_1 = quest.difficulty * 10 + rnd(50);
        quest.extra_info_2 = 0;
        quest.deadline_days = -1;
        rewardfix = 0;
        return true;
    }

    if (rnd(30) == 0 ||
        (game()->current_map == mdata_t::MapId::yowyn && rnd(2) == 0))
    {
        quest.difficulty = clamp(
            rnd_capped(cdata.player().level + 5) +
                rnd_capped(cdata.player().fame / 800 + 1) + 1,
            1,
            50);
        quest.refresh_time =
            game_now() + time::Duration::from_days(rnd(6) + 2) + 1_hour;
        quest.id = 1006;
        quest.escort_difficulty = 0;
        quest.reward_item_id = 5;
        quest.deadline_days = -1;
        quest.extra_info_1 = 15000 + quest.difficulty * 2500;
        quest.extra_info_2 = 0;
        rewardfix = 60 + quest.difficulty * 2;
        return true;
    }

    if (rnd(8) == 0)
    {
        quest.difficulty = clamp(
            rnd_capped(cdata.player().level + 10) +
                rnd_capped(cdata.player().fame / 500 + 1) + 1,
            1,
            80);
        quest.difficulty = roundmargin(quest.difficulty, cdata.player().level);
        quest.refresh_time =
            game_now() + time::Duration::from_days(rnd(6) + 2) + 1_hour;
        quest.reward_item_id = 0;
        quest.id = 1001;
        quest.escort_difficulty = 0;
        quest.reward_item_id = 1;
        quest.deadline_days = -1;
        rewardfix = 135;
        return true;
    }

    if (rnd(6) == 0)
    {
        int i = -1;
        for (int cnt = 0, cnt_end = (game()->number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            int p = rnd(game()->number_of_existing_quests);
            for (int cnt = 0, cnt_end = (game()->number_of_existing_quests);
                 cnt < cnt_end;
                 ++cnt)
            {
                if (quest_data[cnt].id == 1002)
                {
                    if (quest_data[cnt].target_chara_index == p)
                    {
                        p = -1;
                        break;
                    }
                }
            }
            if (p == -1)
            {
                continue;
            }
            if (quest_data[p].client_chara_index != 0)
            {
                if (quest_data[p].originating_map_id != game()->current_map)
                {
                    i = p;
                    break;
                }
            }
        }
        if (i != -1)
        {
            int p = quest_data[i].originating_map_id;
            rewardfix = 70 +
                dist(
                    area_data[game()->current_map].position,
                    area_data[p].position) *
                    2;
            if (p == 33 || game()->current_map == mdata_t::MapId::noyel)
            {
                rewardfix = rewardfix * 175 / 100;
            }
            quest.target_chara_index = i;
            flt();
            flttypemajor = choice(fsetdeliver);
            quest.extra_info_1 = flttypemajor;
            quest.reward_item_id = 5;
            if (flttypemajor == 54000)
            {
                quest.reward_item_id = 2;
            }
            if (flttypemajor == 77000)
            {
                quest.reward_item_id = 3;
            }
            if (flttypemajor == 64000)
            {
                quest.reward_item_id = 77000;
            }
            if (flttypemajor == 60000)
            {
                quest.reward_item_id = 60000;
            }
            quest.target_item_id = get_random_item_id();
            quest.id = 1002;
            quest.escort_difficulty = 0;
            quest.deadline_days = rnd(12) + 3;
            quest.difficulty = clamp(rewardfix / 20 + 1, 1, 25);
            return true;
        }
        else
        {
            return false;
        }
    }

    if (rnd(6) == 0)
    {
        quest.id = 1003;
        quest.deadline_days = rnd(6) + 2;
        quest.reward_item_id = 5;
        quest.extra_info_1 = rnd(8) + 1;
        if (quest.extra_info_1 == 4)
        {
            quest.reward_item_id = 52000;
        }
        if (quest.extra_info_1 == 6)
        {
            quest.reward_item_id = 25000;
        }
        if (quest.extra_info_1 == 1)
        {
            quest.reward_item_id = 25000;
        }
        if (quest.extra_info_1 == 5)
        {
            quest.reward_item_id = 52000;
        }
        if (quest.extra_info_1 == 7)
        {
            quest.reward_item_id = 77000;
        }
        if (quest.extra_info_1 == 2)
        {
            quest.reward_item_id = 56000;
        }
        if (quest.extra_info_1 == 3)
        {
            quest.reward_item_id = 53000;
        }
        quest.extra_info_2 = rnd(7) + 3;
        quest.difficulty = quest.extra_info_2 * 3;
        rewardfix = 60 + quest.difficulty;
        return true;
    }

    if (rnd(5) == 0)
    {
        quest.id = 1004;
        quest.deadline_days = rnd(6) + 2;
        flt();
        flttypemajor = choice(fsetsupply);
        quest.reward_item_id = 5;
        quest.target_item_id = get_random_item_id();
        quest.difficulty =
            clamp(rnd_capped(cdata.player().level + 5) + 1, 1, 30);
        rewardfix = 65 + quest.difficulty;
        return true;
    }

    return false;
}



void quest_check_all_for_failed()
{
    for (int cnt = 0, cnt_end = (game()->number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (quest_data[cnt].id == 0)
        {
            continue;
        }
        if (quest_data[cnt].progress != 1)
        {
            continue;
        }
        if (quest_data[cnt].deadline_days < 0)
        {
            continue;
        }
        --quest_data[cnt].deadline_days;
        if (quest_data[cnt].deadline_days == 0)
        {
            quest_failed(cnt, quest_data[cnt].id);
        }
    }
}



void quest_enter_map()
{
    if (game()->executing_immediate_quest_type == 1009)
    {
        txt(i18n::s.get(
                "core.map.quest.on_enter.party",
                game()->left_minutes_of_executing_quest,
                quest_data.immediate().extra_info_1),
            Message::color{ColorIndex::cyan});
    }
    if (game()->executing_immediate_quest_type == 1006)
    {
        if (quest_data.immediate().extra_info_1 <= 0)
        {
            quest_data.immediate().extra_info_1 = 15000;
            quest_data.immediate().reward_gold = 400;
        }
        txt(i18n::s.get(
                "core.map.quest.on_enter.harvest",
                cnvweight(quest_data.immediate().extra_info_1),
                game()->left_minutes_of_executing_quest),
            Message::color{ColorIndex::cyan});
    }
    if (game()->executing_immediate_quest_type == 1008)
    {
        txt(i18n::s.get(
                "core.map.quest.on_enter.conquer",
                chara_db_get_name(*the_character_db.get_id_from_integer(
                    quest_data.immediate().extra_info_1)),
                game()->left_minutes_of_executing_quest),
            Message::color{ColorIndex::cyan});
    }
}



void quest_exit_map()
{
    if (game()->executing_immediate_quest_type == 1006)
    {
        for (const auto& item : *inv_player())
        {
            if (item->own_state == OwnState::crop)
            {
                item->remove();
            }
        }
        refresh_burden_state();
    }
    if (game()->executing_immediate_quest_status != 3)
    {
        optional<int> quest_idx;
        if (game()->executing_immediate_quest_type >= 1000)
        {
            quest_idx = game()->executing_immediate_quest;
        }
        if (game()->executing_immediate_quest_type == 1007)
        {
            assert(quest_idx);
            if (quest_data[*quest_idx].progress == 0)
            {
                game()->executing_immediate_quest_type = 0;
                game()->executing_immediate_quest_show_hunt_remain = 0;
                game()->executing_immediate_quest = 0;
                game()->executing_immediate_quest_status = 0;
                return;
            }
            else
            {
                txt(i18n::s.get("core.quest.escort.you_left_your_client"));
            }
        }
        quest_failed(quest_idx, game()->executing_immediate_quest_type);
        msg_halt();
    }
    game()->executing_immediate_quest_type = 0;
    game()->executing_immediate_quest_show_hunt_remain = 0;
    game()->executing_immediate_quest = 0;
    game()->executing_immediate_quest_status = 0;
}



TurnResult quest_pc_died_during_immediate_quest()
{
    revive_player(cdata.player());
    chara_gain_skill_exp(cdata.player(), 17, -500);
    chara_gain_skill_exp(cdata.player(), 15, -500);
    levelexitby = 4;
    game()->current_dungeon_level = 0;
    return TurnResult::exit_map;
}



void quest_failed(optional<int> quest_idx, int val0)
{
    if (val0 == 1)
    {
        area_data[game()->previous_map2].winning_streak_in_arena = 0;
        txt(i18n::s.get("core.quest.you_were_defeated"));
        modrank(0, -100);
    }
    if (val0 >= 1000)
    {
        assert(quest_idx);
        auto& quest = quest_data[*quest_idx];

        txt(i18n::s.get("core.quest.failed_taken_from", qname(*quest_idx)));
        if (quest.id == 1002)
        {
            --quest_data[quest.target_chara_index].delivery_has_package_flag;
            txt(i18n::s.get("core.quest.deliver.you_commit_a_serious_crime"),
                Message::color{ColorIndex::purple});
            modify_karma(cdata.player(), -20);
        }
        if (quest.id == 1007)
        {
            txt(i18n::s.get("core.quest.escort.you_failed_to_protect"),
                Message::color{ColorIndex::purple});
            for (auto&& ally : cdata.allies())
            {
                if (ally.is_escorted() &&
                    quest.extra_info_2 ==
                        the_character_db.ensure(ally.id).integer_id)
                {
                    ally.is_escorted() = false;
                    if (ally.state() == Character::State::alive)
                    {
                        if (quest.escort_difficulty == 0)
                        {
                            s = i18n::s.get(
                                "core.quest.escort.failed.assassin");
                            p = -11;
                        }
                        if (quest.escort_difficulty == 1)
                        {
                            s = i18n::s.get("core.quest.escort.failed.poison");
                            p = -4;
                        }
                        if (quest.escort_difficulty == 2)
                        {
                            s = i18n::s.get(
                                "core.quest.escort.failed.deadline", ally);
                            mef_add(
                                cdata.player().position.x,
                                cdata.player().position.y,
                                5,
                                24,
                                rnd(15) + 25,
                                efp,
                                0);
                            mapitem_fire(
                                cdata.player(),
                                ally.position.x,
                                ally.position.y);
                            p = -9;
                        }
                        txt(s, Message::color{ColorIndex::cyan});
                        damage_hp(ally, 999999, p);
                    }
                    ally.set_state(Character::State::empty);
                    break;
                }
            }
            modify_karma(cdata.player(), -10);
        }
        quest.id = 0;
        quest.progress = 0;
    }
    int stat = decrease_fame(cdata.player(), 40);
    p = stat;
    txt(i18n::s.get("core.quest.lose_fame", p(0)),
        Message::color{ColorIndex::red});
}



void quest_team_victorious()
{
    for (auto&& ally : cdata.player_and_allies())
    {
        if (followerin(ally.index) == 0)
        {
            continue;
        }
        if (ally.hp < ally.max_hp / 2)
        {
            ally.hp = ally.max_hp / 2;
        }
    }
    snd("core.cheer");
    if (petarenawin == 1)
    {
        txt(i18n::s.get("core.quest.arena.your_team_is_victorious"),
            Message::color{ColorIndex::green});
        txt(i18n::s.get(
                "core.quest.gain_fame",
                game()->executing_immediate_quest_fame_gained),
            Message::color{ColorIndex::green});
        cdata.player().fame += game()->executing_immediate_quest_fame_gained;
        modrank(1, 100, 2);
        ++area_data[game()->previous_map2].winning_streak_in_pet_arena;
        if (area_data[game()->previous_map2].winning_streak_in_pet_arena % 20 ==
            0)
        {
            crafting_material_gain("core.five_hundred_yen_coin", 1);
        }
        else if (
            area_data[game()->previous_map2].winning_streak_in_pet_arena % 5 ==
            0)
        {
            crafting_material_gain("core.one_hundred_yen_coin", 1);
        }
    }
    else
    {
        txt(i18n::s.get("core.quest.arena.your_team_is_defeated"),
            Message::color{ColorIndex::purple});
        area_data[game()->previous_map2].winning_streak_in_pet_arena = 0;
        modrank(1, -100);
        int stat = decrease_fame(cdata.player(), 60);
        p = stat;
        if (arenaop == 0)
        {
            txt(i18n::s.get("core.quest.lose_fame", p(0)),
                Message::color{ColorIndex::red});
        }
    }
}



void quest_all_targets_killed()
{
    play_music("core.mcFanfare", false);
    game()->executing_immediate_quest_status = 3;
    if (game()->executing_immediate_quest_type == 1)
    {
        snd("core.cheer");
        txt(i18n::s.get("core.quest.arena.you_are_victorious"),
            Message::color{ColorIndex::green});
        txt(i18n::s.get(
                "core.quest.gain_fame",
                game()->executing_immediate_quest_fame_gained),
            Message::color{ColorIndex::green});
        modrank(0, 100, 2);
        cdata.player().fame += game()->executing_immediate_quest_fame_gained;
        txt(i18n::s.get("core.quest.arena.stairs_appear"));
        map_place_upstairs(map_data.width / 2, map_data.height / 2);
        ++area_data[game()->previous_map2].winning_streak_in_arena;
        if (area_data[game()->previous_map2].winning_streak_in_arena % 20 == 0)
        {
            crafting_material_gain("core.five_hundred_yen_coin", 1);
        }
        else if (
            area_data[game()->previous_map2].winning_streak_in_arena % 5 == 0)
        {
            crafting_material_gain("core.one_hundred_yen_coin", 1);
        }
    }
    if (game()->executing_immediate_quest_type == 1001 ||
        game()->executing_immediate_quest_type == 1010)
    {
        quest_data.immediate().progress = 3;
        txt(i18n::s.get("core.quest.hunt.complete"),
            Message::color{ColorIndex::green});
    }
    if (game()->executing_immediate_quest_type == 1007)
    {
        txt(i18n::s.get("core.quest.hunt.complete"),
            Message::color{ColorIndex::green});
    }
    if (game()->executing_immediate_quest_type == 1008)
    {
        game()->left_minutes_of_executing_quest = 0;
        quest_data.immediate().progress = 3;
        txt(i18n::s.get("core.quest.conquer.complete"),
            Message::color{ColorIndex::green});
    }
}



void quest_complete(int quest_idx)
{
    auto& quest = quest_data[quest_idx];

    snd("core.complete1");
    p = quest.reward_gold;
    if (quest.id == 1006)
    {
        if (quest.extra_info_1 != 0)
        {
            if (quest.extra_info_1 * 125 / 100 < quest.extra_info_2)
            {
                p = clamp(
                    p *
                        static_cast<int>(
                            static_cast<double>(quest.extra_info_2) /
                            quest.extra_info_1),
                    p(0),
                    p * 3);
            }
        }
    }
    if (p != 0)
    {
        flt();
        itemcreate_map_inv(54, cdata.player().position, p);
    }
    if (quest.id == 1002)
    {
        p = rnd(2) + 1;
    }
    else
    {
        p = 1;
    }
    if (quest.id == 1008 || quest.id == 1010)
    {
        p = 2 + (rnd(100) < rnd_capped(cdata.player().fame / 5000 + 1));
    }
    flt();
    itemcreate_map_inv(55, cdata.player().position, p);
    if (quest.id == 1009)
    {
        if (quest.extra_info_1 * 150 / 100 < quest.extra_info_2)
        {
            flt();
            itemcreate_map_inv(
                724, cdata.player().position, 1 + quest.extra_info_2 / 10);
        }
    }
    if (quest.reward_item_id != 0)
    {
        p = rnd(rnd(4) + 1) + 1;
        if (quest.id == 1008 || quest.id == 1010)
        {
            p += 2;
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            fixlv = Quality::good;
            if (rnd(2))
            {
                fixlv = Quality::great;
                if (rnd(12) == 0)
                {
                    fixlv = Quality::miracle;
                }
            }
            flt((quest.difficulty + cdata.player().level) / 2 + 1,
                calcfixlv(fixlv));
            if (quest.reward_item_id < 10000)
            {
                if (quest.reward_item_id == 1)
                {
                    flttypemajor = choice(fsetwear);
                }
                if (quest.reward_item_id == 2)
                {
                    flttypemajor = choice(fsetmagic);
                }
                if (quest.reward_item_id == 3)
                {
                    flttypemajor = choice(fsetarmor);
                }
                if (quest.reward_item_id == 4)
                {
                    flttypemajor = choice(fsetweapon);
                }
                if (quest.reward_item_id == 5)
                {
                    flttypemajor = choice(fsetrewardsupply);
                }
            }
            else
            {
                flttypemajor = quest.reward_item_id;
            }
            itemcreate_map_inv(0, cdata.player().position, 0);
        }
    }
    modify_karma(cdata.player(), 1);
    game()->executing_immediate_quest_fame_gained =
        calc_gained_fame(cdata.player(), quest.difficulty * 3 + 10);
    txt(i18n::s.get("core.quest.completed_taken_from", qname(quest_idx)),
        Message::color{ColorIndex::green});
    txt(i18n::s.get(
            "core.quest.gain_fame",
            game()->executing_immediate_quest_fame_gained),
        Message::color{ColorIndex::green});
    cdata.player().fame += game()->executing_immediate_quest_fame_gained;
    txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
    if (quest.id == 1002)
    {
        --quest_data[quest.target_chara_index].delivery_has_package_flag;
    }
    quest.id = 0;
    quest.progress = 0;
    save_trigger_autosaving();
}

} // namespace elona
