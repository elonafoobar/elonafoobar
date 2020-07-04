#include "shop.hpp"

#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
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

void shop_refresh_on_talk(Character& shopkeeper)
{
    if (shopkeeper.role == Role::trader)
    {
        map_calc_trade_goods_price();
    }
    mode = 6;
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");

    bool is_temporary = false;

    auto shop_inv =
        lua::get_data("core.shop_inventory", static_cast<int>(shopkeeper.role));
    if (shop_inv)
    {
        is_temporary = shop_inv->optional_or<bool>("is_temporary", false);
    }

    if (shopkeeper.shop_store_id == 0)
    {
        if (is_temporary)
        {
            shopkeeper.shop_store_id = 1;
        }
        else
        {
            ++game_data.next_inventory_serial_id;
            shopkeeper.shop_store_id = game_data.next_inventory_serial_id;
        }
        shop_refresh(shopkeeper);
    }
    else if (game_data.date.hours() >= shopkeeper.time_to_restore)
    {
        shop_refresh(shopkeeper);
    }
    else
    {
        ctrl_file(
            FileOperation2::map_items_read, u8"shop"s + invfile + u8".s2");
    }
    invfile = shopkeeper.shop_store_id;
    shop_load_shoptmp();
}



void shop_load_shoptmp()
{
    ctrl_file(FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
    mode = 0;
}



void shop_refresh(Character& shopkeeper)
{
    for (const auto& item : g_inv.ground())
    {
        item->remove();
    }

    lua::call("core.Impl.shop_inventory.generate", lua::handle(shopkeeper));

    if (g_config.restock_interval())
    {
        shopkeeper.time_to_restore =
            game_data.date.hours() + 24 * g_config.restock_interval();
    }
    else
    {
        shopkeeper.time_to_restore = game_data.date.hours() - 1;
    }
}



void shop_sell_item(optional_ref<Character> shopkeeper)
{
    mode = 6;
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    ctrl_file(FileOperation2::map_items_read, u8"shop"s + invfile + u8".s2");
    shoptrade = 0;
    if (shopkeeper)
    {
        if (shopkeeper->role == Role::trader)
        {
            shoptrade = 1;
        }
    }
    ctrl_inventory(shopkeeper);
}

} // namespace elona
