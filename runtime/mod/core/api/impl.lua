local Impl = {}

Impl.chara_drop = require("impl/chara_drop.lua")
Impl.shop_inventory = require("impl/shop_inventory.lua")
Impl.show_dialog = require("impl/show_dialog.lua")
Impl.Blending = require("impl/blending.lua")

ELONA.api:add {
   Impl = Impl,
}
