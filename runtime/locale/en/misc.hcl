# TODO
# These text are unclassed. They should be moved to appropriate files.

locale {
    misc {
        ranking {
            changed = "Ranking Change (${_1} ${_2} -> ${_3}) <${_4}>"
            closer_to_next_rank = "You are one step closer to the next rank."
        }

        sound {
            waken = "${name(_1)} notice${_s(_1)} the sound and wake${_s(_1)} up."
            get_anger = "${name(_1)} can no longer put up with it."
            can_no_longer_stand = "\"That's it.\""
        }

        hostile_action {
            glares_at_you = "${name(_1)} glares at you."
            gets_furious = "${name(_1)} gets furious!"
            get_excited = "Animals get excited!"
        }

        wet {
            gets_wet = "${name(_1)} get${s(_1)} wet."
            is_revealed = "${name(_1)} ${is(_1)} revealed ${his(_1)} shape."
        }

        fail_to_cast {
            mana_is_absorbed = "${name(_1)his_owned(_1)} mana is absorbed."
            is_confused_more = "${name(_1)} ${is(_1)} confused more."
            too_difficult = "It's too difficult!"
            dimension_door_opens = "A dimension door opens in front of ${name(_1)}."
            creatures_are_summoned = "Several creatures are summoned from a vortex of magic."
        }

        status_ailment {
            choked = "\"Ughh...!\""
            breaks_away_from_gravity = "${name(_1)} break${s(_1)} away from gravity."
            calms_down = "${name(_1)} calm${s(_1)} down."
            sleepy = "You need to sleep."
            insane = [
                "${name(_1)} start${s(_1)} to take ${his(_1)} cloths off.",
                "${name(_1)} shout${s(_1)}.",
                "${name(_1)} dance${s(_1)}.",
                "\"Weeeeeee!\"",
                "\"Forgive me! Forgive me!\"",
                "\"P-P-Pika!\"",
                "\"Shhhhhh!\"",
                "\"So I have to kill.\"",
                "\"You snail!\"",
            ]
        }

        death {
            good_bye = "Good bye... "
            you_leave_dying_message = "You leave a dying message."
            dying_message = "\"${_1}\""
            date = "${_1}/${_2}/${_3}"
            you_died = "${capitalize(_1)} in ${_2}."
            rank = "{ordinal(_1)}"
            you_are_about_to_be_buried = "You are about to be buried..."
            crawl_up = "Crawl up"
            lie_on_your_back = "Lie on your back"
            you_have_been_buried = "You have been buried. Bye...(Hit any key to exit)"
            sent_message = "${_1} ${_2} ${_3} in ${_4} ${5}"
        }

        score {
            rank = "${ordinal(_1)}"
            score = "${_1}"
        }

        resurrect = "${capitalize(_1)} ${have(_2)} been resurrected!"
        artifact_regeneration = "${_1} turns its shape into ${itemname(_2)}."
        black_cat_licks = "${name(_1)} licks ${itemname(_2)}."
        corpse_is_dried_up = "${itemname(_1)} ${is(_1)} dried up in the sun."
        get_rotten = "${itemname(_1)} rot${s(_1)}."
        extract_seed = "You extract plant seeds from ${itemname(_1)}."

        curse {
            gold_stolen = "A malicious hand filches some gold pieces from ${name(_1)}${his_owned(_1)} wallet."
            blood_sucked = "Something sucks ${name(_1)}${his_owned(_1)} blood."
            experience_reduced = "${name(_1)} become${s(_1)} inexperienced."
            creature_summoned = "Several creatures are summoned from a vortex of magic."
        }

        identify {
            fully_identified = "You appraise ${_1} as ${itemname(_2)}."
            almost_identified = "You sense the quality of ${itemname(_1)} is ${_2}."
        }

        love_miracle {
            uh = "\"Uh...!\""
        }

        pregnant {
            pukes_out = "But ${he(_1)} puke${s(_1)} it out quickly."
            gets_pregnant = "${name(_1)} get${s(_1)} pregnant."

            pats_stomach = "${name(_1)} pat${s(_1)} ${his(_1)} stomach uneasily."
            something_is_wrong = [
                "\"I'm going to have a baby!\"",
                "\"Something is wrong with my stomach...\"",
            ]
            something_breaks_out = "Something splits ${name(_1)}${his_owned(_1)} body and breaks out!"
        }

        walk_down_stairs = "You walk down the stairs. "
        walk_up_stairs = "You walk up the stairs. "

        quest {
            kamikaze_attack {
                messange = "The messenger \"The retreat of our army is over now. You don't need to fight them any more. Please leave at once!\""
                stairs_appear = "Suddenly, stairs appear."
            }
        }

        map {
            jail {
                repent_of_sin = "You repent of your sin."
                guard_approaches = "You hear footsteps coming towards your cell."
                leave_here = "\"Hey punk, our boss says you can leave the jail now. Do not come back, okay?\""
                unlocks_your_cell = "A guard unenthusiastically unlocks your cell."
            }

            shelter {
                eat_stored_food = "You eat stored food."
                no_longer_need_to_stay = "You don't need to stay in the shelter any longer."
            }

            museum {
                chats = [
                    "*noise*",
                    "\"Hmm. Not bad.\"",
                    "\"What's this?\"",
                    "\"Ohh...\"",
                    "\"I want to be stuffed...\"",
                    "\"So this is the famous...\"",
                ]
                chats2 = [
                    "*murmur*",
                    "\"Gross! Disgusting.\"",
                    "\"Hey. Is it really dead?\"",
                    "\"Scut!\"",
                    "\"Absolutely amazing.\"",
                    "\"Can I touch?\"",
                ]
            }

            shop {
                chats = [
                    "*murmur*",
                    "\"I want this! I want this!\"",
                    "\"Oh what's this?\"",
                    "\"I'm just watching\"",
                    "\"My wallet is empty...\"",
                    "\"So this is the famous....\"",
                ]
            }
        }

        custom {
            key_hint = "BackSpace [Delete]  "
            show_room {
                which_show_room = "Which room do you want to visit? "
                list = "Room List"
                name = "Name"
            }
            pet_team {
                which_team = "Which team do you want to play a match? "
                list = "Team List"
                name = "Name"
            }

            incompatible = "Selected item is incompatible."
            fail_to_retrieve_file = "Failed to retrieve designated files."
            do_you_want_to_delete = "Do you really want to delete ${_1}? "
        }

        no_target_around = "You look around and find nothing."

        return {
            forbidden = "Returning while taking a quest if forbidden. Are you sure you want to return?"
            no_location = "You don't know any location you can return to"
            where_do_you_want_to_go = "Where do you want to go?"
            air_becomes_charged = "The air around you becomes charged."
            lord_of_dungeon_might_disappear = "The lord of the dungeon might disappear if you escape now."
        }

        dungeon_level = " Lv"

        save {
            update = "Updating your save data from Ver.${_1} now."
            need_to_save_in_town = "To update your game, please save your game in a town in the previous version then retry."
            take_a_while = "The next updating process may take a while to complete."
            cannot_save_in_user_map = "The game is not saved in a user map."
        }

        living_weapon_taste_blood = "${itemname(_1)} has tasted enough blood!"
        caught_by_assassins = "You are caught by assassins. You have to protect your client."
        finished_eating = "${name(_1)} ${have(_1)} finished eating ${itemname(_2, 1)}."
        spell_passes_through = "The spell passes through ${name(_1)}."
        shakes_head = "${name(_1)} shake${s(_1)} ${his(_1)} head."

        wields_proudly {
            the = "The "
        }

        and = " and "

        income {
            sent_to_your_house = "As a salary, ${_1} gold piece${s(_1)} have been sent to your house."
            sent_to_your_house2 = "As a salary, ${_1} gold piece${s(_1)} and ${_2} item${s(_2)} have been sent to your house."
        }

        tax {
            bill = "A bill has been sent to your house."
            no_duty = "You don't have to pay tax until you hit level 6."
            caution = "Caution! "
            warning = "Warning!! "
            have_to_go_embassy = "You have to go to the Embassy of Palmia and pay tax at once. "
            left_bills = "You are in arrears with your tax for ${_1} month${s(_1)}."
            accused = "You have been accused for being in arrears with your tax for${_1} months."
            lose_fame = "You lose ${_1} fame."
        }
    }
}
