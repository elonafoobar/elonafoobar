ELONA.i18n:add {
   blending = {
      rate_panel = {
         success_rate = "Success Rate: {$1}",
         required_turns = "Time: {$1} turn{s($1)}",
         required_turns_and_hours = "Time: {$1} turn{s($1)} and {$2} hour{s($2)}",
      },

      window = {
         procedure = "Blending Procedure",
         choose_a_recipe = "Choose a recipe",
         chose_the_recipe_of = "Chose the recipe of {$1}",
         add = "Add {$1}(Stock:{$2})",
         selected = "Selected {itemname($1)}",
         start = "Start blending!",
         the_recipe_of = "The recipe of {$1}",
         required_skills = "Required Skills:",
         required_equipment = "Required equipment:",
         havent_identified = "You haven't identified it yet.",
         no_inherited_effects = "No inherited effects",
      },

      prompt = {
         how_many = "How many items do you want to create?",
         start = "Start blending",
         go_back = "Go back",
         from_the_start = "From the start",
      },

      recipe = {
         title = "Choose a recipe",
         name = "Name",
         hint = "[Page]  ",

         warning = "(*) The feature is not implemented yet.",
         which = "Which recipe do you want to use?",
         counter = "{$1} recipes",
         of = "Recipe of {$1}",
      },

      steps = {
         add_ingredient = "Add \"{$1}\".",
         add_ingredient_prompt = "Add {$1}",
         item_name = "Name",
         item_counter = "{$1} items",
         ground = " (Ground)",
         you_add = "You add {itemname($1)}.",
      },

      you_lose = "You lose {itemname($1, 1)}.",

      started = "{name($1)} start{s($1)} blending of {$2}.",
      succeeded = "You successfully create {itemname($1, 1)}!",
      failed = "The blending attempt failed!",

      required_material_not_found = "A required material cannot be found.",

      sounds = {
         "*pug*",
         "*clank*",
      },

      success_rate = {
         perfect = "Perfect!",
         piece_of_cake = "Piece of cake!",
         very_likely = "Very likely",
         no_problem = "No problem",
         probably_ok = "Probably OK",
         maybe = "Maybe",
         bad = "Bad",
         very_bad = "Very bad",
         almost_impossible = "Almost impossible",
         impossible = "Impossible!",

         goes_up = "The success rate goes up.",
         goes_down = "The success rate goes down.",
      },

      material = {
         filter = {
            flavor = "suitable flavoring",
            ore = "any ore",
            wood = "something made of wood",
            fish = "fish",
            anything = "any item",
         },
         item_of = "{$2} {$1}",
      },
   },
}
