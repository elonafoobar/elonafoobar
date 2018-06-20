locale {
    blending {
        rate_panel {
            success_rate = "Success Rate: ${_1}"
            turns = "${_1} turns"
            and_hours = "and ${_1} hours"
            required_time = "Time: ${_1}"
        }

        window {
            procedure = "Blending Procedure"
            choose_a_recipe = "Choose a recipe"
            chose_the_recipe_of = "Chose the recipe of ${_1}"
            add = "Add ${_1}(Stock:${_2})"
            selected = "Selected ${itemname(_1)}"
            start = "Start blending!"
            the_recipe_of = "The recipe of ${_1}"
            required_skills = "Required Skills:"
            required_equipment = "Required equipment:"
            havent_identified = "You haven't identified it yet."
            no_inheritance_effects = "No inheritance effects"
        }

        prompt {
            how_many = "How many items do you want to create?"
            start = "Start blending"
            go_back = "Go back"
            from_the_start = "From the start"
        }

        recipe {
            warning = "(*) The feature is not implemented yet."
            which = "Which recipe do you want to use?"
            choose = "Choose a recipe"
            name = "Name"
            counter = "${_1} recipes"
            of = "Recipe of ${_1}"
        }

        steps {
            add_ingredient = "Add \"${_1}\"."
            add_ingredient_prompt = "Add ${_1}"
            item_name = "Name"
            item_counter = "${_1} items"
            ground = " (Ground)"
            you_add = "You add ${itemname(_1)}."
        }

        you_lose = "You lose ${itemname(_1, 1)}."

        started = "${name(_1)} start${s(_1)} blending of ${_2}."
        succeeded = "You successfully create ${itemname(_1, 1)}!"
        failed = "The blending attempt failed!"

        required_material_not_found = "A required material cannot be found."

        sounds {
            _0 = "*pug*"
            _1 = "*clank*"
        }

        success_rate {
            perfect = "Perfect!"
            piece_of_cake = "Piece of cake!"
            very_likely = "Very likely"
            no_problem = "No problem"
            probably_ok = "Probably OK"
            maybe = "Maybe"
            bad = "Bad"
            very_bad = "Very bad"
            almost_impossible = "Almost impossible"
            impossible = "Impossible!"

            goes_up = "The success rate goes up."
            goes_down = "The success rate goes down."
        }

        result {
            love_food = "You kind of feel guilty..."

            dyeing = "You dye ${itemname(_1)}."

            poisoned_food = "You grin."

            put_on = "You put ${itemname(_2, 1)} on ${itemname(_1)}."
            good_idea_but = "A good idea! But..."
            gains_fireproof = "${itemname(_1)} gain${s(_1)} fireproof."
            gains_acidproof = "${itemname(_1)} gain${s(_1)} acidproof."

            bait_attachment = "You bait ${itemname(_1)} with ${itemname(_2, 1)}."

            blessed_item = "You shower ${itemname(_1)} on ${itemname(_2, 1)}."
            becomes_blessed = "${itemname(_1)} shine${s(_1)} silvery."
            becomes_cursed = "${itemname(_1)} ${is(_1)} wrapped by a dark aura."

            well_refill = "You throw ${itemname(_1)} into ${itemname(_2, 1)}."
            empty_bottle_shatters = "You hear the sound of the empty bottle shatters."
            holy_well_polluted = "The holy well is polluted."
            well_dry = "${itemname(_1)} is completely dry."
            well_refilled = "${itemname(_1)} shines for a moment."
            snow_melts = "But the snow just melts."

            natural_potion = "You draw water from the well into the empty bottle."
            natural_potion_dry = "${itemname(_1)} is dry."
            natural_potion_drop = "Ops! You drop the empty bottle into the well..."
        }

        recipe {
            _200 = "love food"
            _201 = "dyeing"
            _202 = "poisoned food"
            _203 = "fireproof coating"
            _204 = "acidproof coating"
            _205 = "bait attachment"
            _206 = "blessed item"
            _207 = "well refill"
            _208 = "natural potion"
            _209 = "2 artifacts fusion"
            _210 = "3 artifacts fusion"
        }

        ingredient {
            _1 = "suitable flavoring"
            _2 = "any ore"
            _3 = "something made of wood"
            _4 = "fish"
            _5 = "any item"
        }
    }
}
