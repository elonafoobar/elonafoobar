local Chara = require("game.Chara")
local GUI = require("game.GUI")
local I18N = require("game.I18N")
local Internal = require("game.Internal")
local table = require("game.table")

return {
   id = "poppy",
   root = "core.talk.unique.poppy",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("puppys_cave")
         if flag == 1000 then
            return "quest_completed"
         end

         return "find"
      end,
      find = {
         text = {
            {"find.dialog"},
         },
         choices = function()
            local choices = {}
            if Chara.can_recruit_allies() then
               table.insert(choices, {"take", "find.choices.take"})
            end
            table.insert(choices, {"__END__", "__BYE__"})

            return choices
         end
      },
      take = function(t)
         GUI.txt(I18N.get("core.talk.unique.poppy.find.you_must_return", t.speaker))
         t.speaker:recruit_as_ally()
         t.speaker:set_flag("IsEscortedInSubQuest", true)
         t.speaker:refresh()

         return "__END__"
      end,
      quest_completed = {
         text = {
            {"complete"},
         }
      }
   }
}
