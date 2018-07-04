local utils = require "elocheck.utils"

local sbyte = string.byte
local schar = string.char
local ssub = string.sub
local sfind = string.find
local slen = string.len

local BYTE_OPAREN, BYTE_CPAREN = sbyte("("), sbyte(")")
local BYTE_COMMA, BYTE_DQUOTE = sbyte(","), sbyte("\"")
local BYTE_BSLASH = sbyte("\\")
local BYTE_LF, BYTE_CR = sbyte("\n"), sbyte("\r")

local scanner = {}

local Scanner = utils.class()

function Scanner:__init(src)
   self.src = src
   self.line = 1
   self.line_offset = 1
   self.offset = 1
end

function Scanner:peek()
   return sbyte(self.src, self.offset)
end

function Scanner:location()
   return { line = self.line, column = self.offset - self.line_offset }
end

function Scanner:check_char(char)
   if not self:peek() == char then
      error("Expected " .. char)
   end
end

local function is_newline(b)
   return (b == BYTE_LF) or (b == BYTE_CR)
end

function Scanner:next_byte(inc)
   inc = inc or 1
   self.offset = self.offset+inc

   local b = self:peek()

   if is_newline(b) then
      self.line = self.line+1
      self.line_offset = self.offset
   end

   return b
end

function Scanner:skip_newline(newline)
   local b = self:next_byte()

   if b ~= newline and is_newline(b) then
      b = self:next_byte()
   end

   return b
end

function Scanner:skip_till_newline(b)
   while not is_newline(b) and b ~= nil do
      b = self:next_byte()
   end

   return b
end

function Scanner:try_match(pattern)
   local start = self.offset
   self:skip_till_newline(self:peek())
   local line = ssub(self.src, start, self.offset-1)
   local offset = sfind(line, pattern)
   if offset then
      self.offset = self.offset - (slen(line) - offset) - 1
      return true
   end
   return false
end

function Scanner:scan_until(pattern)
   local b
   while true do
      local found = self:try_match(pattern)
      if found then
         -- set stream to match start
         return true
      end

      b = self:next_byte()
      if b == nil then
         break
      end
   end

   return false
end

function Scanner:skip_string()
   self:check_char('"')

   while true do
      local b = self:next_byte()

      if b == BYTE_BSLASH then
         self:next_byte()
      elseif b == BYTE_DQUOTE then
         break
      end
   end
end

local function trim(s)
  return (s:gsub("^%s*(.-)%s*$", "%1"))
end

local function parse_arg(arg_string)
   local parts = {}
   local off = 1

   return trim(arg_string)
end

function Scanner:scan_args()
   self:check_char('(')
   local parens = 1
   local start = self.offset + 1
   local before = start
   local args = {}

   local function add(arg_start)
      local arg_string = ssub(self.src, arg_start, self.offset-1)
      if slen(arg_string) > 0 then
         args[#args+1] = parse_arg(arg_string)
      end
   end

   while true do
      local b = self:next_byte()

      if b == nil then
         self.offset = before
         return nil
      end

      if b == BYTE_DQUOTE then
         self:skip_string()
      elseif b == BYTE_OPAREN then
         parens = parens + 1
      elseif b == BYTE_CPAREN then
         parens = parens - 1
      elseif b == BYTE_COMMA and parens == 1 then
         add(start)
         start = self.offset + 1
      end

      if parens == 0 then
         add(start)
         break
      end
   end

   self.offset = before
   return args
end

function Scanner:scan(wanted)
   local found = self:scan_until(wanted)
   if not found then
      return nil
   end
   local name_start = self.offset
   found = self:scan_until("%(")
   if not found then
      return nil
   end

   local name = ssub(self.src, name_start, self.offset-1)

   local args = self:scan_args()

   if not args then
      return nil
   end

   return {name = name, args = args}
end

function scanner.new(src)
   return Scanner(src)
end

return scanner
