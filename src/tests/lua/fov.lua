require("tests/lua/support/minctest")

local FOV = ELONA.require("core.FOV")

local Chara = ELONA.require("core.Chara")
local Map = ELONA.require("core.Map")

lrun("test FOV.refresh", function()
        Testing.start_in_debug_map()

        local pos = Chara.player().position
        local other = LuaPosition.new(pos.x, pos.y + 5)
        lequal(FOV.you_see(other), true)

        Map.set_tile(pos.x, pos.y + 2, Map.generate_tile("wall"))
        lequal(FOV.you_see(other), true)

        FOV.refresh()
        lequal(FOV.you_see(other), false)
end)

lrun("test FOV.los", function()
        Testing.start_in_debug_map()

        local first = LuaPosition.new(5, 5)
        local second = LuaPosition.new(5, 10)
        lequal(FOV.los(first, second), true)
        lequal(FOV.los(first.x, first.y, second.x, second.y), true)

        Map.set_tile(5, 7, Map.generate_tile("wall"))
        FOV.refresh()
        lequal(FOV.los(first, second), false)
        lequal(FOV.los(first.x, first.y, second.x, second.y), false)
end)

lrun("test FOV.you_see", function()
        Testing.start_in_debug_map()

        local pos = Chara.player().position
        local chara = Chara.create(pos.x, pos.y + 5, "core.putit")
        FOV.refresh()
        lequal(FOV.you_see(chara), true)
        lequal(FOV.you_see(chara.position), true)
        lequal(FOV.you_see(chara.position.x, chara.position.y), true)

        Map.set_tile(pos.x, pos.y + 2, Map.generate_tile("wall"))
        FOV.refresh()
        lequal(FOV.you_see(chara), false)
        lequal(FOV.you_see(chara.position), false)
        lequal(FOV.you_see(chara.position.x, chara.position.y), false)
end)
