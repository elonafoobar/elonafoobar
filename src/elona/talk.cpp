#include "talk.hpp"

#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "deferred_event.hpp"
#include "draw.hpp"
#include "enums.hpp"
#include "game.hpp"
#include "god.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "keybind/keybind.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{

namespace
{

bool chatval_show_impress;

}



void talk_start()
{
    asset_load("core.ie_chat");
    gsel(0);
}



bool talk_setup_variables(Character& chara)
{
    input_halt_input(HaltInput::force);
    if (chara.role == Role::innkeeper)
    {
        if (g_config.extra_help())
        {
            maybe_show_ex_help(7, true);
        }
    }
    if (chara.role == Role::trainer)
    {
        maybe_show_ex_help(8, true);
    }
    set_npc_religion(chara);
    if (scenemode == 0)
    {
        snd("core.chat");
        map_proc_regen_and_update();
    }
    cs = 0;
    chatesc = 1;
    if (chara.relationship <= Relationship::neutral)
    {
        if (!deferred_event_has_pending_events())
        {
            txt(i18n::s.get("core.talk.will_not_listen", chara));
            quest_teleport = false;
            update_screen();
            return false;
        }
    }
    if (game_now() >= chara.interest_reset_time)
    {
        chara.interest = 100;
    }
    if (is_shopkeeper(chara.role))
    {
        invfile = chara.shop_store_id;
        shop_refresh_on_talk(chara);
    }

    return true;
}



void talk_to_npc(Character& chara)
{
    if (!talk_setup_variables(chara))
    {
        return;
    }

    talk_start();
    if (scenemode == 1)
    {
        talk_wrapper(chara, TalkResult::talk_more);
        return;
    }
    chatval_unique_chara_id = none;
    chatval_show_impress = true;
    if (chara.quality == Quality::special && !chara.is_player_or_ally())
    {
        chatval_unique_chara_id = the_character_db.ensure(chara.id).integer_id;
        chatval_show_impress = false;
    }
    if (deferred_event_processing_event() == "core.lomias_talk")
    {
        talk_wrapper(chara, TalkResult::talk_game_begin);
        return;
    }
    if (deferred_event_processing_event() == "core.quest_escort_complete")
    {
        talk_wrapper(chara, TalkResult::talk_finish_escort);
        return;
    }
    if (chara.sleep != 0)
    {
        talk_wrapper(chara, TalkResult::talk_sleeping);
        return;
    }
    if (chara.activity)
    {
        talk_wrapper(chara, TalkResult::talk_busy);
        return;
    }
    if (chara.is_player())
    {
        talk_wrapper(chara, TalkResult::talk_end);
        return;
    }
    if (chara.visited_just_now())
    {
        chara.visited_just_now() = false;
        talk_wrapper(chara, TalkResult::talk_house_visitor);
    }

    if (chatval_unique_chara_id &&
        game()->current_map != mdata_t::MapId::show_house &&
        !chara.is_player_or_ally())
    {
        talk_wrapper(chara, TalkResult::talk_unique);
        return;
    }

    if (quest_teleport)
    {
        quest_teleport = false;
        talk_wrapper(chara, TalkResult::talk_quest_giver);
        return;
    }
    buff = "";

    talk_wrapper(chara, TalkResult::talk_npc);
}



TalkResult talk_more(Character& speaker)
{
    listmax = 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult talk_sleeping(Character& speaker)
{
    listmax = 0;
    buff = "("s + i18n::s.get("core.talk.is_sleeping", speaker) + ")"s;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.bye");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult talk_busy(Character& speaker)
{
    listmax = 0;
    buff = "("s + i18n::s.get("core.talk.is_busy", speaker) + ")"s;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.bye");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult talk_ignored(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.ignores_you", speaker);
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.bye"));
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult talk_game_begin(Character& initial_speaker)
{
    auto speaker = std::ref(initial_speaker);
    if (lomiaseaster)
    {
        cdata.player().blind = 100;
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 0);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 1);
        if (const auto lomias = chara_find("core.lomias"))
        {
            speaker = std::ref(*lomias);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        update_screen();
        await(3000);
        Message::instance().linebreak();
        txt(i18n::s.get(
                "core.talk.unique.lomias.begin.easter_egg.something_is_killed"),
            Message::color{ColorIndex::red});
        txt(i18n::s.get("core.talk.unique.lomias.begin.easter_egg.ugh"));
        snd("core.kill1");
        spillblood(28, 6, 10);
        flt();
        itemcreate_map_inv(705, 28, 6, 0);
        update_screen();
        await(500);
        await(500);
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 2);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 3);
        if (const auto lomias = chara_find("core.lomias"))
        {
            speaker = std::ref(*lomias);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 4);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 5);
        if (const auto lomias = chara_find("core.lomias"))
        {
            speaker = std::ref(*lomias);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 6);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        await(1500);
        update_screen();
        fade_out();
        gsel(0);
        cdata.player().blind = 0;
        txt(i18n::s.get("core.talk.unique.lomias.begin.easter_egg.was_dream"));
    }
    else
    {
        Message::instance().linebreak();
    }
    txt(i18n::s.get("core.talk.unique.lomias.begin.regain_consciousness"));
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 0);
    if (const auto lomias = chara_find("core.lomias"))
    {
        speaker = std::ref(*lomias);
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 1);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 2);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 3);
    if (const auto larnneire = chara_find("core.larnneire"))
    {
        speaker = std::ref(*larnneire);
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum(
        "core.talk.unique.lomias.begin", 4, cdata.player().name);
    if (const auto lomias = chara_find("core.lomias"))
    {
        speaker = std::ref(*lomias);
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    map_data.bgm = 67;
    play_music();
    return TalkResult::talk_unique;
}



void talk_end()
{
    quest_teleport = false;
    if (scenemode == 0)
    {
        screenupdate = -1;
        update_screen();
    }
}



std::string talk_get_speaker_name(const Character& chara)
{
    std::string speaker_name;

    if (scenemode)
    {
        return actor(0, current_actor_index);
    }
    if (chara.alias == ""s)
    {
        speaker_name = chara.name + " "s;
    }
    else
    {
        speaker_name =
            i18n::s.get("core.talk.window.of", chara.name, chara.alias) + " ";
    }
    if (chara.sex == 0)
    {
        speaker_name += cnven(i18n::s.get("core.ui.sex3.male"));
    }
    else
    {
        speaker_name += cnven(i18n::s.get("core.ui.sex3.female"));
    }
    if (chara.alias != ""s)
    {
        speaker_name += " " + i18n::s.get("core.talk.window.fame", chara.fame);
    }
    if (is_shopkeeper(chara.role))
    {
        speaker_name +=
            " " + i18n::s.get("core.talk.window.shop_rank", chara.shop_rank);
    }
    if (game()->reveals_religion)
    {
        speaker_name += " ("s + god_get_name(chara.religion) + ")"s;
    }

    return speaker_name;
}



int talk_window_query(const Character& chara)
{
    const auto speaker_name = talk_get_speaker_name(chara);
    optional<std::pair<int, int>> impress_interest = none;

    if (chatval_show_impress)
    {
        impress_interest = std::make_pair(chara.impression, chara.interest);
    }

    if (chara.portrait != "" || scenemode)
    {
        const auto portrait_id = scenemode
            ? data::InstanceId{actor(1, current_actor_index)}
            : chara.portrait;
        return talk_window_query(
            portrait_id, none, speaker_name, buff, impress_interest);
    }
    else
    {
        return talk_window_query(
            none, chara.image, speaker_name, buff, impress_interest);
    }
}



int talk_window_query(
    optional<data::InstanceId> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest)
{
    cs_bk = -1;
    key_list = keybind_get_bound_key_name("enter");
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        ++keyrange;
    }
    keyrange = listmax;
    talk_window_init(text);

    while (true)
    {
        talk_window_show(
            portrait_id, chara_image, speaker_name, text, impress_interest);
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
        {
            noteget(s, cnt);
            x = wx + 136;
            y = wy + wh - 56 - keyrange * 19 + cnt * 19 + 2;
            display_key(x, y, cnt);
            cs_list(cs == cnt, listn(0, cnt), x + 30, y, 4);
        }
        cs_bk = cs;
        redraw();
        int cursor{};
        auto action = cursor_check_ex(cursor);
        const auto input = stick(StickKey::escape);
        if (input == StickKey::escape)
        {
            if (scenemode)
            {
                scene_cut = 1;
                talk_reset_variables();
                return -1;
            }
        }
        p = -1;
        for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
        {
            if (cnt == cursor)
            {
                p = list(0, cnt);
                break;
            }
        }
        if (p != -1)
        {
            talk_reset_variables();
            return p(0);
        }
        if (action == "cancel" && chatesc != -1)
        {
            talk_reset_variables();
            return -1;
        }
    }
}



void talk_reset_variables()
{
    snd("core.more1");
    cs = 0;
    listmax = 0;
}



void talk_window_init(std::string& text)
{
    if (scenemode == 0)
    {
        screenupdate = -1;
        update_screen();
        cs = 0;
    }
    talk_conv(text, 56 - en * 3);
    wx = (windoww - 600) / 2 + inf_screenx;
    wy = winposy(380);
    ww = 600;
    wh = 380;
    gmode(2, 80);
    draw("core.ie_chat", wx + 4, wy - 16);
}



void talk_window_show(
    optional<data::InstanceId> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest)
{
    gmode(2);
    draw("core.ie_chat", wx, wy - 20);
    if (portrait_id)
    {
        if (const auto rect = draw_get_rect_portrait(*portrait_id))
        {
            gcopy(
                rect->buffer,
                rect->x,
                rect->y,
                rect->width,
                rect->height,
                wx + 42,
                wy + 42);
        }
    }
    else if (chara_image)
    {
        const auto chara_chip_id = *chara_image % 1000;
        draw_chara(
            *chara_image,
            wx + 82,
            wy + 125 - chara_chips[chara_chip_id].offset_y,
            2);
    }
    else
    {
        assert(false);
    }

    font(10 - en * 2);
    display_topic(i18n::s.get("core.talk.window.impress"), wx + 28, wy + 170);
    display_topic(i18n::s.get("core.talk.window.attract"), wx + 28, wy + 215);

    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    mes(wx + 120, wy + 16, speaker_name, {20, 10, 5});

    font(13 - en * 2);
    if (impress_interest)
    {
        int impress, interest;
        std::tie(impress, interest) = *impress_interest;

        std::string impress_enum = i18n::s.get_enum(
            "core.ui.impression", chara_impression_level(impress));
        std::string impress_text;

        if (impress < 150)
        {
            impress_text = ""s + impress;
        }
        else
        {
            impress_text = "???"s;
        }
        mes(wx + 32,
            wy + 198,
            "("s + impress_text + ")"s + impress_enum,
            {20, 10, 5});
        if (interest >= 0)
        {
            for (int cnt = 0, cnt_end = (interest / 5 + 1); cnt < cnt_end;
                 ++cnt)
            {
                draw("core.interest_icon", wx + 26 + cnt * 4, wy + 245);
            }
        }
    }
    else
    {
        mes(wx + 60, wy + 198, "-"s);
        mes(wx + 60, wy + 245, "-"s);
    }
    font(14 - en * 2);
    notesel(text);
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        x = wx + 150;
        y = wy + 43 + cnt * 19;
        noteget(s, p);
        mes(x, y, s, {20, 10, 5});
    }
}



int talk_guide_quest_client()
{
    constexpr int max_quest = 5;

    int ret{};

    for (int i = 0; i < max_quest; ++i)
    {
        const auto quest_id = game()->taken_quests.at(i);
        if (quest_data[quest_id].progress != 1)
            continue;
        if (game()->current_dungeon_level != 1)
            continue;

        auto client = -1;
        if (quest_data[quest_id].id == 1011)
        {
            if (quest_data[quest_id].originating_map_id == game()->current_map)
            {
                client = quest_data[quest_id].target_chara_index;
            }
        }
        if (quest_data[quest_id].id == 1002)
        {
            if (quest_data[quest_data[quest_id].target_chara_index]
                    .originating_map_id == game()->current_map)
            {
                client = quest_data[quest_data[quest_id].target_chara_index]
                             .client_chara_index;
            }
        }
        if (client != -1)
        {
            // Check duplicate
            bool duplicated{};
            for (int j = 0; j < i; ++j)
            {
                if (game()->taken_quests.at(j) == quest_id)
                {
                    duplicated = true;
                    break;
                }
            }
            if (!duplicated)
            {
                rtval(ret) = client;
                ++ret;
            }
        }
    }

    return ret;
}

} // namespace elona
