#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "crafting.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
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
talk_result_t talk_unique_zeome()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.zeome");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    gdata_main_quest_flag = 170;
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_23()
{
    if (event_id() == 1)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.orphe.dialog", 0,
                           i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.orphe.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.orphe.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.orphe.dialog", 3);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.orphe.dialog", 4);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.orphe.dialog", 5);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_28()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.whom_dwell_in_the_vanity");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_29()
{
    if (cdata[0].fame < 20000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.loyter.fame_too_low");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_nightmare == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.loyter.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_nightmare == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.loyter.quest.dialog", 0, cdatan(1, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.loyter.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.loyter.quest.choices.no"));
        buff = i18n::s.get_enum("core.locale.talk.unique.loyter.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.loyter.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.loyter.quest.yes");;
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_nightmare = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_nightmare == 1 || gdata_nightmare == 2)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.loyter.quest.begin.choices.yes"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.loyter.quest.begin.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.loyter.quest.begin.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.loyter.quest.begin.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.loyter.quest.begin.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_nightmare = 2;
        mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
        gdata_destination_map = 5;
        gdata_destination_dungeon_level = 5;
        levelexitby = 2;
        chatteleport = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_nightmare == 3)
    {
        flt();
        nostack = 1;
        itemcreate(-1, 630, cdata[0].position.x, cdata[0].position.y, 0);
        fixmaterial = 15;
        change_item_material();
        flt();
        itemcreate(
                -1, 54, cdata[0].position.x, cdata[0].position.y, 100000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 5);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.loyter.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_nightmare = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_30()
{
    if (gdata_putit_attacks == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miches.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_putit_attacks == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.miches.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.miches.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.miches.quest.choices.no"));
        buff = i18n::s.get_enum("core.locale.talk.unique.miches.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.miches.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miches.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_putit_attacks = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_putit_attacks == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miches.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_putit_attacks == 2)
    {
        flt(calcobjlv(10), calcfixlv(3));
        itemcreate(-1, 449, cdata[0].position.x, cdata[0].position.y, 0);
        flt(calcobjlv(10), calcfixlv(3));
        itemcreate(-1, 66, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 3000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miches.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_putit_attacks = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_31()
{
    if (gdata_thieves_hideout == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.shena.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_thieves_hideout == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.shena.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.shena.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.shena.quest.choices.no"));
        buff = i18n::s.get_enum("core.locale.talk.unique.shena.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.shena.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.shena.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_thieves_hideout = 1;
        cell_featset(48, 5, tile_downstairs, 11, 4);
        return talk_result_t::talk_end;
    }
    if (gdata_thieves_hideout == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.shena.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_thieves_hideout == 2)
    {
        flt();
        itemcreate(-1, 18, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].count = 12;
        flt();
        nostack = 1;
        itemcreate(-1, 685, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].param2 = 5;
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 1500);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.shena.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_thieves_hideout = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_33()
{
    ELONA_APPEND_RESPONSE(
            3, i18n::s.get("core.locale.talk.unique.larnneire.choices.mission"));
    ELONA_APPEND_RESPONSE(
            2, i18n::s.get("core.locale.talk.unique.larnneire.choices.north_tyris"));
    ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.unique.larnneire.choices.fairy_tale"));
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.larnneire.dialog");
    talk_window_query();
    if (chatval == 1)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.fairy_tale", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.fairy_tale", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.fairy_tale", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.fairy_tale", 3);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.fairy_tale", 4);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.fairy_tale", 5);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    if (chatval == 2)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.north_tyris", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.larnneire.north_tyris", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    if (chatval == 3)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.larnneire.mission");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_34()
{
    if (chatflag == 0)
    {
        if (gdata_tutorial_flag == 0)
        {
            buff = i18n::s.get("core.locale.talk.unique.lomias.tutorial.before.dialog");
            ELONA_APPEND_RESPONSE(
                    1, i18n::s.get("core.locale.talk.unique.lomias.tutorial.before.choices.yes"));
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.before.choices.no"));
        }
        if (gdata_tutorial_flag == 1)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.dialog", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.dialog", 3);
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.movement.choices.alright"));
            ELONA_APPEND_RESPONSE(
                    3, i18n::s.get("core.locale.talk.unique.lomias.tutorial.movement.choices.ate"));
        }
        if (gdata_tutorial_flag == 2)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.skills.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.skills.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.skills.dialog", 2);
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.skills.response"));
        }
        if (gdata_tutorial_flag == 3)
        {
            txt(i18n::s.get(
                        "core.locale.common.something_is_put_on_the_ground"));
            flt();
            itemcreate(-1, 14, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].identification_state =
                identification_state_t::completely_identified;
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lomias.tutorial.after_dig.dialog");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_tutorial_flag = 4;
        }
        if (gdata_tutorial_flag == 4)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.identify.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.identify.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.identify.dialog", 2);
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.identify.choices.alright"));
            ELONA_APPEND_RESPONSE(
                    4, i18n::s.get("core.locale.talk.unique.lomias.tutorial.identify.choices.done"));
        }
        if (gdata_tutorial_flag == 5)
        {
            buff = i18n::s.get("core.locale.talk.unique.lomias.tutorial.equip.dialog");
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.equip.choices.alright"));
            ELONA_APPEND_RESPONSE(
                    5, i18n::s.get("core.locale.talk.unique.lomias.tutorial.equip.choices.done"));
        }
        if (gdata_tutorial_flag == 6)
        {
            p = chara_find(3);
            if (p != 0)
            {
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.lomias.tutorial.combat.not_finished");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lomias.tutorial.combat.finished");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_tutorial_flag = 7;
        }
        if (gdata_tutorial_flag == 7)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.chests.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.chests.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(
                    -1, 240, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].param1 = 35;
            inv[ci].param2 = 25;
            flt();
            itemcreate(
                    -1, 636, cdata[0].position.x, cdata[0].position.y, 2);
            txt(i18n::s.get(
                        "core.locale.common.something_is_put_on_the_ground"));
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.chests.dialog", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.chests.response"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_tutorial_flag = 8;
            return talk_result_t::talk_end;
        }
        if (gdata_tutorial_flag == 8)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.house.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.house.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.house.dialog", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.house.dialog", 3);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_tutorial_flag = 99;
        }
        if (gdata_tutorial_flag == 99)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.end.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.end.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_tutorial_flag = -1;
            return talk_result_t::talk_end;
        }
        if (gdata_tutorial_flag == -1)
        {
            buff = i18n::s.get("core.locale.talk.unique.lomias.after.dialog");
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.lomias.after.choices.nothing"));
        }
        if (gdata_tutorial_flag == 0 || gdata_tutorial_flag == -1)
        {
            ELONA_APPEND_RESPONSE(
                    2,
                    i18n::s.get("core.locale.talk.unique.lomias.after.choices.get_out"));
        }
        talk_window_query();
    }
    if (chatval == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.lomias.tutorial.before.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 204, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].subname = 9;
        inv[ci].identification_state =
            identification_state_t::completely_identified;
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        gdata_tutorial_flag = 1;
        return talk_result_t::talk_unique;
    }
    if (chatval == 2)
    {
        tc = chara_find(33);
        if (tc == 0 || cdata[tc].state != 1)
        {
            tc = chara_find(34);
            hostileaction(0, tc);
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lomias.after.get_out.larnneire_died");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.after.get_out.dialog", 0, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.after.get_out.dialog", 1);
        tc = tc * (chara_find(34) == 0)
            + (chara_find(34) != 0) * chara_find(34);
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.after.get_out.dialog", 2, cdatan(1, 0));
        tc = tc * (chara_find(33) == 0)
            + (chara_find(33) != 0) * chara_find(33);
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        chara_vanquish(chara_find(33));
        chara_vanquish(chara_find(34));
        txt(i18n::s.get("core.locale.talk.unique.lomias.after.get_out.leave"));
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            flttypemajor = 60000;
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        }
    }
    if (chatval == 3)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.ate.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.lomias.tutorial.movement.ate.response"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.ate.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.movement.ate.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_tutorial_flag = 2;
        return talk_result_t::talk_unique;
    }
    if (chatval == 4)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.identify.done.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.identify.done.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 58, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].curse_state = curse_state_t::cursed;
        flt();
        itemcreate(-1, 61, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].curse_state = curse_state_t::none;
        flt();
        itemcreate(-1, 363, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].identification_state =
            identification_state_t::completely_identified;
        inv[ci].curse_state = curse_state_t::blessed;
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        gdata_tutorial_flag = 5;
        return talk_result_t::talk_unique;
    }
    if (chatval == 5)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.equip.done.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.equip.done.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.lomias.tutorial.equip.done.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        txtef(9);
        txt(i18n::s.get("core.locale.talk.unique.lomias.tutorial.equip.done.lomias_releases"));
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            chara_create(-1, 3, cdata[0].position.x, cdata[0].position.y);
            cdata[rc].does_not_search_enemy() = true;
        }
        flt();
        itemcreate(-1, 68, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].identification_state =
            identification_state_t::completely_identified;
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        gdata_tutorial_flag = 6;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_79()
{
    if (gdata_main_quest_flag == 200)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.stersha.late");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag < 90)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.stersha.early");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    else
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.stersha.mid");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_80()
{
    if (gdata_main_quest_flag >= 60)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.xabi.late");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag == 50)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.xabi.mid");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag == 40)
    {
        gdata_main_quest_flag = 50;
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.xabi.early", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        update_screen();
        fade_out();
        gsel(4);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
        gsel(0);
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.xabi.early", 1, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 2500);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
        flt();
        itemcreate(-1, 559, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 621, cdata[0].position.x, cdata[0].position.y, 0);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        return talk_result_t::talk_unique;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_139()
{
    if (gdata_main_quest_flag == 20)
    {
        gdata_main_quest_flag = 30;
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.slan.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.slan.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.slan.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
            flttypemajor = fltsetdungeon();
            itemcreate(
                    -1, 0, cdata[tc].position.x, cdata[tc].position.y, 0);
        }
        flt();
        itemcreate(
                -1,
                54,
                cdata[tc].position.x,
                cdata[tc].position.y,
                1000 + rnd(200));
        flt();
        itemcreate(-1, 55, cdata[tc].position.x, cdata[tc].position.y, 3);
        flt();
        itemcreate(-1, 239, cdata[tc].position.x, cdata[tc].position.y, 0);
        inv[ci].param2 = 0;
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.talk.unique.slan.you_receive"));
        txt(i18n::s.get("core.locale.talk.unique.slan.dies", cdata[tc]));
        chara_vanquish(tc);
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_142()
{
    if (gdata_main_quest_flag == 200)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.late", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.late", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.late", 2,
                                cdatan(1, 0), cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag == 120)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.all_stones.dialog", 0, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.all_stones.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.all_stones.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.all_stones.dialog", 3, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.talk.unique.erystia.all_stones.you_receive"));
        flt();
        itemcreate(-1, 360, cdata[0].position.x, cdata[0].position.y, 0);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        gdata_main_quest_flag = 125;
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag == 105)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.stones.dialog", 0, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        update_screen();
        fade_out();
        gsel(4);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
        gsel(0);
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.stones.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.stones.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.stones.dialog", 3);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.stones.dialog", 4);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.talk.unique.erystia.stones.you_receive"));
        gdata_main_quest_flag = 110;
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag >= 60)
    {
        buff = i18n::s.get("core.locale.talk.unique.erystia.investigation.dialog", cdatan(0, 0));
        ELONA_APPEND_RESPONSE(
                6, i18n::s.get("core.locale.talk.unique.erystia.investigation.choices.lesimas"));
        ELONA_APPEND_RESPONSE(
                5, i18n::s.get("core.locale.talk.unique.erystia.investigation.choices.mission"));
        if (gdata_main_quest_flag >= 100 && gdata_main_quest_flag <= 120)
        {
            ELONA_APPEND_RESPONSE(
                3, i18n::s.get("core.locale.talk.unique.erystia.investigation.choices.stones.castle"));
            ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.erystia.investigation.choices.stones.inferno"));
            ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.erystia.investigation.choices.stones.crypt"));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 6)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.lesmias", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.lesmias", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.lesmias", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.lesmias", 3);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.lesmias", 4);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 5)
        {
            if (gdata_main_quest_flag >= 125)
            {
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.mission.excavation", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.mission.excavation", 1);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (gdata_main_quest_flag >= 110)
            {
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.mission.stones", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.mission.stones", 1,
                                    cdatan(0, 0));
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 3)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.castle", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.castle", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.castle", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 2)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.inferno", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.inferno", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.inferno", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 1)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.crypt", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.crypt", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.erystia.investigation.crypt", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        return talk_result_t::talk_end;
    }
    if (gdata_main_quest_flag == 50)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.erystia.introduction.dialog", cdatan(0, 0));
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.erystia.introduction.choices.pledge_strength"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.erystia.introduction.choices.not_interested"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.erystia.introduction.not_interested");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.introduction.pledge_strength.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.introduction.pledge_strength.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.introduction.pledge_strength.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.erystia.introduction.pledge_strength.dialog", 3,
                                cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.talk.unique.erystia.introduction.pledge_strength.you_receive"));
        gdata_main_quest_flag = 60;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_146()
{
    if (gdata_main_quest_flag == 90)
    {
        gdata_main_quest_flag = 100;
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.karam.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.karam.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.karam.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.karam.dialog", 3);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.karam.dialog", 4);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.karam.dialog", 5);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
            flttypemajor = fltsetdungeon();
            itemcreate(
                    -1, 0, cdata[tc].position.x, cdata[tc].position.y, 0);
        }
        flt();
        itemcreate(
                -1,
                54,
                cdata[tc].position.x,
                cdata[tc].position.y,
                1000 + rnd(200));
        flt();
        itemcreate(-1, 55, cdata[tc].position.x, cdata[tc].position.y, 3);
        flt();
        itemcreate(-1, 239, cdata[tc].position.x, cdata[tc].position.y, 0);
        inv[ci].param2 = 0;
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        txt(i18n::s.get("core.locale.talk.unique.karam.dies", cdata[tc]));
        chara_vanquish(tc);
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_208()
{
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.garokk");
    talk_window_query();
    if (chatval == 1)
    {
        invctrl = 1;
        snd(26);
        crafting_menu();
        return talk_result_t::talk_unique;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_209()
{
    ELONA_APPEND_RESPONSE(
            2, i18n::s.get("core.locale.talk.unique.miral.choices.small_medals"));
    ELONA_APPEND_RESPONSE(
            3, i18n::s.get("core.locale.talk.unique.miral.choices.upgrade_cart"));
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.miral.dialog");
    talk_window_query();
    if (chatval == 2)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miral.small_medals");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        invctrl = 28;
        invfile = cdata[tc].shop_store_id;
        shop_sell_item();
        screenupdate = -1;
        update_screen();
        cs = 0;
        return talk_result_t::talk_unique;
    }
    if (chatval == 3)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miral.upgrade_cart.dialog",
                           calccargoupdatecost());
        int stat = item_find(622, 3, 1);
        if (stat != -1)
        {
            ci = stat;
            if (inv[ci].number >= calccargoupdatecost())
            {
                ELONA_APPEND_RESPONSE(
                    1, i18n::s.get("core.locale.talk.unique.miral.upgrade_cart.choices.give"));
            }
        }
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.miral.upgrade_cart.choices.go_back"));
        chatesc = 1;
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.miral.upgrade_cart.go_back");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        txtnew();
        txt(i18n::s.get("core.locale.talk.unique.miral.upgrade_cart.give.limit_increased",
                        cnvweight(calccargoupdate())));
        snd(58);
        inv[ci].number -= calccargoupdatecost();
        gdata_current_cart_limit += calccargoupdate();
        refresh_burden_state();
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.miral.upgrade_cart.give.dialog");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_221()
{
    if (gdata_pael_and_her_mom == 1000)
    {
        if (gdata_current_map == 33 && adata(29, gdata_current_map))
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.pael.festival");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.pael.after_face");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 1001)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.pael.after_death");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 1002)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.pael.after_sold");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 0)
    {
        buff = i18n::s.get("core.locale.talk.unique.pael.before");
        bool stat = talk_give_potion_of_cure_corruption();
        if (!stat)
        {
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_pael_and_her_mom = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 1 || gdata_pael_and_her_mom == 3)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 5 || gdata_pael_and_her_mom == 7)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 1, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 2 || gdata_pael_and_her_mom == 4)
    {
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 2, cdatan(0, 0));
        bool stat = talk_give_potion_of_cure_corruption();
        if (!stat)
        {
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        ++gdata_pael_and_her_mom;
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 6)
    {
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 3);

        bool stat = talk_give_potion_of_cure_corruption();
        if (!stat)
        {
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        ++gdata_pael_and_her_mom;
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 8)
    {
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 4, cdatan(0, 0));
        bool stat = talk_give_potion_of_cure_corruption();
        if (!stat)
        {
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        ++gdata_pael_and_her_mom;
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 9)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 5);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 10)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.pael.progress", 6, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_222()
{
    if (gdata_pael_and_her_mom == 1002)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.paels_mom.after_sold");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom == 10)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.paels_mom.progress.last", 0, cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.paels_mom.progress.last", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 639, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 20000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
        snd(51);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.paels_mom.progress.last", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_pael_and_her_mom = 1000;
        cdata[tc].is_silent() = true;
    }
    if (gdata_pael_and_her_mom == 1000)
    {
        if (gdata_current_map == 33 && adata(29, gdata_current_map))
        {
            buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.festival.dialog");
            int stat = inv_find(559, 0);
            if (stat != -1)
            {
                ELONA_APPEND_RESPONSE(
                    2, i18n::s.get("core.locale.talk.unique.paels_mom.progress.festival.choices.give"));
            }
            ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.paels_mom.progress.festival.choices.take_care"));
            chatesc = 1;
            talk_window_query();
            if (chatval == 2)
            {
                int stat = inv_find(559, 0);
                --inv[stat].number;
                txt(i18n::s.get("core.locale.talk.unique.paels_mom.progress.festival.give.you_hand_her"));
                snd(13);
                modify_karma(0, 20);
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.festival.give.dialog");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.festival.take_care");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
    }
    if (gdata_pael_and_her_mom == 1000)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.paels_mom.progress.end_life.dialog", 0,
                                cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        buff = i18n::s.get_enum("core.locale.talk.unique.paels_mom.progress.end_life.dialog", 1);
        int stat = inv_find(559, 0);
        if (stat != -1)
        {
            ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.choices.give"));
        }
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.choices.end"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.choices.leave"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.end");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            event_add(20, tc);
            return talk_result_t::talk_end;
        }
        if (chatval == 2)
        {
            int stat = inv_find(559, 0);
            --inv[stat].number;
            txt(i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.give.you_hand_her"));
            snd(13);
            modify_karma(0, 20);
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.give.dialog");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.end_life.leave");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom > 7)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.very_late");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom > 5)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.late", cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pael_and_her_mom > 3)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.mid");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.paels_mom.progress.early");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_223()
{
    if (gdata_wife_collector == 0)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.raphael.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.raphael.quest.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.raphael.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.raphael.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.raphael.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_wife_collector = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_wife_collector == 1 || gdata_wife_collector == 1000)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.raphael.bring_wife.choices.this_one"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.raphael.bring_wife.choices.go_back"));
        buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.go_back");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        allyctrl = 1;
        int stat = ctrl_ally();
        if (stat == -1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.this_one.no_such_wife");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        rc = stat;
        if (cdata[rc].is_married() == 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.this_one.not_married");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.this_one.come_along",
                           cdatan(0, rc));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        tcbk = tc;
        tc = rc;
        s = chara_refstr(cdata[tc].id, 8);
        if (!strutil::contains(s(0), u8"/man/"))
        {
            dmgcon(tcbk, status_ailment_t::insane, 1000);
            f = 1;
            modify_karma(0, 2);
        }
        else
        {
            f = 0;
            modify_karma(0, -15);
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.this_one.leaving");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        tc = tcbk;
        if (f == 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.this_one.not_human");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (gdata_wife_collector == 1)
        {
            flt();
            itemcreate(
                    -1, 54, cdata[0].position.x, cdata[0].position.y, 5000);
            txt(i18n::s.get("core.locale.quest.completed"));
            snd(51);
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
            gdata_wife_collector = 1000;
        }
        chara_vanquish(rc);
        snd(51);
        flt();
        itemcreate(-1, 640, cdata[0].position.x, cdata[0].position.y, 2);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.raphael.bring_wife.this_one.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_224()
{
    if (gdata_novice_knight == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.ainc.complete", cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_novice_knight == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.ainc.quest.choices.do_it"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get("core.locale.talk.unique.ainc.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.ainc.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.ainc.quest.do_it");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_novice_knight = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_novice_knight == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.ainc.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_novice_knight == 2)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.ainc.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 661, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 5000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_novice_knight = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_225()
{
    if (gdata_puppys_cave == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.poppy.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (chara_get_free_slot_ally() != 0)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.poppy.find.choices.take"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.poppy.find.dialog");
    talk_window_query();
    if (chatval == 1)
    {
        txt(i18n::s.get("core.locale.talk.unique.poppy.find.you_must_return", cdata[tc]));
        rc = tc;
        new_ally_joins();
        cdata[rc].is_escorted_in_sub_quest() = true;
        chara_refresh(rc);
        return talk_result_t::talk_end;
    }
    else
    {
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_226()
{
    if (gdata_puppys_cave == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.rilian.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_puppys_cave == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.rilian.quest.choices.do_it"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get("core.locale.talk.unique.rilian.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.rilian.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.rilian.quest.do_it");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_puppys_cave = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_puppys_cave == 1)
    {
        if (chara_find_ally(225) == -1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.rilian.quest.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.rilian.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 641, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 2500);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_puppys_cave = 1000;
        chara_vanquish(chara_find_ally(225));
        flt();
        chara_create(-1, 225, 31, 4);
        cdata[rc].character_role = 3;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_227()
{
    if (gdata_cat_house == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.tam.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_cat_house == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.tam.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.tam.quest.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.tam.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.tam.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.tam.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_cat_house = 1;
        cell_featset(23, 22, tile_downstairs, 11, 3);
        return talk_result_t::talk_end;
    }
    if (gdata_cat_house == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.tam.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_cat_house == 2)
    {
        flt();
        nostack = 1;
        itemcreate(-1, 630, cdata[0].position.x, cdata[0].position.y, 0);
        fixmaterial = 24;
        change_item_material();
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 25500);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.tam.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_cat_house = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_231()
{
    if (gdata_defense_line == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.gilbert.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (cdata[0].fame < 5000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.gilbert.fame_too_low");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_defense_line == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.gilbert.quest.dialog", 0,
                                cdatan(1, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.gilbert.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.gilbert.quest.choices.no"));
        buff = i18n::s.get_enum("core.locale.talk.unique.gilbert.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.gilbert.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.gilbert.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_defense_line = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_defense_line == 1 || gdata_defense_line == 2)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.gilbert.quest.begin.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.gilbert.quest.begin.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.gilbert.quest.begin.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.gilbert.quest.begin.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.gilbert.quest.begin.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_defense_line = 2;
        mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
        gdata_destination_map = 12;
        gdata_destination_dungeon_level = 4;
        levelexitby = 2;
        chatteleport = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_defense_line == 3)
    {
        flt();
        itemcreate(-1, 655, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 10000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.gilbert.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_defense_line = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_243()
{
    if (gdata_kamikaze_attack == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.complete", cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_kamikaze_attack == 0)
    {
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.dialog");
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.arnord.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.arnord.quest.choices.no"));
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.arnord.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_kamikaze_attack = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_kamikaze_attack == 1 || gdata_kamikaze_attack == 2)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.arnord.quest.begin.choices.yes"));
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.arnord.quest.begin.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.begin.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.arnord.quest.begin.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.begin.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_kamikaze_attack = 2;
        mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
        gdata_destination_map = 11;
        gdata_destination_dungeon_level = 25;
        levelexitby = 2;
        chatteleport = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_kamikaze_attack == 3)
    {
        flt();
        itemcreate(-1, 662, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 7500);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.arnord.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_kamikaze_attack = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_247()
{
    if (gdata_mias_dream == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.mia.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_mias_dream == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.mia.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.mia.quest.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.mia.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.mia.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.mia.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_mias_dream = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_mias_dream == 1)
    {
        if (chara_find_ally(246) == -1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.mia.quest.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.mia.quest.end", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.mia.quest.end", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 663, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 5000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_mias_dream = 1000;
        chara_relocate(chara_find_ally(246), -1);
        cdata[rc].relationship = -1;
        cdata[rc].original_relationship = -1;
        cdata[rc].character_role = 3;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_252()
{
    if (gdata_rare_books == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.renton.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_rare_books == 0 || gdata_rare_books == 1)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 1);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 2);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.dialog", 3);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        if (gdata_rare_books == 0)
        {
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
            gdata_rare_books = 1;
            return talk_result_t::talk_end;
        }
        p(0) = 0;
        p(1) = 0;
        p(2) = 0;
        p(3) = 0;
        p(4) = 0;
        p(5) = 0;
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number == 0)
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
                buff = i18n::s.get("core.locale.talk.unique.renton.quest.brought", p(0));
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            p(0) = 0;
            p(1) = 0;
            p(2) = 0;
            p(3) = 0;
            p(4) = 0;
            p(5) = 0;
            for (const auto& cnt : items(0))
            {
                if (inv[cnt].number == 0)
                {
                    continue;
                }
                if (inv[cnt].id == 668)
                {
                    if (p(inv[cnt].param2) == 0)
                    {
                        --inv[cnt].number;
                        p(inv[cnt].param2) = 1;
                    }
                }
            }
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.brought_all.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = u8"…"s;
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = u8"… …"s;
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = u8"… … …"s;
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.brought_all.dialog", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            txtef(5);
            txt(i18n::s.get("core.locale.talk.unique.renton.quest.brought_all.ehekatl"));
            txt(i18n::s.get("core.locale.quest.completed"));
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.renton.quest.brought_all.dialog", 2);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(
                    -1, 666, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(
                    -1, 655, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(
                    -1, 54, cdata[0].position.x, cdata[0].position.y, 20000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 5);
            txt(i18n::s.get("core.locale.quest.completed"));
            snd(51);
            txt(i18n::s.get(
                        "core.locale.common.something_is_put_on_the_ground"));
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
            gdata_rare_books = 1000;
        }
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_253()
{
    if (gdata_pyramid_trial != 0)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.marks.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (cdata[0].fame < 3000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.marks.fame_too_low");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_pyramid_trial == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.marks.quest.dialog", 0,
                                cdatan(1, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        if (cdata[0].gold >= 20000)
        {
            ELONA_APPEND_RESPONSE(
                    1, i18n::s.get("core.locale.talk.unique.marks.quest.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get_enum("core.locale.talk.unique.marks.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.marks.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        cdata[0].gold -= 20000;
        snd(12);
        flt();
        itemcreate(-1, 24, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].param1 = 13;
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.marks.quest.pay");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_pyramid_trial = 1;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_259()
{
    if (gdata_red_blossom_in_palmia == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (gdata_red_blossom_in_palmia == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (gdata_red_blossom_in_palmia == 2)
    {
        flt();
        nostack = 1;
        itemcreate(-1, 672, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].param1 = 162;
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 6);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_red_blossom_in_palmia = 1000;
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (gdata_red_blossom_in_palmia == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.noel.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.noel.quest.choices.of_course"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get_enum("core.locale.talk.unique.noel.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.noel.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_red_blossom_in_palmia = 1;
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.of_course");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
    }
    if (cdata[0].gold >= 12000)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.choices.buy"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.dialog");
    talk_window_query();
    if (chatval != 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.bye");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    cdata[0].gold -= 12000;
    snd(12);
    flt();
    itemcreate(-1, 671, cdata[0].position.x, cdata[0].position.y, 0);
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.noel.quest.buy_nuke.buy");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_279()
{
    if (gdata_ambitious_scientist >= 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.icolle.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_ambitious_scientist == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.icolle.quest.choices.alright"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get("core.locale.talk.unique.icolle.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.icolle.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        flt();
        nostack = 1;
        itemcreate(-1, 685, cdata[0].position.x, cdata[0].position.y, 6);
        inv[ci].param2 = 5;
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.icolle.quest.alright");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_ambitious_scientist = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_ambitious_scientist >= 1 && gdata_ambitious_scientist <= 5)
    {
        f = 0;
        const auto tmp = inv_getheader(0);
        const auto invhead = tmp.first;
        const auto invrange = tmp.second;
        for (int cnt = invhead, cnt_end = invhead + invrange; cnt < cnt_end;
                ++cnt)
        {
            if (gdata_ambitious_scientist >= 6)
            {
                break;
            }
            if (inv[cnt].number > 0)
            {
                if (inv[cnt].id == 685)
                {
                    if (inv[cnt].subname != 0)
                    {
                        --inv[cnt].number;
                        ++gdata_ambitious_scientist;
                        f = 1;
                        txt(i18n::s.get("core.locale.talk.unique.icolle.quest.give.deliver",
                                        inv[cnt]));
                        --cnt;
                        continue;
                    }
                }
            }
        }
        if (f)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.icolle.quest.give.have");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (f == 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.icolle.quest.give.do_not_have");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        refresh_burden_state();
    }
    if (gdata_ambitious_scientist >= 6)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.icolle.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        itemcreate(-1, 684, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 2500);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_ambitious_scientist = 1000;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_280()
{
    if (gdata_sewer_sweeping == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_sewer_sweeping == 0)
    {
        listmax = 0;
        buff = i18n::s.get_enum("core.locale.talk.unique.balzak.quest.dialog", 0);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.balzak.quest.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.balzak.quest.choices.no"));
        buff = i18n::s.get_enum("core.locale.talk.unique.balzak.quest.dialog", 1);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.balzak.quest.no");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.quest.yes");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_sewer_sweeping = 1;
        cell_featset(18, 45, tile_downstairs, 11, 20);
        return talk_result_t::talk_end;
    }
    if (gdata_sewer_sweeping == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_sewer_sweeping == 2)
    {
        flt();
        itemcreate(-1, 686, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        nostack = 1;
        itemcreate(-1, 685, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].param2 = 30;
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 15000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.balzak.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_sewer_sweeping = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_290()
{
    if (gdata_belongs_to_mages_guild == 0)
    {
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.lexus.nonmember.choices.tell_me_about"));
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.lexus.nonmember.choices.want_to_join"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get("core.locale.talk.unique.lexus.nonmember.dialog");
        talk_window_query();
        if (chatval == 2)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lexus.nonmember.tell_me_about");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 1)
        {
            if (gdata_joining_mages_guild == 0)
            {
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.lexus.nonmember.want_to_join", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.lexus.nonmember.want_to_join", 1);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_joining_mages_guild = 1;
                gdata_mages_guild_quota = 30;
                snd(44);
                txtef(2);
                txt(i18n::s.get("core.locale.quest.journal_updated"));
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.lexus.nonmember.want_to_join", 2);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (gdata_mages_guild_quota > 0)
            {
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.lexus.nonmember.quota");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lexus.nonmember.end", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata(128) = 10000;
            gdata_belongs_to_thieves_guild = 0;
            gdata_belongs_to_fighters_guild = 0;
            gdata_belongs_to_mages_guild = 1;
            gdata_mages_guild_quota = 0;
            gdata_thieves_guild_quota = 0;
            gdata_joining_mages_guild = 1000;
            gdata_joining_thieves_guild = 0;
            gdata_joining_fighters_guild = 0;
            gdata_fighters_guild_quota2 = 0;
            gdata_mages_guild_quota2 = 0;
            gdata_thieves_guild_quota2 = 0;
            txt(i18n::s.get("core.locale.quest.completed"));
            snd(51);
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
            txtef(5);
            txt(i18n::s.get("core.locale.talk.unique.lexus.nonmember.joined"));
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lexus.nonmember.end", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            cell_movechara(tc, 4, 20);
            cdata[tc].initial_position.x = 4;
            cdata[tc].initial_position.y = 20;
        }
        return talk_result_t::talk_end;
    }
    cell_movechara(tc, 4, 20);
    cdata[tc].initial_position.x = 4;
    cdata[tc].initial_position.y = 20;
    if (gdata_mages_guild_quota2 == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.lexus.member.choices.new_quota"));
    }
    else
    {
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.lexus.member.choices.report_quota"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.lexus.member.dialog",
                       ranktitle(8), cdatan(0, 0));
    talk_window_query();
    if (chatval == 1)
    {
        gdata_mages_guild_quota2 = 1;
        gdata_mages_guild_quota = 75 - gdata(128) / 200;
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.lexus.member.new_quota",
                           gdata_mages_guild_quota);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    if (chatval == 2)
    {
        if (gdata_mages_guild_quota > 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lexus.member.report_quota.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        gdata_mages_guild_quota2 = 0;
        flt(51 - gdata(128) / 200);
        flttypemajor = 54000;
        itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(
                -1,
                54,
                cdata[0].position.x,
                cdata[0].position.y,
                10000 - gdata(128) + 1000);
        flt();
        itemcreate(
                -1,
                55,
                cdata[0].position.x,
                cdata[0].position.y,
                clamp(4 - gdata(128) / 2500, 1, 4));
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        modrank(8, 500, 8);
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.lexus.member.report_quota.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_294()
{
    if (gdata_belongs_to_thieves_guild == 0)
    {
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.abyss.nonmember.choices.tell_me_about"));
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.abyss.nonmember.choices.want_to_join"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get("core.locale.talk.unique.abyss.nonmember.dialog");
        talk_window_query();
        if (chatval == 2)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.abyss.nonmember.tell_me_about");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 1)
        {
            if (gdata_joining_thieves_guild == 0)
            {
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.abyss.nonmember.want_to_join", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_joining_thieves_guild = 1;
                snd(44);
                txtef(2);
                txt(i18n::s.get("core.locale.quest.journal_updated"));
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.abyss.nonmember.want_to_join", 1);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (gdata_left_bill <= 4)
            {
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.abyss.nonmember.quota");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.abyss.nonmember.end", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata(128) = 10000;
            gdata_belongs_to_thieves_guild = 1;
            gdata_belongs_to_fighters_guild = 0;
            gdata_belongs_to_mages_guild = 0;
            gdata_mages_guild_quota = 0;
            gdata_thieves_guild_quota = 0;
            gdata_joining_mages_guild = 0;
            gdata_joining_thieves_guild = 1000;
            gdata_joining_fighters_guild = 0;
            gdata_fighters_guild_quota2 = 0;
            gdata_mages_guild_quota2 = 0;
            gdata_thieves_guild_quota2 = 0;
            txt(i18n::s.get("core.locale.quest.completed"));
            snd(51);
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
            txtef(5);
            txt(i18n::s.get("core.locale.talk.unique.abyss.nonmember.joined"));
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.abyss.nonmember.end", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            cell_movechara(tc, 17, 17);
            cdata[tc].initial_position.x = 17;
            cdata[tc].initial_position.y = 17;
        }
        return talk_result_t::talk_end;
    }
    cell_movechara(tc, 17, 17);
    cdata[tc].initial_position.x = 17;
    cdata[tc].initial_position.y = 17;
    if (gdata_thieves_guild_quota2 == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.lexus.member.choices.new_quota"));
    }
    else
    {
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.lexus.member.choices.report_quota"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.abyss.member.dialog",
                       ranktitle(8), cdatan(0, 0));
    talk_window_query();
    if (chatval == 1)
    {
        gdata_thieves_guild_quota2 = 1;
        gdata_thieves_guild_quota = (10000 - gdata(128)) * 6 + 1000;
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.abyss.member.new_quota",
                           gdata_thieves_guild_quota);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    if (chatval == 2)
    {
        if (gdata_thieves_guild_quota > 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lexus.member.report_quota.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        gdata_thieves_guild_quota2 = 0;
        flt(51 - gdata(128) / 200);
        flttypemajor = 60000;
        itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(
                -1,
                54,
                cdata[0].position.x,
                cdata[0].position.y,
                10000 - gdata(128) + 1000);
        flt();
        itemcreate(
                -1,
                55,
                cdata[0].position.x,
                cdata[0].position.y,
                clamp(3 - gdata(128) / 3000, 1, 3));
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        modrank(8, 500, 8);
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.lexus.member.report_quota.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_297()
{
    if (gdata_belongs_to_fighters_guild == 0)
    {
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.doria.nonmember.choices.tell_me_about"));
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.doria.nonmember.choices.want_to_join"));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = i18n::s.get("core.locale.talk.unique.doria.nonmember.dialog");
        talk_window_query();
        if (chatval == 2)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.doria.nonmember.tell_me_about");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 1)
        {
            if (gdata_joining_fighters_guild == 0)
            {
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.doria.nonmember.want_to_join", 0);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_joining_fighters_guild = 1;
                snd(44);
                txtef(2);
                txt(i18n::s.get("core.locale.quest.journal_updated"));
                while (1)
                {
                    flt(10);
                    chara_create(56, 0, -3, 0);
                    if (the_character_db[cdata[56].id]->rarity / 1000 < 70)
                    {
                        continue;
                    }
                    if (cdata[56].relationship != -3)
                    {
                        continue;
                    }
                    if (cdata[56].quality >= 4)
                    {
                        continue;
                    }
                    break;
                }
                gdata_fighters_guild_quota = 15;
                gdata_fighters_guild_target = cdata[56].id;
                chara_vanquish(56);
                listmax = 0;
                buff = i18n::s.get_enum("core.locale.talk.unique.doria.nonmember.want_to_join", 1,
                                        gdata_fighters_guild_quota,
                                        chara_refstr(gdata_fighters_guild_target, 2));
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (gdata_fighters_guild_quota > 0)
            {
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.doria.nonmember.quota",
                                   gdata_fighters_guild_quota,
                                   chara_refstr(gdata_fighters_guild_target, 2));
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.lexus.nonmember.end", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata(128) = 10000;
            gdata_belongs_to_thieves_guild = 0;
            gdata_belongs_to_fighters_guild = 1;
            gdata_belongs_to_mages_guild = 0;
            gdata_mages_guild_quota = 0;
            gdata_thieves_guild_quota = 0;
            gdata_joining_mages_guild = 0;
            gdata_joining_thieves_guild = 0;
            gdata_joining_fighters_guild = 1000;
            gdata_fighters_guild_quota2 = 0;
            gdata_mages_guild_quota2 = 0;
            gdata_thieves_guild_quota2 = 0;
            txt(i18n::s.get("core.locale.quest.completed"));
            snd(51);
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
            txtef(5);
            txt(i18n::s.get("core.locale.talk.unique.doria.nonmember.joined"));
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.unique.doria.nonmember.end", 1);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            cell_movechara(tc, 29, 2);
            cdata[tc].initial_position.x = 29;
            cdata[tc].initial_position.y = 2;
        }
        return talk_result_t::talk_end;
    }
    cell_movechara(tc, 29, 2);
    cdata[tc].initial_position.x = 29;
    cdata[tc].initial_position.y = 2;
    if (gdata_fighters_guild_quota2 == 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.lexus.member.choices.new_quota"));
    }
    else
    {
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.lexus.member.choices.report_quota"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    buff = i18n::s.get("core.locale.talk.unique.doria.member.dialog",
                       ranktitle(8), cdatan(0, 0));
    talk_window_query();
    if (chatval == 1)
    {
        while (1)
        {
            flt(cdata[0].level + 10);
            chara_create(56, 0, -3, 0);
            if (the_character_db[cdata[56].id]->rarity / 1000 < 70)
            {
                continue;
            }
            if (cdata[56].relationship != -3)
            {
                continue;
            }
            if (cdata[56].quality >= 4)
            {
                continue;
            }
            break;
        }
        gdata_fighters_guild_quota = 2 + rnd(3);
        gdata_fighters_guild_target = cdata[56].id;
        chara_vanquish(56);
        gdata_fighters_guild_quota2 = 1;
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.doria.member.new_quota",
                           gdata_fighters_guild_quota,
                           chara_refstr(gdata_fighters_guild_target, 2));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_unique;
    }
    if (chatval == 2)
    {
        if (gdata_fighters_guild_quota > 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.lexus.member.report_quota.waiting");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        gdata_fighters_guild_quota2 = 0;
        flt(51 - gdata(128) / 200, calcfixlv(3));
        flttypemajor = 10000;
        itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(
                -1,
                54,
                cdata[0].position.x,
                cdata[0].position.y,
                10000 - gdata(128) + 1000);
        flt();
        itemcreate(
                -1,
                55,
                cdata[0].position.x,
                cdata[0].position.y,
                clamp(4 - gdata(128) / 2500, 1, 4));
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        modrank(8, 500, 8);
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.lexus.member.report_quota.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_301()
{
    if (gdata_minotaur_king == 1000)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.complete");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_minotaur_king == 0)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.conery.quest.choices.do_it"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.conery.quest.choices.bye"));
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.dialog");
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.conery.quest.bye");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.do_it", cdatan(0, 0));
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_minotaur_king = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_minotaur_king == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.waiting");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    if (gdata_minotaur_king == 2)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.conery.quest.end");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        flt();
        nostack = 1;
        itemcreate(-1, 630, cdata[0].position.x, cdata[0].position.y, 0);
        fixmaterial = 31;
        change_item_material();
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 50000);
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_minotaur_king = 1000;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_302()
{
    if (cdata[0].gold <= 10)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.rogue_boss.too_poor", cdata[tc]);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.unique.rogue_boss.ambush.choices.try_me"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.unique.rogue_boss.ambush.choices.surrender"));
    buff = i18n::s.get("core.locale.talk.unique.rogue_boss.ambush.dialog",
                       gdatan(1), (cdata[0].gold / 5), cdata[tc]);
    chatesc = 0;
    talk_window_query();
    if (chatval == 0)
    {
        snd(12);
        cdata[0].gold -= cdata[0].gold / 5;
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number > 0)
            {
                if (the_item_db[inv[cnt].id]->is_cargo == 1)
                {
                    txt(lang(
                                itemname(cnt) + u8"を渡した。"s,
                                u8"You hand over "s + itemname(cnt) + u8"."s));
                    item_remove(inv[cnt]);
                }
            }
        }
        refresh_burden_state();
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.rogue_boss.ambush.surrender", cdata[tc]);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        levelexitby = 4;
        chatteleport = 1;
        snd(49);
        return talk_result_t::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.rogue_boss.ambush.try_me", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_322()
{
    if (gdata_little_sister == 0)
    {
        listmax = 0;
        i18n::s.get("core.locale.talk.unique.strange_scientist.first");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_little_sister = 0;
        flt();
        itemcreate(-1, 699, cdata[0].position.x, cdata[0].position.y, 0);
        txt(i18n::s.get(
                    "core.locale.common.something_is_put_on_the_ground"));
        snd(44);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.journal_updated"));
        gdata_little_sister = 1;
        return talk_result_t::talk_end;
    }
    if (gdata_little_sister > 0)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.strange_scientist.choices.reward"));
        ELONA_APPEND_RESPONSE(
                2, i18n::s.get("core.locale.talk.unique.strange_scientist.choices.replenish"));
        if (chara_find_ally(319) != -1)
        {
            ELONA_APPEND_RESPONSE(
                3, i18n::s.get("core.locale.talk.unique.strange_scientist.choices.turn_over"));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        i18n::s.get("core.locale.talk.unique.strange_scientist.dialog");
        talk_window_query();
        if (chatval == 1)
        {
            p = gdata_kill_count_of_little_sister;
            for (int cnt = 1,
                    cnt_end =
                    cnt + (gdata_gift_count_of_little_sister + 1);
                    cnt < cnt_end;
                    ++cnt)
            {
                p += cnt;
            }
            if (gdata_save_count_of_little_sister >= p || 0)
            {
                listmax = 0;
                i18n::s.get("core.locale.talk.unique.strange_scientist.reward.dialog");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
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
                    randomize(gdata_day + cnt);
                    f = 0;
                    if (itemmemory(0, cnt))
                    {
                        f = 1;
                    }
                    if (cnt == 662)
                    {
                        if (gdata_kamikaze_attack >= 1000)
                        {
                            f = 1;
                        }
                    }
                    if (cnt == 655)
                    {
                        if (gdata_rare_books >= 1000)
                        {
                            f = 1;
                        }
                    }
                    if (cnt == 639)
                    {
                        if (gdata_pael_and_her_mom >= 1000)
                        {
                            f = 1;
                        }
                    }
                    if (f)
                    {
                        flt(cdata[0].level * 3 / 2, calcfixlv(3));
                        int stat = itemcreate(-1, cnt, -1, -1, 0);
                        if (stat == 1)
                        {
                            if (inv[ci].quality < 4)
                            {
                                item_remove(inv[ci]);
                            }
                        }
                    }
                    randomize();
                }
                txt(i18n::s.get("core.locale.talk.unique.strange_scientist.reward.choose_one"));
                invsubroutine = 1;
                invctrl(0) = 22;
                invctrl(1) = 4;
                ctrl_inventory();
                exittempinv();
                mode = 0;
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.strange_scientist.reward.find");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            else
            {
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.strange_scientist.reward.not_enough");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            return talk_result_t::talk_end;
        }
        if (chatval == 2)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.strange_scientist.replenish");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(
                    -1, 699, cdata[0].position.x, cdata[0].position.y, 0);
            txt(i18n::s.get(
                        "core.locale.common.something_is_put_on_the_ground"));
            return talk_result_t::talk_end;
        }
        if (chatval == 3)
        {
            txt(i18n::s.get("core.locale.talk.unique.strange_scientist.turn_over.text"));
            ++gdata_save_count_of_little_sister;
            txtef(2);
            txt(lang(
                        u8"リトルシスター殺害"s + gdata_kill_count_of_little_sister
                        + u8"回、救出"s + gdata_save_count_of_little_sister
                        + u8"回。"s,
                        u8"You have saved little sister "s
                        + gdata_save_count_of_little_sister
                        + u8" times and killed "s
                        + gdata_kill_count_of_little_sister + u8" times."s));
            chara_vanquish(chara_find_ally(319));
            snd(51);
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.strange_scientist.turn_over.dialog");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_ignored;
}

talk_result_t talk_unique_345()
{
    if (gdata_blue_capsule_drug >= 3)
    {
        buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.dialog");
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.choices.no"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            f = chara_get_free_slot_ally();
            if (f == 0)
            {
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.yes.party_full");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.yes.dialog");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            rc = tc;
            new_ally_joins();
            gdata_blue_capsule_drug = 0;
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.after_drug.no");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    {
        int stat = inv_find(771, 0);
        if (stat != -1)
        {
            buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug.dialog");
            ELONA_APPEND_RESPONSE(
                    1, i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug.choices.yes"));
            ELONA_APPEND_RESPONSE(
                    0, i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug.choices.no"));
            chatesc = 1;
            talk_window_query();
            if (chatval == 1)
            {
                int stat = inv_find(771, 0);
                --inv[stat].number;
                txt(i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug.yes.you_hand_him"));
                snd(13);
                listmax = 0;
                buff = i18n::s.get("core.locale.talk.unique.kaneda_bike.before_drug.yes.dialog");
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                ++gdata_blue_capsule_drug;
                return talk_result_t::talk_end;
            }
        }
    }
    listmax = 0;
    buff =
        i18n::s.get("core.locale.talk.unique.kaneda_bike.do_not_have_drug");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

talk_result_t talk_unique_348()
{
    if (gdata_current_map != 33 || adata(29, gdata_current_map) == 0)
    {
        return talk_result_t::talk_end;
    }
    if (cdata[0].god_id == core_god::jure)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.part_time_worker.already_believe_in_jure");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.unique.part_time_worker.choices.yes"));
    ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.unique.part_time_worker.choices.no"));
    buff = i18n::s.get("core.locale.talk.unique.part_time_worker.dialog");
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.unique.part_time_worker.yes.choices.yes"));
        ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.unique.part_time_worker.yes.choices.no"));
        buff = i18n::s.get("core.locale.talk.unique.part_time_worker.yes.dialog");
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.unique.part_time_worker.yes.yes");
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            txt(i18n::s.get(
                        "core.locale.common.something_is_put_on_the_ground"));
            flt();
            itemcreate(
                    -1, 767, cdata[0].position.x, cdata[0].position.y, 0);
            cdata[0].god_id = core_god::int2godid(6);
            switch_religion();
            return talk_result_t::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.unique.part_time_worker.no");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

} // namespace

talk_result_t talk_unique()
{
    listmax = 0;
    switch (chatval(1))
    {
        case 2:
            return talk_unique_zeome();
        case 23:
            return talk_unique_23();
        case 28:
            return talk_unique_28();
        case 29:
            return talk_unique_29();
        case 30:
            return talk_unique_30();
        case 31:
            return talk_unique_31();
        case 33:
            return talk_unique_33();
        case 34:
            return talk_unique_34();
        case 79:
            return talk_unique_79();
        case 80:
            return talk_unique_80();
        case 139:
            return talk_unique_139();
        case 142:
            return talk_unique_142();
        case 146:
            return talk_unique_146();
        case 208:
            return talk_unique_208();
        case 209:
            return talk_unique_209();
        case 221:
            return talk_unique_221();
        case 222:
            return talk_unique_222();
        case 223:
            return talk_unique_223();
        case 224:
            return talk_unique_224();
        case 225:
            return talk_unique_225();
        case 226:
            return talk_unique_226();
        case 227:
            return talk_unique_227();
        case 231:
            return talk_unique_231();
        case 243:
            return talk_unique_243();
        case 247:
            return talk_unique_247();
        case 252:
            return talk_unique_252();
        case 253:
            return talk_unique_253();
        case 259:
            return talk_unique_259();
        case 279:
            return talk_unique_279();
        case 280:
            return talk_unique_280();
        case 290:
            return talk_unique_290();
        case 294:
            return talk_unique_294();
        case 297:
            return talk_unique_297();
        case 301:
            return talk_unique_301();
        case 302:
            return talk_unique_302();
        case 322:
            return talk_unique_322();
        case 345:
            return talk_unique_345();
        case 348:
            return talk_unique_348();
    }
    return talk_result_t::talk_ignored;
}

} // namespace elona
