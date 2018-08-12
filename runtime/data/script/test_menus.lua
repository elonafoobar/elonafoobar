local Event = Elona.require("Event")
local Chara = Elona.require("Chara")
local Item = Elona.require("Item")

local function setup()
   local item = Item.create(25, 25, "core.book_a", 1)
   item.param1 = 1

   local shop = Chara.create(23, 23, "core.shopkeeper")
   shop.character_role = 1007
   shop.shop_rank = 1000

   local putit = Chara.create(23, 23, "core.putit")
   putit:recruit_as_ally()

   putit = Chara.create(23, 23, "core.putit")
   putit:recruit_as_ally()

   putit = Chara.create(23, 23, "core.putit")
   putit:recruit_as_ally()

   Item.create(25, 24, "core.gene_machine", 1)

   local bar = Chara.create(28, 23, "core.bartender")
   bar.character_role = 9

   local informer = Chara.create(28, 23, "core.informer")
   informer.character_role = 8

   local slaver = Chara.create(28, 23, "core.elder")
   slaver.character_role = 17

   Item.create(25, 25, "core.scroll_of_return", 1)

   local altar = Item.create(24, 26, "core.altar", 1)
   altar.param1 = 2
   altar = Item.create(24, 27, "core.altar", 1)
   altar.param1 = 5

   Item.create(25, 25, "core.scroll_of_name", 10)
end

Event.register(Event.EventKind.ScriptLoaded, setup)
