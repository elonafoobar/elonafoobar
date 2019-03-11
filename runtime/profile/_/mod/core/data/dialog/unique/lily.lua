local World = Elona.require("World")
local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local Map = Elona.require("Map")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local table = Elona.require("table")

local common = require("data/dialog/common")

local function give_potion()
   local potion = Item.find("core.potion_of_cure_corruption", "PlayerInventory")
   potion.number = potion.number - 1
   GUI.txt(I18N.get("core.locale.talk.unique.lily.progress.end_life.give.you_hand_her"))
   GUI.play_sound("core.equip1")
   Chara.player():modify_karma(20)
end

return {
   name = "lily",
   root = "core.locale.talk.unique.lily",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("pael_and_her_mom")
         if flag == 1002 then
            return "after_sold"
         elseif flag == 10 then
            return "last"
         elseif flag == 1000 then
            if Map.id() == "core.noyel" and Map.area().christmas_festival then
               return "festival"
            end
            return "end_life"
         elseif flag > 7 then
            return "very_late"
         elseif flag > 5 then
            return "late"
         elseif flag > 3 then
            return "mid"
         end

         return "early"
      end,

      after_sold = {
         text = {
            {"after_sold"}
         }
      },

      last = {
         text = {
            {"progress.last._0", args = common.args_name},
            {"progress.last._1"},
            function()
               Item.create(Chara.player().position, "core.happy_apple", 0)
               Item.create(Chara.player().position, "core.gold_piece", 20000)
               Item.create(Chara.player().position, "core.platinum_coin", 4)

               GUI.play_sound("core.complete1")
               common.quest_completed()
            end,
            {"progress.last._2"},
         },
         on_finish = function(t)
            Internal.set_quest_flag("pael_and_her_mom", 1000)
            t.speaker:set_flag("IsSilent", true)
         end
      },

      festival = {
         text = {
            {"progress.festival.dialog"},
         },
         choices = function()
            local choices = {}
            local potion = Item.find("core.potion_of_cure_corruption", "PlayerInventory")
            if potion ~= nil then
               table.insert(choices, {"festival_give", "progress.festival.choices.give"})
            end
            table.insert(choices, {"festival_take_care", "progress.festival.choices.take_care"})

            return choices
         end
      },
      festival_give = {
         text = {
            give_potion,
            {"progress.festival.give.dialog"},
         }
      },
      festival_take_care = {
         text = {
            {"progress.festival.take_care"},
         }
      },

      end_life = {
         text = {
            {"progress.end_life.dialog._0", args = common.args_name},
            {"progress.end_life.dialog._1"},
         },
         choices = function()
            local choices = {}
            local potion = Item.find("core.potion_of_cure_corruption", "PlayerInventory")
            if potion ~= nil then
               table.insert(choices, {"end_life_give", "progress.end_life.choices.give"})
            end
            table.insert(choices, {"end_life_end", "progress.end_life.choices.end"})
            table.insert(choices, {"end_life_leave", "progress.end_life.choices.leave"})

            return choices
         end
      },
      end_life_give = {
         text = {
            give_potion,
            {"progress.end_life.give.dialog"},
         }
      },
      end_life_end = {
         text = {
            {"progress.end_life.end"},
         },
         on_finish = function(t)
            World.add_deferred_event(20, t.speaker.index)
         end
      },
      end_life_leave = {
         text = {
            {"progress.end_life.leave"},
         }
      },

      very_late = {
         text = {
            {"progress.very_late"},
         }
      },
      late = {
         text = {
            {"progress.late", args = common.args_name},
         }
      },
      mid = {
         text = {
            {"progress.mid"},
         }
      },
      early = {
         text = {
            {"progress.early"},
         },
      },
   }
}
