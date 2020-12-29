local Data = require("core.Data")

local unique = require_relative("dialog/unique.lua")

Data.define_prototype("dialog")
Data.add(
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
Data.add("core.dialog", unique)
