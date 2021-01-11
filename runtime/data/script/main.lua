--[==================================[
  | The main entry point in Lua side |
--]==================================]

local subcommand
__APP, __PROFILE_ID, subcommand = ...
prelude = require("prelude.init")
if not __APP then
   -- When this script is called with a nil app (no-GUI or headless mode),
   -- use `HeadlessApp` instance.
   __APP = require("headless_app").new()
   assert(__APP:is_headless())
end

do
   local _log = native.log.log
   function log_error(msg) _log(5, "core", msg) end
   function log_warn(msg)  _log(4, "core", msg) end
   function log_info(msg)  _log(3, "core", msg) end
   function log_debug(msg) _log(2, "core", msg) end
   function log_trace(msg) _log(1, "core", msg) end

   -- TODO: remove this
   function todo(module_name)
      if module_name then
         log_info(module_name..": NOT IMPLEMENTED YET!")
      else
         log_info("NOT IMPLEMENTED YET!")
      end
   end
end

do
   local show_loading_screen = require("loading_screen")
   local init_thread = require("init_thread")
   show_loading_screen(init_thread)
   assert(coroutine.status(init_thread) == "dead")
end

if subcommand == "run" then
   local main_loop = require("main_loop")
   local MainTitleMenu = require("ui.main_title_menu")
   main_loop(MainTitleMenu.new())
elseif subcommand == "repl" then
   local repl = require("repl")
   repl()
else
   error("Unknown subcommand: "..tostring(subcommand))
end
