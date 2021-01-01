local class, xtype = prelude.class, prelude.xtype

local utils = require("json5.utils")

local Printer = class("json5.Printer")

local D_QUOTE = string.byte('"')
local BACKSLASH = string.byte('\\')

function Printer:__init(opts)
   self._opts = opts
   self._indent_level = 0
end

function Printer:stringify(v)
   local ty = xtype(v)
   if ty == "nil" then
      return "null"
   elseif ty == "boolean" then
      return v and "true" or "false"
   elseif ty == "integer" then
      return tostring(v)
   elseif ty == "float" then
      if v ~= v then
         return "NaN"
      elseif v == math.huge then
         return "Infinity"
      elseif v == -math.huge then
         return "-Infinity"
      else
         return tostring(v)
      end
   elseif ty == "string" then
      return self:_quote(v)
   elseif ty == "table" then
      if #v == 0 then
         -- Lua `{}` is evaluated as JSON5 `{}`, not `[]`.
         if self._opts.prettify then
            return self:_object_prettified(v)
         else
            return self:_object(v)
         end
      else
         if self._opts.prettify then
            return self:_array_prettified(v)
         else
            return self:_array(v)
         end
      end
   else
      error(("invalid type '%s'"):format(ty))
   end
end

function Printer:_array(v)
   local items = ""
   for i, e in ipairs(v) do
      items = items..self:stringify(e)
      if self._opts.insert_trailing_comma or i ~= #v then
         items = items..","
      end
   end
   return "["..items.."]"
end

function Printer:_array_prettified(v)
   local items = ""
   items = items.."["..self:_br()
   self._indent_level = self._indent_level + 1
   for i, e in ipairs(v) do
      items = items..self:_indent()
      items = items..self:stringify(e)
      if self._opts.insert_trailing_comma or i ~= #v then
         items = items..","
      end
      items = items..self:_br()
   end
   self._indent_level = self._indent_level - 1
   items = items..self:_indent().."]"
   return items
end

function Printer:_object(v)
   local items = ""
   local size = utils.count_table(v)
   self:_process_object(v, function(i, k, v)
      items = items..self:_may_quote_key(k)
      items = items..":"
      items = items..self:stringify(v)
      if self._opts.insert_trailing_comma or i ~= size then
         items = items..","
      end
   end)
   return "{"..items.."}"
end

function Printer:_object_prettified(v)
   local items = ""
   items = items.."{"..self:_br()
   self._indent_level = self._indent_level + 1
   local size = utils.count_table(v)
   self:_process_object(v, function(i, k, v)
      items = items..self:_indent()
      items = items..self:_may_quote_key(k)
      items = items..": "
      items = items..self:stringify(v)
      if self._opts.insert_trailing_comma or i ~= size then
         items = items..","
      end
      items = items..self:_br()
   end)
   self._indent_level = self._indent_level - 1
   items = items..self:_indent().."}"
   return items
end

function Printer:_quote(s)
   local ret = ""
   local bytes = {s:byte(1, -1)}
   for _, c in ipairs(bytes) do
      if c == D_QUOTE or c == BACKSLASH then
         ret = ret.."\\"
      end
      ret = ret..string.char(c)
   end
   return '"'..ret..'"'
end

function Printer:_may_quote_key(k)
   if self._opts.unquote_key and k ~= "" and utils.is_ident(k) then
      return k
   else
      return self:_quote(k)
   end
end

function Printer:_indent()
   return string.rep(' ', self._opts.indent_width * self._indent_level)
end

function Printer:_br()
   if self._opts.line_ending == "lf" then
      return "\n"
   else
      return "\r\n"
   end
end

function Printer:_process_object(object, f)
   if self._opts.sort_by_key then
      local kv_pairs = {}
      for k, v in pairs(object) do
         kv_pairs[#kv_pairs + 1] = { k, v }
      end
      -- sort by key
      table.sort(kv_pairs, function(a, b) return a[1] < b[1] end)
      local i = 0
      for kv in pairs(kv_pairs) do
         f(i, kv[1], kv[2])
         i = i + 1
      end
   else
      local i = 0
      for k, v in pairs(object) do
         f(i, k, v)
         i = i + 1
      end
   end
end

return Printer
