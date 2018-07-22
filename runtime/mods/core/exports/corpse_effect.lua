local GUI = Elona.require("GUI")
local Enums = Elona.require("Enums")

local corpse_effect = {}

function corpse_effect.test(chara)
   GUI.txtef(Enums.Color.Gold)
   GUI.txt("Yes, it works. " .. chara.name)
end

return corpse_effect
