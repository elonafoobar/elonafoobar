local Registry = {}



local validate = require 'registry.validate'
local compile = require 'registry.compile'



local function add_prefix_if_needed(name, mod_name)
   if name:match("%.") then
      return name
   else
      return mod_name .. "." .. name
   end
end



function Registry.new()
   local instance = {
      _prototypes = {},
      _data = {},
      _by_legacy = {},
   }
   return setmetatable(instance, { __index = Registry })
end



local function define_prototype(r, name, def)
   if r._prototypes[name] then
      error("prototype '" .. name .. "' has already been defined.")
   end
   r._prototypes[name] = def
   r._data[name] = {}
end



local function define_extension_prototype(r, name, def, mod_name)
   def._base = add_prefix_if_needed(def._base, mod_name)
   if not r._prototypes[def._base] then
      error("base prototype '" .. def._base .. "' does not exist")
   end

   if r._prototypes[name] then
      error("extension prototype '" .. name .. "' has already been defined.")
   end
   r._prototypes[name] = def
end



local function define_data(r, prototype_name, data_name, def)
   local proto = r._prototypes[prototype_name]
   if not proto then
      error("prototype '" .. prototype_name .. "' does not exist")
   end
   def._prototype = prototype_name

   def._id = data_name
   def._fully_qualified_id = prototype_name .. "#" .. data_name

   validate(proto, def)
   if r._data[prototype_name][data_name] then
      error("data '" .. prototype_name .. "#" .. data_name .. "' has already been defined.")
   end
   r._data[prototype_name][data_name] = def

   if def.legacy_id then
      local by_legacy = r._by_legacy[prototype_name]

      if not by_legacy then
         by_legacy = {}
         r._by_legacy[prototype_name] = by_legacy
      end

      by_legacy[def.legacy_id] = data_name
   end
end



local function define_extension(prototype_name, data_name, def, mod_name)
   local proto = r._prototypes[prototype_name]
   if not proto then
      error("prototype '" .. prototype_name .. "' does not exist")
   end
   def._prototype = prototype_name

   local base_proto_name = proto._base
   if not r._prototypes[base_proto_name] then
      error("prototype '" .. base_proto_name .. "' does not exist")
   end

   def._base = add_prefix_if_needed(def._base, mod_name)
   local base_data_name = def._base
   local base_data = r._data[base_proto_name][base_data_name]
   if not base_data then
      error("base data '" .. base_proto_name .. "#" .. base_data_name .. "' does not exist")
   end

   if not base_data._extensions then
      base_data._extensions = { [prototype_name] = {} }
   elseif not base_data._extensions[prototype_name] then
      base_data._extensions[prototype_name] = {}
   end

   def._id = data_name
   def._fully_qualified_id = prototype_name .. "#" .. base_data_name .. "-" .. data_name

   validate(proto, def)
   if base_data._extensions[prototype_name][data_name] then
      error("extension '" .. prototype_name .. "#" .. data_name .. "' has already been defined.")
   end
   base_data._extensions[prototype_name][data_name] = def
end



function Registry:get_extension(extension_prototype_name, data_name, extension_name)
   local prototype_name = self._prototypes[extension_prototype_name]._base
   return self._data[prototype_name][data_name]._extensions[extension_prototype_name][extension_name]
end



local function load_prototype_files_base(mod_name, filenames, define, safe_dofile)
   for _, filename in ipairs(filenames) do
      local table = safe_dofile(filename)
      for name, def in pairs(table) do
         name = add_prefix_if_needed(name, mod_name)
         define(name, def)
      end
   end
end



local function load_data_files_base(mod_name, filenames, define, safe_dofile)
   for _, filename in ipairs(filenames) do
      local table = safe_dofile(filename)
      for prototype_name, data_table in pairs(table) do
         prototype_name = add_prefix_if_needed(prototype_name, mod_name)
         for name, def in pairs(data_table) do
            name = add_prefix_if_needed(name, mod_name)
            define(prototype_name, name, def)
         end
      end
   end
end



-- internal
function Registry._compile(mod_name, in_filename, out_filename, is_prototype)
   local out = io.open(out_filename, "w")
   compile(in_filename, out, is_prototype)
   out:close()
end



-- internal
function Registry:_load_prototype_files(mod_name, files, safe_dofile)
   load_prototype_files_base(
      mod_name,
      files,
      function(name, def)
         define_prototype(self, name, def)
      end,
      safe_dofile)
end



-- internal
function Registry:_load_extension_prototype_files(mod_name, files, safe_dofile)
   load_prototype_files_base(
      mod_name,
      files,
      function(name, def)
         define_extension_prototype(self, name, def, mod_name)
      end,
      safe_dofile)
end



-- internal
function Registry:_load_data_files(mod_name, files, safe_dofile)
   load_data_files_base(
      mod_name,
      files,
      function(prototype_name, name, def)
         define_data(self, prototype_name, name, def)
      end,
      safe_dofile)
end



-- internal
function Registry:_load_extension_files(mod_name, files, safe_dofile)
   load_data_files_base(
      mod_name,
      files,
      function(prototype_name, name, def)
         define_extension(self, prototype_name, name, def, mod_name)
      end,
      safe_dofile)
end



return Registry
