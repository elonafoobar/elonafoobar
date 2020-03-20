local unique = require("dialog/unique.lua")

ELONA.data:define_prototype("dialog")
ELONA.data:add(
   "core.dialog",
   {
      ignored = {
         root = "core.talk",
         nodes = {
            __start = {
               text = {
                  {"ignores_you", args = function(t) return {t.speaker} end},
               }
            },
         }
      },
   }
)
ELONA.data:add("core.dialog", unique)
