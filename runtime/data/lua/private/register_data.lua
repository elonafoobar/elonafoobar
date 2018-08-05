local HCL = require "hclua"

local function register_data(mod_name, datatype_name, filepath, registry)
   if registry[mod_name] == nil or registry[mod_name][datatype_name] == nil then
      error("Datatype not registered: " .. mod_name .. "." .. datatype_name)
   end
   local parsed = HCL.parse_file(filepath)
   local data = parsed[datatype_name]

   -- TODO make msg a reserved keyword (_msg)
   if parsed.msg ~= nil then
      error(filepath .. ":" .. parsed.line .. ":" .. parsed.column .. ": " .. parsed.msg)
   end

   if data == nil then
      error(filepath .. ": No data found for datatype " .. datatype_name)
   end

   if data[1] ~= nil then
      error("Datatype object was list, are there duplicate IDs?")
   end

   for key, value in pairs(data) do
      -- if validate(spec, value) then
      value._id = key
      value._mod = mod_name
      registry[mod_name][datatype_name][key] = value
      -- end
   end
end

return register_data
