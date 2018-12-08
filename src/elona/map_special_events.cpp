#include "ability.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "dmgheal.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "variables.hpp"

namespace elona
{

static void _map_events_noyel()
{
    if (game_data.released_fire_giant == 1)
    {
        if (cdata[game_data.fire_giant].state() == Character::State::alive)
        {
            if (game_data.crowd_density < 70)
            {
                if (rnd(4) == 0)
                {
                    flt();
                    objlv = 1;
                    chara_create(-1, 204, -3, 0);
                }
                if (rnd(10) == 0)
                {
                    flt();
                    objlv = 1;
                    chara_create(-1, 185, -3, 0);
                }
            }
        }
    }
}

static void _map_events_quest_party()
{
    if (quest_data.immediate().progress != 3)
    {
        if (game_data.crowd_density <
            game_data.left_minutes_of_executing_quest / 60)
        {
            dbid = 0;
            if (rnd(4) == 0)
            {
                dbid = 204;
            }
            if (rnd(10) == 0)
            {
                dbid = 185;
            }
            if (dbid != 0)
            {
                flt();
                objlv = 1;
                int stat = chara_create(-1, dbid, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                    cdata[rc].hate = 100;
                    cdata[rc].enemy_id = quest_data.immediate().extra_info_2;
                }
            }
        }
    }
}

static void _map_events_tower_of_fire()
{
    if (rnd(5) == 0)
    {
        r = sdata(50, 0) / 50;
        if (r < 6)
        {
            dmg = (6 - r) * (6 - r) * 2;
            txt(i18n::s.get("core.locale.action.exit_map.it_is_hot"),
                Message::color{ColorIndex::red});
            damage_hp(cdata[cc], dmg, -9);
        }
    }
}

static void _map_events_port_kapul()
{
    if (game_data.current_dungeon_level == 25)
    {
        ++game_data.quest_flags.duration_of_kamikaze_attack;
        x = 1;
        y = rnd(map_data.height);
        if (rnd(4) == 0)
        {
            x = map_data.width - 2;
            y = rnd(map_data.height);
        }
        if (rnd(5) == 0)
        {
            x = rnd(map_data.width);
            y = 1;
        }
        if (rnd(6) == 0)
        {
            x = rnd(map_data.width);
            y = map_data.height - 2;
        }
        p = 237;
        if (game_data.quest_flags.duration_of_kamikaze_attack > 50)
        {
            if (rnd(10) == 0)
            {
                p = 245;
            }
        }
        if (game_data.quest_flags.duration_of_kamikaze_attack > 100)
        {
            if (rnd(10) == 0)
            {
                p = 244;
            }
        }
        if (game_data.quest_flags.duration_of_kamikaze_attack > 150)
        {
            if (rnd(10) == 0)
            {
                p = 244;
            }
        }
        if (game_data.quest_flags.duration_of_kamikaze_attack == 250)
        {
            quest_update_journal_msg();
            game_data.quest_flags.kamikaze_attack = 3;
            txt(i18n::s.get("core.locale.misc.quest.kamikaze_attack.message"),
                Message::color{ColorIndex::cyan});
            txt(i18n::s.get(
                "core.locale.misc.quest.kamikaze_attack.stairs_appear"));
            cell_featset(18, 9, tile_downstairs, 11, 1);
        }
        flt();
        chara_create(-1, p, x, y);
        cdata[rc].hate = 1000;
        cdata[rc].enemy_id = 0;
        return;
    }
}

static void _map_events_jail()
{
    if (rnd(50) == 0)
    {
        if (cdata.player().karma < -30)
        {
            txt(i18n::s.get("core.locale.misc.map.jail.repent_of_sin"));
            modify_karma(cdata.player(), 1);
            p = rnd(8) + 10;
            if (sdata.get(p, 0).original_level >= 10)
            {
                chara_gain_fixed_skill_exp(cdata.player(), p, -300);
            }
        }
    }
    if (cdata.player().karma >= -30)
    {
        if (rnd(1000) == 0)
        {
            cell_featread(29, 6);
            if (feat(1) == 21)
            {
                txt(i18n::s.get("core.locale.misc.map.jail.guard_approaches"));
                txt(i18n::s.get("core.locale.misc.map.jail.leave_here"));
                txt(i18n::s.get("core.locale.misc.map.jail.unlocks_your_cell"));
                cell_featset(29, 6, tile_dooropen, 20, 0, -1);
                snd("core.door1");
            }
        }
    }
}

static void _map_events_shelter()
{
    if (game_data.weather == 2 || game_data.weather == 4 ||
        game_data.weather == 1)
    {
        if (cdata.player().nutrition < 5000)
        {
            if (cdata.player().has_anorexia() == 0)
            {
                snd("core.eat1");
                txt(i18n::s.get(
                    "core.locale.misc.map.shelter.eat_stored_food"));
                cdata[cc].nutrition += 5000;
                show_eating_message();
            }
        }
        if (game_data.continuous_active_hours >= 15)
        {
            game_data.continuous_active_hours = 13;
        }
        map_data.turn_cost = 1000000;
    }
    else if (map_data.turn_cost == 1000000)
    {
        map_data.turn_cost = 10000;
        for (auto&& cnt : cdata.all())
        {
            cnt.turn_cost = 0;
        }
        txt(i18n::s.get("core.locale.misc.map.shelter.no_longer_need_to_stay"));
    }
}

static void _map_events_museum()
{
    if (game_data.crowd_density > 0)
    {
        if (rnd(25) == 0)
        {
            txt(i18n::s.get("core.locale.misc.map.museum.chats"),
                Message::color{ColorIndex::cyan});
        }
        if (rnd(25) == 0)
        {
            txt(i18n::s.get("core.locale.misc.map.museum.chats2"),
                Message::color{ColorIndex::cyan});
        }
        if (rnd(15) == 0)
        {
            if (en)
            {
            }
            else if (game_data.ranks.at(3) > 8000)
            {
                txt(u8"「退屈ぅー」"s,
                    u8"「あまり見るものがないな」"s,
                    u8"「こんなので見物料とるの？」"s,
                    u8"館内は少し寂しい…"s,
                    Message::color{ColorIndex::cyan});
            }
            else if (game_data.ranks.at(3) > 5000)
            {
                txt(u8"「いいんじゃない〜」"s,
                    u8"「まあ、普通の博物館だ」"s,
                    u8"「恋人を連れてくればよかったかも」"s,
                    u8"まあまあの客足だ。"s,
                    Message::color{ColorIndex::cyan});
            }
            else if (game_data.ranks.at(3) > 2500)
            {
                txt(u8"「この雰囲気好きだなぁ」"s,
                    u8"「もう一度来ようよ」"s,
                    u8"「時間が経つのを忘れるね！」"s,
                    u8"館内はなかなか賑わっている。"s,
                    Message::color{ColorIndex::cyan});
            }
            else if (game_data.ranks.at(3) > 500)
            {
                txt(u8"「来て良かった♪」"s,
                    u8"「よくこんなに集めたなあ」"s,
                    u8"「むぅ…興味深い」"s,
                    u8"客足が全く絶えない盛況ぶりだ。"s,
                    Message::color{ColorIndex::cyan});
            }
            else
            {
                txt(u8"「素晴らしいコレクションだ！」"s,
                    u8"「感動した」"s,
                    u8"「帰りたくないわ♪」"s,
                    u8"来客は食い入るように展示物を眺めている。"s,
                    Message::color{ColorIndex::cyan});
            }
        }
        return;
    }
}

static void _map_events_shop()
{
    if (game_data.crowd_density > 0)
    {
        if (rnd(25) == 0)
        {
            txt(i18n::s.get("core.locale.misc.map.shop.chats"),
                Message::color{ColorIndex::cyan});
        }
        return;
    }
}

void map_proc_special_events()
{
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        _map_events_noyel();
    }
    if (game_data.executing_immediate_quest_type == 1008)
    {
        _map_events_quest_party();
    }
    if (game_data.current_map == mdata_t::MapId::tower_of_fire)
    {
        _map_events_tower_of_fire();
        return;
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        _map_events_port_kapul();
    }
    if (game_data.current_map == mdata_t::MapId::jail)
    {
        _map_events_jail();
    }
    if (game_data.current_map == mdata_t::MapId::shelter_)
    {
        _map_events_shelter();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::museum)
    {
        _map_events_museum();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        _map_events_shop();
    }
}

} // namespace elona
