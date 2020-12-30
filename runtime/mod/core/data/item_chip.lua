local data = require("core.data")

data.define_prototype("item_chip")
data.add(
   "core.item_chip",
   {
      empty = {
         integer_id = 0,
         source = {
            x = 0,
            y = 0,
         }
      },
      projectile_arrow = {
         integer_id = 1,
         source = {
            x = 48,
            y = 0,
         }
      },
      projectile_bullet = {
         integer_id = 2,
         source = {
            x = 96,
            y = 0,
         }
      },
      projectile_bolt = {
         integer_id = 3,
         source = {
            x = 144,
            y = 0,
         }
      },
      _4 = {
         integer_id = 4,
         source = {
            x = 192,
            y = 0,
         }
      },
      _5 = {
         integer_id = 5,
         source = {
            x = 240,
            y = 0,
         }
      },
      projectile_magic_arrow = {
         integer_id = 6,
         source = {
            x = 288,
            y = 0,
         }
      },
      particle_spark = {
         integer_id = 7,
         source = {
            x = 336,
            y = 0,
         }
      },
      particle_skull = {
         integer_id = 8,
         source = {
            x = 384,
            y = 0,
         }
      },
      particle_candle = {
         integer_id = 9,
         source = {
            x = 432,
            y = 0,
         }
      },
      particle_sweat = {
         integer_id = 10,
         source = {
            x = 480,
            y = 0,
         }
      },
      _11 = {
         integer_id = 11,
         source = {
            x = 528,
            y = 0,
         }
      },
      _12 = {
         integer_id = 12,
         source = {
            x = 576,
            y = 0,
         }
      },
      _13 = {
         integer_id = 13,
         source = {
            x = 624,
            y = 0,
         }
      },
      _14 = {
         integer_id = 14,
         source = {
            x = 672,
            y = 0,
         }
      },
      _15 = {
         integer_id = 15,
         source = {
            x = 720,
            y = 0,
         }
      },
      _16 = {
         integer_id = 16,
         source = {
            x = 768,
            y = 0,
         }
      },
      _17 = {
         integer_id = 17,
         source = {
            x = 816,
            y = 0,
         }
      },
      _18 = {
         integer_id = 18,
         source = {
            x = 864,
            y = 0,
         }
      },
      mef_slime = {
         integer_id = 19,
         animation = 2,
         source = {
            x = 912,
            y = 0,
         }
      },
      _20 = {
         integer_id = 20,
         source = {
            x = 960,
            y = 0,
         }
      },
      _21 = {
         integer_id = 21,
         source = {
            x = 1008,
            y = 0,
         }
      },
      mef_water = {
         integer_id = 22,
         source = {
            x = 1056,
            y = 0,
         }
      },
      _23 = {
         integer_id = 23,
         source = {
            x = 1104,
            y = 0,
         }
      },
      mef_fire = {
         integer_id = 24,
         animation = 3,
         offset_y = 16,
         source = {
            x = 1152,
            y = 0,
         }
      },
      _25 = {
         integer_id = 25,
         source = {
            x = 1200,
            y = 0,
         }
      },
      _26 = {
         integer_id = 26,
         source = {
            x = 1248,
            y = 0,
         }
      },
      mef_liquid = {
         integer_id = 27,
         animation = 3,
         source = {
            x = 1296,
            y = 0,
         }
      },
      _28 = {
         integer_id = 28,
         source = {
            x = 1344,
            y = 0,
         }
      },
      _29 = {
         integer_id = 29,
         source = {
            x = 1392,
            y = 0,
         }
      },
      mef_barrier = {
         integer_id = 30,
         animation = 2,
         offset_y = 16,
         source = {
            x = 1440,
            y = 0,
         }
      },
      _31 = {
         integer_id = 31,
         source = {
            x = 1488,
            y = 0,
         }
      },
      worthless_fake_gold_bar = {
         integer_id = 33,
         source = {
            x = 0,
            y = 48,
         }
      },
      bed = {
         integer_id = 66,
         source = {
            x = 0,
            y = 96,
         }
      },
      rag_doll = {
         integer_id = 67,
         source = {
            x = 48,
            y = 96,
         }
      },
      noble_toy = {
         integer_id = 68,
         source = {
            x = 96,
            y = 96,
         }
      },
      modern_table = {
         integer_id = 69,
         source = {
            x = 144,
            y = 96,
         }
      },
      dining_table = {
         integer_id = 70,
         source = {
            x = 192,
            y = 96,
         }
      },
      _71 = {
         integer_id = 71,
         source = {
            x = 240,
            y = 96,
         }
      },
      barrel = {
         integer_id = 72,
         offset_y = 22,
         source = {
            x = 288,
            y = 96,
         }
      },
      armor = {
         integer_id = 73,
         offset_y = 22,
         source = {
            x = 336,
            y = 96,
         }
      },
      lot_of_goods = {
         integer_id = 74,
         offset_y = 22,
         source = {
            x = 384,
            y = 96,
         }
      },
      lot_of_accessories = {
         integer_id = 75,
         offset_y = 22,
         source = {
            x = 432,
            y = 96,
         }
      },
      goulds_piano = {
         integer_id = 76,
         stack_height = 28,
         offset_y = 22,
         source = {
            x = 480,
            y = 96,
         }
      },
      _77 = {
         integer_id = 77,
         source = {
            x = 528,
            y = 96,
         }
      },
      bar_table_alpha = {
         integer_id = 78,
         offset_y = 22,
         source = {
            x = 576,
            y = 96,
         }
      },
      _79 = {
         integer_id = 79,
         source = {
            x = 624,
            y = 96,
         }
      },
      bar_table_beta = {
         integer_id = 80,
         offset_y = 22,
         source = {
            x = 672,
            y = 96,
         }
      },
      painting_of_madam = {
         integer_id = 81,
         source = {
            x = 720,
            y = 96,
         }
      },
      broken_pillar = {
         integer_id = 82,
         source = {
            x = 768,
            y = 96,
         }
      },
      big_table = {
         integer_id = 83,
         source = {
            x = 816,
            y = 96,
         }
      },
      modern_chair = {
         integer_id = 84,
         source = {
            x = 864,
            y = 96,
         }
      },
      pick = {
         integer_id = 85,
         shadow = 150,
         stack_height = 8,
         offset_y = 8,
         source = {
            x = 912,
            y = 96,
         }
      },
      lantern = {
         integer_id = 86,
         source = {
            x = 960,
            y = 96,
         }
      },
      decorative_armor = {
         integer_id = 87,
         offset_y = 22,
         source = {
            x = 1008,
            y = 96,
         }
      },
      anvil = {
         integer_id = 88,
         offset_y = 22,
         source = {
            x = 1056,
            y = 96,
         }
      },
      closed_pot = {
         integer_id = 89,
         source = {
            x = 1104,
            y = 96,
         }
      },
      open_pot = {
         integer_id = 90,
         source = {
            x = 1152,
            y = 96,
         }
      },
      academic_table = {
         integer_id = 91,
         offset_y = 22,
         source = {
            x = 1200,
            y = 96,
         }
      },
      painting_of_landscape = {
         integer_id = 92,
         source = {
            x = 1248,
            y = 96,
         }
      },
      square_chair = {
         integer_id = 93,
         source = {
            x = 1296,
            y = 96,
         }
      },
      cheap_chair = {
         integer_id = 94,
         source = {
            x = 1344,
            y = 96,
         }
      },
      cupboard = {
         integer_id = 95,
         offset_y = 22,
         source = {
            x = 1392,
            y = 96,
         }
      },
      barn = {
         integer_id = 96,
         stack_height = 18,
         offset_y = 22,
         source = {
            x = 1440,
            y = 96,
         }
      },
      neat_shelf = {
         integer_id = 97,
         offset_y = 22,
         source = {
            x = 1488,
            y = 96,
         }
      },
      closet = {
         integer_id = 98,
         offset_y = 22,
         source = {
            x = 1536,
            y = 96,
         }
      },
      variety_of_tools = {
         integer_id = 99,
         offset_y = 22,
         source = {
            x = 0,
            y = 144,
         }
      },
      variety_of_goods = {
         integer_id = 100,
         offset_y = 22,
         source = {
            x = 48,
            y = 144,
         }
      },
      well = {
         integer_id = 101,
         source = {
            x = 96,
            y = 144,
         }
      },
      variety_of_clothes = {
         integer_id = 102,
         offset_y = 22,
         source = {
            x = 144,
            y = 144,
         }
      },
      furnace = {
         integer_id = 103,
         offset_y = 22,
         source = {
            x = 192,
            y = 144,
         }
      },
      oven = {
         integer_id = 104,
         offset_y = 22,
         source = {
            x = 240,
            y = 144,
         }
      },
      sign = {
         integer_id = 105,
         source = {
            x = 288,
            y = 144,
         }
      },
      crossroad_sign = {
         integer_id = 106,
         source = {
            x = 336,
            y = 144,
         }
      },
      house_board = {
         integer_id = 107,
         offset_y = 22,
         source = {
            x = 384,
            y = 144,
         }
      },
      _108 = {
         integer_id = 108,
         source = {
            x = 432,
            y = 144,
         }
      },
      empty_basket = {
         integer_id = 109,
         source = {
            x = 480,
            y = 144,
         }
      },
      _110 = {
         integer_id = 110,
         source = {
            x = 528,
            y = 144,
         }
      },
      _111 = {
         integer_id = 111,
         source = {
            x = 576,
            y = 144,
         }
      },
      _112 = {
         integer_id = 112,
         source = {
            x = 624,
            y = 144,
         }
      },
      _113 = {
         integer_id = 113,
         source = {
            x = 672,
            y = 144,
         }
      },
      _114 = {
         integer_id = 114,
         source = {
            x = 720,
            y = 144,
         }
      },
      _115 = {
         integer_id = 115,
         source = {
            x = 768,
            y = 144,
         }
      },
      show_case_of_breads = {
         integer_id = 116,
         offset_y = 22,
         source = {
            x = 816,
            y = 144,
         }
      },
      stick_bread = {
         integer_id = 117,
         offset_y = 22,
         source = {
            x = 864,
            y = 144,
         }
      },
      beaker = {
         integer_id = 118,
         offset_y = 22,
         source = {
            x = 912,
            y = 144,
         }
      },
      alchemy_kit = {
         integer_id = 119,
         source = {
            x = 960,
            y = 144,
         }
      },
      pentagram = {
         integer_id = 120,
         source = {
            x = 1008,
            y = 144,
         }
      },
      small_foliage_plant = {
         integer_id = 121,
         source = {
            x = 1056,
            y = 144,
         }
      },
      rose = {
         integer_id = 122,
         source = {
            x = 1104,
            y = 144,
         }
      },
      large_foliage_plant = {
         integer_id = 123,
         offset_y = 12,
         source = {
            x = 1152,
            y = 144,
         }
      },
      sage = {
         integer_id = 124,
         source = {
            x = 1200,
            y = 144,
         }
      },
      gazania = {
         integer_id = 125,
         offset_y = 12,
         source = {
            x = 1248,
            y = 144,
         }
      },
      nerine = {
         integer_id = 126,
         source = {
            x = 1296,
            y = 144,
         }
      },
      anemos = {
         integer_id = 127,
         source = {
            x = 1344,
            y = 144,
         }
      },
      foxtail_grass = {
         integer_id = 128,
         source = {
            x = 1392,
            y = 144,
         }
      },
      carnation = {
         integer_id = 129,
         source = {
            x = 1440,
            y = 144,
         }
      },
      black_crystal = {
         integer_id = 130,
         offset_y = 12,
         source = {
            x = 1488,
            y = 144,
         }
      },
      painting_of_sunflower = {
         integer_id = 131,
         source = {
            x = 1536,
            y = 144,
         }
      },
      canvas = {
         integer_id = 132,
         offset_y = 22,
         source = {
            x = 0,
            y = 192,
         }
      },
      map = {
         integer_id = 133,
         source = {
            x = 48,
            y = 192,
         }
      },
      snow_man = {
         integer_id = 134,
         offset_y = 12,
         source = {
            x = 96,
            y = 192,
         }
      },
      bundle_of_bows = {
         integer_id = 135,
         source = {
            x = 144,
            y = 192,
         }
      },
      bundle_of_weapons = {
         integer_id = 136,
         offset_y = 12,
         source = {
            x = 192,
            y = 192,
         }
      },
      decorated_cloth = {
         integer_id = 137,
         offset_y = 22,
         source = {
            x = 240,
            y = 192,
         }
      },
      decorated_armor = {
         integer_id = 138,
         offset_y = 22,
         source = {
            x = 288,
            y = 192,
         }
      },
      statue_of_armor = {
         integer_id = 139,
         offset_y = 22,
         source = {
            x = 336,
            y = 192,
         }
      },
      disorderly_book = {
         integer_id = 140,
         source = {
            x = 384,
            y = 192,
         }
      },
      lot_of_books = {
         integer_id = 141,
         source = {
            x = 432,
            y = 192,
         }
      },
      craft_rack = {
         integer_id = 142,
         stack_height = 36,
         offset_y = 22,
         source = {
            x = 480,
            y = 192,
         }
      },
      craft_book_shelf = {
         integer_id = 143,
         stack_height = 36,
         offset_y = 22,
         source = {
            x = 528,
            y = 192,
         }
      },
      lot_of_alcohols = {
         integer_id = 144,
         source = {
            x = 576,
            y = 192,
         }
      },
      kitchen = {
         integer_id = 145,
         offset_y = 22,
         source = {
            x = 624,
            y = 192,
         }
      },
      washstand = {
         integer_id = 146,
         offset_y = 22,
         source = {
            x = 672,
            y = 192,
         }
      },
      kitchen_oven = {
         integer_id = 147,
         offset_y = 22,
         source = {
            x = 720,
            y = 192,
         }
      },
      narrow_dining_table = {
         integer_id = 148,
         source = {
            x = 768,
            y = 192,
         }
      },
      elegant_table = {
         integer_id = 149,
         source = {
            x = 816,
            y = 192,
         }
      },
      gorgeous_candlestick = {
         integer_id = 150,
         shadow = 70,
         stack_height = 8,
         offset_y = 22,
         source = {
            x = 864,
            y = 192,
         }
      },
      simple_shelf = {
         integer_id = 151,
         offset_y = 22,
         source = {
            x = 912,
            y = 192,
         }
      },
      sewing_kit = {
         integer_id = 152,
         source = {
            x = 960,
            y = 192,
         }
      },
      carpenters_tool = {
         integer_id = 153,
         source = {
            x = 1008,
            y = 192,
         }
      },
      messy_cloth = {
         integer_id = 154,
         source = {
            x = 1056,
            y = 192,
         }
      },
      silk_cloth = {
         integer_id = 155,
         source = {
            x = 1104,
            y = 192,
         }
      },
      collapsed_grave = {
         integer_id = 156,
         shadow = 150,
         stack_height = 20,
         offset_y = 8,
         source = {
            x = 1152,
            y = 192,
         }
      },
      crumbled_grave = {
         integer_id = 157,
         source = {
            x = 1200,
            y = 192,
         }
      },
      grave_ornamented_with_flowers = {
         integer_id = 158,
         shadow = 150,
         stack_height = 24,
         offset_y = 8,
         source = {
            x = 1248,
            y = 192,
         }
      },
      brand_new_grave = {
         integer_id = 159,
         shadow = 150,
         stack_height = 24,
         offset_y = 8,
         source = {
            x = 1296,
            y = 192,
         }
      },
      solemn_tomb = {
         integer_id = 160,
         offset_y = 22,
         source = {
            x = 1344,
            y = 192,
         }
      },
      grave = {
         integer_id = 161,
         source = {
            x = 1392,
            y = 192,
         }
      },
      old_grave = {
         integer_id = 162,
         source = {
            x = 1440,
            y = 192,
         }
      },
      ceremony_altar = {
         integer_id = 163,
         stack_height = 16,
         offset_y = 22,
         source = {
            x = 1488,
            y = 192,
         }
      },
      green_pea = {
         integer_id = 164,
         offset_y = 22,
         source = {
            x = 1536,
            y = 192,
         }
      },
      small_medal = {
         integer_id = 165,
         source = {
            x = 0,
            y = 240,
         }
      },
      bunk_bed = {
         integer_id = 166,
         offset_y = 22,
         source = {
            x = 48,
            y = 240,
         }
      },
      _167 = {
         integer_id = 167,
         source = {
            x = 96,
            y = 240,
         }
      },
      hero_cheese = {
         integer_id = 168,
         source = {
            x = 144,
            y = 240,
         }
      },
      quwapana = {
         integer_id = 169,
         source = {
            x = 192,
            y = 240,
         }
      },
      stomafillia = {
         integer_id = 170,
         source = {
            x = 240,
            y = 240,
         }
      },
      edible_wild_plant = {
         integer_id = 171,
         source = {
            x = 288,
            y = 240,
         }
      },
      happy_apple = {
         integer_id = 172,
         source = {
            x = 336,
            y = 240,
         }
      },
      grape = {
         integer_id = 173,
         source = {
            x = 384,
            y = 240,
         }
      },
      kiwi = {
         integer_id = 174,
         source = {
            x = 432,
            y = 240,
         }
      },
      cherry = {
         integer_id = 175,
         source = {
            x = 480,
            y = 240,
         }
      },
      guava = {
         integer_id = 176,
         source = {
            x = 528,
            y = 240,
         }
      },
      carrot = {
         integer_id = 177,
         source = {
            x = 576,
            y = 240,
         }
      },
      radish = {
         integer_id = 178,
         source = {
            x = 624,
            y = 240,
         }
      },
      sweet_potato = {
         integer_id = 179,
         source = {
            x = 672,
            y = 240,
         }
      },
      lettuce = {
         integer_id = 180,
         source = {
            x = 720,
            y = 240,
         }
      },
      stack_of_dishes = {
         integer_id = 181,
         source = {
            x = 768,
            y = 240,
         }
      },
      imo = {
         integer_id = 182,
         source = {
            x = 816,
            y = 240,
         }
      },
      api_nut = {
         integer_id = 183,
         source = {
            x = 864,
            y = 240,
         }
      },
      strawberry = {
         integer_id = 184,
         source = {
            x = 912,
            y = 240,
         }
      },
      healthy_leaf = {
         integer_id = 185,
         source = {
            x = 960,
            y = 240,
         }
      },
      rainbow_fruit = {
         integer_id = 186,
         source = {
            x = 1008,
            y = 240,
         }
      },
      qucche = {
         integer_id = 187,
         source = {
            x = 1056,
            y = 240,
         }
      },
      tangerine = {
         integer_id = 188,
         source = {
            x = 1104,
            y = 240,
         }
      },
      magic_fruit = {
         integer_id = 189,
         source = {
            x = 1152,
            y = 240,
         }
      },
      _190 = {
         integer_id = 190,
         source = {
            x = 1200,
            y = 240,
         }
      },
      cbocchi = {
         integer_id = 191,
         source = {
            x = 1248,
            y = 240,
         }
      },
      melon = {
         integer_id = 192,
         source = {
            x = 1296,
            y = 240,
         }
      },
      leccho = {
         integer_id = 193,
         source = {
            x = 1344,
            y = 240,
         }
      },
      _194 = {
         integer_id = 194,
         source = {
            x = 1392,
            y = 240,
         }
      },
      _195 = {
         integer_id = 195,
         source = {
            x = 1440,
            y = 240,
         }
      },
      corpse = {
         integer_id = 196,
         source = {
            x = 1488,
            y = 240,
         }
      },
      shop_strongbox = {
         integer_id = 197,
         stack_height = 24,
         offset_y = 22,
         source = {
            x = 1536,
            y = 240,
         }
      },
      pot = {
         integer_id = 198,
         source = {
            x = 0,
            y = 288,
         }
      },
      animal_bone = {
         integer_id = 199,
         source = {
            x = 48,
            y = 288,
         }
      },
      straw = {
         integer_id = 200,
         source = {
            x = 96,
            y = 288,
         }
      },
      bomb_fish = {
         integer_id = 201,
         source = {
            x = 144,
            y = 288,
         }
      },
      rope = {
         integer_id = 202,
         source = {
            x = 192,
            y = 288,
         }
      },
      bowl = {
         integer_id = 203,
         source = {
            x = 240,
            y = 288,
         }
      },
      washing = {
         integer_id = 204,
         source = {
            x = 288,
            y = 288,
         }
      },
      _205 = {
         integer_id = 205,
         source = {
            x = 336,
            y = 288,
         }
      },
      empty_bowl = {
         integer_id = 206,
         source = {
            x = 384,
            y = 288,
         }
      },
      basket = {
         integer_id = 207,
         source = {
            x = 432,
            y = 288,
         }
      },
      whisky = {
         integer_id = 208,
         source = {
            x = 480,
            y = 288,
         }
      },
      ore_piece = {
         integer_id = 209,
         source = {
            x = 528,
            y = 288,
         }
      },
      bottle_of_whisky = {
         integer_id = 210,
         source = {
            x = 576,
            y = 288,
         }
      },
      crystal = {
         integer_id = 211,
         source = {
            x = 624,
            y = 288,
         }
      },
      raw_ore = {
         integer_id = 212,
         source = {
            x = 672,
            y = 288,
         }
      },
      raw_ore_of_diamond = {
         integer_id = 213,
         source = {
            x = 720,
            y = 288,
         }
      },
      _214 = {
         integer_id = 214,
         source = {
            x = 768,
            y = 288,
         }
      },
      _215 = {
         integer_id = 215,
         source = {
            x = 816,
            y = 288,
         }
      },
      _216 = {
         integer_id = 216,
         source = {
            x = 864,
            y = 288,
         }
      },
      _217 = {
         integer_id = 217,
         source = {
            x = 912,
            y = 288,
         }
      },
      _218 = {
         integer_id = 218,
         source = {
            x = 960,
            y = 288,
         }
      },
      _219 = {
         integer_id = 219,
         source = {
            x = 1008,
            y = 288,
         }
      },
      small_gamble_chest = {
         integer_id = 220,
         source = {
            x = 1056,
            y = 288,
         }
      },
      figurine_of_sword = {
         integer_id = 221,
         source = {
            x = 1104,
            y = 288,
         }
      },
      figurine_of_warrior = {
         integer_id = 222,
         source = {
            x = 1152,
            y = 288,
         }
      },
      molotov = {
         integer_id = 223,
         source = {
            x = 1200,
            y = 288,
         }
      },
      horn = {
         integer_id = 224,
         source = {
            x = 1248,
            y = 288,
         }
      },
      _225 = {
         integer_id = 225,
         source = {
            x = 1296,
            y = 288,
         }
      },
      portable_cooking_tool = {
         integer_id = 226,
         source = {
            x = 1344,
            y = 288,
         }
      },
      _227 = {
         integer_id = 227,
         source = {
            x = 1392,
            y = 288,
         }
      },
      _228 = {
         integer_id = 228,
         source = {
            x = 1440,
            y = 288,
         }
      },
      _229 = {
         integer_id = 229,
         source = {
            x = 1488,
            y = 288,
         }
      },
      _230 = {
         integer_id = 230,
         source = {
            x = 1536,
            y = 288,
         }
      },
      fire_wood = {
         integer_id = 231,
         source = {
            x = 0,
            y = 336,
         }
      },
      scarecrow = {
         integer_id = 232,
         offset_y = 22,
         source = {
            x = 48,
            y = 336,
         }
      },
      sack = {
         integer_id = 233,
         source = {
            x = 96,
            y = 336,
         }
      },
      luxury_drawer = {
         integer_id = 234,
         stack_height = 24,
         offset_y = 22,
         source = {
            x = 144,
            y = 336,
         }
      },
      bookshelf = {
         integer_id = 235,
         stack_height = 36,
         offset_y = 22,
         source = {
            x = 192,
            y = 336,
         }
      },
      modern_rack = {
         integer_id = 236,
         offset_y = 22,
         source = {
            x = 240,
            y = 336,
         }
      },
      round_chair = {
         integer_id = 237,
         source = {
            x = 288,
            y = 336,
         }
      },
      junk_stone = {
         integer_id = 238,
         source = {
            x = 336,
            y = 336,
         }
      },
      wood_piece = {
         integer_id = 239,
         source = {
            x = 384,
            y = 336,
         }
      },
      garbage = {
         integer_id = 240,
         source = {
            x = 432,
            y = 336,
         }
      },
      broken_vase = {
         integer_id = 241,
         source = {
            x = 480,
            y = 336,
         }
      },
      bonfire = {
         integer_id = 242,
         shadow = 250,
         stack_height = 8,
         offset_y = 22,
         source = {
            x = 528,
            y = 336,
         }
      },
      flag = {
         integer_id = 243,
         source = {
            x = 576,
            y = 336,
         }
      },
      broken_sword = {
         integer_id = 244,
         source = {
            x = 624,
            y = 336,
         }
      },
      bone_fragment = {
         integer_id = 245,
         source = {
            x = 672,
            y = 336,
         }
      },
      skeleton = {
         integer_id = 246,
         source = {
            x = 720,
            y = 336,
         }
      },
      tombstone = {
         integer_id = 247,
         source = {
            x = 768,
            y = 336,
         }
      },
      broom = {
         integer_id = 248,
         offset_y = 22,
         source = {
            x = 816,
            y = 336,
         }
      },
      water_tub = {
         integer_id = 249,
         source = {
            x = 864,
            y = 336,
         }
      },
      comfortable_table = {
         integer_id = 250,
         source = {
            x = 912,
            y = 336,
         }
      },
      inner_tube = {
         integer_id = 251,
         source = {
            x = 960,
            y = 336,
         }
      },
      treasure_map = {
         integer_id = 252,
         source = {
            x = 1008,
            y = 336,
         }
      },
      heir_trunk = {
         integer_id = 253,
         source = {
            x = 1056,
            y = 336,
         }
      },
      wallet = {
         integer_id = 254,
         source = {
            x = 1104,
            y = 336,
         }
      },
      well_kept_armor = {
         integer_id = 255,
         source = {
            x = 1152,
            y = 336,
         }
      },
      rack_of_goods = {
         integer_id = 256,
         source = {
            x = 1200,
            y = 336,
         }
      },
      rack_of_accessories = {
         integer_id = 257,
         source = {
            x = 1248,
            y = 336,
         }
      },
      towel = {
         integer_id = 258,
         source = {
            x = 1296,
            y = 336,
         }
      },
      ragged_table = {
         integer_id = 259,
         stack_height = 12,
         offset_y = 8,
         source = {
            x = 1344,
            y = 336,
         }
      },
      cabinet = {
         integer_id = 260,
         stack_height = 22,
         offset_y = 22,
         source = {
            x = 1392,
            y = 336,
         }
      },
      luxury_bed = {
         integer_id = 261,
         source = {
            x = 1440,
            y = 336,
         }
      },
      vase = {
         integer_id = 262,
         offset_y = 22,
         source = {
            x = 1488,
            y = 336,
         }
      },
      high_grade_dresser = {
         integer_id = 263,
         offset_y = 22,
         source = {
            x = 1536,
            y = 336,
         }
      },
      neat_bar_table = {
         integer_id = 264,
         offset_y = 22,
         source = {
            x = 0,
            y = 384,
         }
      },
      large_bouquet = {
         integer_id = 265,
         source = {
            x = 48,
            y = 384,
         }
      },
      chest_of_clothes = {
         integer_id = 266,
         stack_height = 24,
         offset_y = 22,
         source = {
            x = 96,
            y = 384,
         }
      },
      giant_bed = {
         integer_id = 267,
         source = {
            x = 144,
            y = 384,
         }
      },
      plain_bed = {
         integer_id = 268,
         source = {
            x = 192,
            y = 384,
         }
      },
      coffin = {
         integer_id = 269,
         source = {
            x = 240,
            y = 384,
         }
      },
      food_processor = {
         integer_id = 270,
         offset_y = 22,
         source = {
            x = 288,
            y = 384,
         }
      },
      soft_bed = {
         integer_id = 271,
         source = {
            x = 336,
            y = 384,
         }
      },
      cheap_rack = {
         integer_id = 272,
         stack_height = 34,
         offset_y = 22,
         source = {
            x = 384,
            y = 384,
         }
      },
      dresser = {
         integer_id = 273,
         offset_y = 22,
         source = {
            x = 432,
            y = 384,
         }
      },
      clean_bed = {
         integer_id = 274,
         source = {
            x = 480,
            y = 384,
         }
      },
      bathtub = {
         integer_id = 275,
         source = {
            x = 528,
            y = 384,
         }
      },
      pachisuro_machine = {
         integer_id = 276,
         offset_y = 22,
         source = {
            x = 576,
            y = 384,
         }
      },
      casino_table = {
         integer_id = 277,
         offset_y = 8,
         source = {
            x = 624,
            y = 384,
         }
      },
      slot_machine = {
         integer_id = 278,
         offset_y = 22,
         source = {
            x = 672,
            y = 384,
         }
      },
      darts_board = {
         integer_id = 279,
         offset_y = 22,
         source = {
            x = 720,
            y = 384,
         }
      },
      big_foliage_plant = {
         integer_id = 280,
         source = {
            x = 768,
            y = 384,
         }
      },
      old_shelf = {
         integer_id = 281,
         stack_height = 40,
         offset_y = 22,
         source = {
            x = 816,
            y = 384,
         }
      },
      old_bookshelf = {
         integer_id = 282,
         offset_y = 22,
         source = {
            x = 864,
            y = 384,
         }
      },
      cheap_bed = {
         integer_id = 283,
         source = {
            x = 912,
            y = 384,
         }
      },
      cheap_table = {
         integer_id = 284,
         source = {
            x = 960,
            y = 384,
         }
      },
      neat_rack = {
         integer_id = 285,
         offset_y = 22,
         source = {
            x = 1008,
            y = 384,
         }
      },
      simple_dresser = {
         integer_id = 286,
         offset_y = 22,
         source = {
            x = 1056,
            y = 384,
         }
      },
      _287 = {
         integer_id = 287,
         source = {
            x = 1104,
            y = 384,
         }
      },
      sacred_altar = {
         integer_id = 288,
         stack_height = 18,
         offset_y = 22,
         source = {
            x = 1152,
            y = 384,
         }
      },
      comfortable_bed = {
         integer_id = 289,
         source = {
            x = 1200,
            y = 384,
         }
      },
      simple_rack = {
         integer_id = 290,
         stack_height = 36,
         offset_y = 22,
         source = {
            x = 1248,
            y = 384,
         }
      },
      wide_chair = {
         integer_id = 291,
         offset_y = 22,
         source = {
            x = 1296,
            y = 384,
         }
      },
      piano = {
         integer_id = 292,
         stack_height = 32,
         offset_y = 22,
         source = {
            x = 1344,
            y = 384,
         }
      },
      statue_of_cross = {
         integer_id = 293,
         offset_y = 22,
         source = {
            x = 1392,
            y = 384,
         }
      },
      stump = {
         integer_id = 294,
         source = {
            x = 1440,
            y = 384,
         }
      },
      dress = {
         integer_id = 295,
         offset_y = 22,
         source = {
            x = 1488,
            y = 384,
         }
      },
      table = {
         integer_id = 296,
         offset_y = 22,
         source = {
            x = 1536,
            y = 384,
         }
      },
      travelers_food = {
         integer_id = 297,
         source = {
            x = 0,
            y = 432,
         }
      },
      _298 = {
         integer_id = 298,
         source = {
            x = 48,
            y = 432,
         }
      },
      golden_pedestal = {
         integer_id = 299,
         shadow = 250,
         stack_height = 8,
         offset_y = 22,
         source = {
            x = 96,
            y = 432,
         }
      },
      statue_of_money = {
         integer_id = 300,
         offset_y = 22,
         source = {
            x = 144,
            y = 432,
         }
      },
      rabbits_tail = {
         integer_id = 301,
         source = {
            x = 192,
            y = 432,
         }
      },
      remains_blood = {
         integer_id = 302,
         source = {
            x = 240,
            y = 432,
         }
      },
      remains_eye = {
         integer_id = 303,
         source = {
            x = 288,
            y = 432,
         }
      },
      remains_heart = {
         integer_id = 304,
         source = {
            x = 336,
            y = 432,
         }
      },
      remains_bone = {
         integer_id = 305,
         source = {
            x = 384,
            y = 432,
         }
      },
      fishing_pole = {
         integer_id = 306,
         source = {
            x = 432,
            y = 432,
         }
      },
      rune = {
         integer_id = 307,
         source = {
            x = 480,
            y = 432,
         }
      },
      deed = {
         integer_id = 308,
         source = {
            x = 528,
            y = 432,
         }
      },
      moonfish = {
         integer_id = 309,
         source = {
            x = 576,
            y = 432,
         }
      },
      fish = {
         integer_id = 310,
         source = {
            x = 624,
            y = 432,
         }
      },
      flatfish = {
         integer_id = 311,
         source = {
            x = 672,
            y = 432,
         }
      },
      manboo = {
         integer_id = 312,
         source = {
            x = 720,
            y = 432,
         }
      },
      seabream = {
         integer_id = 313,
         source = {
            x = 768,
            y = 432,
         }
      },
      salmon = {
         integer_id = 314,
         source = {
            x = 816,
            y = 432,
         }
      },
      globefish = {
         integer_id = 315,
         source = {
            x = 864,
            y = 432,
         }
      },
      tuna_fish = {
         integer_id = 316,
         source = {
            x = 912,
            y = 432,
         }
      },
      cutlassfish = {
         integer_id = 317,
         source = {
            x = 960,
            y = 432,
         }
      },
      sandborer = {
         integer_id = 318,
         source = {
            x = 1008,
            y = 432,
         }
      },
      gem_cutter = {
         integer_id = 319,
         source = {
            x = 1056,
            y = 432,
         }
      },
      red_treasure_machine = {
         integer_id = 320,
         offset_y = 22,
         source = {
            x = 1104,
            y = 432,
         }
      },
      blue_treasure_machine = {
         integer_id = 321,
         offset_y = 22,
         source = {
            x = 1152,
            y = 432,
         }
      },
      rare_treasure_ball = {
         integer_id = 322,
         source = {
            x = 1200,
            y = 432,
         }
      },
      seed = {
         integer_id = 323,
         source = {
            x = 1248,
            y = 432,
         }
      },
      sleeping_bag = {
         integer_id = 324,
         source = {
            x = 1296,
            y = 432,
         }
      },
      salary_chest = {
         integer_id = 325,
         offset_y = 22,
         source = {
            x = 1344,
            y = 432,
         }
      },
      feather = {
         integer_id = 326,
         source = {
            x = 1392,
            y = 432,
         }
      },
      _327 = {
         integer_id = 327,
         offset_y = 22,
         source = {
            x = 1440,
            y = 432,
         }
      },
      _328 = {
         integer_id = 328,
         source = {
            x = 1488,
            y = 432,
         }
      },
      _329 = {
         integer_id = 329,
         source = {
            x = 1536,
            y = 432,
         }
      },
      shelter = {
         integer_id = 330,
         source = {
            x = 0,
            y = 480,
         }
      },
      masters_delivery_chest = {
         integer_id = 331,
         offset_y = 22,
         source = {
            x = 48,
            y = 480,
         }
      },
      register = {
         integer_id = 332,
         offset_y = 22,
         source = {
            x = 96,
            y = 480,
         }
      },
      book = {
         integer_id = 333,
         source = {
            x = 144,
            y = 480,
         }
      },
      textbook = {
         integer_id = 334,
         source = {
            x = 192,
            y = 480,
         }
      },
      blanket = {
         integer_id = 335,
         source = {
            x = 240,
            y = 480,
         }
      },
      _336 = {
         integer_id = 336,
         source = {
            x = 288,
            y = 480,
         }
      },
      jerky = {
         integer_id = 337,
         source = {
            x = 336,
            y = 480,
         }
      },
      egg = {
         integer_id = 338,
         source = {
            x = 384,
            y = 480,
         }
      },
      bottle_of_milk = {
         integer_id = 339,
         source = {
            x = 432,
            y = 480,
         }
      },
      shit = {
         integer_id = 340,
         source = {
            x = 480,
            y = 480,
         }
      },
      _341 = {
         integer_id = 341,
         source = {
            x = 528,
            y = 480,
         }
      },
      _342 = {
         integer_id = 342,
         source = {
            x = 576,
            y = 480,
         }
      },
      _343 = {
         integer_id = 343,
         source = {
            x = 624,
            y = 480,
         }
      },
      _344 = {
         integer_id = 344,
         source = {
            x = 672,
            y = 480,
         }
      },
      _345 = {
         integer_id = 345,
         source = {
            x = 720,
            y = 480,
         }
      },
      _346 = {
         integer_id = 346,
         source = {
            x = 768,
            y = 480,
         }
      },
      _347 = {
         integer_id = 347,
         source = {
            x = 816,
            y = 480,
         }
      },
      kitty_bank = {
         integer_id = 348,
         offset_y = 22,
         source = {
            x = 864,
            y = 480,
         }
      },
      campfire = {
         integer_id = 349,
         animation = 3,
         source = {
            x = 912,
            y = 480,
         }
      },
      _350 = {
         integer_id = 350,
         source = {
            x = 960,
            y = 480,
         }
      },
      _351 = {
         integer_id = 351,
         source = {
            x = 1008,
            y = 480,
         }
      },
      torch = {
         integer_id = 352,
         source = {
            x = 1056,
            y = 480,
         }
      },
      candle = {
         integer_id = 353,
         offset_y = 48,
         source = {
            x = 1104,
            y = 480,
         }
      },
      potion = {
         integer_id = 354,
         shadow = 20,
         stack_height = 8,
         source = {
            x = 1152,
            y = 480,
         }
      },
      fountain = {
         integer_id = 355,
         animation = 3,
         source = {
            x = 1200,
            y = 480,
         }
      },
      _356 = {
         integer_id = 356,
         source = {
            x = 1248,
            y = 480,
         }
      },
      _357 = {
         integer_id = 357,
         source = {
            x = 1296,
            y = 480,
         }
      },
      _358 = {
         integer_id = 358,
         source = {
            x = 1344,
            y = 480,
         }
      },
      _359 = {
         integer_id = 359,
         source = {
            x = 1392,
            y = 480,
         }
      },
      dish = {
         integer_id = 360,
         shadow = 1,
         stack_height = 2,
         offset_y = 0,
         source = {
            x = 1440,
            y = 480,
         }
      },
      _363 = {
         integer_id = 363,
         source = {
            x = 0,
            y = 528,
         }
      },
      fancy_lamp = {
         integer_id = 364,
         shadow = 250,
         stack_height = 8,
         offset_y = 22,
         source = {
            x = 48,
            y = 528,
         }
      },
      handful_of_snow = {
         integer_id = 365,
         source = {
            x = 96,
            y = 528,
         }
      },
      mini_snow_man = {
         integer_id = 366,
         source = {
            x = 144,
            y = 528,
         }
      },
      snow_scarecrow = {
         integer_id = 367,
         offset_y = 22,
         source = {
            x = 192,
            y = 528,
         }
      },
      snow_barrel = {
         integer_id = 368,
         offset_y = 22,
         source = {
            x = 240,
            y = 528,
         }
      },
      stained_glass_window = {
         integer_id = 369,
         source = {
            x = 288,
            y = 528,
         }
      },
      giants_shackle = {
         integer_id = 370,
         offset_y = 8,
         source = {
            x = 336,
            y = 528,
         }
      },
      empty_bottle = {
         integer_id = 371,
         source = {
            x = 384,
            y = 528,
         }
      },
      holy_well = {
         integer_id = 372,
         offset_y = 22,
         source = {
            x = 432,
            y = 528,
         }
      },
      presidents_chair = {
         integer_id = 373,
         offset_y = 22,
         source = {
            x = 480,
            y = 528,
         }
      },
      green_plant = {
         integer_id = 374,
         source = {
            x = 528,
            y = 528,
         }
      },
      money_tree = {
         integer_id = 375,
         offset_y = 22,
         source = {
            x = 576,
            y = 528,
         }
      },
      barbecue_set = {
         integer_id = 376,
         offset_y = 22,
         source = {
            x = 624,
            y = 528,
         }
      },
      giant_cactus = {
         integer_id = 377,
         offset_y = 22,
         source = {
            x = 672,
            y = 528,
         }
      },
      square_window = {
         integer_id = 378,
         offset_y = 48,
         source = {
            x = 720,
            y = 528,
         }
      },
      window = {
         integer_id = 379,
         offset_y = 48,
         source = {
            x = 768,
            y = 528,
         }
      },
      triangle_plant = {
         integer_id = 380,
         offset_y = 8,
         source = {
            x = 816,
            y = 528,
         }
      },
      board = {
         integer_id = 381,
         offset_y = 22,
         source = {
            x = 864,
            y = 528,
         }
      },
      nice_window = {
         integer_id = 382,
         offset_y = 48,
         source = {
            x = 912,
            y = 528,
         }
      },
      bill = {
         integer_id = 383,
         source = {
            x = 960,
            y = 528,
         }
      },
      tax_masters_tax_box = {
         integer_id = 384,
         offset_y = 22,
         source = {
            x = 1008,
            y = 528,
         }
      },
      _385 = {
         integer_id = 385,
         source = {
            x = 1056,
            y = 528,
         }
      },
      _386 = {
         integer_id = 386,
         source = {
            x = 1104,
            y = 528,
         }
      },
      _387 = {
         integer_id = 387,
         source = {
            x = 1152,
            y = 528,
         }
      },
      _388 = {
         integer_id = 388,
         source = {
            x = 1200,
            y = 528,
         }
      },
      _389 = {
         integer_id = 389,
         source = {
            x = 1248,
            y = 528,
         }
      },
      _390 = {
         integer_id = 390,
         source = {
            x = 1296,
            y = 528,
         }
      },
      gift = {
         integer_id = 391,
         source = {
            x = 1344,
            y = 528,
         }
      },
      pan_flute = {
         integer_id = 392,
         source = {
            x = 1392,
            y = 528,
         }
      },
      alud = {
         integer_id = 393,
         source = {
            x = 1440,
            y = 528,
         }
      },
      harmonica = {
         integer_id = 394,
         source = {
            x = 1488,
            y = 528,
         }
      },
      harp = {
         integer_id = 395,
         offset_y = 22,
         source = {
            x = 1536,
            y = 528,
         }
      },
      breastplate = {
         integer_id = 396,
         source = {
            x = 0,
            y = 576,
         }
      },
      decorative_amulet = {
         integer_id = 398,
         source = {
            x = 96,
            y = 576,
         }
      },
      bardiche = {
         integer_id = 399,
         source = {
            x = 144,
            y = 576,
         }
      },
      dagger = {
         integer_id = 400,
         source = {
            x = 192,
            y = 576,
         }
      },
      spear = {
         integer_id = 401,
         source = {
            x = 240,
            y = 576,
         }
      },
      skull_bow = {
         integer_id = 402,
         source = {
            x = 288,
            y = 576,
         }
      },
      _403 = {
         integer_id = 403,
         source = {
            x = 336,
            y = 576,
         }
      },
      long_bow = {
         integer_id = 404,
         source = {
            x = 384,
            y = 576,
         }
      },
      long_sword = {
         integer_id = 405,
         source = {
            x = 432,
            y = 576,
         }
      },
      _406 = {
         integer_id = 406,
         source = {
            x = 480,
            y = 576,
         }
      },
      decorative_ring = {
         integer_id = 407,
         source = {
            x = 528,
            y = 576,
         }
      },
      robe = {
         integer_id = 408,
         source = {
            x = 576,
            y = 576,
         }
      },
      banded_mail = {
         integer_id = 409,
         source = {
            x = 624,
            y = 576,
         }
      },
      plate_mail = {
         integer_id = 410,
         source = {
            x = 672,
            y = 576,
         }
      },
      knight_shield = {
         integer_id = 411,
         source = {
            x = 720,
            y = 576,
         }
      },
      bolt = {
         integer_id = 412,
         source = {
            x = 768,
            y = 576,
         }
      },
      feather_hat = {
         integer_id = 413,
         source = {
            x = 816,
            y = 576,
         }
      },
      plate_gauntlets = {
         integer_id = 414,
         source = {
            x = 864,
            y = 576,
         }
      },
      holy_lance = {
         integer_id = 415,
         source = {
            x = 912,
            y = 576,
         }
      },
      _416 = {
         integer_id = 416,
         source = {
            x = 960,
            y = 576,
         }
      },
      heavy_boots = {
         integer_id = 418,
         source = {
            x = 1056,
            y = 576,
         }
      },
      pistol = {
         integer_id = 419,
         source = {
            x = 1104,
            y = 576,
         }
      },
      bullet = {
         integer_id = 420,
         source = {
            x = 1152,
            y = 576,
         }
      },
      scythe = {
         integer_id = 421,
         source = {
            x = 1200,
            y = 576,
         }
      },
      light_cloak = {
         integer_id = 422,
         source = {
            x = 1248,
            y = 576,
         }
      },
      girdle = {
         integer_id = 423,
         source = {
            x = 1296,
            y = 576,
         }
      },
      stone = {
         integer_id = 424,
         source = {
            x = 1344,
            y = 576,
         }
      },
      staff = {
         integer_id = 425,
         source = {
            x = 1392,
            y = 576,
         }
      },
      halberd = {
         integer_id = 426,
         source = {
            x = 1440,
            y = 576,
         }
      },
      club = {
         integer_id = 427,
         source = {
            x = 1488,
            y = 576,
         }
      },
      _428 = {
         integer_id = 428,
         source = {
            x = 1536,
            y = 576,
         }
      },
      spellbook = {
         integer_id = 429,
         source = {
            x = 0,
            y = 624,
         }
      },
      _430 = {
         integer_id = 430,
         source = {
            x = 48,
            y = 624,
         }
      },
      katana = {
         integer_id = 431,
         source = {
            x = 96,
            y = 624,
         }
      },
      wakizashi = {
         integer_id = 432,
         source = {
            x = 144,
            y = 624,
         }
      },
      gold_piece = {
         integer_id = 433,
         source = {
            x = 192,
            y = 624,
         }
      },
      _434 = {
         integer_id = 434,
         source = {
            x = 240,
            y = 624,
         }
      },
      _435 = {
         integer_id = 435,
         source = {
            x = 288,
            y = 624,
         }
      },
      _436 = {
         integer_id = 436,
         source = {
            x = 336,
            y = 624,
         }
      },
      platinum_coin = {
         integer_id = 437,
         source = {
            x = 384,
            y = 624,
         }
      },
      material_box = {
         integer_id = 438,
         source = {
            x = 432,
            y = 624,
         }
      },
      ring_mail = {
         integer_id = 440,
         source = {
            x = 528,
            y = 624,
         }
      },
      composite_mail = {
         integer_id = 441,
         source = {
            x = 576,
            y = 624,
         }
      },
      chain_mail = {
         integer_id = 442,
         shadow = 100,
         offset_y = 8,
         source = {
            x = 624,
            y = 624,
         }
      },
      pope_robe = {
         integer_id = 443,
         source = {
            x = 672,
            y = 624,
         }
      },
      light_mail = {
         integer_id = 444,
         source = {
            x = 720,
            y = 624,
         }
      },
      coat = {
         integer_id = 445,
         source = {
            x = 768,
            y = 624,
         }
      },
      breast_plate = {
         integer_id = 446,
         source = {
            x = 816,
            y = 624,
         }
      },
      bulletproof_jacket = {
         integer_id = 447,
         source = {
            x = 864,
            y = 624,
         }
      },
      gloves = {
         integer_id = 448,
         source = {
            x = 912,
            y = 624,
         }
      },
      decorated_gloves = {
         integer_id = 449,
         source = {
            x = 960,
            y = 624,
         }
      },
      thick_gauntlets = {
         integer_id = 450,
         source = {
            x = 1008,
            y = 624,
         }
      },
      light_gloves = {
         integer_id = 451,
         source = {
            x = 1056,
            y = 624,
         }
      },
      composite_gauntlets = {
         integer_id = 452,
         source = {
            x = 1104,
            y = 624,
         }
      },
      small_shield = {
         integer_id = 453,
         source = {
            x = 1152,
            y = 624,
         }
      },
      round_shield = {
         integer_id = 454,
         source = {
            x = 1200,
            y = 624,
         }
      },
      shield = {
         integer_id = 455,
         source = {
            x = 1248,
            y = 624,
         }
      },
      large_shield = {
         integer_id = 456,
         source = {
            x = 1296,
            y = 624,
         }
      },
      kite_shield = {
         integer_id = 457,
         source = {
            x = 1344,
            y = 624,
         }
      },
      tower_shield = {
         integer_id = 458,
         source = {
            x = 1392,
            y = 624,
         }
      },
      tight_boots = {
         integer_id = 459,
         source = {
            x = 1440,
            y = 624,
         }
      },
      composite_boots = {
         integer_id = 460,
         source = {
            x = 1488,
            y = 624,
         }
      },
      armored_boots = {
         integer_id = 461,
         source = {
            x = 1536,
            y = 624,
         }
      },
      symbol_strength = {
         integer_id = 462,
         source = {
            x = 0,
            y = 672,
         }
      },
      symbol_constitution = {
         integer_id = 463,
         source = {
            x = 48,
            y = 672,
         }
      },
      symbol_dexterity = {
         integer_id = 464,
         source = {
            x = 96,
            y = 672,
         }
      },
      symbol_perception = {
         integer_id = 465,
         source = {
            x = 144,
            y = 672,
         }
      },
      symbol_learning = {
         integer_id = 466,
         source = {
            x = 192,
            y = 672,
         }
      },
      symbol_will = {
         integer_id = 467,
         source = {
            x = 240,
            y = 672,
         }
      },
      symbol_magic = {
         integer_id = 468,
         source = {
            x = 288,
            y = 672,
         }
      },
      symbol_charisma = {
         integer_id = 469,
         source = {
            x = 336,
            y = 672,
         }
      },
      scroll = {
         integer_id = 470,
         source = {
            x = 384,
            y = 672,
         }
      },
      rod = {
         integer_id = 471,
         source = {
            x = 432,
            y = 672,
         }
      },
      _472 = {
         integer_id = 472,
         source = {
            x = 480,
            y = 672,
         }
      },
      boots = {
         integer_id = 473,
         source = {
            x = 528,
            y = 672,
         }
      },
      composite_girdle = {
         integer_id = 474,
         source = {
            x = 576,
            y = 672,
         }
      },
      armored_cloak = {
         integer_id = 475,
         source = {
            x = 624,
            y = 672,
         }
      },
      cloak = {
         integer_id = 476,
         source = {
            x = 672,
            y = 672,
         }
      },
      magic_hat = {
         integer_id = 477,
         source = {
            x = 720,
            y = 672,
         }
      },
      fairy_hat = {
         integer_id = 478,
         source = {
            x = 768,
            y = 672,
         }
      },
      helm = {
         integer_id = 479,
         source = {
            x = 816,
            y = 672,
         }
      },
      knight_helm = {
         integer_id = 480,
         source = {
            x = 864,
            y = 672,
         }
      },
      heavy_helm = {
         integer_id = 481,
         source = {
            x = 912,
            y = 672,
         }
      },
      composite_helm = {
         integer_id = 482,
         source = {
            x = 960,
            y = 672,
         }
      },
      engagement_amulet = {
         integer_id = 483,
         source = {
            x = 1008,
            y = 672,
         }
      },
      bejeweled_amulet = {
         integer_id = 484,
         source = {
            x = 1056,
            y = 672,
         }
      },
      charm = {
         integer_id = 485,
         source = {
            x = 1104,
            y = 672,
         }
      },
      neck_guard = {
         integer_id = 486,
         source = {
            x = 1152,
            y = 672,
         }
      },
      talisman = {
         integer_id = 487,
         source = {
            x = 1200,
            y = 672,
         }
      },
      peridot = {
         integer_id = 488,
         source = {
            x = 1248,
            y = 672,
         }
      },
      engagement_ring = {
         integer_id = 489,
         source = {
            x = 1296,
            y = 672,
         }
      },
      ring = {
         integer_id = 490,
         source = {
            x = 1344,
            y = 672,
         }
      },
      armored_ring = {
         integer_id = 491,
         source = {
            x = 1392,
            y = 672,
         }
      },
      composite_ring = {
         integer_id = 492,
         source = {
            x = 1440,
            y = 672,
         }
      },
      stethoscope = {
         integer_id = 493,
         source = {
            x = 1488,
            y = 672,
         }
      },
      trident = {
         integer_id = 494,
         source = {
            x = 1536,
            y = 672,
         }
      },
      _495 = {
         integer_id = 495,
         source = {
            x = 0,
            y = 720,
         }
      },
      _496 = {
         integer_id = 496,
         source = {
            x = 48,
            y = 720,
         }
      },
      _497 = {
         integer_id = 497,
         source = {
            x = 96,
            y = 720,
         }
      },
      crossbow = {
         integer_id = 498,
         source = {
            x = 144,
            y = 720,
         }
      },
      hand_axe = {
         integer_id = 499,
         source = {
            x = 192,
            y = 720,
         }
      },
      battle_axe = {
         integer_id = 500,
         source = {
            x = 240,
            y = 720,
         }
      },
      zantetsu = {
         integer_id = 501,
         source = {
            x = 288,
            y = 720,
         }
      },
      scimitar = {
         integer_id = 502,
         source = {
            x = 336,
            y = 720,
         }
      },
      claymore = {
         integer_id = 503,
         source = {
            x = 384,
            y = 720,
         }
      },
      hammer = {
         integer_id = 504,
         source = {
            x = 432,
            y = 720,
         }
      },
      long_staff = {
         integer_id = 505,
         source = {
            x = 480,
            y = 720,
         }
      },
      training_machine = {
         integer_id = 506,
         offset_y = 22,
         source = {
            x = 528,
            y = 720,
         }
      },
      machine = {
         integer_id = 507,
         offset_y = 22,
         source = {
            x = 576,
            y = 720,
         }
      },
      computer = {
         integer_id = 508,
         offset_y = 22,
         source = {
            x = 624,
            y = 720,
         }
      },
      camera = {
         integer_id = 509,
         source = {
            x = 672,
            y = 720,
         }
      },
      microwave_oven = {
         integer_id = 510,
         offset_y = 22,
         source = {
            x = 720,
            y = 720,
         }
      },
      server = {
         integer_id = 511,
         stack_height = 28,
         offset_y = 22,
         source = {
            x = 768,
            y = 720,
         }
      },
      storage = {
         integer_id = 512,
         offset_y = 22,
         source = {
            x = 816,
            y = 720,
         }
      },
      trash_can = {
         integer_id = 513,
         offset_y = 22,
         source = {
            x = 864,
            y = 720,
         }
      },
      shot_gun = {
         integer_id = 514,
         source = {
            x = 912,
            y = 720,
         }
      },
      chip = {
         integer_id = 515,
         source = {
            x = 960,
            y = 720,
         }
      },
      playback_disc = {
         integer_id = 516,
         source = {
            x = 1008,
            y = 720,
         }
      },
      pop_corn = {
         integer_id = 517,
         source = {
            x = 1056,
            y = 720,
         }
      },
      fried_potato = {
         integer_id = 518,
         source = {
            x = 1104,
            y = 720,
         }
      },
      cyber_snack = {
         integer_id = 519,
         source = {
            x = 1152,
            y = 720,
         }
      },
      laser_gun = {
         integer_id = 520,
         source = {
            x = 1200,
            y = 720,
         }
      },
      energy_cell = {
         integer_id = 521,
         source = {
            x = 1248,
            y = 720,
         }
      },
      wing = {
         integer_id = 522,
         source = {
            x = 1296,
            y = 720,
         }
      },
      food_maker = {
         integer_id = 523,
         shadow = 6,
         stack_height = 40,
         offset_y = 16,
         tall = true,
         source = {
            x = 1344,
            y = 720,
         }
      },
      long_pillar = {
         integer_id = 524,
         stack_height = 65,
         offset_y = 16,
         tall = true,
         source = {
            x = 1392,
            y = 720,
         }
      },
      pillar_ornamented_with_plants = {
         integer_id = 525,
         offset_y = 20,
         tall = true,
         source = {
            x = 1440,
            y = 720,
         }
      },
      pillar_ornamented_with_flowers = {
         integer_id = 526,
         offset_y = 20,
         tall = true,
         source = {
            x = 1488,
            y = 720,
         }
      },
      tree_of_beech = {
         integer_id = 527,
         offset_y = 20,
         tall = true,
         source = {
            x = 1536,
            y = 720,
         }
      },
      card = {
         integer_id = 528,
         source = {
            x = 0,
            y = 768,
         }
      },
      _530 = {
         integer_id = 530,
         source = {
            x = 96,
            y = 768,
         }
      },
      figurine = {
         integer_id = 531,
         stack_height = 40,
         offset_y = 16,
         tall = true,
         source = {
            x = 144,
            y = 768,
         }
      },
      town_book = {
         integer_id = 532,
         source = {
            x = 192,
            y = 768,
         }
      },
      deck = {
         integer_id = 533,
         source = {
            x = 240,
            y = 768,
         }
      },
      whistle = {
         integer_id = 534,
         source = {
            x = 288,
            y = 768,
         }
      },
      vomit = {
         integer_id = 535,
         source = {
            x = 336,
            y = 768,
         }
      },
      shuriken = {
         integer_id = 536,
         source = {
            x = 384,
            y = 768,
         }
      },
      grenade = {
         integer_id = 537,
         source = {
            x = 432,
            y = 768,
         }
      },
      token_of_friendship = {
         integer_id = 538,
         source = {
            x = 480,
            y = 768,
         }
      },
      fortune_cookie = {
         integer_id = 539,
         source = {
            x = 528,
            y = 768,
         }
      },
      tomato = {
         integer_id = 540,
         source = {
            x = 576,
            y = 768,
         }
      },
      large_bookshelf = {
         integer_id = 541,
         stack_height = 36,
         offset_y = 22,
         source = {
            x = 624,
            y = 768,
         }
      },
      special_steamed_meat_bun = {
         integer_id = 542,
         source = {
            x = 672,
            y = 768,
         }
      },
      luxury_sofa = {
         integer_id = 543,
         offset_y = 22,
         source = {
            x = 720,
            y = 768,
         }
      },
      deer_head = {
         integer_id = 544,
         offset_y = 48,
         source = {
            x = 768,
            y = 768,
         }
      },
      fur_carpet = {
         integer_id = 545,
         shadow = 0,
         stack_height = 0,
         offset_y = 0,
         source = {
            x = 816,
            y = 768,
         }
      },
      kitchen_knife = {
         integer_id = 546,
         source = {
            x = 864,
            y = 768,
         }
      },
      machine_gun = {
         integer_id = 547,
         source = {
            x = 912,
            y = 768,
         }
      },
      _548 = {
         integer_id = 548,
         source = {
            x = 960,
            y = 768,
         }
      },
      recipe_holder = {
         integer_id = 549,
         source = {
            x = 1008,
            y = 768,
         }
      },
      recipe = {
         integer_id = 550,
         source = {
            x = 1056,
            y = 768,
         }
      },
      sack_of_sugar = {
         integer_id = 551,
         source = {
            x = 1104,
            y = 768,
         }
      },
      puff_puff_bread = {
         integer_id = 552,
         source = {
            x = 1152,
            y = 768,
         }
      },
      bottle_of_salt = {
         integer_id = 553,
         source = {
            x = 1200,
            y = 768,
         }
      },
      pot_for_testing = {
         integer_id = 554,
         source = {
            x = 1248,
            y = 768,
         }
      },
      frying_pan_for_testing = {
         integer_id = 555,
         source = {
            x = 1296,
            y = 768,
         }
      },
      sand_bag = {
         integer_id = 563,
         offset_y = 15,
         tall = true,
         source = {
            x = 96,
            y = 816,
         }
      },
      figurine_tall = {
         integer_id = 564,
         tall = true,
         source = {
            x = 144,
            y = 816,
         }
      },
      moon_gate = {
         integer_id = 566,
         offset_y = 12,
         tall = true,
         source = {
            x = 240,
            y = 816,
         }
      },
      moon_gate_b = {
         integer_id = 567,
         offset_y = 12,
         tall = true,
         source = {
            x = 288,
            y = 816,
         }
      },
      flower_arch = {
         integer_id = 568,
         offset_y = 12,
         tall = true,
         source = {
            x = 336,
            y = 816,
         }
      },
      bait = {
         integer_id = 569,
         shadow = 6,
         stack_height = 70,
         offset_y = 12,
         tall = true,
         source = {
            x = 384,
            y = 816,
         }
      },
      christmas_tree = {
         integer_id = 570,
         offset_y = 20,
         tall = true,
         source = {
            x = 432,
            y = 816,
         }
      },
      pillar = {
         integer_id = 571,
         stack_height = 64,
         offset_y = 20,
         tall = true,
         source = {
            x = 480,
            y = 816,
         }
      },
      statue_of_holy_cross = {
         integer_id = 572,
         offset_y = 20,
         tall = true,
         source = {
            x = 528,
            y = 816,
         }
      },
      modern_lamp_b = {
         integer_id = 573,
         offset_y = 20,
         tall = true,
         source = {
            x = 576,
            y = 816,
         }
      },
      tree_of_fir = {
         integer_id = 574,
         offset_y = 20,
         tall = true,
         source = {
            x = 624,
            y = 816,
         }
      },
      tree_of_naked = {
         integer_id = 575,
         offset_y = 20,
         tall = true,
         source = {
            x = 672,
            y = 816,
         }
      },
      modern_lamp_a = {
         integer_id = 576,
         offset_y = 20,
         tall = true,
         source = {
            x = 720,
            y = 816,
         }
      },
      freezer = {
         integer_id = 577,
         shadow = 6,
         stack_height = 48,
         offset_y = 20,
         tall = true,
         source = {
            x = 768,
            y = 816,
         }
      },
      statue_of_cat = {
         integer_id = 578,
         offset_y = 20,
         tall = true,
         source = {
            x = 816,
            y = 816,
         }
      },
      throne = {
         integer_id = 579,
         offset_y = 20,
         tall = true,
         source = {
            x = 864,
            y = 816,
         }
      },
      rack_of_potions = {
         integer_id = 580,
         shadow = 6,
         stack_height = 40,
         offset_y = 20,
         tall = true,
         source = {
            x = 912,
            y = 816,
         }
      },
      stove = {
         integer_id = 581,
         offset_y = 20,
         tall = true,
         source = {
            x = 960,
            y = 816,
         }
      },
      giant_foliage_plant = {
         integer_id = 582,
         offset_y = 20,
         tall = true,
         source = {
            x = 1008,
            y = 816,
         }
      },
      furnance = {
         integer_id = 583,
         shadow = 6,
         stack_height = 44,
         offset_y = 20,
         tall = true,
         source = {
            x = 1056,
            y = 816,
         }
      },
      fireplace = {
         integer_id = 584,
         shadow = 6,
         stack_height = 40,
         offset_y = 20,
         tall = true,
         source = {
            x = 1104,
            y = 816,
         }
      },
      street_lamp = {
         integer_id = 585,
         offset_y = 20,
         tall = true,
         source = {
            x = 1152,
            y = 816,
         }
      },
      big_cupboard = {
         integer_id = 586,
         shadow = 6,
         stack_height = 44,
         offset_y = 20,
         tall = true,
         source = {
            x = 1200,
            y = 816,
         }
      },
      tree_of_ash = {
         integer_id = 587,
         offset_y = 20,
         tall = true,
         source = {
            x = 1248,
            y = 816,
         }
      },
      tree_of_palm = {
         integer_id = 588,
         offset_y = 20,
         tall = true,
         source = {
            x = 1296,
            y = 816,
         }
      },
      tree_of_zelkova = {
         integer_id = 589,
         offset_y = 20,
         tall = true,
         source = {
            x = 1344,
            y = 816,
         }
      },
      dead_tree = {
         integer_id = 590,
         offset_y = 20,
         tall = true,
         source = {
            x = 1392,
            y = 816,
         }
      },
      tree_of_fruits = {
         integer_id = 591,
         offset_y = 20,
         tall = true,
         source = {
            x = 1440,
            y = 816,
         }
      },
      tree_of_fruitless = {
         integer_id = 592,
         offset_y = 20,
         tall = true,
         source = {
            x = 1488,
            y = 816,
         }
      },
      tree_of_cedar = {
         integer_id = 593,
         offset_y = 20,
         tall = true,
         source = {
            x = 1536,
            y = 816,
         }
      },
      shrine_gate = {
         integer_id = 627,
         offset_y = 22,
         source = {
            x = 0,
            y = 912,
         }
      },
      disguise_set = {
         integer_id = 628,
         source = {
            x = 48,
            y = 912,
         }
      },
      material_kit = {
         integer_id = 629,
         source = {
            x = 96,
            y = 912,
         }
      },
      panty = {
         integer_id = 630,
         source = {
            x = 144,
            y = 912,
         }
      },
      leash = {
         integer_id = 631,
         source = {
            x = 192,
            y = 912,
         }
      },
      mine = {
         integer_id = 632,
         source = {
            x = 240,
            y = 912,
         }
      },
      skeleton_key = {
         integer_id = 633,
         source = {
            x = 288,
            y = 912,
         }
      },
      lockpick = {
         integer_id = 634,
         source = {
            x = 336,
            y = 912,
         }
      },
      unicorn_horn = {
         integer_id = 635,
         source = {
            x = 384,
            y = 912,
         }
      },
      cooler_box = {
         integer_id = 636,
         source = {
            x = 432,
            y = 912,
         }
      },
      rice_barrel = {
         integer_id = 637,
         offset_y = 22,
         source = {
            x = 480,
            y = 912,
         }
      },
      eastern_bed = {
         integer_id = 638,
         source = {
            x = 528,
            y = 912,
         }
      },
      decorated_window = {
         integer_id = 639,
         offset_y = 48,
         source = {
            x = 576,
            y = 912,
         }
      },
      king_drawer = {
         integer_id = 640,
         stack_height = 34,
         offset_y = 22,
         source = {
            x = 624,
            y = 912,
         }
      },
      menu_board = {
         integer_id = 641,
         offset_y = 22,
         source = {
            x = 672,
            y = 912,
         }
      },
      black_board = {
         integer_id = 642,
         offset_y = 22,
         source = {
            x = 720,
            y = 912,
         }
      },
      sofa = {
         integer_id = 643,
         offset_y = 22,
         source = {
            x = 768,
            y = 912,
         }
      },
      flowerbed = {
         integer_id = 644,
         offset_y = 32,
         source = {
            x = 816,
            y = 912,
         }
      },
      toilet = {
         integer_id = 645,
         source = {
            x = 864,
            y = 912,
         }
      },
      craft_cupboard = {
         integer_id = 646,
         offset_y = 22,
         source = {
            x = 912,
            y = 912,
         }
      },
      sink = {
         integer_id = 647,
         offset_y = 22,
         source = {
            x = 960,
            y = 912,
         }
      },
      junk = {
         integer_id = 648,
         offset_y = 22,
         source = {
            x = 1008,
            y = 912,
         }
      },
      double_bed = {
         integer_id = 649,
         source = {
            x = 1056,
            y = 912,
         }
      },
      eastern_lamp = {
         integer_id = 650,
         offset_y = 22,
         source = {
            x = 1104,
            y = 912,
         }
      },
      eastern_window = {
         integer_id = 651,
         offset_y = 48,
         source = {
            x = 1152,
            y = 912,
         }
      },
      chochin = {
         integer_id = 652,
         offset_y = 48,
         source = {
            x = 1200,
            y = 912,
         }
      },
      partition = {
         integer_id = 653,
         offset_y = 32,
         source = {
            x = 1248,
            y = 912,
         }
      },
      monster_heart = {
         integer_id = 654,
         source = {
            x = 1296,
            y = 912,
         }
      },
      _655 = {
         integer_id = 655,
         offset_y = 22,
         source = {
            x = 1344,
            y = 912,
         }
      },
      secret_treasure = {
         integer_id = 656,
         source = {
            x = 1392,
            y = 912,
         }
      },
      tamers_whip = {
         integer_id = 657,
         source = {
            x = 1440,
            y = 912,
         }
      },
      little_ball = {
         integer_id = 658,
         source = {
            x = 1488,
            y = 912,
         }
      },
      eastern_partition = {
         integer_id = 659,
         offset_y = 22,
         source = {
            x = 1536,
            y = 912,
         }
      },
      _work_buffer = {
         integer_id = 660,
         tall = true,
         source = {
            x = 0,
            y = 960,
         }
      },
      summoning_crystal = {
         integer_id = 662,
         offset_y = 22,
         source = {
            x = 96,
            y = 960,
         }
      },
      _663 = {
         integer_id = 663,
         source = {
            x = 144,
            y = 960,
         }
      },
      downstairs = {
         integer_id = 664,
         shadow = 0,
         source = {
            x = 192,
            y = 960,
         }
      },
      upstairs = {
         integer_id = 665,
         shadow = 0,
         source = {
            x = 240,
            y = 960,
         }
      },
      new_years_gift = {
         integer_id = 666,
         source = {
            x = 288,
            y = 960,
         }
      },
      kotatsu = {
         integer_id = 667,
         shadow = 0,
         source = {
            x = 336,
            y = 960,
         }
      },
      daruma = {
         integer_id = 668,
         offset_y = 8,
         source = {
            x = 384,
            y = 960,
         }
      },
      kagami_mochi = {
         integer_id = 669,
         offset_y = 8,
         source = {
            x = 432,
            y = 960,
         }
      },
      mochi = {
         integer_id = 670,
         source = {
            x = 480,
            y = 960,
         }
      },
      lightsabre = {
         integer_id = 671,
         source = {
            x = 528,
            y = 960,
         }
      },
      festival_wreath = {
         integer_id = 672,
         offset_y = 38,
         source = {
            x = 576,
            y = 960,
         }
      },
      pedestal = {
         integer_id = 673,
         source = {
            x = 624,
            y = 960,
         }
      },
      counter = {
         integer_id = 674,
         stack_height = 24,
         offset_y = 22,
         source = {
            x = 672,
            y = 960,
         }
      },
      jures_body_pillow = {
         integer_id = 675,
         offset_y = 16,
         source = {
            x = 720,
            y = 960,
         }
      },
      new_years_decoration = {
         integer_id = 676,
         offset_y = 40,
         source = {
            x = 768,
            y = 960,
         }
      },
      miniature_tree = {
         integer_id = 677,
         shadow = 50,
         stack_height = 8,
         offset_y = 16,
         source = {
            x = 816,
            y = 960,
         }
      },
      bottle_of_soda = {
         integer_id = 678,
         source = {
            x = 864,
            y = 960,
         }
      },
      blue_capsule_drug = {
         integer_id = 679,
         shadow = 1,
         source = {
            x = 912,
            y = 960,
         }
      },
      statue_of_opatos = {
         integer_id = 680,
         offset_y = 16,
         tall = true,
         source = {
            x = 960,
            y = 960,
         }
      },
      statue_of_kumiromi = {
         integer_id = 681,
         offset_y = 16,
         tall = true,
         source = {
            x = 1008,
            y = 960,
         }
      },
      statue_of_mani = {
         integer_id = 682,
         offset_y = 16,
         tall = true,
         source = {
            x = 1056,
            y = 960,
         }
      },
      luxury_cabinet = {
         integer_id = 683,
         stack_height = 50,
         offset_y = 22,
         tall = true,
         source = {
            x = 1104,
            y = 960,
         }
      },
      blue_stall = {
         integer_id = 684,
         shadow = 18,
         stack_height = 50,
         offset_y = 52,
         tall = true,
         source = {
            x = 1152,
            y = 960,
         }
      },
      red_stall = {
         integer_id = 685,
         shadow = 18,
         stack_height = 50,
         offset_y = 52,
         tall = true,
         source = {
            x = 1200,
            y = 960,
         }
      },
      statue_of_creator = {
         integer_id = 686,
         offset_y = 16,
         tall = true,
         source = {
            x = 1248,
            y = 960,
         }
      },
      statue_of_ehekatl = {
         integer_id = 687,
         offset_y = 16,
         tall = true,
         source = {
            x = 1296,
            y = 960,
         }
      },
      guillotine = {
         integer_id = 688,
         offset_y = 16,
         tall = true,
         source = {
            x = 1344,
            y = 960,
         }
      },
      iron_maiden = {
         integer_id = 689,
         offset_y = 16,
         tall = true,
         source = {
            x = 1392,
            y = 960,
         }
      },
      statue_of_jure = {
         integer_id = 690,
         offset_y = 16,
         tall = true,
         source = {
            x = 1440,
            y = 960,
         }
      },
      gene_machine = {
         integer_id = 691,
         stack_height = 48,
         offset_y = 16,
         tall = true,
         source = {
            x = 1488,
            y = 960,
         }
      },
      statue_of_lulwy = {
         integer_id = 692,
         offset_y = 16,
         tall = true,
         source = {
            x = 1536,
            y = 960,
         }
      },
      putitoro = {
         integer_id = 695,
         source = {
            x = 96,
            y = 1008,
         }
      },
      _696 = {
         integer_id = 696,
         source = {
            x = 144,
            y = 1008,
         }
      },
      dragon_slayer = {
         integer_id = 697,
         source = {
            x = 192,
            y = 1008,
         }
      },
      claymore_unique = {
         integer_id = 698,
         source = {
            x = 240,
            y = 1008,
         }
      },
      stradivarius = {
         integer_id = 699,
         source = {
            x = 288,
            y = 1008,
         }
      },
   }
)
