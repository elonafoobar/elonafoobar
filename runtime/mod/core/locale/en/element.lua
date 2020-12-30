local i18n = require("core.i18n")

i18n.add {
   element = {
      name = {
         starving = "starving",
         rotten = "rotten",
         fearful = "fearful",
         silky = "silky",

         _50 = "burning",
         _51 = "icy",
         _52 = "electric",
         _54 = "psychic",
         _58 = "numb",
         _57 = "shivering",
         _55 = "poisonous",
         _56 = "infernal",
         _59 = "chaotic",
         _53 = "gloomy",
         _61 = "cut",
         _62 = "ether",
      },

      damage = {
         default = "{name($1)} {is($1)} wounded.",
         _50 = "{name($1)} {is($1)} burnt.",
         _51 = "{name($1)} {is($1)} frozen.",
         _52 = "{name($1)} {is($1)} shocked.",
         _53 = "{name($1)} {is($1)} struck by dark force.",
         _54 = "{name($1)} suffer{s($1)} a splitting headache.",
         _55 = "{name($1)} suffer{s($1)} from venom.",
         _56 = "{name($1)} {is($1)} chilled by infernal squall.",
         _57 = "{name($1)} {is($1)} shocked by a shrill sound.",
         _58 = "{name($1)}{his_owned($1)} nerves are hurt.",
         _59 = "{name($1)} {is($1)} hurt by chaotic force.",
         -- _60
         _61 = "{name($1)} get{s($1)} a cut.",
         -- _62
         _63 = "{name($1)} {is($1)} burnt by acid.",
      },

      resist = {
         gain = {
            _50 = "Suddenly, {name($1)} feel{s($1)} very hot.",
            _51 = "Suddenly, {name($1)} feel{s($1)} very cool.",
            _52 = "{name($1)}{is($1)} struck by an electric shock.",
            _54 = "Suddenly, {name($1)}{his_owned($1)} mind becomes very clear.",
            _58 = "{name($1)}{his_owned($1)} nerve is sharpened.",
            _53 = "{name($1)} no longer fear{s($1)} darkness.",
            _57 = "{name($1)}{his_owned($1)} eardrums get thick.",
            _59 = "Suddenly, {name($1)} understand{s($1)} chaos.",
            _55 = "{name($1)} now {have($1)} antibodies to poisons.",
            _56 = "{name($1)} {is($1)} no longer afraid of hell.",
            _60 = "{name($1)}{his_owned($1)} body is covered by a magical aura.",
         },
         lose = {
            _50 = "{name($1)} sweat{s($1)}.",
            _51 = "{name($1)} shiver{s($1)}.",
            _52 = "{name($1)} {is($1)} shocked.",
            _54 = "{name($1)}{his_owned($1)} mind becomes slippery.",
            _58 = "{name($1)} become{s($1)} dull.",
            _53 = "Suddenly, {name($1)} fear{s($1)} darkness.",
            _57 = "{name($1)} become{s($1)} very sensitive to noises.",
            _59 = "{name($1)} no longer understand{s($1)} chaos.",
            _55 = "{name($1)} lose{s($1)} antibodies to poisons.",
            _56 = "{name($1)} {is($1)} afraid of hell.",
            _60 = "The magical aura disappears from {name($1)}{his_owned($1)} body.",
         },
      },
   },
}
