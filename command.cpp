#include "command.hpp"
#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "card.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "quest.hpp"
#include "shop.hpp"
#include "snail/application.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

// TODO organize by order in pc_turn()

turn_result_t do_give_command()
{
    txt(lang(u8"どの方向に？ "s, u8"Which direction? "s));
    update_screen();
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(i18n::_(u8"ui", u8"invalid_target"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    tc = map(x, y, 1);
    if (tc == 0)
    {
        txt(i18n::_(u8"ui", u8"invalid_target"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    tc -= 1;
    if (tc == 0)
    {
        if (gdata_mount != 0)
        {
            tc = gdata_mount;
        }
    }
    if (tc != 0)
    {
        if (tc < 16)
        {
            if (cdata[tc].is_escorted() == 0)
            {
                return try_interact_with_npc();
            }
        }
        update_screen();
        invctrl = 10;
        snd(100);
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    txt(i18n::_(u8"ui", u8"invalid_target"));
    update_screen();
    return turn_result_t::pc_turn_user_error;
}

turn_result_t do_interact_command()
{
    txt(lang(
        u8"操作する対象の方向は？"s, u8"Choose the direction of the target."s));
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(i18n::_(u8"ui", u8"invalid_target"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    tc = map(x, y, 1);
    if (tc == 0)
    {
        txt(i18n::_(u8"ui", u8"invalid_target"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    tc -= 1;
    txt(lang(
        name(tc) + u8"に何をする？ "s,
        u8"What action do you want to perform to "s + him(tc) + u8"? "s));
    p = 0;
    if (tc != 0)
    {
        if (cdata[0].confused == 0)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"話しかける"s, u8"Talk"s), u8"null"s, ""s + 0);
            ELONA_APPEND_PROMPT(
                lang(u8"攻撃する"s, u8"Attack"s), u8"null"s, ""s + 1);
        }
        if (cdata[tc].is_escorted() == 0)
        {
            if (cdata[tc].is_escorted_in_sub_quest() == 0)
            {
                if (tc < 16)
                {
                    ELONA_APPEND_PROMPT(
                        lang(u8"所持品"s, u8"Inventory"s), u8"null"s, ""s + 4);
                }
                else
                {
                    ELONA_APPEND_PROMPT(
                        lang(u8"何かを渡す"s, u8"Give"s), u8"null"s, ""s + 2);
                }
                if (cdata[tc].is_livestock() == 1)
                {
                    ELONA_APPEND_PROMPT(
                        lang(u8"連れ出す"s, u8"Bring Out"s),
                        u8"null"s,
                        ""s + 5);
                }
                if (tc < 16)
                {
                    ELONA_APPEND_PROMPT(
                        lang(u8"着替えさせる"s, u8"Appearance"s),
                        u8"null"s,
                        ""s + 8);
                }
            }
        }
        ELONA_APPEND_PROMPT(
            lang(u8"言葉を教える"s, u8"Teach Words"s), u8"null"s, ""s + 7);
        ELONA_APPEND_PROMPT(
            lang(u8"口調を変える"s, u8"Change Tone"s), u8"null"s, ""s + 10);
        if (gdata_current_map != 35)
        {
            if (cdata[tc].is_hung_on_sand_bag())
            {
                ELONA_APPEND_PROMPT(
                    lang(u8"縄を解く"s, u8"Release"s), u8"null"s, ""s + 9);
            }
        }
    }
    ELONA_APPEND_PROMPT(lang(u8"名前をつける"s, u8"Name"s), u8"null"s, ""s + 3);
    if (0 || gdata_wizard)
    {
        ELONA_APPEND_PROMPT(lang(u8"情報"s, u8"Info"s), u8"null"s, ""s + 6);
    }
    {
        int stat = show_prompt(promptx, prompty, 200);
        if (stat == -1)
        {
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        rtval = stat;
    }
    screenupdate = -1;
    p = rtval;
    if (p == 0)
    {
        update_screen();
        talk_to_npc();
        if (chatteleport == 1)
        {
            chatteleport = 0;
            return turn_result_t::exit_map;
        }
        else
        {
            return turn_result_t::turn_end;
        }
    }
    if (p == 1)
    {
        update_screen();
        try_to_melee_attack();
        return turn_result_t::turn_end;
    }
    if (p == 2)
    {
        update_screen();
        invctrl = 10;
        snd(100);
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    if (p == 3)
    {
        update_screen();
        return call_npc();
    }
    if (p == 4)
    {
        return try_interact_with_npc();
    }
    if (p == 5)
    {
        rc = tc;
        new_ally_joins();
        update_screen();
        return turn_result_t::turn_end;
    }
    if (p == 6)
    {
        csctrl = 4;
        snd(26);
        cc = tc;
        menu_character_sheet();
        cc = 0;
        return turn_result_t::pc_turn_user_error;
    }
    if (p == 7)
    {
        txt(lang(
            u8"どんな言葉を教えようか。"s,
            u8"What sentence should "s + name(tc) + u8" learn? "s));
        inputlog = "";
        input_text_dialog((windoww - 360) / 2 + inf_screenx, winposy(90), 20);
        cdata[tc].has_custom_talk() = false;
        if (inputlog == ""s)
        {
            cdatan(4, tc) = "";
        }
        else
        {
            cdatan(4, tc) = inputlog;
            txtef(9);
            txt(""s + cdatan(4, tc));
        }
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (p == 8)
    {
        gsel(4);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
        gsel(0);
        ccbk = cc;
        cc = tc;
        change_appearance();
        cc = ccbk;
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (p == 9)
    {
        snd(58);
        cdata[tc].is_hung_on_sand_bag() = false;
        txt(lang(
            name(tc) + u8"の縄を解いた。"s,
            u8"You release "s + name(tc) + u8"."s));
        flt();
        itemcreate(-1, 733, cdata[tc].position.x, cdata[tc].position.y, 0);
    }
    if (p == 10)
    {
        change_npc_tone();
    }
    update_screen();
    return turn_result_t::pc_turn_user_error;
}


turn_result_t do_bash_command()
{
    txt(lang(
        u8"どの方向に体当たりする？ "s,
        u8"Which direction do you want to bash? "s));
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    return do_bash();
}

turn_result_t do_dig_command()
{
    txt(lang(
        u8"どの方向を掘る？ "s, u8"Which direction do you want to dig? "s));
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    refx = x;
    refy = y;
    tlocx = x;
    tlocy = y;
    if (tlocx == cdata[0].position.x)
    {
        if (tlocy == cdata[0].position.y)
        {
            rowactre = 0;
            spot_digging();
            return turn_result_t::turn_end;
        }
    }
    if ((chipm(7, map(x, y, 0)) & 4) == 0 || chipm(0, map(x, y, 0)) == 3
        || mdata(6) == 1)
    {
        txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    screenupdate = -1;
    update_screen();
    return do_dig_after_sp_check();
}

turn_result_t do_search_command()
{
    ++msgdup;
    txt(lang(
        u8"周囲を注意深く調べた。"s,
        u8"You search the surroundings carefully."s));
    if (gdata_current_map == 35)
    {
        p = 9999;
        for (const auto& cnt : items(-1))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].own_state != 5)
            {
                continue;
            }
            if (inv[cnt].id != 748)
            {
                continue;
            }
            if (p > dist(
                        inv[cnt].position.x,
                        inv[cnt].position.y,
                        cdata[0].position.x,
                        cdata[0].position.y))
            {
                p = dist(
                    inv[cnt].position.x,
                    inv[cnt].position.y,
                    cdata[0].position.x,
                    cdata[0].position.y);
            }
        }
        if (p != 9999)
        {
            while (1)
            {
                if (p <= 3)
                {
                    txt(lang(
                        u8"辺りの空気は息苦しいほどの緊張に包まれている。"s,
                        u8"The air around you is filled with strained silence."s));
                }
                if (p <= 9)
                {
                    txt(lang(
                        u8"微かだが、あなたの心臓はトクンと脈打った。"s,
                        u8"Your heart starts beating in your chest."s));
                    break;
                }
                if (p <= 16)
                {
                    txt(lang(
                        u8"まだだ、まだ遠い…"s,
                        u8"Still, still lying far ahead."s));
                    break;
                }
                txt(lang(
                    u8"あなたは青い水晶の存在を感じた。"s,
                    u8"You sense a blue crystal lying somewhere in this area."s));
                break;
            }
        }
    }
    for (int cnt = 0; cnt < 11; ++cnt)
    {
        y = cdata[cc].position.y + cnt - 5;
        if (y < 0 || y >= mdata(1))
        {
            continue;
        }
        for (int cnt = 0; cnt < 11; ++cnt)
        {
            x = cdata[cc].position.x + cnt - 5;
            if (x < 0 || x >= mdata(0))
            {
                continue;
            }
            if (map(x, y, 6) != 0)
            {
                cell_featread(x, y);
                refx = x;
                refy = y;
                if (std::abs(cdata[cc].position.y - y) <= 1
                    && std::abs(cdata[cc].position.x - x) <= 1)
                {
                    if (feat(1) == 14)
                    {
                        if (feat(0) == 0)
                        {
                            int stat = try_to_reveal();
                            if (stat == 1)
                            {
                                discover_trap();
                                txt(lang(
                                    u8"罠を発見した。"s,
                                    u8"You discover a trap."s));
                            }
                        }
                    }
                    if (feat(1) == 22)
                    {
                        int stat = try_to_reveal();
                        if (stat == 1 || 0)
                        {
                            discover_hidden_path();
                            txt(lang(
                                u8"隠れた通路を発見した。"s,
                                u8"You discover a hidden path."s));
                        }
                    }
                }
                if (feat(1) == 32)
                {
                    if (gdata_current_map != 35)
                    {
                        if (cdata[cc].position.x == x
                            && cdata[cc].position.y == y)
                        {
                            snd(24);
                            txt(lang(
                                u8"なんと小さなメダルを見つけた！"s,
                                u8"You find a small coin!"s));
                            map(x, y, 6) = 0;
                            flt();
                            itemcreate(-1, 622, x, y, 0);
                        }
                        else
                        {
                            if (dist(
                                    cdata[cc].position.x,
                                    cdata[cc].position.y,
                                    x,
                                    y)
                                > 2)
                            {
                                txt(lang(
                                    u8"この辺りには何かがありそうな予感がする…"s,
                                    u8"You sense something."s));
                            }
                            else
                            {
                                txt(lang(
                                    u8"あなたは何かが輝くのを目にした。"s,
                                    u8"You see something shines."s));
                            }
                        }
                    }
                }
            }
        }
    }
    cell_featread(cdata[cc].position.x, cdata[cc].position.y);
    if (feat(1) == 14)
    {
        if (feat(0) == tile_trap)
        {
            if (cdata[0].god_id == core_god::mani)
            {
                if (cc == 0)
                {
                    movx = cdata[cc].position.x;
                    movy = cdata[cc].position.y;
                    disarm_trap();
                }
            }
        }
    }
    if (feat(1) >= 24 && feat(1) <= 28)
    {
        rowactre(0) = 1;
        rowactre(1) = cdata[cc].position.x;
        rowactre(2) = cdata[cc].position.y;
        if (feat(1) == 24)
        {
            spot_digging();
        }
        if (feat(1) == 27)
        {
            spot_digging();
        }
        if (feat(1) == 26)
        {
            spot_fishing();
        }
        if (feat(1) == 25)
        {
            spot_mining_or_wall();
        }
        if (feat(1) == 28)
        {
            spot_material();
        }
    }
    return turn_result_t::turn_end;
}

turn_result_t do_pray_command()
{
    int stat = item_find(60002);
    if (stat != -1)
    {
        ci = stat;
        if (core_god::int2godid(inv[ci].param1) != cdata[0].god_id)
        {
            begin_to_believe_god();
            return turn_result_t::turn_end;
        }
    }
    return do_pray();
}

turn_result_t do_throw_command()
{
    int ccthrowpotion = 0;
    if (is_in_fov(cc))
    {
        txt(lang(
            name(cc) + u8"は"s + itemname(ci, 1) + u8"を投げた。"s,
            name(cc) + u8" throw"s + _s(cc) + u8" "s + itemname(ci, 1)
                + u8"."s));
    }
    if (dist(cdata[cc].position.x, cdata[cc].position.y, tlocx, tlocy) * 4
            > rnd(sdata(111, cc) + 10) + sdata(111, cc) / 4
        || rnd(10) == 0)
    {
        x = tlocx + rnd(2) - rnd(2);
        y = tlocy + rnd(2) - rnd(2);
        if (x >= 0)
        {
            if (y >= 0)
            {
                if (x < mdata(0))
                {
                    if (y < mdata(1))
                    {
                        if ((chipm(7, map(x, y, 0)) & 4) == 0)
                        {
                            tlocx = x;
                            tlocy = y;
                        }
                    }
                }
            }
        }
    }
    aniref(0) = inv[ci].image;
    aniref(1) = inv[ci].color;
    anix = tlocx;
    aniy = tlocy;
    play_animation(15);
    ti = inv_getfreeid(-1);
    removeitem(ci, 1);
    if (inv[ci].id == 685)
    {
        if (ti != -1)
        {
            item_copy(ci, ti);
            inv[ti].number = 1;
            inv[ti].position.x = tlocx;
            inv[ti].position.y = tlocy;
            ci = ti;
        }
    }
    if (cc == 0)
    {
        refresh_burden_state();
    }
    x = tlocx;
    y = tlocy;
    play_animation(14);
    if (inv[ci].id == 685 || inv[ci].id == 699)
    {
        snd(91);
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        if (map(tlocx, tlocy, 1) != 0)
        {
            tc = map(tlocx, tlocy, 1) - 1;
            txt(lang(
                name(tc) + u8"に見事に命中した！"s,
                u8"It hits "s + name(tc) + u8"!"s));
            if (inv[ci].id == 685)
            {
                if (tc < ELONA_MAX_PARTY_CHARACTERS
                    || cdata[tc].character_role != 0 || cdata[tc].quality == 6
                    || cdata[tc].is_lord_of_dungeon() == 1)
                {
                    txt(lang(
                        u8"その生物には無効だ。"s,
                        u8"The creature can't be captured."s));
                    return turn_result_t::turn_end;
                }
                if (cdata[tc].level > inv[ci].param2)
                {
                    txt(lang(
                        u8"その生物を捕獲するには、より高レベルのモンスターボールが必要だ。"s,
                        u8"Power level of the ball is not enough to capture the creature."s));
                    return turn_result_t::turn_end;
                }
                if (cdata[tc].hp > cdata[tc].max_hp / 10)
                {
                    txt(lang(
                        u8"捕獲するためにはもっと弱らせる必要がある。"s,
                        u8"You need to weaken the creature to capture it."s));
                    return turn_result_t::turn_end;
                }
                txtef(2);
                txt(lang(
                    name(tc) + u8"をモンスターボールに捕獲した。"s,
                    u8"You capture "s + name(tc) + u8"."s));
                animeload(8, tc);
                inv[ci].subname = cdata[tc].id;
                inv[ci].param3 = cdata[tc].level;
                inv[ci].weight = clamp(cdata[tc].weight, 10000, 100000);
                inv[ci].value = 1000;
            }
            else
            {
                if (cdata[tc].id != 319 || tc < 16)
                {
                    txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
                    return turn_result_t::turn_end;
                }
                if (gdata_current_map == 6 || gdata_current_map == 40
                    || gdata_current_map == 35)
                {
                    txt(lang(
                        u8"この場所では効果がない。"s,
                        u8"This doesn't work in this area."s));
                    return turn_result_t::turn_end;
                }
                rc = tc;
                new_ally_joins();
            }
            chara_vanquish(tc);
            quest_check();
        }
        return turn_result_t::turn_end;
    }
    if (the_item_db[inv[ci].id]->category == 52000 || inv[ci].id == 772)
    {
        if (inv[ci].id != 601)
        {
            if (is_in_fov({tlocx, tlocy}))
            {
                if (inv[ci].id == 587)
                {
                    snd(86);
                }
                else
                {
                    snd(47);
                }
            }
            if (map(tlocx, tlocy, 1) != 0)
            {
                tc = map(tlocx, tlocy, 1) - 1;
                if (is_in_fov(tc))
                {
                    txt(lang(
                        name(tc) + u8"に見事に命中した！"s,
                        u8"It hits "s + name(tc) + u8"!"s));
                    wet(tc, 25);
                }
                rowact_check(tc);
                if (inv[ci].id == 587)
                {
                    if (is_in_fov(tc))
                    {
                        if (tc != 0)
                        {
                            txtef(9);
                            txt(lang(u8"「いてー！」"s, u8"\"Hey!\""s),
                                lang(
                                    u8"「やったな」"s,
                                    u8"\"Now you did it.\""s),
                                lang(u8" *クスクス* "s, u8"*chuckle*"s),
                                lang(u8"「キャハハ」"s, u8"\"Tee-hee-hee!\""s),
                                lang(
                                    u8"「こやつめ」"s,
                                    u8"\"You'll pay for this.\""s),
                                lang(u8"「むむっ」"s, u8"*grin*"s));
                        }
                    }
                    return turn_result_t::turn_end;
                }
                if (inv[ci].id == 772)
                {
                    if (is_in_fov(tc))
                    {
                        txtef(4);
                        txt(lang(u8" *ぷちゅ* "s, u8"*crumble*"s));
                    }
                    if (inv[ci].param3 == -1)
                    {
                        if (is_in_fov(tc))
                        {
                            txtef(4);
                            txt(lang(
                                name(tc) + u8"は怒りに体を奮わせた！"s,
                                name(tc) + u8" "s + is(tc)
                                    + u8" engulfed in fury!"s));
                        }
                        cdata[tc].furious += rnd(10) + 5;
                    }
                    return turn_result_t::turn_end;
                }
                if (tc >= 16)
                {
                    hostileaction(cc, tc);
                }
                ccthrowpotion = cc;
                potionthrow = 100;
                cc = tc;
                dbid = inv[ci].id;
                access_item_db(15);
                cc = ccthrowpotion;
                return turn_result_t::turn_end;
            }
            if (inv[ci].id == 587)
            {
                if (map(tlocx, tlocy, 4) != 0)
                {
                    cell_itemlist(tlocx, tlocy);
                    f = 0;
                    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
                    {
                        p = list(0, cnt);
                        if (inv[p].id == 541)
                        {
                            if (is_in_fov({tlocx, tlocy}))
                            {
                                txt(lang(
                                    itemname(p, 1)
                                        + u8"に命中して、雪だるまは崩れた。"s,
                                    u8"It hits "s + itemname(p, 1)
                                        + u8" and breaks it."s));
                            }
                            --inv[p].number;
                            f = 1;
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        cell_refresh(tlocx, tlocy);
                        return turn_result_t::turn_end;
                    }
                }
            }
            if (inv[ci].id == 587)
            {
                if (chipm(0, map(tlocx, tlocy, 0)) == 4)
                {
                    return turn_result_t::turn_end;
                }
                if (is_in_fov({tlocx, tlocy}))
                {
                    txt(lang(
                        u8"それは地面に落ちて溶けた。"s,
                        u8"It falls on the ground and melts."s));
                }
            }
            else if (is_in_fov({tlocx, tlocy}))
            {
                txt(lang(
                    u8"それは地面に落ちて砕けた。"s,
                    u8"It falls on the ground and shatters."s));
            }
            if (inv[ci].id == 772)
            {
                if (is_in_fov({tlocx, tlocy}))
                {
                    txtef(4);
                    txt(lang(u8" *ぷちゅ* "s, u8"*crumble*"s));
                }
                return turn_result_t::turn_end;
            }
            efp = 50 + sdata(111, cc) * 10;
            if (inv[ci].id == 392)
            {
                mef_add(tlocx, tlocy, 3, 19, rnd(15) + 5, efp, cc);
                return turn_result_t::turn_end;
            }
            if (inv[ci].id == 577)
            {
                mef_add(tlocx, tlocy, 5, 24, rnd(15) + 25, efp, cc);
                mapitem_fire(tlocx, tlocy);
                return turn_result_t::turn_end;
            }
            mef_add(
                tlocx,
                tlocy,
                6,
                27,
                -1,
                efp,
                cc,
                inv[ci].id,
                static_cast<int>(inv[ci].curse_state), // TODO
                inv[ci].color);
            return turn_result_t::turn_end;
        }
    }
    if (is_in_fov({tlocx, tlocy}))
    {
        txt(lang(
            u8"それは地面に落ちて砕けた。"s,
            u8"It falls on the ground and shatters."s));
        snd(47);
    }
    if (inv[ci].id == 578)
    {
        flt();
        itemcreate(-1, 54, tlocx, tlocy, inv[ci].param1);
    }
    return turn_result_t::turn_end;
}

turn_result_t do_close_command()
{
    int stat = ask_direction_to_close();
    if (stat == 0)
    {
        txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    cell_featread(x, y);
    if (feat(1) != 20)
    {
        txt(lang(
            u8"その方向に閉められるものはない。"s,
            u8"There's nothing to close."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (map(x, y, 1) != 0)
    {
        txt(lang(
            u8"何かが邪魔で閉められない。"s,
            u8"There's something on the floor."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    cell_featset(x, y, tile_doorclosed, 21, -1, -1);
    txt(lang(name(cc) + u8"は扉を閉めた。"s, name(cc) + u8" close the door."s));
    return turn_result_t::turn_end;
}

turn_result_t do_change_ammo_command()
{
    f = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata_body_part(cc, cnt) % 10000 == 0)
        {
            continue;
        }
        if (cdata_body_part(cc, cnt) / 10000 == 11)
        {
            ci = cdata_body_part(cc, cnt) % 10000 - 1;
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        txt(lang(u8"矢弾を装備していない。"s, u8"You need to equip an ammo."s));
        return turn_result_t::pc_turn_user_error;
    }
    listmax = 0;
    cs = -1;
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[ci].enchantments[cnt].id;
        i = enc / 10000;
        if (i != 0)
        {
            enc = enc % 10000;
            if (i == 9)
            {
                if (inv[ci].count == cnt)
                {
                    cs = cnt;
                }
                list(0, listmax) = cnt;
                ++listmax;
                continue;
            }
        }
    }
    if (listmax == 0)
    {
        inv[ci].count = -1;
        txt(lang(
            itemname(ci) + u8"は切り替えに対応していない。"s,
            itemname(ci) + u8" isn't capable of changing ammos."s));
        return turn_result_t::pc_turn_user_error;
    }
    snd(90);
    ++cs;
    if (cs >= listmax)
    {
        inv[ci].count = -1;
    }
    else
    {
        inv[ci].count = list(0, cs);
    }
    txt(lang(u8"現在の装填弾:"s, u8"Current Ammo Type:"s));
    for (int cnt = 0, cnt_end = (listmax + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            s(0) = lang(u8"通常弾"s, u8"Normal"s);
            s(1) = lang(u8"無限"s, u8"Unlimited"s);
        }
        else
        {
            p = list(0, cnt - 1);
            i(0) = inv[ci].enchantments[p].power % 1000;
            i(1) = inv[ci].enchantments[p].power / 1000;
            s(0) = ammoname(inv[ci].enchantments[p].id % 10000);
            s(1) = ""s + i + u8"/"s + i(1);
        }
        s = s + u8":"s + s(1);
        if (inv[ci].count == cnt - 1)
        {
            s = u8"["s + s + u8"]"s;
            txtef(4);
        }
        else
        {
            s = u8" "s + s + u8" "s;
        }
        txt(u8" "s + s);
    }
    return turn_result_t::pc_turn_user_error;
}

turn_result_t do_offer_command()
{
    if (cdata[0].god_id.empty())
    {
        txt(lang(
            u8"あなたは神を信仰していないが、試しに捧げてみた。"s,
            u8"You don't believe in God."s));
        return turn_result_t::turn_end;
    }
    rowact_item(ci);
    item_separate(ci);
    txt(lang(
        u8"あなたは"s + itemname(ci) + u8"を"s
            + i18n::_(u8"god", cdata[0].god_id, u8"name")
            + u8"に捧げ、その名を唱えた。"s,
        u8"You put "s + itemname(ci)
            + u8" on the altar and mutter the name of "s
            + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"."s));
    snd(121);
    play_animation(7);
    int stat = item_find(60002);
    if (stat != -1)
    {
        ti = stat;
    }
    else
    {
        return turn_result_t::turn_end;
    }
    if (inv[ci].id == 204)
    {
        i = clamp(inv[ci].weight / 200, 1, 50);
        if (inv[ci].param3 < 0)
        {
            i = 1;
        }
    }
    else
    {
        i = 25;
    }
    if (core_god::int2godid(inv[ti].param1) != cdata[0].god_id)
    {
        f = 0;
        if (inv[ti].param1 == 0)
        {
            f = 1;
            txt(lang(
                u8"異世界で、"s + i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8"が空白の祭壇の権利を主張した。"s,
                i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8" claims the empty altar."s));
        }
        else
        {
            txt(lang(
                u8"異様な霧が現れ、"s
                    + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"と"s
                    + i18n::_(
                          u8"god",
                          core_god::int2godid(inv[ti].param1),
                          u8"name")
                    + u8"の幻影がせめぎあった。"s,
                u8"Strange fogs surround all over the place. You see shadows of "s
                    + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8" and "s
                    + i18n::_(
                          u8"god",
                          core_god::int2godid(inv[ti].param1),
                          u8"name")
                    + u8" make a fierce dance."s));
            if (rnd(17) <= i)
            {
                f = 1;
            }
            else
            {
                f = 0;
            }
        }
        if (f == 1)
        {
            modpiety(i * 5);
            cdata[0].praying_point += i * 30;
            animode = 100;
            play_animation(19);
            snd(120);
            if (inv[ti].param1 != 0)
            {
                txt(lang(
                    u8"あなたの神の幻影は、次第に色濃くなった。"s,
                    u8"The shadow of your god slowly gets bolder."s));
            }
            txtef(5);
            txt(lang(
                i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"は"s
                    + itemname(ti) + u8"を支配した。"s,
                i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8" takes over the altar."s));
            txtgod(cdata[0].god_id, 2);
            inv[ti].param1 = core_god::godid2int(cdata[0].god_id);
        }
        else
        {
            txt(lang(
                i18n::_(u8"god", core_god::int2godid(inv[ti].param1), u8"name")
                    + u8"は祭壇を守りきった。"s,
                i18n::_(u8"god", core_god::int2godid(inv[ti].param1), u8"name")
                    + u8" keeps the altar."s));
            txtgod(core_god::int2godid(inv[ti].param1), 3);
            label_1892();
        }
    }
    else
    {
        txtef(2);
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (i >= 15)
            {
                txt(lang(
                    itemname(ci) + u8"はまばゆく輝いて消えた。"s,
                    itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                        + u8" all around and disappear"s + _s2(inv[ci].number)
                        + u8"."s));
                txtgod(cdata[0].god_id, 4);
                break;
            }
            if (i >= 10)
            {
                txt(lang(
                    itemname(ci)
                        + u8"は輝いて消え、三つ葉のクローバーがふってきた。"s,
                    itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                        + u8" for a moment and disappear"s + _s2(inv[ci].number)
                        + u8". A three-leaved falls from the altar."s));
                break;
            }
            if (i >= 5)
            {
                txt(lang(
                    itemname(ci) + u8"は一瞬輝いて消えた。"s,
                    itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                        + u8" for a moment and disappear"s + _s2(inv[ci].number)
                        + u8"."s));
                break;
            }
            if (i >= 1)
            {
                txt(lang(
                    itemname(ci) + u8"は消えた。"s,
                    itemname(ci) + u8" disappear"s + _s2(inv[ci].number)
                        + u8"."s));
                break;
            }
        }
        modpiety(i);
        cdata[0].praying_point += i * 7;
    }
    removeitem(ci, inv[ci].number);
    return turn_result_t::turn_end;
}

turn_result_t do_look_command()
{
    page = 0;
    pagesize = 16;
    cs_bk = -1;
    label_2076();
    if (listmax == 0)
    {
        ++msgdup;
        txt(lang(
            u8"視界内にターゲットは存在しない。"s,
            u8"You look around and find nothing."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    cs = 0;
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        if (list(0, cnt) == cdata[0].enemy_id)
        {
            cs = cnt % pagesize;
            page = cnt / pagesize;
        }
    }
label_1952_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_1953_internal:
    if (cs != cs_bk)
    {
        screenupdate = -1;
        update_screen();
        keyrange = 0;
        font(20 - en * 2, snail::font_t::style_t::bold);
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            key_list(cnt) = key_select(cnt);
            ++keyrange;
            x = list(1, p) - scx;
            y = list(2, p) - scy;
            if (cs == cnt)
            {
                i = p;
                get_route(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[list(0, p)].position.x,
                    cdata[list(0, p)].position.y);
                dx = (tlocx - scx) * inf_tiles + inf_screenx;
                dy = (tlocy - scy) * inf_tiles + inf_screeny;
                if (maxroute != 0)
                {
                    dx = cdata[cc].position.x;
                    dy = cdata[cc].position.y;
                    for (int cnt = 0; cnt < 100; ++cnt)
                    {
                        int stat = route_info(dx, dy, cnt);
                        if (stat == 0)
                        {
                            break;
                        }
                        else if (stat == -1)
                        {
                            continue;
                        }
                        sx = (dx - scx) * inf_tiles + inf_screenx;
                        sy = (dy - scy) * inf_tiles + inf_screeny;
                        if (sy + inf_tiles <= windowh - inf_verh)
                        {
                            pos(sx, sy * (sy > 0));
                            snail::application::instance()
                                .get_renderer()
                                .set_blend_mode(snail::blend_mode_t::blend);
                            snail::application::instance()
                                .get_renderer()
                                .set_draw_color({255, 255, 255, 25});
                            snail::application::instance()
                                .get_renderer()
                                .fill_rect(
                                    sx,
                                    sy * (sy > 0),
                                    inf_tiles
                                        - (sx + inf_tiles > windoww)
                                            * (sx + inf_tiles - windoww),
                                    inf_tiles + (sy < 0) * inf_screeny
                                        - (sy + inf_tiles > windowh - inf_verh)
                                            * (sy + inf_tiles - windowh
                                               + inf_verh));
                        }
                    }
                }
                sx = x * inf_tiles + inf_screenx;
                sy = y * inf_tiles + inf_screeny;
                if (sy + inf_tiles <= windowh - inf_verh)
                {
                    pos(sx, sy * (sy > 0));
                    snail::application::instance()
                        .get_renderer()
                        .set_blend_mode(snail::blend_mode_t::blend);
                    snail::application::instance()
                        .get_renderer()
                        .set_draw_color({127, 127, 255, 50});
                    snail::application::instance().get_renderer().fill_rect(
                        sx,
                        sy * (sy > 0),
                        inf_tiles,
                        inf_tiles + (sy < 0) * inf_screeny
                            - (sy + inf_tiles > windowh - inf_verh)
                                * (sy + inf_tiles - windowh + inf_verh));
                }
            }
            display_key(
                x * inf_tiles + inf_screenx - 12,
                y * inf_tiles + inf_screeny - 12,
                cnt);
        }
        color(0, 0, 0);
        txttargetnpc(
            cdata[list(0, i)].position.x, cdata[list(0, i)].position.y);
        cs_bk = cs;
        render_hud();
        redraw();
    }
    await(config::instance().wait1);
    key_check();
    cursor_check();
    if (key == key_target)
    {
        key = key_list(cs);
    }
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (p != -1)
    {
        cdata[0].enemy_id = p;
        snd(20);
        txt(lang(
            name(p) + u8"をターゲットにした。"s,
            u8"You target "s + name(p) + u8"."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1952_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1952_internal;
        }
    }
    if (key == key_cancel)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    goto label_1953_internal;
}

turn_result_t do_dip_command()
{
    if (inv[cidip].id == 617)
    {
        item_separate(ci);
        item_num(cidip, -1);
        snd(13);
        txt(lang(
            itemname(cidip, 1) + u8"を"s + itemname(ci) + u8"に装着した。"s,
            u8"You bait "s + itemname(ci) + u8" with "s + itemname(cidip, 1)
                + u8"."s));
        if (inv[ci].param4 == inv[cidip].param1)
        {
            inv[ci].count += rnd(10) + 15;
        }
        else
        {
            inv[ci].count = rnd(10) + 15;
            inv[ci].param4 = inv[cidip].param1;
        }
        return turn_result_t::turn_end;
    }
    snd(17);
    if (the_item_db[inv[cidip].id]->category == 52000)
    {
        if (the_item_db[inv[ci].id]->subcategory == 60001)
        {
            item_separate(ci);
            item_num(cidip, -1);
            if (inv[cidip].id != 601)
            {
                txt(lang(
                    itemname(cidip, 1) + u8"を"s + itemname(ci)
                        + u8"に浸した。"s,
                    u8"You dip "s + itemname(ci) + u8" into "s
                        + itemname(cidip, 1) + u8"."s));
                if (inv[ci].id == 602)
                {
                    txt(lang(
                        u8"井戸は汚れた。"s, u8"The holy well is polluted."s));
                    return turn_result_t::turn_end;
                }
                if (inv[ci].param3 >= 20)
                {
                    txt(lang(
                        itemname(ci) + u8"は完全に枯れている。"s,
                        itemname(ci) + u8" is completely dry."s));
                    return turn_result_t::turn_end;
                }
                txt(lang(
                    itemname(ci) + u8"は一瞬輝いた。"s,
                    itemname(ci) + u8" shines for a moment."s));
                if (inv[cidip].id == 587)
                {
                    txt(lang(u8"こんな量では… "s, u8"Snow just melts."s));
                }
                else
                {
                    inv[ci].param1 += rnd(3);
                }
                return turn_result_t::turn_end;
            }
            else
            {
                if (inv[ci].param1 < -5 || inv[ci].param3 >= 20
                    || (inv[ci].id == 602 && gdata_holy_well_count <= 0))
                {
                    const auto valn = itemname(ci);
                    txt(lang(valn + u8"は涸れている。"s, valn + u8" is dry."s));
                    txt(lang(
                        u8"あっ！空き瓶を井戸に落としてしまった…"s,
                        u8"Ops! You drop the empty bottle into the well..."s));
                    return turn_result_t::turn_end;
                }
                if (inv_getfreeid(0) == -1)
                {
                    txt(lang(
                        u8"バックパックが一杯だ。"s,
                        u8"Your inventory is full."s));
                    return turn_result_t::turn_end;
                }
                if (inv[ci].id == 602)
                {
                    --gdata_holy_well_count;
                    flt();
                    int stat = itemcreate(0, 516, -1, -1, 0);
                    if (stat != 0)
                    {
                        inv[ci].curse_state = curse_state_t::blessed;
                    }
                }
                else
                {
                    inv[ci].param1 -= 3;
                    flt(20);
                    flttypemajor = 52000;
                    itemcreate(0, 0, -1, -1, 0);
                }
                txt(lang(
                    u8"空き瓶に水をすくった。"s,
                    u8"You draw water from the well into the empty bottle."s));
                txt(lang(
                    itemname(ci, 1) + u8"を手に入れた。"s,
                    u8"You get "s + itemname(ci, 1) + u8"."s));
                item_stack(0, ci, 1);
                return turn_result_t::turn_end;
            }
        }
    }
    if (inv[cidip].id == 262)
    {
        if (the_item_db[inv[ci].id]->category == 57000)
        {
            item_num(cidip, -1);
            item_separate(ci);
            txt(lang(
                itemname(ci) + u8"に"s + itemname(cidip, 1)
                    + u8"を混入した！あなたはにやりと笑った。"s,
                u8"You made aphrodisiac food! You grin."s));
            if (is_cursed(inv[cidip].curse_state))
            {
                dipcursed(ci);
            }
            ibitmod(14, ci, 1);
            return turn_result_t::turn_end;
        }
    }
    if (inv[cidip].id == 620)
    {
        if (the_item_db[inv[ci].id]->category == 57000)
        {
            item_num(cidip, -1);
            item_separate(ci);
            txt(lang(
                itemname(ci) + u8"に"s + itemname(cidip, 1)
                    + u8"を混入した！あなたはうしろめたさを感じた…"s,
                u8"You made aphrodisiac food! You kind of feel guilty..."s));
            if (is_cursed(inv[cidip].curse_state))
            {
                dipcursed(ci);
            }
            ibitmod(6, ci, 1);
            return turn_result_t::turn_end;
        }
    }
    if (inv[cidip].id == 519)
    {
        if (inv[cidip].curse_state == curse_state_t::blessed)
        {
            in = inv[cidip].number;
        }
        else
        {
            in = 1;
            item_separate(ci);
        }
        item_num(cidip, -1);
        inv[ci].color = inv[cidip].color;
        txt(lang(
            u8"あなたは"s + itemname(ci) + u8"を染めた。"s,
            u8"You dye "s + itemname(ci) + u8"."s));
        if (inv_getowner(ci) == -1)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        if (inv[ci].body_part != 0)
        {
            create_pcpic(cc, true);
        }
        return turn_result_t::turn_end;
    }
    if (inv[cidip].id == 566)
    {
        if (inv[cidip].curse_state == curse_state_t::blessed)
        {
            in = inv[cidip].number;
        }
        else
        {
            in = 1;
            item_separate(ci);
        }
        txt(lang(
            itemname(ci) + u8"に"s + itemname(cidip, 1) + u8"を塗りたくった。"s,
            u8"You put "s + itemname(cidip, 1) + u8" on "s + itemname(ci)
                + u8"."s));
        if (is_cursed(inv[cidip].curse_state))
        {
            dipcursed(ci);
        }
        else
        {
            ibitmod(1, ci, 1);
            txt(lang(
                itemname(ci) + u8"は酸から守られた。"s,
                itemname(ci) + u8" gain"s + _s2(in) + u8" acidproof."s));
        }
        item_num(cidip, -1);
        return turn_result_t::turn_end;
    }
    if (inv[cidip].id == 736)
    {
        if (inv[cidip].curse_state == curse_state_t::blessed)
        {
            in = inv[cidip].number;
        }
        else
        {
            in = 1;
            item_separate(ci);
        }
        txt(lang(
            itemname(ci, in) + u8"に"s + itemname(cidip, 1)
                + u8"を塗りたくった。"s,
            u8"You put "s + itemname(cidip, 1) + u8" on "s + itemname(ci, in)
                + u8"."s));
        if (is_cursed(inv[cidip].curse_state))
        {
            dipcursed(ci);
        }
        else if (inv[ci].id == 567)
        {
            txt(lang(u8"いいアイデアだ！しかし…"s, u8"A good idea! But..."s));
        }
        else
        {
            ibitmod(2, ci, 1);
            txt(lang(
                itemname(ci) + u8"は熱から守られた。"s,
                itemname(ci) + u8" gain"s + _s2(in) + u8" fireproof."s));
        }
        item_num(cidip, -1);
        return turn_result_t::turn_end;
    }
    if (inv[cidip].id == 516)
    {
        item_num(cidip, -1);
        if (inv[cidip].curse_state == curse_state_t::blessed)
        {
            txtef(2);
            txt(lang(
                itemname(ci) + u8"は銀色に輝いた。"s,
                itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                    + u8" silvery."s));
            inv[ci].curse_state = curse_state_t::blessed;
            chara_refresh(cc);
            return turn_result_t::turn_end;
        }
        if (is_cursed(inv[cidip].curse_state))
        {
            txtef(8);
            txt(lang(
                itemname(ci) + u8"は黒いオーラに包まれた。"s,
                itemname(ci) + u8" "s + is2(inv[ci].number)
                    + u8" wrapped by a dark aura."s));
            inv[ci].curse_state = curse_state_t::cursed;
            chara_refresh(cc);
            return turn_result_t::turn_end;
        }
    }
    txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
    return turn_result_t::turn_end;
}

turn_result_t do_use_command()
{
    screenupdate = -1;
    update_screen();
    tc = cc;
    tlocx = cdata[cc].position.x;
    tlocy = cdata[cc].position.y;
    if (ibit(7, ci) == 1)
    {
        if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12
            < inv[ci].count)
        {
            txt(lang(
                u8"そのアイテムが次に使用できるのは"s + cnvdate(inv[ci].count)
                    + u8"だ。"s,
                u8"This item will be useable again at "s
                    + cnvdate(inv[ci].count) + u8"."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        item_separate(ci);
        inv[ci].count = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12 + inv[ci].param3;
    }
    if (ibit(4, ci) == 1)
    {
        if (inv[ci].count <= 0)
        {
            txt(lang(u8"それはもう使えない。"s, u8"It's out of charge."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        item_separate(ci);
        --inv[ci].count;
    }
    if (the_item_db[inv[ci].id]->subcategory == 58500)
    {
        return do_plant();
    }
    if (the_item_db[inv[ci].id]->subcategory == 59500)
    {
        return blending_menu();
    }
    if (the_item_db[inv[ci].id]->subcategory == 60004)
    {
        if (gdata_continuous_active_hours < 15)
        {
            txt(lang(u8"まだ眠たくない。"s, u8"You don't feel sleepy yet."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        gdata(91) = 100;
        continuous_action_others();
        return turn_result_t::turn_end;
    }
    if (inv[ci].id == 413 || inv[ci].id == 414)
    {
        return do_gatcha();
    }
    if (inv[ci].id == 312 || inv[ci].id == 313 || inv[ci].id == 314
        || inv[ci].id == 315)
    {
        atxid = 1;
        casino_dealer();
        return turn_result_t::turn_end;
    }
    if (inv[ci].function == 1 || inv[ci].function == 2 || inv[ci].function == 3
        || inv[ci].function == 4)
    {
        prodtype = inv[ci].function;
        snd(26);
        invctrl = 0;
        crafting_menu();
        return turn_result_t::turn_end;
    }
    if (ibit(10, ci))
    {
        if (inv[ci].param2 < calcexpalive(inv[ci].param1))
        {
            txt(lang(
                u8"この武器はまだ血を吸い足りない。"s,
                u8"The weapon needs more blood."s));
        }
        else
        {
            txtnew();
            txt(lang(
                itemname(ci) + u8"は十分に血を吸い成長できる！"s,
                itemname(ci) + u8" sucked enough blood and ready to grow!"s));
            randomize(inv[ci].subname);
            exrand_randomize(inv[ci].subname);
            if (inv[ci].param1 >= 4 + rnd(12))
            {
                txt(lang(
                    u8"しかし、なんだか様子がおかしい…"s,
                    u8"But you sense something weird."s));
            }
            txt(lang(u8"それは…"s, u8"It..."s));
            reftype = the_item_db[inv[ci].id]->category;
            listmax = 0;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                randomize(inv[ci].subname + inv[ci].param1 * 10 + cnt);
                exrand_randomize(inv[ci].subname + inv[ci].param1 * 10 + cnt);
                int stat = enchantment_add(
                    ci,
                    enchantment_generate(enchantment_gen_level(4)),
                    enchantment_gen_p(),
                    0,
                    0,
                    1);
                if (stat != 0)
                {
                    if (rtval == 34)
                    {
                        if (rnd(3))
                        {
                            continue;
                        }
                    }
                    list(0, listmax) = rtval;
                    list(1, listmax) = rtval(1);
                    get_enchantment_description(
                        list(0, listmax), list(1, listmax), 0);
                    ELONA_APPEND_PROMPT(s, u8"null"s, ""s + promptmax);
                    ++listmax;
                }
            }
            list(0, listmax) = -1;
            ++listmax;
            s = lang(u8"ボーナス+1"s, u8"Bonus+1"s);
            ELONA_APPEND_PROMPT(s, u8"null"s, ""s + promptmax);
            rtval = show_prompt(promptx, prompty, 400);
            txtnew();
            if (rtval == -1)
            {
                txt(lang(
                    itemname(ci) + u8"は不満そうに震えた。"s,
                    itemname(ci) + u8" vibrates as if she is displeased."s));
            }
            else
            {
                if (list(0, rtval) == -1)
                {
                    ++inv[ci].enhancement;
                }
                else
                {
                    enchantment_add(ci, list(0, rtval), list(1, rtval), 0, 1);
                }
                txtef(2);
                txt(lang(
                    itemname(ci) + u8"は嬉しげに震えた。"s,
                    itemname(ci) + u8" vibrates as if she is pleased."s));
                randomize(inv[ci].subname);
                exrand_randomize(inv[ci].subname);
                if (inv[ci].param1 >= 4 + rnd(12))
                {
                    txt(lang(
                        u8"その力は次第に脅威になっている。"s,
                        u8"Its power is becoming a threat."s));
                    int stat = enchantment_add(ci, 45, 50);
                    if (stat == 0)
                    {
                        inv[ci].enchantments[14].id = 0;
                        txt(lang(
                            itemname(ci) + u8"はエンチャントを消した。"s,
                            itemname(ci) + u8" removes an enchantment."s));
                    }
                }
                inv[ci].param2 = 0;
                ++inv[ci].param1;
            }
            randomize();
            exrand_randomize();
        }
        chara_refresh(cc);
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    switch (inv[ci].function)
    {
    case 24:
        x = cdata[cc].position.x;
        y = cdata[cc].position.y;
        if (mdata(6) == 1)
        {
            txt(lang(u8"ここでは使えない。"s, u8"You can't place it here."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        if (map(x, y, 6) != 0)
        {
            txt(lang(u8"ここには置けない。"s, u8"You can't place it here."s));
            return turn_result_t::pc_turn_user_error;
        }
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        cell_featset(x, y, 0, 14, 7, cc);
        txt(lang(u8"地雷を設置した。"s, u8"You set up the mine."s));
        snd(58);
        goto label_2229_internal;
    case 44:
        if (inv_getowner(ci) != -1)
        {
            txt(lang(
                u8"床に置かないと使えない。"s,
                u8"You need to put it on the ground."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        txt(lang(
            u8"あなたは"s + itemname(ci, 1) + u8"に座った。"s,
            u8"You sit on "s + itemname(ci, 1) + u8"."s));
        ELONA_APPEND_PROMPT(
            lang(u8"くつろぐ"s, u8"Relax."s), u8"null"s, ""s + 0);
        if (inv[ci].param1 != 1)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"マイチェアにする"s, u8"It's my chair."s),
                u8"null"s,
                ""s + 1);
        }
        if (inv[ci].param1 != 2)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"お客用のチェアにする"s, u8"It's for my guest."s),
                u8"null"s,
                ""s + 2);
        }
        if (inv[ci].param1 != 0)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"誰でも座っていい"s, u8"It's free to use."s),
                u8"null"s,
                ""s + 3);
        }
        {
            int stat = show_prompt(promptx, prompty, 260);
            if (stat == -1)
            {
                goto label_2229_internal;
            }
            rtval = stat;
        }
        if (rtval == 0)
        {
            txt(lang(
                u8"あなたは存分にくつろいだ。"s,
                u8"You relax as much as you like."s));
            goto label_2229_internal;
        }
        if (rtval == 1)
        {
            txt(lang(
                itemname(ci, 1) + u8"はあなた専用の席になった！"s,
                itemname(ci, 1) + u8" is your seat now."s));
            inv[ci].param1 = 1;
            goto label_2229_internal;
        }
        if (rtval == 2)
        {
            txt(lang(
                itemname(ci, 1) + u8"は訪問者の席になった！"s,
                itemname(ci, 1) + u8" is used by your guests now."s));
            inv[ci].param1 = 2;
            goto label_2229_internal;
        }
        if (rtval == 3)
        {
            txt(lang(
                itemname(ci, 1) + u8"は誰でも座っていい席になった！"s,
                itemname(ci, 1) + u8" can be used by anyone."s));
            inv[ci].param1 = 0;
            goto label_2229_internal;
        }
        goto label_2229_internal;
    case 8:
        if (mdata(6) != 5)
        {
            txt(lang(
                u8"それはここでは使えない。"s, u8"You can't use it here."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        screenupdate = -1;
        update_screen();
        return turn_result_t::show_house_board;
    case 19:
        txt(lang(u8"誰を対象にする？"s, u8"Make up who?"s));
        {
            int stat = ask_direction();
            f = 0;
            if (stat != 0)
            {
                if (map(x, y, 1) > 0)
                {
                    tc = map(x, y, 1) - 1;
                    if (tc < 16)
                    {
                        screenupdate = -1;
                        update_screen();
                        ccbk = cc;
                        cc = tc;
                        label_2044();
                        cc = ccbk;
                        f = 1;
                    }
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        }
        update_screen();
        return turn_result_t::pc_turn_user_error;
        break;
    case 15:
        efid = 184;
        magic();
        goto label_2229_internal;
    case 16:
        efid = 185;
        magic();
        goto label_2229_internal;
    case 17:
        efid = 183;
        magic();
        goto label_2229_internal;
    case 14:
        if (cc == 0)
        {
            if (inv[ci].number < 5)
            {
                txt(lang(u8"雪が足りない…"s, u8"You need more snow."s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
            removeitem(ci, 5);
        }
        flt();
        itemcreate(-1, 541, cdata[0].position.x, cdata[0].position.y, 0);
        if (is_in_fov(cc))
        {
            snd(86);
            txt(lang(
                name(cc) + u8"は雪だるまを作った！"s,
                name(cc) + u8" make"s + _s(cc) + u8" a snow man!"s));
        }
        goto label_2229_internal;
    case 13:
        snd(6);
        if (gdata_torch == 0)
        {
            gdata_torch = 1;
            txt(lang(u8"松明を灯した。"s, u8"You light up the torch."s));
        }
        else
        {
            gdata_torch = 0;
            txt(lang(u8"松明を消した。"s, u8"You put out the fire."s));
        }
        chara_refresh(0);
        goto label_2229_internal;
    case 9:
    {
        int stat = label_2083();
        if (stat == 1)
        {
            return turn_result_t::turn_end;
        }
        else
        {
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
    }
        goto label_2229_internal;
    case 5:
        txt(lang(u8"何に聴診器を当てる？"s, u8"Auscultate who?"s));
        update_screen();
        {
            int stat = ask_direction();
            if (stat == 0)
            {
                txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
        }
        tc = map(x, y, 1) - 1;
        if (tc == 0)
        {
            txt(lang(u8" *ドクン ドクン* "s, u8"You blush."s));
            gdata(94) = 0;
            return turn_result_t::turn_end;
        }
        if (tc > 0 && tc < 16)
        {
            if (cdata[tc].state == 1)
            {
                gdata(94) = 0;
                if (cdata[tc].has_been_used_stethoscope() == 1)
                {
                    cdata[tc].has_been_used_stethoscope() = false;
                    txt(lang(
                        name(tc) + u8"から聴診器を外した。"s,
                        u8"You no longer watch on "s + his(tc)
                            + u8" health."s));
                    return turn_result_t::turn_end;
                }
                txt(lang(
                    u8"あなたは"s + name(tc) + u8"に聴診器を当てた。"s,
                    u8"You start to keep an eye on "s + his(tc)
                        + u8" health."s));
                if (cdata[tc].sex == 1)
                {
                    txt(lang(
                        ""s + name(tc) + u8"は顔を赤らめた。"s,
                        name(tc) + u8" blush"s + _s(tc, true) + u8"."s));
                    txtef(4);
                    txt(lang(u8"「キャー」"s, u8"\"Pervert!\""s));
                }
                cdata[tc].has_been_used_stethoscope() = true;
                return turn_result_t::turn_end;
            }
        }
        txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
        break;
    case 23:
        txt(lang(u8"誰を紐で結ぶ？"s, u8"Leash who?"s));
        update_screen();
        {
            int stat = ask_direction();
            f = 0;
            if (stat != 0)
            {
                if (map(x, y, 1) > 0)
                {
                    tc = map(x, y, 1) - 1;
                    if (tc == 0)
                    {
                        txt(lang(
                            u8"あなたは自分を紐でくくってみた…"s,
                            u8"You leash yourself..."s));
                    }
                    else if (cdata[tc].is_leashed() == 0)
                    {
                        if (tc >= 16)
                        {
                            if (rnd(5) == 0)
                            {
                                txt(lang(
                                    name(tc)
                                        + u8"が激しく抵抗したため紐は切れた。"s,
                                    u8"The leash is cut as "s + name(tc)
                                        + u8" resists."s));
                                --inv[ci].number;
                                cell_refresh(
                                    inv[ci].position.x, inv[ci].position.y);
                                refresh_burden_state();
                                goto label_2229_internal;
                            }
                        }
                        cdata[tc].is_leashed() = true;
                        txt(lang(
                            u8"あなたは"s + name(tc)
                                + u8"を紐でくくりつけた。"s,
                            u8"You leash "s + name(tc) + u8"."s));
                        txtef(9);
                        txt(lang(
                            name(tc) + u8"は呻き声を洩らした。「アン…♪」"s,
                            name(tc) + u8" gasp"s + _s(tc) + u8", "s
                                + u8"\"Pervert!\""s));
                    }
                    else
                    {
                        cdata[tc].is_leashed() = false;
                        txt(lang(
                            u8"あなたは"s + name(tc)
                                + u8"にくくりつけた紐をほどいた。"s,
                            u8"You unleash "s + name(tc) + u8"."s));
                        txtef(9);
                        txt(lang(
                            name(tc) + u8"は呻き声を洩らした。「はぁはぁ…」"s,
                            name(tc) + u8" gasp"s + _s(tc) + u8", "s
                                + u8"\"D-don't sto....N-nothing!\""s));
                    }
                    animeload(8, tc);
                    f = 1;
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        }
        goto label_2229_internal;
    case 45:
        if (gdata_current_map == 35)
        {
            txt(lang(
                u8"このエリアでは使えない。"s,
                u8"You cant use it in this area."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        txt(lang(u8"誰を吊るす？"s, u8"Hang who?"s));
        update_screen();
        {
            int stat = ask_direction();
            f = 0;
            if (stat != 0)
            {
                if (map(x, y, 1) > 0)
                {
                    tc = map(x, y, 1) - 1;
                    if (cdata[tc].hp >= cdata[tc].max_hp / 5)
                    {
                        txt(lang(
                            u8"もっと弱らせないと吊るせない。"s,
                            u8"The target needs to be weakened."s));
                        return turn_result_t::pc_turn_user_error;
                    }
                    if (tc != 0)
                    {
                        if (tc < 16)
                        {
                            txt(lang(
                                u8"仲間を吊るすなんてとんでもない！"s,
                                u8"Hanging your ally is a brutal idea!"s));
                            return turn_result_t::pc_turn_user_error;
                        }
                    }
                    if (cdata[tc].is_hung_on_sand_bag())
                    {
                        txt(lang(
                            u8"それは既に吊るされている。"s,
                            u8"It's already hanged up."s));
                        return turn_result_t::pc_turn_user_error;
                    }
                    if (tc == 0)
                    {
                        txt(lang(
                            u8"あなたは自分を吊るそうと思ったがやめた…"s,
                            u8"You try to hang yourself but rethink..."s));
                    }
                    else
                    {
                        snd(58);
                        cdata[tc].is_hung_on_sand_bag() = true;
                        txt(lang(
                            u8"あなたは"s + name(tc) + u8"を吊るした。"s,
                            u8"You hang up "s + name(tc) + u8"."s));
                        txt(lang(
                            name(tc) + u8"は呻き声を洩らした。「アン…♪」"s,
                            name(tc) + u8" gasp"s + _s(tc) + u8", "s
                                + u8"\"Pervert!\""s));
                        animeload(8, tc);
                        --inv[ci].number;
                        cell_refresh(inv[ci].position.x, inv[ci].position.y);
                        refresh_burden_state();
                    }
                    f = 1;
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        }
        goto label_2229_internal;
    case 6:
    {
        txt(lang(
            itemname(ci, 1) + u8"を再生した。"s,
            u8"You play "s + itemname(ci, 1) + u8"."s));
        auto music = inv[ci].param1 + 50 + 1;
        if (music > 90)
        {
            music = 90;
        }
        mdata(13) = music;
        play_music(music);
    }
        goto label_2229_internal;
    case 10:
        screenupdate = -1;
        update_screen();
        return turn_result_t::play_scene;
    case 7:
        if (inv[ci].own_state != 3)
        {
            if (mdata(7) == 0 || gdata_current_map == 13
                || gdata_current_map == 30)
            {
                if (gdata_current_map == 2)
                {
                    txt(lang(
                        u8"ワールドマップで建設するべきだ。"s,
                        u8"You can only build it in the world map."s));
                }
                else
                {
                    txt(lang(
                        u8"ここには建てられない。"s,
                        u8"You can't build it here."s));
                }
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
            gdata(91) = 101;
            continuous_action_others();
            return turn_result_t::turn_end;
        }
        if (adata(16, gdata_current_map) == 8)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                if (adata(20, gdata_current_map) != -1)
                {
                    txt(lang(
                        u8"クエストを放棄してシェルターに非難する？"s,
                        u8"Really give up the quest and evacuate to the shelter?"s));
                    ELONA_YES_NO_PROMPT();
                    rtval = show_prompt(promptx, prompty, 160);
                    if (rtval != 0)
                    {
                        update_screen();
                        return turn_result_t::pc_turn_user_error;
                    }
                }
            }
        }
        gdata(91) = 102;
        continuous_action_others();
        goto label_2229_internal;
    case 11:
        if (moneybox(inv[ci].param2) > cdata[0].gold)
        {
            txt(lang(
                u8"金貨が足りない…"s, u8"You count your coins and sigh..."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        if (inv[ci].param1 >= 1000000000)
        {
            txt(lang(u8"貯金箱は一杯だ。"s, u8"The money box is full."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        item_separate(ci);
        snd(12);
        cdata[0].gold -= moneybox(inv[ci].param2);
        inv[ci].param1 += moneybox(inv[ci].param2);
        inv[ci].weight += 100;
        goto label_2229_internal;
    case 20:
        efid = 458;
        efp = 400;
        magic();
        goto label_2229_internal;
    case 47:
        txt(lang(u8"それは鈍く輝いた。"s, u8"It glows dully."s));
        goto label_2229_internal;
    case 22:
        snd(118);
        if (mdata(6) != 3 && mdata(6) != 2)
        {
            txt(lang(
                u8"それは街でしか使えない。"s,
                u8"You can only use it in a town."s));
            goto label_2229_internal;
        }
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        txt(lang(
            u8"突然、あなたの目の前に異次元へのゲートが現れた。"s,
            u8"Suddenly, a strange gate opens."s));
        comctrl = 2;
        {
            int stat = label_19432();
            if (stat == 1)
            {
                return do_enter_strange_gate();
            }
        }
        goto label_2229_internal;
    case 49:
        txt(lang(
            itemname(ci, 1) + u8"を振った。"s,
            u8"You swing "s + itemname(ci, 1) + u8"."s));
        snd(58);
        efid = 49;
        efp = 100;
        magic();
        goto label_2229_internal;
    case 21:
        txt(lang(
            itemname(ci, 1) + u8"を振った。"s,
            u8"You swing "s + itemname(ci, 1) + u8"."s));
        snd(58);
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        fixmaterial = inv[ci].material;
        efid = 21;
        efp = 500;
        magic();
        goto label_2229_internal;
    case 25:
        txt(lang(
            itemname(ci, 1) + u8"を使った。"s,
            u8"You hold "s + itemname(ci, 1) + u8" up high."s));
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        efid = 637;
        efp = 500;
        magic();
        goto label_2229_internal;
    case 26:
        txt(lang(
            itemname(ci, 1) + u8"を始動させた。"s,
            u8"You activate "s + itemname(ci, 1) + u8"."s));
        gdata_diastrophism_flag = 1;
        snd(64);
        txtef(5);
        txt(lang(
            u8"オパートス「フハハハ！間もなく、この地に変動が起こるであろう！」"s,
            u8"A voice echoes, "s
                + u8"\"Muwahahaha! I shall shake the land for you!\""s));
        goto label_2229_internal;
    case 34:
        txt(lang(
            itemname(ci, 1) + u8"を始動させた。"s,
            u8"You activate "s + itemname(ci, 1) + u8"."s));
        txtef(5);
        txt(lang(
            u8"ジュア「べ、別にあんたのためにするんじゃないからね。バカっ！」"s,
            u8"A voice echoes, "s + u8"\"I-I'm not doing for you! Silly!\""s));
        efid = 637;
        efp = 5000;
        magic();
        goto label_2229_internal;
    case 43:
        txt(lang(
            itemname(ci, 1) + u8"を始動させた。"s,
            u8"You activate "s + itemname(ci, 1) + u8"."s));
        snd(64);
        txtef(5);
        txt(lang(
            u8"エヘカトル「呼んだ？呼んだ？」"s,
            u8"A voice echoes, "s + u8"\"Did you call me? Call me?\""s));
        buff_add(tc, 19, 77, 2500);
        goto label_2229_internal;
    case 27:
        txt(lang(
            itemname(ci, 1) + u8"を始動させた。"s,
            u8"You activate "s + itemname(ci, 1) + u8"."s));
        snd(64);
        txtef(5);
        if (gdata_weather == 1)
        {
            txt(lang(
                u8"ルルウィ「あさはかね。エーテルの風を止めてあげるとでも思ったの？」"s,
                u8"A rather angry voice echoes, "s
                u8"\"Listen my little slave. Did you really think I would turn a hand in this filthy wind for you?\""s));
            goto label_2229_internal;
        }
        p = gdata_weather;
        while (1)
        {
            if (rnd(10) == 0)
            {
                gdata_weather = 0;
            }
            if (rnd(10) == 0)
            {
                gdata_weather = 3;
            }
            if (rnd(15) == 0)
            {
                gdata_weather = 4;
            }
            if (rnd(20) == 0)
            {
                gdata_weather = 2;
            }
            if (gdata_weather != p)
            {
                break;
            }
        }
        txt(lang(
            u8"ルルウィ「あらあら、定命の分際でそんなおねだりするの？ウフフ…今回は特別よ」"s,
            u8"An impish voice echoes, "s
            u8"\"Ah you ask too much for a mortal. Still, it is hard to refuse a call from such a pretty slave like you.\""s));
        txt(lang(u8"天候が変わった。"s, u8"The weather changes."s));
        envonly = 1;
        play_music();
        goto label_2229_internal;
    case 28:
        if (mdata(6) == 1)
        {
            txt(lang(u8"ここでは使えない。"s, u8"You can't place it here."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        if (cdata[0].position.x != 33 || cdata[0].position.y != 16)
        {
            if (gdata_red_blossom_in_palmia == 1)
            {
                txt(lang(
                    u8"ここはクエストの目標位置ではない。本当にここに設置する？"s,
                    u8"This location is not your quest goal. Really place it here?"s));
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    update_screen();
                    return turn_result_t::pc_turn_user_error;
                }
            }
        }
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        txt(lang(
            u8"原子爆弾を設置した。逃げろォー！"s,
            u8"You set up the nuke...now run!!"s));
        snd(58);
        mef_add(
            cdata[cc].position.x, cdata[cc].position.y, 7, 632, 10, 100, cc);
        goto label_2229_internal;
    case 48:
        if (gdata_current_map != 35 || usermapid == 0)
        {
            txt(lang(
                u8"それはこの場所ではみすぼらしく見える。"s,
                u8"It looks so dumb here."s));
            goto label_2229_internal;
        }
        txt(lang(
            u8"この石像を見つめていると、何かを投げつけたくなってうずうずしてきた！"s,
            u8"Watching this strange statue makes you want to throw something at it!"s));
        goto label_2229_internal;
    case 29:
        trait(inv[ci].param1) = 1;
        if (inv[ci].param1 == 169)
        {
            trait(162) = 0;
        }
        if (inv[ci].param1 == 162)
        {
            trait(169) = 0;
        }
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        txt(lang(
            u8"あなたは新たなフィートを獲得した！"s,
            u8"You gain a new feat."s));
        animeload(10, 0);
        chara_refresh(cc);
        goto label_2229_internal;
    case 30:
        txt(lang(
            itemname(ci, 1) + u8"を始動させた。"s,
            u8"You activate "s + itemname(ci, 1) + u8"."s));
        efid = inv[ci].param1;
        efp = inv[ci].param2;
        tc = cc;
        efstatus = curse_state_t::none;
        magic();
        goto label_2229_internal;
    case 41:
        if (gdata_next_level_minus_one_kumiromis_experience_becomes_available
            > cdata[0].level)
        {
            txt(lang(
                u8"クミロミの声がした。「ダメ…経験…足りない…」"s,
                u8"Kumiromi talks to you, "s
                u8"\"No...you aren't...experienced enough...for this...\""s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        snd(64);
        gdata_next_level_minus_one_kumiromis_experience_becomes_available += 10;
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        ++gdata_acquirable_feat_count;
        txt(lang(
            u8"「…よく…経験をつんだね…酬いてあげる…」"s,
            u8"\"...You have acquired enough...experience...I shall reward you...\""s));
        txtef(5);
        txt(lang(
            u8"クミロミはあなたを祝福した。あなたは新たなフィートを取得できるようになった！"s,
            u8"Kumiromi blesses you. You can obtain one more feat now!"s));
        goto label_2229_internal;
    case 42:
        snd(38);
        txtef(8);
        txt(lang(
            u8"何だか嫌な予感がする…"s,
            u8"You have a bad feeling about this..."s));
        goto label_2229_internal;
    case 46:
        txtnew();
        txt(lang(u8"本当に首を吊る？"s, u8"Really hang yourself?"s));
        ELONA_YES_NO_PROMPT();
        rtval = show_prompt(promptx, prompty, 160);
        if (rtval != 0)
        {
            return turn_result_t::turn_end;
        }
        dmghp(0, 99999, -20);
        goto label_2229_internal;
    case 33:
        if (inv[ci].subname == 0)
        {
            txt(lang(
                u8"モンスターボールは空っぽだ。"s, u8"This ball is empty."s));
            goto label_2229_internal;
        }
        if (chara_get_free_slot_ally() == 0)
        {
            txt(lang(
                u8"仲間はこれ以上増やせない。"s, u8"Your party is full."s));
            goto label_2229_internal;
        }
        txt(lang(
            itemname(ci, 1) + u8"を使用した。"s,
            u8"You activate "s + itemname(ci, 1) + u8"."s));
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        flt();
        novoidlv = 1;
        chara_create(56, inv[ci].subname, -3, 0);
        rc = 56;
        new_ally_joins();
        goto label_2229_internal;
    case 31:
        x = cdata[cc].position.x;
        y = cdata[cc].position.y;
        cell_featread(x, y);
        if (feat(1) != 29)
        {
            txt(lang(
                u8"それは種を植えた場所で使わなければならない。"s,
                u8"You don't see any plant on the ground."s));
            goto label_2229_internal;
        }
        if (feat == tile_plant + 2)
        {
            txt(lang(
                u8"この作物は既に成長しきっている。"s,
                u8"The plant has already grown full."s));
            goto label_2229_internal;
        }
        if (feat == tile_plant + 3)
        {
            feat = tile_plant + 1;
            try_to_grow_plant();
            txt(lang(u8"枯れた植物に生命が宿った。"s, u8"The plant revives."s));
        }
        else
        {
            ++feat;
            txt(lang(u8"植物は成長した。"s, u8"The plant grows."s));
        }
        cell_featset(x, y, feat, feat(1), feat(2), feat(3));
        animeload(8, 0);
        goto label_2229_internal;
    case 32:
        txtnew();
        txt(lang(
            u8"まずは素体となる仲間を選ぶ必要がある。"s,
            u8"Choose an original body."s));
        rc = 0;
        allyctrl = 5;
        {
            int stat = ctrl_ally();
            if (stat == -1)
            {
                return turn_result_t::turn_end;
            }
            rc = stat;
        }
        txtnew();
        txt(lang(
            u8"遺伝子を取り出す仲間を選ぶ必要がある。この仲間は合成後、永久に失われる。"s,
            u8"Choose a gene. Once you extract a gene, the subject will be lost forever."s));
        allyctrl = 5;
        {
            int stat = ctrl_ally();
            if (stat == -1)
            {
                return turn_result_t::turn_end;
            }
            tc = stat;
        }
        update_screen();
        txtnew();
        txt(lang(
            u8"本当に"s + cdatan(0, rc) + u8"に"s + cdatan(0, tc)
                + u8"の遺伝子を組み込む？"s,
            u8"Really add "s + cdatan(0, tc) + u8"'s gene to "s + cdatan(0, rc)
                + u8"?"s));
        ELONA_YES_NO_PROMPT();
        rtval = show_prompt(promptx, prompty, 160);
        if (rtval != 0)
        {
            return turn_result_t::turn_end;
        }
        txtnew();
        txtef(5);
        txt(lang(
            ""s + cdatan(0, rc) + u8"は"s + cdatan(0, tc)
                + u8"の遺伝子を受けついだ！"s,
            ""s + cdatan(0, rc) + u8" has inherited "s + cdatan(0, tc)
                + u8"'s gene!"s));
        anic = rc;
        play_animation(20);
        {
            int stat = transplant_body_parts();
            if (stat != -1)
            {
                cdata_body_part(rc, stat) = rtval * 10000;
                txtef(2);
                txt(lang(
                    cdatan(0, rc) + u8"は新しい"s
                        + i18n::_(u8"ui", u8"body_part", u8"_"s + rtval)
                        + u8"を得た！"s,
                    cdatan(0, rc) + u8" gains new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_"s + rtval)
                        + u8"!"s));
                refresh_speed_correction_value(rc);
            }
        }
        {
            int stat = gain_skills_by_geen_engineering();
            if (stat != 0)
            {
                for (int cnt = 0; cnt < 2; ++cnt)
                {
                    if (rtval(cnt) == -1)
                    {
                        break;
                    }
                    skillgain(rc, rtval(cnt), 1);
                    txtef(2);
                    txt(lang(
                        cdatan(0, rc) + u8"は"s
                            + i18n::_(
                                  u8"ability",
                                  std::to_string(rtval(cnt)),
                                  u8"name")
                            + u8"の技術を覚えた！"s,
                        cdatan(0, rc) + u8" learns "s
                            + i18n::_(
                                  u8"ability",
                                  std::to_string(rtval(cnt)),
                                  u8"name")
                            + u8" skill!"s));
                }
            }
        }
        if (cdata[tc].level > cdata[rc].level)
        {
            lv = (cdata[tc].level - cdata[rc].level) / 2 + 1;
            for (int cnt = 0, cnt_end = (lv); cnt < cnt_end; ++cnt)
            {
                r2 = 1;
                gain_level(rc);
            }
            txtef(2);
            txt(lang(
                cdatan(0, rc) + u8"はレベル"s + cdata[rc].level
                    + u8"になった！"s,
                cdatan(0, rc) + u8" is now level "s + cdata[rc].level
                    + u8"!"s));
            listmax = 0;
            for (int cnt = 10; cnt < 18; ++cnt)
            {
                list(0, listmax) = cnt;
                list(1, listmax) = sdata.get(cnt, tc).original_level;
                ++listmax;
            }
            sort_list_by_column1();
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                p = listmax - cnt - 1;
                i = list(0, p);
                if (list(1, p) > sdata.get(i, rc).original_level)
                {
                    p = (list(1, p) - sdata.get(i, rc).original_level) * 500;
                    p = clamp(p * 10 / clamp(lv, 2, 10), 1000, 10000);
                    skillmod(i, rc, p);
                }
            }
        }
        chara_vanquish(tc);
        autosave = 1 * (gdata_current_map != 35);
        skillexp(151, 0, 1200);
        randomize();
        screenupdate = -1;
        update_screen();
        cc = rc;
        csctrl = 4;
        snd(26);
        menu_character_sheet();
        cc = 0;
        goto label_2229_internal;
    case 35:
        txt(lang(
            u8"あなたはアイアンメイデンの中に入った。"s,
            u8"You enter the iron maiden."s));
        txtef(9);
        txt(lang(u8"「わくわく♪」"s, u8"\"Interesting!\""s));
        txt(lang(
            u8"突然誰かが蓋を閉めた。"s,
            u8"Suddenly, someone closes the door."s));
        txtef(9);
        txt(lang(u8"「ニヤリ」"s, u8"*Grin*"s));
        dmghp(0, 9999, -18);
        goto label_2229_internal;
    case 36:
        txt(lang(
            u8"あなたはギロチンに首をつっこんでみた。"s,
            u8"You set your head on the guillotine."s));
        txtef(9);
        txt(lang(u8"「わくわく♪」"s, u8"\"Interesting!\""s));
        txt(lang(
            u8"突然誰かがギロチンの刃を落とした。"s,
            u8"Suddenly, someone activates the guillotine."s));
        txtef(9);
        txt(lang(u8"「ニヤリ」"s, u8"*Grin*"s));
        dmghp(0, 9999, -19);
        goto label_2229_internal;
    case 39:
        txtef(9);
        txt(lang(u8" *ピーーーー* "s, u8"*Peeeeeeeeeep* "s));
        make_sound(cdata[cc].position.x, cdata[cc].position.y, 10, 1, 1, cc);
        goto label_2229_internal;
    case 37: show_card_collection(); goto label_2229_internal;
    }
label_2229_internal:
    refresh_burden_state();
    return turn_result_t::turn_end;
}

turn_result_t do_open_command()
{
    int refweight = 0;
    if (inv[ci].id == 361)
    {
        modify_karma(0, -10);
        invctrl(0) = 22;
        invctrl(1) = 0;
        invfile = inv[ci].param1;
        snd(23);
        shop_sell_item();
        screenupdate = -1;
        update_screen();
        return turn_result_t::turn_end;
    }
    if (inv[ci].id == 560)
    {
        invctrl(0) = 24;
        invctrl(1) = 0;
        snd(100);
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    if (inv[ci].id == 616)
    {
        invctrl(0) = 24;
        invctrl(1) = 2;
        snd(100);
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    if (inv[ci].id == 701)
    {
        invctrl(0) = 24;
        invctrl(1) = 8;
        snd(100);
        ctrl_inventory();
        return turn_result_t::turn_end;
    }
    if (inv[ci].id == 600)
    {
        snd(22);
        txt(lang(u8"足枷を外した。"s, u8"You unlock the shackle."s));
        if (gdata_current_map == 33)
        {
            if (gdata_current_dungeon_level == 1)
            {
                if (gdata_released_fire_giant == 0)
                {
                    if (cdata[gdata_fire_giant].state == 1)
                    {
                        tc = chara_find(203);
                        if (tc != 0)
                        {
                            txtef(9);
                            txt(lang(
                                u8"モイアー「馬鹿やろう！！」"s,
                                u8"Moyer yells, "s + u8"\"You idiot!\""s));
                            cdata[gdata_fire_giant].enemy_id = tc;
                            cdata[gdata_fire_giant].hate = 1000;
                        }
                        gdata_released_fire_giant = 1;
                    }
                }
            }
        }
        return turn_result_t::turn_end;
    }
    if (inv[ci].count != 0)
    {
        invfile = inv[ci].count;
        invcontainer(1) = ci;
        if (inv[ci].id == 641)
        {
            refweight = -1;
        }
        else
        {
            refweight = 0;
        }
        if (inv[ci].count == 3 || inv[ci].count == 4 || inv[ci].count == 6)
        {
            if (gdata_current_map != 7)
            {
                txt(lang(
                    u8"それは家の中でのみ使用できる。"s,
                    u8"You can only use it at your home."s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
        }
        if (inv[ci].count == 5)
        {
            if (adata(16, gdata_current_map) != 102)
            {
                txt(lang(
                    u8"それは店の中でのみ使用できる。"s,
                    u8"You can only use it at your shop"s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
        }
        ctrl_file(file_operation2_t::_4, u8"shoptmp.s2");
        if (fs::exists(
                filesystem::dir::tmp() / (u8"shop"s + invfile + u8".s2")))
        {
            ctrl_file(file_operation2_t::_3, u8"shop"s + invfile + u8".s2");
        }
        else
        {
            for (const auto& cnt : items(-1))
            {
                inv[cnt].number = 0;
            }
        }
        shoptrade = 0;
        invsubroutine = 1;
        invctrl(0) = 22;
        invctrl(1) = 2;
        if (invfile == 3)
        {
            txt(lang(
                u8"残り"s + gdata_rights_to_succeed_to
                    + u8"個分のアイテムの相続権を持っている。"s,
                u8"You can claim "s + gdata_rights_to_succeed_to
                    + u8" more heirloom"s + _s2(gdata_rights_to_succeed_to)
                    + u8"."s));
            invctrl(1) = 1;
        }
        if (invfile == 6 || inv[invcontainer(1)].id == 641)
        {
            if (invfile == 6)
            {
                invcontainer = 15;
            }
            else
            {
                invcontainer = 4;
            }
            menucycle = 1;
            invctrl(1) = 3;
        }
        mode = 6;
        snd(100);
        ctrl_inventory();
        invcontainer = 0;
        if (refweight == -1)
        {
            refweight = inv_weight(-1) + 2500;
        }
        ctrl_file(file_operation2_t::_4, u8"shop"s + invfile + u8".s2");
        ctrl_file(file_operation2_t::_3, u8"shoptmp.s2");
        if (refweight != 0)
        {
            inv[invcontainer(1)].weight = refweight;
            refresh_burden_state();
        }
        update_screen();
        mode = 0;
        return turn_result_t::turn_end;
    }
    item_separate(ci);
    if (inv[ci].param1 != 0)
    {
        if (inv[ci].param2 != 0)
        {
            int stat = unlock_box(inv[ci].param2);
            if (stat == 0)
            {
                screenupdate = -1;
                update_screen();
                return turn_result_t::turn_end;
            }
        }
    }
    if (inv[ci].param1 == 0)
    {
        txt(lang(u8"中身は空っぽだ。"s, u8"It's empty!"s));
    }
    else
    {
        if (inv[ci].id == 752)
        {
            open_new_year_gift();
        }
        else
        {
            open_box();
        }
        item_stack(cc, ri);
    }
    screenupdate = -1;
    update_screen();
    return turn_result_t::turn_end;
}

turn_result_t do_use_stairs_command(int val0)
{
    int movelevelbystairs = 0;
    if (dbg_freemove)
    {
        txt(lang(
            u8"デバッグ中はその操作はできない。"s,
            u8"You can't perform the action while in the debug mode."s));
        return turn_result_t::pc_turn_user_error;
    }
    int stat = item_find(631, 3, -1);
    if (stat != -1)
    {
        if (mdata(6) == 3 || mdata(6) == 2)
        {
            ci = stat;
            return step_into_gate();
        }
    }
    cell_featread(cdata[cc].position.x, cdata[cc].position.y);
    movelevelbystairs = 0;
    if (val0 == 1)
    {
        if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 753) != -1)
        {
            txt(lang(
                u8"本当にこたつの中に入る？"s,
                u8"Really get into the Kotatsu?"s));
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            if (rtval != 0)
            {
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
            txt(lang(u8"まっくらだ！"s, u8"It's dark here!"s));
            cdata[0].blind += 2;
            return turn_result_t::turn_end;
        }
    }
    if (gdata_current_map == 7)
    {
        if (val0 == 1)
        {
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 751)
                != -1)
            {
                if (gdata_current_dungeon_level >= adata(10, gdata_current_map))
                {
                    txt(lang(
                        u8"これ以上降りられない。"s,
                        u8"You can't go down any more."s));
                    return turn_result_t::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                }
            }
        }
        if (val0 == 2)
        {
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 750)
                != -1)
            {
                if (gdata_current_dungeon_level <= adata(17, gdata_current_map))
                {
                    txt(lang(
                        u8"これ以上昇れない。"s,
                        u8"You can't go up any more."s));
                    return turn_result_t::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                }
            }
        }
    }
    if (movelevelbystairs == 0)
    {
        if (mdata(6) != 1)
        {
            if (val0 == 1)
            {
                if (feat(1) != 11)
                {
                    txt(lang(
                        u8"降りる階段は見つからない。"s,
                        u8"There're no downstairs here."s));
                    update_screen();
                    return turn_result_t::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                    if (gdata_current_map == 42
                        && gdata_current_dungeon_level >= gdata(186))
                    {
                        txt(lang(
                            u8"階段は不思議なバリアで塞がれている。"s,
                            u8"The path is blocked by a strange barrier."s));
                        return turn_result_t::pc_turn_user_error;
                    }
                }
            }
            if (val0 == 2)
            {
                if (feat(1) != 10)
                {
                    txt(lang(
                        u8"昇る階段は見つからない。"s,
                        u8"There're no upstairs here."s));
                    update_screen();
                    return turn_result_t::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                }
            }
        }
    }
    if (feat == tile_downlocked)
    {
        f = 0;
        if (gdata_current_dungeon_level == 3)
        {
            if (gdata_main_quest_flag >= 65)
            {
                f = 1;
            }
        }
        if (gdata_current_dungeon_level == 17)
        {
            if (gdata_main_quest_flag >= 115)
            {
                f = 1;
            }
        }
        if (gdata_current_dungeon_level == 25)
        {
            if (gdata_main_quest_flag >= 125)
            {
                f = 1;
            }
        }
        if (gdata_current_dungeon_level == 44)
        {
            if (gdata_main_quest_flag >= 125)
            {
                f = 1;
            }
        }
        if (f == 1)
        {
            if (gdata_current_dungeon_level == 44)
            {
                txt(lang(
                    u8"厳重に封印された扉の前に立つと、三つの魔石が鈍い光を放った。"s,
                    u8"The magic stones shine softly as you approach the sealed door."s));
            }
            else
            {
                txt(lang(u8"扉の鍵を開けた。"s, u8"You unlock the door"s));
            }
            snd(23);
            cell_featset(
                cdata[cc].position.x,
                cdata[cc].position.y,
                tile_downstairs,
                11);
            return turn_result_t::turn_end;
        }
        snd(22);
        txt(lang(
            u8"鍵のかかった扉が行く手を塞いでいる。"s,
            u8"The door is locked. It seems you need a specific key to unlock the door."s));
        return turn_result_t::turn_end;
    }
    if (adata(16, gdata_current_map) == 8)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (adata(20, gdata_current_map) != -1)
            {
                txt(lang(
                    u8"クエストを放棄して階を移動する？"s,
                    u8"Really give up the quest and move over?"s));
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    update_screen();
                    return turn_result_t::pc_turn_user_error;
                }
            }
        }
    }
    if (movelevelbystairs == 1)
    {
        bool ok = actionsp(0, 15);
        if (!ok || cdata[0].inventory_weight_type >= 3)
        {
            if (!ok || rnd(5 - cdata[0].inventory_weight_type) == 0)
            {
                txt(lang(
                    u8"うわああ！"s + name(0) + u8"は階段から足を踏み外した。"s,
                    u8"Noooo! You lost your step and roll down!"s));
                dmghp(
                    cc,
                    cdata[cc].max_hp
                            * (cdata[0].inventory_weight * 10
                                   / cdata[0].max_inventory_weight
                               + 10)
                            / 100
                        + 1,
                    -7);
                msg_halt();
            }
            if (cdata[0].state == 0)
            {
                return turn_result_t::turn_begin;
            }
        }
    }
    if (feat(1) == 15)
    {
        if (feat(2) + feat(3) * 100 == 35)
        {
            comctrl = 0;
            int stat = label_19432();
            if (stat == 1)
            {
                return do_enter_strange_gate();
            }
            else
            {
                return turn_result_t::pc_turn_user_error;
            }
        }
    }
    snd(49);
    levelexitby = 4;
    return turn_result_t::exit_map;
}

turn_result_t do_movement_command()
{
    f = 0;
    if (cdata[cc].dimmed != 0)
    {
        if (cdata[cc].dimmed + 10 > rnd(60))
        {
            f = 1;
        }
    }
    if (cdata[cc].drunk != 0)
    {
        if (rnd(5) == 0)
        {
            txtef(9);
            txt(lang(u8" *ふらり* "s, u8"*stagger*"s));
            f = 1;
        }
    }
    if (cdata[cc].confused != 0 || f == 1)
    {
        cdata[cc].next_position.x = cdata[cc].position.x + rnd(3) - 1;
        cdata[cc].next_position.y = cdata[cc].position.y + rnd(3) - 1;
    }
    if (gdata_mount != 0)
    {
        if (cdata[gdata_mount].continuous_action_id != 0)
        {
            if (cdata[gdata_mount].continuous_action_turn > 0)
            {
                txt(lang(
                    name(gdata_mount) + u8"はあなたを睨み付けた。"s,
                    name(gdata_mount) + u8" stares in your face."s));
                cdata[gdata_mount].continuous_action_id = 0;
                cdata[gdata_mount].continuous_action_turn = 0;
            }
        }
    }
    cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
    if (cdata[0].inventory_weight_type >= 4)
    {
        ++msgdup;
        txt(lang(u8"潰れていて動けない！ "s, u8"You carry too much to move!"s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (cellchara != -1 && cellchara != 0)
    {
        tc = cellchara;
        if (cdata[tc].relationship >= 10
            || (cdata[tc].relationship == -1
                && config::instance().ignoredislike != 0)
            || (cdata[tc].relationship == 0
                && (adata(16, gdata_current_map) == 101
                    || adata(16, gdata_current_map) == 102 || key_shift)))
        {
            if (cdata[tc].is_hung_on_sand_bag() == 0)
            {
                if (mdata(6) == 1)
                {
                    goto label_2204_internal;
                }
                if (config::instance().scroll)
                {
                    cdata[0].next_position.x = cdata[tc].position.x;
                    cdata[0].next_position.y = cdata[tc].position.y;
                    label_1438();
                }
                cell_swap(cc, tc);
                txt(lang(
                    name(tc) + u8"と入れ替わった。"s,
                    u8"You displace "s + name(tc) + u8"."s));
                if (cdata[tc].id == 271)
                {
                    if (rnd(5) == 0)
                    {
                        if (cdata[tc].sleep == 0)
                        {
                            p = rnd(clamp(cdata[cc].gold, 0, 20) + 1);
                            if (cdata[cc].is_protected_from_thieves())
                            {
                                p = 0;
                            }
                            if (p != 0)
                            {
                                snd(11);
                                cdata[cc].gold -= p;
                                cdata[tc].gold += p;
                                txt(lang(
                                        u8"「おっと、ごめんよ」"s,
                                        u8"\"Ops, sorry.\""s),
                                    lang(
                                        u8"「気をつけな」"s,
                                        u8"\"Watch it.\""s));
                            }
                        }
                    }
                }
                if (cdata[tc].continuous_action_id == 1)
                {
                    if (cdata[tc].continuous_action_turn > 0)
                    {
                        txt(lang(
                            name(tc) + u8"はあなたを睨み付けた。"s,
                            name(tc) + u8" stares in your face."s));
                        cdata[tc].continuous_action_id = 0;
                        cdata[tc].continuous_action_turn = 0;
                    }
                }
                label_2206();
                return turn_result_t::turn_end;
            }
        }
        if (running)
        {
            if (cdata[tc].relationship >= -2 || keybd_wait >= 40)
            {
                return turn_result_t::pc_turn_user_error;
            }
        }
        if (cdata[tc].relationship <= -1)
        {
            cdata[0].enemy_id = tc;
            if (cdata[tc].is_invisible() == 1)
            {
                if (cdata[0].can_see_invisible() == 0)
                {
                    if (cdata[tc].wet == 0)
                    {
                        cdata[0].enemy_id = 0;
                    }
                }
            }
            if (keybd_attacking == 0)
            {
                keybd_wait = 1;
                keybd_attacking = 1;
            }
            try_to_melee_attack();
            return turn_result_t::turn_end;
        }
        talk_to_npc();
        if (chatteleport == 1)
        {
            chatteleport = 0;
            return turn_result_t::exit_map;
        }
        return turn_result_t::turn_end;
    }
    else
    {
        keybd_attacking = 0;
    }
    if (mdata(6) == 1)
    {
        if (dbg_freemove)
        {
            x = cdata[0].next_position.x;
            y = cdata[0].next_position.y;
            if (x >= 0 && x < mdata(0) && y >= 0 && y < mdata(1))
            {
                if (map(x, y, 1) == 0)
                {
                    cellaccess = 1;
                }
            }
        }
    }
    if (cellaccess == 1)
    {
    label_2204_internal:
        if (mdata(6) == 1)
        {
            if (264 <= map(cdata[cc].next_position.x,
                           cdata[cc].next_position.y,
                           0)
                && map(cdata[cc].next_position.x, cdata[cc].next_position.y, 0)
                    < 363)
            {
                return turn_result_t::pc_turn_user_error;
            }
        }
        return proc_movement_event();
    }
    if (mdata(6) == 6
        || (gdata_current_dungeon_level == 1 && mdata(6) != 1
            && (mdata(6) < 20 || 23 < mdata(6))))
    {
        if (cdata[cc].next_position.x < 0
            || cdata[cc].next_position.x > mdata(0) - 1
            || cdata[cc].next_position.y < 0
            || cdata[cc].next_position.y > mdata(1) - 1)
        {
            txt(lang(
                mdatan(0) + u8"を去る？ "s,
                u8"Do you want to leave "s + mdatan(0) + u8"? "s));
            if (mdata(6) == 7)
            {
                if (gdata(73) != 3)
                {
                    txt(lang(
                        u8"注意！現在のクエストは失敗に終わってしまう。"s,
                        u8"Warning! You are going to abandon your current quest."s));
                }
            }
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            update_screen();
            if (rtval == 0)
            {
                gdata(60) = cdata[0].position.x;
                gdata(61) = cdata[0].position.y;
                snd(49);
                --gdata_current_dungeon_level;
                levelexitby = 4;
                return turn_result_t::exit_map;
            }
            return turn_result_t::pc_turn_user_error;
        }
    }
    if (cellfeat != -1)
    {
        if (cellfeat == 21)
        {
            return proc_movement_event();
        }
        keyhalt = 1;
        if (cellfeat == 23)
        {
            snd(99);
            return turn_result_t::show_quest_board;
        }
        if (cellfeat == 31)
        {
            snd(99);
            voting_box();
            return turn_result_t::turn_end;
        }
        if (cellfeat == 33)
        {
            menucycle = 1;
            show_city_chart();
            return turn_result_t::pc_turn_user_error;
        }
    }
    if (cdata[0].confused != 0)
    {
        ++msgdup;
        txt(lang(u8" *ごつん* "s, u8"*bump*"s));
        update_screen();
    }
    return turn_result_t::pc_turn_user_error;
}

turn_result_t do_read_command()
{
    if (inv[ci].id == 783)
    {
        if (inv[ci].subname == 0)
        {
            txt(lang(
                u8"最後に調合したアイテムを、レシピに加えることができる。(まだ未実装)"s,
                u8"You can add a recipe of the item you previously created.(Not implemented yet)"s));
            return turn_result_t::turn_end;
        }
    }
    efid = 0;
    dbid = inv[ci].id;
    access_item_db(13);
    if (efid == 1115)
    {
        return build_new_building();
    }
    return turn_result_t::turn_end;
}

turn_result_t do_eat_command()
{
    if (cc == 0)
    {
        int stat = cargocheck();
        if (stat == 0)
        {
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        if (itemusingfind(ci) > 0)
        {
            txt(lang(
                u8"そのアイテムは他の誰かが使用中だ。"s,
                u8"Someone else is using the item."s));
            return turn_result_t::pc_turn_user_error;
        }
    }
    else if (itemusingfind(ci) != -1)
    {
        tc = itemusingfind(ci);
        if (tc != cc)
        {
            rowactend(tc);
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"は"s + name(tc) + u8"の食べ物を横取りした。"s,
                    name(cc) + u8" snatch"s + _s(cc) + u8" "s + name(tc)
                        + your(tc) + u8" food."s));
            }
        }
    }
    cdata[cc].emotion_icon = 116;
    continuous_action_eating();
    return turn_result_t::turn_end;
}

turn_result_t do_drink_command()
{
    dbid = inv[ci].id;
    access_item_db(15);
    return turn_result_t::turn_end;
}

turn_result_t do_zap_command()
{
    dbid = inv[ci].id;
    access_item_db(14);
    int stat = label_2172();
    if (stat == 0)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    return turn_result_t::turn_end;
}

turn_result_t do_rest_command()
{
    do_rest();
    return turn_result_t::turn_end;
}

turn_result_t do_fire_command()
{
    cc = 0;
    int stat = label_2072();
    if (stat == 0)
    {
        return turn_result_t::pc_turn_user_error;
    }
    tc = cdata[0].enemy_id;
    if (cdata[tc].relationship >= 0)
    {
        int stat = label_2073();
        if (stat == 0)
        {
            return turn_result_t::pc_turn_user_error;
        }
    }
    {
        int stat = can_do_ranged_attack();
        if (stat == -1)
        {
            ++msgdup;
            txt(lang(
                u8"射撃用の道具を装備していない。"s,
                u8"You need to equip a firing weapon."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        if (stat == -2)
        {
            ++msgdup;
            txt(lang(
                u8"矢/弾丸を装備する必要がある。"s,
                u8"You need to equip ammos or arrows."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        if (stat == -3)
        {
            ++msgdup;
            txt(lang(
                u8"矢/弾丸の種類が適していない。"s,
                u8"You're equipped with wrong type of ammos."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
    }
    do_ranged_attack();
    return turn_result_t::turn_end;
}

turn_result_t do_get_command()
{
    const auto item_info = cell_itemoncell(cdata[0].position);
    const auto number = item_info.first;
    const auto item = item_info.second;

    if (map(cdata[0].position.x, cdata[0].position.y, 6) != 0
        && gdata_current_map != 35 && number == 0)
    {
        cell_featread(cdata[0].position.x, cdata[0].position.y);
        if (feat(1) == 29)
        {
            if (feat < tile_plant + 2)
            {
                txt(lang(u8"芽を摘み取った。"s, u8"You nip a young plant."s));
                map(cdata[0].position.x, cdata[0].position.y, 6) = 0;
                return turn_result_t::turn_end;
            }
            if (feat == tile_plant + 3)
            {
                txt(lang(
                    u8"枯れた草を摘み取った。"s, u8"You nip a dead plant."s));
                map(cdata[0].position.x, cdata[0].position.y, 6) = 0;
                return turn_result_t::turn_end;
            }
            if (!inv_getspace(0))
            {
                txt(lang(
                    u8"バックパックが一杯だ。"s, u8"Your inventory is full."s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
            label_2236();
            harvest_plant(
                chipm(0, map(cdata[0].position.x, cdata[0].position.y, 0)) == 2
                    ? 1
                    : 0);
            if (feat(2) == 40)
            {
                autosave = 1 * (gdata_current_map != 35);
            }
            refresh_burden_state();
            return turn_result_t::turn_end;
        }
        if (mdata(6) == 1 && feat(1) == 15 && feat(2) + feat(3) * 100 >= 300
            && feat(2) + feat(3) * 100 < 450)
        {
            txt(lang(
                u8"本当にこの建物を撤去する？（注意！建物と中の物は完全に失われます）"s,
                u8"Really remove this building?"s));
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            if (rtval != 0)
            {
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
            area = feat(2) + feat(3) * 100;
            map(cdata[0].position.x, cdata[0].position.y, 6) = 0;
            adata(16, area) = 0;
            removeworker(area);
            label_1749();
            ctrl_file(file_operation_t::_13);
            snd(58);
            txt(lang(u8"建物を撤去した。"s, u8"You remove the building."s));
            return turn_result_t::turn_end;
        }
    }

    if (number == 0)
    {
        if ((mdata(6) == 3 || mdata(6) == 2)
            && chipm(0, map(cdata[0].position.x, cdata[0].position.y, 0)) == 4)
        {
            snd(83);
            txt(lang(
                u8"雪をかきあつめた。"s, u8"You rake up a handful of snow."s));
            if (!actionsp(0, 10))
            {
                txt(lang(
                    u8"疲労し過ぎて失敗した！"s, u8"You are too exhausted!"s));
                return turn_result_t::turn_end;
            }
            flt();
            {
                int stat = itemcreate(0, 587, -1, -1, 0);
                if (stat != 0)
                {
                    inv[ci].curse_state = curse_state_t::none;
                    inv[ci].identification_state =
                        identification_state_t::completely_identified;
                    item_stack(0, ci, 1);
                }
            }
            return turn_result_t::turn_end;
        }
        ++msgdup;
        txt(lang(u8"あなたは空気をつかんだ。"s, u8"You grasp at the air."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }

    ci = item;
    if (number > 1)
    {
        invctrl = 3;
        snd(100);
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    if ((inv[ci].own_state > 0 && inv[ci].own_state < 3)
        || inv[ci].own_state == 5)
    {
        snd(27);
        ++msgdup;
        if (inv[ci].own_state == 2)
        {
            txt(lang(u8"それは持ち運べない。"s, u8"You can't carry it."s));
        }
        if (inv[ci].own_state == 1 || inv[ci].own_state == 5)
        {
            txt(lang(
                    u8"それはあなたの物ではない。"s,
                    u8"It's not your property."s),
                lang(
                    u8"盗むなんてとんでもない。"s,
                    u8"You can't just take it."s),
                lang(u8"それは拾えない。"s, u8"It's not yours."s));
        }
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    in = inv[ci].number;

    int stat = pick_up_item();
    if (stat == 1 || stat == -1)
    {
        return turn_result_t::turn_end;
    }
    else
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
}

turn_result_t do_cast_command()
{
    tc = cc;
    int stat = label_2167();
    if (stat == 0)
    {
        return turn_result_t::pc_turn_user_error;
    }
    return turn_result_t::turn_end;
}

turn_result_t do_short_cut_command()
{
    menucycle = 0;
    if (gdata(40 + sc) == 0)
    {
        ++msgdup;
        txt(lang(
            u8"そのキーにはショートカットが割り当てられていない。"s,
            u8"The key is unassigned."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (gdata(40 + sc) >= 10000)
    {
        invsc = gdata((40 + sc)) % 10000;
        invctrl(0) = gdata((40 + sc)) / 10000;
        invctrl(1) = 0;
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    efid = gdata(40 + sc);
    if (efid >= 300 && efid < 400)
    {
        return do_use_magic();
    }
    if (efid >= 600)
    {
        if (mdata(6) == 1)
        {
            txtnew();
            txt(lang(
                u8"その行為は、ワールドマップにいる間はできない。"s,
                u8"You can't do that while you're in a global area."s));
            display_msg();
            redraw();
            return turn_result_t::pc_turn_user_error;
        }
        if (efid < 661)
        {
            if (spact(efid - 600) == 0)
            {
                txt(lang(
                    u8"もうその行動はできない。"s,
                    u8"You can't use this shortcut any more."s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
        }
        return do_use_magic();
    }
    if (efid >= 400)
    {
        if (mdata(6) == 1)
        {
            txtnew();
            txt(lang(
                u8"その行為は、ワールドマップにいる間はできない。"s,
                u8"You can't do that while you're in a global area."s));
            display_msg();
            redraw();
            return turn_result_t::pc_turn_user_error;
        }
        if (spell(efid - 400) <= 0)
        {
            ++msgdup;
            txt(lang(
                u8"その魔法はもう使えない。"s,
                u8"You can't use that spell anymore."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        return do_cast_command();
    }
    return turn_result_t::pc_turn_user_error;
}

turn_result_t do_exit_command()
{
    txtnew();
    if (gdata_current_map == 35)
    {
        txtef(3);
        txt(lang(
            u8"ユーザーマップの中ではセーブできない。それでも終了する？"s,
            u8"You can't save the game in a user made map. Exit anyway?"s));
    }
    else
    {
        txt(lang(
            u8"これまでの冒険を記録して終了する？"s,
            u8"Do you want to save the game and exit?"s));
    }
    ELONA_APPEND_PROMPT(lang(u8"はい"s, u8"Exit"s), u8"a"s, ""s + promptmax);
    ELONA_APPEND_PROMPT(
        lang(u8"いいえ"s, u8"Cancel"s), u8"b"s, ""s + promptmax);
    ELONA_APPEND_PROMPT(
        lang(u8"ゲーム設定"s, u8"Game Setting"s), u8"c"s, ""s + promptmax);
    rtval = show_prompt(promptx, prompty, 190);
    if (rtval == 0)
    {
        if (gdata_current_map != 35)
        {
            snd(44);
            save_game();
            txt(lang(
                u8"無事に記録された。"s,
                u8"Your game has been saved successfully."s));
            txt(lang(
                name(cc)
                    + u8"は静かに目を閉じた… (キーを押すと自動終了します)"s,
                u8"You close your eyes and peacefully fade away. (Hit any key to exit)"s));
            msg_halt();
            update_screen();
        }
        await(300);
        return turn_result_t::finish_elona;
    }
    if (rtval == 2)
    {
        snd(20);
        set_option();
    }
    update_screen();
    return turn_result_t::pc_turn_user_error;
}

int ask_direction_to_close()
{
    int number_of_doors{};
    position_t pos;
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dy == 0 && dx == 0)
                continue;

            int x = cdata[0].position.x + dx;
            int y = cdata[0].position.y + dy;
            cell_featread(x, y);
            if (feat(1) == 20 && map(x, y, 1) == 0)
            {
                ++number_of_doors;
                pos = {x, y};
            }
        }
    }
    if (number_of_doors == 1)
    {
        x = pos.x;
        y = pos.y;
        return 1;
    }

    txt(lang(u8"何を閉める？"s, u8"Which door do you want to close? "s));
    update_screen();
    return ask_direction();
}

} // namespace elona
