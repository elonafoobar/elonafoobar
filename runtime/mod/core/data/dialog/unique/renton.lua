local Chara = ELONA.require("core.Chara")
local GUI = ELONA.require("core.GUI")
local I18N = ELONA.require("core.I18N")
local Internal = ELONA.require("core.Internal")
local Item = ELONA.require("core.Item")

local common = require("../common.lua")

local function take_books()
   local taken_books = {}
   for _, item in ipairs(Item.player_inventory()) do
      if item.number ~= 0 and item.id == "core.book_of_rachel" and item.param2 >= 1 and item.param2 <= 4 then
         if not taken_books[item.param2] then
            item.number = item.number - 1
            taken_books[item.param2] = true
         end
      end
   end
end

return {
   root = "core.talk.unique.renton",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("rare_books")
         if flag == 1000 then
            return "quest_completed"
         elseif flag == 0 or flag == 1 then
            return "quest_dialog"
         end

         return "__IGNORED__"
      end,
      quest_completed = {
         text = {
            {"complete"},
         },
      },
      quest_dialog = {
         text = {
            {"quest.dialog._0"},
            {"quest.dialog._1"},
            {"quest.dialog._2"},
            {"quest.dialog._3"},
         },
         choices = {
            {"quest_check", "__MORE__"},
         },
      },
      quest_check = function()
         if Internal.get_quest_flag("rare_books") == 0 then
            GUI.show_journal_update_message()
            Internal.set_quest_flag("rare_books", 1)
            return "__END__"
         end

         local found_books = {}
         local total_books = 0
         for _, item in ipairs(Item.player_inventory()) do
            if item.number ~= 0 and item.id == "core.book_of_rachel" and item.param2 >= 1 and item.param2 <= 4 then
               if not found_books[item.param2] then
                  total_books = total_books + 1
                  found_books[item.param2] = true
               end
            end
         end

         if total_books > 0 then
            if total_books ~= 4 then
               return {choice = "quest_brought_some", opts = {total_books}}
            else
               return "quest_finish"
            end
         end
      end,
      quest_brought_some = {
         text = {
            {"quest.brought", args = function(_, _, opts) return opts end},
         },
      },
      quest_finish = {
         text = {
            take_books,
            {"quest.brought_all.dialog._0"},
            {"quest.brought_all.dialog._1"},
            {"quest.brought_all.dialog._2"},
            {"quest.brought_all.dialog._3"},
            {"quest.brought_all.dialog._4"},
            function(t)
               GUI.txt(I18N.get(t.dialog.root .. ".quest.brought_all.ehekatl"), "orange")
            end,
            {"quest.brought_all.dialog._5"},
         },
         on_finish = function()
            Item.create(Chara.player().position, "core.statue_of_lulwy", 0)
            Item.create(Chara.player().position, "core.hero_cheese", 0)
            Item.create(Chara.player().position, "core.gold_piece", 20000)
            Item.create(Chara.player().position, "core.platinum_coin", 5)

            common.quest_completed()

            Internal.set_quest_flag("rare_books", 1000)
         end
      },
   }
}
