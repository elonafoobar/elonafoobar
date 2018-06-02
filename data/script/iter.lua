local Event = Elona.require("Event")
local Chara = Elona.require("Chara")
local Enums = Elona.require("Enums")

local function setup()
   local chara = Chara.player()
   chara:damage_hp(999999, Enums.DamageSource.Shatter)
end

Event.register(Event.EventKind.AllTurnsFinished, setup)
