locale {
    skill {
        gained = "You have learned new ability, ${_1}."

        default {
            increase = "${name(_1)}${his_owned(_1)} ${_2} skill increases."
            decrease = "${name(_1)}${his_owned(_1)} ${_2} skill falls off."
        }

        # HP
        _2 {
            increase = "${name(_1)}${his_owned(_1)} life force increases."
            decrease = "${name(_1)}${his_owned(_1)} life force decreases."
        }

        # MP
        _3 {
            increase = "${name(_1)}${his_owned(_1)} mana increases."
            decrease = "${name(_1)}${his_owned(_1)} mana decreases."
        }

        # Strength
        _10 {
            increase = "${name(_1)}${his_owned(_1)} muscles feel stronger."
            decrease = "${name(_1)}${his_owned(_1)} muscles soften."
        }

        # Constitution
        _11 {
            increase = "${name(_1)} begin${s(_1)} to feel good when being hit hard."
            decrease = "${name(_1)} lose${s(_1)} patience."
        }

        # Dexterity
        _12 {
            increase = "${name(_1)} become${s(_1)} dexterous."
            decrease = "${name(_1)} become${s(_1)} clumsy."
        }

        # Perception
        _13 {
            increase = "${name(_1)} feel${s(_1)} more in touch with the world."
            decrease = "${name(_1)} ${is(_1)} getting out of touch with the world."
        }

        # Learning
        _14 {
            increase = "${name(_1)} feel${s(_1)} studious."
            decrease = "${name(_1)} lose${s(_1)} curiosity."
        }

        # Will
        _15 {
            increase = "${name(_1)}${his_owned(_1)} will hardens."
            decrease = "${name(_1)}${his_owned(_1)} will softens."
        }

        # Magic
        _16 {
            increase = "${name(_1)}${his_owned(_1)} magic improves."
            decrease = "${name(_1)}${his_owned(_1)} magic degrades."
        }

        # Charisma
        _17 {
            increase = "${name(_1)} enjoy${s(_1)} showing off ${his(_1)} body."
            decrease = "${name(_1)} start${s(_1)} to avoid eyes of people."
        }

        # Speed
        _18 {
            increase = "${name(_1)}${his_owned(_1)} speed increases."
            decrease = "${name(_1)}${his_owned(_1)} speed decreases."
        }

        # Luck
        _19 {
            increase = "${name(_1)} become${s(_1)} lucky."
            decrease = "${name(_1)} become${s(_1)} unlucky."
        }
    }
}
