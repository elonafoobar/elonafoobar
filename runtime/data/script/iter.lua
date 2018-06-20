local Chara = Elona.require("Chara")
local Event = Elona.require("Event")
local Iter = Elona.require("Iter")
local Map = Elona.require("Map")

local function setup()
   local player_pos = Chara.player().position
   for pos in Iter.rectangle_iter(player_pos.x - 1, player_pos.y - 1,
                                  player_pos.x + 1, player_pos.y + 1) do
      if not (pos.x == player_pos.x and pos.y == player_pos.y) then
         local chara = Chara.create(pos.x, pos.y, 249)
         assert(chara:recruit_as_ally())
      end
   end

   for i=0, 100 do
      Chara.create(Map.random_pos(), 229)
   end
end


Event.register(Event.EventKind.MapInitialized, setup)
