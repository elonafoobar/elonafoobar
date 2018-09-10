local HCL = require "hclua"
local inspect = require "inspect"

local function shared_keys(a, b)
   local keys = {}

   for k, _ in pairs(a) do
      if b[k] ~= nil then
         keys[#keys+1] = k
      end
   end

   return keys
end

local function register_data(mod_name, datatype_mod_name, datatype_name, filepath, registry)
   if registry[datatype_mod_name] == nil or registry[datatype_mod_name][datatype_name] == nil then
      error("Datatype not registered: " .. datatype_mod_name .. "." .. datatype_name)
   end
   local parsed = HCL.parse_file(filepath)
   local data = parsed[datatype_name]

   -- TODO make msg a reserved keyword (_msg)
   if parsed.msg ~= nil then
      error(filepath .. ":" .. parsed.line .. ":" .. parsed.column .. ": " .. parsed.msg)
   end

   if data == nil then
      -- No data to load.
      return
   end

   if data[1] ~= nil then
      error("Datatype object was list, are there duplicate IDs?\nIDs that were duplicate: " ..
               inspect(shared_keys(data[1], data[2])))
   end

   local id_prefix = datatype_mod_name .. "." .. datatype_name .. ":"
   for key, value in pairs(data) do
      -- if validate(spec, value) then

      -- namespaced by mod declaring datatype and mod declaring data
      -- core.chara:core.putit
      local id = mod_name .. "." .. key
      local full_id = id_prefix .. id

      value._id = id
      value._full_id = full_id
      value._mod = mod_name

      local datatype_table = registry[datatype_mod_name][datatype_name]
      if not datatype_table[mod_name] then
         datatype_table[mod_name] = {}
      end
      if datatype_table[mod_name][key] ~= nil then
         error("Datatype already exists: " .. id)
      end

      datatype_table[mod_name][key] = value
      -- end
   end
end

return register_data
