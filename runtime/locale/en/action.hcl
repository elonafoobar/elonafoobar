locale {
    action {
        cannot_do_in_global = "You can't do that while you're in a global area."
        hit_key_for_help = "Hit ? key to display help."
        really_attack = "Really attack ${name(_1)}?"

        backpack_squashing = "Your backpack is squashing you!"

        day_breaks = "Day breaks."
        new_day = "A day passes and a new day begins."

        weather {
            changes = "The weather changes."
            ether_wind {
                starts = "Ether Wind starts to blow. You need to find a shelter!"
                stops = "The Ether Wind dissipates."
            }
            rain {
                draw_cloud = "You draw a rain cloud."
                starts = "It starts to rain."
                starts_heavy = "Suddenly, rain begins to pour down from the sky."
                stops = "It stops raining."
                becomes_heavier = "The rain becomes heavier."
                becomes_lighter = "The rain becomes lighter."
            }
            snow {
                starts = "It starts to snow."
                stops = "It stops raining."
            }
        }

        time_stop {
            begins = "${name(_1)} stop${s(_1)} time."
            ends = "Time starts to run again."
        }

        which_direction {
            default = "Which direction? "
            spell = "Which direction do you want to cast the spell? "
            wand = "Which direction do you want to zap the wand? "
            cannot_see_location = "You can't see the location."
            out_of_range = "It's out of range."
        }


        exit_map {
            not_permitted = "You are not permitted to explore this dungeon."
            no_invitation_to_pyramid = "You don't have an invitation."
            cannot_enter_jail = "The guards turn you away from the jail."
            surface {
                returned_to = "You returned to the surface of ${_1}"
                left = "You left the surface of ${_1}."
            }

            delivered_to_your_home = "You were delivered to your home."

            entered = "You entered ${_1}."
            returned_to = "You returned to ${_1}"
            left = "You left ${_1}."

            burdened_by_cargo = "The weight of your cargo burdens your traveling speed."

            mountain_pass = "You entered the Mountain Pass."
            larna = "You reached the town of Larna."

            it_is_hot = "It's hot!"

            gate {
                step_into = "You stepped into the gate. The gate disappears."
                need_network = "You have to turn on network setting."
            }
        }

        interact {
            choose = "Choose the direction of the target."
            prompt = "What action do you want to perform to ${him(_1)}? "
            choices {
                talk = "Talk"
                attack = "Attack"
                inventory = "Inventory"
                give = "Give"
                bring_out = "Bring Out"
                appearance = "Appearance"
                teach_words = "Teach Words"
                change_tone = "Change Tone"
                release = "Release"
                name = "Name"
                info = "Info"
            }

            change_tone {
                prompt = "What sentence should ${name(_1)} learn? "
                default_tone = "Default Tone"
                tone_of_voice = "Tone of Voice"
                enter = "Enter [Change Tone] "
                title = "Title"
                is_somewhat_different = "${name(_1)} is somewhat different."
            }
            name {
                prompt = "What do you want to call ${him(_1)}? "
                cancel = "You changed your mind."
                you_named = "You named ${him(_1)} ${basename(_1)}."
            }
            release = "You release ${name(_1)}."
        }

        bash {
            prompt = "Which direction do you want to bash? "
            tree {
                execute = "You throw your weight against ${itemname(_1)}."
                no_fruits = "It seems there are no fruits left on the tree."
                falls_down = "${itemname(_1, 1)} falls down from the tree."
            }
            choked {
                execute = "${name(_1)} bash${s(_1, true)} up ${name(_2)} at full power."
                spits = "${name(_1)} spit${s(_1)} mochi."
                dialog = "\"You saved me!\""
            }
            execute = "${name(_1)} bash${s(_1, true)} up ${name(_2)}"
            disturbs_sleep = "${name(_1)} disturb${s(_1)} ${his(_2)} sleep."
            shatters_pot = "${name(_1)} shatter${s(_1)} the pot."
            door {
                destroyed = "You bash up the door. The door is destroyed."
                execute = "You bash up the door."
                jail = "As might be expected, the door of the Jail is hard."
                hurt = "${name(_1)} hurt${s(_1)} ${his(_1)} muscle."
                cracked = "The door is cracked a bit."
            }
            air = "${name(_1)} bash${s(_1, true)} up the air."
        }

        move {
            sense_something = "You sense something under your foot."
            walk_into = "You walk into ${_1}."
            twinkle = "*twinkle*"

            item_on_cell {
                item = "You see ${_1} here."
                building = "${_1} is constructed here."
                not_owned = "You see ${_1} placed here." # TODO correct name?
                more_than_three = "There are ${_1} items lying here."
            }

            feature {
                stair {
                    down = "There is a stair leading downwards here."
                    up = "There is a stair leading upwards here."
                }
                material {
                    spot = "You can search this location to collect some materials."
                    remains = "You can collect materials from the remains lying here."
                    mining = "You can collect materials from the mining spot here."
                    spring = "You can collect materials from the spring here."
                    plants = "You can collect materials from plants here."
                }
                seed {
                    type {
                        vegetable = "vegetable"
                        fruit = "fruit"
                        herb = "herb"
                        strange = "strange"
                        artifact = "artifact"
                        gem = "gem"
                        magic = "magic"
                    }
                    growth {
                        seed = "A ${_1} seed is planted."
                        bud = "A ${_1} bud is growing."
                        tree = "A ${_1} tree has bore a lot of fruit."
                        withered = "A ${_1} tree has withered..."
                    }
                }
            }

            trap {
                disarm {
                    fail = "You fail to disarm the trap."
                    succeed = "You disarm the trap."
                    dismantle = "You dismantle the trap."
                }
                evade = "${name(_1)} evade${s(_1)} a trap."
                activate {
                    text = "${name(_1)} activate${s(_1)} a trap!"
                    blind = "Gallons of ink spreads."
                    paralyze = "Stimulative gas spreads."
                    confuse = "Smelly gas spreads."
                    poison = "Poisonous gas spreads."
                    sleep = "Sleeping gas spreads."
                    mine = "*kabooom*"
                    spears {
                        text = "Several spears fly out from the ground."
                        target_floating = "But they don't reach ${name(_1)}."
                    }
                }
            }

            global {
                nap = "You take a nap."

                weather {
                    snow {
                        message {
                            _0 = "Snow delays your travel."
                            _1 = "You are caught in a snowdrift."
                            _2 = "It's hard to walk on a snowy road."
                        }
                        sound {
                            # TODO: JP has 4 variants, EN has 5
                            _0 = " *kisssh*"
                            _1 = "*thudd*"
                            _2 = "*siz*"
                            _3 = "*clump*"
                            _4 = "*skritch*"
                        }
                        eat = "You are too hungry. You chow down snow."
                    }

                    heavy_rain {
                        message {
                            # TODO: JP has 3 variants, EN has 2
                            _0 = "It's raining heavily. You lose your way."
                            _1 = "You can't see a thing!"
                            _2 = "It's raining heavily. You lose your way."
                        }
                        sound {
                            # TODO: JP has 4 variants, EN has 5
                            _0 = "*drip*"
                            _1 = "*sip*"
                            _2 = "*drizzle*"
                            _3 = "*splash*"
                            _4 = "*kissh*"
                        }
                    }
                }

                ambush {
                    text = "Ambush!"
                    distance_from_nearest_town = "Distance from nearest town:${_1}" # NOTE
                    enemy_strength = "Enemy strength:${_1}" # NOTE

                    rank {
                        putit = "Putit Rank"
                        orc = "Orc Rank"
                        grizzly_bear = "Grizzly Bear Rank"
                        drake = "Drake Rank"
                        lich = "Lich Rank"
                        dragon = "Dragon Rank"
                    }
                }

                diastrophism = "A sudden diastrophism hits the continent."
            }
        }

        target {
            out_of_sight = "This location is out of sight."
            you_are_targeting = "You are targeting ${name(_1)}.(Distance ${_2})"

            level {
                _0 = "You can absolutely beat ${him(_1)} with your eyes closed and arms crossed."
                _1 = "You bet you can beat ${him(_1)} with your eyes closed."
                _2 = "${he(_1)} ${is(_1)} an easy opponent." # TODO cnven(he())
                _3 = "You will probably win."
                _4 = "Won't be an easy fight."
                _5 = "The opponent looks quite strong."
                _6 = "${he(_1)} ${is(_1)} at least twice stronger than you." # TODO cnven(he())
                _7 = "You will get killed unless miracles happen."
                _8 = "You will get killed, a hundred percent sure."
                _9 = "${he(_1)} can mince you with ${his(_1)} eyes closed." # TODO cnven(he())
                _10 = "If ${he(_1)} is a giant, you are less than a dropping of an ant."
            }
        }

        look {
            find_nothing = "You look around and find nothing."
            cannot_see = "You can't see the location." # TODO possible duplicate
            target = "You target ${name(_1)}."
            target_the_ground = "You target the ground."
        }

        ranged {
            load_normal_ammo = "You load normal ammo."
            no_target = "You find no target."
        }

        ammo {
            need_to_equip = "You need to equip an ammo."
            is_not_capable = "${itemname(_1)} isn't capable of changing ammos."

            current = "Current Ammo Type" # NOTE
            normal = "Normal"
            unlimited = "Unlimited"
        }

        unlock {
            do_not_have_lockpicks = "You don't have lockpicks."
            use_lockpick = "You use a lockpick."
            use_skeleton_key = "You also use the skeleton key."
            too_difficult = "The lock mechanism is beyond your skill."
            easy = "Easy."
            fail = "You fail to unlock it."
            lockpick_breaks = "Your lockpick breaks."
            try_again = "Try again?"
            succeed = "You successfully unlock it."
        }

        open {
            text = "You open ${itemname(_1)}."
            goods = "Several quality goods spread out from ${itemname(_1)}."
            new_year_gift {
                something_jumps_out = "Something jumps out from the pack!"
                trap = "It's trap! The gift ignites."
                cursed_letter = "You find a cursed letter inside."
                ring = "*ring ring ring*"
                younger_sister = "The pack contains your younger sister!"
                something_inside = "There's something inside the pack."
                wonderful = "This is truly a wonderful gift!"
            }
            door {
                succeed = "${name(_1)} open${s(_1)} the door."
                fail = "${name(_1)} fail${s(_1)} to open the door."
            }
        }

        close {
            nothing_to_close = "There's nothing to close."
            blocked = "There's something on the floor."
            execute = "${name(_1)} close the door."
        }

        pick_up {
            execute = "${name(_1)} pick${s(_1)} up ${_2}."
            used_by_mount = "${name(_1)} ${is(_1)} using it."
            do_you_want_to_remove = "Do you want to remove ${itemname(_1)}?"
            you_absorb_magic = "You absorb magic from ${itemname(_1)}."
            poison_drips = "Poison drips from your hands."
            your_inventory_is_full = "Your inventory is full."
            shopkeepers_inventory_is_full = "Shopkeeper's inventory is full."

            you_buy = "You buy ${_1}."
            you_sell = "You sell ${_1}."
            you_sell_stolen = "You sell ${_1}.(Stolen item sold) "
            thieves_guild_quota = "You still need to sell stuff worth ${_1} gold pieces in order to advance ranks in the Thieves Guild."

            put_in_container = "You put ${_1} in the container."
        }

        drop {
            execute = "You drop ${_1}."
            too_many_items = "The place is too crowded. You can't drop stuff anymore."
            water_is_blessed = "The water is blessed."
        }

        dig {
            prompt = "Which direction do you want to dig? "
            too_exhausted = "You are too exhausted to do that."
        }

        search {
            execute = "You search the surroundings carefully."
            crystal {
                sense = "You sense a blue crystal lying somewhere in this area."
                far = "Still, still lying far ahead."
                normal = "Your heart starts beating in your chest."
                close = "The air around you is filled with strained silence."
            }
            discover {
                trap = "You discover a trap."
                hidden_path = "You discover a hidden path."
            }
            small_coin {
                find = "You find a small coin!"
                far = "You sense something."
                close = "You see something shines."
            }
        }

        throw {
            execute = "${name(_1)} throw${s(_1)} ${itemname(_2, 1)}."
            hits = "It hits ${name(_1)}!"
            monster_ball {
                does_not_work = "This doesn't work in this area."
                cannot_be_captured = "The creature can't be captured."
                not_enough_power = "Power level of the ball is not enough to capture the creature."
                not_weak_enough = "You need to weaken the creature to capture it."
                capture = "You capture ${name(_1)}."
            }
            snow {
                hits_snowman = "It hits ${itemname(_1, 1)} and breaks it."
                melts = "It falls on the ground and melts."

                dialog {
                    _0 ="\"Hey!\""
                    _1 ="\"Now you did it.\""
                    _2 ="*chuckle*"
                    _3 ="\"Tee-hee-hee!\""
                    _4 ="\"You'll pay for this.\""
                    _5 ="*grin*"
                }
            }

            tomato = "*crumble*"
            shatters = "It falls on the ground and shatters."
        }

        read {
            cannot_see = "${name(_1)} can see nothing."
            book {
                finished_decoding = "You finished decoding ${itemname(_1, 1)}!"
                falls_apart = "${itemname(_1, 1)} falls apart."
                not_interested = "You are not interested in this book. Do you want to read it anyway? "
                already_decoded = "You already have decoded the book."
                void_permit = "According to the card, you are permitted to explore the void now."
                book_of_rachel = "It's a lovely fairy tale written by Rachel."
                learned_recipe = "You learned the recipe!"
            }
            scroll {
                dimmed_or_confused = "${name(_1)} stagger${s(_1)}."
                execute = "${name(_1)} read${s(_1)} ${itemname(_2, 1)}."
            }
        }

        zap {
            execute = "You zap ${itemname(_1, 1)}."
            fail = "${name(_1)} fail to use the power of the rod."
        }

        cast {
            overcast_warning = "You are going to over-cast the spell. Are you sure?"
            confused = "${name(_1)} try${s(_1)} to cast a spell in confusion."

            # TODO: possible duplicate
            self = "${name(_1)} cast ${_2}."
            other = "${name(_1)} ${_2}."

            silenced = "The mist of silence interrupts a spell."
            fail = "${name(_1)} fail${s(_1)} to cast a spell."
        }

        drink {
            potion = "${name(_1)} drink${s(_1)} ${itemname(_2, 1)}."
            well {
                is_dry = "${_1} is dry."
                draw = "${name(_1)} draw${s(_1)} water from ${_2}."

                effect {
                    falls {
                        text = "${name(_1)} falls in the well!"
                        dialog = "${name(_1)} yells, \"G-Give me your hands!\""
                        floats = "Soon ${he(_1)} floats up to the surface."
                    }

                    finds_gold = "${name(_1)} find${s(_1)} some gold pieces in water."
                    pregnancy = "${name(_1)} swallow${s(_1)} something bad."
                    monster = "Something comes out from the well!"
                    wish_too_frequent = "You feel as a stroke of good fortune passed by."
                    default = "Phew, fresh water tastes good."
                }

                completely_dried_up = "${itemname(_1)} has completely dried up."
                dried_up = "${itemname(_1)} has dried up."
            }
        }

        dip {
            rots = "${itemname(_1)} rots."
            unchanged = "${itemname(_1)} remains unchanged."
            rusts = "${itemname(_1)} rusts."
        }

        plant {
            cannot_plant_it_here = "You can't plant it here."
            in_field = "You plant ${itemname(_1, 1)}."
            execute = "You plant ${itemname(_1, 1)}."
            new_plant_grows = "A new plant grows!"
            harvest = "You harvest ${itemname(_1, 1)}."
        }

        ally_joins {
            party_full = "Your party is already full. You can't invite someone anymore."
            success = "${basename(_1)} join${s(_1)} your party!"
        }

        offer {
            do_not_believe = "You don't believe in God."
            execute = "You put ${itemname(_1)} on the altar and mutter the name of ${_2}."
            claim = "${_1} claims the empty altar."
            take_over {
                attempt = "Strange fogs surround all over the place. You see shadows of ${_1} and ${_2} make a fierce dance."
                shadow = "The shadow of your god slowly gets bolder."
                succeed = "${_1} takes over the altar."
                fail = "${_1} keeps the altar."
            }
            result {
                best = "${itemname(_1)} shine${s(_1)} all aruond and dissappear${s(_1)}."
                good = "${itemname(_1)} for a moment and disappear${s(_1)}. A three-leaved falls from the altar."
                okay = "${itemname(_1)} shine${s(_1)} for a moment and disappear${s(_1)}."
                poor = "${itemname(_1)} disappear${s(_1)}."
            }
        }

        shortcut {
            unassigned = "The key is unassigned."
            cannot_use_anymore = "You can't use this shortcut any more."
            cannot_use_spell_anymore = "You can't use that spell anymore."
        }

        equip {
            two_handed {
                fits_well = "${itemname(_1)} fits well for two-hand fighting style."
                too_light = "${itemname(_1)} is too light for two-hand fighting style."
                too_heavy = "${itemname(_1)} is too heavy for two-wield fighting style."
                too_heavy_other_hand = "${itemname(_1)} is too heavy for two-wield fighting style."
                too_heavy_when_riding = "${itemname(_1)} is too heavy to use when riding."
            }
        }

        melee {
            shield_bash = "${name(_1)} bash${s(_1, true)} ${name(_2)} with ${his(_1)} shield."
        }

        gatcha {
            prompt = "Pay ${_1} to gasha-gasha?"
            do_not_have = "You don't have ${_1}."
        }

        angband {
            q = "What..."
            y = "No...no..."
            at = "Ahhhhh!!"
        }

        npc {
            is_busy_now = "${name(_1)} ${is(_1)} busy now."
            sand_bag {
                _0 = "\"Release me now.\""
                _1 = "\"I won't forget this.\""
                _2 = "\"Hit me!\""
            }
            leash {
                dialog {
                    _0 = "\"Ouch!\""
                    _1 = "\"Stop it!\""
                }
                untangle = "${name(_1)} untangle${s(_1)} the leash."
            }
            arena {
                _0 = "\"Come on!\""
                _1 = "\"More blood!\""
                _2 = "\"Beat'em!\""
                _3 = "\"Use your brain!\""
                _4 = "\"Wooooo!\""
                _5 = "\"Go go!\""
                _6 = "\"Good fighting.\""
                _7 = "\"Yeeee!\""
            }
            drunk {
                gets_the_worse = "${name(_1)} gets the worse for drink and catches ${name(_2)}."
                dialog {
                    _0 = "\"Have a drink baby.\""
                    _1 = "\"What are you looking at?\""
                    _2 = "\"I ain't drunk.\""
                    _3 = "\"Let's have fun.\""
                }
                annoyed {
                    text = "${name(_1)} is pretty annoyed with the drunkard."
                    dialog = "\"Your time is over, drunk!\""
                }
            }
        }
    }
}
