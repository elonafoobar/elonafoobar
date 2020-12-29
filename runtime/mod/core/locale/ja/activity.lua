local I18N = ELONA.require("core.I18N")

I18N.add_data_text(
   "core.activity",
   {
      eat = {
         cancel_prompt = "食事を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は食事を中断した。",
      },
      read = {
         cancel_prompt = "読書を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は読書を中断した。",
      },
      travel = {
         cancel_prompt = "移動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は移動を中断した。",
      },
      sleep = {
         cancel_prompt = "休息を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は休息を中断した。",
      },
      dig_wall = {
         cancel_prompt = "採掘を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は採掘を中断した。",
      },
      perform = {
         cancel_prompt = "演奏を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は演奏を中断した。",
      },
      fish = {
         cancel_prompt = "釣りを中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は釣りを中断した。",
      },
      search_material = {
         cancel_prompt = "採取を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は採取を中断した。",
      },
      dig_around = {
         cancel_prompt = "探索を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は探索を中断した。",
      },
      sleep = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      build_shelter = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      enter_shelter = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      harvest = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      study = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      steal = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      sex = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
      blend = {
         cancel_prompt = "行動を中断したほうがいいだろうか？ ",
         canceled = "{name($1)}は行動を中断した。",
      },
   }
)

I18N.add {
   activity = {
      cancel = {
         item = "{name($1)}は行動を中断した。",
      },

      eat = {
         start = {
            normal = "{name($1)}は{itemname($2, 1)}を口に運んだ。",
            in_secret = "{name($1)}は{itemname($2, 1)}をこっそりと口に運んだ。",

            mammoth = "「いただきマンモス」",
         },

         finish = "{kare_wa($1)}{itemname($2, 1)}を食べ終えた。",
      },

      perform = {
         start = "{name($1)}は{itemname($2)}の演奏をはじめた。",

         sound = {
            random = {
               "ﾁｬﾗﾝ♪ ",
               "ﾎﾟﾛﾝ♪ ",
               "ﾀﾞｰﾝ♪ ",
            },
            cha = "ｼﾞｬﾝ♪ ",
         },

         gets_angry = "{name($1)}は激怒した。",

         dialog = {
            interest = {
               "{name($1)}は歓声を上げた。",
               "{name($1)}は目を輝かせた。",
               "「ブラボー」",
               "「いいぞ！」",
               "{name($1)}はうっとりした。",
               "{name($1)}は{name($2)}の演奏を褒め称えた。",
            },
            disinterest = {
               "「飽きた」",
               "「前にも聴いたよ」",
               "「またこの曲か…」",
            },
            angry = {
               "「引っ込め！」",
               "「うるさい！」",
               "「下手っぴ！」",
               "「何のつもりだ！」",
            },
         },

         throws_rock = "{name($1)}は石を投げた。",

         quality = {
            _0 = "まるで駄目だ…",
            _1 = "不評だった…",
            _2 = "もっと練習しなくては…",
            _3 = "演奏を終えた。",
            _4 = "いまいちだ。",
            _5 = "手ごたえがあった。",
            _6 = "納得できる演奏ができた。",
            _7 = "大盛況だ！",
            _8 = "素晴らしい！",
            _9 = "歴史に残る名演だ！",
         },

         tip = "{name($1)}は合計 {$2}のおひねりを貰った。",
      },

      sex = {
         take_clothes_off = "{name($1)}は服を脱ぎ始めた。",
         spare_life = "「そ、その{$1}とは体だけの関係{da($2)}{ore($2, 3)}は何も知らないから、命だけは…！」",

         dialog = {
            "「きくぅ」",
            "「もふもふ」",
            "「くやしい、でも…」",
            "「はぁはぁ！」",
            "「ウフフフ」",
         },

         after_dialog = {
            "よかった{yo($1, 2)}",
            "す、すごい{yo($1, 2)}",
            "も、もうだめ{da($1, 2)}",
            "は、激しかった{yo($1, 2)}",
            "か、完敗{da($1, 2)}",
         },

         take = "さあ、小遣いを受け取って{kure($1, 3)}",
         take_all_i_have = "これが{ore($1, 3)}の財布の中身の全て{da($1)}",
         gets_furious = "{name($1)}は激怒した。「なめてんの？」",

         -- 「(after_dialog)(take/take_all_i_have)」
         format = "「{$1}{$2}」",
      },

      steal = {
         start = "{itemname($1, 1)}に目星をつけた。",
         notice = {
            in_fov = "{name($1)}は窃盗を見咎めた。",
            out_of_fov = "{name($1)}は不審な物音に気づいた。",
            dialog = {
               guard = "「貴様、何をしている！」",
               other = "「ガード！ガード！」",
            },
            you_are_found = "盗みを見咎められた！",
         },
         target_is_dead = "対象は死んでいる",
         cannot_be_stolen = "それは盗めない。",
         you_lose_the_target = "対象が見当たらない。",
         it_is_too_heavy = "重すぎて手に負えない。",
         abort = "行動を中断した。",
         succeed = "{itemname($1)}を盗んだ。",
         guilt = "あなたは良心の呵責を感じた。",
      },

      rest = {
         start = "あなたは横になった。",
         finish = "あなたは休息を終えた。",
         drop_off_to_sleep = "あなたはそのまま眠りにおちた…",
      },

      sleep = {
         start = {
            global = "露営の準備を始めた。",
            other = "寝る仕度を始めた。",
         },

         finish = "あなたは眠り込んだ。",
         but_you_cannot = "しかし、大事な用を思い出して飛び起きた。",

         new_gene = {
            title = "遺伝子",
            text = "{name($1)}とあなたは熱い一夜を供にした。新たな遺伝子が生成された。",

            choices = {
               _0 = "ふぅ",
            },
         },

         slept_for = "{$1}時間眠った。あなたはリフレッシュした。",

         wake_up = {
            so_so = "まあまあの目覚めだ。",
            good = "心地よい目覚めだ。潜在能力が伸びた(計{$1}%)。",
         },
      },

      construct = {
         start = "{itemname($1, 1)}の建設を始めた。",
         finish = "{itemname($1, 1)}を作り終えた。",
      },

      pull_hatch = {
         start = "{itemname($1, 1)}のハッチを回し始めた。",
         finish = "{itemname($1, 1)}のハッチを回し終えた。",
      },

      dig = "{itemname($1, 1)}を掘り始めた。",

      study = {
         start = {
            bored = "もう飽きた。",
            studying = "{$1}の学習を始めた。",
            training = "トレーニングを始めた。",
            weather_is_bad = "外が悪天候なので、じっくりと取り組むことにした。",
         },
         finish = {
            studying = "{$1}の学習を終えた。",
            training = "トレーニングを終えた。",
         },
      },

      read = {
         start = "{kare_wa($1)}{itemname($2, 1)}を読み始めた。",
         finish = "{kare_wa($1)}{itemname($2, 1)}を読み終えた。",
      },

      harvest = {
         sound = {
            " *ザクッ* ",
            " *♪* ",
            " *ズシュ* ",
            " *ジャリ* ",
         },
         finish = "{itemname($1, 1)}を収穫した({$2})",
      },

      fishing = {
         start = "釣りを始めた。",
         fail = "何も釣れなかった…",
         get = "{itemname($1, 1)}を釣り上げた！",
      },

      material = {
         start = "採取を始めた。",
         get = "マテリアル:{$3}を{$2}個{$1}。",

         get_verb = {
            dig_up = "掘り当てた",
            fish_up = "釣り上げた",
            harvest = "採取した",
            find = "見つけた",
            get = "入手した",
         },

         lose = "マテリアル:{$1}を{$2}個失った",
         lose_total = "(残り {$1}個) ",

         digging = {
            fails = "採掘に失敗した。",
            no_more = "鉱石を掘りつくした。",
         },
         fishing = {
            fails = "釣りに失敗した。",
            no_more = "泉は干上がった。",
         },
         searching = {
            fails = "採取に失敗した。",
            no_more = "もう何もない。",
         },
         harvesting = {
            no_more = "もう目ぼしい植物は見当たらない。",
         },
      },

      dig_spot = {
         start = {
            global = "地面を掘り始めた。",
            other = "探索を始めた。",
         },

         sound = {
            " *ざくっ* ",
            " *カキン* ",
            " *ごつっ* ",
            " *じゃり* ",
            " *♪* ",
         },

         finish = "地面を掘り終えた。",
         something_is_there = " *ガチッ* …何かがある！",
      },

      dig_mining = {
         start = {
            wall = "壁を掘りはじめた。",
            spot = "鉱石を掘り始めた。",
            hard = "この壁はとても固そうだ！",
         },

         finish = {
            wall = "壁を掘り終えた。",
            find = "何かを見つけた。",
         },

         fail = "背中が痛い…掘るのを諦めた。",
      },

      iron_maiden = "突然ふたが閉まった！",
      guillotine = "突然ギロチンが落ちてきた！",
   },
}
