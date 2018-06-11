locale {
    damage {
        miss {
            # target evades attacker
            ally = "${name(_2)} evade${s(_2)} ${name(_1)}."
            # attacker misses target
            other = "${name(_1)} miss${s(_1, true)} ${name(_2)}."
        }
        evade {
            # target evades attacker
            ally = "${name(_2)} skillfully evade${s(_2)} ${name(_1)}."
            # target evades attacker
            other = "${name(_2)} skillfully evade${s(_2)} ${name(_1)}."
        }
        furthermore = "Futhermore,"

        is_frightened = "${name(_1)} ${is(_1)} frightened."
        critical_hit = "Critical Hit!"

        wields_proudly = "${name(_1)} wield${s(_1)} ${_2} proudly."

        is_healed = "${name(_1)} ${is(_1)} healed."
        lay_hand = "${name(_1)} shout${s(_1)}, \"Lay hand!\""

        runs_away_in_terror = "${name(_1)} run${s(_1)} away in terror."
        sleep_is_disturbed = "${name(_1)}${r(_1)} sleep ${is(_1)} disturbed"

        explode_click = "*click*"
        splits = "${name(_1)} split${s(_1)}!"
        is_engulfed_in_fury = "${name(_1)} ${is(_1)} engulfed in fury!"

        you_feel_sad = "You feel sad for a moment."
        get_off_corpse = "${you()} get off the corpse of ${name(_1)}."
        death_word_breaks = "The death word breaks."

        magic_reaction_hurts = "Magic reaction hurts ${name(_1)}!"

        weapon {
            # <attacker> <verb>s something with his <weapon>.
            attacks_with = "${name(_1)} ${_2}${s(_1)} ${name(_3)} with ${his(_1)} ${_4}."

            # <attacker> <verb>s something and <...>
            attacks_and = "${name(_1)} ${_2}${s(_1)} ${name(_3)} ${_4}"

            attacks_unarmed = "${name(_1)} ${_2}${s(_1)} ${name(_3)}."
            attacks_unarmed_and = "${name(_1)} ${_2}${s(_1)} ${name(_3)} ${_4}"

            and = "and"

            # _106 is for unarmed. It is a special case since unarmed
            # attacks can each have a unique name.

            # "verb_and" is always the same as "verb" here. It is
            # different in Japanese.
            _108 {
                name = "bow"
                verb_and = "shoot"
                verb = "shoot"
            }
            _109 {
                name = "crossbow"
                verb_and = "shoot"
                verb = "shoot"
            }
            _110 {
                name = "gun"
                verb_and = "shoot"
                verb = "shoot"
            }
            _100 {
                name = "sword"
                verb_and = "slash"
                verb = "slash"
            }
            _104 {
                name = "spear"
                verb_and = "stab"
                verb = "stab"
            }
            _101 {
                name = "dagger"
                verb_and = "stab"
                verb = "stab"
            }
            _105 {
                name = "staff"
                verb_and = "smash"
                verb = "smash"
            }
            _103 {
                name = "mace"
                verb_and = "smash"
                verb = "smash"
            }
            _102 {
                name = "axe"
                verb_and = "slash"
                verb = "slash"
            }
            _107 {
                name = "scythe"
                verb_and = "slash"
                verb = "slash"
            }
            _111 {
                # name is automatically set based on thrown item name
                verb_and = "shoot"
                verb = "shoot"
            }
        }

        reactive_attack {
            thorns = "${name(_1)} ${is(_1)} stuck by several thorns."
            ether_thorns = "${name(_1)} ${is(_1)} stuck by several ether thorns."
            acids = "Acids spread over the ground."
        }

        levels {
            scratch = "make${s(_2)} a scratch."
            slightly = "slightly wound${s(_2)} ${him(_1)}."
            moderately = "moderately wound${s(_2)} ${him(_1)}."
            severely = "severely wound${s(_2)} ${him(_1)}."
            critically = "critically wound${s(_2)} ${him(_1)}!"
        }

        reactions {
            screams = "${name(_1)} scream${s(_1)}."
            writhes_in_pain = "${name(_1)} writhe${s(_1)} in pain."
            is_severely_hurt = "${name(_1)} ${is(_1)} severely hurt!"
        }

        element {
            default = "${name(_1)} ${is(_1)} wounded."
            _50 = "${name(_1)} ${is(_1)} burnt."
            _51 = "${name(_1)} ${is(_1)} frozen."
            _52 = "${name(_1)} ${is(_1)} shocked."
            _53 = "${name(_1)} ${is(_1)} struck by dark force."
            _54 = "${name(_1)} suffer${s(_1)} a splitting headache."
            _55 = "${name(_1)} suffer${s(_1)} from venom."
            _56 = "${name(_1)} ${is(_1)} chilled by infernal squall."
            _57 = "${name(_1)} ${is(_1)} shocked by a shrill sound."
            _58 = "${name(_1)}${r(_1)} nerves are hurt."
            _59 = "${name(_1)} ${is(_1)} hurt by chaotic force."
            # _60
            _61 = "${name(_1)} get${s(_1)} a cut."
            # _62
            _63 = "${name(_1)} ${is(_1)} burnt by acid."
        }

        sand_bag {
            _0 = "\"Kill me already!\""
            _1 = "\"No..not yet...!\""
            _2 = "\"I can't take it anymore...\""
            _3 = "\"Argh!\""
            _4 = "\"Uhhh\""
            _5 = "\"Ugggg\""
        }
    }
}
