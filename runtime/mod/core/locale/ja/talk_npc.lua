local I18N = require("core.I18N")

I18N.add {
   talk = {
      will_not_listen = "{name($1)}は耳を貸さない。",
      is_sleeping = "{name($1)}はぐっすり眠っている…",
      is_busy = "{name($1)}はお取り込み中だ…",
      ignores_you = "…(あなたを無視している)",

      window = {
         impress = "友好",
         attract = "興味",
         fame = "名声 {$1}",
         shop_rank = "店の規模:{$1}",

         of = "{$2} {$1}",
      },

      tag = {
         ref = "{$1}",
      },

      npc = {
         common = {
            choices = {
               talk = "話がしたい",
               trade = "アイテム交換",
               sex = "気持ちいいことしない？",
            },

            thanks = "{thanks($1, 2)}",
            you_kidding = "冷やかし{ka($1, 1)}",
            hand_over = "{itemname($1, 1)}を手渡した。",

            sex = {
               prompt = "なかなかの体つき{dana($1)}よし、買{u($1, 2)}",

               choices = {
                  accept = "はじめる",
                  go_back = "やめる",
               },

               start = "いく{yo($1, 2)}",
               response = "うふふ",
            },
         },

         quest_giver = {
            choices = {
               about_the_work = "依頼について",
               here_is_item = "{itemname($1, 1)}を納入する",
               here_is_delivery = "配達物を渡す",
            },

            about = {
               during = "頼んでいた依頼は順調{kana($1, 1)}",

               choices = {
                  take = "受諾する",
                  leave = "やめる",
               },

               too_many_unfinished = "未完了の依頼が多すぎじゃない{kana($1, 1)}この仕事は、安心してまかせられない{yo($1)}",
               backpack_full = "どうやらバックパックが一杯のよう{da($1)}持ち物を整理してまた来て{kure($1)}",
               party_full = "これ以上仲間を連れて行けないよう{da($1)}人数を調整してまた来て{kure($1)}",

               thanks = "{thanks($1)}期待してい{ru($1)}",
               here_is_package = "これが依頼の品物{da($1)}期限には十分気をつけて{kure($1)}",
            },

            accept = {
               hunt = "では、早速案内するので、モンスターを一匹残らず退治して{kure($1)}",
               harvest = "畑までは案内するから、しっかりと期限内に作物を納入して{kure($1)}",
               party = "ついて来て{kure($1)}パーティー会場まで案内する{yo($1)}",
            },

            finish = {
               escort = "無事に到着できてほっとした{yo($1)}{thanks($1, 2)}",
            },
         },

         servant = {
            choices = {
               fire = "解雇する",
            },

            fire = {
               prompt = "({name($1)}は悲しそうな目であなたを見ている。本当に縁を切る？)",

               choices = {
                  yes = "切る",
                  no = "やめる",
               },

               you_dismiss = "{name($1)}を解雇した… ",
            },
         },

         ally = {
            choices = {
               wait_at_town = "街で待機しろ",
               ask_for_marriage = "婚約を申し込む",
               make_gene = "遺伝子を残す",
               silence = {
                  start = "黙らせる",
                  stop = "喋らせる",
               },
               abandon = "縁を切る",
            },

            wait_at_town = "(あなたは、{name($1)}に街で待っているように指示した)",

            marriage = {
               refuses = "({name($1)}はやんわりと断った)",
               accepts = "はい…喜んで。",
            },

            make_gene = {
               refuses = "こんな場所では嫌よ",
               accepts = "いやん、あなたったら…",
            },

            silence = {
               start = "({name($1)}はしゅんとなった…)",
               stop = "({name($1)}はあなたに抱きついた)",
            },

            abandon = {
               prompt = "({name($1)}は悲しそうな目であなたを見ている。本当に縁を切る？)",

               choices = {
                  yes = "切る",
                  no = "やめる",
               },

               you_abandoned = "{name($1)}と別れた…",
            },
         },

         maid = {
            choices = {
               think_of_house_name = "家の名前を考えてくれ",
               meet_guest = "客に会う",
               do_not_meet = "追い返す",
            },

            think_of_house_name = {
               suffixes = {
                  "{$1}の家",
                  "{$1}邸",
                  "{$1}城",
                  "{$1}ハーレム",
                  "{$1}の巣窟",
                  "{$1}ハウス",
                  "{$1}ホーム",
                  "{$1}の住処",
                  "{$1}宅",
                  "{$1}の隠れ家",
                  "{$1}ドーム",
               },
               come_up_with = "そう{dana($2)}これからこの家の名前は{$1}{da($2)}",
            },

            do_not_meet = "追い返す{yo($1)}",
         },

         trainer = {
            choices = {
               train = {
                  ask = "訓練したい",
                  accept = "訓練する",
               },
               learn = {
                  ask = "新しい能力を覚えたい",
                  accept = "習得する",
               },
               go_back = "やめる",
            },
            leave = "訓練が必要なときは、声をかけて{kure($1)}",
            cost = {
               training = "{$1}の能力を訓練するには{$2} platかかるけどいい{kana($3, 1)}",
               learning = "{$1}の能力を習得するには{$2} platかかるけどいい{kana($3, 1)}",
            },
            finish = {
               training = "訓練は完了し{ta($1)}潜在能力が伸びているはずなので、後は自分で鍛えて{kure($1)}",
               learning = "可能な限りの知識は教え{ta($1)}後は存分に訓練して{kure($1)}",
            },
         },

         shop = {
            choices = {
               buy = "買いたい",
               sell = "売りたい",
               attack = "襲撃するよ",
               invest = "投資したい",
               ammo = "矢弾の充填",
            },

            criminal = {
               buy = "犯罪者に売る物はない{yo($1)}",
               sell = "犯罪者から買う物はない{yo($1)}",
            },

            ammo = {
               no_ammo = "充填する必要はないみたい{da($1)}",
               cost = "そう{dana($2, 3)}、全ての矢弾を補充すると{$1} gold{da($2)}",

               choices = {
                  pay = "頼む",
                  go_back = "やめる",
               },
            },

            invest = {
               ask = "投資をしてくれる{noka($2, 1)}{$1} goldかかるけどいいの{kana($2, 1)}",

               choices = {
                  invest = "投資する",
                  reject = "やめる",
               },
            },

            attack = {
               dialog = "{rob($1, 2)}",

               choices = {
                  attack = "神に祈れ",
                  go_back = "いや、冗談です",
               },
            },
         },

         innkeeper = {
            choices = {
               eat = "食事をとる",
               go_to_shelter = "シェルターに入る",
            },

            eat = {
               not_hungry = "腹が減っているようにはみえない{yo($1)}",
               here_you_are = "{dozo($1)}",

               results = {
                  "なかなか美味しかった。",
                  "悪くない。",
                  "あなたは舌鼓をうった。",
               },
            },

            go_to_shelter = "悪天候時はシェルターを無料で開放している{nda($1)}すみやかに避難して{kure($1)}",
         },

         wizard = {
            choices = {
               identify = "鑑定したい",
               identify_all = "全て鑑定してほしい",
               investigate = "調査したい",
               ["return"] = "帰還したい",
            },

            identify = {
               already = "鑑定するアイテムはないみたい{da($1)}",
               finished = "鑑定結果はこの通り{da($1)}",
               need_investigate = "さらなる知識を求めるのなら、調査する必要が{aru($1)}",

               count = "{$2}個の未判明のアイテムのうち、{$1}個のアイテムが完全に判明した。",
            },

            ["return"] = "ここからふもとに下りるのは不便だから、ボランティアで帰還サービスをやってい{ru($1)}{kimi($1, 3)}も帰還サービスを希望{kana($1)}",

         },

         informer = {
            choices = {
               show_adventurers = "冒険者の情報",
               investigate_ally = "仲間の調査",
            },

            show_adventurers = "お目当ての情報は見つかった{kana($1)}",

            investigate_ally = {
               cost = "10000 goldかかるけどいい{ka($1, 1)}",

               choices = {
                  pay = "調査する",
                  go_back = "やめる",
               },
            },
         },

         healer = {
            choices = {
               restore_attributes = "能力の復元",
            },

            restore_attributes = "治療が完了し{ta($1)}",
         },

         bartender = {
            choices = {
               call_ally = "仲間を呼び戻す",
            },

            call_ally = {
               no_need = "そいつは呼び戻す必要はないよう{da($1)}",
               cost = "そいつを呼び戻すには、{$1} gold必要{da($2)}",

               choices = {
                  pay = "呼び戻す",
                  go_back = "やめる",
               },

               brings_back = "(バーテンが店の奥から{name($2)}を連れてきた){dozo($1)}",
            },
         },

         adventurer = {
            choices = {
               hire = "護衛を依頼する",
               join = "仲間に誘う",
            },

            hire = {
               cost = "{ore($2, 3)}の剣が必要な{noka($2, 1)}そう{dana($2, 3)}、{$1} gold払うならば、7日間護衛を引き受け{ru($2)}",

               choices = {
                  pay = "頼む",
                  go_back = "やめる",
               },

               you_hired = "{name($1)}を雇った。",
            },

            join = {
               too_weak = "{kimi($1, 3)}の仲間になれと？あまりにも力の差がありすぎる{na($1)}",
               not_known = "{kimi($1, 3)}の仲間になれと？悪い{ga($1, 3)}お断り{da($1)}",
               party_full = "これ以上仲間を連れて行けないよう{da($1)}人数を調整してまた来て{kure($1)}",
               accept = "{kimi($1, 3)}となら上手くやっていけそう{da($1)}{yoro($1, 2)}",
            },
         },

         arena_master = {
            choices = {
               enter_duel = "試合に出る[決闘]",
               enter_rumble = "試合に出る[ランブル]",
               score = "成績を聞く",
            },

            enter = {
               game_is_over = "残念だが、今日の試合はもう終了し{ta($1)}",
               target = "今日の対戦相手は{$1}{da($2)}挑戦する{noka($2, 1)}",
               target_group = "対戦相手はレベル{$1}以下の相手複数{da($2)}挑戦する{noka($2, 1)}",

               choices = {
                  enter = "挑戦する",
                  leave = "やめる",
               },

               cancel = "用があるときは声をかけて{kure($1)}",
            },

            streak = "現在は{$1}連勝中{da($2)}5連勝,20連勝毎にボーナスを与え{ru($2)}",
         },

         pet_arena_master = {
            choices = {
               register_duel = "ペットデュエル",
               register_team = "チームバトル",
            },

            register = {
               target = "一対一の戦いで、対戦相手はレベル{$1}ぐらいの相手{da($2)}挑戦する{noka($2, 1)}",
               target_group = "人同士のチームバトルで、対戦相手はレベル{$2}以下の相手複数{da($3)}挑戦する{noka($3, 1)}",

               choices = {
                  enter = "挑戦する",
                  leave = "やめる",
               },
            },
         },

         slave_trader = {
            choices = {
               buy = "奴隷を買う",
               sell = "奴隷を売る",
            },

            buy = {
               cost = "そう{dana($3)}{$1}を{$2} goldでどう{da($3, 1)}",

               choices = {
                  pay = "買い取る",
                  go_back = "やめる",
               },

               you_buy = "{$1}を買い取った。",
            },

            sell = {
               price = "なかなかの身体つき{dana($2)}{$1} goldでどう{da($2, 1)}",

               choices = {
                  deal = "売る",
                  go_back = "やめる",
               },

               you_sell_off = "{$1}を売り飛ばした。",
            },
         },

         horse_keeper = {
            choices = {
               buy = "馬を買う",
            },
         },

         sister = {
            choices = {
               buy_indulgence = "免罪符を買いたい",
            },

            buy_indulgence = {
               karma_is_not_low = "その程度の罪なら自分でなんとかしなさい。",
               cost = "免罪符を希望する{noka($2, 1)}{$1} goldかかるけどいいの{kana($2, 1)}",

               choices = {
                  buy = "買う",
                  go_back = "やめる",
               },
            },
         },

         guard = {
            choices = {
               where_is = "{basename($1)}の居場所を聞く",
               lost_wallet = "落し物の財布を届ける",
               lost_suitcase = "落し物のカバンを届ける",
            },

            where_is = {
               direction = {
                  north = "北",
                  south = "南",
                  east = "東",
                  west = "西",
               },

               dead = "奴なら今は死んでいる{yo($1, 2)}",
               very_close = "{basename($2)}ならすぐ近くにいる{yo($3)}{$1}の方を向いてごらん。",
               close = "ちょっと前に{$1}の方で見かけた{yo($3)}",
               moderate = "{basename($2)}なら{$1}の方角を探してごらん。",
               far = "{basename($2)}に会いたいのなら、{$1}にかなり歩く必要があ{ru($3)}",
               very_far = "{basename($2)}{ka($3, 3)}、ここから{$1}の物凄く離れた場所にいるはず{da($3)}",
            },

            lost = {
               empty = {
                  dialog = "む…中身が空っぽ{dana($1, 2)}",
                  response = "しまった…",

               },
               dialog = "わざわざ落し物を届けてくれた{noka($1)}{kimi($1, 3)}は市民の模範{da($1)}{thanks($1)}",
               response = "当然のことだ",

               found_often = {
                  dialog = {
                     _0 = "む、また{kimi($1, 3)}{ka($1)}随分と頻繁に財布を見つけられるもの{dana($1)}",
                     _1 = "（…あやしい）",
                  },
                  response = "ぎくっ",
               },
            },
         },

         spell_writer = {
            choices = {
               reserve = "魔法書の予約",
            },
         },

         prostitute = {
            choices = {
               buy = "暗い場所に移ろう",
            },

            buy = "そう{dana($2)}金貨{$1}枚を前払いで{kure($2)}",
         },

         caravan_master = {
            choices = {
               hire = "キャラバンを雇う",
            },

            hire = {
               tset = "つぇｔ",

               choices = {
                  go_back = "やめる",
               },
            },
         },

         moyer = {
            choices = {
               sell_paels_mom = "パエルの母を売る",
            },

            sell_paels_mom = {
               prompt = "ほほう、モンスターの顔をした人間か。見世物としてなかなかいけそうだ。金貨50000枚で買い取ろう。",

               choices = {
                  sell = "売る",
                  go_back = "やめる",
               },

               you_sell = "パエルの母親を売った…",
            },
         },
      },
   },
}
