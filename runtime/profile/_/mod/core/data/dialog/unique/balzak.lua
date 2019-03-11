local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local Map = Elona.require("Map")

return {
   name = "balzak",
   root = "core.locale.talk.unique.balzak",
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
         }
      },
      quest_yes = {
         text = {
            GUI.show_journal_update_message,
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("sewer_sweeping", 1)
            Map.set_feat(18, 45, 231, 11, 20)
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

               GUI.txt(I18N.get("core.locale.quest.completed"))
               GUI.play_sound("core.complete1")
               GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
               GUI.show_journal_update_message()
            end,
            {"quest.end"},
         },
         on_finish = function()
            Internal.set_quest_flag("sewer_sweeping", 1000)
         end
      },
   }
}
