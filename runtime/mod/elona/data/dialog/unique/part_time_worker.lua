local Chara = Elona.game.Chara
local Map = Elona.game.Map
local Item = Elona.game.Item

return {
   id = "part_time_worker",
   root = "elona.talk.unique.part_time_worker",
   nodes = {
      __start = function()
         if not (Map.id() == "elona.noyel" and Map.area().christmas_festival) then
            return "__END__"
         end
         if Chara.player().god_id == "elona.jure" then
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
            Item.create(Chara.player().position, "elona.jures_body_pillow", 0)
            Chara.player():switch_religion("elona.jure")
         end
      },
      no = {
         text = {
            {"no"},
         },
      },
   }
}
