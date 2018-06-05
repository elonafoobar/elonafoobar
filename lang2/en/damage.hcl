locale {
    damage {
        healed = "${name(_1)} ${is(_1)} healed."
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

        levels {
            scratch = "make${s(_2)} a scratch."
            slightly = "slightly wound${s(_2)} ${him(_1)}."
            moderately = "moderately wound${s(_2)} ${him(_1)}."
            severely = "severely wound${s(_2)} ${him(_1)}."
            critically = "critically wound${s(_2)} ${him(_1)}!"
        }

        reactions {
            screams = "${name(_1)} scream${s(_1)}."
            writhes = "${name(_1)} writhe${s(_1)} in pain."
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

        status_ailment {
            blinded {
                apply = "${name(_1)} ${is(_1)} blinded."
                heal = "${name(_1)} can see again."
            }
            confused {
                apply = "${name(_1)} ${is(_1)} confused."
                heal = "${name(_1)} recover${s(_1)} from confusion."
            }
            paralyzed {
                apply = "${name(_1)} ${is(_1)} paralyzed"
                heal = "${name(_1)} recover${s(_1)} from paralysis."
            }
            poisoned {
                apply = "${name(_1)} ${is(_1)} poisoned"
                heal = "${name(_1)} recover${s(_1)} from poison."
            }
            sleep {
                apply = "${name(_1)} fall${s(_1)} asleep."
                heal = "${name(_1)} awake${s(_1)} from ${his(_1)} sleep."
            }
            fear {
                apply = "${name(_1)} ${is(_1)} frightened."
                heal = "${name(_1)} shake${s(_1)} off ${his(_1)} fear."
            }
            dimmed {
                apply = "${name(_1)} ${is(_1)} dimmed."
                # heal text was originally the same as poisoned.
                heal = "${name(_1)} regain${s(_1)} ${his(_1)} senses."
            }
            bleeding {
                apply = "${name(_1)} begin${s(_1)} to bleed."
                heal = "${name(_1)}${r(_1)} bleeding stops."
            }
            drunk {
                apply = "${name(_1)} get${s(_1)} drunk."
                heal = "${name(_1)} get${s(_1)} sober."
            }
            insane {
                apply = "${name(_1)} become${s(_1)} insane."
                heal = "${name(_1)} come${s(_1)} to ${himself(_1)} again."
            }
            sick {
                apply = "${name(_1)} get${s(_1)} sick."
                heal = "${name(_1)} recover${s(_1)} from ${his(_1)} illness."
            }
        }

        death_by {
            chara {
                transformed_into_meat {
                    active = "transform${s(_2)} ${him(_1)} into several pieces of meat."
                    passive = "${name(_1)} ${is(_1)} transformed into several pieces of meat."
                }
                destroyed {
                    active = "destroy${s(_2)} ${him(_1)}"
                    passive = "${name(_1)} ${is(_1)} killed."
                }
                minced {
                    active = "mince${s(_2)} ${him(_1)}."
                    passive = "${name(_1)} ${is(_1)} minced."
                }
                killed {
                    active = "kill${s(_2)} ${him(_1)}."
                    passive = "${name(_1)} ${is(_1)} slain."
                }
                death_cause = "was killed by ${basename(_1)}"
            }
            element {
                default {
                    active = "kill${_s(_2)} ${him(_1)}."
                    passive = "${name(_1)} ${is(_1)} killed."
                }
                _50 {
                    active = "burn${s(_2)} ${him(_1)} to death."
                    passive = "${name(_1)} ${is(_1)} burnt to ashes."
                }
                _51 {
                    active = "transform${s(_2)} ${him(_1)} to an ice sculpture."
                    passive = "${name(_1)} ${is(_1)} frozen and turn${s(_1)} into an ice sculpture."
                }
                _52 {
                    active = "electrocute${s(_2)} ${him(_1)} to death."
                    passive = "${name(_1)} ${is(_1)} struck by lightning and die${s(_1)}."
                }
                _53 {
                    active = "let${s(_2)} the depths swallow ${him(_1)}."
                    passive = "${name(_1)} ${is(_1)} consumed by darkness."
                }
                _54 {
                    active = "completely disable${s(_2)} ${him(_1)}."
                    passive = "${name(_1)} lose${s(_1)} ${his(_1)} mind and commit${s(_1)} a suicide."
                }
                _55 {
                    active = "kill${s(_2)} ${him(_1)} with poison."
                    passive = "${name(_1)} ${is(_1)} poisoned to death."
                }
                _56 {
                    active = "entrap${s(_2)} ${him(_1)} into the inferno."
                    passive = "${name(_1)} go${s(_1, true)} to hell."
                }
                _57 {
                    active = "shatter${s(_2)} ${him(_1)} to atoms."
                    passive = "${name(_1)} resonate${s(_1)} and break up."
                }
                _58 {
                    active = "destroy${s(_2)} ${his(_1)} nerves."
                    passive = "${name(_1)} die${s(_1)} from neurofibroma."
                }
                _59 {
                    active = "let${s(_2)} the chaos consume ${him(_1)}."
                    passive = "${name(_1)} ${is(_1)} drawn into a chaotic vortex."
                }
                # _60
                _61 {
                    active = "cut${s(_2)} ${him(_1)} into thin strips."
                    passive = "${name(_1)} ${is(_1)} cut into thin strips."
                }
                # _62
                _63 {
                    active = "melt${s(_2)} ${him(_1)} away."
                    passive = "${name(_1)} melt${s(_1)}."
                }
            }
            other {
                _1 {
                    text = "${name(_1)} ${is(_1)} caught in a trap and die${s(_1)}."
                    death_cause = "got caught in a trap and died"
                }
                _2 {
                    text = "${name(_1)} die${s(_1)} from over-casting."
                    death_cause = "was completely wiped by magic reaction"
                }
                _3 {
                    text = "${name(_1)} ${is(_1)} starved to death."
                    death_cause = "was starved to death"
                }
                _4 {
                    text = "${name(_1)} ${is(_1)} killed with poison."
                    death_cause = "miserably died from poison"
                }
                _5 {
                    text = "${name(_1)} die${s(_1)} from curse."
                    death_cause = "died from curse"
                }
                _6 {
                    text = "${name(_1)} ${is(_1)} squashed by ${_2}."
                    death_cause = "was squashed by ${_1}".
                    backpack = "backpack"
                }
                _7 {
                    text = "${name(_1)} tumble${s(_1)} from stairs and die${s(_1)}."
                    death_cause = "tumbled from stairs and died"
                }
                _8 {
                    text = "${name(_1)} ${is(_1)} killed by an audience."
                    death_cause = "was killed by an audience"
                }
                _9 {
                    text = "${name(_1)} ${is(_1)} burnt and turned into ash."
                    death_cause = "was burnt and turned into ash"
                }
                # _10
                _11 {
                    text = "${name(_1)} ${is(_1)} assassinated by the unseen hand."
                    death_cause = "got assassinated by the unseen hand"
                }
                _12 {
                    text = "${name(_1)} ${is(_1)} killed by food poisoning."
                    death_cause = "got killed by food poisoning"
                }
                _13 {
                    text = "${name(_1)} die${s(_1)} from loss of blood."
                    death_cause = "died from loss of blood"
                }
                _14 {
                    text = "${name(_1)} die${s(_1)} of the Ether disease."
                    death_cause = "died of the Ether disease"
                }
                _15 {
                    text = "${name(_1)} melt${s(_1)} down."
                    death_cause = "melted down"
                }
                _16 {
                    text = "${name(_1)} shatter${s(_1)}."
                    death_cause = "committed suicide"
                }
                _17 {
                    text = "${name(_1)} ${is(_1)} turned into atoms."
                    death_cause = "was killed by an atomic bomb"
                }
                _18 {
                    text = "${name(_1)} step${s(_1)} into an iron maiden and die${s(_1)}."
                    death_cause = "stepped in an iron maiden and died"
                }
                _19 {
                    text = "${name(_1)} ${is(_1)} guillotined and die${s(_1)}."
                    death_cause = "was guillotined"
                }
                _20 {
                    text = "${name(_1)} hang${s(_1)} ${his(_1)}self."
                    death_cause = "commited suicide by hanging"
                }
                _21 {
                    text = "${name(_1)} choke${s(_1)} on mochi and die."
                    death_cause = "ate mochi and died"
                }
            }
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
