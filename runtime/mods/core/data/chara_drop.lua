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
      Item.create(chara.position, "core.wallet", 0)
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
         name = "rich_person",
         drops = { make_lootrich(8) }
      },
      {
         name = "noble_child",
         drops = { make_lootrich(4) }
      },
      {
         name = "tourist",
         drops = { make_lootrich(2) }
      },
      {
         name = "vesda",
         drops = {{ id = "core.gloves_of_vesda" }}
      },
      {
         name = "god_boss",
         on_generate = function(args)
            -- Kill count is 1 by now on first kill.
            if Chara.kill_count(args.chara.new_id) == 1 then
               return make_drops({ "core.rod_of_wishing", "core.artifact_seed" })
            else
               return make_drops({ "core.artifact_seed",  "core.artifact_seed" })
            end
         end
      },
      {
         name = "tuwen",
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
         name = "rabbit",
         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      {
         name = "zombie",
         drops = {{ one_in = 100, id = "core.potion_of_descent" }}
      },
      {
         name = "lomias",
         drops = {{ one_in = 4,   id = "core.secret_experience_of_lomias" }}
      },
      {
         name = "mummy",
         drops = {{ one_in = 300, id = "core.book_of_resurrection" }}
      },
      {
         name = "cupid_of_love",
         drops = {{ one_in = 140, id = "core.happy_bed" }}
      },
      {
         name = "hermit_crab",
         drops = {{ one_in = 100, id = "core.solemn_tomb" }}
      },
      {
         name = "rogue",
         drops = {{ one_in = 90, id = "core.blue_capsule_drug" }}
      },
      {
         name = "executioner",
         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      {
         name = "deformed_eye",
         drops = {{ one_in = 150, id = "core.potion_of_evolution" }}
      },
      {
         name = "gwen",
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
         name = "fairy",
         drops = {{ one_in = 200, id = "core.secret_experience_of_kumiromi" }}
      },
      {
         name = "mine_dog",
         drops = {{ one_in = 3, id = "core.mine" }}
      },
      {
         name = "imp",
         drops = {{ one_in = 600, id = "core.scroll_of_name" }}
      },
      {
         name = "rogue_boss",
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
         name = "silver_bell",
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
         name = "gold_bell",
         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.gold_piece", 2500 + Rand.rnd((Chara.player().fame + 1000)))
               end
         }}
      },
      {
         name = "the_leopard_warrior",
         drops = {{
               on_create = function(args)
                  for _=0,12 do
                     local item = Item.create(args.chara.position, "core.tomato", 1, { nostack = true })
                     if item and Rand.coinflip() then
                        item.param3 = -1
                        item.image = 336
                     end
                  end
               end
         }}
      }
})
