local ReadOnly = {}

local function make_read_only_inner(t, seen)
   if seen[t] then return end

   seen[t] = true
   for x, y in pairs(t) do
      if type(x) == "table" then
         if type(y) == "table" then
            t[make_read_only_inner(x, seen)] = make_read_only_inner(y, seen)
         else
            t[make_read_only_inner(x, seen)] = y
         end
      elseif type(y) == "table" then
         t[x] = make_read_only_inner(y, seen)
      end
   end

   local proxy = {}
   local mt = {
      -- hide the actual table being accessed
      __metatable = "read only table",
      __index = function(_, k) return t[k] end,
      __pairs = function() return pairs(t) end,
      __newindex = function (_,k,v)
         error("attempt to update a read-only table (key: " .. tostring(k) .. ", value: " .. tostring(v) .. ")", 2)
      end
   }
   setmetatable(proxy, mt)
   return proxy
end

function ReadOnly.make_read_only(t)
   return make_read_only_inner(t, {})
end

local oldpairs = pairs
function pairs(t)
   local mt = getmetatable(t)
   if mt==nil then
      return oldpairs(t)
   elseif type(mt.__pairs) ~= "function" then
      return oldpairs(t)
   end

   return mt.__pairs()
end

return ReadOnly
