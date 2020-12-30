local prelude = _ENV.prelude
local xtype, p, fun = prelude.xtype, prelude.p, prelude.fun

local __debug__ = false

local data = {}

local PROTOTYPES = {}
local INSTANCES = {}
local BY_INTEGER_ID = {}
local BY_INDEX = {}
local RESOLVERS = {}

local RESERVED_FIELDS = {
   "id",
   "fqid",
   "prototype_id",
   "index",
}

local function is_valid_id(id)
   if type(id) ~= "string" then
      return false
   end
   return id:match("^[A-Za-z_0-9]+$") or is_namespaced_id(id)
end

local function is_namespaced_id(id)
   return id:match("^[A-Za-z_0-9]+%.[A-Za-z_0-9]+$")
end

-- `id` must be a valid namespaced ID.
local function split_namespaced_id(id)
   return id:gmatch("(.+)%.(.+)")
end

local function qualify_id(mod_id, data_id)
   return mod_id.."."..data_id
end

local function fully_qualify_id(proto_id, instance_id)
   return proto_id.."#"..instance_id
end

local function get_current_mod_id()
   -- This global variable is defined by the system.
   return _ENV._MOD_ID
end

local Schema = {new = function(...) return {validate = function(x) return x end} end}

--- Defines a new prototype
--- @tparam string prototype_id Non-namespaced data prototype ID
function data.define_prototype(prototype_id, ...)
   if not is_valid_id(prototype_id) then
      error("Invalid prototype ID: "..tostring(prototype_id))
   end
   if is_namespaced_id(prototype_id) then
      local mod_id, data_id = split_namespaced_id(prototype_id)
      error("Use '"..data_id.."' instead of namespaced ID '"..prototype_id.."'")
   end
   prototype_id = qualify_id(get_current_mod_id(), prototype_id)

   local schema, err = Schema.new(...)
   if err then
      error("Failed to define prototype '"..prototype_id.."': "..err)
   end

   if PROTOTYPES[prototype_id] then
      error("duplicate prototype definition: "..prototype_id)
   end
   PROTOTYPES[prototype_id] = schema

   INSTANCES[prototype_id] = {}
   BY_INTEGER_ID[prototype_id] = {}
   BY_INDEX[prototype_id] = {}
end

--- Adds data instances of `prototype_id`.
--- @tparam string prototype_id Data prototype ID
--- @tparam table instances Data instances
function data.add(prototype_id, instances)
   local prototype = PROTOTYPES[prototype_id]
   if not prototype then
      if not is_valid_id(prototype_id) then
         error("Invalid prototype ID: "..tostring(prototype_id))
      end
      if not is_namespaced_id(prototype_id) then
         error("Prototype ID must be namespaced: "..tostring(prototype_id))
      end
      error("Prototype '"..prototype_id.."' not found")
   end
   if type(instances) ~= "table" then
      error("instances must be a table.")
   end

   for instance_id, instance_definition in pairs(instances) do
      if not is_valid_id(instance_id) then
         error("Invalid instance ID: "..tostring(instance_id))
      end
      if is_namespaced_id(instance_id) then
         local mod_id, data_id = split_namespaced_id(instance_id)
         error("Use '"..data_id.."' instead of namespaced ID '"..instance_id.."'")
      end
      instance_id = qualify_id(get_current_mod_id(), instance_id)
      local fqid = fully_qualify_id(prototype_id, instance_id)

      local instance, err = prototype.validate(instance_definition)
      if err then
         error("Validation error in '"..fqid.."': "..err)
      end

      local instance_storage = INSTANCES[prototype_id]
      local by_index_table = BY_INDEX[prototype_id]
      local by_integer_id_table = BY_INTEGER_ID[prototype_id]

      if instance_storage[instance_id] then
         error("duplicate instance definition: "..fqid)
      end

      for _, reserved_field in ipairs(RESERVED_FIELDS) do
         if instance[reserved_field] then
            error(fqid..": '"..reserved_field.."' is a reserved field")
         end
      end

      instance.id = instance_id
      instance.fqid = fqid
      instance.prototype_id = prototype_id

      if instance.integer_id then
         if xtype(instance.integer_id) ~= "integer" then
            error(fqid..": 'integer_id' must be an integer")
         end
         by_integer_id_table[instance.integer_id] = instance
      end

      by_index_table[#by_index_table + 1] = instance
      instance.index = #by_index_table

      instance_storage[instance_id] = instance

      if __debug__ then
         p(instance)
      end
   end
end

--- Adds data resolvers of `prototype_id`.
--- @tparam string prototype_id Namespaced data prototype ID
--- @tparam table resolvers Data resolvers
function data.add_resolver(prototype_id, resolvers)
   -- TODO
end

--- Gets data instance.
--- @tparam string prototype_id Namespaced data prototype ID
--- @tparam string instance_id Namespaced data instance ID
--- @treturn any?
function data.get(prototype_id, instance_id)
   local instances = INSTANCES[prototype_id]
   return instances and instances[instance_id]
end

--- Returns iterator over a certain data instances.
--- @tparam string prototype_id Data prototype ID
--- @treturn iterator?
function data.instances(prototype_id)
   local instances = INSTANCES[prototype_id]
   return fun.iter(instances)
end

return data
