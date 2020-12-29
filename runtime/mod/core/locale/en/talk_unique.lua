local I18N = require("core.I18N")

I18N.add {
   talk = {
      unique = {
         zeome = {
            dialog = "So you've made it this far. Evidently, <Chaos> wants no poise even within their own creation...Nefia. Well, it seems they have left me no choice but to whip you!",
         },

         whom_dwell_in_the_vanity = {
            dialog = "Leave me alone.",
         },

         -- TODO
         orphe = {
            dialog = {
               _0 = "Most impressive.",
               _1 = "<This sentence is untranslated.>",
               _2 = "<This sentence is untranslated.>",
               _3 = "<This sentence is untranslated.>",
               _4 = "<This sentence is untranslated.>",
               _5 = "<This sentence is untranslated.>",
            },
         },

         loyter = {
            fame_too_low = "Who the hell are you?",
            complete = "You have the money, now get lost.",

            quest = {
               dialog = {
                  _0 = "Hey you! Hold up! I've seen your face before punk... {$1}... Ah yes... I remember now. You've been making quite a name for yourself throughout Tyris, haven't you?",
                  _1 = "You wanna make some quick cash? I've got a request from the organization of Zanan. They need a test subject in order to get some experimental data. Or perhaps \"sacrifice\" would be a more appropriate term. *If* you survive, I'll pay you enough to party until you waste away. Make your decision quickly.",
               },

               choices = {
                  yes = "Fine, let's do it.",
                  no = "Not a chance, you worm.",
               },

               yes = "Excellent. Let me know when you've finished your preparations for death and I'll take you to the testing grounds.",
               no = "Fine then, piss off you spineless coward.",

               begin = {
                  dialog = "So, are you ready?",

                  choices = {
                     -- TODO duplicate
                     yes = "Yes.",
                     no = "No.",
                  },

                  yes = "Follow me.",
                  no = "Be quick.",
               },

               ["end"] = "You came back alive... astonishing. You're the first and I swear you'll be the last. Zanan's senior commanders should find this data most intriguing. I do not want such a clumsy beast watching my back on the battlefield.",
            },
         },

         miches = {
            complete = "Hi there adventurer! Would you like some tea?",

            quest = {
               dialog = {
                  _0 = "Ah, you... adventurer, you've definitely come to the right place.",
                  _1 = "Recently, when I wake in the morning my stuffed toys are always chewed up. So I stayed up last night and secretly watched. You know what I found? Putits were chewing up my stuffed animals! I'm pretty sure they're getting into my house through the window to the neighbor's place. I beg of you adventurer, won't you eradicate the Putits for me?",
               },

               choices = {
                  yes = "Sure thing.",
                  no = "Not now.",
               },

               yes = "Fabulous! The trouble is all in the house just south of here.",
               no = "Okay... but... if you change your mind please come back.",

               waiting = "Aggh! My stuffed toys are ruined! Hurry up and kill the Putits!",
               ["end"] = "Eh? You wiped out the slimes? Thanks so much. My stuffed animals are delighted too. Here, you might find this useful.",
            },
         },

         shena = {
            complete = "Oh it's you, our hero.",

            quest = {
               dialog = {
                  _0 = "Welcome~!", -- NOTE: New dialog for EN
                  _1 = "Excuse me, do you have a moment? The kegs from the bar have been stolen, and the manager is really put out. If you're not busy, could you help out? It was those thugs, I'm sure of it. They've certainly set up a base inside Vernis. With all the mud they leave behind, they're most likely hanging out near the gravesite.",
               },

               choices = {
                  yes = "I'd be happy to help.",
                  no = "Don't bother me.",
               },

               yes = "Really? Thanks, we really appreciate it.",
               no = "Alright, but please... think about it.",

               waiting = "Welcome! Welcome! Have you found the bandit's lair yet? It should be near the graveyard.",
               ["end"] = "Yes, I've already gotten wind of your deeds. It's a big relief to be rid of those miscreants. I can't thank you enough. I know it isn't much, but please take this as a token of our thanks.",
            },
         },

         larnneire = {
            dialog = "I'm glad you got well again. I thought you were a goner until just a few minutes ago.",

            choices = {
               mission = "What's your mission?",
               north_tyris = "Tell me about North Tyris.",
               fairy_tale = "You mentioned a fairy tale.",
            },

            fairy_tale = {
               _0 = "You may have heard of this story before...",
               _1 = "There was once a prince who had his shape changed into that of an ugly beast by a witch. Despairing of his bloodcurdling appearance, he hid himself in a forest far from his kingdom.",
               _2 = "One day a woman rushed into his hut and passed out, having been badly wounded by a pack of wolves. He treated her with the knowledge and fear that his ugly body might scare her. This fear turned into reality soon enough for she cried out as she woke up.",
               _3 = "However, as days passed by and she regained her health, the woman had come to recognize the kindness and generosity that was within the heart of this beast. She decided to live with him.",
               _4 = "They surmounted various difficulties throughout their lives and the story comes to an end when the curse set upon the prince finally breaks and the beast returned to his former shape, that of a flawlessly handsome prince. The two of them got along very well from that time on. A happy ending... although just an ordinary story, don't you agree?",
               _5 = "The elders of Vindale used to tell me this kind of story. But I never liked this one. Perhaps it is because I felt like the beast that she loved despite the fact that his ugliness had been left behind somewhere.",
            },

            north_tyris = {
               _0 = "North Tyris is a continent in the western hemisphere of Irva. Lots of merchants and travelers set foot on North Tyris' soil with the dream of making a fortune in the ancient ruins of Nefia.",
               _1 = "If you haven't set your destination yet, you might want to visit Vernis. It's a mining town located south of here.",
            },

            mission = "We are messengers from Vindale. Our journey ends here in North Tyris at the great city of Palmia where we're supposed to have a talk with King Xabi, a man of fairness and compassion.",
         },

         lomias = {
            begin = {
               easter_egg = {
                  _0 = "This cave...it's a good place to keep out the rain. Lomias, check the inner chamber to be sure there is no danger lurking here.",
                  _1 = "Okay. Wait here.",
                  _2 = "...what was that sound? ...Lomias, are you alright?",
                  _3 = "It's nothing. Looks like this cave is long abandoned. It's a good place to stay.",
                  _4 = "I see, that's convenient for us...wait Lomias, what arey you carrying?...Argh! Putits!",
                  _5 = "Don't worry. It appears these putits had been kept as pets by someone. They are kind of...cute.",
                  _6 = "Huh, sounds like even you have a soft spot...Come here, the injured is about to wake up.",

                  something_is_killed = "Something is killed.",
                  ugh = "\"Uggghhh!\"",
                  was_dream = "It was...a dream...?",
               },
               regain_consciousness = "You regain consciousness.",

               _0 = "...you...you're awake already? Remarkable. I was beginning to worry that nursing a lowly adventurer would bring our urgent travel to a halt.",
               _1 = "You were badly wounded, passing out on the bank of a river. It was fortunate that we found you before the dark mantle of night enveloped this whole valley, almost as if Ehekatl, the goddess of luck herself had her eyes upon you.",
               _2 = "...stop your curious eyes. Yes, we are sons of Vindale whom they call the irreverent forest. Though we Eleas, noble but blameless \"heretics\", aren't keen to spend idle time responding to every senseless question about our race, you should be more thankful for your fate. If it weren't the lady Larnneire who cured your mortal wound, you wouldn't be hearing my tirade. For the lady is no ordinary Elea and only she can...",
               _3 = "You talk too much Lomias, even though the one injured before you is still dazed.",
               _4 = "...yes, it's a bad habit of mine. Well, {$1}...",
            },

            tutorial = {
               before = {
                  dialog = "It looks like you aren't familiar with this land. Before we leave, I can spare a moment to teach you a few lessons.",
                  choices = {
                     yes = "I would like to play the tutorial.",
                     no = "I can take care of myself.",
                  },

                  yes = "A wise choice. I will start from the beginning.",
               },

               movement = {
                  dialog = {
                     _0 = "Pray tell me at least you know how to move. Sure, pressing cursor keys will do. But it's better to use a key pad if you have one. By using a key pad, you can easily access keys which are used frequently. Like [0] for picking up stuff, [5] for passing a turn and [*] for targeting.",
                     _1 = "Although there're many actions you can perform, basically you can access them by using only 3 keys, [z],[x] and [c].",
                     _2 = "Let's try them now. First, you need food to live. If your stomach is empty, you will lose Hp and your action speed slows down. Make sure you always have enough food in your inventory.",
                     _3 = "Here, you can have this meat. Press [x], then press [9] a few times to select the <Eat> menu. Once there, select the meat on the ground.",
                  },

                  choices = {
                     alright = "Alright.",
                     ate = "I ate it.",
                  },

                  ate = {
                     dialog = {
                        _0 = "...err..you really ate that thing? Oh well..",
                        _1 = "You can also use other items by pressing [x]. For example, if you want to read a book, press [x], hit [9] a few times to select the <Read> menu, then choose a book you want to read.",
                        _2 = "Now, allow me to explain how to act by using the [z] key.", -- NOTE: New dialog for EN
                     },
                     response = "What!",
                  },
               },

               skills = {
                  dialog = {
                     _0 = "You can perform skills or other actions including bashing and digging by pressing [z]. Here's a tip. You can bash doors to break locks and trees to get some fruits. It can be used to wake someone, but surely they won't be happy.",
                     _1 = "Also, remember that [space] key is a very useful key. When there's an object under your foot, it automatically chooses a suitable action for you.",
                     _2 = "Let's try it now. Try digging some walls by pressing [z] and choosing <dig>.",
                  },
                  response = "Okay.",
               },

               after_dig = {
                  dialog = "Looks like you found something.",
               },

               identify = {
                  dialog = {
                     _0 = "Many items need to be identified before you can know what exactly they are. You can identify items by reading some scrolls or asking a wizard in a town. Remember that using unidentified potions or scrolls is very dangerous. ",
                     _1 = "Weapons and armor also need to be identified. If you carry them long enough, you will get a hunch as to how good they are. But to gain full knowledge of the items, you need to identify them.",
                     _2 = "Now I'll give you a scroll of identify. Read it by using [x] and identify the gold bar you just found.",
                  },

                  choices = {
                     alright = "Alright, I will try.",
                     done = "Done...",
                  },

                  done = {
                     dialog = {
                        _0 = "(Lomias grins. Looks like he buried it unnoticed.)",
                        _1 = "Okay, I will now tell you how to fight. Before the combat starts, you need to equip weapons. Take my old bow and arrows and equip them.",
                     },
                  },
               },

               equip = {
                  dialog = "To equip weapons or armor, press [c] and press [9] to select [Wear]. Note that if you wear cursed equipment, they can't be removed normally and cause some unwelcome effects. That bow is cursed. Use this scroll of uncurse to uncurse it.",
                  choices = {
                     alright = "Will do.",
                     done = "All done.",
                  },

                  done = {
                     dialog = {
                        _0 = "Good. Now listen carefully.",
                        _1 = "By moving towards a target, you automatically attack it with your close range weapon. To use your long range weapon, you can either press [z] and choose [Shoot] or simply press [f] (Fire). You will shoot a nearby enemy. If you want to change your target, press [*].",
                        _2 = "Get ready. I will summon some weak monsters. Kill them with your bow if possible. Try to stay away from the enemies as bows aren't effective in close range. I've dropped a few potions in case you get hurt. You know how to use them right? Yes, use [x] key.",
                     },

                     lomias_releases = "Lomias releases tiny cute creatures.",
                  },
               },

               combat = {
                  not_finished = "Kill them all.",
                  finished = "Well done.",
               },

               chests = {
                  dialog = {
                     _0 = "Let's learn a little history of North Tyris. This sacred land governed by Palmia is known for ancient ruins <<Nefia>>. Occasionally new ruins are found and lost by erratic movements of the earths crust.",
                     _1 = "A lord lives at the lowest layer of these ruins, protecting great treasures and therefore attracts numerous adventurers. However, avoid those ruins which exceed your current level. You may gain a lot, but you may lose your life.",
                     _2 = "You might find chests containing loot in ruins. There's one nearby, open it.",
                  },
                  response = "Okay.",
               },

               house = {
                  dialog = {
                     _0 = "Notice the chest has a lock? Locked chests require sufficient lockpick skill and lockpicks to open. You need to practice to open that chest. Be aware, those chests are heavy and trust me, give up if you can't open them when you're in dungeons. I saw a fool running around with a chest on his back and he got killed.",
                     _1 = "As you explore dungeons, your backpack may get heavier. Remember to leave stuff you don't need in your house. Overweight will slow your movement.",
                     _2 = "Finally, I'm going to explain a bit about your house. As you already know, you can safely store items in your house. And the salary chest periodically gets filled with some gold and items. Eventually you might be able to buy a new house.",
                     _3 = "You can do several things by using a house board in your house. Try it later.",
                  },
               },

               ["end"] = {
                  dialog = {
                     _0 = "Alright, we're finished. You should already know how to survive in North Tyris by now.",
                     _1 = "(You've finished the tutorial!)",
                  },
               },
            },

            after = {
               dialog = "What?",

               choices = {
                  nothing = "Nothing.",
                  get_out = "Get out of my house!",
               },

               get_out = {
                  larnneire_died = "You...you scum!",

                  dialog = {
                     _0 = "{$1} is right. The time left for us is scarce. We need to depart, Lomias.",
                     _1 = "Yes. Palmia is still far away. Perhaps, It was fortunate that we could have a little rest before everything begins.",
                     _2 = "Farewell..until we meet again. May the blessing of Lulwy be with you.",
                  },

                  leave = "Lomias and Larnneire leave the cave.",
               },
            },
         },

         stersha = {
            late = "The tragedy of our king, and the collapse of our world, Palmia is...Sierre Terre is in difficult times.",
            mid = "The whole kingdom is devastated to hear the tragic news of our king. This throne... it feels very cold without him.",
            early = "Palmia is an old and historical kingdom which respects peace and freedom. The royalism has been obsoleted long time ago, but people still carry loyalty to the old kings and my husband, King Xabi.",
         },

         xabi = {
            late = "Any assistance you provide to us will be most welcome.",
            mid = "In times like these, we can't afford to let those we can trust sit idly on their swords. If you're willing to serve Palmia, then you should pay a visit to Erystia in the library. We will be sure to reward you with honor and riches commiserate with your sacrifice.",
            early = {
               _0 = "What's that you say? You have a message from one of our scouts? ...Very well then, let me see it.",
               _1 = "I see... then what we feared has indeed come to pass. If evil has set its sights on the artifact hidden within the depths of Lesimas, then for the honor of our King we are bound to stop it... You must be tired, {$1}. Give me a moment to prepare appropriate compensation for your efforts today.",
            },
         },

         slan = {
            dialog = {
               _0 = "You...you there, listen to me. *cough* *cough* I-I'm a scout of Palmia...I've been investigating on Zanan's strange activities in Lesimas.... *cough* I have a favor to ask...",
               _1 = "T-There's no time left for me to explain all....my wounds are... *cough* Listen, Sierre Terre is in danger...this letter..this letter...this is our only hope....",
               _2 = "I have no choice but to trust you.... *cough* bring the letter to Palmia.... I-I beg you...You can take everything I have on me...so... plea..s..",
            },
            you_receive = "You receive a letter to the king Xabi. Your journal has been updated.",
            dies = "{basename($1)} dies silently...",
         },

         erystia = {
            late = {
               -- TODO
               _0 = "You've done well.",
               _1 = "<This sentence is untranslated.>",
               _2 = "<This sentence is untranslated.>",
            },

            all_stones = {
               dialog = {
                  _0 = "It looks like you've finally managed to acquire all three of the stones, {$1}. According to the information we've learned during the excavation, these stones are the key that will unlock the deepest reaches of Lesimas. However, be aware that terrifying monsters lurk in the abyss of Lesimas, and we have no idea how deep those caverns go.",
                  _1 = "This will be your last mission. This will be no easy task, but failure is not an option. It's up to you to complete the excavation of Lesimas and find the room where the codex is kept. If you can't retrieve the <Origin of Vice> we will never be able to uncover the conspiracy Zanan has set into motion.",
                  _2 = "If what Karam told us is true, the codex will be guarded by the late king Zashim's cousin, Zeome. Zeome was known to have been a very powerful warlock. In his day, he was by far the most powerful sorcerer alive. I wouldn't dare confront him unless you are extremely well prepared.",
                  _3 = ": Words alone are not enough to express our gratitude for all that you have done. This ring is a gift from Queen Stersha. We are praying for your success, {$1}.",
               },

               you_receive = "You receive a key of Lesimas 25th level. Your journal has been updated.",
            },

            stones = {
               dialog = {
                  _0 = "I've been waiting for you to return, {$1}. I hope that Karam is... no, I can tell just by looking at you. Then our rescue attempt was too little too late.",
                  _1 = "Well take Karam's message to heart then... I remember reading about the <Origin of Vice> in one of these books. I believe it referred to the codex as an exhaustive account of the history of all things in Irva. If, as Karam suspected, Saimore is trying to acquire the codex in order cover up gaps in his story we can't allow him to succeed.",
                  _2 = "I'm sure you've already heard the tragic news about the king. All of Palmia is heartbroken by the king's demise, but we can't afford to spend our time mourning right now. We have to push on, for Karam... and for the king's sake.",
                  _3 = "Your next task is to retrieve the three magic stones. It's written in several of our historical accounts that the stones are the key to unlocking the secrets of Lesimas. We already know where the stones are located, but actually getting the stones is definitely easier said than done. First, you should scout the areas, gather info, and build your strength.",
                  _4 = "Please come see me anytime you get information that would be useful to the expedition. I know you've just returned and we're asking an awful lot of you, but I don't have any other choice.",
               },

               you_receive = "You receive a key of Lesimas 17th level. Your journal has been updated.",
            },

            investigation = {
               dialog = "{$1}, how's your investigation going? Ask anything you'd like to know.",

               choices = {
                  lesimas = "Tell me about Lesimas.",
                  mission = "Tell me about the mission again.",
                  stones = {
                     castle = "Tell me about the ancient castle.",
                     inferno = "Tell me about the tower of infernos.",
                     crypt = "Tell me about the crypt of the damned.",
                  },
               },

               lesmias = {
                  _0 = "Lesimas is one of the numerous ruins of Nefia. It is a significant part of the history of Palmia. The Eulderna sought to bring themselves prosperity using one of the treasures of Nefia, so the third king, Zashim and his cousin Zeome organized an excavation of Lesimas.",
                  _1 = "Eventually the king and his cousin received word that the excavation had been completed, so they descended to the deepest reaches of Lesimas. Together they set foot into the darkened room where the codex was said to reside, yet after some number of hours, King Zashim emerged from the chamber alone. As the legend goes, King Zashim said the following words to his aides.",
                  _2 = "\"In the hands of the mighty it was dull and lifeless, devoid of magic... yet... in the hands of the meek it shone with a brilliant golden light that defies description. But no matter how I tried, I could not show that light to anyone else. The codex was meant to remain in these depths for all of eternity. We should seal this place off. My cousin will never return from these caves.\"",
                  _3 = "And so, they sealed the cavern with powerful magic and bound that seal to three magic stones. They gave each stone to a powerful guardian and sent them to three separate strongholds to watch over the stones. I don't believe the guardians knew the true value or purpose of the stones. ",
                  _4 = "Since that day, the passing generations of Palmia's royal family have preserved King Zashim's mandate and we've always deceived the other nations into believing there was nothing of value in Lesimas.",
               },

               mission = {
                  excavation = {
                     _0 = "Complete the excavation of Lesimas and find the room where the codex is kept. And retrieve the <Origin of Vice>.",
                     _1 = "If what Karam told us is true, the codex will be guarded by the late king Zashim's cousin, Zeome. Zeome was known to have been a very powerful warlock. In his day, he was by far the most powerful sorcerer alive. I wouldn't dare confront him unless you are extremely well prepared.",
                  },
                  stones = {
                     _0 = "Your next task is to retrieve the three magic stones. It's said that the stones are the key to unlocking the secrets of Lesimas. We already know where the stones are located, but all three locations are extremely dangerous. First, you should scout the areas, gather info, and build your strength.",
                     _1 = "Your duty will be to penetrate into Lesimas and make contact with <Karam>. In the last report we received from him, he told us he was on the 16th floor. If you can find him, perhaps we can get this excavation back on track. Godspeed, {$1}, find out what happened to <Karam>.",
                  },
               },

               castle = {
                  _0 = "The <King's Magic Stone>, along with numerous other treasures, sleeps deep in the recesses of the vaults of the Ancient Castle, which was built by a long forgotten generation of the royal family. However, the royal family eventually relocated to Palmia and the former throne of the kingdom fell into disrepair and decay. It has been ages since anyone even set foot in the old castle...",
                  _1 = "After <Lord Wynan> took charge of the castle in the first century, even the thugs of Derphy became too scared to approach the castle. The danger level in the castle is roughly equivalent to the 17th floor of Lesimas.",
                  _2 = "It is rumored that <Wynan> still rules the throne along with his personally trained army. Legends tell that the deadly halberd he carries, <Rankis>, can drain the life from his enemies with the greatest of ease. It would be wise to boost your resistance to nether... oh, and bear in mind that unless you can time your actions wisely he'll devour you like a dog.",
               },
               inferno = {
                  _0 = "If you head north from Palmia, through the untamed lands, you will eventually see a tower blazing with an aura of flames. The guardian of the tower, a powerful witch named <Quruiza the Red-eyed Deceiver>, watches over the <Sage's magic stone>. ",
                  _1 = "Quruiza's magic is not the only thing you have to fear either, her husband, the <Steel Dragon Corgon> has pledged his strength to her defense. No doubt you'll have to face him as well.",
                  _2 = "I probably don't need to tell you this, but if you plan to brave the tower, you'll need some sort of powerful resistance to heat and flames. If you find you can't hack it inside, I'd suggest you find some way to protect yourself from the heat before venturing back inside. The danger level in the tower is roughly equivalent to the 15th floor of Lesimas. ",
               },
               crypt = {
                  _0 = "The <Crypt of the Damned> is an ancient cave where the walking dead have amassed in droves. It is the most dangerous of the three strongholds. Countless famous adventurers have lost their lives in the crypt, doomed to wander its halls for all eternity as undead.",
                  _1 = "I believe that the <Dark Abomination Issizzle> rules the hallowed crypts. He is a powerful necromancer and his name is feared all across the continent. Issizzle is shrouded in mystery so I'm afraid I can't tell you much more.",
                  _2 = "The crypt of the damned is along the road that runs between Vernis and Palmia. The danger level of the crypt is roughly equivalent to the 25th floor of Lesimas. You will need to be well prepared before venturing into the crypts.",
               },
            },

            introduction = {
               dialog = "You must be {$1}. I've already heard some of the soldiers talking about you. My name is Erystia, and I came to Nefia in order to research the history behind the various labyrinths here. The King has placed me in charge of the expedition to investigate Lesimas. Unfortunately, due to numerous obstacles and an abundance of hostile monsters residing in the caverns, our investigation has made little, if any, progress. It would be very reassuring if we had the strength of adventurers like you backing us up.",

               choices = {
                  pledge_strength = "I will gladly pledge my strength to Palmia.",
                  not_interested = "I'm not interested.",
               },

               not_interested = "Fair enough... but should you change your mind feel free to come back.",
               pledge_strength = {
                  dialog = {
                     _0 = "Fantastic. I hate to admit it, but the castle's regular soldiers have been virtually useless so far...",
                     _1 = "Our objective is to penetrate to the deepest reaches of Lesimas and retrieve the <codex> hidden there. Once we know the true nature of the <codex>, we can complete our research on the ancient dungeon. You probably won't remember all this after hearing it only once, so feel free to ask me about it again.",
                     _2 = "Now, on to the first order of business. We need you to investigate the fate of one of our agents. His name is <Karam>. Like you, he is one of the foremost adventurers in the land. He agreed to assist with the expedition into Lesimas. He had been contributing information to the expedition's limited intelligence on the caverns. However... we haven't heard anything from him in some number of weeks.",
                     _3 = "Your duty will be to penetrate into Lesimas and make contact with <Karam>. In the last report we received from him, he told us he was on the 16th floor. If you can find him, perhaps we can get this excavation back on track. Godspeed, {$1}, find out what happened to <Karam>.",
                  },

                  you_receive = "You receive a key of Lesimas 4th level. Your journal has been updated.",
               },
            },
         },

         karam = {
            dialog = {
               _0 = "Who's there? So... Erystia sent you to find me... as you can see I'm badly wounded. I'm pretty much screwed aren't I? But then... now that you're here maybe I won't have to die in vain after all.",
               _1 = "I have something to ask of you. Relay this message to Erystia for me... Tell her that she must believe me when I say that the one guarding the codex in the depths of Lesimas is none other than former King Zashim's brother, Zeome. He's the one controlling the magic of the codex... or... no, not just the codex, but the whole of Lesimas. He's no longer human... he's something... more.",
               _2 = "But it doesn't end there... You need to know that Saimore from Zanan is also after the codex. But... why?",
               _3 = "The codex Zeome possesses... it's called the <Origin of Vice>. They say it describes the darkness inherent in the world. But if Saimore's widely accepted story about the end of Rehm-Ido and the beginning of the era of Sierre Terre is true, then why would he be after the relic?",
               _4 = "Saimore has been pushing for war against the Eleas. The truth is that Saimore's claim that the irreverent forest destroyed the world of the era of Rehm-Ido is a carefully constructed lie and that the <Meshella> are real. But then, if Saimore's theory was just a deception meant to incite a war, then what is he really after? I have a bad feeling about all of this...",
               _5 = "My role in this saga is at an end... I'll never make it out with these injuries... Deliver my message to the capital quickly... and may the gods of fate watch over you...",
            },

            dies = "{basename($1)} kills himself...",
         },

         garok = {
            dialog = "Don't you see I'm busy!",
         },

         miral = {
            dialog = "Oh oh, what we got, talk about rare! A traveler? I would have given you a feast if it were not Garok that handles today's dinner. You know, his cooking is as loutish as his creations. Oh well, you've come all the way here, what can I do for you?",

            choices = {
               small_medals = "I have some small medals.",
               upgrade_cart = "Can you upgrade my cart?",
            },

            small_medals = "Ho ho ho! You got small medals! Let me see, let me see! Would you like to trade them for one of my proud works?",

            upgrade_cart = {
               dialog = "Upgrade your cart? It's not something I get excited about but if you can give me {$1} small medals, I'll think about it.",

               choices = {
                  give = "Here, take these medals.",
                  go_back = "I think not.",
               },

               give = {
                  dialog = "Here you are.",
                  limit_increased = "Your cart's weight limit has increased by {$1}.",
               },

               go_back = "Huh.",
            },
         },

         pael = {
            festival = "Mommy looks to be in a good condition today. I hate the festival because there are so many people out there but I hope St.Jure will watch over her!",
            after_face = "Why does mommy look so sad? Her face has changed but she's still my mommy. I know my friends will understand too... and if they don't then they're no friends of mine! I'll always be by her side. Always.",
            after_death = "Go away! Never come back again! Bastard!",
            after_sold = "Mommy... where have you gone mommy?",

            before = "Mommy is really sick... but the doctor said she has the ether plague and he can't do anything...",

            give = {
               choice = "(Hand her a potion of cure corruption.)",
               do_not_have = "Liar!",
               you_give = "You give her a potion.",
               dialog = "R-Really? Mommy, mommy! {$1} gave us a cure! Are you gonna be ok now?",
            },

            progress = {
               _0 = "I hope mommy gets better soon!",
               _1 = "Thanks {$1}, you're the best! Mommy's getting better and better.",
               _2 = "Ah, hi {$1}. Thanks to you Mommy's been getting better! But... it still looks like she needs more time before she's really healthy.",
               _3 = "Mommy looks a lot better these days! The doctor said she's gonna be okay. Even the other kids have come to visit her in the past few weeks. I want mommy to be able to play with us soon...",
               _4 = "{$1}! It's mommy... something's wrong! Suddenly she started acting strange and... now her body is changing and... oh gods...",
               _5 = "Mommy! Mommy are you okay? Mommy?",
               _6 = "{$1}, mommy has something to say to you.",
            },
         },

         lily = {
            after_sold = "You are cruel.",

            progress = {
               last = {
                  _0 = "{$1}, I'm sorry you have to see me this way... please don't turn away... don't run. It seems my disease has already progressed too far... my twisted and hideous body... I can never return to normal... the disease is too advanced now.",
                  _1 = "Even though you couldn't cure me, you have my thanks for all that you've done. It was... your efforts were not in vain. You helped Pael make a lot of friends... surely that counts for something.",
                  _2 = "This isn't much, I know, but it's the least I can do. Please accept these gifts.",
               },
               end_life = {
                  dialog = {
                     _0 = "{$1}, I have... I have one final request. Take this knife and... *weep*. If Pael's friends saw me like this, they'd run in fear and treat her with fear and suspicion. As long as she can be happy, I...",
                     _1 = "Please, I'm begging you. Please put me out of my misery...",
                  },

                  choices = {
                     give = "(Give her a potion of cure corruption.)",
                     ["end"] = "(End her life.)",
                     leave = "There's still hope.",
                  },

                  give = {
                     you_hand_her = "You hand her a potion.",
                     dialog = "No matter how many I drink, my body won't return to normal... thank you though...",
                  },

                  ["end"] = "Th-thank you... thank...",
                  leave = "You... you would force me to keep living like this? You'll find there's much suffering and pain in this world that you can't heal with such optimistic words. I'm sorry... I'm sure you know that well, but... I'll be waiting for you to change your mind.",
               },
               festival = {
                  dialog = "Oh, it's already this time of the year. Poor Pael, she should stop worrying about me and go to the festival. We used to visit the St.Jure's statue and pray together around this time.",

                  choices = {
                     give = "(Give her a potion of cure corruption.)",
                     take_care = "Take care.",
                  },

                  give = {
                     dialog = "Oh, thank you. You have a very kind heart, you know. The potion, I feel like the medicine is working better during the festival. Maybe it's the blessing of St.Jure?",
                     you_hand_her = "You hand her a potion.",
                  },

                  take_care = "Thanks for coming to see me. Please enjoy yourself at the festival during your stay.",
               },
               very_late = "*cough* *cough* I'm... sorry... I don't... feel well... *huff* *huff*",
               late = "It's good to see you, {$1}. Hmm? You say I look happy? Hehe, just before you arrived Pael made a snowman outside. She said she made it with her friends. I haven't seen her smile like that since her father died. When I see that snowman through the window, I feel a joy I cannot describe to you.",
               mid = "Thanks for everything you've done for us. The medicine has mostly stopped the pain. If I can get better I promise to play with my daughter to her heart's content... thankfully the other kids in the neighborhood have been coming to visit these past few days. Pael seems quite shy, but even still she's started to talk to them little by little. I hope Pael can make a lot of friends.",
               early = "Oh... I'm sorry you have to see me like this. Pael's father died when she was five... he was eaten by a swarm of putits. Ever since then, she just sits around the house. She's always watching the other kids play from the window, staring longingly like she'd love to join them. I can tell she's torn between watching over me and joining the outside world. She has a kind heart beating in that little chest of hers. She's a bit spoiled, but she's a good kid, he he.",

            },
         },

         raphael = {
            quest = {
               dialog = "Don't you know who I am? I am, by far, without question, doubtlessly and unabashedly, the sexiest man in this town -- if not the whole of North Tyris. I can have any woman I desire. I could even take the princess of Palmia if I wanted. Yet, strange as it sounds, lately I've grown tired of the game. Honestly, I want a woman who will serve me unconditionally and never complain. Why don't you let me keep one of your wives? You'd have my thanks. ",
               choices = {
                  yes = "Sure.",
                  no = "Don't mock me you filthy wretch.",
               },

               yes = "Great. Bring me a fine young girl!",
               no = "Pah, it's not that important anyhow.",
            },

            bring_wife = {
               dialog = "Which one? Who have you brought for me to inspect?",

               choices = {
                  this_one = "How's this one?",
                  go_back = "Forget it.",
               },

               go_back = "Bring me your wife!",

               this_one = {
                  no_such_wife = "Huh?",
                  not_married = "I want your wife, it's pointless if you aren't married!",
                  come_along = "So... this is your wife eh? {$1} is her name? Don't be embarrassed, come along!",
                  leaving = "Ick, you're leaving me with him!?",
                  not_human = "She's...she's not--hiii--She's not even hu--huuuuu--human..",
                  ["end"] = "She's a work of art! Looks like we have the same taste in women. Hey, if you bring me another one as good as this one, I will give you something incredible. ",
               },
            },
         },

         ainc = {
            complete = "Yeeeeck! Yeee-eeeck! Oh, it's you again.",

            quest = {
               dialog = "Yeeeck! Nooo! Don't!! Get away from me!! Yeeeee-eeeck! Hump, oh....excuse me. You...you look like a skilled adventurer. Could you give me your hand? I need to slay the head of Yeek to be promoted to the rank of knight. The duty is too heavy for me....yeeee-eeck! No...! Hump...I don't want to recall anything anymore. Please do this duty for me.",
               choices = {
                  do_it = "I'll do it for you.",
               },

               do_it = "Fantastic! This duty...it's impossible for me. Yeeks live in a dungeon west from here. I'm counting on you.",
               bye = "Yeeeeck!",
               waiting = "Yeeeeck! Noo...! Don't..! That's my nose..! Yeee-eeeck! Hump, oh, it's you...",
               ["end"] = "Oh, you've brought me the head! I can pass the test now. Thank you very much.",
            },
         },

         poppy = {
            complete = "Ruff-ruff!",

            find = {
               dialog = "Woof!",

               choices = {
                  take = "I'll take you",
               },

               you_must_return = "You must return the puppy safely.",
            },
         },

         rilian = {
            complete = "Hello there!",

            quest = {
               dialog = "Oh no, Poppy has disappeared again... He probably got lost in that cave again. Now what do I do, Papa is too busy to deal with this... Oh, Adventurer, go and find Poppy for me. Poppy? He's my puppy, and my best friend.",
               choices = {
                  do_it = "I'll get your puppy.",
               },

               do_it = "Great! I'm sure he's lost in that cave he always plays in. The cave is just outside the east side of town. Thanks in advance.",
               bye = "Poppy...",
               waiting = "Where's Poppy?",
               ["end"] = "Poppy you're safe! Thank you adventurer, you can have this...",
            },
         },

         tam = {
            complete = "Well...actually...I found this inn more comfortable than my house.",

            quest = {
               dialog = "Hey you, are you..uh...alright with cats? Well, those filthy...they creatures took over my house. I've been asking adventurers to clean up the cats from my house ever since but none returned. What's happening in my house? You...can you take a look inside my house?",

               choices = {
                  yes = "No problem.",
                  no = "None of my business.",
               },

               yes = "Thank God. My house is south from here. Be careful, for it is unknown what inhabits my home.",
               no = "Uh...fine...",
               waiting = "Is my home safe from the cats?",
               ["end"] = "What? An evil cat tamer? My God...I have no idea why such a creature took over my home. But uh...thanks anyway.",
            },
         },

         gilbert = {
            complete = "Ah, the bravest of the brave. Care for a drink? Muwahaha!",
            fame_too_low = "Be gone. I have no interest in weak soldiers. Muwahahaha!",

            quest = {
               dialog = {
                  _0 = "By Opatos! You are the famous {$1}, are you not? I have a favor I'd like to ask of someone like you. ",
                  _1 = "I am colonel of the Juere Liberation Army, Gilbert. We're not the true national army, but even so we fully intend to free the Juere Territories from their occupation by those Yerles dogs. However, our army is having a hard time breaking through their strong front lines on the Palmia border. We only have our swords against their advanced weapons, after all. If things go on like they are, our army might be totally annihalated. So I ask you, will you lend us your power?",
               },

               choices = {
                  yes = "(Hear him out.)",
                  no = "(Don't get involved.)",
               },

               yes = "Mwahahaha! Good, good. We'll be counting on you. Once you've prepared, come speak to me again.",
               no = "Mwahahaha! You damn coward!",

               begin = {
                  dialog = "Are your preparations complete, then?",

                  choices = {
                     yes = "They are.",
                     no = "Not yet.",
                  },

                  yes = "Hahaha! I pray Opatos' favor be with you!",
                  no = "We're waiting on you.",
               },

               ["end"] = "Muwahahahah! Muwahahahahaha! Mu-mu...wa..! *cough* *cough* My...My apologies. Your heroic figure striding the battlefield was so amazing that even I was shaken. With this, the Liberation Army can pass the borders of Palmia. Please, accept this reward as my thanks.",
            },
         },

         arnord = {
            complete = "I hope we can talk again sometime, {$1}!",

            quest = {
               dialog = "Right now, the 10th regiment of the Palmian army is entrenched in battle with the suicide squadron! The enemy has broken through our suppression fire and now they're assaulting us with suicide bombers. The enemy know they're going to die and they're trying to take us with them. How can we fight an enemy with no regard for his own life! At this rate it looks like we'll be totally annihilated! We need you to lend us your hand and lead the reinforcements.",

               choices = {
                  yes = "I accept.",
                  no = "That sounds... dangerous. No thanks.",
               },

               yes = "Thank the gods. Call me when you're prepared. Be sure to bring a ranged weapon!",
               no = "I'm sorry to hear that.",

               begin = {
                  dialog = "Are you ready to go? We need you to hold off the suicide squadron's onslaught and buy time for the Palmian army to retreat.",

                  choices = {
                     yes = "Okay, let's roll.",
                     no = "I'm not ready yet.",
                  },

                  yes = "I'll guide you to the battlefield then. Whatever you do, don't let them get close! I'll tell the Palmian army to begin a steady retreat.",
                  no = "Hurry up!",
               },

               ["end"] = "Well done. I cannot believe you made it back alive! I've heard my comrades are safe. I can find no words to express my gratitude. Please take this reward.",
            },
         },

         mia = {
            complete = "Mia's happy happy nyah!",

            quest = {
               dialog = "Nyobody knyows the touble Mia's seen, nyobody knyows Mia's Tru-bull. Nuah? Adventurer? Nyou find silver cat for me?",

               choices = {
                  yes = "I'll find one for you!",
                  no = "Oh...God...",
               },

               yes = "Nyowl! Mia trust nyou. Nyo hurting cats!",
               no = "Nyo? Mia can wait nyou. Mia have goood mannyah!",
               waiting = "Nyoroon nyoroon. Nyou still look for Mia's cat?",
               ["end"] = {
                  -- NOTE: Before was one sentence in EN, now is two
                  _0 = "Nyanya! Nyou bring Mia silver cat! Come come, I nyo hurt nyou, nyo hurt nyou.",
                  _1 = "Mia thank you very much. Nyou can have Mia's precious!",
               },
            },
         },

         renton = {
            complete = "I wonder... does my life really have any value?",

            quest = {
               dialog = {
                  _0 = "Talent or no talent... if you're a success it doesn't really matter now does it? My sister came here to Lumiest hoping to make it as an artist. She dearly loved the beauty of all things, but she had no artistic ability. She tried so hard and she pushed her limits to succeed, but in the end she was rejected and it drained all the life out of her. The people here mocked and insulted her; nobody understood her. Then, one winter day, despondent, she jumped into the lake and drowned herself. ",
                  _1 = "I was sure... her obsession with painting had wrecked her health. Her devotion and desire for fame alienated her from ordinary people. But, not long after my sister died, a prodigal artist came here to Lumiest. With hardly any effort, all the things she wanted came to her. Fame, happiness, fortune... ",
                  _2 = "To be privileged, or to be poor, it's all just a matter of fate and inescapable coincidence... Do you understand what it is I'm trying to say? That's right, it's tough for me to explain exactly how I feel. It's just that... I guess I no longer understand the meaning of life... that's all. ",
                  _3 = "I remember my sister really loved a series of children's books illustrated by a woman named Rachel. I'm sure they're really rare, or even impossible to find, but... I'd like to read them just once. I feel that perhaps you can understand how I feel... ",
               },

               brought = "You've brought {$1} book{s($1)}, just for my sake? You have my thanks. If I recall correctly, there are four volumes in the series. If you can find all four for me I'll find some way to thank you. ",

               brought_all = {
                  dialog = {
                     _0 = "Oh! So these are Rachel's storybooks? I feel like I should read them soon... it's been such a long time. Give me a moment to look at them will you. These... these are! And this! And... *Renton bubbles at the mouth* ",
                     _1 = "...",
                     _2 = "... ...",
                     _3 = "... ... ...",
                     _4 = "And this... *huff* *huff* ",
                     _5 = "*A crazed look wells up in Renton's eyes* These books... only a true artistic genius could've painted like this. Effort alone is simply not enough... my sister... no matter how long or hard she tried, she never could've painted such beauty. If the goddess of luck truly exists, I should devote myself to her. I'm sorry... you do deserve a reward. I'd like to be alone for a while... if you don't mind. ",
                  },

                  ehekatl = "\"Mew?\"",
               },
            },
         },

         marks = {
            complete = "Heh, don't worry, I won't break in your house.",
            fame_too_low = "Leave me alone, please.",

            quest = {
               dialog = {
                  _0 = "Ah, you're the famous {$1}, aren't you? You came at a fine time. North of Kapul lies an enigmatic pyramid; you may have heard of it. The pyramid has existed since Nefia was a barren desert where even grass wouldn't grow and it's said that ancient treasure is buried within. However, it's sealed by some bizarre enchantments and is impenetrable... well, it WAS impenetrable.",
                  _1 = "I have received a very strange letter. The sender calls himself Tsen, lord of the Pyramid. He has sent me an invitation to enter his pyramid... However, I am not foolish enough to barge into such a trap. I'll turn this invitation over to you. Of course, I won't let you have it for nothing. 20,000 gold and it's yours.",
               },
               choices = {
                  pay = "Alright, I'll pay.",
               },

               pay = "Deal then. You can keep this invitation.",
               bye = "Heh, talk to me again when you have money.",
            },
         },

         noel = {
            complete = "You're still alive I see. Good luck glorious murderer.",

            quest = {
               dialog = {
                  _0 = "Hey, you're not from around here are you? I can tell just by your smell. The world out there... it's taught me that the meek are inevitably used, abused, and then chewed up and swallowed kicking and screaming. The people here are a rank lot, you won't win them over with sympathy and compassion. Don't you ever wonder how people like that can survive? Don't you want to know? ",
                  _1 = "It's so simple, we live by feeding off of others. Spite, hatred, wickedness, and unrelenting cutthroat vigor are the only strengths you can rely on in this town. The outside world looks down on our lot, so we will make the outside world recognize our might. Say, stranger, why don't you join me in my world?",
               },

               choices = {
                  of_course = "Of course I will.",
               },

               of_course = "Looks like you're one of us after all. I can't give you a welcome feast, but I can tell you a delicious little story. When I imagine others suffering, whimpering in pain and misery, I get goose bumps. How divine! At the inn in Palmia, there's a stuffed toy laying on the floor of the private room. Stick this bomb inside that toy for me. If you can drown those mindless ants in blood for me, I'll reward you well ",
               bye = "Then find somewhere else to stand, coward.",

               buy_nuke = {
                  dialog = "Here, you need a nuke. Only 12000 gold pieces.",

                  choices = {
                     buy = "I'll buy.",
                  },

                  buy = "Go, make the brilliant blood red roses bloom.",
                  bye = "Then go away.",
               },

               waiting = "Go, make the brilliant blood red roses bloom.",
               ["end"] = "I can feel it already... the suffering... the misery... the pain... You've killed many people this day, you should be proud. Little kids, girls, women, old men, the sick, the feeble, even those neither born nor conceived yet. My body's hot, excited, I can hardly breathe... I won't be able to sleep tonight. My thanks, these are for you. ",
            },
         },

         icolle = {
            complete = "I don't have time to talk, I'm busy conducting experiments. Out of the way!",

            quest = {
               dialog = "Oh oh oh! You've come at *just* the right time. I'm so busy I'd take help from a cat if I had to. I'm doing research in the most remarkable field of genetic engineering. You see, I can take two living creatures and combine them to produce an even stronger creature! Is that not the most amazing thing you've ever heard? I need five test subjects for the final stage of the experiment. Won't you go get some for me? I'll reward you with the gene splicing machine I'm building.",
               choices = {
                  alright = "Alright, I'll see what I can do.",
               },

               alright = "Good good! Take these monster balls with you. Do you know how to use them? Yes yes, throw them at a monster when it is near death. The ball won't work if the monster is too high in level, so be careful. Please bring me five captured monsters. Oh... and... *please* bring them back to me IN the balls!",
               bye = "Then get out of my way you fool!",

               give = {
                  deliver = "You deliver {itemname($1, 1)}.", -- TODO duplicate
                  have = "Oh oh! What a fine batch of samples you've brought me. I can finally proceed with the final stage.",
                  do_not_have = "Let's go over this one last time... I need five samples to proceed. FIVE.",
               },

               ["end"] = "Success! The experiment is a huge success! You've done a great job! To express my thanks I'll let you use my gene splicing machine. Please take good care of it.",
            },
         },

         balzak = {
            complete = "Clean! The roads are clean in Lumiest today!",

            quest = {
               dialog = {
                  _0 = "Wait there! Wait!",
                  _1 = "I'm Balzak, a well known pro garage man who has been cleaning the roads of Lumiest for 10 years. I've never missed a single garbage that messes the beautiful town of Lumiest. But my days are over. Foul creatures now nest in the sewer and sick smells spread everywhere. Adventurer, you are my only hope. Kill them, kill them for my sake!",
               },

               choices = {
                  yes = "Alright.",
                  no = "I'm not interested.",
               },

               yes = "That's the word I wanted to hear! You'll find the sewer entrance near the inn. Be aware, they are pretty tough.",
               no = "Ok. You are cruel.",
               waiting = "Oh, it's you. What about the task I asked you?",
               ["end"] = "Whaaat! You've really done it? Amazing! Here, take it, you deserve this.",
            },
         },


         lexus = {
            nonmember = {
               dialog = "Halt...the stairs lead to the Mages Guild office. Only the members of the guild are allowed to enter.",

               choices = {
                  tell_me_about = "Tell me about the Mages Guild.",
                  want_to_join = "I want to join the Mages Guild.",
               },

               tell_me_about = "The Mages Guild is made up by experienced and confirmed experts in their field of magic. We offer a variety of services such as discounted spellbook prices, reservation of spellbooks, and training related skills. But joining the Mages Guild requires you to pass a difficult test that most common mages will fail.",
               want_to_join = {
                  _0 = "So you are interested in joining our guild and we only need elite mages. Let's see if you are worthy of becoming one of us.",
                  _1 = "In north Tyris, there are several ancient books encrypted with an unique rune language. Should you want to join the guild, put them into the delivery chest after you have decrypted them and we shall reward you with guild points.",
                  _2 = "You will need to gather 30 guild points in order to enter the Mages Guild. Until then, we have no more to speak.",
               },

               quota = "To pass the test, you need to gather 30 guild points.",

               ["end"] = {
                  _0 = "Quite impressive...you have accomplished the task.",
                  _1 = "Congratulations. You are a formal member of the Mages Guild now. You can now use this stairs to enter the office. Always conform to the guild's rule and perform your tasks.",
               },

               joined = "You have joined the Mages Guild!",
            },

            member = {
               dialog = "Welcome to the Mages Guild, {$1} {$2}... Please come in.",
               choices = {
                  new_quota = "Do you have any tasks for me?",
                  report_quota = "About my task.",
               },

               new_quota = "Sure, there're plenty of tasks for you. For now, collect the ancient books and decrypt them. When you gather {$1} guild points, we will think about your promotion.",
               report_quota = {
                  waiting = "You have your task to complete.",
                  ["end"] = "You've done very well. I will give a report of your achievement to the council.",
               },
            },
         },

         abyss = {
            nonmember = {
               dialog = "Halt...the stairs lead to the Thieves Guild office. Only the members of the guild are allowed to enter.",

               choices = {
                  tell_me_about = "Tell me about the Thieves Guild.",
                  want_to_join = "I want to join the Thieves Guild.",
               },

               tell_me_about = "The Thieves Guild is made up by experienced and confirmed experts in their field of the shadow arts. We offer a variety of services such as buying stolen goods, discount at black markets, and training related skills. But joining the Thieves Guild requires you to pass a difficult test that most common thieves will fail.",
               want_to_join = {
                  _0 = "So...you're interested in our guild? We hide in the shadows of the society. You must win our trust to enter the guild.",
                  _1 = "It is a simple task. We require you to not pay tax for 4 months. Take it granted the guards will try to hunt you down. If you aren't ready to face it, just forget it.",
               },

               quota = "I've already told you what you must do. Don't pay tax for 4 months.",

               ["end"] = {
                  _0 = "Quite impressive...you have accomplished the task.",
                  _1 = "Congratulations. You are a formal member of the Thieves Guild now. You can now use this stairs to enter the office. Always conform to the guild's rule and perform your tasks.",
               },

               joined = "You have joined the Thieves Guild!",
            },

            member = {
               -- TODO much duplication
               dialog = "Welcome to the Thieves Guild, {$1} {$2}... Please come in.",

               new_quota = "Alright. The Thieves Guild wants you to put stolen goods into circulation. Steal some goods and sell them to any vendors. When the sum of your earning reaches {$1} gold pieces, we will think about your promotion.",
            },
         },

         doria = {
            nonmember = {
               dialog = "Halt...the stairs lead to the Fighters Guild office. Only the members of the guild are allowed to enter.",

               choices = {
                  tell_me_about = "Tell me about the Fighters Guild.",
                  want_to_join = "I want to join the Fighters Guild.",
               },

               tell_me_about = "The Fighters Guild is made up by experienced and confirmed experts in their field of the fighting. We offer a variety of services such as reduced prices of identification and restoring, and training related skills. But joining the Fighters Guild requires you to pass a difficult test that most common fighters will fail.",
               want_to_join = {
                  _0 = "To join the Fighters Guild, you must first face a test to earn our trust. We only need skilled hunters who will obey our law and remain undaunted even in a desperate battle.",
                  _1 = "The task given to you is this. Find and slay {$1} {$2}. When you complete this, talk to me again.",
               },

               quota = "You still need to slay {$1} more {$2}.",

               ["end"] = {
                  _0 = "Quite impressive...you have accomplished the task.",
                  _1 = "Congratulations. You are a formal member of the Fighters Guild now. You can now use this stairs to enter the office. Always conform to the guild's rule and perform your tasks.",
               },

               joined = "You have joined the Fighters Guild!",
            },

            member = {
               -- TODO much duplication
               dialog = "Welcome to the Fighters Guild, {$1} {$2}... Please come in.",

               new_quota = "There's a task for you. Go find and slay {$1} {$2}. Then we will think about your promotion.",
            },
         },

         conery = {
            complete = "Ahh it's you. I owe you for what you've done for me. What do you say? Why don't you join my unit?",

            quest = {
               dialog = "What do I do about this... You, over there... You couldn't have gotten here a moment too soon. Yowyn is in great danger of being destroyed by the minotaur legion. The mayor of Yowyn is a close friend of mine and I don't want to leave him out in the cold. I want to send a detachment to reinforce him but I can't. The current political climate in Palmia is too volatile and the troops must remain in the castle. That's why I'm asking an adventurer like you. Will you attack the minotaur's camp for me? I will reward you handsomely if you do this.",

               choices = {
                  do_it = "Leave it to me!",
                  bye = "No way.",
               },

               do_it = "What? You will? Great... Head to the Minotaur's Nest south of Yowyn and take the head of the minotaurs' king. Godspeed, ",
               bye = "I knew you'd refuse... and after all, why wouldn't you?",
               waiting = "What's wrong? You must make haste. Yowyn is in grave danger.",
               ["end"] = "You've returned. I've been waiting for you. I've already heard the good word about the hero who crushed the minotaur king. Take this as a sign of my eternal gratitude.",
            },
         },

         rogue_boss = {
            too_poor = "Bah, a beggar without a penny. What a waste of time! Just go away!",

            ambush = {
               dialog = "Halt, halt, traveler. You're a quite fortunate one. Before you is the renowned band of legendary brigands \"{$1}\" that the mere mention of its name is enough to silence a naughty child. Yet we will spare your life for only a toll of {$2} gold pieces and your cargos. Quite fortunate indeed.",

               choices = {
                  try_me = "Try me.",
                  surrender = "I surrender.",
               },

               try_me = "You've got some guts. But your decision sure ain't a wise one. This will be your grave, kid.",
               surrender = "A wise choice.",
            },
         },

         strange_scientist = {
            first = "Please, hear me out. If you should happen to run into any little sisters during your travels, please help them out. They seem to be monsters at first glance, but I'm doing important research that will return these girls to their gentle smiling nature. Please I beg of you... use these balls to bring the little sisters to me. I'd be very grateful, perhaps I'd even reward you.",

            dialog = "Many people feel we need to free these girls from their never-ending oppression, but there are also scumbags that would murder them for their own personal gain. That's right; they say eating the girls' flesh will evolve the human body. I know there must be a better way to help them... don't forget that. Remember that if you take their lives, you will eventually get what's coming to you. ",

            choices = {
               reward = "What about the reward you promised me?",
               replenish = "I need to replenish my supply of little balls.",
               turn_over = "(Turn over the little sister.)",
            },

            reward = {
               not_enough = "You haven't brought me enough sisters yet. Bring me a few more and then we'll discuss your reward.",
               dialog = "That's right...your reward. The little sisters have been picking things up for you that people have lost in town. Please, take whatever you like. If you like, you can wait until you've lost something valuable.",
               choose_one = "You can choose 1 item.",
               find = "Did you find what you were looking for?",
            },

            replenish = "Well then, take this with you. Be careful though, it's heavy.",

            turn_over = {
               text = "You turn over the little sister.",
               dialog = "Thanks, I appreciate what you've done. It won't be long before I can reward you.",
            },

            saved_count = "You have saved little sister {$1} times and killed {$2} times.",
         },

         kaneda_bike = {
            after_drug = {
               dialog = "So, you wanted to ride me right?",

               choices = {
                  yes = "Yes!",
                  no = "Not really.",
               },

               yes = {
                  party_full = "Oops, it seems your party is already full.",
                  dialog = "That's the spirit!",
               },

               no = "If you say so.",
            },

            before_drug = {
               dialog = "That-that's a capsule drug! ...hey, you want to give it to me?",

               choices = {
                  yes = "Take it.",
                  no = "Nope.",
               },

               yes = {
                  you_hand_him = "You hand him a capsule drug.",
                  dialog = "Great, you are great.",
               },
            },

            do_not_have_drug = "Stay away from me, will ya?",
         },

         part_time_worker = {
            already_believe_in_jure = "Ah, you already believe in Jure right? Sorry bro, but we are only looking for new contracts.",

            dialog = "We are running a special campaign to help you join our religion! Be a brother of Jure today and win free body pillow of Jure! During the festival, you won't have to pay penalty to convert your religion neither. So what are you waiting? Sign up now!",

            choices = {
               yes = "I will become a faithful servant of Jure.",
               no = "Not interested.",
            },

            yes = {
               dialog = "Okie, just making sure. Do you really want to convert your religion?",

               choices = {
                  yes = "Yes.",
                  no = "No.",
               },

               yes = "Thanks, bro! I just filled my daily quota.",
            },

            no = "Shit!",
         },
      },
   },
}
