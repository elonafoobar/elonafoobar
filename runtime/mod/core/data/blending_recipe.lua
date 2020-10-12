local Chara = ELONA.require("core.Chara")
local Enchantment = ELONA.require("core.Enchantment")
local Enums = ELONA.require("core.Enums")
local GUI = ELONA.require("core.GUI")
local I18N = ELONA.require("core.I18N")
local Inventory = ELONA.require("core.Inventory")
local Item = ELONA.require("core.Item")
local Rand = ELONA.require("core.Rand")
local World = ELONA.require("core.World")



local function create_item(product_id, on_item_created)
   return function(_args)
      local product = Item.create(
         Chara.player().position,
         { id = product_id, nostack = true })
      if product then
         if on_item_created then
            on_item_created(product)
         end
         GUI.txt(I18N.get("core.blending.succeeded", product), "green")
         GUI.play_sound("core.drink1")
      end
   end
end



ELONA.data:define_prototype("blending_recipe")
ELONA.data:add(
   "core.blending_recipe",
   {
      love_food = {
         integer_id = 200,
         type = 1,
         required_turns = 10,
         required_skills = {
            ["core.cooking"] = 8,
            ["core.alchemy"] = 3,
         },
         materials = {
            { category = 57000 },
            { id = "core.love_potion" },
         },
         known = true,
         on_success = function(args)
            local food = args.materials[1]

            food.is_aphrodisiac = true
            GUI.txt(I18N.get("core.blending.succeeded", food), "green")
            GUI.txt(I18N.get("core.action.dip.result.love_food.guilty"))
            GUI.play_sound("core.offer1")
         end,
      },
      dyeing = {
         integer_id = 201,
         type = 1,
         required_turns = 4,
         required_skills = {
            ["core.stat_dexterity"] = 6,
         },
         materials = {
            "anything",
            { id = "core.bottle_of_dye" },
         },
         known = true,
         on_success = function(args)
            local target, dye = args.materials[1], args.materials[2]

            target.tint = dye.tint
            GUI.txt(I18N.get("core.action.dip.result.dyeing", target), "green")
            GUI.play_sound("core.drink1")
         end,
      },
      poisoned_food = {
         integer_id = 202,
         type = 1,
         required_turns = 7,
         required_skills = {
            ["core.cooking"] = 3,
         },
         materials = {
            { category = 57000 },
            { id = "core.poison" },
         },
         known = true,
         on_success = function(args)
            local food = args.materials[1]

            food.is_poisoned = true
            GUI.txt(I18N.get("core.blending.succeeded", food), "green")
            GUI.txt(I18N.get("core.action.dip.result.poisoned_food"))
            GUI.play_sound("core.offer1")
         end,
      },
      fireproof_coating = {
         integer_id = 203,
         type = 1,
         required_turns = 15,
         required_skills = {
            ["core.stat_dexterity"] = 18,
         },
         materials = {
            "anything",
            { id = "core.fireproof_liquid" },
         },
         known = true,
         on_success = function(args)
            local target, potion_of_fireproof = args.materials[1], args.materials[2]

            GUI.txt(I18N.get("core.action.dip.result.put_on", target, potion_of_fireproof), "green")
            if target.id == "core.fireproof_blanket" then
               GUI.txt(I18N.get("core.action.dip.result.good_idea_but"))
            else
               target.is_fireproof = true
               GUI.txt(I18N.get("core.action.dip.result.gains_fireproof", target))
            end
            GUI.play_sound("core.drink1")
         end,
      },
      acidproof_coating = {
         integer_id = 204,
         type = 1,
         required_turns = 15,
         required_skills = {
            ["core.stat_dexterity"] = 10,
         },
         materials = {
            "anything",
            { id = "core.acidproof_liquid" },
         },
         known = true,
         on_success = function(args)
            local target, potion_of_acidproof = args.materials[1], args.materials[2]

            GUI.txt(I18N.get("core.action.dip.result.put_on", target, potion_of_acidproof), "green")
            target.is_acidproof = true
            GUI.txt(I18N.get("core.action.dip.result.gains_acidproof", target))
            GUI.play_sound("core.drink1")
         end,
      },
      bait_attachment = {
         integer_id = 205,
         type = 1,
         required_turns = 10,
         required_skills = {
            ["core.fishing"] = 2,
            ["core.stat_dexterity"] = 10,
         },
         materials = {
            { id = "core.fishing_pole" },
            { id = "core.bait" },
         },
         known = true,
         on_success = function(args)
            local rod, bait = args.materials[1], args.materials[2]

            GUI.txt(I18N.get("core.action.dip.result.bait_attachment", rod, bait), "green")
            if rod.param4 == bait.param1 then
               rod.count = rod.count + Rand.between(15, 25)
            else
               rod.count = Rand.between(15, 25)
               rod.param4 = bait.param1
            end
            GUI.play_sound("core.equip1")
         end,
      },
      blessed_item = {
         integer_id = 206,
         type = 1,
         required_turns = 5,
         required_skills = {
            ["core.stat_dexterity"] = 5,
         },
         materials = {
            "anything",
            { id = "core.bottle_of_water" },
         },
         known = true,
         on_success = function(args)
            local target, water = args.materials[1], args.materials[2]

            GUI.txt(I18N.get("core.action.dip.result.blessed_item", target, water), "green")
            if water.curse_state == Enums.CurseState.BLESSED then
               GUI.txt(I18N.get("core.action.dip.result.becomes_blessed", target), "orange")
               target.curse_state = Enums.CurseState.BLESSED
            end
            if water.curse_state == Enums.CurseState.CURSED or water.curse_state == Enums.CurseState.DOOMED then
               GUI.txt(I18N.get("core.action.dip.result.becomes_cursed", target), "purple")
               target.curse_state = Enums.CurseState.CURSED
            end
            GUI.play_sound("core.drink1")
         end,
      },
      well_refill = {
         integer_id = 207,
         type = 2,
         required_turns = 3,
         required_skills = {
            ["core.stat_dexterity"] = 3,
         },
         materials = {
            { category = 60001 },
            { category = 52000 },
         },
         known = true,
         on_success = function(args)
            local well, potion = args.materials[1], args.materials[2]

            GUI.txt(I18N.get("core.action.dip.result.well_refill", well, potion))
            if potion.id == "core.empty_bottle" then
               GUI.txt(I18N.get("core.action.dip.result.empty_bottle_shatters"))
               return
            end
            GUI.play_sound("core.drink1")
            if well.id == "core.holy_well" then
               GUI.txt(I18N.get("core.action.dip.result.holy_well_polluted"))
               return
            end
            if well.param3 >= 20 then
               GUI.txt(I18N.get("core.action.dip.result.well_dry", well))
               return
            end
            GUI.txt(I18N.get("core.action.dip.result.well_refilled", well), "green")
            if potion.id == "core.handful_of_snow" then
               GUI.txt(I18N.get("core.action.dip.result.snow_melts.blending"))
            else
               well.param1 = well.param1 + Rand.rnd(3)
            end
         end,
      },
      natural_potion = {
         integer_id = 208,
         type = 2,
         required_turns = 16,
         required_skills = {
            ["core.stat_dexterity"] = 24,
         },
         materials = {
            { category = 60001 },
            { id = "core.empty_bottle" },
         },
         on_success = function(args)
            local well = args.materials[1]

            if well.param1 < -5 or well.param3 >= 20 or
                  (well.id == "core.holy_well" and World.data.holy_well_count <= 0) then
               GUI.txt(I18N.get("core.action.dip.result.natural_potion_dry", well))
               GUI.txt(I18N.get("core.action.dip.result.natural_potion_drop"))
               return
            end
            if not Inventory.player():has_free_slot() then
               GUI.txt(I18N.get("core.ui.inv.common.inventory_is_full"))
               return
            end
            local natural_potion
            if well.id == "core.holy_well" then
               World.data.holy_well_count = World.data.holy_well_count - 1
               natural_potion = Item.create(-1, -1, { id = "core.bottle_of_water", inventory = Inventory.player() })
               if natural_potion then
                  natural_potion.curse_state = Enums.CurseState.BLESSED
               end
            else
               well.param1 = well.param1 - 3
               natural_potion = Item.create(-1, -1, { objlv = 20, flttypemajor = 52000, inventory = Inventory.player() })
            end
            if natural_potion then
               GUI.txt(I18N.get("core.action.dip.result.natural_potion"))
               GUI.txt(I18N.get("core.action.dip.you_get", natural_potion), "green")
               Inventory.player():stack(natural_potion, true)
               GUI.play_sound("core.drink1")
            end
         end,
      },
      two_artifacts_fusion = {
         integer_id = 209,
         type = 2,
         required_turns = 16,
         required_skills = {
            ["core.alchemy"] = 999,
         },
         materials = {
            "anything",
            "anything",
         },
         generated = true,
         on_success = function(args)
            -- This recipe has no effect in vanilla.
         end,
      },
      three_artifacts_fusion = {
         integer_id = 210,
         type = 2,
         required_turns = 16,
         required_skills = {
            ["core.alchemy"] = 999,
         },
         materials = {
            "anything",
            "anything",
            "anything",
         },
         generated = true,
         on_success = function(args)
            -- This recipe has no effect in vanilla.
         end,
      },
      fried_potato = {
         integer_id = 898,
         type = 0,
         required_turns = 16,
         required_hours = 15,
         required_skills = {
            ["core.disarm_trap"] = 4,
            ["core.door_creation"] = 20,
            ["core.stat_dexterity"] = 8,
         },
         materials = {
            { id = "core.sack_of_flour" },
            { filter = "flavor" },
         },
         generated = true,
         on_success = create_item("core.fried_potato"),
      },
      mochi = {
         integer_id = 1156,
         type = 0,
         required_turns = 20,
         required_hours = 2,
         required_skills = {
            ["core.cooking"] = 4,
            ["core.jeweler"] = 20,
            ["core.stealth"] = 8,
         },
         materials = {
            { id = "core.sack_of_flour" },
         },
         generated = true,
         on_success = create_item("core.mochi"),
      },
      puff_puff_bread = {
         integer_id = 1187,
         type = 0,
         required_turns = 30,
         required_skills = {
            ["core.cooking"] = 10,
            ["core.alchemy"] = 5,
         },
         materials = {
            "anything",
         },
         generated = true,
         on_success = create_item("core.puff_puff_bread"),
      },
      dragon_slayer = {
         integer_id = 1191,
         type = 0,
         required_turns = 45,
         required_hours = 16,
         required_skills = {
            ["core.cooking"] = 10,
            ["core.alchemy"] = 65,
            ["core.stat_strength"] = 105,
         },
         materials = {
            { category = 10000 },
            { id = "core.summoning_crystal" },
            { id = "core.vanilla_rock" },
         },
         on_success = create_item("core.dragon_slayer"),
      },
      putitoro = {
         integer_id = 1192,
         type = 0,
         required_turns = 24,
         required_hours = 1,
         required_skills = {
            ["core.cooking"] = 20,
            ["core.jeweler"] = 10,
            ["core.gene_engineer"] = 5,
         },
         materials = {
            { id = "core.corpse", of = "core.putit" },
            { filter = "fish" },
         },
         on_success = create_item("core.putitoro", function(putitoro)
            local enchantments = {
               [10010] = 100,
               [10011] = 200,
               [10016] = 300,
               [10017] = 500,
               [60010] = 100,
               [60011] = 200,
               [60016] = 300,
               [60017] = 500,
            }
            for id, power in pairs(enchantments) do
               Enchantment.add(putitoro, id, power)
            end
         end),
      },
   }
)
