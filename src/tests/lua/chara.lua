require "tests/lua/support/minctest"

local Chara = Elona.require("Chara")

lrun("test Chara.is_alive", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "core.putit")
        lequal(Chara.is_alive(putit), true)

        putit:damage_hp(putit.max_hp + 1)
        lequal(Chara.is_alive(putit), false)
end)

lrun("test Chara.is_player", function()
        Testing.start_in_debug_map()

        lequal(Chara.is_player(Chara.player()), true)

        local putit = Chara.create(0, 0, "core.putit")
        lequal(Chara.is_player(putit), false)
end)

lrun("test Chara.is_ally", function()
        Testing.start_in_debug_map()

        lequal(Chara.is_ally(Chara.player()), false)

        local putit = Chara.create(0, 0, "core.putit")
        lequal(Chara.is_ally(putit), false)

        lequal(putit:recruit_as_ally(), true)
        -- TODO: enable this test case.
        -- lequal(Chara.is_ally(putit), true)
end)

lrun("test Chara.count", function()
        Testing.start_in_debug_map()

        Chara.create(0, 0, "core.putit")
        Chara.create(0, 1, "core.putit")

        lequal(Chara.count(), 2)

        Chara.create(0, 2, "core.putit")

        lequal(Chara.count(), 3)
end)

lrun("test Chara.player", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player.index, 0)
end)

lrun("test Chara.create", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(4, 8, "core.putit")
        lok(putit ~= nil, "Character was nil.")
        lequal(putit.position.x, 4)
        lequal(putit.position.y, 8)
end)

local function tally()
   local count = 0
   for _, _ in Chara.iter(0, 245) do
      count = count + 1
   end
   return count
end

lrun("test Chara.iter", function()
        Testing.start_in_debug_map()

        Chara.create(0, 0, "core.putit")
        Chara.create(0, 1, "core.putit")

        local count = tally()

        Chara.create(0, 2, "core.putit")

        lequal(tally(), count + 1)
end)
