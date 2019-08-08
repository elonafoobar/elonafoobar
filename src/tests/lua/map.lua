require_relative("tests/lua/support/minctest")

local Map = require("game.Map")
local Enums = require("game.Enums")

lrun("test Map.width/Map.height", function()
        Testing.start_in_debug_map()

        lequal(Map.width(), 50)
        lequal(Map.height(), 50)
end)

lrun("test Map.valid", function()
        -- Testing.start_in_debug_map()

        lequal(Map.valid(LuaPosition.new(0, 0)), true)
        lequal(Map.valid(LuaPosition.new(35, 1)), true)
        lequal(Map.valid(LuaPosition.new(305, 1)), false)
        lequal(Map.valid(LuaPosition.new(-1, 0)), false)

        lequal(Map.valid(0, 0), true)
        lequal(Map.valid(35, 1), true)
        lequal(Map.valid(305, 1), false)
        lequal(Map.valid(-1, 0), false)
end)

lrun("test Map.is_blocked", function()
        -- Testing.start_in_debug_map()

        local pos = LuaPosition.new(5, 5)
        lequal(Map.is_blocked(pos), false)
        lequal(Map.is_blocked(pos.x, pos.y), false)

        Map.set_tile(5, 5, Map.generate_tile(Enums.TileKind.Wall))
        lequal(Map.is_blocked(pos), true)
        lequal(Map.is_blocked(pos.x, pos.y), true)
end)
