local Data = {}


local DataRegistry = {}


local reserved_fields = {
   "id",
   "fqid",
   "proto_id",
   "index",
   "ext",
}

local xtype, p = prelude.xtype, prelude.p
local __debug__ = _ENV.__debug__




local Schema = {new = function(...) return {validate = function(x) return x end} end}



local function get_private_table(t)
   return getmetatable(t)
end



local function is_namespaced_id(id)
   return id:match("^[A-Za-z_0-9]+%.[A-Za-z_0-9]+$")
end



local function is_valid_id(id)
   if type(id) ~= "string" then
      return false
   end
   return id:match("^[A-Za-z_0-9]+$") or is_namespaced_id(id)
end



-- `id` must be a valid namespaced ID.
local function split_namespaced_id(id)
   return id:gmatch("(.+)%.(.+)")
end



local function get_current_mod_id()
   -- This global variable is defined by the system.
   return _ENV._MOD_ID
end



local function qualify_id(mod_id, data_id)
   return mod_id.."."..data_id
end



local function fully_qualify_id(proto_id, inst_id)
   return proto_id.."#"..inst_id
end



-- @tparam NonNamespacedPrototypeId proto_id
-- @tparam any ...
function DataRegistry:define_prototype(proto_id, ...)
   local self = get_private_table(self)

   if not is_valid_id(proto_id) then
      error("Invalid prototype ID: "..tostring(proto_id))
   end
   if is_namespaced_id(proto_id) then
      local mod_id, data_id = split_namespaced_id(proto_id)
      error("Use '"..data_id.."' instead of namespaced ID '"..mod_id.."'")
   end
   proto_id = qualify_id(get_current_mod_id(), proto_id)

   local schema, err = Schema.new(...)
   if err then
      error("Failed to define prototype '"..proto_id.."': "..err)
   end

   if self._prototypes[proto_id] then
      error("duplicate prototype definition: "..proto_id)
   end
   self._prototypes[proto_id] = schema

   self._instance_storages[proto_id] = {}
   self._by_integer_id_tables[proto_id] = {}
   self._by_index_tables[proto_id] = {}
end



-- @tparam NamespacedPrototypeId proto_id
-- @tparam [any] instances
-- @treturn Prototype
function DataRegistry:add(proto_id, instances)
   local self = get_private_table(self)

   if not is_valid_id(proto_id) then
      error("Invalid prototype ID: "..tostring(proto_id))
   end
   local prototype = self._prototypes[proto_id]
   if not prototype then
      error("Prototype '"..proto_id.."' not found")
   end
   if type(instances) ~= "table" then
      error("instances must be a table.")
   end

   for inst_id, instance_definition in pairs(instances) do
      if not is_valid_id(inst_id) then
         error("Invalid instance ID: "..tostring(inst_id))
      end
      if is_namespaced_id(inst_id) then
         local mod_id, data_id = split_namespaced_id(inst_id)
         error("Use '"..data_id.."' instead of namespaced ID '"..mod_id.."'")
      end
      inst_id = qualify_id(get_current_mod_id(), inst_id)
      local fqid = fully_qualify_id(proto_id, inst_id)

      local instance, err = prototype.validate(instance_definition)
      if err then
         error("Validation error in '"..fqid.."': "..err)
      end

      local instance_storage = self._instance_storages[proto_id]
      local by_index_table = self._by_index_tables[proto_id]
      local by_integer_id_table = self._by_integer_id_tables[proto_id]

      if instance_storage[inst_id] then
         error("duplicate instance definition: "..fqid)
      end

      for _, reserved_field in ipairs(reserved_fields) do
         if instance[reserved_field] then
            error(fqid..": '"..reserved_field.."' is a reserved field")
         end
      end

      instance.id = inst_id
      instance.fqid = fqid
      instance.proto_id = proto_id
      instance.ext = {}

      if instance.integer_id then
         if xtype(instance.integer_id) ~= "integer" then
            error(fqid..": 'integer_id' must be an integer")
         end
         by_integer_id_table[instance.integer_id] = instance
      end

      by_index_table[#by_index_table+1] = instance
      instance.index = #by_index_table

      instance_storage[inst_id] = instance

      if __debug__ then
         p(instance)
      end
   end
end



-- @tparam NamespacedPrototypeId proto_id
-- @tparam NamespacedInstanceId inst_id
function DataRegistry:get(proto_id, inst_id)
   local self = get_private_table(self)

   local instance_storage = self._instance_storages[proto_id]
   return instance_storage and instance_storage[inst_id]
end


-- @treturn DataRegistry
function Data.new_registry()
   local reg = {}
   local mt = {
      -- These fields are private. You have to access this metatable through
      -- `getmetatable()`, but the function is not exported to mod
      -- environments.
      _prototypes = {},
      _instance_storages = {},
      _by_integer_id_tables = {},
      _by_index_tables = {},
      __index = DataRegistry,
   }
   setmetatable(reg, mt)
   return reg, mt
end

return Data
