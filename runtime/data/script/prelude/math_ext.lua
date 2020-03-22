local math_ext = {}
for k, v in pairs(math) do
   math_ext[k] = v
end

local math_min, math_max = math_ext.min, math_ext.max

function math_ext.clamp(n, min, max)
  return math_min(math_max(n, min), max)
end


-- Disable random number generation. Instaed, use core.Random module.
math_ext.random = nil
math_ext.randomseed = nil


return math_ext
