local Calc = Elona.require("Calc")
local Map = Elona.require("Map")
local Math = Elona.require("Math")
local Rand = Elona.require("Rand")
local table = Elona.require("table")

local function chara_filter_town(callbacks)
   return function()
      local opts = { level = 10, quality = "Bad", fltselect = 5 }

      local result = {}
      local level = Map.current_dungeon_level()
      local callback = callbacks[level]

      if callback then
         local result_ = callback()
         if result_ ~= nil and type(result_) == "table" then
            result = result_
         end
      end

      return table.merge(opts, result)
   end
end

--[[
   chara_filter:
   a function that returns a table with any of the following properties:
   id: string ID of the character to generate
   level: approximate level of the character to generate
   quality: approximate quality of the character to generate
   objlv: exact level of the character to generate
   fixlv: exact quality of the character to generate
   fltn: filter, to be used with fltn()
   fltselect: ?
   flttypemajor: ?
]]
data:define_type("map")
data:add_multi(
   "core.map",
   {
      {
         name = "test_world",
         id = 47,
         appearance = 0,
         map_type = "WorldMap",
         outer_map = 47,
         outer_map_position = { x = 26, y = 23 },
         entrance_type = "WorldMapPos",
         tile_set = "WorldMap",
         tile_type = 1,
         base_turn_cost = 50000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 0,
      },
      {
         name = "test_world_north_border",
         id = 48,
         appearance = 158,
         map_type = "Guild",
         outer_map = 47,
         outer_map_position = { x = 28, y = 1 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "south_tyris",
         id = 44,
         appearance = 0,
         map_type = "WorldMap",
         outer_map = 44,
         outer_map_position = { x = 26, y = 23 },
         entrance_type = "WorldMapPos",
         tile_set = "WorldMap",
         tile_type = 1,
         base_turn_cost = 50000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 0,
      },
      {
         name = "south_tyris_north_border",
         id = 45,
         appearance = 158,
         map_type = "Guild",
         outer_map = 44,
         outer_map_position = { x = 42, y = 1 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "the_smoke_and_pipe",
         id = 46,
         appearance = 159,
         map_type = "Guild",
         outer_map = 44,
         outer_map_position = { x = 39, y = 13 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "north_tyris",
         id = 4,
         appearance = 0,
         map_type = "WorldMap",
         outer_map = 4,
         outer_map_position = { x = 26, y = 23 },
         entrance_type = "WorldMapPos",
         tile_set = "WorldMap",
         tile_type = 1,
         base_turn_cost = 50000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 0,
      },
      {
         name = "vernis",
         id = 5,
         appearance = 132,
         map_type = "Town",
         outer_map_position = { x = 26, y = 23 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 999,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 1,

         chara_filter = chara_filter_town(
            {
               [1] = function()
                  if Rand.one_in(2) then
                     return { id = "core.miner" }
                  end

                  return nil
               end
            }
         )
      },
      {
         name = "yowyn",
         id = 12,
         appearance = 142,
         map_type = "Town",
         outer_map_position = { x = 43, y = 32 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 999,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 2,

         chara_filter = chara_filter_town(
            {
               [1] = function()
                  if Rand.one_in(2) then
                     return { id = "core.farmer" }
                  end

                  return nil
               end
            }
         )
      },
      {
         name = "palmia",
         id = 15,
         appearance = 136,
         map_type = "Town",
         outer_map_position = { x = 53, y = 24 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 3,

         chara_filter = chara_filter_town(
            {
               [1] = function()
                  if Rand.one_in(3) then
                     return { id = "core.noble" }
                  end

                  return nil
               end
            }
         )
      },
      {
         name = "derphy",
         id = 14,
         appearance = 142,
         map_type = "Town",
         outer_map_position = { x = 14, y = 35 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 999,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 4,

         chara_filter = chara_filter_town(
            {
               [1] = function()
                  if Rand.one_in(3) then
                     return { id = "core.rogue" }
                  elseif Rand.one_in(2) then
                     return { id = "core.prostitute" }
                  end
               end,

               -- Thieves guild
               [3] = function()
                  return { id = "core.thief_guild_member" }
               end
            }
         )
      },
      {
         name = "port_kapul",
         id = 11,
         appearance = 132,
         map_type = "Town",
         outer_map_position = { x = 3, y = 15 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 999,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 5,

         chara_filter = chara_filter_town(
            {
               -- Fighters guild
               [3] = function()
                  return { id = "core.fighter_guild_member" }
               end
            }
         )
      },
      {
         name = "noyel",
         id = 33,
         appearance = 156,
         map_type = "Town",
         outer_map_position = { x = 89, y = 14 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 6,

         villagers_make_snowmen = true,
         chara_filter = chara_filter_town(
            {
               [1] = function()
                  if Rand.one_in(3) then
                     return { id = "core.sister" }
                  end
               end
            }
         )
      },
      {
         name = "lumiest",
         id = 36,
         appearance = 132,
         map_type = "Town",
         outer_map_position = { x = 61, y = 32 },
         outer_map = 4,
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 999,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         quest_town_id = 7,

         chara_filter = chara_filter_town(
            {
               [1] = function()
                  if Rand.one_in(3) then
                     return { id = "core.artist" }
                  end
               end,

               -- Mages guild
               [3] = function()
                  return { id = "core.mage_guild_member" }
               end
            }
         )
      },
      {
         name = "fields",
         id = 2,
         appearance = 0,
         map_type = "Field",
         outer_map = 4,
         outer_map_position = { x = 0, y = 0 },
         entrance_type = "Center",
         tile_set = "Normal",
         tile_type = 4,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = true,
         default_ai_calm = 0,
      },
      {
         name = "your_home",
         id = 7,
         map_type = "PlayerOwned",
         entrance_type = "South",
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 10,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,

         -- Only set when not yet upgraded.
         appearance = 138,
         outer_map_position = { x = 22, y = 21 },
         tile_set = "Normal",
         tile_type = 3,
         outer_map = 4,

         -- Special case due to Your Home being able to change
         -- position/appearance, so those properties shouldn't be
         -- overwritten when all areas are refreshed.
         is_fixed = false,
      },
      {
         name = "show_house",
         id = 35,
         map_type = "Temporary",
         outer_map = 4,
         outer_map_position = { x = 35, y = 27 },
         entrance_type = "South",
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = true,
         default_ai_calm = 1,
         appearance = 158,
         tile_set = "Normal",
         tile_type = 3,

         reveals_fog = true,
         prevents_monster_ball = true,
      },
      {
         name = "arena",
         id = 6,
         appearance = 0,
         map_type = "Temporary",
         outer_map = 4,
         outer_map_position = { x = 22, y = 21 },
         entrance_type = "Center",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = true,
         default_ai_calm = 0,

         reveals_fog = true,
         prevents_domination = true,
         prevents_monster_ball = true,
      },
      {
         name = "pet_arena",
         id = 40,
         appearance = 0,
         map_type = "Temporary",
         outer_map = 4,
         outer_map_position = { x = 23, y = 21 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = true,
         default_ai_calm = 0,

         reveals_fog = true,
         prevents_teleport = true,
         prevents_domination = true,
         prevents_monster_ball = true,
      },
      {
         name = "quest",
         id = 13,
         appearance = 0,
         map_type = "Temporary",
         outer_map = 4,
         outer_map_position = { x = 22, y = 21 },
         entrance_type = "Center",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = true,
         default_ai_calm = 0,

         shows_floor_count_in_name = true,
         prevents_building_shelter = true,
      },
      {
         name = "lesimas",
         id = 3,
         appearance = 139,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 23, y = 29 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 45,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         can_return_to = true,
         shows_floor_count_in_name = true,
         chara_filter = function()
            local opts = { objlv = Calc.calc_objlv(Map.current_dungeon_level()), quality = "Bad" }

            if Map.current_dungeon_level() < 4 and opts.objlv > 5 then
               opts.objlv = 5
            end

            return opts
         end
      },
      {
         name = "the_void",
         id = 42,
         appearance = 139,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 81, y = 51 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 50,
         deepest_level = 99999999,
         is_indoor = true,
         is_generated_every_time = true,
         default_ai_calm = 0,

         can_return_to = true,
         prevents_domination = true,
         chara_filter = function()
            return { level = Math.modf(Map.current_dungeon_level(), 50) + 5, quality = "Bad" }
         end
      },
      {
         name = "tower_of_fire",
         id = 16,
         appearance = 145,
         map_type = "DungeonTower",
         outer_map = 4,
         outer_map_position = { x = 43, y = 4 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 15,
         deepest_level = 18,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            return { level = Map.current_dungeon_level(), quality = "Bad", fltn = "fire" }
         end
      },
      {
         name = "crypt_of_the_damned",
         id = 17,
         appearance = 141,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 38, y = 20 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 25,
         deepest_level = 30,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            return { level = Map.current_dungeon_level(), quality = "Bad", fltn = "undead" }
         end
      },
      {
         name = "ancient_castle",
         id = 18,
         appearance = 144,
         map_type = "DungeonCastle",
         outer_map = 4,
         outer_map_position = { x = 26, y = 44 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 17,
         deepest_level = 22,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            local opts = { level = Map.current_dungeon_level(), quality = "Bad" }

            if Rand.one_in(2) then
               opts.fltn = "man"
            end

            return opts
         end
      },
      {
         name = "dragons_nest",
         id = 19,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 13, y = 32 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 30,
         deepest_level = 33,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            return { level = Map.current_dungeon_level(), quality = "Bad" }
         end
      },
      {
         name = "mountain_pass",
         id = 26,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 64, y = 43 },
         entrance_type = "StairDown",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 25,
         deepest_level = 29,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,
      },
      {
         name = "puppy_cave",
         id = 27,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 29, y = 24 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 2,
         deepest_level = 5,
         is_indoor = true,
         is_generated_every_time = true,
         default_ai_calm = 0,
      },
      {
         name = "minotaurs_nest",
         id = 38,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 43, y = 39 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 23,
         deepest_level = 27,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            local opts = { level = Map.current_dungeon_level(), quality = "Bad" }

            if Rand.one_in(2) then
               opts.fltn = "mino"
            end

            return opts
         end
      },
      {
         name = "yeeks_nest",
         id = 28,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 38, y = 31 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 5,
         deepest_level = 5,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            local opts = { level = Map.current_dungeon_level(), quality = "Bad" }

            if Rand.one_in(2) then
               opts.fltn = "yeek"
            end

            return opts
         end
      },
      {
         name = "pyramid",
         id = 37,
         appearance = 160,
         map_type = "Dungeon",
         outer_map = 4,
         outer_map_position = { x = 4, y = 11 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 0,
         base_turn_cost = 10000,
         danger_level = 20,
         deepest_level = 21,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         prevents_teleport = true,
         chara_filter = function()
            return { level = Map.current_dungeon_level(), quality = "Bad", flttypemajor = 13 }
         end
      },
      {
         name = "lumiest_graveyard",
         id = 10,
         appearance = 141,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 74, y = 31 },
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 4,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,

         chara_filter = function()
            return { level = 20, quality = "Bad", fltselect = 4 }
         end
      },
      {
         name = "truce_ground",
         id = 20,
         appearance = 147,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 51, y = 9 },
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 4,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,

         chara_filter = function()
            return { level = 20, quality = "Bad", fltselect = 4 }
         end
      },
      {
         name = "jail",
         id = 41,
         appearance = 161,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 28, y = 37 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 12,
         base_turn_cost = 100000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = true,
         default_ai_calm = 0,

         prevents_teleport = true,
         prevents_return = true,
         prevents_random_events = true,
      },
      {
         name = "cyber_dome",
         id = 21,
         appearance = 148,
         map_type = "Guild",
         outer_map = 4,
         outer_map_position = { x = 21, y = 27 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 8,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,

         chara_filter = function()
            return { level = 10, quality = "Bad", fltn = "sf" }
         end
      },
      {
         name = "larna",
         id = 25,
         appearance = 142,
         map_type = "Guild",
         outer_map = 4,
         outer_map_position = { x = 64, y = 47 },
         entrance_type = "Custom",
         tile_set = "Normal",
         tile_type = 9,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,

         can_return_to = true,
      },
      {
         name = "miral_and_garoks_workshop",
         id = 34,
         appearance = 157,
         map_type = "Guild",
         outer_map_position = { x = 88, y = 25 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
         outer_map = 4,

         reveals_fog = true,
      },
      {
         name = "mansion_of_younger_sister",
         id = 29,
         appearance = 162,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 18, y = 2 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,

         can_return_to = true,
         villagers_make_snowmen = true,
      },
      {
         name = "embassy",
         id = 32,
         appearance = 155,
         map_type = "Guild",
         outer_map = 4,
         outer_map_position = { x = 53, y = 21 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,

         reveals_fog = true,
      },
      {
         name = "north_tyris_south_border",
         id = 43,
         appearance = 158,
         map_type = "Guild",
         outer_map = 4,
         outer_map_position = { x = 27, y = 52 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 2,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_indoor = false,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "fort_of_chaos_beast",
         id = 22,
         appearance = 149,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 13, y = 43 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 10000,
         danger_level = 33,
         deepest_level = 33,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "fort_of_chaos_machine",
         id = 23,
         appearance = 149,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 51, y = 32 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 10000,
         danger_level = 33,
         deepest_level = 33,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "fort_of_chaos_collapsed",
         id = 24,
         appearance = 149,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 35, y = 10 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 10000,
         danger_level = 33,
         deepest_level = 33,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,
      },
      {
         name = "shelter",
         id = 30,
         appearance = 0,
         map_type = "PlayerOwned",
         outer_map = 4,
         outer_map_position = { x = 35, y = 10 },
         entrance_type = "StairUp",
         tile_set = "Normal",
         tile_type = 100,
         base_turn_cost = 1000000,
         danger_level = -999999,
         deepest_level = 999999,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 1,

         reveals_fog = true,
         prevents_return = true,
         prevents_building_shelter = true,
         prevents_random_events = true,
      },
      {
         name = "test_site",
         id = 9,
         appearance = 0,
         map_type = "Shelter",
         outer_map = 4,
         outer_map_position = { x = 20, y = 20 },
         entrance_type = "Center",
         tile_set = "Normal",
         tile_type = 4,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 45,
         is_indoor = false,
         is_generated_every_time = true,
         default_ai_calm = 0,
      },
   }
)

local function player_owned(opts)
   local new_opts = {
         is_home = true,

         -- Dummy; they are overwritten when you build the building.
         map_type = "PlayerOwned",
         outer_map = 0,
         outer_map_position = { x = 0, y = 0 },
         entrance_type = "South",
         tile_set = "Normal",
         tile_type = 3,
         base_turn_cost = 10000,
         danger_level = 1,
         deepest_level = 1,
         is_generated_every_time = false,
         default_ai_calm = 0,
   }

   return table.merge(new_opts, opts)
end

-- These maps can be player-owned.
data:add_multi(
   "core.map",
   {
      player_owned {
         name = "museum",
         id = 101,
         appearance = 151,
         is_indoor = true,
         deed = "core.deed_of_museum"
      },
      player_owned {
         name = "shop",
         id = 102,
         is_fixed = false,

         -- Dummy; they are overwritten when you build the building.
         is_indoor = true,
         appearance = 150,
         deed = "core.deed_of_shop"
      },
      player_owned {
         name = "crop",
         id = 103,
         is_fixed = false,

         -- Dummy; they are overwritten when you build the building.
         appearance = 152,
         is_indoor = false,
         deed = "core.deed_of_farm"
      },
      player_owned {
         name = "storage_house",
         id = 104,
         is_fixed = false,

         -- Dummy; they are overwritten when you build the building.
         appearance = 153,
         is_indoor = true,
         deed = "core.deed_of_storage_house"
      },
      player_owned {
         name = "ranch",
         id = 31,
         is_fixed = false,

         -- Dummy; they are overwritten when you build the building.
         appearance = 154,
         is_indoor = false,
         default_ai_calm = 1,
         deed = "core.deed_of_ranch"
      },
      player_owned {
         name = "your_dungeon",
         id = 39,
         is_fixed = false,

         -- Dummy; they are overwritten when you build the building.
         appearance = 138,
         is_indoor = true,
         default_ai_calm = 1,
         deed = "core.deed_of_dungeon"
      },
      {
         name = "random_dungeon",
         id = 8,
         is_fixed = false,

         -- Dummy; they are overwritten when a dungeon is generated.
         is_indoor = true,
         appearance = 138,
         base_turn_cost = 10000,
         map_type = "PlayerOwned",
         outer_map_position = { x = 0, y = 0 },
         deepest_level = 1,
         entrance_type = "South",
         is_generated_every_time = false,
         default_ai_calm = 1,
         danger_level = 1,
         tile_type = 3,
         tile_set = "Normal",
         outer_map = 4,
      },
})
