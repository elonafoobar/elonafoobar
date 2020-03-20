i18n:add {
   talk = {
      will_not_listen = "{name($1)} won't listen.",
      is_sleeping = "{name($1)} is sleeping.",
      is_busy = "{name($1)} is in the middle of something.",
      ignores_you = "({he($1)} ignores you...)",

      window = {
         impress = "Impress",
         attract = "Attract",
         fame = "Fame: {$1}",
         shop_rank = "Shop Rank:{$1}",

         of = "{$1} of {$2}",
      },

      tag = {
         ref = "{$1} guest{s($1)}",
      },

      npc = {
         common = {
            choices = {
               talk = "Let's Talk.",
               trade = "Are you interested in trade?",
               sex = "Interested in a little tail t'night?",
            },

            thanks = "Thanks!",
            you_kidding = "You kidding? ",
            hand_over = "You hand over {itemname($1, 1)}.",

            sex = {
               prompt = "You are...quite attractive. I'll buy you.",

               choices = {
                  accept = "Let's do it.",
                  go_back = "W-wai.t..",
               },

               start = "Okay, no turning back now!",
               response = "Come on!",
            },
         },

         quest_giver = {
            choices = {
               about_the_work = "About the work.",
               here_is_item = "Here is {itemname($1, 1)} you asked.",
               here_is_delivery = "Here's your delivery.",
            },

            about = {
               during = "What about my contract? Is everything alright? ",

               choices = {
                  take = "I will take the job.",
                  leave = "Not now.",
               },

               too_many_unfinished = "Hey, you've got quite a few unfinished contracts. See me again when you have finished them.",
               backpack_full = "It seems your backpack is already full. Come see me again when you're ready.",
               party_full = "It seems your party is already full. Come see me again when you're ready.",

               thanks = "Thanks. I'm counting on you.",
               here_is_package = "Here's the package. Be aware of the deadline. I don't want to report you to the guards.",
            },

            accept = {
               hunt = "Great! I'll guide you to the place, kill them all!",
               harvest = "Fine. I'll take you to my farm.",
               party = "Alright, I'll take you to the party now.",
            },

            finish = {
               escort = "We made it! Thank you!",
            },
         },

         servant = {
            choices = {
               fire = "You are fired.",
            },

            fire = {
               prompt = "({name($1)} looks at you sadly. Really dismiss {him($1)}? )",

               choices = {
                  yes = "Yes.",
                  no = "No.",
               },

               you_dismiss = "You dismiss {name($1)}.",
            },
         },

         ally = {
            choices = {
               wait_at_town = "Wait at the town.",
               ask_for_marriage = "May I ask for your hand?",
               make_gene = "Let's make a gene.",
               silence = {
                  start = "Shut up.",
                  stop = "You can speak now.",
               },
               abandon = "I'm going to abandon you.",
            },

            wait_at_town = "(You order {name($1)} to wait at the town.)",

            marriage = {
               refuses = "({name($1)} gently refuses your proposal. )",
               accepts = "With preasure.",
            },

            make_gene = {
               refuses = "Not here!",
               accepts = "*blush*",
            },

            silence = {
               start = "({name($1)} stops talking...)",
               stop = "({name($1)} hugs you.)",
            },

            abandon = {
               prompt = "({name($1)} looks at you sadly. Really abandon {him($1)}?)",

               choices = {
                  yes = "Yes.",
                  no = "No.",
               },

               you_abandoned = "You abandoned {name($1)}...",
            },
         },

         maid = {
            choices = {
               think_of_house_name = "Think of a nice name for my house.",
               meet_guest = "Yes, I'll meet the guest now.",
               do_not_meet = "I don't want to meet anyone.",
            },

            think_of_house_name = {
               suffixes = {
                  "{$1} Home",
                  "{$1} Mansion",
                  "{$1} Shack",
                  "{$1} Nest",
                  "{$1} Base",
                  "{$1} Hideout",
                  "{$1} Dome",
                  "{$1} Hut",
                  "{$1} Cabin",
                  "{$1} Hovel",
                  "{$1} Shed",
               },
               come_up_with = "Hey, I've come up a good idea! \"{$1}\", doesn't it sound so charming?",
            },

            do_not_meet = "Alright.",
         },

         trainer = {
            choices = {
               train = {
                  ask = "Train me.",
                  accept = "Train me.",
               },
               learn = {
                  ask = "What skills can you teach me?",
                  accept = "Teach me the skill.",
               },
               go_back = "Never mind.",
            },
            leave = "Come see me again when you need more training.",
            cost = {
               training = "Training {$1} will cost you {$2} platinum pieces.",
               learning = "Learning {$1} will cost you {$2} platinum pieces.",
            },
            finish = {
               training = "Well done. You've got more room to develop than anyone else I've ever drilled. Keep training.",
               learning = "I've taught you all that I know of the skill. Now develop it by yourself.",
            },
         },

         shop = {
            choices = {
               buy = "I want to buy something.",
               sell = "I want to sell something.",
               attack = "Prepare to die!",
               invest = "Need someone to invest in your shop?",
               ammo = "I need ammos for my weapon.",
            },

            criminal = {
               buy = "I don't have business with criminals.",
               sell = "I don't have business with criminals.",
            },

            ammo = {
               no_ammo = "Reload what? You don't have any ammo in your inventory.",
               cost = "Sure, let me check what type of ammos you need....Okay, reloading all of your ammos will cost {$1} gold pieces.",

               choices = {
                  pay = "Alright.",
                  go_back = "Another time.",
               },
            },

            invest = {
               ask = "Oh, do you want to invest in my shop? It will cost you {$1} golds. I hope you got the money.",

               choices = {
                  invest = "Invest",
                  reject = "Reject",
               },
            },

            attack = {
               dialog = "Oh crap. Another bandit trying to spoil my business! Form up, mercenaries.",

               choices = {
                  attack = "Pray to your God.",
                  go_back = "W-Wait! I was just kidding.",
               },
            },
         },

         innkeeper = {
            choices = {
               eat = "Bring me something to eat.",
               go_to_shelter = "Take me to the shelter.",
            },

            eat = {
               not_hungry = "You don't seem that hungry.",
               here_you_are = "Here you are.",

               results = {
                  "It was tasty.",
                  "Not bad at all.",
                  "You smack your lips.",
               },
            },

            go_to_shelter = "The shelter is free to use for anyone. Here, come in.",
         },

         wizard = {
            choices = {
               identify = "I need you to identify an item.",
               identify_all = "Identify all of my stuff.",
               investigate = "Investigate an item.",
               ["return"] = "I want to return.",
            },

            identify = {
               already = "Your items have already been identified.",
               finished = "Here, I have finished identifing your stuff.",
               need_investigate = "You need to investigate it to gain more knowledge.",

               count = "{$1} out of {$2} unknown items are fully identified.",
            },

            ["return"] = "I'm practicing a spell of return. Would you like to take my service?",

         },

         informer = {
            choices = {
               show_adventurers = "Show me the list of adventurers.",
               investigate_ally = "I want you to investigate one of my allies.",
            },

            show_adventurers = "Done?",

            investigate_ally = {
               cost = "10000 gold pieces.",

               choices = {
                  pay = "Too expensive, but okay.",
                  go_back = "No way!",
               },
            },
         },

         healer = {
            choices = {
               restore_attributes = "Restore my attributes.",
            },

            restore_attributes = "Done treatment. Take care!",

         },

         bartender = {
            choices = {
               call_ally = "Call back my allies.",
            },

            call_ally = {
               no_need = "Huh? You don't need to do that.",
               cost = "Alright. We had taken good care of your pet. It will cost you {$1} gold pieces.",

               choices = {
                  pay = "I'll pay.",
                  go_back = "Never mind.",
               },

               brings_back = "({name($1)} brings {name($2)} from the stable.) There you go.",
            },
         },

         adventurer = {
            choices = {
               hire = "I want to hire you.",
               join = "Join me!",
            },

            hire = {
               cost = "I will take the job for {$1} gold pieces, for seven day.",

               choices = {
                  pay = "Sounds fair enough.",
                  go_back = "Some other time.",
               },

               you_hired = "You hired {name($1)}.",
            },

            join = {
               too_weak = "Huh? You are no match for me.",
               not_known = "Huh? What made you think I'd want to join you? I don't even know you well.",
               party_full = "It seems your party is already full. Come see me again when you're ready.",
               accept = "Sure, I guess you and I can make a good team.",
            },
         },

         arena_master = {
            choices = {
               enter_duel = "I'm entering the arena. [Duel]",
               enter_rumble = "I'm entering the arena. [Rumble]",
               score = "Tell me my scores.",
            },

            enter = {
               game_is_over = "The game is over today. Come again tomorrow.",
               target = "You got {$1} today. What'ya say?",
               target_group = "Your play is a group of monster around level {$1}. Sounds easy huh?",

               choices = {
                  enter = "Alright.",
                  leave = "I'll pass.",
               },

               cancel = "Alright. Call me if you changed your mind.",
            },

            streak = "Your winning streak has reached {$1} matches now. Keep the audience excited. You get nice bonus at every 5th and 20th wins in a row.",
         },

         pet_arena_master = {
            choices = {
               register_duel = "I want to register my pet. [Duel]",
               register_team = "I want to register my team. [Team]",
            },

            register = {
               target = "The opponent is around level {$1}. Want to give it a try? ",
               target_group = "It's a {$1} vs {$1} match. The opponent's group is formed by the pets less than {$2} levels. What you say?",

               choices = {
                  enter = "I'll send my pet.",
                  leave = "I'll pass.",
               },
            },
         },

         slave_trader = {
            choices = {
               buy = "I want to buy a slave.",
               sell = "I want to sell a slave.",
            },

            buy = {
               cost = "Okay. Let me check the stable....How about {$1} for {$2} gold pieces. I'd say it's quite a bargain!",

               choices = {
                  pay = "I'll pay.",
                  go_back = "Never mind.",
               },

               you_buy = "You buy {$1}.",
            },

            sell = {
               price = "Let me see....Hmmm, this one got a nice figure. I'll give you {$1} gold pieces.",

               choices = {
                  deal = "Deal.",
                  go_back = "No way.",
               },

               you_sell_off = "You sell off {$1}.",
            },
         },

         horse_keeper = {
            choices = {
               buy = "I want to buy a horse.",
            },
         },

         sister = {
            choices = {
               buy_indulgence = "I want to buy an indulgence.",
            },

            buy_indulgence = {
               karma_is_not_low = "You karma isn't that low. Come back after you have committed more crimes!",
               cost = "In the authority of all the saints, I will grant you an indulgence, for money of course. The price is {$1} gold pieces.",

               choices = {
                  buy = "Deal.",
                  go_back = "The price is too high.",
               },
            },
         },

         guard = {
            choices = {
               where_is = "Where is {basename($1)}?",
               lost_wallet = "Here is a lost wallet I found.",
               lost_suitcase = "Here is a lost suitcase I found.",
            },

            where_is = {
               direction = {
                  north = "north",
                  south = "south",
                  east = "east",
                  west = "west",
               },

               dead = "Oh forget it, dead for now.",
               very_close = "Oh look carefully before asking, just turn {$1}.",
               close = "I saw {basename($2)} just a minute ago. Try {$1}.",
               moderate = "Walk to {$1} for a while, you'll find {basename($2)}.",
               far = "If you want to meet {basename($2)}, you have to considerably walk to {$1}.",
               very_far = "You need to walk long way to {$1} to meet {basename($2)}.",
            },

            lost = {
               empty = {
                  dialog = "Hmm! It's empty!",
                  response = "Oops...!",

               },
               dialog = "How nice of you to take the trouble to bring it. You're a model citizen indeed!",
               response = "It's nothing.",

               found_often = {
                  dialog = {
                     _0 = "Oh, it's you again? How come you find the wallets so often?",
                     _1 = "(...suspicious)",
                  },
                  response = "I really found it on the street!",
               },
            },
         },

         spell_writer = {
            choices = {
               reserve = "I want to reserve some books.",
            },
         },

         prostitute = {
            choices = {
               buy = "I'll buy you.",
            },

            buy = "Okay sweetie, I need {$1} gold pieces in front.",

         },

         caravan_master = {
            choices = {
               hire = "Hire caravan.",
            },

            hire = {
               tset = "tset",

               choices = {
                  go_back = "Never mind!",
               },
            },
         },

         moyer = {
            choices = {
               sell_paels_mom = "I want to sell Pael's mom.",
            },

            sell_paels_mom = {
               prompt = "Look what we have! A woman who got a monster's face. It'll be a good show. Wanna sell me for 50000 gold coins?",

               choices = {
                  sell = "Sure, take her.",
                  go_back = "You cold bastard.",
               },

               you_sell = "You sell Pael's mom...",
            },
         },
      },
   },
}
