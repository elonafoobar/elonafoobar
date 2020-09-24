#include "world.hpp"

#include "adventurer.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "character.hpp"
#include "deferred_event.hpp"
#include "draw.hpp"
#include "food.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "i18n.hpp"
#include "initialize_map.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "random_event.hpp"
#include "save.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

elona_vector1<int> ranknorma;



void weather_changes_by_location(bool output_immediately)
{
    if (game()->weather == "core.snow")
    {
        if (game()->pc_x_in_world_map < 65 && game()->pc_y_in_world_map > 10)
        {
            game()->weather = "core.rain";
            sound_play_environmental();
            game()->weather_change_count += 3;
            if (output_immediately)
            {
                txt(i18n::s.get("core.action.weather.changes"));
            }
            else
            {
                Message::instance().buffered_message_append(
                    i18n::s.get("core.action.weather.changes"));
            }
        }
    }
    if (game()->weather == "core.hard_rain" || game()->weather == "core.rain")
    {
        if (game()->pc_x_in_world_map > 65 || game()->pc_y_in_world_map < 10)
        {
            game()->weather = "core.snow";
            sound_play_environmental();
            game()->weather_change_count += 3;
            if (output_immediately)
            {
                txt(i18n::s.get("core.action.weather.changes"));
            }
            else
            {
                Message::instance().buffered_message_append(
                    i18n::s.get("core.action.weather.changes"));
            }
        }
    }
}



void weather_changes()
{
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
        game()->weather_change_count = rnd(22) + 2;
        const auto prev_weather = game()->weather;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (game()->date.month % 3 == 0)
            {
                if (game()->date.day >= 1 && game()->date.day <= 10)
                {
                    if (game()->last_etherwind_month != game()->date.month)
                    {
                        if (rnd(15) < game()->date.day + 5)
                        {
                            game()->weather = "core.etherwind";
                            txt(i18n::s.get(
                                    "core.action.weather.ether_wind.starts"),
                                Message::color{ColorIndex::red});
                            game()->last_etherwind_month = game()->date.month;
                            game()->weather_change_count = rnd(24) + 24;
                            break;
                        }
                    }
                }
            }
            if (prev_weather == "core.sunny")
            {
                g_prev_weather = "";
                if (cdata.player().traits().level("core.rainy_clouds") != 0)
                {
                    if (rnd(4) == 0)
                    {
                        game()->weather = "core.rain";
                        txt(i18n::s.get("core.action.weather.rain.draw_cloud"));
                        break;
                    }
                }
                if (game()->pc_x_in_world_map > 65 ||
                    game()->pc_y_in_world_map < 10)
                {
                    if (rnd(2) == 0)
                    {
                        game()->weather = "core.snow";
                        txt(i18n::s.get("core.action.weather.snow.starts"));
                        break;
                    }
                }
                else
                {
                    if (rnd(10) == 0)
                    {
                        game()->weather = "core.rain";
                        txt(i18n::s.get("core.action.weather.rain.starts"));
                        break;
                    }
                    if (rnd(40) == 0)
                    {
                        game()->weather = "core.hard_rain";
                        txt(i18n::s.get(
                            "core.action.weather.rain.starts_heavy"));
                        break;
                    }
                    if (rnd(60) == 0)
                    {
                        game()->weather = "core.snow";
                        txt(i18n::s.get("core.action.weather.snow.starts"));
                        break;
                    }
                }
            }
            if (prev_weather == "core.rain")
            {
                if (rnd(4) == 0)
                {
                    game()->weather = "core.sunny";
                    txt(i18n::s.get("core.action.weather.rain.stops"));
                    break;
                }
                if (rnd(15) == 0)
                {
                    game()->weather = "core.hard_rain";
                    txt(i18n::s.get(
                        "core.action.weather.rain.becomes_heavier"));
                    break;
                }
            }
            if (prev_weather == "core.hard_rain")
            {
                if (rnd(3) == 0)
                {
                    game()->weather = "core.rain";
                    txt(i18n::s.get(
                        "core.action.weather.rain.becomes_lighter"));
                    break;
                }
            }
            if (prev_weather == "core.etherwind")
            {
                if (rnd(2) == 0)
                {
                    game()->weather = "core.sunny";
                    txt(i18n::s.get("core.action.weather.ether_wind.stops"));
                    break;
                }
            }
            if (prev_weather == "core.snow")
            {
                if (rnd(3) == 0)
                {
                    game()->weather = "core.sunny";
                    txt(i18n::s.get("core.action.weather.snow.stops"));
                    break;
                }
            }
        }
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
        if (prev_weather != game()->weather)
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
    if (game()->date.hour == 6)
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
    if (game()->date.hour >= 24)
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
        event_add(10);
        game()->play_days += game()->date.hour / 24;
        game()->date.day += game()->date.hour / 24;
        game()->date.hour = game()->date.hour % 24;
        if (game()->date.day >= 31)
        {
            ++game()->date.month;
            game()->date.day = game()->date.day - 30;
            if (game()->date.month % 2 == 0)
            {
                ++game()->holy_well_count;
            }
        }
        if (game()->date.month >= 13)
        {
            ++game()->date.year;
            game()->date.month = 1;
            game()->last_month_when_trainer_visited = 0;
            game()->wish_count = clamp(game()->wish_count - 1, 0, 10);
            game()->lost_wallet_count =
                clamp(game()->lost_wallet_count - 1, 0, 999999);
        }
        if (game()->date.day == 1 || game()->date.day == 15)
        {
            supply_income();
        }
        if (game()->quest_flags.pael_and_her_mom == 1 ||
            game()->quest_flags.pael_and_her_mom == 3 ||
            game()->quest_flags.pael_and_her_mom == 5 ||
            game()->quest_flags.pael_and_her_mom == 7 ||
            game()->quest_flags.pael_and_her_mom == 9)
        {
            if (area_data[game()->current_map].id != mdata_t::MapId::noyel)
            {
                if (rnd(20) == 0)
                {
                    ++game()->quest_flags.pael_and_her_mom;
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
            cdata.player().praying_point += 4;
        }
        else
        {
            if (rnd(5) == 0)
            {
                --cdata.player().piety_point;
            }
            cdata.player().praying_point += 32;
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



void initialize_building_data()
{
    DIM4(bddata, 40, 20, 10);
    DIM3(bdref, 10, 7);
    bdref(0, 1) = 0;
    bdref(1, 1) = 1500;
    bdref(0, 2) = 1;
    bdref(1, 2) = 2500;
    bdref(0, 3) = 2;
    bdref(1, 3) = 2500;
    bdref(0, 4) = 3;
    bdref(1, 4) = 2500;
    bdref(0, 5) = 4;
    bdref(1, 5) = 2500;
    bdref(0, 6) = 5;
    bdref(1, 6) = 2500;
}



void initialize_economy()
{
    elona_vector1<int> bkdata;
    if (initeco)
    {
        game()->politics_map_id = static_cast<int>(mdata_t::MapId::palmia);
    }
    bkdata(0) = game()->current_map;
    bkdata(1) = game()->current_dungeon_level;
    bkdata(2) = cdata.player().position.x;
    bkdata(3) = cdata.player().position.y;
    save_save_game(save_game_no_message);
    mode = 11;
    cdata.player().position.x = 0;
    cdata.player().position.y = 0;
    scx = cdata.player().position.x;
    scy = cdata.player().position.y;
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none)
        {
            continue;
        }
        if (area_data[cnt].quest_town_id == 0)
        {
            continue;
        }
        game()->current_map = area_data[cnt].id;
        game()->current_dungeon_level = 1;
        if (game()->current_map != bkdata(0) ||
            game()->current_dungeon_level != bkdata(1))
        {
            initialize_map();
        }
        p = area_data[cnt].quest_town_id;
        if (initeco)
        {
            if (p == 1)
            {
                podata(100, p) = 1500 + rnd(200);
                podata(101, p) = 0;
                addbuilding(p, 1, 27, 22);
                addbuilding(p, 1, 28, 23);
            }
            if (p == 2)
            {
                podata(100, p) = 80 + rnd(20);
                podata(101, p) = 0;
                addbuilding(p, 2, 42, 31);
                addbuilding(p, 2, 43, 33);
            }
            if (p == 3)
            {
                podata(100, p) = 6500 + rnd(500);
                podata(101, p) = 0;
            }
            if (p == 4)
            {
                podata(100, p) = 1100 + rnd(150);
                podata(101, p) = 0;
                addbuilding(p, 5, 12, 34);
            }
            if (p == 5)
            {
                podata(100, p) = 3500 + rnd(300);
                podata(101, p) = 0;
                addbuilding(p, 6, 4, 16);
            }
            if (p == 6)
            {
                podata(100, p) = 800 + rnd(200);
                podata(101, p) = 0;
            }
            if (p == 7)
            {
                podata(100, p) = 2600 + rnd(300);
                podata(101, p) = 0;
                addbuilding(p, 3, 60, 33);
            }
            podata(200, p) = podata(100, p) * 5 + rnd(1000);
        }
        save_save_map_local_data();
    }
    game()->current_map = bkdata(0);
    game()->current_dungeon_level = bkdata(1);
    cdata.player().position.x = bkdata(2);
    cdata.player().position.y = bkdata(3);
    game()->reset_world_map_in_diastrophism_flag = 1;
    mode = 3;
    mapsubroutine = 1;
    initialize_map();
    initeco = 0;
}



int initialize_world_map()
{
    p = 0;
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::random_dungeon)
        {
            if (area_data[cnt].has_been_conquered != -1)
            {
                ++p;
            }
        }
    }
    p = 40 - p;
    if (p < 1)
    {
        p = 1;
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        cxinit = rnd(map_data.width);
        cyinit = rnd(map_data.height);
        map_global_place_random_nefias();
    }
    map_global_prepare();
    return 1;
}



void modrank(int rank_id, int amount, int min)
{
    int rank_factor = game()->ranks.at(rank_id) / 100;
    int orgrank_at_m75 = game()->ranks.at(rank_id);
    int i_at_m75 = amount;
    if (amount > 0)
    {
        i_at_m75 = amount * (rank_factor + 20) * (rank_factor + 20) / 2500;
        game()->rank_deadlines.at(rank_id) = ranknorma(rank_id);
        if (game()->ranks.at(rank_id) == 100)
        {
            return;
        }
        if (min != 0)
        {
            if (i_at_m75 / 100 > min)
            {
                i_at_m75 = min * 100;
            }
        }
    }
    game()->ranks.at(rank_id) -= i_at_m75;
    if (game()->ranks.at(rank_id) >= 10000)
    {
        game()->ranks.at(rank_id) = 10000;
    }
    if (game()->ranks.at(rank_id) < 100)
    {
        game()->ranks.at(rank_id) = 100;
    }
    if (orgrank_at_m75 / 100 != game()->ranks.at(rank_id) / 100)
    {
        i_at_m75 = game()->ranks.at(rank_id) / 100 - orgrank_at_m75 / 100;
        if (i_at_m75 < 0)
        {
            Message::instance().txtef(ColorIndex::green);
        }
        else
        {
            Message::instance().txtef(ColorIndex::purple);
        }
        const auto from = orgrank_at_m75 / 100;
        const auto to = game()->ranks.at(rank_id) / 100;
        txt(i18n::s.get(
            "core.misc.ranking.changed",
            rankn(10, rank_id),
            from,
            to,
            ranktitle(rank_id)));
    }
    else if (i_at_m75 > 0)
    {
        txt(i18n::s.get("core.misc.ranking.closer_to_next_rank"),
            Message::color{ColorIndex::green});
    }
}

} // namespace elona
