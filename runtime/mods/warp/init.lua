local Map = Elona.require("Map")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Input = Elona.require("Input")

local exports = {}
exports.on_use = {}

local function warpable_maps()
   local keys = {}
   for k, v in pairs(data.raw["core.map"]) do
      if v.deed == nil then
         keys[#keys+1] = k
      end
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

function exports.on_use.warper()
   local maps = warpable_maps()
   GUI.txt("Which map? ")
   local index = prompt_choice_paged(maps)
   if index then
      local map = maps[index]
      GUI.txt("Warping to " .. map)
      Map.travel_to(map)
      return true
   end

   return false
end

return {
   Exports = exports
}
