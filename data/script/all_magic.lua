local Event = Elona.require("Event")
local Enums = Elona.require("Enums")
local Item = Elona.require("Item")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local table = Elona.require("table")

local potions = {736, 711, 706, 626, 577, 566, 559, 519, 433, 432,
429, 382, 379, 376, 375, 372, 370, 368, 364, 287, 286, 285, 262, 76,
75, 74, 72, 71, 70, 69, 68, 30, 29, 28, 27}

local scrolls = {737, 709, 638, 632, 549, 515, 509, 508, 507, 506,
502, 501, 500, 479, 431, 430, 411, 398, 395, 390, 389, 388, 384, 363,
362, 288, 245, 244, 243, 242, 236, 209, 17, 16, 15, 14}

local rods = {581, 570, 565, 551, 545, 518, 517, 485, 480, 412, 391,
385, 377, 366, 290, 203, 202, 176, 175, 125, 123, 122, 121, 120, 119,
19, 18}

local all = table.merge(table.merge(table.deepcopy(potions),
                                    table.deepcopy(scrolls),
                                    true),
                        table.deepcopy(rods), true)

local potion_switcher = 241
local scroll_switcher = 100
local rod_switcher = 186

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, 733, 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag(Enums.CharaFlag.IsHungOnSandBag, true)
   return chara
end

local function make_item_variants(x, y, item_id)
   for _, curse_state in pairs({Enums.CurseState.Blessed,
                                Enums.CurseState.None,
                                Enums.CurseState.Cursed}) do
      local item = Item.create(x, y, item_id, 10)
      item.curse_state = curse_state
      item.identify_state = Enums.IdentifyState.Completely
      item.count = 999
   end
end

local function switch_item_type(chara)
   local list
   GUI.txt_color(2)
   if chara.index == Store.potion_chara.index then
      list = potions
      GUI.txt("*potion* ")
   elseif chara.index == Store.rod_chara.index then
      list = rods
      GUI.txt("*rod* ")
   elseif chara.index == Store.scroll_chara.index then
      list = scrolls
      GUI.txt("*scroll* ")
   else
      GUI.txt_color(0)
      return
   end

   for i, item in Item.iter(5080, 5480) do
      if table.find(all, function(id) return item.id == id end) then
         Item.remove(item)
      end
   end

   for i, id in ipairs(list) do
      local x = (i / 5) + 21
      local y = (i % 5) + 23
      make_item_variants(x, y, id)
   end
end

local function gain_all_spells()
   for spell_id=400, 466 do
      if spell_id ~= 426 and spell_id ~= 427 then
         Chara.player():gain_skill(spell_id, 100, 10000);
      end
   end
end

local function setup()
   Store.potion_chara = make_sandbag(23, 28, potion_switcher)
   Store.scroll_chara = make_sandbag(25, 28, scroll_switcher)
   Store.rod_chara = make_sandbag(27, 28, rod_switcher)

   Store.test_chara = make_sandbag(25, 22, 34)

   -- TODO add docs
   Chara.player():gain_skill_exp(14, 999999)
   Chara.player():gain_skill_exp(155, 999999)
   Chara.player():gain_skill_exp(174, 999999)
   Chara.player():gain_skill(164, 9999)
   Chara.player():gain_skill(172, 9999)
   Chara.player():gain_skill(188, 9999)
   gain_all_spells()
end

Event.register(Event.EventKind.MapInitialized, setup)
Event.register(Event.EventKind.CharaDamaged, switch_item_type)
