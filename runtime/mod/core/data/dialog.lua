local unique = require("dialog/unique.lua")

data:define_prototype("dialog")
data:add(
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
data:add("core.dialog", unique)
