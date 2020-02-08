local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item

return {
   id = "kaneda_bike",
   root = "core.talk.unique.kaneda_bike",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("blue_capsule_drug")
         if flag >= 3 then
            return "query_join"
         end

         return "check_drug"
      end,

      query_join = {
         text = {
            {"after_drug.dialog"},
         },
         choices = {
            {"query_join_yes", "after_drug.choices.yes"},
            {"query_join_no", "after_drug.choices.no"}
         },
         default_choice = "query_join_no"
      },
      query_join_yes = function()
         if not Chara.can_recruit_allies() then
            return "party_full"
         end

         return "join_party"
      end,
      query_join_no = {
         text = {
            {"after_drug.no"},
         },
      },
      party_full = {
         text = {
            {"after_drug.yes.party_full"},
         },
      },
      join_party = {
         text = {
            {"after_drug.yes.dialog"},
         },
         on_finish = function(t)
            t.speaker:recruit_as_ally()
            Internal.set_quest_flag("blue_capsule_drug", 0)
         end
      },

      check_drug = function()
         if Item.find("core.blue_capsule_drug", "PlayerInventory") ~= nil then
            return "query_give_drug"
         end

         return "do_not_have_drug"
      end,
      query_give_drug = {
         text = {
            {"before_drug.dialog"},
         },
         choices = {
            {"give_drug", "before_drug.choices.yes"},
            {"do_not_have_drug", "before_drug.choices.no"}
         },
         default_choice = "do_not_have_drug"
      },
      give_drug = {
         text = {
            function()
               local drug = Item.find("core.blue_capsule_drug", "PlayerInventory")
               drug.number = drug.number - 1
               GUI.txt(I18N.get("core.talk.unique.kaneda_bike.before_drug.yes.you_hand_him"))
               GUI.play_sound("core.equip1")
            end,
            {"before_drug.yes.dialog"},
         },
         on_finish = function()
            Internal.set_quest_flag("blue_capsule_drug", Internal.get_quest_flag("blue_capsule_drug") + 1)
         end
      },
      do_not_have_drug = {
         text = {
            {"do_not_have_drug"},
         },
      },
   }
}
