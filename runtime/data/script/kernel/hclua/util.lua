local Util = {}

local class_metatable = {}

function class_metatable.__call(class, ...)
   local obj = setmetatable({}, class)

   if class.__init then
      class.__init(obj, ...)
   end

   return obj
end

function Util.class()
   local class = setmetatable({}, class_metatable)
   class.__index = class
   return class
end

function Util.is_instance(object, class)
   return rawequal(debug.getmetatable(object), class)
end

function Util.read_to_string(file)
   local f = assert(io.open(file, "rb"))
   local content = f:read("*all")
   f:close()
   return content
end

function Util.unprefix(str, prefix)
   if str:sub(1, #prefix) == prefix then
      return str:sub(#prefix + 1)
   else
      return str
   end
end

return Util
