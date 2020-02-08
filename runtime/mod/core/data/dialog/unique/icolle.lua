local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item

local common = require("data/dialog/common")

local function give_monster_balls()
   local flag = Internal.get_quest_flag("ambitious_scientist")
   local found = false

   for _, item in Item.iter(0, 200) do
      if flag >= 6 then
         break
      end

      if item.number > 0 and item.id == "core.monster_ball" and item.subname ~= 0 then
         found = true
         while item.number > 0 and flag < 6 do
            GUI.txt(I18N.get("core.talk.unique.icolle.quest.give.deliver", item));
            item.number = item.number - 1
            flag = flag + 1
         end
      end
   end

   Chara.player():refresh_burden_state()

   Internal.set_quest_flag("ambitious_scientist", flag)
   return found
end

return {
   id = "icolle",
   root = "core.talk.unique.icolle",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("ambitious_scientist")
         if flag >= 1000 then
            return "quest_completed"
         elseif flag == 0 then
            return "quest_ask"
         elseif flag >= 1 and flag <= 5 then
            return "quest_check"
         elseif flag >= 6 then
            return "quest_finish"
         end

         return "__IGNORED__"
      end,
      quest_completed = {
         text = {
            {"complete"},
         },
      },
      quest_ask = {
         text = {
            {"quest.dialog"},
         },
         choices = {
            {"quest_yes", "quest.choices.alright"},
            {"quest_no", "__BYE__"}
         },
         default_choice = "quest_no"
      },
      quest_yes = {
         text = {
            function()
               local monster_balls = Item.create(Chara.player().position, {id = "core.monster_ball", nostack = true, number = 6})
               monster_balls.param2 = 5
               GUI.show_journal_update_message()
            end,
            {"quest.alright"},
         },
         on_finish = function()
            Internal.set_quest_flag("ambitious_scientist", 1)
         end
      },
      quest_no = {
         text = {
            {"quest.bye"},
         },
      },
      quest_check = function()
         local gave = give_monster_balls()

         if gave then
            return "quest_give"
         end

         return "quest_waiting"
      end,
      quest_give = {
         text = {
            {"quest.give.have"}
         },
         choices = function()
            if Internal.get_quest_flag("ambitious_scientist") >= 6 then
               return {{"quest_finish", "__BYE__"}}
            end
            return {{"__END__", "__BYE__"}}
         end
      },
      quest_waiting = {
         text = {
            {"quest.give.do_not_have"},
         },
      },
      quest_finish = {
         text = {
            {"quest.end"},
         },
         on_finish = function()
            Item.create(Chara.player().position, "core.gene_machine", 0)
            Item.create(Chara.player().position, "core.gold_piece", 2500)
            Item.create(Chara.player().position, "core.platinum_coin", 2)

            common.quest_completed()

            Internal.set_quest_flag("ambitious_scientist", 1000)
         end
      }
   }
}
