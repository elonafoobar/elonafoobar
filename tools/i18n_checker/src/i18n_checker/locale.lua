local hclua = require "hclua"
local inspect = require "inspect"

local sfind = string.find
local sgsub = string.gsub

local locale = {}

local function is_enum_key(key)
   return sfind(key, "%._%d+")
end

local function strip_enum_index(key)
   return sgsub(key, "%._%d+.*", "")
end

local function visit_object(state, current_key, hcl, filename)
   for key, value in pairs(hcl) do
      local next_key = current_key .. "." .. key
      if type(value) == "table" then
         visit_object(state, next_key, value, filename)
      elseif type(value) == "string" then
         local used = false
         if is_enum_key(next_key) then
            -- ignore usage statistics for individual enum keys
            used = true
            local base = strip_enum_index(next_key)
            state[base] = {key = base, used = false, filename = filename}
         end
         state[next_key] = {key = next_key, text = value, used = used, filename = filename}
      else
         error("Unknown type encountered: " .. type(value))
      end
   end
end

function locale.make_table(source)
   local state = {}
   local parsed = hclua.parse(source.text)

   visit_object(state, "core", parsed, source.filename)

   return state
end

return locale
