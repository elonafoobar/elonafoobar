#include "blending.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

elona_vector2<int> rpdata;
elona_vector2<std::string> rfnameorg;
elona_vector1<std::string> rpdatan;
elona_vector1<int> rpref;
int rpid = 0;
int rpmode = 0;
elona_vector1<int> rppage;
int rpresult = 0;
elona_vector1<int> inhlist_at_m184;

void continuous_action_blending()
{
label_19341_internal:
    rpid = rpref(0);
    if (rpid == 0)
    {
        rowactend(cc);
        return;
    }
    if (cdata[cc].continuous_action_id == 0)
    {
        txtnew();
        txt(i18n::s.get("core.locale.blending.started", cdata[cc], rpname(rpid)));
        cdata[cc].continuous_action_id = 12;
        cdata[cc].continuous_action_turn = rpref(2) % 10000;
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (rnd(30) == 0)
        {
            txtef(4);
            txt(i18n::s.get_enum("core.locale.blending.sounds", rnd(2)));
        }
        return;
    }
    if (rpref(2) >= 10000)
    {
        cdata[cc].continuous_action_turn = rpref(2) / 10000;
        for (int cnt = 0;; ++cnt)
        {
            mode = 12;
            ++gdata_hour;
            weather_changes();
            render_hud();
            if (cnt % 5 == 0)
            {
                txtef(4);
                txt(i18n::s.get_enum("core.locale.blending.sounds", rnd(2)));
            }
            redraw();
            await(config::instance().animewait * 5);
            gdata_minute = 0;
            cc = 0;
            --cdata[cc].continuous_action_turn;
            if (cdata[cc].continuous_action_turn <= 0)
            {
                int stat = label_1931();
                if (stat == 0)
                {
                    txt(i18n::s.get("core.locale.blending.required_material_not_found"));
                    break;
                }
                label_1933();
                if (rpref(1) > 0)
                {
                    cdata[cc].continuous_action_turn = rpref(2) / 10000;
                    cnt = 0 - 1;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        rowactend(cc);
        mode = 0;
        return;
    }
    int stat = label_1931();
    if (stat == 0)
    {
        txt(i18n::s.get("core.locale.blending.required_material_not_found"));
        rowactend(cc);
        return;
    }
    label_1933();
    if (rpref(1) > 0)
    {
        cdata[cc].continuous_action_id = 0;
        goto label_19341_internal;
    }
    rowactend(cc);
    return;
}

void initialize_recipememory()
{
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        recipememory(200 + cnt) = 1;
    }
    return;
}

void initialize_recipe()
{
    DIM3(rpdata, 100, 1200);
    SDIM4(rfnameorg, 20, 2, 6);
    SDIM3(rpdatan, 40, 1200);
    DIM2(rpref, 100);
    rpsourcelist(0) = 0;
    rpsourcelist(1) = 898;
    rpsourcelist(2) = 1156;
    rpsourcelist(3) = 1187;
    rpsourcelist(4) = 209;
    rpsourcelist(5) = 210;
    rpid = 200;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10000;
    rpdata(1, rpid) = 10;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 8;
    rpdata(12, rpid) = 178;
    rpdata(13, rpid) = 3;
    rpdata(20, rpid) = 57000;
    rpdata(21, rpid) = 620;
    rpid = 201;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10001;
    rpdata(1, rpid) = 4;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 6;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 519;
    rpid = 202;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10002;
    rpdata(1, rpid) = 7;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 3;
    rpdata(20, rpid) = 57000;
    rpdata(21, rpid) = 262;
    rpid = 203;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10003;
    rpdata(1, rpid) = 15;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 18;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 736;
    rpid = 204;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10004;
    rpdata(1, rpid) = 15;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 10;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 566;
    rpid = 205;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10005;
    rpdata(1, rpid) = 10;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 185;
    rpdata(11, rpid) = 2;
    rpdata(12, rpid) = 12;
    rpdata(13, rpid) = 10;
    rpdata(20, rpid) = 342;
    rpdata(21, rpid) = 617;
    rpid = 206;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10006;
    rpdata(1, rpid) = 5;
    rpdata(2, rpid) = 1;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 5;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 516;
    rpid = 207;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10007;
    rpdata(1, rpid) = 3;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 3;
    rpdata(20, rpid) = 60001;
    rpdata(21, rpid) = 52000;
    rpid = 208;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10008;
    rpdata(1, rpid) = 16;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 12;
    rpdata(11, rpid) = 24;
    rpdata(20, rpid) = 60001;
    rpdata(21, rpid) = 601;
    rpid = 209;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10009;
    rpdata(1, rpid) = 16;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 178;
    rpdata(11, rpid) = 999;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 9004;
    rpid = 210;
    rpdatan(rpid) = i18n::s.get_enum("core.locale.blending.recipe", rpid);
    rpdata(0, rpid) = 10009;
    rpdata(1, rpid) = 16;
    rpdata(2, rpid) = 2;
    rpdata(10, rpid) = 178;
    rpdata(11, rpid) = 999;
    rpdata(20, rpid) = 9004;
    rpdata(21, rpid) = 9004;
    rpdata(22, rpid) = 9004;
    rpid = 898;
    rpdata(0, rpid) = 498;
    rpdata(1, rpid) = 150060;
    rpdata(10, rpid) = 175;
    rpdata(11, rpid) = 4;
    rpdata(12, rpid) = 457;
    rpdata(13, rpid) = 20;
    rpdata(14, rpid) = 12;
    rpdata(15, rpid) = 8;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 260;
    rpdata(21, rpid) = 9001;
    rpid = 1156;
    rpdata(0, rpid) = 756;
    rpdata(1, rpid) = 20020;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 4;
    rpdata(12, rpid) = 179;
    rpdata(13, rpid) = 20;
    rpdata(14, rpid) = 157;
    rpdata(15, rpid) = 8;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 260;
    ++rpid;
    rpid = 1187;
    rpdata(0, rpid) = 787;
    rpdata(1, rpid) = 30;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 10;
    rpdata(12, rpid) = 178;
    rpdata(13, rpid) = 5;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 9004;
    rpid = 1191;
    rpdata(0, rpid) = 791;
    rpdata(1, rpid) = 160045;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 10;
    rpdata(12, rpid) = 178;
    rpdata(13, rpid) = 65;
    rpdata(14, rpid) = 10;
    rpdata(15, rpid) = 105;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 10000;
    rpdata(21, rpid) = 748;
    rpdata(22, rpid) = 716;
    rpid = 1192;
    rpdata(0, rpid) = 792;
    rpdata(1, rpid) = 10024;
    rpdata(10, rpid) = 184;
    rpdata(11, rpid) = 20;
    rpdata(12, rpid) = 0;
    rpdata(13, rpid) = 10;
    rpdata(14, rpid) = 151;
    rpdata(15, rpid) = 5;
    rpdata(30, rpid) = 0;
    rpdata(20, rpid) = 204;
    rpdata(21, rpid) = 9005;
    rpdata(40, rpid) = 10003;
    rpdata(50, rpid) = 10017;
    rpdata(51, rpid) = 500;
    rpdata(52, rpid) = 60017;
    rpdata(53, rpid) = 500;
    rpdata(54, rpid) = 10010;
    rpdata(55, rpid) = 100;
    rpdata(56, rpid) = 60010;
    rpdata(57, rpid) = 100;
    rpdata(58, rpid) = 10016;
    rpdata(59, rpid) = 300;
    rpdata(60, rpid) = 60016;
    rpdata(61, rpid) = 300;
    rpdata(62, rpid) = 10011;
    rpdata(63, rpid) = 200;
    rpdata(64, rpid) = 60011;
    rpdata(65, rpid) = 200;
    rfnameorg(0, 1) = u8"flavor"s;
    rfnameorg(1, 1) = i18n::s.get_enum("core.locale.blending.ingredient", 1);
    rfnameorg(0, 2) = u8"ore"s;
    rfnameorg(1, 2) = i18n::s.get_enum("core.locale.blending.ingredient", 2);
    rfnameorg(0, 3) = u8"wood"s;
    rfnameorg(1, 3) = i18n::s.get_enum("core.locale.blending.ingredient", 3);
    rfnameorg(0, 5) = u8"fish"s;
    rfnameorg(1, 5) = i18n::s.get_enum("core.locale.blending.ingredient", 4);
    rfnameorg(0, 4) = "";
    rfnameorg(1, 4) = i18n::s.get_enum("core.locale.blending.ingredient", 5);
    return;
}

void window_recipe2(int val0)
{
    int x_at_m183 = 0;
    int w_at_m183 = 0;
    int dx_at_m183 = 0;
    int dy_at_m183 = 0;
    std::string s_at_m183;
    int p_at_m183 = 0;
    x_at_m183 = wx + ww;
    w_at_m183 = 400;
    gmode(2);
    pos(x_at_m183 + w_at_m183 - 520, 0);
    gcopy(3, 960, 288, 480, 68);
    dx_at_m183 = x_at_m183 + w_at_m183 - 500;
    dy_at_m183 = 10;
    font(15 - en * 2, snail::font_t::style_t::bold);
    s_at_m183 = ""s + rpsuccessrate(rpdiff(rpid, step, -1));
    bmes(
        i18n::s.get("core.locale.blending.rate_panel.success_rate", s_at_m183),
        dx_at_m183 + 140,
        dy_at_m183,
        {235, 235, 235},
        {30, 30, 30});
    p_at_m183 = rpdata(1, rpid);
    if (rpmode)
    {
        if (p_at_m183 < 10000)
        {
            p_at_m183 = p_at_m183 * val0;
        }
        else
        {
            p_at_m183 = p_at_m183 % 10000;
        }
        p_at_m183 += rpdata(1, rpid) / 10000 * val0 * 10000;
    }
    s_at_m183 = i18n::s.get("core.locale.blending.rate_panel.turns", p_at_m183 % 10000);
    if (p_at_m183 >= 10000)
    {
        s_at_m183 += i18n::s.get("core.locale.blending.rate_panel.and_hours", p_at_m183 / 10000);
    }
    bmes(
        i18n::s.get("core.locale.blending.rate_panel.required_time", s_at_m183),
        dx_at_m183 + 140,
        dy_at_m183 + 20,
        {235, 235, 235},
        {40, 40, 40});
}



void window_recipe_(
    int prm_1050,
    int prm_1051,
    int prm_1052,
    int prm_1053,
    int prm_1054)
{
    elona_vector1<std::string> s_at_m184;
    int xfix2_at_m184 = 0;
    int dx_at_m184 = 0;
    int dy_at_m184 = 0;
    int i_at_m184 = 0;
    int p_at_m184 = 0;
    int cnt2_at_m184 = 0;
    SDIM1(s_at_m184);
    if (windowshadow == 1)
    {
        window(
            prm_1051 + 4,
            prm_1052 + 4,
            prm_1053,
            prm_1054 - prm_1054 % 8,
            true);
        boxf(prm_1051 + prm_1053 - 522, 0, 486, 69, {30, 30, 30});
        windowshadow = 0;
    }
    window(prm_1051, prm_1052, prm_1053, prm_1054 - prm_1054 % 8);
    window_recipe2();
    gmode(2);
    line(
        prm_1051 + 50 + 0,
        prm_1052 + prm_1054 - 48 - prm_1054 % 8,
        prm_1051 + prm_1053 - 40,
        prm_1052 + prm_1054 - 48 - prm_1054 % 8,
        {194, 170, 146});
    line(
        prm_1051 + 50 + 0,
        prm_1052 + prm_1054 - 49 - prm_1054 % 8,
        prm_1051 + prm_1053 - 40,
        prm_1052 + prm_1054 - 49 - prm_1054 % 8,
        {234, 220, 188});
    s_at_m184(0) = u8"Page."s + (rppage + 1) + u8"/"s + (rppage(1) + 1);
    s_at_m184(1) = ""s + key_prev + u8","s + key_next + ""s
        + i18n::s.get("core.locale.blending.recipe.hint");
    if (step == -1)
    {
        s_at_m184(1) += strhint3;
    }
    else
    {
        s_at_m184(1) += strhint3b;
    }
    font(12 + sizefix - en * 2);
    pos(prm_1051 + 25 + 0, prm_1052 + prm_1054 - 43 - prm_1054 % 8);
    mes(s_at_m184(1));
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(prm_1051 + prm_1053 - strlen_u(s_at_m184) * 7 - 40 - xfix2_at_m184,
        prm_1052 + prm_1054 - 65 - prm_1054 % 8);
    mes(s_at_m184);
    dx_at_m184 = prm_1051 + 35;
    dy_at_m184 = y + 48;
    font(12 - en * 2, snail::font_t::style_t::bold);
    pos(dx_at_m184 - 10, dy_at_m184);
    mes(i18n::s.get("core.locale.blending.window.procedure"));
    dy_at_m184 = dy_at_m184 + 18;
    font(13 - en * 2);
    i_at_m184 = 1;
    pos(dx_at_m184 - 10, dy_at_m184 - 2);
    if (step == i_at_m184 - 2)
    {
        boxf(
            dx_at_m184 - 10,
            dy_at_m184 - 2,
            prm_1053 - 60,
            17,
            {60, 20, 10, 32});
    }
    else if (step > i_at_m184 - 2)
    {
        boxf(
            dx_at_m184 - 10,
            dy_at_m184 - 2,
            prm_1053 - 60,
            17,
            {20, 20, 20, 32});
    }
    if (step == -1)
    {
        pos(dx_at_m184, dy_at_m184);
        mes(""s + i_at_m184 + u8"."s
            + i18n::s.get("core.locale.blending.window.choose_a_recipe"));
    }
    else
    {
        pos(dx_at_m184, dy_at_m184);
        mes(""s + i_at_m184 + u8"."s
            + i18n::s.get("core.locale.blending.window.chose_the_recipe_of", rpname(rpid)));
    }
    dy_at_m184 += 17;
    ++i_at_m184;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpdata(20 + cnt, rpid) == 0)
        {
            break;
        }
        pos(dx_at_m184 - 10, dy_at_m184 - 2);
        if (step == i_at_m184 - 2)
        {
            boxf(
                dx_at_m184 - 10,
                dy_at_m184 - 2,
                prm_1053 - 60,
                17,
                {60, 20, 10, 32});
        }
        else if (step > i_at_m184 - 2)
        {
            boxf(
                dx_at_m184 - 10,
                dy_at_m184 - 2,
                prm_1053 - 60,
                17,
                {20, 20, 20, 32});
        }
        if (step <= cnt)
        {
            int stat = blendmatnum(rpdata(20 + cnt, rpid), cnt);
            p_at_m184 = stat;
            s_at_m184 = i18n::s.get("core.locale.blending.window.add", rpmatname(cnt), p_at_m184);
        }
        else
        {
            s_at_m184 = i18n::s.get("core.locale.blending.window.selected", inv[rpref(10 + cnt * 2)]);
            s_at_m184 = strmid(s_at_m184, 0, 44);
        }
        pos(dx_at_m184, dy_at_m184);
        mes(""s + i_at_m184 + u8"."s + s_at_m184);
        dy_at_m184 += 17;
        ++i_at_m184;
    }
    pos(wx + ww + 243, wy - 4);
    gcopy(3, 1040, 96, 160, 70);
    pos(dx_at_m184 - 10, dy_at_m184 - 2);
    if (step == i_at_m184 - 2)
    {
        boxf(
            dx_at_m184 - 10,
            dy_at_m184 - 2,
            prm_1053 - 60,
            17,
            {60, 20, 10, 32});
    }
    else if (step > i_at_m184 - 2)
    {
        boxf(
            dx_at_m184 - 10,
            dy_at_m184 - 2,
            prm_1053 - 60,
            17,
            {20, 20, 20, 32});
    }
    pos(dx_at_m184, dy_at_m184);
    mes(""s + i_at_m184 + u8"."s
        + i18n::s.get("core.locale.blending.window.start"));
    dy_at_m184 += 30;
    if (rppage == 0)
    {
        font(12 - en * 2, snail::font_t::style_t::bold);
        pos(dx_at_m184 - 10, dy_at_m184);
        mes(i18n::s.get("core.locale.blending.window.the_recipe_of", rpname(rpid)));
        dy_at_m184 += 20;
        pos(dx_at_m184 - 10, dy_at_m184);
        mes(i18n::s.get("core.locale.blending.window.required_skills"));
        dy_at_m184 = dy_at_m184 + 18;
        font(13 - en * 2);
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (rpdata(10 + cnt * 2, rpid) == 0)
            {
                break;
            }
            if (rpdata(11 + cnt * 2, rpid)
                > sdata(rpdata(10 + cnt * 2, rpid), 0))
            {
                color(150, 0, 0);
            }
            else
            {
                color(0, 120, 0);
            }
            pos(dx_at_m184 + cnt % 2 * 140, dy_at_m184 + cnt / 2 * 17);
            mes(i18n::_(
                    u8"ability",
                    std::to_string(rpdata(10 + cnt * 2, rpid)),
                    u8"name")
                + u8"  "s + rpdata((11 + cnt * 2), rpid) + u8"("s
                + sdata(rpdata((10 + cnt * 2), rpid), 0) + u8")"s);
            color(0, 0, 0);
        }
        dy_at_m184 += 50;
        font(12 - en * 2, snail::font_t::style_t::bold);
        pos(dx_at_m184 - 10, dy_at_m184);
        mes(i18n::s.get("core.locale.blending.window.required_equipment"));
        return;
    }
    if (prm_1050 == -1)
    {
        return;
    }
    font(12 - en * 2, snail::font_t::style_t::bold);
    pos(dx_at_m184 - 10, dy_at_m184);
    mes(itemname(prm_1050));
    dy_at_m184 += 20;
    font(13 - en * 2);
    if (inv[prm_1050].identification_state
        <= identification_state_t::partly_identified)
    {
        pos(dx_at_m184, dy_at_m184);
        mes(i18n::s.get("core.locale.blending.window.havent_identified"));
        dy_at_m184 += 16;
        return;
    }
    getinheritance(prm_1050, inhlist_at_m184, p_at_m184);
    if (p_at_m184 > 0)
    {
        for (int cnt = 0, cnt_end = (p_at_m184); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m184 = inhlist_at_m184(cnt);
            if (inv[prm_1050].enchantments[cnt2_at_m184].id == 0)
            {
                break;
            }
            get_enchantment_description(
                inv[prm_1050].enchantments[cnt2_at_m184].id,
                inv[prm_1050].enchantments[cnt2_at_m184].power,
                the_item_db[inv[prm_1050].id]->category);
            color(0, 0, 100);
            if (inv[prm_1050].enchantments[cnt2_at_m184].power < 0)
            {
                color(180, 0, 0);
            }
            pos(dx_at_m184, dy_at_m184);
            mes(cnven(s));
            color(0, 0, 0);
            dy_at_m184 += 16;
        }
    }
    else
    {
        pos(dx_at_m184, dy_at_m184);
        mes(i18n::s.get("core.locale.blending.window.no_inheritance_effects"));
        dy_at_m184 += 16;
        ++p_at_m184;
    }
    return;
}

turn_result_t blending_menu()
{
    elona_vector1<int> blendchecklist;
    step = -1;
    rpid = 0;
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_blend.bmp", 1);
    gsel(0);
    clear_rprefmat();
label_1923:
    if (step != -1)
    {
        if (rpdata(20 + step, rpid) == 0)
        {
            rppage = 0;
            window_recipe(list2, -1, wx + ww, wy, 400, wh);
            txtnew();
            txt(i18n::s.get("core.locale.blending.prompt.how_many"));
            ELONA_APPEND_PROMPT(
                i18n::s.get("core.locale.blending.prompt.start"),
                u8"a"s,
                ""s + promptmax);
            ELONA_APPEND_PROMPT(
                i18n::s.get("core.locale.blending.prompt.go_back"),
                u8"b"s,
                ""s + promptmax);
            ELONA_APPEND_PROMPT(
                i18n::s.get("core.locale.blending.prompt.from_the_start"),
                u8"c"s,
                ""s + promptmax);
            p = 10;
            for (int cnt = 0; cnt < 10; ++cnt)
            {
                if (rpref(10 + cnt * 2) == -1)
                {
                    break;
                }
                if (rpdata(2, rpid) == 2 && cnt == 0)
                {
                    continue;
                }
                if (inv[rpref(10 + cnt * 2)].number < p)
                {
                    p = inv[rpref(10 + cnt * 2)].number;
                }
            }
            rpmode = 1;
            rtval = show_prompt(
                promptx, prompty, 220, show_prompt_type::with_number, p);
            rpmode = 0;
            if (rtval == 0)
            {
                rpref(1) = TODO_show_prompt_val;
                rpref(2) = rpdata(1, rpid);
                rpref(3) = rpdiff(rpid, step, -1);
                continuous_action_blending();
                return turn_result_t::turn_end;
            }
            if (rtval == 2)
            {
                step = -1;
                goto label_1923;
            }
            --step;
            goto label_1923;
        }
    }
    page = 0;
    pagesize = 16;
    listmax = 0;
    cs = 0;
    cs_bk = -1;
    cc = 0;
    screenupdate = -1;
    update_screen();
    if (step == -1)
    {
        rppage(0) = 0;
        rppage(1) = 0;
        listmax = 0;
        for (int cnt = 0; cnt < 1200; ++cnt)
        {
            if (rpdata(0, cnt) == 0)
            {
                continue;
            }
            if (recipememory(cnt) > 0)
            {
                list(0, listmax) = cnt;
                list(1, listmax) = cnt;
                ++listmax;
            }
        }
        sort_list_by_column1();
        windowshadow(1) = 1;
        txtnew();
        txt(i18n::s.get("core.locale.blending.recipe.warning"));
        txtnew();
        txt(i18n::s.get("core.locale.blending.recipe.which"));
        goto label_1924_internal;
    }
    rppage = 1;
    {
        int stat = blendlist(list, step);
        listmax = stat;
    }
    sort_list_by_column1();
    goto label_1927_internal;
label_1924_internal:
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
    DIM2(blendchecklist, pagesize);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        blendchecklist(cnt) = blendcheckmat(list(0, p));
    }
label_1925_internal:
    s(0) = i18n::s.get("core.locale.blending.recipe.title");
    s(1) = strhint2;
    windowshadow = windowshadow(1);
    display_window(
        (windoww - 780) / 2 + inf_screenx, winposy(445), 380, 432, 74);
    display_topic(i18n::s.get("core.locale.blending.recipe.name"), wx + 28, wy + 30);
    s = i18n::s.get("core.locale.blending.recipe.counter", listmax);
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(wx + 130, wy + wh - 65 - wh % 8);
    mes(s);
    keyrange = 0;
    gmode(2);
    prepare_item_image(550, 0);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 60 + cnt * 19, ww - 100, 18, {12, 14, 16, 16});
        }
        pos(wx + 37, wy + 70 + cnt * 19);
        gmode(2);
        gcopy_c(
            1,
            0,
            960,
            item_chips[550].width,
            item_chips[550].height,
            inf_tiles,
            inf_tiles);
        pos(wx + 330, wy + 53 + cnt * 19);
        if (blendchecklist(cnt) == 1)
        {
            gcopy(3, 336, 360, 24, 24);
        }
        rpid = list(0, p);
        pos(wx + 317, wy + 60 + cnt * 19);
        gcopy(3, 64 + (4 - rpdiff(rpid, -1, -1) / 25) * 16, 624, 16, 16);
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        p = list(0, p);
        rpid = p;
        s = i18n::s.get("core.locale.blending.recipe.of", cnven(rpname(rpid)));
        display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);
        cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1, 0, 0, p);
    }
    if (cs_bk != cs)
    {
        rpid = list(0, pagesize * page + cs);
        windowshadow = windowshadow(1);
        window_recipe(list2, -1, wx + ww, wy, 400, wh);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    windowshadow(1) = 0;
    pos(wx + 10, wy + wh - 100);
    gcopy(3, 960, 96, 80, 90);
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (p != -1)
    {
        rpid = p;
        step = 0;
        rppage(0) = 1;
        rppage(1) = 1;
        rpref(0) = rpid;
        goto label_1923;
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1924_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1924_internal;
        }
    }
    if (key == key_cancel)
    {
        screenupdate = 0;
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    goto label_1925_internal;
label_1927_internal:
    windowshadow(1) = 1;
    txtnew();
    txt(i18n::s.get("core.locale.blending.steps.add_ingredient", rpmatname(step)));
label_1928_internal:
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
    s(0) = i18n::s.get("core.locale.blending.steps.add_ingredient_prompt", rpmatname(step));
    s(1) = strhint2;
    windowshadow = windowshadow(1);
    display_window(
        (windoww - 780) / 2 + inf_screenx, winposy(445), 380, 432, 74);
    display_topic(i18n::s.get("core.locale.blending.steps.item_name"), wx + 28, wy + 30);
    s = i18n::s.get("core.locale.blending.steps.item_counter", listmax);
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(wx + 130, wy + wh - 65 - wh % 8);
    mes(s);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 60 + cnt * 19, ww - 100, 18, {12, 14, 16, 16});
        }
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        p = list(0, p);
        s = itemname(p, inv[p].number);
        s = strmid(s, 0, 28);
        if (p >= 5080)
        {
            s += i18n::s.get("core.locale.blending.steps.ground");
        }
        display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);
        p(1) = inv[p].image % 1000;
        prepare_item_image(p(1), inv[p].color, inv[p].param1);
        pos(wx + 37, wy + 69 + cnt * 19);
        gmode(2);
        gcopy_c(
            1,
            0,
            960,
            item_chips[p(1)].width,
            item_chips[p(1)].height,
            item_chips[p(1)].width * inf_tiles / item_chips[p(1)].height,
            inf_tiles);
        if (inv[p].body_part != 0)
        {
            draw("equipped", wx + 46, wy + 72 + cnt * 18 - 3);
        }
        cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1, 0, 1, p);
    }
    p = list(0, pagesize * page + cs);
    if (listmax == 0)
    {
        p = -1;
    }
    if (cs_bk != cs)
    {
        windowshadow = windowshadow(1);
        window_recipe(list2, p, wx + ww, wy, 400, wh);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    windowshadow(1) = 0;
    pos(wx + 10, wy + wh - 100);
    gcopy(3, 960, 96, 80, 90);
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1928_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1928_internal;
        }
    }
    if (p != -1)
    {
        ci = p;
        if (ibit(13, ci))
        {
            snd(27);
            txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
            goto label_1928_internal;
        }
        rpref(10 + step * 2 + 0) = ci;
        rpref(10 + step * 2 + 1) = inv[ci].id;
        snd(17);
        txt(i18n::s.get("core.locale.blending.steps.you_add", inv[ci]));
        ++step;
        p = rpdiff(rpid, step, step - 1);
        goto label_1923;
    }
    if (key == key_prev)
    {
        snd(1);
        --rppage;
        cs_bk = -1;
        if (rppage < 0)
        {
            rppage = rppage(1);
        }
    }
    if (key == key_next)
    {
        snd(1);
        ++rppage;
        cs_bk = -1;
        if (rppage > rppage(1))
        {
            rppage = 0;
        }
    }
    if (key == key_cancel)
    {
        --step;
        goto label_1923;
    }
    goto label_1928_internal;
}

std::string rpmatname(int prm_1037)
{
    std::string s_at_m177;
    int p_at_m177 = 0;
    s_at_m177 = u8"?????"s;
    if (rpdata(20 + prm_1037, rpid) < 9000)
    {
        s_at_m177 = ioriginalnameref(rpdata(20 + prm_1037, rpid));
    }
    else if (rpdata(20 + prm_1037, rpid) < 10000)
    {
        s_at_m177 = rfnameorg(1, rpdata(20 + prm_1037, rpid) - 9000);
    }
    else
    {
        s_at_m177 = fltname(rpdata(20 + prm_1037, rpid));
    }
    if (rpdata(40 + prm_1037, rpid) == 0)
    {
        return s_at_m177;
    }
    if (rpdata(40 + prm_1037, rpid) >= 10000)
    {
        p_at_m177 = rpdata((40 + prm_1037), rpid) % 10000;
        if (p_at_m177 < 0 || p_at_m177 >= 800)
        {
            s_at_m177 += u8"/bugged/"s;
            return s_at_m177;
        }
        s_at_m177 = i18n::s.get("core.locale.blending.ingredient.corpse",
                                chara_refstr(p_at_m177, 2));
        return s_at_m177;
    }
    return s_at_m177;
}


std::string rpsuccessrate(int prm_1040)
{
    if (prm_1040 == 100)
    {
        return i18n::s.get("core.locale.blending.success_rate.perfect");
    }
    if (prm_1040 >= 90)
    {
        return i18n::s.get("core.locale.blending.success_rate.piece_of_cake");
    }
    if (prm_1040 >= 80)
    {
        return i18n::s.get("core.locale.blending.success_rate.very_likely");
    }
    if (prm_1040 >= 70)
    {
        return i18n::s.get("core.locale.blending.success_rate.no_problem");
    }
    if (prm_1040 >= 60)
    {
        return i18n::s.get("core.locale.blending.success_rate.probably_ok");
    }
    if (prm_1040 >= 50)
    {
        return i18n::s.get("core.locale.blending.success_rate.maybe");
    }
    if (prm_1040 >= 40)
    {
        return i18n::s.get("core.locale.blending.success_rate.bad");
    }
    if (prm_1040 >= 30)
    {
        return i18n::s.get("core.locale.blending.success_rate.very_bad");
    }
    if (prm_1040 >= 20)
    {
        return i18n::s.get("core.locale.blending.success_rate.almost_impossible");
    }
    return i18n::s.get("core.locale.blending.success_rate.impossible");
}

std::string rpname(int prm_516)
{
    std::string s_at_m62;
    s_at_m62 = u8"?????"s;
    if (rpdatan(prm_516) != ""s)
    {
        return rpdatan(prm_516);
    }
    if (prm_516 >= 400)
    {
        return ioriginalnameref(prm_516 - 400);
    }
    return s_at_m62;
}

int rpdiff(int, int prm_1042, int prm_1043)
{
    int p1_at_m180 = 0;
    int f_at_m180 = 0;
    int f2_at_m180 = 0;
    int i_at_m180 = 0;
    int d_at_m180 = 0;
    int p_at_m180 = 0;
    p1_at_m180 = 80;
    f_at_m180 = 100;
    if (prm_1042 > 0)
    {
        for (int cnt = 0, cnt_end = (prm_1042); cnt < cnt_end; ++cnt)
        {
            f2_at_m180 = 0;
            if (rpref(10 + cnt * 2) == -1)
            {
                break;
            }
            i_at_m180 = rpref(10 + cnt * 2);
            if (inv[i_at_m180].curse_state == curse_state_t::blessed)
            {
                f2_at_m180 -= 10;
            }
            if (is_cursed(inv[i_at_m180].curse_state))
            {
                f2_at_m180 += 20;
            }
            f_at_m180 += f2_at_m180;
            if (prm_1043 == cnt)
            {
                while (1)
                {
                    if (f2_at_m180 < 0)
                    {
                        txtef(2);
                        txt(i18n::s.get("core.locale.blending.success_rate.goes_up"));
                        break;
                    }
                    if (f2_at_m180 > 0)
                    {
                        txtef(3);
                        txt(i18n::s.get("core.locale.blending.success_rate.goes_down"));
                        break;
                    }
                    break;
                }
            }
        }
    }
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        if (rpdata(10 + cnt * 2, rpid) == 0)
        {
            break;
        }
        if (sdata(rpdata(10 + cnt * 2, rpid), 0) <= 0)
        {
            p1_at_m180 -= 125;
            continue;
        }
        d_at_m180 = rpdata(11 + cnt * 2, rpid);
        if (prm_1042 > 0)
        {
            d_at_m180 = d_at_m180 * f_at_m180 / 100;
            if (d_at_m180 < 1)
            {
                d_at_m180 = 1;
            }
        }
        p_at_m180 =
            (d_at_m180 * 200 / sdata(rpdata((10 + cnt * 2), rpid), 0) - 200)
            * -1;
        if (p_at_m180 > 0)
        {
            p_at_m180 /= 5;
        }
        if (p_at_m180 < -125)
        {
            p_at_m180 = -125;
        }
        p1_at_m180 += p_at_m180;
    }
    if (p1_at_m180 < 25)
    {
        p1_at_m180 = 0;
    }
    if (p1_at_m180 > 100)
    {
        p1_at_m180 = 100;
    }
    return p1_at_m180;
}

int blendcheckext(int prm_1038, int prm_1039)
{
    int p_at_m178 = 0;
    if (rpdata(40 + prm_1039, rpid) >= 10000)
    {
        p_at_m178 = rpdata((40 + prm_1039), rpid) % 10000;
        if (p_at_m178 < 0 || p_at_m178 >= 800)
        {
            return 0;
        }
        if (inv[prm_1038].subname == p_at_m178)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int blendcheckmat(int prm_1044)
{
    int f_at_m181 = 0;
    int step_at_m181 = 0;
    int id_at_m181 = 0;
    int rp_at_m181 = 0;
    int o_at_m181 = 0;
    rpid = prm_1044;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpdata(20 + cnt, rpid) == 0)
        {
            break;
        }
        f_at_m181 = 0;
        step_at_m181 = cnt;
        id_at_m181 = rpdata(20 + cnt, rpid);
        rp_at_m181 = cnt;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            if (cnt == 0)
            {
                o_at_m181 = -1;
            }
            if (cnt == 1)
            {
                o_at_m181 = 0;
            }
            for (const auto& cnt : items(o_at_m181))
            {
                if (inv[cnt].number <= 0)
                {
                    continue;
                }
                if ((rpdata(2, rpid) <= 0 || step_at_m181 != 0)
                    && inv[cnt].own_state > 0)
                {
                    continue;
                }
                if (o_at_m181 == -1)
                {
                    if (dist(
                            inv[cnt].position.x,
                            inv[cnt].position.y,
                            cdata[0].position.x,
                            cdata[0].position.y)
                        > 4)
                    {
                        continue;
                    }
                }
                if (rpdata(40 + rp_at_m181, rpid))
                {
                    int stat = blendcheckext(cnt, rp_at_m181);
                    if (stat == 0)
                    {
                        continue;
                    }
                }
                if (id_at_m181 < 9000)
                {
                    if (inv[cnt].id == id_at_m181)
                    {
                        f_at_m181 = 1;
                        break;
                    }
                    continue;
                }
                if (id_at_m181 < 10000)
                {
                    if (instr(
                            the_item_db[inv[cnt].id]->rffilter,
                            0,
                            u8"/"s + rfnameorg(0, (id_at_m181 - 9000)) + u8"/"s)
                            != -1
                        || id_at_m181 == 9004)
                    {
                        f_at_m181 = 1;
                        break;
                    }
                    continue;
                }
                if (the_item_db[inv[cnt].id]->category == id_at_m181)
                {
                    f_at_m181 = 1;
                    break;
                }
            }
            if (f_at_m181 == 1)
            {
                break;
            }
        }
        if (f_at_m181 == 0)
        {
            break;
        }
    }
    return f_at_m181;
}

int blendmatnum(int prm_1045, int prm_1046)
{
    int m_at_m182 = 0;
    int o_at_m182 = 0;
    m_at_m182 = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            o_at_m182 = -1;
        }
        if (cnt == 1)
        {
            o_at_m182 = 0;
        }
        for (const auto& cnt : items(o_at_m182))
        {
            if (inv[cnt].number <= 0)
            {
                continue;
            }
            if ((rpdata(2, rpid) <= 0 || prm_1046 != 0)
                && inv[cnt].own_state > 0)
            {
                continue;
            }
            if (o_at_m182 == -1)
            {
                if (dist(
                        inv[cnt].position.x,
                        inv[cnt].position.y,
                        cdata[0].position.x,
                        cdata[0].position.y)
                    > 4)
                {
                    continue;
                }
            }
            if (rpdata(40 + prm_1046, rpid))
            {
                int stat = blendcheckext(cnt, prm_1046);
                if (stat == 0)
                {
                    continue;
                }
            }
            if (prm_1045 < 9000)
            {
                if (inv[cnt].id == prm_1045)
                {
                    m_at_m182 += inv[cnt].number;
                }
                continue;
            }
            if (prm_1045 < 10000)
            {
                if (instr(
                        the_item_db[inv[cnt].id]->rffilter,
                        0,
                        u8"/"s + rfnameorg(0, (prm_1045 - 9000)) + u8"/"s)
                        != -1
                    || prm_1045 == 9004)
                {
                    m_at_m182 += inv[cnt].number;
                }
                continue;
            }
            if (the_item_db[inv[cnt].id]->category == prm_1045)
            {
                m_at_m182 += inv[cnt].number;
                continue;
            }
        }
    }
    return m_at_m182;
}

int blendlist(elona_vector2<int>& prm_1047, int prm_1048)
{
    int id_at_m183 = 0;
    int m_at_m183 = 0;
    int o_at_m183 = 0;
    int reftype_at_m183 = 0;
    int f_at_m183 = 0;
    id_at_m183 = rpdata(20 + prm_1048, rpid);
    m_at_m183 = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            o_at_m183 = -1;
        }
        if (cnt == 1)
        {
            o_at_m183 = 0;
        }
        for (const auto& cnt : items(o_at_m183))
        {
            if (m_at_m183 >= 500)
            {
                break;
            }
            if (inv[cnt].number <= 0)
            {
                continue;
            }
            if ((rpdata(2, rpid) <= 0 || step != 0) && inv[cnt].own_state > 0)
            {
                continue;
            }
            if (o_at_m183 == -1)
            {
                if (dist(
                        inv[cnt].position.x,
                        inv[cnt].position.y,
                        cdata[0].position.x,
                        cdata[0].position.y)
                    > 4)
                {
                    continue;
                }
            }
            reftype_at_m183 = the_item_db[inv[cnt].id]->category;
            if (rpdata(40 + prm_1048, rpid))
            {
                int stat = blendcheckext(cnt, prm_1048);
                if (stat == 0)
                {
                    continue;
                }
            }
            if (id_at_m183 < 9000)
            {
                if (inv[cnt].id != id_at_m183)
                {
                    continue;
                }
            }
            else if (id_at_m183 < 10000)
            {
                if (instr(
                        the_item_db[inv[cnt].id]->rffilter,
                        0,
                        u8"/"s + rfnameorg(0, (id_at_m183 - 9000)) + u8"/"s)
                        == -1
                    && id_at_m183 != 9004)
                {
                    continue;
                }
            }
            else if (reftype_at_m183 != id_at_m183)
            {
                continue;
            }
            if (step > 0)
            {
                f_at_m183 = cnt;
                for (int cnt = 0, cnt_end = (step); cnt < cnt_end; ++cnt)
                {
                    if (rpref(10 + cnt * 2) == f_at_m183)
                    {
                        f_at_m183 = -999;
                        break;
                    }
                }
                if (f_at_m183 == -999)
                {
                    continue;
                }
            }
            prm_1047(0, m_at_m183) = cnt;
            prm_1047(1, m_at_m183) = reftype_at_m183 * 1000 + inv[cnt].id;
            ++m_at_m183;
        }
    }
    return m_at_m183;
}

void clear_rprefmat()
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        rpref(10 + cnt * 2) = -1;
    }
    return;
}


int label_1931()
{
    f = 1;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpref(10 + cnt * 2) == -1)
        {
            break;
        }
        if (rpref(10 + cnt * 2) == -2)
        {
            f = 0;
            break;
        }
        if (inv[rpref(10 + cnt * 2)].number <= 0
            || inv[rpref(10 + cnt * 2)].id != rpref(11 + cnt * 2))
        {
            f = 0;
            break;
        }
    }
    return f;
}

int label_1932()
{
    p = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpref(10 + cnt * 2) == -1)
        {
            break;
        }
        if (rpref(10 + cnt * 2) == -2)
        {
            continue;
        }
        if ((rpdata(2, rpid) <= 0 || cnt != 0) && rpresult)
        {
            --inv[rpref(10 + cnt * 2)].number;
        }
        else if (rnd(3) == 0)
        {

            txt(i18n::s.get("core.locale.blending.you_lose", inv[rpref(10 + cnt * 2)]));
            --inv[rpref(10 + cnt * 2)].number;
        }
        if (chara_unequip(rpref(10 + cnt * 2)))
        {
            chara_refresh(0);
        }
        cell_refresh(
            inv[rpref(10 + cnt * 2)].position.x,
            inv[rpref(10 + cnt * 2)].position.y);
    }
    refresh_burden_state();
    return 1;
}

void label_1933()
{
    rpresult = 1;
    if (rpdiff(rpid, -1, -1) < rnd(100))
    {
        rpresult = 0;
        txtef(3);
        txt(i18n::s.get("core.locale.blending.failed"));
    }
    else
    {
        if (rpdata(0, rpid) >= 10000)
        {
            label_1935();
        }
        else
        {
            flt();
            nostack = 1;
            int stat = itemcreate(
                -1,
                rpdata(0, rpid),
                cdata[0].position.x,
                cdata[0].position.y,
                0);
            if (stat != 0)
            {
                for (int cnt = 0;; ++cnt)
                {
                    if (rpdata(50 + cnt * 2, rpid) == 0)
                    {
                        break;
                    }
                    enchantment_add(
                        ci,
                        rpdata(50 + cnt * 2, rpid),
                        rpdata(51 + cnt * 2, rpid),
                        0,
                        1);
                }
            }
            txtef(2);
            txt(i18n::s.get("core.locale.blending.succeeded", inv[ci]));
            snd(17);
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            if (rpdata(10 + cnt * 2, rpid) == 0)
            {
                break;
            }
            skillexp(
                rpdata(10 + cnt * 2, rpid),
                0,
                50 + rpdata((11 + cnt * 2), rpid) + rpref(2) / 10000 * 25,
                2,
                50);
        }
    }
    --rpref(1);
    label_1932();
    return;
}

// TODO: Much duplication with do_dip_command()
void label_1935()
{
    int cibk = ci;
    ci = rpref(10);
    ti = rpref(12);
    if (rpdata(2, rpid) == 2)
    {
        item_separate(ci);
    }
    else if (inv[ci].number <= 1)
    {
        rpref(10) = -2;
    }
    else
    {
        int stat = item_separate(ci);
        if (rpref(10) == stat)
        {
            rpref(10) = -2;
        }
        else
        {
            rpref(10) = stat;
        }
    }
    switch (rpdata(0, rpid))
    {
    case 10000:
        ibitmod(6, ci, 1);
        txtef(2);
        txt(i18n::s.get("core.locale.blending.succeeded", inv[ci]));
        txt(i18n::s.get("core.locale.action.dip.result.love_food.guilty"));
        snd(65);
        break;
    case 10001:
        inv[ci].color = inv[ti].color;
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.result.dyeing", inv[ci]));
        snd(17);
        break;
    case 10002:
        ibitmod(14, ci, 1);
        txtef(2);
        txt(i18n::s.get("core.locale.blending.succeeded", inv[ci]));
        txt(i18n::s.get("core.locale.action.dip.result.poisoned_food"));
        snd(65);
        break;
    case 10003:
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.result.put_on", inv[ci], inv[ti]));
        if (inv[ci].id == 567)
        {
            txt(i18n::s.get("core.locale.action.dip.result.good_idea_but"));
        }
        else
        {
            ibitmod(2, ci, 1);
            txt(i18n::s.get("core.locale.action.dip.result.gains_fireproof", inv[ci]));
        }
        snd(17);
        break;
    case 10004:
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.result.put_on", inv[ci], inv[ti]));
        ibitmod(1, ci, 1);
        txt(i18n::s.get("core.locale.action.dip.result.gains_acidproof", inv[ci]));
        snd(17);
        break;
    case 10005:
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.result.bait_attachment", inv[ci], inv[ti]));
        if (inv[ci].param4 == inv[ti].param1)
        {
            inv[ci].count += rnd(10) + 15;
        }
        else
        {
            inv[ci].count = rnd(10) + 15;
            inv[ci].param4 = inv[ti].param1;
        }
        snd(13);
        break;
    case 10006:
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.result.blessed_item", inv[ci], inv[ti]));
        if (inv[ti].curse_state == curse_state_t::blessed)
        {
            txtef(5);
            txt(i18n::s.get("core.locale.action.dip.result.becomes_blessed", inv[ci]));
            inv[ci].curse_state = curse_state_t::blessed;
        }
        if (is_cursed(inv[ti].curse_state))
        {
            txtef(8);
            txt(i18n::s.get("core.locale.action.dip.result.becomes_cursed", inv[ci]));
            inv[ci].curse_state = curse_state_t::cursed;
        }
        snd(17);
        break;
    case 10007:
        txt(i18n::s.get("core.locale.action.dip.result.well_refill", inv[ci], inv[ti]));
        if (inv[ti].id == 601)
        {
            txt(i18n::s.get("core.locale.action.dip.result.empty_bottle_shatters"));
            break;
        }
        snd(17);
        if (inv[ci].id == 602)
        {
            txt(i18n::s.get("core.locale.action.dip.result.holy_well_polluted"));
            break;
        }
        if (inv[ci].param3 >= 20)
        {
            txt(i18n::s.get("core.locale.action.dip.result.well_dry", inv[ci]));
            break;
        }
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.result.well_refilled", inv[ci]));
        if (inv[ti].id == 587)
        {
            txt(i18n::s.get("core.locale.action.dip.result.snow_melts.blending"));
        }
        else
        {
            inv[ci].param1 += rnd(3);
        }
        break;
    case 10008:
        if (inv[ci].param1 < -5 || inv[ci].param3 >= 20
            || (inv[ci].id == 602 && gdata_holy_well_count <= 0))
        {
            txt(i18n::s.get("core.locale.action.dip.result.natural_potion_dry", inv[ci]));
            txt(i18n::s.get("core.locale.action.dip.result.natural_potion_drop"));
            break;
        }
        if (inv_getfreeid(0) == -1)
        {
            txt(i18n::s.get("core.locale.ui.inv.common.inventory_is_full"));
            break;
        }
        cibk = ci;
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
        txt(i18n::s.get("core.locale.action.dip.result.natural_potion"));
        txtef(2);
        txt(i18n::s.get("core.locale.action.dip.you_get", inv[ci]));
        item_stack(0, ci, 1);
        item_stack(0, ci);
        ci = cibk;
        snd(17);
        break;
    }

    item_stack(0, ci);
    if (inv[ci].body_part != 0)
    {
        create_pcpic(0, true);
    }
    if (inv_getowner(ci) == -1)
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
    }
    chara_refresh(0);
    return;
}

} // namespace elona
