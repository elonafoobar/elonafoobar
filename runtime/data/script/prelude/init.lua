local prelude = {}


-- Prelude libraries which are exposed to each mod environment.


-- Lua standard libraries
prelude.assert = assert
prelude.error = error
prelude.ipairs = ipairs
prelude.next = next
prelude.pairs = pairs
prelude.pcall = pcall
prelude.print = print
prelude.select = select
prelude.tonumber = tonumber
prelude.tostring = tostring
prelude.type = type
prelude.xpcall = xpcall

prelude.coroutine = require("prelude.coroutine_ext")
prelude.math = require("prelude.math_ext")
prelude.string = require("prelude.string_ext")
prelude.table = require("prelude.table_ext")
prelude.utf8 = require("prelude.utf8_ext")


-- Additional libraries
prelude.inspect = require("prelude.inspect")
prelude.fun = require("prelude.luafun.fun")



-- Miscellaneous

local pairs, print, type, setmetatable, deepcopy, mathtype, inspect =
   prelude.pairs, prelude.print, prelude.type, _ENV.setmetatable, prelude.table.deepcopy, prelude.math.type, prelude.inspect


function prelude.class(name, Super)
   local Class
   if Super then
      Class = deepcopy(Super)
   else
      Class = {}
   end
   Class.__type = name
   Class.__class = Class
   Class.__super = Super

   Class.new = function(...)
      local self = {}
      setmetatable(self, {__index = Class})
      if Class.__init then
         Class.__init(self, ...)
      end
      return self
   end

   return Class
end


function prelude.xtype(v)
   local ty = type(v)
   if ty == "number" then
      return mathtype(v)
   elseif ty == "table" or ty == "usertype" then
      if v.__type then
         return v.__type
      else
         return ty
      end
   else
      return ty
   end
end


function prelude.p(...)
   print(inspect(...))
end


return prelude
