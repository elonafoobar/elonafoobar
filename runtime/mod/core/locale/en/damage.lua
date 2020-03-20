i18n:add {
   damage = {
      miss = {
         -- target evades attacker
         ally = "{name($2)} evade{s($2)} {name($1)}.",
         -- attacker misses target
         other = "{name($1)} miss{s($1, true)} {name($2)}.",
      },
      evade = {
         -- target evades attacker
         ally = "{name($2)} skillfully evade{s($2)} {name($1)}.",
         -- target evades attacker
         other = "{name($2)} skillfully evade{s($2)} {name($1)}.",
      },
      furthermore = "Futhermore,",

      is_frightened = "{name($1)} {is($1)} frightened.",
      critical_hit = "Critical Hit!",

      wields_proudly = "{name($1)} wield{s($1)} {$2} proudly.",

      is_healed = "{name($1)} {is($1)} healed.",
      lay_hand = "{name($1)} shout{s($1)}, \"Lay hand!\"",

      runs_away_in_terror = "{name($1)} run{s($1)} away in terror.",
      sleep_is_disturbed = "{name($1)}{his_owned($1)} sleep {is($1)} disturbed",

      explode_click = "*click*",
      splits = "{name($1)} split{s($1)}!",
      is_engulfed_in_fury = "{name($1)} {is($1)} engulfed in fury!",

      you_feel_sad = "You feel sad for a moment.",
      get_off_corpse = "{you()} get off the corpse of {name($1)}.",
      death_word_breaks = "The death word breaks.",

      magic_reaction_hurts = "Magic reaction hurts {name($1)}!",

      weapon = {
         -- TODO: When the <verb> is "slash"/"smash", the text lacks "e".
         -- <attacker> <verb>s something with his <weapon>.
         attacks_with = "{name($1)} {$2}{s($1)} {name($3)} with {his($1)} {$4}.",

         -- TODO: When the <verb> is "slash"/"smash", the text lacks "e".
         -- <attacker> <verb>s something and <...>
         attacks_and = "{name($1)} {$2}{s($1)} {name($3)} and",

         attacks_throwing = "{name($1)} {$2}{s($1)} {name($3)} and",

         attacks_unarmed = "{name($1)} {$2}{s($1)} {name($3)}.",
         attacks_unarmed_and = "{name($1)} {$2}{s($1)} {name($3)} and",

         -- _106 is for unarmed. It is a special case since unarmed
         -- attacks can each have a unique name.

         -- "verb_and" is always the same as "verb" here. It is
         -- different in Japanese.
         _108 = {
            name = "bow",
            verb_and = "shoot",
            verb = "shoot",
         },
         _109 = {
            name = "crossbow",
            verb_and = "shoot",
            verb = "shoot",
         },
         _110 = {
            name = "gun",
            verb_and = "shoot",
            verb = "shoot",
         },
         _100 = {
            name = "sword",
            verb_and = "slash",
            verb = "slash",
         },
         _104 = {
            name = "spear",
            verb_and = "stab",
            verb = "stab",
         },
         _101 = {
            name = "dagger",
            verb_and = "stab",
            verb = "stab",
         },
         _105 = {
            name = "staff",
            verb_and = "smash",
            verb = "smash",
         },
         _103 = {
            name = "mace",
            verb_and = "smash",
            verb = "smash",
         },
         _102 = {
            name = "axe",
            verb_and = "slash",
            verb = "slash",
         },
         _107 = {
            name = "scythe",
            verb_and = "slash",
            verb = "slash",
         },
         _111 = {
            verb_and = "shoot",
            verb = "shoot",
         },
      },

      reactive_attack = {
         thorns = "{name($1)} {is($1)} stuck by several thorns.",
         ether_thorns = "{name($1)} {is($1)} stuck by several ether thorns.",
         acids = "Acids spread over the ground.",
      },

      levels = {
         scratch = "make{s($2)} a scratch.",
         slightly = "slightly wound{s($2)} {him($1)}.",
         moderately = "moderately wound{s($2)} {him($1)}.",
         severely = "severely wound{s($2)} {him($1)}.",
         critically = "critically wound{s($2)} {him($1)}!",
      },

      reactions = {
         screams = "{name($1)} scream{s($1)}.",
         writhes_in_pain = "{name($1)} writhe{s($1)} in pain.",
         is_severely_hurt = "{name($1)} {is($1)} severely hurt!",
      },

      vorpal = {
         melee = "*vopal*",
         ranged = "*vopal*",
      },

      sand_bag = {
         _0 = "\"Kill me already!\"",
         _1 = "\"No..not yet...!\"",
         _2 = "\"I can't take it anymore...\"",
         _3 = "\"Argh!\"",
         _4 = "\"Uhhh\"",
         _5 = "\"Ugggg\"",
      },
   },
}
