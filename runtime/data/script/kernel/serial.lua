local Handle = require("handle")
local serpent = require("serpent")

local Serial = {}

local resolve_handles

local function resolve_handle(value, seen)
   if type(value) == "table" and not seen[value] then
      if value.__handle then
         -- Set the handle's metatable.
         setmetatable(value, Handle.get_metatable(value.__kind))
      else
         -- Avoid recursive tables.
         seen[value] = true
         resolve_handles(value, seen)
      end
   end
end

-- Does not mutate `value`.
local function remove_volatile_data(value)
   if type(value) ~= "table" then
      return value
   end

   -- For table, remove volatile data.
   local result = {}
   for k, v in pairs(value) do
      if type(k) == "string" and k:sub(1, 1) == "_" then
         -- It's a private field, skipping.
      else
         -- This rule is only applied to top-level fields because we have to
         -- save Handle object with its private fields such as `__index`.
         result[k] = v
      end
   end
   return result
end

resolve_handles = function(data, seen)
   for key, value in pairs(data) do
      resolve_handle(value, seen)
   end
end

Serial.save = function(s)
   s = remove_volatile_data(s)
   local dump = serpent.dump(s)
   return dump
end

function Serial.load(dump)
   local ok, data = serpent.load(dump)
   if not ok then
      error("Mod data load error: " .. data, 2)
   end
   if type(data) == "table" then
      if data.__handle then
         resolve_handle(data, {})
      else
         resolve_handles(data, {})
      end
   end
   return data
end

return Serial
