local Chara = Elona.require("Chara")
local Map = Elona.require("Map")
local Item = Elona.require("Item")

return {
   id = "part_time_worker",
   root = "core.locale.talk.unique.part_time_worker",
   nodes = {
      __start = function()
         if not (Map.id() == "core.noyel" and Map.area().christmas_festival) then
            return "__END__"
         end
         if Chara.player().god_id == "core.jure" then
            return "already_believe_in_jure"
         end

         return "dialog"
      end,
      already_believe_in_jure = {
         text = {
            {"already_believe_in_jure"},
         },
      },
      dialog = {
         text = {
            {"dialog"},
         },
         choices = {
            {"confirm", "choices.yes"},
            {"no", "choices.no"}
         },
         default_choice = "no"
      },
      confirm = {
         text = {
            {"yes.dialog"},
         },
         choices = {
            {"convert_to_jure", "yes.choices.yes"},
            {"no", "yes.choices.no"}
         },
         default_choice = "no"
      },
      convert_to_jure = {
         text = {
            {"yes.yes"},
         },
         on_finish = function()
            Item.create(Chara.player().position, "core.jures_body_pillow", 0)
            Chara.player():switch_religion("core.jure")
         end
      },
      no = {
         text = {
            {"no"},
         },
      },
   }
}
