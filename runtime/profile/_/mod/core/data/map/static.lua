local map = {}

-- Hardcoded behavior:
-- - creation of character based on quest (puppy's cave)
function map.puppy_cave(generator)
   generator.generate_nefia()
end

return map
