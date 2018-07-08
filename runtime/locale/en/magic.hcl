locale {
    magic {
        common {
            too_exhausted = "You are too exhausted!"
            it_is_cursed = "It's cursed!"
            resists = "${name(_1)} resist${s(_1)}."
            melts_alien_children = "${name(_1)}${his_owned(_1)} alien children melt in ${his(_1)} stomach."
            cursed = "${name(_1)} hear${s(_1)} devils laugh."
        }

        # By convention, if the magic text contains both the name of the target and caster, the
        # caster will be argument _1, and the target will be argument _2.

        slow = "${name(_1)}${his_owned(_1)} aging process slows down."
        speed = "${name(_1)}${his_owned(_1)} aging process speeds up."

        bolt {
            ally = "The bolt hits ${name(_1)}."
            other = "The bolt hits ${name(_1)} and"
        }

        explosion {
            # JP uses different words (爆発 and 誘爆) for explosions that were started originally or
            # as part of a chain. The text is the same in EN, however.
            begins = "${name(_1)} explode${s(_1)}."
            chain = "${name(_1)} explode${s(_1)}."
            ally = "The explosion hits ${name(_1)}."
            other = "The explosion hits ${name(_1)} and"
        }

        ball {
            ally = "The Ball hits ${name(_1)}."
            other = "The ball hits ${name(_1)} and"
        }

        arrow {
            ally = "The arrow hits ${name(_1)}."
            other = "The arrow hits ${name(_1)} and"
        }

        healed {
            slightly = "${name(_1)} ${is(_1)} slightly healed."
            normal = "${name(_1)} ${is(_1)} healed."
            greatly = "${name(_1)} ${is(_1)} greatly healed."
            completely = "${name(_1)} ${is(_1)} completely healed."
        }

        rain_of_sanity = "${name(_1)} ${is(_1)} completely sane again."

        special_attack {
            self = "${name(_1)} cast ${_2}."
            other = "${name(_1)} ${_2}."
        }

        sucks_blood {
            ally = "${name(_1)} suck${s(_1)} ${name(_2)}${his_owned(_2)} blood."
            other = "${name(_1)} suck${s(_1)} ${name(_2)}${his_owned(_2)} blood and"
        }

        disassembly = "\"Delete.\""

        touch {
            ally = "${name(_1)} touch${s(_1, true)} ${name(_2)} with ${his(_1)} ${_3} ${_4}."
            other = "${name(_1)} touch${s(_1, true)} ${name(_2)} with ${his(_1)} ${_3} ${_4} and"
        }

        hunger = "Suddenly ${name(_1)} feel${s(_1)} hungry."
        weaken = "${name(_1)} ${is(_1)} weakened."

        summon = "Several monsters come out from a portal."

        teleport {
            prevented = "Magical field prevents teleportation."
            suspicious_hand {
                succeeded = "${name(_1)} steal${s(_1)} ${_3} gold pieces from ${name(_2)}."
                prevented = "${name(_1)} guard${s(_1)} ${his(_1)} wallet from a thief."
                after = "A thief escapes laughing."
            }
            shadow_step = "${name(_1)} teleport${s(_1)} toward ${basename(_2)}."
            draw_shadow = "${name(_1)} ${is(_1)} drawn."
            disappears = "Suddenly, ${name(_1)} disappear${s(_1)}."
        }

        breath {
            no_element = "breath"
            named = "${_1} breath"
            bellows = "${name(_1)} bellow${s(_1)} ${_2} from ${his(_1)} mouth."
            ally = "The breath hits ${_1}."
            other = "The breath hits ${_1} and"
        }

        insanity {
            _0 = "${name(_2)} see${s(_2)} maggots breed in the rent stomach of ${name(_1)}."
            _1 = "${name(_2)} see${s(_2)} ${name(_1)} chow${s(_1)} dead bodies."
            _2 = "${name(_2)} shudders${s(_2)} at ${name(_1)}${his_owned(_1)} terrifying eyes."
            _3 = "${name(_2)} feel${s(_2)} sick at entrails caught in ${name(_1)}${his_owned(_1)} tentacles."
        }

        map {
            need_global_map = "You need to read it while you are in the global map."
            cursed = "The cursed map crumbles as you touch."
            apply = "There's a mark on the map..."
            mark = "O"
        }

        love_potion {
            cursed = "This love potion is cursed. ${name(_1)} look${s(_1)} at ${you()} with a contemptuous glance."
            spill = "${name(_1)} sense${s(_1)} a sign of love,"
            self = "You are excited!"
            other = "${name(_1)} give${s(_1)} ${you()} the eye."
        }

        pregnant = "${name(_1)} put${s(_1)} something into ${name(_2)}${his_owned(_2)} body!"

        mirror = "You examine yourself."

        milk {
            cursed {
                self = "Geee it's cursed! The taste is very dangerous."
                other = "\"Argh, the milk is cursed!\""
            }
            self = "The taste is very thick, almost addictive."
            other = "\"Yummy!\""
        }

        alcohol {
            cursed {
                _0 = "*Hic*"
                _1 = "\"Ah, bad booze.\""
                _2 = "\"Ugh...\""
                _3 = "\"Bah, smells like rotten milk.\""
            }
            normal {
                _0 = "*Hic*"
                _1 = "\"Ah, good booze.\""
                _2 = "\"La-la-la-la.\""
                _3 = "\"I'm going to heaven.\""
                _4 = "\"Whew!\""
                _5 = "\"I'm revived!\""
                _6 = "\"Awesome.\""
            }
        }

        acid {
            self = "Arrrrg!"
            apply = "The sulfuric acid melts ${name(_1)}."
        }

        water {
            self = "*quaff* The water is refreshing."
            other = "*quaff*"
        }

        restore_stamina {
            dialog = "*quaff* Juicy!"
            apply = "${name(_1)} restore${s(_1)} some stamina."
        }

        restore_stamina_greater {
            dialog = "*quaff*"
            apply = "${name(_1)} greatly restore${s(_1)} stamina."
        }

        salt {
            snail = "It's salt! ${name(_1)} start${s(_1)} to melt."
            apply = "\"Salty!\""
        }

        dirty_water {
            self = "*quaff* Yucky!"
            other = "*quaff*"
        }

        steal {
            in_quest = "You have no time for it!"
        }

        mount {
            no_place_to_get_off = "There's no place to get off."

            dismount = "You dismount from ${name(_1)}."
            dismount_dialog {
                _0 = "\"Phew.\""
                _1 = "\"How was my ride?\""
                _2 = "\"Tired...tired...\""
                _3 = "\"It was nice.\""
            }

            only_ally = "You can only ride an ally."
            not_client = "You can't ride a client."
            ride_self = "You try to ride yourself."
            stays_in_area = "The ally currently stays in this area."
            currently_riding = "${name(_1)} ${is(_1)} currently riding ${name(_2)}."

            mount {
                execute = "You ride ${name(_1)}. (${name(_1)}'s speed: ${_2}->"
                suitable = "You feel comfortable."
                unsuitable = "This creature is too weak to carry you."
                dialog {
                    _0 = "\"Awww.\""
                    _1 = "\"You should go on a diet.\""
                    _2 = "\"Let's roll!\""
                    _3 = "\"Be gentle.\""
                }
            }
        }

        perform {
            do_not_know = "${name(_1)} ${does(_1)}n't know how to play an instrument."
        }

        cook {
            do_not_know = "You don't know how to cook."
        }

        fish {
            do_not_know = "You don't know how to fish."
            need_bait = "You need a bait to fish."
            not_good_place = "This isn't a good place to fish."
            cannot_during_swim = "You can't fish while swimming."
        }

        prayer = "A golden aura wraps ${name(_1)}!"

        create_material {
            materials = "materials"
            junks = "junks"
            apply = "Some ${_1} fall from above!"
        }

        mutation {
            spell = "${name(_1)} cast${s(_1)} an insane glance on ${name(_2)}."
            resist = "You resist the threat of mutation."
            apply = "You mutate."
        }

        cure_mutation = "You are now one step closer to yourself."

        resurrection {
            cursed = "Hoards of undead raise from the hell!"
            fail = "${name(_1)}${his_owned(_1)} prayer doesn't reach the underworld."
            apply = "${_1} ${have(_2)} been resurrected!"
            dialog = "\"Thanks!\""
        }

        uncurse {
            apply = "${name(_1)} ${his_owned(_1)} equipment are surrounded by a white aura."
            blessed = "${name(_1)} ${is(_1)} surrounded by a holy aura."
            item = "The aura uncurses some ${his(_1)} stuff."
            equipment = "The aura uncurses some of ${his(_1)} equipment."
            resist = "Several items resist the aura and remain cursed."
        }

        oracle {
            cursed = "You hear a sepulchral whisper but the voice is too small to distinguish a word."
            no_artifacts = "No artifacts have been generated yet."

            was_held_by = "${_1} was held by ${basename(_2)} at ${_3} in ${_4}/${_5}, ${_6}. "
            was_created_at = "${_1} was created at ${_2} in ${_3}/${_4}, ${_5}. "
        }

        gain_knowledge {
            suddenly = "Suddenly, "
            furthermore = "Furthermore, "
            gain = "you gain knowledge of a spell, ${_1}."
            lose = "Suddenly, you lose knowledge of a spell, ${_1}."
        }

        descent = "${name(_1)} lose${s(_1)} a level..."
        gain_skill = "${name(_1)} gain${s(_1)} a skill of ${_2}!"

        faith {
            doubt = "Your god doubts your faith."
            apply = "You feel as if ${_1} is watching you."
            blessed = "A three-leaved falls from the sky."
        }

        gain_skill_potential {
            the = "The "
            furthermore_the = "Furthermore, the "
            increases = "potential of ${name(_1)}${his_owned(_1)} ${_2} skill increases."
            decreases = "The potential of ${name(_1)}${his_owned(_1)} ${_2} skill decreases."
        }

        troll_blood {
            apply = "${name(_1)}${his_owned(_1)} blood burns and a new strength fills ${his(_1)} body!"
            blessed = "It really burns!"
        }

        gain_potential {
            blessed = "${name(_1)}${his_owned(_1)} potential of every attribute expands."
            increases = "${name(_1)}${his_owned(_1)} potential of ${_2} expands."
            decreases = "${name(_1)}${his_owned(_1)} potential of ${_2} decreases."
        }

        vanish = "${name(_1)} vanish${s(_1, true)}."

        sense {
            cursed = "Hmm? You suffer minor memory defect."
            magic_mapping = "${name(_1)} sense${s(_1)} nearby locations."
            sense_object = "${name(_1)} sense${s(_1)} nearby objects."
        }

        vorpal {
            sound = "*Gash*"
            ally = "${name(_1)} cut${s(_1)} ${name(_2)}${his_owned(_2)} head."
            other = "${name(_1)} cut${s(_1)} ${name(_2)}${his_owned(_2)} head and"
        }

        restore {
            body {
                apply = "${name(_1)}${his_owned(_1)} body is restored."
                cursed = "${name(_1)}${his_owned(_1)} body is damaged."
                blessed = "In addition, ${his(_1)} body is enchanted."
            }
            mind {
                apply = "${name(_1)}${his_owned(_1)} spirit is restored."
                cursed = "${name(_1)}${his_owned(_1)} spirit is damaged."
                blessed = "In addition, ${his(_1)} spirit is enchanted."
            }
        }

        escape {
            cancel = "The air around you gradually loses power."
            during_quest = "Returning while taking a quest if forbidden. Are you sure you want to return?"
            begin = "The air around you becomes charged."
            lord_may_disappear = "The lord of the dungeon might disappear if you escape now."
        }

        return {
            cancel = "The air around you gradually loses power."

            prevented {
                normal = "Strange power prevents you from returning."
                ally = "One of your allies prevents you from returning."
                overweight = "Someone shouts, \"Sorry, overweight.\""
            }

            you_commit_a_crime = "You commit a crime."
            door_opens = "A dimensional door opens in front of you."
            destination_changed = "The capricious controller of time has changed your destination!"
        }

        harvest_mana = "${name(_1)}${his_owned(_1)} mana is restored."
        absorb_magic = "${name(_1)} absorb${s(_1)} mana from the air."
        poison_attack = "${name(_1)} ${is(_1)} hit by poison!"
        ink_attack = "Ink squirts into ${name(_1)}${his_owned(_1)} face!"
        confusion = "A foul stench floods ${name(_1)}${his_owned(_1)} nostrils!"
        paralysis = "${name(_1)} get${s(_1)} numbness!"
        sleep = "Strange sweet liquid splashes onto ${name(_1)}!"

        curse {
            spell = "${name(_1)} point${s(_1)} ${name(_2)} and mutter${s(_1)} a curse."
            no_effect = "Your prayer nullifies the curse."
            apply = "${name(_1)}${his_owned(_1)} ${_2} glows black."
        }

        weaken_resistance {
            nothing_happens = "Nothing happens."
        }

        diary {
            cat_sister = "How...! You suddenly get a younger cat sister!"
            younger_sister = "How...! You suddenly get a younger sister!"
            young_lady = "A young lady falls from the sky."
        }

        domination {
            does_not_work_in_area = "The effect doesn't work in this area."
            cannot_be_charmed = "${name(_1)} cannot be charmed."
        }

        map_effect {
            web = "The ground is covered with thick webbing."
            fog = "The air is wrapped in a dense fog."
            acid = "Acid puddles are generated."
            fire = "Walls of fire come out from the ground."
            ether_mist = "Ether mist spreads."
        }

        name {
            prompt = "What do you want to name this artifact?"
            apply = "It's now called ${_1}."
        }

        garoks_hammer {
            no_effect = "This item leaves no room for improvement."
            apply = "It becomes ${itemname(_1, 1)}."
        }

        change_material {
            more_power_needed = "More magic power is needed to reconstruct an artifact."
            artifact_reconstructed = "${name(_1)}${his_owned(_1)} ${itemname(_2, 1, false)} is reconstructed."
            apply = "${name(_1)}${his_owned(_1)} ${_2} transforms into ${itemname(_3, 1)}."
        }

        deed_of_inheritance {
            claim = "You claim the right of succession. (+${_1})"
            can_now_inherit = "You can now inherit ${_1} items."
        }

        enchant {
            apply = "${itemname(_1)} ${is(_1)} surrounded by a golden aura."
            resist = "${itemname(_1)} resist${s(_1)}."
        }

        fill_charge {
            more_power_needed = "You need at least 10 recharge powers to recharge items."
            spend = "You spend 10 recharge powers. (Total:${_1})"
            cannot_recharge = "You can't recharge this item."
            cannot_recharge_anymore = "${itemname(_1)} cannot be recharged anymore."
            apply = "${itemname(_1)} ${is(_1)} recharged by ${_2}."
            fail = "You fail to recharge ${itemname(_1)}."
            explodes = "${itemname(_1)} explode${s(_1)}."
        }

        draw_charge = "You destroy ${itemname(_1)} and extract ${_2} recharge powers. (Total:${_3})"

        change {
            apply = "${name(_1)} change${s(_1)}."
            cannot_be_changed = "${name(_1)} cannot be changed."
        }

        flying {
            apply = "${itemname(_1, 1)} becomes light as a feather."
            cursed = "${itemname(_1, 1)} becomes heavy."
        }

        alchemy = "It is metamorphosed into ${itemname(_1, 1)}."

        create {
            wall = "A wall appears."
            door {
                resist = "These walls seem to resist your magic."
                apply = "A door appears."
            }
        }

        swarm = "Swarm!"
        drop_mine = "${name(_1)} drop${s(_1)} something on the ground."
        gravity = "${name(_1)} feel${s(_1)} gravity."
        mewmewmew = "Mewmewmew!"
        meteor = "Innumerable meteorites fall all over the area!"

        cheer {
            apply = "${name(_1)} cheer${s(_1)}."
            is_excited = "${name(_1)} ${is(_1)} excited!"
        }

        cure_corruption {
            apply = "Your Ether Disease is cured greatly."
            cursed = " The Ether Disease spreads around your body."
        }

        eye_of_ether = "${name(_1)} gazes at you. Your Ether Disease deteriorates."

        insult {
            apply = "${name(_1)} insult${s(_1)} ${name(_2)}."
        }

        gaze = "${name(_1)} gaze${s(_1)} at ${name(_2)}."
        molotov = "${name(_1)} ${is(_1)} surrounded by flames."

        scavenge {
            apply = "${name(_1)} loot${s(_1)} ${name(_2)}${his_owned(_2)} backpack."
            rotten = "${name(_1)} notice${s(_1)} unusual odor from ${itemname(_2, 1)} and step${s(_1)} back."
            eats = "${name(_1)} eat${s(_1)} ${itemname(_2, 1)}!"
        }

        wizards_harvest = "${itemname(_1)} fall${s(_1)} down!"
        four_dimensional_pocket = "You summon 4 dimensional pocket."
    }
}
