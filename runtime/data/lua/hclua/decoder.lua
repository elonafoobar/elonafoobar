local Util = require "hclua.util"

local Decoder = {}

local sfind = string.find
local slen = string.len
local ssub = string.sub
local sgsub = string.gsub
local sgmatch = string.gmatch
local tinsert = table.insert

local function decode_error(ast_node, msg)
   error("decode error: " .. msg)
end

local function check_tag(ast_node, tag)
   if ast_node.tag ~= tag then
      decode_error(ast_node, "expected " .. tag)
   end
end

local decode_object, decode_value

local decode_handlers = {}

decode_handlers["Boolean"] = function(ast_node)
   local value = ast_node[1]

   if value == "true" then
      return true
   elseif value == "false" then
      return false
   end

   decode_error(ast_node, "Unknown boolean value: " .. value)
end

decode_handlers["Number"] = function(ast_node)
   local value = ast_node[1]
   return tonumber(value)
end

decode_handlers["Float"] = decode_handlers["Number"]

decode_handlers["String"] = function(ast_node)
   return ast_node[1]
end

decode_handlers["Name"] = decode_handlers["String"]
decode_handlers["HIL"] = decode_handlers["String"]
decode_handlers["List"] = function(ast_node)
   local list = {}

   for i=1,#ast_node do
      list[i] = decode_value(ast_node[i])
   end

   return list
end

local function join_strings(list, delimiter)
   local len = #list
   if len == 0 then
      return ""
   end
   local result = list[1]
   for i = 2, len do
      result = result .. delimiter .. list[i]
   end
   return result
end

decode_handlers["Heredoc"] = function(ast_node)
   local text = ast_node[1]

   -- We need to find the end of the marker
   local anchor_end = sfind(text, "\n")
   if anchor_end == nil then
      decode_error(ast_node, "heredoc doesn't contain newline")
   end

   local content_begin = anchor_end + 1
   local content_end = slen(text) - content_begin - (anchor_end - 2)

   local unindent = ssub(text, 3, 3) == "-"

   -- We can optimize if the heredoc isn't marked for indentation
   if not unindent then
      return ssub(text, content_begin, content_begin + content_end)
   end

   -- We need to unindent each line based on the indentation level of the marker
   local content = ssub(text, content_begin, content_begin + content_end + 1)
   local lines = {}
   for line in sgmatch(content, "([^\n]*)\n?") do
      tinsert(lines, line)
   end

   local whitespace_prefix = lines[#lines]

   local indented = true
   for _, line in pairs(lines) do
      if slen(whitespace_prefix) > slen(line) then
         indented = false
         break
      end

      local prefix_found = Util.unprefix(line, whitespace_prefix) ~= line

      if not prefix_found then
         indented = false
         break
      end
   end

   -- If all lines are not at least as indented as the terminating mark, return the
   -- heredoc as is, but trim the leading space from the marker on the final line.
   if not indented then
      local function trim_right(s)
         local n = #s
         while n > 0 and s:find("^%s", n) do n = n - 1 end
         return ssub(s, 1, n)
      end

      return trim_right(content) .. "\n"
   end

   local unindented_lines = {}
   for i=1, #lines do
      if i == #lines then
         unindented_lines[i] = ""
         break
      end

      local line = lines[i]
      unindented_lines[i] = Util.unprefix(line, whitespace_prefix)
   end

   return join_strings(unindented_lines, "\n")
end

decode_handlers["Object"] = function(ast_node)
   return decode_object(ast_node)
end

function decode_value(ast_node)
   local decode_handler = decode_handlers[ast_node.tag]

   if not decode_handler then
      decode_error(ast_node, "Unknown literal: " .. ast_node.tag)
   end

   return decode_handler(ast_node)
end

local function is_list(state)
   return type(state) == "table" and state[1] ~= nil
end

local function is_object(state)
   return type(state) == "table" and not is_list(state)
end

local function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

local function recurse_objects(a, b, keys)
   local a_child = deepcopy(a)
   local b_child = deepcopy(b)

   for _, key in pairs(keys) do
      a_child = a_child[key]
      b_child = b_child[key]
   end

   return a_child, b_child
end

-- Checks down the list of keys provided in nested fashion.
local function objects_share_keys(a, b, keys)
   for key, value in pairs(b) do
      if a[key] then
         return true
      end
   end

   return false
end

local function set_object_nested(this, value, keys)
   local key

   assert(#keys > 0)

   if #keys == 1 then
      this[keys[#keys]] = value
      return
   end

   local this_parent = this[keys[1]]

   for i=2, #keys-1 do
     this_parent = this_parent[keys[i]]
   end

   this_parent[keys[#keys]] = value
end

local function merge_objects(this, other, keys)
   if this == other then
      decode_error("merge_objects was called on the same object: " .. tostring(this))
   end

   if not (is_object(this) and is_object(other)) then
      decode_error("merge_objects was called with non-objects: "
                      .. tostring(this) .. " " .. tostring(other))
   end

   for key, value in pairs(other) do
      local tmp = this[key]
      if tmp then
         if is_object(tmp) and is_object(value) then
            merge_objects(tmp, value)
         else
            this[key] = value
         end
      else
         this[key] = value
      end
   end
end

local function object_length(object)
  local count = 0
  for _ in pairs(object) do count = count + 1 end
  return count
end

local function object_common_nested_keys(a, b)
   local a_child = deepcopy(a)
   local b_child = deepcopy(b)
   local keys = {}
   local finished = false

   while not finished do
      if object_length(a_child) ~= 1 or object_length(b_child) ~= 1 then
         break
      end

      for k, v in pairs(a_child) do
         if b_child[k] == nil then
            finished = true
            break
         end
         if type(a_child[k]) ~= "table" or type(b_child[k]) ~= "table" then
            finished = true
            break
         end

         keys[#keys+1] = k
         a_child = a_child[k]
         b_child = b_child[k]
         break
      end
   end

   return keys, a_child, b_child
end

local function expand_objects(this, other, keys)
   local this_child, other_child = recurse_objects(this, other, keys)

   local list = {}
   list[1] = this_child
   list[2] = other_child
   set_object_nested(this, list, keys)
end

local function merge_object_lists(this, other, keys)
   local this_child, other_child = recurse_objects(this, other, keys)
   local list, object

   if is_object(this_child) and is_list(other_child) then
      object = this_child
      list = other_child
   elseif is_list(this_child) and is_object(other_child) then
      object = other_child
      list = this_child
   else
      assert(is_list(this_child) and is_list(other_child))
   end

   if list == nil then
      for _, v in pairs(this_child) do
         other_child[#other_child+1] = v
      end

      set_object_nested(this, other_child, keys)
   else
      list[#list+1] = object
      set_object_nested(this, list, keys)
   end
end

local function decode_object_pair(ast_node, object)
   check_tag(ast_node, "Pair")
   local value = decode_value(ast_node[2])

   local keys = ast_node[1]
   check_tag(keys, "Keys")
   local parent = {}
   local nested = parent
   if #keys > 1 then
      for i=2,#keys-1 do
         local key = keys[i][1]
         nested[key] = {}
         nested = nested[key]
      end
      nested[keys[#keys][1]] = value
      value = parent
   end

   local first_key = keys[1][1]
   local existing = object[first_key]
   local expand = false

   if existing then
      if is_list(existing) then
         -- This is an object list. Add the object.
         existing[#existing+1] = value
      else
         -- We tried assigning to a value that exists already.
         -- First, attempt to see if this is an object.
         if is_object(existing) then
            if not is_object(value) then
               -- We tried assigning a non-object to an existing object.
               -- (The list case was checked above.) Expand it into a
               -- list.
               expand = true;
            else
               -- If the objects share any keys at some nested level
               -- of size 1, see if those two levels share any keys.
               -- If they do, expand into a list at that level. Else,
               -- merge the objects at that level.
               local keys, a, b = object_common_nested_keys(existing, value)
               if a[1] ~= nil or b[1] ~= nil then
                  merge_object_lists(existing, value, keys)
               elseif objects_share_keys(a, b, keys) then
                  if #keys == 0 then
                     expand = true
                  else
                     expand_objects(existing, value, keys)
                  end
               else
                  merge_objects(existing, value, keys)
                  object[first_key] = existing
               end
            end
         else
            -- We tried assigning something to a non-object.
            -- Expand it into a list.
            expand = true;
         end

         if expand then
            local list = {}
            list[1] = existing
            list[2] = value
            object[first_key] = list
         end
      end
   else
      object[first_key] = value
   end
end

function decode_object(ast_node)
   local object = {}

   for i=1,#ast_node do
      local pair = ast_node[i]
      decode_object_pair(pair, object)
   end

   return object
end

function Decoder.decode(ast)
   check_tag(ast, "Object")
   return decode_object(ast)
end

return Decoder
