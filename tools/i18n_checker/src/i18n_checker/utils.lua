local utils = {}

utils.dir_sep = package.config:sub(1,1)
utils.is_windows = utils.dir_sep == "\\"

local bom = "\239\187\191"

-- Returns all contents of file (path or file handler) or nil + error message.
function utils.read_file(file)
   local handler

   if type(file) == "string" then
      local open_err
      handler, open_err = io.open(file, "rb")

      if not handler then
         open_err = utils.unprefix(open_err, file .. ": ")
         return nil, "couldn't read: " .. open_err
      end
   else
      handler = file
   end

   local res, read_err = handler:read("*a")
   handler:close()

   if not res then
      return nil, "couldn't read: " .. read_err
   end

   -- Use :len() instead of # operator because in some environments
   -- string library is patched to handle UTF.
   if res:sub(1, bom:len()) == bom then
      res = res:sub(bom:len() + 1)
   end

   return res
end

-- Maps func over array.
function utils.map(func, array)
   local res = {}

   for i, item in ipairs(array) do
      res[i] = func(item)
   end

   return res
end

function utils.filter(tbl, func, ...)
    local newtbl = {}
    local insert = #tbl > 0
    for k, v in pairs(tbl) do
        if func(v, k, ...) then
            if insert then table.insert(newtbl, v)
            else newtbl[k] = v end
        end
    end
    return newtbl
end

function utils.merge(...)
   local arg={...}
   local result = { }
   for _,t in ipairs(arg) do
      if type(t) == "table" then
         for k,v in pairs(t) do
            result[k] = v
         end
      else
         error("invalid value")
      end
   end
   return result
end

function utils.unprefix(str, prefix)
   if str:sub(1, #prefix) == prefix then
      return str:sub(#prefix + 1)
   else
      return str
   end
end

local control_chars_translation = {
  ["\a"] = "\\a",  ["\b"] = "\\b", ["\f"] = "\\f",  ["\n"] = "\\n",
  ["\r"] = "\\r",  ["\t"] = "\\t", ["\v"] = "\\v"
}

local function escape_char(c) return control_chars_translation[c] end

function utils.escape(str)
  local result = str:gsub("\\", "\\\\"):gsub("(%c)", escape_char)
  return result
end

function utils.join_strings(list, delimiter)
   local len = #list
   if len == 0 then
      return ""
   end
   local string = list[1]
   for i = 2, len do
      string = string .. delimiter .. list[i]
   end
   return string
end

function utils.flatten(list)
  if type(list) ~= "table" then return {list} end
  local flat_list = {}
  for _, elem in ipairs(list) do
    for _, val in ipairs(utils.flatten(elem)) do
      flat_list[#flat_list + 1] = val
    end
  end
  return flat_list
end

local class_metatable = {}

function class_metatable.__call(class, ...)
   local obj = setmetatable({}, class)

   if class.__init then
      class.__init(obj, ...)
   end

   return obj
end

function utils.class()
   local class = setmetatable({}, class_metatable)
   class.__index = class
   return class
end

function utils.is_instance(object, class)
   return rawequal(debug.getmetatable(object), class)
end

return utils
