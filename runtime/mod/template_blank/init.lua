-- Your core here

local Event = require("game.Event")
local GUI = require("game.GUI")

Event.register('core.game_initialized', function(args)
   GUI.txt('Hello, World!')
end)
