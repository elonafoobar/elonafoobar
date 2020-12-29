--[[

type I18NKey = string

type FormattableObject = string | list of Segment

type Segment = string | EmbeddedExpression

type EmbeddedExpression = Variable | FunctionCall | number | boolean | nil

type Variable = { "v", integer }

type FunctionCall = { "f", mod_name, function_name, args... }

type FormattableObjectList = list of FormattableObject. It has field `__list`, true,
                             to distinguish it from FormattableObject.


--]]


-- Stores all of locale resources except for data-associated text.
--  Keys: I18NKey
--  Values: FormattableObject | FormattableObjectList
local storage = {}

-- Stores all of data-associated locale resources.
--  Keys: I18NKey
--  Values: FormattableObject | FormattableObjectList
local storage_for_data = {}

local localize_functions = {}

-- These variables are passed from native code through "_ENV.native".
-- Parse format and returns fomattable object or error.
local parse_fmt = native.Internal.parse_fmt
-- Generate random number.
local rnd = native.Rand.rnd



-- Evaluate formattable object with given arguments and returns the result.
-- @param x Segment The formattable object
-- @param args The arguments
-- @return The formatted result. It can be non-string value.
local function eval(x, args)
   if type(x) == "string" then
      -- A plain string, just returns it.
      return x
   elseif type(x) == "table" then
      -- x is an `EmbeddedExpression`, needs evaluation.
      if x[1] == "v" then -- Is it a `Variable`?
         -- Structure:
         --  [1]: tag (string), "v"
         --  [2]: index (integer)
         local nth = x[2]
         local len = #args
         if len < nth then
            return "<missing argument #"..tostring(nth)..">"
         else
            return args[nth]
         end
      elseif x[1] == "f" then -- Is it a `FunctionCall`?
         -- Structure:
         --  [1]: tag (string), "f"
         --  [2]: namespaced_function_name (string)
         --  [3]: argument 1 (any)
         --  [4]: argument 2 (any)
         --  ...
         local func = localize_functions[x[2]]
         if not func then
            return "<unknown function '"..tostring(x[2]).."'>"
         end
         local func_args = {}
         for i = 4, #x do
            func_args[#func_args+1] = eval(x[i], args)
         end
         return func(table.unpack(func_args))
      else
         assert(false)
      end
   else
      return x
   end
end



-- Make formattable object from @a v.
-- @param v Format string
-- @return FormattableObject
-- @raise Error if @a v is invalid.
local function make_fomattable_object(v)
   if v == "" then return "" end

   local ret, err = parse_fmt(v)
   if err then
      print(v)
      error(err)
   end
   assert(type(ret) == "table")
   assert(#ret > 0)
   if #ret == 1 and type(ret[1]) ~= "table" then
      return tostring(ret[1])
   else
      return ret
   end
end



local function collect_i18n_resources(table, current_key, result)
   for k, v in pairs(table) do
      local key = current_key.."."..k
      if type(v) == "string" then
         result[key] = make_fomattable_object(v)
      elseif #v == 0 then
         collect_i18n_resources(v, key, result)
      else
         assert(type(v) == "table")
         for i, e in ipairs(v) do
            v[i] = make_fomattable_object(e)
         end
         result[key] = v
         result[key].__list = true
      end
   end
end



-- @param fmt Formattable object. It is a plain string (which means that the
--            string does not have interpolation) or a list of segments. Each
--            segment can be a plain string or complex string interpolation,
--            passed to `eval()`.
-- @param args The arguments passed to `eval()`
-- @return The formatted text
local function format(fmt, args)
   if type(fmt) == "string" then
      -- A plain string, just returns it.
      return fmt
   else
      -- A list of segments.
      local joined = ""
      for _, segment in ipairs(fmt) do
         local x = eval(segment, args)
         if type(x) == "table" and x.__handle then
            x = x:__tostring()
         end
         joined = joined..tostring(x)
      end
      return joined
   end
end




local I18N = {}



function I18N.get_optional(key, args)
   local fmt = storage[key]
   if fmt == nil then return nil end -- not found

   if type(fmt) == "table" and fmt.__list then -- Is it a `FormattableObjectList`?
      -- Choose one element of the list at random.
      fmt = fmt[rnd(#fmt) + 1]
   end

   return format(fmt, args)
end



function I18N.get_data_text_optional(key, args)
   local fmt = storage_for_data[key]
   if fmt == nil then return nil end -- not found

   if type(fmt) == "table" and fmt.__list then -- Is it a `FormattableObjectList`?
      -- Choose one element of the list at random.
      fmt = fmt[rnd(#fmt) + 1]
   end

   return format(fmt, args)
end



function I18N.get_list(key)
   local ret = storage[key]
   if ret == nil then return {} end
   if type(ret) == "table" then
      if ret.__list then
         return ret
      else
         -- error
         return {}
      end
   elseif type(ret) == "string" then
      return {ret}
   else
      -- error
      return {}
   end
end



-- for testing
function I18N.format(fmt, args)
   return format(make_fomattable_object(fmt), args)
end



I18N.interface = {}



function I18N.interface:add(data)
   collect_i18n_resources(data, _MOD_ID, storage)
end



function I18N.interface:add_data_text(prototype_id, data)
   for k, v in pairs(data) do
      local key = prototype_id.."#".._MOD_ID.."."..k
      collect_i18n_resources(v, key, storage_for_data)
   end
end



function I18N.interface:add_function(functions)
   for func_name, func in pairs(functions) do
      localize_functions[_MOD_ID.."."..func_name] = func
   end
end



return I18N
