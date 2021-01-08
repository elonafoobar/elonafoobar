local exports = {}

local GLOBAL_RNG = nil

exports.rngs = {
   DefaultGenerator = native.random.DefaultGenerator,
   -- TODO
   -- VanillaGenerator = native.random.VanillaGenerator,
}

-- TODO
-- exports.Dice = native.random.Dice

function exports.global_rng()
   return GLOBAL_RNG
end

function exports.set_global_rng(new_rng)
   local prev_rng = GLOBAL_RNG
   GLOBAL_RNG = new_rng
   return prev_rng
end

function exports.run_with_seed(seed, fn, ...)
   local rng = exports.rngs.DefaultGenerator.new(seed)
   local prev_rng = exports.set_global_rng(rng)
   local result = { pcall(fn, ...) }
   exports.set_global_rng(prev_rng)
   if result[1] then
      for i = 1, #result do
         result[i] = result[i + 1]
      end
      -- return all results of `fn`
      return table.unpack(result)
   else
      -- re-throw error
      error(result[2])
   end

   --[[
   local rng = exports.rngs.DefaultGenerator.new(seed)
   local prev_rng = exports.set_global_rng(rng)
   defer
      exports.set_global_rng(prev_rng)
   end
   return fn(...)
   --]]
end

function exports.run_with_rng(rng, fn, ...)
   local prev_rng = exports.set_global_rng(rng)
   local result = { pcall(fn, ...) }
   exports.set_global_rng(prev_rng)
   if result[1] then
      for i = 1, #result do
         result[i] = result[i + 1]
      end
      -- return all results of `fn`
      return table.unpack(result)
   else
      -- re-throw error
      error(result[2])
   end

   --[[
   local prev_rng = exports.set_global_rng(rng)
   defer
      exports.set_global_rng(prev_rng)
   end
   return fn(...)
   --]]
end

-- Define shorthands.
do
   local FUNCTIONS = {
      "rnd", "rnd_range",
      "rnd_small", "rnd_range_small",
      "frnd", "frnd_01", "frnd_range",
      "one_in", "n_in",
      "percent",
      "roll",
      "choice", "sample",
      "shuffle",
      "set_seed", "seed",
      "incdec",
   }

   for _, function_name in ipairs(FUNCTIONS) do
      -- Forward to the global RNG.
      exports[function_name] = function(...)
         local rng = exports.global_rng()
         return rng[function_name](rng, ...)
      end
   end
end

function exports.__INTERNAL_API_init_global_rng(seed)
   exports.set_global_rng(exports.rngs.DefaultGenerator.new(seed))
end

return exports
