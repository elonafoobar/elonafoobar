local data = { _table = {} }
function data:add_multi(tbl)
   for _, v in ipairs(tbl) do
      self:add(v)
   end
end
function data:add(data)
   self._table[data.id] = data
end



local Calc = Elona.require("Calc")
local Map = Elona.require("Map")
local Math = Elona.require("Math")
local Rand = Elona.require("Rand")
local table = Elona.require("table")

local map = require("data/map/static")

local function chara_filter_town(callbacks)
   return function()
      local opts = { level = 10, quality = "Bad", fltselect = 5 }

      if callbacks == nil then
         return opts
      end

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
   generator:
    a function taking an object of type LuaMapGenerator which
    generates the map. See the mapgen/ folder for examples.

]]
data:add_multi(
   {
      {
         id = "test_world",
         legacy_id = 47,
         appearance = 0,
         map_type = "WorldMap",
         outer_map = "core.test_world",
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
         id = "test_world_north_border",
         legacy_id = 48,
         appearance = 158,
         map_type = "Guild",
         outer_map = "core.test_world",
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

         chara_filter = chara_filter_town(),
      },
      {
         id = "south_tyris",
         legacy_id = 44,
         appearance = 0,
         map_type = "WorldMap",
         outer_map = "core.south_tyris",
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
         id = "south_tyris_north_border",
         legacy_id = 45,
         appearance = 158,
         map_type = "Guild",
         outer_map = "core.south_tyris",
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

         chara_filter = chara_filter_town(),
      },
      {
         id = "the_smoke_and_pipe",
         legacy_id = 46,
         appearance = 159,
         map_type = "Guild",
         outer_map = "core.south_tyris",
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

         chara_filter = chara_filter_town(),
      },
      {
         id = "north_tyris",
         legacy_id = 4,
         appearance = 0,
         map_type = "WorldMap",
         outer_map = "core.north_tyris",
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
         id = "vernis",
         legacy_id = 5,
         appearance = 132,
         map_type = "Town",
         outer_map_position = { x = 26, y = 23 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "vernis",

         chara_filter = chara_filter_town {
            [1] = function()
               if Rand.one_in(2) then
                  return { id = "core.miner" }
               end

               return nil
            end
         }
      },
      {
         id = "yowyn",
         legacy_id = 12,
         appearance = 142,
         map_type = "Town",
         outer_map_position = { x = 43, y = 32 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "yowyn",

         chara_filter = chara_filter_town {
            [1] = function()
               if Rand.one_in(2) then
                  return { id = "core.farmer" }
               end

               return nil
            end
         }
      },
      {
         id = "palmia",
         legacy_id = 15,
         appearance = 136,
         map_type = "Town",
         outer_map_position = { x = 53, y = 24 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "palmia",

         chara_filter = chara_filter_town {
            [1] = function()
               if Rand.one_in(3) then
                  return { id = "core.noble" }
               end

               return nil
            end
         }
      },
      {
         id = "derphy",
         legacy_id = 14,
         appearance = 142,
         map_type = "Town",
         outer_map_position = { x = 14, y = 35 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "rogueden",

         chara_filter = chara_filter_town {
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

      },
      {
         id = "port_kapul",
         legacy_id = 11,
         appearance = 132,
         map_type = "Town",
         outer_map_position = { x = 3, y = 15 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "kapul",

         chara_filter = chara_filter_town {
            -- Fighters guild
            [3] = function()
               return { id = "core.fighter_guild_member" }
            end
         }
      },
      {
         id = "noyel",
         legacy_id = 33,
         appearance = 156,
         map_type = "Town",
         outer_map_position = { x = 89, y = 14 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "noyel",

         villagers_make_snowmen = true,
         chara_filter = chara_filter_town {
            [1] = function()
               if Rand.one_in(3) then
                  return { id = "core.sister" }
               end
            end
         }
      },
      {
         id = "lumiest",
         legacy_id = 36,
         appearance = 132,
         map_type = "Town",
         outer_map_position = { x = 61, y = 32 },
         outer_map = "core.north_tyris",
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
         quest_custom_map = "lumiest",

         chara_filter = chara_filter_town {
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
      },
      {
         id = "fields",
         legacy_id = 2,
         appearance = 0,
         map_type = "Field",
         outer_map = "core.north_tyris",
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
         id = "your_home",
         legacy_id = 7,
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
         outer_map = "core.north_tyris",

         -- Special case due to Your Home being able to change
         -- position/appearance, so those properties shouldn't be
         -- overwritten when all areas are refreshed.
         is_fixed = false,
      },
      {
         id = "show_house",
         legacy_id = 35,
         map_type = "Temporary",
         outer_map = "core.north_tyris",
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
         id = "arena",
         legacy_id = 6,
         appearance = 0,
         map_type = "Temporary",
         outer_map = "core.north_tyris",
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
         id = "pet_arena",
         legacy_id = 40,
         appearance = 0,
         map_type = "Temporary",
         outer_map = "core.north_tyris",
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
         id = "quest",
         legacy_id = 13,
         appearance = 0,
         map_type = "Temporary",
         outer_map = "core.north_tyris",
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
         id = "lesimas",
         legacy_id = 3,
         appearance = 139,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "the_void",
         legacy_id = 42,
         appearance = 139,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "tower_of_fire",
         legacy_id = 16,
         appearance = 145,
         map_type = "DungeonTower",
         outer_map = "core.north_tyris",
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
         id = "crypt_of_the_damned",
         legacy_id = 17,
         appearance = 141,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "ancient_castle",
         legacy_id = 18,
         appearance = 144,
         map_type = "DungeonCastle",
         outer_map = "core.north_tyris",
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
         id = "dragons_nest",
         legacy_id = 19,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "mountain_pass",
         legacy_id = 26,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "puppy_cave",
         legacy_id = 27,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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

         generator = map.puppy_cave,
      },
      {
         id = "minotaurs_nest",
         legacy_id = 38,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "yeeks_nest",
         legacy_id = 28,
         appearance = 146,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "pyramid",
         legacy_id = 37,
         appearance = 160,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
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
         id = "lumiest_graveyard",
         legacy_id = 10,
         appearance = 141,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
         id = "truce_ground",
         legacy_id = 20,
         appearance = 147,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
         id = "jail",
         legacy_id = 41,
         appearance = 161,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
         id = "cyber_dome",
         legacy_id = 21,
         appearance = 148,
         map_type = "Guild",
         outer_map = "core.north_tyris",
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
         id = "larna",
         legacy_id = 25,
         appearance = 142,
         map_type = "Guild",
         outer_map = "core.north_tyris",
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
         chara_filter = chara_filter_town(),
      },
      {
         id = "miral_and_garoks_workshop",
         legacy_id = 34,
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
         outer_map = "core.north_tyris",

         reveals_fog = true,
         chara_filter = chara_filter_town(),
      },
      {
         id = "mansion_of_younger_sister",
         legacy_id = 29,
         appearance = 162,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
         is_hidden_in_world_map = true,
      },
      {
         id = "embassy",
         legacy_id = 32,
         appearance = 155,
         map_type = "Guild",
         outer_map = "core.north_tyris",
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
         chara_filter = chara_filter_town(),
      },
      {
         id = "north_tyris_south_border",
         legacy_id = 43,
         appearance = 158,
         map_type = "Guild",
         outer_map = "core.north_tyris",
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

         chara_filter = chara_filter_town(),
      },
      {
         id = "fort_of_chaos_beast",
         legacy_id = 22,
         appearance = 149,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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

         chara_filter = chara_filter_town(),
      },
      {
         id = "fort_of_chaos_machine",
         legacy_id = 23,
         appearance = 149,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
         id = "fort_of_chaos_collapsed",
         legacy_id = 24,
         appearance = 149,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
         id = "shelter",
         legacy_id = 30,
         appearance = 0,
         map_type = "PlayerOwned",
         outer_map = "core.north_tyris",
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
         id = "test_site",
         legacy_id = 9,
         appearance = 0,
         map_type = "Shelter",
         outer_map = "core.north_tyris",
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
      is_fixed = false,

      -- Dummy; they are overwritten when you build the building.
      is_indoor = true,
      appearance = 150,
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
      outer_map = "core.north_tyris",
   }

   return table.merge(new_opts, opts)
end

local function chara_filter_museum_shop()
   local fltselect
   if Rand.one_in(1) then
      fltselect = 5
   else
      fltselect = 7
   end

   return { level = 100, quality = "Bad", fltselect = fltselect }
end

-- These maps are player-created.
data:add_multi(
   {
      player_owned {
         id = "museum",
         legacy_id = 101,
         appearance = 151,
         is_indoor = true,
         chara_filter = chara_filter_museum_shop,
         deed = "core.deed_of_museum",
      },
      player_owned {
         id = "shop",
         legacy_id = 102,
         is_indoor = true,
         appearance = 150,
         chara_filter = chara_filter_museum_shop,
         deed = "core.deed_of_shop",
      },
      player_owned {
         id = "crop",
         legacy_id = 103,
         appearance = 152,
         is_indoor = false,
         deed = "core.deed_of_farm",
      },
      player_owned {
         id = "storage_house",
         legacy_id = 104,
         appearance = 153,
         is_indoor = true,
         deed = "core.deed_of_storage_house",
      },
      player_owned {
         id = "ranch",
         legacy_id = 31,
         appearance = 154,
         is_indoor = false,
         default_ai_calm = 1,
         deed = "core.deed_of_ranch",
      },
      player_owned {
         id = "your_dungeon",
         legacy_id = 39,
         appearance = 138,
         is_indoor = true,
         default_ai_calm = 1,
         deed = "core.deed_of_dungeon",
      },
      {
         id = "random_dungeon",
         legacy_id = 8,
         entrance_type = "StairUp",
         tile_set = "Normal",
         appearance = 138,
         base_turn_cost = 10000,
         is_indoor = true,
         is_generated_every_time = false,
         default_ai_calm = 0,

         chara_filter = function()
            return { level = Map.data.current_dungeon_level, quality = "Bad" }
         end,

         -- The following fields are required for loading the data but
         -- ignored. They are replaced on generation.
         appearance = 133,
         tile_type = 1,
         map_type = "Dungeon",
         outer_map = "core.north_tyris",
         outer_map_position = { x = 0, y = 0 },
         danger_level = 1,
         deepest_level = 1,
      },
})



return { ["core.map"] = data._table }
