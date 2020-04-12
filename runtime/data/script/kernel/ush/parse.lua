local table = prelude.table
local string = prelude.string


-- Internal functions --

-- :: string -> string
local function _escape_sequence(c)
   if c == '"' then return '"'
   elseif c == "\r" then return "" -- newline immediately after backslash is just ignored
   elseif c == "\n" then return ""
   elseif c == "\\" then return "\\"
   elseif c == "t" then return "\t"
   elseif c == "n" then return "\n"
   elseif c == "r" then return "\r"
   elseif c == "0" then return "\0"
   else error("(ush) invalid escape sequence: \\"..c)
   end
end



-- :: string -> boolean
local function _is_delimiter(c)
   return c == "\t" or c == " " or c == "\n" or c == "\r" or c == ";"
end



-- Lexer
local Lexer = {}



function Lexer.new(src)
   local self = {
      _source = src,
      _index = 1,
   }
   setmetatable(self, {__index = Lexer})
   return self
end



function Lexer:scan()
   local tokens = {}
   while true do
      local token = self:_scan_one_token()
      if not token then
         break
      end
      tokens[#tokens+1] = token
   end
   return tokens
end



function Lexer:_scan_one_token()
   if self:_eos() then
      return nil
   end

   local first = self:_get()

   if first == "\t" or first == " " then
      self._index = self._index + 1
      return self:_scan_one_token()
   end

   local s
   if first == '"' or first == "'" then
      self._index = self._index + 1 -- skip quotation.
      s = self:_scan_string(function(c) return c == first end)
      self._index = self._index + 1 -- skip quotation.
   else
      s = self:_scan_string(_is_delimiter)
   end
   return s
end



-- :: (string -> boolean) -> string
function Lexer:_scan_string(is_delimiter)
   local s = ""
   while not self:_eos() do
      local c = self:_get()
      self._index = self._index + 1

      if is_delimiter(c) then
         break
      end

      if c == "\\" then
         if self:_eos() then
            error("(ush) invalid escape sequence")
         end
         s = s.._escape_sequence(self:_get())
      else
         s = s..c
      end
   end
   return s
end



function Lexer:_get()
   return string.at(self._source, self._index)
end



function Lexer:_eos()
   return #self._source < self._index
end



-- :: string -> List<Token>
local function tokenize(src)
   local lexer = Lexer.new(src)
   return lexer:scan()
end



-- string -> tokens
return function(src)
   local tokens = tokenize(src)
   if #tokens == 0 then
      error("(ush) invalid command line: "..src)
   end
   return table.unpack(tokens)
end
