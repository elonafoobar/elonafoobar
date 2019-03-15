local maps = {}

-- Hardcoded behavior:
-- - creation of character based on quest (puppy's cave)
function maps.puppy_cave(generator)
   print("Generating from Lua")
   generator.generate_nefia()
end

return maps
