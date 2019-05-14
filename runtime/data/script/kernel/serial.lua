local Handle = require "handle"
local serpent = require "serpent"
local inspect = require "inspect"

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

resolve_handles = function(data, seen)
   for key, value in pairs(data) do
      resolve_handle(value, seen)
   end
end

Serial.save = function(s)
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
