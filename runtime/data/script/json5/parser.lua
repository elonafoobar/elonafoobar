local class = prelude.class

local TokenStream = require("json5.token_stream")

local Parser = class("json5.Parser")

function Parser:__init(source)
   self._ts = TokenStream.new(source)
end

function Parser:parse()
   return self:_parse_value()
end

function Parser:_parse_value()
   local tok, value = self._ts:get()
   if tok == "[" then
      return self:_parse_array()
   elseif tok == "{" then
      return self:_parse_object()
   elseif tok == "null" then
      return nil
   elseif tok == "true" then
      return true
   elseif tok == "false" then
      return false
   elseif tok == "Infinity" then
      return value
   elseif tok == "NaN" then
      return value
   elseif tok == "number" then
      return value
   elseif tok == "string" then
      return value
   else
      error(("expect any JSON5 value, but actually '%s'"):format(tok))
   end
end

function Parser:_parse_array()
   -- The open bracket '[' has been consumed by the caller.
   local array = {}
   while true do
      local next_tok = self._ts:peek()
      if next_tok == "EOF" then
         error("expect any JSON5 value or ']', but actually EOF")
      elseif next_tok == "]" then
         self._ts:get()
         break
      end

      array[#array + 1] = self:_parse_value()

      local delimiter = self._ts:get()
      if delimiter == "]" then
         break
      elseif delimiter ~= "," then
         error(("expect ']' or ',', but actually '%s'"):format(delimiter))
      end
   end
   return array
end

function Parser:_parse_object()
   -- The open brace '{' has been consumed by the caller.
   local object = {}
   while true do
      local next_tok = self._ts:peek()
      if next_tok == "EOF" then
         error("expect any JSON5 value or '}', but actually EOF")
      elseif next_tok == "}" then
         self._ts:get()
         break
      end

      local k = self:_parse_key()
      local kv_separator = self._ts:get()
      if kv_separator ~= ":" then
         error(("expect ':', but actually '%s'"):format(kv_separator))
      end
      local v = self:_parse_value()

      object[k] = v

      local delimiter = self._ts:get()
      if delimiter == "}" then
         break
      elseif delimiter ~= "," then
         error(("expect '}' or ',', but actually '%s'"):format(delimiter))
      end
   end
   return object
end

function Parser:_parse_key()
   local tok, value = self._ts:get()
   if tok == "null" then
      return "null"
   elseif tok == "true" then
      return "true"
   elseif tok == "false" then
      return "false"
   elseif tok == "Infinity" then
      return "Infinity"
   elseif tok == "NaN" then
      return "NaN"
   elseif tok == "string" then
      return value
   elseif tok == "identifier" then
      return value
   else
      error(("expect an object key, but actually '%s'"):format(tok))
   end
end

return Parser
