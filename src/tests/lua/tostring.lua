require_relative("tests/lua/support/minctest")

local Chara = require("game.Chara")
local Item = require("game.Item")
local World = require("game.World")

Testing.start_in_debug_map()

lrun("test LuaPosition:tostring", function()
   local pos = Chara.player().position
   print(tostring(pos), "(25, 25)")
   local pos2 = LuaPosition.new(52, 12)
   print(tostring(pos2), "(52, 12)")
end)

lrun("test LuaDateTime:tostring", function()
   local datetime = World.data.date
   print(tostring(datetime), "517/12/30 01:10:00")
end)
