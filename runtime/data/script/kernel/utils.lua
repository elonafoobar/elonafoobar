local utils = {}



function utils.make_singleton(klass, ...)
   local instance = klass.new(...)
   for k, v in pairs(klass) do
      if type(v) == "function" then
         instance[k] = function(...)
            return v(instance, ...)
         end
      end
   end
   return instance
end



return utils
