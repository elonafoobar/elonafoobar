i18n:add {
   talk = {
      visitor = {
         wanted_to_say_hi = "まあ、とくに用もないんだけど{na($1)}",
         receive = "{name($2)}に{itemname($1, 1)}をもらった！",

         choices = {
            yes = "いい",
            no = "だめ",
         },

         adventurer = {
            new_year = {
               happy_new_year = "明けましておめでとう{da($1, 2)}",
               gift = "日ごろの感謝の意をこめてこれをあげる{yo($1)}",
               throws = "{name($1)}は{itemname($2, 1)}を置いていった。",
            },

            hate = {
               dialog = "貴様！見つけた{yo($1, 2)}",
               text = "「これでも食らうがいい{yo($1, 2)}」",
               throws = "{name($1)}は火炎瓶を投げた。",
            },

            like = {
               dialog = "これ、あげ{ru($1, 2)}",
               wonder_if = "友達100人できるかな♪",
            },

            train = {
               choices = {
                  learn = "習得する",
                  train = "訓練する",
                  pass = "遠慮しとく",
               },

               learn = {
                  dialog = "{$1}のスキルを、友達価格の{$2} platで教えてあげてもいい{ga($3, 3)}どう{kana($3, 1)}",
                  after = "新しい技術をどうやら習得できたようだ{na($1)}",
               },

               train = {
                  dialog = "{$1}のスキルを、友達価格の{$2} platで訓練してもいい{ga($3, 3)}どう{kana($3, 1)}",
                  after = "よし、これで訓練は終わり{da($1)}かなり潜在能力が伸びた{yo($1, 2)}",
               },

               pass = "わかった{yo($1)}またしばらくしてから尋ねてみ{ru($1)}",
            },

            friendship = {
               dialog = "友達の証としてこれをあげ{ru($1, 2)}大事に使って{yo($1)}",
               no_empty_spot = "部屋が一杯で置けなかった…",
            },

            souvenir = {
               dialog = "近くまで来たので寄ってみた{nda($1)}ついでだから、土産にこれをあげ{ru($1)}",
               inventory_is_full = "所持品が一杯で受け取れなかった…",
               receive = "{itemname($1, 1)}を受け取った。",
            },

            materials = {
               dialog = "旅の途中にこんなものを拾った{nda($1)}{kimi($1, 3)}の役に立つと思って持ってきた{yo($1)}",
               receive = "{name($1)}は色々なものが詰まった袋を、あなたに手渡した。",
            },

            favorite_skill = {
               dialog = "{$1}は{ore($2, 3)}の得意なスキルの内の一つ{da($2)}",
            },

            favorite_stat = {
               dialog = "{ore($2, 3)}は{$1}が自慢なの{da($2)}",
            },

            conversation = {
               dialog = "やあ。特に用はない{ga($2, 3)}、なんだか暇を持てましていたら、{kimi($2, 3)}と話がしたくなって{na($2, 3)}、寄ってみた{nda($2)}",
               hold = "あなたと{name($1)}は愉快に語り合った！",
            },

            drink = {
               dialog = "酒でも飲んで親睦を深めよう{yo($1, 2)}",
               cheers = "あなたと{name($1)}は乾杯した！",
            },
         },

         trainer = {
            no_more_this_month = "今月はもう訓練は終わり{da($1)}",

            dialog = {
               member = "{$1}の一員足るもの、ギルドの名に恥じないよう、常に己の技量を磨き続けなければならない{yo($3)}ギルドの一員である{kimi($3, 3)}には、たったのプラチナ{$2}枚で潜在能力を伸ばす訓練を施してあげる{yo($3)}",
               nonmember = "鍛えている{kana($2, 2)}冒険者として生き残るには、日ごろの鍛錬が大切{da($2, 2)}わずかプラチナ{$1}枚で、潜在能力を伸ばす特別な訓練を施してあげる{yo($2, 2)}",
            },

            choices = {
               not_today = "訓練しない",
               improve = "{$1}を鍛える",
            },

            regret = "後悔する{yo($1, 2)}",
            potential_expands = "{name($1)}の{$2}の潜在能力が大きく上昇した。",
            after = "うむ、なかなか見所がある{yo($1)}",
         },

         beggar = {
            dialog = "パンを買う金さえない{nda($1)}恵んで{kure($1, 3)}、おねがい{da($1, 2)}",
            spare = "あなたは{$1}goldを乞食に渡した。",
            after = "{thanks($1, 2)}この恩は一生忘れない{yo($1)}",
            cheap = "ケチ！",
         },

         punk = {
            dialog = "フッ。よく逃げ出さずに戻ってきた{na($1)}準備はいいか。",
            hump = "ふん！",
         },

         mysterious_producer = {
            want_to_be_star = "スターになりたい{kana($1, 1)}",
            no_turning_back = "よい心がけだ{na($1, 2)}",
         },

         merchant = {
            choices = {
               buy = "買いたい",
               sell = "売りたい",
               not_now = "今はいい",
            },

            dialog = "今日は{kimi($1, 3)}の幸運な日{da($1)}普段は一般の客には売らない格安の品を、特別に見せてあげ{ru($1)}覚えておいて{kure($1, 3)}、今日だけだ{yo($1)}",
            regret = "後になって後悔しても知らない{yo($1)}",
         },
      },
   },
}
