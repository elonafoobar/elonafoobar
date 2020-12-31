local class = prelude.class

local Lexer = require("json5.lexer")

local TokenStream = class("json5.TokenStream")

function TokenStream:__init(source)
   self._lexer = Lexer.new(source)
   self:get()
end

function TokenStream:peek()
   return self._next_tok, self._next_val
end

function TokenStream:get()
   local t, v = self._next_tok, self._next_val
   self._next_tok, self._next_val = self._lexer:scan()
   return t, v
end

return TokenStream
