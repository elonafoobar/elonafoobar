ELONA.i18n:add {
   action = {
      use = {
         useable_again_at = "そのアイテムが次に使用できるのは{$1}だ。",
         out_of_charge = "それはもう使えない。",
         not_sleepy = "まだ眠たくない。",

         living = {
            needs_more_blood = "この武器はまだ血を吸い足りない。",
            ready_to_grow = "{itemname($1)}は十分に血を吸い成長できる！",
            weird = "しかし、なんだか様子がおかしい…",
            it = "それは…",

            bonus = "ボーナス+1",

            displeased = "{itemname($1)}は不満そうに震えた。",
            pleased = "{itemname($1)}は嬉しげに震えた。",
            becoming_a_threat = "その力は次第に脅威になっている。",
            removes_enchantment = "{itemname($1)}はエンチャントを消した。",
         },


         mine = {
            cannot_use_here = "ここでは使えない。",
            cannot_place_here = "ここには置けない。",
            you_set_up = "地雷を設置した。",
         },

         chair = {
            needs_place_on_ground = "床に置かないと使えない。",
            you_sit_on = "あなたは{itemname($1, 1)}に座った。",

            choices = {
               relax = "くつろぐ",
               my_chair = "マイチェアにする",
               guest_chair = "お客用のチェアにする",
               free_chair = "誰でも座っていい",
            },

            relax = "あなたは存分にくつろいだ。",
            my_chair = "{itemname($1, 1)}はあなた専用の席になった！",
            guest_chair = "{itemname($1, 1)}は訪問者の席になった！",
            free_chair = "{itemname($1, 1)}は誰でも座っていい席になった！",
         },

         house_board = {
            cannot_use_it_here = "それはここでは使えない。",
         },

         dresser = {
            prompt = "誰を対象にする？",
         },

         snow = {
            need_more = "雪が足りない…",
            make_snowman = "{name($1)}は雪だるまを作った！",
         },

         torch = {
            light = "松明を灯した。",
            put_out = "松明を消した。",
         },

         stethoscope = {
            prompt = "何に聴診器を当てる？",
            self = " *ドクン ドクン* ",
            other = {
               start = {
                  text = "あなたは{name($1)}に聴診器を当てた。",
                  female = {
                     text = "{name($1)}は顔を赤らめた。",
                     dialog = "「キャー」",
                  },
               },
               stop = "{name($1)}から聴診器を外した。",
            },
         },

         leash = {
            prompt = "誰を紐で結ぶ？",
            self = "あなたは自分を紐でくくってみた…",
            other = {
               start = {
                  resists = "{name($1)}が激しく抵抗したため紐は切れた。",
                  text = "あなたは{name($1)}を紐でくくりつけた。",
                  dialog = "{name($1)}は呻き声を洩らした。「アン…♪」",
               },
               stop = {
                  text = "あなたは{name($1)}にくくりつけた紐をほどいた。",
                  dialog = "{name($1)}は呻き声を洩らした。「はぁはぁ…」",
               },
            },
         },

         sandbag = {
            cannot_use_here = "このエリアでは使えない。",
            prompt = "誰を吊るす？",

            not_weak_enough = "もっと弱らせないと吊るせない。",
            already = "それは既に吊るされている。",
            ally = "仲間を吊るすなんてとんでもない！",
            self = "あなたは自分を吊るそうと思ったがやめた…",
            start = "あなたは{name($1)}を吊るした。",
         },

         music_disc = {
            play = "{itemname($1, 1)}を再生した。",
         },

         shelter = {
            only_in_world_map = "ワールドマップで建設するべきだ。",
            cannot_build_it_here = "ここには建てられない。",
            during_quest = "クエストを放棄してシェルターに避難する？",
         },

         money_box = {
            not_enough_gold = "金貨が足りない…",
            full = "貯金箱は一杯だ。",
         },

         summoning_crystal = {
            use = "それは鈍く輝いた。",
         },

         rune = {
            only_in_town = "それは街でしか使えない。",
            use = "突然、あなたの目の前に異次元へのゲートが現れた。",
         },

         hammer = {
            use = "{itemname($1, 1)}を振った。",
         },

         unicorn_horn = {
            use = "{itemname($1, 1)}を使った。",
         },

         statue = {
            activate = "{itemname($1, 1)}を始動させた。",

            opatos = "オパートス「フハハハ！間もなく、この地に変動が起こるであろう！」",
            jure = "ジュア「べ、別にあんたのためにするんじゃないからね。バカっ！」",
            ehekatl = "エヘカトル「呼んだ？呼んだ？」",
            lulwy = {
               during_etherwind = "ルルウィ「あさはかね。エーテルの風を止めてあげるとでも思ったの？」",
               normal = "ルルウィ「あらあら、定命の分際でそんなおねだりするの？ウフフ…今回は特別よ」",
            },

            creator = {
               in_usermap = "この石像を見つめていると、何かを投げつけたくなってうずうずしてきた！",
               normal = "それはこの場所ではみすぼらしく見える。",
            },
         },

         nuke = {
            cannot_place_here = "ここでは使えない。",
            not_quest_goal = "ここはクエストの目標位置ではない。本当にここに設置する？",
            set_up = "原子爆弾を設置した。逃げろォー！",
         },

         secret_treasure = {
            use = "あなたは新たなフィートを獲得した！",
         },

         secret_experience = {
            kumiromi = {
               not_enough_exp = "クミロミの声がした。「ダメ…経験…足りない…」",
               use = {
                  dialog = "「…よく…経験をつんだね…酬いてあげる…」",
                  text = "クミロミはあなたを祝福した。あなたは新たなフィートを取得できるようになった！",
               },
            },

            lomias = "何だか嫌な予感がする…",
         },

         rope = {
            prompt = "本当に首を吊る？",
         },

         monster_ball = {
            empty = "モンスターボールは空っぽだ。",
            party_is_full = "仲間はこれ以上増やせない。",
            use = "{itemname($1, 1)}を使用した。",
         },

         gem_stone = {
            kumiromi = {
               no_plant = "それは種を植えた場所で使わなければならない。",
               already_grown = "この作物は既に成長しきっている。",
               revives = "枯れた植物に生命が宿った。",
               grows = "植物は成長した。",
            },
         },

         gene_machine = {
            choose_original = "まずは素体となる仲間を選ぶ必要がある。",
            choose_subject = "遺伝子を取り出す仲間を選ぶ必要がある。この仲間は合成後、永久に失われる。",
            precious_ally = "{name($1)}はあなたの大事な仲間だ。遺伝子を取り出すには聴診器を外す必要がある。",

            prompt = "本当に{basename($2)}に{basename($1)}の遺伝子を組み込む？",
            has_inherited = "{basename($1)}は{basename($2)}の遺伝子を受けついだ！",
            gains = {
               body_part = "{basename($1)}は新しい{$2}を得た！",
               ability = "{basename($1)}は{$2}の技術を覚えた！",
               level = "{basename($1)}はレベル{$2}になった！",
            },
         },

         iron_maiden = {
            use = "あなたはアイアンメイデンの中に入った。",
            interesting = "「わくわく♪」",
            someone_activates = "突然誰かが蓋を閉めた。",
            grin = "「ニヤリ」",
         },

         guillotine = {
            use = "あなたはギロチンに首をつっこんでみた。",
            someone_activates = "突然誰かがギロチンの刃を落とした。",
         },

         whistle = {
            use = " *ピーーーー* ",
         },

         deck = {
            put_away = "デッキをしまった。",
            no_deck = "デッキを所持していない。",
            add_card = "{itemname($1, 1)}をデッキに加えた。",
         },
      },
   },
}
