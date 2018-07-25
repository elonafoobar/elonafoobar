local Exports = Elona.require("core", "Exports")
local Chara = Elona.require("Chara")
local Enums = Elona.require("Enums")
local Event = Elona.require("Event")
local GUI = Elona.require("GUI")
local Input = Elona.require("Input")
local Item = Elona.require("Item")

local callbacks = {}
local max = 0
local last = 0

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, 733, 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag(Enums.CharaFlag.IsHungOnSandBag, true)
   return chara
end

local function prompt(chara)
   if chara.index ~= Store.map_local.runner.index then
      return
   end

   local index = Input.prompt_number("Which? ", max, last)
   if index then
      local cb = callbacks[index]
      if cb then
         last = index
         GUI.txt(cb.name .. " ", Enums.Color.Gold)
         cb.func(Chara.player())
      end
   else
      GUI.txt("Never mind.")
   end
end

local function setup()
   Store.map_local.runner = make_sandbag(25, 22, 242)

   local i = 1
   GUI.txt("Loading... ")
   for key, func in pairs(Exports.eating_effect) do
      GUI.txt(key .. " ")
      callbacks[i] = {func = func, name = key}
      max = i
      i = i + 1
   end
end

Event.register(Event.EventKind.ScriptLoaded, setup)
Event.register(Event.EventKind.CharaDamaged, prompt)
