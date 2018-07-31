local Handle = require "handle"
local serpent = require "serpent"

local inspect = require "inspect"

local Serial = {}

local function resolve_handles(data)
   for key, value in pairs(data) do
      if type(value) == "table" then
         if value.__handle then
            -- Set the handle's metatable.
            setmetatable(value, Handle.get_metatable(value.kind))
         else
            resolve_handles(value)
         end
      end
   end
end

Serial.save = serpent.dump

function Serial.load(raw_data)
   local ok, data = serpent.load(raw_data)
   if not ok then
      error("Mod data load error: " .. data, 2)
   end
   resolve_handles(data)
   return data
end

return Serial
