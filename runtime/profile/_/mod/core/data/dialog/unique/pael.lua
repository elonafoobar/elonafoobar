local GUI = Elona.require("GUI")
local Map = Elona.require("Map")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

local common = require("data/dialog/common")

local function prompt_give_potion(prompt)
   return {
      text = {
         prompt
      },
      choices = {
         {"give_check", "give.choice"},
         {"__END__", "__BYE__"}
      }
   }
end

return {
   name = "pael",
   root = "core.locale.talk.unique.pael",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("pael_and_her_mom")
         if flag == 1000 then
            if Map.id() == "core.noyel" and Map.area().christmas_festival then
               return "festival"
            end
            return "after_face"
         elseif flag == 1001 then
            return "after_death"
         elseif flag == 1002 then
            return "after_sold"
         elseif flag == 0 then
            return "before"
         elseif flag == 1 or flag == 3 then
            return "progress_0"
         elseif flag == 5 or flag == 7 then
            return "progress_1"
         elseif flag == 2 or flag == 4 then
            return "progress_2"
         elseif flag == 6 then
            return "progress_3"
         elseif flag == 8 then
            return "progress_4"
         elseif flag == 9 then
            return "progress_5"
         elseif flag == 10 then
            return "progress_6"
         end

         return "__IGNORED__"
      end,
      give_check = function()
         local potion = Item.find("core.potion_of_cure_corruption", "PlayerInventory")
         if potion == nil then
            return "do_not_have_potion"
         end

         return "give_potion"
      end,
      do_not_have_potion = {
         text = {
          {"give.do_not_have"}
         },
         choices = {
            {"__END__", "__MORE__"}
         }
      },
      give_potion = {
         text = {
            function()
               local potion = Item.find("core.potion_of_cure_corruption", "PlayerInventory")
               potion.number = potion.number - 1
               GUI.txt(I18N.get("core.locale.talk.unique.pael.give.you_give"))
               GUI.play_sound("core.equip1")
            end,
            {"give.dialog"}
         },
         choices = {
            {"__END__", "__MORE__"}
         },
         on_finish = function()
            GUI.show_journal_update_message()
            Internal.set_quest_flag("pael_and_her_mom", Internal.get_quest_flag("pael_and_her_mom") + 1)
         end
      },
      after_face = {
         text = {
            {"after_face"},
         }
      },
      after_sold = {
         text = {
            {"after_sold"},
         }
      },
      after_death = {
         text = {
            {"after_death"},
         }
      },
      festival = {
         text = {
            {"festival"}
         }
      },
      before = prompt_give_potion({"before"}),
      progress_0 = {
         text = {
            {"progress._0"},
         }
      },
      progress_1 = {
         text = {
            {"progress._1", args = common.args_name},
         }
      },
      progress_2 = prompt_give_potion({"progress._2", args = common.args_name}),
      progress_3 = prompt_give_potion({"progress._3"}),
      progress_4 = prompt_give_potion({"progress._4", args = common.args_name}),
      progress_5 = {
         text = {
            {"progress._5"},
         }
      },
      progress_6 = {
         text = {
            {"progress._6", args = common.args_name},
         }
      },
   }
}
