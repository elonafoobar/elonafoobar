local Log = {}

local Enums = require("core.enums")
local internal = _ENV.native.__Log -- TODO
local format = _ENV.kernel.I18N.format

Log.Level = Enums.new_enum {
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
   -- TODO: not implemented yet
   -- local mod_name = get_caller_mod_name()
   local mod_name = "core"
   internal.log(level, mod_name, format(fmt, {...}))
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
   assert(Log.Level:is_valid_value(new_level), "Log.set_level: invalid log level")
   internal.set_level(new_level)
end

--- Check if `level` is enabled.
--- @tparam Level level Severity to check
--- @tparam boolean True if enabled
function Log.is_enabled(level)
   return internal.level() <= level
end

--- Set whether log should be output to stderr.
--- @tparam boolean should_output Whether log should be output to stderr
function Log.output_stderr(should_output)
   internal.output_stderr(should_output)
end

return Log
