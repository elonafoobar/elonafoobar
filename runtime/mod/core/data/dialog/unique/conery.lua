local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local Internal = Elona.game.Internal
local Item = Elona.game.Item

local common = require("data/dialog/common")

return {
   id = "conery",
   root = "core.talk.unique.conery",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("minotaur_king")
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
            {"complete"}
         }
      },
      quest_ask = {
         text = {
            {"quest.dialog"}
         },
         choices = {
            {"quest_yes", "quest.choices.do_it"},
            {"quest_no", "quest.choices.bye"}
         },
         default_choice = "quest_no"
      },
      quest_yes = {
         text = {
            GUI.show_journal_update_message,
            {"quest.do_it"},
         },
         on_finish = function()
            Internal.set_quest_flag("minotaur_king", 1)
         end
      },
      quest_no = {
         text = {
            {"quest.bye", args = common.args_name},
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
            local material_kit = Item.create(Chara.player().position, {id = "core.material_kit", nostack = true})
            material_kit:change_material("core.adamantium")
            Item.create(Chara.player().position, "core.gold_piece", 50000)
            Item.create(Chara.player().position, "core.platinum_coin", 4)

            common.quest_completed()

            Internal.set_quest_flag("minotaur_king", 1000)
         end
      },
   }
}
