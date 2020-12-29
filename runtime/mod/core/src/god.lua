local Data = ELONA.require("core.Data")
local Log = ELONA.require("core.Log")
local Rand = ELONA.require("core.Rand")
local math = math
local table = table

local God = {}

--- Get a random god ID or Eyth ("")
--- @treturn string God ID or Eyth ("")
function God.get_random_god_or_eyth()
   local ids = {""} -- Eyth of Infidel
   for k, v in pairs(Data.get_table("core.god")) do
      ids[#ids+1] = k
   end
   return Rand.choice(ids)
end

--- Switch `chara`'s religion to `new_religion`. If `chara` believes `new_religion`, does nothing.
--- @tparam LuaCharacter chara
--- @tparam string new_religion
function God.switch_religion(chara, new_religion)
   if chara.religion == new_religion then
      return
   end

   chara.religion = new_religion

   chara.piety_point = 0
   chara.prayer_point = 500
   chara.piety_rank = 0

   -- TODO
   chara.spacts:lose("core.prayer_of_jure")
   chara.spacts:lose("core.absorb_magic")
   chara.spacts:lose("core.lulwys_trick")

   if chara.religion == "" then
      GUI.txt(I18N.get("core.god.switch.unbeliever"), "orange")
   else
      Animation.play_miracle_animation(Mode.target_one, chara)
      GUI.snd("core.complete1")
      GUI.txt(I18N.get("core.god.switch.follower", God.get_name(chara.religion)), "orange")

      -- TODO
      if chara.religion == "core.itzpalt" then
         chara.spacts:gain("core.absorb_magic")
      elseif chara.religion == "core.jure" then
         chara.spacts:gain("core.prayer_of_jure")
      elseif chara.religion == "core.lulwy" then
         chara.spacts:gain("core.lulwys_trick")
      end

      txtgod(chara.religion, 5)
   end
end

--- Add `chara`'s piety by `amount`
--- @tparam LuaCharacter chara
--- @tparam integer amount
function God.add_piety(chara, amount)
   -- Check the degree of the piety.
   if chara.piety_rank == 4 then
      if chara.piety_point >= 4000 then
         chara.piety_rank = chara.piety_rank + 1
         txtgod(chara.religion, 8)
      end
   end
   if chara.piety_rank == 2 then
      if chara.piety_point >= 2500 then
         chara.piety_rank = chara.piety_rank + 1
         txtgod(chara.religion, 7)
      end
   end
   if chara.piety_rank == 0 then
      if chara.piety_point >= 1500 then
         chara.piety_rank = chara.piety_rank + 1
         txtgod(chara.religion, 7)
      end
   end

   -- Faith skill is not enough.
   if chara.skills:level("core.faith") * 100 < chara.piety_point then
      GUI.txt(I18N.get("core.god.indifferent"))
      return
   end

   -- Modify the piety.
   -- TODO
   -- if Map.current().id == "core.show_house" then
   --    amount = amount // 10
   -- end
   chara.piety_point = chara.piety_point + amount
end

--- Apply god's blessing to `believer`.
--- @tparam LuaCharacter believer
function God.apply_blessing(believer)
   if believer.religion == "" then
      return
   end

   local god_data = Data.get("core.god", believer.religion)
   if not god_data then
      Log.warn("God.apply_blessing: god data of '{$1}' not found", believer.religion)
      return
   end

   local skills = god_data.skills
   if not skills then
      return -- No skill bonus
   end

   local P = believer.piety_point
   local F = believer.skills:level("core.faith")

   for skill_id, bonus_data in pairs(skills) do
      if believer.skills:level(skill_id) > 0 then
         believer.skills:add_level(skill_id,
            math.clamp(P // bonus_data.factor, 1, bonus_data.limit + F // 10))
      end
   end
end

--- Get god's name or Eyth of Infidel.
--- @tparam string id God ID
--- @treturn string Localized god name or Eyth of Infidel if `id` is empty.
function God.get_name(id)
   if id == "" then
      return I18N.get("core.god.eyth_name")
   else
      return I18N.get_data_text("core.god", id, "name")
   end
end

--- Check `offering` is offerable to the god `believer` worships.
--- @tparam LuaItem offering An item
--- @tparam LuaCharacter believer A believer
--- @treturn boolean
function God.is_offerable(offering, believer)
   if believer.religion == "" then
      return false
   end

   local god_data = Data.get("core.god", believer.religion)
   if not god_data then
      Log.warn("God.is_offerable: god data of '{$1}' not found", believer.religion)
      return false
   end

   return not not table.contains(god_data.offerings, offering.id)
end

-- TODO
-- txtgod

return God
