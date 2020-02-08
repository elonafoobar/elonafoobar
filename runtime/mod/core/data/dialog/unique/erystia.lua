local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item
local table = Elona.game.table

local common = require("data/dialog/common")

return {
   id = "erystia",
   root = "core.talk.unique.erystia",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("main_quest")
         if flag == 200 then
            return "late"
         elseif flag == 120 then
            return "all_stones"
         elseif flag == 105 then
            return "stones"
         elseif flag >= 60 then
            return "investigation"
         elseif flag == 50 then
            return "introduction"
         end
         return "__IGNORED__"
      end,

      late = {
         text = {
            {"late._0"},
            {"late._1"},
            {"late._2", args = function() return {Chara.player().title, Chara.player().basename} end},
         },
         choices = {
            {"__END__", "__MORE__"},
         }
      },

      all_stones = {
         text = {
            {"all_stones.dialog._0", args = common.args_name},
            {"all_stones.dialog._1"},
            {"all_stones.dialog._2"},
            {"all_stones.dialog._3", args = common.args_name},
         },
         on_finish = function()
            GUI.play_sound("core.write1")
            GUI.txt(I18N.get("core.talk.unique.erystia.all_stones.you_receive"), "Green")
            Item.create(Chara.player().position, "core.palmia_pride", 0)
            GUI.txt(I18N.get("core.common.something_is_put_on_the_ground"))
            Internal.set_quest_flag("main_quest", 125)
         end
      },

      stones = {
         text = {
            {"stones.dialog._0", args = common.args_name},
            GUI.fade_out,
            {"stones.dialog._1"},
            {"stones.dialog._2"},
            {"stones.dialog._3"},
            {"stones.dialog._4"},
         },
         on_finish = function()
            GUI.play_sound("core.write1")
            GUI.txt(I18N.get("core.talk.unique.erystia.stones.you_receive"), "Green")
            Internal.set_quest_flag("main_quest", 110)
         end
      },

      investigation = {
         text = {
            {"investigation.dialog", args = common.args_name},
         },
         choices = function()
            local choices = {
               {"lesmias", "investigation.choices.lesimas"},
               {"mission", "investigation.choices.mission"},
            }
            local flag = Internal.get_quest_flag("main_quest")

            if flag >= 100 and flag <= 120 then
               table.insert(choices, {"stones_castle", "investigation.choices.stones.castle"})
               table.insert(choices, {"stones_inferno", "investigation.choices.stones.inferno"})
               table.insert(choices, {"stones_crypt", "investigation.choices.stones.crypt"})
            end

            table.insert(choices, {"__END__", "__BYE__"})

            return choices
         end
      },
      lesmias = {
         text = {
            {"investigation.lesmias._0"},
            {"investigation.lesmias._1"},
            {"investigation.lesmias._2"},
            {"investigation.lesmias._3"},
            {"investigation.lesmias._4"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },

      mission = function()
         local flag = Internal.get_quest_flag("main_quest")

         if flag >= 125 then
            return "mission_excavation"
         elseif flag >= 110 then
            return "mission_stones_0"
         else
            return "mission_stones_1"
         end
      end,
      mission_excavation = {
         text = {
            {"investigation.mission.excavation._0"},
            {"investigation.mission.excavation._1"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      mission_stones_0 = {
         text = {
            {"investigation.mission.stones._0"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      mission_stones_1 = {
         text = {
            {"investigation.mission.stones._1", args = common.args_name},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      stones_castle = {
         text = {
            {"investigation.castle._0"},
            {"investigation.castle._1"},
            {"investigation.castle._2"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      stones_inferno = {
         text = {
            {"investigation.inferno._0"},
            {"investigation.inferno._1"},
            {"investigation.inferno._2"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      stones_crypt = {
         text = {
            {"investigation.crypt._0"},
            {"investigation.crypt._1"},
            {"investigation.crypt._2"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },

      introduction = {
         text = {
            {"introduction.dialog", args = common.args_name},
         },
         choices = {
            {"pledge_strength", "introduction.choices.pledge_strength"},
            {"not_interested", "introduction.choices.not_interested"},
         },
         default_choice = "not_interested"
      },
      not_interested = {
         text = {
            {"introduction.not_interested"},
         }
      },
      pledge_strength = {
         text = {
            {"introduction.pledge_strength.dialog._0"},
            {"introduction.pledge_strength.dialog._1"},
            {"introduction.pledge_strength.dialog._2"},
            {"introduction.pledge_strength.dialog._3", args = common.args_name},
         },
         on_finish = function()
            GUI.play_sound("core.write1")
            GUI.txt(I18N.get("core.talk.unique.erystia.introduction.pledge_strength.you_receive"), "Green")
            Internal.set_quest_flag("main_quest", 60)
         end
      },
   }
}
