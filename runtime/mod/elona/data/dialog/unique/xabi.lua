local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item

local common = require("data/dialog/common")

return {
   id = "xabi",
   root = "elona.talk.unique.xabi",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("main_quest")
         if flag >= 60 then
            return "late"
         elseif flag == 50 then
            return "mid"
         elseif flag == 40 then
            return "early"
         end

         return "__IGNORED__"
      end,
      late = {
         text = {
            {"late"}
         }
      },
      mid = {
         text = {
            {"mid"}
         }
      },
      early = {
         text = {
            function() Internal.set_quest_flag("main_quest", 50) end,
            {"early._0"},
            GUI.fade_out,
            {"early._1", args = common.args_name},
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            Item.create(Chara.player().position, "elona.gold_piece", 2500)
            Item.create(Chara.player().position, "elona.platinum_coin", 3)
            Item.create(Chara.player().position, "elona.potion_of_cure_corruption", 0)
            Item.create(Chara.player().position, "elona.treasure_map", 0)
            GUI.txt(I18N.get("core.common.something_is_put_on_the_ground"))
            GUI.show_journal_update_message()
         end
      }
   }
}
