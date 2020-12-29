local I18N = require("core.I18N")

I18N.add {
   ai = {
      snail = {
         "\"Snail!\"",
         "\"Kill!\"",
      },

      ally = {
         sells_items = "{name($1)} sells {$2} item{s($2)} and earns {$3} gold piece{s($3)}.",
         visits_trainer = "{basename($1)} visits a trainer and develops {his($1)} potential!",
      },

      swap = {
         displace = "{name($1)} displace{s($1)} {name($2)}.",
         glare = "{name($2)} glare{s($2)} at {name($1)}.",
      },

      crushes_wall = "{name($1)} crush{s($1, true)} the wall!",

      fire_giant = {
         "\"Filthy monster!\"",
         "\"Go to hell!\"",
         "\"I'll get rid of you.\"",
         "\"Eat this!\"",
      },

      makes_snowman = "{name($1)} make{s($1)} {itemname($2)}!",

      snowball = {
         "*grin*",
         "\"Fire in the hole!\"",
         "\"Tee-hee-hee!\"",
         "\"Eat this!\"",
         "\"Watch out!\"",
         "\"Scut!\"",
      },

      dragostea_din_tei = {
         sing = {
            "\"Vrei sa pleci dar♪\"",
            "\"Numa numa yay!!\"",
            "\"Numa numa numa yay!!\"",
            "\"Mai-Ya-Hi♪\"",
            "\"Mai-Ya-Hoo♪\"",
            "\"Mai-Ya-Ha Ma Mi A♪\"",
         },
      },
   },
}
