local exports = {}


-- Prelude libraries which are exposed to each mod environment.


-- Lua standard libraries
exports.assert = assert
exports.error = error
exports.ipairs = ipairs
exports.next = next
exports.pairs = pairs
exports.pcall = pcall
exports.print = print
exports.select = select
exports.tonumber = tonumber
exports.tostring = tostring
exports.type = type
exports.xpcall = xpcall

exports.coroutine = require("prelude.coroutine_ext")
exports.math = require("prelude.math_ext")
exports.string = require("prelude.string_ext")
exports.table = require("prelude.table_ext")
exports.utf8 = require("prelude.utf8_ext")


-- Additional libraries
exports.inspect = require("prelude.inspect")



-- Miscellaneous

local pairs, print, type, setmetatable, deepcopy, mathtype, inspect =
   exports.pairs, exports.print, exports.type, exports.setmetatable, exports.table.deepcopy, exports.math.type, exports.inspect


function exports.class(name, Super)
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


function exports.xtype(v)
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


function exports.p(...)
   print(inspect(...))
end


-- Inject prelude into `env`.
function exports.import(env)
   for k, v in pairs(exports) do
      if k ~= "import" then
         env[k] = v
      end
   end
end


return exports
