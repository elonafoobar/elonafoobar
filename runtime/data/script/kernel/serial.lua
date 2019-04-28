local Handle = require "handle"
local serpent = require "serpent"
local inspect = require "inspect"

local Serial = {}

local function resolve_handles(data, seen)
   for key, value in pairs(data) do
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
end

Serial.save = serpent.dump

function Serial.load(dump)
   local ok, data = serpent.load(dump)
   if not ok then
      error("Mod data load error: " .. data, 2)
   end
   resolve_handles(data, {})
   return data
end

return Serial
