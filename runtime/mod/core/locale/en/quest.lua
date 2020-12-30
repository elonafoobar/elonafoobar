local i18n = require("core.i18n")

i18n.add {
   quest = {
      journal_updated = "Your journal has been updated.",
      minutes_left = "{$1} min left for the quest.",
      completed = "You have completed the quest!",
      completed_taken_from = "You have completed the quest taken from {$1}.",
      failed_taken_from = "You have failed the quest taken from {$1}.",
      gain_fame = "You gain {$1} fame.",
      lose_fame = "You lose {$1} fame.",

      hunt = {
         complete = "The area is secured!",
         remaining = "{$1} more to go.",
      },
      party = {
         is_over = "The party is over.",
         final_score = "Your final score is {$1} points!",
         complete = "People had a hell of a good time!",
         fail = "The party turned out to be a big flop...",

         is_satisfied = "{basename($1)} {is($1)} satisfied.",
         total_bonus = "(Total Bonus:{$1}%)",
      },
      collect = {
         complete = "You complete the task!",
         fail = "You fail to fulfill your task...",
      },
      conquer = {
         complete = "You successfully slay the target.",
         fail = "You failed to slay the target...",
      },
      deliver = {
         you_commit_a_serious_crime = "You commit a serious crime!",
      },
      escort = {
         complete = "You complete the escort.",
         you_failed_to_protect = "You have failed to protect the client.",
         you_left_your_client = "You left your client.",

         failed = {
            assassin = "\"Hey, the assassins are killing me.\"",
            poison = "\"Poison! P-P-Poison in my vein!!\"",
            deadline = "\"I missed the deadline. I don't have a right to live anymore.\" {name($1)} pours a bottole of molotov cocktail over {himself($1)}.",
         },
      },
      arena = {
         you_are_victorious = "You are victorious!",
         your_team_is_victorious = "Your team is victorious!",
         your_team_is_defeated = "Your team is defeated.",
         stairs_appear = "Stairs appear.",
      },

      you_were_defeated = "You were defeated.",

      giver = {
         have_something_to_ask = "",
         days_to_perform = "You have {$1} days to perform the task.",
         how_about_it = "How about it?",

         complete = {
            done_well = "You've done well. Thanks. Here's your reward.",
            take_reward = "",
            extra_coins = "I've added some extra coins since you worked really hard.",
            music_tickets = "The party was terrific! I'll give you these tickets as an extra bonus.",
         },
      },

      info = {
         gold_pieces = "{$1} gold pieces",
         ["and"] = " and ",
         no_deadline = "-",
         days = "{$1}d",
         heavy = "(Heavy!)",
         now = " (Now {$1})",

         harvest = {
            text = "Gather harvests weight {$1}.",
         },

         party = {
            text = "Gather {$1}.",
            points = "{$1} points",
         },

         escort = {
            text = "Escort the client to {$1}.",
         },

         hunt = {
            text = "Eliminate monsters.",
         },

         supply = {
            text = "Give {$1} to the client.",
         },

         deliver = {
            text = "Deliver {$1} to {$3} who lives in {$2}.",
            deliver = "",
         },

         conquer = {
            text = "Slay {$1}.",
            unknown_monster = "unknown monster",
         },

         huntex = {
            text = "Eliminate monsters",
         },

         collect = {
            text = "Acquire {$1} from {$2} for the client.",
            target = "the target in {$1}",
         },
      },

      journal = {
         complete = "Complete",
         job = "Job",
         client = "Client  : ",
         location = "Location: ",
         deadline = "Deadline: ",
         reward = "Reward  : ",
         detail = "Detail  : ",
         remaining = "",
         report_to_the_client = "Report to the client.",
      },
   },
}
