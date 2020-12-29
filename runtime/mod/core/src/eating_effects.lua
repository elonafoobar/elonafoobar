local Chara = ELONA.require("core.Chara")
local FOV = ELONA.require("core.FOV")
local GUI = ELONA.require("core.GUI")
local I18N = ELONA.require("core.I18N")
local Rand = ELONA.require("core.Rand")
local Trait = ELONA.require("core.Trait")
local math = math

local EatingEffects = {}

local function eat_message(eater, locale_id, color)
   local locale_key = "core.food.effect.corpse." .. locale_id
   if FOV.you_see(eater) then
      GUI.txt(I18N.get(locale_key, eater), color)
   end
end

local function mod_resist_chance(eater, elem, chance)
   if Rand.one_in(chance) then
      eater:modify_resistance(elem, 50)
   end
end


function EatingEffects.iron(eater)
   eat_message(eater, "iron", "purple")
   eater:apply_ailment("dimmed", 200)
end

function EatingEffects.deformed_eye(eater)
   eat_message(eater, "deformed_eye", "purple")
   eater:modify_sanity(-25)
   eater:apply_ailment("insane", 500)
end

function EatingEffects.horse(eater)
   eat_message(eater, "horse", "green")
   eater:gain_skill_exp("core.stat_constitution", 100)
end

function EatingEffects.holy_one(eater)
   eat_message(eater, "holy_one", "green")
   eater:modify_sanity(-50)
   mod_resist_chance(eater, "mind", 5)
end

function EatingEffects.at(eater)
   eat_message(eater, "at", "none")
end

function EatingEffects.guard(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "guard", "purple")
   eater:modify_karma(-15)
end

function EatingEffects.vesda(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "vesda", "green")
   eater:modify_resistance("fire", 100)
end

function EatingEffects.insanity(eater)
   eat_message(eater, "insanity", "purple")
   eater:modify_resistance("mind", 50)
   eater:modify_sanity(-500)
   eater:apply_ailment("insane", 1000)
end

function EatingEffects.putit(eater)
   eat_message(eater, "putit", "green")
   eater:gain_skill_exp("core.stat_charisma", 150)
end

function EatingEffects.cupid_of_love(eater)
   eat_message(eater, "cupid_of_love", "green")
   eater:gain_skill_exp("core.stat_charisma", 400)
end


local function eating_effect_poisonous(gain_resist)
   return function(eater)
      eat_message(eater, "poisonous", "purple")
      eater:apply_ailment("poisoned", 100)
      if gain_resist then
         mod_resist_chance(eater, "poison", 6)
      end
   end
end

EatingEffects.cobra = eating_effect_poisonous(true)
EatingEffects.poisonous = eating_effect_poisonous(false)


function EatingEffects.troll(eater)
   eat_message(eater, "troll", "green")
   eater:gain_skill_exp("core.healing", 200)
end

function EatingEffects.rotten_one(eater)
   eat_message(eater, "rotten_one", "purple")
   eater:eat_rotten_food()
end

function EatingEffects.beetle(eater)
   eat_message(eater, "beetle", "green")
   eater:gain_skill_exp("core.stat_strength", 250)
end

function EatingEffects.mandrake(eater)
   eat_message(eater, "mandrake", "green")
   eater:gain_skill_exp("core.meditation", 500)
end

function EatingEffects.grudge(eater)
   eat_message(eater, "grudge", "purple")
   eater:apply_ailment("confused", 200)
end

function EatingEffects.calm(eater)
   eat_message(eater, "calm", "green")
   eater:modify_sanity(20)
end

function EatingEffects.fire_crab(eater)
   EatingEffects.calm(eater)
   mod_resist_chance(eater, "fire", 5)
end

function EatingEffects.fire_centipede(eater)
   mod_resist_chance(eater, "fire", 5)
end

function EatingEffects.yith(eater)
   eat_message(eater, "insanity", "purple")
   eater:modify_sanity(-50)
   mod_resist_chance(eater, "mind", 5)
end

function EatingEffects.lightning(eater)
   eat_message(eater, "lightning", "purple")
   eater:apply_ailment("paralyzed", 300)
end

function EatingEffects.cat(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "cat", "none")
   eater:modify_karma(-5)
end

function EatingEffects.ether(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "ether", "purple")
   Trait.progress_ether_disease_stage(eater, 1000)
end


local function eating_effect_giant(amount)
   return function(eater)
      eat_message(eater, "giant", "green")
      eater:gain_skill_exp("core.stat_constitution", amount)
   end
end

EatingEffects.cyclops = eating_effect_giant(500)
EatingEffects.titan = eating_effect_giant(800)


function EatingEffects.imp(eater)
   eat_message(eater, "imp", "green")
   eater:gain_skill_exp("core.stat_magic", 500)
end

function EatingEffects.hand(eater)
   eat_message(eater, "strength", "green")
   eater:gain_skill_exp("core.stat_strength", 400)
end

function EatingEffects.mammoth(eater)
   eat_message(eater, "strength", "green")
   -- NOTE: doesn't apply anything?
end


local function eating_effect_ghost(amount)
   return function(eater)
      eat_message(eater, "ghost", "green")
      eater:gain_skill_exp("core.stat_will", amount);
   end
end

EatingEffects.ghost = eating_effect_ghost(250)
EatingEffects.nymph = eating_effect_ghost(400)


function EatingEffects.quickling(eater)
   eat_message(eater, "quickling", "green")

   local current = eater:get_skill("core.stat_speed").level
   local amount = math.clamp(2500 - current * current // 10, 20, 2500)
   eater:gain_skill_exp("core.stat_speed", amount);
end

function EatingEffects.alien(eater)
   eat_message(eater, "alien", "none")
   eater:make_pregnant()
end

function EatingEffects.fire_ent(eater)
   mod_resist_chance(eater, "fire", 3)
end

function EatingEffects.ice_ent(eater)
   mod_resist_chance(eater, "cold", 3)
end

function EatingEffects.electric_cloud(eater)
   mod_resist_chance(eater, "lightning", 4)
end

function EatingEffects.chaos_cloud(eater)
   eat_message(eater, "chaos_cloud", "purple")
   eater:apply_ailment("confused", 300)
   mod_resist_chance(eater, "chaos", 5)
end

function EatingEffects.floating_eye(eater)
   EatingEffects.lightning(eater)
   mod_resist_chance(eater, "nerve", 3)
end

function EatingEffects.chaos_eye(eater)
   EatingEffects.lightning(eater)
   mod_resist_chance(eater, "chaos", 3)
end

function EatingEffects.mad_gaze(eater)
   EatingEffects.lightning(eater)
   mod_resist_chance(eater, "mind", 3)
end


local function eating_effect_pumpkin(resist_gain_chance)
   return function(eater)
      mod_resist_chance(eater, "mind", resist_gain_chance)
   end
end

EatingEffects.pumpkin = eating_effect_pumpkin(10)
EatingEffects.greater_pumpkin = eating_effect_pumpkin(8)
EatingEffects.halloween_nightmare = eating_effect_pumpkin(6)


function EatingEffects.stalker(eater)
   mod_resist_chance(eater, "darkness", 4)
end


return EatingEffects
