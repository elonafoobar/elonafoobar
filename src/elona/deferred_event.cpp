#include "deferred_event.hpp"

#include "ability.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "net.hpp"
#include "quest.hpp"
#include "random_event.hpp"
#include "save.hpp"
#include "scene.hpp"
#include "serialization/serialization.hpp"
#include "serialization/utils.hpp"
#include "talk.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

namespace
{

struct DeferredEvent
{
    int id;
    int param1;
    int param2;



    DeferredEvent(int id, int param1, int param2)
        : id(id)
        , param1(param1)
        , param2(param2)
    {
    }



    DeferredEvent() noexcept = default;
    DeferredEvent(const DeferredEvent&) noexcept = default;
    DeferredEvent(DeferredEvent&&) noexcept = default;
    DeferredEvent& operator=(const DeferredEvent&) noexcept = default;
    DeferredEvent& operator=(DeferredEvent&&) noexcept = default;



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(id);
        ar(param1);
        ar(param2);
        /* clang-format on */
    }
};



class DeferredEventQueue
{
public:
    DeferredEvent& front()
    {
        assert(!_queue.empty());
        return _queue.front();
    }



    bool empty() const noexcept
    {
        return _queue.empty();
    }



    bool has(int event_type)
    {
        return range::find_if(_queue, [=](const auto& e) {
                   return e.id == event_type;
               }) != std::end(_queue);
    }



    void enqueue(int event_type, int param1, int param2)
    {
        _queue.emplace_back(event_type, param1, param2);
    }



    void dequeue()
    {
        _queue.pop_front();
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(_queue);
        /* clang-format on */
    }



private:
    std::deque<DeferredEvent> _queue;
};



DeferredEventQueue g_event_queue;



namespace event_handlers
{

void eh_conquer_lesimas(const DeferredEvent&)
{
    conquer_lesimas();
    flt();
    chara_create(-1, 23, cdata.player().position.x, cdata.player().position.y);
}



void eh_lomias_talks(const DeferredEvent&)
{
    const auto lomias = chara_find("core.lomias");
    assert(lomias);
    talk_to_npc(*lomias);
}



void eh_zeome_talks(const DeferredEvent&)
{
    const auto zeome = chara_find("core.zeome");
    assert(zeome);
    talk_to_npc(*zeome);
}



void eh_lord_of_normal_nefia(const DeferredEvent&)
{
    optional_ref<Character> lord;
    do
    {
        map_set_chara_generation_filter();
        fixlv = Quality::miracle;
        initlv = game_data.current_dungeon_level + rnd(5);
        lord = chara_create(-1, 0, -3, 0);
    } while (!lord);
    assert(lord);

    lord->is_lord_of_dungeon() = true;
    area_data[game_data.current_map].has_been_conquered = lord->index;
    lord->name += u8" Lv"s + lord->level;
    txt(i18n::s.get("core.event.reached_deepest_level"));
    txt(i18n::s.get(
            "core.event.guarded_by_lord",
            mapname(game_data.current_map),
            *lord),
        Message::color{ColorIndex::red});
}



void eh_conquer_nefia(const DeferredEvent&)
{
    play_music("core.mcVictory");
    snd("core.complete1");
    flt(0, calcfixlv());
    flttypemajor = 54000;
    itemcreate_map_inv(0, cdata.player().position, 0);
    flt();
    itemcreate_map_inv(236, cdata.player().position, 0);
    nostack = 1;
    flt();
    if (const auto item = itemcreate_map_inv(54, cdata.player().position, 0))
    {
        item->set_number(200 + item->number() * 5);
    }
    flt();
    itemcreate_map_inv(
        55,
        cdata.player().position,
        clamp(rnd(3) + game_data.current_dungeon_level / 10, 1, 6));
    flt();
    if (const auto item = itemcreate_map_inv(239, cdata.player().position, 0))
    {
        item->param2 = 0;
    }
    txt(i18n::s.get("core.quest.completed"), Message::color{ColorIndex::green});
    snd("core.complete1");
    txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
    modrank(2, 300, 8);
    game_data.executing_immediate_quest_fame_gained = calc_gained_fame(
        cdata.player(), game_data.current_dungeon_level * 30 + 200);
    txt(i18n::s.get(
            "core.quest.gain_fame",
            game_data.executing_immediate_quest_fame_gained),
        Message::color{ColorIndex::green});
    cdata.player().fame += game_data.executing_immediate_quest_fame_gained;
    if (game_data.current_map == mdata_t::MapId::the_void)
    {
        area_data[game_data.current_map].has_been_conquered = 0;
        game_data.void_next_lord_floor = game_data.void_next_lord_floor + 5;
        txt(i18n::s.get("core.event.seal_broken"));
    }
    else
    {
        area_data[game_data.current_map].has_been_conquered = -1;
    }
}



void eh_player_died(const DeferredEvent&)
{
    if (cdata.player().level > 5)
    {
        for (int i = 10; i < 18; ++i)
        {
            if (cdata.player().get_skill(i).level != 0 && rnd(3) == 0)
            {
                chara_gain_skill_exp(cdata.player(), i, -500);
            }
        }
        if (cdata.player().karma < -30)
        {
            modify_karma(cdata.player(), 10);
        }
    }
    else
    {
        txt(i18n::s.get("core.event.death_penalty_not_applied"));
    }
    if (game_data.ether_disease_stage >= 20000)
    {
        modify_ether_disease_stage(-2000);
    }
    txt(i18n::s.get("core.event.you_lost_some_money"));
    cdata.player().gold -= cdata.player().gold / 3;
    decrease_fame(cdata.player(), 10);
    chara_refresh(cdata.player());
    save_set_autosave();
}



void eh_quest_all_target_killed(const DeferredEvent&)
{
    quest_all_targets_killed();
}



void eh_quest_update_deadline(const DeferredEvent&)
{
    quest_check_all_for_failed();
}



void eh_wandering_vendor(const DeferredEvent&)
{
    const auto shopkeeper = chara_find("core.shopkeeper");
    assert(shopkeeper);
    talk_to_npc(*shopkeeper);
}



void eh_reunoin_with_pets(const DeferredEvent&)
{
    update_screen();
    std::vector<std::string> choices;
    for (int i = 0; i < 4; ++i)
    {
        choices.push_back(
            i18n::s.get_enum("core.event.popup.reunion_with_pet.choices", i));
    }
    int result = show_random_event_window(
        i18n::s.get("core.event.popup.reunion_with_pet.title"),
        i18n::s.get("core.event.popup.reunion_with_pet.text"),
        choices,
        u8"bg_re13");
    p = 3;
    if (result == 0)
    {
        p = 165;
    }
    if (result == 1)
    {
        p = 164;
    }
    if (result == 2)
    {
        p = 108;
    }
    if (result == 3)
    {
        p = 166;
    }
    flt();
    initlv = cdata.player().level * 2 / 3 + 1;
    novoidlv = 1;
    if (const auto chara = chara_create(
            -1, p, cdata.player().position.x, cdata.player().position.y))
    {
        new_ally_joins(*chara);
    }
}



void eh_marriage(const DeferredEvent&)
{
    play_music("core.mcWedding");
    show_random_event_window(
        i18n::s.get("core.event.popup.marriage.title"),
        i18n::s.get("core.event.popup.marriage.text", cdata[marry]),
        {i18n::s.get_enum("core.event.popup.marriage.choices", 0)},
        u8"bg_re14");
    for (int i = 0; i < 5; ++i)
    {
        flt(calcobjlv(cdata[marry].level + 5), calcfixlv(Quality::good));
        flttypemajor = choice(fsetchest);
        itemcreate_map_inv(0, cdata.player().position, 0);
    }
    itemcreate_map_inv(559, cdata.player().position, 0);
    flt();
    itemcreate_map_inv(55, cdata.player().position, rnd(3) + 2);
    txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
    save_set_autosave();
}



void eh_quest_time_is_up(const DeferredEvent&)
{
    switch (game_data.executing_immediate_quest_type)
    {
    case 1009:
        txt(i18n::s.get("core.quest.party.is_over"));
        calcpartyscore();
        calcpartyscore2();
        txt(i18n::s.get(
            "core.quest.party.final_score",
            quest_data.immediate().extra_info_2));
        if (quest_data.immediate().extra_info_1 <=
            quest_data.immediate().extra_info_2)
        {
            game_data.executing_immediate_quest_status = 3;
            quest_data.immediate().progress = 3;
            txt(i18n::s.get("core.quest.party.complete"),
                Message::color{ColorIndex::green});
            msg_halt();
        }
        else
        {
            txt(i18n::s.get("core.quest.party.fail"),
                Message::color{ColorIndex::purple});
        }
        break;
    case 1006:
        if (quest_data.immediate().extra_info_1 <
            quest_data.immediate().extra_info_2)
        {
            game_data.executing_immediate_quest_status = 3;
            quest_data.immediate().progress = 3;
            txt(i18n::s.get("core.quest.collect.complete"),
                Message::color{ColorIndex::green});
            msg_halt();
        }
        else
        {
            txt(i18n::s.get("core.quest.collect.fail"),
                Message::color{ColorIndex::purple});
        }
        break;
    case 1008:
        txt(i18n::s.get("core.quest.conquer.fail"),
            Message::color{ColorIndex::purple});
        break;
    }

    // In the case you exited the quest map at the turn when time is up, you
    // have already left the map when this event is being processed. Therefore
    // you need not exit twice, or you will go to the continent map. See #1450
    // for details.
    if (game_data.current_map == mdata_t::MapId::quest)
    {
        levelexitby = 4;
        snd("core.exitmap1");
        chatteleport = 1;
    }
}



void eh_quest_failed(const DeferredEvent& event)
{
    // param1: The character ID of the man who you escort.

    for (int i = 0; i < game_data.number_of_existing_quests; ++i)
    {
        if (quest_data[i].id == 1007 && quest_data[i].progress == 1 &&
            quest_data[i].extra_info_2 == event.param1)
        {
            rq = i;
            quest_failed(quest_data[rq].id);
            break;
        }
    }
}



void eh_quest_escort_complete(const DeferredEvent& event)
{
    // param1: The quest index which you are about to complete.
    // param2: The character index of the man who you escort.

    txt(i18n::s.get("core.quest.escort.complete"));
    talk_to_npc(cdata[event.param2]);
    rq = event.param1;
    quest_complete();
    chara_vanquish(cdata[event.param2]);
}



void eh_okaeri(const DeferredEvent&)
{
    i = 0;
    for (int chara_index = 1; chara_index < ELONA_MAX_CHARACTERS; ++chara_index)
    {
        if (cdata[chara_index].state() != Character::State::alive)
            continue;
        if (cdata[chara_index].role != Role::adventurer &&
            cdata[chara_index].role != Role::other)
        {
            if (cdata[chara_index].role != Role::none ||
                cdata[chara_index].relationship == 0 ||
                cdata[chara_index].current_map == game_data.current_map)
            {
                cdata[chara_index].emotion_icon = 2006;
                bool did_speak = chara_custom_talk(cdata[chara_index], 104);
                if (!did_speak)
                {
                    ++i;
                }
            }
        }
    }
    for (int j = 0; j < clamp(i(0), 0, 3); ++j)
    {
        txt(i18n::s.get("core.event.okaeri"), Message::color{ColorIndex::cyan});
    }
    if (game_data.number_of_waiting_guests != 0)
    {
        optional_ref<Character> maid;
        for (auto&& chara : cdata.all())
        {
            if (chara.state() != Character::State::alive)
                continue;
            if (chara.role == Role::maid)
            {
                maid = chara;
                break;
            }
        }
        if (maid)
        {
            talk_to_npc(*maid);
        }
    }
}



void eh_ragnarok(const DeferredEvent& event)
{
    // param1: The character index who causes Ragnarok.

    if (map_data.type == mdata_t::MapType::world_map)
        return;

    game_data.weather = 1;
    sound_play_environmental();
    txt(i18n::s.get("core.event.ragnarok"));
    msg_halt();
    RagnarokAnimation().play();
    for (int i = 0; i < 200; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            x = rnd(map_data.width);
            y = rnd(map_data.height);
            cell_data.at(x, y).chip_id_actual = 37;
        }
        x = rnd(inf_screenw) + scx;
        y = rnd(inf_screenh) + scy;
        if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height ||
            rnd(5) == 0)
        {
            x = rnd(map_data.width);
            y = rnd(map_data.height);
        }
        mef_add(x, y, 5, 24, rnd(15) + 20, 50, event.param1);
        mapitem_fire(cdata[event.param1], x, y);
        if (i % 4 == 0)
        {
            flt(100, calcfixlv(Quality::good));
            if (rnd(4))
            {
                fltnrace = u8"core.dragon"s;
            }
            else
            {
                fltnrace = u8"core.giant"s;
            }
            if (const auto chara = chara_create(-1, 0, x, y))
            {
                chara->is_temporary() = true;
            }
        }
        if (i % 7 == 0)
        {
            update_screen();
            if (rnd(7))
            {
                snd("core.fire1");
            }
            else
            {
                snd("core.crush1");
            }
            await(g_config.animation_wait());
        }
    }
}



void eh_lily_killed(const DeferredEvent& event)
{
    // param1: Lily's character index.

    damage_hp(cdata[event.param1], 9999, -11);
    cdata[event.param1].role = Role::none;
    cdata[event.param1].set_state(Character::State::empty);
    flt();
    itemcreate_map_inv(55, cdata[event.param1].position, 4);
    game_data.quest_flags.pael_and_her_mom = 1001;
    if (const auto pael = chara_find("core.pael"))
    {
        if (pael->state() == Character::State::alive)
        {
            txt(i18n::s.get("core.event.pael"),
                Message::color{ColorIndex::blue});
            pael->relationship = -3;
            pael->hate = 1000;
            pael->enemy_id = 0;
        }
    }
}



void eh_nuclear_bomb(const DeferredEvent& event)
{
    // param1, param2: The position (x, y) where the bomb explodes.

    if (map_data.type == mdata_t::MapType::world_map)
        return;

    txt(i18n::s.get("core.event.bomb"), Message::color{ColorIndex::red});
    msg_halt();
    gsel(7);
    picload(filesystem::dirs::graphic() / u8"bg22.bmp", 0, 0, true);
    gsel(4);
    gmode(0);
    gcopy_c(
        7,
        0,
        0,
        640,
        480,
        windoww / 2 - 1,
        windowh / 2 - 1,
        windoww + 4,
        windowh + 4);
    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime9.bmp", 0, 0, true);
    gsel(0);
    dx = windoww / 2;
    dy = (windowh - inf_verh) / 2;
    p(0) = 0;
    p(1) = 0;
    p(2) = 0;
    p(3) = 0;
    p(4) = 0;
    for (int i = 0; i < 40; ++i)
    {
        if (i == 14)
        {
            snd("core.atk_fire");
        }
        int x = 0, y = 0;
        if (i >= 16)
        {
            x = 5 - rnd(10);
            y = 5 - rnd(10);
        }
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, x, y);
        if (i > 8)
        {
            --p;
        }
        else
        {
            ++p;
        }
        gmode(2, 255 - p * 5);
        gcopy_c(
            7,
            i / 2 % 2 * 192,
            408,
            192,
            dx,
            dy,
            48,
            clamp(p * 32, 0, 192),
            clamp(p * 8, 0, 48));
        if (i > 14)
        {
            ++p(1);
        }
        else if (i < 12)
        {
            p(1) = i / 2 % 2;
        }
        else if (i >= 12)
        {
            p(1) = i % 3;
        }
        gmode(2);
        gcopy_c(
            7,
            p(1) * 96,
            288,
            96,
            48,
            dx,
            dy - clamp(i * 3 / 2, 0, 18) - 16,
            clamp(i * 12, 0, 144),
            clamp(i * 6, 0, 72));
        if (i > 4)
        {
            ++p(2);
            ++p(3);
        }
        gmode(2, clamp(p(2) * 6, 0, 100));
        gcopy_c(
            7,
            0,
            0,
            96,
            96,
            dx,
            dy - clamp(p(2) * 2, 0, 40),
            clamp(p(2) * 8, 0, 240),
            clamp(p(2) * 5, 0, 96));
        gmode(2, p(3) * 10);
        gcopy_c(
            7,
            96,
            0,
            96,
            96,
            dx,
            dy - clamp(p(3) * 2, 0, 160) - 6,
            clamp(p(3) * 10, 0, 96),
            clamp(p(3) * 10, 0, 96));
        gmode(2, clamp(p(3) * 5, 0, 100));
        gcopy_c(
            7,
            i / 4 % 2 * 192,
            96,
            192,
            80,
            dx,
            dy - 4,
            clamp(p(2) * 8, 0, 400),
            clamp(p(2), 0, 48));
        gmode(2, p(3) * 10);
        gcopy_c(
            7,
            i / 3 % 2 * 192,
            192,
            96,
            96,
            dx,
            dy - 48 - clamp(p(3) * 2, 0, 148),
            192,
            96);
        redraw();
        await(g_config.animation_wait() * 3.5);
    }
    gmode(2);
    update_entire_screen();
    tlocx = event.param1;
    tlocy = event.param2;
    range_ = 31;
    ele = 59;
    BallAnimation({tlocx, tlocy}, range_, BallAnimation::Type::atomic_bomb, ele)
        .play();
    update_screen();
    for (int i = 0; i < range_ * 2 + 1; ++i)
    {
        dy = tlocy - range_ + i;
        if (dy < 0 || dy >= map_data.height)
            continue;
        {
            for (int j = 0; j < range_ * 2 + 1; ++j)
            {
                dx = tlocx - range_ + j;
                if (dx < 0 || dx >= map_data.width)
                    continue;
                if (dist(tlocx, tlocy, dx, dy) > range_)
                    continue;
                f = 0;
                if (chip_data.for_cell(dx, dy).effect & 4)
                {
                    f = 1;
                }
                if (rnd(4) || f == 1)
                {
                    cell_data.at(dx, dy).chip_id_actual = 37;
                }
                if (rnd(10) == 0 || f == 1)
                {
                    mef_add(dx, dy, 5, 24, rnd(15) + 20, 50);
                }
                if (cell_data.at(dx, dy).chara_index_plus_one != 0)
                {
                    dmg = 1000;
                    damage_hp(
                        cdata[cell_data.at(dx, dy).chara_index_plus_one - 1],
                        dmg,
                        -17);
                }
                mapitem_fire(cdata.player(), dx, dy);
            }
        }
    }
    if (event.param1 == 33 && event.param2 == 16 &&
        game_data.current_map == mdata_t::MapId::palmia &&
        game_data.quest_flags.red_blossom_in_palmia == 1)
    {
        game_data.quest_flags.red_blossom_in_palmia = 2;
        quest_update_journal_msg();
    }
    if (map_is_town_or_guild())
    {
        modify_karma(cdata.player(), -80 + trait(162) * 60);
    }
    else
    {
        modify_karma(cdata.player(), -10);
    }
    net_send_news("bomb", mapname(game_data.current_map));
}



void eh_guild_alarm(const DeferredEvent& event)
{
    // param1: The flag whether you belogs to the guild. (0: No / 1: Yes)

    if (event.param1 != 0)
        return;

    txt(i18n::s.get("core.event.alarm"), Message::color{ColorIndex::red});
    for (auto&& chara : cdata.others())
    {
        if (chara.state() == Character::State::alive)
        {
            chara.relationship = -3;
            chara.enemy_id = 0;
            chara.hate = 250;
        }
    }
}



void eh_rogue_party_ambush(const DeferredEvent&)
{
    const auto rogue_boss = chara_find("core.rogue_boss");
    assert(rogue_boss);
    talk_to_npc(*rogue_boss);
    game_data.rogue_boss_encountered = 23;
}



void eh_init_economy(const DeferredEvent&)
{
    initeco = 1;
    initialize_economy();
}



void eh_guest_visit(const DeferredEvent&)
{
    --game_data.number_of_waiting_guests;
    if (chara_get_free_slot() == -1)
    {
        txt(i18n::s.get("core.event.guest_lost_his_way"));
        return;
    }

    optional_ref<Character> guest;
    if (rnd(3) == 0)
    {
        flt(0, Quality::good);
        if ((game_data.last_month_when_trainer_visited !=
                 game_data.date.month ||
             rnd(5) == 0) &&
            rnd(3))
        {
            if ((guest = chara_create(-1, 333, -3, 0)))
            {
                guest->role = Role::guest_trainer;
            }
        }
        else if (rnd(10) == 0)
        {
            if ((guest = chara_create(-1, 334, -3, 0)))
            {
                guest->role = Role::guest_producer;
            }
        }
        else if (rnd(10) == 0)
        {
            if ((guest = chara_create(-1, 1, -3, 0)))
            {
                guest->role = Role::guest_wandering_vendor;
                guest->shop_rank = clamp(cdata.player().fame / 100, 20, 100);
            }
        }
        else if (rnd(4) == 0)
        {
            if ((guest = chara_create(-1, 9, -3, 0)))
            {
                guest->role = Role::guest_beggar;
            }
        }
        else if (rnd(4) == 0)
        {
            if ((guest = chara_create(-1, 174, -3, 0)))
            {
                guest->role = Role::guest_punk;
            }
        }
        else
        {
            if ((guest = chara_create(-1, 16, -3, 0)))
            {
                guest->role = Role::guest_citizen;
            }
        }

        assert(guest);
        guest->relationship = 0;
        guest->original_relationship = 0;
        guest->is_temporary() = true;
    }
    else
    {
        int p = 0;
        for (int _i = 0; _i < 100; ++_i)
        {
            const auto adventurer_index = rnd(39) + 16;
            auto& adventurer = cdata[adventurer_index];
            if (adventurer.state() ==
                    Character::State::adventurer_in_other_map &&
                !adventurer.is_contracting() &&
                adventurer.current_map != game_data.current_map &&
                adventurer.relationship >= 0)
            {
                if (rnd(25) < p)
                {
                    break;
                }
                if (!guest)
                {
                    guest = adventurer;
                    ++p;
                    if (adventurer.impression < 25)
                    {
                        if (rnd(12) == 0)
                        {
                            break;
                        }
                    }
                    if (adventurer.impression < 0)
                    {
                        if (rnd(4))
                        {
                            break;
                        }
                    }
                    continue;
                }
                if (guest->impression < adventurer.impression)
                {
                    guest = adventurer;
                    ++p;
                }
            }
        }
        if (!guest)
        {
            txt(i18n::s.get("core.event.guest_already_left"));
            return;
        }
        guest->set_state(Character::State::alive);
        cxinit = cdata.player().position.x;
        cyinit = cdata.player().position.y;
        chara_place(*guest);
    }

    guest->visited_just_now() = true;
    OptionalItemRef chair_for_guest;
    for (int cnt = 0; cnt < 17; ++cnt)
    {
        const auto chara_index = cnt == 0 ? guest->index : cnt - 1;
        auto&& chara = cdata[chara_index];
        if (chara.state() != Character::State::alive)
        {
            continue;
        }
        if (game_data.mount != 0 && chara.index == game_data.mount)
        {
            continue;
        }
        OptionalItemRef chair;
        auto distance_to_guest_chair = 6;
        for (const auto& item : g_inv.ground())
        {
            if (item->function != 44)
                continue;
            if (chara.index == guest->index)
            {
                if (item->param1 == 2)
                {
                    cell_swap(chara, item->pos());
                    chair_for_guest = item;
                    chair = item;
                    break;
                }
                else
                {
                    continue;
                }
            }
            if (!chair_for_guest)
            {
                break;
            }
            else if (item == chair_for_guest)
            {
                continue;
            }
            const auto d = dist(item->pos(), chair_for_guest->pos());
            if (d < distance_to_guest_chair)
            {
                if (cell_data.at(item->pos().x, item->pos().y)
                            .chara_index_plus_one == 0 ||
                    chara.is_player() || chara.index == guest->index)
                {
                    chair = item;
                    distance_to_guest_chair = d;
                }
            }
            if (chara.is_player() && item->param1 == 1)
            {
                chair = item;
                break;
            }
        }
        if (chair)
        {
            cell_swap(chara, chair->pos());
        }
        chara.direction = direction(
            chara.position.x,
            chara.position.y,
            guest->position.x,
            guest->position.y);
        if (chara.is_player())
        {
            game_data.player_next_move_direction = chara.direction;
        }
    }

    talk_to_npc(*guest);
}



void eh_blaggers(const DeferredEvent&)
{
    if (map_data.type == mdata_t::MapType::world_map)
        return;
    txt(i18n::s.get("core.event.blaggers"));
    for (int i = 0; i < 3; ++i)
    {
        flt();
        initlv = cdata.player().level;
        chara_create(
            -1, 215, cdata.player().position.x, cdata.player().position.y);
    }
}



void eh_little_sister(const DeferredEvent& event)
{
    // param1, param2: The position (x, y) where Big Daddy standed.

    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        return;
    }
    flt();
    chara_create(-1, 319, event.param1, event.param2);
    txt(i18n::s.get("core.event.little_sister_slips"),
        Message::color{ColorIndex::blue});
}



void eh_god_inside_ehekatl(const DeferredEvent& event)
{
    // param1, param2: The position (x, y) where Ehekatl standed.

    txt(i18n::s.get("core.event.ehekatl"), Message::color{ColorIndex::orange});
    msg_halt();
    RagnarokAnimation().play();
    flt();
    chara_create(-1, 336, event.param1, event.param2);
}



void eh_lord_of_void(const DeferredEvent&)
{
    randomize(game_data.date.year + game_data.current_dungeon_level);
    int c = choice(std::initializer_list<int>{
        300, 26,  27, 28,  29,  140, 34, 141, 143, 144,
        145, 242, 25, 257, 230, 202, 37, 33,  80,  332,
    });
    randomize();
    flt();
    fixlv = Quality::miracle;
    initlv = clamp(game_data.current_dungeon_level / 4, 50, 250);
    if (const auto lord = chara_create(-1, c, -3, 0))
    {
        lord->is_lord_of_dungeon() = true;
        lord->relationship = -3;
        lord->original_relationship = -3;
        area_data[game_data.current_map].has_been_conquered = lord->index;
        txt(i18n::s.get(
                "core.event.guarded_by_lord",
                mapname(game_data.current_map),
                *lord),
            Message::color{ColorIndex::red});
        if (game_data.current_dungeon_level % 50 == 0)
        {
            net_send_news("void", cnvrank(game_data.current_dungeon_level));
        }
    }
}



void eh_snow_blindness(const DeferredEvent&)
{
    i = 0;
    for (auto&& chara : cdata.player_and_allies())
    {
        if (chara.state() != Character::State::alive)
            continue;
        if (chara.role != Role::adventurer && chara.role != Role::other)
        {
            chara.emotion_icon = 2010;
            txt(i18n::s.get("core.event.my_eyes", chara));
        }
    }
}

} // namespace event_handlers



void proc_one_event(const DeferredEvent& event)
{
    using namespace event_handlers;

    switch (event.id)
    {
    case 1: eh_conquer_lesimas(event); break;
    case 2: eh_lomias_talks(event); break;
    case 3: eh_zeome_talks(event); break;
    case 4: eh_lord_of_normal_nefia(event); break;
    case 5: eh_conquer_nefia(event); break;
    case 6: eh_player_died(event); break;
    case 8: eh_quest_all_target_killed(event); break;
    case 10: eh_quest_update_deadline(event); break;
    case 11: eh_wandering_vendor(event); break;
    case 12: eh_reunoin_with_pets(event); break;
    case 13: eh_marriage(event); break;
    case 14: eh_quest_time_is_up(event); break;
    case 15: eh_quest_failed(event); break;
    case 16: eh_quest_escort_complete(event); break;
    case 17: eh_okaeri(event); break;
    case 18: eh_ragnarok(event); break;
    case 20: eh_lily_killed(event); break;
    case 21: eh_nuclear_bomb(event); break;
    case 22: eh_guild_alarm(event); break;
    case 23: eh_rogue_party_ambush(event); break;
    case 24: eh_init_economy(event); break;
    case 25: eh_guest_visit(event); break;
    case 26: eh_blaggers(event); break;
    case 27: eh_little_sister(event); break;
    case 28: eh_god_inside_ehekatl(event); break;
    case 29: eh_lord_of_void(event); break;
    case 30: eh_snow_blindness(event); break;
    default: assert(0); break;
    }
}

} // namespace



// TODO add serialization routines local to this file

int event_processing_event()
{
    return g_event_queue.empty() ? -1 : g_event_queue.front().id;
}



bool event_has_pending_events()
{
    return !g_event_queue.empty();
}



bool event_find(int event_type)
{
    return g_event_queue.has(event_type);
}



void event_add(int event_type, int param1, int param2)
{
    g_event_queue.enqueue(event_type, param1, param2);
}



TurnResult event_start_proc()
{
    const auto event = g_event_queue.front();
    proc_one_event(event);
    g_event_queue.dequeue();

    if (chatteleport == 1)
    {
        chatteleport = 0;
        return TurnResult::exit_map;
    }
    return TurnResult::turn_begin;
}



void event_load(const fs::path& path)
{
    serialization::binary::load(path, g_event_queue);
}



void event_save(const fs::path& path)
{
    serialization::binary::save(path, g_event_queue);
}

} // namespace elona
