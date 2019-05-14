local magic = require("data/magic/magic")

data:define_type("magic")
data:add_multi(
   "core.magic",
   {
      {
         id = "eye_of_insanity",
         legacy_id = 636,
         callback = magic.eye_of_insanity
      }
   }
)
