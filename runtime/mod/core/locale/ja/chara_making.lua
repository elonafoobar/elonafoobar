local i18n = require("core.i18n")

i18n.add {
   chara_making = {
      common = {
         reroll = "リロール",
      },

      select_race = {
         caption = "やあ、待っていたよ。早速旅の支度をしようか。",
         title = "種族の選択",

         race = "選択できる種族",
         detail = "種族の説明",

         race_info = {
            race = "種族",
            attribute_bonus = {
               text = "能力ボーナス",
               _0 = "皆無",
               _1 = "最高",
               _2 = "理想的",
               _3 = "高い",
               _4 = "やや高い",
               _5 = "普通",
               _6 = "少し",
               _7 = "微々",
            },

            trained_skill = {
               text = "獲得技能",
               proficient_in = "武器の専門  ",
            },
         },
      },

      select_gender = {
         caption = "男性と女性に能力の違いはない。",
         title = "性別の選択",

         gender = "性別の候補",
      },

      select_class = {
         caption = "職業や種族は、初期の能力だけでなく、成長の方向性に影響するんだ。",
         title = "職業の選択",

         class = "選択できる職業",
         detail = "職業の説明",
      },

      roll_attributes = {
         caption = "死にたくないなら、ある程度の能力は必要だね。",
         title = "能力",

         proceed = "決定",

         attribute_reroll = "能力のロール",
         min_roll = "最低値ロール",
         locked_items_desc = "ロックされた能力は\n変化しません",
         locks_left = "残りロック",
      },

      select_feats = {
         caption = "フィートとは、君の持っている有益な特徴だ。3つまで選べるよ。",
      },

      select_alias = {
         caption = "有名になると、名前とは別の通り名で呼ばれることがあるらしい。",
         title = "異名の選択",

         lock_alias = "異名のロック",
         alias_list = "異名の候補",
      },

      customize_appearance = {
         caption = "君の見た目を知っておきたいな。まあ、後からいつでも変えられるけどね。",
      },

      final_screen = {
         caption = "決定ｷｰを押すことで、生い立ちをリロールできる。",

         are_you_satisfied = {
            prompt = "満足できたかな？",

            yes = "はい",
            no = "いいえ",
            restart = "最初から",
            go_back = "前に戻る",
         },

         what_is_your_name = "最後の質問だ。君の名前は？",
      },
   },
}
