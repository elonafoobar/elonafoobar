local unique = require("data/dialog/unique")

data:define_type("dialog")
data:add_multi(
   "core.dialog",
   {
      {
         id = "ignored",
         root = "core.talk",
         nodes = {
            __start = {
               text = {
                  {"ignores_you", args = function(t) return {t.speaker} end},
               }
            },
         }
      }
   }
)
data:add_multi("core.dialog", unique)
