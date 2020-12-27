#include "shop.hpp"

#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_item.hpp"
#include "food.hpp"
#include "game.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/interface.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "skill.hpp"
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
            ++game()->next_inventory_serial_id;
            shopkeeper.shop_store_id = game()->next_inventory_serial_id;
        }
        shop_refresh(shopkeeper);
    }
    else if (game_now() >= shopkeeper.shop_restock_time)
    {
        shop_refresh(shopkeeper);
    }
    else
    {
        inv_open_tmp_inv(fs::u8path("shop"s + invfile + ".s2"));
    }
    invfile = shopkeeper.shop_store_id;
    shop_load_shoptmp();
}



void shop_load_shoptmp()
{
    inv_close_tmp_inv(fs::u8path("shop"s + invfile + ".s2"));
    mode = 0;
}



void shop_refresh(Character& shopkeeper)
{
    inv_open_tmp_inv_no_physical_file();

    lua::call("core.Impl.shop_inventory.generate", lua::handle(shopkeeper));

    shopkeeper.shop_restock_time =
        game_now() + time::Duration::from_days(g_config.restock_interval());
}



void shop_sell_item(optional_ref<Character> shopkeeper)
{
    mode = 6;
    inv_open_tmp_inv(fs::u8path("shop"s + invfile + ".s2"));
    shoptrade = 0;
    if (shopkeeper)
    {
        if (shopkeeper->role == Role::trader)
        {
            shoptrade = 1;
        }
    }
    CtrlInventoryOptions opts;
    opts.inventory_owner = shopkeeper;
    ctrl_inventory(opts);
}

} // namespace elona
