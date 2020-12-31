--[==================================[
  | The main entry point in Lua side |
--]==================================]

__APP, __PROFILE_ID = ...
prelude = require("prelude.init")

do
   local _log = native.Log.log
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

do
   local main_loop = require("main_loop")
   local MainTitleMenu = require("ui.main_title_menu")
   main_loop(MainTitleMenu.new())
end
