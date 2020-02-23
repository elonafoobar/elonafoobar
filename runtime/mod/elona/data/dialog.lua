local unique = require("data/dialog/unique")

data:add_multi(
   "core.dialog",
   {
      {
         id = "ignored",
         root = "elona.talk",
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
