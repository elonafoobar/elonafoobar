require("tests/lua/support/minctest")

local Chara = Elona.game.Chara
local Skill = Elona.game.Skill

lrun("test LuaCharacter:damage_hp", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "core.putit")

        putit:damage_hp(1)
        lequal(putit.hp, putit.max_hp - 1)
end)

lrun("test LuaCharacter:recruit_as_ally", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player:recruit_as_ally(), false)

        local putit = Chara.create(0, 0, "core.putit")
        putit:damage_hp(putit.max_hp + 1)
        -- Caller is expected to use Chara.is_alive() to check validity
        -- lequal(putit:recruit_as_ally(), false)

        putit = Chara.create(0, 0, "core.putit")
        lequal(putit:recruit_as_ally(), true)
        lequal(putit:recruit_as_ally(), false)
end)

lrun("test LuaCharacter:get_flag", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "core.putit")
        lequal(putit:get_flag("explodes"), false)

        local kamikaze_yeek = Chara.create(0, 1, "core.kamikaze_yeek")
        lequal(kamikaze_yeek:get_flag("explodes"), true)
end)

lrun("test LuaCharacter:set_flag", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player:get_flag("is_floating"), false)

        player:set_flag("is_floating", true)

        lequal(player:get_flag("is_floating"), true)
end)

lrun("test LuaCharacter:gain_skill_exp", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "core.putit")
        lequal(putit:get_skill("core.attribute_strength").current_level, 4)

        putit:gain_skill_exp("core.attribute_strength", 10000)

        lequal(putit:get_skill("core.attribute_strength").current_level, 14)
end)

lrun("test LuaCharacter:modify_resistance", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "core.putit")
        lequal(Skill.resistance("fire", putit), 100)
        lequal(Skill.resistance("cold", putit), 100)

        putit:modify_resistance("fire", 50)
        putit:modify_resistance("cold", -50)

        lequal(Skill.resistance("fire", putit), 150)
        lequal(Skill.resistance("cold", putit), 50)
end)

assert(lresults())
