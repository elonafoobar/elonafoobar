data:add(
   {
      {
         type = "core.item",
         name = "warper",

         id = 910,
         image = 695,
         value = 780,
         weight = 500,

         material = 35,
         is_usable = true,

         level = 1,
         category = 60000,
         subcategory = 99999,
         rarity = 1000000,
         coefficient = 100,

         color = "Blue",
         locale_key_prefix = "warp.locale.item.warper",

         on_use_callback = "exports:warp.on_use.warper"
      }
})
