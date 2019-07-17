local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local table = Elona.require("table")

local common = require("data/dialog/common")

local function buy_nuke()
   GUI.txt(I18N.get("core.common.something_is_put_on_the_ground"))
   Chara.player().gold = Chara.player().gold - 12000
   GUI.play_sound("core.paygold1")
   Item.create(Chara.player().position, "core.nuclear_bomb", 0)
end

return {
   id = "noel",
   root = "core.talk.unique.noel",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("red_blossom_in_palmia")
         if flag == 1000 then
            return "quest_completed"
         elseif flag == 1 then
            return "quest_waiting"
         elseif flag == 2 then
            return "quest_finish"
         elseif flag == 0 then
            return "quest_ask"
         end

         return "__IGNORED__"
      end,
      quest_completed = {
         text = {
            {"complete"},
         },
         choices = {
            {"buy_nuke", "__MORE__"}
         }
      },
      quest_waiting = {
         text = {
            {"quest.waiting"}
         },
         choices = {
            {"buy_nuke", "__MORE__"}
         }
      },
      quest_finish = {
         text = {
            function()
               local secret_treasure = Item.create(Chara.player().position, {id = "core.secret_treasure", nostack = true})
               secret_treasure.param1 = 162
               Item.create(Chara.player().position, "core.platinum_coin", 6)

               common.quest_completed()

               Internal.set_quest_flag("red_blossom_in_palmia", 1000)
            end,
            {"quest.end"},
         },
         choices = {
            {"buy_nuke", "__MORE__"}
         }
      },
      quest_ask = {
         text = {
            {"quest.dialog._0"},
            {"quest.dialog._1"},
         },
         choices = {
            {"quest_yes", "quest.choices.of_course"},
            {"quest_no", "__BYE__"},
         },
         default_choice = "quest_no"
      },
      quest_yes = {
         text = {
            function()
               GUI.show_journal_update_message()
               Internal.set_quest_flag("red_blossom_in_palmia", 1)
            end,
            {"quest.of_course"},
         },
         choices = {
            {"buy_nuke", "__MORE__"},
         }
      },
      quest_no = {
         text = {
            {"quest.bye"},
         },
      },
      buy_nuke = {
         text = {
            {"quest.buy_nuke.dialog"},
         },
         choices = function()
            local choices = {}
            if Chara.player().gold >= 12000 then
               table.insert(choices, {"buy_nuke_yes", "quest.buy_nuke.choices.buy"})
            end
            table.insert(choices, {"buy_nuke_no", "__BYE__"})

            return choices
         end,
         default_choice = "buy_nuke_no"
      },
      buy_nuke_yes = {
         text = {
            buy_nuke,
            {"quest.buy_nuke.buy"},
         },
      },
      buy_nuke_no = {
         text = {
            {"quest.buy_nuke.bye"},
         },
      },
   }
}
