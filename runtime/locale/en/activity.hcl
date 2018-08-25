locale {
    activity {
        cancel {
            prompt = "Do you want to cancel ${_1}? "
            normal = "${name(_1)} stop${s(_1)} ${_2}."
            item = "${name(_1)} cancel${s(_1)} ${his(_1)} action."
        }

        eat {
            start {
                normal = "${name(_1)} start${s(_1)} to eat ${itemname(_2, 1)}."
                in_secret = "${name(_1)} start${s(_1)} to eat ${itemname(_2, 1)} in secret."

                mammoth = "\"Let's eatammoth.\""
            }

            finish = "${name(_1)} ${have(_1)} finished eating ${itemname(_2, 1)}."
        }

        perform {
            start = "${name(_1)} start${s(_1)} to play ${itemname(_2)}."

            sound {
                random = [
                    "*Tiki*",
                    "*Dan*",
                    "*Lala*"
                ]
                cha = "*Cha*"
            }

            gets_angry = "${name(_1)} get${s(_1)} angry."

            dialog {
                interest = [
                    "${name(_1)} clap${s(_1)}.",
                    "${name(_1)} listen${s(_1)} to ${name(_2)}${his_owned(_2)} music joyfully.",
                    "\"Bravo!\"",
                    "\"Nice song.\"",
                    "\"Scut!\"",
                    "${name(_1)} ${is(_1)} excited!"
                ]
                disinterest = [
                    "\"Boring.\"",
                    "\"I've heard this before.\"",
                    "\"This song again?\""
                ]
                angry = [
                    "\"Boo boo!\"",
                    "\"Shut it!\"",
                    "\"What are you doing!\"",
                    "\"You can't play shit.\""
                ]
            }

            throws_rock = "${name(_1)} throw${s(_1)} a rock."

            quality {
                _0 = "It is a waste of time."
                _1 = "Almost everyone ignores you."
                _2 = "You need to practice lot more."
                _3 = "You finish your performance."
                _4 = "Not good."
                _5 = "People seem to like your performance."
                _6 = "Your performance is successful."
                _7 = "Wonderful!"
                _8 = "Great performance. Everyone cheers you."
                _9 = "A Legendary stage!"
            }

            tip = "The audience gives ${name(_1)} total of ${_2} gold pieces."
        }

        sex {
            take_clothes_off = "${name(_1)} begin${s(_1)} to take ${his(_1)} clothes off."
            spare_life = "\"I-I don't really know that ${_1}. Please spare my life!\""

            dialog = [
                "\"Yes!\"",
                "\"Ohhh\"",
                "*gasp*",
                "*rumble*",
                "\"come on!\""
            ]

            after_dialog = [
                "You are awesome!",
                "Oh my god....",
                "Okay, okay, you win!",
                "Holy...!"
            ]

            take = "Here, take this."
            take_all_i_have = "Take this money, it's all I have!"
            gets_furious = "${name(_1)} gets furious, \"And you think you can just run away?\""

            # "(after_dialog) (take/take_all_i_have)"
            format = "\"${_1} ${_2}\""
        }

        steal {
            start = "You target ${itemname(_1, 1)}."
            notice {
                in_fov = "${name(_1)} notice${s(_1)} you,"
                out_of_fov = "${name(_1)} hear${s(_1)} loud noise,"
                dialog {
                    guard = "\"You there, stop!\""
                    other = "\"Guards! Guards!\""
                }
                you_are_found = "You are found stealing."
            }
            target_is_dead = "The target is dead."
            cannot_be_stolen = "It can't be stolen."
            you_lose_the_target = "You lose the target."
            it_is_too_heavy = "It's too heavy."
            abort = "You abort stealing."
            succeed = "You successfully steal ${itemname(_1)}."
            guilt = "You feel the stings of conscience."
        }

        rest {
            start = "You lie down to rest."
            finish = "You finished taking a rest."
            drop_off_to_sleep = "After a short while, you drop off to sleep."
        }

        sleep {
            start {
                global = "You start to camp."
                other = "You lie down."
            }

            finish = "You fall asleep."
            but_you_cannot = "But you can't sleep right now."

            new_gene {
                title = "Gene"
                text = "You spent a night with ${name(_1)}. A new gene is created."

                choices {
                    _0 = "Sweet."
                }
            }

            slept_for = "You have slept for ${_1} hours. You are refreshed."

            wake_up {
                so_so = "You wake up feeling so so."
                good = "You wake up feeling good. Your potential increases. (Total:${_1}%)"
            }
        }

        construct {
            start = "You start to construct ${itemname(_1, 1)}."
            finish = "You finish constructing ${itemname(_1, 1)}."
        }

        pull_hatch {
            start = "You start to pull the hatch."
            finish = "You finish pulling the hatch of ${itemname(_1, 1)}."
        }

        dig = "You start to pick ${itemname(_1, 1)}."

        study {
            start {
                bored = "You are bored."
                studying = "You begin to study ${_1}."
                training = "You start training."
                weather_is_bad = "The weather's bad outside, you have plenty of time to waste."
            }
            finish {
                studying = "You finish studying ${_1}."
                training = "You finish training."
            }
        }

        read {
            start = "${name(_1)} start${s(_1)} to read ${itemname(_2, 1)}."
            finish = "${name(_1)} ${have(_1)} finished reading the book."
        }

        harvest {
            sound = [
                "*sing*",
                "*pull*",
                "*thud*",
                "*rumble*",
                "*gasp*"
            ]
            finish = "You harvest ${itemname(_1, 1)}. (${_2})"
        }

        fishing {
            start = "You start fishing."
            fail = "A waste of a time..."
            get = "You get ${itemname(_1, 1)}!"
        }

        material {
            start = "You start to search the spot."
            get = "You ${_1} ${_2} ${_3}${s(_2)}."

            get_verb {
                dig_up = "dig up"
                fish_up = "fish up"
                harvest = "harvest"
                find = "find"
                get = "get"
            }

            lose = "You lose ${_1} ${_2}${s(_1)}."
            lose_total = "(Total: ${_1}) "

            digging {
                fails = "Your mining attempt fails."
                no_more = "There's no more ore around."
            }
            fishing {
                fails = "Your fishing attempt fails."
                no_more = "The spring dries up."
            }
            searching {
                fails = "Your searching attempt fails."
                no_more = "You can't find anything anymore."
            }
            harvesting {
                no_more = "There's no more plant around."
            }
        }

        dig_spot {
            start {
                global = "You start to dig the ground."
                other = "You start to dig the spot."
            }

            sound = [
                "*clink*",
                "*smash*",
                "*thud*",
                "*sing*",
                "*sigh*"
            ]

            finish = "You finish digging."
            something_is_there = "*click* ...something is there!"
        }

        dig_mining {
            start {
                wall = "You start to dig the wall."
                spot = "You start to dig the mining spot."
                hard = "These walls look pretty hard!"
            }

            finish {
                wall = "You finished digging the wall."
                find = "You found something out of crushed heaps of rock."
            }

            fail = "Your back hurts...You give up digging."
        }

        iron_maiden = "Suddenly, the iron maiden falls forward."
        guillotine = "Suddenly, the guillotine is activated."
    }
}
