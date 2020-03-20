ELONA.i18n:add {
   magic = {
      common = {
         too_exhausted = "You are too exhausted!",
         it_is_cursed = "It's cursed!",
         resists = "{name($1)} resist{s($1)}.",
         melts_alien_children = "{name($1)}{his_owned($1)} alien children melt in {his($1)} stomach.",
         cursed = "{name($1)} hear{s($1)} devils laugh.",
      },

      buff = {
         no_effect = "But it produces no effect.",
         holy_veil_repels = "The holy veil repels the hex.",
         resists = "{name($1)} resist{s($1)} the hex.",
         ends = "The effect of {$1} ends.",
      },

      -- By convention, if the magic text contains both the name of the target and caster, the
      -- caster will be argument _1, and the target will be argument _2.

      slow = "{name($1)}{his_owned($1)} aging process slows down.",
      speed = "{name($1)}{his_owned($1)} aging process speeds up.",

      bolt = {
         ally = "The bolt hits {name($1)}.",
         other = "The bolt hits {name($1)} and",
      },

      explosion = {
         -- JP uses different words (爆発 and 誘爆) for explosions that were started originally or
         -- as part of a chain. The text is the same in EN, however.
         begins = "{name($1)} explode{s($1)}.",
         chain = "{name($1)} explode{s($1)}.",
         ally = "The explosion hits {name($1)}.",
         other = "The explosion hits {name($1)} and",
      },

      ball = {
         ally = "The Ball hits {name($1)}.",
         other = "The ball hits {name($1)} and",
      },

      arrow = {
         ally = "The arrow hits {name($1)}.",
         other = "The arrow hits {name($1)} and",
      },

      healed = {
         slightly = "{name($1)} {is($1)} slightly healed.",
         normal = "{name($1)} {is($1)} healed.",
         greatly = "{name($1)} {is($1)} greatly healed.",
         completely = "{name($1)} {is($1)} completely healed.",
      },

      rain_of_sanity = "{name($1)} {is($1)} completely sane again.",

      special_attack = {
         self = "{name($1)} cast {$2}.",
         other = "{name($1)}{$2}",
      },

      sucks_blood = {
         ally = "{name($1)} suck{s($1)} {name($2)}{his_owned($2)} blood.",
         other = "{name($1)} suck{s($1)} {name($2)}{his_owned($2)} blood and",
      },

      disassembly = "\"Delete.\"",

      touch = {
         ally = "{name($1)} touch{s($1, true)} {name($2)} with {his($1)} {$3} {$4}.",
         other = "{name($1)} touch{s($1, true)} {name($2)} with {his($1)} {$3} {$4} and",
      },

      hunger = "Suddenly {name($1)} feel{s($1)} hungry.",
      weaken = "{name($1)} {is($1)} weakened.",

      summon = "Several monsters come out from a portal.",

      teleport = {
         prevented = "Magical field prevents teleportation.",
         suspicious_hand = {
            succeeded = "{name($1)} steal{s($1)} {$3} gold pieces from {name($2)}.",
            prevented = "{name($1)} guard{s($1)} {his($1)} wallet from a thief.",
            after = "A thief escapes laughing.",
         },
         shadow_step = "{name($1)} teleport{s($1)} toward {basename($2)}.",
         draw_shadow = "{name($1)} {is($1)} drawn.",
         disappears = "Suddenly, {name($1)} disappear{s($1)}.",
      },

      breath = {
         no_element = "breath",
         named = "{$1} breath",
         bellows = "{name($1)} bellow{s($1)} {$2} from {his($1)} mouth.",
         ally = "The breath hits {name($1)}.",
         other = "The breath hits {name($1)} and",
      },

      insanity = {
         "{name($2)} see{s($2)} maggots breed in the rent stomach of {name($1)}.",
         "{name($2)} see{s($2)} {name($1)} chow{s($1)} dead bodies.",
         "{name($2)} shudders{s($2)} at {name($1)}{his_owned($1)} terrifying eyes.",
         "{name($2)} feel{s($2)} sick at entrails caught in {name($1)}{his_owned($1)} tentacles.",
      },

      map = {
         need_global_map = "You need to read it while you are in the global map.",
         cursed = "The cursed map crumbles as you touch.",
         apply = "There's a mark on the map...",
         mark = "O",
      },

      love_potion = {
         cursed = "This love potion is cursed. {name($1)} look{s($1)} at {you()} with a contemptuous glance.",
         spill = "{name($1)} sense{s($1)} a sign of love,",
         self = "You are excited!",
         other = "{name($1)} give{s($1)} {you()} the eye.",
      },

      pregnant = "{name($1)} put{s($1)} something into {name($2)}{his_owned($2)} body!",

      mirror = "You examine yourself.",

      milk = {
         cursed = {
            self = "Geee it's cursed! The taste is very dangerous.",
            other = "\"Argh, the milk is cursed!\"",
         },
         self = "The taste is very thick, almost addictive.",
         other = "\"Yummy!\"",
      },

      alcohol = {
         cursed = {
            "*Hic*",
            "\"Ah, bad booze.\"",
            "\"Ugh...\"",
            "\"Bah, smells like rotten milk.\"",
         },
         normal = {
            "*Hic*",
            "\"Ah, good booze.\"",
            "\"La-la-la-la.\"",
            "\"I'm going to heaven.\"",
            "\"Whew!\"",
            "\"I'm revived!\"",
            "\"Awesome.\"",
         },
      },

      acid = {
         self = "Arrrrg!",
         apply = "The sulfuric acid melts {name($1)}.",
      },

      water = {
         self = "*quaff* The water is refreshing.",
         other = "*quaff*",
      },

      restore_stamina = {
         dialog = "*quaff* Juicy!",
         apply = "{name($1)} restore{s($1)} some stamina.",
      },

      restore_stamina_greater = {
         dialog = "*quaff*",
         apply = "{name($1)} greatly restore{s($1)} stamina.",
      },

      salt = {
         snail = "It's salt! {name($1)} start{s($1)} to melt.",
         apply = "\"Salty!\"",
      },

      dirty_water = {
         self = "*quaff* Yucky!",
         other = "*quaff*",
      },

      steal = {
         in_quest = "You have no time for it!",
      },

      mount = {
         no_place_to_get_off = "There's no place to get off.",

         dismount = "You dismount from {name($1)}.",
         dismount_dialog = {
            "\"Phew.\"",
            "\"How was my ride?\"",
            "\"Tired...tired...\"",
            "\"It was nice.\"",
         },

         only_ally = "You can only ride an ally.",
         not_client = "You can't ride a client.",
         ride_self = "You try to ride yourself.",
         stays_in_area = "The ally currently stays in this area.",
         currently_riding = "{name($1)} {is($1)} currently riding {name($2)}.",

         mount = {
            execute = "You ride {name($1)}. ({name($1)}'s speed: {$2}->",
            suitable = "You feel comfortable.",
            unsuitable = "This creature is too weak to carry you.",
            dialog = {
               "\"Awww.\"",
               "\"You should go on a diet.\"",
               "\"Let's roll!\"",
               "\"Be gentle.\"",
            },
         },
      },

      perform = {
         do_not_know = "{name($1)} {does($1)}n't know how to play an instrument.",
      },

      cook = {
         do_not_know = "You don't know how to cook.",
      },

      fish = {
         do_not_know = "You don't know how to fish.",
         need_bait = "You need a bait to fish.",
         not_good_place = "This isn't a good place to fish.",
         cannot_during_swim = "You can't fish while swimming.",
      },

      prayer = "A golden aura wraps {name($1)}!",

      create_material = {
         materials = "materials",
         junks = "junks",
         apply = "Some {$1} fall from above!",
      },

      mutation = {
         spell = "{name($1)} cast{s($1)} an insane glance on {name($2)}.",
         resist = "You resist the threat of mutation.",
         apply = "You mutate.",
      },

      cure_mutation = "You are now one step closer to yourself.",

      resurrection = {
         cursed = "Hoards of undead raise from the hell!",
         fail = "{name($1)}{his_owned($1)} prayer doesn't reach the underworld.",
         apply = "{$1} {have($2)} been resurrected!",
         dialog = "\"Thanks!\"",
      },

      uncurse = {
         apply = "{name($1)} {his_owned($1)} equipment are surrounded by a white aura.",
         blessed = "{name($1)} {is($1)} surrounded by a holy aura.",
         item = "The aura uncurses some {his($1)} stuff.",
         equipment = "The aura uncurses some of {his($1)} equipment.",
         resist = "Several items resist the aura and remain cursed.",
      },

      oracle = {
         cursed = "You hear a sepulchral whisper but the voice is too small to distinguish a word.",
         no_artifacts = "No artifacts have been generated yet.",

         was_held_by = "{$1} was held by {basename($2)} at {$3} in {$4}/{$5}, {$6}. ",
         was_created_at = "{$1} was created at {$2} in {$3}/{$4}, {$5}. ",
      },

      gain_knowledge = {
         suddenly = "Suddenly, ",
         furthermore = "Furthermore, ",
         gain = "you gain knowledge of a spell, {$1}.",
         lose = "Suddenly, you lose knowledge of a spell, {$1}.",
      },

      descent = "{name($1)} lose{s($1)} a level...",
      gain_skill = "{name($1)} gain{s($1)} a skill of {$2}!",

      faith = {
         doubt = "Your god doubts your faith.",
         apply = "You feel as if {$1} is watching you.",
         blessed = "A three-leaved falls from the sky.",
      },

      gain_skill_potential = {
         the = "The ",
         furthermore_the = "Furthermore, the ",
         increases = "potential of {name($1)}{his_owned($1)} {$2} skill increases.",
         decreases = "The potential of {name($1)}{his_owned($1)} {$2} skill decreases.",
      },

      troll_blood = {
         apply = "{name($1)}{his_owned($1)} blood burns and a new strength fills {his($1)} body!",
         blessed = "It really burns!",
      },

      gain_potential = {
         blessed = "{name($1)}{his_owned($1)} potential of every attribute expands.",
         increases = "{name($1)}{his_owned($1)} potential of {$2} expands.",
         decreases = "{name($1)}{his_owned($1)} potential of {$2} decreases.",
      },

      vanish = "{name($1)} vanish{s($1, true)}.",

      sense = {
         cursed = "Hmm? You suffer minor memory defect.",
         magic_mapping = "{name($1)} sense{s($1)} nearby locations.",
         sense_object = "{name($1)} sense{s($1)} nearby objects.",
      },

      vorpal = {
         sound = "*Gash*",
         ally = "{name($1)} cut{s($1)} {name($2)}{his_owned($2)} head.",
         other = "{name($1)} cut{s($1)} {name($2)}{his_owned($2)} head and",
      },

      restore = {
         body = {
            apply = "{name($1)}{his_owned($1)} body is restored.",
            cursed = "{name($1)}{his_owned($1)} body is damaged.",
            blessed = "In addition, {his($1)} body is enchanted.",
         },
         mind = {
            apply = "{name($1)}{his_owned($1)} spirit is restored.",
            cursed = "{name($1)}{his_owned($1)} spirit is damaged.",
            blessed = "In addition, {his($1)} spirit is enchanted.",
         },
      },

      escape = {
         cancel = "The air around you gradually loses power.",
         during_quest = "Returning while taking a quest is forbidden. Are you sure you want to return?",
         begin = "The air around you becomes charged.",
         lord_may_disappear = "The lord of the dungeon might disappear if you escape now.",
      },

      ["return"] = {
         cancel = "The air around you gradually loses power.",

         prevented = {
            normal = "Strange power prevents you from returning.",
            ally = "One of your allies prevents you from returning.",
            overweight = "Someone shouts, \"Sorry, overweight.\"",
         },

         you_commit_a_crime = "You commit a crime.",
         door_opens = "A dimensional door opens in front of you.",
         destination_changed = "The capricious controller of time has changed your destination!",
      },

      harvest_mana = "{name($1)}{his_owned($1)} mana is restored.",
      absorb_magic = "{name($1)} absorb{s($1)} mana from the air.",
      poison_attack = "{name($1)} {is($1)} hit by poison!",
      ink_attack = "Ink squirts into {name($1)}{his_owned($1)} face!",
      confusion = "A foul stench floods {name($1)}{his_owned($1)} nostrils!",
      paralysis = "{name($1)} get{s($1)} numbness!",
      sleep = "Strange sweet liquid splashes onto {name($1)}!",

      curse = {
         spell = "{name($1)} point{s($1)} {name($2)} and mutter{s($1)} a curse.",
         no_effect = "Your prayer nullifies the curse.",
         apply = "{name($1)}{his_owned($1)} {$2} glows black.",
      },

      weaken_resistance = {
         nothing_happens = "Nothing happens.",
      },

      diary = {
         cat_sister = "How...! You suddenly get a younger cat sister!",
         younger_sister = "How...! You suddenly get a younger sister!",
         young_lady = "A young lady falls from the sky.",
      },

      domination = {
         does_not_work_in_area = "The effect doesn't work in this area.",
         cannot_be_charmed = "{name($1)} cannot be charmed.",
      },

      map_effect = {
         web = "The ground is covered with thick webbing.",
         fog = "The air is wrapped in a dense fog.",
         acid = "Acid puddles are generated.",
         fire = "Walls of fire come out from the ground.",
         ether_mist = "Ether mist spreads.",
      },

      name = {
         prompt = "What do you want to name this artifact?",
         apply = "It's now called {$1}.",
      },

      garoks_hammer = {
         no_effect = "This item leaves no room for improvement.",
         apply = "It becomes {itemname($1, 1)}.",
      },

      change_material = {
         more_power_needed = "More magic power is needed to reconstruct an artifact.",
         artifact_reconstructed = "{name($1)}{his_owned($1)} {itemname($1, false)} is reconstructed.",
         apply = "{name($1)}{his_owned($1)} {$2} transforms into {itemname($3, 1)}.",
      },

      deed_of_inheritance = {
         claim = "You claim the right of succession. (+{$1})",
         can_now_inherit = "You can now inherit {$1} items.",
      },

      enchant = {
         apply = "{itemname($1)} {is($1)} surrounded by a golden aura.",
         resist = "{itemname($1)} resist{s($1)}.",
      },

      fill_charge = {
         more_power_needed = "You need at least 10 recharge powers to recharge items.",
         spend = "You spend 10 recharge powers. (Total:{$1})",
         cannot_recharge = "You can't recharge this item.",
         cannot_recharge_anymore = "{itemname($1)} cannot be recharged anymore.",
         apply = "{itemname($1)} {is($1)} recharged by {$2}.",
         fail = "You fail to recharge {itemname($1)}.",
         explodes = "{itemname($1)} explode{s($1)}.",
      },

      draw_charge = "You destroy {itemname($1)} and extract {$2} recharge powers. (Total:{$3})",

      change = {
         apply = "{name($1)} change{s($1)}.",
         cannot_be_changed = "{name($1)} cannot be changed.",
      },

      flying = {
         apply = "{itemname($1, 1)} becomes light as a feather.",
         cursed = "{itemname($1, 1)} becomes heavy.",
      },

      alchemy = "It is metamorphosed into {itemname($1, 1)}.",

      create = {
         wall = "A wall appears.",
         door = {
            resist = "These walls seem to resist your magic.",
            apply = "A door appears.",
         },
      },

      swarm = "Swarm!",
      drop_mine = "{name($1)} drop{s($1)} something on the ground.",
      gravity = "{name($1)} feel{s($1)} gravity.",
      mewmewmew = "Mewmewmew!",
      meteor = "Innumerable meteorites fall all over the area!",

      cheer = {
         apply = "{name($1)} cheer{s($1)}.",
         is_excited = "{name($1)} {is($1)} excited!",
      },

      cure_corruption = {
         apply = "Your Ether Disease is cured greatly.",
         cursed = " The Ether Disease spreads around your body.",
      },

      eye_of_ether = "{name($1)} gazes at you. Your Ether Disease deteriorates.",

      insult = {
         apply = "{name($1)} insult{s($1)} {name($2)}.",

         -- In English, there is no difference between man's words and woman's.
         man = {
            -- They are duplicated to emulate vanilla's behavior.
            "\"You suck!\"",
            "\"You suck!\"",
            "\"You will die alone.\"",
            "\"You will die alone.\"",
            "\"Bow down before me.\"",
            "\"Bow down before me.\"",
            "\"Go jump off a bridge.\"",
            "\"Go jump off a bridge.\"",
            "\"Bang your head against the wall!\"",
            "\"Bang your head against the wall!\"",
            "\"Why do you sniff under your dog's tail?\"",
            "\"Why do you sniff under your dog's tail?\"",
            "\"The world is against you because you are a unsavory decomposing virus.\"",
            "\"The world is against you because you are a unsavory decomposing virus.\"",
            "\"The world is against you because you are a unsavory decomposing virus.\"",
            "\"You are no better than a immoral guzzling bureaucrat.\"",
            "\"You are no better than a immoral guzzling bureaucrat.\"",
            "\"You are no better than a immoral guzzling bureaucrat.\"",
            "\"You are so lowly.\"",
            "\"You are so lowly.\"",
            "\"You are so lowly.\"",
            "\"Get off me.\"",
            "\"Get off me.\"",
            "\"Get off me.\"",
         },

         -- In English, there is no difference between man's words and woman's.
         woman = {
            -- They are duplicated to emulate vanilla's behavior.
            "\"You suck!\"",
            "\"You suck!\"",
            "\"You will die alone.\"",
            "\"You will die alone.\"",
            "\"Bow down before me.\"",
            "\"Bow down before me.\"",
            "\"Go jump off a bridge.\"",
            "\"Go jump off a bridge.\"",
            "\"Bang your head against the wall!\"",
            "\"Bang your head against the wall!\"",
            "\"Why do you sniff under your dog's tail?\"",
            "\"Why do you sniff under your dog's tail?\"",
            "\"The world is against you because you are a unsavory decomposing virus.\"",
            "\"The world is against you because you are a unsavory decomposing virus.\"",
            "\"The world is against you because you are a unsavory decomposing virus.\"",
            "\"You are no better than a immoral guzzling bureaucrat.\"",
            "\"You are no better than a immoral guzzling bureaucrat.\"",
            "\"You are no better than a immoral guzzling bureaucrat.\"",
            "\"You are so lowly.\"",
            "\"You are so lowly.\"",
            "\"You are so lowly.\"",
            "\"Get off me.\"",
            "\"Get off me.\"",
            "\"Get off me.\"",
         },
      },

      gaze = "{name($1)} gaze{s($1)} at {name($2)}.",
      molotov = "{name($1)} {is($1)} surrounded by flames.",

      scavenge = {
         apply = "{name($1)} loot{s($1)} {name($2)}{his_owned($2)} backpack.",
         rotten = "{name($1)} notice{s($1)} unusual odor from {itemname($2, 1)} and step{s($1)} back.",
         eats = "{name($1)} eat{s($1)} {itemname($2, 1)}!",
      },

      wizards_harvest = "{itemname($1)} fall{s($1)} down!",
      four_dimensional_pocket = "You summon 4 dimensional pocket.",
   },
}
