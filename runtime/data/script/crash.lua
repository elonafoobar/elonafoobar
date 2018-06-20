local Event = Elona.require("Event")
local Chara = Elona.require("Chara")
local Map = Elona.require("Map")
local GUI = Elona.require("GUI")

Event.register(Event.EventKind.AllTurnsFinished, function()
                  Chara.create(Map.random_pos(), 3)
                  GUI.txt("Count: " .. tostring(Chara.count()) .. " ")
end)
