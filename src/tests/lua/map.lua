require "tests/lua/support/minctest"

local Map = Elona.require("Map")
local Enums = Elona.require("Enums")

lrun("test Map.width/Map.height", function()
        Testing.start_in_debug_map()

        lequal(Map.width(), 50)
        lequal(Map.height(), 50)
end)

lrun("test Map.valid", function()
        Testing.start_in_debug_map()

        lequal(Map.valid(LuaPosition.new(0, 0)), true)
        lequal(Map.valid(LuaPosition.new(35, 1)), true)
        lequal(Map.valid(LuaPosition.new(305, 1)), false)
        lequal(Map.valid(LuaPosition.new(-1, 0)), false)

        lequal(Map.valid(0, 0), true)
        lequal(Map.valid(35, 1), true)
        lequal(Map.valid(305, 1), false)
        lequal(Map.valid(-1, 0), false)
end)

lrun("test Map.can_access", function()

        Testing.start_in_debug_map()

        local pos = LuaPosition.new(5, 5)
        lequal(Map.can_access(pos), true)
        lequal(Map.can_access(pos.x, pos.y), true)

        Map.set_tile(5, 5, Map.generate_tile(Enums.TileKind.Wall))
        lequal(Map.can_access(pos), false)
        lequal(Map.can_access(pos.x, pos.y), false)
end)

assert(lresults())
