local val = 0

local function value()
   return val
end

local function increment_locally()
   val = val + 1
end

return {
   value = value,
   increment_locally = increment_locally
}
