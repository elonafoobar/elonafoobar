require("tests/lua/support/minctest")

local Chara = ELONA.require("core.Chara")
local EatingEffects = ELONA.require("core.EatingEffects")

Testing.start_in_debug_map()
for name, func in pairs(EatingEffects) do
   lrun("test " .. name, function()
      lok(pcall(function() func(Chara.player()) end), "")
   end)
end
