require "tests/lua/support/minctest"

local Chara = Elona.require("Chara")
local Exports = Elona.require("core", "Exports")

Testing.start_in_debug_map()
for name, func in pairs(Exports.eating_effect) do
   lrun("test " .. name, function()
      lok(pcall(function() func(Chara.player()) end), "")
   end)
end
