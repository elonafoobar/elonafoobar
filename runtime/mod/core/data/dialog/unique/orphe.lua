local Chara = Elona.require("Chara")
local I18N = Elona.require("I18N")
local World = Elona.require("World")

return {
   id = "orphe",
   root = "core.locale.talk.unique.orphe",

   nodes = {
      __start = function()
         if World.deferred_event_id() == 1 then
            return "dialog"
         end

         return "__IGNORED__"
      end,
      dialog = {
         text = {
            {"dialog._0", args = function()
                local sex
                if Chara.player().sex == "Female" then
                   sex = 1
                else
                   sex = 0
                end
                return {I18N.get_enum("core.locale.ui.sex", sex)}
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
