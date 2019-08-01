locale {
    action {
        cannot_do_in_global = "You can't do that while you're in a global area."
        hit_key_for_help = "Hit ? key to display help."
        really_attack = "Really attack ${name(_1)}?"
        someone_else_is_using = "Someone else is using the item."

        backpack_squashing = "Your backpack is squashing you!"

        day_breaks = "Day breaks."
        new_day = "A day passes and a new day begins."

        playtime_report = "You have been playing Elona for ${_1} hour${s(_1)}."

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
            ask = "Which direction?"
            spell = "Which direction do you want to cast the spell? "
            wand = "Which direction do you want to zap the wand? "
            door = "Which door do you want to close? "
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
                title = "Tone of Voice"
                hint = "Enter [Change Tone] "
                tone_title = "Title"
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
            drunk = "*stagger*"
            confused = "*bump*"
            interrupt = "${name(_1)} stares in your face."
            carry_too_much = "You carry too much to move!"
            displace {
                text = "You displace ${name(_1)}."
                dialog = [
                    "\"Oops, sorry.\"",
                    "\"Watch it.\""
                ]
            }

            leave {
                prompt = "Do you want to leave ${_1}? "
                abandoning_quest = "Warning! You are going to abandon your current quest."
            }

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
                        # TODO They always use "a" even if "${_1}" begins with a vowel.
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
                        message = [
                            "Snow delays your travel.",
                            "You are caught in a snowdrift.",
                            "It's hard to walk on a snowy road."
                        ]
                        sound = [
                            " *kisssh*",
                            "*thudd*",
                            "*siz*",
                            "*clump*",
                            "*skritch*"
                        ]
                        eat = "You are too hungry. You chow down snow."
                    }

                    heavy_rain {
                        message = [
                            "It's raining heavily. You lose your way.",
                            "You can't see a thing!"
                        ]
                        sound = [
                            "*drip*",
                            "*sip*",
                            "*drizzle*",
                            "*splash*",
                            "*kissh*"
                        ]
                    }
                }

                ambush {
                    text = "Ambush!"
                    distance_from_nearest_town = "Distance from nearest town:${_1}" # NOTE
                    enemy_strength = "Enemy strength:"

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
            target = "You target ${name(_1)}."
            target_ground = "You target the ground."
        }

        ranged {
            load_normal_ammo = "You load normal ammo."
            no_target = "You find no target."

            equip {
                need_weapon = "You need to equip a firing weapon."
                need_ammo = "You need to equip ammos or arrows."
                wrong_ammo = "You're equipped with wrong type of ammos."
            }
        }

        get {
            plant {
                dead = "You nip a dead plant."
                young = "You nip a young plant."
            }

            building {
                prompt = "Really remove this building?"
                remove = "You remove the building."
            }

            snow = "You rake up a handful of snow."
            air = "You grasp at the air."

            cannot_carry = "You can't carry it."

            not_owned = [
                "It's not your property.",
                "You can't just take it.",
                "It's not yours."
            ]
        }

        ammo {
            need_to_equip = "You need to equip an ammo."
            is_not_capable = "${itemname(_1)} isn't capable of changing ammos."

            current = "Current Ammo Type"
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
            shackle {
                text = "You unlock the shackle."
                dialog = "Moyer yells, \"You idiot!\""
            }

            only_in_home = "You can only use it at your home."
            only_in_shop = "You can only use it at your shop"
            empty = "It's empty!"
        }

        use_stairs {
            cannot_during_debug = "You can't perform the action while in the debug mode."
            kotatsu {
                prompt = "Really get into the Kotatsu?"
                use = "It's dark here!"
            }
            cannot_go {
                down = "You can't go down any more."
                up = "You can't go up any more."
            }
            no {
                downstairs = "There're no downstairs here."
                upstairs = "There're no upstairs here."
            }
            blocked_by_barrier = "The path is blocked by a strange barrier."

            unlock {
                normal = "You unlock the door"
                stones = "The magic stones shine softly as you approach the sealed door."
            }

            locked = "The door is locked. It seems you need a specific key to unlock the door."

            prompt_give_up_quest = "Really give up the quest and move over?"
            prompt_give_up_game = "Do you want to give up the game?"

            lost_balance = "Noooo! You lost your step and roll down!"
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

                dialog = [
                    "\"Hey!\"",
                    "\"Now you did it.\"",
                    "*chuckle*",
                    "\"Tee-hee-hee!\"",
                    "\"You'll pay for this.\"",
                    "*grin*"
                ]
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
            }
            scroll {
                dimmed_or_confused = "${name(_1)} stagger${s(_1)}."
                execute = "${name(_1)} read${s(_1)} ${itemname(_2, 1)}."
            }
            recipe {
                info = "You can add a recipe of the item you previously created.(Not implemented yet)"
                learned = "You learned the recipe!"
            }
        }

        eat {
            snatches = "${name(_1)} snatch${s(_1)} ${name(_2)}${his_owned(_2)} food."
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
            execute = "You dip ${itemname(_1)} into ${itemname(_2, 1)}."
            you_get = "You get ${itemname(_1, 1)}."

            rots = "${itemname(_1)} rots."
            unchanged = "${itemname(_1)} remains unchanged."
            rusts = "${itemname(_1)} rusts."

            # Also shared with blending results
            result {
                love_food {
                    made = "You made aphrodisiac food! "
                    guilty = "You kind of feel guilty..."
                    grin = "You grin."
                }

                dyeing = "You dye ${itemname(_1)}."

                poisoned_food = "You grin."

                put_on = "You put ${itemname(_2, 1)} on ${itemname(_1)}."
                good_idea_but = "A good idea! But..."
                gains_fireproof = "${itemname(_1)} gain${s(_1)} fireproof."
                gains_acidproof = "${itemname(_1)} gain${s(_1)} acidproof."

                bait_attachment = "You bait ${itemname(_1)} with ${itemname(_2, 1)}."

                blessed_item = "You shower ${itemname(_1)} on ${itemname(_2, 1)}."
                becomes_blessed = "${itemname(_1)} shine${s(_1)} silvery."
                becomes_cursed = "${itemname(_1)} ${is(_1)} wrapped by a dark aura."

                well_refill = "You throw ${itemname(_1)} into ${itemname(_2, 1)}."
                empty_bottle_shatters = "You hear the sound of the empty bottle shatters."
                holy_well_polluted = "The holy well is polluted."
                well_dry = "${itemname(_1)} is completely dry."
                well_refilled = "${itemname(_1)} shines for a moment."
                snow_melts {
                    dip = "Snow just melts."
                    blending = "But the snow just melts."
                }

                natural_potion = "You draw water from the well into the empty bottle."
                natural_potion_dry = "${itemname(_1)} is dry."
                natural_potion_drop = "Oops! You drop the empty bottle into the well..."
            }
        }

        plant {
            cannot_plant_it_here = "You can't plant it here."
            on_field = "You plant ${itemname(_1, 1)} on the field."
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
            you_change = "You change your equipment."

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

        quicksave = " *Save* "

        exit {
            cannot_save_in_usermap = "You can't save the game in a user made map. Exit anyway?"
            prompt = "Do you want to save the game and exit?"

            choices {
                exit = "Exit"
                cancel = "Cancel"
                game_setting = "Game Setting"
            }

            saved = "Your game has been saved successfully."
            you_close_your_eyes = "You close your eyes and peacefully fade away. (Hit any key to exit)"
        }

        npc {
            is_busy_now = "${name(_1)} ${is(_1)} busy now."
            sand_bag = [
                "\"Release me now.\"",
                "\"I won't forget this.\"",
                "\"Hit me!\""
            ]
            leash {
                dialog = [
                    "\"Ouch!\"",
                    "\"Stop it!\""
                ]
                untangle = "${name(_1)} untangle${s(_1)} the leash."
            }
            arena = [
                "\"Come on!\"",
                "\"More blood!\"",
                "\"Beat'em!\"",
                "\"Use your brain!\"",
                "\"Wooooo!\"",
                "\"Go go!\"",
                "\"Good fighting.\"",
                "\"Yeeee!\""
            ]
            drunk {
                gets_the_worse = "${name(_1)} gets the worse for drink and catches ${name(_2)}."
                dialog = [
                    "\"Have a drink baby.\"",
                    "\"What are you looking at?\"",
                    "\"I ain't drunk.\"",
                    "\"Let's have fun.\""
                ]
                annoyed {
                    text = "${name(_1)} is pretty annoyed with the drunkard."
                    dialog = "\"Your time is over, drunk!\""
                }
            }
        }

        autopick {
            reloaded_autopick_file = "Reloaded autopick file."
        }

        take_screenshot = "You took screenshot."
    }
}
