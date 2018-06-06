locale {
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
}
