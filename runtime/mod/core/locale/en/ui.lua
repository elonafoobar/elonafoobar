local I18N = ELONA.require("core.I18N")

I18N.add {
   ui = {
      yes = "Yes",
      no = "No..",
      bye = "Bye bye.",
      more = "(More)",

      save = "*saving*",
      playtime = "{$1}:{$2}:{$3} Sec",
      save_on_suspend = "App focus was lost. Quicksaving game.",

      date = "{$1} {$2}/{$3}",
      date_hour = "{$1}h",

      article = "[{$1}]",

      gold = " gold pieces",
      platinum = " platinum pieces",
      unit_of_weight = "s",

      no_gold = "(You don't have enough money!)",
      invalid_target = "There's no valid target in that direction.",

      assign_shortcut = "You have assigned the shortcut to {{{$1}}} key.",

      curse_state = {
         cursed = "cursed",
         blessed = "blessed",
         doomed = "doomed",
      },

      menu = {
         change = "Change",
         chara = {
            chara = "Chara",
            wear = "Wear",
            feat = "Feat",
            material = "Material",
         },
         spell = {
            spell = "Spell",
            skill = "Skill",
         },
         log = {
            log = "Log",
            journal = "Journal",
            chat = "Chat",
         },
         town = {
            chart = "Chart",
            economy = "City",
            politics = "Law",
         },
      },

      hint = {
         -- TODO trim whitespace and brackets
         cursor = "Cursor [Select]  ",
         page = " [Page]  ",
         close = "Shift,Esc [Close]  ",
         back = "Shift,Esc [Back]  ",
         enter = "Enter,",
         known_info = " [Known info]  ",
         mode = " [Mode]  ",
         portrait = "p [Portrait]  ",
         shortcut = "0~9 [Shortcut]  ",
         help = " [Help]  ",
      },

      quick_menu = {
         -- Page 1
         help = "Help",
         log = "Log",
         chara = "Chara",
         journal = "Journal",

         -- Page 2
         wear = "Wear",
         rest = "Rest",
         spell = "Spell",
         skill = "Skill",
         fire = "Fire",
         dig = "Dig",

         -- Page 3
         pray = "Pray",
         ammo = "Ammo",
         interact = "Interact",
         bash = "Bash",

         -- Page selection
         info = "Info",
         action = "Action",
         etc = "Etc",
      },

      exhelp = {
         title = "- Norne's travel guide -",
      },

      message = {
         key_hint = "Up,Down [Scr 1 line]   Left,Right [Scr 1 page]   Hit other key to close",
      },

      chat = {
         key_hint = "Hit any key to close",
      },

      scene = {
         which = "Which scene do you want to replay?",
         you_can_play = "You can play the unlocked scenes.",
         scene_no = "Scene No. ",
         has_been_played = "The scene has been played.",
      },

      spell = {
         title = "Spell",

         name = "Name",
         cost = "Cost",
         stock = "Stock",
         lv_chance = "Lv/Chance",
         effect = "Effect",

         turn_counter = "t",
         power = "Power:",
      },

      skill = {
         title = "Skill",

         name = "Name",
         cost = "Cost",
         detail = "Detail",
      },

      chara_sheet = {
         title = {
            default = "Character Sheet",
            training = "Skill Training",
            learning = "Skill Learning",
         },

         category = {
            skill = "Skill",
            weapon_proficiency = "Weapon Proficiency",
            resistance = "Resistance",
         },

         train_which_skill = "Train which skill?",
         you_can_spend_bonus = "You can spend {$1} bonus points.",

         attributes = "Attributes(Org) - Potential",
         combat_rolls = "Combat Rolls",
         history = "Trace",
         blessing_and_hex = "Blessing and Hex",
         extra_info = "Extra Info",

         damage = {
            protect = "Prot",
            evade = "Evade",

            hit = "Hit",

            melee = "Melee",
            unarmed = "Unarmed",
            dist = "Dist",
         },

         exp = {
            level = "Level",
            exp = "EXP",
            next_level = "Next Lv",
            god = "God",
            guild = "Guild",
         },

         personal = {
            name = "Name",
            aka = "Aka",
            race = "Race",
            sex = "Sex",
            class = "Class",
            age = "Age",
            height = "Height",
            weight = "Weight",

            age_counter = "",
         },

         attribute = {
            life = "Life",
            mana = "Mana",
            sanity = "Sanity",
            speed = "Speed",
            fame = "Fame",
            karma = "Karma",
            melee = "Melee",
            shoot = "Shoot",
         },

         time = {
            turns = "Turns",
            days = "Days",
            kills = "Kills",
            time = "Time",

            turn_counter = "{$1} Turns",
            days_counter = "{$1} Days",
         },

         weight = {
            cargo_weight = "Cargo Wt",
            cargo_limit = "Cargo Lmt",
            equip_weight = "Equip Wt",
            deepest_level = "Deepest Lv",

            level_counter = "{$1} Level",
         },

         buff = {
            duration = "({$1}) ",
            is_not_currently = "This character isn't currently blessed or hexed.",
            hint = "Hint",
         },

         skill = {
            name = "Name",
            level = "Lv",
            potential = "Potential",
            detail = "Detail",
            resist = "Resist {$1}",
         },

         hint = {
            -- TODO trim whitespace and brackets
            hint = "Cursor [Hint]  ",
            spend_bonus = "Enter [Spend Bonus]  ",
            reroll = "Enter Key [Reroll]  ",
            confirm = "Shift,Esc [Confirm]",
            train_skill = "Enter [Train Skill]  ",
            learn_skill = "Enter [Learn Skill]  ",
            blessing_info = "Cursor [Blessing/Curse Info] ",
            track_skill = "Track Skill",
         },
      },

      equip = {
         title = "Equipment",

         category = "Category",
         name = "Name",
         weight = "Weight",

         resist = {
            _0 = "Fi",
            _1 = "Co",
            _2 = "Li",
            _3 = "Da",
            _4 = "Mi",
            _5 = "Po",
            _6 = "Nt",
            _7 = "So",
            _8 = "Nr",
            _9 = "Ch",
            _10 = "Ma",
         },

         maintenance = {
            _0 = "St",
            _1 = "Co",
            _2 = "De",
            _3 = "Pe",
            _4 = "Le",
            _5 = "Wi",
            _6 = "Ma",
            _7 = "Ch",
            _8 = "Sp",
            _9 = "Lu",
         },

         ailment = {
            _0 = "Bl",
            _1 = "Pa",
            _2 = "Co",
            _3 = "Fe",
            _4 = "Sl",
            _5 = "Po",
         },

         fireproof = "Fi",
         acidproof = "Ac",

         equip_weight = "Equip weight",
         hit_bonus = "Hit Bonus",
         damage_bonus = "Damage Bonus",

         main_hand = "Hand*",

         cannot_be_taken_off = "{itemname($1)} can't be taken off.",
         you_unequip = "You unequip {itemname($1)}.",
      },

      material = {
         name = "Name",
         detail = "Detail",
      },

      appearance = {
         hint = "Right,left [Change]  Shift,Esc [Close]",

         -- Whitespace is significant.
         -- Text is limited to 8~9 halfwidth characters.
         basic = {
            title = "Appearance",
            category = "Category",

            done = "Done    ",
            portrait = "Portrait",
            hair = "Hair    ",
            sub_hair = "Sub Hair",
            hair_color = "Hair CL ",
            body = "Body    ",
            cloth = "Cloth   ",
            pants = "Pants   ",
            set_detail = "Set Detail",

            custom = "Custom  ",
            riding = "Riding  ",
         },
         detail = {
            body_color = "Body CL ",
            cloth_color = "Cloth CL",
            pants_color = "Pants CL",
            etc_1 = "Etc1    ",
            etc_2 = "Etc2    ",
            etc_3 = "Etc3    ",
            eyes = "Eyes    ",
            set_basic = "Set Basic",
         },
         equipment = {
            title = "Parts to hide",
            part = "Part",

            done = "Done    ",
            chest = "Chest   ",
            leg = "Leg     ",
            belt = "Belt    ",
            glove = "Glove   ",
            mantle = "Mantle  ",
         },
      },

      journal = {
         rank = {
            fame = "Fame",
            pay = "Pay: About {$1} gold pieces ",
            deadline = "\nDeadline: {$1} Days left",

            arena = "EX Arena Wins:{$1}  Highest Level:{$2}",
         },

         income = {
            -- TODO remove tags
            salary = {
               title = "Salary (Paid every 1st and 15th day)",
               sum = "@BL  Sum    : About {$1} GP",
            },
            bills = {
               title = "Bills  (Issued every 1st day)",
               labor = "@RE  Labor  : About {$1} GP",
               maintenance = "@RE  Maint. : About {$1} GP",
               tax = "@RE  Tax    : About {$1} GP",
               sum = "@RE  Sum    : About {$1} GP",
               unpaid = "You have {$1} unpaid bills.",
            },
         },
      },

      board = {
         title = "Notice Board",

         difficulty = "$",
         difficulty_counter = "$ x {$1}",

         no_new_notices = "It seems there are no new notices.",
         do_you_meet = "Do you want to meet the client?",
      },

      npc_list = {
         title = "NPC List",

         wage = "Wage",
         init_cost = "Init. Cost(Wage)",
         name = "Name",
         info = "Info",

         age_counter = "({$1})",
         gold_counter = "{$1}gp",
      },

      reserve = {
         title = "Reserve List",

         name = "Name",
         status = "Status",

         not_reserved = "-",
         reserved = "Reserved",

         unavailable = "\"Ah, that book is unavailable.\"",
      },

      adventurers = {
         title = "Adventurer Rank",

         name_and_rank = "Name and Rank",
         fame_lv = "Fame(Lv)",
         location = "Location",

         unknown = "Unknown",
         hospital = "Hospital",

         rank_counter = "",
      },

      alias = {
         title = "Alias Selection",

         list = "Alias List",
         reroll = "Reroll",
      },

      town_chart = {
         title = "City Chart",

         chart = "{$1} City Chart",

         no_economy = "There's no economy running in this area.",
         empty = "Empty",
      },

      economy = {
         information = "Town Information",
         finance = "Town Finance",

         population = "Population",
         basic_tax = "Basic Tax",
         excise_tax = "Excise Tax",

         population_detail = "Population Detail",
         finance_detail = "Finance Detail",
      },

      politics = {
         law = "Law",
         global = "Global",
         law_of = "Law of {$1}",

         name = "The capital of this country is {$1}.",
         taxes = "The consumption tax in this city is {$1}%.",
         well_pollution = "The well is polluted. ({$1} people have died)",
         lawless = "Murder is allowed in this city.",
      },

      ally_list = {
         name = "Name",
         status = "Status",
         proceed = "Proceed",

         dead = "(Dead)",
         waiting = "Waiting",
         alive = "(Alive)",

         call = {
            prompt = "Call who?",
            title = "Ally List",

            waiting = "(Waiting)",
         },
         sell = {
            prompt = "Sell who?",
            title = "Ally List",

            value = "Value",
         },
         pet_arena = {
            prompt = "Participant",
            title = "Ally List",

            ["in"] = "In",

            need_at_least_one = "You need at least 1 pet to start the battle.",
            is_dead = "{he($1)} {is($1)} dead.",
            too_many = "Too many participants.",
         },
         shop = {
            prompt = "Who takes the role of shopkeeper?",
            title = "Ally List",

            chr_negotiation = "CHR/Negotiation",
         },
         ranch = {
            prompt = "Who takes the role of breeder?",
            title = "Ally List",

            breed_power = "Breed Power",
         },
         stayer = {
            prompt = "Who stays in your home?",
            title = "Ally List",
         },
         gene_engineer = {
            prompt = "Who is the subject?",
            title = "Ally List",

            body_skill = "Body/Skill",
            none = "None",

            skill_too_low = "You need to be a better gene engineer.",
         },
      },

      analysis = {
         title = "Analyze Self",
         result = "Analysis Result",
      },

      manual = {
         topic = "Topic",
         keys = {
            list = "Key List",
            item = {
               title = "Item Keys",

               get = "Get",
               drop = "Drop",
               examine = "Examine",
               wear_wield = "Wear/Wield",
               eat = "Eat",
               quaff = "Quaff",
               read = "Read",
               zap = "Zap",
               tool = "Tool",
               blend = "Blend",
               throw = "Throw",
               ammo = "Ammo",
            },
            action = {
               title = "Action Keys",

               search = "Search",
               cast = "Cast",
               interact = "Interact",
               go_down = "Go Down",
               go_up = "Go Up",
               wait = "Wait",
               target = "Target",
               fire = "Fire",
               apply = "Apply",
               bash = "Bash",
               dig = "Dig",
               open = "Open",
            },
            info = {
               title = "Information Keys",

               chara = "Character Info",
               journal = "Journal",
               help = "Help",
               log = "Log",
               material = "Material",
               feat = "Feat",
            },
            other = {
               title = "Other Keys",

               save = "Save",
               pray = "Pray",
               offer = "Offer",
               close = "Close",
               give = "Give",

               hide_interface = "Hide interface",
               export_chara_sheet = "Export chara sheet",
               console = "Console",
            },
         },
      },

      impression = {
         _0 = "Foe",
         _1 = "Hate",
         _2 = "Annoying",
         _3 = "Normal",
         _4 = "Amiable",
         _5 = "Friend",
         _6 = "Fellow",
         _7 = "Soul Mate",
         _8 = "*Love*",
      },

      home = {
         _0 = "cave",
         _1 = "shack",
         _2 = "cozy house",
         _3 = "estate",
         _4 = "cyber house",
         _5 = "small castle",
      },

      furniture = {
         _0 = "",
         _1 = "stupid",
         _2 = "lame",
         _3 = "cool",
         _4 = "madam's favorite",
         _5 = "bewitched",
         _6 = "maniac",
         _7 = "magnificent",
         _8 = "royal",
         _9 = "masterpiece",
         _10 = "heavenly",
         _11 = "godly",
      },

      weight = {
         _0 = "extremely mini",
         _1 = "small",
         _2 = "handy",
         _3 = "rather big",
         _4 = "huge",
         _5 = "pretty huge",
         _6 = "monstrous-size",
         _7 = "bigger than a man",
         _8 = "legendary-size",
         _9 = "heavier than an elephant",
      },

      reward = {
         _0 = "",
         _1 = "equipment",
         _2 = "magical goods",
         _3 = "armor",
         _4 = "weapons",
         _5 = "ores",
         _6 = "furnitures",
      },

      time = {
         _0 = "Midnight",
         _1 = "Dawn",
         _2 = "Morning",
         _3 = "Noon",
         _4 = "Dusk",
         _5 = "Night",
         _6 = "",
         _7 = "",
      },

      attribute = {
         _0 = " STR",
         _1 = " CON",
         _2 = " DEX",
         _3 = " PER",
         _4 = " LER",
         _5 = " WIL",
         _6 = " MAG",
         _7 = " CHR",
      },

      quality = {
         _0 = "",
         _1 = "bad",
         _2 = "good",
         _3 = "great",
         _4 = "miracle",
         _5 = "godly",
         _6 = "special",
      },

      resistance = {
         _0 = "Critically Weak",
         _1 = "Weak",
         _2 = "No Resist",
         _3 = "Little",
         _4 = "Normal",
         _5 = "Strong",
         _6 = "Superb",
      },

      mark = {
         _0 = ".",
         _1 = "?",
         _2 = "!",
         _3 = "",
      },

      sex = {
         _0 = "Male",
         _1 = "Female",
      },

      sex2 = {
         _0 = "boy",
         _1 = "girl",
      },

      sex3 = {
         male = "male",
         female = "female",
      },

      onii = {
         _0 = "brother",
         _1 = "sister",
      },

      syujin = {
         _0 = "my master",
         _1 = "my lady",
      },

      inventory_command = {
         _0 = "",
         _1 = "Examine",
         _2 = "Drop",
         _3 = "Pick Up",
         _4 = "",
         _5 = "Eat",
         _6 = "Wear",
         _7 = "Read",
         _8 = "Drink",
         _9 = "Zap",
         _10 = "Give",
         _11 = "Buy",
         _12 = "Sell",
         _13 = "Identify",
         _14 = "Use",
         _15 = "Open",
         _16 = "Cook",
         _17 = "Mix",
         _18 = "Mix Target",
         _19 = "Offer",
         _20 = "Trade",
         _21 = "Present",
         _22 = "Take",
         _23 = "Target",
         _24 = "Put",
         _25 = "Take",
         _26 = "Throw",
         _27 = "Pickpocket",
         _28 = "Trade",
         _29 = "Reserve",
      },

      cast_style = {
         _0 = " casts a spell.",
         _1 = " splits cobweb.",
         _2 = " spreads body fluid.",
         _3 = " puts out a tentacle.",
         _4 = " gazes.",
         _5 = " scatters spores.",
         _6 = " vibrates.",
      },

      -- Each entry corresponds to a value of originalnameref2 in core.item. There are always 6
      -- enum values.
      random_item = {
         potion = {
            name = "potion",
            _0 = "clear",
            _1 = "green",
            _2 = "blue",
            _3 = "gold",
            _4 = "brown",
            _5 = "red",
         },

         spellbook = {
            name = "spellbook",
            _0 = "thick",
            _1 = "mossy",
            _2 = "clear",
            _3 = "luxurious",
            _4 = "old",
            _5 = "bloody",
         },

         scroll = {
            name = "scroll",
            _0 = "blurred",
            _1 = "mossy",
            _2 = "ragged",
            _3 = "boring",
            _4 = "old",
            _5 = "bloody",
         },

         rod = {
            name = "rod",
            _0 = "iron",
            _1 = "ivy",
            _2 = "sapphire",
            _3 = "golden",
            _4 = "wooden",
            _5 = "rusty",
         },

         ring = {
            name = "ring",
            _0 = "iron",
            _1 = "green",
            _2 = "sapphire",
            _3 = "golden",
            _4 = "wooden",
            _5 = "rusty",
         },
      },


      cheer_up_message = {
         _1 = "Larnneire cheers, \"Way to go!\"",
         _2 = "Lomias grins, \"Go for it.\"",
         _3 = "Kumiromi worries, \"Are you...okay..?\"",
         _4 = "Lulwy sneers, \"You're tougher than I thought, little kitty.\"",
         _5 = "Larnneire cries, \"No...before it is too late...\"",
         _6 = "Lomias grins, \"It hasn't even started yet... has it?\"",
         _7 = "Lulwy warns you, \"Have a rest, kitty. If you are broken, you're no use to me.\"",
         _8 = "Lulwy laughs, \"I guess there's no use warning you. Alright. Do as you please, kitty.\"",
         _12 = "Opatos laughs, \"Muwahahahahahaha!\"",
         _24 = "Ehekatl hugs you,\"Don't die! Promise you don't die!\"",
      },

      autodig = {
         mode = "Autodig",
         enabled = "You enable autodig.",
         disabled = "You disable autodig.",
      },

      autopick = {
         do_you_really_pick_up = "Pick up {name($1)}?",
         do_you_really_destroy = "Destroy {name($1)}?",
         destroyed = "{name($1)} was destroyed.",
         do_you_really_open = "Open {name($1)}?",
      },

      digital_clock = {
         time = "{zfill($1, 2)}:{zfill($2, 2)}:{zfill($3, 2)}",
         date = "{zfill($1, 2)}/{zfill($2, 2)}/{zfill($3, 2)}",
      },

      save_header = {
         last_played_at = "Last played at {$1}/{zfill($2, 2)}/{zfill($3, 2)} {zfill($4, 2)}:{zfill($5, 2)}",
         play_seconds = {
            minutes = "Played in {$1} min.",
            hours = "Played in {$1} h. and {$2} min.",
         },
      },
   },
}
