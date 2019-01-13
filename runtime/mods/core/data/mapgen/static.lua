local Chara = Elona.require("Chara")
local I18N = Elona.require("I18N")
local Item = Elona.require("Item")
local Map = Elona.require("Map")
local Rand = Elona.require("Rand")
local World = Elona.require("World")
local table = Elona.require("table")

local maps = {}

local function create_items(items)
   for _, data in ipairs(items) do
      local x, y, id, opts = table.unpack(data)

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
      local x, y, id, opts = table.unpack(data)

      local count = (opts and opts["_count"]) or 1

      for i=1,count do
         local chara = Chara.create(x, y, id)

         if opts then
            for k, v in pairs(opts) do
               if k == "_name" then
                  chara.basename = I18N.get(v, chara.basename)
               elseif k ~= "_count" then
                  chara[k] = v
               end
            end
         end
      end
   end
end

function maps.shelter(generator)
   if Map.current_dungeon_level() == 1 then
      -- Shelter from innkeeper
      generator.load_custom("shelter_2")
      Map.data.is_temporary = true
      Map.data.type = "Shelter"
   else
      -- Shelter from item (dungeon level is shelter ID)
      generator.load_custom("shelter_1")
      Map.data.is_user_map = false
   end

   Map.data.max_crowd_density = 0
   Map.data.max_item_count = 5
   Map.data.bgm = "core.mcLonely"

   generator.place_player()
end

function maps.museum(generator)
   generator.load_custom("museum_1")

   Map.data.is_user_map = false
   Map.data.bgm = "core.mcTown3"

   generator.place_player()

   local items = {
      { 15, 17, "core.book_b", { param1 = 4 } }
   }

   create_items(items)
end

function maps.shop(generator)
   generator.load_custom("shop_1")

   Map.data.bgm = "core.mcTown3"
   Map.data.max_item_count = 10

   generator.place_player()

   local items = {
      { 17, 14, "core.book_b", { param1 = 8 } },
      { 19, 10, "core.shop_strongbox", { count = 5 } },
      { 17, 11, "core.register" }
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
      { 14, 5, "core.book_b", { param1 = 9 } }
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
      { 23, 8, "core.book_b", { param1 = 11 } },
      { 22, 6, "core.register" },
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
      { 39, 54, "core.book_b", { param1 = 15 } },
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

   for j=0, Map.height()-1 do
      for i=0, Map.width()-1 do
         Map.set_tile(i, j, Map.generate_tile("Normal"))
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
   Map.data.bgm = "core.mcRuin"

   local items = {
      { 10, 8, "core.altar", { param1 = 1, own_state = 1} },
      { 13, 8, "core.altar", { param1 = 2, own_state = 1} },
      { 10, 13, "core.altar", { param1 = 5, own_state = 1} },
      { 13, 13, "core.altar", { param1 = 4, own_state = 1} },
      { 20, 8, "core.altar", { param1 = 3, own_state = 1} },
      { 23, 8, "core.altar", { param1 = 7, own_state = 1} },
      { 20, 13, "core.altar", { param1 = 6, own_state = 1} },
      { 23, 13, "core.altar", { param1 = 0, own_state = 1} },
   }

   create_items(items)

   generator.place_player()

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end
end

function maps.embassy(generator)
   generator.load_custom("office_1")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 9, 2, "core.sales_person", { role = 1012, shop_rank = 10 } },
      { 15, 2, "core.sales_person", { role = 1012, shop_rank = 10 } },
      { 21, 2, "core.sales_person", { role = 1013, shop_rank = 10 } },
      { 3, 2, "core.sales_person", { role = 1013, shop_rank = 10 } },
      { -3, 0, "core.citizen", { _count = 3, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 3, role = 4 } },
      { 3, 9, "core.guard", { role = 14 } },
      { 9, 9, "core.guard", { role = 14 } },
      { 15, 9, "core.guard", { role = 14 } },
      { 21, 9, "core.guard", { role = 14 } },
   }

   create_charas(charas)

   generator.place_player()
end

local function generate_tyris_border(generator)
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 7, 23, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor", ai_calm = 3 } },
      { 5, 17, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader", ai_calm = 3  } },
      { 16, 19, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 17, 13, "core.bartender", { role = 9 } },
      { 7, 3, "core.caravan_master", { role = 23 } },
      { -3, 0, "core.beggar", { _count = 2 } },
      { -3, 0, "core.mercenary_warrior", { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { -3, 0, "core.mercenary_archer", { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { -3, 0, "core.mercenary_wizard", { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { 5, 7, "core.guard", { role = 14, ai_calm = 3 } },
      { 8, 7, "core.guard", { role = 14, ai_calm = 3 } },
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

maps.north_tyris_south_border = maps.tyris_border
maps.south_tyris_north_border = maps.tyris_border

function maps.the_smoke_and_pipe(generator)
   generator.load_custom("inn1")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 19, 10, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 26, 16, "core.the_leopard_warrior", { role = 3, ai_calm = 3 } },
      { 25, 15, "core.town_child", { ai_calm = 3 } },
      { 25, 17, "core.town_child", { ai_calm = 3 } },
      { 27, 18, "core.town_child", { ai_calm = 3 } },
      { 27, 16, "core.town_child", { ai_calm = 3 } },
      { 26, 17, "core.town_child", { ai_calm = 3 } },
      { 4, 3, "core.silvia", { role = 3 } },
      { 4, 2, "core.rogue" },
      { 3, 3, "core.farmer" },
      { 4, 4, "core.artist" },
      { 5, 4, "core.noble" },
      { 24, 3, "core.hot_spring_maniac" },
      { 26, 4, "core.hot_spring_maniac" },
      { 25, 5, "core.hot_spring_maniac" },
      { 25, 9, "core.hot_spring_maniac" },
      { 12, 9, "core.bard" },
      { -3, 0, "core.beggar", { _count = 2 } },
      { -3, 0, "core.mercenary_warrior", { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { -3, 0, "core.old_person", { _count = 2, relationship = "Unconcerned", original_relationship = "Unconcerned" } },
      { -3, 0, "core.mercenary", { _count = 2 } },
      { -3, 0, "core.tourist", { _count = 2 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.miral_and_garoks_workshop(generator)
   generator.load_custom("smith0")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 17, 11, "core.garokk", { role = 3, shop_rank = 100 } },
      { 8, 16, "core.miral", { role = 1016, shop_rank = 100 } },
      { -3, 0, "core.cat", { _count = 5, role = 3 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.mansion_of_younger_sister(generator)
   generator.load_custom("sister")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcRuin"

   if generator.is_first_generation() then
      local item = Item.create(12, 8, "core.book_of_rachel", 0)
      item.param2 = 4
   end

   local charas = {
      { 12, 6, "core.younger_sister_of_mansion", { role = 1019 } },
      { -3, 0, "core.young_lady", { _count = 6, role = 3 } },
      { -3, 0, "core.silver_cat", { _count = 8, role = 3 } },
   }

   create_charas(charas)

   generator.place_player()
end

function maps.cyber_dome(generator)
   generator.load_custom("cyberdome")

   Map.data.max_crowd_density = 10
   Map.data.bgm = "core.mcRuin"

   local items = {
      { 19, 5, "core.altar", { param1 = 1, own_state = 1 } },
   }

   create_items(items)

   local charas = {
      { 9, 16, "core.sales_person", { role = 1011, shop_rank = 10 } },
      { 9, 8, "core.sales_person", { role = 1011, shop_rank = 10 } },
      { 28, 7, "core.strange_scientist", { role = 3 } },
      { -3, 0, "core.citizen_of_cyber_dome", { _count = 4, role = 4 } },
      { -3, 0, "core.citizen_of_cyber_dome2", { _count = 4, role = 4 } },
   }

   create_charas(charas)

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end

   generator.place_player()
end

function maps.larna(generator)
   generator.load_custom("highmountain")

   Map.data.max_crowd_density = 20
   Map.data.bgm = "core.mcRuin"

   local charas = {
      { 21, 23, "core.wizard", { role = 21 } },
      { 9, 44, "core.shopkeeper", { role = 1017, shop_rank = 5, _name = "core.locale.chara.job.dye_vendor" } },
      { 13, 37, "core.shopkeeper", { role = 1018, shop_rank = 30, _name = "core.locale.chara.job.souvenir_vendor" } },
      { 24, 48, "core.bartender", { role = 9 } },
      { 7, 36, "core.hot_spring_maniac" },
      { 9, 38, "core.hot_spring_maniac" },
      { 6, 33, "core.hot_spring_maniac" },
      { 3, 33, "core.hot_spring_maniac" },
      { 8, 31, "core.hot_spring_maniac" },
      { 4, 36, "core.hot_spring_maniac" },
      { -3, 0, "core.citizen", { _count = 7, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 7, role = 4 } },
      { -3, 0, "core.hot_spring_maniac", { _count = 22 } },
   }

   create_charas(charas)

   for i=0, Map.data.max_crowd_density do
      Chara.generate_from_map()
   end

   generator.place_player()
end

-- Hardcoded behavior:
-- - removal of pets from map
-- - creation of arena boss(es)
function maps.arena(generator)
   generator.load_custom("arena_1")

   generator.place_player()

   -- NOTE: internally, arena logic is handled
end

-- Hardcoded behavior:
-- - removal of non-participant pets from map
-- - creation of enemy team
-- - display of health bars for enemies
function maps.pet_arena(generator)
   generator.load_custom("arena_2")

   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPetArena"

   generator.place_player()

   -- NOTE: internally, pet arena logic is handled
end


local function fort_of_chaos(boss)
   return function(generator)
      generator.load_custom("god")

      Map.data.max_crowd_density = 0
      Map.data.bgm = "core.mcBoss2"

      local charas = {
         { 12, 14, boss }
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
      { 18, 10, "core.larnneire", { role = 3 } },
      { 16, 11, "core.lomias", { role = 3 } },
   }

   create_charas(charas)

   local items = {
      { 15, 19, "core.heir_trunk", { count = 3 } },
      { 15, 19, "core.salary_chest", { count = 4 } },
      { 9, 8, "core.freezer", { count = 6 } },
      { 18, 19, "core.book_b", { param1 = 1 } },
   }

   create_items(items)
end

local function initialize_rank_5_home()
   local charas = {
      { 31, 20, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 9, 20, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { 4, 20, "core.shopkeeper", { role = 1008, shop_rank = 10, _name = "core.locale.chara.job.goods_vendor" } },
      { 4, 11, "core.wizard", { role = 5 } },
      { 30, 11, "core.bartender", { role = 9 } },
      { 30, 4, "core.healer", { role = 12 } },
      { 4, 4, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
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

-- Hardcoded behavior:
-- - moving of existing characters if home was upgraded
-- - application of home rank points based on home scale
function maps.your_home(generator)
   generator.load_custom("home" .. World.home_scale())

   Map.data.bgm = "core.mcLonely"
   Map.data.is_user_map = false
   Map.data.tileset = 3
   generator.set_entrance_type("Center")

   generator.place_player()

   if Map.current_dungeon_level() == 1 then
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
      { 23, 14, "core.marks", { role = 3 } },
      { 13, 18, "core.noel", { role = 3 } },
      { 16, 17, "core.abyss", { role = 3 } },
      { 10, 17, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 15, 15, "core.bartender", { role = 9 } },
      { 13, 3, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 29, 23, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 26, 7, "core.shopkeeper", { role = 1008, shop_rank = 10, _name = "core.locale.chara.job.goods_vendor" } },
      { 30, 4, "core.shopkeeper", { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 29, 4, "core.shopkeeper", { role = 17, _name = "core.locale.chara.job.slave_master" } },
      { 10, 6, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { 7, 15, "core.arena_master", { role = 10 } },
      { 9, 18, "core.elder", { role = 6, _name = "core.locale.chara.job.of_derphy" } },
      { 13, 18, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 5, 26, "core.wizard", { role = 5 } },
      { 3, 28, "core.informer", { role = 8 } },
      { -3, 0, "core.citizen", { _count = 4, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 4, role = 4 } },
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
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.thieves_guild.name"))

   generator.place_player()

   local charas = {
      { 21, 9, "core.sin", { role = 3, _name = "core.locale.chara.job.trainer" } },
      { 3, 6, "core.trainer", { role = 7 } },
      { 3, 12, "core.wizard", { role = 5 } },
      { 5, 18, "core.shopkeeper", { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 27, 13, "core.shopkeeper", { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 21, 19, "core.shopkeeper", { role = 1021, shop_rank = 10, _name = "core.locale.chara.job.fence" } },
      { -3, 0, "core.thief_guild_member", { _count = 16 } },
   }

   create_charas(charas)
end

-- Hardcoded behavior:
-- - creation of character based on quest (mia's dream)
function maps.palmia(generator)
   generator.load_custom("palmia")

   Map.data.max_crowd_density = 45
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 42, 27, "core.bartender", { role = 9 } },
      { 34, 3, "core.healer", { role = 12 } },
      { 22, 31, "core.arena_master", { role = 10 } },
      { 5, 15, "core.erystia", { role = 3 } },
      { 41, 11, "core.mia", { role = 3 } },
      { 5, 6, "core.conery", { role = 3 } },
      { 24, 6, "core.cleaner", { role = 3 } },
      { 15, 22, "core.cleaner", { role = 3 } },
      { 15, 22, "core.bard", { role = 3 } },
      { 48, 18, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 30, 17, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 48, 3, "core.shopkeeper", { role = 1008, shop_rank = 8, _name = "core.locale.chara.job.goods_vendor" } },
      { 42, 17, "core.shopkeeper", { role = 1001, shop_rank = 12 } },
      { 11, 14, "core.shopkeeper", { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.baker", image = 138 } },
      { 41, 3, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 41, 28, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 7, 2, "core.stersha", { role = 15, ai_calm = 3 } },
      { 6, 2, "core.xabi", { role = 15, ai_calm = 3 } },
      { 49, 11, "core.elder", { role = 6, _name = "core.locale.chara.job.of_palmia" } },
      { 30, 27, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 32, 27, "core.wizard", { role = 5 } },
      { 29, 28, "core.informer", { role = 8 } },
      { 16, 5, "core.guard", { role = 14, ai_calm = 3 } },
      { 16, 9, "core.guard", { role = 14, ai_calm = 3 } },
      { 5, 3, "core.guard", { role = 14, ai_calm = 3 } },
      { 8, 3, "core.guard", { role = 14, ai_calm = 3 } },
      { 35, 14, "core.guard", { role = 14, ai_calm = 3 } },
      { 38, 14, "core.guard", { role = 14, ai_calm = 3 } },
      { 29, 2, "core.guard", { role = 14, ai_calm = 3 } },
      { 19, 18, "core.guard", { role = 14, ai_calm = 3 } },
      { 22, 18, "core.guard", { role = 14, ai_calm = 3 } },
      { -3, 0, "core.citizen", { _count = 5, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 5, role = 4 } },
      { -3, 0, "core.guard", { _count = 4, role = 14 } },
   }

   create_charas(charas)

   generator.update_quests_in_map()

   for i=0, 25 do
      Chara.generate_from_map()
   end
end

-- Hardcoded behavior:
-- - creation of stairs based on quest (sewer sweeping)
function maps.lumiest(generator)
   generator.load_custom("lumiest")

   Map.data.max_crowd_density = 40
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 12, 24, "core.renton", { role = 3 } },
      { 21, 3, "core.balzak", { role = 3 } },
      { 5, 20, "core.lexus", { role = 3 } },
      { 28, 29, "core.cleaner", { role = 3 } },
      { 41, 19, "core.bard", { role = 3 } },
      { 32, 43, "core.bard", { role = 3 } },
      { 29, 28, "core.bard", { role = 3 } },
      { 16, 45, "core.bard", { role = 3 } },
      { 13, 24, "core.bard", { role = 3 } },
      { 41, 42, "core.bartender", { role = 9 } },
      { 10, 16, "core.healer", { role = 12 } },
      { 47, 30, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 24, 47, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 37, 30, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { 37, 12, "core.shopkeeper", { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.baker", image = 138 } },
      { 6, 15, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 33, 43, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 47, 12, "core.shopkeeper", { role = 1014, shop_rank = 5, _name = "core.locale.chara.job.fisher" } },
      { 3, 38, "core.elder", { role = 6, _name = "core.locale.chara.job.of_lumiest" } },
      { 21, 28, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 21, 30, "core.wizard", { role = 5 } },
      { 23, 38, "core.informer", { role = 8 } },
      { -3, 0, "core.citizen", { _count = 6, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 6, role = 4 } },
      { -3, 0, "core.guard", { _count = 7, role = 14 } },
   }

   create_charas(charas)

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
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.mages_guild.name"))

   generator.place_player()

   local charas = {
      { 24, 3, "core.revlus", { role = 3 } },
      { 27, 8, "core.wizard", { role = 1020, _name = "core.locale.chara.job.spell_writer" } },
      { 22, 8, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 3, 9, "core.healer", { role = 12 } },
      { 12, 6, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 3, 3, "core.wizard", { role = 5 } },
      { -3, 0, "core.mage_guild_member", { _count = 16 } },
   }

   create_charas(charas)
end

function maps.lumiest_sewer(generator)
   generator.load_custom("sqSewer")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = false
   generator.set_name(I18N.get("core.locale.map.unique.the_sewer.name"))

   generator.mark_quest_targets()

   generator.set_entrance_type("StairUp")
   generator.place_player()
end

-- Hardcoded behavior:
-- - creation of stairs based on quest (cat house)
function maps.yowyn(generator)
   generator.load_custom("yowyn")
   Map.data.max_crowd_density = 35
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 3, 17, "core.ainc", { role = 3 } },
      { 26, 11, "core.tam", { role = 3 } },
      { 14, 20, "core.gilbert_the_colonel", { role = 3 } },
      { 11, 5, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 25, 8, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 7, 8, "core.shopkeeper", { role = 1008, shop_rank = 8, _name = "core.locale.chara.job.goods_vendor" } },
      { 14, 14, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 35, 18, "core.shopkeeper", { role = 22, _name = "core.locale.chara.job.horse_master" } },
      { 33, 16, "core.lame_horse", { role = 3 } },
      { 37, 19, "core.lame_horse", { role = 3 } },
      { 34, 19, "core.yowyn_horse", { role = 3 } },
      { 38, 16, "core.yowyn_horse", { role = 3 } },
      { 3, 4, "core.elder", { role = 6, _name = "core.locale.chara.job.of_yowyn" } },
      { 20, 14, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 24, 16, "core.wizard", { role = 5 } },
      { 26, 16, "core.informer", { role = 8 } },
      { 14, 12, "core.gwen", { role = 3 } },
      { -3, 0, "core.citizen", { _count = 2, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 2, role = 4 } },
      { -3, 0, "core.guard", { _count = 3, role = 14 } },
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
   Map.data.should_regenerate = false
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
   Map.data.should_regenerate = false
   Map.data.is_temporary = true
   generator.set_name(I18N.get("core.locale.map.unique.battle_field.name"))

   generator.mark_quest_targets()

   generator.set_entrance_type("South")
   generator.place_player()

   local enemies = {}

   for _, chara in Chara.iter(57, 245) do
      if Chara.is_alive(chara) and Chara.flag(chara, "IsQuestTarget") then
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

-- Hardcoded behavior:
-- - creation of fire giant (uses serialized variable)
-- - creation of character based on quest (pael and her mom)
function maps.noyel(generator)
   generator.load_custom("noyel")

   Map.data.max_crowd_density = 35
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      -- { 46, 18, "core.ebon", { role = 3 } },
      { 47, 18, "core.moyer_the_crooked", { role = 1015 } },
      { 47, 20, "core.town_child", { role = 3 } },
      { 45, 19, "core.town_child", { role = 3 } },
      { 49, 20, "core.town_child", { role = 3 } },
      { 28, 22, "core.bard", { role = 3 } },
      { 19, 3, "core.pael", { role = 3 } },
      { 40, 33, "core.bartender", { role = 9 } },
      { 44, 6, "core.healer", { role = 12 } },
      { 44, 3, "core.nun", { role = 19 } },
      { 19, 31, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { 11, 31, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 38, 34, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 5, 27, "core.shopkeeper", { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.baker", image = 138 } },
      { 56, 5, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 39, 35, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 5, 18, "core.elder", { role = 6, _name = "core.locale.chara.job.of_noyel" } },
      { 18, 20, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 4, 33, "core.wizard", { role = 5 } },
      { 6, 33, "core.informer", { role = 8 } },
   }

   create_charas(charas)

   local chara

   for i=0,3 do
      chara = Chara.create(Rand.rnd(32), Rand.rnd(Map.height()), "core.citizen")
      chara.role = 4
      chara = Chara.create(Rand.rnd(32), Rand.rnd(Map.height()), "core.citizen2")
      chara.role = 4
   end
   for i=0,3 do
      chara = Chara.create(Rand.rnd(32), Rand.rnd(Map.height()), "core.guard")
      chara.role = 14
   end

   generator.update_quests_in_map()

   for i=0,8 do
      chara = Chara.generate_from_map(Rand.rnd(11) + 25, Rand.rnd(5) + 15, "core.town_child")
      chara.role = 3
   end
   for i=0,20 do
      Chara.generate_from_map(Rand.rnd(55), Rand.rnd(Map.height()))
   end
end

function maps.port_kapul(generator)
   generator.load_custom("kapul")

   Map.data.max_crowd_density = 40
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 15, 18, "core.raphael", { role = 3 } },
      { 36, 27, "core.arnord", { role = 3 } },
      { 5, 26, "core.icolle", { role = 3 } },
      { 29, 3, "core.doria", { role = 3 } },
      { 24, 21, "core.cleaner", { role = 3 } },
      { 12, 26, "core.cleaner", { role = 3 } },
      { 8, 11, "core.cleaner", { role = 3 } },
      { 8, 14, "core.bard", { role = 3 } },
      { 16, 17, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 23, 7, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { 32, 14, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 22, 14, "core.shopkeeper", { role = 1008, shop_rank = 10, _name = "core.locale.chara.job.goods_vendor" } },
      { 16, 25, "core.shopkeeper", { role = 1007, shop_rank = 10, _name = "core.locale.chara.job.blackmarket" } },
      { 17, 28, "core.shopkeeper", { role = 1002, shop_rank = 10, _name = "core.locale.chara.job.food_vendor" } },
      { 22, 22, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 35, 3, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 15, 15, "core.bartender", { role = 9 } },
      { 26, 3, "core.arena_master", { role = 10 } },
      { 25, 4, "core.master_of_pet_arena", { role = 11 } },
      { 8, 12, "core.elder", { role = 6, _name = "core.locale.chara.job.of_port_kapul" } },
      { 16, 4, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 14, 4, "core.wizard", { role = 5 } },
      { 17, 5, "core.informer", { role = 8 } },
      { 27, 11, "core.healer", { role = 12 } },
      { -3, 0, "core.citizen", { _count = 2, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 2, role = 4 } },
      { -3, 0, "core.sailor", { _count = 4, role = 4 } },
      { -3, 0, "core.guard_port_kapul", { _count = 5, role = 14 } },
      { 7, 6, "core.captain", { role = 4 } },
   }

   create_charas(charas)

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
   Map.data.should_regenerate = true
   generator.set_name(I18N.get("core.locale.map.unique.fighters_guild.name"))

   generator.place_player()

   local charas = {
      { 27, 4, "core.fray", { role = 3 } },
      { 28, 10, "core.healer", { role = 12 } },
      { 15, 10, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 14, 18, "core.wizard", { role = 5 } },
      { 29, 15, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { -3, 0, "core.fighter_guild_member", { _count = 16 } },
   }

   create_charas(charas)
end

-- Hardcoded behavior:
-- - setting of a quest flag (duration of kamikaze attack)
function maps.doom_ground(generator)
   generator.load_custom("sqkamikaze")

   Map.data.tileset = 0
   Map.data.is_indoors = false
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = false
   Map.data.is_temporary = true
   generator.set_name(I18N.get("core.locale.map.unique.doom_ground.name"))

   generator.set_entrance_type("Center")
   generator.place_player()

   for i=0, 10 do
      local chara = Chara.create(Chara.player().position, "core.palmian_elite_soldier")
      chara.relationship = "Friend"
      chara.original_relationship = "Friend"
   end

   generator.set_no_aggro_refresh(true)
end

-- Hardcoded behavior:
-- - creation of stairs based on quest (thieves hideout)
-- - creation of character based on quest (puppy's cave)
function maps.vernis(generator)
   generator.load_custom("vernis")

   Map.data.max_crowd_density = 40
   Map.data.is_user_map = false

   generator.place_player()

   local charas = {
      { 39, 3, "core.whom_dwell_in_the_vanity" },
      { 42, 23, "core.loyter", { role = 3 } },
      { 24, 5, "core.miches", { role = 3 } },
      { 40, 24, "core.shena", { role = 3 } },
      { 40, 25, "core.dungeon_cleaner", { role = 3 } },
      { 30, 5, "core.rilian", { role = 3 } },
      { 42, 24, "core.bard", { role = 3 } },
      { 47, 9, "core.shopkeeper", { role = 1014, shop_rank = 5, _name = "core.locale.chara.job.fisher" } },
      { 14, 12, "core.shopkeeper", { role = 1001, shop_rank = 12, _name = "core.locale.chara.job.blacksmith" } },
      { 39, 27, "core.shopkeeper", { role = 1009, shop_rank = 12, _name = "core.locale.chara.job.trader" } },
      { 10, 15, "core.shopkeeper", { role = 1006, shop_rank = 10, _name = "core.locale.chara.job.general_vendor" } },
      { 7, 26, "core.wizard", { role = 1004, shop_rank = 11, _name = "core.locale.chara.job.magic_vendor" } },
      { 14, 25, "core.shopkeeper", { role = 1005, shop_rank = 8, _name = "core.locale.chara.job.innkeeper" } },
      { 22, 26, "core.shopkeeper", { role = 1003, shop_rank = 9, _name = "core.locale.chara.job.baker", image = 138 } },
      { 28, 16, "core.wizard", { role = 5 } },
      { 38, 27, "core.bartender", { role = 9 } },
      { 6, 25, "core.healer", { role = 12 } },
      { 10, 7, "core.elder", { role = 6, _name = "core.locale.chara.job.of_vernis" } },
      { 27, 16, "core.trainer", { role = 7, _name = "core.locale.chara.job.trainer" } },
      { 25, 16, "core.informer", { role = 8 } },
      { -3, 0, "core.citizen", { _count = 4, role = 4 } },
      { -3, 0, "core.citizen2", { _count = 4, role = 4 } },
      { -3, 0, "core.guard", { _count = 4, role = 14 } },
   }

   create_charas(charas)

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
   Map.data.should_regenerate = false
   generator.set_name(I18N.get("core.locale.map.unique.the_mine.name"))

   generator.mark_quest_targets()

   generator.place_player()
end

function maps.robbers_hideout(generator)
   generator.load_custom("sqRogue")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = false
   generator.set_name(I18N.get("core.locale.map.unique.robbers_hideout.name"))

   generator.mark_quest_targets()

   generator.place_player()
end

function maps.test_site_vernis(generator)
   generator.load_custom("sqNightmare")

   Map.data.tileset = 0
   Map.data.is_indoors = true
   Map.data.type = "Dungeon"
   Map.data.max_crowd_density = 0
   Map.data.bgm = "core.mcPuti"
   Map.data.should_regenerate = false
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
      local item = Item.create(-1, -1, "core.dead_tree", 0)
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
      local item = Item.create(-1, -1, { flttypemajor = 80000 })
      item.own_state = 1
   end
end

-- Hardcoded behavior:
-- - creation of random encounters
function maps.fields(generator)
   Map.data.max_crowd_density = 4
   Map.data.is_user_map = false
   generator.create(34, 22)

   for j=0, Map.height()-1 do
      for i=0, Map.width()-1 do
         Map.set_tile(i, j, Map.generate_tile("Normal"))
      end
   end

   generator.set_name("")

   local stood_tile = generator.stood_world_map_tile()

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

-- Hardcoded behavior:
-- - setting of next boss floor every 5 floors
-- - creation of random boss every 5 floors
function maps.the_void(generator)
   generator.generate_nefia()
end

-- Hardcoded behavior:
-- - quest event when deepest level is reached
-- - creation of stairs when deepest level is reached
function maps.lesimas(generator)
   generator.set_tileset(Map.data.tileset)

   if generator.is_deepest_level() then
      generator.load_custom("lesimas_1")

      Map.data.max_crowd_density = 0
      Map.data.is_temporary = true
      Map.data.bgm = "core.mcLastBoss"
      generator.set_name(I18N.get_enum_property("core.locale.map.unique", "the_depth", 3))

      generator.set_stair_up_pos(16, 13)
      generator.place_player()

      if Chara.kill_count("core.zeome") == 0 then
         Chara.create(16, 6, "core.zeome")
      elseif Chara.kill_count("core.orphe") == 0 then
         Chara.create(16, 6, "core.orphe")
      end
   else
      generator.generate_nefia()

      if Map.current_dungeon_level() == 3 then
         local chara = Chara.create(Chara.player().position, "core.slan")
         chara.role = 3
         chara.ai_calm = 3
      end
      if Map.current_dungeon_level() == 17 then
         local chara = Chara.create(Chara.player().position, "core.karam")
         chara.role = 3
         chara.ai_calm = 3
      end
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
         generator.generate_nefia()
      end
   end
end

maps.tower_of_fire = dungeon_with_boss("firet1")
maps.crypt_of_the_damned = dungeon_with_boss("undeadt1")
maps.ancient_castle = dungeon_with_boss("roguet1")
maps.dragons_nest = dungeon_with_boss("d_1")

-- Hardcoded behavior:
-- - creation of character based on quest (puppy's cave)
function maps.puppy_cave(generator)
   generator.generate_nefia()
end

-- Hardcoded behavior:
-- - creation of character based on quest (minotaur king)
function maps.minotaurs_nest(generator)
   generator.generate_nefia()
end

-- Hardcoded behavior:
-- - creation of character based on quest (novice knight)
function maps.yeeks_nest(generator)
   generator.generate_nefia()
end

function maps.pyramid(generator)
   if Map.current_dungeon_level() == 20 then
      generator.load_custom("sqPyramid")
      Map.data.max_crowd_density = 40
      Map.data.bgm = "core.mcPuti"
      generator.place_player()
      for i=0, Map.data.max_crowd_density + 1 do
         Chara.generate_from_map()
      end
   elseif Map.current_dungeon_level() == 21 then
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
   -- Internally, nefia generation is affected by the global quest ID.
   generator.generate_nefia()
end

-- Hardcoded behavior:
-- - handling of dungeon lord at lowest level
function maps.random_dungeon(generator)
   generator.generate_nefia()
end

function maps.show_house()
   -- no-op
end

return maps
