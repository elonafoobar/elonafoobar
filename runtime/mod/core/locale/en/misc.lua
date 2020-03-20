-- TODO
-- These text are unclassed. They should be moved to appropriate files.

i18n.add {
   misc = {
      ranking = {
         changed = "Ranking Change ({$1} {$2} -> {$3}) <{$4}>",
         closer_to_next_rank = "You are one step closer to the next rank.",
      },

      sound = {
         waken = "{name($1)} notice{_s($1)} the sound and wake{_s($1)} up.",
         get_anger = "{name($1)} can no longer put up with it.",
         can_no_longer_stand = "\"That's it.\"",
      },

      hostile_action = {
         glares_at_you = "{name($1)} glares at you.",
         gets_furious = "{name($1)} gets furious!",
         get_excited = "Animals get excited!",
      },

      wet = {
         gets_wet = "{name($1)} get{s($1)} wet.",
         is_revealed = "{name($1)} {is($1)} revealed {his($1)} shape.",
      },

      fail_to_cast = {
         mana_is_absorbed = "{name($1)}{his_owned($1)} mana is absorbed.",
         is_confused_more = "{name($1)} {is($1)} confused more.",
         too_difficult = "It's too difficult!",
         dimension_door_opens = "A dimension door opens in front of {name($1)}.",
         creatures_are_summoned = "Several creatures are summoned from a vortex of magic.",
      },

      status_ailment = {
         choked = "\"Ughh...!\"",
         breaks_away_from_gravity = "{name($1)} break{s($1)} away from gravity.",
         calms_down = "{name($1)} calm{s($1)} down.",
         sleepy = "You need to sleep.",
         insane = {
            "{name($1)} start{s($1)} to take {his($1)} cloths off.",
            "{name($1)} shout{s($1)}.",
            "{name($1)} dance{s($1)}.",
            "\"Weeeeeee!\"",
            "\"Forgive me! Forgive me!\"",
            "\"P-P-Pika!\"",
            "\"Shhhhhh!\"",
            "\"So I have to kill.\"",
            "\"You snail!\"",
         },
      },

      death = {
         good_bye = "Good bye... ",
         you_leave_dying_message = "You leave a dying message.",
         dying_message = "\"{$1}\"",
         date = "{$1}/{$2}/{$3}",
         you_died = "{capitalize($1)} in {$2}.",
         rank = "{ordinal($1)}",
         you_are_about_to_be_buried = "You are about to be buried...",
         crawl_up = "Crawl up",
         lie_on_your_back = "Lie on your back",
         you_have_been_buried = "You have been buried. Bye...(Hit any key to exit)",
      },

      score = {
         rank = "{ordinal($1)}",
         score = "{$1}",
      },

      resurrect = "{capitalize($1)} {have($2)} been resurrected!",
      artifact_regeneration = "{$1} turns its shape into {itemname($2)}.",
      black_cat_licks = "{name($1)} licks {itemname($2)}.",
      corpse_is_dried_up = "{itemname($1)} {is($1)} dried up in the sun.",
      get_rotten = "{itemname($1)} rot{s($1)}.",
      extract_seed = "You extract plant seeds from {itemname($1)}.",

      curse = {
         gold_stolen = "A malicious hand filches some gold pieces from {name($1)}{his_owned($1)} wallet.",
         blood_sucked = "Something sucks {name($1)}{his_owned($1)} blood.",
         experience_reduced = "{name($1)} become{s($1)} inexperienced.",
         creature_summoned = "Several creatures are summoned from a vortex of magic.",
      },

      identify = {
         fully_identified = "You appraise {$1} as {itemname($2)}.",
         almost_identified = "You sense the quality of {itemname($1)} is {$2}.",
      },

      love_miracle = {
         uh = "\"Uh...!\"",
      },

      pregnant = {
         pukes_out = "But {he($1)} puke{s($1)} it out quickly.",
         gets_pregnant = "{name($1)} get{s($1)} pregnant.",

         pats_stomach = "{name($1)} pat{s($1)} {his($1)} stomach uneasily.",
         something_is_wrong = {
            "\"I'm going to have a baby!\"",
            "\"Something is wrong with my stomach...\"",
         },
         something_breaks_out = "Something splits {name($1)}{his_owned($1)} body and breaks out!",
      },

      walk_down_stairs = "You walk down the stairs. ",
      walk_up_stairs = "You walk up the stairs. ",

      quest = {
         kamikaze_attack = {
            message = "The messenger \"The retreat of our army is over now. You don't need to fight them any more. Please leave at once!\"",
            stairs_appear = "Suddenly, stairs appear.",
         },
      },

      map = {
         jail = {
            repent_of_sin = "You repent of your sin.",
            guard_approaches = "You hear footsteps coming towards your cell.",
            leave_here = "\"Hey punk, our boss says you can leave the jail now. Do not come back, okay?\"",
            unlocks_your_cell = "A guard unenthusiastically unlocks your cell.",
         },

         shelter = {
            eat_stored_food = "You eat stored food.",
            no_longer_need_to_stay = "You don't need to stay in the shelter any longer.",
         },

         museum = {
            chats = {
               "*noise*",
               "\"Hmm. Not bad.\"",
               "\"What's this?\"",
               "\"Ohh...\"",
               "\"I want to be stuffed...\"",
               "\"So this is the famous...\"",
            },
            chats2 = {
               "*murmur*",
               "\"Gross! Disgusting.\"",
               "\"Hey. Is it really dead?\"",
               "\"Scut!\"",
               "\"Absolutely amazing.\"",
               "\"Can I touch?\"",
            },
         },

         shop = {
            chats = {
               "*murmur*",
               "\"I want this! I want this!\"",
               "\"Oh what's this?\"",
               "\"I'm just watching\"",
               "\"My wallet is empty...\"",
               "\"So this is the famous....\"",
            },
         },
      },

      custom = {
         key_hint = "BackSpace [Delete]  ",
         show_room = {
            which_show_room = "Which room do you want to visit? ",
            list = "Room List",
            name = "Name",
         },
         pet_team = {
            which_team = "Which team do you want to play a match? ",
            list = "Team List",
            name = "Name",
         },

         incompatible = "Selected item is incompatible.",
         fail_to_retrieve_file = "Failed to retrieve designated files.",
         do_you_want_to_delete = "Do you really want to delete {$1}? ",
      },

      no_target_around = "You look around and find nothing.",

      ["return"] = {
         forbidden = "Returning while taking a quest is forbidden. Are you sure you want to return?",
         no_location = "You don't know any location you can return to",
         where_do_you_want_to_go = "Where do you want to go?",
         air_becomes_charged = "The air around you becomes charged.",
         lord_of_dungeon_might_disappear = "The lord of the dungeon might disappear if you escape now.",
      },

      dungeon_level = " Lv",

      save = {
         update = "Updating your save data from Ver.{$1} now.",
         need_to_save_in_town = "To update your game, please save your game in a town in the previous version then retry.",
         take_a_while = "The next updating process may take a while to complete.",
         cannot_save_in_user_map = "The game is not saved in a user map.",
      },

      living_weapon_taste_blood = "{itemname($1)} has tasted enough blood!",
      caught_by_assassins = "You are caught by assassins. You have to protect your client.",
      finished_eating = "{name($1)} {have($1)} finished eating {itemname($2, 1)}.",
      spell_passes_through = "The spell passes through {name($1)}.",
      shakes_head = "{name($1)} shake{s($1)} {his($1)} head.",

      wields_proudly = {
         the = "The ",
      },

      ["and"] = " and ",

      income = {
         sent_to_your_house = "As a salary, {$1} gold piece{s($1)} have been sent to your house.",
         sent_to_your_house2 = "As a salary, {$1} gold piece{s($1)} and {$2} item{s($2)} have been sent to your house.",
      },

      tax = {
         bill = "A bill has been sent to your house.",
         no_duty = "You don't have to pay tax until you hit level 6.",
         caution = "Caution! ",
         warning = "Warning!! ",
         have_to_go_embassy = "You have to go to the Embassy of Palmia and pay tax at once. ",
         left_bills = "You are in arrears with your tax for {$1} month{s($1)}.",
         accused = "You have been accused for being in arrears with your tax for{$1} months.",
         lose_fame = "You lose {$1} fame.",
      },
   },
}
