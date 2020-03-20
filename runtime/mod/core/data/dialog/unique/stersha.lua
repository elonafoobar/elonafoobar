local Internal = ELONA.require("core.Internal")

return {
   root = "core.talk.unique.stersha",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("main_quest")
         if flag == 200 then
            return "late"
         elseif flag < 90 then
            return "early"
         else
            return "mid"
         end
      end,
      late = {
         text = {
            {"late"}
         }
      },
      early = {
         text = {
            {"early"}
         }
      },
      mid = {
         text = {
            {"mid"}
         }
      },
   }
}
