-- Internal functions
local function _escape_sequence(c)
   if c == '"' then return '"'
   elseif c == '\r' then return '' -- newline immediately after backslash is just ignored
   elseif c == '\n' then return ''
   elseif c == '\\' then return '\\'
   elseif c == 't' then return '\t'
   elseif c == 'n' then return '\n'
   elseif c == 'r' then return '\r'
   elseif c == '0' then return '\0'
   elseif c == ' ' then return ' '
   elseif c == '$' then return '$'
   elseif c == '&' then return '&'
   elseif c == '(' then return '('
   elseif c == ')' then return ')'
   elseif c == ';' then return ';'
   elseif c == '<' then return '<'
   elseif c == '>' then return '>'
   elseif c == '{' then return '{'
   elseif c == '|' then return '|'
   elseif c == '}' then return '}'
   else error("Unknown escape sequence: \\" .. c)
   end
end



local function _is_delimiter(c)
   return c == '\t' or c == ' ' or
      c == '\n' or c == '\r' or
      c == '|' or c == '&' or
      c == '<' or c == '>' or
      c == '(' or c == ')' or
      c == '{' or c == '}' or
      c == ';'
end



local function token(kind, value)
   return {
      kind = kind,
      value = value,
   }
end



-- TextBuffer
local TextBuffer = {}



function TextBuffer.new(src)
   local self = {_source = src, _index = 1}
   setmetatable(self, {__index = TextBuffer})
   return self
end



function TextBuffer:peek()
   return self._source:sub(self._index, self._index)
end



function TextBuffer:get()
   self._index = self._index + 1
   return self._source:sub(self._index - 1, self._index - 1)
end



function TextBuffer:eos()
   return #self._source < self._index
end



function TextBuffer:skip_to(delimiter)
   local prev = self._index
   local s, e = self._source:find(delimiter, self._index, true --[[ disable pattern matching ]])
   if s == nil then return nil end
   self._index = s
   return self._source:sub(prev, s - 1)
end



function TextBuffer:seek(offset)
   self._index = self._index + offset
end



function TextBuffer:rest()
   return self._source:sub(self._index, -1)
end



-- Lexer
local Lexer = {}



function Lexer.new(src, sublexer)
   local self = {
      _source = TextBuffer.new(src),
      _token = token('NONE'),
      _state = 'NORMAL',
      _lua_expr_delimiter = '',
      _sublexer = sublexer,
   }
   setmetatable(self, {__index = Lexer})
   self:scan()
   return self
end



function Lexer:get()
   return self._token
end



function Lexer:scan()
   self._token = self:_scan_impl()
end



function Lexer:_eos()
   return self._source:eos() or (self._sublexer and self._source:peek() == ')')
end



function Lexer:_scan_impl()
   if self:_eos() then
      return token('EOS')
   end

   if self._state == 'IN_LUA_EXPR' then
      local expr = self._source:skip_to(self._lua_expr_delimiter)
      if not expr then
         error('Expected ' .. self._lua_expr_delimiter)
      end
      self._lua_expr_delimiter = ''
      self._state = 'NORMAL'
      return token('RAW_STRING', expr)
   end

   local first = self._source:peek()

   if first == '\t' or first == ' ' then
      self._source:get()
      return self:_scan_impl()
   elseif first == '\r' or first == '\n' then
      self._source:get()
      return token('SEMICOLON')
   elseif first == '|' then
      self._source:get()
      if not self:_eos() and self._source:peek() == '|' then
         self._source:get()
         return token('OROR')
      else
         return token('OR')
      end
   elseif first == '&' then
      self._source:get()
      if not self:_eos() and self._source:peek() == '|' then
         self._source:get()
         return token('ANDAND')
      else
         error("'&' is not supported. Did you mean '&&'?")
      end
   elseif first == ';' then
      self._source:get()
      return token('SEMICOLON')
   elseif first == '<' then
      self._source:get()
      error("'<' is not supported. Did you mean '>'?")
   elseif first == '>' then
      self._source:get()
      return token('GREATER_THAN')
   elseif first == '(' then
      self._source:get()
      if not self:_eos() and self._source:peek() == '(' then
         self._source:get()
         self._state = 'IN_LUA_EXPR'
         self._lua_expr_delimiter = '))'
         return token('DOUBLE_PAREN_LEFT')
      else
         return token('PAREN_LEFT')
      end
   elseif first == ')' then
      self._source:get()
      if not self:_eos() and self._source:peek() == ')' then
         self._source:get()
         self._state = 'NORMAL'
         return token('DOUBLE_PAREN_RIGHT')
      else
         return token('PAREN_RIGHT')
      end
   elseif first == '{' then
      self._source:get()
      return token('BRACE_LEFT')
   elseif first == '}' then
      self._source:get()
      return token('BRACE_RIGHT')
   elseif first == '[' then
      self._source:get()
      if not self:_eos() and self._source:peek() == '[' then
         self._source:get()
         self._state = 'IN_LUA_EXPR'
         self._lua_expr_delimiter = ']]'
         return token('DOUBLE_BRACKET_LEFT')
      else
         -- fall through
      end
   elseif first == ']' then
      self._source:get()
      if not self:_eos() and self._source:peek() == ']' then
         self._source:get()
         self._state = 'NORMAL'
         return token('DOUBLE_BRACKET_RIGHT')
      else
         -- fall through
      end
   end

   local str_segments = {}
   while not self:_eos() do
      local c = self._source:peek()
      if _is_delimiter(c) then
         break
      elseif c == '"' then
         self._source:get()
         local ss = self:_scan_string(function(c) return c == '"' end)
         self._source:get() -- skip double quote.
         for _, s in ipairs(ss) do
            str_segments[#str_segments+1] = s
         end
      elseif c == "'" then
         self._source:get()
         local str = ''
         while not self:_eos() do
            c = self._source:get()
            if c == "'" then
               break
            else
               str = str .. c
            end
         end
         str_segments[#str_segments+1] = {kind = 'literal', string = str}
      else
         local ss = self:_scan_string(_is_delimiter)
         for _, s in ipairs(ss) do
            str_segments[#str_segments+1] = s
         end
      end
   end
   return token('STRING', str_segments)
end



function Lexer:_scan_string(is_delimiter)
   local ss = {}
   local s = ''
   while not self:_eos() do
      local c = self._source:peek()
      if is_delimiter(c) then
         break
      elseif c == '\\' then
         self._source:get()
         if self:_eos() then
            error('invalid escape sequence')
         end
         s = s .. _escape_sequence(self._source:get())
      elseif c == '$' then
         if #s ~= 0 then
            ss[#ss+1] = {kind = 'literal', string = s}
         end
         s = ''
         self._source:get()
         if self:_eos() then
            error('unexpected <EOS>')
         end
         local second = self._source:peek()
         if second == '(' then
            -- $(x y z)
            self._source:get()
            local sublexer = Lexer.new(self._source:rest(), true)
            local tokens = {}
            while true do
               local tok = sublexer:get()
               tokens[#tokens+1] = tok
               if tok.kind == 'EOS' then
                  break
               end
               sublexer:scan()
            end
            self._source:seek(#self._source:rest() - #sublexer._source:rest())
            ss[#ss+1] = {kind = 'command_substitution', tokens = tokens}
         elseif second == '{' then
            -- ${VARIABLE}
            self._source:get()
            local name = ''
            while not self:_eos() do
               local c = self._source:get()
               if c == '}' then
                  break
               end
               name = name .. c
            end
            ss[#ss+1] = {kind = 'variable', name = name}
         else
            -- $VARIABLE
            local name = ''
            while not self:_eos() do
               local c = self._source:get()
               if not c:match('[%w_]') then
                  break
               end
               name = name .. c
            end
            ss[#ss+1] = {kind = 'variable', name = name}
         end
      else
         self._source:get()
         s = s .. c
      end
   end
   if #s ~= 0 then
      ss[#ss+1] = {kind = 'literal', string = s}
   end
   return ss
end



return function(src)
   local lexer = Lexer.new(src)
   local tokens = {}
   while true do
      local tok = lexer:get()
      tokens[#tokens+1] = tok
      if tok.kind == 'EOS' then break end
      lexer:scan()
   end
   return tokens
end
