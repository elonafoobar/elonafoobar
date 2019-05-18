local utils = require "i18n_checker.utils"
local inspect = require "inspect"

local format = {}

local color_support = not utils.is_windows or os.getenv("ANSICON")

local function plural(number)
   return (number == 1) and "" or "s"
end

local color_codes = {
   reset = 0,
   bright = 1,
   red = 31,
   green = 32,
   cyan = 36
}

local function encode_color(c)
   return "\27[" .. tostring(color_codes[c]) .. "m"
end

local function colorize(str, ...)
   str = str .. encode_color("reset")

   for _, color in ipairs({...}) do
      str = encode_color(color) .. str
   end

   return encode_color("reset") .. str
end

local function format_color(str, color, ...)
   return color and colorize(str, ...) or str
end

local function format_number(number, color)
   return format_color(tostring(number), color, "bright", (number > 0) and "red" or "reset")
end

local function format_message(event, color)
   return format_color(event.msg, color, "bright", "reset")
      .. format_color(" (" .. utils.escape(event.key) .. ") ", "cyan", "bright", "cyan")
end

local function count_warnings_errors(events)
   local warnings, errors = 0, 0

   for _, event in ipairs(events) do
      if event.kind == "error" then
         errors = errors + 1
      else
         warnings = warnings + 1
      end
   end

   return warnings, errors
end

local function format_file_report_header(report, file_name, opts)
   local label = "Checking " .. file_name
   local status

   if report.fatal then
      status = format_color("error", opts.color, "bright")
   elseif #report == 0 then
      status = format_color("OK", opts.color, "bright", "green")
   else
      local warnings, errors = count_warnings_errors(report)

      if warnings > 0 then
         status = format_color(tostring(warnings).." warning"..plural(warnings), opts.color, "bright", "red")
      end

      if errors > 0 then
         status = status and (status.." / ") or ""
         status = status..(format_color(tostring(errors).." error"..plural(errors), opts.color, "bright", "red"))
      end
   end

   return label .. (" "):rep(math.max(50 - #label, 1)) .. status
end

local function format_location(file, location, opts)
   local res = ("%s:%d:%d"):format(file, location.line, location.column)

   if opts.ranges then
      res = ("%s-%d"):format(res, location.end_column)
   end

   return res
end

local function format_event(file_name, event, opts)
   local message = format_message(event, opts.color)

   return format_location(file_name, event, opts) .. ": " .. message
end

local function format_file_report(report, file_name, opts)
   local buf = {format_file_report_header(report, file_name, opts)}

   if #report > 0 then
      table.insert(buf, "")

      for _, event in ipairs(report) do
         table.insert(buf, "    " .. format_event(file_name, event, opts))
      end

      table.insert(buf, "")
   end

   return table.concat(buf, "\n")
end

function format.format(report)
   local opts = {color = true, quiet = 1}
   local buf = {}

   if opts.quiet <= 2 then
      for _, file_report in ipairs(report) do
         if opts.quiet == 0 or #file_report.new_report > 0 then
            table.insert(buf, (opts.quiet == 2 and format_file_report_header or format_file_report) (
               file_report.new_report, file_report.abs_path, opts))
         end
      end

      if #buf > 0 and buf[#buf]:sub(-1) ~= "\n" then
         table.insert(buf, "")
      end
   end

   local total = ("Total: %s warning%s / %s error%s in %d file%s\n"):format(
      format_number(report.warnings, opts.color), plural(report.warnings),
      format_number(report.errors, opts.color), plural(report.errors),
      #report, plural(#report))

   table.insert(buf, total)
   return table.concat(buf, "\n")
end

return format
