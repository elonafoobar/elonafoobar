local Math = require "math"

Math.randomseed = nil
Math.random = nil

function Math.clamp(n, min, max)
  return Math.min(Math.max(n, min), max)
end

return Math
