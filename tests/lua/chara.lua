require "tests/lua/support/minctest"

local Chara = Elona.require("Chara")
local Enums = Elona.require("Enums")

lrun("test Chara.is_alive", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, 3)
        lequal(Chara.is_alive(putit), true)

        putit:damage_hp(putit.max_hp + 1)
        lequal(Chara.is_alive(putit), false)
end)

lrun("test Chara.is_player", function()
        Testing.start_in_debug_map()

        lequal(Chara.is_player(Chara.player()), true)

        local putit = Chara.create(0, 0, 3)
        lequal(Chara.is_player(putit), false)
end)

lrun("test Chara.is_ally", function()
        Testing.start_in_debug_map()

        lequal(Chara.is_ally(Chara.player()), false)

        local putit = Chara.create(0, 0, 3)
        lequal(Chara.is_ally(putit), false)

        putit:recruit_as_ally()
        lequal(Chara.is_ally(putit), true)
end)

lrun("test Chara.flag", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, 3)
        lequal(Chara.flag(putit, Enums.CharaFlag.Explodes), false)

        local kamikaze_yeek = Chara.create(0, 1, 237)
        lequal(Chara.flag(kamikaze_yeek, Enums.CharaFlag.Explodes), true)
end)

lrun("test Chara.player", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player.idx, 0)
end)

lrun("test Chara.create", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(4, 8, 3)
        lok(putit ~= nil, "Character was nil.")
        lequal(putit.position.x, 4)
        lequal(putit.position.y, 8)
end)

assert(lresults())
