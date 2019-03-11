local Chara = Elona.require("Chara")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local World = Elona.require("World")

local function surrender_cost()
   return Chara.player().gold / 5
end

local function surrender()
   GUI.play_sound("core.paygold1")
   Chara.player().gold = Chara.player().gold - surrender_cost()

   for _, item in Item.iter(0, 200) do
      if item.number > 0 and item.proto.is_cargo then
         GUI.txt(I18N.get("core.locale.talk.npc.common.hand_over", item))
         item:remove()
      end
   end

   Chara.player():refresh_burden_state()
end

return {
   name = "rogue_boss",
   root = "core.locale.talk.unique.rogue_boss",
   nodes = {
      __start = function()
         if Chara.player().gold <= 10 then
            return "too_poor"
         end

         return "ambush"
      end,
      ambush = {
         text = {
            {
               "ambush.dialog",
               args = function(t)
                  return {
                     World.random_title("Party"),
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
            {"ambush.try_me", args = function(t) return {t.speaker} end},
         },
      },
      surrender = {
         text = {
            surrender,
            {"ambush.surrender", args = function(t) return {t.speaker} end},
         },
         on_finish = function()
            Internal.leave_map()
            GUI.play_sound("core.exitmap1")
         end
      },
   }
}
