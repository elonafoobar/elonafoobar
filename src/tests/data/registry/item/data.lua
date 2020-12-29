local Data = ELONA.require("core.Data")

-- Contains all possible item parameters for testing.
Data.add(
   "core.item",
   {
      putitoro = {
         integer_id = 9999,
         image = 695,
         value = 2000,
         weight = 200,
         dice_x = 0,
         dice_y = 0,
         hit_bonus = 0,
         damage_bonus = 0,
         pv = 0,
         dv = 0,
         material = 0,
         chargelevel = 0,
         is_readable = false,
         is_zappable = false,
         is_drinkable = false,
         is_cargo = true,
         is_usable = false,
         appearance = 0,
         expiration_date = 0,
         level = 1,
         fltselect = 1,
         category = 57000,
         subcategory = 99999,
         rarity = 150000,
         coefficient = 0,
         light = 0,
         originalnameref2 = "",
         has_random_name = false,
         tags = { "noshop", "nodownload" },
         rftags = { "fish" },
         color = "white",
         locale_key_prefix = "core.item.putitoro",
      }
   }
)
