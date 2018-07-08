locale {
    element {
        name {
            starving = "starving"
            rotten = "rotten"
            fearful = "fearful"
            silky = "silky"

            _50 = "burning"
            _51 = "icy"
            _52 = "electric"
            _54 = "psychic"
            _58 = "numb"
            _57 = "shivering"
            _55 = "poisonous"
            _56 = "infernal"
            _59 = "chaotic"
            _53 = "gloomy"
            _61 = "cut"
            _62 = "ether"
        }

        damage {
            default = "${name(_1)} ${is(_1)} wounded."
            _50 = "${name(_1)} ${is(_1)} burnt."
            _51 = "${name(_1)} ${is(_1)} frozen."
            _52 = "${name(_1)} ${is(_1)} shocked."
            _53 = "${name(_1)} ${is(_1)} struck by dark force."
            _54 = "${name(_1)} suffer${s(_1)} a splitting headache."
            _55 = "${name(_1)} suffer${s(_1)} from venom."
            _56 = "${name(_1)} ${is(_1)} chilled by infernal squall."
            _57 = "${name(_1)} ${is(_1)} shocked by a shrill sound."
            _58 = "${name(_1)}${his_owned(_1)} nerves are hurt."
            _59 = "${name(_1)} ${is(_1)} hurt by chaotic force."
            # _60
            _61 = "${name(_1)} get${s(_1)} a cut."
            # _62
            _63 = "${name(_1)} ${is(_1)} burnt by acid."
        }

        resist {
            gain {
                _50 = "Suddenly, ${name(_1)} feel${s(_1)} very hot."
                _51 = "Suddenly, ${name(_1)} feel${s(_1)} very cool."
                _52 = "${name(_1)}${is(_1)} struck by an electric shock."
                _54 = "Suddenly, ${name(_1)}${his_owned(_1)} mind becomes very clear."
                _58 = "${name(_1)}${his_owned(_1)} nerve is sharpened."
                _53 = "${name(_1)} no longer fear${s(_1)} darkness."
                _57 = "${name(_1)}${his_owned(_1)} eardrums get thick."
                _59 = "Suddenly, ${name(_1)} understand${s(_1)} chaos."
                _55 = "${name(_1)} now ${have(_1)} antibodies to poisons."
                _56 = "${name(_1)} ${is(_1)} no longer afraid of hell."
                _60 = "${name(_1)}${his_owned(_1)} body is covered by a magical aura."
            }
            lose {
                _50 = "${name(_1)} sweat${s(_1)}."
                _51 = "${name(_1)} shiver${s(_1)}."
                _52 = "${name(_1)} ${is(_1)} shocked."
                _54 = "${name(_1)}${his_owned(_1)} mind becomes slippery."
                _58 = "${name(_1)} become${s(_1)} dull."
                _53 = "Suddenly, ${name(_1)} fear${s(_1)} darkness."
                _57 = "${name(_1)} become${s(_1)} very sensitive to noises."
                _59 = "${name(_1)} no longer understand${s(_1)} chaos."
                _55 = "${name(_1)} lose${s(_1)} antibodies to poisons."
                _56 = "${name(_1)} ${is(_1)} afraid of hell."
                _60 = "The magical aura disappears from ${name(_1)}${his_owned(_1)} body."
            }
        }
    }
}
