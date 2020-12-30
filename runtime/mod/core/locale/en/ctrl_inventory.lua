local i18n = require("core.i18n")

i18n.add {
   ui = {
      inv = {
         title = {
            -- _0
            _1 = "Examine what? ",
            _2 = "Drop what? ",
            _3 = "Which item do you want to pick up? ",
            -- _4
            _5 = "Eat what? ",
            _6 = "Equip what?",
            _7 = "Read what? ",
            _8 = "Drink what? ",
            _9 = "Zap what? ",
            _10 = "Which item do you want to give? ",
            _11 = "What do you want to buy? ",
            _12 = "What do you want to sell? ",
            _13 = "Which item do you want to identify? ",
            _14 = "Use what? ",
            _15 = "Open what? ",
            _16 = "Cook what? ",
            _17 = "Blend what? ",
            _18 = "Which item do you want to apply the effect of {$1}?",
            _19 = "What do you want to offer to your God? ",
            _20 = "Which item do you want to trade? ",
            _21 = "What do you offer for {$1}?",
            _22 = "Take what? ",
            _23 = "Target what? ",
            _24 = "Put what? ",
            _25 = "Which item do you want to take? ",
            _26 = "Throw what? ",
            _27 = "Steal what? ",
            _28 = "Trade what? ",
            _29 = "Which item do you want to reserve? ",
         },

         window = {
            tag = {
               no_drop = "Tag No-Drop",
               multi_drop = "Multi Drop",
            },

            change = "Change",
            select_item = "{$1}",

            weight = "Weight",
            name = "Name",

            total_weight = "Weight {$1}/{$2}  Cargo {$3}",

            ground = "Ground",
            main_hand = "Main hand",
         },

         common = {
            set_as_no_drop = "It's set as no-drop. You can reset it from the <examine> menu.",
            does_not_exist = "The item doesn't exist.",
            inventory_is_full = "Your inventory is full.",

            invalid = "Invalid Item ID found ({$1}). It has been removed from your inventory.",
         },

         examine = {
            no_drop = {
               set = "You set {itemname($1)} as no-drop.",
               unset = "{itemname($1)} is no longer set as no-drop.",
            },
         },

         drop = {
            multi = "You can continuously drop items.",
            cannot_anymore = "You can't drop items any more.",
            how_many = "How many? (1 to {$1})",
         },

         eat = {
            too_bloated = {
               "Your are too full to eat.",
               "You are too bloated to eat any more.",
               "Your stomach can't digest any more.",
            },
         },

         equip = {
            too_heavy = "It's too heavy to equip.",

            you_equip = "You equip {itemname($1)}.",
            doomed = "You are now one step closer to doom.",
            cursed = "You suddenly feel a chill and shudder.",
            blessed = "You feel as someone is watching you intently.",
         },

         identify = {
            need_more_power = "You need higher identification to gain new knowledge.",

            -- NOTE: previously itemname(ci, 1)
            partially = "The item is half-identified as {itemname($1)}.",
            fully = "The item is fully identified as {itemname($1)}.",
         },

         give = {
            is_sleeping = "{name($1)} {is($1)} sleeping.",
            inventory_is_full = "{his($1)} inventory is full.",

            present = {
               text = "You give {name($1)} {itemname($2, 1)}.",
               dialog = "\"Thank you!\"",
            },

            refuse_dialog = {
               _0 = "\"Too heavy!\"",
               _1 = "\"No way.\"",
               _2 = "\"I don't want it.\"",
               _3 = "\"Never!\"",
            },

            too_creepy = "\"I don't want it. It's too creepy.\"",
            cursed = "\"It's cursed!\"",
            no_more_drink = "\"Enough for me.\"",
            abortion = "\"Abortion...\"",

            you_hand = "You hand {itemname($1, 1)} to {name($2)}.",
            engagement = "{name($1)} blushes.",

            love_potion = {
               text = "{name($1)} throws it on the ground angrily.",
               dialog = {
                  "\"You scum!\"",
                  "\"What are you trying to do!\"",
                  "\"Guard! Guard! Guard!\"",
               },
            },

            refuses = "{name($1)} refuse{s($1)} to take {itemname($2, 1)}.",
         },

         buy = {
            how_many = "How many? (1 to {$1})",
            prompt = "Do you really want to buy {$1} for {$2} gold pieces?",

            not_enough_money = {
               "You check your wallet and shake your head.",
               "You need to earn more money!",
            },

            window = {
               price = "Price",
            },
         },

         sell = {
            how_many = "How many? (1 to {$1})",
            prompt = "Do you really want to sell {$1} for {$2} gold pieces?",

            not_enough_money = "{name($1)} checks {his($1)} wallet and shake {his($1)} head.",
         },

         offer = {
            no_altar = "There's no altar here.",
         },

         trade = {
            too_low_value = "You don't have stuff that match {itemname($1)}.",
            you_receive = "You receive {itemname($2)} in exchange for {itemname($1)}.",
         },

         take = {
            no_claim = "You don't have a claim.",
            can_claim_more = "You can claim {$1} more heirloom{s($1)}.",
            really_leave = "Really leave these items?",
         },

         put = {
            container = {
               full = "The container is full.",
               too_heavy = "The container can only hold items weight less than {$1}.",
               cannot_hold_cargo = "The container cannot hold cargos",
            },

            guild = {
               have_no_quota = "You have no quota for Mages Guild.",
               you_deliver = "You deliver {itemname($1)}. ",
               remaining = "{$1}guild points are needed to gain a rank.",
               you_fulfill = "You fulfill the quota!",
            },

            tax = {
               not_enough_money = "You don't have enough money.",
               do_not_have_to = "You don't have to pay your tax yet.",
               you_pay = "You pay {itemname($1)}.",
            },

            harvest = "You deliver {itemname($1)}. +{$2} Delivered({$3}) Quota ({$4})",
         },

         take_ally = {
            refuse_dialog = "\"It's mine.\"",

            cursed = "{itemname($1)} is cursed and can't be taken off.",
            swallows_ring = "{name($1)} swallows {itemname($2, 1)} angrily.",
            you_take = "You take {$1}.",

            window = {
               equip_weight = "EquipWt",
               equip = "Equip",
            },
         },

         throw = {
            cannot_see = "You can't see the location.",
            location_is_blocked = "The location is blocked.",
         },

         steal = {
            has_nothing = "{name($1)} has nothing to steal.",
            there_is_nothing = "There's nothing to steal.",
            do_not_rob_ally = "You don't want to rob your ally.",
         },

         trade_medals = {
            medals = "(Coins: {$1})",
            medal_value = "{$1} Coins",
            inventory_full = "Your inventory is full.",
            not_enough_medals = "You don't have enough coins.",
            you_receive = "You receive {itemname($1, 1)}!",

            window = {
               medal = "Medal",
            },
         },

         cannot_use_cargo_items = "You can only use cargo items on the surface.",
      },
   },
}
