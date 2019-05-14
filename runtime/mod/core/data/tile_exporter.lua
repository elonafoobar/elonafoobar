data:define_type("tile_exporter")
data:add_multi(
   "core.tile_exporter",
   {
      {
         id = "chara",
         base = "core.chara",
         maximum = 188,
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
               atlas = "__BUILTIN__/graphic/character.bmp",
               properties = {
                  legacy_id = tostring(v.legacy_id)
               }
            }
         end
      },
      {
         id = "item",
         base = "core.item",
         maximum = 400,
         export = function(v)
            local image = ""
            image = data.by_legacy["core.item_chip"][v.image]
            image = data.raw["core.item_chip"][image]

            return {
               source = image.source,
               color = image.color,
               atlas = "__BUILTIN__/graphic/item.bmp",
               tall = image.tall,
               properties = {
                  legacy_id = tostring(v.legacy_id)
               }
            }
         end
      },
      {
         id = "map_chip",
         base = "core.map_chip",
         on_export = function(exporter)
            exporter.export({atlas_index = 1})
            exporter.export({atlas_index = 2})
            exporter.export({atlas_index = 3})
         end,
         export = function(v, opts)
            if tonumber(opts.atlas_index) ~= v.atlas then
               return nil
            end

            return {
               source = v.source,
               atlas = "__BUILTIN__/graphic/map" .. opts.atlas_index .. ".bmp",
               properties = {
                  legacy_id = tostring(v.legacy_id)
               }
            }
         end
      },
      {
         id = "map_object",
         base = "core.map_object",
         export = function(v, opts)
            local sources = {}
            for _, tile in ipairs(v.tiles) do
               sources[#sources+1] = {
                  source = data.raw["core.map_chip"][tile].source,
                  atlas = "__BUILTIN__/graphic/map1.bmp",
                  image_name = tostring(v.legacy_id) .. "_" .. tile,
                  properties = {
                     legacy_id = tostring(v.legacy_id),
                     tile = tile
                  }
               }
            end

            return sources
         end
      }
   }
)
