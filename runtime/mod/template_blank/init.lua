-- Your core here

local Event = Elona.game.Event
local GUI = Elona.game.GUI

Event.register('core.game_initialized', function(args)
   GUI.txt('Hello, World!')
end)
