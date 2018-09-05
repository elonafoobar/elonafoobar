local Lexer = {}

local sbyte = string.byte
local slen = string.len
local ssub = string.sub
local schar = string.char
local sreverse = string.reverse
local tconcat = table.concat
local mfloor = math.floor

-- No point in inlining these, fetching a constant ~= fetching a local.
local BYTE_0, BYTE_9, BYTE_f, BYTE_F = sbyte("0"), sbyte("9"), sbyte("f"), sbyte("F")
local BYTE_x, BYTE_X, BYTE_i, BYTE_I = sbyte("x"), sbyte("X"), sbyte("i"), sbyte("I")
local BYTE_l, BYTE_L, BYTE_u, BYTE_U = sbyte("l"), sbyte("L"), sbyte("u"), sbyte("U")
local BYTE_e, BYTE_E, BYTE_p, BYTE_P = sbyte("e"), sbyte("E"), sbyte("p"), sbyte("P")
local BYTE_a, BYTE_z, BYTE_A, BYTE_Z = sbyte("a"), sbyte("z"), sbyte("A"), sbyte("Z")
local BYTE_n = sbyte("n")
local BYTE_DOT, BYTE_COLON = sbyte("."), sbyte(":")
local BYTE_OBRACK, BYTE_CBRACK = sbyte("["), sbyte("]")
local BYTE_OBRACE, BYTE_CBRACE = sbyte("{"), sbyte("}")
local BYTE_QUOTE, BYTE_DQUOTE = sbyte("'"), sbyte('"')
local BYTE_PLUS, BYTE_DASH, BYTE_LDASH = sbyte("+"), sbyte("-"), sbyte("_")
local BYTE_SLASH, BYTE_BSLASH = sbyte("/"), sbyte("\\")
local BYTE_EQ, BYTE_NE = sbyte("="), sbyte("~")
local BYTE_LT, BYTE_GT = sbyte("<"), sbyte(">")
local BYTE_LF, BYTE_CR = sbyte("\n"), sbyte("\r")
local BYTE_HASH, BYTE_STAR = sbyte("#"), sbyte("*")
local BYTE_DOLLAR, BYTE_COMMA = sbyte("$"), sbyte(",")
local BYTE_SPACE, BYTE_FF, BYTE_TAB, BYTE_VTAB = sbyte(" "), sbyte("\f"), sbyte("\t"), sbyte("\v")

local function to_hex(b)
   if BYTE_0 <= b and b <= BYTE_9 then
      return b-BYTE_0
   elseif BYTE_a <= b and b <= BYTE_f then
      return 10+b-BYTE_a
   elseif BYTE_A <= b and b <= BYTE_F then
      return 10+b-BYTE_A
   else
      return nil
   end
end

local function to_dec(b)
   if BYTE_0 <= b and b <= BYTE_9 then
      return b-BYTE_0
   else
      return nil
   end
end

local function is_ascii(codepoint)
   return codepoint < 0x80
end

local function to_utf(codepoint)
   if is_ascii(codepoint) then  -- ASCII?
      return schar(codepoint)
   end

   local buf = {}
   local mfb = 0x3F

   repeat
      buf[#buf+1] = schar(codepoint % 0x40 + 0x80)
      codepoint = mfloor(codepoint / 0x40)
      mfb = mfloor(mfb / 2)
   until codepoint <= mfb

   buf[#buf+1] = schar(0xFE - mfb*2 + codepoint)
   return sreverse(tconcat(buf))
end

local function is_utf(codepoint)
   return not is_ascii(codepoint) and to_utf(codepoint)
end

local function is_alpha(b)
   return (BYTE_a <= b and b <= BYTE_z) or
      (BYTE_A <= b and b <= BYTE_Z) or b == BYTE_LDASH
end

local function is_newline(b)
   return (b == BYTE_LF) or (b == BYTE_CR)
end

local function is_space(b)
   return (b == BYTE_SPACE) or (b == BYTE_FF) or
      (b == BYTE_TAB) or (b == BYTE_VTAB)
end

local function is_ident_char(b)
   return (is_alpha(b) or to_dec(b) or b == BYTE_LDASH or b == BYTE_DASH
      or b == BYTE_DOT or b == BYTE_COLON or b == BYTE_SLASH
              or is_utf(b))
end

local simple_escapes = {
   [sbyte("a")] = sbyte("\a"),
   [sbyte("b")] = sbyte("\b"),
   [sbyte("f")] = sbyte("\f"),
   [sbyte("n")] = sbyte("\n"),
   [sbyte("r")] = sbyte("\r"),
   [sbyte("t")] = sbyte("\t"),
   [sbyte("v")] = sbyte("\v"),
   [BYTE_BSLASH] = BYTE_BSLASH,
   [BYTE_QUOTE] = BYTE_QUOTE,
   [BYTE_DQUOTE] = BYTE_DQUOTE
}

local function next_byte(state, inc)
   inc = inc or 1
   state.offset = state.offset+inc
   return sbyte(state.src, state.offset)
end

-- Skipping helpers.
-- Take the current character, skip something, return next character.

local function skip_newline(state, newline)
   local b = next_byte(state)

   if b ~= newline and is_newline(b) then
      b = next_byte(state)
   end

   state.line = state.line+1
   state.line_offset = state.offset
   return b
end

local function skip_till_newline(state, b)
   while not is_newline(b) and b ~= nil do
      b = next_byte(state)
   end

   return b
end

local function skip_till_comment_end(state, b)
   while b ~= nil do
      if b == BYTE_STAR then
         b = next_byte(state)

         if b == BYTE_SLASH then
            return b
         end
      end
      b = next_byte(state)
   end

   return b
end

local function skip_till_heredoc_end(state, b, anchor)
   local buffer = ""
   local line = ""
   local indent_line = ""

   while b ~= nil do
      if b == BYTE_LF then
         if (slen(buffer) ~= 0) then
            buffer = buffer .. "\n"
         end
         buffer = buffer .. indent_line
         buffer = buffer .. line
         line = ""
         indent_line = ""
      elseif (slen(line) == 0) and (b == BYTE_SPACE or b == BYTE_TAB) then
         indent_line = indent_line .. schar(b)
      else
         line = line .. schar(b)
      end

      if line == anchor then
         b = next_byte(state)
         return b, true
      end

      b = next_byte(state)
   end

   return b, false
end

local function skip_space(state, b)
   while is_space(b) or is_newline(b) do
      if is_newline(b) then
         b = skip_newline(state, b)
      else
         b = next_byte(state)
      end
   end

   return b
end

-- Token handlers.

local function lex_short_string(state, quote)
   local b = next_byte(state)
   local chunks  -- Buffer is only required when there are escape sequences.
   local chunk_start = state.offset
   local braces = 0
   local dollar = false
   local hil = false

   while b ~= nil do
      if b == quote and braces == 0 then
         break
      end

      if braces == 0 and dollar and b == BYTE_OBRACE then
         braces = braces + 1
         hil = true
      elseif braces > 0 and b == BYTE_OBRACE then
         braces = braces + 1
      end

      if braces > 0 and b == BYTE_CBRACE then
         braces = braces - 1
      end

      dollar = false
      if braces == 0 and b == BYTE_DOLLAR then
         dollar = true
      end

      if b == BYTE_BSLASH then
         -- Escape sequence.

         if not chunks then
            -- This is the first escape sequence, init buffer.
            chunks = {}
         end

         -- Put previous chunk into buffer.
         if chunk_start ~= state.offset then
            chunks[#chunks+1] = ssub(state.src, chunk_start, state.offset-1)
         end

         b = next_byte(state)

         -- The final string escape sequence evaluates to.
         local s

         local escape_byte = simple_escapes[b]

         if escape_byte then  -- Is it a simple escape sequence?
            b = next_byte(state)
            s = schar(escape_byte)
         elseif is_newline(b) then
            if braces == 0 then
               return nil, "string literal not terminated"
            end
            b = skip_newline(state, b)
            s = "\n"
         elseif b == BYTE_x then
            -- Hexadecimal escape.
            b = next_byte(state)  -- Skip "x".
            -- Exactly two hexadecimal digits.
            local c1, c2

            if b then
               c1 = to_hex(b)
            end

            if not c1 then
               return nil, "invalid hexadecimal escape sequence", -2
            end

            b = next_byte(state)

            if b then
               c2 = to_hex(b)
            end

            if not c2 then
               return nil, "invalid hexadecimal escape sequence", -3
            end

            b = next_byte(state)
            s = schar(c1*16 + c2)
         elseif b == BYTE_u or b == BYTE_U then
            local size = 4
            if b == BYTE_U then
               size = 8
            end

            b = next_byte(state)  -- Skip "u".

            local codepoint = 0
            local hexdigits = 0

            while hexdigits < size do
               local hex

               if b then
                  hex = to_hex(b)
               end

               if hex then
                  hexdigits = hexdigits + 1
                  codepoint = codepoint*16 + hex

                  if codepoint > 0x10FFFF then
                     -- UTF-8 value too large.
                     return nil, "UTF-8 escape sequence too large", -hexdigits-size-1
                  end
               else
                  return nil, "UTF-8 escape sequence contained invalid character:(" .. schar(b) .. ")", -size-1
               end
               b = next_byte(state)
            end

            s = to_utf(codepoint)
         elseif b == BYTE_z then
            -- Zap following span of spaces.
            b = skip_space(state, next_byte(state))
         else
            -- Must be a decimal escape.
            local cb

            if b then
               cb = to_dec(b)
            end

            if not cb then
               return nil, "invalid escape sequence", -1
            end

            -- Up to three decimal digits.
            b = next_byte(state)

            if b then
               local c2 = to_dec(b)

               if c2 then
                  cb = 10*cb + c2
                  b = next_byte(state)

                  if b then
                     local c3 = to_dec(b)

                     if c3 then
                        cb = 10*cb + c3

                        if cb > 255 then
                           return nil, "invalid decimal escape sequence", -3
                        end

                        b = next_byte(state)
                     end
                  end
               end
            end

            s = schar(cb)
         end

         if s then
            chunks[#chunks+1] = s
         end

         -- Next chunk starts after escape sequence.
         chunk_start = state.offset
      elseif b == nil or (is_newline(b) and braces == 0) then
         return nil, "unfinished string"
      else
         b = next_byte(state)
      end
   end

   if b == nil and braces ~= 0 then
      return nil, "expected terminating brace"
   end

   -- Offset now points at the closing quote.
   local string_value

   if chunks then
      -- Put last chunk into buffer.
      if chunk_start ~= state.offset then
         chunks[#chunks+1] = ssub(state.src, chunk_start, state.offset-1)
      end

      string_value = tconcat(chunks)
   else
      -- There were no escape sequences.
      string_value = ssub(state.src, chunk_start, state.offset-1)
   end

   next_byte(state)  -- Skip the closing quote.

   local ty = "string"

   if hil then
      ty = "hil"
   end

   return ty, string_value
end

-- Payload for a number is simply a substring.
local function lex_number(state, b)
   local start = state.offset

   local exp_lower, exp_upper = BYTE_e, BYTE_E
   local is_digit = to_dec
   local has_digits = false
   local is_float = false
   local is_negative = false

   if b == BYTE_DASH then
      b = next_byte(state)
      is_negative = true
   end

   if b == BYTE_0 then
      b = next_byte(state)

      if b == BYTE_x or b == BYTE_X then
         exp_lower, exp_upper = BYTE_p, BYTE_P
         is_digit = to_hex
         b = next_byte(state)
      else
         has_digits = true
      end
   end

   while b ~= nil and is_digit(b) do
      b = next_byte(state)
      has_digits = true
   end

   if b == BYTE_DOT then
      -- Fractional part.
      is_float = true
      b = next_byte(state)  -- Skip dot.

      while b ~= nil and is_digit(b) do
         b = next_byte(state)
         has_digits = true
      end
   end

   if b == exp_lower or b == exp_upper then
      -- Exponent part.
      is_float = true
      b = next_byte(state)

      -- Skip optional sign.
      if b == BYTE_PLUS or b == BYTE_DASH then
         b = next_byte(state)
      end

      -- Exponent consists of one or more decimal digits.
      if b == nil or not to_dec(b) then
         return nil, "malformed number"
      end

      repeat
         b = next_byte(state)
      until b == nil or not to_dec(b)
   end

   if not has_digits then
      return nil, "malformed number"
   end

   -- Is it cdata literal?
   if b == BYTE_i or b == BYTE_I then
      -- It is complex literal. Skip "i" or "I".
      next_byte(state)
   else
      -- uint64_t and int64_t literals can not be fractional.
      if not is_float then
         if b == BYTE_u or b == BYTE_U then
            -- It may be uint64_t literal.
            local b1, b2 = sbyte(state.src, state.offset+1, state.offset+2)

            if (b1 == BYTE_l or b1 == BYTE_L) and (b2 == BYTE_l or b2 == BYTE_L) then
               -- It is uint64_t literal.
               next_byte(state, 3)
            end
         elseif b == BYTE_l or b == BYTE_L then
            -- It may be uint64_t or int64_t literal.
            local b1, b2 = sbyte(state.src, state.offset+1, state.offset+2)

            if b1 == BYTE_l or b1 == BYTE_L then
               if b2 == BYTE_u or b2 == BYTE_U then
                  -- It is uint64_t literal.
                  next_byte(state, 3)
               else
                  -- It is int64_t literal.
                  next_byte(state, 2)
               end
            end
         end
      end
   end

   local ty = "number"

   if is_float then
      ty = "float"
   end

   return ty, ssub(state.src, start, state.offset-1)
end


local function lex_ident(state)
   local start = state.offset
   local b = next_byte(state)

   while (b ~= nil) and is_ident_char(b) do
      b = next_byte(state)
   end

   local ident = ssub(state.src, start, state.offset-1)

   if ident == "true" or ident == "false" then
      return "bool", ident
   end

   return "name", ident
end

local function lex_hash(state)
   local b = next_byte(state)
   local start = state.offset

   b = skip_till_newline(state, b)
   local comment_value = ssub(state.src, start, state.offset-1)
   skip_newline(state, b)
   return "comment", comment_value
end

local function lex_slash(state)
   local b = next_byte(state)

   if b == BYTE_STAR then
      -- Long comment.
      b = next_byte(state);
      local start = state.offset
      b = skip_till_comment_end(state, b)
      if b == nil then
         return nil, "expected multiline comment end", b
      end
      local comment_value = ssub(state.src, start, state.offset-2)
      next_byte(state)
      return "comment", comment_value
   elseif b == BYTE_SLASH then
      -- Short comment.
      b = next_byte(state);
      local start = state.offset
      b = skip_till_newline(state, b)
      local comment_value = ssub(state.src, start, state.offset-1)
      skip_newline(state, b)
      return "comment", comment_value
   else
      return "/"
   end
end

local function lex_eq(state)
   next_byte(state)
   return "="
end

local function lex_lt(state)
   local b = next_byte(state)

   if b == BYTE_LT then
      local indented = false
      b = next_byte(state);

      if b == BYTE_DASH then
         indented = true
         b = next_byte(state)
      end

      local start = state.offset
      b = skip_till_newline(state, b)
      local anchor = ssub(state.src, start, state.offset-1)
      -- TODO invalid heredoc anchor characters
      if (slen(anchor) == 0) then
         return nil, "zero-length heredoc anchor"
      end

      local success
      b, success = skip_till_heredoc_end(state, b, anchor)
      local heredoc_value = ssub(state.src, start, state.offset-1) .. "\n"

      if not success then
         return nil, "heredoc anchor not found"
      end

      local buffer = "<<"

      if indented then
         buffer = buffer .. "-"
      end

      return "heredoc", buffer .. heredoc_value
   else
      return "<"
   end
end

local function lex_gt(state)
   next_byte(state)
   return ">"
end

local function lex_dash(state)
   local b = next_byte(state)
   if b ~= nil and to_dec(b) then
      state.offset = state.offset - 1
      b = BYTE_DASH
      return lex_number(state, b)
   end
   return "-"
end

local function lex_dot(state)
   local b = next_byte(state)
   if b ~= nil and to_dec(b) then
      state.offset = state.offset - 1
      b = BYTE_DOT
      return lex_number(state, b)
   end
   return "."
end

local function lex_bracket(state)
   next_byte(state)
   return "["
end

local function lex_any(state, b)
   next_byte(state)
   return schar(b)
end

-- Maps first bytes of tokens to functions that handle them.
-- Each handler takes the first byte as an argument.
-- Each handler stops at the character after the token and returns the token and,
--    optionally, a value associated with the token.
-- On error handler returns nil, error message and, optionally, start of reported location as negative offset.
local byte_handlers = {
   [BYTE_DOT] = lex_dot,
   [BYTE_OBRACK] = lex_bracket,
   [BYTE_QUOTE] = lex_short_string,
   [BYTE_DQUOTE] = lex_short_string,
   [BYTE_HASH] = lex_hash,
   [BYTE_DASH] = lex_dash,
   [BYTE_SLASH] = lex_slash,
   [BYTE_EQ] = lex_eq,
   [BYTE_LT] = lex_lt,
   [BYTE_GT] = lex_gt,
   [BYTE_LDASH] = lex_ident
}

for b=BYTE_0, BYTE_9 do
   byte_handlers[b] = lex_number
end

for b=BYTE_a, BYTE_z do
   byte_handlers[b] = lex_ident
end

for b=BYTE_A, BYTE_Z do
   byte_handlers[b] = lex_ident
end

local function decimal_escaper(char)
   return "\\" .. tostring(sbyte(char))
end

-- Returns quoted printable representation of s.
function Lexer.quote(s)
   return "'" .. s:gsub("[^\32-\126]", decimal_escaper) .. "'"
end

-- Creates and returns lexer state for source.
function Lexer.new_state(src)
   local state = {
      src = src,
      line = 1,
      line_offset = 1,
      offset = 1
   }

   if ssub(src, 1, 2) == "#!" then
      -- Skip shebang.
      skip_newline(state, skip_till_newline(state, next_byte(state, 2)))
   end

   return state
end

function Lexer.next_token(state)
   local b = skip_space(state, sbyte(state.src, state.offset))

   -- Save location of token start.
   local token_line = state.line
   local token_column = state.offset - state.line_offset + 1
   local token_offset = state.offset

   local token, token_value, err_offset, err_end_column

   if b == nil then
      token = "eof"
   else
      token, token_value, err_offset = (byte_handlers[b] or lex_any)(state, b)
   end

   if err_offset then
      local token_body = ssub(state.src, state.offset + err_offset, state.offset)
      token_value = token_value .. " " .. Lexer.quote(token_body)
      token_line = state.line
      token_column = state.offset - state.line_offset + 1 + err_offset
      token_offset = state.offset + err_offset
      err_end_column = token_column + #token_body - 1
   end

   return token, token_value, token_line, token_column, token_offset, err_end_column or token_column
end

return Lexer
