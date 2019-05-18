local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local table = Elona.require("table")

local common = require("data/dialog/common")

return {
   id = "marks",
   root = "core.locale.talk.unique.marks",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("pyramid_trial")
         if flag ~= 0 then
            return "quest_completed"
         elseif Chara.player().fame < 3000 then
            return "quest_fame_too_low"
         elseif flag == 0 then
            return "quest_ask"
         end

         return "__IGNORED__"
      end,
      quest_completed = {
         text = {
            {"complete"},
         },
      },
      quest_fame_too_low = {
         text = {
            {"fame_too_low"},
         },
      },
      quest_ask = {
         text = {
            {"quest.dialog._0", args = common.args_title},
            {"quest.dialog._1"},
         },
         choices = function()
            local choices = {}
            if Chara.player().gold >= 20000 then
               table.insert(choices, {"quest_yes", "quest.choices.pay"})
            end
            table.insert(choices, {"quest_no", "__BYE__"})

            return choices
         end,
         default_choice = "quest_no"
      },
      quest_yes = {
         text = {
            function()
               GUI.show_journal_update_message()
               GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))

               Chara.player().gold = Chara.player().gold - 20000
               GUI.play_sound("core.paygold1")
               local book = Item.create(Chara.player().position, "core.book_b", 0)
               book.param1 = 13
            end,
            {"quest.pay"},
         },
         on_finish = function()
            Internal.set_quest_flag("pyramid_trial", 1)
         end
      },
      quest_no = {
         text = {
            {"quest.bye"},
         },
      },
   }
}
