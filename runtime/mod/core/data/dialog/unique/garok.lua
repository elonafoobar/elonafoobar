local Internal = require("core.Internal")

return {
   root = "core.talk.unique.garok",
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
