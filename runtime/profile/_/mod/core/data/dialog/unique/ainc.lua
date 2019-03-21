local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

local common = require("data/dialog/common")

return {
   name = "ainc",
   root = "core.locale.talk.unique.ainc",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("novice_knight")
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
            {"complete", args = common.args_name}
         }
      },
      quest_ask = {
         text = {
            {"quest.dialog"}
         },
         choices = {
            {"quest_yes", "quest.choices.do_it"},
            {"quest_no", "__BYE__"}
         }
      },
      quest_yes = {
         text = {
            GUI.show_journal_update_message,
            {"quest.do_it"},
         },
         on_finish = function()
            Internal.set_quest_flag("novice_knight", 1)
         end
      },
      quest_no = {
         text = {
            {"quest.bye"},
         }
      },
      quest_waiting = {
         text = {
            {"quest.waiting"},
         }
      },
      quest_finish = {
         text = {
            {"quest.end"},
         },
         on_finish = function()
            Item.create(Chara.player().position, "core.dal_i_thalion", 0)
            Item.create(Chara.player().position, "core.gold_piece", 5000)
            Item.create(Chara.player().position, "core.platinum_coin", 3)

            GUI.txt(I18N.get("core.locale.quest.completed"))
            GUI.play_sound("core.complete1")
            GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
            GUI.show_journal_update_message()

            Internal.set_quest_flag("novice_knight", 1000)
         end
      },
   }
}
