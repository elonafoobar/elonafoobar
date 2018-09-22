locale {
    chara {
        you = "you"
        something = "something"

        age_unknown = "Unknown"

        name_with_title = "{${_1}}"

        contract_expired = "The period of contract with ${basename(_1)} has been expired."

        corruption {
            symptom = "The symptom of the Ether disease is shown up on you."
            add = "Your disease is getting worse."
            remove = "The symptoms of the Ether disease seem to calm down."
        }

        gain_level {
            self = "${name(_1)} have gained a level."
            other = "${name(_1)} ${have(_1)} grown up."
        }

        weight {
            gain = "${name(_1)} gain${s(_1)} weight."
            lose = "${name(_1)} lose${s(_1)} weight."
        }

        height {
            gain = "${name(_1)} grow${s(_1)} taller."
            lose = "${name(_1)} grow${s(_1)} smaller."
        }

        place_failure {
            ally = "${name(_1)} loses ${his(_1)} way."
            other = "${name(_1)} is killed."
        }

        impression {
            gain = "Your relation with ${basename(_1)} becomes <${_2}>!"
            lose = "Your relation with ${basename(_1)} becomes <${_2}>..."
        }

        job {
            general_vendor = "${trim_job(_1)}the general vendor"
            innkeeper = "${trim_job(_1)}the Innkeeper"
            trader = "${trim_job(_1)}the trader"
            goods_vendor = "${trim_job(_1)}the goods vendor"
            baker = "${trim_job(_1)}the baker"
            magic_vendor = "${trim_job(_1)}the magic vendor"
            blacksmith = "${trim_job(_1)}the blacksmith"
            trainer = "${trim_job(_1)}the trainer"
            fisher = "${trim_job(_1)}the fisher"
            blackmarket = "${trim_job(_1)}the blackmarket vendor"
            food_vendor = "${trim_job(_1)}the food vendor"
            souvenir_vendor = "${trim_job(_1)}the souvenir vendor"

            # Vernis
            of_vernis = "${_1} of Vernis"

            # Palmia
            of_palmia = "${_1} of Palmia city"

            # Noyel
            street_vendor = "${trim_job(_1)}the street vendor"
            street_vendor2 = "${trim_job(_1)}the street vendor"
            of_noyel = "${_1} of Noyel"
            fanatic = [
                "Opatos Fanatic",
                "Mani Fanatic",
                "Ehekatl Fanatic"
            ]

            # Yowyn
            horse_master = "${trim_job(_1)}the horse master"
            of_yowyn = "${_1} of Yowyn"

            # Derphy
            slave_master = "The slave master"
            of_derphy = "${_1} of Derphy"

            # Port Kapul
            of_port_kapul = "${_1} of Port Kapul"

            # Lumiest
            of_lumiest = "${_1} of Lumiest"

            # High Mountain
            dye_vendor = "${trim_job(_1)}the dye vendor"

            # Mages Guild
            spell_writer = "${trim_job(_1)}the spell writer"

            # Thieves Guild
            fence = "${trim_job(_1)}the fence"

            # Encounter
            wandering_vendor = "${trim_job(_1)}the wandering vendor"


            own_name = "${_2} the ${_1}"

            alien {
                child = "child"
                alien_kid = "alien kid"
                child_of = "child of ${_1}"
            }

            shade = "shade"
        }

        garbage = "a garbage"
    }
}
