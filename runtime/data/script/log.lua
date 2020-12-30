local LOGGERS = {}

local function make_logger(mod_id)
   local Log = {}

   local enums = require("enums")
   local I18n = require("i18n")
   local internal = _ENV.native.Log

   Log.Level = enums.new_enum {
      ERROR = 5,
      WARN = 4,
      INFO = 3,
      DEBUG = 2,
      TRACE = 1,
   }

   --- Output log message with the given `level`.
   --- @tparam Level level Severity
   --- @tparam string fmt Format string
   function Log.log(level, fmt, ...)
      internal.log(level, mod_name, I18n.format(fmt, {...}))
   end

   --- Output log message (severity: `Level.error`)
   --- @tparam string fmt Format string
   function Log.error(fmt, ...)
      Log.log(Log.Level.ERROR, fmt, ...)
   end

   --- Output log message (severity: `Level.warn`)
   --- @tparam string fmt Format string
   function Log.warn(fmt, ...)
      Log.log(Log.Level.WARN, fmt, ...)
   end

   --- Output log message (severity: `Level.info`)
   --- @tparam string fmt Format string
   function Log.info(fmt, ...)
      Log.log(Log.Level.INFO, fmt, ...)
   end

   --- Output log message (severity: `Level.debug`)
   --- @tparam string fmt Format string
   function Log.debug(fmt, ...)
      Log.log(Log.Level.DEBUG, fmt, ...)
   end

   --- Output log message (severity: `Level.trace`)
   --- @tparam string fmt Format string
   function Log.trace(fmt, ...)
      Log.log(Log.Level.TRACE, fmt, ...)
   end

   --- Get log level
   --- @treturn Level level Severity
   function Log.level()
      return internal.level()
   end

   --- Set log level
   --- @tparam Level new_level Severity
   function Log.set_level(new_level)
      internal.set_level(new_level)
   end

   --- Check if `level` is enabled.
   --- @tparam Level level Severity to check
   --- @tparam boolean True if enabled
   function Log.is_enabled(level)
      return internal.level() <= level
   end

   return Log
end

local function get_logger(mod_id)
   local logger = LOGGERS[mod_id]
   if logger then
      return logger
   else
      logger = make_logger(mod_id)
      LOGGERS[mod_id] = logger
      return logger
   end
end

return get_logger
