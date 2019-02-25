data:add(
   {
      {
         type = "core.item",
         name = "counter",

         id = 900,
         image = 900,
         value = 780,
         weight = 500,

         material = 31,
         is_usable = true,

         level = 1,
         category = 60000,
         subcategory = 99999,
         rarity = 1000000,
         coefficient = 100,

         color = "Blue",
         locale_key_prefix = "kiroku.locale.item.counter",

         on_use_callback = "exports:kiroku.on_use.counter"
      }
})
