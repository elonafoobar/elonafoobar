local Rand = Elona.require("Rand")
local Item = Elona.require("Item")
local Math = Elona.require("Math")
local World = Elona.require("World")

local function make_choices_list(list, id)
   for i, v in ipairs(list) do
      list[i] = { index = i - 1 }
      list[i][id] = v
   end
   return list
end

local function make_id_list(list)
   return make_choices_list(list, "id")
end

local function make_filter_list(list)
   return make_choices_list(list, "flttypemajor")
end

local deed_items = make_id_list(
   {
      "core.deed",
      "core.deed_of_museum",
      "core.deed_of_shop",
      "core.deed_of_farm",
      "core.deed_of_storage_house",
      "core.shelter",
      "core.deed_of_ranch"
   }
)

local medal_items = make_id_list(
   {
      "core.scroll_of_growth",
      "core.scroll_of_faith",
      "core.scroll_of_superior_material",
      "core.rod_of_domination",
      "core.artifact_seed",
      "core.presidents_chair",
      "core.bill",
      "core.potion_of_cure_corruption",
      "core.bottle_of_water",
      "core.tax_masters_tax_box",
      "core.cat_sisters_diary",
      "core.little_sisters_diary",
      "core.girls_diary",
      "core.shrine_gate",
      "core.bottle_of_hermes_blood",
      "core.sages_helm",
      "core.diablo",
      "core.license_of_the_void_explorer",
      "core.garoks_hammer"
   }
)

-- NOTE: duplicated from fsetwear.
local filter_set_wear = make_filter_list({10000, 10000, 24000, 24000,
                                          25000, 12000, 16000, 20000,
                                          19000, 18000, 22000, 14000,
                                          32000, 34000})

local merchant_rules = {
   { choices = filter_set_wear },
   { fixlv = "Great" },
   { one_in = 2, fixlv = "Miracle" },
}

local function merchant_item_count()
   return 4 + Rand.rnd(4)
end

--[[
Shop inventory generation is defined using the "rules" field, which is
an array of rules to apply to a generated item. Each rule consists of
one or zero predicates and some properties used in the generation of
the item. This allows inserting/removing values or altering
probabilities without needing to create a new generation function
every time.

Some notes:
  - Each rule is applied in order of definition in the "rules"
    list.
  - Only the first predicate found in each rule will be applied. If
    no predicates are found, the rule is always applied.

Rule predicates:
  index = 2
    the property is always applied when the 2nd item is being
    generated. Use for defining a set array of items to create.
  one_in = 5
    the property is applied one out of every 5 times. Equivalent to
    rnd(5) == 0.
  all_but_one_in = 5
    the property is always applied except one out of every 5 times.
    Equivalent to rnd(5) != 0.
  predicate = function(args) return args.index > 10 end
    a function, to which the following arguments are passed as a
    table. If it returns true, the properties are applied.
      index: index of the item being generated.
      shopkeeper: character who is the shopkeeper.

Available properties:
  id: string id of the item. If it equals "Stop", skip generation
      of an item this cycle.
  flttypeminor: number.
  flttypemajor: number.
  fixlv: string enum indicating quality.
  fltn: used with fltn().
  choices: an array of properties. one out of the set of properties
           provided will be applied.
  on_generate: a function that will have a table of arguments passed to it.
    index: index of the item being generated.
    shopkeeper: character who is the shopkeeper.
]]

-- NOTE: "id" must be the same as a character role, and between
-- [1000,1999]. (2003 is special-cased.)
data:define_type("shop_inventory")
data:add_multi(
   "core.shop_inventory",
   {
      {
         name = "magic_vendor",
         id = 1004,
         rules = {
            {
               choices = {
                  {flttypeminor = 52001},
                  {flttypemajor = 53000},
                  {flttypemajor = 52000},
               }
            },
            { one_in = 7, flttypemajor = 54000 },
            { one_in = 15, flttypemajor = 55000 },
            { one_in = 20, id = "core.recipe" },
         }
      },
      {
         name = "younger_sister_of_mansion",
         id = 1019,
         rules = {
            { id = "core.sisters_love_fueled_lunch" }
         }
      },
      {
         name = "spell_writer",
         id = 1020,
         rules = {
            {
               on_generate = function()
                  local reserved = {}
                  for item_id, _ in pairs(data.raw["core.item"]) do
                     if Item.memory(item_id, 2) > 1 then
                        reserved[#reserved+1] = item_id
                     end
                  end

                  if #reserved == 0 then
                     return
                  end

                  return { id = Rand.choice(reserved) }
               end
            }
         },
         item_price = function(args)
            return args.item.value * 3 / 2
         end
      },
      {
         name = "moyer",
         id = 1015,
         rules = {
            {
               choices = {
                  {flttypemajor = 59000},
                  {flttypemajor = 32000},
                  {flttypemajor = 34000},
               }
            },
            { one_in = 3, fixlv = "Great" },
            { one_in = 10, fixlv = "Miracle" },
         },
         item_price = function(args)
            return args.item.value * 2
         end
      },
      {
         name = "general_vendor",
         id = 1006,
         rules = {
            {
               choices = {
                  {flttypemajor = 25000},
                  {flttypemajor = 60000},
                  {flttypemajor = 20000},
                  {flttypemajor = 77000},
                  {flttypemajor = 59000},
               }
            },
            { one_in = 20, id = "core.small_gamble_chest" },
            { one_in = 8, flttypemajor = 91000 },
            { one_in = 10, choices = deed_items },
         }
      },
      {
         name = "bakery",
         id = 1003,
         rules = {
            { all_but_one_in = 3, id = "Stop" },
            {
               choices = {
                  {flttypeminor = 57001},
                  {flttypeminor = 57001},
                  {flttypeminor = 57002},
               }
            },
         }
      },
      {
         name = "food_vendor",
         id = 1002,
         rules = {
            { all_but_one_in = 3, id = "Stop" },
            { flttypemajor = 57000 },
            { one_in = 5, flttypemajor = 91000 },
         }
      },
      {
         name = "blackmarket",
         id = 1007,
         rules = {
            { choices = filter_set_wear },
            { one_in = 3, fixlv = "Great" },
            { one_in = 10, fixlv = "Miracle" },
         },
         item_count = function(args)
            return 6 + args.shopkeeper.shop_rank / 10
         end,
         item_price = function(args)
            if World.belongs_to_guild("thieves") then
               return args.item.value * 2
            else
               return args.item.value * 3
            end
         end
      },
      {
         name = "wandering_merchant",
         id = 1010,
         rules = merchant_rules,
         item_count = merchant_item_count,
         item_price = function(args)
            return args.item.value * 2
         end
      },
      {
         name = "visiting_merchant",
         id = 2003, -- NOTE: the only shop ID for which (id / 1000) != 1.
         rules = merchant_rules,
         item_count = merchant_item_count,
         item_price = function(args)
            return args.item.value * 4 / 5
         end
      },
      {
         name = "innkeeper",
         id = 1005,
         rules = {
            { flttypemajor = 56000 },
            { one_in = 3, choices = filter_set_wear },
            { one_in = 3, flttypemajor = 60000 },
            { one_in = 5, flttypemajor = 57000 },
            { one_in = 4, flttypemajor = 53000 },
            { one_in = 15, flttypemajor = 55000 },
            { one_in = 10, flttypemajor = 91000 },
            { one_in = 10, choices = deed_items },
            { one_in = 15, id = "core.deed_of_heirship" },
         }
      },
      {
         name = "blacksmith",
         id = 1001,
         rules = {
            {
               choices = {
                  {flttypemajor = 16000},
                  {flttypemajor = 12000},
                  {flttypemajor = 22000},
                  {flttypemajor = 18000},
                  {flttypemajor = 14000},
                  {flttypemajor = 19000},
               }
            },
            {
               one_in = 3,
               choices = {
                  {flttypemajor = 10000},
                  {flttypemajor = 24000},
                  {flttypemajor = 24000},
               }
            }
         }
      },
      {
         name = "trader",
         id = 1009,
         rules = {
            { flttypemajor = 92000 },
         }
      },
      {
         name = "the_fence",
         id = 1021,
         rules = {
            { flttypemajor = 59000 },
            { one_in = 2, id = "core.lockpick" },
            { one_in = 2, id = "core.disguise_set" },
         }
      },
      {
         name = "sales_person_a",
         id = 1011,
         rules = {
            { one_in = 4, flttypemajor = 24000 },
            { one_in = 5, flttypemajor = 24000 },
            { one_in = 3, flttypemajor = 57000 },
            { fltn = "sf" },
         }
      },
      {
         name = "sales_person_c",
         id = 1013,
         rules = {
            { all_except_one_in = 3, id = "Stop" },
            { flttypemajor = 55000 },
            { one_in = 3, choices = deed_items },
            { one_in = 5, id = "core.deed_of_heirship" },
         }
      },
      {
         name = "souvenir_vendor",
         id = 1018,
         ignores_noshop = true,
         rules = {
            { fltn = "spshop" },
         },
         item_price = function(args)
            local price = Math.clamp(args.item.value, 1, 1000000) * 50
            if args.item.new_id == "core.gift" then
               price = price * 10
            end
            return price
         end
      },
      {
         name = "street_vendor",
         id = 1022,
         rules = {
            { fltn = "fest" },
            { one_in = 12, id = "core.upstairs" },
            { one_in = 12, id = "core.downstairs" },
            { one_in = 5, id = "core.bottle_of_soda" },
            { one_in = 12, id = "core.festival_wreath" },
            { one_in = 12, id = "core.new_years_decoration" },
            { one_in = 12, id = "core.miniature_tree" },
         }
      },
      {
         name = "dye_vendor",
         id = 1017,
         rules = {
            { id = "core.bottle_of_dye" },
         }
      },
      {
         name = "sales_person_b",
         id = 1012,
         rules = {
            { flttypemajor = 60000 },
            { index = 0, id = "core.microwave_oven" },
            { index = 1, id = "core.shop_strongbox" },
            { index = 2, id = "core.register" },
            { index = 3, id = "core.salary_chest" },
            { index = 4, id = "core.freezer" },
            { index = 5, id = "core.playback_disc" },
            { index = 6, id = "core.house_board" },
            { predicate = function(args) return args.index > 10 and not Rand.one_in(3) end, id = "Stop" },
            { index = 19, id = "core.red_treasure_machine" },
            { index = 20, id = "core.blue_treasure_machine" },
            { index = 21, id = "core.tax_masters_tax_box" },
         },
      },
      {
         name = "fisher",
         id = 1014,
         rules = {
            { id = "core.bait" }
         }
      },
      {
         name = "miral",
         id = 1016,
         rules = medal_items,
         item_count = function() return #medal_items end,
         on_generate_item = function(args)
            args.item.number = 1
            args.item.curse_state = "None"
            if args.item.new_id == "core.rod_of_domination" then
               args.item.count = 4
            end
         end
      }
})
