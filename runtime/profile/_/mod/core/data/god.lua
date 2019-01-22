local Math = Elona.require("Math")

local function blessing(factor, max)
   return function(piety_point, faith)
      return Math.clamp(piety_point / factor, 1, max + faith / 10)
   end
end

local function secret_treasure(id)
   return { id = "core.secret_treasure", param1 = id, nostack = true }
end

data:define_type("god")
data:add_multi(
   "core.god",
   {
      {
         name = "mani",
         id = 1,
         servant = "core.android",
         items = {
            { id = "core.gemstone_of_mani", _only_once = true }
         },
         artifact = "core.winchester_premium",
         skills = {
            [12]  = blessing(400, 8),
            [13]  = blessing(300, 14),
            [154] = blessing(500, 8),
            [110] = blessing(250, 18),
            [159] = blessing(350, 8),
            [158] = blessing(250, 16),
            [176] = blessing(300, 10),
            [179] = blessing(350, 12),
         },
         offerings = {
            "core.laser_gun",
            "core.shot_gun",
            "core.blank_disc",
            "core.chip",
            "core.storage",
            "core.server",
            "core.microwave_oven",
            "core.camera",
            "core.training_machine",
            "core.computer",
            "core.machine",
            "core.machine_gun",
            "core.pistol",
         }
      },
      {
         name = "lulwy",
         id = 2,
         servant = "core.black_angel",
         items = {
            { id = "core.lulwys_gem_stone_of_god_speed", _only_once = true }
         },
         artifact = "core.wind_bow",
         skills = {
            [13]  = blessing(450, 10),
            [18]  = blessing(350, 30),
            [108] = blessing(350, 16),
            [109] = blessing(450, 12),
            [157] = blessing(450, 12),
            [174] = blessing(550, 8),
         },
         offerings = {
            "core.skull_bow",
            "core.crossbow",
            "core.short_bow",
            "core.long_bow",
         },
         special_actions = { 25 }
      },
      {
         name = "itzpalt",
         id = 3,
         servant = "core.exile",
         items = {
            secret_treasure(165),
         },
         artifact = "core.elemental_staff",
         skills = {
            [16]  = blessing(300, 18),
            [155] = blessing(350, 15),
            [50]  = blessing(50, 200),
            [51]  = blessing(50, 200),
            [52]  = blessing(50, 200),
         },
         offerings = {
            "core.long_staff",
            "core.staff",
         },
         special_actions = { 24 }
      },
      {
         name = "ehekatl",
         id = 4,
         servant = "core.black_cat",
         items = {
            secret_treasure(163),
         },
         artifact = "core.lucky_dagger",
         skills = {
            [17]  = blessing(250, 20),
            [19]  = blessing(100, 50),
            [173] = blessing(300, 15),
            [164] = blessing(350, 17),
            [185] = blessing(300, 12),
            [158] = blessing(450, 8),
         },
         offerings = {
            "core.fish_a",
            "core.sandborer",
            "core.cutlassfish",
            "core.tuna",
            "core.globefish",
            "core.salmon",
            "core.seabream",
            "core.manboo",
            "core.flatfish",
            "core.sardine",
            "core.moonfish",
            "core.bomb_fish",
         }
      },
      {
         name = "opatos",
         id = 5,
         servant = "core.golden_knight",
         items = {
            secret_treasure(164),
         },
         artifact = "core.gaia_hammer",
         skills = {
            [10]  = blessing(450, 11),
            [11]  = blessing(350, 16),
            [168] = blessing(350, 15),
            [153] = blessing(300, 16),
            [163] = blessing(350, 12),
            [174] = blessing(450, 8),
         },
         offerings = {
            "core.junk_stone",
            "core.raw_ore_of_diamond",
            "core.raw_ore_of_emerald",
            "core.raw_ore_of_mica",
            "core.raw_ore_of_rubynus",
            "core.gold_bar",
            "core.sun_crystal",
            "core.mana_crystal",
            "core.earth_crystal",
         }
      },
      {
         name = "jure",
         id = 6,
         servant = "core.defender",
         items = {
            { id = "core.jures_gem_stone_of_holy_rain", _only_once = true },
            secret_treasure(166),
         },
         artifact = "core.holy_lance",
         skills = {
            [15]  = blessing(300, 16),
            [154] = blessing(250, 18),
            [155] = blessing(400, 10),
            [161] = blessing(400, 9),
            [184] = blessing(450, 8),
            [174] = blessing(400, 10),
            [164] = blessing(400, 12),
         },
         offerings = {
            "core.junk_stone",
            "core.raw_ore_of_diamond",
            "core.raw_ore_of_emerald",
            "core.raw_ore_of_mica",
            "core.raw_ore_of_rubynus",
            "core.gold_bar",
            "core.sun_crystal",
            "core.mana_crystal",
            "core.earth_crystal",
         },
         special_actions = { 23 }
      },
      {
         name = "kumiromi",
         id = 7,
         servant = "core.cute_fairy",
         items = {
            { id = "core.kumiromis_gem_stone_of_rejuvenation", _only_once = true },
         },
         artifact = "core.kumiromi_scythe",
         skills = {
            [13]  = blessing(400, 8),
            [12]  = blessing(350, 12),
            [14]  = blessing(250, 16),
            [180] = blessing(300, 12),
            [178] = blessing(350, 10),
            [177] = blessing(350, 9),
            [150] = blessing(350, 8),
         },
         offerings = {
            "core.magical_seed",
            "core.gem_seed",
            "core.artifact_seed",
            "core.unknown_seed",
            "core.herb_seed",
            "core.fruit_seed",
            "core.vegetable_seed",
            "core.leccho",
            "core.melon",
            "core.cbocchi",
            "core.green_pea",
            "core.healthy_leaf",
            "core.imo",
            "core.lettuce",
            "core.sweet_potato",
            "core.radish",
            "core.carrot",
            "core.edible_wild_plant",
         }
      },
   }
)
