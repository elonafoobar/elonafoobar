locale {
    status_ailment {
        message {
            blinded {
                apply = "${name(_1)} ${is(_1)} blinded."
                heal = "${name(_1)} can see again."
            }
            confused {
                apply = "${name(_1)} ${is(_1)} confused."
                heal = "${name(_1)} recover${s(_1)} from confusion."
            }
            paralyzed {
                apply = "${name(_1)} ${is(_1)} paralyzed."
                heal = "${name(_1)} recover${s(_1)} from paralysis."
            }
            poisoned {
                apply = "${name(_1)} ${is(_1)} poisoned."
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
                heal = "${name(_1)}${his_owned(_1)} bleeding stops."
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

        name {
            hunger {
                _0 = "Starving!",
                _1 = "Starving",
                _2 = "Hungry!",
                _3 = "Hungry",
                _4 = "Hungry",
                _5 = "",
                _6 = "",
                _7 = "",
                _8 = "",
                _9 = "",
                _10 = "Satisfied",
                _11 = "Satisfied!",
                _12 = "Bloated",
            }

            burden {
                _0 = "",
                _1 = "Burden",
                _2 = "Burden!",
                _3 = "Overweight",
                _4 = "Overweight!",
            }

            sleepy {
                _0 = "Sleepy",
                _1 = "Need Sleep",
                _2 = "Need Sleep!",
            }

            sick {
                _0 = "Sick",
                _1 = "Very Sick",
            }

            poison {
                _0 = "Poisoned",
                _1 = "Poisoned Bad!",
            }

            dimmed {
                _0 = "Dim",
                _1 = "Muddled",
                _2 = "Unconscious",
            }

            angry {
                _0 = "Fury",
                _1 = "Berserk",
            }

            bleeding {
                _0 = "Bleeding",
                _1 = "Bleeding!",
                _2 = "Hemorrhage",
            }

            insane {
                _0 = "Unsteady",
                _1 = "Insane",
                _2 = "Paranoia",
            }

            drunk = "Drunk"
            wet = "Wet"
            gravity = "Gravity"

            sleep {
                _0 = "Sleep",
                _1 = "Deep Sleep",
            }

            blind = "Blinded"
            paralyzed = "Paralyzed"
            choked = "Choked"
            confused = "Confused"
            fear = "Fear"

            tired {
                _0 = "Tired",
                _1 = "Very tired",
                _2 = "VERY tired",
            }
        }
    }
}
