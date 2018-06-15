require "tests/lua/support/minctest"

local Chara = Elona.require("Chara")
local Enums = Elona.require("Enums")
local Skill = Elona.require("Skill")

lrun("test LuaCharacter:damage_hp", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, 3)

        putit:damage_hp(1)
        lequal(putit.hp, putit.max_hp - 1)
end)

lrun("test LuaCharacter:recruit_as_ally", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player:recruit_as_ally(), false)

        local putit = Chara.create(0, 0, 3)
        putit:damage_hp(putit.max_hp + 1)
        -- Caller is expected to use Chara.is_alive() to check validity
        -- lequal(putit:recruit_as_ally(), false)

        putit = Chara.create(0, 0, 3)
        lequal(putit:recruit_as_ally(), true)
        lequal(putit:recruit_as_ally(), false)
end)

lrun("test LuaCharacter:set_flag", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(Chara.flag(player, Enums.CharaFlag.IsFloating), false)

        player:set_flag(Enums.CharaFlag.IsFloating, true)

        lequal(Chara.flag(player, Enums.CharaFlag.IsFloating), true)
end)

lrun("test LuaCharacter:gain_skill_exp", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, 3)
        lequal(Skill.level(10, putit), 4)

        putit:gain_skill_exp(10, 10000)

        lequal(Skill.level(10, putit), 14)
end)

assert(lresults())
