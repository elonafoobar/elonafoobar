locale {
    food {
        # Names for cooked food.
        # These are organized by type, then quality.
        names {
            # Meat
            _1 {
                default_origin = "beast"
                _1 = "grotesque ${_1} meat"
                _2 = "charred ${_1} meat"
                _3 = "roast ${_1}"
                _4 = "deep fried ${_1}"
                _5 = "skewer grilled ${_1}"
                _6 = "${_1} croquette"
                _7 = "${_1} hamburger"
                _8 = "${_1} cutlet"
                _9 = "${_1} steak"
            }
            # Vegetable
            _2 {
                default_origin = "vegetable"
                _1 = "kitchen refuse ${_1}"
                _2 = "smelly ${_1}"
                _3 = "${_1} salad"
                _4 = "fried ${_1}"
                _5 = "${_1} roll"
                _6 = "${_1} tempura"
                _7 = "${_1} gratin"
                _8 = "meat and ${_1} stew"
                _9 = "${_1} curry"
            }
            # Fruit
            _3 {
                default_origin = "fruit"
                _1 = "dangerous ${_1}"
                _2 = "doubtful ${_1}"
                _3 = "${_1} jelly salad"
                _4 = "${_1} pudding"
                _5 = "${_1} sherbet"
                _6 = "${_1} ice cream"
                _7 = "${_1} crepe"
                _8 = "${_1} fruit cake"
                _9 = "${_1} grand parfait"
            }
            # Candy
            _4 {
                default_origin = "candy"
                _1 = "collapsed ${_1}"
                _2 = "nasty ${_1}"
                _3 = "${_1} cookie"
                _4 = "${_1} jelly"
                _5 = "${_1} pie"
                _6 = "${_1} bun"
                _7 = "${_1} cream puff"
                _8 = "${_1} cake"
                _9 = "${_1} sachertorte"
            }
            # Noodle
            _5 {
                default_origin = "noodle"
                _1 = "risky ${_1}"
                _2 = "exhausted ${_1}"
                _3 = "salad pasta"
                _4 = "udon"
                _5 = "soba"
                _6 = "peperoncino"
                _7 = "carbonara"
                _8 = "ramen"
                _9 = "meat spaghetti"
            }
            # Fish
            _6 {
                default_origin = "fish"
                _1 = "leftover ${_1}"
                _2 = "bony ${_1}"
                _3 = "fried ${_1}"
                _4 = "stewed ${_1}"
                _5 = "${_1} soup"
                _6 = "${_1} tempura"
                _7 = "${_1} sausage"
                _8 = "${_1} sashimi"
                _9 = "${_1} sushi"
            }
            # Bread
            _7 {
                default_origin = "bread"
                _1 = "fearsome ${_1}"
                _2 = "hard ${_1}"
                _3 = "walnut bread"
                _4 = "apple pie"
                _5 = "sandwich"
                _6 = "croissant"
                _7 = "croquette sandwich"
                _8 = "chocolate babka"
                _9 = "melon flavored bread"
            }
            # Egg
            _8 {
                default_origin = "animal"
                _1 = "grotesque ${_1} egg"
                _2 = "overcooked ${_1} egg"
                _3 = "fried ${_1} egg"
                _4 = "${_1} egg toast"
                _5 = "soft boiled ${_1} egg"
                _6 = "soup with ${_1} egg"
                _7 = "mature ${_1} cheese"
                _8 = "${_1} cheese cake"
                _9 = "${_1} omlet"
            }
        }

        passed_rotten {
            _0 = "\"Yuck!!\""
            _1 = "\"....!!\""
            _2 = "\"W-What...\""
            _3 = "\"Are you teasing me?\""
            _4 = "\"You fool!\""
            _5 = "\"Yuck!!\"" # JP has 6 options, so one more was added here.
        }

        mochi {
            chokes = "${name(_1)} choke${s(_1)} on mochi!"
            dialog = "\"Mm-ghmm\""
        }

        hunger_status {
            hungry {
                _0 = "You are getting hungry."
                _1 = "You feel hungry."
                _2 = "Now what shall I eat?"
            }
            very_hungry {
                _0 = "Your hunger makes you dizzy."
                _1 = "You have to eat something NOW."
            }
            starving {
                _0 = "You are starving!"
                _1 = "You are almost dead from hunger."
            }
        }

        eating_message {
            bloated {
                _0 = "Phew! You are pretty bloated."
                _1 = "You've never eaten this much before!"
                _2 = "Your stomach is unbelievably full!"
            }
            satisfied {
                _0 = "You are satisfied!"
                _1 = "This hearty meal has filled your stomach."
                _2 = "You really ate!"
                _3 = "You pat your stomach contentedly."
            }
            normal {
                _0 = "You can eat more."
                _1 = "You pat your stomach."
                _2 = "You satisfied your appetite a little."
            }
            hungry {
                _0 = "You are still a bit hungry."
                _1 = "Not enough..."
                _2 = "You want to eat more."
                _3 = "Your stomach is still somewhat empty."
            }
            very_hungry {
                _0 = "No, it was not enough at all."
                _1 = "You still feel very hungry."
                _2 = "You aren't satisfied."
            }
            starving {
                _0 = "It didn't help you from starving!"
                _1 = "It prolonged your death for seconds."
                _2 = "Empty! Your stomach is still empty!"
            }
        }

        not_affected_by_rotten = "But ${name(_1)}${his_owned(_1)} stomach isn't affected."

        anorexia {
            develops = "${name(_1)} develop${s(_1)} anorexia."
            recovers_from = "${name(_1)} manage${s(_1)} to recover from anorexia."
        }

        vomits = "${name(_1)} vomit${s(_1)}."
        spits_alien_children = "${name(_1)} spit${s(_1)} alien children from ${his(_1)} body!"

        eat_status {
            good = "${name(_1)} feel${s(_1)} good."
            bad = "${name(_1)} feel${s(_1)} bad."
            cursed_drink = "${name(_1)} feel${s(_1)} grumpy."
        }

        cook = "You cook ${_1} with ${_itemname(_2, 1)} and make ${_itemname(_3, 1)}."

        effect {
            rotten = "Ugh! Rotten food!"

            raw_meat = "Ugh...Raw meat..."
            powder = "It tastes like...powder..."
            raw = "Er...this needs to be cooked."
            boring {
                _0 = "It doesn't taste awful but..."
                _1 = "Very boring food."
            }

            raw_glum = "${name(_1)} looks glum."

            herb {
                curaria = "This herb invigorates you."
                morgia = "You feel might coming through your body."
                mareilon = "You feel magical power springs up inside you."
                spenseweed = "You feel as your sense is sharpened."
                alraunia = "Your hormones are activated."
            }

            human {
                like = "It's your favorite human flesh!"
                dislike = "Eeeek! It's human flesh!"
                would_have_rather_eaten = "You would've rather eaten human flesh."
                delicious = "Delicious!"
            }

            bomb_fish = "「Ugh-Ughu」 ${name(_1)} spew${s(_1)} up ${itemname(_2, 1)}."
            little_sister = "${name(_1)} evolve${s(_1)}."
            hero_cheese = "The food is a charm!"

            fortune_cookie = "${name(_1)} read${s(_1)} the paper fortune."
            sisters_love_fueled_lunch = "${name(_1)}${his_owned(_1)} heart is warmed."

            poisoned {
                text = "It's poisoned! ${name(_1)} writhe${s(_1)} in agony!"
                dialog {
                    _0 = "\"Gyaaaaa...!\""
                    _1 = "\"Ugh!\""
                }
            }

            spiked {
                self = "You are excited!"
                other {
                    _0 = "${name(_1)} gasps, \"I f-feel...strange...\""
                    _1 = "${name(_1)} gasps \"Uh..uh..What is this feeling...\""
                }
            }

            ability {
                develops = "${name(_1)}${his_owned(_1)} ${_2} develops."
                deteriorates = "${name(_1)}${his_owned(_1)} ${_2} deteriorates."
            }

            growth = "${name(_1)}${his_owned(_1)} ${_2} enters a period of rapid growth."

            corpse {
                iron = "It's too hard! ${name(_1)}${his_owned(_1)} stomach screams."
                deformed_eye = "It tastes really, really strange."
                horse = "A horsemeat! It's nourishing"
                holy_one = "${name(_1)} feel${s(_1)} as ${he(_1)} ${have(_1)} been corrupted."
                at = "You dare to eat @..."
                guard = "Guards hate you."
                vesda = "${name(_1)}${his_owned(_1)} body burns up for a second."
                insanity = "Sheer madness!"
                putit = "${name(_1)}${his_owned(_1)} skin becomes smooth."
                cupid_of_love = "${name(_1)} feel${s(_1)} love!"
                poisonous = "Argh! It's poisonous!"
                troll = "A troll meat. This must be good for your body."
                rotten_one = "Of course, it's rotten! Urgh..."
                beetle = "Mighty taste!"
                mandrake = "${name(_1)} ${is(_1)} magically stimulated."
                grudge = "Something is wrong with ${name(_1)}${his_owned(_1)} stomach..."
                calm = "Eating this brings ${name(_1)} inner peace."
                chaos_cloud = "${name(_1)} ${is(_1)} shaken by a chaotic power."
                lightning = "${name(_1)}${his_owned(_1)} nerve is damaged."
                cat = "How can you eat a cat!!"
                ether = "Ether corrupts ${name(_1)}${his_owned(_1)} body."
                giant = "This food is good for your endurance."
                imp = "This food is good for your magic."
                strength = "This food is good for your strength."
                ghost = "This food is good for your will power."
                quickling = "Wow, ${name(_1)} speed${s(_1)} up!"
                alien = "Something gets into ${name(_1)}${his_owned(_1)} body."
            }

            quality {
                bad {
                    _0 = "Boy, it gives your stomach trouble!"
                    _1 = "Ugh! Yuk!"
                    _2 = "Awful taste!!"
                }
                so_so {
                    _0 = "Uh-uh, the taste is so so."
                    _1 = "The taste is not bad."
                }
                good {
                    _0 = "It tasted good."
                    _1 = "Decent meal."
                }
                great {
                    _0 = "Delicious!"
                    _1 = "Gee what a good taste!"
                    _2 = "It tasted pretty good!"
                }
                delicious {
                    _0 = "Wow! Terrific food!"
                    _1 = "Yummy! Absolutely yummy!"
                    _2 = "It tasted like seventh heaven!"
                }
            }
        }
    }
}
