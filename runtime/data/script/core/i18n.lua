--- Functions for localization.
--  See the I18N section for more information.
--  @usage local I18N = ELONA.require("core.I18N")
--  @module "I18N"
local I18N = {}


local internal = kernel.I18N


local function get(key, args)
   return internal.get_optional(key, args) or ("<Unknown ID: %s>"):format(key)
end


local function get_optional(key, args)
   return internal.get_optional(key, args)
end


local function get_data_text(key, args)
   return internal.get_data_text_optional(key, args) or ("<Unknown ID: %s>"):format(key)
end


--- Gets a localized string and optionally formats it with arguments.
--  This will return a string with a warning if the localization
--  string doesn't exist.
--
--  @tparam string key the ID of the localization string
--  @treturn string the formatted string
--  @usage I18N.get("core.map.you_see", "Vernis")
--  @function get
function I18N.get(key, ...)
   return get(key, {...})
end


--- Gets a localized string and optionally formats it with arguments.
--  This will return nil if the localization string doesn't exist.
--
--  @tparam string key the ID of the localization string
--  @treturn[1] string the formatted string
--  @treturn[2] nil
--  @function get_optional
function I18N.get_optional(key, ...)
   return get_optional(key, {...})
end


--- Gets a localized string from an enum-style localization object.
--  This will return a string with a warning if the localization
--  string doesn't exist.
--
--  @tparam string key the ID of the localization string
--  @tparam num index the index into the enum
--  @treturn string the formatted string
--  @function get_enum
function I18N.get_enum(key, index, ...)
   return get(("%s._%d"):format(key, index), {...})
end


--- Gets a localized string from an enum-style localization object and optionally
--  formats it with arguments. This will return nil if the localization string
--  doesn't exist.
--
--  @tparam string key the ID of the localization string
--  @tparam num index the index into the enum
--  @treturn[1] string the formatted string
--  @treturn[2] nil
--  @function get_enum_optional
function I18N.get_enum_optional(key, index, ...)
   return get_optional(("%s._%d"):format(key, index), {...})
end


--- Gets a localized string from an enum-style localization object
--  where the enum's children are themselves objects. This will return
--  a string with a warning if the localization string doesn't exist.
--
--  @tparam string key_base the base ID of the localization string
--  @tparam string key_property the property of the enum object to get
--  @tparam num index the index into the enum
--  @treturn string the formatted string
--  @function get_enum_property
function I18N.get_enum_property(key_base, key_property, index, ...)
   return get(("%s._%d.%s"):format(key_base, index, key_property), {...})
end


--- Gets a localized string from an enum-style localization object
--  where the enum's children are themselves objects. This will return
--  nil if the localization string doesn't exist.
--
--  @tparam string key_base the base ID of the localization string
--  @tparam string key_property the property of the enum object to get
--  @tparam num index the index into the enum
--  @treturn[1] string the formatted string
--  @treturn[2] nil
--  @function get_enum_property_optional
function I18N.get_enum_property_optional(key_base, key_property, index, ...)
   return get_optional(("%s._%d.%s"):format(key_base, index, key_property), {...})
end


--- Get a localized text associated with the given data ID.
--  This will return a string with a warning if the localization
--  string doesn't exist.
--
--  @tparam string prototype_id Data prototype ID.
--  @tparam string instance_id Data instance ID.
--  @tparam string property_name I18N key of the property to get.
--  @treturn string The formatted string
--  @function get_data_text
function I18N.get_data_text(prototype_id, instance_id, property_name, ...)
   return get_data_text(("%s#%s.%s"):format(prototype_id, instance_id, property_name), {...})
end


I18N.add = internal.add
I18N.add_data_text = internal.add_data_text
I18N.add_function = internal.add_function


return I18N
