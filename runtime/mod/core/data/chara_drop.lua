local Chara = ELONA.require("core.Chara")
local Item = ELONA.require("core.Item")
local Map = ELONA.require("core.Map")
local Rand = ELONA.require("core.Rand")

-- Returns 'drops' table from array of item IDs.
local function make_drops(ids)
   local result = {}
   for _, v in ipairs(ids) do
      result[#result+1] = { id = v }
   end
   return result
end


local function lootrich(chara, count)
   for _ = 1, count do
      Item.create(chara.position, {level = chara.level, flttypeminor = 77001});
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


--[[
Items that characters drop can be specified here.

Fields:
  drops:
    array of droppable items.
  on_generate:
    a function for programatically generating the "drops" table. It
    is called with these arguments.
      chara: character that was killed.

Each item of "drops" can have these properties.
  one_in: chance item is created.
  id: string ID of item to create.
  level: approximate level of item, which is calculated with calcobjlv().
  quality: approximate quality of item, which is calculated with calcfixlv().
  flttypemajor: filter category.
  flttypeminor: filter category.
  on_create: a function called with these arguments.
    chara: character that was killed.
--]]

data:define_type("chara_drop")
data:add_multi(
   "core.chara_drop",
   {
      {
         id = "rich_person",
         drops = { make_lootrich(8) }
      },
      {
         id = "noble_child",
         drops = { make_lootrich(4) }
      },
      {
         id = "tourist",
         drops = { make_lootrich(2) }
      },
      {
         id = "vesda",
         drops = {{ id = "core.gloves_of_vesda" }}
      },
      {
         id = "god_boss",
         on_generate = function(args)
            -- Kill count is 1 by now on first kill.
            if Chara.kill_count(args.chara.id) == 1 then
               return make_drops({ "core.rod_of_wishing", "core.artifact_seed" })
            else
               return make_drops({ "core.artifact_seed",  "core.artifact_seed" })
            end
         end
      },
      {
         id = "tuwen",
         on_generate = function()
            if Map.id() == "core.pyramid" then
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
         id = "rabbit",
         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      {
         id = "zombie",
         drops = {{ one_in = 100, id = "core.potion_of_descent" }}
      },
      {
         id = "lomias",
         drops = {{ one_in = 4,   id = "core.secret_experience_of_lomias" }}
      },
      {
         id = "mummy",
         drops = {{ one_in = 300, id = "core.book_of_resurrection" }}
      },
      {
         id = "cupid_of_love",
         drops = {{ one_in = 140, id = "core.happy_bed" }}
      },
      {
         id = "hermit_crab",
         drops = {{ one_in = 100, id = "core.solemn_tomb" }}
      },
      {
         id = "rogue",
         drops = {{ one_in = 90, id = "core.blue_capsule_drug" }}
      },
      {
         id = "executioner",
         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      {
         id = "deformed_eye",
         drops = {{ one_in = 150, id = "core.potion_of_evolution" }}
      },
      {
         id = "gwen",
         drops = {{
               one_in = 50,
               on_create = function(args)
                  local item = Item.create(args.chara.position, "core.secret_treasure")
                  if item then
                     item.param1 = 169
                  end
               end
         }}
      },
      {
         id = "fairy",
         drops = {{ one_in = 200, id = "core.secret_experience_of_kumiromi" }}
      },
      {
         id = "mine_dog",
         drops = {{ one_in = 3, id = "core.mine" }}
      },
      {
         id = "imp",
         drops = {{ one_in = 600, id = "core.scroll_of_name" }}
      },
      {
         id = "rogue_boss",
         drops = {{
               on_create = function(args)
                  for _=0, 2 + Rand.rnd(4) do
                     local item = Item.create(args.chara.position,
                                            {
                                               level = args.chara.level,
                                               flttypemajor = 92000,
                                               quality = "good",
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
         id = "silver_bell",
         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.platinum_coin", 1 + Rand.rnd(3))
                  if Rand.coinflip() then
                     Item.create(args.chara.position, "core.small_medal")
                  end
               end
         }}
      },
      {
         id = "gold_bell",
         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.gold_piece", 2500 + Rand.rnd_capped(Chara.player().fame + 1000))
               end
         }}
      },
      {
         id = "the_leopard_warrior",
         drops = {{
               on_create = function(args)
                  for _=0,12 do
                     local item = Item.create(args.chara.position,
                                              {
                                                 id = "core.tomato",
                                                 number = 1,
                                                 nostack = true
                                              }
                     )
                     if item and Rand.coinflip() then
                        item.param3 = -1
                        item.image = 336
                     end
                  end
               end
         }}
      }
})
