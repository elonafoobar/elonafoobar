local Event = Elona.require("Event")
local Input = Elona.require("Input")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")

local role = 1
local switcher = nil
local rank = nil
local shop = nil

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, "core.sand_bag", 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag("IsHungOnSandBag", true)
   return chara
end

local function query_role()
   local new_role = Input.prompt_number("Rank? ", 22, role)
   if new_role ~= 0 then
      GUI.txt("role: " .. new_role)
      role = new_role
      shop.role = 1000 + role

      local id = data.by_legacy["core.shop_inventory"][shop.role]

      if id then
         GUI.txtef("Gold")
         GUI.txt("role: " .. id)
         GUI.txtnew()
      end
   end
end

local function query_rank()
   local new_rank = Input.prompt_number("Rank? ", 1000, role)
   if new_rank then
      shop.shop_rank = new_rank

      GUI.txtef("Gold")
      GUI.txt("rank: " .. shop.shop_rank)
      GUI.txtnew()
   end
end

local function create_spellbooks()
   for item_id, v in pairs(data.raw["core.item"]) do
      if v.originalnameref2 == "spellbook" then
         local item = Item.create(Chara.player().position, item_id)
         item.curse_state = "None"
         item.identify_state = "Completely"
      end
   end
end

local function setup()
   Chara.player():gain_skill(150, 9999)
   switcher = make_sandbag(23, 23, "core.yeek")
   rank = make_sandbag(27, 23, "core.yeek")

   shop = Chara.create(25, 23, "core.putit")
   shop.relationship = "Neutral"
   shop.role = 1000 + role

   create_spellbooks()
end

Event.register(Event.EventKind.MapInitialized, setup)
Event.register(Event.EventKind.CharaDamaged, function(chara)
                  if chara.index == switcher.index then
                     query_role()
                  elseif chara.index == rank.index then
                     query_rank()
                  end
end)
