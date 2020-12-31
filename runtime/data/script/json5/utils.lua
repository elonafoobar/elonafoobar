local utils = {}

local CODE_0 = string.byte('0')
local CODE_9 = string.byte('9')
local CODE_A = string.byte('A')
local CODE_F = string.byte('F')
local CODE_Z = string.byte('Z')
local CODE_a = string.byte('a')
local CODE_f = string.byte('f')
local CODE_z = string.byte('z')
local UNDERSCORE = string.byte('_')
local DOLLAR = string.byte('$')

utils.INFINITY = 1 / 0
utils.NAN = 0 / 0

function utils.count_table(t)
   local n = 0
   for _ in pairs(t) do
      n = n + 1
   end
   return n
end

function utils.is_ident_start(c)
   c = c:byte()
   return (CODE_A <= c and c <= CODE_Z) or
      (CODE_a <= c and c <= CODE_z) or
      c == UNDERSCORE or c == DOLLAR
end

function utils.is_digit(c)
   c = c:byte()
   return CODE_0 <= c and c <= CODE_9
end

function utils.is_hex_digit(c)
   c = c:byte()
   return (CODE_0 <= c and c <= CODE_9) or
      (CODE_A <= c and c <= CODE_F) or
      (CODE_a <= c and c <= CODE_f)
end

function utils.is_ident_continue(c)
   return utils.is_ident_start(c) or utils.is_digit(c)
end

function utils.is_ident(s)
   if not utils.is_ident_start(s:sub(1, 1)) then
      return false
   end
   for i = 1, #s do
      if not utils.is_ident_continue(s:sub(i, i)) then
         return false
      end
   end
   return true
end

function utils.byte_count_utf8(c)
   if                   c <= 0x7F then return 1
   elseif 0xC2 <= c and c <= 0xDF then return 2
   elseif 0xE0 <= c and c <= 0xEF then return 3
   elseif 0xF0 <= c and c <= 0xF7 then return 4
   elseif 0xF8 <= c and c <= 0xFB then return 5
   elseif 0xFC <= c and c <= 0xFD then return 6
   else                                return 1
   end
end

function utils.is_surrogate_pair_first(c)
   return 0xD800 <= c and c <= 0xDBFF
end

function utils.hex_digit_char_to_integer(c)
   if     c == "0" then return 0
   elseif c == "1" then return 1
   elseif c == "2" then return 2
   elseif c == "3" then return 3
   elseif c == "4" then return 4
   elseif c == "5" then return 5
   elseif c == "6" then return 6
   elseif c == "7" then return 7
   elseif c == "8" then return 8
   elseif c == "9" then return 9
   elseif c == "A" or c == "a" then return 10
   elseif c == "B" or c == "b" then return 11
   elseif c == "C" or c == "c" then return 12
   elseif c == "D" or c == "d" then return 13
   elseif c == "E" or c == "e" then return 14
   elseif c == "F" or c == "f" then return 15
   else return nil
   end
end

function utils.surrogate_pair_to_codepoint(first, second)
   return 0x10000 + (first - 0xD800) * 0x400 + (second - 0xDC00)
end

function utils.codepoint_to_string(codepoint)
   if codepoint <= 0x007F then
      -- 1 byte in UTF-8
      return string.char(codepoint)
   elseif codepoint <= 0x07FF then
      -- 2 bytes in UTF-8
      local first = 0xC0 | (codepoint >> 6)
      local second = 0x80 | (codepoint & 0x3F)
      return string.char(first, second)
   elseif codepoint <= 0xFFFF then
      -- 3 bytes in UTF-8.
      local first = 0xE0 | (codepoint >> 12)
      local second = 0x80 | ((codepoint >> 6) & 0x3F)
      local third = 0x80 | (codepoint & 0x3F)
      return string.char(first, second, third)
   else
      -- 4 bytes in UTF-8.
      local first = 0xF0 | (codepoint >> 18)
      local second = 0x80 | ((codepoint >> 12) & 0x3F)
      local third = 0x80 | ((codepoint >> 6) & 0x3F)
      local forth = 0x80 | (codepoint & 0x3F)
      return string.char(first, second, third, forth)
   end
end

function utils.codepoint_to_hex_digit_string(c)
   local ret = tonumber(c, 16)
   if #ret < 2 then
      return "0"..ret
   else
      return ret
   end
end

return utils
