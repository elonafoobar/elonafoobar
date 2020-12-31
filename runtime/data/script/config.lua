local config = {}

local xtype, inspect = _ENV.prelude.xtype, _ENV.prelude.inspect
local Fs = _ENV.native.Fs

local eval_in_dsl_env = require("config_dsl")
local json5 = require("json5")

local function make_schema(schema)
   local result = {}

   local flatten
   function flatten(table, current)
      for k, v in pairs(table) do
         local key = current and (current.."."..k) or k
         result[key] = v
         if v.type == "section" then
            flatten(v.children, key)
         end
      end
   end

   flatten(schema)

   return result
end

local _setters = {}
local _options = {}
local _schemas = {}

--[[
-- { a = { b = { c = 1 }, d = 2 } }
-- => { ["a.b.c"] = 1, ["a.d"] = 2 }
--]]
local function flatten(obj)
   local result = {}

   local f
   f = function(table, cur)
      for k, v in pairs(table) do
         local key = cur and (cur.."."..k) or k
         if type(v) == "table" then
            f(v, key)
         else
            result[key] = v
         end
      end
   end
   f(obj)

   return result
end



local function exists(option_key)
   return _schemas[option_key] and _schemas[option_key].type ~= "section"
end



local function validate(schema, value)
   local default = schema.default

   -- Check 'type'.
   if xtype(value) ~= schema.type then
      return default
   end

   -- Check 'enum'.
   if schema.enum then
      for _, e in ipairs(schema.enum) do
         if e == value then
            return value
         end
      end
      if value == "__unknown__" then
         return value
      else
         return default
      end
   end

   -- Check 'min'.
   if schema.min then
      if value < schema.min then
         return schema.min
      end
   end

   -- Check 'max'.
   if schema.max then
      if schema.max < value then
         return schema.max
      end
   end

   return value -- It is perfectly valid.
end



local function load_options_impl(config_str, filename)
   local conf, err = json5.parse(config_str)
   if err then
      log_warn(err)
      return
   end

   conf = flatten(conf)
   for k, v in pairs(conf) do
      config.set(k, v)
   end
end



local function load_default_values_if_unset()
   for option_key, schema in pairs(_schemas) do
      if config.get(option_key) == nil then
         -- Almost all of options have thier own default values, but there are some exceptions:
         -- * Sections
         -- * Option "core.screen.display_mode" in headless mode
         if schema.default ~= nil then
            config.set(option_key, schema.default)
         end
      end
   end
end



local function should_save(option_key, value)
   local schema = _schemas[option_key]
   return not schema.is_hidden or value ~= schema.default
end

local function split_keys_by_dot(keys)
   local ret = {}
   for k in keys:gmatch("([^.]+)") do
      ret[#ret+1] = k
   end
   return ret
end

-- option_key :: string
-- setter :: (string | number | boolean) -> nil
-- result :: nil
function config.bind_setter(option_key, setter)
   assert(exists(option_key), "config.bind_setter(): option '"..option_key.."' not found")

   _setters[option_key] = setter
end

function config.inject_enum(option_key, enum, default_value)
   assert(#enum ~= 0, "config.inject_enum(): enum must have at least one value.")

   _schemas[option_key].enum = enum
   _schemas[option_key].default = default_value

   if default_value ~= "__unknown__" then
      for i = 1, #enum do
         if enum[i] == default_value then
            return
         end
      end
      assert(false, "config.inject_enum(): default_value must be in enum.")
   end
end

function config.validate(option_key, value)
   return validate(_schemas[option_key], value)
end

function config.load_schema(schema_str, filename, mod_id)
   local result = eval_in_dsl_env(schema_str, filename, mod_id)
   if not result then
      return
   end

   local schema = {
      [mod_id] = {
         type = "section",
         children = result.schema,
         children_keys = result.children_keys,
      }
   }
   _schemas = make_schema(schema)
end

function config.load_options(config_str, filename)
   load_options_impl(config_str, filename)
   load_default_values_if_unset()

   local options = {}
   for k, v in pairs(_options) do
      options[#options + 1] = { k, v }
   end
   table.sort(options, function(a, b) return a[1] < b[1] end)
   for _, kv in pairs(options) do
      log_info(("Config: '%s' = %s"):format(kv[1], inspect(kv[2])))
   end
end

function config.serialize()
   local obj = {}
   for option_key, value in pairs(_options) do
      if should_save(option_key, value) then
         local keys = split_keys_by_dot(option_key)
         local o = obj
         for i = 1, #keys-1 do
            local key = keys[i]
            if not o[key] then
               o[key] = {}
            end
            o = o[key]
         end
         o[keys[#keys]] = value
      end
   end

   local ordering = {} -- TODO

   local opts = {
      prettify = true,
      unquote_key = true,
      insert_trailing_comma = true,
      sort = function(_k1, v1, _k2, v2)
         return ordering[v1] < ordering[v2]
      end,
   }
   return json5.stringify(obj, opts)
end

function config.save()
   local path = Fs.get_config_file_path(__PROFILE_ID)
   local file = io.open(path, "w")
   local output = config.serialize()
   assert(file:write(output))
   file:flush()
   file:close()
end

function config.clear()
   _setters = {}
   _options = {}
   _schemas = {}
end

-- option_key :: string
-- value :: string | number | boolean
-- result :: nil
function config.set(option_key, value)
   if value == nil then return end

   if exists(option_key) then
      value = config.validate(option_key, value)
      _options[option_key] = value
      if _setters[option_key] then
         _setters[option_key](value)
      end
   else
      log_warn(("Config.set: option '%s' not found"):format(option_key))
   end
end

-- option_key :: string
-- result :: string | number | boolean | nil
function config.get(option_key)
   return _options[option_key]
end

function config.get_children_keys(option_key)
   if _schemas[option_key] then
      return _schemas[option_key].children_keys
   else
      return {}
   end
end

function config.get_enum(option_key)
   return _schemas[option_key].enum
end

function config.get_min(option_key)
   return _schemas[option_key].min or math.mininteger
end

function config.get_max(option_key)
   return _schemas[option_key].max or math.maxinteger
end

function config.get_step(option_key)
   return _schemas[option_key].step or 1
end

function config.is_boolean_option(option_key)
   return _schemas[option_key].type == "boolean"
end

function config.is_integer_option(option_key)
   return _schemas[option_key].type == "integer"
end

function config.is_string_option(option_key)
   return _schemas[option_key].type == "string"
end

function config.is_enum_option(option_key)
   local s = _schemas[option_key]
   return s.type == "string" and s.enum ~= nil
end

function config.is_section(option_key)
   return _schemas[option_key].type == "section"
end

function config.is_hidden(option_key)
   if option_key:match("^[%w_]+%.wizard$") then
      -- Section <any mod name>.wizard is hidden unless wizard mode is enabled.
      return not config.get("core.wizard.is_enabled")
   else
      return not not _schemas[option_key].is_hidden
   end
end

return config
