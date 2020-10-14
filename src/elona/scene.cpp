#include "scene.hpp"

#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "keybind/keybind.hpp"
#include "lua_env/interface.hpp"
#include "message.hpp"
#include "randomgen.hpp"
#include "talk.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

void do_play_scene()
{
    if (game()->played_scene < sceneid)
    {
        game()->played_scene = sceneid;
    }
    if (!g_config.story())
    {
        return;
    }

    int scidx = 0;
    int scidxtop = 0;
    int val0{};

    scene_cut = 0;
    scenemode = 1;
    SDIM4(actor, 20, 3, 10);
    data::InstanceId background_image_id{u8"core.void"};
    y1 = 60;
    y2 = windowh - 60;
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{
            lua::resolve_path_for_mod("<core>/locale/<LANGUAGE>/lazy/scene.hsp")
                .native(),
            std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    s = u8"{"s + sceneid + u8"}"s;
    scidx = instr(buff, 0, s);
    if (scidx == -1)
    {
        scene_fade_to_black();
        return;
    }

    scidx += s(0).size();

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            const auto input = stick(StickKey::escape);
            if (input == StickKey::escape)
            {
                scene_cut = 1;
            }
            if (scene_cut == 1)
            {
                scene_fade_to_black();
                return;
            }
            notesel(buff);
            {
                buff(0).clear();
                std::ifstream in{
                    lua::resolve_path_for_mod(
                        "<core>/locale/<LANGUAGE>/lazy/scene.hsp")
                        .native(),
                    std::ios::binary};
                std::string tmp;
                while (std::getline(in, tmp))
                {
                    buff(0) += tmp + '\n';
                }
            }
            cs = 0;
            key_list = keybind_get_bound_key_name("enter");
            scidxtop = scidx;
            scidxtop = 0;
            val0 = 0;
        }

        p(1) = instr(buff, scidx, u8"{"s) + scidx;
        if (p(1) == -1)
        {
            scene_fade_to_black();
            return;
        }
        p(2) = instr(buff, scidx, u8"}"s) + scidx + 1;
        if (p(2) == -1)
        {
            scene_fade_to_black();
            return;
        }

        if (scidxtop != 0)
        {
            scidx = p(1);
            buff = strmid(buff, scidxtop, scidx - scidxtop);
            p = noteinfo();
            for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
            {
                noteget(s, p - cnt - 1);
                if (s == ""s)
                {
                    notedel(p - cnt - 1);
                }
            }
            gmode(0);
            asset_load(background_image_id);
            draw(background_image_id, 0, y1, windoww, y2 - y1);
            gmode(2);
            boxf(0, 0, windoww, y1, {5, 5, 5});
            boxf(0, y2, windoww, windowh - y2, {5, 5, 5});
            if (val0 == 1)
            {
                gsel(0);
                gmode(0);
                gcopy(4, 0, 0, windoww, windowh, 0, 0);
                gmode(2);
                talk_to_npc(cdata.player());
                init = true;
                continue;
            }
            if (val0 == 2)
            {
                gsel(0);
                gmode(0);
                gcopy(4, 0, 0, windoww, windowh, 0, 0);
                gmode(2);
                redraw();
                await(1000);
                init = true;
                continue;
            }
            font(16 - en * 2);
            x = 44;
            for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
            {
                y = y1 + 31 + (9 - noteinfo() / 2 + cnt) * 20;
                noteget(s, cnt);
                x = windoww / 2 - s(0).size() * 4;
                dx = 80 + strlen_u(s(0)) * 8;
                if (dx < 180)
                {
                    dx = 0;
                }
                gmode(2, 95);
                draw_centered("core.scene_title", windoww / 2, y + 4, dx, 72);
            }
            x = 40;
            for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
            {
                y = y1 + 28 + (9 - noteinfo() / 2 + cnt) * 20;
                noteget(s, cnt);
                x = windoww / 2 - strlen_u(s(0)) * 4;
                gmode(2);
                bmes(s, x, y, {240, 240, 240}, {10, 10, 10});
            }
            gsel(0);
            for (int cnt = 1; cnt < 16; ++cnt)
            {
                await(30);
                const auto input = stick(StickKey::escape);
                if (input == StickKey::escape)
                {
                    scene_cut = 1;
                }
                gmode(2, cnt * 16);
                gcopy(4, 0, 0, windoww, windowh, 0, 0);
                redraw();
            }
            gmode(2);
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh, 0, 0);
            gmode(2);
            anime_halt(windoww - 120, windowh - 60);
            boxf(0, 0, windoww, y1, {5, 5, 5});
            boxf(0, y2, windoww, windowh - y2, {5, 5, 5});
            init = true;
            continue;
        }

        s = strmid(buff, p(1), p(2) - p(1));
        scidx = p(2) + 1;
        if (s == u8"{txt}"s)
        {
            scidxtop = scidx;
            val0 = 0;
            continue;
        }
        if (strutil::contains(s(0), u8"{chat_"))
        {
            current_actor_index = elona::stoi(strmid(s, 6, 1));
            scidxtop = scidx;
            val0 = 1;
            continue;
        }
        if (s == u8"{fade}"s)
        {
            gsel(4);
            boxf(0, 0, windoww, windowh, {0, 0, 0, 255});
            gsel(0);
            animation_fade_in();
            continue;
        }
        if (s == u8"{fadein}"s)
        {
            for (int cnt = 0; cnt < 25; ++cnt)
            {
                redraw();
                gmode(2, cnt * 15);
                gcopy(4, 0, 0, windoww, windowh, 0, 0);
                gmode(2);
                await(10);
            }
            continue;
        }
        if (s == u8"{wait}"s)
        {
            scidxtop = scidx;
            val0 = 2;
            continue;
        }
        if (s == u8"{end}"s)
        {
            await(1000);
            scene_fade_to_black();
            return;
        }
        p(3) = instr(buff, scidx, u8"\""s) + scidx + 1;
        p(4) = instr(buff, p(3), u8"\""s) + p(3);
        s(1) = strmid(buff, p(3), p(4) - p(3));
        scidx = p(4) + 1;
        if (s == u8"{pic}"s)
        {
            background_image_id = data::InstanceId{"core." + s(1)};
            continue;
        }
        if (s == u8"{mc}"s)
        {
            play_music(data::InstanceId{s(1)});
            continue;
        }
        if (s == u8"{se}"s)
        {
            snd(data::InstanceId{s(1)});
            continue;
        }
        if (strutil::contains(s(0), u8"{actor_"))
        {
            const auto actor_index = elona::stoi(strmid(s, 7, 1));
            csvsort(s, s(1), 44);
            actor(0, actor_index) = s;
            actor(1, actor_index) = s(1);
        }
    }
}



void scene_fade_to_black()
{
    gsel(4);
    boxf(0, 0, windoww, windowh, {0, 0, 0, 255});
    gsel(0);
    animation_fade_in();
    scenemode = 0;
}



std::string ask_win_comment()
{
    std::vector<std::string> choices;
    {
        const auto choices_ = i18n::s.get_list("core.scenario.win_words");
        if (choices_.empty())
        {
            choices.push_back("I can't sleep tonight.");
        }
        else
        {
            choices = sampled(choices_, std::min(choices_.size(), size_t(3)));
        }
    }

    Prompt prompt(Prompt::Type::cannot_cancel);
    for (const auto& choice : choices)
    {
        prompt.append(choice);
    }
    const auto selected_index = prompt.query(promptx, prompty, 310);

    return choices[selected_index];
}



void conquer_lesimas()
{
    snd("core.complete1");
    stop_music();
    txt(i18n::s.get("core.win.conquer_lesimas"));
    update_screen();

    const auto win_comment = ask_win_comment();

    mode = 7;
    screenupdate = -1;
    update_screen();
    if (jp)
    {
        Message::instance().clear();
        txt(u8"「お前がここに辿り着くことは」台座から、何かの声が聞こえる。"s);
        flt();
        chara_create(
            -1, 23, cdata.player().position.x, cdata.player().position.y);
        play_music("core.mcChaos");
        msg_halt();
        Message::instance().clear();
        txt(u8"「決まっていたことなのだ…遅かれ早かれな」"s);
        txt(u8"部屋の空気が突然緊張し、あなたの前に端麗な青年が現れた。"s);
        txt(u8"「我々からすれば、複雑性の一面に過ぎないが、人間は運命とでも呼ぶのだろう？」"s);
        msg_halt();
        Message::instance().clear();
        txt(u8"あなたは懸命に脚の震えを抑えようとしたが、難しかった。"s);
        txt(u8"華奢に見える幼顔の男の影は、人のものではない。"s);
        txt(u8"あどけない瞳の奥に、あなたは底知れない力と闇を感じた。"s);
        msg_halt();
        Message::instance().clear();
        txt(u8"「ネフィアの永遠の盟約に基づき」青年は台座の横の死体を指し、皮肉な微笑を送った。"s);
        txt(u8"「この哀れな老人が守っていたものは、今からお前のものだ」"s);
        msg_halt();
        Message::instance().clear();
        txt(u8"あなたは、台座の上に置かれている絢爛な装飾の本を、いぶかしげに眺めた。"s);
        msg_halt();
        // BUG: creation of Orphe can fail in a certain condition.
        const auto orphe = chara_find("core.orphe");
        assert(orphe);
        talk_to_npc(*orphe);
        Message::instance().clear();
        txt(u8"青年は悪戯っぽくニヤリと笑い、壁に寄りかかった。"s);
        msg_halt();
        Message::instance().clear();
        chara_vanquish(*orphe);
        screenupdate = -1;
        update_screen();
        txt(u8"…どれくらい時間がたっただろう。氷の瞳の男は、いつの間にか姿を消していた。あなたは不安を振り払い、ゆっくりと本に手を伸ばした…"s);
        msg_halt();
    }
    mode = 0;
    play_music("core.mcMarch2");
    ui_win_screen_fade();
    asset_load("core.void");
    draw_region("core.void", 0, 0, 0, 0, 640, 480, windoww, windowh);
    gsel(0);
    animation_fade_in();
    draw_region("core.void", 0, 0, 0, 0, windoww, windowh);
    asset_load("core.g1");
    gsel(0);
    ui_draw_caption(i18n::s.get(
        "core.win.you_acquired_codex",
        cdata.player().alias,
        cdata.player().name));
    windowshadow = 1;
    ww = 680;
    wh = 488;
    pagesize = 0;
    ui_display_window(
        i18n::s.get("core.win.window.title"),
        ""s + strhint3,
        windoww / 2 - ww / 2,
        windowh / 2 - wh / 2,
        ww,
        wh);
    gmode(2, 250);
    draw_centered("core.g1", wx + ww - 120, wy + wh / 2, ww / 3 - 20, wh - 140);
    gmode(2);
    display_topic(i18n::s.get("core.win.window.caption"), wx + 28, wy + 40);
    font(14 - en * 2);
    mes(wx + 40,
        wy + 76,
        i18n::s.get("core.win.window.arrived_at_tyris", 517, 8, 12));
    mes(wx + 40,
        wy + 116,
        i18n::s.get(
            "core.win.window.have_killed",
            game()->deepest_dungeon_danger_level,
            game()->total_kill_count));
    mes(wx + 40, wy + 146, i18n::s.get("core.win.window.score", calcscore()));
    const auto date = game_date();
    mes(wx + 40,
        wy + 186,
        i18n::s.get(
            "core.win.window.lesimas", date.year(), date.month(), date.day()));
    mes(wx + 40, wy + 206, i18n::s.get("core.win.window.comment", win_comment));
    mes(wx + 40,
        wy + 246,
        i18n::s.get("core.win.window.your_journey_continues"));
    redraw();
    key_list = keybind_get_bound_key_name("enter");
    keyrange = 0;

    while (1)
    {
        auto action = cursor_check_ex();
        if (action == "cancel")
        {
            play_the_last_scene_again();
            return;
        }
    }
}



void play_the_last_scene_again()
{
    update_entire_screen();
    Message::instance().linebreak();
    txt(i18n::s.get("core.win.watch_event_again"));
    if (yes_no())
    {
        conquer_lesimas();
        return;
    }
    story_quest_set_progress("core.elona", 180);
    update_screen();
}

} // namespace elona
