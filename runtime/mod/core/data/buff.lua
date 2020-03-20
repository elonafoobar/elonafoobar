local Chara = ELONA.require("core.Chara")
local math = math
local I18N = ELONA.require("core.I18N")

local function mod_skill_level(args, id, amount)
   local skill = args.chara:get_skill(id)

   skill.current_level = skill.current_level + amount
end

local function mod_skill_level_clamp(args, id, amount)
   local skill = args.chara:get_skill(id)

   skill.current_level =
      math.clamp(skill.current_level + amount,
                 skill.current_level and 1 or 0, 9999)
end

local function get_description(self, power)
   return I18N.get_enum_property("core.buff", "description", self.legacy_id, self._effect(power))
end

--[[
List of fields:

buff_type:
   indicates if the buff has a positive or negative
   effect. If the buff is of type "hex" and is obtained from an item,
   the buff will gain more power if the item is cursed (power = power
   * 150 / 100), and less if it is blessed (power = 50). Vice-versa
   for the other buff types.
      - If buff_type is "buff", the buff animation is played on gain.
      - If the buff type is "food", it will be lost if the bearer vomits.
      - If buff_type is "hex":
         + The debuff animation is played on gain.
         + Any instance of it will be considered a target for removal in
           Holy Light/Vanquish Hex.
         + The target of the buff can potentially resist gaining it
           through skills/traits.
duration:
   function taking a power level which returns the number of turns the
   buff lasts.
on_refresh:
   function for applying the effects of the buff. The effects are
   applied on character refresh, so the state of the character will be
   reset before applying. It takes two arguments, "self" which is the
   buff definition itself and "args", a table with these fields:
      - power: buff power.
      - chara: character which the buff is being applied to.
on_removal:
   function which is run when the buff expires. It takes two
   arguments, "self" and the "args" table, with these fields:
      - chara: character which the buff was applied to.
description:
   function for returning the localized buff description. It takes two
   arguments, "self" and "power", the buff's power. It can be used for
   passing additional arguments to be used in the localized string,
   primarily the buff's calculated power.

_effect isn't strictly necessary, but it is typically used for
calculating the actual effect from the buff's power, and displaying it
in the description.
]]

-- TODO: buff icons
data:define_prototype("buff")
data:add(
   "core.buff",
   {
      holy_shield = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Attempts to apply fear will be ignored.
         legacy_id = 1,
         buff_type = "buff",
         duration = function(power)
            return 10 + power // 10
         end,
         on_refresh = function(self, args)
            args.chara.pv = args.chara.pv + self._effect(args.power)
            args.chara:heal_ailment("fear", 0)
         end,
         _effect = function(power)
            return 25 + power // 15
         end,
         description = get_description
      },
      mist_of_silence = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Silence behavior.
         legacy_id = 2,
         buff_type = "hex",
         duration = function(power)
            return 5 + power // 40
         end,
         on_refresh = function(_self, _args)
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      regeneration = {
         legacy_id = 3,
         buff_type = "buff",
         duration = function(power)
            return 12 + power // 20
         end,
         on_refresh = function(_self, args)
            mod_skill_level(args, "core.healing", 40)
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      elemental_shield = {
         legacy_id = 4,
         buff_type = "buff",
         duration = function(power)
            return 4 + power // 6
         end,
         on_refresh = function(_self, args)
            mod_skill_level(args, "core.element_fire", 100)
            mod_skill_level(args, "core.element_cold", 100)
            mod_skill_level(args, "core.element_lightning", 100)
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      speed = {
         legacy_id = 5,
         buff_type = "buff",
         duration = function(power)
            return 8 + power // 30
         end,
         on_refresh = function(self, args)
            mod_skill_level(args, "core.attribute_speed", self._effect(args.power))
         end,
         _effect = function(power)
            return math.modf(50 + math.sqrt(power // 5))
         end,
         description = get_description
      },
      slow = {
         legacy_id = 6,
         buff_type = "hex",
         duration = function(power)
            return 8 + power // 30
         end,
         on_refresh = function(self, args)
            args.chara:get_skill("core.attribute_speed").current_level =
               args.chara:get_skill("core.attribute_speed").current_level - self._effect(args.power)
         end,
         _effect = function(power)
            return math.min(20 + power // 20, 50)
         end,
         description = get_description
      },
      hero = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Attempts to apply confusion or fear will be ignored.
         legacy_id = 7,
         buff_type = "buff",
         duration = function(power)
            return 10 + power // 4
         end,
         on_refresh = function(self, args)
            mod_skill_level(args, "core.attribute_strength", self._effect(args.power))
            mod_skill_level(args, "core.attribute_dexterity", self._effect(args.power))
            args.chara:heal_ailment("fear", 0)
            args.chara:heal_ailment("confused", 0)
         end,
         _effect = function(power)
            return 5 + power // 30
         end,
         description = get_description
      },
      mist_of_frailness = {
         legacy_id = 8,
         buff_type = "hex",
         duration = function(power)
            return 6 + power // 10
         end,
         on_refresh = function(_self, args)
            args.chara.dv = args.chara.dv // 2
            args.chara.pv = args.chara.pv // 2
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      element_scar = {
         legacy_id = 9,
         buff_type = "hex",
         duration = function(power)
            return 4 + power // 15
         end,
         on_refresh = function(_self, args)
            mod_skill_level_clamp(args, "core.element_fire", -100)
            mod_skill_level_clamp(args, "core.element_cold", -100)
            mod_skill_level_clamp(args, "core.element_lightning", -100)
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      holy_veil = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Additional chance to resist if a hex is applied to this
         --    character.
         legacy_id = 10,
         buff_type = "buff",
         duration = function(power)
            return 15 + power // 5
         end,
         on_refresh = function(_self, _args)
         end,
         _effect = function(power)
            return 50 + power // 3 * 2
         end,
         description = get_description
      },
      nightmare = {
         legacy_id = 11,
         buff_type = "hex",
         duration = function(power)
            return 4 + power // 15
         end,
         on_refresh = function(_self, args)
            mod_skill_level_clamp(args, "core.element_nerve", -100)
            mod_skill_level_clamp(args, "core.element_mind", -100)
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      divine_wisdom = {
         legacy_id = 12,
         buff_type = "buff",
         duration = function(power)
            return 10 + power // 4
         end,
         on_refresh = function(self, args)
            local a, b = self._effect(args.power)
            mod_skill_level(args, "core.attribute_learning", a)
            mod_skill_level(args, "core.attribute_magic", a)
            mod_skill_level(args, "core.literacy", b)
         end,
         _effect = function(power)
            return 6 + power // 40, 3 + power // 100
         end,
         description = get_description
      },
      punishment = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Ignored when removing status effects on a character.
         --  + Ignored when casting Holy Light/Vanquish Hex.
         legacy_id = 13,
         buff_type = "hex",
         duration = function(power)
            return power
         end,
         on_refresh = function(self, args)
            mod_skill_level(args, "core.attribute_speed", -self._effect(args.power))
            if args.chara.pv > 1 then
               args.chara.pv = args.chara.pv // 5
            end
         end,
         _effect = function(_power)
            return 20, 20
         end,
         description = get_description
      },
      lulwys_trick = {
         legacy_id = 14,
         buff_type = "buff",
         duration = function(_power)
            return 7
         end,
         on_refresh = function(self, args)
            mod_skill_level(args, "core.attribute_speed", self._effect(args.power))
         end,
         _effect = function(power)
            return 155 + power // 5
         end,
         description = get_description
      },
      incognito = {
         -- NOTE: The initial incognito effect is applied by the
         -- incognito spell when it is cast, but the effect when the
         -- buff expires is handled by the buff itself.
         legacy_id = 15,
         buff_type = "buff",
         duration = function(power)
            return 4 + power // 40
         end,
         on_refresh = function(_self, args)
            args.chara:set_flag("is_incognito", true)
         end,
         on_removal = function(_self, args)
            if not Chara.is_player(args.chara) then
               return
            end
            for _, chara in Chara.iter(16, 245) do
               if Chara.is_alive(chara) then
                  if chara.role == 14 and Chara.player().karma < -30 then
                     chara.relationship = "aggressive"
                     chara.hate = 80
                     chara.emotion_icon = 218
                  end
               end
            end
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      death_word = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Inflicts 9999 damage when it expires, but outside of
         --    buff_delete().
         --  + On application, will always be resisted if character is
         --    of "miracle" or "godly" quality.
         --  + Removed when a character with the "is_death_master" flag
         --    is killed.
         legacy_id = 16,
         buff_type = "hex",
         duration = function(_power)
            return 20
         end,
         on_refresh = function(_self, args)
            args.chara:set_flag("is_sentenced_daeth", true)
         end,
         on_removal = function(_self, args)
            args.chara:set_flag("is_sentenced_daeth", false)
         end,
         _effect = function(_power)
            return 0
         end,
         description = get_description
      },
      boost = {
         legacy_id = 17,
         buff_type = "buff",
         duration = function(_power)
            return 5
         end,
         on_refresh = function(self, args)
            mod_skill_level(args, "core.attribute_speed", self._effect(args.power))
            args.chara:get_skill("core.attribute_strength").current_level =
               args.chara:get_skill("core.attribute_strength").current_level * 150 // 100 + 10
            args.chara:get_skill("core.attribute_dexterity").current_level =
               args.chara:get_skill("core.attribute_dexterity").current_level * 150 // 100 + 10
            mod_skill_level(args, "core.healing", 50)
            args.chara.pv = args.chara.pv * 150 // 100 + 25
            args.chara.dv = args.chara.dv * 150 // 100 + 25
            args.chara.hit_bonus = args.chara.hit_bonus * 150 // 100 + 50
         end,
         _effect = function(_power)
            return 120
         end,
         description = get_description
      },
      contingency = {
         -- NOTE: Has these hardcoded behaviors.
         --  + Check for lethal damage and chance to heal. If the
         --    "is_contracting_with_reaper" flag is set then the buff is
         --    expected to be be active on the same character.
         legacy_id = 18,
         buff_type = "buff",
         duration = function(_power)
            return 66
         end,
         on_refresh = function(_self, args)
            args.chara:set_flag("is_contracting_with_reaper", true)
         end,
         on_removal = function(_self, args)
            args.chara:set_flag("is_contracting_with_reaper", false)
         end,
         _effect = function(power)
            return math.clamp(25 + power // 17, 25, 80)
         end,
         description = get_description
      },
      luck = {
         legacy_id = 19,
         buff_type = "buff",
         duration = function(_power)
            return 777
         end,
         on_refresh = function(self, args)
            mod_skill_level(args, "core.attribute_luck", self._effect(args.power))
         end,
         _effect = function(power)
            return power
         end,
         description = get_description
      },
   }
)

local function register_growth_buff(attribute_index, attribute_name)
   data:add(
      "core.buff",
      {
         ["grow_" .. attribute_name] = {
            legacy_id = attribute_index + 20,
            buff_type = "food",
            duration = function(power)
               return 10 + power // 10
            end,
            on_refresh = function(self, args)
               args.chara:set_growth_buff(attribute_index, self._effect(args.power))
            end,
            _effect = function(power)
               return power
            end,
            description = get_description
         }
      }
   )
end


-- These buffs will be applied when a piece of equipment with a
-- corresponding attribute preservation enchantment is eaten. The buff
-- applied depends on the integer ID of the preserved attribute, so
-- only the attribute IDs from 0-9 are valid.
register_growth_buff(0, "strength")
register_growth_buff(1, "constitution")
register_growth_buff(2, "dexterity")
register_growth_buff(3, "perception")
register_growth_buff(4, "learning")
register_growth_buff(5, "will")
register_growth_buff(6, "magic")
register_growth_buff(7, "charisma")
register_growth_buff(8, "speed")
register_growth_buff(9, "luck")
