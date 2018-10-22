local Item = Elona.require("Item")
local Math = Elona.require("Math")
local Chara = Elona.require("Chara")
local Skill = Elona.require("Skill")
local Rand = Elona.require("Rand")

local shop_inventory = {}

local function default_item_count(args)
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
end

function shop_inventory.apply_flttype(flttype)
   local filter_set = data.raw["core.filter_set"][flttype]
   if filter_set then
      return Rand.choice(filter_set.set)
   end
   return flttype
end

function shop_inventory.apply_rule_properties(rule, ret, index, shopkeeper)
   if rule.id then
      ret.id = rule.id
   end
   if rule.fixlv then
      ret.fixlv = rule.fixlv
   end
   if rule.fltn then
      ret.fltn = rule.fltn
   end
   if rule.flttypemajor then
      ret.flttypemajor = shop_inventory.apply_flttype(rule.flttypemajor)
   end
   if rule.flttypeminor then
      ret.flttypeminor = shop_inventory.apply_flttype(rule.flttypeminor)
   end

   if rule.choices then
      local selected = Rand.choice(rule.choices)
      ret = shop_inventory.apply_rule_properties(selected, ret)
   end

   if rule.on_generate then
      local props = rule.on_generate({index = index, shopkeeper = shopkeeper})
      ret = shop_inventory.apply_rule_properties(props, ret)
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
            return nil
         end
      end
   end

   return ret
end

local function filter_contains(exp, filter)
   return string.match("/" .. exp .. "/", filter)
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
   local filter = data.raw["core.item"][item.new_id].filter

   if filter_contains("neg", filter) then
      return true
   end

   if filter_contains("noshop", filter) and inv._id ~= "core.souvenir_vendor" then
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

local function rarity_num(factor)
   return function(rarity) return rarity / factor end
end

-- Map of item category -> function returning sold item amount based
-- on rarity
shop_inventory.item_count_factors = {
   [57000] = function() return 1 end,
   [92000] = rarity_num(200),
   [90000] = rarity_num(100),
   [52000] = rarity_num(100),
   [53000] = rarity_num(100),
   [60000] = rarity_num(200),
   [64000] = rarity_num(80),
   [59000] = rarity_num(500),
}

function shop_inventory.calc_sold_item_count(item_def)
   local category = item_def.category
   local rarity = item_def.rarity / 1000
   local count = 1

   local f = shop_inventory.item_count_factors[category]
   if f then
      count = f(rarity)
   end

   if item_def._id == "core.small_gamble_chest" then
      count = Rand.rnd(8)
   end

   if count < 1 then
      count = 1
   end

   return count
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

-- Calculate adjusted amount of cargo items to be sold based on the
-- cargo's value.
function shop_inventory.calc_cargo_amount(item)
   local rate = Item.trade_rate(item)
   local result = item.number

   for _, v in ipairs(shop_inventory.cargo_amount_rates) do
      local apply

      if v.type == "lt" then
         apply = rate <= v.threshold
      else
         apply = rate >= v.threshold
      end

      if apply then
         result = v.amount(result)
         if v.discard_chance and Rand.one_in(v.discard_chance) then
            return nil
         end
      end
   end

   return result * (100 + Skill.level(156, Chara.player()) * 10) / 100 + 1
end

function shop_inventory.do_generate(shopkeeper, inv)
   local item_count
   if inv.item_count then
      item_count = inv.item_count({shopkeeper = shopkeeper})
   else
      item_count = default_item_count({shopkeeper = shopkeeper})
   end

   for index = 0, item_count do
      local args = shop_inventory.apply_rules(index, shopkeeper, inv)

      if not args then
         goto continue
      end

      args.nostack = true
      local item = Item.roll(-1, -1, args)
      if not item then
         -- Shop inventory is full.
         break
      end

      if inv.on_generate_item then
         inv.on_generate_item({item = item, index = index, shopkeeper = shopkeeper})

         -- Skip the remaining adjustments of item number/price.
         goto continue
      end

      if shop_inventory.should_remove(item) then
         item:remove()
         goto continue
      end

      item.number = Rand.rnd(shop_inventory.calc_sold_item_count(item))

      if inv._id == "core.trader" then
         local number = shop_inventory.calc_cargo_amount(item)
         if number == nil then
            item:remove()
            goto continue
         else
            item.number = number
         end
      end

      if item.curse_state == "Blessed" then
         item.number = 1
      end

      if inv.item_price then
         item.value = inv.item_price({item = item, shopkeeper = shopkeeper})
      end

      Item.stack(-1, item) -- invalidates "item".

      ::continue::
   end
end

function shop_inventory.generate(shopkeeper)
   -- Obtain shop inventory data by using the character_role as its
   -- legacy ID index. If it does not exist, a default set of items
   -- will be generated as a fallback.
   local id = data.by_legacy["core.shop_inventory"][shopkeeper.character_role]
   local inv = {}
   if id then
      inv = data.raw["core.shop_inventory"][id]
   end

   shop_inventory.do_generate(shopkeeper, inv)
end

return shop_inventory
