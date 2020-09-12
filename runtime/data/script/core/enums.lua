local Enums = {}


local function new_enum(definitions)
   local enum = {}
   for k, v in pairs(definitions) do
      enum[k] = v
      enum[v] = k
   end
   return enum
end

Enums.new_enum = new_enum



--- @enum CurseState
---
--- The curse state of an item.
--- @usage local item = Item.create(10, 10, "core.putitoro", 3)
--- item.curse_state = "Blessed"
Enums.CurseState = new_enum {
   doomed = -2,
   cursed = -1,
   none = 0,
   blessed = 1,
}



--- @enum IdentifyState
---
--- The identify state of an item.
--- @usage local item = Item.create(10, 10, "core.putitoro", 3)
--- item.identify_state = "Completely"
Enums.IdentifyState = new_enum {
   unidentified = 0,
   partly = 1,
   almost = 2,
   completely = 3,
}



--- @enum Quality
---
--- The quality of randomly generated equipment.
Enums.Quality = new_enum {
   none = 0,
   bad = 1,
   good = 2,
   great = 3,
   miracle = 4,
   godly = 5,
   special = 6,
}



return Enums
