local Random = {}

local class = _ENV.prelude.class

--- @native
Random.incdec = _ENV.native.Random.incdec

--- @class
--- Weighted random sampler
local WeightedSampler = class("core.Random.WeightedSampler")

function WeightedSampler:__init()
   self._inner = _ENV.native.Random.WeightedSampler.new()
   self._values = {}
end

--- Adds candidate value with `weight`.
--- @tparam any value
--- @tparam integer weight
function WeightedSampler:add(value, weight)
   self._inner:add(weight)
   self._values[#self._values+1] = value
end

--- Gets one value randomly selected from added candidates.
--- @treturn any? The selected value or `nil` if no value.
function WeightedSampler:get()
   if #self._values == 0 then
      return nil
   else
      return self._values[self._inner:get()]
   end
end

Random.WeightedSampler = WeightedSampler

return Random
