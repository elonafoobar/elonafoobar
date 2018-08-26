local Event = Elona.require("Event")
local Chara = Elona.require("Chara")

local function setup()
   Chara.create(25, 24, "core.caravan_master")
end

Event.register(Event.EventKind.GameInitialized, setup)
