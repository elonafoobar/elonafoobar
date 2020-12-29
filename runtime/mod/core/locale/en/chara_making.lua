local I18N = require("core.I18N")

I18N.add {
   chara_making = {
      common = {
         reroll = "Reroll",
      },

      select_race = {
         caption = "Welcome traveler, I've been looking for you.",
         title = "Race Selection",

         race = "Race",
         detail = "Detail",

         race_info = {
            race = "Race",
            attribute_bonus = {
               text = "Attribute Bonus",
               _0 = "None",
               _1 = "Best",
               _2 = "Great",
               _3 = "Good",
               _4 = "Not bad",
               _5 = "Normal",
               _6 = "Little",
               _7 = "Slight",
            },

            trained_skill = {
               text = "Trained Skill",
               proficient_in = "Proficient in ",
            },
         },
      },

      select_gender = {
         caption = "What's your gender?",
         title = "Gender Selection",

         gender = "Gender",
      },

      select_class = {
         caption = "Your class and race determine growth rate of your skills and attributes.",
         title = "Class Selection",

         class = "Class",
         detail = "Detail",
      },

      roll_attributes = {
         caption = "You should prepare well, if you want to survive long enough in Irva.",
         title = "Attributes",

         proceed = "Proceed",

         attribute_reroll = "Attb Reroll",
         min_roll = "Min Roll",
         locked_items_desc = "Locked items will\nnot change.",
         locks_left = "Locks left",
      },

      select_feats = {
         caption = "Choose your feats wisely.",
      },

      select_alias = {
         caption = "Choose your Alias.",
         title = "Alias Selection",

         lock_alias = "Lock Alias",
         alias_list = "Alias List",
      },

      customize_appearance = {
         caption = "What you look like? Don't worry, you can change them later.",
      },

      final_screen = {
         caption = "Hit the enter key to reroll your personal history.",

         are_you_satisfied = {
            prompt = "Are you satisfied now?",

            yes = "Yes",
            no = "No",
            restart = "Restart",
            go_back = "Go back",
         },

         what_is_your_name = "Last question. What's your name?",
      },
   },
}
