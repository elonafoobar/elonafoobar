local Chara = Elona.require("Chara")
local Enums = Elona.require("Enums")
local FOV = Elona.require("FOV")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Math = Elona.require("Math")
local Skill = Elona.require("Skill")
local Rand = Elona.require("Rand")

local eating_effect = {}

local function eat_message(eater, locale_id, color)
   local locale_key = "core.locale.food.effect.corpse." .. locale_id
   if FOV.you_see(eater) then
      GUI.txtef(color)
      GUI.txt(I18N.get(locale_key, eater))
   end
end

local function mod_resist_chance(eater, elem, chance)
   if Rand.one_in(chance) then
      eater:modify_resistance(elem, 50)
   end
end


function eating_effect.iron(eater)
   eat_message(eater, "iron", Enums.Color.Purple)
   eater:apply_ailment(Enums.StatusAilment.Dimmed, 200)
end

function eating_effect.deformed_eye(eater)
   eat_message(eater, "deformed_eye", Enums.Color.Purple)
   eater:gain_sanity(-25)
   eater:apply_ailment(Enums.StatusAilment.Insane, 500)
end

function eating_effect.horse(eater)
   eat_message(eater, "horse", Enums.Color.Green)
   eater:gain_skill_exp(11, 100)
end

function eating_effect.holy_one(eater)
   eat_message(eater, "holy_one", Enums.Color.Green)
   eater:gain_sanity(-50)
   mod_resist_chance(eater, Enums.Element.Mind, 5)
end

function eating_effect.at(eater)
   eat_message(eater, "at", Enums.Color.None)
end

function eating_effect.guard(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "guard", Enums.Color.Purple)
   eater:modify_karma(-15)
end

function eating_effect.vesda(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "vesda", Enums.Color.Green)
   eater:modify_resistance(Enums.Element.Fire, 100)
end

function eating_effect.insanity(eater)
   eat_message(eater, "insanity", Enums.Color.Purple)
   eater:modify_resistance(Enums.Element.Mind, 50)
   eater:gain_sanity(-500)
   eater:apply_ailment(Enums.StatusAilment.Insane, 1000)
end

function eating_effect.putit(eater)
   eat_message(eater, "putit", Enums.Color.Green)
   eater:gain_skill_exp(17, 150)
end

function eating_effect.cupid_of_love(eater)
   eat_message(eater, "cupid_of_love", Enums.Color.Green)
   eater:gain_skill_exp(17, 400)
end


local function eating_effect_poisonous(gain_resist)
   return function(eater)
      eat_message(eater, "poisonous", Enums.Color.Purple)
      eater:apply_ailment(Enums.StatusAilment.Poisoned, 100)
      if gain_resist then
         mod_resist_chance(eater, Enums.Element.Poison, 6)
      end
   end
end

eating_effect.cobra = eating_effect_poisonous(true)
eating_effect.poisonous = eating_effect_poisonous(false)


function eating_effect.troll(eater)
   eat_message(eater, "troll", Enums.Color.Green)
   eater:gain_skill_exp(154, 200)
end

function eating_effect.rotten_one(eater)
   eat_message(eater, "rotten_one", Enums.Color.Purple)
   eater:eat_rotten_food()
end

function eating_effect.beetle(eater)
   eat_message(eater, "beetle", Enums.Color.Green)
   eater:gain_skill_exp(10, 250)
end

function eating_effect.mandrake(eater)
   eat_message(eater, "mandrake", Enums.Color.Green)
   eater:gain_skill_exp(155, 500)
end

function eating_effect.grudge(eater)
   eat_message(eater, "grudge", Enums.Color.Purple)
   eater:apply_ailment(Enums.StatusAilment.Confused, 200)
end

function eating_effect.calm(eater)
   eat_message(eater, "calm", Enums.Color.Green)
   eater:gain_sanity(20)
end

function eating_effect.fire_crab(eater)
   eating_effect.calm(eater)
   mod_resist_chance(eater, Enums.Element.Fire, 5)
end

function eating_effect.fire_centipede(eater)
   mod_resist_chance(eater, Enums.Element.Fire, 5)
end

function eating_effect.yith(eater)
   eat_message(eater, "insanity", Enums.Color.Purple)
   eater:gain_sanity(-50)
   mod_resist_chance(eater, Enums.Element.Mind, 5)
end

function eating_effect.lightning(eater)
   eat_message(eater, "lightning", Enums.Color.Purple)
   eater:apply_ailment(Enums.StatusAilment.Paralyzed, 300)
end

function eating_effect.cat(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "cat", Enums.Color.None)
   eater:modify_karma(-5)
end

function eating_effect.ether(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "ether", Enums.Color.Purple)
   eater:modify_corruption(1000)
end


local function eating_effect_giant(amount)
   return function(eater)
      eat_message(eater, "giant", Enums.Color.Green)
      eater:gain_skill_exp(11, amount)
   end
end

eating_effect.cyclops = eating_effect_giant(500)
eating_effect.titan = eating_effect_giant(800)


function eating_effect.imp(eater)
   eat_message(eater, "imp", Enums.Color.Green)
   eater:gain_skill_exp(16, 500)
end

function eating_effect.hand(eater)
   eat_message(eater, "strength", Enums.Color.Green)
   eater:gain_skill_exp(10, 400)
end

function eating_effect.mammoth(eater)
   eat_message(eater, "strength", Enums.Color.Green)
   -- NOTE: doesn't apply anything?
end


local function eating_effect_ghost(amount)
   return function(eater)
      eat_message(eater, "ghost", Enums.Color.Green)
      eater:gain_skill_exp(15, amount);
   end
end

eating_effect.ghost = eating_effect_ghost(250)
eating_effect.nymph = eating_effect_ghost(400)


function eating_effect.quickling(eater)
   eat_message(eater, "quickling", Enums.Color.Green)

   local current = Skill.level(18, eater)
   local amount = Math.clamp(2500 - current * current / 10, 20, 2500)
   eater:gain_skill_exp(18, amount);
end

function eating_effect.alien(eater)
   eat_message(eater, "alien", Enums.Color.None)
   eater:make_pregnant()
end

function eating_effect.fire_ent(eater)
   mod_resist_chance(eater, Enums.Element.Fire, 3)
end

function eating_effect.ice_ent(eater)
   mod_resist_chance(eater, Enums.Element.Cold, 3)
end

function eating_effect.electric_cloud(eater)
   mod_resist_chance(eater, Enums.Element.Lightning, 4)
end

function eating_effect.chaos_cloud(eater)
   eat_message(eater, "chaos_cloud", Enums.Color.Purple)
   eater:apply_ailment(Enums.StatusAilment.Confused, 300)
   mod_resist_chance(eater, Enums.Element.Chaos, 5)
end

function eating_effect.floating_eye(eater)
   eating_effect.lightning(eater)
   mod_resist_chance(eater, Enums.Element.Nerve, 3)
end

function eating_effect.chaos_eye(eater)
   eating_effect.lightning(eater)
   mod_resist_chance(eater, Enums.Element.Chaos, 3)
end

function eating_effect.mad_gaze(eater)
   eating_effect.lightning(eater)
   mod_resist_chance(eater, Enums.Element.Mind, 3)
end


local function eating_effect_pumpkin(resist_gain_chance)
   return function(eater)
      mod_resist_chance(eater, Enums.Element.Mind, resist_gain_chance)
   end
end

eating_effect.pumpkin = eating_effect_pumpkin(10)
eating_effect.greater_pumpkin = eating_effect_pumpkin(8)
eating_effect.halloween_nightmare = eating_effect_pumpkin(6)


function eating_effect.stalker(eater)
   mod_resist_chance(eater, Enums.Element.Darkness, 4)
end


return eating_effect
