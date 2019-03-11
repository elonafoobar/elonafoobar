local unique = require("data/dialog/unique")

data:define_type("dialog")
data:add_multi(
   "core.dialog",
   {
      lomias = unique.lomias
   }
)
