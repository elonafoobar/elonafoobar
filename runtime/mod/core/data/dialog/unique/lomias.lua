local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")

local common = require("data/dialog/common")

return {
   id = "lomias",
   root = "core.locale.talk.unique.lomias",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("tutorial")
         if flag == 0 then
            return "tutorial_0"
         elseif flag == 1 then
            return "tutorial_1"
         elseif flag == 2 then
            return "tutorial_2"
         elseif flag == 3 then
            return "tutorial_3"
         elseif flag == 4 then
            return "tutorial_4"
         elseif flag == 5 then
            return "tutorial_5"
         elseif flag == 6 then
            return "tutorial_6"
         elseif flag == 7 then
            return "tutorial_7"
         elseif flag == 8 then
            return "tutorial_8"
         elseif flag == 99 then
            return "tutorial_99"
         elseif flag == -1 then
            return "tutorial_after"
         end

         return "__END__"
      end,
      tutorial_0 = {
         text = {
            {"tutorial.before.dialog"},
         },
         choices = {
            {"start_tutorial", "tutorial.before.choices.yes"},
            {"__END__", "tutorial.before.choices.no"},
            {"get_out", "after.choices.get_out"}
         }
      },
      tutorial_1 = {
         text = {
            {"tutorial.movement.dialog._0"},
            {"tutorial.movement.dialog._1"},
            {"tutorial.movement.dialog._2"},
            {"tutorial.movement.dialog._3"},
         },
         choices = {
            {"__END__", "tutorial.movement.choices.alright"},
            {"ate", "tutorial.movement.choices.ate"}
         }
      },
      tutorial_2 = {
         text = {
            {"tutorial.skills.dialog._0"},
            {"tutorial.skills.dialog._1"},
            {"tutorial.skills.dialog._2"},
         },
         choices = {
            {"__END__", "tutorial.skills.response"}
         }
      },
      tutorial_3 = {
         text = {
            function()
               GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
               local scroll = Item.create(Chara.player().position, "core.scroll_of_identify", 0)
               scroll.identify_state = "Completely"
            end,
            {"tutorial.after_dig.dialog"},
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            Internal.set_quest_flag("tutorial", 4)
         end
      },
      tutorial_4 = {
         text = {
            {"tutorial.identify.dialog._0"},
            {"tutorial.identify.dialog._1"},
            {"tutorial.identify.dialog._2"},
         },
         choices = {
            {"__END__", "tutorial.identify.choices.alright"},
            {"identify_done", "tutorial.identify.choices.done"},
         }
      },
      tutorial_5 = {
         text = {
            {"tutorial.equip.dialog"}
         },
         choices = {
            {"__END__", "tutorial.equip.choices.alright"},
            {"equip_done", "tutorial.equip.choices.done"},
         }
      },
      tutorial_6 = function()
         local putit = Chara.find("core.putit", "Others")
         if putit ~= nil then
            return "tutorial_6_not_finished"
         end
         return "tutorial_6_finished"
      end,
      tutorial_6_not_finished = {
         text = {
            {"tutorial.combat.not_finished"}
         }
      },
      tutorial_6_finished = {
         text = {
            {"tutorial.combat.finished"}
         },
         choices = {
            {"tutorial_7", "__MORE__"}
         },
         on_finish = function()
            Internal.set_quest_flag("tutorial", 7)
         end
      },
      tutorial_7 = {
         text = {
            {"tutorial.chests.dialog._0"},
            {"tutorial.chests.dialog._1"},
            function()
               local chest = Item.create(Chara.player().position, "core.chest", 0)
               chest.param1 = 35
               chest.param2 = 25
               Item.create(Chara.player().position, "core.lockpick", 2)
               GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
            end,
            {"tutorial.chests.dialog._2"},
         },
         choices = {
            {"__END__", "tutorial.chests.response"}
         },
         on_finish = function()
            Internal.set_quest_flag("tutorial", 8)
         end
      },
      tutorial_8 = {
         text = {
            {"tutorial.house.dialog._0"},
            {"tutorial.house.dialog._1"},
            {"tutorial.house.dialog._2"},
            {"tutorial.house.dialog._3"}
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            Internal.set_quest_flag("tutorial", 99)
         end
      },
      tutorial_99 = {
         text = {
            {"tutorial.end.dialog._0"},
            {"tutorial.end.dialog._1"}
         },
         on_finish = function()
            Internal.set_quest_flag("tutorial", -1)
         end
      },
      tutorial_after = {
         text = {
            {"after.dialog"}
         },
         choices = {
            {"__END__", "after.choices.nothing"},
            {"get_out", "after.choices.get_out"}
         }
      },
      start_tutorial = {
         text = {
            {"tutorial.before.yes"}
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            local corpse = Item.create(Chara.player().position, "core.corpse", 0)
            corpse.subname = 9
            corpse.identify_state = "Completely"
            GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
            Internal.set_quest_flag("tutorial", 1)
         end
      },
      get_out = function(t)
         local larnneire = Chara.find("core.larnneire", "Others")
         if not Chara.is_alive(larnneire) then
            local lomias = Chara.find("core.lomias", "Others")
            Chara.player():act_hostile_against(lomias)
            t:say("after.get_out.larnneire_died", "__BYE__")
            return "__END__"
         end
         return "get_out_1"
      end,
      get_out_1 = {
         text = {
            {"after.get_out.dialog._0", args = common.args_name, speaker = "core.larnneire"},
            {"after.get_out.dialog._1", speaker = "core.lomias"},
            {"after.get_out.dialog._2", args = common.args_title},
         },
         on_finish = function()
            Chara.find("core.larnneire", "Others"):vanquish()
            Chara.find("core.lomias", "Others"):vanquish()

            GUI.txt(I18N.get("core.locale.quest.completed"))
            GUI.play_sound("core.complete1")
            GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
            for i=0,2 do
               Item.create(Chara.player().position, {flttypemajor = 60000})
            end
         end
      },
      ate = {
         text = {
            {"tutorial.movement.ate.dialog._0", choice = "tutorial.movement.ate.response"},
            {"tutorial.movement.ate.dialog._1"},
            {"tutorial.movement.ate.dialog._2"},
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            Internal.set_quest_flag("tutorial", 2)
         end
      },
      identify_done = {
         text = {
            {"tutorial.identify.done.dialog._0"},
            {"tutorial.identify.done.dialog._1"},
         },
         choices = {
            {"__start", "__MORE__"}
         },
         on_finish = function()
            local item = Item.create(Chara.player().position, "core.long_bow", 0)
            item.curse_state = "Cursed"
            item = Item.create(Chara.player().position, "core.arrow", 0)
            item.curse_state = "None"
            item = Item.create(Chara.player().position, "core.scroll_of_vanish_curse", 0)
            item.identify_state = "Completely"
            item.curse_state = "Blessed"
            GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
            Internal.set_quest_flag("tutorial", 5)
         end
      },
      equip_done = {
         text = {
            {"tutorial.equip.done.dialog._0"},
            {"tutorial.equip.done.dialog._1"},
            {"tutorial.equip.done.dialog._2"}
         },
         choices = {
            {"__END__", "__MORE__"}
         },
         on_finish = function()
            GUI.txt(I18N.get("core.locale.talk.unique.lomias.tutorial.equip.done.lomias_releases"), "Cyan")
            for i=0,2 do
               local putit = Chara.create(Chara.player().position, "core.putit")
               putit:set_flag("IsNotAttackedByEnemy", true)
            end
            local item = Item.create(Chara.player().position, "core.potion_of_cure_minor_wound", 0)
            item.identify_state = "Completely"
            Internal.set_quest_flag("tutorial", 6)
         end
      }
   }
}
