local json5 = {}

local Parser = require("json5.parser")
local Printer = require("json5.printer")

--- Parses JSON5 text.
---
--- @tparam string source JSON5 text
--- @treturn[1] any Parsed object
--- @treturn[2] nil If failed
--- @treturn[2] string Error message
function json5.parse(source)
   local ok, result = pcall(function()
      local parser = Parser.new(source)
      return parser:parse()
   end)
   if ok then
      return result
   else
      return nil, result
   end
end

--- Stringify arbitary value as JSON5.
---
--- @tparam any value
--- @tparam[opt] table opts
--- @treturn string The stringified value
function json5.stringify(value, opts)
   opts = opts or {}
   if opts.prettify              == nil then opts.prettify              = false end
   if opts.indent_width          == nil then opts.indent_width          = 2     end
   if opts.insert_trailing_comma == nil then opts.insert_trailing_comma = false end
   if opts.unquote_key           == nil then opts.unquote_key           = false end
   if opts.sort_by_key           == nil then opts.sort_by_key           = false end
   if opts.line_ending           == nil then opts.line_ending           = "LF"  end

   local printer = Printer.new(opts)
   return printer:stringify(value)
end

return json5
