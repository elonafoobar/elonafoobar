local I18N = require("core.I18N")

I18N.add {
   food = {
      -- Names for cooked food.
      -- These are organized by type, then quality.
      names = {
         -- Meat
         _1 = {
            default_origin = "beast",
            _1 = "grotesque {$1} meat",
            _2 = "charred {$1} meat",
            _3 = "roast {$1}",
            _4 = "deep fried {$1}",
            _5 = "skewer grilled {$1}",
            _6 = "{$1} croquette",
            _7 = "{$1} hamburger",
            _8 = "{$1} cutlet",
            _9 = "{$1} steak",
         },
         -- Vegetable
         _2 = {
            default_origin = "vegetable",
            _1 = "kitchen refuse {$1}",
            _2 = "smelly {$1}",
            _3 = "{$1} salad",
            _4 = "fried {$1}",
            _5 = "{$1} roll",
            _6 = "{$1} tempura",
            _7 = "{$1} gratin",
            _8 = "meat and {$1} stew",
            _9 = "{$1} curry",
         },
         -- Fruit
         _3 = {
            default_origin = "fruit",
            _1 = "dangerous {$1}",
            _2 = "doubtful {$1}",
            _3 = "{$1} jelly salad",
            _4 = "{$1} pudding",
            _5 = "{$1} sherbet",
            _6 = "{$1} ice cream",
            _7 = "{$1} crepe",
            _8 = "{$1} fruit cake",
            _9 = "{$1} grand parfait",
         },
         -- Candy
         _4 = {
            default_origin = "candy",
            _1 = "collapsed {$1}",
            _2 = "nasty {$1}",
            _3 = "{$1} cookie",
            _4 = "{$1} jelly",
            _5 = "{$1} pie",
            _6 = "{$1} bun",
            _7 = "{$1} cream puff",
            _8 = "{$1} cake",
            _9 = "{$1} sachertorte",
         },
         -- Noodle
         _5 = {
            default_origin = "noodle",
            _1 = "risky {$1}",
            _2 = "exhausted {$1}",
            _3 = "salad pasta",
            _4 = "udon",
            _5 = "soba",
            _6 = "peperoncino",
            _7 = "carbonara",
            _8 = "ramen",
            _9 = "meat spaghetti",
         },
         -- Fish
         _6 = {
            default_origin = "fish",
            _1 = "leftover {$1}",
            _2 = "bony {$1}",
            _3 = "fried {$1}",
            _4 = "stewed {$1}",
            _5 = "{$1} soup",
            _6 = "{$1} tempura",
            _7 = "{$1} sausage",
            _8 = "{$1} sashimi",
            _9 = "{$1} sushi",
         },
         -- Bread
         _7 = {
            default_origin = "bread",
            _1 = "fearsome {$1}",
            _2 = "hard {$1}",
            _3 = "walnut bread",
            _4 = "apple pie",
            _5 = "sandwich",
            _6 = "croissant",
            _7 = "croquette sandwich",
            _8 = "chocolate babka",
            _9 = "melon flavored bread",
         },
         -- Egg
         _8 = {
            default_origin = "animal",
            _1 = "grotesque {$1} egg",
            _2 = "overcooked {$1} egg",
            _3 = "fried {$1} egg",
            _4 = "{$1} egg toast",
            _5 = "soft boiled {$1} egg",
            _6 = "soup with {$1} egg",
            _7 = "mature {$1} cheese",
            _8 = "{$1} cheese cake",
            _9 = "{$1} omlet",
         },
      },

      passed_rotten = {
         "\"Yuck!!\"",
         "\"....!!\"",
         "\"W-What...\"",
         "\"Are you teasing me?\"",
         "\"You fool!\"",
      },

      mochi = {
         chokes = "{name($1)} choke{s($1)} on mochi!",
         dialog = "\"Mm-ghmm\"",
      },

      hunger_status = {
         hungry = {
            "You are getting hungry.",
            "You feel hungry.",
            "Now what shall I eat?",
         },
         very_hungry = {
            "Your hunger makes you dizzy.",
            "You have to eat something NOW.",
         },
         starving = {
            "You are starving!",
            "You are almost dead from hunger.",
         },
      },

      eating_message = {
         bloated = {
            "Phew! You are pretty bloated.",
            "You've never eaten this much before!",
            "Your stomach is unbelievably full!",
         },
         satisfied = {
            "You are satisfied!",
            "This hearty meal has filled your stomach.",
            "You really ate!",
            "You pat your stomach contentedly.",
         },
         normal = {
            "You can eat more.",
            "You pat your stomach.",
            "You satisfied your appetite a little.",
         },
         hungry = {
            "You are still a bit hungry.",
            "Not enough...",
            "You want to eat more.",
            "Your stomach is still somewhat empty.",
         },
         very_hungry = {
            "No, it was not enough at all.",
            "You still feel very hungry.",
            "You aren't satisfied.",
         },
         starving = {
            "It didn't help you from starving!",
            "It prolonged your death for seconds.",
            "Empty! Your stomach is still empty!",
         },
      },

      not_affected_by_rotten = "But {name($1)}{his_owned($1)} stomach isn't affected.",

      anorexia = {
         develops = "{name($1)} develop{s($1)} anorexia.",
         recovers_from = "{name($1)} manage{s($1)} to recover from anorexia.",
      },

      vomits = "{name($1)} vomit{s($1)}.",
      spits_alien_children = "{name($1)} spit{s($1)} alien children from {his($1)} body!",

      eat_status = {
         good = "{name($1)} feel{s($1)} good.",
         bad = "{name($1)} feel{s($1)} bad.",
         cursed_drink = "{name($1)} feel{s($1)} grumpy.",
      },

      cook = "You cook {$1} with {itemname($2, 1)} and make {itemname($3, 1)}.",

      effect = {
         rotten = "Ugh! Rotten food!",

         raw_meat = "Ugh...Raw meat...",
         powder = "It tastes like...powder...",
         raw = "Er...this needs to be cooked.",
         boring = {
            "It doesn't taste awful but...",
            "Very boring food.",
         },

         raw_glum = "{name($1)} looks glum.",

         herb = {
            curaria = "This herb invigorates you.",
            morgia = "You feel might coming through your body.",
            mareilon = "You feel magical power springs up inside you.",
            spenseweed = "You feel as your sense is sharpened.",
            alraunia = "Your hormones are activated.",
         },

         human = {
            like = "It's your favorite human flesh!",
            dislike = "Eeeek! It's human flesh!",
            would_have_rather_eaten = "You would've rather eaten human flesh.",
            delicious = "Delicious!",
         },

         bomb_fish = "「Ugh-Ughu」 {name($1)} spew{s($1)} up {itemname($2, 1)}.",
         little_sister = "{name($1)} evolve{s($1)}.",
         hero_cheese = "The food is a charm!",

         fortune_cookie = "{name($1)} read{s($1)} the paper fortune.",
         sisters_love_fueled_lunch = "{name($1)}{his_owned($1)} heart is warmed.",

         poisoned = {
            text = "It's poisoned! {name($1)} writhe{s($1)} in agony!",
            dialog = {
               "\"Gyaaaaa...!\"",
               "\"Ugh!\"",
            },
         },

         spiked = {
            self = "You are excited!",
            other = {
               "{name($1)} gasps, \"I f-feel...strange...\"",
               "{name($1)} gasps \"Uh..uh..What is this feeling...\"",
            },
         },

         ability = {
            develops = "{name($1)}{his_owned($1)} {$2} develops.",
            deteriorates = "{name($1)}{his_owned($1)} {$2} deteriorates.",
         },

         corpse = {
            iron = "It's too hard! {name($1)}{his_owned($1)} stomach screams.",
            deformed_eye = "It tastes really, really strange.",
            horse = "A horsemeat! It's nourishing",
            holy_one = "{name($1)} feel{s($1)} as {he($1)} {have($1)} been corrupted.",
            at = "You dare to eat @...",
            guard = "Guards hate you.",
            vesda = "{name($1)}{his_owned($1)} body burns up for a second.",
            insanity = "Sheer madness!",
            putit = "{name($1)}{his_owned($1)} skin becomes smooth.",
            cupid_of_love = "{name($1)} feel{s($1)} love!",
            poisonous = "Argh! It's poisonous!",
            troll = "A troll meat. This must be good for your body.",
            rotten_one = "Of course, it's rotten! Urgh...",
            beetle = "Mighty taste!",
            mandrake = "{name($1)} {is($1)} magically stimulated.",
            grudge = "Something is wrong with {name($1)}{his_owned($1)} stomach...",
            calm = "Eating this brings {name($1)} inner peace.",
            chaos_cloud = "{name($1)} {is($1)} shaken by a chaotic power.",
            lightning = "{name($1)}{his_owned($1)} nerve is damaged.",
            cat = "How can you eat a cat!!",
            ether = "Ether corrupts {name($1)}{his_owned($1)} body.",
            giant = "This food is good for your endurance.",
            imp = "This food is good for your magic.",
            strength = "This food is good for your strength.",
            ghost = "This food is good for your will power.",
            quickling = "Wow, {name($1)} speed{s($1)} up!",
            alien = "Something gets into {name($1)}{his_owned($1)} body.",
         },

         quality = {
            bad = {
               "Boy, it gives your stomach trouble!",
               "Ugh! Yuk!",
               "Awful taste!!",
            },
            so_so = {
               "Uh-uh, the taste is so so.",
               "The taste is not bad.",
            },
            good = {
               "It tasted good.",
               "Decent meal.",
            },
            great = {
               "Delicious!",
               "Gee what a good taste!",
               "It tasted pretty good!",
            },
            delicious = {
               "Wow! Terrific food!",
               "Yummy! Absolutely yummy!",
               "It tasted like seventh heaven!",
            },
         },
      },
   },
}
