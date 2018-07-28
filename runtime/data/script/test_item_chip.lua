local Event = Elona.require("Event")
local Enums = Elona.require("Enums")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local Rand = Elona.require("Rand")

local shopkeeper = 1
local whom_dwell = 28

local short_pic = 378
local tall_pic = 429

local items = {503, 504, 255, 76, 75, 142, 276}

local function setup()
   local shop = Chara.create(23, 23, shopkeeper)
   shop.character_role = 1001
   shop.shop_rank = 12

   -- Let's Ragnarok!
   Chara.create(25, 23, whom_dwell)

   for i=0,5 do
      for j=0,10 do
         for k=0,2 do
            local id
            if Rand.coinflip() then
               id = items[Rand.rnd(7) + 1]
            else
               id = Rand.rnd(500)
            end
            local item = Item.create(25 - 2 + i, 25 - 5 + j, id, 1)

            if id == 503 or id == 504 then
               if Rand.coinflip() then
                  item.param1 = short_pic
               else
                  item.param1 = tall_pic
               end
            end
         end
      end
   end
end

Event.register(Event.EventKind.ScriptLoaded, setup)
