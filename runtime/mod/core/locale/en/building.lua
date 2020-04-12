ELONA.i18n:add {
   building = {
      can_only_use_in_world_map = "You can only use it in the world map.",
      cannot_build_it_here = "You can't build it here.",
      cannot_build_anymore = "You can't build a building anymore.",
      really_build_it_here = "Really build it here? ",

      built_new_house = "You've built a new house!",
      built_new = "You've built a {$1}!",

      not_enough_money = "You don't have enough money...",

      names = {
         _521 = "museum",
         _522 = "shop",
         _542 = "crop",
         _543 = "storage",
         _572 = "ranch",
         _712 = "dungeon",
      },

      guests = {
         armory = "{basename($1)} of armory",
         general_store = "{basename($1)} of general store",
         magic_store = "{basename($1)} of magic store",
         goods_store = "{basename($1)} of goods store",
         blackmarket = "{basename($1)} of blackmarket",
      },

      house_board = {
         only_use_in_home = "You can only use it in your home.",
         item_count = "There are {$2} items and {$3} furniture in {$1}.(Max:{$4}) ",
         what_do = "What do you want to do?",

         choices = {
            assign_a_shopkeeper = "Assign a shopkeeper",
            extend = "Extend({$1} GP)",
            assign_a_breeder = "Assign a breeder",
            design = "Design",
            home_rank = "Home rank",
            allies_in_your_home = "Allies in your home",
            recruit_a_servant = "Recruit a servant",
            move_a_stayer = "Move a stayer",
         },
      },

      home = {
         hire = {
            who = "Who do you want to hire?",
            too_many_guests = "You already have too many guests in your home.",
            you_hire = "You hire {basename($1)}.",
         },

         design = {
            help = "Left click to place the tile, left click with Ctrl key to fill, right click to pick the tile under your mouse cursor, movement keys to move current position, hit the enter key to show the list of tiles, hit the cancel key to exit.",
         },

         move = {
            who = "Move who?",
            dont_touch_me = "{basename($1)}\"Don't touch me!\"",
            where = "Where do you want to move {basename($1)}?",
            invalid = "The location is invalid.",
            is_moved = "{basename($1)} {is($1)} moved to the location.",
         },

         staying = {
            count = "{$1} members are staying at your home (Max: {$2}).",
            remove = {
               ally = "{basename($1)} {is($1)} no longer staying at your home.",
               worker = "You remove {basename($1)} from {his($1)} job.",
            },

            add = {
               ally = "{basename($1)} stay{s($1)} at your home now.",
               worker = "{basename($1)} take{s($1)} charge of the job now.",
            },
         },

         rank = {
            title = "Home Value",
            enter_key = "Enter key,",
            value = "Value",
            heirloom_rank = "Heirloom Rank",

            type = {
               base = "Base",
               deco = "Deco",
               heir = "Heir",
               total = "Total",
            },

            star = "*",
            place = "{$1}",
            change = "Furniture Value:{$1} Heirloom Value:{$2} Home Rank:{$3}->{$4} Your home is now known as <{$5}>.",
         },
      },

      shop = {
         extend = "You extend your shop! You can display max of {$1} items now!",
         current_shopkeeper = "Current shopkeeper is {basename($1)}.",
         no_assigned_shopkeeper = "You haven't assigned a shopkeeper yet.",

         log = {
            no_shopkeeper = "[Shop] Your shop doesn't have a shopkeeper.",
            could_not_sell = "[Shop] {$1} customers visited your shop but {basename($2)} couldn't sell any item.",
            sold_items = "[Shop] {$1} customers visited your shop and {basename($2)} sold {$3} item{s($3)}. {capitalize(basename($2))} put {$4} in the shop strong box.",
            gold = "{$1} gold pieces",
            and_items = " and {$1} items",
         },
      },

      ranch = {
         current_breeder = "Current breeder is {basename($1)}.",
         no_assigned_breeder = "You haven't assigned a breeder yet.",
      },

      museum = {
         rank_change = "Museum Rank:{$1}->{$2} Your museum is now known as <{$3}>.",
      },
   },
}
