local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local table = Elona.require("table")

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
   name = "icolle",
   root = "core.locale.talk.unique.icolle",
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

            GUI.txt(I18N.get("core.locale.quest.completed"))
            GUI.play_sound("core.complete1")
            GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"))
            GUI.show_journal_update_message()
            Internal.set_quest_flag("ambitious_scientist", 1000)
         end
      }
   }
}
