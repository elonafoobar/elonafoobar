local Event = Elona.require("Event")
local Chara = Elona.require("Chara")
local Map = Elona.require("Map")

local function setup()
   for i=0, 40 do
      Chara.create(Map.random_pos(), 248)
   end
end

Event.register(Event.EventKind.MapInitialized, setup)
