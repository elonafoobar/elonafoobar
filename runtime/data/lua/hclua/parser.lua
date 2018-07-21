local x = os.clock()
local Lexer = require "hclua.lexer"
local Util = require "hclua.util"

local Parser = {}

local function new_state(src)
   return {
      lexer = Lexer.new_state(src),
      code_lines = {}, -- Set of line numbers containing code.
      line_endings = {}, -- Maps line numbers to "comment", "string", or nil based on whether
                         -- the line ending is within a token.
      comments = {}, -- Array of {comment = string, location = location}.
      hanging_semicolons = {} -- Array of locations of semicolons not following a statement.
   }
end

local function location(state)
   return {
      line = state.line,
      column = state.column,
      offset = state.offset,
   }
end

Parser.SyntaxError = Util.class()

function Parser.SyntaxError:__init(loc, end_column, msg, prev_loc, prev_end_column)
   self.line = loc.line
   self.column = loc.column
   self.end_column = end_column
   self.msg = msg

   if prev_loc then
      self.prev_line = prev_loc.line
      self.prev_column = prev_loc.column
      self.prev_end_column = prev_end_column
   end
end

function Parser.syntax_error(loc, end_column, msg, prev_loc, prev_end_column)
   error(Parser.SyntaxError(loc, end_column, msg, prev_loc, prev_end_column), 0)
end

local function token_body_or_line(state)
   return state.lexer.src:sub(state.offset, state.lexer.offset - 1):match("^[^\r\n]*")
end

local function mark_line_endings(state, first_line, last_line, token_type)
   for line = first_line, last_line - 1 do
      state.line_endings[line] = token_type
   end
end

local function token_name(token)
   return Lexer.quote(token)
end

local function skip_token(state)
   while true do
      local err_end_column
      state.token, state.token_value, state.line,
         state.column, state.offset, err_end_column = Lexer.next_token(state.lexer)

      if not state.token then
         Parser.syntax_error(state, err_end_column, state.token_value)
      elseif state.token == "comment" then
         state.comments[#state.comments+1] = {
            contents = state.token_value,
            location = location(state),
            end_column = state.column + #token_body_or_line(state) - 1
         }

         mark_line_endings(state, state.line, state.lexer.line, "comment")
      else
         if state.token ~= "eof" then
            mark_line_endings(state, state.line, state.lexer.line, "string")
            state.code_lines[state.line] = true
            state.code_lines[state.lexer.line] = true
         end

         break
      end
   end
end

local function init_ast_node(node, loc, tag)
   node.location = loc
   node.tag = tag
   return node
end

local function new_ast_node(state, tag)
   return init_ast_node({}, location(state), tag)
end

local function parse_error(state, msg, prev_loc, prev_end_column)
   local token_repr, end_column

   if state.token == "eof" then
      token_repr = "<eof>"
      end_column = state.column
   else
      token_repr = token_body_or_line(state)
      end_column = state.column + #token_repr - 1
      token_repr = Lexer.quote(token_repr)
   end

   Parser.syntax_error(state, end_column, msg .. " near " .. token_repr, prev_loc, prev_end_column)
end

local function check_token(state, token)
   if state.token ~= token then
      parse_error(state, "expected " .. token_name(token))
   end
end

local function test_and_skip_token(state, token)
   if state.token == token then
      skip_token(state)
      return true
   end
end

local function atom(tag)
   return function(state)
      local ast_node = new_ast_node(state, tag)
      ast_node[1] = state.token_value
      skip_token(state)
      return ast_node
   end
end

local parse_object_list

local simple_expressions = {}

simple_expressions.bool = atom("Boolean")
simple_expressions.hil = atom("HIL")
simple_expressions.string = atom("String")
simple_expressions.number = atom("Number")
simple_expressions.float = atom("Float")
simple_expressions.name = atom("Name")
simple_expressions.heredoc = atom("Heredoc")

simple_expressions["{"] = function(state)
   skip_token(state)
   return parse_object_list(state, nil, true)
end

simple_expressions["["] = function(state)
   local ast_node = new_ast_node(state, "List")
   local need_comma = false
   skip_token(state)

   while true do
      if need_comma then
         if not (state.token == "," or state.token == "]") then
            parse_error(state, "error parsing list, expected comma or list end")
         end
      end

      if state.token == "," then
         skip_token(state)
         if not need_comma then
            parse_error(state, "unexpected comma found while parsing list")
         end
         need_comma = false
      elseif state.token == "]" then
         skip_token(state)
         break
      else
         local literal_handler = simple_expressions[state.token]

         if not literal_handler then
            parse_error(state, "unexpected token while parsing list")
         end

         local rhs = literal_handler(state)
         ast_node[#ast_node+1] = rhs
         need_comma = true
      end
   end

   return ast_node
end

local function parse_object(state)
   local literal_handler = simple_expressions[state.token]

   if not literal_handler then
      parse_error(state, "Unknown token")
   end

   return literal_handler(state)
end

local function parse_object_item(state)
   if state.token == "=" then
      skip_token(state)
      return parse_object(state)
   elseif state.token == "{" then
      return simple_expressions["{"](state)
   else
      parse_error(state, "Expected start of object ('{') or assignment ('=')")
   end
end

local function parse_keys(state)
   local key_count = 0
   local keys = new_ast_node(state, "Keys")

   while true do
      if state.token == "eof" then
         parse_error(state, "end of file reached")
      elseif state.token == "=" then
         if key_count > 1 then
            parse_error(state, "nested object expected: {")
         elseif key_count == 0 then
            parse_error(state, "expected to find at least one object key")
         end

         break
      elseif state.token == "{" then
         if key_count == 0 then
            parse_error(state, "expected identifier or string")
         end

         break
      elseif state.token == "name" or state.token == "string" then
         key_count = key_count + 1
         keys[#keys+1] = simple_expressions[state.token](state)
      else
         parse_error(state, "found invalid token when parsing object keys")
      end
   end

   return keys
end

function parse_object_list(state, loc, is_nested)
   local object_list = {location = loc, tag = "Object"}

   if is_nested == nil then
      is_nested = false
   end

   while state.token ~= "eof" do
      -- We're inside a nested object list, so end at a CBRACE.
      if is_nested and state.token == "}" then
         skip_token(state)
         return object_list
      end

      local keys = parse_keys(state)
      local value = parse_object_item(state)

      -- object lists can be optionally comma-delimited e.g. when a list of maps
      -- is being expressed, so a comma is allowed here - it's simply consumed
      if state.token == "," then
         skip_token(state)
      end

      -- Defer merging of nested maps to the decoding stage.
      local node = init_ast_node({keys, value}, location(state), "Pair")
      object_list[#object_list+1] = node
   end

   if is_nested then
      parse_error(state, "expected end of object list")
   end

   return object_list
end

function Parser.parse(src)
   local state = new_state(src)
   skip_token(state)
   local ast = parse_object_list(state)
   check_token(state, "eof")
   return ast, state.comments, state.code_lines, state.line_endings, state.hanging_semicolons
end

return Parser
