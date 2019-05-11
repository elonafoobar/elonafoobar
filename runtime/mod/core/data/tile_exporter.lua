data:define_type("tile_exporter")
data:add_multi(
   "core.tile_exporter",
   {
      {
         id = "chara",
         export = function(v)
            local image = ""
            if v.image then
               image = v.image
            elseif v.female_image then
               image = v.female_image
            elseif v.male_image then
               image = v.male_image
            else
               local race = data.raw["core.race"][v.race]
               image = race.female_image
            end
            image = data.by_legacy["core.chara_chip"][image]
            image = data.raw["core.chara_chip"][image]

            return {
               source = image.source,
               color = image.color,
               tall = image.tall,
               atlas = "__BUILTIN__/graphic/character.bmp"
            }
         end
      },
      {
         id = "item",
         export = function(v)
            local image = ""
            image = data.by_legacy["core.item_chip"][v.image]
            image = data.raw["core.item_chip"][image]

            return {
               source = image.source,
               color = image.color,
               atlas = "__BUILTIN__/graphic/item.bmp"
            }
         end
      }
   }
)
