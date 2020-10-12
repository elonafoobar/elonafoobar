#include "game_clock.hpp"

#include "adventurer.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "character.hpp"
#include "draw.hpp"
#include "food.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random_event.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

// See world.cpp
extern elona_vector1<int> ranknorma;



namespace
{

void on_minute_changed(lua_int elapsed_minutes)
{
    ++game()->play_turns;
    if (game()->play_turns % 20 == 0)
    {
        monster_respawn();
    }
    if (game()->play_turns % 10 == 1)
    {
        auto_identify();
    }
    if (game()->left_minutes_of_executing_quest > 0)
    {
        const auto previous_left_minutes =
            game()->left_minutes_of_executing_quest;
        game()->left_minutes_of_executing_quest -= elapsed_minutes;
        if (previous_left_minutes / 10 !=
            game()->left_minutes_of_executing_quest / 10)
        {
            txt(i18n::s.get(
                    "core.quest.minutes_left",
                    (game()->left_minutes_of_executing_quest + 1)),
                Message::color{ColorIndex::cyan});
        }
        if (game()->left_minutes_of_executing_quest <= 0)
        {
            game()->left_minutes_of_executing_quest = 0;
            deferred_event_add("core.quest_time_is_up");
        }
    }
}



void on_hour_changed(
    lua_int elapsed_hours,
    lua_int elapsed_days,
    lua_int elapsed_months,
    lua_int elapsed_years)
{
    (void)elapsed_hours;

    if (area_data[game()->current_map].id == mdata_t::MapId::museum)
    {
        update_museum();
    }
    if (game()->current_map == mdata_t::MapId::your_home)
    {
        building_update_home_rank();
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        game()->pc_x_in_world_map = cdata.player().position.x;
        game()->pc_y_in_world_map = cdata.player().position.y;
    }
    --game()->weather_change_count;
    weather_changes_by_location();
    if (game()->weather_change_count < 0)
    {
        const auto changed = weather_changes();
        if (game()->weather == "core.hard_rain")
        {
            maybe_show_ex_help(11);
        }
        if (game()->weather == "core.snow")
        {
            maybe_show_ex_help(12);
        }
        if (game()->weather == "core.etherwind")
        {
            maybe_show_ex_help(13);
        }
        if (changed)
        {
            sound_play_environmental();
        }
    }
    draw_prepare_map_chips();
    adventurer_update();
    foods_get_rotten();
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (rnd(3) == 0)
        {
            ++game()->continuous_active_hours;
        }
        if (rnd(15) == 0)
        {
            if (mode == 0)
            {
                txt(i18n::s.get("core.action.move.global.nap"));
                game()->continuous_active_hours -= 3;
                if (game()->continuous_active_hours < 0)
                {
                    game()->continuous_active_hours = 0;
                }
            }
        }
    }
    else if (game()->current_map != mdata_t::MapId::shelter_)
    {
        ++game()->continuous_active_hours;
    }

    const auto date_time = game_date_time();
    if (date_time.hour() == 6)
    {
        txt(i18n::s.get("core.action.day_breaks"),
            Message::color{ColorIndex::orange});
    }
    if (game()->continuous_active_hours >= 15)
    {
        maybe_show_ex_help(9);
    }
    if (cdata.player().nutrition < 5000)
    {
        maybe_show_ex_help(10);
    }

    if (elapsed_days > 0)
    {
        if (game()->number_of_waiting_guests < 3)
        {
            if (rnd(8 + game()->number_of_waiting_guests * 5) == 0)
            {
                ++game()->number_of_waiting_guests;
            }
        }
        txt(i18n::s.get("core.action.new_day"),
            Message::color{ColorIndex::orange});
        update_shop_and_report();
        for (int rank_id = 0; rank_id < 9; ++rank_id)
        {
            if (game()->ranks.at(rank_id) >= 10000)
            {
                game()->ranks.at(rank_id) = 10000;
                continue;
            }
            if (rank_id == 3 || rank_id == 4 || rank_id == 5 || rank_id == 8)
            {
                continue;
            }
            --game()->rank_deadlines.at(rank_id);
            if (game()->rank_deadlines.at(rank_id) <= 0)
            {
                modrank(rank_id, (game()->ranks.at(rank_id) / 12 + 100) * -1);
                game()->rank_deadlines.at(rank_id) = ranknorma(rank_id);
            }
        }
        snd("core.night");
        deferred_event_add("core.quest_update_deadline");
        game()->play_days += elapsed_days;
        if (elapsed_months > 0)
        {
            if (date_time.month() % 2 == 0)
            {
                ++game()->holy_well_amount;
            }
        }
        if (elapsed_years > 0)
        {
            game()->wish_count = clamp(game()->wish_count - 1, 0, 10);
            game()->lost_wallet_count =
                clamp(game()->lost_wallet_count - 1, 0, 999999);
        }
        if (date_time.day() == 1 || date_time.day() == 15)
        {
            supply_income();
        }
        if (story_quest_progress("core.pael_and_her_mom") == 1 ||
            story_quest_progress("core.pael_and_her_mom") == 3 ||
            story_quest_progress("core.pael_and_her_mom") == 5 ||
            story_quest_progress("core.pael_and_her_mom") == 7 ||
            story_quest_progress("core.pael_and_her_mom") == 9)
        {
            if (area_data[game()->current_map].id != mdata_t::MapId::noyel)
            {
                if (rnd(20) == 0)
                {
                    story_quest_add_progress("core.pael_and_her_mom", 1);
                    quest_update_journal_msg();
                }
            }
        }
    }

    if (mode == 0)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            if (rnd(40) == 0)
            {
                --cdata.player().piety_point;
            }
            cdata.player().prayer_point += 4;
        }
        else
        {
            if (rnd(5) == 0)
            {
                --cdata.player().piety_point;
            }
            cdata.player().prayer_point += 32;
        }
    }
    if (cdata.player().piety_point < 0)
    {
        cdata.player().piety_point = 0;
    }
    if (cdata.player().activity.turns != 0)
    {
        if (cdata.player().activity.id != "core.travel")
        {
            update_screen();
        }
    }
    if (!map_prevents_random_events())
    {
        proc_random_event();
    }
}

} // namespace



void game_advance_clock(
    time::Duration elapsed_time,
    GameAdvanceClockEvents triggered_events)
{
    const auto prev_date_time = game_date_time();
    game()->universal_clock.advance(elapsed_time);

    if (triggered_events == GameAdvanceClockEvents::none)
        return;

    const lua_int m0 = prev_date_time.month();
    const lua_int d0 = prev_date_time.day();
    const lua_int h0 = prev_date_time.hour();
    const lua_int min0 = prev_date_time.minute();
    const lua_int s0 = prev_date_time.second();
    const lua_int ms0 = prev_date_time.millisecond();

    const auto elapsed_seconds = (ms0 + elapsed_time.milliseconds()) / 1000;
    const auto elapsed_minutes = (s0 + elapsed_seconds) / 60;
    const auto elapsed_hours = (min0 + elapsed_minutes) / 60;
    const auto elapsed_days = (h0 + elapsed_hours) / 24;
    const auto elapsed_months = (d0 + elapsed_days) / 30;
    const auto elapsed_years = (m0 + elapsed_months) / 12;

    if (elapsed_minutes > 0)
    {
        if ((triggered_events & GameAdvanceClockEvents::on_minute_changed) !=
            GameAdvanceClockEvents::none)
        {
            on_minute_changed(elapsed_minutes);
        }

        if (elapsed_hours > 0)
        {
            if ((triggered_events & GameAdvanceClockEvents::on_hour_changed) !=
                GameAdvanceClockEvents::none)
            {
                on_hour_changed(
                    elapsed_hours, elapsed_days, elapsed_months, elapsed_years);
            }
        }
    }
}

} // namespace elona
