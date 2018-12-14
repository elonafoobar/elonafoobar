local Chara = Elona.require("Chara")
local I18N = Elona.require("I18N")
local Item = Elona.require("Item")
local Map = Elona.require("Map")
local Rand = Elona.require("Rand")
local World = Elona.require("World")
local table = Elona.require("table")

local maps = {}

local TILE_DEFAULT = 396

local function create_items(items)
   for _, data in ipairs(items) do
      local id, x, y, opts = table.unpack(data)

      local item = Item.create(x, y, id, 0)

      if opts then
         for k, v in pairs(opts) do
            item[k] = v
         end
      end
   end
end

local function create_charas(charas)
   for _, data in ipairs(charas) do
      local id, x, y, opts = table.unpack(data)

      local count = opts["_count"] or 1

      for i=0,count do
         local chara = Chara.create(x, y, id)

         if opts then
            for k, v in pairs(opts) do
               if k == "_name" then
                  chara.name = I18N.get(v, chara.name)
               else
                  chara[k] = v
               end
            end
         end
      end
   end
end

function maps.shelter(generator)
   if Map.current_dungeon_level() == 1 then
      generator.load_custom("shelter_2")
      Map.data.refresh_type = 0
      Map.data.type = "Shelter"
   else
      generator.load_custom("shelter_1")
      Map.data.is_user_map = false
   end

   Map.data.max_crowd_density = 0
   Map.data.max_item_count = 5
   Map.data.bgm = "core.mcLonely"

   generator.place_player()
end

function maps.nefia(generator)
   generator.generate_nefia()
   if Map.current_dungeon_level() == Map.deepest_level then
      World.add_event(4)
   end
end

function maps.museum(generator)
   generator.load_custom("museum_1")

   Map.data.is_user_map = false
   Map.data.bgm = "core.mcTown3"

   generator.place_player()

   local items = {
      { "core.book_b", 15, 17, { param1 = 4 } }
   }

   create_items(items)
end

function maps.shop(generator)
   generator.load_custom("shop_1")

   Map.data.bgm = "core.mcTown3"
   Map.data.max_item_count = 10

   generator.place_player()

   local items = {
      { "core.book_b", 17, 14, { param1 = 8 } },
      { "core.shop_strongbox", 19, 10, { count = 5 } },
      { "core.register", 17, 11 }
   }

   create_items(items)
end

function maps.crop(generator)
   generator.load_custom("crop_1")

   Map.data.bgm = "core.mcLonely"
   Map.data.max_item_count = 80
   Map.data.is_user_map = false

   generator.place_player()

   local items = {
      { "core.book_b", 14, 5, { param1 = 9 } }
   }

   create_items(items)
end

function maps.ranch(generator)
   generator.load_custom("ranch_1")

   Map.data.bgm = "core.mcLonely"
   Map.data.max_item_count = 80
   Map.data.is_user_map = false

   generator.place_player()

   local items = {
      { "core.book_b", 23, 8, { param1 = 11 } },
      { "core.register", 22, 6 },
   }

   create_items(items)
end

function maps.your_dungeon(generator)
   generator.load_custom("dungeon1")

   Map.data.bgm = "core.mcLonely"
   Map.data.max_item_count = 350
   Map.data.is_user_map = false

   generator.place_player()

   local items = {
      { "core.book_b", 39, 54, { param1 = 15 } },
   }

   create_items(items)
end

function maps.storage_house(generator)
   generator.load_custom("storage_1")

   Map.data.bgm = "core.mcLonely"
   Map.data.max_item_count = 200
   Map.data.is_user_map = false

   generator.place_player()
end

function maps.test_site(generator)
   generator.create(16, 16)

   Map.data.max_crowd_density = 0

   for j=0, Map.height() do
      for i=0, Map.width() do
         -- TODO
         Map.set_tile(i, j, TILE_DEFAULT)
      end
   end

   generator.place_player()

   local pos = Chara.player().position
   Chara.create(pos.x, pos.y + 5)

   local chara = Chara.create(pos, "core.wizard")
   chara.role = 22
   chara:set_flag("IsLivestock", true)
end

function maps.lumiest_graveyard(generator)
   generator.load_custom("grave_1")

   Map.data.max_crowd_density = 7
   Map.data.bgm = "core.mcRuin"

   generator.place_player()

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end
end

function maps.jail(generator)
   generator.load_custom("jail1")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   generator.place_player()
end

function maps.truce_ground(generator)
   generator.load_custom("shrine_1")

   Map.data.max_crowd_density = 10

   local items = {
      { "core.altar", 10, 8, { param1 = 1, own_state = 1} },
      { "core.altar", 13, 8, { param1 = 2, own_state = 1} },
      { "core.altar", 10, 13, { param1 = 5, own_state = 1} },
      { "core.altar", 13, 13, { param1 = 4, own_state = 1} },
      { "core.altar", 20, 8, { param1 = 3, own_state = 1} },
      { "core.altar", 23, 8, { param1 = 7, own_state = 1} },
      { "core.altar", 20, 13, { param1 = 6, own_state = 1} },
      { "core.altar", 23, 13, { param1 = 0, own_state = 1} },
   }

   create_items(items)

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end
end

function maps.embassy(generator)
   generator.load_custom("office_1")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 173, 9, 2, { role = 1012, shop_rank = 10 } },
      { 173, 15, 2, { role = 1012, shop_rank = 10 } },
      { 173, 21, 2, { role = 1013, shop_rank = 10 } },
      { 173, 3, 2, { role = 1013, shop_rank = 10 } },
      { 16, -3, 0, { _count = 3, role = 4 } },
      { 39, -3, 0, { _count = 3, role = 4 } },
      { 77, 3, 9, { role = 14 } },
      { 77, 9, 9, { role = 14 } },
      { 77, 15, 9, { role = 14 } },
      { 77, 21, 9, { role = 14 } },
   }

   create_charas(charas)
end

local function generate_tyris_border(generator)
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { "core.shopkeeper", 7, 23, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor", ai_calm = 3 } },
      { "core.shopkeeper", 5, 17, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader", ai_calm = 3  } },
      { "core.shopkeeper", 16, 19, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { "core.bartender", 17, 13, { role = 9 } },
      { "core.caravan_master", 7, 3, { role = 23 } },
      { "core.beggar", -3, 0, { _count = 2 } },
      { "core.mercenary_warrior", -3, 0, { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { "core.mercenary_archer", -3, 0, { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { "core.mercenary_wizard", -3, 0, { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { "core.guard", 5, 7, { role = 14, ai_calm = 3 } },
      { "core.guard", 8, 7, { role = 14, ai_calm = 3 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.test_world_north_border(generator)
   generator.load_custom("test2")

   generate_tyris_border(generator)

   World.add_event(30)
end

function maps.tyris_border(generator)
   generator.load_custom("station-nt1")

   generate_tyris_border(generator)
end

function maps.the_smoke_and_pipe(generator)
   generator.load_custom("inn1")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { "core.shopkeeper", 19, 10, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { "core.the_leopard_warrior", 26, 16, { role = 3, ai_calm = 3 } },
      { "core.town_child", 25, 15, { ai_calm = 3 } },
      { "core.town_child", 25, 17, { ai_calm = 3 } },
      { "core.town_child", 27, 18, { ai_calm = 3 } },
      { "core.town_child", 27, 16, { ai_calm = 3 } },
      { "core.town_child", 26, 17, { ai_calm = 3 } },
      { "core.silvia", 4, 3, { role = 3 } },
      { "core.rogue", 4, 2 },
      { "core.farmer", 3, 3 },
      { "core.artist", 4, 4 },
      { "core.noble", 5, 4 },
      { "core.hot_spring_maniac", 24, 3 },
      { "core.hot_spring_maniac", 26, 4 },
      { "core.hot_spring_maniac", 25, 5 },
      { "core.hot_spring_maniac", 25, 9 },
      { "core.bard", 12, 9 },
      { "core.beggar", -3, 0, { _count = 2 } },
      { "core.mercenary_warrior", -3, 0, { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { "core.old_person", -3, 0, { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { "core.mercenary", -3, 0, { _count = 2 } },
      { "core.tourist", -3, 0, { _count = 2 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.miral_and_garoks_workship(generator)
   generator.load_custom("smith0")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { "core.garokk", 17, 11, { role = 3, shop_rank = 100 } },
      { "core.miral", 8, 16, { role = 1016, shop_rank = 100 } },
      { "core.cat", -3, 0, { _count = 5, role = 3 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.mansion_of_younger_sister(generator)
   generator.load_custom("sister")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   if generator.is_first_generation then
      local item = Item.create(12, 8, "core.book_of_rachel", 0)
      item.param2 = 4
   end

   local charas = {
      { "core.young_lady", -3, 0, { _count = 6, role = 3 } },
      { "core.silver_cat", -3, 0, { _count = 8, role = 3 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.cyber_dome(generator)
   generator.load_custom("cyberdome")

   Map.data.max_crowd_density = 10

   local items = {
      { "core.altar", 19, 5, { param1 = 1, own_state = 1 } },
   }

   create_items(items)

   local charas = {
      { "core.sales_person", 9, 16, { role = 1011, shop_rank = 10 } },
      { "core.sales_person", 9, 8, { role = 1011, shop_rank = 10 } },
      { "core.strange_scientist", 28, 7, { role = 3 } },
      { "core.citizen_of_cyber_dome", -3, 0, { _count = 4, role = 4 } },
      { "core.citizen_of_cyber_dome2", -3, 0, { _count = 4, role = 4 } },
   }

   create_charas(charas)

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end
end

function maps.larna(generator)
   generator.load_custom("highmountain")

   Map.data.max_crowd_density = 20
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 41, 21, 23, { role = 21 } },
      { "core.shopkeeper", 9, 44, { role = 1017, shop_rank = 5, _name = "core.locale.chara.job.dye_vendor" } },
      { "core.shopkeeper", 13, 37, { role = 1018, shop_rank = 30, _name = "core.locale.chara.job.souvenir_vendor" } },
      { "core.bartender", 24, 48, { role = 9 } },
      { "core.hot_spring_maniac", 7, 36 },
      { "core.hot_spring_maniac", 9, 38 },
      { "core.hot_spring_maniac", 6, 33 },
      { "core.hot_spring_maniac", 3, 33 },
      { "core.hot_spring_maniac", 8, 31 },
      { "core.hot_spring_maniac", 4, 36 },
      { "core.citizen", -3, 0, { _count = 7, role = 4 } },
      { "core.citizen2", -3, 0, { _count = 7, role = 4 } },
      { "core.hot_spring_maniac", -3, 0, { _count = 22 } },
   }

   create_charas(charas)

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end

   generator.place_player()
end

function maps.arena(generator)
   generator.load_custom("arena_1")

   generator.place_player()

   -- NOTE: internally, arena logic is handled
end

function maps.arena(generator)
   generator.load_custom("arena_2")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPetArena"

   -- NOTE: internally, pet arena logic is handled
end


local function fort_of_chaos(boss)
   return function(generator)
      generator.load_custom("god")

      Map.data.max_crowd_density = 0
      Map.data.bgm = "core.mcBoss2"

      local charas = {
         { boss, 12, 14 }
      }

      create_charas(charas)

      generator.place_player()
   end
end

maps.fort_of_chaos_beast = fort_of_chaos("core.frisia")
maps.fort_of_chaos_machine = fort_of_chaos("core.utima")
maps.fort_of_chaos_collapsed = fort_of_chaos("core.azzrssil")


local function initialize_rank_0_home()
   Map.data.play_campfire_sound = true

   local charas = {
      { "core.larnneire", 18, 10, { role = 3 } },
      { "core.lomias", 16, 11, { role = 3 } },
   }

   create_charas(charas)

   local items = {
      { "core.heir_trunk", 15, 19, { count = 3 } },
      { "core.salary_chest", 15, 19, { count = 4 } },
      { "core.freezer", 9, 8, { count = 6 } },
      { "core.book_b", 18, 19, { param1 = 1 } },
   }

   create_items(items)
end

local function initialize_rank_5_home()
   local charas = {
      { "core.shopkeeper", 31, 20, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { "core.shopkeeper", 9, 20, { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.armory" } },
      { "core.shopkeeper", 4, 20, { role = 1008, shop_rank = 10, _name = "core.locale.chara.job.goods_vendor" } },
      { 41, 4, 11, { role = 5 } },
      { 70, 30, 11, { role = 9 } },
      { 74, 30, 4, { role = 12 } },
      { 41, 4, 4, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
   }

   create_charas(charas)
end

local function initialize_home_map_data()
   if World.home_scale() == 0 then
      Map.data.max_item_count = 100
   elseif World.home_scale() == 1 then
      Map.data.max_item_count = 150
   elseif World.home_scale() == 2 then
      Map.data.max_item_count = 200
   elseif World.home_scale() == 3 then
      Map.data.max_item_count = 300
   elseif World.home_scale() == 4 then
      Map.data.max_item_count = 350
      Map.data.tileset = 8
   elseif World.home_scale() == 5 then
      Map.data.max_item_count = 400
   end
end

function maps.your_home(generator)
   generator.load_custom("home" .. World.home_scale())

   Map.data.bgm = "core.mcLonely"
   Map.data.is_user_map = false
   Map.data.tileset = 3
   generator.set_entrance_type("Center")

   generator.place_player()

   if Map.current_dungeon_level == 1 then
      if World.home_scale() == 0 then
         initialize_rank_0_home()
      end

      if World.home_scale() == 5 then
         initialize_rank_5_home()
      end
   else
      Item.create(Chara.player().position, "core.tight_rope", 0)
   end

   initialize_home_map_data()
end

local function world_map(name)
   return function(generator)
      generator.load_custom(name)
      generator.initialize_world_map()
      generator.place_player()
   end
end

maps.north_tyris = world_map("ntyris")
maps.south_tyris = world_map("styris")
maps.test_world = world_map("test")

function maps.derphy(generator)
   generator.load_custom("rogueden")

   Map.data.max_crowd_density = 35
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 253, 23, 14, { role = 3 } },
      { 259, 13, 18, { role = 3 } },
      { 294, 16, 17, { role = 3 } },
      { 1, 10, 17, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 70, 15, 15, { role = 9 } },
      { 1, 13, 3, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 1, 29, 23, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 1, 26, 7, { role = 1008, shop_rank = 10, _name = "core.locale.chara.job.goods_vendor" } },
      { 1, 30, 4, { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 1, 29, 4, { role = 17, _name = "core.locale.chara.job.slave_master" } },
      { 1, 10, 6, { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.armory" } },
      { 73, 7, 15, { role = 10 } },
      { 38, 9, 18, { role = 6, _name = "core.locale.chara.job.of_derphy" } },
      { 40, 13, 18, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 5, 26, { role = 5 } },
      { 69, 3, 28, { role = 8 } },
      { 16, -3, 0, { _count = 4, role = 4 } },
      { 39, -3, 0, { _count = 4, role = 4 } },
   }

   create_charas(charas)

   generator.update_quests_in_map()

   for i=0, 20 do
      Chara.generate_from_map()
   end
end

function maps.thieves_guild(generator)
   generator.load_custom("thiefguild")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Guild"
   Map.data.max_crowd_density = 25
   Map.data.bgm = "core.mcRuin"
   Map.data.should_regenerate = false
   generator.set_name(I18N.get("core.locale.map.unique.thieves_guild.name"))

   generator.place_player()

   local charas = {
      { 292, 21, 9, { role = 3, _name = "core.locale.chara.job.trainer" } },
      { 40, 3, 6, { role = 7 } },
      { 41, 3, 12, { role = 5 } },
      { 1, 5, 18, { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 1, 27, 13, { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 1, 21, 19, { role = 1021, shop_rank = 10, _name = "core.locale.chara.job.fence" } },
      { 293, -3, 0, { _count = 16 } },
   }

   create_charas(charas)
end

function maps.palmia(generator)
   generator.load_custom("palmia")

   Map.data.max_crowd_density = 45
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 70, 42, 27, { role = 9 } },
      { 74, 34, 3, { role = 12 } },
      { 73, 22, 31, { role = 10 } },
      { 142, 5, 15, { role = 3 } },
      { 247, 41, 11, { role = 3 } },
      { 301, 5, 6, { role = 3 } },
      { 320, 24, 6, { role = 3 } },
      { 320, 15, 22, { role = 3 } },
      { 326, 15, 22, { role = 3 } },
      -- TODO
      -- if (game_data.quest_flags.mias_dream == 1000)
      -- {
      --     { 246, 42, 11, { role = 3 } },
      -- }
      { 1, 48, 18, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 1, 30, 17, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 1, 48, 3, { role = 1008, shop_rank = 8, _name = "core.locale.chara.job.goods_vendor" } },
      { 1, 42, 17, { role = 1001, shop_rank = 12 } },
      { 1, 11, 14, { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.bakery", image = 138 } },
      { 41, 41, 3, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 1, 41, 28, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 79, 7, 2, { role = 15, ai_calm = 3 } },
      { 80, 6, 2, { role = 15, ai_calm = 3 } },
      { 38, 49, 11, { role = 6, _name = "core.locale.chara.job.of_palmia" } },
      { 40, 30, 27, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 32, 27, { role = 5 } },
      { 69, 29, 28, { role = 8 } },
      { 77, 16, 5, { role = 14, ai_calm = 3 } },
      { 77, 16, 9, { role = 14, ai_calm = 3 } },
      { 77, 5, 3, { role = 14, ai_calm = 3 } },
      { 77, 8, 3, { role = 14, ai_calm = 3 } },
      { 77, 35, 14, { role = 14, ai_calm = 3 } },
      { 77, 38, 14, { role = 14, ai_calm = 3 } },
      { 77, 29, 2, { role = 14, ai_calm = 3 } },
      { 77, 19, 18, { role = 14, ai_calm = 3 } },
      { 77, 22, 18, { role = 14, ai_calm = 3 } },
      { 16, -3, 0, { _count = 5, role = 4 } },
      { 39, -3, 0, { _count = 5, role = 4 } },
      { 77, -3, 0, { _count = 4, role = 14 } },
   }

   create_charas(charas)

   --TODO
   -- if (game_data.quest_flags.mias_dream == 1000)
   -- {
   --     { 246, 42, 11, { role = 3 } },
   -- }

   generator.update_quests_in_map()

   for i=0, 25 do
      Chara.generate_from_map()
   end
end

function maps.lumiest(generator)
   generator.load_custom("lumiest")

   Map.data.max_crowd_density = 40
   Map.data.is_user_map = false

   generator.place_player()

   -- TODO
   -- if (game_data.quest_flags.sewer_sweeping)
   -- {
   --     cell_featset(18, 45, tile_downstairs, 11, 20)
   -- }

   local charas = {
      { 252, 12, 24, { role = 3 } },
      { 280, 21, 3, { role = 3 } },
      { 290, 5, 20, { role = 3 } },
      { 320, 28, 29, { role = 3 } },
      { 326, 41, 19, { role = 3 } },
      { 326, 32, 43, { role = 3 } },
      { 326, 29, 28, { role = 3 } },
      { 326, 16, 45, { role = 3 } },
      { 326, 13, 24, { role = 3 } },
      { 70, 41, 42, { role = 9 } },
      { 74, 10, 16, { role = 12 } },
      { 1, 47, 30, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 1, 24, 47, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 1, 37, 30, { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.armory" } },
      { 1, 37, 12, { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.bakery", image = 138 } },
      { 41, 6, 15, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 1, 33, 43, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 1, 47, 12, { role = 1014, shop_rank = 5, _name = "core.locale.chara.job.fisher" } },
      { 38, 3, 38, { role = 6, _name = "core.locale.chara.job.of_lumiest" } },
      { 40, 21, 28, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 21, 30, { role = 5 } },
      { 69, 23, 38, { role = 8 } },
      { 16, -3, 0, { _count = 6, role = 4 } },
      { 39, -3, 0, { _count = 6, role = 4 } },
      { 77, -3, 0, { _count = 7, role = 14 } },
   }

   generator.update_quests_in_map()

   for i=0,25 do
      Chara.generate_from_map()
   end
end

function maps.mages_guild(generator)
   generator.load_custom("mageguild")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Guild"
   Map.data.max_crowd_density = 25
   Map.data.bgm = "core.mcRuin"
   Map.data.should_regenerate = false
   generator.set_name(I18N.get("core.locale.map.unique.mages_guild.name"))

   generator.place_player()

   local charas = {
      { 288, 24, 3, { role = 3 } },
      { 41, 27, 8, { role = 1020, _name = "core.locale.chara.job.spell_writer" } },
      { 41, 22, 8, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 74, 3, 9, { role = 12 } },
      { 40, 12, 6, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 3, 3, { role = 5 } },
      { 289, -3, 0, { _count = 16 } },
   }

   create_charas(charas)
end

function map.lumiest_sewer(generator)
   generator.load_custom("sqSewer")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = 61
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.the_sewer.name"))

   generator.mark_quest_targets()

   generator.set_entrance_type("StairUp")
   generator.place_player()
end

function map.yowyn(generator)
   generator.load_custom("yowyn")
   Map.data.max_crowd_density = 35
   Map.data.is_user_map = false

   generator.place_player()

   -- TODO
   -- if (game_data.quest_flags.cat_house)
   -- {
   --     cell_featset(23, 22, tile_downstairs, 11, 3)
   -- }

   local charas = {
      { 224, 3, 17, { role = 3 } },
      { 227, 26, 11, { role = 3 } },
      { 231, 14, 20, { role = 3 } },
      { 1, 11, 5, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 1, 25, 8, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 1, 7, 8, { role = 1008, shop_rank = 8, _name = "core.locale.chara.job.goods_vendor" } },
      { 1, 14, 14, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 1, 35, 18, { role = 22, _name = "core.locale.chara.job.horse_master" } },
      { 267, 33, 16, { role = 3 } },
      { 267, 37, 19, { role = 3 } },
      { 268, 34, 19, { role = 3 } },
      { 268, 38, 16, { role = 3 } },
      { 38, 3, 4, { role = 6, _name = "core.locale.chara.job.of_yowyn" } },
      { 40, 20, 14, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 24, 16, { role = 5 } },
      { 69, 26, 16, { role = 8 } },
      { 213, 14, 12, { role = 3 } },
      { 16, -3, 0, { _count = 2, role = 4 } },
      { 39, -3, 0, { _count = 2, role = 4 } },
      { 77, -3, 0, { _count = 3, role = 14 } },
   }

   create_charas(charas)

   generator.update_quests_in_map()

   for i=0,15 do
      Chara.generate_from_map()
   end
end

function maps.cat_mansion(generator)
   Map.data.tileset = 0
   generator.load_custom("sqcat")
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.cat_mansion.name"))

   generator.mark_quest_targets()

   generator.place_player()
end

function maps.battle_field(generator)
   Map.data.tileset = 0
   generator.load_custom("sqwar")
   Map.data.is_indoors = false
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = true
   Map.data.refresh_type = 0
   generator.set_name(I18N.get("core.locale.map.unique.battle_field.name"))

   generator.mark_quest_targets()

   generator.set_entrance_type("South")
   generator.place_player()

   local enemies = {}

   for chara in Chara.iter(57, 245) do
      if Chara.is_alive(chara) and chara:get_flag("IsQuestTarget") then
         enemies[#enemies+1] = chara
      end
   end

   for i=0, 30 do
      local id = "core.juere_infantry"
      if i > 22 then
         id = "core.juere_swordman"
      end

      local chara = Chara.create(11, 16, id)

      chara.relationship = "Friend"
      chara.original_relationship = "Friend"
      chara.hate = 100
      local enemy = Rand.choice(enemies)
      chara.enemy_id = enemy.index
      enemy.hate = 100
      enemy.enemy_id = chara.index
   end
   generator.set_no_aggro_refresh(true)
end

function maps.noyel(generator)
   generator.load_custom("noyel")

   Map.data.max_crowd_density = 35
   Map.data.user_map_flag = 0

   generator.place_player()

   local charas = {
      -- TODO
      { 202, 46, 18, { role = 3 } },
      -- game_data.fire_giant = rc
      { 203, 47, 18, { role = 1015 } },
      { 35, 47, 20, { role = 3 } },
      { 35, 45, 19, { role = 3 } },
      { 35, 49, 20, { role = 3 } },
      { 326, 28, 22, { role = 3 } },
      { 221, 19, 3, { role = 3 } },
      -- TODO
      -- if (game_data.quest_flags.pael_and_her_mom != 1001)
      -- {
      --     { 222, 19, 2, { role = 3 } },
      -- }
      { 70, 40, 33, { role = 9 } },
      { 74, 44, 6, { role = 12 } },
      { 206, 44, 3, { role = 19 } },
      { 1, 19, 31, { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.armory" } },
      { 1, 11, 31, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 1, 38, 34, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 1, 5, 27, { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.bakery", image = 138 } },
      { 41, 56, 5, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 1, 39, 35, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 38, 5, 18, { role = 6, _name = "core.locale.chara.job.of_noyel" } },
      { 40, 18, 20, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 4, 33, { role = 5 } },
      { 69, 6, 33, { role = 8 } },
   }

   create_charas(charas)

   local chara

   for i=0,3 do
      chara = Chara.create(Rand.rnd(32), Rand.rnd(Map.height()), 16)
      chara.role = 4
      chara = Chara.create(Rand.rnd(32), Rand.rnd(Map.height()), 39)
      chara.role = 4
   end
   for i=0,3 do
      chara = Chara.create(Rand.rnd(32), Rand.rnd(Map.height()), 77)
      chara.role = 14
   end

   generator.update_quests_in_map()

   for i=0,8 do
      chara = Chara.generate_from_map(Rand.rnd(11) + 25, Rand.rnd(5) + 15, 35)
      chara.role = 3
   end
   for i=0,20 do
      chara = Chara.generate_from_map(Rand.rnd(55), Rand.rnd(Map.height()))
   end
end

function maps.port_kapul(generator)
   generator.load_custom("kapul")

   Map.data.max_crowd_density = 40
   Map.data.user_map_flag = 0

   generator.place_player()

   local charas = {
      { 223, 15, 18, { role = 3 } },
      { 243, 36, 27, { role = 3 } },
      { 279, 5, 26, { role = 3 } },
      { 297, 29, 3, { role = 3 } },
      { 320, 24, 21, { role = 3 } },
      { 320, 12, 26, { role = 3 } },
      { 320, 8, 11, { role = 3 } },
      { 326, 8, 14, { role = 3 } },
      { "core.shopkeeper", 16, 17, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { "core.shopkeeper", 23, 7, { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.armory" } },
      { "core.shopkeeper", 32, 14, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { "core.shopkeeper", 22, 14, { role = 1008, shop_rank = 10, _name = "core.locale.chara.job.goods_vendor" } },
      { "core.shopkeeper", 16, 25, { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { "core.shopkeeper", 17, 28, { role = 1002, shop_rank = 10, _name = "core.locale.chara.job.food_vendor" } },
      { 41, 22, 22, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { "core.shopkeeper", 35, 3, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 70, 15, 15, { role = 9 } },
      { 73, 26, 3, { role = 10 } },
      { 179, 25, 4, { role = 11 } },
      { 38, 8, 12, { role = 6, _name = "core.locale.chara.job.of_port_kapul" } },
      { 40, 16, 4, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 14, 4, { role = 5 } },
      { 69, 17, 5, { role = 8 } },
      { 74, 27, 11, { role = 12 } },
      { 16, -3, 0, { _count = 2, role = 4 } },
      { 39, -3, 0, { _count = 2, role = 4 } },
      { 71, -3, 0, { _count = 4, role = 4 } },
      { 76, -3, 0, { _count = 5, role = 14 } },
      { 72, 7, 6, { role = 4 } },
   }

   generator.update_quests_in_map()

   for i=0,20 do
      Chara.generate_from_map()
   end
end

function maps.fighters_guild(generator)
   generator.load_custom("fighterguild")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Guild"
   Map.data.max_crowd_density = 25
   Map.data.bgm = "core.mcRuin"
   Map.data.should_regenerate = 0
   generator.set_name(I18N.get("core.locale.map.unique.fighters_guild.name"))

   generator.place_player()

   local charas = {
      { 291, 27, 4, { role = 3 } },
      { 74, 28, 10, { role = 12 } },
      { 40, 15, 10, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 41, 14, 18, { role = 5 } },
      { 1, 29, 15, { role = 1001, shop_rank = 12, "core.locale.chara.job.armory" } },
      { 295, -3, 0 },
   }

   create_charas(charas)
end

function maps.doom_ground(generator)
   generator.load_custom("sqkamikaze")

   Map.data.tileset = 0
   Map.data.is_indoors = false
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = true
   Map.data.refresh_type = 0
   generator.set_name(I18N.get("core.locale.map.unique.doom_ground.name"))

   -- TODO
   -- game_data.quest_flags.duration_of_kamikaze_attack = 0
   generator.set_entrance_type("Center")
   generator.place_player()

   for i=0, 10 do
      local chara = Chara.create(204, Chara.player().position, 204)
      chara.relationship = "Friend"
      chara.original_relationship = "Friend"
   end

   generator.set_no_aggro_refresh(true)
end

function maps.vernis(generator)
   generator.load_custom("vernis")

   Map.data.max_crowd_density = 40
   Map.data.user_map_flag = 0

   generator.place_player()

   -- TODO
   -- if (game_data.quest_flags.thieves_hideout)
   -- {
   --     cell_featset(48, 5, tile_downstairs, 11, 4)
   -- }

   local charas = {
      { 28, 39, 3 },
      { 29, 42, 23, { role = 3 } },
      { 30, 24, 5, { role = 3 } },
      { 31, 40, 24, { role = 3 } },
      { 32, 40, 25, { role = 3 } },
      { 226, 30, 5, { role = 3 } },
      { 326, 42, 24, { role = 3 } },
      -- TODO
      -- if (game_data.quest_flags.puppys_cave == 1000)
      -- {
      --     { 225, 31, 4, { role = 3 } },
      -- }
      { 1, 47, 9, { role = 1014, shop_rank = 5, _name = "core.locale.chara.job.fisher" } },
      { 1, 14, 12, { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.armory" } },
      { 1, 39, 27, { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 1, 10, 15, { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 41, 7, 26, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 1, 14, 25, { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 1, 22, 26, { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.bakery", image = 138 } },
      { 41, 28, 16, { role = 5 } },
      { 70, 38, 27, { role = 9 } },
      { 74, 6, 25, { role = 12 } },
      { 38, 10, 7, { role = 6, _name = "core.locale.chara.job.of_vernis" } },
      { 40, 27, 16, { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 69, 25, 16, { role = 8 } },
      { 16, -3, 0, { _count = 4, role = 4 } },
      { 39, -3, 0, { _count = 4, role = 4 } },
      { 77, -3, 0, { _count = 4, role = 14 } },
   }

   generator.update_quests_in_map()

   for i=0,25 do
      Chara.generate_from_map()
   end
end

function maps.the_mine(generator)
   generator.load_custom("puti")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.the_mine.name"))

   generator.mark_quest_targets()

   generator.place_player()
end

function maps.robbers_hideout(generator)
   generator.load_custom("sqrogue")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.robbers_hideout.name"))

   generator.mark_quest_targets()

   generator.place_player()
end

function maps.test_site(generator)
   generator.load_custom("sqNightmare")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = 61
   Map.data.should_regenerate = 1
   generator.set_name(I18N.get("core.locale.map.unique.test_site.name"))

   generator.mark_quest_targets()

   generator.place_player(6, 27)
end

function maps.fields_forest(generator)
   generator.set_name(I18N.get_enum_property("core.locale.map.unique", "forest", 2))
   Map.spray_tile(8, 25)
   Map.spray_tile(0, 10)
   Map.spray_tile(1, 4)
   Map.spray_tile(4, 2)
   for i=0, 20 + Rand.rnd(20) do
      local item = Item.create(-1, -1, { flttypemajor = 80000 })
      item.own_state = 1
      Map.set_tile(item.position, 0)
   end
end

function maps.fields_sea(generator)
   generator.set_name(I18N.get_enum_property("core.locale.map.unique", "sea", 2))
end

function maps.fields_grassland(generator)
   generator.set_name(I18N.get_enum_property("core.locale.map.unique", "grassland", 2))
   Map.spray_tile(9, 10)
   Map.spray_tile(10, 10)
   Map.spray_tile(0, 30)
   Map.spray_tile(1, 4)
   Map.spray_tile(4, 2)
   Map.spray_tile(3, 2)
   Map.spray_tile(4, 2)
   Map.spray_tile(5, 2)
   for i=0, 10 + Rand.rnd(10) do
      local item = Item.create(-1, -1, { flttypemajor = 80000 })
      item.own_state = 1
   end
end

function maps.fields_desert(generator)
   generator.set_name(I18N.get_enum_property("core.locale.map.unique", "desert", 2))
   Map.spray_tile(18, 25)
   Map.spray_tile(17, 10)
   Map.spray_tile(19, 2)
   Map.spray_tile(20, 4)
   Map.spray_tile(21, 2)
   for i=0, 4 + Rand.rnd(4) do
      local item = Item.create(-1, -1, 527)
      item.own_state = 1
   end
end

function maps.fields_snow_field(generator)
   generator.set_name(I18N.get_enum_property("core.locale.map.unique", "snow_field", 2))
   Map.spray_tile(57, 4)
   Map.spray_tile(56, 4)
   Map.spray_tile(49, 2)
   Map.spray_tile(46, 1)
   Map.spray_tile(47, 1)
   Map.spray_tile(48, 1)
   Map.spray_tile(51, 1)
   for i=0, 3 + Rand.rnd(5) do
      local item = Item.create(-1, -1, { flttypemajor = 80000, fltselect = 8 })
      item.own_state = 1
   end
end

function maps.fields_plain_field(generator)
   generator.set_name(I18N.get_enum_property("core.locale.map.unique", "plain_field", 2))
   Map.spray_tile(1, 10)
   Map.spray_tile(2, 2)
   Map.spray_tile(3, 2)
   Map.spray_tile(4, 2)
   Map.spray_tile(5, 2)
   Map.spray_tile(6, 2)
   for i=0, 5 + Rand.rnd(5) do
      local item = Item.create(-1, 0, -1, -1, { flttypemajor = 80000 })
      item.own_state = 1
   end
end

function maps.fields(generator)
   Map.data.max_crowd_density = 4
   Map.data.is_user_map = false
   generator.create(34, 22)

   for i=0, Map.height() do
      for j=0, Map.width() do
         -- TODO
         Map.set_tile(i, j, TILE_DEFAULT)
      end
   end

   generator.set_name("")

   local stood_tile = generator.stood_world_map_tile

   if 4 <= stood_tile and stood_tile < 9 then
      maps.fields_forest(generator)
   elseif 264 <= stood_tile and stood_tile < 363 then
      maps.fields_sea(generator)
   elseif 9 <= stood_tile and stood_tile < 13 then
      maps.fields_grassland(generator)
   elseif 13 <= stood_tile and stood_tile < 17 then
      maps.fields_desert(generator)
   elseif Map.chip_type(stood_tile) == 4 then
      maps.fields_snow_field(generator)
   else
      maps.fields_plain_field(generator)
   end

   generator.place_player()

   if 264 > stood_tile or stood_tile >= 363 then
      for i=0, 4 + Rand.rnd(5) do
         Item.create(-1, -1, { flttypeminor = 64000 })
      end
   end
end

function maps.the_void(generator)
   generator.generate_nefia()
end

function maps.lesimas(generator)
   generator.set_tileset(Map.data.tileset)
   generator.generate_nefia()

   if Map.current_dungeon_level() == 3 then
      local chara = Chara.create(Chara.player().position, 139)
      chara.role = 3
      chara.ai_calm = 3
   end
   if Map.current_dungeon_level() == 17 then
      local chara = Chara.create(Chara.player().position, 146)
      chara.role = 3
      chara.ai_calm = 3
   end
end

local function dungeon_with_boss(deepest_map)
   return function(generator)
      if generator.is_deepest_level() then
         generator.load_custom(deepest_map)
         Map.data.max_crowd_density = 0
         Map.data.bgm = "core.mcLastBoss"
         generator.place_player()
      else
         generator.generate_random_nefia()
      end
   end
end

maps.tower_of_fire = dungeon_with_boss("firet1")
maps.crypt_of_the_damned = dungeon_with_boss("undeadt1")
maps.ancient_castle = dungeon_with_boss("roguet1")
maps.dragons_nest = dungeon_with_boss("d_1")

function maps.puppy_cave(generator)
   generator.generate_nefia()
end

function maps.minotaurs_nest(generator)
   generator.generate_nefia()
end

function maps.yeeks_nest(generator)
   generator.generate_nefia()
end

function maps.pyramid(generator)
   if Map.current_dungeon_level == 20 then
      generator.load_custom("sqPyramid")
      Map.data.max_crowd_density = 40
      Map.data.bgm = "core.mcPuti"
      generator.place_player()
      for i=0, Map.data.max_crowd_density + 1 do
         Chara.generate_from_map()
      end
   elseif Map.current_dungeon_level == 21 then
      generator.load_custom("sqPyramid2")
      Map.data.max_crowd_density = 0
      Map.data.bgm = "core.mcPuti"
      generator.place_player()
   end
end

function maps.mountain_pass(generator)
   generator.generate_nefia()
end

function maps.quest(generator)
   -- Internally, generates the appropriate map based on quest type.
   generator.generate_nefia()
end

function maps.show_house()
   -- no-op
end

return maps
