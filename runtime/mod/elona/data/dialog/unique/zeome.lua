local Internal = Elona.game.Internal

return {
   id = "zeome",
   root = "elona.talk.unique.zeome",

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
