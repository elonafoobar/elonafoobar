local Event = Elona.require("Event")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")

local function iter()
   for i, chara in Chara.iter(0, 10) do
      if chara.index == 0 then
         GUI.txt("Player found: " .. chara.name .. " ")
      end
   end
end

Event.register(Event.EventKind.CharaMoved, iter)
