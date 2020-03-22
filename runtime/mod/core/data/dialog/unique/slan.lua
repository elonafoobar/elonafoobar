local Chara = ELONA.require("core.Chara")
local GUI = ELONA.require("core.GUI")
local I18N = ELONA.require("core.I18N")
local Internal = ELONA.require("core.Internal")
local Item = ELONA.require("core.Item")
local Map = ELONA.require("core.Map")
local Rand = ELONA.require("core.Rand")

return {
   root = "core.talk.unique.slan",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("main_quest")
         if flag == 20 then
            return "dialog"
         end

         return "__IGNORED__"
      end,
      dialog = {
         text = {
            function() Internal.set_quest_flag("main_quest", 30) end,
            {"dialog._0"},
            {"dialog._1"},
            {"dialog._2"},
         },
         on_finish = function(t)
            for i=0,3 do
               Item.create(
                  Chara.player().position,
                  {
                     level = Map.data.current_dungeon_level,
                     quality = "bad",
                     flttypemajor = Internal.filter_set_dungeon()
                  }
               )
            end
            Item.create(Chara.player().position, "core.gold_piece", Rand.between(1000, 1200))
            Item.create(Chara.player().position, "core.platinum_coin", 3)
            local item = Item.create(Chara.player().position, "core.bejeweled_chest", 0)
            item.param2 = 0
            GUI.play_sound("core.write1")
            GUI.txt(I18N.get("core.talk.unique.slan.you_receive"))
            GUI.txt(I18N.get("core.talk.unique.slan.dies", t.speaker))
            t.speaker:vanquish()
         end
      }
   }
}
