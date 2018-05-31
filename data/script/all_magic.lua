local Event = Elona.require("Event")
local Enums = Elona.require("Enums")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local table = Elona.require("table")

local potions = {736, 711, 706, 626, 577, 566, 559, 519, 433, 432,
429, 382, 379, 376, 375, 372, 370, 368, 364, 287, 286, 285, 262, 76,
75, 74, 72, 71, 70, 69, 68, 30, 29, 28, 27}

local spellbooks = {732, 731, 710, 708, 697, 696, 660, 628, 624, 623,
582, 569, 564, 550, 548, 546, 505, 484, 481, 434, 410, 397, 396, 387,
386, 383, 381, 380, 378, 374, 373, 371, 369, 367, 365, 289, 272, 271,
270, 269, 268, 267, 265, 264, 263, 257, 252, 251, 250, 249, 248, 247,
246, 118, 116, 34, 33, 32, 22, 21, 20}

local rods = {581, 570, 565, 551, 545, 518, 517, 485, 480, 412, 391,
385, 377, 366, 290, 203, 202, 176, 175, 125, 123, 122, 121, 120, 119,
19, 18}

local all = table.merge(table.merge(table.deepcopy(potions),
                                    table.deepcopy(spellbooks), true),
                        table.deepcopy(rods), true)

local potion_switcher = 241
local spellbook_switcher = 321
local rod_switcher = 220

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, 733, 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag(Enums.CharaFlag.IsHungOnSandBag, true)
   return chara
end

local function switch_item_type(chara)
   local list
   GUI.txt_color(2)
   if chara.index == Store.potion_chara.index then
      list = potions
      GUI.txt("*potion* ")
   elseif chara.index == Store.spellbook_chara.index then
      list = spellbooks
      GUI.txt("*spellbook* ")
   elseif chara.index == Store.rod_chara.index then
      list = rods
      GUI.txt("*rod* ")
   else
      GUI.txt_color(0)
      return
   end

   for i, item in Item.iter_all() do
      GUI.txt("item " .. tostring(i) .. " ")
      if table.find(all, function(i) return item.id == i end) then
         Item.remove(item)
      end
   end

   for i, id in ipairs(list) do
      local x = (i / 5) + 12
      local y = (i % 5) + 25
      local item = Item.create(x, y, id, 1)
      item.curse_state = Enums.CurseState.None
      item.identify_state = Enums.IdentifyState.Completely
   end
end

local function setup()
   Store.potion_chara = make_sandbag(23, 28, potion_switcher)
   Store.spellbook_chara = make_sandbag(25, 28, spellbook_switcher)
   Store.rod_chara = make_sandbag(27, 28, rod_switcher)

   Store.test_chara = make_sandbag(25, 23, 34)

   -- TODO add docs
   Chara.player():gain_skill_exp(14, 999999)
   Chara.player():gain_skill(150, 9999)
   Chara.player():gain_skill(165, 9999)
end

Event.register(Event.EventKind.MapInitialized, setup)
Event.register(Event.EventKind.CharaDamaged, switch_item_type)
