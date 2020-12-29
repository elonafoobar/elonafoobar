local I18N = ELONA.require("core.I18N")

I18N.add {
   chara = {
      you = "you",
      something = "something",

      age_unknown = "Unknown",

      quality = {
         miracle = "<{$1}>",
         godly = "{{{$1}}}",
      },

      contract_expired = "The period of contract with {basename($1)} has been expired.",

      corruption = {
         symptom = "The symptom of the Ether disease is shown up on you.",
         add = "Your disease is getting worse.",
         remove = "The symptoms of the Ether disease seem to calm down.",
      },

      gain_level = {
         self = "{name($1)} have gained a level.",
         other = "{name($1)} {have($1)} grown up.",
      },

      weight = {
         gain = "{name($1)} gain{s($1)} weight.",
         lose = "{name($1)} lose{s($1)} weight.",
      },

      height = {
         gain = "{name($1)} grow{s($1)} taller.",
         lose = "{name($1)} grow{s($1)} smaller.",
      },

      place_failure = {
         ally = "{name($1)} loses {his($1)} way.",
         other = "{name($1)} is killed.",
      },

      impression = {
         gain = "Your relation with {basename($1)} becomes <{$2}>!",
         lose = "Your relation with {basename($1)} becomes <{$2}>...",
      },

      job = {
         general_vendor = "{trim_job($1)}the general vendor",
         innkeeper = "{trim_job($1)}the innkeeper",
         trader = "{trim_job($1)}the trader",
         goods_vendor = "{trim_job($1)}the goods vendor",
         baker = "{trim_job($1)}the baker",
         magic_vendor = "{trim_job($1)}the magic vendor",
         blacksmith = "{trim_job($1)}the blacksmith",
         trainer = "{trim_job($1)}the trainer",
         fisher = "{trim_job($1)}the fisher",
         blackmarket = "{trim_job($1)}the blackmarket vendor",
         food_vendor = "{trim_job($1)}the food vendor",
         souvenir_vendor = "{trim_job($1)}the souvenir vendor",

         -- Vernis
         of_vernis = "{$1} of Vernis",

         -- Palmia
         of_palmia = "{$1} of Palmia city",

         -- Noyel
         street_vendor = "{trim_job($1)}the street vendor",
         street_vendor2 = "{trim_job($1)}the street vendor",
         of_noyel = "{$1} of Noyel",
         fanatic = {
            "Opatos Fanatic",
            "Mani Fanatic",
            "Ehekatl Fanatic",
         },

         -- Yowyn
         horse_master = "{trim_job($1)}the horse master",
         of_yowyn = "{$1} of Yowyn",

         -- Derphy
         slave_master = "The slave master",
         of_derphy = "{$1} of Derphy",

         -- Port Kapul
         of_port_kapul = "{$1} of Port Kapul",

         -- Lumiest
         of_lumiest = "{$1} of Lumiest",

         -- High Mountain
         dye_vendor = "{trim_job($1)}the dye vendor",

         -- Mages Guild
         spell_writer = "{trim_job($1)}the spell writer",

         -- Thieves Guild
         fence = "{trim_job($1)}the fence",

         -- Encounter
         wandering_vendor = "{trim_job($1)}the wandering vendor",


         own_name = "{$2} the {$1}",

         alien = {
            child = "child",
            alien_kid = "alien kid",
            child_of = "child of {$1}",
         },

         shade = "shade",
      },

      garbage = "a garbage",
   },
}



I18N.add_data_text(
   "core.chara",
   {
      bug = {
         name = "bug",
      },
      user = {
         name = "user",
      },
      shopkeeper = {
         name = "shopkeeper",
         text_101 = {"\"Guard! Guard!\"", "\"Ambush!\"", "\"You thief!\""},
         text_102 = {"\"Please spare my life.\"", "\"Ahhhh....\""},
         text_103 = {"\"Die thief.\"", "\"You deserve this.\""},
      },
      caravan_master = {
         name = "caravan master",
      },
      bartender = {
         name = "bartender",
         text_100 = {"You hear the sound of cocktail shakers.", "\"How 'bout a drink sir?\"", "\"We got vintage crim ales.\"", "The bar is crowded with people."},
         text_101 = {"\"Hey, stop it drunkard.\"", "\"Are you sick from drinking too much?\""},
         text_102 = {"\"I got killed by a drunkard.\"", "\"This is ridiculous.\""},
         text_104 = {"\"Welcome home. I've got some decent ales for you.\"", "\"Are you tired? How'bout a drink?\""},
         text_103 = "\"Sober up now huh?\"",
      },
      informer = {
         name = "informer",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      arena_master = {
         name = "arena master",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      healer = {
         name = "healer",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
         text_104 = {"\"Are you wounded?\"", "\"Good to see you again. Welcome home.\""},
      },
      nun = {
         name = "sister",
         text_100 = {"You hear the chants of prayer in the distance.", "\"Come hither stray kittens, I shall guide you to the light.\"", "\"Pray hard. There's always chance for salvation.\"", "\"Do unto others as you wish others to do unto you.\""},
         text_101 = {"\"Atone for you sin.\"", "\"Well, you need to be punished.\"", "\"You sonova...\"", "\"Shit!\""},
         text_102 = "\"God help me!\"",
         text_104 = {"\"Are you wounded?\"", "\"Good to see you again. Welcome home.\""},
         text_103 = "\"Go to hell.\"",
      },
      elder = {
         name = "elder",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      trainer = {
         name = "trainer",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      guild_trainer = {
         name = "guild trainer",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      guard_port_kapul = {
         name = "guard",
         text_101 = {"\"Stop there criminal!\"", "\"You scum! Stay there.\"", "\"You are under arrest.\"", "\"You will pay for your sin.\""},
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      guard = {
         name = "guard",
         text_101 = {"\"Stop there criminal!\"", "\"You scum! Stay there.\"", "\"You are under arrest.\"", "\"You will pay for your sin.\""},
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      palmian_elite_soldier = {
         name = "palmian elite soldier",
         text_101 = {"\"Who the hell released this monster!\"", "\"Fire, fire, fire!\"", "\"This is ridiculous.\"", "\"Blood! My blooood!\"", "\"Holy cow!\"", "\"What is THIS?\"", "\"Go go go!\""},
         text_102 = {"\"Ok, I'm done.\"", "\"Arrrrrggghhh!\"", "\"Man down! Man down!\"", "\"M-Medic!\"", "\"We got another man killed!\""},
      },
      zeome = {
         name = "<Zeome> the false prophet",
         text_100 = "You hear raspy bitter laughter in the distance...",
         text_101 = "\"Fool!\"",
         text_102 = "\"Impossible!\"",
         text_103 = "\"Hahaha!\"",
      },
      at = {
         name = "@",
         text_100 = "\"Qy@\"",
         text_101 = "\"Qy@!!\"",
         text_102 = "\"Q...Qy...@\"",
         text_103 = "\"Qy@!\"",
      },
      orphe = {
         name = "<Orphe> the chaos child",
         text_100 = {"You hear childish laughter, only it's oddly distorted in some eldritch manner.", "You have been looking for someone like this..."},
      },
      mad_scientist = {
         name = "<Mad scientist>",
      },
      isca = {
         name = "<Isca> the fallen angel",
      },
      whom_dwell_in_the_vanity = {
         name = "<Whom dwell in the vanity>",
         text_100 = {"You have been struck by a terrible feeling of powerlessness.", "The air around here is heavy and sorrowful. But you somehow feel not all is lost.", "\"Elishe...why did it have to be you...\""},
         text_101 = {"You are like a rabbit fascinated by a snake.", "Someone mutters. \"Worthless.\"", "You sense death."},
         text_102 = "\"Finally...I come to you...Elishe...\"",
         text_103 = "\"I live again...in vain.\"",
      },
      loyter = {
         name = "<Loyter> the crimson of Zanan",
         text_100 = {"Loyter grumbles incessantly. \"How he sounds so miserable...\"", "You hear someone muttering sulfurously somewhere.", "Loyter mutters to himself. \"Why are you still attached to him...\""},
         text_101 = {"\"Oh what a jerk.\"", "\"Die like a maggot you are.\""},
         text_102 = "\"You are shit.\"",
         text_103 = "\"Huh? Done already?\"",
      },
      vesda = {
         name = "<Vesda> the fire dragon",
      },
      miches = {
         name = "<Miches> the apprentice",
         text_100 = {"You hear childish laughter nearby.", "\"You know your face is funny looking. Were you born that way?\"", "\"How are your travels? I'd love to go but I'm stuck here...\"", "\"I'm so bored. Maybe we can play a game of Putits & Yeeks later.\""},
         text_101 = {"\"You molester!\"", "\"Stop it!\""},
         text_102 = "\"N-Nooo...\"",
         text_103 = "\"You are so weak.\"",
      },
      shena = {
         name = "<Shena> the draw",
         text_100 = {"\"Come on in! The ale is flowing well tonight!\"", "\"Hey! Keep yer stinking hands of the serving ladies!\"", "The rowdy crowd is making a fair bit of noise tonight.", "You hear the sound of tankerds striking in a toast."},
         text_101 = {"\"You are drinking too much!\"", "\"Stop it before I get angry.\""},
         text_102 = "\"Why me?\"",
         text_103 = "\"Ahhh! Are you alright, sir?\"",
      },
      the_leopard_warrior = {
         name = "<The leopard warrior>",
         text_100 = {"\"Aural...it seems I know that name.\"", "\"Lady Silvia, you are my only princess.\""},
         text_101 = {"\"If Jarn wishes, then let it be done.\"", "\"Grrrrrr!\"", "\"Doal!\""},
         text_102 = "\"Me...meow....\"",
         text_103 = "\"Let Janus decide your fate.\"",
      },
      silvia = {
         name = "<Silvia> The princess",
         text_100 = {"\"Come on, you stupid leopard! You ignorant, mean, stupid, uncouth numbnut!\"", "\"Don't touch! Don't touch me, leopard!\"", "You hear someone stamping her feet."},
         text_101 = {"\"I will beat you with a whip!\"", "\"You...you insolent peasant! I will bring you to the scaffold!\""},
         text_102 = {"\"To hell with me!\"", "\"Villain! Devil! Fiend! Murderer, murderer murderer!\""},
         text_103 = "\"And you promised you wouldn't leave me alone...\"",
      },
      dungeon_cleaner = {
         name = "<Dungeon cleaner>",
         text_100 = {"*bzzzz*whirrrrrrr*click*", "Something is buffing the floor at an inhuman speed."},
         text_101 = {"\"Target acquired!\"", "\"Resistance is futile!\""},
         text_102 = "\"Pwned!\"",
         text_103 = "\"WTF\"",
      },
      larnneire = {
         name = "<Larnneire> the listener of wind",
         text_100 = {"\"You know the fairy tale where a wicked witch transforms a dashing prince into an monster?\"", "The stunning beauty of Elea's face halts your step a moment.", "\"The world is thrown into bedlam and chaos. We must remain strong in the face of it.\"", "\"The man we saw in Vernis, he just might be...\"", "Someone mutters in mysterious ancient language.", "\"Eleas is already being regarded as a heretic, your lofty dignity isn't helping this.\""},
         text_101 = {"\"Do we really have to fight?\"", "\"Sorry, I don't have time for this.\"", "The Elean little girl has an angry look in her beautiful cold eyes."},
         text_102 = "\"A-ah...I failed my task...this world....this world will....\"",
         text_103 = "\"Sorry...\"",
      },
      lomias = {
         name = "<Lomias> the messenger from Vindale",
         text_100 = {"\"Wait'll they hear the news we bring. And they think they have problems. Hah!\"", "\"Hey... This is a fine looking cave. I oughta enquire about it sometime. Everyone needs a hideaway...\"", "\"Pah! It would take a child less than a day to walk to Vernis, we won't be late.\"", "\"Man, that girl at the pub... She could clean my glass if you know what I mean!\"", "You hear someone testing the string of his bow."},
         text_101 = {"\"You repay kindness with ingratitude?\"", "\"Do you really mean it?\""},
         text_102 = "\"Jesus...you are kidding...\"",
         text_103 = "\"There's always someone I can never understand.\"",
      },
      slan = {
         name = "<Slan> the shadow of Palmia",
         text_100 = {"\"H-help me... please...\"", "\"Is someone there? Help me... The King must be forewarned!\"", "You hear cries of help echoing off the walls. They sound quite weak...."},
      },
      karam = {
         name = "<Karam> the lonely wolf of Karune",
         text_100 = {"\"Curse my weakness! This shouldn't have happened.\"", "\"This place will be the end of me I fear.\"", "You hear a low moan of pain somewhere."},
      },
      erystia = {
         name = "<Erystia> the scholar of history",
         text_100 = {"\"I wonder what the runic translation of this is...\"", "\"Hmm...interesting. Interesting indeed...\"", "You hear someone arranging books on shelves."},
         text_101 = {"\"Stop it, please!\"", "\"Why are you doing this?\""},
         text_102 = "\"How can you....\"",
         text_103 = "\"You are useless!\"",
      },
      issizzle = {
         name = "<Issizzle> the dark abomination",
      },
      wynan = {
         name = "<Wynan> the lord of the Ancient Castle",
      },
      quruiza = {
         name = "<Quruiza> the red-eyed Deceiver",
      },
      corgon = {
         name = "<Corgon> the steel dragon",
      },
      lulwy = {
         name = "<Lulwy>",
      },
      ehekatl = {
         name = "<Ehekatl>",
      },
      god_inside_ehekatl = {
         name = "<God inside Ehekatl>",
      },
      opatos = {
         name = "<Opatos>",
      },
      kumiromi = {
         name = "<Kumiromi>",
      },
      mani = {
         name = "<Mani>",
      },
      _test = {
         name = "_test",
      },
      putit = {
         name = "putit",
         text_102 = "*putit*",
      },
      red_putit = {
         name = "red putit",
         text_102 = "*putit*",
      },
      slime = {
         name = "slime",
         text_102 = "*putit*",
      },
      acid_slime = {
         name = "acid slime",
         text_102 = "*putit*",
      },
      bubble = {
         name = "bubble",
         text_102 = "*putit*",
      },
      blue_bubble = {
         name = "blue bubble",
         text_102 = "*putit*",
      },
      mass_monster = {
         name = "mass monster",
      },
      cube = {
         name = "cube",
      },
      rabbit = {
         name = "rabbit",
      },
      snail = {
         name = "snail",
         text_100 = "*Zzzzle*",
      },
      fallen_soldier = {
         name = "fallen soldier",
         text_101 = {"\"What the hell!\"", "\"You will regret this.\"", "\"Ok, no turning back now.\"", "\"Now you die!\"", "\"Come on chicken.\"", "\"Huh.\"", "\"You touch me, you die.\""},
         text_102 = {"\"You....you will pay for this someday...\"", "\"Nooo!\"", "\"A murderer!\"", "\"Stop it!\"", "\"F-forgive me...\"", "\"Arrr--rr...\"", "\"D-don't!\""},
         text_103 = {"\"Look at you.\"", "\"Bye bye.\""},
      },
      mercenary = {
         name = "mercenary",
         text_101 = {"\"What the hell!\"", "\"You will regret this.\"", "\"Ok, no turning back now.\"", "\"Now you die!\"", "\"Come on chicken.\"", "\"Huh.\"", "\"You touch me, you die.\""},
         text_102 = {"\"You....you will pay for this someday...\"", "\"Nooo!\"", "\"A murderer!\"", "\"Stop it!\"", "\"F-forgive me...\"", "\"Arrr--rr...\"", "\"D-don't!\""},
         text_103 = {"\"Look at you.\"", "\"Bye bye.\""},
      },
      beggar = {
         name = "beggar",
         text_101 = {"\"P-please, no sir...\"", "\"Waaaa!\"", "\"You get nothing from killing me...\"", "\"Don't make a fool of me!\"", "\"Why are you doing this?\"", "\"A violent revolution!\"", "\"W-w-what...!\""},
         text_102 = {"\"You are cruel.\"", "\"Ahhhh!\"", "\"I don't deserve this...\"", "\"It's unfair.\"", "\"Beggars always cry...\"", "\"My life is pathetic.\""},
         text_103 = {"\"Weak! Weak!\"", "\"Huh?\"", "\"Ha ha ha!\""},
      },
      farmer = {
         name = "farmer",
         text_103 = "\"Weak!\"",
      },
      cleaner = {
         name = "cleaner",
      },
      miner = {
         name = "miner",
      },
      bard = {
         name = "bard",
         text_100 = {"\"Oh I once heard of a place called Nantucket...\"", "\"Ninety-nine Yeeks in a dank hole. Ninety-nine Yeeks in a Hole!\"", "\"Crawling in my Robes! These wounds will need a Healer!\"", "\"If you go down to the woods today. You're sure of a big surprise. If you go down to the woods today. You'd better go in disguise.\""},
         text_101 = {"\"-Stop it..!\"", "\"Was my music that bad?\""},
         text_102 = {"\"No way!\"", "\"It's a bitter tirade.\"", "\"Did I suck that bad?\" "},
      },
      sister = {
         name = "sister",
      },
      holy_beast = {
         name = "holy beast",
         text_100 = {"\"Happy holy night!\"", "The town is awash with people arriving at the festival and drums and whistles make a merry rhythm.", "\"It's a festival!\"", "You feel excited.", "Fervor!"},
      },
      part_time_worker = {
         name = "part time worker",
         text_100 = {"\"St.Jure's body pillow for FREE!\"", "\"Step right up!\"", "\"You there lucky one, a beautiful and sweet woman awaits for you!\"", "\"A flower growing in the desert, fragile yet most noble. A maiden pure in heart with compassion and indomitable will to vanquish evil. Jure of Healing, our only Goddess!\""},
      },
      fanatic = {
         name = "Jure fanatic",
         text_100 = {"\"Jure, oh holy Jure, forgive our sins and purify us from all unrighteousness.\"", "\"We're so ready to see you, Goddess Jure!\"", "\"Glory to Jure! May the victory always be with Jure!\"", "\"Come, become a new servant of Jure today.\"", "\"Death to the heretic! Crack down those who bring shame to the name of Jure!\""},
      },
      rogue = {
         name = "rogue",
      },
      prostitute = {
         name = "prostitute",
      },
      prisoner = {
         name = "prisoner",
      },
      artist = {
         name = "artist",
      },
      noble = {
         name = "noble",
      },
      mage_guild_member = {
         name = "mage guild member",
      },
      thief_guild_member = {
         name = "thief guild member",
      },
      fighter_guild_member = {
         name = "fighter guild member",
      },
      town_child = {
         name = "town child",
         text_101 = {"\"H-help-!\"", "\"No no!\"", "\"You are evil.\"", "\"Pervert!\"", "\"G-g-go away!\"", "\"Why are you teasing me?\"", "\"Adults.\""},
         text_102 = {"\"Mom....\"", "\"A---ahh-\"", "\"Go to hell!\"", "\"Waaaan!\"", "\"Urghhh!\"", "\"My life ends here.\"", "\"Sorry, mom, dad....\""},
         text_103 = "\"Weak! You are weak!\"",
      },
      old_person = {
         name = "old person",
         text_101 = {"\"Stop it, please.\"", "\"Unreasonable!\"", "\"You foul scum.\"", "\"Fool!\"", "\"Youngsters.\"", "\"Respect elders!\"", "\"Leave me alone.\""},
         text_102 = {"\"God will punish you.\"", "\"My remaining years...\"", "\"Demon!\"", "\"Grrhhh\"", "\"I hate this planet.\"", "\"Am I dead?\""},
         text_103 = {"\"Holy...why are you so weak?\"", "\"Muwahahaha!\""},
      },
      punk = {
         name = "punk",
      },
      wild_sheep = {
         name = "wild sheep",
      },
      flying_frog = {
         name = "flying frog",
      },
      gangster = {
         name = "gangster",
      },
      kobold = {
         name = "kobold",
      },
      yeek = {
         name = "yeek",
      },
      yeek_warrior = {
         name = "yeek warrior",
      },
      yeek_archer = {
         name = "yeek archer",
      },
      master_yeek = {
         name = "master yeek",
      },
      kamikaze_yeek = {
         name = "kamikaze yeek",
      },
      kamikaze_samurai = {
         name = "kamikaze samurai",
      },
      bomb_rock = {
         name = "bomb rock",
      },
      hard_gay = {
         name = "hard gay",
         text_100 = {"\"Foooooo!\"", "\"Fooooo\"", "\"Foooooo!\""},
         text_101 = {"\"Foooooo!\"", "\"Fooooo\"", "\"Foooooo!\""},
         text_102 = {"\"Foooooo!\"", "\"Fooooo\"", "\"Foooooo!\""},
         text_104 = {"\"Foooooo!\"", "\"Fooooo\"", "\"Foooooo!\""},
         text_103 = {"\"Foooooo!\"", "\"Fooooo\"", "\"Foooooo!\""},
      },
      rodlob = {
         name = "<Rodlob> the boss of yeeks",
      },
      hot_spring_maniac = {
         name = "citizen",
      },
      centipede = {
         name = "centipede",
      },
      mushroom = {
         name = "mushroom",
      },
      spore_mushroom = {
         name = "spore mushroom",
      },
      chaos_mushroom = {
         name = "chaos mushroom",
      },
      citizen = {
         name = "citizen",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      citizen2 = {
         name = "citizen",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      citizen_of_cyber_dome = {
         name = "citizen of cyber dome",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      citizen_of_cyber_dome2 = {
         name = "citizen of cyber dome",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      sales_person = {
         name = "sales person",
      },
      sailor = {
         name = "sailor",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      captain = {
         name = "captain",
         text_102 = {"\"I was a good citizen.\"", "\"Go to hell!\"", "\"I give up.\"", "\"Nooooo.....\"", "\"Is it a joke?\"", "\"Why me.\"", "\"W-What have you done!\""},
      },
      stersha = {
         name = "<Stersha> the queen of Palmia",
         text_100 = {"The quiet majesty of the room makes you feel small and grubby.", "You note just how alert and well armed the guards are.", "Somewhere, a harpsichord is playing a tune befitting nobility."},
      },
      xabi = {
         name = "<Xabi> the king of Palmia",
      },
      orc = {
         name = "orc",
      },
      lizard_man = {
         name = "lizard man",
      },
      minotaur = {
         name = "minotaur",
      },
      minotaur_magician = {
         name = "minotaur magician",
      },
      minotaur_boxer = {
         name = "minotaur boxer",
      },
      minotaur_king = {
         name = "minotaur king",
      },
      ungaga = {
         name = "<Ungaga> the minotaur king",
      },
      troll = {
         name = "troll",
      },
      warrior_of_elea = {
         name = "warrior of Elea",
      },
      wizard_of_elea = {
         name = "wizard of Elea",
      },
      asura = {
         name = "asura",
      },
      mitra = {
         name = "mitra",
      },
      varuna = {
         name = "varuna",
      },
      wizard = {
         name = "wizard",
      },
      warrior = {
         name = "warrior",
      },
      mandrake = {
         name = "mandrake",
      },
      beetle = {
         name = "beetle",
      },
      orc_warrior = {
         name = "orc warrior",
      },
      goda = {
         name = "<Goda> the captain of orc",
      },
      zombie = {
         name = "zombie",
      },
      bat = {
         name = "bat",
      },
      vampire_bat = {
         name = "vampire bat",
      },
      dragon_bat = {
         name = "dragon bat",
      },
      fire_ent = {
         name = "fire ent",
      },
      ice_ent = {
         name = "ice ent",
      },
      lich = {
         name = "lich",
      },
      master_lich = {
         name = "master lich",
      },
      demi_lich = {
         name = "demi lich",
      },
      executioner = {
         name = "executioner",
      },
      messenger_of_death = {
         name = "messenger of death",
      },
      hound = {
         name = "hound",
      },
      fire_hound = {
         name = "fire hound",
      },
      ice_hound = {
         name = "ice hound",
      },
      lightning_hound = {
         name = "lightning hound",
      },
      dark_hound = {
         name = "dark hound",
      },
      illusion_hound = {
         name = "illusion hound",
      },
      nerve_hound = {
         name = "nerve hound",
      },
      poison_hound = {
         name = "poison hound",
      },
      sound_hound = {
         name = "sound hound",
      },
      nether_hound = {
         name = "nether hound",
      },
      chaos_hound = {
         name = "chaos hound",
      },
      giant_squirrel = {
         name = "giant squirrel",
      },
      killer_squirrel = {
         name = "killer squirrel",
      },
      grudge = {
         name = "grudge",
      },
      hungry_demon = {
         name = "hungry demon",
      },
      hungry_sea_lion = {
         name = "hungry sea lion",
      },
      super_hungry_sea_lion = {
         name = "super hungry sea lion",
      },
      electric_cloud = {
         name = "electric cloud",
      },
      chaos_cloud = {
         name = "chaos cloud",
      },
      floating_eye = {
         name = "floating eye",
      },
      chaos_eye = {
         name = "chaos eye",
      },
      mad_gaze = {
         name = "mad gaze",
      },
      death_gaze = {
         name = "death gaze",
      },
      wyvern = {
         name = "wyvern",
      },
      puppet = {
         name = "puppet",
      },
      wasp = {
         name = "wasp",
      },
      red_wasp = {
         name = "red wasp",
      },
      cyclops = {
         name = "cyclops",
      },
      titan = {
         name = "titan",
         text_101 = "*THUMP*",
      },
      imp = {
         name = "imp",
      },
      nether_imp = {
         name = "nether imp",
      },
      chaos_imp = {
         name = "chaos imp",
      },
      hand_of_the_dead = {
         name = "hand of the dead",
      },
      hand_of_the_chaos = {
         name = "hand of the chaos",
      },
      hand_of_the_murderer = {
         name = "hand of the murderer",
      },
      ghost = {
         name = "ghost",
      },
      nymph = {
         name = "nymph",
      },
      man_eater_flower = {
         name = "man eater flower",
      },
      chaos_flower = {
         name = "chaos flower",
      },
      cobra = {
         name = "cobra",
      },
      king_cobra = {
         name = "king cobra",
      },
      fire_drake = {
         name = "fire drake",
      },
      ice_drake = {
         name = "ice drake",
      },
      lesser_mummy = {
         name = "lesser mummy",
      },
      mummy = {
         name = "mummy",
      },
      greater_mummy = {
         name = "greater mummy",
      },
      tuwen = {
         name = "<Tuwen> the master of the pyramid",
      },
      ancient_coffin = {
         name = "ancient coffin",
      },
      goblin = {
         name = "goblin",
      },
      goblin_warrior = {
         name = "goblin warrior",
      },
      goblin_shaman = {
         name = "goblin shaman",
      },
      goblin_wizard = {
         name = "goblin wizard",
      },
      red_baptist = {
         name = "red baptist",
      },
      blue_baptist = {
         name = "blue baptist",
      },
      brown_bear = {
         name = "brown bear",
      },
      grizzly = {
         name = "grizzly",
      },
      mammoth = {
         name = "Mammoth",
      },
      living_armor = {
         name = "living armor",
      },
      steel_mass = {
         name = "steel mass",
      },
      golden_armor = {
         name = "golden armor",
      },
      death_armor = {
         name = "death armor",
      },
      medusa = {
         name = "medusa",
      },
      euryale = {
         name = "euryale",
      },
      stheno = {
         name = "stheno",
      },
      cupid_of_love = {
         name = "cupid of love",
      },
      lesser_phantom = {
         name = "lesser phantom",
      },
      tyrannosaurus = {
         name = "Tyrannosaurus",
      },
      harpy = {
         name = "harpy",
      },
      green_dragon = {
         name = "green dragon",
      },
      red_dragon = {
         name = "red dragon",
      },
      white_dragon = {
         name = "white dragon",
      },
      elec_dragon = {
         name = "elec dragon",
      },
      nether_dragon = {
         name = "nether dragon",
      },
      chaos_dragon = {
         name = "chaos dragon",
      },
      cerberus = {
         name = "cerberus",
      },
      scorpion = {
         name = "scorpion",
      },
      king_scorpion = {
         name = "king scorpion",
      },
      spider = {
         name = "spider",
      },
      black_widow = {
         name = "black widow",
      },
      paralyzer = {
         name = "paralyzer",
      },
      tarantula = {
         name = "tarantula",
      },
      blood_spider = {
         name = "blood spider",
      },
      wooden_golem = {
         name = "wooden golem",
      },
      stone_golem = {
         name = "stone golem",
      },
      steel_golem = {
         name = "steel golem",
      },
      golden_golem = {
         name = "golden golem",
      },
      mithril_golem = {
         name = "mithril golem",
      },
      sky_golem = {
         name = "sky golem",
      },
      adamantium_golem = {
         name = "adamantium golem",
      },
      fire_crab = {
         name = "fire crab",
      },
      fire_centipede = {
         name = "fire centipede",
      },
      cultist_of_fire = {
         name = "cultist of fire",
      },
      skeleton_warrior = {
         name = "skeleton warrior",
      },
      skeleton_berserker = {
         name = "skeleton berserker",
      },
      missionary_of_darkness = {
         name = "missionary of darkness",
      },
      pawn = {
         name = "<Pawn>",
      },
      rook = {
         name = "<Rook>",
      },
      bishop = {
         name = "<Bishop>",
      },
      knight = {
         name = "<Knight>",
      },
      queen = {
         name = "<Queen>",
      },
      king = {
         name = "<King>",
      },
      mercenary_warrior = {
         name = "mercenary warrior",
      },
      mercenary_archer = {
         name = "mercenary archer",
      },
      mercenary_wizard = {
         name = "mercenary wizard",
      },
      rogue_boss = {
         name = "rogue boss",
      },
      rogue_warrior = {
         name = "rogue warrior",
      },
      rogue_archer = {
         name = "rogue archer",
      },
      rogue_wizard = {
         name = "rogue wizard",
      },
      yerles_machine_infantry = {
         name = "Yerles machine infantry",
      },
      yerles_elite_machine_infantry = {
         name = "Yerles elite machine infantry",
      },
      gilbert = {
         name = "<Gilbert> the colonel",
         text_100 = {"\"Help the helpless! Crush the vileness!\"", "\"Atten-TION! Salute!\"", "\"For the Kingdom, we shall never fall!\"", "\"Who's house? Mah House!\""},
      },
      yerles_self_propelled_gun = {
         name = "yerles self-propelled gun",
      },
      juere_infantry = {
         name = "juere infantry",
      },
      juere_swordman = {
         name = "juere swordman",
      },
      rock_thrower = {
         name = "rock thrower",
      },
      cat = {
         name = "cat",
         text_100 = {"\"Meow.\"", "\"Mew.\"", "\"Mew mew.\"", "\"Rowr!\"", "\"Mewl.\""},
         text_101 = {"\"Meow!\"", "\"Mew mew!\"", "\"Mew!\"", "\"Meow\""},
         text_102 = "\"Me...meow....\"",
         text_103 = {"*hiss*", "\"Meoow!\"", "\"Meew!\"", "\"Mew!\"", "\"Meow meow.\""},
      },
      silver_cat = {
         name = "silver cat",
         text_100 = {"\"Meow.\"", "\"Mew.\"", "\"Mew mew.\"", "\"Mew!\"", "\"Mewl.\""},
         text_101 = {"\"Meow!\"", "\"Mew mew!\"", "\"Mew!\"", "\"Meow\""},
         text_102 = "\"Me...meow....\"",
         text_103 = {"*hiss*", "\"Meoow!\"", "\"Meew!\"", "\"Mew!\"", "\"Meow meow.\""},
      },
      stray_cat = {
         name = "stray cat",
         text_100 = {"\"Do you know where my home is?\"", "\"I'm going home.\"", "\"I'm going home!\"", "\"Momma? Where are you?\"", "\"Home! Nyaow!\""},
         text_101 = {"\"I'm gonna be killed.\"", "\"I'm gonna die!\""},
         text_102 = "\"I'm...going...hom....e...\"",
         text_103 = "\"That scared me!\"",
      },
      lion = {
         name = "lion",
         text_100 = "You hear the near silent footfalls of a cat. A Big cat.",
      },
      cacy = {
         name = "<Cacy> the cat tamer",
      },
      carbuncle = {
         name = "carbuncle",
      },
      dog = {
         name = "dog",
      },
      poppy = {
         name = "<Poppy> the little dog",
         text_100 = {"You hear the high pitched yips of a young dog.", "A plaintive howl is heard in the distance.", "Rowf!"},
      },
      rilian = {
         name = "<Rilian> the dog lover",
         text_100 = {"\"Poppy!\"", "\"Wuff wuff.\""},
         text_101 = "\"What! Stop!\"",
         text_102 = "\"Poppy, where are you Poppy....\"",
         text_103 = "\"Idiot!\"",
      },
      tam = {
         name = "<Tam> the cat hater",
         text_100 = {"\" hate those bloody cats!\"", "\"Come closer kitty, I gotta present for ya!\"", "\"I've got your number, mate. It's down to two for you. Ahh! There's a oner. Ha ha, yes. Not long for you now!\""},
      },
      little_girl = {
         name = "little girl",
         text_102 = {"\"No....no...!\"", "\"I'm sorry I failed you.\""},
         text_104 = "\"Welcome home!\"",
         text_103 = {"The little girl brushes dust off her clothes.", "The little girl smiles at you.", "You look admiringly at the little girl.", "\"Another death. *grin* \""},
      },
      rat = {
         name = "rat",
      },
      hermit_crab = {
         name = "hermit crab",
      },
      public_performer = {
         name = "public performer",
      },
      frisia = {
         name = "<Frisia> the cat queen",
      },
      younger_sister = {
         name = "younger sister",
      },
      younger_sister_of_mansion = {
         name = "younger sister",
      },
      younger_cat_sister = {
         name = "younger cat sister",
      },
      young_lady = {
         name = "young lady",
      },
      utima = {
         name = "<Utima> the destroyer of Xeren",
      },
      azzrssil = {
         name = "<Azzrssil> the impure",
      },
      master_of_pet_arena = {
         name = "master of pet arena",
      },
      garok = {
         name = "<Garok> the legendary smith",
         text_100 = {"You hear the rhythmic clang of a hammer on steel.", "You hear the whoosh of a bellows being pumped.", "You hear the perfect ring of steel-on-steel. It makes your blood race.", "\"And just what shall you be, oh noble ingot? A dagger perhaps, an axe blade by chance? Let us find out...\"", "\"Ah! A good shipment of steel today. Oh, what to make, decisions, decisions...\"", "\"With this, I have created half a legend. Your wielder will make the other half with you.\"", "\"Let's just sit you on the shelf oh noble blade, for soon your brothers shall join you.\""},
      },
      miral = {
         name = "<Miral> the legendary smith",
         text_100 = {"\"Oh, what to make for dinner.\"", "\"All work and no play makes Miral a dull boy.\"", "\"There's never enough time in the world to get everything done.\"", "\"Guests? Goodness it has been a while indeed.\"", "\"I've got a cat I wanna frame! And now nothing shall ever be the same.\""},
      },
      twintail = {
         name = "twintail",
         text_100 = {"All around you is the sensation of being in a sacred place.", "You have seldom felt such an air of peace.", "All around is very quiet, yet you aren't the least bit lonely.", "In your mind you hear the strange echoes of a voice in prayer."},
      },
      silver_wolf = {
         name = "silver wolf",
         text_100 = {"All around you is the sensation of being in a sacred place.", "You have seldom felt such an air of peace.", "All around is very quiet, yet you aren't the least bit lonely.", "In your mind you hear the strange echoes of a voice in prayer."},
      },
      nurse = {
         name = "nurse",
      },
      rich_person = {
         name = "rich person",
      },
      noble_child = {
         name = "noble child",
      },
      tourist = {
         name = "tourist",
      },
      festival_tourist = {
         name = "festival tourist",
         text_100 = {"\"Let's check the food stall.\"", "\"No! I want to play a little longer!\"", "\"What a noisy street.\"", "\"So it's the holy night festival people were talking about...\"", "\"Hey look, those children are making cute snowmen.\"", "\"Where does the giant come from?\"", "\"Holy cow!\"", "\"It's that time of year again.\"", "\"Aha, some human garbage.\""},
      },
      blade = {
         name = "blade",
      },
      blade_alpha = {
         name = "blade alpha",
      },
      blade_omega = {
         name = "blade omega",
      },
      kaneda_bike = {
         name = "<Kaneda Bike>",
         text_100 = {"*Varoom!*", "*Va-Va-Va*"},
         text_101 = {"\"Teeee tsuuu oooooo!!.\"", "\"Yo, what's up? A fight?\"", "\"Relax, it's gonna take some time to warm my engine up.\""},
         text_102 = "*Pan*",
         text_103 = {"\"My body is too peaky for ya.\"", "\"Just hold on Tetsuo. I'm gonna find you to end your pain.\""},
      },
      cub = {
         name = "cub",
         text_100 = {"*Bo-Bo-Bo*", "*Pusss*"},
         text_101 = {"\"Craaaap! You are so dead!.\"", "\"You dorf, get away get away!\""},
         text_102 = "*Pan*",
         text_103 = {"\"Teeee tsuuu oooooo!!.\"", "\"Yo, what's up? A fight?\"", "\"Relax, it's gonna take some time to warm my engine up.\""},
      },
      mine_dog = {
         name = "mine dog",
      },
      iron_maiden = {
         name = "iron maiden",
      },
      deformed_eye = {
         name = "deformed eye",
      },
      impure_eye = {
         name = "impure eye",
      },
      wisp = {
         name = "wisp",
      },
      hedgehog = {
         name = "hedgehog",
      },
      shining_hedgehog = {
         name = "shining hedgehog",
      },
      chicken = {
         name = "chicken",
         text_100 = {"You hear something scratching for worms.", "\"*Bwwwuuuuu-buk-buk-buk-buKAWK*\"", "You hear poultry in the distance."},
      },
      pumpkin = {
         name = "pumpkin",
      },
      puppy = {
         name = "puppy",
      },
      greater_pumpkin = {
         name = "greater pumpkin",
      },
      halloween_nightmare = {
         name = "halloween nightmare",
      },
      stalker = {
         name = "stalker",
      },
      shadow_stalker = {
         name = "shadow stalker",
      },
      ebon = {
         name = "<Ebon> the fire giant",
         text_100 = {"You hear a bonfire in the distance, only it sounds like it's breathing."},
      },
      moyer = {
         name = "<Moyer> the crooked",
         text_100 = {"\"Hey now, I stopped, I stopped!\"", "\"Behold! a Legendary Giant of Fire! Be careful you aren't burned now.\"", "\"And if you think that's special, wait till you see what I got over here!\""},
      },
      maid = {
         name = "maid",
         text_100 = {"", "\"Oh Master, I don't do THOSE sorts of things♪...\"", "The maid looks good enough to touch."},
      },
      ebon2 = {
         name = "<Ebon> the fire giant",
         text_100 = {"You hear a bonfire in the distance, only it sounds like it's breathing, AND moving..."},
      },
      test_subject = {
         name = "<Stersha> the queen of Palmia",
      },
      gwen = {
         name = "<Gwen> the innocent",
         text_100 = {"\"Oh my! Such pretty flowers♪\"", "\"Can I tag along? I won't be a bother♪\"", "\"I hope Sandra's red cape...♪\"", "\"Eat flowers evil-doer!♪\"", "\"Red is the color of love, of blood, and of roses♪\"", "\"A crown of flowers did his mother weave with all her heart...♪\"", "\"♪La, laaaah, la, la-la. Lah, la-la, la la....♪\""},
      },
      pael = {
         name = "Lonely <Pael>",
         text_100 = {"\"Mother...\"", "\"Do not go alone.\"", "\"Oh, look at you...\""},
      },
      lily = {
         name = "Pael's mom <Lily>",
         text_100 = {"\"Pael, such a spoiled child... dear oh dear.\"", "\"Hush now, I've got you.\"", "\"I hope Pael is not in trouble with the guards again...\"", "\"Now you be good dear, understand?\""},
      },
      raphael = {
         name = "<Raphael> the womanizer",
         text_100 = {"\"Ladies! The line starts here!\"", "\"No woman can resist my charms, be they my dashing good looks, my wit and charm, or even my coinpurse.\"", "\"ero-ero-ero-ero, mushroom, mushroom!\"", "\"I am the Gods gift to women. Come and get a memory you shall never forget!\""},
      },
      ainc = {
         name = "<Ainc> the novice knight",
         text_100 = {"\"Let's roll!\"", "\"I may be new to this whole knight gig, but I won't be for long!\"", "\"Are my spurs polished enough you think? I'd just die if a senior thought they were sub-par.\"", "You hear someone adjusting their armor for the umpteenth time."},
      },
      arnord = {
         name = "<Arnord> the injured soldier",
         text_100 = {"\"Pah, a minor flesh wound...\"", "\"Come closer... I got rounds for this thing still...\"", "\"It's not a tumor!\"", "\"I'll be back.\""},
      },
      mia = {
         name = "<Mia> the cat freak",
         text_100 = {"\"I nyo talk funny, nyou talk funny♪\"", "\"Nyah! Water! I hates it so.\"", "\"Pug!\"", "\"Nyo touching! No Bump-Bump for nyou.\"", "\"♪Nyobody knyows the touble Mia's seen, nyobody knyows Mia's Tru-bull♪\"", "You hear the oddest voice in the crowd, it is lilting and...cat-like?", "\"Meow♪1\""},
      },
      renton = {
         name = "<Renton> the suffering wizard",
         text_100 = {"\"I mean there's nothing in my soul but pain and misery. Oh and agony too, can't leave that out.\"", "\"My body will keep moving, like a machine, but without the oils of love, my heart will not stop squeaking.\"", "You hear the shuffling step of a man who's world is nothing but pain and misery. With just an aftertaste of agony, for good measure.", "\"Will the kiss of Death bring an end to the cloying, double-plus-ungood that is my life?\""},
      },
      marks = {
         name = "<Marks> the great thief",
         text_100 = {"\"Impossible? Bah, to you maybe.\"", "\"You catch me? Ha! You'd have a better chance shackling your shadow!\"", "You hear the swagger of a man of supreme confidence, only it's oh so quiet..."},
      },
      noel = {
         name = "<Noel> the bomber",
         text_100 = {"You hear a someone making ticking sounds, followed by a pantomimed 'Ka-BOOOOM', followed by manical laughter.", "\"He says to me, he says to me, 'Baby I'm TIRED of workin' for the MAN!' I says, I says, WHY DON'T YOU BLOW HIM TO BITS?\"", "\"You got STYLE, baby. But if you're going to be a real villain, you gotta get a gimmick.' And so I go I says YEAH, baby. A gimmick, that's it. High explosives.\""},
      },
      conery = {
         name = "<Conery> Palmian major general",
         text_100 = {"\"Kill a man, they put you in the gallows. Kill ten-thousand, they make you a General.\"", "\"We're going to need all the help we can get, yes indeed.\"", "\"You know what separates a soldier from a thug? The polish on his buttons, that's what.\""},
      },
      thief = {
         name = "thief",
         text_100 = {"\"Heh, easy money...\"", "\"Think I can get some good coin for those fancy bits you got on stranger?\"", "\"Another one with a coinpurse just dangling there, like a bit of ripe fruit. Time to pluck it.\""},
      },
      robber = {
         name = "robber",
         text_100 = {"\"Man, this one'll feed me for a week. Two even!\"", "\"I was just sayin' we needed some coin, and look, it just came walkin' towards us.\"", "\"Your GP or your HP good chum!\""},
      },
      master_thief = {
         name = "master thief",
         text_100 = {"\"Like taking candy from a baby in armor.\"", "You hear someone humming the *Money* tune while cracking their knuckles.", "\"Another satisfying finance adjustment.\""},
      },
      great_race_of_yith = {
         name = "great race of Yith",
      },
      shub_niggurath = {
         name = "Shub-Niggurath",
      },
      gagu = {
         name = "gagu",
      },
      spiral_king = {
         name = "spiral king",
      },
      fairy = {
         name = "fairy",
      },
      black_cat = {
         name = "black cat",
      },
      cute_fairy = {
         name = "cute fairy",
         text_100 = {"You hear the fluttering of gossamer wings.", "You hear tittering laughter like tiny crystal bells.", "You smell what reminds you of sugarplums..."},
      },
      android = {
         name = "android",
      },
      black_angel = {
         name = "black angel",
         text_100 = {"You hear what sounds like wings of feather, but with grace and dignity somehow...", "You hear a quiet voice in prayer, but with a note of sadness...", "You smell Myrrh in the air, but with the faintest hints of charcoal..."},
      },
      exile = {
         name = "exile",
      },
      golden_knight = {
         name = "golden knight",
      },
      defender = {
         name = "defender",
      },
      lame_horse = {
         name = "lame horse",
         text_100 = "You hear faltering hoofbeats in the distance.",
      },
      wild_horse = {
         name = "wild horse",
         text_100 = {"You hear hoofbeats, but they are wild and free."},
      },
      noyel_horse = {
         name = "Noyel horse",
         text_100 = {"You hear hoofbeats, a trot that almost belongs on a parade."},
      },
      yowyn_horse = {
         name = "Yowyn horse",
         text_100 = "You hear the crisp hoofbeats of a horse trained for war.",
      },
      wild_horse2 = {
         name = "wild horse",
         text_100 = "You hear hoofbeats. You hope it's not zebras.",
      },
      mutant = {
         name = "mutant",
      },
      icolle = {
         name = "<Icolle> the biologist",
         text_100 = {"\"Science is it's own reward!\"", "\"With a little bit of this, and a little bit of that, why, who knows what you are going to get?\"", "\"I wonder if a black cat's genes are more or less lucky than a regular cat?\""},
      },
      balzak = {
         name = "<Balzak> the janitor",
         text_100 = {"\"This citie's health is my charge!\"", "\"Those who DARE litter before me shall face my broom!\"", "\"I am garbage's worst nightmare.\""},
      },
      revlus = {
         name = "<Revlus> the mage guildmaster",
         text_100 = {"\"Magic is not for the faint of heart, nor dull of mind.\"", "You hear chants for spells you can't even begin to imagine the purpose of.", "A pulse of arcane and raw eldritch energies nearly knocks you off your feet."},
      },
      lexus = {
         name = "<Lexus> the guild watchman",
         text_100 = {"\"I am an officer of the Mage Guild's jurisdiction. Beware the un-learn-ed.\"", "\"Stop... Let me make sure you are on my lists.\""},
      },
      sin = {
         name = "<Sin> the thief guildmaster",
      },
      abyss = {
         name = "<Abyss> the thief watchman",
         text_100 = {"\"I am an officer of the Thief Guild's jurisdiction. Beware the clumsy-fingered.\"", "\"Stop... Let me make sure you are on my lists.\""},
      },
      fray = {
         name = "<Fray> the fighter guildmaster",
      },
      doria = {
         name = "<Doria> the fighter watchman",
         text_100 = {"\"I am an officer of the Fighter Guild's jurisdiction. Beware the weak-thewed.\"", "\"Stop... Let me make sure you are on my lists.\""},
      },
      silver_eyed_witch = {
         name = "silver eyed witch",
         text_100 = {"\"What do I have to fear? You aren't an Abyssal One.\"", "\"Good grief, is someone trying to cop a feel?\" "},
      },
      big_daddy = {
         name = "<Big daddy>",
         text_100 = {"You feel the ground tremble with the steps of a large, angry, Protector.", "Little Sister: \"Look Mr. Bubbles, the angels.\"", "Little Sister: \"Look Mr. Bubbles, the angels are dancing in the sky!\"", "You hear the tread of something you do NOT want to anger. Ever."},
      },
      little_sister = {
         name = "<Little sister>",
         text_100 = {"\"Mr. Bubbles, please stand up... Please!\"", "You hear the sound of a frightened little girl somewhere.", "\"Angel, angel, until we find the right one we don't dare die...\""},
      },
      strange_scientist = {
         name = "<Strange scientist>",
         text_100 = {"\"The path of the righteous is not always easy, yes?\"", "\"I'll not have him hurt my Little ones... I've worked far too long on them to see them fail now.\""},
         text_101 = "\"How can you do these things?\"",
         text_102 = "\"Have you no heart?\"",
         text_103 = "\"Have you no heart?\"",
      },
      mysterious_producer = {
         name = "<Mysterious Producer>",
         text_100 = {"\"The problem is about choice. It is always about the choices we make.\"", "\"While choices make the man, a pity most see only the shallowest ones to choose from.\""},
         text_101 = "\"How can you do these things?\"",
         text_102 = "\"Have you no heart?\"",
         text_103 = "\"Have you no heart?\"",
      },
      shade = {
         name = "shade",
      },
      quickling = {
         name = "quickling",
      },
      quickling_archer = {
         name = "quickling archer",
      },
      silver_bell = {
         name = "silver bell",
         text_100 = "*ring*",
         text_101 = "*ring*",
      },
      gold_bell = {
         name = "gold bell",
         text_100 = "*ring*",
         text_101 = "*ring*",
      },
      alien = {
         name = "alien",
      },
   }
)
