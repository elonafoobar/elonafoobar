local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local table = Elona.require("table")

return {
   id = "whom_dwell_in_the_vanity",
   root = "core.locale.talk.unique.whom_dwell_in_the_vanity",
   nodes = {
      __start = {
         text = {
            {"dialog"},
         },
      },
   }
}
