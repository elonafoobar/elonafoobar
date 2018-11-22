local Math = Elona.require("Math")
local I18N = Elona.require("I18N")

local function mod_skill(args, id, amount)
   local skill = args.chara:get_skill(id)

   skill.current_level = skill.current_level + amount
end

local function mod_skill_clamp(args, id, amount)
   local skill = args.chara:get_skill(id)

   skill.current_level =
      Math.clamp(skill.current_level + amount,
                 skill.current_level and 1 or 0, 9999)
end

-- TODO: buff icons
data:define_type("buff")
data:add_multi(
   "core.buff",
   {
      {
         name = "holy_shield",
         id = 1,
         buff_type = "Buff",
         duration = function(power)
            return 10 + power // 10
         end,
         on_refresh = function(self, args)
            args.chara.pv = args.chara.pv + self._effect(args.power)
            args.chara.fear = 0
         end,
         _effect = function(power)
            return 25 + power // 15
         end,
         description = function(self, power)
            return I18N.get("core.buff.holy_shield", self._effect(power))
         end
      },
      {
         name = "mist_of_silence",
         id = 2,
         buff_type = "Hex",
         duration = function(power)
            return 5 + power // 40
         end,
         on_refresh = function(self, args)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.mist_of_silence")
         end
      },
      {
         name = "regeneration",
         id = 3,
         buff_type = "Buff",
         duration = function(power)
            return 12 + power // 20
         end,
         on_refresh = function(self, args)
            mod_skill(args, 154, 40)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.regeneration")
         end
      },
      {
         name = "elemental_shield",
         id = 4,
         buff_type = "Buff",
         duration = function(power)
            return 4 + power // 6
         end,
         on_refresh = function(self, args)
            mod_skill(args, 50, 100)
            mod_skill(args, 51, 100)
            mod_skill(args, 52, 100)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.elemental_shield")
         end
      },
      {
         name = "speed",
         id = 5,
         buff_type = "Buff",
         duration = function(power)
            return 8 + power // 30
         end,
         on_refresh = function(self, args)
            mod_skill(args, 18, self._effect(args.power))
         end,
         _effect = function(power)
            return Math.modf(50 + Math.sqrt(power // 5))
         end,
         description = function(self, power)
            return I18N.get("core.buff.speed", self._effect(power))
         end
      },
      {
         name = "slow",
         id = 6,
         buff_type = "Hex",
         duration = function(power)
            return 8 + power // 30
         end,
         on_refresh = function(self, args)
            args.chara:get_skill(18).current_level =
               args.chara:get_skill(18).current_level - self._effect(args.power)
         end,
         _effect = function(power)
            return Math.min(20 + power // 20, 50)
         end,
         description = function(self, power)
            return I18N.get("core.buff.slow", self._effect(power))
         end
      },
      {
         name = "hero",
         id = 7,
         buff_type = "Buff",
         duration = function(power)
            return 10 + power // 4
         end,
         on_refresh = function(self, args)
            mod_skill(args, 10, self._effect(args.power))
            mod_skill(args, 12, self._effect(args.power))
            args.chara.fear = 0
            args.chara.confused = 0
         end,
         _effect = function(power)
            return 5 + power // 30
         end,
         description = function(self, power)
            return I18N.get("core.buff.hero", self._effect(power))
         end
      },
      {
         name = "mist_of_frailness",
         id = 8,
         buff_type = "Hex",
         duration = function(power)
            return 6 + power // 10
         end,
         on_refresh = function(self, args)
            args.chara.dv = args.chara.dv // 2
            args.chara.pv = args.chara.pv // 2
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.mist_of_frailness")
         end
      },
      {
         name = "element_scar",
         id = 9,
         buff_type = "Hex",
         duration = function(power)
            return 4 + power // 15
         end,
         on_refresh = function(self, args)
            mod_skill_clamp(args, 50, -100)
            mod_skill_clamp(args, 51, -100)
            mod_skill_clamp(args, 52, -100)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.element_scar")
         end
      },
      {
         name = "holy_veil",
         id = 10,
         buff_type = "Buff",
         duration = function(power)
            return 15 + power // 5
         end,
         on_refresh = function(self, args)
         end,
         _effect = function(power)
            return 50 + power // 3 * 2
         end,
         description = function(self, power)
            return I18N.get("core.buff.holy_veil", self._effect(power))
         end
      },
      {
         name = "nightmare",
         id = 11,
         buff_type = "Hex",
         duration = function(power)
            return 4 + power // 15
         end,
         on_refresh = function(self, args)
            mod_skill_clamp(args, 58, -100)
            mod_skill_clamp(args, 54, -100)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.nightmare")
         end
      },
      {
         name = "divine_wisdom",
         id = 12,
         buff_type = "Buff",
         duration = function(power)
            return 10 + power // 4
         end,
         on_refresh = function(self, args)
            local a, b = self._effect(args.power)
            mod_skill(args, 14, a)
            mod_skill(args, 16, a)
            mod_skill(args, 150, b)
         end,
         _effect = function(power)
            return 6 + power // 40, 3 + power // 100
         end,
         description = function(self, power)
            return I18N.get("core.buff.divine_wisdom", self._effect(power))
         end
      },
      {
         name = "punishment",
         id = 13,
         buff_type = "Hex",
         duration = function(power)
            return power
         end,
         on_refresh = function(self, args)
            mod_skill(args, 18, -self._effect(args.power))
            if args.chara.pv > 1 then
               args.chara.pv = args.chara.pv // 5
            end
         end,
         _effect = function(power)
            return 20, 20
         end,
         description = function(self, power)
            return I18N.get("core.buff.punishment", self._effect(power))
         end
      },
      {
         name = "lulwys_trick",
         id = 14,
         buff_type = "Buff",
         duration = function(power)
            return 7
         end,
         on_refresh = function(self, args)
            mod_skill(args, 18, self._effect(args.power))
         end,
         _effect = function(power)
            return 155 + power // 5
         end,
         description = function(self, power)
            return I18N.get("core.buff.lulwys_trick", self._effect(power))
         end
      },
      {
         name = "incognito",
         id = 15,
         buff_type = "Buff",
         duration = function(power)
            return 4 + power // 40
         end,
         on_refresh = function(self, args)
            args.chara:set_bit(16, 1)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.incognito")
         end
      },
      {
         name = "death_word",
         id = 16,
         buff_type = "Hex",
         duration = function(power)
            return 20
         end,
         on_refresh = function(self, args)
            args.chara:set_bit(973, 1)
         end,
         _effect = function(power)
            return 0
         end,
         description = function(self, power)
            return I18N.get("core.buff.death_word")
         end
      },
      {
         name = "boost",
         id = 17,
         buff_type = "Buff",
         duration = function(power)
            return 5
         end,
         on_refresh = function(self, args)
            mod_skill(args, 18, self._effect(args.power))
            args.chara:get_skill(10).current_level = args.chara:get_skill(10).current_level * 150 // 100 + 10
            args.chara:get_skill(12).current_level = args.chara:get_skill(12).current_level * 150 // 100 + 10
            mod_skill(args, 154, 50)
            args.chara.pv = args.chara.pv * 150 // 100 + 25
            args.chara.dv = args.chara.dv * 150 // 100 + 25
            args.chara.hit_bonus = args.chara.hit_bonus * 150 // 100 + 50
         end,
         _effect = function(power)
            return 120
         end,
         description = function(self, power)
            return I18N.get("core.buff.boost", self._effect(power))
         end
      },
      {
         name = "contingency",
         id = 18,
         buff_type = "Buff",
         duration = function(power)
            return 66
         end,
         on_refresh = function(self, args)
            args.chara:set_bit(980, 1)
         end,
         _effect = function(power)
            return Math.clamp(25 + power // 17, 25, 80)
         end,
         description = function(self, power)
            return I18N.get("core.buff.contingency", self._effect(power))
         end
      },
      {
         name = "luck",
         id = 19,
         buff_type = "Buff",
         duration = function(power)
            return 777
         end,
         on_refresh = function(self, args)
            mod_skill(args, 19, self._effect(args.power))
         end,
         _effect = function(power)
            return power
         end,
         description = function(self, power)
            return I18N.get("core.buff.luck", self._effect(power))
         end
      },
   }
)

local function register_growth_buff(id, name, growth_buff_index)
   data:add({
      {
         type = "core.buff",
         name = "grow_" .. name,
         id = id,
         buff_type = "Food",
         duration = function(power)
            return 10 + power // 10
         end,
         on_refresh = function(self, args)
            args.chara:set_growth_buff(growth_buff_index, self._effect(args.power))
         end,
         _effect = function(power)
            return power
         end,
         description = function(self, power)
            return I18N.get("core.buff.grow_" .. name, self._effect(power))
         end
      }
   })
end

register_growth_buff(20, "strength", 0)
register_growth_buff(21, "constitution", 1)
register_growth_buff(22, "dexterity", 2)
register_growth_buff(23, "perception", 3)
register_growth_buff(24, "learning", 4)
register_growth_buff(25, "will", 5)
register_growth_buff(26, "magic", 6)
register_growth_buff(27, "charisma", 7)
register_growth_buff(28, "speed", 8)
register_growth_buff(29, "luck", 9)
