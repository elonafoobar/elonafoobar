local native = _ENV.native
local class, xtype = prelude.class, prelude.xtype
local Color = native.Graphics.Color

local Enums = {}

local Enum = class("core.Enums.Enum")

function Enum:__init(definitions)
   assert(type(definitions) == "table", "Enum.new: definitions must be a table.")

   for k, v in pairs(definitions) do
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

-- https://dlang.org/library/std/typecons/flag.html
Enums.BooleanFlag = Enum.new {
   YES = true,
   NO = false,
}

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

function Enums.CurseState.is_cursed(c)
   return c <= Enums.CurseState.CURSED
end

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

Enums.ColorPalette = Enums.new_enum {
   NONE         = Color.rgb(255, 255, 255),
   WHITE        = Color.rgb(255 - 1, 255, 255), -- TODO
   GREEN        = Color.rgb(175, 255, 175),
   RED          = Color.rgb(255, 155, 155),
   BLUE         = Color.rgb(175, 175, 255),
   ORANGE       = Color.rgb(255, 215, 175),
   YELLOW       = Color.rgb(255, 255, 175),
   GREY         = Color.rgb(155, 154, 153),
   PURPLE       = Color.rgb(185, 155, 215),
   CYAN         = Color.rgb(155, 205, 205),
   LIGHT_RED    = Color.rgb(255, 195, 185),
   GOLD         = Color.rgb(235, 215, 155),
   WHITE2       = Color.rgb(255, 255 - 1, 255), -- TODO
   LIGHT_BROWN  = Color.rgb(225, 215, 185),
   DARK_GREEN   = Color.rgb(105, 235, 105),
   LIGHT_GREY   = Color.rgb(205, 205, 205),
   PALE_RED     = Color.rgb(255, 225, 225),
   LIGHT_BLUE   = Color.rgb(225, 225, 255),
   LIGHT_PURPLE = Color.rgb(225, 195, 255),
   LIGHT_GREEN  = Color.rgb(215, 255, 215),
   YELLOW_GREEN = Color.rgb(210, 250, 160),
}

Enums.ItemCategory = Enums.new_enum {
   UNIDENTIFIED = 0,
   MELEE_WEAPON = 10000,
   HELM = 12000,
   SHIELD = 14000,
   ARMOR = 16000,
   BOOTS = 18000,
   BELT = 19000,
   CLOAK = 20000,
   GLOVES = 22000,
   RANGED_WEAPON = 24000,
   AMMO = 25000,
   RING = 32000,
   NECKLACE = 34000,
   POTION = 52000,
   SCROLL = 53000,
   SPELLBOOK = 54000,
   BOOK = 55000,
   ROD = 56000,
   FOOD = 57000,
   TOOL = 59000,
   FURNITURE = 60000,
   WELL = 60001,
   ALTAR = 60002,
   BODYPARTS = 62000,
   JUNK = 64000,
   GOLD_PIECE = 68000,
   PLATINUM = 69000,
   CHEST = 72000,
   ORE = 77000,
   TREE = 80000,
   TRAVELERS_FOOD = 91000,
   CARGO = 92000,
   BUG = 99999999,
}

function Enums.ItemCategory.is_equipment(c)
   return c <= 50000
end

Enums.DamageSource = Enums.new_enum {
   TRAP = -1,
   OVERCASTING = -2,
   STARVATION = -3,
   POISONING = -4,
   CURSE = -5,
   BACKPACK_WEIGHT = -6,
   FALL_FROM_STAIRS = -7,
   AUDIENCE = -8,
   BURN = -9,
   -- -10 used in unused casino codepath
   UNSEEN_HAND = -11,
   FOOD_POISONING = -12,
   BLOOD_LOSS = -13,
   ETHER_DISEASE = -14,
   ACID = -15,
   SHATTER = -16,
   ATOMIC_BOMB = -17,
   IRON_MAIDEN = -18,
   GUILLOTINE = -19,
   HANGING = -20,
   MOCHI = -21,
}

Enums.BuffType = Enums.new_enum {
   BUFF = 0,
   HEX = 1,
   FOOD = 2,
}

Enums.TurnResult = Enums.new_enum {
   NONE = 0,
   INITIALIZE_MAP = 1,
   PASS_ONE_TURN = 2,
   PASS_ONE_TURN_FREEZE_TIME = 3,
   TURN_BEGIN = 4,
   TURN_END = 5,
   PC_TURN = 6,
   PC_TURN_USER_ERROR = 7,
   EXIT_MAP = 8,
   PC_DIED = 9,
   FINISH_ELONA = 10,
}

Enums.AdditionalItemInfo = Enums.new_enum {
   NONE = 0,
   RESISTANCE = 1,
   MAINTENANCE_AND_AILMENT = 2,
}

function Enums.AdditionalItemInfo.next(v)
   return (v + 1) % 3
end

function Enums.AdditionalItemInfo.prev(v)
   return (3 + v - 1) % 3
end

Enums.Role = Enums.new_enum {
   NONE = 0,
   OTHER = 3,
   CITIZEN = 4,
   APPRAISER = 5,
   MAYER = 6,
   TRAINER = 7,
   INFORMER = 8,
   BARTENDER = 9,
   ARENA_MASTER = 10,
   PET_ARENA_MASTER = 11,
   HEALER = 12,
   ADVENTURER = 13,
   GUARD = 14,
   KING = 15,
   SHOP_GUARD = 16,
   SLAVE_MASTER = 17,
   MAID = 18,
   SISTER = 19,
   USER = 20,
   RETURNER = 21,
   HORSE_MASTER = 22,
   CARAVAN_MASTER = 23,

   -- Shopkeepers
   BLACKSMITH = 1001,
   FOOD_VENDOR = 1002,
   BAKERY = 1003,
   MAGIC_VENDOR = 1004,
   INNKEEPER = 1005,
   GENERAL_VENDOR = 1006,
   BLACKMARKET_VENDOR = 1007,
   GENERAL_STORE = 1008,
   TRADER = 1009,
   WANDERING_VENDOR = 1010,
   FIREARM_VENDOR = 1011,
   FURNITURE_VENDOR = 1012,
   DEED_VENDOR = 1013,
   FISHER = 1014,
   MOYER = 1015,
   MIRAL = 1016,
   DYE_VENDOR = 1017,
   SOUVENIR_VENDOR = 1018,
   LUNCH_VENDOR = 1019,
   SPELL_WRITER = 1020,
   FENCE = 1021,
   STREET_VENDOR = 1022,

   -- Guests
   GUEST_BEGGAR = 2000,
   GUEST_PUNK = 2001,
   GUEST_CITIZEN = 2002,
   GUEST_WANDERING_VENDOR = 2003,
   GUEST_TRAINER = 2005,
   GUEST_PRODUCER = 2006,
}

function Enums.Role.is_shopkeeper(role)
   return (1000 <= role and role < 2000) or role == Enums.Role.GUEST_WANDERING_VENDOR
end

function Enums.Role.is_guest(role)
   return 2000 <= role
end

Enums.OwnState = Enums.new_enum {
   -- Your lost items on death.
   LOST = -2,

   -- Your lost items on death. When you enter the map where you died, the
   -- lost items's `OwnState` are set to this value. If you do not pick
   -- them up, they will disappear in your second visit.
   LOST_DISAPPEARING = -1,

   -- Usual state. Items in character inventory or on dungeons.
   NONE = 0,

   -- Town's property. It cannot be obtained.
   -- TODO rename?
   TOWN = 1,

   -- It cannot be carried (e.g., wandering vendor's trunk)
   -- TODO rename?
   SHOP = 2,

   -- Built shelter.
   SHELTER = 3,

   -- Crops placed in Harvest quests.
   CROP = 4,

   -- Town's property, and not available for use.
   -- TODO rename?
   TOWN_SPECIAL = 5,

   -- Harvested crops. Defining it can fix one known bug in vanilla, but for
   -- now, I don't.
   -- CROP_HARVESTED = 6,
}

Enums.MenuResult = Enums.new_enum {
   PUSH = 0,
   CLOSE = 1,
}

return Enums
