local I18N = ELONA.require("core.I18N")

I18N.add {
   enchantment = {
      level = "#",
      it = "It ",

      with_parameters = {
         attribute = {
            in_food = {
               increases = "has essential nutrients to enhance your {$1}.",
               decreases = "has which deteriorates your {$1}.",
            },
            other = {
               increases = "increases your {$1} by {$2}.",
               decreases = "decreases your {$1} by {$2}.",
            },
         },

         resistance = {
            increases = "grants your resistance to {$1}.",
            decreases = "weakens your resistance to {$1}.",
         },

         skill = {
            increases = "improves your {$1} skill.",
            decreases = "decreases your {$1} skill.",
         },

         skill_maintenance = {
            in_food = "can help you exercise your {$1} faster.",
            other = "maintains {$1}.",
         },

         extra_damage = "deals {$1} damage.",
         invokes = "invokes {$1}.",
         ammo = {
            text = "can be loaded with {$1}.",
            max = "Max {$1}",
            kinds = {
               _0 = "rapid ammo",
               _1 = "explosive ammo",
               _2 = "piercing ammo",
               _3 = "magic ammo",
               _4 = "time stop ammo",
               _5 = "burst ammo",
            },
         },
      },

      no_parameters = {
         _21 = "causes random teleport.",
         _22 = "prevents you from teleporting.",
         _23 = "negates the effect of blindness.",
         _24 = "negates the effect of paralysis.",
         _25 = "negates the effect of confusion.",
         _26 = "negates the effect of fear.",
         _27 = "negates the effect of sleep.",
         _28 = "negates the effect of poison.",
         _29 = "speeds up your travel progress.",
         _30 = "protects you from Etherwind.",
         _31 = "negates the effect of being stranded by bad weather.",
         _32 = "floats you.",
         _33 = "protects you from mutation.",
         _34 = "enhances your spells.",
         _35 = "allows you to see invisible creatures.",
         _36 = "absorbs stamina from an enemy.",
         _37 = "brings an end.",
         _38 = "absorbs MP from an enemy.",
         _39 = "gives you a chance to throw an absolute piercing attack.",
         _40 = "occasionally stops time.",
         _41 = "protects you from thieves.",
         _42 = "allows you to digest rotten food.",
         _43 = "protects you from cursing words.",
         _44 = "increases your chance to deliver critical hits.",
         _45 = "sucks blood of the wielder.",
         _46 = "disturbs your growth.",
         _47 = "attracts monsters.",
         _48 = "prevents aliens from entering your body.",
         _49 = "increases the quality of reward.",
         _50 = "increases the chance of extra melee attack.",
         _51 = "increases the chance of extra ranged attack.",
         _52 = "decreases physical damage you take.",
         _53 = "sometimes nullifies damage you take.",
         _54 = "deals cut damage to the attacker.",
         _55 = "diminishes bleeding.",
         _56 = "catches signals from God.",
         _57 = "inflicts massive damage to dragons.",
         _58 = "inflicts massive damage to undeads.",
         _59 = "reveals religion.",
         _60 = "makes audience drunk with haunting tones.",
         _61 = "inflicts massive damage to Gods.",
      },

      item_ego = {
         major = {
            -- TODO the append position differs based on language.
            _0 = "of fire",
            _1 = "of silence",
            _2 = "of cold",
            _3 = "of lightning",
            _4 = "of defender",
            _5 = "of healing",
            _6 = "of resist blind",
            _7 = "of resist paralysis",
            _8 = "of resist confusion",
            _9 = "of resist fear",
            _10 = "of resist sleep",
         },
         minor = {
            _0 = "singing",
            _1 = "servant's",
            _2 = "follower's",
            _3 = "howling",
            _4 = "glowing",
            _5 = "conspicuous",
            _6 = "magical",
            _7 = "enchanted",
            _8 = "mighty",
            _9 = "trustworthy",
         },
      },
   },
}
