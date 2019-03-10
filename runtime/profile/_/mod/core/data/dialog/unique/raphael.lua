local Chara = Elona.require("Chara")
local Input = Elona.require("Input")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local table = Elona.require("table")

local function give_wife(raphael, wife)
   if not table.contains(wife.proto.tags, "man") then
      raphael:apply_ailment("Insane", 1000)
      Chara.player():modify_karma(2)
      return true
   else
      Chara.player():modify_karma(-15)
      return false
   end
end

return {
   name = "raphael",
   root = "core.locale.talk.unique.raphael",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("wife_collector")
         if flag == 0 then
            return "quest_ask"
         elseif flag == 1 or flag == 1000 then
            return "bring_wife"
         end

         return "__IGNORED__"
      end,

      quest_ask = {
         text = {
            {"quest.dialog"}
         },
         choices = {
            {"quest_yes", "quest.choices.yes"},
            {"quest_no", "quest.choices.no"},
         }
      },
      quest_no = {
         text = {
            GUI.show_journal_update_message,
            {"quest.no"},
         },
      },
      quest_yes = {
         text = {
            GUI.show_journal_update_message,
            {"quest.yes"},
         },
         on_finish = function()
            Internal.set_quest_flag("wife_collector", 1)
         end
      },

      bring_wife = {
         text = {
            {"bring_wife.dialog"},
         },
         choices = {
            {"bring_wife_choose", "bring_wife.choices.this_one"},
            {"bring_wife_go_back", "bring_wife.choices.go_back"},
         }
      },
      bring_wife_go_back = {
         text = {
            {"bring_wife.go_back"},
         },
      },
      bring_wife_choose = function(t, state)
         local wife = Input.choose_ally("Sell")
         if wife == nil then
            return "no_such_wife"
         end

         if not wife:get_flag("IsMarried") then
            return "not_married"
         end

         state.wife = wife

         t:say({"bring_wife.this_one.come_along", args = {wife.name}})

         local raphael = t.speaker
         local result = give_wife(raphael, state.wife)

         t.speaker = state.wife
         t:say("bring_wife.this_one.leaving")

         t.speaker = raphael

         if result then
            t:say("bring_wife.this_one.not_human")
         elseif Internal.get_quest_flag("wife_collector") == 1 then
            Item.create(Chara.player().position, "core.gold_piece", 5000)
            GUI.txt(I18N.get("core.locale.quest.completed"))
            GUI.show_journal_update_message()
            Internal.set_quest_flag("wife_collector", 1000)
         end

         return "bring_wife_end"
      end,
      no_such_wife = {
         text = {
            {"bring_wife.this_one.no_such_wife"},
         }
      },
      not_married = {
         text = {
            {"bring_wife.this_one.not_married"},
         }
      },
      bring_wife_end = {
         text = {
            function(_, state)
               state.wife:vanquish()
               GUI.play_sound("core.complete1")
               Item.create(Chara.player().position, "core.unicorn_horn", 2)
               Item.create(Chara.player().position, "core.platinum_coin", 2)
               GUI.txt(I18N.get("core.locale.common.something_is_put_on_the_ground"));
            end,
            {"bring_wife.this_one.end"}
         }
      }
   }
}
