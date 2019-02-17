# NOTE: Will change drastically with the introduction of custom gods.

locale {
    god {
        indifferent = " Your God becomes indifferent to your gift."
        enraged = "${_1} is enraged." # TODO duplicate?

        switch {
            unbeliever = "You are an unbeliever now."
            follower = "You become a follower of ${_1}!"
        }

        pray {
            do_not_believe = "You don't believe in God."
            prompt = "Really pray to your God?"
            you_pray_to = "You pray to ${_1}."
            indifferent = "${_1} is indifferent to you."

            servant {
                no_more = "No more than 2 God's servants are allowed in your party."
                party_is_full = "Your party is full. The gift is reserved."
                prompt_decline = "Do you want to decline this gift?"
            }
        }

        window {
            title = "< ${_1} >"

            abandon = "Abandon God"
            convert = "Convert to ${_1}"
            believe = "Believe in ${_1}"
            cancel = "Cancel"

            # NOTE: The extra whitespace is significant. These strings should have the same number
            # of characters each.
            offering = "Offering"
            bonus    = "   Bonus"
            ability  = " Ability"
        }

        text {
            eyth {
                name = "Eyth of Infidel",
            }
        }
    }
}
