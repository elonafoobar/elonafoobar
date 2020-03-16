i18n.add {
   item = {
      chip = {
         dryrock = "a dryrock",
         field = "a field",
      },

      desc = {
         have_to_identify = "You have to identify the item to gain knowledge.",
         no_information = "There is no information about this object.",

         it_is_made_of = "It is made of {$1}.",
         speeds_up_ether_disease = "It speeds up the ether disease while equipping.",

         weapon = {
            it_can_be_wielded = "It can be wielded as a weapon.",
            pierce = " Pierce ",
            light = "It is a light weapon.",
            heavy = "It is a heavy weapon.",
         },

         bonus = "It modifies hit bonus by {$1} and damage bonus by {$2}.",
         dv_pv = "It modifies DV by {$1} and PV by {$2}.",
         deck = "Collected cards",

         bit = {
            acidproof = "It is acidproof.",
            fireproof = "It is fireproof.",
            precious = "It is precious.",
            blessed_by_ehekatl = "It is blessed by Ehekatl.",
            stolen = "It is a stolen item.",
            alive = "It is alive.",
            show_room_only = "It can be only used in a show room.",
            handmade = "It is a hand-made item.",
            eternal_force = "The enemy dies.",
         },

         window = {
            title = "Known Information",
            error = "Unknown item definition. If possible, please report which menu the \"Known info\" menu (x key) was opened from (e.g. Drink, Zap, Eat, etc.).",
         },
      },

      armor_class = {
         heavy = "(Heavy)",
         medium = "(Medium)",
         light = "(Light)",
      },

      filter_name = {
         _60001 = "well",
         _57000 = "food",
         _56000 = "rods",
         _53000 = "scrolls",
         _52000 = "potions",
         _64000 = "junks",
         _77000 = "ores",
         _60000 = "furniture",
         _25000 = "ammos",
         default = "Unknown",
      },

      something_falls_and_disappears = "Something falls to the ground and disappears...",
      something_falls_from_backpack = "Something falls to the ground from your backpack.",

      stacked = "{itemname($1, 1)} has been stacked. (Total:{$2})",

      acid = {
         damaged = "{name($1)}{his_owned($1)} {itemname($0, false)} is damaged by acid.",
         immune = "{name($1)}{his_owned($1)} {itemname($0, false)} is immune to acid.",
      },

      item_on_the_ground_get_broiled = "{itemname($1)} on the ground get{_s($1)} perfectly broiled.",
      someones_item_get_broiled = "{name($2)}{his_owned($2)} {itemname($0, false)} get{_s($1)} perfectly broiled.",
      fireproof_blanket_protects_item = "{itemname($1, 1)} protects {name($2)}{his_owned($2)} stuff from fire.",
      fireproof_blanket_turns_to_dust = "{itemname($1, 1)} turns to dust.",
      item_someone_equips_turns_to_dust = "{$1} {name($3)} equip{s($3)} turn{s($2)} to dust.",
      someones_item_turns_to_dust = "{name($3)}{his_owned($3)} {$1} turn{s($2)} to dust.",
      item_on_the_ground_turns_to_dust = "{$1} on the ground turn{s($2)} to dust.",

      coldproof_blanket_protects_item = "{itemname($1, 1)} protects {name($2)}{his_owned($2)} stuff from cold.",
      coldproof_blanket_is_broken_to_pieces = "{itemname($1, 1)} is broken to pieces.",
      someones_item_breaks_to_pieces = "{name($3)}{his_owned($3)} {$1} break{s($2)} to pieces.",
      item_on_the_ground_breaks_to_pieces = "{$1} on the ground break{s($2)} to pieces.",

      items_are_destroyed = "Too many item data! Some items in this area are destroyed.",

      unknown_item = "unknown item (incompatible version)",

      miracle_paren = "<{$1}>",
      godly_paren = "{{{$1}}}",

      charges = "(Charges: {$1})",

      approximate_curse_state = {
         cursed = "(Scary)",
         doomed = "(Dreadful)",
      },

      gift_rank = {
         _0 = "cheap",
         _1 = "so so",
         _2 = "exciting",
         _3 = "expensive",
         _4 = "hot and gorgeous",
         _5 = "crazy epic",
      },

      kitty_bank_rank = {
         _0 = "(500 GP)",
         _1 = "(2k GP)",
         _2 = "(10K GP)",
         _3 = "(50K GP)",
         _4 = "(500K GP)",
         _5 = "(5M GP)",
         _6 = "(500M GP)",
      },

      bait_rank = {
         _0 = "water flea",
         _1 = "grasshopper",
         _2 = "ladybug",
         _3 = "dragonfly",
         _4 = "locust",
         _5 = "beetle",
      },

      ancient_book_title = {
         _0 = "Voynich Manuscript",
         _1 = "Dhol Chants",
         _2 = "Ponape Scripture",
         _3 = "Revelations of Glaaki",
         _4 = "G'harne Fragments",
         _5 = "Liber Damnatus",
         _6 = "Book of Dzyan",
         _7 = "Book of Eibon",
         _8 = "Grand Grimoire",
         _9 = "Celaeno Fragments",
         _10 = "Necronomicon",
         _11 = "The R'lyeh Text",
         _12 = "Eltdown Shards",
         _13 = "The Golden Bough",
         _14 = "Apocalypse",
      },
   },
}



i18n.add {
   item = {
      bug = {
         name = "gold bar",
         description = {
            main = {
               text = "not used in the game",
            },
         },
      },
      long_sword = {
         name = "long sword",
         description = {
            main = {
               text = "A double-edged sword",
            },
         },
      },
      dagger = {
         name = "dagger",
         description = {
            main = {
               text = "A small double-edged weapon used for close combat,",
            },
         },
      },
      hand_axe = {
         name = "hand axe",
         description = {
            main = {
               text = "A small single-bladed axe,",
            },
         },
      },
      club = {
         name = "club",
         description = {
            main = {
               text = "A blunt weapon with a round end that is sometimes spiked,",
            },
         },
      },
      magic_hat = {
         name = "magic hat",
         description = {
            main = {
               text = "A hat mages often wear,",
            },
         },
      },
      fairy_hat = {
         name = "fairy hat",
         description = {
            main = {
               text = "An exotic hat crafted by faeries,",
            },
         },
      },
      breastplate = {
         name = "breastplate",
         description = {
            main = {
               text = "An armor that offers decent protection,",
            },
         },
      },
      robe = {
         name = "robe",
         description = {
            main = {
               text = "A common robe,",
            },
         },
      },
      decorated_gloves = {
         name = "decorated gloves",
         description = {
            main = {
               text = "Gloves often worn by nobility,",
            },
         },
      },
      thick_gauntlets = {
         name = "thick gauntlets",
         description = {
            main = {
               text = "A pair of gauntlets made mostly of thick leather,",
            },
         },
      },
      heavy_boots = {
         name = "heavy boots",
         description = {
            main = {
               text = "Boots made for travel,",
            },
         },
      },
      composite_boots = {
         name = "composite boots",
         description = {
            main = {
               text = "A pair of boots with an armored mesh,",
            },
         },
      },
      decorative_ring = {
         name = "decorative ring",
         description = {
            main = {
               text = "A pretty ring,",
            },
         },
      },
      scroll_of_identify = {
         name = "identify",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_oracle = {
         name = "oracle",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_teleportation = {
         name = "teleportation",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_incognito = {
         name = "incognito",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      rod_of_identify = {
         name = "identify",
         description = {
            main = {
               text = "A wooden rod,",
            },
         },
      },
      rod_of_teleportation = {
         name = "teleportation",
         description = {
            main = {
               text = "A rod made out of steel,",
            },
         },
      },
      spellbook_of_teleportation = {
         name = "teleportation",
         description = {
            main = {
               text = "A yellowed tome whose words seem to move on their own/",
            },
         },
      },
      spellbook_of_identify = {
         name = "identify",
         description = {
            main = {
               text = "A yellowed tome that contains the secret of any item,",
            },
         },
      },
      spellbook_of_uncurse = {
         name = "uncurse",
         description = {
            main = {
               text = "A tome often carried by priests,",
            },
         },
      },
      book_a = {
         name = "book",
         unidentified_name = "book",
         description = {
            main = {
               text = "A leather bound book,",
            },
         },
      },
      book_b = {
         name = "book",
         unidentified_name = "book",
         description = {
            main = {
               text = "A book with watermarks,",
            },
         },
      },
      bugged_book = {
         name = "bugged book",
         unidentified_name = "book",
         description = {
            main = {
               text = "generated when failed to create an item",
            },
         },
      },
      bottle_of_dirty_water = {
         name = "dirty water",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "A bottle of murky water,",
            },
         },
      },
      potion_of_blindness = {
         name = "blindness",
         description = {
            main = {
               text = "Sometimes carried by prostitutes,",
            },
         },
      },
      potion_of_confusion = {
         name = "confusion",
         description = {
            main = {
               text = "A label says \"\"Please do not drink to identify contents,\"",
            },
         },
      },
      potion_of_paralysis = {
         name = "paralysis",
         description = {
            main = {
               text = "A label dictates \"\"For medical use only,\"",
            },
         },
      },
      sleeping_drug = {
         name = "sleeping drug",
         description = {
            main = {
               text = "A label says \"\"Do not inhale,\"",
            },
         },
      },
      crim_ale = {
         name = "crim ale",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "crim is some kind of addictive berry",
            },
         },
      },
      spellbook_of_ice_bolt = {
         name = "ice bolt",
         description = {
            main = {
               text = "The tome is cool to the touch,",
            },
         },
      },
      spellbook_of_fire_bolt = {
         name = "fire bolt",
         description = {
            main = {
               text = "The tome is strangely warm,",
            },
         },
      },
      spellbook_of_lightning_bolt = {
         name = "lightning bolt",
         description = {
            main = {
               text = "This tome lets off a static discharge,",
            },
         },
      },
      earth_crystal = {
         name = "earth crystal",
      },
      mana_crystal = {
         name = "mana crystal",
      },
      sun_crystal = {
         name = "sun crystal",
      },
      gold_bar = {
         name = "gold bar",
      },
      raw_ore_of_rubynus = {
         name = "rubynus",
      },
      raw_ore_of_mica = {
         name = "mica",
      },
      raw_ore_of_emerald = {
         name = "emerald",
      },
      raw_ore_of_diamond = {
         name = "diamond",
      },
      wood_piece = {
         name = "wood piece",
         description = {
            main = {
               text = "Not dry enough to burn easily,",
            },
         },
      },
      junk_stone = {
         name = "junk stone",
         description = {
            main = {
               text = "A useless stone that seems to break apart into sand when touched,",
            },
         },
      },
      garbage = {
         name = "garbage",
         description = {
            main = {
               text = "Stinky,,,",
            },
         },
      },
      broken_vase = {
         name = "broken vase",
         description = {
            main = {
               text = "Why would you take the time to collect the broken pieces?!?",
            },
         },
      },
      washing = {
         name = "washing",
         description = {
            main = {
               text = "North Tyris laws have harsh penalties for polluting water,",
            },
         },
      },
      bonfire = {
         name = "bonfire",
         description = {
            main = {
               text = "You smell something strange burning,",
            },
         },
      },
      flag = {
         name = "flag",
         description = {
            main = {
               text = "Comes with its own support so it does not touch the ground,",
            },
         },
      },
      broken_sword = {
         name = "broken sword",
         description = {
            main = {
               text = "The materials can probably be salvaged,",
            },
         },
      },
      bone_fragment = {
         name = "bone fragment",
         description = {
            main = {
               text = "Some bones are valuable",
            },
         },
      },
      skeleton = {
         name = "skeleton",
         description = {
            main = {
               text = "Bones of an unknown creature,",
            },
         },
      },
      tombstone = {
         name = "tombstone",
         description = {
            main = {
               text = "Please do not kick the tombstones,",
            },
         },
      },
      gold_piece = {
         name = "gold piece",
         description = {
            main = {
               text = "Standard currency of North Tyris,",
            },
         },
      },
      platinum_coin = {
         name = "platinum coin",
         description = {
            main = {
               text = "Rare coins used by the guilds for currency,",
            },
         },
      },
      diablo = {
         name = "<Diablo>",
         unidentified_name = "pure black sword",
         description = {
            main = {
               text = "This sword seems to be sentient,",
            },
         },
      },
      zantetsu = {
         name = "<Zantetsu>",
         unidentified_name = "shining silver katana",
         description = {
            main = {
               text = "Sword rumored to cut through anything,",
            },
         },
      },
      long_bow = {
         name = "long bow",
         description = {
            main = {
               text = "A bow specifically designed to shoot further than a short bow,",
            },
         },
      },
      knight_shield = {
         name = "knight shield",
         description = {
            main = {
               text = "A shield given to knights,",
            },
         },
      },
      pistol = {
         name = "pistol",
         description = {
            main = {
               text = "Made by Cyber Dome In",
            },
         },
      },
      arrow = {
         name = "arrow",
         description = {
            main = {
               text = "Hand forged arrows,",
            },
         },
      },
      bullet = {
         name = "bullet",
         description = {
            main = {
               text = "Made by Cyber Dome In",
            },
         },
      },
      scythe_of_void = {
         name = "<Scythe of Void>",
         unidentified_name = "scythe that sings death",
         description = {
            main = {
               text = "This weapon's very existence defies all logic,",
            },
         },
      },
      mournblade = {
         name = "<Mournblade>",
         unidentified_name = "chaotic sword",
         description = {
            main = {
               text = "An evil black sword surrounded with an aura of dread,",
            },
         },
      },
      light_cloak = {
         name = "light cloak",
         description = {
            main = {
               text = "Designed for children and smaller races,",
            },
         },
      },
      girdle = {
         name = "girdle",
         description = {
            main = {
               text = "A type of belt,",
            },
         },
      },
      decorative_amulet = {
         name = "decorative amulet",
         description = {
            main = {
               text = "A cute amulet,",
            },
         },
      },
      potion_of_cure_minor_wound = {
         name = "cure minor wound",
         description = {
            main = {
               text = "A potion that cures some wounds,",
            },
         },
      },
      potion_of_cure_major_wound = {
         name = "cure major wound",
         description = {
            main = {
               text = "A potion that cures some wounds,",
            },
         },
      },
      potion_of_cure_critical_wound = {
         name = "cure critical wound",
         description = {
            main = {
               text = "A potion that cures some wounds,",
            },
         },
      },
      potion_of_healing = {
         name = "healing",
         description = {
            main = {
               text = "A potion that cures some wounds,",
            },
         },
      },
      potion_of_healer = {
         name = "healer",
         description = {
            main = {
               text = "A potion that cures some wounds,",
            },
         },
      },
      ragnarok = {
         name = "<Ragnarok>",
         unidentified_name = "sword that ends all",
         description = {
            main = {
               text = "It's said that only a god can use its true power,",
            },
         },
      },
      potion_of_healer_odina = {
         name = "healer <Odina>",
         description = {
            main = {
               text = "A potion made by a talented alchemist cures some wounds,",
            },
         },
      },
      potion_of_healer_eris = {
         name = "healer <Eris>",
         description = {
            main = {
               text = "A potion made by a talented alchemist cures some wounds,",
            },
         },
      },
      potion_of_healer_jure = {
         name = "healer <Jure>",
         description = {
            main = {
               text = "A potion whose formula was created by Jure herself,",
            },
         },
      },
      round_chair = {
         name = "round chair",
         description = {
            main = {
               text = "A chair for a small child or a fairy,",
            },
         },
      },
      bookshelf = {
         name = "bookshelf",
         description = {
            main = {
               text = "Because there is no public library in Nort Tyris,",
            },
         },
      },
      luxury_drawer = {
         name = "luxury drawer",
         description = {
            main = {
               text = "A place to keep your spare clothes,",
            },
         },
      },
      boring_bed = {
         name = "boring bed",
         description = {
            main = {
               text = "A refurbished be",
            },
         },
      },
      rag_doll = {
         name = "rag doll",
         description = {
            main = {
               text = "A cute stuffed teddy bear,",
            },
         },
      },
      toy = {
         name = "toy",
         description = {
            main = {
               text = "A child's toy,",
            },
         },
      },
      modern_table = {
         name = "modern table",
         description = {
            main = {
               text = "A table made with Cyber Dome technology,",
            },
         },
      },
      dining_table = {
         name = "dining table",
         description = {
            main = {
               text = "A hand crafted dining table,",
            },
         },
      },
      armor = {
         name = "armor",
         description = {
            main = {
               text = "Armor on display,",
            },
         },
      },
      lot_of_goods = {
         name = "goods",
         description = {
            main = {
               text = "A display case for various gift items,",
            },
         },
      },
      lot_of_accessories = {
         name = "accessories",
         description = {
            main = {
               text = "A display case for various gift items,",
            },
         },
      },
      grand_piano = {
         name = "grand piano",
         description = {
            main = {
               text = "A beautifully crafted piano,",
            },
         },
      },
      bar_table_alpha = {
         name = "bar table alpha",
         description = {
            main = {
               text = "A table holding alcohol,",
            },
         },
      },
      bar_table_beta = {
         name = "bar table beta",
         description = {
            main = {
               text = "A table with coasters and peanut boxes,",
            },
         },
      },
      barrel = {
         name = "barrel",
         description = {
            main = {
               text = "A barrel for storing items,",
            },
         },
      },
      modern_chair = {
         name = "modern chair",
         description = {
            main = {
               text = "A chair made in Asseria,",
            },
         },
      },
      pick = {
         name = "pick",
         description = {
            main = {
               text = "A pick sometimes used for mining,",
            },
         },
      },
      lantern = {
         name = "lantern",
         description = {
            main = {
               text = "A light source,",
            },
         },
      },
      decorative_armor = {
         name = "decorative armor",
         description = {
            main = {
               text = "A set of decorative armor,",
            },
         },
      },
      anvil = {
         name = "anvil",
         description = {
            main = {
               text = "An anvil used for blacksmithing,",
            },
         },
      },
      closed_pot = {
         name = "closed pot",
         description = {
            main = {
               text = "A covered pot,",
            },
         },
      },
      open_pot = {
         name = "open pot",
         description = {
            main = {
               text = "An uncovered pot,",
            },
         },
      },
      academic_table = {
         name = "academic table",
         description = {
            main = {
               text = "A desk used for students in Asseria schools,",
            },
         },
      },
      rack_of_potions = {
         name = "potions",
         description = {
            main = {
               text = "A potions rack,",
            },
         },
      },
      square_chair = {
         name = "square chair",
         description = {
            main = {
               text = "An everyday chair,",
            },
         },
      },
      cheap_chair = {
         name = "cheap chair",
         description = {
            main = {
               text = "More like a foot stool,",
            },
         },
      },
      cupboard = {
         name = "cupboard",
         description = {
            main = {
               text = "A cupboard to store dishes,",
            },
         },
      },
      barn = {
         name = "barn",
      },
      neat_shelf = {
         name = "neat shelf",
         description = {
            main = {
               text = "A shelf containing books on crafting,",
            },
         },
      },
      closet = {
         name = "closet",
         description = {
            main = {
               text = "A closet for storing items,",
            },
         },
      },
      variety_of_tools = {
         name = "tools",
      },
      variety_of_goods = {
         name = "goods",
      },
      well = {
         name = "well",
         description = {
            main = {
               text = "Toss a coin in,",
            },
         },
      },
      variety_of_clothes = {
         name = "clothes",
      },
      furnace = {
         name = "furnace",
         description = {
            main = {
               text = "A furnace used for smithing,",
            },
         },
      },
      oven = {
         name = "oven",
         description = {
            main = {
               text = "A dwarven oven,",
            },
         },
      },
      sign = {
         name = "sign",
         description = {
            main = {
               text = "Sig",
            },
         },
      },
      crossroad_sign = {
         name = "crossroad sign",
         description = {
            main = {
               text = "Oop'",
            },
         },
      },
      board = {
         name = "board",
         description = {
            main = {
               text = "A note on this board reads \"\"Wante",
            },
         },
      },
      spellbook_of_minor_teleportation = {
         name = "minor teleportation",
         description = {
            main = {
               text = "The words in this tome do not seem to stay in one place,",
            },
         },
      },
      empty_basket = {
         name = "empty basket",
         description = {
            main = {
               text = "This basket is made out of wicker,",
            },
         },
      },
      spellbook_of_summon_monsters = {
         name = "summon monsters",
         description = {
            main = {
               text = "You can swear you hear growling,",
            },
         },
      },
      rod_of_cure_minor_wound = {
         name = "cure minor wound",
         description = {
            main = {
               text = "A wooden rod with a cloth grip,",
            },
         },
      },
      rod_of_magic_missile = {
         name = "magic missile",
         description = {
            main = {
               text = "A rod made out of iron,",
            },
         },
      },
      rod_of_summon_monsters = {
         name = "summon monsters",
         description = {
            main = {
               text = "A heavy rod,",
            },
         },
      },
      rod_of_ice_bolt = {
         name = "ice bolt",
         description = {
            main = {
               text = "A rod made out of wood,",
            },
         },
      },
      rod_of_fire_bolt = {
         name = "fire bolt",
         description = {
            main = {
               text = "A rod made out of metal,",
            },
         },
      },
      show_case_of_breads = {
         name = "breads",
         description = {
            main = {
               text = "A shelf of bread for display,",
            },
         },
      },
      rod_of_heal = {
         name = "heal",
         description = {
            main = {
               text = "A decorated wooden rod with a cloth grip,",
            },
         },
      },
      beaker = {
         name = "beaker",
         description = {
            main = {
               text = "Fragile scientific equipment,",
            },
         },
      },
      alchemy_kit = {
         name = "alchemy kit",
         description = {
            main = {
               text = "An alchemy kit with tools for basic alchemy,",
            },
         },
      },
      pentagram = {
         name = "pentagram",
         description = {
            main = {
               text = "An ancient religious symbol now containing six points!",
            },
         },
      },
      small_foliage_plant = {
         name = "small foliage plant",
         description = {
            main = {
               text = "Plants in a pot,",
            },
         },
      },
      rose = {
         name = "rose",
         description = {
            main = {
               text = "A symbol of love,",
            },
         },
      },
      large_foliage_plant = {
         name = "large foliage plant",
         description = {
            main = {
               text = "A decorative plant,",
            },
         },
      },
      sage = {
         name = "sage",
         description = {
            main = {
               text = "An herb used to season food,",
            },
         },
      },
      gazania = {
         name = "gazania",
         description = {
            main = {
               text = "Decorative flowers,",
            },
         },
      },
      nerine = {
         name = "nerine",
         description = {
            main = {
               text = "Decorative flowers,",
            },
         },
      },
      anemos = {
         name = "anemos",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      foxtail_grass = {
         name = "foxtail grass",
         description = {
            main = {
               text = "Has seeds that can be dangerous to your pets,",
            },
         },
      },
      carnation = {
         name = "carnation",
         description = {
            main = {
               text = "A symbol of love towards one's parents,",
            },
         },
      },
      pillar_ornamented_with_plants = {
         name = "ornamented with plants",
         description = {
            main = {
               text = "A pillar designed after one's common in Eludernia,",
            },
         },
      },
      pillar_ornamented_with_flowers = {
         name = "ornamented with flowers",
         description = {
            main = {
               text = "A pillar designed after one's common in Eludernia,",
            },
         },
      },
      canvas = {
         name = "canvas",
         description = {
            main = {
               text = "A canvas used for painting on,",
            },
         },
      },
      map = {
         name = "map",
         description = {
            main = {
               text = "A map of Elona,",
            },
         },
      },
      food_maker = {
         name = "food maker",
         description = {
            main = {
               text = "A tool used to cook food in Asseria,",
            },
         },
      },
      bundle_of_bows = {
         name = "bows",
         description = {
            main = {
               text = "A display of bows,",
            },
         },
      },
      bundle_of_weapons = {
         name = "weapons",
         description = {
            main = {
               text = "A display of weapons,",
            },
         },
      },
      decorated_cloth = {
         name = "decorated cloth",
         description = {
            main = {
               text = "A decorative cloth often used as a clothing store display,",
            },
         },
      },
      decorated_armor = {
         name = "decorated armor",
         description = {
            main = {
               text = "A decorative cloth often used as a display for armor stores,",
            },
         },
      },
      statue_of_armor = {
         name = "armor",
         description = {
            main = {
               text = "A shelf or armor,",
            },
         },
      },
      disorderly_book = {
         name = "disorderly book",
         description = {
            main = {
               text = "This is just a mess!",
            },
         },
      },
      lot_of_books = {
         name = "books",
         description = {
            main = {
               text = "A disorderly stacks of books,",
            },
         },
      },
      craft_rack = {
         name = "craft rack",
         description = {
            main = {
               text = "A nicely crafted piece of furniture,",
            },
         },
      },
      craft_book_shelf = {
         name = "craft book shelf",
         description = {
            main = {
               text = "A nicely crafted bookshelf,",
            },
         },
      },
      lot_of_alcohols = {
         name = "alcohols",
         description = {
            main = {
               text = "Often found in bars,",
            },
         },
      },
      kitchen = {
         name = "kitchen",
         description = {
            main = {
               text = "Part of a kitchen set,",
            },
         },
      },
      washstand = {
         name = "sink",
         description = {
            main = {
               text = "The water is dirty...",
            },
         },
      },
      kitchen_oven = {
         name = "kitchen oven",
         description = {
            main = {
               text = "The other half of a kitchen set,",
            },
         },
      },
      narrow_dining_table = {
         name = "narrow dining table",
         description = {
            main = {
               text = "A dining room table,",
            },
         },
      },
      elegant_table = {
         name = "elegant table",
         description = {
            main = {
               text = "Keep your elbows off the table!",
            },
         },
      },
      gorgeous_candlestick = {
         name = "gorgeous candlestick",
         description = {
            main = {
               text = "An ornamental candlestick,",
            },
         },
      },
      simple_shelf = {
         name = "simple shelf",
         description = {
            main = {
               text = "A shelf for your dining room,",
            },
         },
      },
      sewing_kit = {
         name = "sewing kit",
         description = {
            main = {
               text = "An sewing kit intended for clothing repair,",
            },
         },
      },
      carpenters_tool = {
         name = "carpenter's tool",
         description = {
            main = {
               text = "Used to craft some wooden items,",
            },
         },
      },
      messy_cloth = {
         name = "messy cloth",
         description = {
            main = {
               text = "A pile of laundry,",
            },
         },
      },
      silk_cloth = {
         name = "silk cloth",
         description = {
            main = {
               text = "Silk cloth woven by faeries,",
            },
         },
      },
      collapsed_grave = {
         name = "collapsed grave",
         description = {
            main = {
               text = "A common style grave that has started to crumble,",
            },
         },
      },
      crumbled_grave = {
         name = "crumbled grave",
         description = {
            main = {
               text = "A common style grave that has been destroyed,",
            },
         },
      },
      grave_ornamented_with_flowers = {
         name = "ornamented with flowers",
         description = {
            main = {
               text = "A recent grave with flowers for the departed... The name is still readable,",
            },
         },
      },
      brand_new_grave = {
         name = "brand new grave",
         description = {
            main = {
               text = "A recent grave... The name is still readable,",
            },
         },
      },
      solemn_tomb = {
         name = "solemn tomb",
         description = {
            main = {
               text = "A tome of a rich or heroic figure,",
            },
         },
      },
      ancient_tomb = {
         name = "ancient tomb",
         description = {
            main = {
               text = "An ancient Euldernan style tomb,",
            },
         },
      },
      old_grave = {
         name = "old grave",
         description = {
            main = {
               text = "An old norland tomb,",
            },
         },
      },
      altar = {
         name = "altar",
         description = {
            main = {
               text = "An altar to the gods",
            },
         },
      },
      ceremony_altar = {
         name = "ceremony altar",
         description = {
            main = {
               text = "An altar for rituals to give tribute to the gods,",
            },
         },
      },
      fountain = {
         name = "fountain",
         description = {
            main = {
               text = "Throw a coin in,",
            },
         },
      },
      bunk_bed = {
         name = "bunk bed",
         description = {
            main = {
               text = "A makeshift bunk be",
            },
         },
      },
      rod_of_lightning_bolt = {
         name = "lightning bolt",
         description = {
            main = {
               text = "A rod made out of bronze,",
            },
         },
      },
      rod_of_slow = {
         name = "slow",
         description = {
            main = {
               text = "A rod with a silver tip,",
            },
         },
      },
      quwapana = {
         name = "quwapana",
         description = {
            main = {
               text = "A type of vegetation,",
            },
         },
      },
      aloe = {
         name = "aloe",
         description = {
            main = {
               text = "A type of vegetation,",
            },
         },
      },
      edible_wild_plant = {
         name = "edible wild plant",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      apple = {
         name = "apple",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      grape = {
         name = "grape",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      kiwi = {
         name = "kiwi",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      cherry = {
         name = "cherry",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      guava = {
         name = "guava",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      carrot = {
         name = "carrot",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      radish = {
         name = "radish",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      sweet_potato = {
         name = "sweet potato",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      lettuce = {
         name = "lettuce",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      stack_of_dishes = {
         name = "dish",
         description = {
            main = {
               text = "A set of decorative dishes,",
            },
         },
      },
      imo = {
         name = "imo",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      api_nut = {
         name = "api nut",
         description = {
            main = {
               text = "A nut used to make candy",
            },
         },
      },
      strawberry = {
         name = "strawberry",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      healthy_leaf = {
         name = "healthy leaf",
         description = {
            main = {
               text = "A type of vegetation,",
            },
         },
      },
      rainbow_fruit = {
         name = "rainbow fruit",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      qucche = {
         name = "qucche",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      tangerine = {
         name = "tangerine",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      lemon = {
         name = "lemon",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      green_pea = {
         name = "green pea",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      cbocchi = {
         name = "cbocchi",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      melon = {
         name = "melon",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      leccho = {
         name = "leccho",
         description = {
            main = {
               text = "A type of vegetable,",
            },
         },
      },
      rod_of_magic_mapping = {
         name = "magic mapping",
         description = {
            main = {
               text = "A rod plated with adamantium,",
            },
         },
      },
      rod_of_cure = {
         name = "cure",
         description = {
            main = {
               text = "A wooden rod with a cloth grip,",
            },
         },
      },
      corpse = {
         name = "corpse",
         description = {
            main = {
               text = "A corpse of an unknown creature,",
            },
         },
      },
      bottle_of_whisky = {
         name = "whisky",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "A bottle of dwarven whisky,",
            },
         },
      },
      ether_dagger = {
         name = "<Ether Dagger>",
         unidentified_name = "dagger surrounded by wind",
         description = {
            main = {
               text = "This dagger seems to be made out of wind,",
            },
         },
      },
      bow_of_vindale = {
         name = "<Bow of Vindale>",
         unidentified_name = "shaking bow",
      },
      worthless_fake_gold_bar = {
         name = "worthless fake gold bar",
         unidentified_name = "valuable gold bar",
         description = {
            main = {
               text = "What a waste of time......,",
            },
         },
      },
      scroll_of_uncurse = {
         name = "uncurse",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      stone = {
         name = "stone",
         description = {
            main = {
               text = "It's just a stone",
            },
         },
      },
      sickle = {
         name = "sickle",
         description = {
            main = {
               text = "A farmer's tool for harvesting crops,",
            },
         },
      },
      staff = {
         name = "staff",
         description = {
            main = {
               text = "A staff used in a variety of ways,",
            },
         },
      },
      spear = {
         name = "spear",
         description = {
            main = {
               text = "A polearm with a sharp point,",
            },
         },
      },
      ore_piece = {
         name = "ore piece",
         description = {
            main = {
               text = "Pretty worthless,",
            },
         },
      },
      lot_of_empty_bottles = {
         name = "empty bottles",
         description = {
            main = {
               text = "They still smell of alcohol,",
            },
         },
      },
      basket = {
         name = "basket",
         description = {
            main = {
               text = "It's empty,",
            },
         },
      },
      empty_bowl = {
         name = "empty bowl",
         description = {
            main = {
               text = "It's empty,",
            },
         },
      },
      bowl = {
         name = "bowl",
         description = {
            main = {
               text = "I'm not sure I want to eat this,",
            },
         },
      },
      tight_rope = {
         name = "tight rope",
         description = {
            main = {
               text = "You start to practice your knots on this piece of rope,",
            },
         },
      },
      dead_fish = {
         name = "dead fish",
         description = {
            main = {
               text = "Hiding one of these is a popular prank in North Tyris...",
            },
         },
      },
      straw = {
         name = "straw",
         description = {
            main = {
               text = "This can be useful to the right person,",
            },
         },
      },
      animal_bone = {
         name = "animal bone",
         description = {
            main = {
               text = "Probably leftovers from a meal,",
            },
         },
      },
      pot = {
         name = "pot",
         description = {
            main = {
               text = "Useful for cooking!",
            },
         },
      },
      katana = {
         name = "katana",
         description = {
            main = {
               text = "A unique curved sword made through a folding process,",
            },
         },
      },
      scimitar = {
         name = "scimitar",
         description = {
            main = {
               text = "A curved sword,",
            },
         },
      },
      battle_axe = {
         name = "battle axe",
         description = {
            main = {
               text = "A large double-bladed axe",
            },
         },
      },
      hammer = {
         name = "hammer",
         description = {
            main = {
               text = "A tool that is sometimes adopted as a weapon",
            },
         },
      },
      trident = {
         name = "trident",
         description = {
            main = {
               text = "A three pronged polearm,",
            },
         },
      },
      long_staff = {
         name = "long staff",
         description = {
            main = {
               text = "A staff used primarily as a weapon and sometimes for magic,",
            },
         },
      },
      short_bow = {
         name = "short bow",
         description = {
            main = {
               text = "A standard easy to use bow,",
            },
         },
      },
      machine_gun = {
         name = "machine gun",
         description = {
            main = {
               text = "Made by Cyber Dome In",
            },
         },
      },
      claymore = {
         name = "claymore",
         description = {
            main = {
               text = "A large sword normally held in two hands,",
            },
         },
      },
      ration = {
         name = "ration",
         description = {
            main = {
               text = "A ratio",
            },
         },
      },
      bardiche = {
         name = "bardiche",
         description = {
            main = {
               text = "A single-bladed axe resembling a polearm,",
            },
         },
      },
      halberd = {
         name = "halberd",
         description = {
            main = {
               text = "A weapon resembling a spear with the head of an axe,",
            },
         },
      },
      scroll_of_return = {
         name = "return",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      figurine_of_warrior = {
         name = "warrior",
      },
      figurine_of_sword = {
         name = "sword",
      },
      bejeweled_chest = {
         name = "bejeweled chest",
         description = {
            main = {
               text = "An ancient jeweled chest,",
            },
         },
      },
      chest = {
         name = "chest",
         description = {
            main = {
               text = "A heavy chest,",
            },
         },
      },
      safe = {
         name = "safe",
         description = {
            main = {
               text = "It might not be safe to carry...",
            },
         },
      },
      scroll_of_magical_map = {
         name = "magical map",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_gain_attribute = {
         name = "gain attribute",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_wonder = {
         name = "wonder",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_minor_teleportation = {
         name = "minor teleportation",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      spellbook_of_magic_mapping = {
         name = "magic mapping",
         description = {
            main = {
               text = "A tome that makes you aware of your surroundings,",
            },
         },
      },
      spellbook_of_oracle = {
         name = "oracle",
         description = {
            main = {
               text = "A tome of prophecys,",
            },
         },
      },
      spellbook_of_return = {
         name = "return",
         description = {
            main = {
               text = "A tome that allows a person to return to specific places containing a rift,",
            },
         },
      },
      spellbook_of_cure_minor_wound = {
         name = "cure minor wound",
         description = {
            main = {
               text = "This tome has carefully been taken care of,",
            },
         },
      },
      spellbook_of_cure_critical_wound = {
         name = "cure critical wound",
         description = {
            main = {
               text = "This tome has been carefully preserved,",
            },
         },
      },
      spellbook_of_cure_eris = {
         name = "cure <Eris>",
         description = {
            main = {
               text = "A tome of arcane healing,",
            },
         },
      },
      spellbook_of_cure_jure = {
         name = "cure <Jure>",
         description = {
            main = {
               text = "A tome of words written by Jure herself,",
            },
         },
      },
      bottle_of_beer = {
         name = "beer",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "A bottle of beer,",
            },
         },
      },
      horn = {
         name = "horn",
         description = {
            main = {
               text = "A horn imported from Marr Nis Farra,",
            },
         },
      },
      campfire = {
         name = "campfire",
         description = {
            main = {
               text = "Due to magic these logs never burn up,",
            },
         },
      },
      portable_cooking_tool = {
         name = "portable cooking tool",
         description = {
            main = {
               text = "A cooking set popular among adventurers,",
            },
         },
      },
      spellbook_of_magic_arrow = {
         name = "magic arrow",
         description = {
            main = {
               text = "A tome that teaches how to use magical energy,",
            },
         },
      },
      stick_bread = {
         name = "stick bread",
         description = {
            main = {
               text = "A loaf of baked bread,",
            },
         },
      },
      raw_noodle = {
         name = "raw noodle",
         description = {
            main = {
               text = "This would taste better cooked,",
            },
         },
      },
      sack_of_flour = {
         name = "flour",
         description = {
            main = {
               text = "Flour used for baking,",
            },
         },
      },
      bomb_fish = {
         name = "bomb fish",
         description = {
            main = {
               text = "A type of fish,",
            },
         },
      },
      poison = {
         name = "poison",
         description = {
            main = {
               text = "Warning",
            },
         },
      },
      spellbook_of_nether_eye = {
         name = "nether eye",
         description = {
            main = {
               text = "You feel like the world of the dead has its eye on you,",
            },
         },
      },
      spellbook_of_chaos_eye = {
         name = "chaos eye",
         description = {
            main = {
               text = "This tome makes no sense,",
            },
         },
      },
      spellbook_of_nerve_eye = {
         name = "nerve eye",
         description = {
            main = {
               text = "Reading this tome makes your eye twitch,",
            },
         },
      },
      wakizashi = {
         name = "wakizashi",
         description = {
            main = {
               text = "A short sword usually worn together with a katana,",
            },
         },
      },
      spellbook_of_darkness_beam = {
         name = "darkness beam",
         description = {
            main = {
               text = "This tome seems to bend light,",
            },
         },
      },
      spellbook_of_illusion_beam = {
         name = "illusion beam",
         description = {
            main = {
               text = "A tome that hurts your eyes when read,",
            },
         },
      },
      spellbook_of_ice_ball = {
         name = "ice ball",
         description = {
            main = {
               text = "This tome is cold,",
            },
         },
      },
      spellbook_of_fire_ball = {
         name = "fire ball",
         description = {
            main = {
               text = "This tome is hot,",
            },
         },
      },
      spellbook_of_sound_ball = {
         name = "sound ball",
         description = {
            main = {
               text = "You can swear you hear a buzzing sound from this tome,",
            },
         },
      },
      spellbook_of_chaos_ball = {
         name = "chaos ball",
         description = {
            main = {
               text = "You find this tome confusing,",
            },
         },
      },
      fire_wood = {
         name = "fire wood",
         description = {
            main = {
               text = "Dried wood ready for burning,",
            },
         },
      },
      scarecrow = {
         name = "scarecrow",
         description = {
            main = {
               text = "Used by farmers to keep birds away from their crops,",
            },
         },
      },
      broom = {
         name = "broom",
         description = {
            main = {
               text = "Useful for cleaning,",
            },
         },
      },
      long_pillar = {
         name = "long pillar",
         description = {
            main = {
               text = "A pillar designed after one's common in Eludernia,",
            },
         },
      },
      broken_pillar = {
         name = "broken pillar",
         description = {
            main = {
               text = "A pillar designed after one's common in Eluderni",
            },
         },
      },
      street_lamp = {
         name = "street lamp",
         description = {
            main = {
               text = "A lamp that decorates the streets of Asseria,",
            },
         },
      },
      water_tub = {
         name = "water tub",
         description = {
            main = {
               text = "A warning label reads \"\"Not suitable for golems\"",
            },
         },
      },
      comfortable_table = {
         name = "comfortable table",
         description = {
            main = {
               text = "A table often used in one's house,",
            },
         },
      },
      inner_tube = {
         name = "inner tube",
         description = {
            main = {
               text = "Such an odd design,,,",
            },
         },
      },
      mysterious_map = {
         name = "mysterious map",
         description = {
            main = {
               text = "A map with no recognizable landmarks,",
            },
         },
      },
      suitcase = {
         name = "suitcase",
         description = {
            main = {
               text = "A suitcase lost by a traveler, ",
            },
         },
      },
      wallet = {
         name = "wallet",
         description = {
            main = {
               text = "A wallet lost by a traveler,",
            },
         },
      },
      potion_of_restore_body = {
         name = "restore body",
         description = {
            main = {
               text = "A potion that restores physical stats,",
            },
         },
      },
      potion_of_restore_spirit = {
         name = "restore spirit",
         description = {
            main = {
               text = "A potion that restores spiritual stats,",
            },
         },
      },
      potion_of_potential = {
         name = "potential",
         description = {
            main = {
               text = "A valuable potion,",
            },
         },
      },
      scroll_of_curse = {
         name = "curse",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      spellbook_of_wishing = {
         name = "wishing",
         description = {
            main = {
               text = "This tome is ancient and has a crushing aura of power,",
            },
         },
      },
      rod_of_wishing = {
         name = "wishing",
         description = {
            main = {
               text = "A dragon scale rod with a diamond tip,",
            },
         },
      },
      well_kept_armor = {
         name = "well kept armor",
         description = {
            main = {
               text = "Oiled and polished decorative armor",
            },
         },
      },
      rack_of_goods = {
         name = "goods",
         description = {
            main = {
               text = "Products for display or sale,",
            },
         },
      },
      rack_of_accessories = {
         name = "accessories",
         description = {
            main = {
               text = "Products for display or sale,",
            },
         },
      },
      towel = {
         name = "towel",
         description = {
            main = {
               text = "Soft fluffy towels!",
            },
         },
      },
      ragged_table = {
         name = "ragged table",
         description = {
            main = {
               text = "A rustic table,",
            },
         },
      },
      cabinet = {
         name = "cabinet",
         description = {
            main = {
               text = "The drawer is locked,",
            },
         },
      },
      luxury_bed = {
         name = "luxury bed",
         description = {
            main = {
               text = "A bed made in Asseria,",
            },
         },
      },
      vase = {
         name = "vase",
         description = {
            main = {
               text = "A vase on a night stand,",
            },
         },
      },
      high_grade_dresser = {
         name = "high grade dresser",
         description = {
            main = {
               text = "A beautifully crafted dresser,",
            },
         },
      },
      neat_bar_table = {
         name = "neat bar table",
         description = {
            main = {
               text = "A bar table with racks of alcohol and wine,",
            },
         },
      },
      large_bouquet = {
         name = "large bouquet",
         description = {
            main = {
               text = "A beautiful bouquet of flowers,",
            },
         },
      },
      chest_of_clothes = {
         name = "clothes",
         description = {
            main = {
               text = "A clean set of clothing,",
            },
         },
      },
      giant_bed = {
         name = "giant bed",
         description = {
            main = {
               text = "A large and elegant bed,",
            },
         },
      },
      plain_bed = {
         name = "plain bed",
         description = {
            main = {
               text = "A bed made in Cyber Dome,",
            },
         },
      },
      coffin = {
         name = "coffin",
         description = {
            main = {
               text = "It would be disrespectful of the deceased to sleep in this",
            },
         },
      },
      food_processor = {
         name = "food processor",
         description = {
            main = {
               text = "A miracle of technology!",
            },
         },
      },
      soft_bed = {
         name = "soft bed",
         description = {
            main = {
               text = "A soft bed meant for a child,",
            },
         },
      },
      cheap_rack = {
         name = "cheap rack",
         description = {
            main = {
               text = "An ordinary inexpensive rack,",
            },
         },
      },
      dresser = {
         name = "dresser",
         description = {
            main = {
               text = "A common dresser,",
            },
         },
      },
      clean_bed = {
         name = "clean bed",
         description = {
            main = {
               text = "At least it's clean,",
            },
         },
      },
      bathtub = {
         name = "bathtub",
         description = {
            main = {
               text = "A porcelain bathtub,",
            },
         },
      },
      pachisuro_machine = {
         name = "pachisuro machine",
         description = {
            main = {
               text = "Similar to a slot machine,",
            },
         },
      },
      casino_table = {
         name = "casino table",
         description = {
            main = {
               text = "It's no fun without other people,,,",
            },
         },
      },
      slot_machine = {
         name = "slot machine",
         description = {
            main = {
               text = "Do you want to try it?",
            },
         },
      },
      darts_board = {
         name = "darts board",
         description = {
            main = {
               text = "A note reads \"\"Please do not play drunk!\"",
            },
         },
      },
      big_foliage_plant = {
         name = "big foliage plant",
         description = {
            main = {
               text = "The leaves look fake,",
            },
         },
      },
      old_shelf = {
         name = "old shelf",
         description = {
            main = {
               text = "It looks like it's going to fall apart!",
            },
         },
      },
      old_bookshelf = {
         name = "old bookshelf",
         description = {
            main = {
               text = "You see large cracks in the wood,",
            },
         },
      },
      cheap_bed = {
         name = "cheap bed",
         description = {
            main = {
               text = "A bed made out of recycled parts...,,",
            },
         },
      },
      cheap_table = {
         name = "cheap table",
         description = {
            main = {
               text = "A table made out of recycled wood,",
            },
         },
      },
      neat_rack = {
         name = "neat rack",
         description = {
            main = {
               text = "A rack with a framed set of glass doors,",
            },
         },
      },
      simple_dresser = {
         name = "simple dresser",
         description = {
            main = {
               text = "A dresser often made for children,",
            },
         },
      },
      big_cupboard = {
         name = "big cupboard",
         description = {
            main = {
               text = "Holds a lot of dishes,",
            },
         },
      },
      sacred_altar = {
         name = "sacred altar",
         description = {
            main = {
               text = "An altar with a holy aura,",
            },
         },
      },
      comfortable_bed = {
         name = "comfortable bed",
         description = {
            main = {
               text = "An average bed,",
            },
         },
      },
      simple_rack = {
         name = "simple rack",
      },
      wide_chair = {
         name = "wide chair",
      },
      upright_piano = {
         name = "upright piano",
         description = {
            main = {
               text = "A piano commonly found in bars",
            },
         },
      },
      statue_of_cross = {
         name = "cross",
         description = {
            main = {
               text = "An ancient symbol,",
            },
         },
      },
      stump = {
         name = "stump",
         description = {
            main = {
               text = "The remains of a tree that has been cut out of the ground and is used as a seat,",
            },
         },
      },
      dress = {
         name = "dress",
         description = {
            main = {
               text = "A lovely dress,",
            },
         },
      },
      table = {
         name = "table",
         description = {
            main = {
               text = "A common table,",
            },
         },
      },
      cargo_travelers_food = {
         name = "traveler's food",
         description = {
            main = {
               text = "Travel rations often used by merchants,",
            },
         },
      },
      throne = {
         name = "throne",
         description = {
            main = {
               text = "Built for royalty,",
            },
         },
      },
      golden_pedestal = {
         name = "golden pedestal",
         description = {
            main = {
               text = "A pedestal decorated with gold leaf,",
            },
         },
      },
      statue_of_money = {
         name = "money",
         description = {
            main = {
               text = "A statue common in Asseria style casinos,",
            },
         },
      },
      remains_skin = {
         name = "skin",
         description = {
            main = {
               text = "The skin of a creature,",
            },
         },
      },
      remains_blood = {
         name = "blood",
         description = {
            main = {
               text = "The blood of a creature,",
            },
         },
      },
      remains_eye = {
         name = "eye",
         description = {
            main = {
               text = "The eye of a creature,",
            },
         },
      },
      remains_heart = {
         name = "heart",
         description = {
            main = {
               text = "The heart of a creature,",
            },
         },
      },
      remains_bone = {
         name = "bone",
         description = {
            main = {
               text = "The bones of a creature,",
            },
         },
      },
      fishing_pole = {
         name = "fishing pole",
         description = {
            main = {
               text = "A pole used for bait fishing,",
            },
         },
      },
      rune = {
         name = "rune",
         description = {
            main = {
               text = "A magical rune that warps reality,",
            },
         },
      },
      deed = {
         name = "deed",
      },
      moonfish = {
         name = "moonfish",
         description = {
            main = {
               text = "A beautiful fish as pale as the moon,",
            },
         },
      },
      sardine = {
         name = "sardine",
         description = {
            main = {
               text = "A small oily fish,",
            },
         },
      },
      flatfish = {
         name = "flatfish",
         description = {
            main = {
               text = "An odd fish that lays on its side,",
            },
         },
      },
      manboo = {
         name = "manboo",
      },
      seabream = {
         name = "seabream",
      },
      salmon = {
         name = "salmon",
         description = {
            main = {
               text = "A fish with unique spawning habits,",
            },
         },
      },
      globefish = {
         name = "globefish",
         description = {
            main = {
               text = "A fish that can inflate itself into a round ball,",
            },
         },
      },
      tuna = {
         name = "tuna",
         description = {
            main = {
               text = "A carnivorous fish,",
            },
         },
      },
      cutlassfish = {
         name = "cutlassfish",
         description = {
            main = {
               text = "A fish that looks something like an Eel,",
            },
         },
      },
      sandborer = {
         name = "sandborer",
      },
      gloves_of_vesda = {
         name = "<Gloves of Vesda>",
         unidentified_name = "burning gloves",
      },
      blood_moon = {
         name = "<Blood Moon>",
         unidentified_name = "bloody mace",
      },
      ring_of_steel_dragon = {
         name = "<Ring of Steel Dragon>",
         unidentified_name = "steel ring",
      },
      staff_of_insanity = {
         name = "<Staff of Insanity>",
         unidentified_name = "shivering staff",
      },
      rankis = {
         name = "<Rankis>",
         unidentified_name = "cursed halberd",
      },
      palmia_pride = {
         name = "<Palmia Pride>",
         unidentified_name = "blue ring",
      },
      shopkeepers_trunk = {
         name = "shopkeeper's trunk",
      },
      scroll_of_greater_identify = {
         name = "greater identify",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_vanish_curse = {
         name = "vanish curse",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      potion_of_defender = {
         name = "defender",
         description = {
            main = {
               text = "A magical potion that can protect you from harm,",
            },
         },
      },
      spellbook_of_holy_shield = {
         name = "holy shield",
         description = {
            main = {
               text = "A yellowed tome with a holy aura,",
            },
         },
      },
      rod_of_silence = {
         name = "silence",
         description = {
            main = {
               text = "A mica tipped rod,",
            },
         },
      },
      spellbook_of_silence = {
         name = "silence",
         description = {
            main = {
               text = "A tome whose words are impossible to pronounce for most creatures,",
            },
         },
      },
      potion_of_silence = {
         name = "silence",
         description = {
            main = {
               text = "...,,",
            },
         },
      },
      spellbook_of_regeneration = {
         name = "regeneration",
         description = {
            main = {
               text = "A tome that looks like new,",
            },
         },
      },
      potion_of_troll_blood = {
         name = "troll blood",
         description = {
            main = {
               text = "Tastes worse than it smells,",
            },
         },
      },
      spellbook_of_resistance = {
         name = "resistance",
         description = {
            main = {
               text = "A tome that seems undamaged by the weather,",
            },
         },
      },
      potion_of_resistance = {
         name = "resistance",
         description = {
            main = {
               text = "A magical potion that can protect you from harm,",
            },
         },
      },
      spellbook_of_speed = {
         name = "speed",
         description = {
            main = {
               text = "A hastily written tome,",
            },
         },
      },
      spellbook_of_slow = {
         name = "slow",
         description = {
            main = {
               text = "A yellowed tome that's pages seem to move slowly,",
            },
         },
      },
      potion_of_speed = {
         name = "speed",
         description = {
            main = {
               text = "A magical potion that increases your speed temporarily,",
            },
         },
      },
      potion_of_slow = {
         name = "slow",
         description = {
            main = {
               text = "An item often carried by thieves,",
            },
         },
      },
      rod_of_speed = {
         name = "speed",
         description = {
            main = {
               text = "A rod made out of glass,",
            },
         },
      },
      spellbook_of_hero = {
         name = "hero",
         description = {
            main = {
               text = "Strangely reading this book gives you a slight adrenalin rush,",
            },
         },
      },
      potion_of_hero = {
         name = "hero",
         description = {
            main = {
               text = "A label warns \"\"Can give a false sense of confidence,\"",
            },
         },
      },
      spellbook_of_weakness = {
         name = "weakness",
         description = {
            main = {
               text = "A battered tome,",
            },
         },
      },
      spellbook_of_elemental_scar = {
         name = "elemental scar",
         description = {
            main = {
               text = "A weathered and warped tome,",
            },
         },
      },
      potion_of_weakness = {
         name = "weakness",
         description = {
            main = {
               text = "A strangely colored potion,",
            },
         },
      },
      spellbook_of_holy_veil = {
         name = "holy veil",
         description = {
            main = {
               text = "A tome on religious spells,",
            },
         },
      },
      scroll_of_holy_veil = {
         name = "holy veil",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      rod_of_holy_light = {
         name = "holy light",
         description = {
            main = {
               text = "A gold plated rod,",
            },
         },
      },
      spellbook_of_holy_light = {
         name = "holy light",
         description = {
            main = {
               text = "A tome with a calming glow,",
            },
         },
      },
      spellbook_of_holy_rain = {
         name = "holy rain",
         description = {
            main = {
               text = "A slightly damp tome,",
            },
         },
      },
      scroll_of_holy_light = {
         name = "holy light",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_holy_rain = {
         name = "holy rain",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_mana = {
         name = "mana",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      rod_of_mana = {
         name = "mana",
         description = {
            main = {
               text = "A rod wrapped in dawn cloth,",
            },
         },
      },
      bottle_of_sulfuric = {
         name = "sulfuric",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "A clear odorless liquid,",
            },
         },
      },
      gem_cutter = {
         name = "gem cutter",
         description = {
            main = {
               text = "Some magical materials are just that hard to cut!",
            },
         },
      },
      material_box = {
         name = "material box",
         description = {
            main = {
               text = "A box filled with materials,",
            },
         },
      },
      scroll_of_gain_material = {
         name = "gain material",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      spellbook_of_nightmare = {
         name = "nightmare",
         description = {
            main = {
               text = "A tome that has an aura of dread,",
            },
         },
      },
      spellbook_of_knowledge = {
         name = "knowledge",
         description = {
            main = {
               text = "An insightful tome,",
            },
         },
      },
      scroll_of_knowledge = {
         name = "knowledge",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      cargo_rag_doll = {
         name = "rag doll",
         description = {
            main = {
               text = "A cargo of children's toys,",
            },
         },
      },
      cargo_barrel = {
         name = "barrel",
         description = {
            main = {
               text = "A cargo of barrels,",
            },
         },
      },
      cargo_piano = {
         name = "piano",
         description = {
            main = {
               text = "A cargo of pianos,",
            },
         },
      },
      cargo_rope = {
         name = "rope",
         description = {
            main = {
               text = "A cargo of rope,",
            },
         },
      },
      cargo_coffin = {
         name = "coffin",
         description = {
            main = {
               text = "A cargo of coffins,",
            },
         },
      },
      cargo_manboo = {
         name = "manboo",
         description = {
            main = {
               text = "A cargo of fish,",
            },
         },
      },
      cargo_grave = {
         name = "grave",
         description = {
            main = {
               text = "A cargo of grave materials,",
            },
         },
      },
      cargo_tuna_fish = {
         name = "tuna fish",
         description = {
            main = {
               text = "A cargo of fish,",
            },
         },
      },
      cargo_whisky = {
         name = "whisky",
         description = {
            main = {
               text = "A cargo of alcohol,",
            },
         },
      },
      cargo_noble_toy = {
         name = "noble toy",
         description = {
            main = {
               text = "A cargo of children's toys,",
            },
         },
      },
      cargo_inner_tube = {
         name = "inner tube",
         description = {
            main = {
               text = "A cargo of ship materials,",
            },
         },
      },
      spellbook_of_detect_objects = {
         name = "detect objects",
         description = {
            main = {
               text = "Makes you feel like a treasure hunter,",
            },
         },
      },
      scroll_of_detect_objects = {
         name = "detect objects",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      rod_of_uncurse = {
         name = "uncurse",
         description = {
            main = {
               text = "A rod wrapped in spirit cloth,",
            },
         },
      },
      red_treasure_machine = {
         name = "red treasure machine",
         description = {
            main = {
               text = "A treasure machine accepting rare coins,",
            },
         },
      },
      blue_treasure_machine = {
         name = "blue treasure machine",
         description = {
            main = {
               text = "A treasure machine accepting very rare coins,",
            },
         },
      },
      treasure_ball = {
         name = "treasure ball",
         description = {
            main = {
               text = "I'm sure there's something good inside,",
            },
         },
      },
      rare_treasure_ball = {
         name = "rare treasure ball",
         description = {
            main = {
               text = "This contains a rare treasure,",
            },
         },
      },
      vegetable_seed = {
         name = "vegetable seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      fruit_seed = {
         name = "fruit seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      herb_seed = {
         name = "herb seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      unknown_seed = {
         name = "unknown seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      artifact_seed = {
         name = "artifact seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      morgia = {
         name = "morgia",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      mareilon = {
         name = "mareilon",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      spenseweed = {
         name = "spenseweed",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      curaria = {
         name = "curaria",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      alraunia = {
         name = "alraunia",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      stomafillia = {
         name = "stomafillia",
         description = {
            main = {
               text = "A type of herb,",
            },
         },
      },
      sleeping_bag = {
         name = "sleeping bag",
         description = {
            main = {
               text = "Useful for camping and sleeping in moldy dungeons!",
            },
         },
      },
      potion_of_weaken_resistance = {
         name = "weaken resistance",
         description = {
            main = {
               text = "A label informs you \"\"can cause harmful side effects,\"",
            },
         },
      },
      scroll_of_growth = {
         name = "growth",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_faith = {
         name = "faith",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      potion_of_mutation = {
         name = "mutation",
         description = {
            main = {
               text = "Mutates your genetic makeup,",
            },
         },
      },
      potion_of_cure_mutation = {
         name = "cure mutation",
         description = {
            main = {
               text = "Cures mutated genes,",
            },
         },
      },
      spellbook_of_mutation = {
         name = "mutation",
         description = {
            main = {
               text = "This tome appears to have legs,",
            },
         },
      },
      banded_mail = {
         name = "banded mail",
         description = {
            main = {
               text = "A form of mail reinforced with leather,",
            },
         },
      },
      plate_mail = {
         name = "plate mail",
         description = {
            main = {
               text = "An armor forged by dwarves,",
            },
         },
      },
      ring_mail = {
         name = "ring mail",
         description = {
            main = {
               text = "Leather armor with metal rings sewn on,",
            },
         },
      },
      composite_mail = {
         name = "composite mail",
         description = {
            main = {
               text = "A sturdy armor,",
            },
         },
      },
      chain_mail = {
         name = "chain mail",
         description = {
            main = {
               text = "An armor made of small linked rings,",
            },
         },
      },
      pope_robe = {
         name = "pope robe",
         description = {
            main = {
               text = "A robe from ancient times that has an aura of peace,",
            },
         },
      },
      light_mail = {
         name = "light mail",
         description = {
            main = {
               text = "A mail made of leather with thin plating,",
            },
         },
      },
      coat = {
         name = "coat",
         description = {
            main = {
               text = "A coat often worn when cold,",
            },
         },
      },
      breast_plate = {
         name = "breast plate",
         description = {
            main = {
               text = "An armor designed to protect the chest,",
            },
         },
      },
      bulletproof_jacket = {
         name = "bulletproof jacket",
         description = {
            main = {
               text = "Protects from more than just bullets,",
            },
         },
      },
      gloves = {
         name = "gloves",
         description = {
            main = {
               text = "A thick pair of gloves,",
            },
         },
      },
      plate_gauntlets = {
         name = "plate gauntlets",
         description = {
            main = {
               text = "A pair of plated gauntlets,",
            },
         },
      },
      light_gloves = {
         name = "light gloves",
         description = {
            main = {
               text = "A pair of gloves with a soft inner lining,",
            },
         },
      },
      composite_gauntlets = {
         name = "composite gauntlets",
         description = {
            main = {
               text = "A pair of gauntlets made out of a composite mesh,",
            },
         },
      },
      small_shield = {
         name = "small shield",
         description = {
            main = {
               text = "A small reinforced shield,",
            },
         },
      },
      round_shield = {
         name = "round shield",
         description = {
            main = {
               text = "Used to block hostile weapons,",
            },
         },
      },
      shield = {
         name = "shield",
         description = {
            main = {
               text = "A shield with a crest,",
            },
         },
      },
      large_shield = {
         name = "large shield",
         description = {
            main = {
               text = "A large circular shield,",
            },
         },
      },
      kite_shield = {
         name = "kite shield",
         description = {
            main = {
               text = "A shield shaped like a kite,",
            },
         },
      },
      tower_shield = {
         name = "tower shield",
         description = {
            main = {
               text = "It's like your very on portable wall!",
            },
         },
      },
      shoes = {
         name = "shoes",
         description = {
            main = {
               text = "A pair of shoes,",
            },
         },
      },
      boots = {
         name = "boots",
         description = {
            main = {
               text = "A standard pair of boots,",
            },
         },
      },
      tight_boots = {
         name = "tight boots",
         description = {
            main = {
               text = "A tight fitting pair of boots,",
            },
         },
      },
      armored_boots = {
         name = "armored boots",
         description = {
            main = {
               text = "A pair of boots with armored plating,",
            },
         },
      },
      composite_girdle = {
         name = "composite girdle",
         description = {
            main = {
               text = "A girdle with straps designed to keep loose clothing out of the way,",
            },
         },
      },
      plate_girdle = {
         name = "plate girdle",
         description = {
            main = {
               text = "A reinforced girdle,",
            },
         },
      },
      armored_cloak = {
         name = "armored cloak",
         description = {
            main = {
               text = "A reinforced cloak designed for protection,",
            },
         },
      },
      cloak = {
         name = "cloak",
         description = {
            main = {
               text = "A heavy cloak designed for travel,",
            },
         },
      },
      feather_hat = {
         name = "feather hat",
         description = {
            main = {
               text = "A hat with a feather often worn by nobles,",
            },
         },
      },
      heavy_helm = {
         name = "heavy helm",
         description = {
            main = {
               text = "A helm designed for good protection,",
            },
         },
      },
      knight_helm = {
         name = "knight helm",
         description = {
            main = {
               text = "A helm made for knights,",
            },
         },
      },
      helm = {
         name = "helm",
         description = {
            main = {
               text = "A standard helm,",
            },
         },
      },
      composite_helm = {
         name = "composite helm",
         description = {
            main = {
               text = "A very sturdy helm,",
            },
         },
      },
      peridot = {
         name = "peridot",
         description = {
            main = {
               text = "A gem attached to a neck chain,",
            },
         },
      },
      talisman = {
         name = "talisman",
         description = {
            main = {
               text = "A talisman said to ward off evil,",
            },
         },
      },
      neck_guard = {
         name = "neck guard",
         description = {
            main = {
               text = "Sometimes the only thing between an enemy sword and your neck,",
            },
         },
      },
      charm = {
         name = "charm",
         description = {
            main = {
               text = "A good luck charm,",
            },
         },
      },
      bejeweled_amulet = {
         name = "bejeweled amulet",
         description = {
            main = {
               text = "An amulet that shows one's wealth",
            },
         },
      },
      engagement_amulet = {
         name = "engagement amulet",
         description = {
            main = {
               text = "An amulet that shows one's love,",
            },
         },
      },
      composite_ring = {
         name = "composite ring",
         description = {
            main = {
               text = "A ring made out of composite,",
            },
         },
      },
      armored_ring = {
         name = "armored ring",
         description = {
            main = {
               text = "Protects a portion of your finger,",
            },
         },
      },
      ring = {
         name = "ring",
         description = {
            main = {
               text = "A plain ring,",
            },
         },
      },
      engagement_ring = {
         name = "engagement ring",
         description = {
            main = {
               text = "A ring given to show one's intent to marry,",
            },
         },
      },
      stethoscope = {
         name = "stethoscope",
         description = {
            main = {
               text = "A real one can be used to check your health,",
            },
         },
      },
      scroll_of_ally = {
         name = "ally",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      rod_of_domination = {
         name = "domination",
         description = {
            main = {
               text = "A rod made out of rubynus,",
            },
         },
      },
      spellbook_of_domination = {
         name = "domination",
         description = {
            main = {
               text = "A tome that seems to break your will,",
            },
         },
      },
      crossbow = {
         name = "crossbow",
         description = {
            main = {
               text = "A ranged weapon designed to shoot straight and pierce armor,",
            },
         },
      },
      bolt = {
         name = "bolt",
         description = {
            main = {
               text = "Standard equipment for hunting rabbits,",
            },
         },
      },
      spellbook_of_web = {
         name = "web",
         description = {
            main = {
               text = "You can swear you see spiders crawling over this tome out of the corner of your eye,",
            },
         },
      },
      rod_of_web = {
         name = "web",
         description = {
            main = {
               text = "A rod wrapped in silk,",
            },
         },
      },
      machine = {
         name = "machine",
         description = {
            main = {
               text = "Asserian technology,",
            },
         },
      },
      computer = {
         name = "computer",
         description = {
            main = {
               text = "Asserian computer technology,",
            },
         },
      },
      training_machine = {
         name = "training machine",
         description = {
            main = {
               text = "Asserian health equipment,",
            },
         },
      },
      camera = {
         name = "camera",
         description = {
            main = {
               text = "Asserian photography technology,",
            },
         },
      },
      microwave_oven = {
         name = "microwave oven",
         description = {
            main = {
               text = "Asserian cooking technolog",
            },
         },
      },
      server = {
         name = "server",
         description = {
            main = {
               text = "Asserian computer technology,",
            },
         },
      },
      storage = {
         name = "storage",
         description = {
            main = {
               text = "You do not know how to open it,",
            },
         },
      },
      trash_can = {
         name = "trash can",
         description = {
            main = {
               text = "North Tyris laws make it illegal to search,",
            },
         },
      },
      chip = {
         name = "chip",
         description = {
            main = {
               text = "Asserian computer technology,",
            },
         },
      },
      blank_disc = {
         name = "blank disc",
         description = {
            main = {
               text = "Asserian computer technology,",
            },
         },
      },
      shot_gun = {
         name = "shot gun",
         description = {
            main = {
               text = "Made by Cyber Dome In",
            },
         },
      },
      pop_corn = {
         name = "pop corn",
         description = {
            main = {
               text = "Buttery popcorn,",
            },
         },
      },
      fried_potato = {
         name = "fried potato",
         description = {
            main = {
               text = "Greasy fries!",
            },
         },
      },
      cyber_snack = {
         name = "cyber snack",
         description = {
            main = {
               text = "potato chips,",
            },
         },
      },
      scroll_of_inferior_material = {
         name = "inferior material",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_change_material = {
         name = "change material",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_superior_material = {
         name = "superior material",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      figurine = {
         name = "figurine",
         description = {
            main = {
               text = "A statue of a creature,",
            },
         },
      },
      card = {
         name = "card",
         description = {
            main = {
               text = "A card of a creature,",
            },
         },
      },
      little_sisters_diary = {
         name = "little sister's diary",
         description = {
            main = {
               text = "A diary written in with crayon,",
            },
         },
      },
      scroll_of_enchant_weapon = {
         name = "enchant weapon",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_greater_enchant_weapon = {
         name = "greater enchant weapon",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_enchant_armor = {
         name = "enchant armor",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      scroll_of_greater_enchant_armor = {
         name = "greater enchant armor",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      heir_trunk = {
         name = "heir trunk",
         description = {
            main = {
               text = "A magical trunk that can connect to \"\"fourth dimensional inheritance storage\"\" for a small fee,",
            },
         },
      },
      deed_of_heirship = {
         name = "heirship",
         description = {
            main = {
               text = "A deed of heirship,",
            },
         },
      },
      laser_gun = {
         name = "laser gun",
         description = {
            main = {
               text = "A remnant of ancient times,",
            },
         },
      },
      energy_cell = {
         name = "energy cell",
         description = {
            main = {
               text = "Do not tamper with lens,",
            },
         },
      },
      rail_gun = {
         name = "<Rail Gun>",
         unidentified_name = "gun of genocide",
      },
      scroll_of_recharge = {
         name = "recharge",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      bottle_of_water = {
         name = "water",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "A bottle of pure water,",
            },
         },
      },
      rod_of_change_creature = {
         name = "change creature",
         description = {
            main = {
               text = "A rod made out of ether,",
            },
         },
      },
      rod_of_alchemy = {
         name = "alchemy",
         description = {
            main = {
               text = "A rod made out of emerald,",
            },
         },
      },
      bottle_of_dye = {
         name = "dye",
         description = {
            main = {
               text = "Expertly made dye that works on most materials,",
            },
         },
      },
      wing = {
         name = "wing",
         description = {
            main = {
               text = "A marvel of genetic engineering,",
            },
         },
      },
      deed_of_museum = {
         name = "museum",
         description = {
            main = {
               text = "A deed for a museum,",
            },
         },
      },
      deed_of_shop = {
         name = "shop",
         description = {
            main = {
               text = "A deed for a shop,",
            },
         },
      },
      tree_of_beech = {
         name = "beech",
         description = {
            main = {
               text = "A type of tree,",
            },
         },
      },
      tree_of_cedar = {
         name = "cedar",
         description = {
            main = {
               text = "A type of tree with a scented wood,",
            },
         },
      },
      tree_of_fruitless = {
         name = "fruitless",
         description = {
            main = {
               text = "A tree with no fruits,",
            },
         },
      },
      tree_of_fruits = {
         name = "fruits",
         description = {
            main = {
               text = "A fruit tree,",
            },
         },
      },
      dead_tree = {
         name = "dead tree",
         description = {
            main = {
               text = "A tree that has died from bad weather,",
            },
         },
      },
      tree_of_zelkova = {
         name = "zelkova",
         description = {
            main = {
               text = "A type of tree,",
            },
         },
      },
      tree_of_palm = {
         name = "palm",
         description = {
            main = {
               text = "A tree found in warm climates,",
            },
         },
      },
      tree_of_ash = {
         name = "ash",
         description = {
            main = {
               text = "A type of tree,",
            },
         },
      },
      furnance = {
         name = "furnance",
         description = {
            main = {
               text = "Some furnances are used to heat an area and others are used for metalwork,",
            },
         },
      },
      fireplace = {
         name = "fireplace",
         description = {
            main = {
               text = "Used to heat a house,",
            },
         },
      },
      stove = {
         name = "stove",
         description = {
            main = {
               text = "A stove useful for cooking food,",
            },
         },
      },
      giant_foliage_plant = {
         name = "giant foliage plant",
         description = {
            main = {
               text = "A plant used for decoration,",
            },
         },
      },
      big_table = {
         name = "big table",
      },
      painting_of_madam = {
         name = "madam",
         description = {
            main = {
               text = "A copy of a painting by a famous Yerles artist,",
            },
         },
      },
      painting_of_landscape = {
         name = "landscape",
         description = {
            main = {
               text = "A painting of a landscape,",
            },
         },
      },
      painting_of_sunflower = {
         name = "sunflower",
         description = {
            main = {
               text = "A painting of a sunflower,",
            },
         },
      },
      statue_of_cat = {
         name = "cat",
         description = {
            main = {
               text = "A painting of a cat,",
            },
         },
      },
      black_crystal = {
         name = "black crystal",
         description = {
            main = {
               text = "A black crystal,",
            },
         },
      },
      snow_man = {
         name = "snow man",
         description = {
            main = {
               text = "A snow man,",
            },
         },
      },
      deed_of_farm = {
         name = "farm",
         description = {
            main = {
               text = "A deed for a farm,",
            },
         },
      },
      deed_of_storage_house = {
         name = "storage house",
         description = {
            main = {
               text = "A deed for a storage house,",
            },
         },
      },
      disc = {
         name = "disc",
         description = {
            main = {
               text = "A message is written on it saying \"\"Please do not throw,\"",
            },
         },
      },
      rod_of_wall_creation = {
         name = "wall creation",
         description = {
            main = {
               text = "A wall made out of obsidian,",
            },
         },
      },
      spellbook_of_wall_creation = {
         name = "wall creation",
         description = {
            main = {
               text = "This tome seems to be heavier than it is,",
            },
         },
      },
      salary_chest = {
         name = "salary chest",
         description = {
            main = {
               text = "A salary chest for freelance employment,",
            },
         },
      },
      spellbook_of_healing_rain = {
         name = "healing rain",
         description = {
            main = {
               text = "A slightly damp tome,",
            },
         },
      },
      scroll_of_healing_rain = {
         name = "healing rain",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      spellbook_of_healing_hands = {
         name = "healing hands",
         description = {
            main = {
               text = "A handy tome,",
            },
         },
      },
      rod_of_healing_hands = {
         name = "healing hands",
         description = {
            main = {
               text = "A silver plated rod,",
            },
         },
      },
      feather = {
         name = "feather",
         description = {
            main = {
               text = "A product of magic,",
            },
         },
      },
      gem_seed = {
         name = "gem seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      magical_seed = {
         name = "magical seed",
         description = {
            main = {
               text = "A type of seed,",
            },
         },
      },
      shelter = {
         name = "shelter",
         description = {
            main = {
               text = "This kit can be used to build a shelter that protects you from the weather!",
            },
         },
      },
      seven_league_boots = {
         name = "seven league boots",
         description = {
            main = {
               text = "Rare boots magically enhanced to allow faster travel,",
            },
         },
      },
      vindale_cloak = {
         name = "vindale cloak",
         description = {
            main = {
               text = "made in vindale",
            },
         },
      },
      aurora_ring = {
         name = "aurora ring",
         description = {
            main = {
               text = "Protects you from bad weather,",
            },
         },
      },
      potion_of_cure_corruption = {
         name = "cure corruption",
         description = {
            main = {
               text = "A label reads \"\"For use in curing harmful diseases only\"",
            },
         },
      },
      masters_delivery_chest = {
         name = "master's delivery chest",
         unidentified_name = "delivery chest",
      },
      shop_strongbox = {
         name = "shop strongbox",
         description = {
            main = {
               text = "A chest containing your shop's profit",
            },
         },
      },
      register = {
         name = "register",
         description = {
            main = {
               text = "Needed to run a shop,",
            },
         },
      },
      textbook = {
         name = "textbook",
         unidentified_name = "book",
         description = {
            main = {
               text = "A textbook used to study a trade,",
            },
         },
      },
      spellbook_of_acid_ground = {
         name = "acid ground",
         description = {
            main = {
               text = "The pages of this tome are tinted green,",
            },
         },
      },
      rod_of_acid_ground = {
         name = "acid ground",
         description = {
            main = {
               text = "A mithril rod,",
            },
         },
      },
      acidproof_liquid = {
         name = "acidproof liquid",
         description = {
            main = {
               text = "Use on an item to protect it from acid,",
            },
         },
      },
      fireproof_blanket = {
         name = "fireproof blanket",
         description = {
            main = {
               text = "Produced to protect the user from hot areas while sleeping but has found more use protecting one's equipment!",
            },
         },
      },
      coldproof_blanket = {
         name = "coldproof blanket",
         description = {
            main = {
               text = "Produced to protect from cold areas while sleeping but has found more use protecting one's equipment!",
            },
         },
      },
      spellbook_of_fire_wall = {
         name = "fire wall",
         description = {
            main = {
               text = "This tome is warm,",
            },
         },
      },
      rod_of_fire_wall = {
         name = "fire wall",
         description = {
            main = {
               text = "A platinum rod,",
            },
         },
      },
      jerky = {
         name = "jerky",
         description = {
            main = {
               text = "Dried out travel rations,",
            },
         },
      },
      deed_of_ranch = {
         name = "ranch",
         description = {
            main = {
               text = "A deed for a ranch,",
            },
         },
      },
      egg = {
         name = "egg",
         description = {
            main = {
               text = "This egg would taste better cooked,",
            },
         },
      },
      bottle_of_milk = {
         name = "milk",
         description = {
            main = {
               text = "Milk",
            },
         },
      },
      shit = {
         name = "shit",
         description = {
            main = {
               text = "Stinky...,,",
            },
         },
      },
      playback_disc = {
         name = "playback disc",
         description = {
            main = {
               text = "A mysterious disc that seems to play your memories,",
            },
         },
      },
      molotov = {
         name = "molotov",
         description = {
            main = {
               text = "A label on the bottle states \"\"Light before throwing\"\",",
            },
         },
      },
      kitty_bank = {
         name = "kitty bank",
         description = {
            main = {
               text = "Please don't break me,..., Nyu?",
            },
         },
      },
      freezer = {
         name = "freezer",
         description = {
            main = {
               text = "A freezer to keep your food from spoiling,",
            },
         },
      },
      modern_rack = {
         name = "modern rack",
      },
      rod_of_make_door = {
         name = "make door",
         description = {
            main = {
               text = "A pearl tipped rod,",
            },
         },
      },
      spellbook_of_make_door = {
         name = "make door",
         description = {
            main = {
               text = "This tome is yellowed and warped,",
            },
         },
      },
      torch = {
         name = "torch",
         description = {
            main = {
               text = "This enchanted torch will never burn out,",
            },
         },
      },
      candle = {
         name = "candle",
         description = {
            main = {
               text = "A creepy set of candles,",
            },
         },
      },
      fancy_lamp = {
         name = "fancy lamp",
         description = {
            main = {
               text = "A lamp from Asseria,",
            },
         },
      },
      modern_lamp_a = {
         name = "modern lamp",
         description = {
            main = {
               text = "An Asserian lamp,",
            },
         },
      },
      handful_of_snow = {
         name = "snow",
         description = {
            main = {
               text = "Some snow,",
            },
         },
      },
      tree_of_naked = {
         name = "naked",
         description = {
            main = {
               text = "A type of tree,",
            },
         },
      },
      tree_of_fir = {
         name = "fir",
         description = {
            main = {
               text = "A type of tree,",
            },
         },
      },
      snow_scarecrow = {
         name = "snow scarecrow",
         description = {
            main = {
               text = "Is there a need for one in the snow?",
            },
         },
      },
      mini_snow_man = {
         name = "mini snow man",
         description = {
            main = {
               text = "A small snowman,",
            },
         },
      },
      snow_barrel = {
         name = "snow barrel",
         description = {
            main = {
               text = "A barrel with snow on it,",
            },
         },
      },
      modern_lamp_b = {
         name = "modern lamp",
         description = {
            main = {
               text = "An Asserian lamp,",
            },
         },
      },
      statue_of_holy_cross = {
         name = "holy cross",
         description = {
            main = {
               text = "A holy symbol from ancient times,",
            },
         },
      },
      pillar = {
         name = "pillar",
      },
      stained_glass_window = {
         name = "stained glass window",
         description = {
            main = {
               text = "A expensive stained glass window often used to decorate chapels,",
            },
         },
      },
      cargo_christmas_tree = {
         name = "christmas tree",
         description = {
            main = {
               text = "A cargo of pine trees,",
            },
         },
      },
      cargo_snow_man = {
         name = "snow man",
         description = {
            main = {
               text = "A cargo of snow men,",
            },
         },
      },
      christmas_tree = {
         name = "christmas tree",
         description = {
            main = {
               text = "A tree used for an ancient holiday,",
            },
         },
      },
      giants_shackle = {
         name = "giant's shackle",
         unidentified_name = "shakle",
         description = {
            main = {
               text = "I would not want to be attached to those!",
            },
         },
      },
      empty_bottle = {
         name = "empty bottle",
         unidentified_name = "empty bottle",
         description = {
            main = {
               text = "An empty bottle,",
            },
         },
      },
      holy_well = {
         name = "holy well",
         description = {
            main = {
               text = "A note reads \"\"Please do not taint the town's water supply\"",
            },
         },
      },
      presidents_chair = {
         name = "president's chair",
         unidentified_name = "glory chair",
         description = {
            main = {
               text = "A rare chair made for Asseria's elite,",
            },
         },
      },
      green_plant = {
         name = "green plant",
         description = {
            main = {
               text = "A plant used for decoration,",
            },
         },
      },
      money_tree = {
         name = "money tree",
         description = {
            main = {
               text = "Money grows on this tree,",
            },
         },
      },
      barbecue_set = {
         name = "barbecue set",
         description = {
            main = {
               text = "An amazing set of cooking tools,",
            },
         },
      },
      giant_cactus = {
         name = "giant cactus",
         description = {
            main = {
               text = "A decorative cactus,",
            },
         },
      },
      square_window = {
         name = "square window",
      },
      window = {
         name = "window",
      },
      triangle_plant = {
         name = "triangle plant",
      },
      house_board = {
         name = "house board",
      },
      nice_window = {
         name = "nice window",
      },
      kings_bed = {
         name = "king's bed",
      },
      flower_arch = {
         name = "flower arch",
      },
      bill = {
         name = "bill",
         unidentified_name = "lousy paper",
      },
      tax_masters_tax_box = {
         name = "tax master's tax box",
         unidentified_name = "tax box",
         description = {
            main = {
               text = "Pay your taxes here,",
            },
         },
      },
      bait = {
         name = "bait",
         description = {
            main = {
               text = "Bait for a fishing pole,",
            },
         },
      },
      fish_a = {
         name = "",
      },
      fish_b = {
         name = "",
      },
      love_potion = {
         name = "love potion",
         unidentified_name = "clear liquid",
         description = {
            main = {
               text = "A label reads \"\"To be used only on livestock\"",
            },
         },
      },
      treasure_map = {
         name = "treasure map",
         unidentified_name = "crumbling paper",
         description = {
            main = {
               text = "A map from sources unknown that leads to treasure,",
            },
         },
      },
      small_medal = {
         name = "small medal",
         unidentified_name = "silver coin",
         description = {
            main = {
               text = "Dwarven currency rarely found outside of their homeland,",
            },
         },
      },
      cat_sisters_diary = {
         name = "cat sister's diary",
         description = {
            main = {
               text = "Nyo reading!",
            },
         },
      },
      girls_diary = {
         name = "girl's diary",
         description = {
            main = {
               text = "A girl's diary",
            },
         },
      },
      shrine_gate = {
         name = "shrine gate",
         unidentified_name = "foreign gate",
      },
      bottle_of_hermes_blood = {
         name = "hermes blood",
         description = {
            main = {
               text = "A rare item that increases your speed,",
            },
         },
      },
      sages_helm = {
         name = "<Sage's Helm>",
         unidentified_name = "shining helm",
      },
      spellbook_of_incognito = {
         name = "incognito",
         description = {
            main = {
               text = "A tome whose words often mean another thing,",
            },
         },
      },
      disguise_set = {
         name = "disguise set",
         description = {
            main = {
               text = "Disguise kit - with instructions,",
            },
         },
      },
      material_kit = {
         name = "material kit",
         description = {
            main = {
               text = "This hard to produce item can change the material of many items!",
            },
         },
      },
      moon_gate = {
         name = "moon gate",
      },
      flying_scroll = {
         name = "flying scroll",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      panty = {
         name = "panty",
         description = {
            main = {
               text = "A fitting weapon for those who fight dirty,",
            },
         },
      },
      leash = {
         name = "leash",
         description = {
            main = {
               text = "A leather leash for your pets!",
            },
         },
      },
      mine = {
         name = "mine",
         description = {
            main = {
               text = "The warning label reads \"\"Do not step on mine when armed\"",
            },
         },
      },
      lockpick = {
         name = "lockpick",
         description = {
            main = {
               text = "A questionable item not intended for public use,",
            },
         },
      },
      skeleton_key = {
         name = "skeleton key",
         unidentified_name = "white key",
         description = {
            main = {
               text = "An item stolen from a legendary locksmith,",
            },
         },
      },
      scroll_of_escape = {
         name = "escape",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      happy_apple = {
         name = "happy apple",
         unidentified_name = "mysterious apple",
         description = {
            main = {
               text = "A magical fruit said to come from Ehekatl's garden,",
            },
         },
      },
      unicorn_horn = {
         name = "unicorn horn",
         description = {
            main = {
               text = "Known for it's amazing healing properties unicorn horns are also a reminder of how Elonians have driven the species into near extinction,,",
            },
         },
      },
      cooler_box = {
         name = "cooler box",
         unidentified_name = "chilly box",
         description = {
            main = {
               text = "A cooler box",
            },
         },
      },
      hero_cheese = {
         name = "hero cheese",
         unidentified_name = "mysterious cheese",
         description = {
            main = {
               text = "A type of cheese eaten by heros",
            },
         },
      },
      rice_barrel = {
         name = "rice barrel",
         description = {
            main = {
               text = "A barrel for holding rice,",
            },
         },
      },
      eastern_bed = {
         name = "eastern bed",
         description = {
            main = {
               text = "A useful bed of eastern design,",
            },
         },
      },
      decorated_window = {
         name = "decorated window",
      },
      king_drawer = {
         name = "king drawer",
         description = {
            main = {
               text = "It even has a book shelf!",
            },
         },
      },
      menu_board = {
         name = "menu board",
         description = {
            main = {
               text = "A menu for a restaurant,",
            },
         },
      },
      black_board = {
         name = "black board",
         description = {
            main = {
               text = "Technophiles use this to teach,",
            },
         },
      },
      sofa = {
         name = "sofa",
         description = {
            main = {
               text = "A finely crafted sofa,",
            },
         },
      },
      flowerbed = {
         name = "flowerbed",
         description = {
            main = {
               text = "A beautiful bed of flowers,",
            },
         },
      },
      toilet = {
         name = "toilet",
         description = {
            main = {
               text = "You can drink from it but I don't recommend it,,,",
            },
         },
      },
      craft_cupboard = {
         name = "craft cupboard",
         description = {
            main = {
               text = "A place to store your fine china,",
            },
         },
      },
      sink = {
         name = "sink",
         description = {
            main = {
               text = "Has its own water filtration system,",
            },
         },
      },
      junk = {
         name = "junk",
         description = {
            main = {
               text = "One man's junk is another man's treasure!",
            },
         },
      },
      double_bed = {
         name = "double bed",
      },
      eastern_lamp = {
         name = "eastern lamp",
      },
      eastern_window = {
         name = "eastern window",
      },
      chochin = {
         name = "chochin",
      },
      partition = {
         name = "partition",
      },
      spellbook_of_darkness_arrow = {
         name = "darkness arrow",
         description = {
            main = {
               text = "This tome seems to carefully bend light,",
            },
         },
      },
      dal_i_thalion = {
         name = "<Dal-i-thalion>",
         unidentified_name = "light shoes",
      },
      magic_fruit = {
         name = "magic fruit",
         unidentified_name = "rare fruit",
         description = {
            main = {
               text = "A type of fruit,",
            },
         },
      },
      monster_heart = {
         name = "monster heart",
         unidentified_name = "beating heart",
         description = {
            main = {
               text = "Helps to tame monsters,",
            },
         },
      },
      speed_ring = {
         name = "speed ring",
         description = {
            main = {
               text = "A rare magical ring that increases your speed,",
            },
         },
      },
      statue_of_opatos = {
         name = "Opatos",
         unidentified_name = "god",
         description = {
            main = {
               text = "You feel the ground shake slightly at this statue,",
            },
         },
      },
      statue_of_lulwy = {
         name = "Lulwy",
         unidentified_name = "goddess",
         description = {
            main = {
               text = "A beautiful statue of a winged goddess,",
            },
         },
      },
      sisters_love_fueled_lunch = {
         name = "sister's love fueled lunch",
         description = {
            main = {
               text = "It even has cookies!",
            },
         },
      },
      book_of_rachel = {
         name = "book",
         description = {
            main = {
               text = "A book decorated with pictures,",
            },
         },
      },
      cargo_art = {
         name = "art",
         description = {
            main = {
               text = "A cargo of art supplies,",
            },
         },
      },
      cargo_canvas = {
         name = "canvas",
         description = {
            main = {
               text = "A cargo of canvas,",
            },
         },
      },
      nuclear_bomb = {
         name = "nuclear bomb",
         unidentified_name = "very dangerous bomb",
         description = {
            main = {
               text = "A horrifying weapon of destruction from ancient times,",
            },
         },
      },
      secret_treasure = {
         name = "secret treasure",
         unidentified_name = "mysterious jewel",
         description = {
            main = {
               text = "This strange object seems to slightly shift its shape,",
            },
         },
      },
      wind_bow = {
         name = "<Wind Bow>",
         unidentified_name = "bow surrounded by wind",
      },
      winchester_premium = {
         name = "<Winchester Premium>",
         unidentified_name = "ancient shot gun",
      },
      kumiromi_scythe = {
         name = "<Kumiromi Scythe>",
         unidentified_name = "harvest scythe",
      },
      elemental_staff = {
         name = "<Elemental Staff>",
         unidentified_name = "elemental staff",
      },
      holy_lance = {
         name = "<Holy Lance>",
         unidentified_name = "holy lance",
      },
      lucky_dagger = {
         name = "<Lucky Dagger>",
         unidentified_name = "thin dagger",
      },
      gaia_hammer = {
         name = "<Gaia Hammer>",
         unidentified_name = "giant hammer",
      },
      lulwys_gem_stone_of_god_speed = {
         name = "god speed",
         unidentified_name = "heavenly jewel",
      },
      jures_gem_stone_of_holy_rain = {
         name = "holy rain",
         unidentified_name = "heavenly jewel",
      },
      kumiromis_gem_stone_of_rejuvenation = {
         name = "rejuvenation",
         unidentified_name = "heavenly jewel",
      },
      gem_stone_of_mani = {
         name = "Mani",
         unidentified_name = "strange jewel",
      },
      gene_machine = {
         name = "gene machine",
         unidentified_name = "freaky machine",
      },
      monster_ball = {
         name = "monster ball",
         description = {
            main = {
               text = "A strange item invented by a mad scientist...,",
            },
         },
      },
      statue_of_jure = {
         name = "Jure",
         unidentified_name = "goddess",
      },
      ancient_book = {
         name = "ancient book",
         description = {
            main = {
               text = "A book written in a dead language,",
            },
         },
      },
      iron_maiden = {
         name = "iron maiden",
         description = {
            main = {
               text = "A device of pure pain!",
            },
         },
      },
      guillotine = {
         name = "guillotine",
         description = {
            main = {
               text = "You are sure to get ahead in life with one of these!",
            },
         },
      },
      pan_flute = {
         name = "pan flute",
         description = {
            main = {
               text = "A type of instrument designed after (but larger than) fairy made flutes,",
            },
         },
      },
      lute = {
         name = "lute",
         description = {
            main = {
               text = "A lute is a common musical instrument among bards,",
            },
         },
      },
      harmonica = {
         name = "harmonica",
         description = {
            main = {
               text = "A harmonica commonly found in Culdia,",
            },
         },
      },
      harp = {
         name = "harp",
         description = {
            main = {
               text = "An expertly crafted harp favored by the Erea of Vindale,",
            },
         },
      },
      eastern_partition = {
         name = "eastern partition",
      },
      axe_of_destruction = {
         name = "<Axe of Destruction>",
         unidentified_name = "giant axe",
      },
      spellbook_of_magic_ball = {
         name = "magic ball",
         description = {
            main = {
               text = "A tome that teaches how to manipulate magic energy by sheer force of will, ",
            },
         },
      },
      spellbook_of_magic_laser = {
         name = "magic laser",
         description = {
            main = {
               text = "A tome that teaches how to focus magic energy",
            },
         },
      },
      potion_of_salt_solution = {
         name = "salt solution",
         description = {
            main = {
               text = "Some salt,",
            },
         },
      },
      little_ball = {
         name = "little ball",
         unidentified_name = "mechanical ball",
         description = {
            main = {
               text = "This ball gives you unique powers...",
            },
         },
      },
      town_book = {
         name = "town book",
      },
      deck = {
         name = "deck",
         description = {
            main = {
               text = "A deck of card'",
            },
         },
      },
      rabbits_tail = {
         name = "rabbit's tail",
         unidentified_name = "fluffy tail",
         description = {
            main = {
               text = "A tail said to bring luck,",
            },
         },
      },
      whistle = {
         name = "whistle",
         description = {
            main = {
               text = "Useful for waking people up or just playing pranks,",
            },
         },
      },
      vomit = {
         name = "vomit",
         description = {
            main = {
               text = "Why did you pick this up?,,,",
            },
         },
      },
      beggars_pendant = {
         name = "<Beggar's Pendant>",
         unidentified_name = "dirty pendant",
      },
      potion_of_descent = {
         name = "descent",
         description = {
            main = {
               text = "A strange potion,",
            },
         },
      },
      stradivarius = {
         name = "<Stradivarius>",
         unidentified_name = "elegant string",
         description = {
            main = {
               text = "A legendary instrument,",
            },
         },
      },
      book_of_resurrection = {
         name = "resurrection",
         description = {
            main = {
               text = "A book said to hold the secrets of life itself,",
            },
         },
      },
      scroll_of_contingency = {
         name = "contingency",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      spellbook_of_contingency = {
         name = "contingency",
         description = {
            main = {
               text = "An ancient tome,",
            },
         },
      },
      potion_of_evolution = {
         name = "evolution",
         description = {
            main = {
               text = "You say it's evolution?",
            },
         },
      },
      deed_of_dungeon = {
         name = "dungeon",
      },
      shuriken = {
         name = "shuriken",
         description = {
            main = {
               text = "A Hira-Shuriken,",
            },
         },
      },
      grenade = {
         name = "grenade",
         description = {
            main = {
               text = "Made by Cyber Dome In",
            },
         },
      },
      secret_experience_of_kumiromi = {
         name = "Kumiromi",
         unidentified_name = "strange jewel",
      },
      vanilla_rock = {
         name = "<Vanilla Rock>",
         unidentified_name = "shining rock",
      },
      secret_experience_of_lomias = {
         name = "Lomias",
         unidentified_name = "strange jewel",
      },
      shenas_panty = {
         name = "<Shena's Panty>",
         unidentified_name = "scentful panty",
      },
      claymore_unique = {
         name = "<Claymore>",
         unidentified_name = "brutish sword",
      },
      happy_bed = {
         name = "happy bed",
         description = {
            main = {
               text = "It is said that you will sleep better in one of these",
            },
         },
      },
      statue_of_ehekatl = {
         name = "Ehekatl",
         unidentified_name = "goddess",
      },
      arbalest = {
         name = "<Arbalest>",
         unidentified_name = "purple necklace",
      },
      twin_edge = {
         name = "<Twin Edge>",
         unidentified_name = "yellow necklace",
      },
      music_ticket = {
         name = "music ticket",
         unidentified_name = "some kind of ticket",
         description = {
            main = {
               text = "Tickets given out to promising musicians,",
            },
         },
      },
      kill_kill_piano = {
         name = "<Kill Kill Piano>",
         unidentified_name = "heavy piano",
      },
      alud = {
         name = "<Al'ud>",
         unidentified_name = "tough lute",
      },
      shield_of_thorn = {
         name = "<Shield of Thorn>",
         unidentified_name = "tingling shield",
      },
      crimson_plate = {
         name = "<Crimson Plate>",
         unidentified_name = "red girdle",
      },
      gift = {
         name = "gift",
         description = {
            main = {
               text = "It's hard to open,",
            },
         },
      },
      token_of_friendship = {
         name = "friendship",
         unidentified_name = "crumbling paper",
         description = {
            main = {
               text = "A token given only to friends,",
            },
         },
      },
      spellbook_of_4_dimensional_pocket = {
         name = "4 dimensional pocket",
         description = {
            main = {
               text = "A tome on alternate dimension",
            },
         },
      },
      spellbook_of_harvest = {
         name = "harvest",
         description = {
            main = {
               text = "A tome on secret form's of magical alchemy,",
            },
         },
      },
      sand_bag = {
         name = "sand bag",
         description = {
            main = {
               text = "Attach your own punching bag!",
            },
         },
      },
      small_gamble_chest = {
         name = "small gamble chest",
         description = {
            main = {
               text = "Popular among gamblers,",
            },
         },
      },
      scythe = {
         name = "scythe",
         description = {
            main = {
               text = "A farmer's tool that has largely replaced sickles,",
            },
         },
      },
      fireproof_liquid = {
         name = "fireproof liquid",
         description = {
            main = {
               text = "Use on an item to protect it from fire,",
            },
         },
      },
      scroll_of_name = {
         name = "name",
         description = {
            main = {
               text = "A magical scroll with arcane writing,",
            },
         },
      },
      fortune_cookie = {
         name = "fortune cookie",
         description = {
            main = {
               text = "Will tell you your fortune,",
            },
         },
      },
      frisias_tail = {
         name = "<Frisia's Tail>",
         unidentified_name = "cat's tail",
      },
      unknown_shell = {
         name = "<Unknown Shell>",
         unidentified_name = "beautiful shell",
      },
      hiryu_to = {
         name = "<Hiryu-To>",
         unidentified_name = "rutilant katana",
      },
      license_of_the_void_explorer = {
         name = "the void explorer",
         unidentified_name = "strange paper",
         description = {
            main = {
               text = "This will allow you to explore the void that has been found recently in the south-west,",
            },
         },
      },
      plank_of_carneades = {
         name = "Carneades",
      },
      schrodingers_cat = {
         name = "Schrodinger's cat",
      },
      heart = {
         name = "heart",
      },
      tamers_whip = {
         name = "tamer's whip",
      },
      book_of_bokonon = {
         name = "Bokonon",
      },
      summoning_crystal = {
         name = "summoning crystal",
         unidentified_name = "beautiful stone",
      },
      statue_of_creator = {
         name = "Creator",
         unidentified_name = "fishy statue",
      },
      upstairs = {
         name = "upstairs",
      },
      downstairs = {
         name = "downstairs",
      },
      new_years_gift = {
         name = "new year's gift",
      },
      kotatsu = {
         name = "kotatsu",
      },
      daruma = {
         name = "daruma",
      },
      kagami_mochi = {
         name = "kagami mochi",
      },
      mochi = {
         name = "mochi",
      },
      five_horned_helm = {
         name = "<Five Horned Helm>",
         unidentified_name = "horned helmet",
      },
      mauser_c96_custom = {
         name = "<Mauser C96 Custom>",
         unidentified_name = "rusted pistol",
      },
      lightsabre = {
         name = "lightsabre",
      },
      garoks_hammer = {
         name = "Garok's hammer",
         unidentified_name = "master hammer",
      },
      goulds_piano = {
         name = "<Gould's Piano>",
         unidentified_name = "nondescriptive piano",
      },
      festival_wreath = {
         name = "festival wreath",
      },
      pedestal = {
         name = "pedestal",
      },
      counter = {
         name = "counter",
      },
      red_stall = {
         name = "red stall",
      },
      blue_stall = {
         name = "blue stall",
      },
      jures_body_pillow = {
         name = "Jure's body pillow",
      },
      new_years_decoration = {
         name = "new year's decoration",
      },
      miniature_tree = {
         name = "miniature tree",
      },
      bottle_of_soda = {
         name = "soda",
         unidentified_name = "clear liquid",
      },
      blue_capsule_drug = {
         name = "blue capsule drug",
         unidentified_name = "blue capsule",
      },
      tomato = {
         name = "tomato",
      },
      large_bookshelf = {
         name = "large bookshelf",
      },
      luxury_cabinet = {
         name = "luxury cabinet",
      },
      special_steamed_meat_bun = {
         name = "special steamed meat bun",
      },
      statue_of_kumiromi = {
         name = "Kumiromi",
         unidentified_name = "god",
      },
      statue_of_mani = {
         name = "Mani",
         unidentified_name = "god",
      },
      luxury_sofa = {
         name = "luxury sofa",
      },
      deer_head = {
         name = "deer head",
      },
      fur_carpet = {
         name = "fur carpet",
      },
      kitchen_knife = {
         name = "kitchen knife",
      },
      dish = {
         name = "dish",
      },
      recipe = {
         name = "recipe",
      },
      recipe_holder = {
         name = "recipe holder",
      },
      bottle_of_salt = {
         name = "salt",
      },
      sack_of_sugar = {
         name = "sugar",
      },
      puff_puff_bread = {
         name = "puff puff bread",
      },
      skull_bow = {
         name = "skull bow",
      },
      pot_for_testing = {
         name = "for testing",
         description = {
            main = {
               text = "dev item",
            },
         },
      },
      frying_pan_for_testing = {
         name = "for testing",
         description = {
            main = {
               text = "dev item",
            },
         },
      },
      dragon_slayer = {
         name = "<Dragon Slayer>",
         unidentified_name = "two-edged great sword",
         description = {
            main = {
               text = "dev item",
            },
         },
      },
      putitoro = {
         name = "putitoro",
         description = {
            main = {
               text = "dev item",
            },
         },
      },
   },
}
