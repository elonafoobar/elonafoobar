require("tests/lua/support/minctest")

local Chara = Elona.game.Chara
local Enums = Elona.game.Enums
local Skill = Elona.game.Skill

lrun("test LuaCharacter:damage_hp", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "elona.putit")

        putit:damage_hp(1)
        lequal(putit.hp, putit.max_hp - 1)
end)

lrun("test LuaCharacter:recruit_as_ally", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player:recruit_as_ally(), false)

        local putit = Chara.create(0, 0, "elona.putit")
        putit:damage_hp(putit.max_hp + 1)
        -- Caller is expected to use Chara.is_alive() to check validity
        -- lequal(putit:recruit_as_ally(), false)

        putit = Chara.create(0, 0, "elona.putit")
        lequal(putit:recruit_as_ally(), true)
        lequal(putit:recruit_as_ally(), false)
end)

lrun("test LuaCharacter:get_flag", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "elona.putit")
        lequal(putit:get_flag("Explodes"), false)

        local kamikaze_yeek = Chara.create(0, 1, "elona.kamikaze_yeek")
        lequal(kamikaze_yeek:get_flag("Explodes"), true)
end)

lrun("test LuaCharacter:set_flag", function()
        Testing.start_in_debug_map()

        local player = Chara.player()
        lequal(player:get_flag("IsFloating"), false)

        player:set_flag("IsFloating", true)

        lequal(player:get_flag("IsFloating"), true)
end)

lrun("test LuaCharacter:gain_skill_exp", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "elona.putit")
        lequal(putit:get_skill("elona.attribute_strength").current_level, 4)

        putit:gain_skill_exp("elona.attribute_strength", 10000)

        lequal(putit:get_skill("elona.attribute_strength").current_level, 14)
end)

lrun("test LuaCharacter:modify_resistance", function()
        Testing.start_in_debug_map()

        local putit = Chara.create(0, 0, "elona.putit")
        lequal(Skill.resistance(Enums.Element.Fire, putit), 100)
        lequal(Skill.resistance(Enums.Element.Cold, putit), 100)

        putit:modify_resistance(Enums.Element.Fire, 50)
        putit:modify_resistance(Enums.Element.Cold, -50)

        lequal(Skill.resistance(Enums.Element.Fire, putit), 150)
        lequal(Skill.resistance(Enums.Element.Cold, putit), 50)
end)

assert(lresults())
