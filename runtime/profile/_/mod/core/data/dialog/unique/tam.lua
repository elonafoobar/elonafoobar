local Chara = Elona.require("Chara")
local Map = Elona.require("Map")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

local common = require("data/dialog/common")

return {
   id = "tam",
   root = "core.locale.talk.unique.tam",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("cat_house")
         if flag == 1000 then
            return "quest_completed"
         elseif flag == 0 then
            return "quest_ask"
         elseif flag == 1 then
            return "quest_waiting"
         elseif flag == 2 then
            return "quest_finish"
         end

         return "__IGNORED__"
      end,
      quest_completed = {
         text = {
            {"complete"},
         },
      },
      quest_ask = {
         text = {
            {"quest.dialog"},
         },
         choices = {
            {"quest_yes", "quest.choices.yes"},
            {"quest_no", "quest.choices.no"}
         },
      },
      quest_yes = {
         text = {
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("cat_house", 1)
            Map.set_feat(23, 22, 231, 11, 3)
         end
      },
      quest_no = {
         text = {
            {"quest.no"},
         },
      },
      quest_waiting = {
         text = {
            {"quest.waiting"}
         }
      },
      quest_finish = {
         text = {
            function()
               local item = Item.create(Chara.player().position, "core.material_kit", 0)
               item:change_material("core.dragon_scale")
               Item.create(Chara.player().position, "core.gold_piece", 25500)
               Item.create(Chara.player().position, "core.platinum_coin", 4)

               common.quest_completed()
            end,
            {"quest.end"},
         },
         on_finish = function()
            Internal.set_quest_flag("cat_house", 1000)
         end
      }
   }
}
