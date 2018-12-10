local Map = Elona.require("Map")
local World = Elona.require("World")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local table = Elona.require("table")

local maps = {}

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
         Map.set_tile(0)
      end
   end

   generator.place_player()

   -- TODO
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
      -- TODO
      Map.generate_chara()
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
      -- TODO
      Map.generate_chara()
   end
end

function maps.embassy(generator)
   generator.load_custom("office_1")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { "core.sales_person", 9, 2, { role = 1012, shop_rank = 10 } },
      { "core.sales_person", 15, 2, { role = 1012, shop_rank = 10 } },
      { "core.sales_person", 21, 2, { role = 1013, shop_rank = 10 } },
      { "core.sales_person", 3, 2, { role = 1013, shop_rank = 10 } },
      { "core.citizen", -3, 0, { _count = 3, role = 4 } },
      { "core.citizen2", -3, 0, { _count = 3, role = 4 } },
      { "core.guard", 9, 9, { role = 14 } },
      { "core.guard", 15, 9, { role = 14 } },
      { "core.guard", 21, 9, { role = 14 } },
      { "core.guard", 27, 9, { role = 14 } },
   }

   create_charas(charas)
end

local function generate_tyris_border(generator)
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { "core.shopkeeper", 7, 23, { role = 1007, shop_rank = 10, ai_calm = 3, _name = "core.locale.chara.job.general_vendor" } },
      { "core.shopkeeper", 5, 17, { role = 1009, shop_rank = 12, ai_calm = 3, _name = "core.locale.chara.job.trader" } },
      { "core.shopkeeper", 16, 19, { role = 1005, shop_rank = 8, ai_calm = 3, _name = "core.locale.chara.job.innkeeper" } },
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
      { "core.garokk", 17, 11, { role = 3 } },
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

   -- TODO
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

function map.cyber_dome(generator)
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
      -- TODO
      Map.generate_chara()
   end
end

function maps.larna(generator)
   generator.load_custom("highmountain")

   Map.data.max_crowd_density = 20
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { "core.wizard", 21, 23, { role = 21 } },
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
      Map.generate_chara()
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
      { "core.wizard", 4, 11, { role = 5 } },
      { "core.bartender", 30, 11, { role = 9 } },
      { "core.healer", 30, 4, { role = 12 } },
      { "core.wizard", 30, 4, { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
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

   local charas = {}
end

return maps
