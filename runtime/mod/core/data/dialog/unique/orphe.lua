local Chara = require("core.Chara")
local I18N = require("core.I18N")
local World = require("core.World")

return {
   root = "core.talk.unique.orphe",

   nodes = {
      __start = function()
         if World.deferred_event_id() == "core.conquer_lesimas" then
            return "dialog"
         end

         return "__IGNORED__"
      end,
      dialog = {
         text = {
            {"dialog._0", args = function()
                local sex
                if Chara.player().sex == "female" then
                   sex = 1
                else
                   sex = 0
                end
                return {I18N.get_enum("core.ui.sex", sex)}
            end},
            {"dialog._1"},
            {"dialog._2"},
            {"dialog._3"},
            {"dialog._4"},
            {"dialog._5"},
         }
      }
   }
}
