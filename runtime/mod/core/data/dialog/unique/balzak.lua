local Chara = require("core.Chara")
local GUI = require("core.GUI")
local Internal = require("core.Internal")
local Item = require("core.Item")

local common = require_relative("../common.lua")

return {
   root = "core.talk.unique.balzak",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("sewer_sweeping")
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
            common.journal_updated,
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("sewer_sweeping", 1)
            common.create_downstairs(18, 45, 20)
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
               Item.create(Chara.player().position, "core.statue_of_jure", 0)
               local monster_ball = Item.create(Chara.player().position, {id = "core.monster_ball", nostack = true})
               monster_ball.param2 = 30
               Item.create(Chara.player().position, "core.gold_piece", 15000)
               Item.create(Chara.player().position, "core.platinum_coin", 4)

               common.quest_completed()
            end,
            {"quest.end"},
         },
         on_finish = function()
            Internal.set_quest_flag("sewer_sweeping", 1000)
         end
      },
   }
}
