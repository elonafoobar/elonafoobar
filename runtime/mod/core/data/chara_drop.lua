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

ELONA.data:define_prototype("chara_drop")
ELONA.data:add(
   "core.chara_drop",
   {
      rich_person = {
         drops = { make_lootrich(8) }
      },
      noble_child = {
         drops = { make_lootrich(4) }
      },
      tourist = {
         drops = { make_lootrich(2) }
      },
      vesda = {
         drops = {{ id = "core.gloves_of_vesda" }}
      },
      god_boss = {
         on_generate = function(args)
            -- Kill count is 1 by now on first kill.
            if Chara.kill_count(args.chara.id) == 1 then
               return make_drops({ "core.rod_of_wishing", "core.artifact_seed" })
            else
               return make_drops({ "core.artifact_seed",  "core.artifact_seed" })
            end
         end
      },
      tuwen = {
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
      rabbit = {
         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      zombie = {
         drops = {{ one_in = 100, id = "core.potion_of_descent" }}
      },
      lomias = {
         drops = {{ one_in = 4,   id = "core.secret_experience_of_lomias" }}
      },
      mummy = {
         drops = {{ one_in = 300, id = "core.book_of_resurrection" }}
      },
      cupid_of_love = {
         drops = {{ one_in = 140, id = "core.happy_bed" }}
      },
      hermit_crab = {
         drops = {{ one_in = 100, id = "core.solemn_tomb" }}
      },
      rogue = {
         drops = {{ one_in = 90, id = "core.blue_capsule_drug" }}
      },
      executioner = {
         drops = {{ one_in = 200, id = "core.rabbits_tail" }}
      },
      deformed_eye = {
         drops = {{ one_in = 150, id = "core.potion_of_evolution" }}
      },
      gwen = {
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
      fairy = {
         drops = {{ one_in = 200, id = "core.secret_experience_of_kumiromi" }}
      },
      mine_dog = {
         drops = {{ one_in = 3, id = "core.mine" }}
      },
      imp = {
         drops = {{ one_in = 600, id = "core.scroll_of_name" }}
      },
      rogue_boss = {
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
      silver_bell = {
         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.platinum_coin", 1 + Rand.rnd(3))
                  if Rand.coinflip() then
                     Item.create(args.chara.position, "core.small_medal")
                  end
               end
         }}
      },
      gold_bell = {
         drops = {{
               on_create = function(args)
                  Item.create(args.chara.position, "core.gold_piece", 2500 + Rand.rnd_capped(Chara.player().fame + 1000))
               end
         }}
      },
      the_leopard_warrior = {
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
   }
)
