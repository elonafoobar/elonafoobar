#include "../util/strutil.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "crafting.hpp"
#include "data/types/type_item.hpp"
#include "dialog.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "talk.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int chatval_ = 0;

void _arnord_goto_map()
{
    game_data.quest_flags.kamikaze_attack = 2;
    map_data.stair_down_pos =
        cdata.player().position.y * 1000 + cdata.player().position.x;
    game_data.destination_map = 11;
    game_data.destination_dungeon_level = 25;
    levelexitby = 2;
    chatteleport = 1;
}

void _arnord_receive_reward()
{
    flt();
    itemcreate(
        -1, 662, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1, 54, cdata.player().position.x, cdata.player().position.y, 7500);
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 3);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
}

TalkResult talk_unique_arnord()
{
    if (game_data.quest_flags.kamikaze_attack == 1000)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.arnord.complete", cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.kamikaze_attack == 0)
    {
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.dialog");
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.unique.arnord.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.unique.arnord.quest.choices.no"));
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.arnord.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        quest_update_journal_msg();
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.kamikaze_attack = 1;

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.kamikaze_attack == 1 ||
        game_data.quest_flags.kamikaze_attack == 2)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.arnord.quest.begin.choices.yes"));
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get(
                "core.locale.talk.unique.arnord.quest.begin.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.begin.dialog");
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.arnord.quest.begin.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        quest_update_journal_msg();
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.begin.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        _arnord_goto_map();

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.kamikaze_attack == 3)
    {
        _arnord_receive_reward();

        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.kamikaze_attack = 1000;

        return TalkResult::talk_end;
    }
    return TalkResult::talk_end;
}


void _mia_receive_reward()
{
    flt();
    itemcreate(
        -1, 663, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1, 54, cdata.player().position.x, cdata.player().position.y, 5000);
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 3);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    game_data.quest_flags.mias_dream = 1000;
    chara_relocate(cdata[chara_find_ally(246)], none);
    cdata[rc].relationship = -1;
    cdata[rc].original_relationship = -1;
    cdata[rc].character_role = 3;
}

TalkResult talk_unique_mia()
{
    if (game_data.quest_flags.mias_dream == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.mia.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.mias_dream == 0)
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.unique.mia.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.unique.mia.quest.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.mia.quest.dialog");
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.mia.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        quest_update_journal_msg();
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.mia.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.mias_dream = 1;

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.mias_dream == 1)
    {
        if (chara_find_ally(246) == -1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.mia.quest.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.mia.quest.end", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.mia.quest.end", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        _mia_receive_reward();

        return TalkResult::talk_end;
    }
    return TalkResult::talk_ignored;
}


void _renton_take_books()
{
    p(0) = 0;
    p(1) = 0;
    p(2) = 0;
    p(3) = 0;
    p(4) = 0;
    p(5) = 0;
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number() == 0)
        {
            continue;
        }
        if (inv[cnt].id == 668)
        {
            if (p(inv[cnt].param2) == 0)
            {
                inv[cnt].modify_number(-1);
                p(inv[cnt].param2) = 1;
            }
        }
    }
}

void _renton_receive_reward()
{
    flt();
    itemcreate(
        -1, 666, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1, 655, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1, 54, cdata.player().position.x, cdata.player().position.y, 20000);
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 5);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    game_data.quest_flags.rare_books = 1000;
}

TalkResult talk_unique_renton()
{
    if (game_data.quest_flags.rare_books == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.renton.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.rare_books == 0 ||
        game_data.quest_flags.rare_books == 1)
    {
        listmax = 0;
        buff =
            i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff =
            i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff =
            i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff =
            i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 3);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        if (game_data.quest_flags.rare_books == 0)
        {
            quest_update_journal_msg();
            game_data.quest_flags.rare_books = 1;
            return TalkResult::talk_end;
        }

        p(0) = 0;
        p(1) = 0;
        p(2) = 0;
        p(3) = 0;
        p(4) = 0;
        p(5) = 0;
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number() == 0)
            {
                continue;
            }
            if (inv[cnt].id == 668)
            {
                p(inv[cnt].param2) = 1;
            }
        }
        for (int cnt = 1; cnt < 5; ++cnt)
        {
            p += p(cnt);
        }

        if (p != 0)
        {
            if (p != 4)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.renton.quest.brought", p(0));
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_end;
            }

            _renton_take_books();

            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.renton.quest.brought_all.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            if (jp)
            {
                buff = u8"…"s;
            }
            else
            {
                buff = u8"..."s;
            }
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            if (jp)
            {
                buff = u8"… …"s;
            }
            else
            {
                buff = u8"... ..."s;
            }
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            if (jp)
            {
                buff = u8"… … …"s;
            }
            else
            {
                buff = u8"... ... ..."s;
            }
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.renton.quest.brought_all.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            txt(i18n::s.get(
                    "core.locale.talk.unique.renton.quest.brought_all.ehekatl"),
                Message::color{ColorIndex::orange});
            txt(i18n::s.get("core.locale.quest.completed"));
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.renton.quest.brought_all.dialog", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _renton_receive_reward();
        }
        return TalkResult::talk_end;
    }
    return TalkResult::talk_ignored;
}


void _marks_receive_invitation()
{
    cdata.player().gold -= 20000;
    snd("core.paygold1");
    flt();
    itemcreate(-1, 24, cdata.player().position.x, cdata.player().position.y, 0);
    inv[ci].param1 = 13;
}

TalkResult talk_unique_marks()
{
    if (game_data.quest_flags.pyramid_trial != 0)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.marks.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (cdata.player().fame < 3000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.marks.fame_too_low");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.pyramid_trial == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.marks.quest.dialog", 0, cdatan(1, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        if (cdata.player().gold >= 20000)
        {
            ELONA_APPEND_RESPONSE(
                1,
                i18n::s.get("core.locale.talk.unique.marks.quest.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        buff =
            i18n::s.get_enum("core.locale.talk.unique.marks.quest.dialog", 1);
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.marks.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        quest_update_journal_msg();
        txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));

        _marks_receive_invitation();

        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.marks.quest.pay");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.pyramid_trial = 1;

        return TalkResult::talk_end;
    }
    return TalkResult::talk_ignored;
}


void _noel_receive_reward()
{
    flt();
    nostack = 1;
    itemcreate(
        -1, 672, cdata.player().position.x, cdata.player().position.y, 0);
    inv[ci].param1 = 162;
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 6);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    game_data.quest_flags.red_blossom_in_palmia = 1000;
}

void _noel_buy_nuke()
{
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    cdata.player().gold -= 12000;
    snd("core.paygold1");
    flt();
    itemcreate(
        -1, 671, cdata.player().position.x, cdata.player().position.y, 0);
}

TalkResult talk_unique_noel()
{
    if (game_data.quest_flags.red_blossom_in_palmia == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (game_data.quest_flags.red_blossom_in_palmia == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (game_data.quest_flags.red_blossom_in_palmia == 2)
    {
        _noel_receive_reward();

        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (game_data.quest_flags.red_blossom_in_palmia == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.noel.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.noel.quest.choices.of_course"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        buff = i18n::s.get_enum("core.locale.talk.unique.noel.quest.dialog", 1);
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.noel.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }

        quest_update_journal_msg();
        game_data.quest_flags.red_blossom_in_palmia = 1;

        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.of_course");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (cdata.player().gold >= 12000)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.noel.quest.buy_nuke.choices.buy"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    buff = i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.dialog");
    chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.bye");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }

    _noel_buy_nuke();

    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.buy");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return TalkResult::talk_end;
}


void _icolle_receive_monster_balls()
{
    flt();
    nostack = 1;
    itemcreate(
        -1, 685, cdata.player().position.x, cdata.player().position.y, 6);
    inv[ci].param2 = 5;
    quest_update_journal_msg();
}

int _icolle_check_monster_balls()
{
    int f_ = 0;
    const auto tmp = inv_getheader(0);
    const auto invhead = tmp.first;
    const auto invrange = tmp.second;
    for (int cnt = invhead, cnt_end = invhead + invrange; cnt < cnt_end; ++cnt)
    {
        if (game_data.quest_flags.ambitious_scientist >= 6)
        {
            break;
        }
        if (inv[cnt].number() > 0)
        {
            if (inv[cnt].id == 685)
            {
                if (inv[cnt].subname != 0)
                {
                    inv[cnt].modify_number(-1);
                    ++game_data.quest_flags.ambitious_scientist;
                    f_ = 1;
                    txt(i18n::s.get(
                        "core.locale.talk.unique.icolle.quest.give.deliver",
                        inv[cnt]));
                    --cnt;
                    continue;
                }
            }
        }
    }

    return f_;
}

void _icolle_receive_reward()
{
    flt();
    itemcreate(
        -1, 684, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1, 54, cdata.player().position.x, cdata.player().position.y, 2500);
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 2);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    game_data.quest_flags.ambitious_scientist = 1000;
}

TalkResult talk_unique_icolle()
{
    if (game_data.quest_flags.ambitious_scientist >= 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.icolle.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.ambitious_scientist == 0)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.icolle.quest.choices.alright"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        buff = i18n::s.get("core.locale.talk.unique.icolle.quest.dialog");
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.icolle.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }

        _icolle_receive_monster_balls();

        txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.icolle.quest.alright");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.ambitious_scientist = 1;

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.ambitious_scientist >= 1 &&
        game_data.quest_flags.ambitious_scientist <= 5)
    {
        f = _icolle_check_monster_balls();
        if (f)
        {
            listmax = 0;
            buff =
                i18n::s.get("core.locale.talk.unique.icolle.quest.give.have");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (f == 0)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.icolle.quest.give.do_not_have");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        refresh_burden_state();
    }
    if (game_data.quest_flags.ambitious_scientist >= 6)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.icolle.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        _icolle_receive_reward();
    }
    return TalkResult::talk_end;
}


void _balzak_receive_reward()
{
    flt();
    itemcreate(
        -1, 686, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    nostack = 1;
    itemcreate(
        -1, 685, cdata.player().position.x, cdata.player().position.y, 0);
    inv[ci].param2 = 30;
    flt();
    itemcreate(
        -1, 54, cdata.player().position.x, cdata.player().position.y, 15000);
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 4);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
}

TalkResult talk_unique_balzak()
{
    if (game_data.quest_flags.sewer_sweeping == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.sewer_sweeping == 0)
    {
        listmax = 0;
        buff =
            i18n::s.get_enum("core.locale.talk.unique.balzak.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.unique.balzak.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.unique.balzak.quest.choices.no"));
        buff =
            i18n::s.get_enum("core.locale.talk.unique.balzak.quest.dialog", 1);
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.balzak.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        quest_update_journal_msg();
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.sewer_sweeping = 1;
        cell_featset(18, 45, tile_downstairs, 11, 20);

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.sewer_sweeping == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.sewer_sweeping == 2)
    {
        _balzak_receive_reward();

        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        game_data.quest_flags.sewer_sweeping = 1000;
        return TalkResult::talk_end;
    }
    return TalkResult::talk_ignored;
}


void _lexus_join_mages_guild()
{
    game_data.ranks.at(8) = 10000;
    game_data.guild.belongs_to_thieves_guild = 0;
    game_data.guild.belongs_to_fighters_guild = 0;
    game_data.guild.belongs_to_mages_guild = 1;
    game_data.guild.mages_guild_quota = 0;
    game_data.guild.thieves_guild_quota = 0;
    game_data.guild.joining_mages_guild = 1000;
    game_data.guild.joining_thieves_guild = 0;
    game_data.guild.joining_fighters_guild = 0;
    game_data.guild.fighters_guild_quota_recurring = 0;
    game_data.guild.mages_guild_quota_recurring = 0;
    game_data.guild.thieves_guild_quota_recurring = 0;
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    quest_update_journal_msg();
    txt(i18n::s.get("core.locale.talk.unique.lexus.nonmember.joined"),
        Message::color{ColorIndex::orange});
}

void _lexus_start_trial()
{
    game_data.guild.joining_mages_guild = 1;
    game_data.guild.mages_guild_quota = 30;
    quest_update_journal_msg();
}

void _lexus_update_quota()
{
    game_data.guild.mages_guild_quota_recurring = 1;
    game_data.guild.mages_guild_quota = 75 - game_data.ranks.at(8) / 200;
    quest_update_journal_msg();
}

void _lexus_move_self()
{
    cell_movechara(tc, 4, 20);
    cdata[tc].initial_position.x = 4;
    cdata[tc].initial_position.y = 20;
}

void _lexus_receive_reward()
{
    game_data.guild.mages_guild_quota_recurring = 0;
    flt(51 - game_data.ranks.at(8) / 200);
    flttypemajor = 54000;
    itemcreate(-1, 0, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1,
        54,
        cdata.player().position.x,
        cdata.player().position.y,
        10000 - game_data.ranks.at(8) + 1000);
    flt();
    itemcreate(
        -1,
        55,
        cdata.player().position.x,
        cdata.player().position.y,
        clamp(4 - game_data.ranks.at(8) / 2500, 1, 4));
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    modrank(8, 500, 8);
}

TalkResult talk_unique_lexus()
{
    if (game_data.guild.belongs_to_mages_guild == 0)
    {
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get("core.locale.talk.unique.lexus.nonmember.choices.tell_"
                        "me_about"));
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get("core.locale.talk.unique.lexus.nonmember.choices.want_"
                        "to_join"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        buff = i18n::s.get("core.locale.talk.unique.lexus.nonmember.dialog");
        chatval_ = talk_window_query();
        if (chatval_ == 2)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.lexus.nonmember.tell_me_about");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_unique;
        }
        if (chatval_ == 1)
        {
            if (game_data.guild.joining_mages_guild == 0)
            {
                listmax = 0;
                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.lexus.nonmember.want_to_join", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.lexus.nonmember.want_to_join", 1);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();

                _lexus_start_trial();

                listmax = 0;
                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.lexus.nonmember.want_to_join", 2);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_unique;
            }
            if (game_data.guild.mages_guild_quota > 0)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.lexus.nonmember.quota");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.lexus.nonmember.end", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _lexus_join_mages_guild();

            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.lexus.nonmember.end", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _lexus_move_self();
        }
        return TalkResult::talk_end;
    }
    _lexus_move_self();

    if (game_data.guild.mages_guild_quota_recurring == 0)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.lexus.member.choices.new_quota"));
    }
    else
    {
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get(
                "core.locale.talk.unique.lexus.member.choices.report_quota"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    buff = i18n::s.get(
        "core.locale.talk.unique.lexus.member.dialog",
        ranktitle(8),
        cdatan(0, 0));
    chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        _lexus_update_quota();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.lexus.member.new_quota",
            game_data.guild.mages_guild_quota);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_unique;
    }
    if (chatval_ == 2)
    {
        if (game_data.guild.mages_guild_quota > 0)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.lexus.member.report_quota.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_unique;
        }

        _lexus_receive_reward();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.lexus.member.report_quota.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    return TalkResult::talk_end;
}


void _abyss_start_trial()
{
    game_data.guild.joining_thieves_guild = 1;
    quest_update_journal_msg();
}

void _abyss_join_thieves_guild()
{
    game_data.ranks.at(8) = 10000;
    game_data.guild.belongs_to_thieves_guild = 1;
    game_data.guild.belongs_to_fighters_guild = 0;
    game_data.guild.belongs_to_mages_guild = 0;
    game_data.guild.mages_guild_quota = 0;
    game_data.guild.thieves_guild_quota = 0;
    game_data.guild.joining_mages_guild = 0;
    game_data.guild.joining_thieves_guild = 1000;
    game_data.guild.joining_fighters_guild = 0;
    game_data.guild.fighters_guild_quota_recurring = 0;
    game_data.guild.mages_guild_quota_recurring = 0;
    game_data.guild.thieves_guild_quota_recurring = 0;
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    quest_update_journal_msg();
    txt(i18n::s.get("core.locale.talk.unique.abyss.nonmember.joined"),
        Message::color{ColorIndex::orange});
}

void _abyss_move_self()
{
    cell_movechara(tc, 17, 17);
    cdata[tc].initial_position.x = 17;
    cdata[tc].initial_position.y = 17;
}

void _abyss_update_quota()
{
    game_data.guild.thieves_guild_quota_recurring = 1;
    game_data.guild.thieves_guild_quota =
        (10000 - game_data.ranks.at(8)) * 6 + 1000;
    quest_update_journal_msg();
}

void _abyss_receive_reward()
{
    game_data.guild.thieves_guild_quota_recurring = 0;
    flt(51 - game_data.ranks.at(8) / 200);
    flttypemajor = 60000;
    itemcreate(-1, 0, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1,
        54,
        cdata.player().position.x,
        cdata.player().position.y,
        10000 - game_data.ranks.at(8) + 1000);
    flt();
    itemcreate(
        -1,
        55,
        cdata.player().position.x,
        cdata.player().position.y,
        clamp(3 - game_data.ranks.at(8) / 3000, 1, 3));
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    modrank(8, 500, 8);
}

TalkResult talk_unique_abyss()
{
    if (game_data.guild.belongs_to_thieves_guild == 0)
    {
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get("core.locale.talk.unique.abyss.nonmember.choices.tell_"
                        "me_about"));
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get("core.locale.talk.unique.abyss.nonmember.choices.want_"
                        "to_join"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        buff = i18n::s.get("core.locale.talk.unique.abyss.nonmember.dialog");
        chatval_ = talk_window_query();
        if (chatval_ == 2)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.abyss.nonmember.tell_me_about");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_unique;
        }
        if (chatval_ == 1)
        {
            if (game_data.guild.joining_thieves_guild == 0)
            {
                listmax = 0;
                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.abyss.nonmember.want_to_join", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();

                _abyss_start_trial();

                listmax = 0;
                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.abyss.nonmember.want_to_join", 1);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_unique;
            }
            if (game_data.left_bill <= 4)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.abyss.nonmember.quota");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.abyss.nonmember.end", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _abyss_join_thieves_guild();

            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.abyss.nonmember.end", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _abyss_move_self();
        }
        return TalkResult::talk_end;
    }
    _abyss_move_self();

    if (game_data.guild.thieves_guild_quota_recurring == 0)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.lexus.member.choices.new_quota"));
    }
    else
    {
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get(
                "core.locale.talk.unique.lexus.member.choices.report_quota"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    buff = i18n::s.get(
        "core.locale.talk.unique.abyss.member.dialog",
        ranktitle(8),
        cdatan(0, 0));
    chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        _abyss_update_quota();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.abyss.member.new_quota",
            game_data.guild.thieves_guild_quota);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_unique;
    }
    if (chatval_ == 2)
    {
        if (game_data.guild.thieves_guild_quota > 0)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.lexus.member.report_quota.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_unique;
        }

        _abyss_receive_reward();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.lexus.member.report_quota.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    return TalkResult::talk_end;
}


void _doria_start_trial()
{
    game_data.guild.joining_fighters_guild = 1;
    quest_update_journal_msg();
    while (1)
    {
        flt(10);
        chara_create(56, 0, -3, 0);
        if (the_character_db[cdata.tmp().id]->rarity / 1000 < 70)
        {
            continue;
        }
        if (cdata.tmp().relationship != -3)
        {
            continue;
        }
        if (cdata.tmp().quality >= Quality::miracle)
        {
            continue;
        }
        break;
    }
    game_data.guild.fighters_guild_quota = 15;
    game_data.guild.fighters_guild_target = cdata.tmp().id;
    chara_vanquish(56);
}

void _doria_join_fighters_guild()
{
    game_data.ranks.at(8) = 10000;
    game_data.guild.belongs_to_thieves_guild = 0;
    game_data.guild.belongs_to_fighters_guild = 1;
    game_data.guild.belongs_to_mages_guild = 0;
    game_data.guild.mages_guild_quota = 0;
    game_data.guild.thieves_guild_quota = 0;
    game_data.guild.joining_mages_guild = 0;
    game_data.guild.joining_thieves_guild = 0;
    game_data.guild.joining_fighters_guild = 1000;
    game_data.guild.fighters_guild_quota_recurring = 0;
    game_data.guild.mages_guild_quota_recurring = 0;
    game_data.guild.thieves_guild_quota_recurring = 0;
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    quest_update_journal_msg();
    txt(i18n::s.get("core.locale.talk.unique.doria.nonmember.joined"),
        Message::color{ColorIndex::orange});
}

void _doria_move_self()
{
    cell_movechara(tc, 29, 2);
    cdata[tc].initial_position.x = 29;
    cdata[tc].initial_position.y = 2;
}

void _doria_update_quota()
{
    while (1)
    {
        flt(cdata.player().level + 10);
        chara_create(56, 0, -3, 0);
        if (the_character_db[cdata.tmp().id]->rarity / 1000 < 70)
        {
            continue;
        }
        if (cdata.tmp().relationship != -3)
        {
            continue;
        }
        if (cdata.tmp().quality >= Quality::miracle)
        {
            continue;
        }
        break;
    }
    game_data.guild.fighters_guild_quota = 2 + rnd(3);
    game_data.guild.fighters_guild_target = cdata.tmp().id;
    chara_vanquish(56);
    game_data.guild.fighters_guild_quota_recurring = 1;
    quest_update_journal_msg();
}

void _doria_receive_reward()
{
    game_data.guild.fighters_guild_quota_recurring = 0;
    flt(51 - game_data.ranks.at(8) / 200, calcfixlv(Quality::good));
    flttypemajor = 10000;
    itemcreate(-1, 0, cdata.player().position.x, cdata.player().position.y, 0);
    flt();
    itemcreate(
        -1,
        54,
        cdata.player().position.x,
        cdata.player().position.y,
        10000 - game_data.ranks.at(8) + 1000);
    flt();
    itemcreate(
        -1,
        55,
        cdata.player().position.x,
        cdata.player().position.y,
        clamp(4 - game_data.ranks.at(8) / 2500, 1, 4));
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    modrank(8, 500, 8);
}

TalkResult talk_unique_doria()
{
    if (game_data.guild.belongs_to_fighters_guild == 0)
    {
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get("core.locale.talk.unique.doria.nonmember.choices.tell_"
                        "me_about"));
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get("core.locale.talk.unique.doria.nonmember.choices.want_"
                        "to_join"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        buff = i18n::s.get("core.locale.talk.unique.doria.nonmember.dialog");
        chatval_ = talk_window_query();
        if (chatval_ == 2)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.doria.nonmember.tell_me_about");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_unique;
        }
        if (chatval_ == 1)
        {
            if (game_data.guild.joining_fighters_guild == 0)
            {
                listmax = 0;
                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.doria.nonmember.want_to_join", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;

                _doria_start_trial();

                buff = i18n::s.get_enum(
                    "core.locale.talk.unique.doria.nonmember.want_to_join",
                    1,
                    game_data.guild.fighters_guild_quota,
                    chara_refstr(game_data.guild.fighters_guild_target, 2));
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_unique;
            }
            if (game_data.guild.fighters_guild_quota > 0)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.doria.nonmember.quota",
                    game_data.guild.fighters_guild_quota,
                    chara_refstr(game_data.guild.fighters_guild_target, 2));
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return TalkResult::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.lexus.nonmember.end", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _doria_join_fighters_guild();

            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.unique.doria.nonmember.end", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _doria_move_self();
        }
        return TalkResult::talk_end;
    }
    _doria_move_self();

    if (game_data.guild.fighters_guild_quota_recurring == 0)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.lexus.member.choices.new_quota"));
    }
    else
    {
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get(
                "core.locale.talk.unique.lexus.member.choices.report_quota"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    buff = i18n::s.get(
        "core.locale.talk.unique.doria.member.dialog",
        ranktitle(8),
        cdatan(0, 0));
    chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        _doria_update_quota();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.doria.member.new_quota",
            game_data.guild.fighters_guild_quota,
            chara_refstr(game_data.guild.fighters_guild_target, 2));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_unique;
    }
    if (chatval_ == 2)
    {
        if (game_data.guild.fighters_guild_quota > 0)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.lexus.member.report_quota.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_unique;
        }

        _doria_receive_reward();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.lexus.member.report_quota.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    return TalkResult::talk_end;
}


void _conery_receive_reward()
{
    flt();
    nostack = 1;
    itemcreate(
        -1, 630, cdata.player().position.x, cdata.player().position.y, 0);
    change_item_material(inv[ci], 31);
    flt();
    itemcreate(
        -1, 54, cdata.player().position.x, cdata.player().position.y, 50000);
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, 4);
    txt(i18n::s.get("core.locale.quest.completed"));
    snd("core.complete1");
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    game_data.quest_flags.minotaur_king = 1000;
}

TalkResult talk_unique_conery()
{
    if (game_data.quest_flags.minotaur_king == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.minotaur_king == 0)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get("core.locale.talk.unique.conery.quest.choices.do_it"));
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.unique.conery.quest.choices.bye"));
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.dialog");
        chatval_ = talk_window_query();
        if (chatval_ != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.conery.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return TalkResult::talk_end;
        }
        quest_update_journal_msg();
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.conery.quest.do_it", cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        game_data.quest_flags.minotaur_king = 1;

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.minotaur_king == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.minotaur_king == 2)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        _conery_receive_reward();

        return TalkResult::talk_end;
    }
    return TalkResult::talk_ignored;
}

void _rogue_boss_surrender()
{
    snd("core.paygold1");
    cdata.player().gold -= cdata.player().gold / 5;
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number() > 0)
        {
            if (the_item_db[inv[cnt].id]->is_cargo)
            {
                txt(i18n::s.get(
                    "core.locale.talk.npc.common.hand_over", inv[cnt]));
                inv[cnt].remove();
            }
        }
    }
    refresh_burden_state();
}

void _rogue_boss_leave_map()
{
    levelexitby = 4;
    chatteleport = 1;
    snd("core.exitmap1");
}

TalkResult talk_unique_rogue_boss()
{
    if (cdata.player().gold <= 10)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.rogue_boss.too_poor", cdata[tc]);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    ELONA_APPEND_RESPONSE(
        1,
        i18n::s.get(
            "core.locale.talk.unique.rogue_boss.ambush.choices.try_me"));
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get(
            "core.locale.talk.unique.rogue_boss.ambush.choices.surrender"));
    buff = i18n::s.get(
        "core.locale.talk.unique.rogue_boss.ambush.dialog",
        gdatan(1),
        (cdata.player().gold / 5),
        cdata[tc]);
    chatesc = 0;
    chatval_ = talk_window_query();
    if (chatval_ == 0)
    {
        _rogue_boss_surrender();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.rogue_boss.ambush.surrender", cdata[tc]);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        _rogue_boss_leave_map();

        return TalkResult::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.unique.rogue_boss.ambush.try_me", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return TalkResult::talk_end;
}


void _strange_scientist_receive_little_balls()
{
    game_data.quest_flags.little_sister = 0;
    flt();
    itemcreate(
        -1, 699, cdata.player().position.x, cdata.player().position.y, 0);
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    quest_update_journal_msg();
    game_data.quest_flags.little_sister = 1;
}

bool _strange_scientist_can_receive_reward()
{
    p = game_data.quest_flags.kill_count_of_little_sister;
    for (int cnt = 1,
             cnt_end =
                 cnt + (game_data.quest_flags.gift_count_of_little_sister + 1);
         cnt < cnt_end;
         ++cnt)
    {
        p += cnt;
    }

    return game_data.quest_flags.save_count_of_little_sister >= p || 0;
}

void _strange_scientist_pick_reward()
{
    begintempinv();
    mode = 6;
    flt();
    itemcreate(-1, 283, -1, -1, 0);
    flt();
    itemcreate(-1, 284, -1, -1, 0);
    for (int cnt = 0; cnt < 800; ++cnt)
    {
        if (cnt == 672)
        {
            continue;
        }
        randomize(game_data.date.day + cnt);
        f = 0;
        if (itemmemory(0, cnt))
        {
            f = 1;
        }
        if (cnt == 662)
        {
            if (game_data.quest_flags.kamikaze_attack >= 1000)
            {
                f = 1;
            }
        }
        if (cnt == 655)
        {
            if (game_data.quest_flags.rare_books >= 1000)
            {
                f = 1;
            }
        }
        if (cnt == 639)
        {
            if (game_data.quest_flags.pael_and_her_mom >= 1000)
            {
                f = 1;
            }
        }
        if (f)
        {
            flt(cdata.player().level * 3 / 2, calcfixlv(Quality::good));
            int stat = itemcreate(-1, cnt, -1, -1, 0);
            if (stat == 1)
            {
                if (inv[ci].quality < Quality::miracle)
                {
                    inv[ci].remove();
                }
            }
        }
        randomize();
    }
    txt(
        i18n::s.get("core.locale.talk.unique.strange_scientist."
                    "reward.choose_one"));
    invsubroutine = 1;
    invctrl(0) = 22;
    invctrl(1) = 4;
    ctrl_inventory();
    exittempinv();
    mode = 0;
}

void _strange_scientist_replenish_little_balls()
{
    flt();
    itemcreate(
        -1, 699, cdata.player().position.x, cdata.player().position.y, 0);
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
}

void _strange_scientist_turn_over()
{
    txt(i18n::s.get(
        "core.locale.talk.unique.strange_scientist.turn_over.text"));
    ++game_data.quest_flags.save_count_of_little_sister;
    txt(i18n::s.get(
            "core.locale.talk.unique.strange_scientist.saved_count",
            game_data.quest_flags.save_count_of_little_sister,
            game_data.quest_flags.kill_count_of_little_sister),
        Message::color{ColorIndex::green});
    chara_vanquish(chara_find_ally(319));
    snd("core.complete1");
}

TalkResult talk_unique_strange_scientist()
{
    if (game_data.quest_flags.little_sister == 0)
    {
        listmax = 0;
        i18n::s.get("core.locale.talk.unique.strange_scientist.first");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();

        _strange_scientist_receive_little_balls();

        return TalkResult::talk_end;
    }
    if (game_data.quest_flags.little_sister > 0)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.strange_scientist.choices.reward"));
        ELONA_APPEND_RESPONSE(
            2,
            i18n::s.get(
                "core.locale.talk.unique.strange_scientist.choices.replenish"));
        if (chara_find_ally(319) != -1)
        {
            ELONA_APPEND_RESPONSE(
                3,
                i18n::s.get("core.locale.talk.unique.strange_scientist.choices."
                            "turn_over"));
        }
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        i18n::s.get("core.locale.talk.unique.strange_scientist.dialog");
        chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            if (_strange_scientist_can_receive_reward())
            {
                listmax = 0;
                i18n::s.get(
                    "core.locale.talk.unique.strange_scientist.reward.dialog");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();

                _strange_scientist_pick_reward();

                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.strange_scientist.reward.find");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            else
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.strange_scientist.reward.not_"
                    "enough");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            return TalkResult::talk_end;
        }
        if (chatval_ == 2)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.strange_scientist.replenish");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _strange_scientist_replenish_little_balls();

            return TalkResult::talk_end;
        }
        if (chatval_ == 3)
        {
            _strange_scientist_turn_over();

            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.strange_scientist.turn_over.dialog");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        return TalkResult::talk_end;
    }
    return TalkResult::talk_ignored;
}


void _kaneda_bike_join_party()
{
    rc = tc;
    new_ally_joins();
    game_data.quest_flags.blue_capsule_drug = 0;
}

void _kaneda_bike_give_drug()
{
    int stat = inv_find(771, 0);
    inv[stat].modify_number(-1);
    txt(
        i18n::s.get("core.locale.talk.unique.kaneda_bike.before_"
                    "drug.yes.you_hand_him"));
    snd("core.equip1");
}

TalkResult talk_unique_kaneda_bike()
{
    if (game_data.quest_flags.blue_capsule_drug >= 3)
    {
        buff = i18n::s.get(
            "core.locale.talk.unique.kaneda_bike.after_drug.dialog");
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.kaneda_bike.after_drug.choices.yes"));
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get(
                "core.locale.talk.unique.kaneda_bike.after_drug.choices.no"));
        chatesc = 1;
        chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            f = chara_get_free_slot_ally();
            if (f == 0)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.kaneda_bike.after_drug.yes.party_"
                    "full");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.unique.kaneda_bike.after_drug.yes.dialog");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();

            _kaneda_bike_join_party();

            return TalkResult::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.no");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    {
        int stat = inv_find(771, 0);
        if (stat != -1)
        {
            buff = i18n::s.get(
                "core.locale.talk.unique.kaneda_bike.before_drug.dialog");
            ELONA_APPEND_RESPONSE(
                1,
                i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug."
                            "choices.yes"));
            ELONA_APPEND_RESPONSE(
                0,
                i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug."
                            "choices.no"));
            chatesc = 1;
            chatval_ = talk_window_query();
            if (chatval_ == 1)
            {
                _kaneda_bike_give_drug();

                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.unique.kaneda_bike.before_drug.yes."
                    "dialog");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();

                ++game_data.quest_flags.blue_capsule_drug;

                return TalkResult::talk_end;
            }
        }
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.do_not_have_drug");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return TalkResult::talk_end;
}


void _part_time_worker_switch_religion()
{
    flt();
    itemcreate(
        -1, 767, cdata.player().position.x, cdata.player().position.y, 0);
    cdata.player().god_id = core_god::int2godid(6);
    switch_religion();
}

TalkResult talk_unique_part_time_worker()
{
    if (game_data.current_map != mdata_t::MapId::noyel ||
        !area_data[game_data.current_map].christmas_festival)
    {
        return TalkResult::talk_end;
    }
    if (cdata.player().god_id == core_god::jure)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.unique.part_time_worker.already_believe_in_jure");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.locale.talk.unique.part_time_worker.choices.yes"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.unique.part_time_worker.choices.no"));
    buff = i18n::s.get("core.locale.talk.unique.part_time_worker.dialog");
    chatesc = 1;
    chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.unique.part_time_worker.yes.choices.yes"));
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get(
                "core.locale.talk.unique.part_time_worker.yes.choices.no"));
        buff =
            i18n::s.get("core.locale.talk.unique.part_time_worker.yes.dialog");
        chatesc = 1;
        chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            listmax = 0;
            buff =
                i18n::s.get("core.locale.talk.unique.part_time_worker.yes.yes");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            txt(i18n::s.get(
                "core.locale.common.something_is_put_on_the_ground"));

            _part_time_worker_switch_religion();

            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.part_time_worker.no");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.ui.bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return TalkResult::talk_end;
}

} // namespace

TalkResult talk_unique()
{
    listmax = 0;

    auto& chara = cdata[tc];
    const auto& dialog_id = the_character_db[chara.id]->dialog_id;

    if (dialog_id)
    {
        dialog_start(chara, *dialog_id);
        return TalkResult::talk_end;
    }

    switch (*chatval_unique_chara_id)
    {
    case 243: return talk_unique_arnord();
    case 247: return talk_unique_mia();
    case 252: return talk_unique_renton();
    case 253: return talk_unique_marks();
    case 259: return talk_unique_noel();
    case 279: return talk_unique_icolle();
    case 280: return talk_unique_balzak();
    case 290: return talk_unique_lexus();
    case 294: return talk_unique_abyss();
    case 297: return talk_unique_doria();
    case 301: return talk_unique_conery();
    case 302: return talk_unique_rogue_boss();
    case 322: return talk_unique_strange_scientist();
    case 345: return talk_unique_kaneda_bike();
    case 348: return talk_unique_part_time_worker();
    }
    return TalkResult::talk_ignored;
}

} // namespace elona
