local Rand = Elona.require("Rand")
local Item = Elona.require("Item")
local Math = Elona.require("Math")
local World = Elona.require("World")

local function make_id_list(list)
   for i, v in ipairs(list) do
      list[i] = { index = i - 1, id = v }
   end
   return list
end

local deed_items = make_id_list({344, 521, 522, 542, 543, 555, 572})
local medal_items = make_id_list({430, 431, 502, 480, 421, 603, 615,
                                  559, 516, 616, 623, 505, 624, 625,
                                  626, 627, 56, 742, 760})

local merchant_rules = {
   { flttypemajor = "core.wear", fixlv = "Great" },
   { one_in = 2, fixlv = "Miracle" },
}

local function merchant_item_count()
   return 4 + Rand.rnd(4)
end

-- Shop inventories are primarily defined using the "rules" field,
-- which is an array of rules to apply to a generated item. Each rule
-- is applied _in order_. This allows inserting/removing values or
-- altering probabilities without needing to create a new generation
-- function every time.
--
-- Rule predicates:
--   one_in = 5
--     the property is applied one out of every 5 times. If not
--     provided, it is assumed to be 1, e.g. always apply the
--     properties provided. Equivalent to rnd(5) == 0.
--   all_but_one_in = 5
--     the property is always applied except one out of every 5 times.
--     Equivalent to rnd(5) != 0.
--   index = 2
--     the property is always applied when the 2nd item is being
--     generated. Use for defining a set array of items to create.
--   predicate = function(args) return args.index > 10 end
--     a function, to which the following arguments are passed as a
--     table. If it returns true, the properties are applied.
--       index: index of the item being generated.
--       shopkeeper: character who is the shopkeeper.
--
-- Properties:
--   id: string id of the item. If it equals "Stop", no more rules are
--       applied.
--   flttypeminor: either a number or string ID of a core.filter_set to use
--   flttypemajor: either a number or string ID of a core.filter_set to use
--   fixlv: string enum indicating quality.
--   fltn: used with fltn().
--   choice: an array of properties. one out of the set of properties
--           provided will be applied.
--   on_generate: a function that will have a table of arguments passed to it.
--     index: index of the item being generated.
--     shopkeeper: character who is the shopkeeper.


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
            { choice = {{flttypeminor = 52001}, {flttypemajor = 53000}, {flttypemajor = 52000}} },
            { one_in = 7, flttypemajor = 54000 },
            { one_in = 15, flttypemajor = 55000 },
            { one_in = 20, id = 783 },
         }
      },
      {
         name = "younger_sister_of_mansion",
         id = 1019,
         rules = {
            { id = 667 }
         }
      },
      {
         name = "spell_writer",
         id = 1020,
         rules = {
            {
               on_generate = function()
                  local reserved = {}
                  for k, def in pairs(data.raw["core.item"]) do
                     if Item.memory(k, 2) > 1 then
                        reserved[#reserved+1] = def.id
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
            { choice = {{flttypemajor = 59000}, {flttypemajor = 32000}, {flttypemajor = 34000}} },
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
               choice = {
                  {flttypemajor = 25000},
                  {flttypemajor = 60000},
                  {flttypemajor = 20000},
                  {flttypemajor = 77000},
                  {flttypemajor = 59000}
               }
            },
            { one_in = 20, id = 734 },
            { one_in = 8, flttypemajor = 91000 },
            { one_in = 10, id_set = "core.deed" },
         }
      },
      {
         name = "bakery",
         id = 1003,
         rules = {
            { all_but_one_in = 3, id = "Stop" }, -- rnd(3) != 0
            { choice = {{flttypeminor = 57001}, {flttypeminor = 57001}, {flttypeminor = 57002}}},
         }
      },
      {
         name = "food_vendor",
         id = 1002,
         rules = {
            { all_but_one_in = 3, id = "Stop" }, -- rnd(3) != 0
            { flttypemajor = 57000 },
            { one_in = 5, flttypemajor = 91000 },
         }
      },
      {
         name = "blackmarket",
         id = 1007,
         rules = {
            { flttypemajor = "core.wear" },
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
         id = 2003, -- NOTE: only shop ID for which (id / 1000) != 1.
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
            { one_in = 3, flttypemajor = "core.wear" },
            { one_in = 3, flttypemajor = 60000 },
            { one_in = 5, flttypemajor = 57000 },
            { one_in = 4, flttypemajor = 53000 },
            { one_in = 15, flttypemajor = 55000 },
            { one_in = 10, flttypemajor = 91000 },
            { one_in = 10, choice = deed_items },
            { one_in = 15, id = 511 },
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
            { one_in = 3, choices = {{flttypemajor = 10000}, {flttypemajor = 24000}, {flttypemajor = 24000}} }
         }
      },
      {
         name = "trader",
         id = 1009,
         rules = {
            { flttypemajor = 92000 }
         }
      },
      {
         name = "the_fence",
         id = 1021,
         rules = {
            { flttypemajor = 59000 },
            { one_in = 2, id = 636 },
            { one_in = 2, id = 629 },
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
            { one_in = 3, choice = deed_items },
            { one_in = 5, id = 511 },
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
            { one_in = 12, id = 750 },
            { one_in = 12, id = 751 },
            { one_in = 5, id = 770 },
            { one_in = 12, id = 762 },
            { one_in = 12, id = 768 },
            { one_in = 12, id = 769 },
         }
      },
      {
         name = "dye_vendor",
         id = 1017,
         rules = {
            { id = 519 }
         }
      },
      {
         name = "sales_person_b",
         id = 1012,
         rules = {
            { flttypemajor = 60000 },
            { index = 0, id = 510 },
            { index = 1, id = 561 },
            { index = 2, id = 562 },
            { index = 3, id = 547 },
            { index = 4, id = 579 },
            { index = 5, id = 576 },
            { index = 6, id = 611 },
            { predicate = function(args) return args.index > 10 and not Rand.one_in(3) end, id = "Stop" },
            { index = 19, id = 413 },
            { index = 20, id = 414 },
            { index = 21, id = 616 },
         },
         flttypemajor_for_item_count = 60000,
      },
      {
         name = "fisher",
         id = 1014,
         rules = {
            { id = 617 }
         }
      },
      {
         name = "miral",
         id = 1016,
         rules = medal_items,
         on_generate_item = function(args)
            args.item.number = 1
            args.item.curse_state = "None"
            if args.item.new_id == "core.rod_of_domination" then
               args.item.count = 4
            end
            return true -- skip rest
         end
      }
})
