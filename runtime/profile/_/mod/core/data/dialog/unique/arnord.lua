local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

local common = require("data/dialog/common")

return {
   name = "arnord",
   root = "core.locale.talk.unique.arnord",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("kamikaze_attack")
         if flag == 1000 then
            return "quest_completed"
         elseif flag == 0 then
            return "quest_ask"
         elseif flag == 1 or flag == 2 then
            return "quest_begin"
         elseif flag == 3 then
            return "quest_finish"
         end

         return "__IGNORED__"
      end,
      quest_completed = {
         text = {
            {"complete", args = common.args_name},
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
            GUI.show_journal_update_message,
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("kamikaze_attack", 1)
         end
      },
      quest_no = {
         text = {
            {"quest.no"},
         },
      },
      quest_begin = {
         text = {
            {"quest.begin.dialog"}
         },
         choices = {
            {"quest_begin_yes", "quest.begin.choices.yes"},
            {"quest_begin_no", "quest.begin.choices.no"}
         },
      },
      quest_begin_yes = {
         text = {
            {"quest.begin.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("kamikaze_attack", 2)
            Internal.go_to_quest_map("core.port_kapul", 25)
         end
      },
      quest_begin_no = {
         text = {
            {"quest.begin.no"},
         },
      },
      quest_finish = {
         text = {
            function()
               Item.create(Chara.player().position, "core.magic_fruit", 0)
               Item.create(Chara.player().position, "core.gold_piece", 7500)
               Item.create(Chara.player().position, "core.platinum_coin", 3)

               common.quest_completed()
            end,
            {"quest.end"},
         },
         on_finish = function()
            Internal.set_quest_flag("kamikaze_attack", 1000)
         end
      }
   }
}
