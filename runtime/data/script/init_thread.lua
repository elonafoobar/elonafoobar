--[=================================[
  | The main initialization process |
  | It is called by loading_screen. |
--]=================================]

return coroutine.create(function()
   local native = _ENV.native
   local Fs = native.Fs
   local Mods = native.Mods

   local Api = require("api")
   local Config = require("config")
   local get_logger = require("log")

   local resolved_mod_list
   do
      local mods = Mods.new()
      coroutine.yield("Resolve mod versions")
      mods:resolve_versions("default")

      coroutine.yield("Install mods")
      mods:install()

      coroutine.yield("Scan metadata")
      mods:scan_metadata()

      resolved_mod_list = mods:get_resolved_mod_list()
      mods = nil
   end

   do
      log_info("Load core")

      local core = require("core_api")

      local Api = require("api")
      for k, v in pairs(core) do
         Api.register("core."..k, v)
      end
   end

   coroutine.yield("Create mod environments")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version = table.unpack(mod)
      local chunk_cache = {}
      local env = {}

      env.require = function(module_path)
         if module_path == "core.Log" then
            return get_logger(mod_id)
         else
            return Api.require(module_path)
         end
      end
      env.require_relative = function(file_path)
         log_trace(mod_id..": require_relative('"..file_path.."')")
         local path = Fs.resolve_relative_path(mod_id, version, file_path)
         local cache = chunk_cache[path]
         if cache ~= nil then
            return cache
         end
         -- TODO
         -- * Move it to native side
         -- * Windows file path is UTF-16, not UTF-8.
         local require_result = assert(loadfile(path, "t", env))()
         if require_result == nil then
            require_result = true
         end
         chunk_cache[path] = require_result
         return require_result
      end
      for k, v in pairs(prelude) do
         env[k] = v
      end

      mod[3] = env
   end

   coroutine.yield("Load config schema")
   --[[
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version = table.unpack(mod)
      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "config-schema.lua")
      local file = io.open(path)
      local schema_file_content = file:read("a")
      Config.load_schema(schema_file_content, path, mod_id)
      file:close()
      file = nil
   end
   --]]

   coroutine.yield("Load config")
   --[[
   do
      local path = Fs.get_config_file_path()
      local file = io.open(path)
      local config_file_content = file:read("a")
      Config.load_options(config_file_content, path)
      file:close()
      file = nil
   end
   --]]

   coroutine.yield("Run init.lua")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)
      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "init.lua")
      if Fs.exists(path) then
         log_info(("Run %s-%s/init.lua"):format(mod_id, version))
         local init_result = assert(loadfile(path, "t", env))()
         if type(init_result) == "table" then
            if mod_id == "core" then
               for k, v in pairs(init_result) do
                  Api.merge_core_module(mod_id.."."..k, v)
               end
            else
               for k, v in pairs(init_result) do
                  Api.register(mod_id.."."..k, v)
               end
            end
         end
      end
   end

   coroutine.yield("Run data.lua")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)

      _ENV._MOD_ID = mod_id

      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "data.lua")
      if Fs.exists(path) then
         log_info(("Run %s-%s/data.lua"):format(mod_id, version))
         assert(loadfile(path, "t", env))()
      end

      _ENV._MOD_ID = nil
   end

   coroutine.yield("Run data-update.lua")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)

      _ENV._MOD_ID = mod_id

      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "data-update.lua")
      if Fs.exists(path) then
         log_info(("Run %s-%s/data-update.lua"):format(mod_id, version))
         assert(loadfile(path, "t", env))()
      end

      _ENV._MOD_ID = nil
   end

   coroutine.yield("Run i18n.lua")
   local lang = Config.get("core.language.language")
   local i18n = require("i18n")
   i18n.__INTERNAL_API_inject_current_language(lang)
   i18n.__INTERNAL_API_inject_current_language = nil
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)

      _ENV._MOD_ID = mod_id

      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "locale/"..lang..".lua") -- TODO
      if Fs.exists(path) then
         log_info(("Run %s-%s/locale/%s.lua"):format(mod_id, version, lang)) -- TODO
         assert(loadfile(path, "t", env))()
      end

      _ENV._MOD_ID = nil
   end

   do
      local data = require("data")
      local event = require("event")
      event.__INTERNAL_API_remove_unknown_events(data.instances("core.event"):tomap())
      event.__INTERNAL_API_remove_unknown_events = nil
   end

   coroutine.yield("Load key bindings")
   do
      -- TODO
   end

   return 'Done'
end)
