local Chara = require("core.Chara")
local GUI = require("core.GUI")
local I18N = require("core.I18N")
local Internal = require("core.Internal")
local Item = require("core.Item")

local common = require_relative("../common.lua")

return {
   root = "core.talk.unique.ainc",
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
         },
         default_choice = "quest_no"
      },
      quest_yes = {
         text = {
            common.journal_updated,
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

            GUI.txt(I18N.get("core.quest.completed"))
            GUI.play_sound("core.complete1")
            GUI.txt(I18N.get("core.common.something_is_put_on_the_ground"))
            GUI.show_journal_update_message()

            Internal.set_quest_flag("novice_knight", 1000)
         end
      },
   }
}
