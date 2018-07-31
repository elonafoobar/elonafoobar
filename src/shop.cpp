#include "shop.hpp"
#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

void shop_refresh_on_talk()
{
    if (tc > 0)
    {
        if (cdata[tc].character_role == 1009)
        {
            calc_trade_goods_price();
        }
    }
    mode = 6;
    ctrl_file(file_operation2_t::map_items_write, u8"shoptmp.s2");
    if (cdata[tc].shop_store_id == 0)
    {
        if (cdata[tc].character_role == 1010
            || cdata[tc].character_role == 2003)
        {
            cdata[tc].shop_store_id = 1;
        }
        else
        {
            ++gdata_next_inventory_serial_id;
            cdata[tc].shop_store_id = gdata_next_inventory_serial_id;
        }
        shop_refresh();
    }
    else if (
        gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12
        >= cdata[tc].time_to_restore)
    {
        shop_refresh();
    }
    else
    {
        ctrl_file(file_operation2_t::map_items_read, u8"shop"s + invfile + u8".s2");
    }
    invfile = cdata[tc].shop_store_id;
    shop_load_shoptmp();
    return;
}

void shop_load_shoptmp()
{
    ctrl_file(file_operation2_t::map_items_write, u8"shop"s + invfile + u8".s2");
    ctrl_file(file_operation2_t::map_items_read, u8"shoptmp.s2");
    mode = 0;
    return;
}

void shop_refresh()
{
    for (const auto& cnt : items(-1))
    {
        inv[cnt].remove();
    }
    p = std::min(80, 20 + cdata[tc].shop_rank / 2);
    if (cdata[tc].character_role == 1007)
    {
        p = 6 + cdata[tc].shop_rank / 10;
    }
    if (cdata[tc].character_role == 1010)
    {
        p = 4 + rnd(4);
    }
    if (cdata[tc].character_role == 2003)
    {
        p = 4 + rnd(4);
    }
    if (cdata[tc].character_role == 1016)
    {
        p = 20;
    }
    if (cdata[tc].character_role == 1018)
    {
        p /= 2;
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        flt(calcobjlv(cdata[tc].shop_rank), calcfixlv(2));
        dbid = 0;
        if (cdata[tc].character_role == 1004)
        {
            p = rnd(3);
            if (p == 0)
            {
                flttypeminor = 52001;
            }
            if (p == 1)
            {
                flttypemajor = 53000;
            }
            if (p == 2)
            {
                flttypemajor = 52000;
            }
            if (rnd(7) == 0)
            {
                flttypemajor = 54000;
            }
            if (rnd(15) == 0)
            {
                flttypemajor = 55000;
            }
            if (0 || rnd(20) == 0)
            {
                dbid = 783;
            }
        }
        if (cdata[tc].character_role == 1019)
        {
            dbid = 667;
        }
        if (cdata[tc].character_role == 1020)
        {
            listmax = 0;
            for (int cnt = 0; cnt < 800; ++cnt)
            {
                if (itemmemory(2, cnt) > 1)
                {
                    list(0, listmax) = cnt;
                    ++listmax;
                }
            }
            if (listmax == 0)
            {
                return;
            }
            dbid = list(0, rnd(listmax));
        }
        if (cdata[tc].character_role == 1015)
        {
            p = rnd(3);
            if (p == 0)
            {
                flttypemajor = 59000;
            }
            if (p == 1)
            {
                flttypemajor = 32000;
            }
            if (p == 2)
            {
                flttypemajor = 34000;
            }
            if (rnd(3) == 0)
            {
                fixlv = 3;
            }
            if (rnd(10) == 0)
            {
                fixlv = 4;
            }
        }
        if (cdata[tc].character_role == 1006)
        {
            p = rnd(5);
            if (p == 0)
            {
                flttypemajor = 25000;
            }
            if (p == 1)
            {
                flttypemajor = 60000;
            }
            if (p == 2)
            {
                flttypemajor = 20000;
            }
            if (p == 3)
            {
                flttypemajor = 77000;
            }
            if (p == 4)
            {
                flttypemajor = 59000;
            }
            if (rnd(20) == 0)
            {
                dbid = 734;
            }
            if (rnd(8) == 0)
            {
                flttypemajor = 91000;
            }
            if (rnd(10) == 0)
            {
                dbid = choice(isetdeed);
            }
        }
        if (cdata[tc].character_role == 1003)
        {
            if (rnd(3) != 0)
            {
                continue;
            }
            if (rnd(3) != 0)
            {
                flttypeminor = 57001;
            }
            else
            {
                flttypeminor = 57002;
            }
        }
        if (cdata[tc].character_role == 1002)
        {
            if (rnd(3) != 0)
            {
                continue;
            }
            flttypemajor = 57000;
            if (rnd(5) == 0)
            {
                flttypemajor = 91000;
            }
        }
        if (cdata[tc].character_role == 1007)
        {
            flttypemajor = choice(fsetwear);
            if (rnd(3) == 0)
            {
                fixlv = 3;
            }
            if (rnd(10) == 0)
            {
                fixlv = 4;
            }
        }
        if (cdata[tc].character_role == 1010
            || cdata[tc].character_role == 2003)
        {
            flttypemajor = choice(fsetwear);
            fixlv = 3;
            if (rnd(2) == 0)
            {
                fixlv = 4;
            }
        }
        if (cdata[tc].character_role == 1005)
        {
            flttypemajor = 91000;
            if (rnd(4))
            {
                flttypeminor = 52002;
            }
            if (rnd(20) == 0)
            {
                dbid = 734;
            }
        }
        if (cdata[tc].character_role == 1008)
        {
            flttypemajor = 56000;
            if (rnd(3) == 0)
            {
                flttypemajor = choice(fsetwear);
            }
            if (rnd(3) == 0)
            {
                flttypemajor = 60000;
            }
            if (rnd(5) == 0)
            {
                flttypemajor = 57000;
            }
            if (rnd(4) == 0)
            {
                flttypemajor = 53000;
            }
            if (rnd(15) == 0)
            {
                flttypemajor = 55000;
            }
            if (rnd(10) == 0)
            {
                flttypemajor = 91000;
            }
            if (rnd(10) == 0)
            {
                dbid = choice(isetdeed);
            }
            if (rnd(15) == 0)
            {
                dbid = 511;
            }
        }
        if (cdata[tc].character_role == 1001)
        {
            p = rnd(6);
            if (p == 0)
            {
                flttypemajor = 16000;
            }
            if (p == 1)
            {
                flttypemajor = 12000;
            }
            if (p == 2)
            {
                flttypemajor = 22000;
            }
            if (p == 3)
            {
                flttypemajor = 18000;
            }
            if (p == 4)
            {
                flttypemajor = 14000;
            }
            if (p == 5)
            {
                flttypemajor = 19000;
            }
            if (rnd(3) == 0)
            {
                if (rnd(3) == 0)
                {
                    flttypemajor = 10000;
                }
                else
                {
                    flttypemajor = 24000;
                }
            }
        }
        if (cdata[tc].character_role == 1009)
        {
            flttypemajor = 92000;
        }
        if (cdata[tc].character_role == 1021)
        {
            flttypemajor = 59000;
            if (rnd(2) == 0)
            {
                dbid = 636;
            }
            if (rnd(2) == 0)
            {
                dbid = 629;
            }
        }
        if (cdata[tc].character_role == 1011)
        {
            if (rnd(4) == 0)
            {
                flttypemajor = 24000;
            }
            if (rnd(5) == 0)
            {
                flttypemajor = 25000;
            }
            if (rnd(3) == 0)
            {
                flttypemajor = 57000;
            }
            fltn(u8"sf"s);
        }
        if (cdata[tc].character_role == 1013)
        {
            if (rnd(3) != 0)
            {
                continue;
            }
            flttypemajor = 55000;
            if (rnd(3))
            {
                dbid = choice(isetdeed);
            }
            if (rnd(5) == 0)
            {
                dbid = 511;
            }
        }
        if (cdata[tc].character_role == 1018)
        {
            fltn(u8"spshop"s);
        }
        if (cdata[tc].character_role == 1022)
        {
            fltn(u8"fest"s);
            if (rnd(12) == 0)
            {
                dbid = 750;
            }
            if (rnd(12) == 0)
            {
                dbid = 751;
            }
            if (rnd(5) == 0)
            {
                dbid = 770;
            }
            if (rnd(12) == 0)
            {
                dbid = 762;
            }
            if (rnd(12) == 0)
            {
                dbid = 768;
            }
            if (rnd(12) == 0)
            {
                dbid = 769;
            }
        }
        if (cdata[tc].character_role == 1017)
        {
            dbid = 519;
        }
        if (cdata[tc].character_role == 1012)
        {
            flttypemajor = 60000;
            if (cnt == 0)
            {
                dbid = 510;
            }
            if (cnt == 1)
            {
                dbid = 561;
            }
            if (cnt == 2)
            {
                dbid = 562;
            }
            if (cnt == 3)
            {
                dbid = 547;
            }
            if (cnt == 4)
            {
                dbid = 579;
            }
            if (cnt == 5)
            {
                dbid = 576;
            }
            if (cnt == 6)
            {
                dbid = 611;
            }
            if (cnt > 10)
            {
                if (rnd(3) != 0)
                {
                    continue;
                }
            }
            if (cnt == 19)
            {
                dbid = 413;
            }
            if (cnt == 20)
            {
                dbid = 414;
            }
            if (cnt == 21)
            {
                dbid = 616;
            }
        }
        if (cdata[tc].character_role == 1014)
        {
            dbid = 617;
        }
        if (cdata[tc].character_role == 1016)
        {
            if (cnt == 0)
            {
                dbid = 430;
            }
            if (cnt == 1)
            {
                dbid = 431;
            }
            if (cnt == 2)
            {
                dbid = 502;
            }
            if (cnt == 3)
            {
                dbid = 480;
            }
            if (cnt == 4)
            {
                dbid = 421;
            }
            if (cnt == 5)
            {
                dbid = 603;
            }
            if (cnt == 6)
            {
                dbid = 615;
            }
            if (cnt == 7)
            {
                dbid = 559;
            }
            if (cnt == 8)
            {
                dbid = 516;
            }
            if (cnt == 9)
            {
                dbid = 616;
            }
            if (cnt == 10)
            {
                dbid = 623;
            }
            if (cnt == 11)
            {
                dbid = 505;
            }
            if (cnt == 12)
            {
                dbid = 624;
            }
            if (cnt == 13)
            {
                dbid = 625;
            }
            if (cnt == 14)
            {
                dbid = 626;
            }
            if (cnt == 15)
            {
                dbid = 627;
            }
            if (cnt == 16)
            {
                dbid = 56;
            }
            if (cnt == 17)
            {
                dbid = 742;
            }
            if (cnt == 18)
            {
                dbid = 760;
            }
            if (cnt > 18)
            {
                continue;
            }
        }
        nostack = 1;
        int stat = itemcreate(-1, dbid, -1, -1, 0);
        if (stat == 0)
        {
            break;
        }
        if (cdata[tc].character_role == 1016)
        {
            inv[ci].set_number(1);
            inv[ci].curse_state = curse_state_t::none;
            if (inv[ci].id == 480)
            {
                inv[ci].count = 4;
            }
            continue;
        }
        f = 0;
        if (strutil::contains(the_item_db[inv[ci].id]->filter, u8"/neg/"))
        {
            f = 1;
        }
        if (strutil::contains(the_item_db[inv[ci].id]->filter, u8"/noshop/"))
        {
            if (cdata[tc].character_role != 1018)
            {
                f = 1;
            }
        }
        if (f)
        {
            inv[ci].remove();
            continue;
        }
        if (cdata[tc].character_role == 1012)
        {
            flttypemajor = 60000;
        }
        calc_number_of_items_sold_at_shop();
        inv[ci].set_number(rnd(rtval) + 1);
        if (cdata[tc].character_role == 1009)
        {
            p = trate(inv[ci].param1);
            if (p <= 70)
            {
                inv[ci].set_number(inv[ci].number() * 200 / 100);
            }
            if (p <= 50)
            {
                inv[ci].set_number(inv[ci].number() * 200 / 100);
            }
            if (p >= 80)
            {
                inv[ci].set_number(inv[ci].number() / 2 + 1);
                if (rnd(2))
                {
                    inv[ci].remove();
                    continue;
                }
            }
            if (p >= 100)
            {
                inv[ci].set_number(inv[ci].number() / 2 + 1);
                if (rnd(3))
                {
                    inv[ci].remove();
                    continue;
                }
            }
            inv[ci].set_number(inv[ci].number() * (100 + sdata(156, 0) * 10) / 100 + 1);
        }
        p = the_item_db[inv[ci].id]->category;
        if (is_cursed(inv[ci].curse_state))
        {
            inv[ci].remove();
            continue;
        }
        if (inv[ci].curse_state == curse_state_t::blessed)
        {
            inv[ci].set_number(1);
        }
        if (p == 52000)
        {
            if (inv[ci].id == 516)
            {
                inv[ci].remove();
            }
        }
        if (p == 57000)
        {
            if (the_item_db[inv[ci].id]->subcategory == 58500)
            {
                if (rnd(5))
                {
                    inv[ci].remove();
                }
            }
        }
        if (cdata[tc].character_role == 1018)
        {
            inv[ci].value = clamp(inv[ci].value, 1, 1000000) * 50;
            if (inv[ci].id == 729)
            {
                inv[ci].value *= 10;
            }
        }
        if (cdata[tc].character_role == 1015)
        {
            inv[ci].value *= 2;
        }
        if (cdata[tc].character_role == 1007)
        {
            if (gdata_belongs_to_thieves_guild != 0)
            {
                inv[ci].value *= 2;
            }
            else
            {
                inv[ci].value *= 3;
            }
        }
        if (cdata[tc].character_role == 1010)
        {
            inv[ci].value *= 2;
        }
        if (cdata[tc].character_role == 2003)
        {
            inv[ci].value = inv[ci].value * 4 / 5;
        }
        if (cdata[tc].character_role == 1020)
        {
            inv[ci].value = inv[ci].value * 3 / 2;
        }
        item_stack(-1, ci);
    }
    if (config::instance().restock_interval)
    {
        cdata[tc].time_to_restore = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12
            + 24 * config::instance().restock_interval;
    }
    else
    {
        cdata[tc].time_to_restore = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 - 1;
    }
}

void calc_number_of_items_sold_at_shop()
{
    p = the_item_db[inv[ci].id]->category;
    i = the_item_db[inv[ci].id]->rarity / 1000;
    rtval = 1;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (i <= 100)
        {
            break;
        }
        if (p == 57000)
        {
            rtval = 1;
            break;
        }
        if (p == 92000)
        {
            rtval = i / 200;
            break;
        }
        if (p >= 90000)
        {
            rtval = i / 100;
            break;
        }
        if (p == 52000)
        {
            rtval = i / 100;
            break;
        }
        if (p == 53000)
        {
            rtval = i / 100;
            break;
        }
        if (p == 60000)
        {
            rtval = i / 200;
            break;
        }
        if (p == 64000)
        {
            rtval = i / 80;
            break;
        }
        if (p == 59000)
        {
            rtval = i / 500;
            break;
        }
    }
    if (dbid == 734)
    {
        rtval = rnd(8);
    }
    if (rtval < 1)
    {
        rtval = 1;
        return;
    }
    return;
}

void calc_trade_goods_price()
{
    DIM2(trate, 8);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        trate(cnt) = 100;
    }
    if (gdata_current_map == mdata_t::map_id_t::vernis)
    {
        trate(0) = 130;
        trate(1) = 70;
        trate(3) = 110;
        trate(2) = 85;
        trate(6) = 150;
        trate(7) = 120;
    }
    if (gdata_current_map == mdata_t::map_id_t::port_kapul)
    {
        trate(0) = 65;
        trate(1) = 110;
        trate(4) = 125;
        trate(5) = 65;
        trate(2) = 70;
        trate(6) = 200;
        trate(7) = 150;
    }
    if (gdata_current_map == mdata_t::map_id_t::palmia)
    {
        trate(0) = 120;
        trate(2) = 75;
        trate(4) = 75;
        trate(1) = 125;
        trate(6) = 110;
        trate(7) = 80;
    }
    if (gdata_current_map == mdata_t::map_id_t::yowyn)
    {
        trate(0) = 120;
        trate(3) = 75;
        trate(2) = 120;
        trate(6) = 160;
        trate(7) = 100;
    }
    if (gdata_current_map == mdata_t::map_id_t::derphy)
    {
        trate(0) = 85;
        trate(3) = 70;
        trate(5) = 120;
        trate(2) = 130;
        trate(6) = 130;
        trate(7) = 90;
    }
    if (gdata_current_map == mdata_t::map_id_t::noyel)
    {
        trate(1) = 175;
        trate(0) = 170;
        trate(3) = 160;
        trate(5) = 130;
        trate(2) = 140;
        trate(6) = 75;
        trate(7) = 120;
    }
    if (gdata_current_map == mdata_t::map_id_t::lumiest)
    {
        trate(1) = 145;
        trate(0) = 130;
        trate(3) = 100;
        trate(5) = 120;
        trate(2) = 120;
        trate(6) = 100;
        trate(7) = 70;
    }
    randomize(
        (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
         + gdata_year * 24 * 30 * 12)
        / 100);
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        trate(cnt) += rnd(15) - rnd(15);
    }
    randomize();
    return;
}

void shop_sell_item()
{
    mode = 6;
    ctrl_file(file_operation2_t::map_items_write, u8"shoptmp.s2");
    ctrl_file(file_operation2_t::map_items_read, u8"shop"s + invfile + u8".s2");
    shoptrade = 0;
    if (tc > 0)
    {
        if (cdata[tc].character_role == 1009)
        {
            shoptrade = 1;
        }
    }
    ctrl_inventory();
    return;
}

} // namespace elona
