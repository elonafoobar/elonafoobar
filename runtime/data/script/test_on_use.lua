local Enums = Elona.require("Enums")
local Event = Elona.require("Event")
local Item = Elona.require("Item")

local function setup()
   local item = Item.create(25, 26, "kiroku.counter", 1)
   item.identify_state = Enums.IdentifyState.Completely
end

Event.register(Event.EventKind.MapInitialized, setup)
