local native = _ENV.native
local class, xtype = prelude.class, prelude.xtype

local Enums = {}

local Enum = class("core.Enums.Enum")

function Enum:__init(definitions)
   assert(type(definitions) == "table", "Enum.new: definitions must be a table.")

   for k, v in pairs(definitions) do
      assert(type(k) == "string", "Enum.new: name must be a string.")
      assert(xtype(v) == "integer", "Enum.new: value must be an integer.")
      self[k] = v
      self[v] = k
   end
end

function Enum:is_valid_value(value)
   return type(self[value]) == "string"
end

function Enum:is_valid_name(name)
   return xtype(self[name]) == "integer"
end

Enums.Enum = Enum

Enums.new_enum = Enum.new

--- @enum CurseState
---
--- The curse state of an item.
--- @usage local item = Item.create(10, 10, "core.putitoro", 3)
--- item.curse_state = Enums.CurseState.BLESSED
Enums.CurseState = Enums.new_enum {
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
Enums.IdentifyState = Enums.new_enum {
   UNIDENTIFIED = 0,
   PARTLY = 1,
   ALMOST = 2,
   COMPLETELY = 3,
}

--- @enum Quality
---
--- The quality of randomly generated equipment.
Enums.Quality = Enums.new_enum {
   NONE = 0,
   BAD = 1,
   GOOD = 2,
   GREAT = 3,
   MIRACLE = 4,
   GODLY = 5,
   SPECIAL = 6,
}

--- @enum Relationship
---
--- The relationship between characters
Enums.Relationship = Enums.new_enum {
   -- Your enemy. Mainly dungeon monsters.
   ENEMY = -3,

   -- A town citizen who you attacked once.
   UNFRIENDLY = -2,

   -- Not enemy, not your ally. E.g., little girl, cat, Gwen-chan
   NEUTRAL = -1,

   -- Friendly person. Town citizen.
   FRIENDLY = 0,

   -- Your ally.
   ALLY = 10,
}

-- TODO ldoc
Enums.SkillType = Enums.new_enum {
   STAT = 0,
   RESISTANCE = 1,
   TOWN_SKILL = 2, -- TODO rename
   SPELL = 3,
   SPACT = 4,
}

return Enums
