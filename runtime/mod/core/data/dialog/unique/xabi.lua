local Chara = require("core.Chara")
local GUI = require("core.GUI")
local i18n = require("core.i18n")
local Internal = require("core.Internal")
local Item = require("core.Item")

local common = require_relative("../common.lua")

return {
   root = "core.talk.unique.xabi",
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
            function() GUI.fade_out() end,
            {"early._1", args = common.args_name},
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            Item.create(Chara.player().position, "core.gold_piece", 2500)
            Item.create(Chara.player().position, "core.platinum_coin", 3)
            Item.create(Chara.player().position, "core.potion_of_cure_corruption", 0)
            Item.create(Chara.player().position, "core.treasure_map", 0)
            GUI.txt(i18n.get("core.common.something_is_put_on_the_ground"))
            GUI.show_journal_update_message()
         end
      }
   }
}
