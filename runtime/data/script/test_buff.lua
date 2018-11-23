local Event = Elona.require("Event")
local Input = Elona.require("Input")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")

local switcher = nil

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, "core.sand_bag", 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag("IsHungOnSandBag", true)
   return chara
end

local function data_keys(kind)
   local keys = {}
   for k, _ in pairs(data.raw[kind]) do
      keys[#keys+1] = k
   end
   return keys
end

local function prompt_choice_paged(items)
   local page_no = 0
   local result

   while true do
      local page = {}
      for i=1,10 do
         local index = page_no * 10 + i
         if not items[index] then
            break
         end
         page[#page+1] = items[index]
      end

      page[#page+1] = I18N.get("core.locale.ui.more")

      local selected = Input.prompt_choice(page)

      if selected == nil then
         break
      elseif selected == #page then
         page_no = page_no + 1
         if not items[page_no * 10] then
            page_no = 0
         end
      else
         result = page_no * 10 + selected
         break
      end
   end

   return result
end

local function query_buff()
   local buffs = data_keys("core.buff")
   GUI.txt("Buff? ")
   local index = prompt_choice_paged(buffs)
   if index then
      local buff_id = buffs[index]
      local power = Input.prompt_number("Power? ", 9999, 100)
      if power then
         local buff = data.raw["core.buff"][buff_id]
         GUI.txtef("Gold")
         GUI.txt("Buff: " .. I18N.get_enum_property("core.locale.buff", "name", buff.id))
         Chara.player():add_buff(buff_id, power, 50)
      end
   end
end

local function setup()
   switcher = make_sandbag(25, 23, "core.silver_cat")

   -- Guard aggro is only refreshed when entering an existing map, so
   -- it will only be reapplied when incognito ends.
   for i=0,5 do
      local guard = Chara.create(27, 27, "core.guard")
      guard.role = 14
   end

   Chara.player().karma = -50
end

Event.register(Event.EventKind.MapInitialized, setup)
Event.register(Event.EventKind.CharaDamaged, function(chara)
                  if chara.index == switcher.index then
                     query_buff()
                  end
end)

Event.register(Event.EventKind.CharaCreated, function(chara)
                  print("Created " .. chara.index)
end)

Event.register(Event.EventKind.CharaRemoved, function(chara)
                  print("Removed " .. chara.index)
end)
