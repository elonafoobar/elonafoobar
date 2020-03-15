local Chara = Elona.game.Chara
local FOV = Elona.game.FOV
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local math = math
local Rand = Elona.game.Rand

local eating_effect = {}

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


function eating_effect.iron(eater)
   eat_message(eater, "iron", "purple")
   eater:apply_ailment("dimmed", 200)
end

function eating_effect.deformed_eye(eater)
   eat_message(eater, "deformed_eye", "purple")
   eater:modify_sanity(-25)
   eater:apply_ailment("insane", 500)
end

function eating_effect.horse(eater)
   eat_message(eater, "horse", "green")
   eater:gain_skill_exp("core.attribute_constitution", 100)
end

function eating_effect.holy_one(eater)
   eat_message(eater, "holy_one", "green")
   eater:modify_sanity(-50)
   mod_resist_chance(eater, "mind", 5)
end

function eating_effect.at(eater)
   eat_message(eater, "at", "none")
end

function eating_effect.guard(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "guard", "purple")
   eater:modify_karma(-15)
end

function eating_effect.vesda(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "vesda", "green")
   eater:modify_resistance("fire", 100)
end

function eating_effect.insanity(eater)
   eat_message(eater, "insanity", "purple")
   eater:modify_resistance("mind", 50)
   eater:modify_sanity(-500)
   eater:apply_ailment("insane", 1000)
end

function eating_effect.putit(eater)
   eat_message(eater, "putit", "green")
   eater:gain_skill_exp("core.attribute_charisma", 150)
end

function eating_effect.cupid_of_love(eater)
   eat_message(eater, "cupid_of_love", "green")
   eater:gain_skill_exp("core.attribute_charisma", 400)
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

eating_effect.cobra = eating_effect_poisonous(true)
eating_effect.poisonous = eating_effect_poisonous(false)


function eating_effect.troll(eater)
   eat_message(eater, "troll", "green")
   eater:gain_skill_exp("core.healing", 200)
end

function eating_effect.rotten_one(eater)
   eat_message(eater, "rotten_one", "purple")
   eater:eat_rotten_food()
end

function eating_effect.beetle(eater)
   eat_message(eater, "beetle", "green")
   eater:gain_skill_exp("core.attribute_strength", 250)
end

function eating_effect.mandrake(eater)
   eat_message(eater, "mandrake", "green")
   eater:gain_skill_exp("core.meditation", 500)
end

function eating_effect.grudge(eater)
   eat_message(eater, "grudge", "purple")
   eater:apply_ailment("confused", 200)
end

function eating_effect.calm(eater)
   eat_message(eater, "calm", "green")
   eater:modify_sanity(20)
end

function eating_effect.fire_crab(eater)
   eating_effect.calm(eater)
   mod_resist_chance(eater, "fire", 5)
end

function eating_effect.fire_centipede(eater)
   mod_resist_chance(eater, "fire", 5)
end

function eating_effect.yith(eater)
   eat_message(eater, "insanity", "purple")
   eater:modify_sanity(-50)
   mod_resist_chance(eater, "mind", 5)
end

function eating_effect.lightning(eater)
   eat_message(eater, "lightning", "purple")
   eater:apply_ailment("paralyzed", 300)
end

function eating_effect.cat(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "cat", "none")
   eater:modify_karma(-5)
end

function eating_effect.ether(eater)
   if not Chara.is_player(eater) then
      return
   end
   eat_message(eater, "ether", "purple")
   eater:modify_corruption(1000)
end


local function eating_effect_giant(amount)
   return function(eater)
      eat_message(eater, "giant", "green")
      eater:gain_skill_exp("core.attribute_constitution", amount)
   end
end

eating_effect.cyclops = eating_effect_giant(500)
eating_effect.titan = eating_effect_giant(800)


function eating_effect.imp(eater)
   eat_message(eater, "imp", "green")
   eater:gain_skill_exp("core.attribute_magic", 500)
end

function eating_effect.hand(eater)
   eat_message(eater, "strength", "green")
   eater:gain_skill_exp("core.attribute_strength", 400)
end

function eating_effect.mammoth(eater)
   eat_message(eater, "strength", "green")
   -- NOTE: doesn't apply anything?
end


local function eating_effect_ghost(amount)
   return function(eater)
      eat_message(eater, "ghost", "green")
      eater:gain_skill_exp("core.attribute_will", amount);
   end
end

eating_effect.ghost = eating_effect_ghost(250)
eating_effect.nymph = eating_effect_ghost(400)


function eating_effect.quickling(eater)
   eat_message(eater, "quickling", "green")

   local current = eater:get_skill("core.attribute_speed").current_level
   local amount = math.clamp(2500 - current * current // 10, 20, 2500)
   eater:gain_skill_exp("core.attribute_speed", amount);
end

function eating_effect.alien(eater)
   eat_message(eater, "alien", "none")
   eater:make_pregnant()
end

function eating_effect.fire_ent(eater)
   mod_resist_chance(eater, "fire", 3)
end

function eating_effect.ice_ent(eater)
   mod_resist_chance(eater, "cold", 3)
end

function eating_effect.electric_cloud(eater)
   mod_resist_chance(eater, "lightning", 4)
end

function eating_effect.chaos_cloud(eater)
   eat_message(eater, "chaos_cloud", "purple")
   eater:apply_ailment("confused", 300)
   mod_resist_chance(eater, "chaos", 5)
end

function eating_effect.floating_eye(eater)
   eating_effect.lightning(eater)
   mod_resist_chance(eater, "nerve", 3)
end

function eating_effect.chaos_eye(eater)
   eating_effect.lightning(eater)
   mod_resist_chance(eater, "chaos", 3)
end

function eating_effect.mad_gaze(eater)
   eating_effect.lightning(eater)
   mod_resist_chance(eater, "mind", 3)
end


local function eating_effect_pumpkin(resist_gain_chance)
   return function(eater)
      mod_resist_chance(eater, "mind", resist_gain_chance)
   end
end

eating_effect.pumpkin = eating_effect_pumpkin(10)
eating_effect.greater_pumpkin = eating_effect_pumpkin(8)
eating_effect.halloween_nightmare = eating_effect_pumpkin(6)


function eating_effect.stalker(eater)
   mod_resist_chance(eater, "darkness", 4)
end


return eating_effect
