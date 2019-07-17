local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

local common = require("data/dialog/common")

return {
   id = "shena",
   root = "core.talk.unique.shena",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("thieves_hideout")
         if flag == 1000 then
            return "quest_completed"
         elseif flag == 0 then
            return "quest_ask"
         elseif flag == 1 then
            return "quest_waiting"
         elseif flag == 2 then
            return "quest_finish"
         end
         return "__END__"
      end,
      quest_completed = {
         text = {
            {"complete"}
         }
      },
      quest_ask = {
         text = {
            {"quest.dialog._0"},
            {"quest.dialog._1"}
         },
         choices = {
            {"quest_yes", "quest.choices.yes"},
            {"quest_no", "quest.choices.no"}
         },
         default_choice = "quest_no"
      },
      quest_yes = {
         text = {
            GUI.show_journal_update_message,
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("thieves_hideout", 1)
            common.create_downstairs(48, 5, 4)
         end
      },
      quest_no = {
         text = {
            {"quest.no"},
         }
      },
      quest_waiting = {
         text = {
            {"quest.waiting"},
         }
      },
      quest_finish = {
         text = {
            function()
               local rod_of_identify = Item.create(Chara.player().position, "core.rod_of_identify", 0)
               rod_of_identify.count = 12
               local monster_ball = Item.create(Chara.player().position, {id = "core.monster_ball", nostack = true})
               monster_ball.param2 = 5
               Item.create(Chara.player().position, "core.gold_piece", 1500)
               Item.create(Chara.player().position, "core.platinum_coin", 2)

               common.quest_completed()
            end,
            {"quest.end"},
         },
         on_finish = function()
            Internal.set_quest_flag("thieves_hideout", 1000)
         end
      },
   }
}
