local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Rand = Elona.require("Rand")

local magic = {}

function magic.eye_of_insanity(m)
   GUI.txt(I18N.get("core.locale.magic.insanity", m.caster, m.target), "Purple")
   local roll = Rand.roll(m.dice_x, m.dice_y, m.dice_bonus) + 1
   m.target:modify_sanity(-Rand.rnd(roll))
   return true
end

return magic
