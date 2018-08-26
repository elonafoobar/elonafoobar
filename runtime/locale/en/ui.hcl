locale {
    ui {
        save = "*saving*"
        playtime = "${_1}:${_2}:${_3} Sec"
        save_on_suspend = "App focus was lost. Quicksaving game."

        date = "${_1} ${_2}/${_3}"
        date_hour = "${_1}h"

        article = "[${_1}]"

        menu {
            change = "Change"
            chara {
                chara = "Chara"
                wear = "Wear"
                feat = "Feat"
                material = "Material"
            }
            spell {
                spell = "Spell"
                skill = "Skill"
            }
            log {
                log = "Log"
                journal = "Journal"
                chat = "Chat"
            }
            town {
                chart = "Chart"
                economy = "City"
                politics = "Law"
            }
        }

        hint {
            # TODO trim whitespace and brackets
            cursor = "Cursor [Select]  "
            page = " [Page]  "
            close = "Shift,Esc [Close]  "
            back = "Shift,Esc [Back]  "
            enter = "Enter,"
            known_info = " [Known info]  "
            mode = " [Mode]  "
            portrait = "p [Portrait]  "
            shortcut = "0~9 [Shortcut]  "
            help = " [Help]  "
        }

        quick_menu {
            # Page 1
            help = "Help"
            log = "Log"
            chara = "Chara"
            journal = "Journal"

            # Page 2
            wear = "Wear"
            rest = "Rest"
            spell = "Spell"
            skill = "Skill"
            fire = "Fire"
            dig = "Dig"

            # Page 3
            pray = "Pray"
            ammo = "Ammo"
            interact = "Interact"
            bash = "Bash"

            # Page selection
            info = "Info"
            action = "Action"
            etc = "Etc"
        }

        exhelp {
            title = "- Norne's travel guide -"
        }

        message {
            hit_any_key = "Hit any key to close"
        }

        scene {
            which = "Which scene do you want to replay?"
            you_can_play = "You can play the unlocked scenes."
            scene_no = "Scene No. "
            has_been_played = "The scene has been played."
        }

        spell {
            title = "Spell"

            name = "Name"
            cost = "Cost"
            stock = "Stock"
            lv_chance = "Lv/Chance"
            effect = "Effect"

            turn_counter = "t"
            power = "Power:"
        }

        skill {
            title = "Skill"

            name = "Name"
            cost = "Cost"
            detail = "Detail"
        }

        chara_sheet {
            title {
                default = "Character Sheet"
                training = "Skill Training"
                learning = "Skill Learning"
            }

            category {
                skill = "Skill"
                weapon_proficiency = "Weapon Proficiency"
                resistance = "Resistance"
            }

            train_which_skill = "Train which skill?"
            you_can_spend_bonus = "You can spend ${_1} bonus points."

            attributes = "Attributes(Org) - Potential"
            combat_rolls = "Combat Rolls"
            history = "Trace"
            blessing_and_hex = "Blessing and Hex"
            extra_info = "Extra Info"

            damage {
                protect = "Prot"
                evade = "Evade"

                hit = "Hit"

                melee = "Melee"
                unarmed = "Unarmed"
                dist = "Dist"
            }

            exp {
                level = "Level"
                exp = "EXP"
                next_level = "Next Lv"
                god = "God"
                guild = "Guild"
            }

            personal {
                name = "Name"
                aka = "Aka"
                race = "Race"
                sex = "Sex"
                class = "Class"
                age = "Age"
                height = "Height"
                weight = "Weight"

                age_counter = ""
            }

            attribute {
                life = "Life"
                mana = "Mana"
                sanity = "Sanity"
                speed = "Speed"
                fame = "Fame"
                karma = "Karma"
                melee = "Melee"
                shoot = "Shoot"
            }

            time {
                turns = "Turns"
                days = "Days"
                kills = "Kills"
                time = "Time"

                turn_counter = "${_1} Turns"
                days_counter = "${_1} Days"
            }

            weight {
                cargo_weight = "Cargo Wt"
                cargo_limit = "Cargo Lmt"
                equip_weight = "Equip Wt"
                deepest_level = "Deepest Lv"

                level_counter = "${_1} Level"
            }

            buff {
                duration = "(${_1}) "
                is_not_currently = "This character isn't currently blessed or hexed."
                hint = "Hint"
            }

            skill {
                name = "Name"
                level = "Lv"
                potential = "Potential"
                detail = "Detail"
                resist = "Resist ${_1}"
            }

            hint {
                # TODO trim whitespace and brackets
                hint = "Cursor [Hint]  "
                spend_bonus = "Enter [Spend Bonus]  "
                reroll = "Enter Key [Reroll]  "
                confirm = "Shift,Esc [Confirm]"
                train_skill = "Enter [Train Skill]  "
                learn_skill = "Enter [Learn Skill]  "
                blessing_info = "Cursor [Blessing/Curse Info] "
                track_skill = "Track Skill"
            }
        }

        equip {
            title = "Equipment"

            category = "Category"
            name = "Name"
            weight = "Weight"

            resist = "Fi Co Li Da Mi Po Nt So Nr Ch Ma"

            equip_weight = "Equip weight"
            hit_bonus = "Hit Bonus"
            damage_bonus = "Damage Bonus"

            main_hand = "Hand*"

            cannot_be_taken_off = "${itemname(_1)} can't be taken off."
            you_unequip = "You unequip ${itemname(_1)}."
        }

        material {
            name = "Name"
            detail = "Detail"
        }

        appearance {
            hint = "Right,left [Change]  Shift,Esc [Close]"

            # Whitespace is significant.
            # Text is limited to 8~9 halfwidth characters.
            basic {
                title = "Appearance"
                category = "Category"

                done       = "Done    "
                portrait   = "Portrait"
                hair       = "Hair    "
                sub_hair   = "Sub Hair"
                hair_color = "Hair CL "
                body       = "Body    "
                cloth      = "Cloth   "
                pants      = "Pants   "
                set_detail = "Set Detail"

                custom     = "Custom  "
                riding     = "Riding  "
            }
            detail {
                body_color  = "Body CL "
                cloth_color = "Cloth CL"
                pants_color = "Pants CL"
                etc_1       = "Etc1    "
                etc_2       = "Etc2    "
                etc_3       = "Etc3    "
                eyes        = "Eyes    "
                set_basic   = "Set Basic"
            }
            equipment {
                title = "Parts to hide"
                part = "Part"

                done   = "Done    "
                chest  = "Chest   "
                leg    = "Leg     "
                belt   = "Belt    "
                glove  = "Glove   "
                mantle = "Mantle  "
            }
        }

        journal {
            rank {
                fame = "Fame"
                pay = "Pay: About ${_1} gold pieces "
                deadline = "\nDeadline: ${_1} Days left"

                arena = "EX Arena Wins:${_1}  Highest Level:${_2}"
            }

            income {
                # TODO remove tags
                salary {
                    title = "Salary (Paid every 1st and 15th day)"
                    sum = "@BL  Sum    : About ${_1} GP"
                }
                bills {
                    title = "Bills  (Issued every 1st day)"
                    labor = "@RE  Labor  : About ${_1} GP"
                    maintenance = "@RE  Maint. : About ${_1} GP"
                    tax = "@RE  Tax    : About ${_1} GP"
                    sum = "@RE  Sum    : About ${_1} GP"
                    unpaid = "You have ${_1} unpaid bills."
                }
            }
        }

        board {
            title = "Notice Board"

            difficulty = "$"
            difficulty_counter = "$ x ${_1}"

            no_new_notices = "It seems there are no new notices."
            do_you_meet = "Do you want to meet the client?"
        }

        npc_list {
            title = "NPC List"

            wage = "Wage"
            init_cost = "Init. Cost(Wage)"
            name = "Name"
            info = "Info"

            age_counter = "(${_1})"
            gold_counter = "${_1}gp"
        }

        reserve {
            title = "Reserve List"

            name = "Name"
            status = "Status"

            not_reserved = "-"
            reserved = "Reserved"

            unavailable = "\"Ah, that book is unavailable.\""
        }

        adventurers {
            title = "Adventurer Rank"

            name_and_rank = "Name and Rank"
            fame_lv = "Fame(Lv)"
            location = "Location"

            unknown = "Unknown"
            hospital = "Hospital"

            rank_counter = ""
        }

        alias {
            title = "Alias Selection"

            list = "Alias List"
            reroll = "Reroll"
        }

        town_chart {
            title = "City Chart"

            chart = "${_1} City Chart"

            no_economy = "There's no economy running in this area."
            empty = "Empty"
        }

        economy {
            information = "Town Information"
            finance = "Town Finance"

            population = "Population"
            basic_tax = "Basic Tax"
            excise_tax = "Excise Tax"

            population_detail = "Population Detail"
            finance_detail = "Finance Detail"
        }

        politics {
            law = "Law"
            global = "Global"
            law_of = "Law of ${_1}"

            name = "The capital of this country is ${_1}."
            taxes = "The consumption tax in this city is ${_1}%."
            well_pollution = "The well is polluted. (${_1} people have died)"
            lawless = "Murder is allowed in this city."
        }

        ally_list {
            name = "Name"
            status = "Status"
            proceed = "Proceed"

            dead = "(Dead)"
            waiting = "Waiting"
            alive = "(Alive)"

            call {
                prompt = "Call who?"
                title = "Ally List"

                waiting = "(Waiting)"
            }
            sell {
                prompt = "Sell who?"
                title = "Ally List"

                value = "Value"
            }
            pet_arena {
                prompt = "Participant"
                title = "Ally List"

                in = "In"

                need_at_least_one = "You need at least 1 pet to start the battle."
                is_dead = "${he(_1)} ${is(_1)} dead."
                too_many = "Too many participants."
            }
            shop {
                prompt = "Who takes the role of shopkeeper?"
                title = "Ally List"

                chr_negotiation = "CHR/Negotiation"
            }
            ranch {
                prompt = "Who takes the role of breeder?"
                title = "Ally List"

                breed_power = "Breed Power"
            }
            stayer {
                prompt = "Who stays in your home?"
                title = "Ally List"
            }
            gene_engineer {
                prompt = "Who is the subject?"
                title = "Ally List"

                body_skill = "Body/Skill"
                none = "None"

                skill_too_low = "You need to be a better gene engineer."
            }
        }

        manual {
            topic = "Topic"
            keys {
                list = "Key List"
                item {
                    title = "Item Keys"

                    get = "Get"
                    drop = "Drop"
                    examine = "Examine"
                    wear_wield = "Wear/Wield"
                    eat = "Eat"
                    quaff = "Quaff"
                    read = "Read"
                    zap = "Zap"
                    tool = "Tool"
                    blend = "Blend"
                    throw = "Throw"
                    ammo = "Ammo"
                }
                action {
                    title = "Action Keys"

                    search = "Search"
                    cast = "Cast"
                    interact = "Interact"
                    go_down = "Go Down"
                    go_up = "Go Up"
                    wait = "Wait"
                    target = "Target"
                    fire = "Fire"
                    apply = "Apply"
                    bash = "Bash"
                    dig = "Dig"
                    open = "Open"
                }
                info {
                    title = "Information Keys"

                    chara = "Character Info"
                    journal = "Journal"
                    help = "Help"
                    log = "Log"
                    material = "Material"
                    feat = "Feat"
                }
                other {
                    title = "Other Keys"

                    save = "Save"
                    pray = "Pray"
                    offer = "Offer"
                    close = "Close"
                    give = "Give"

                    hide_interface = "Hide interface"
                    export_chara_sheet = "Export chara sheet"
                    console = "Console"
                }
            }
        }
    }
}
