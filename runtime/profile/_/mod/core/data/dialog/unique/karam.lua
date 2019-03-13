local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local Map = Elona.require("Map")
local Rand = Elona.require("Rand")

return {
   name = "karam",
   root = "core.locale.talk.unique.karam",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("main_quest")
         if flag == 90 then
            return "dialog"
         end

         return "__IGNORED__"
      end,
      dialog = {
         text = {
            function() Internal.set_quest_flag("main_quest", 100) end,
            {"dialog._0"},
            {"dialog._1"},
            {"dialog._2"},
            {"dialog._3"},
            {"dialog._4"},
            {"dialog._5"},
         },
         on_finish = function(t)
            for i=0,3 do
               Item.create(
                  Chara.player().position,
                  {
                     level = Map.data.current_dungeon_level,
                     quality = "Bad",
                     flttypemajor = Internal.filter_set_dungeon()
                  }
               )
            end
            Item.create(Chara.player().position, "core.gold_piece", Rand.between(1000, 1200))
            Item.create(Chara.player().position, "core.platinum_coin", 3)
            local item = Item.create(Chara.player().position, "core.bejeweled_chest", 0)
            item.param2 = 0
            GUI.show_journal_update_message()
            GUI.txt(I18N.get("core.locale.talk.unique.karam.dies", t.speaker))
            t.speaker:vanquish()
         end
      }
   },
}
