local i18n = require("core.i18n")

i18n.add {
   death_by = {
      chara = {
         -- _1 is victim, _2 is attacker.
         transformed_into_meat = {
            active = {
               by_spell = "transforms {him($1)} into several pieces of meat.",
               by_chara = "transform{s($2)} {him($1)} into several pieces of meat.",
            },
            passive = "{name($1)} {is($1)} transformed into several pieces of meat.",
         },
         destroyed = {
            active = {
               by_spell = "destroys {him($1)}.",
               by_chara = "destroy{s($2)} {him($1)}.",
            },
            passive = "{name($1)} {is($1)} killed.",
         },
         minced = {
            active = {
               by_spell = "minces {him($1)}.",
               by_chara = "mince{s($2)} {him($1)}.",
            },
            passive = "{name($1)} {is($1)} minced.",
         },
         killed = {
            active = {
               by_spell = "kills {him($1)}.",
               by_chara = "kill{s($2)} {him($1)}.",
            },
            passive = "{name($1)} {is($1)} slain.",
         },
         death_cause = "was killed by {basename($1)}",
      },
      element = {
         -- _1 is victim, _2 is attacker.
         default = {
            active = {
               by_spell = "kills {him($1)}.",
               by_chara = "kill{s($2)} {him($1)}.",
            },
            passive = "{name($1)} {is($1)} killed.",
         },
         _50 = {
            active = {
               by_spell = "burns {him($1)} to death.",
               by_chara = "burn{s($2)} {him($1)} to death.",
            },
            passive = "{name($1)} {is($1)} burnt to ashes.",
         },
         _51 = {
            active = {
               by_spell = "transforms {him($1)} to an ice sculpture.",
               by_chara = "transform{s($2)} {him($1)} to an ice sculpture.",
            },
            passive = "{name($1)} {is($1)} frozen and turn{s($1)} into an ice sculpture.",
         },
         _52 = {
            active = {
               by_spell = "electrocutes {him($1)} to death.",
               by_chara = "electrocute{s($2)} {him($1)} to death.",
            },
            passive = "{name($1)} {is($1)} struck by lightning and die{s($1)}.",
         },
         _53 = {
            active = {
               by_spell = "lets the depths swallow {him($1)}.",
               by_chara = "let{s($2)} the depths swallow {him($1)}.",
            },
            passive = "{name($1)} {is($1)} consumed by darkness.",
         },
         _54 = {
            active = {
               by_spell = "completely disables {him($1)}.",
               by_chara = "completely disable{s($2)} {him($1)}.",
            },
            passive = "{name($1)} lose{s($1)} {his($1)} mind and commit{s($1)} a suicide.",
         },
         _55 = {
            active = {
               by_spell = "kills {him($1)} with poison.",
               by_chara = "kill{s($2)} {him($1)} with poison.",
            },
            passive = "{name($1)} {is($1)} poisoned to death.",
         },
         _56 = {
            active = {
               by_spell = "entraps {him($1)} into the inferno.",
               by_chara = "entrap{s($2)} {him($1)} into the inferno.",
            },
            passive = "{name($1)} go{s($1, true)} to hell.",
         },
         _57 = {
            active = {
               by_spell = "shatters {him($1)} to atoms.",
               by_chara = "shatter{s($2)} {him($1)} to atoms.",
            },
            passive = "{name($1)} resonate{s($1)} and break up.",
         },
         _58 = {
            active = {
               by_spell = "destroys {his($1)} nerves.",
               by_chara = "destroy{s($2)} {his($1)} nerves.",
            },
            passive = "{name($1)} die{s($1)} from neurofibroma.",
         },
         _59 = {
            active = {
               by_spell = "lets the chaos consume {him($1)}.",
               by_chara = "let{s($2)} the chaos consume {him($1)}.",
            },
            passive = "{name($1)} {is($1)} drawn into a chaotic vortex.",
         },
         -- _60
         _61 = {
            active = {
               by_spell = "cuts {him($1)} into thin strips.",
               by_chara = "cut{s($2)} {him($1)} into thin strips.",
            },
            passive = "{name($1)} {is($1)} cut into thin strips.",
         },
         -- _62
         _63 = {
            active = {
               by_spell = "melts {him($1)} away.",
               by_chara = "melt{s($2)} {him($1)} away.",
            },
            passive = "{name($1)} melt{s($1)}.",
         },
      },
      other = {
         _1 = {
            text = "{name($1)} {is($1)} caught in a trap and die{s($1)}.",
            death_cause = "got caught in a trap and died",
         },
         _2 = {
            text = "{name($1)} die{s($1)} from over-casting.",
            death_cause = "was completely wiped by magic reaction",
         },
         _3 = {
            text = "{name($1)} {is($1)} starved to death.",
            death_cause = "was starved to death",
         },
         _4 = {
            text = "{name($1)} {is($1)} killed with poison.",
            death_cause = "miserably died from poison",
         },
         _5 = {
            text = "{name($1)} die{s($1)} from curse.",
            death_cause = "died from curse",
         },
         _6 = {
            text = "{name($1)} {is($1)} squashed by {$2}.",
            death_cause = "was squashed by {$1}",
            backpack = "backpack",
         },
         _7 = {
            text = "{name($1)} tumble{s($1)} from stairs and die{s($1)}.",
            death_cause = "tumbled from stairs and died",
         },
         _8 = {
            text = "{name($1)} {is($1)} killed by an audience.",
            death_cause = "was killed by an audience",
         },
         _9 = {
            text = "{name($1)} {is($1)} burnt and turned into ash.",
            death_cause = "was burnt and turned into ash",
         },
         -- _10
         _11 = {
            text = "{name($1)} {is($1)} assassinated by the unseen hand.",
            death_cause = "got assassinated by the unseen hand",
         },
         _12 = {
            text = "{name($1)} {is($1)} killed by food poisoning.",
            death_cause = "got killed by food poisoning",
         },
         _13 = {
            text = "{name($1)} die{s($1)} from loss of blood.",
            death_cause = "died from loss of blood",
         },
         _14 = {
            text = "{name($1)} die{s($1)} of the Ether disease.",
            death_cause = "died of the Ether disease",
         },
         _15 = {
            text = "{name($1)} melt{s($1)} down.",
            death_cause = "melted down",
         },
         _16 = {
            text = "{name($1)} shatter{s($1)}.",
            death_cause = "committed suicide",
         },
         _17 = {
            text = "{name($1)} {is($1)} turned into atoms.",
            death_cause = "was killed by an atomic bomb",
         },
         _18 = {
            text = "{name($1)} step{s($1)} into an iron maiden and die{s($1)}.",
            death_cause = "stepped in an iron maiden and died",
         },
         _19 = {
            text = "{name($1)} {is($1)} guillotined and die{s($1)}.",
            death_cause = "was guillotined",
         },
         _20 = {
            text = "{name($1)} hang{s($1)} {his($1)}self.",
            death_cause = "commited suicide by hanging",
         },
         _21 = {
            text = "{name($1)} choke{s($1)} on mochi and die.",
            death_cause = "ate mochi and died",
         },
      },
   },

}
