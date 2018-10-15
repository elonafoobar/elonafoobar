local data = {}
data.raw = {}
data.types = {}

function data:define_type(name, validate)
   local full_name = _ENV["_MOD_NAME"] .. "." .. name

   if self.types[full_name] then
      error("duplicate type definition of " .. full_name)
   end

   if not validate then
      validate = function() return true end
   end

   self.types[full_name] = validate
end

function data:add_multi(data_type, array)
   for _, v in pairs(array) do
      v.type = data_type
   end
   self:add(array)
end

function data:add(array)
   if type(array) ~= "table" then
      error("not table")
   end

   for _, v in pairs(array) do
      if type(v) ~= "table" then
         error("not array entry")
      end

      local name = v.name
      local data_type = v.type

      if not name or not data_type then
         error("missing name or type")
      end

      local full_name = _ENV["_MOD_NAME"] .. "." .. name

      if not self.types[data_type] then
         error("unknown type " .. data_type)
      end

      local dt = self.raw[data_type]

      if not dt then
         dt = {}
         self.raw[data_type] = dt
      end

      dt[full_name] = v
   end
end

local function dump()
   for typename, t in pairs(data.raw) do
      local count = 0
      for k, _ in pairs(t) do
         count = count + 1
      end
      print("--- " .. typename .. ": \n   " .. count .. " items")
   end
end

return data
