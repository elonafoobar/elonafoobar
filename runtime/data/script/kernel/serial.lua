local Handle = require "handle"
local serpent = require "serpent"
local inspect = require "inspect"

local Serial = {}

local function resolve_handles(data)
   for key, value in pairs(data) do
      if type(value) == "table" then
         if value.__handle then
            -- Set the handle's metatable.
            setmetatable(value, Handle.get_metatable(value.__kind))
         else
            resolve_handles(value)
         end
      end
   end
end

-- Serial.save = serpent.dump
function Serial.save(data)
   for _, v in pairs(data) do
      if type(v) ~= "table" or not v.__handle then
         print("Save: " .. inspect(data))
      end
      break
   end

   local dump = serpent.dump(data)
   return dump
end

function Serial.load(dump)
   local ok, data = serpent.load(dump)
   if not ok then
      error("Mod data load error: " .. data, 2)
   end
   resolve_handles(data)

   for _, v in pairs(data) do
      if type(v) ~= "table" or not v.__handle then
         print("Load: " .. inspect(data))
      end
      break
   end

   return data
end

return Serial
