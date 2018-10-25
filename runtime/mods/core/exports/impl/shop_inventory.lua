local Item = Elona.require("Item")
local Math = Elona.require("Math")
local Chara = Elona.require("Chara")
local Skill = Elona.require("Skill")
local Rand = Elona.require("Rand")

local shop_inventory = {}

function shop_inventory.default_item_number(args)
   return Math.min(80, 20 + args.shopkeeper.shop_rank / 2)
end

function shop_inventory.test_rule_predicate(rule, index, shopkeeper)
   if rule.index then
      return index == rule.index
   end
   if rule.one_in then
      return Rand.one_in(rule.one_in)
   end
   if rule.all_but_one_in then
      return not Rand.one_in(rule.all_but_one_in)
   end
   if rule.predicate then
      return rule.predicate({index = index, shopkeeper = shopkeeper}) == true
   end

   return true
end

function shop_inventory.apply_rule_properties(rule, ret, index, shopkeeper)
   for k, v in pairs(rule) do
      -- Apply "choices" and "on_generate" after the other properties
      -- have been copied.
      -- NOTE: The predicate fields get copied too, but are ignored by
      -- Item.create().
      if k ~= "choices" and k ~= "on_generate" then
         ret[k] = v
      end
   end

   if rule.choices then
      local chosen_rule = Rand.choice(rule.choices)
      ret = shop_inventory.apply_rule_properties(chosen_rule, ret)
   end

   if rule.on_generate then
      local generated_rule = rule.on_generate({index = index, shopkeeper = shopkeeper})

      -- NOTE: This could potentially recurse somewhat deeply if the
      -- generated rule also contains an on_generate field.
      ret = shop_inventory.apply_rule_properties(generated_rule, ret)
   end

   return ret
end

function shop_inventory.apply_rules(index, shopkeeper, inv)
   local ret = {level = shopkeeper.shop_rank, quality = "Bad"}

   if not inv.rules then
      return ret
   end

   for _, rule in ipairs(inv.rules) do
      if shop_inventory.test_rule_predicate(rule, index, shopkeeper) then
         ret = shop_inventory.apply_rule_properties(rule, ret, index, shopkeeper)

         if ret.id == "Stop" then
            -- Don't generate an item this cycle.
            return nil
         end
      end
   end

   return ret
end

local function has_tag(find, tags)
   if not tags then
      return false
   end

   for _, v in ipairs(tags) do
      if v == find then
         return true
      end
   end

   return false
end

-- If all of the properties of an item match that of an exclusion, the item is
-- removed.
shop_inventory.item_exclusions = {
   { category = 52000, new_id = "core.bottle_of_water" },
   { category = 57000, subcategory = 58500 } -- seeds
}

local function is_excluded(item)
   for _, exclusion in ipairs(shop_inventory.item_exclusions) do
      for k, v in pairs(exclusion) do
         if item[k] == v then
            return true
         end
      end
   end

   return false
end

local function is_cursed(item)
   return item.curse_state == "Cursed" or item.curse_state == "Doomed"
end

function shop_inventory.should_remove(item, inv)
   local tags = data.raw["core.item"][item.new_id].tags

   if has_tag("neg", tags) then
      return true
   end

   if has_tag("noshop", tags) and not inv.ignores_noshop then
      return true
   end

   if is_cursed(item) then
      return true
   end

   if is_excluded(item) then
      return true
   end

   return false
end

-- Higher factor means fewer items.
local function number_from_rarity(factor)
   return function(args) return (args.item_def.rarity / 1000) / factor end
end

-- Map of item category/id -> function returning sold item amount.
-- Gets passed the item's definition and the item instance.
shop_inventory.item_number_factors = {
   [57000] = function() return 1 end,
   [92000] = number_from_rarity(200),
   [90000] = number_from_rarity(100),
   [52000] = number_from_rarity(100),
   [53000] = number_from_rarity(100),
   [60000] = number_from_rarity(200),
   [64000] = number_from_rarity(80),
   [59000] = number_from_rarity(500),

   ["core.small_gamble_chest"] = function() return Rand.rnd(8) end
}

function shop_inventory.calc_max_item_number(item)
   local item_def = data.raw["core.item"][item.new_id]
   local category = item_def.category
   local number = 1

   local f = shop_inventory.item_number_factors[category]
   if f then
      number = f({item_def = item_def, item = item})
   end

   f = shop_inventory.item_number_factors[item.new_id]
   if f then
      number = f({item_def = item_def, item = item})
   end

   if number < 1 then
      number = 1
   end

   return number
end

-- Parameters for adjusting the amount of available cargo based on the
-- cargo's fluctuating value. Cargo of higher value will be more
-- difficult to find in shops. More than one modifier can be applied
-- if multiple value thresholds are reached.
shop_inventory.cargo_amount_rates = {
   { threshold = 70,  type = "lt", amount = function(n) return n * 200 / 100 end                    },
   { threshold = 50,  type = "lt", amount = function(n) return n * 200 / 100 end                    },
   { threshold = 80,  type = "gt", amount = function(n) return n / 2 + 1     end, remove_chance = 2 },
   { threshold = 100, type = "gt", amount = function(n) return n / 2 + 1     end, remove_chance = 3 },
}

function shop_inventory.cargo_amount_modifier(amount)
   return amount * (100 + Skill.level(156, Chara.player()) * 10) / 100 + 1
end

-- Calculate adjusted amount of cargo items to be sold based on the
-- cargo's value.
function shop_inventory.calc_cargo_amount(item)
   local rate = Item.trade_rate(item)
   local amount = item.number

   for _, v in ipairs(shop_inventory.cargo_amount_rates) do
      local apply

      if v.type == "lt" then
         apply = rate <= v.threshold
      else
         apply = rate >= v.threshold
      end

      if apply then
         amount = v.amount(amount)
         if v.discard_chance and Rand.one_in(v.discard_chance) then
            return nil
         end
      end
   end

   return shop_inventory.cargo_amount_modifier(amount)
end

function shop_inventory.do_generate(shopkeeper, inv)
   -- Determine how many items to create. Shops can also adjust the
   -- amount with a formula.
   local items_to_create = shop_inventory.default_item_number({shopkeeper = shopkeeper})
   if inv.item_number then
      items_to_create = inv.item_number({shopkeeper = shopkeeper, item_number = items_to_create})
   end

   for index = 0, items_to_create - 1 do
      -- Go through each generation rule the shop defines and get back
      -- a table of options for Item.create().
      local args = shop_inventory.apply_rules(index, shopkeeper, inv)

      if not args then
         goto continue
      end

      args.nostack = true
      local item = Item.create(1, -1, args)
      if not item then
         -- Shop inventory is full, don't generate anything else.
         break
      end

      -- If the shop defines special handling of item state on
      -- generation, use it and skip the remaining adjustments to the
      -- item that happen afterward.
      if inv.on_generate_item then
         inv.on_generate_item({item = item, index = index, shopkeeper = shopkeeper})
         goto continue
      end

      -- Exclude items like cursed items, seeds or water.
      if shop_inventory.should_remove(item, inv) then
         item:remove()
         goto continue
      end

      -- Calculate the number of items sold (always above 0).
      item.number = Rand.rnd(shop_inventory.calc_max_item_number(item)) + 1

      -- Cargo traders have special behavior for calculating the sold
      -- item number.
      if inv._id == "core.trader" then
         local number = shop_inventory.calc_cargo_amount(item)
         if number == nil then
            item:remove()
            goto continue
         else
            item.number = number
         end
      end

      if not item:is_valid() then
         goto continue
      end

      -- Blessed items are never generated in multiple (per cycle).
      if item.curse_state == "Blessed" then
         item.number = 1
      end

      -- Shops can adjust the price of items through a formula.
      if inv.item_base_value then
         item.value = inv.item_base_value({item = item, shopkeeper = shopkeeper})
      end

      Item.stack(-1, item) -- invalidates "item".

      ::continue::
   end
end

function shop_inventory.generate(shopkeeper)
   -- Obtain shop inventory data by using the shopkeeper's
   -- character_role as its legacy ID index. If it does not exist, a
   -- default set of items will be generated as a fallback.
   local id = data.by_legacy["core.shop_inventory"][shopkeeper.role]
   local inv = {}
   if id then
      inv = data.raw["core.shop_inventory"][id]
   end

   shop_inventory.do_generate(shopkeeper, inv)
end

return shop_inventory
