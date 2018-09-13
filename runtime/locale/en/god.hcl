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

                desc {
                    mani = "This android shows enormous strength when boosting."
                    lulwy = "This black angel shows enormous strength when boosting."
                    itzpalt = "This exile can cast several spells in a row."
                    ehekatl = "Weapons and armor licked by this cat receive a blessing of Ehekatl which adds an extra enchantment."
                    opatos = "This knight can hold really heavy stuff for you."
                    jure = "This defender can use Lay on hand to heal a mortally wounded ally. The ability becomes re-useable after sleeping."
                    kumiromi = "This fairy generates a seed after eating."
                }
            }
        }

        desc {
            window {
                title = "< ${_1} >"

                abandon = "Abandon God"
                convert = "Convert to ${_1}"
                believe = "Believe in ${_1}"
                cancel = "Cancel"
            }

            # NOTE: The extra whitespace is significant. These strings should have the same number
            # of characters each.
            offering = "Offering"
            bonus    = "   Bonus"
            ability  = " Ability"

            # NOTE: These currently depend on manual line breaking (<br>, <p>) to fit in the
            # decription window. They should be checked manually.

            # Mani
            _1 {
                text = "Mani is a clockwork god of machinery. Those faithful to Mani<br>receive immense knowledge of machines and learn a way to use them<br>effectively.<p>"
                offering = "Corpses/Guns/Machinery<p>"
                bonus = "DEX/PER/Firearm/Healing/Detection/Jeweler/Lockpick/Carpentry<p>"
                ability = "Mani's decomposition (Passive: Extract materials<br>from traps.)<p>"
            }

            # Lulwy
            _2 {
                text = "Lulwy is a goddess of wind. Those faithful to Lulwy receive<br>the blessing of wind and can move swiftly.<p>"
                offering = "Corpses/Bows<p>"
                bonus = "PER/SPD/Bow/Crossbow/Stealth/Magic Device<p>"
                ability = "Lulwy's trick (Boost your speed for a short time.)<p>"
            }

            # Itzpalt
            _3 {
                text = "Itzpalt is a god of elements. Those faithful to Itzpalt are<br>protected from elemental damages and learn to absorb mana from<br>their surroundings.<p>"
                offering = "Corpses/Staves<p>"
                bonus = "MAG/Meditation/RES Fire/RES Cold/RES Lightning<p>"
                ability = "Absorb mana (Absorb mana from the air.)<p>"
            }

            # Ehekatl
            _4 {
                text = "Ehekatl is a goddess of luck. Those faithful to Ehekatl are<br>really lucky.<p><p>"
                offering = "Corpses/Fish<p>"
                bonus = "CHR/LUCK/Evasion/Magic Capacity/Fishing/Lockpick<p>"
                ability = "Ehekatl school of magic (Passive: Randomize casting mana<br>cost.)<p>"
            }

            # Opatos
            _5 {
                text = "Opatos is a god of earth. Those faithful to Opatos have massive<br>strength and defense.<p><p>"
                offering = "Corpses/Ores<p>"
                bonus = "STR/CON/Shield/Weight Lifting/Mining/Magic Device<p>"
                ability = "Opatos' shell (Passive: Reduce any physical damage you<br>receive.)<p>"
            }

            # Jure
            _6 {
                text = "Jure is a god of healing. Those faithful to Jure can heal wounds.<p><p>"
                offering = "Corpses/Ores<p>"
                bonus = "WIL/Healing/Meditation/Anatomy/Cooking/Magic Device/Magic Capacity<p>"
                ability = "Prayer of Jure (Heal yourself.)<p>"
            }

            # Kumiromi
            _7 {
                text = "Kumiromi is a god of harvest. Those faithful to Kumiromi receive<br>the blessings of nature.<p><p>"
                offering = "Corpses/Vegetables/Seeds<p>"
                bonus = "PER/DEX/LER/Gardening/Alchemy/Tailoring/Literacy<p>"
                ability = "Kumiromi's recycle (Passive: Extract seeds from rotten <p>foods.)<p>"
            }
        }
    }
}
