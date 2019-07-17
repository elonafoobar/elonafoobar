local Internal = Elona.require("Internal")

return {
   id = "zeome",
   root = "core.talk.unique.zeome",

   nodes = {
      __start = {
         text = {
            {"dialog"}
         },
         choices = {
            {"__END__", "__MORE__"}
         },
         on_finish = function()
            Internal.set_quest_flag("main_quest", 170)
         end
      }
   }
}
