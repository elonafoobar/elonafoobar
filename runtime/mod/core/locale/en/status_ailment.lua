local I18N = ELONA.require("core.I18N")

I18N.add {
   status_ailment = {
      message = {
         blinded = {
            apply = "{name($1)} {is($1)} blinded.",
            heal = "{name($1)} can see again.",
         },
         confused = {
            apply = "{name($1)} {is($1)} confused.",
            heal = "{name($1)} recover{s($1)} from confusion.",
         },
         paralyzed = {
            apply = "{name($1)} {is($1)} paralyzed.",
            heal = "{name($1)} recover{s($1)} from paralysis.",
         },
         poisoned = {
            apply = "{name($1)} {is($1)} poisoned.",
            heal = "{name($1)} recover{s($1)} from poison.",
         },
         sleep = {
            apply = "{name($1)} fall{s($1)} asleep.",
            heal = "{name($1)} awake{s($1)} from {his($1)} sleep.",
         },
         fear = {
            apply = "{name($1)} {is($1)} frightened.",
            heal = "{name($1)} shake{s($1)} off {his($1)} fear.",
         },
         dimmed = {
            apply = "{name($1)} {is($1)} dimmed.",
            -- heal text was originally the same as poisoned.
            heal = "{name($1)} regain{s($1)} {his($1)} senses.",
         },
         bleeding = {
            apply = "{name($1)} begin{s($1)} to bleed.",
            heal = "{name($1)}{his_owned($1)} bleeding stops.",
         },
         drunk = {
            apply = "{name($1)} get{s($1)} drunk.",
            heal = "{name($1)} get{s($1)} sober.",
         },
         insane = {
            apply = "{name($1)} become{s($1)} insane.",
            heal = "{name($1)} come{s($1)} to {himself($1)} again.",
         },
         sick = {
            apply = "{name($1)} get{s($1)} sick.",
            heal = "{name($1)} recover{s($1)} from {his($1)} illness.",
         },
      },

      name = {
         hunger = {
            _0 = "Starving!",
            _1 = "Starving",
            _2 = "Hungry!",
            _3 = "Hungry",
            _4 = "Hungry",
            _5 = "",
            _6 = "",
            _7 = "",
            _8 = "",
            _9 = "",
            _10 = "Satisfied",
            _11 = "Satisfied!",
            _12 = "Bloated",
         },

         burden = {
            _0 = "",
            _1 = "Burden",
            _2 = "Burden!",
            _3 = "Overweight",
            _4 = "Overweight!",
         },

         sleepy = {
            _0 = "Sleepy",
            _1 = "Need Sleep",
            _2 = "Need Sleep!",
         },

         sick = {
            _0 = "Sick",
            _1 = "Very Sick",
         },

         poison = {
            _0 = "Poisoned",
            _1 = "Poisoned Bad!",
         },

         dimmed = {
            _0 = "Dim",
            _1 = "Muddled",
            _2 = "Unconscious",
         },

         angry = {
            _0 = "Fury",
            _1 = "Berserk",
         },

         bleeding = {
            _0 = "Bleeding",
            _1 = "Bleeding!",
            _2 = "Hemorrhage",
         },

         insane = {
            _0 = "Unsteady",
            _1 = "Insane",
            _2 = "Paranoia",
         },

         drunk = "Drunk",
         wet = "Wet",
         gravity = "Gravity",

         sleep = {
            _0 = "Sleep",
            _1 = "Deep Sleep",
         },

         blind = "Blinded",
         paralyzed = "Paralyzed",
         choked = "Choked",
         confused = "Confused",
         fear = "Fear",

         tired = {
            _0 = "Tired",
            _1 = "Very tired",
            _2 = "VERY tired",
         },
      },
   },
}
