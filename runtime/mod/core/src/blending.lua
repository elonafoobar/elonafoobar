local data = require("core.data")
local i18n = require("core.i18n")
local table = table



local Blending = {}



function Blending.get_material_name(recipe_id, step)
   local recipe_data = data.get("core.blending_recipe", recipe_id)
   assert(recipe_data)
   local material = recipe_data.materials[step]
   assert(material)

   if material == "anything" then
      return i18n.get("core.blending.material.filter.anything")
   end
   if material.filter then
      return i18n.get("core.blending.material.filter."..material.filter)
   end
   if material.category then
      return i18n.get_enum_optional("core.item.filter_name", material.category)
            or i18n.get("core.item.filter_name.default")
   end
   if material.id then
      local item_data = data.get("core.item", material.id)
      local item_name = i18n.get(item_data.locale_key_prefix..".name")
      if material.of then
         local chara_name = i18n.get_data_text("core.chara", material.of, "name")
         return i18n.get("core.blending.material.item_of", item_name, chara_name)
      else
         return item_name
      end
   end
   return "?????"
end



function Blending.check_material(item, recipe_id, step)
   local recipe_data = data.get("core.blending_recipe", recipe_id)
   assert(recipe_data)
   local material = recipe_data.materials[step]
   assert(material)

   if material == "anything" then
      return true
   end
   if material.filter then
      local item_data = data.get("core.item", item.id)
      return not not table.contains(item_data.rftags, material.filter)
   end
   if material.category then
      local item_data = data.get("core.item", item.id)
      return item_data.category == material.category
   end
   if material.id then
      if material.of then
         return item.id == material.id and (material.of == data.get_id_by_integer("core.chara", item.subname))
      else
         return item.id == material.id
      end
   end
   return false
end



return Blending
