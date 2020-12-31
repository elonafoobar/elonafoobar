local class = prelude.class

local utils = require("json5.utils")

local Lexer = class("json5.Lexer")

function Lexer:__init(source)
   self._source = source
   self._pos = 1
end

function Lexer:scan()
   self:_skip_whitespaces_and_comments()
   if self:_eof() then
      return "EOF"
   end
   return self:_scan_internal()
end

function Lexer:_skip_whitespaces_and_comments()
   if self:_eof() then
      return
   end

   while true do
      local c = self:_peek()
      if c == '/' then
         self:_get()
         if self:_eof() then
            error(self:_invalid_char("'//' or '/*'"))
         end

         local k = self:_peek()
         if k == '/' then -- '//', single line comment
            self:_get()
            while not self:_eof() do
               local c = self:_get()
               if c == '\r' then
                  if not self:_eof() and self:_peek() == '\n' then
                     self:_get()
                  end
                  break
               elseif c == '\n' then
                  break
               end
            end
         elseif k == '*' then -- '/*' multi-line comment
            self:_get()
            local previos_char_is_asterisk = false
            while true do
               if self:_eof() then
                  error(self:_invalid_char("'*/'"))
               end

               local c = self:_get()
               if c == '*' then
                  previos_char_is_asterisk = true
               elseif c == '/' then
                  if previos_char_is_asterisk then
                     break
                  end
               else
                  previos_char_is_asterisk = false
               end
            end
         else
            error(self:_invalid_char("'//' or '/*'"))
         end
      elseif c == ' ' or c == '\t' or c == '\r' or c == '\n' then
         self:_get()
      else
         return
      end
   end
end

function Lexer:_scan_internal()
   local c = self:_peek()
   if c == '[' then
      self:_get()
      return '['
   elseif c == ']' then
      self:_get()
      return ']'
   elseif c == '{' then
      self:_get()
      return '{'
   elseif c == '}' then
      self:_get()
      return '}'
   elseif c == ':' then
      self:_get()
      return ':'
   elseif c == ',' then
      self:_get()
      return ','
   elseif c== '\'' or c == '"' then
      return self:_scan_string()
   else
      return self:_scan_numeric_or_identifier()
   end
end

function Lexer:_scan_string()
   local s = ""
   local q = self:_get() -- ' or "
   while true do
      if self:_eof() then
         error(self:_invalid_char(q == '"' and "'\"'" or "'"))
      end

      local c = self:_get()
      if c == q then
         break
      elseif c == '\r' or c == '\n' then
         local br
         if not self:_eof() and self:_peek() == '\n' then
            br = "\\r\\n"
         elseif c == '\r' then
            br = "\\r"
         else
            br = "\\n"
         end
         error(("raw line break cannot be included in string literals, use '%s'"):format(br))
      elseif c == '\\' then
         s = s..self:_scan_escape_sequence()
      else
         s = s..c
      end
   end
   return "string", s
end

-- Escape Sequence Table
-- +----+-----------------+--------+
-- | \' | apostrophe      | U+0027 |
-- | \" | quotation mark  | U+0022 |
-- | \\ | reverse solidus | U+005C |
-- | \b | backspace       | U+0008 |
-- | \f | form feed       | U+000C |
-- | \n | line feed       | U+000A |
-- | \r | carriage return | U+000D |
-- | \t | horizontal tab  | U+0009 |
-- | \v | vertical tab    | U+000B |
-- | \0 | null            | U+0000 |
-- +----+-----------------+--------+
function Lexer:_scan_escape_sequence()
   if self:_eof() then
      error(self:_invalid_char("escape sequence"))
   end

   local c = self:_get()
   if c == '\'' then return "'"
   elseif c == '"' then return "\""
   elseif c == '\\' then return "\\"
   elseif c == 'b' then return "\b"
   elseif c == 'f' then return "\f"
   elseif c == 'n' then return "\n"
   elseif c == 'r' then return "\r"
   elseif c == 't' then return "\t"
   elseif c == 'v' then return "\v"
   elseif c == '0' then
      if utils.is_digit(self:_peek()) then
         error("C-style octal character literal is not allowed except for '\\0'. Use prefix \\x or \\u")
      else
         return "\0"
      end
   elseif c == '\r' then
      if self:_peek() == '\n' then
         self:_get()
      end
      return "" -- skip the line break.
   elseif c == '\n' then
      return "" -- skip the line break.
   elseif utils.is_digit(c) then
      error("C-style octal character literal is not allowed except for '\\0'. Use prefix \\x or \\u")
   elseif c == 'x' then
      -- \xNN (N: a hexadecimal digit)
      -- U+0000 - U+00FF
      local codepoint = self:_escape_sequence_codepoint(2)
      if utils.is_hex_digit(self:_peek()) then
         error("Escape sequence prefixed by '\\x' must be followed by only two hexadecimal digits, but got third one.")
      end
      return utils.codepoint_to_string(codepoint)
   elseif c == 'u' then
      -- \uNNNN (N: a hexadecimal digit)
      -- U+0000 - U+FFFF
      local first = self:_escape_sequence_codepoint(4)
      if utils.is_hex_digit(self:_peek()) then
         error("Escape sequence prefixed by '\\u' must be followed by only four hexadecimal digits, but got fifth one.")
      end
      if self:_peek() == '\\' then
         -- Surrogate pair?
         self:_get()
         if self:_peek() == 'u' then
            -- They are a surrogate pair.
            local second = self:_escape_sequence_codepoint(4)
            if utils.is_hex_digit(self:_peek()) then
               error("Escape sequence prefixed by '\\u' must be followed by only four hexadecimal digits, but got fifth one.")
            end
            return utils.codepoint_to_string(utils.surrogate_pair_to_codepoint(first, second))
         else
            if utils.is_surrogate_pair_first(first) then
               error(self:_invalid_char("second part of surrogate pair"))
            end
            -- Not surrogate pair, next escape sequence.
            return utils.codepoint_to_string(first)..self:_scan_escape_sequence()
         end
      else
         return utils.codepoint_to_string(first)
      end
   else
      return c
   end
end

-- NumericOrIdentifier
--     Numeric
--     Identifier
--
-- Numeric
--     Sign? 'Infinity'
--     Sign? 'NaN'
--     Sign? HexadecimalInteger
--     Sign? '0' Digit* ('.' Digit*)? Exponent?
--     Sign? NonZeroDigit Digit* ('.' Digit*)? Exponent?
--     Sign? '.' Digit+ Exponent?
--
-- Sign
--     '+'
--     '-'
--
-- Exponent
--     ExponentPrefix Sign? Digit+
--
-- ExponentPrefix
--     'e'
--     'E'
--
-- HexadecimalInteger
--     HexadecimalPrefix HexDigit+
--
-- HexadecimalPrefix
--     '0x'
--     '0X'
--
-- Digit
--     '0'
--     NonZeroDigit
--
-- NonZeroDigit
--     '1' | '2' | ... | '9'
--
-- HexDigit
--     Digit
--     'a' | 'b' | ... | 'f'
--     'A' | 'B' | ... | 'F'
--
-- Identifier
--     IdentifierStart IdentifierContinue*
--
-- IdentifierStart
--     '$'
--     '_'
--     'a' | 'b' | ... | 'z'
--     'A' | 'B' | ... | 'Z'
--
-- IdentifierContinue
--     IdentifierStart
--     Digit
function Lexer:_scan_numeric_or_identifier()
   local sign
   local starts_with_decimal_point = false
   local start = self._pos

   if self:_peek() == '+' then
      self:_get()
      start = start + 1
      sign = 1
   elseif self:_peek() == '-' then
      self:_get()
      sign = -1
   end

   local c = self:_peek()
   if c == '0' then
      self:_get()
      if self:_eof() then
         return "number", 0
      end

      if self:_peek() == 'x' or self:_peek() == 'X' then
         self:_get()
         self._consume_hexadecial_integer()
         return "number", tonumber(self._source:sub(start, self._pos - 1), 16)
      end

      while not self:_eof() do
         if utils.is_digit(self:_peek()) then
            self:_get()
         else
            break
         end
      end
   elseif utils.is_digit(c) then
      while not self:_eof() do
         if utils.is_digit(self:_peek()) then
            self:_get()
         else
            break
         end
      end
   elseif c == '.' then
      starts_with_decimal_point = true
   elseif utils.is_ident_start(c) then
      return self:_scan_identifier(sign)
   else
      error("invalid character, "..self:_get_current_char_for_error_message())
   end

   local has_decimal_point = false
   if self:_peek() == '.' then
      self:_get()
      local has_any_digit = false
      while not self:_eof() do
         if utils.is_digit(self:_peek()) then
            self:_get()
            has_any_digit = true
         else
            break
         end
      end
      if starts_with_decimal_point and not has_any_digit then
         error(self:_invalid_char("a digit"))
      end
      has_decimal_point = true
   end

   local has_exponent = self:_consume_exponent()
   local value = tonumber(self._source:sub(start, self._pos - 1))
   if has_decimal_point or has_exponent then
      return "number", value * 1.0
   else
      return "number", math.floor(value)
   end
end

function Lexer:_consume_hexadecial_integer()
   local has_any_digit = false
   while not self:_eof() do
      if utils.is_hex_digit(self:_peek()) then
         self:_get()
         has_any_digit = true
      else
         break
      end
   end
   if not has_any_digit then
      error(self:_invalid_char("hexadecimal digit (0-9, a-f or A-F)"))
   end
end

function Lexer:_consume_exponent()
   if self:_eof() then
      return false
   end

   if self:_peek() ~= 'e' and self:_peek() ~= 'E' then
      return false
   end

   self:_get()
   if self:_eof() then
      error(self:_invalid_char("digit"))
   end
   if self:_peek() == '+' or self:_peek() == '-' then
      self:_get()
   end
   local has_any_digit = false
   while not self:_eof() do
      if utils.is_hex_digit(self:_peek()) then
         self:_get()
         has_any_digit = true
      else
         break
      end
   end
   if not has_any_digit then
      error(self:_invalid_char("a digit"))
   end

   return true
end

function Lexer:_scan_identifier(sign)
   local name = ""
   while not self:_eof() do
      if utils.is_ident_continue(self:_peek()) then
         name = name..self:_get()
      else
         break
      end
   end

   -- Check special literals.
   if name == "Infinity" then
      if sign then
         return "number", sign * utils.INFINITY
      else
         return "Infinity", utils.INFINITY
      end
   elseif name == "NaN" then
      if sign then
         return "number", utils.NAN
      else
         return "NaN", utils.NAN
      end
   elseif name == "null" then
      if sign then
         error("expected a number, but actually got 'null'")
      else
         return "null"
      end
   elseif name == "true" then
      if sign then
         error("expected a number, but actually got 'true'")
      else
         return "true"
      end
   elseif name == "false" then
      if sign then
         error("expected a number, but actually got 'false'")
      else
         return "false"
      end
   end

   return "identifier", name
end

function Lexer:_escape_sequence_codepoint(n)
   local ret = 0
   for i = 1, n do
      local c = self:_peek()
      if not utils.is_hex_digit(c) then
         error(self:_invalid_char("hexadecimal digit (0-9, a-f or A-F)"))
      end
      ret = ret * 16 + utils.hex_digit_char_to_integer(c)
   end
  return ret
end

function Lexer:_peek()
   return self._source:sub(self._pos, self._pos)
end

function Lexer:_get()
  local ret = self:_peek()
  self._pos = self._pos + 1
  return ret
end

function Lexer:_eof()
   return #self._source < self._pos
end

function Lexer:_invalid_char(expected_char)
   return ("expected %s, but actually got %s."):format(expected_char, self:_get_current_char_for_error_message())
end

function Lexer:_get_current_char_for_error_message()
  if self:_eof() then
      return "<EOF>"
   end

   local start = self._pos
   local end_ = start + utils.byte_count_utf8(string.byte(self._source:sub(self._pos, self._pos)))
   if #self._source < end_ then
      return "<Invalid UTF-8>"
   end

   local length = end_ - start
   if length == 1 then
      local c = self:_peek()
      if c == '\0' then return "<NUL>"
      elseif c == '"' then return "\""
      elseif c == '\'' then return "'"
      elseif c == '\\' then return "'\\'"
      elseif c == '\b' then return "'\\b'"
      elseif c == '\f' then return "'\\f'"
      elseif c == '\n' then return "'\\n'"
      elseif c == '\r' then return "'\\r'"
      elseif c == '\t' then return "'\\t'"
      elseif c == '\v' then return "'\\v'"
      else
         if self:_peek() < ' ' then
            return ("'U+%s'"):format(utils.codepoint_to_hex_digit_string(self:_peek():byte()))
         else
            return ("'%s'"):format(self:_peek())
         end
      end
   elseif length == 2 then
      local first = self._source:sub(start, start):byte()
      local second = self._source:sub(start + 1, start + 1):byte()
      local codepoint = ((first & 0x1F) << 6) | (second & 0x3F)
      return ("'U+%s'"):format(utils.codepoint_to_hex_digit_string(codepoint))
   elseif length == 3 then
      local first = self._source:sub(start, start):byte()
      local second = self._source:sub(start + 1, start + 1):byte()
      local third = self._source:sub(start + 2, start + 2):byte()
      local codepoint = ((first & 0x0F) << 12) | ((second & 0x3F) << 6) | (third & 0x3F)
      return ("'U+%s'"):format(utils.codepoint_to_hex_digit_string(codepoint))
   elseif length == 4 then
      local first = self._source:sub(start, start):byte()
      local second = self._source:sub(start + 1, start + 1):byte()
      local third = self._source:sub(start + 2, start + 2):byte()
      local forth = self._source:sub(start + 3, start + 3):byte()
      local codepoint = ((first & 0x07) << 18) | ((second & 0x3F) << 12) | ((third & 0x3F) << 6) | (forth & 0x3F)
      return ("'U+%s'"):format(utils.codepoint_to_hex_digit_string(codepoint))
   else
      return "<Invalid UTF-8>"
   end
end

return Lexer
