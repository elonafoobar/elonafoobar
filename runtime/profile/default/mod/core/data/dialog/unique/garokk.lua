local Internal = Elona.require("Internal")

return {
   id = "garokk",
   root = "core.locale.talk.unique.garokk",
   nodes = {
      __start = {
         text = {
            {"dialog"},
         },
         choices = {
            {"__END__", "__BYE__"},
         }
      },
      -- Unused in vanilla.
      craft = function()
         Internal.material_kit_crafting_menu()
         return "__start"
      end
   }
}
