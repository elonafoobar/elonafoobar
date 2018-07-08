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
            title = "Choose a recipe"
            name = "Name"
            hint = "[Page]  "

            warning = "(*) The feature is not implemented yet."
            which = "Which recipe do you want to use?"
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
            corpse = "${_1} corpse"
        }
    }
}
