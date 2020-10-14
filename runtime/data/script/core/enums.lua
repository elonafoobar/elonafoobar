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
--- item.curse_state = Enums.CurseState.BLESSED
Enums.CurseState = new_enum {
   DOOMED = -2,
   CURSED = -1,
   NONE = 0,
   BLESSED = 1,
}

--- @enum IdentifyState
---
--- The identify state of an item.
--- @usage local item = Item.create(10, 10, "core.putitoro", 3)
--- item.identify_state = Enums.IdentifyState.COMPLETELY
Enums.IdentifyState = new_enum {
   UNIDENTIFIED = 0,
   PARTLY = 1,
   ALMOST = 2,
   COMPLETELY = 3,
}

--- @enum Quality
---
--- The quality of randomly generated equipment.
Enums.Quality = new_enum {
   NONE = 0,
   BAD = 1,
   GOOD = 2,
   GREAT = 3,
   MIRACLE = 4,
   GODLY = 5,
   SPECIAL = 6,
}

return Enums
