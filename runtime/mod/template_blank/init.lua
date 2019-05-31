-- Your core here

local Event = Elona.require('Event')
local GUI = Elona.require('GUI')

Event.register('core.game_initialized', function(args)
   GUI.txt('Hello, World!')
end)
