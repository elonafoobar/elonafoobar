locale {
    building {
        can_only_use_in_world_map = "You can only use it in the world map."
        cannot_build_it_here = "You can't build it here."
        cannot_build_anymore = "You can't build a building anymore."
        really_build_it_here = "Really build it here? "

        built_new_house = "You've built a new house!"
        built_new = "You've built a ${_1}!"

        not_enough_money = "You don't have enough money..."

        names {
            _521 = "museum"
            _522 = "shop"
            _542 = "crop"
            _543 = "storage"
            _572 = "ranch"
            _712 = "dungeon"
        }

        guests {
            armory = "${basename(_1)} of armory"
            general_store = "${basename(_1)} of general store"
            magic_store = "${basename(_1)} of magic store"
            goods_store = "${basename(_1)} of goods store"
            blackmarket = "${basename(_1)} of blackmarket"
        }

        house_board {
            only_use_in_home = "You can only use it in your home."
            item_count = "There are ${_2} items and ${_3} furniture in ${_1}.(Max:${_4}) "
            what_do = "What do you want to do?"

            choices {
                assign_a_shopkeeper = "Assign a shopkeeper"
                extend = "Extend(${_1} GP)"
                assign_a_breeder = "Assign a breeder"
                design = "Design"
                home_rank = "Home rank"
                allies_in_your_home = "Allies in your home"
                recruit_a_servant = "Recruit a servant"
                move_a_stayer = "Move a stayer"
            }
        }

        home {
            hire {
                who = "Who do you want to hire?"
                too_many_guests = "You already have too many guests in your home."
                you_hire = "You hire ${basename(_1)}."
            }

            design {
                help = "Left click to place the tile, right click to pick the tile under your mouse cursor, movement keys to move current position, hit the enter key to show the list of tiles, hit the cancel key to exit."
            }

            move {
                who = "Move who?"
                dont_touch_me = "${basename(_1)}\"Don't touch me!\""
                where = "Where do you want to move ${basename(_1)}?"
                invalid = "The location is invalid."
                is_moved = "${basename(_1)} ${is(_1)} moved to the location."
            }

            staying {
                count = "${_1} members are staying at your home (Max: ${_2})."
                remove {
                    ally = "${basename(_1)} ${is(_1)} no longer staying at your home."
                    worker = "You remove ${basename(_1)} from ${his(_1)} job."
                }

                add {
                    ally = "${basename(_1)} stay${s(_1)} at your home now."
                    worker = "${basename(_1)} take${s(_1)} charge of the job now."
                }
            }

            rank {
                title = "Home Value"
                enter_key = "Enter key,"
                value = "Value"
                heirloom_rank = "Heirloom Rank"

                type {
                    base = "Base"
                    deco = "Deco"
                    heir = "Heir"
                    total = "Total"
                }

                star = "*"
                place = "${_1}"
                change = "Furniture Value:${_1} Heirloom Value:${_2} Home Rank:${_3}->${_4} Your home is now known as <${_5}>."
            }
        }

        shop {
            info = "Shop"
            extend = "You extend your shop! You can display max of ${_1} items now!"
            current_shopkeeper = "Current shopkeeper is ${basename(_1)}."
            no_assigned_shopkeeper = "You haven't assigned a shopkeeper yet."

            log {
                no_shopkeeper = "Your shop doesn't have a shopkeeper."
                could_not_sell = "${_1} customers visited your shop but ${basename(_2)} couldn't sell any item."
                sold_items = "${_1} customers visited your shop and ${basename(_2)} sold ${_3} items. ${basename(_2)} put ${_4} in the shop strong box."
                gold = "${_1} gold pieces"
                and_items = " and ${_1} items"
            }
        }

        ranch {
            current_breeder = "Current breeder is ${basename(_1)}."
            no_assigned_breeder = "You haven't assigned a breeder yet."
        }

        museum {
            rank_change = "Museum Rank:${_1}->${_2} Your museum is now known as <${_3}>."
        }
    }
}
