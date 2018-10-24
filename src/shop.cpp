#include "shop.hpp"
#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "food.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/interface.hpp"
#include "map.hpp"
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
            map_calc_trade_goods_price();
        }
    }
    mode = 6;
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    if (cdata[tc].shop_store_id == 0)
    {
        if (cdata[tc].character_role == 1010
            || cdata[tc].character_role == 2003)
        {
            cdata[tc].shop_store_id = 1;
        }
        else
        {
            ++game_data.next_inventory_serial_id;
            cdata[tc].shop_store_id = game_data.next_inventory_serial_id;
        }
        shop_refresh();
    }
    else if (game_data.date.hours() >= cdata[tc].time_to_restore)
    {
        shop_refresh();
    }
    else
    {
        ctrl_file(
            FileOperation2::map_items_read, u8"shop"s + invfile + u8".s2");
    }
    invfile = cdata[tc].shop_store_id;
    shop_load_shoptmp();
}

void shop_load_shoptmp()
{
    ctrl_file(FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
    mode = 0;
}

void shop_refresh()
{
    for (const auto& cnt : items(-1))
    {
        inv[cnt].remove();
    }

    lua::call(
        "exports:core.impl.shop_inventory.generate", lua::handle(cdata[tc]));

    if (Config::instance().restock_interval)
    {
        cdata[tc].time_to_restore =
            game_data.date.hours() + 24 * Config::instance().restock_interval;
    }
    else
    {
        cdata[tc].time_to_restore = game_data.date.hours() - 1;
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
}

void shop_sell_item()
{
    mode = 6;
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    ctrl_file(FileOperation2::map_items_read, u8"shop"s + invfile + u8".s2");
    shoptrade = 0;
    if (tc > 0)
    {
        if (cdata[tc].character_role == 1009)
        {
            shoptrade = 1;
        }
    }
    ctrl_inventory();
}

} // namespace elona
