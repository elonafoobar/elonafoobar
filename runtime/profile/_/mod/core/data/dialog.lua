local Chara = Elona.require("Chara")
local Event = Elona.require("Event")
local I18n = Elona.require("I18n")

local npc = nil

data:define_type("dialog")
data:add_multi(
   "core.dialog",
   {
      {
         name = "whom_dwell_in_the_vanity",

         -- TODO legacy field that needs removal.
         _full_id = "core.dialog#core.whom_dwell_in_the_vanity",

         nodes = {
            _start = {
               text = "core.locale.talk.unique.whom_dwell_in_the_vanity",
               choices = "End"
            }
         }
      },
      {
         name = "orphe",

         nodes = {
            __start = function()
               if Event.id() == 1 then
                  return "dialog"
               else
                  return "__ignored__"
               end
            end,
            dialog = function(t)
               t.text { "core.locale.talk.unique.orphe.dialog._0", I18n.get_enum("core.locale.ui.sex", Chara.player().sex) }
               t.text_enum { "core.locale.talk.unique.orphe.dialog", 1, 5 }
            end
         }
      },
      {
         name = "loyter",

         nodes = {
            __start = function()
            end,
         }
      },
      npc,
   }
)
