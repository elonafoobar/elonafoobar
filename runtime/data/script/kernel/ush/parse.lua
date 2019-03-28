local lex = require 'ush/lex'
local ast = require 'ush/ast'


-- Parser
local Parser = {}



local function _build_ast_from_string_segments(segments)
   local ss = {}
   for _, segment in ipairs(segments) do
      if segment.kind == 'literal' then
         ss[#ss+1] = ast.StringLiteral(segment.string)
      elseif segment.kind == 'variable' then
         ss[#ss+1] = ast.Variable(segment.name)
      elseif segment.kind == 'command_substitution' then
         local subparser = Parser.new()
         local cmd = subparser:parse(segment.tokens)
         ss[#ss+1] = ast.CommandSubstitution(cmd)
      else
         error('unreachable')
      end
   end
   return ast.String(ss)
end



function Parser.new()
   local self = {}
   setmetatable(self, {__index = Parser})
   return self
end



function Parser:get()
   return self._tokens[self._index]
end



function Parser:next()
   self._index = self._index + 1
end



function Parser:parse(x)
   if type(x) == 'string' then
      -- from source
      -- x is source string.
      self._tokens = lex(x)
   else
      -- from token sequence
      -- x is array of tokens.
      self._tokens = x
   end
   self._index = 1

   return self:parse_tier1()
end



function Parser:expect(token_kind)
   local tok = self:get()
   if tok.kind == token_kind then
      self:next()
      return tok
   else
      error('Expected ' .. token_kind .. ', but actually ' .. tok.kind, 2)
   end
end



-- x; y
function Parser:parse_tier1()
   local lhs = self:parse_tier2()
   while self:get().kind == 'SEMICOLON' do
      self:next()
      local token_kind = self:get().kind
      if token_kind ~= 'STRING' and token_kind ~= 'DOUBLE_PAREN_LEFT' and token_kind ~= 'DOUBLE_BRACKET_LEFT' then
         -- trailing semicolon is allowed.
         break
      end
      local rhs = self:parse_tier2()
      lhs = ast.CommandListThen(lhs, rhs)
   end
   return lhs
end



-- x && y
-- x || y
function Parser:parse_tier2()
   local lhs = self:parse_tier3()
   while self:get().kind == 'ANDAND' or self:get().kind == 'OROR' do
      self:next()
      local rhs = self:parse_tier3()
      if self:get().kind == 'ANDAND' then
         lhs = ast.CommandListAnd(lhs, rhs)
      else
         lhs = ast.CommandListOr(lhs, rhs)
      end
   end
   return lhs
end



function Parser:parse_tier3()
   local lhs = self:parse_tier4()
   while self:get().kind == 'OR' do
      self:next()
      local rhs = self:parse_tier4()
      lhs = ast.Pipeline(lhs, rhs)
   end
   return lhs
end



-- x > out
function Parser:parse_tier4()
   local cmd = self:parse_tier5()
   if self:get().kind == 'GREATER_THAN' then
      self:next()
      if self:get().kind == 'STRING' then
         local string_segments = self:get().value
         self:next()
         return ast.RedirectCommand(cmd, _build_ast_from_string_segments(string_segments))
      else
         error("Expect a filepath.")
      end
   end
   return cmd
end



-- (x; y)
-- {x; y}
-- x a b c
function Parser:parse_tier5()
   if self:get().kind == 'PAREN_LEFT' then
      -- ( grouped command executed in a subshell )
      self:next()
      local cmd
      if self:get().kind ~= 'PAREN_RIGHT' then
         cmd = self:parse_tier1()
      end
      self:expect('PAREN_RIGHT')
      return ast.CommandGroup(cmd, true)
   elseif self:get().kind == 'BRACE_LEFT' then
      -- { grouped command executed in the current shell }
      self:next()
      local cmd
      if self:get().kind ~= 'BRACE_RIGHT' then
         cmd = self:parse_tier1()
      end
      self:expect('BRACE_RIGHT')
      return ast.CommandGroup(cmd, false)
   else
      local cmd = self:parse_tier6()
      if not cmd then
         error('Invalid token: ' .. self:get().kind)
      end
      local args = {}
      while true do
         local arg = self:parse_tier6()
         if not arg then break end
         args[#args+1] = arg
      end
      return ast.SimpleCommand(cmd, args)
   end
end



-- "str"
-- (( lua expr ))
-- [[ lua expr ]]
function Parser:parse_tier6()
   local tok = self:get()
   if tok.kind == 'STRING' then
      local string_segments = self:get().value
      self:next()
      return _build_ast_from_string_segments(string_segments)
   elseif tok.kind == 'DOUBLE_PAREN_LEFT' then
      -- (( embedded Lua expression ))
      self:next()
      local expr = self:expect('RAW_STRING').value
      self:expect('DOUBLE_PAREN_RIGHT')
      return ast.EmbeddedLuaExpression(expr, false)
   elseif tok.kind == 'DOUBLE_BRACKET_LEFT' then
      -- [[ embedded Lua expression ]] similar to (()), but it returns only boolean, true/false.
      self:next()
      local expr = self:expect('RAW_STRING').value
      self:expect('DOUBLE_BRACKET_RIGHT')
      return ast.EmbeddedLuaExpression(expr, true)
   else
      return nil
   end
end



return function(x)
   local parser = Parser.new()
   return parser:parse(x)
end
