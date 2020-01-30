local process_section
local process_option



local function stype(v)
   if type(v) == "number" then
      return math.type(v)
   else
      return type(v)
   end
end



local function process_section_internal(schema, options)
   assert(#options % 2 == 0, "invalid config schema")

   local is_hidden = true
   local children_keys = {}
   for i = 1, #options//2 do
      local kind = options[i*2 - 1][1]
      local name = options[i*2 - 1][2]
      if type(name) ~= "string" then
         error("option or section name must be string, but "..type(name))
      end
      local def = options[i*2]

      if kind == "section" then
         schema[name] = process_section(def)
      elseif kind == "option" then
         local v, err = process_option(def)
         if err then
            error("option '"..name.."': "..err)
         end
         schema[name] = v
      else
         error("unknown config type: "..tostring(kind))
      end
      is_hidden = is_hidden and schema[name].is_hidden
      children_keys[#children_keys+1] = name
   end

   is_hidden = is_hidden or options.is_hidden
   return schema, is_hidden, children_keys
end



process_section = function(def)
   local schema, is_hidden, children_keys = process_section_internal({}, def)
   return {
      type = "section",
      children = schema,
      is_hidden = is_hidden,
      children_keys = children_keys,
   }
end



process_option = function(def)
   local ty = stype(def)
   if ty == "boolean" then
      return {
         type = "boolean",
         default = def,
      }
   elseif ty == "integer" then
      return {
         type = "interger",
         default = def,
      }
   elseif ty == "float" then
      return {
         type = "float",
         default = def,
      }
   elseif ty == "string" then
      return {
         type = "string",
         default = def,
      }
   elseif ty == "table" then
      -- TODO
      def.type = def.type or stype(def.default)
      if not def.type then
         return nil, "cannot detect the type of the option: set default value or type."
      end
      def.type = def.type or stype(def.default)
      return def
   else
      return nil, "option default value must be boolean, number, string or table."
   end
end



--[[
local env = make_dsl_env(result)
local result = {}
assert(loadfile(path, "t", env))(result)
print(result.schema)
--]]
local function make_dsl_env(result)
   local config = function(def)
      local schema, _, children_keys = process_section_internal({}, def)
      result.schema = schema
      result.children_keys = children_keys
   end
   local section = function(name)
      return {"section", name}
   end
   local option = function(name)
      return {"option", name}
   end

   return {
      config = config,
      section = section,
      option = option,
   }
end



local function eval_in_dsl_env(chunk_str, chunk_name, mod_id)
   local result = {}

   local env = make_dsl_env(result)
   local f, err = load(chunk_str, chunk_name, "t", env)
   if err then
      -- TODO Log.warn(err, mod_id)
      print(err)
      return nil
   end
   local _, err = pcall(f)
   if err then
      -- TODO Log.warn(err, mod_id)
      print(err)
      return nil
   end

   return result
end



return eval_in_dsl_env
