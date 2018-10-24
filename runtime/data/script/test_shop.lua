local Event = Elona.require("Event")
local Input = Elona.require("Input")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")

local role = 16
local switcher = nil
local shop = nil

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, "core.sand_bag", 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag("IsHungOnSandBag", true)
   return chara
end

local function next_role()
   local new_role = Input.prompt_number("Which? ", 22, role)
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

local function setup()
   switcher = make_sandbag(23, 23, "core.yeek")

   shop = Chara.create(25, 23, "core.putit")
   shop.relationship = "Neutral"
   shop.role = 1000 + role

   Item.create(Chara.player().position, { id = "core.diablo", quality = "Bad", level = 0 })
end

Event.register(Event.EventKind.MapInitialized, setup)
Event.register(Event.EventKind.CharaDamaged, function(chara)
                  if chara.index == switcher.index then
                     next_role()
                  end
end)
