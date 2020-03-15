-- Your core here

local Event = ELONA.require("core.Event")
local GUI = ELONA.require("core.GUI")

Event.register('core.game_initialized', function(args)
   GUI.txt('Hello, World!')
end)
