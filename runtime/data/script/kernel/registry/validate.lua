local inspect = require 'inspect'



local function is_valid_prototype_name(name)
   -- abc.efg
   return name:match("[a-zA-Z0-9_]+%.[a-zA-Z0-9_]+")
end



local is_valid_data_name = is_valid_prototype_name
local visit_properties



local function is_list(x)
   if type(x) ~= "table" then
      return false
   end
   local len = 0
   for _, _ in pairs(x) do
      len = len + 1
   end
   for _, _ in ipairs(x) do
      len = len - 1
   end
   return len == 0
end



local function is_object(x)
   if type(x) ~= "table" then
      return false
   end
   return not is_list(x)
end



local function table_checker(p, data)
   if data == nil then
      local default = p.default
      if default == nil then
         error("invalid data")
      end
      if type(default) ~= "table" then
         error("invalid prototoype")
      end
      return default
   end

   if type(data) ~= "table" then
      error("invalid data:" .. type(data) .. ":" .. inspect(p))
   end

   local properties = p.properties
   visit_properties(properties, data)
end



local function list_checker(p, data)
   if not is_list(data) then
      error("invalid data")
   end
end



local function object_checker(p, data)
      if not is_object(data) then
         error("invalid data")
      end
end



local function string_checker(p, data)
   if data == nil then
      local default = p.default
      if default == nil then
         error("invalid data")
      end
      if type(default) ~= "string" then
         error("invalid prototoype")
      end
      return default
   end

   if type(data) ~= "string" then
      error("invalid data:" .. type(data))
   end
end



local function number_checker(p, data)
   if data == nil then
      local default = p.default
      if default == nil then
         error("invalid data")
      end
      if type(default) ~= "number" then
         error("invalid prototoype")
      end
      return default
   end

   if type(data) ~= "number" then
      error("invalid data:" .. type(data))
   end
end



local function boolean_checker(p, data)
   if data == nil then
      local default = p.default
      if default == nil then
         error("invalid data")
      end
      if type(default) ~= "boolean" then
         error("invalid prototoype:" .. type(default) .. ":" .. default)
      end
      return default
   end

   if type(data) ~= "boolean" then
      error("invalid data:" .. type(data) .. ":" .. data)
   end
end



local function integer_checker(p, data)
   if data == nil then
      local default = p.default
      if default == nil then
         error("invalid data")
      end
      if type(default) ~= "number" or math.type(default) ~= "integer" then
         error("invalid prototoype")
      end
      return default
   end

   if type(data) ~= "number" or math.type(data) ~= "integer" then
      error("invalid data:" .. type(data))
   end
end



local function float_checker(p, data)
   if data == nil then
      local default = p.default
      if default == nil then
         error("invalid data")
      end
      if type(default) ~= "number" or math.type(default) ~= "float" then
         error("invalid prototoype")
      end
      return default
   end

   if type(data) ~= "number" or math.type(data) ~= "float" then
      error("invalid data:" .. type(data))
   end
end



local function function_checker(p, data)
   error("TODO")
end



local function any_checker(p, data)
   if data == nil then
      error("invalid data")
   end
end



local function dispatch_to_checker(type_name, p, data)
   if type_name == "table" then
      return table_checker(p, data)
   elseif type_name == "list" then
      return list_checker(p, data)
   elseif type_name == "object" then
      return object_checker(p, data)
   elseif type_name == "string" then
      return string_checker(p, data)
   elseif type_name == "number" then
      return number_checker(p, data)
   elseif type_name == "boolean" then
      return boolean_checker(p, data)
   elseif type_name == "integer" then
      return integer_checker(p, data)
   elseif type_name == "float" then
      return float_checker(p, data)
   elseif type_name == "function" then
      return function_checker(p, data)
   elseif type_name == "any" then
      return any_checker(p, data)
   else
      if not is_valid_prototype_name(type_name) then
         error("invalid prototype:" .. type_name)
      end
      if type(data) ~= "string" then
         error("invalid data")
      end
      if not is_valid_data_name(data) then
         error("invalid data:" .. type_name .. ":" .. data)
      end
   end
end



local function visit_item(key, p, data)
   local x = data[key]
   local t = type(p)
   if t == "table" then
      type_ = p.type
      if type(type_) ~= "string" then
         error("invalid prototype:" .. type(type_) .. ":" .. key)
      end
      local new = dispatch_to_checker(type_, p, x)
      if new then
         data[key] = new
      end
   elseif t == "string" then
      local new = dispatch_to_checker(p, { type=p }, x)
      if new then
         data[key] = new
      end
   elseif t == "number" then
      if not x then
         data[key] = p
      elseif math.type(p) == "integer" then
         if math.type(x) ~= "integer" then
            error("invalid data")
         end
      elseif math.type(p) == "float" then
         if math.type(x) ~= "float" then
            error("invalid data")
         end
      end
   elseif t == "boolean" then
      if not x then
         data[key] = p
      elseif type(x) ~= "boolean" then
         error("invalid data")
      end
   elseif t == "function" then
      error("TODO")
   else
      -- nil, thread, or userdata
      error("invalid prototype")
   end
end



visit_properties = function(p, data)
   if type(p) ~= "table" then
      error("invalid prototype")
   end

   for k, v in pairs(p) do
      ok, ret = pcall(visit_item, k, v, data)
      if not ok then
         error(ret .. " in " .. k)
      end
   end
end



local function validate(prototype, data)
   visit_properties(prototype, data)
end



return validate
