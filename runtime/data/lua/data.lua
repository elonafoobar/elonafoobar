local data = {}
data.raw = {}
data.by_legacy = {}
data.types = {}

function data:define_type(name, validate)
   local instance_id = _ENV["_MOD_NAME"] .. "." .. name

   if self.types[instance_id] then
      error("duplicate type definition of " .. instance_id)
   end

   if not validate then
      validate = function() return true end
   end

   self.types[instance_id] = validate
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

      local instance_id = _ENV["_MOD_NAME"] .. "." .. name


      local validator = self.types[data_type]

      if not validator then
         error("unknown type " .. data_type)
      end

      local ok, err = pcall(validator, v)
      if not ok then
         error(data_type .. ":" .. instance_id .. " validation error: " .. err)
      end

      local dt = self.raw[data_type]

      if not dt then
         dt = {}
         self.raw[data_type] = dt
      end

      if dt[instance_id] then
         error("duplicate definition of " .. data_type .. ":" .. instance_id)
      end

      if v._id then
         error(data_type .. ":" .. instance_id .. ": _id is a reserved field")
      end

      dt[instance_id] = v
      v._id = instance_id

      if v.id and type(v.id) == "number" then
         local by_legacy = self.by_legacy[data_type]

         if not by_legacy then
            by_legacy = {}
            self.by_legacy[data_type] = by_legacy
         end

         by_legacy[v.id] = instance_id
      end
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
