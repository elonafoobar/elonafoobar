require "tests/lua/support/minctest"

local Chara = Elona.require("Chara")
local Exports = Elona.require("core", "Exports")

for name, func in pairs(Exports.eating_effect) do
   lrun("test " .. name, function()
           Testing.start_in_debug_map()
           lok(pcall(function() func(Chara.player()) end), "")
   end)
end
