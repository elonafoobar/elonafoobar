local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item
local World = Elona.game.World

local common = require("data/dialog/common")

local function surrender_cost()
   return Chara.player().gold // 5
end

local function surrender()
   GUI.play_sound("core.paygold1")
   Chara.player().gold = Chara.player().gold - surrender_cost()

   for _, item in Item.iter(0, 200) do
      if item.number > 0 and item.prototype.is_cargo then
         GUI.txt(I18N.get("core.talk.npc.common.hand_over", item))
         item:remove()
      end
   end

   Chara.player():refresh_burden_state()
end

return {
   id = "rogue_boss",
   root = "core.talk.unique.rogue_boss",
   nodes = {
      __start = function()
         if Chara.player().gold <= 10 then
            return "too_poor"
         end

         return "ambush"
      end,
      too_poor = {
         text = {
            {"too_poor", args = common.args_speaker}
         },
         choices = {
            {"__END__", "__MORE__"}
         },
      },
      ambush = {
         text = {
            {
               "ambush.dialog",
               args = function(t)
                  return {
                     World.random_title("party"),
                     surrender_cost(),
                     t.speaker
                  }
               end
            },
         },
         choices = {
            {"try_me", "ambush.choices.try_me"},
            {"surrender", "ambush.choices.surrender"},
         }
      },
      try_me = {
         text = {
            {"ambush.try_me", args = common.args_speaker},
         },
      },
      surrender = {
         text = {
            surrender,
            {"ambush.surrender", args = common.args_speaker},
         },
         on_finish = function()
            Internal.leave_map()
            GUI.play_sound("core.exitmap1")
         end
      },
   }
}
