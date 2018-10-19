local Chara = Elona.require("Chara")
local Item = Elona.require("Item")
local Map = Elona.require("Map")
local Rand = Elona.require("Rand")

-- Returns 'drops' table from array of item IDs.
local function make_drops(ids)
   local result = {}
   for _, v in ipairs(ids) do
      result[#result+1] = { id = v }
   end
   return result
end


local function lootrich(chara, count)
   for _=0,count do
      Item.roll(chara.position, {level = chara.level, flttypeminor = 77001});
   end
   if Rand.one_in(3) then
      Item.create(chara.position, "core.wallet")
   end
end

local function make_lootrich(count)
   return
      {
         on_create = function(args)
            lootrich(args.chara, count)
         end
      }
end


local function assert_type(it, field, ty)
   assert(it[field])
   assert(type(it[field]) == ty)
end

local function assert_type_opt(it, field, ty)
   if it[field] then
      assert(type(it[field]) == ty)
   end
end

local function validator(it)
   assert_type(it, "drops", "table")
   assert_type_opt(it, "on_generate", "function")

   for k, v in ipairs(it.drops) do
      assert(type(v) == "table")
      assert_type_opt(v, "one_in", "number")

      -- Creation callback
      assert_type_opt(v, "on_create", "function")

      -- Specific string ID
      assert_type_opt(v, "id", "string")

      -- Generation from flt()
      assert_type_opt(v, "level", "number")
      assert_type_opt(v, "flttypemajor", "number")
      assert_type_opt(v, "flttypeminor", "number")
      assert_type_opt(v, "quality", "string")
   end
end

data:define_type("chara_drop", validator)
data:add_multi(
   "core.chara_drop",
   {
      {
         name = "183",
         drops = make_lootrich(8)
      },
      {
         name = "184",
         drops = make_lootrich(4)
      },
      {
         name = "185",
         drops = make_lootrich(2)
      },
      {
         name = "140",
         drops = {{ id = "core.gloves_of_vesda" }}
      },
      {
         name = "175_177_178",
         _ids = { 175, 177, 178 },
         on_generate = function(args)
            -- NOTE: chara will be dead/invalid at this point...
            if Chara.kill_count(args.chara.id) == 0 then
               return make_drops({ "core.rod_of_wishing", "core.artifact_seed" })
            else
               return make_drops({ "core.artifact_seed",  "core.artifact_seed" })
            end
         end
      },
      {
         name = "tuwen",
         _ids = 257,
         on_generate = function()
            if Map.id() == 257 then
               return make_drops({ "core.statue_of_opatos",
                                   "core.platinum_coin",
                                   "core.platinum_coin",
                                   "core.platinum_coin",
                                   "core.platinum_coin",
                                   "core.treasure_map" })
            end
            return {}
         end
      },
      {
         name = "5",

         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      {
         name = "21",

         drops = {{ one_in = 100, id = "core.potion_of_descent" }}
      },
      {
         name = "34",

         drops = {{ one_in = 4,   id = "core.secret_experience_of_lomias" }}
      },
      {
         name = "99_100_101",
         _ids = { 99, 100, 101 },

         drops = {{ one_in = 300, id = "core.book_of_resurrection" }}
      },
      {
         name = "117",

         drops = {{ one_in = 140, id = "core.happy_bed" }}
      },
      {
         name = "168",

         drops = {{ one_in = 100, id = "core.solemn_tomb" }}
      },
      {
         name = "302_303_304_305",
         _ids = { 302, 303, 304, 305 },

         drops = {{ one_in = 90, id = "core.blue_capsule_drug" }}
      },
      {
         name = "307_308",
         _ids = { 307, 308 },

         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      {
         name = "189_190",
         _ids = { 189, 190 },

         drops = {{ one_in = 150, id = "core.potion_of_evolution" }}
      },
      {
         name = "213",

         drops = {{
               one_in = 50,
               on_create = function(args)
                  local item = Item.create(args.chara.position, "core.secret_treasure", 0)
                  if item then
                     item.param1 = 169
                  end
               end
         }}
      },
      {
         name = "250",

         drops = {{ one_in = 200, id = "core.secret_experience_of_kumiromi" }}
      },
      {
         name = "341",

         drops = {{ one_in = 3, id = "core.mine" }}
      },
      {
         name = "85_86_87",
         _ids = { 85, 86, 87 },

         drops = {{ one_in = 600, id = "core.scroll_of_name" }}
      },
      {
         name = "302",

         drops = {{
               on_create = function(args)
                  for _=0, 2 + Rand.rnd(4) do
                     local item = Item.roll(args.chara.position,
                                            {
                                               level = args.chara.level,
                                               flttypemajor = 92000,
                                               quality = "Good",
                                               nostack = true
                                            }
                     )
                     if item then
                        item.number = Rand.rnd(5) + 1
                     end
                  end
               end
         }}
      },
      {
         name = "328",

         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.platinum_coin", 1 + Rand.rnd(3))
                  if Rand.coinflip() then
                     Item.create(args.chara.position, "core.small_medal", 0)
                  end
               end
         }}
      },
      {
         name = "329",

         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.gold_piece", 2500 + Rand.rnd((Chara.player().fame + 1000)))
               end
         }}
      },
      {
         name = "351_352",
         _ids = { 351, 352 },

         drops = {{
               on_create = function(args)
                  for _=0,12 do
                     -- nostack = 1
                     local item = Item.create(args.chara.position, "core.tomato")
                     if item and Rand.coinflip() then
                        item.param3 = -1
                        item.image = 336
                     end
                  end
               end
         }}
      }
})
