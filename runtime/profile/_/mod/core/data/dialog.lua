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
      }
})
