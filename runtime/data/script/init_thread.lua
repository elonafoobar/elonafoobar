--[=================================[
  | The main initialization process |
  | It is called by loading_screen. |
--]=================================]

return coroutine.create(function()
   local native = _ENV.native
   local Fs = native.Fs
   local Mods = native.Mods

   local Api = require("api")
   local get_logger = require("log")

   local resolved_mod_list
   do
      local mods = Mods.new()
      coroutine.yield("Resolve mod versions")
      mods:resolve_versions()

      coroutine.yield("Install mods")
      mods:install()

      coroutine.yield("Scan metadata")
      mods:scan_metadata()

      resolved_mod_list = mods:get_resolved_mod_list()
      mods = nil
   end

   do
      log_info("Load core")

      local core = {}
      core.Audio = require("audio")
      core.Config = require("config")
      core.Data = require("data")
      core.Enums = require("enums")
      core.Env = require("env")
      core.Graphics = require("graphics")
      core.I18n = require("i18n")
      core.UI = require("ui")

      -- core.Inventory = require("inventory")
      -- core.Item = require("item")
      -- core.Message = require("message")
      -- core.Net = require("net")
      -- core.Random = require("random")
      -- core.StoryQuest = require("story_quest")
      -- core.Trait = require("trait")

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

      env.ELONA = {}
      env.ELONA.require = function(module_path)
         if module_path == "core.Log" then
            return get_logger(mod_id)
         else
            return Api.require(module_path)
         end
      end
      env.require = function(file_path)
         log_trace(mod_id..": require('"..file_path.."')")
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
   -- for _, mod in ipairs(resolved_mod_list) do
   --    local env = mod[3]
   --    config_schema(env)
   -- end

   coroutine.yield("Load config")
   -- config()

   coroutine.yield("Run init.lua")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)
      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "init.lua")
      assert(loadfile(path, "t", env))()
   end

   coroutine.yield("Run data.lua")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)

      _ENV._MOD_ID = mod_id

      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "data.lua")
      assert(loadfile(path, "t", env))()

      _ENV._MOD_ID = nil
   end

   coroutine.yield("Run i18n.lua")
   for _, mod in ipairs(resolved_mod_list) do
      local mod_id, version, env = table.unpack(mod)

      _ENV._MOD_ID = mod_id

      -- TODO
      -- * Move it to native side
      -- * Windows file path is UTF-16, not UTF-8.
      local path = Fs.get_lua_full_path(mod_id, version, "locale/ja.lua") -- TODO
      assert(loadfile(path, "t", env))()

      _ENV._MOD_ID = nil
   end

   return 'Done'
end)
