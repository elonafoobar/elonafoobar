local Item = Elona.require("Item")
local Event = Elona.require("Event")

local function setup()
   Item.create(25, 26, "kiroku.counter", 1)
end

Event.register(Event.EventKind.MapInitialized, setup)
