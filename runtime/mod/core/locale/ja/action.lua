local I18N = require("core.I18N")

I18N.add {
   action = {
      cannot_do_in_global = "その行為は、ワールドマップにいる間はできない。",
      hit_key_for_help = "?キーを押すと、コマンドの一覧が見られる。",
      really_attack = "本当に{name($1)}を攻撃する？ ",
      someone_else_is_using = "そのアイテムは他の誰かが使用中だ。",

      backpack_squashing = "{you()}は荷物に圧迫されもがいた。",

      day_breaks = "夜が明けた。",
      new_day = "一日が終わり、日付が変わった。",

      playtime_report = "Elonaをはじめてから{$1}時間が経過しています。",

      weather = {
         changes = "天候が変わった。",
         ether_wind = {
            starts = "エーテルの風が吹き始めた。すぐに避難しなくては。",
            stops = "エーテルの風は止んだ。",
         },
         rain = {
            draw_cloud = "あなたは雨雲を引き寄せた。",
            starts = "雨が降り出した。",
            starts_heavy = "突然どしゃぶりになった。",
            stops = "雨は止んだ。",
            becomes_heavier = "雨が本格的に降り出した。",
            becomes_lighter = "雨は小降りになった。",
         },
         snow = {
            starts = "雪が降ってきた。",
            stops = "雪は止んだ。",
         },
      },

      time_stop = {
         begins = "{name($1)}は時を止めた。",
         ends = "時は再び動き出した。",
      },

      which_direction = {
         default = "どの方向に？ ",
         ask = "どの方向？",
         spell = "どの方向に唱える？ ",
         wand = "どの方向に振る？ ",
         door = "何を閉める？",
         cannot_see_location = "その場所は見えない。",
         out_of_range = "射程距離外だ。",
      },


      exit_map = {
         not_permitted = "あなたはこの洞窟の探索を許可されていない。",
         no_invitation_to_pyramid = "あなたはピラミッドへの招待状を持っていない。",
         cannot_enter_jail = "あなたはガードに追い返された。",
         surface = {
            returned_to = "{$1}の表層に戻った。",
            left = "{$1}の表層を後にした。",
         },

         delivered_to_your_home = "あなたは家まで運ばれた。",

         entered = "{$1}に入った。",
         returned_to = "{$1}に戻った。",
         left = "{$1}を後にした。",

         burdened_by_cargo = "荷車の重量超過でかなり鈍足になっている！ ",

         mountain_pass = "マウンテンパスに降りた。",
         larna = "ラーナの村に辿りついた。",

         it_is_hot = "熱い！",

         gate = {
            step_into = "あなたはゲートに足を踏み入れた。ゲートはあなたの背後で消滅した。",
            need_network = "ネット機能をONにする必要がある。",
         },
      },

      interact = {
         choose = "操作する対象の方向は？",
         prompt = "{name($1)}に何をする？ ",
         choices = {
            talk = "話しかける",
            attack = "攻撃する",
            inventory = "所持品",
            give = "何かを渡す",
            bring_out = "連れ出す",
            appearance = "着替えさせる",
            teach_words = "言葉を教える",
            change_tone = "口調を変える",
            release = "縄を解く",
            name = "名前をつける",
            info = "情報",
            hang = "吊る",
         },

         change_tone = {
            prompt = "どんな言葉を教えようか。",
            default_tone = "デフォルトの口調",
            title = "口調一覧",
            hint = "決定 [口調の変更]  ",
            tone_title = "題名",
            is_somewhat_different = "{name($1)}の口調が変わった気がする。",
         },
         name = {
            prompt = "{name($1)}を何と呼ぶ？ ",
            cancel = "名前をつけるのはやめた。",
            you_named = "{basename($1)}という名前で呼ぶことにした。",
         },
         release = "{name($1)}の縄を解いた。",
      },

      bash = {
         prompt = "どの方向に体当たりする？ ",
         tree = {
            execute = "{itemname($1)}に体当たりした。",
            no_fruits = "もう実はないようだ… ",
            falls_down = "{itemname($1, 1)}が降ってきた。",
         },
         choked = {
            execute = "{name($1)}は{name($2)}に全力で体当たりした。",
            spits = "{name($1)}はもちを吐き出した。",
            dialog = "「助かったよ！」",
         },
         execute = "{name($1)}は{name($2)}に体当たりした。",
         disturbs_sleep = "{name($2)}は睡眠を妨害された。",
         shatters_pot = "{name($1)}は壷を割った。",
         door = {
            destroyed = "扉に体当たりして破壊した。",
            execute = "扉に体当たりした。",
            jail = "さすがに牢獄の扉は頑丈だ。",
            hurt = "{name($1)}は筋肉を痛めた。",
            cracked = "扉は少しだけ壊れた。",
         },
         air = "{name($1)}は空気に体当たりした。",
      },

      move = {
         drunk = " *ふらり* ",
         confused = " *ごつん* ",
         interrupt = "{name($1)}はあなたを睨み付けた。",
         carry_too_much = "潰れていて動けない！ ",
         displace = {
            text = "{name($1)}と入れ替わった。",
            dialog = {
               "「おっと、ごめんよ」",
               "「気をつけな」",
            },
         },

         leave = {
            prompt = "{$1}を去る？ ",
            abandoning_quest = "注意！現在のクエストは失敗に終わってしまう。",
         },

         sense_something = "地面に何かがあるようだ。",
         walk_into = "足元には{$1}がある。",
         twinkle = " *キラン* ",

         item_on_cell = {
            item = "{$1}が落ちている。",
            building = "{$1}が設置されている。",
            not_owned = "{$1}がある。",
            many = "ここには{$1}種類のアイテムがある。",
         },

         feature = {
            stair = {
               down = "降り階段がある。",
               up = "昇り階段がある。",
            },
            material = {
               spot = "何かが見つかりそうだ。",
               remains = "何かの残骸がある。",
               mining = "採掘場がある。",
               spring = "泉がある。",
               plants = "色んな植物が生えている。",
            },
            seed = {
               type = {
                  vegetable = "野菜",
                  fruit = "果物",
                  herb = "ハーブ",
                  strange = "何か",
                  artifact = "アーティファクト",
                  gem = "宝石",
                  magic = "魔法の木",
               },
               growth = {
                  seed = "{$1}の種が植えてある。",
                  bud = "{$1}が育っている。",
                  tree = "{$1}の実が成っている。",
                  withered = "{$1}の草は枯れてしまっている… ",
               },
            },
         },

         trap = {
            disarm = {
               fail = "解除に失敗した。",
               succeed = "罠を解除した。",
               dismantle = "あなたは罠を解体した。",
            },
            evade = "{name($1)}は罠を避けた。",
            activate = {
               text = "{kare_wa($1)}罠にかかった！",
               blind = "墨が噴き出した。",
               paralyze = "刺激的な匂いがただよう。",
               confuse = "臭い匂いがたちこめた。",
               poison = "魔法の力がテレポートを防いだ。",
               sleep = "毒ガスが噴き出した。",
               mine = " *チュドーン！* ",
               spears = {
                  text = "槍が地面から飛び出した。",
                  target_floating = "しかし{name($1)}には届かなかった。",
               },
            },
         },

         global = {
            nap = "仮眠をとった。",

            weather = {
               snow = {
                  message = {
                     "積雪のせいで旅程が遅れている。",
                     "雪道を進むのは大変な苦労だ。",
                     "深い雪に脚をとられている。",
                  },
                  sound = {
                     " *ずぶっ* ",
                     " *ザシュ* ",
                     " *ズボ* ",
                     " *ズサッ* ",
                  },
                  eat = "空腹のあまり、あなたは積もっている雪を腹にかきこんだ。",
               },

               heavy_rain = {
                  message = {
                     "雨が激しすぎてどこを歩いているかもわからない！",
                     "あまりにも視界が悪すぎる。",
                     "豪雨のせいで前が全く見えない。",
                  },
                  sound = {
                     " *びしゃ* ",
                     " *ザブッ* ",
                     " *パシャッ* ",
                     " *ざぶ* ",
                  },
               },
            },

            ambush = {
               text = "襲撃だ！",
               distance_from_nearest_town = "最も近い街までの距離:{$1}", -- NOTE
               enemy_strength = "敵勢力:",

               rank = {
                  putit = "プチ級",
                  orc = "オーク級",
                  grizzly_bear = "グリズリー級",
                  drake = "ドレイク級",
                  lich = "リッチ級",
                  dragon = "ドラゴン級",
               },
            },

            diastrophism = "この大陸に大きな地殻変動が起こった。",
         },
      },

      target = {
         out_of_sight = "視界範囲外",
         you_are_targeting = "現在のターゲットは{name($1)} (距離 {$2})",

         level = {
            _0 = "目隠しして座っていても勝てる。",
            _1 = "目隠ししていても勝てそうだ。",
            _2 = "負ける気はしない。",
            _3 = "たぶん勝てそうだ。",
            _4 = "勝てない相手ではない。",
            _5 = "相手はかなり強そうだ。",
            _6 = "少なくとも、あなたの倍は強そうだ。",
            _7 = "奇跡が起きなければ殺されるだろう。",
            _8 = "確実に殺されるだろう。",
            _9 = "絶対に勝てない相手だ。",
            _10 = "相手が巨人だとすれば、あなたは蟻のフン以下だ。",
         },
      },

      look = {
         find_nothing = "視界内にターゲットは存在しない。",
         target = "{name($1)}をターゲットにした。",
         target_ground = "地面をターゲットにした。",
      },

      ranged = {
         load_normal_ammo = "通常弾を装填した。",
         no_target = "ターゲットが見当たらない。",

         equip = {
            need_weapon = "射撃用の道具を装備していない。",
            need_ammo = "矢/弾丸を装備する必要がある。",
            wrong_ammo = "矢/弾丸の種類が適していない。",
         },
      },

      get = {
         plant = {
            dead = "枯れた草を摘み取った。",
            young = "芽を摘み取った。",
         },

         building = {
            prompt = "本当にこの建物を撤去する？（注意！建物と中の物は完全に失われます）",
            remove = "建物を撤去した。",
         },

         snow = "雪をかきあつめた。",
         air = "あなたは空気をつかんだ。",

         cannot_carry = "それは持ち運べない。",

         not_owned = {
            "それはあなたの物ではない。",
            "盗むなんてとんでもない。",
            "それは拾えない。",
         },
      },

      ammo = {
         need_to_equip = "矢弾を装備していない。",
         is_not_capable = "{itemname($1)}は切り替えに対応していない。",

         current = "現在の装填弾",
         normal = "通常弾",
         unlimited = "無限",
      },

      unlock = {
         do_not_have_lockpicks = "ロックピックを所持していない。",
         use_lockpick = "ロックピックを使用した。",
         use_skeleton_key = "スケルトンキーも使用した。",
         too_difficult = "この鍵を開ける技術はない。",
         easy = "楽勝だ。",
         fail = "開錠に失敗した。",
         lockpick_breaks = "ロックピックは壊れた。",
         try_again = "もう一度試みる？",
         succeed = "開錠に成功した。",
      },

      open = {
         text = "あなたは{itemname($1)}を開けた。",
         goods = "{itemname($1)}から溢れ出た高級品が、足元に散らばった。",
         new_year_gift = {
            something_jumps_out = "悪意を持った何かが袋から飛び出してきた！",
            trap = "罠だ！お年玉袋は発火した。",
            cursed_letter = "中には呪いの手紙が入っていた。",
            ring = " *チリリリリーン* ",
            younger_sister = "妹が入っていた！",
            something_inside = "何かが袋から出てきた。",
            wonderful = "これは素晴らしい贈り物だ！",
         },
         door = {
            succeed = "{name($1)}は扉を開けた。",
            fail = "{kare_wa($1)}開錠に失敗した。",
         },
         shackle = {
            text = "足枷を外した。",
            dialog = "モイアー「馬鹿やろう！！」",
         },

         only_in_home = "それは家の中でのみ使用できる。",
         only_in_shop = "それは店の中でのみ使用できる。",
         empty = "中身は空っぽだ。",
      },

      use_stairs = {
         cannot_during_debug = "デバッグ中はその操作はできない。",
         kotatsu = {
            prompt = "本当にこたつの中に入る？",
            use = "まっくらだ！",
         },
         cannot_go = {
            down = "これ以上降りられない。",
            up = "これ以上昇れない。",
         },
         no = {
            downstairs = "降りる階段は見つからない。",
            upstairs = "昇る階段は見つからない。",
         },
         blocked_by_barrier = "階段は不思議なバリアで塞がれている。",

         unlock = {
            normal = "扉の鍵を開けた。",
            stones = "厳重に封印された扉の前に立つと、三つの魔石が鈍い光を放った。",
         },

         locked = "鍵のかかった扉が行く手を塞いでいる。",

         prompt_give_up_quest = "クエストを放棄して階を移動する？",
         prompt_give_up_game = "試合を放棄する？",

         lost_balance = "うわああ！{you()}は階段から足を踏み外した。",
      },

      close = {
         nothing_to_close = "その方向に閉められるものはない。",
         blocked = "何かが邪魔で閉められない。",
         execute = "{name($1)}は扉を閉めた。",
      },

      pick_up = {
         execute = "{name($1)}は{$2}を拾った。",
         used_by_mount = "それは{name($1)}が使用中だ。",
         do_you_want_to_remove = "{itemname($1)}を撤去する？ ",
         you_absorb_magic = "あなたは{itemname($1)}から魔力を吸い取った。",
         poison_drips = "あなたの手から毒が滴った。",
         your_inventory_is_full = "バックパックには、もうアイテムを入れる余裕がない。",
         shopkeepers_inventory_is_full = "店の倉庫が一杯のため売れない。",

         you_buy = "{$1}を買った。",
         you_sell = "{$1}を売った。",
         you_sell_stolen = "盗品の{$1}を売却した。",
         thieves_guild_quota = "盗賊ギルドのノルマ達成まで、あと金貨{$1}枚相当の盗品を売却する必要がある。",

         put_in_container = "{$1}を保管した。",
      },

      drop = {
         execute = "{$1}を地面に置いた。",
         too_many_items = "もう周りに物を置くスペースがない！ ",
         water_is_blessed = "水は祝福を受けた。",
      },

      dig = {
         prompt = "どの方向を掘る？ ",
         too_exhausted = "疲れ過ぎて無理だ。",
      },

      search = {
         execute = "周囲を注意深く調べた。",
         crystal = {
            sense = "あなたは青い水晶の存在を感じた。",
            far = "まだだ、まだ遠い…",
            normal = "微かだが、あなたの心臓はトクンと脈打った。",
            close = "辺りの空気は息苦しいほどの緊張に包まれている。",
         },
         discover = {
            trap = "罠を発見した。",
            hidden_path = "隠れた通路を発見した。",
         },
         small_coin = {
            find = "なんと小さなメダルを見つけた！",
            far = "この辺りには何かがありそうな予感がする…",
            close = "あなたは何かが輝くのを目にした。",
         },
      },

      throw = {
         execute = "{name($1)}は{itemname($2, 1)}を投げた。",
         hits = "{name($1)}に見事に命中した！",
         monster_ball = {
            does_not_work = "この場所では効果がない。",
            cannot_be_captured = "その生物には無効だ。",
            not_enough_power = "その生物を捕獲するには、より高レベルのモンスターボールが必要だ。",
            not_weak_enough = "捕獲するためにはもっと弱らせる必要がある。",
            capture = "{name($1)}をモンスターボールに捕獲した。",
         },
         snow = {
            hits_snowman = "{itemname($1, 1)}に命中して、雪だるまは崩れた。",
            melts = "それは地面に落ちて溶けた。",

            dialog = {
               "「いてー！」",
               "「やったな」",
               " *クスクス* ",
               "「キャハハ」",
               "「こやつめ」",
               "「むむっ」",
            },
         },

         tomato = " *ぷちゅ* ",
         shatters = "それは地面に落ちて砕けた。",
      },

      read = {
         cannot_see = "{name($1)}は何も見えない。",
         book = {
            finished_decoding = "{itemname($1, 1)}を解読した！",
            falls_apart = "{itemname($1, 1)}は塵となって崩れ落ちた。",
            not_interested = "この本の内容には興味がない。それでも読む？ ",
            already_decoded = "それは既に解読済みだ。",

            void_permit = "すくつの探索を許可する、という内容の文面が形式的に書いてある。",
            book_of_rachel = "レイチェルという作家による、心あたたまる童話集だ。",
         },
         scroll = {
            dimmed_or_confused = "{name($1)}はふらふらした。",
            execute = "{kare_wa($1)}{itemname($2, 1)}を読んだ。",
         },
         recipe = {
            info = "最後に調合したアイテムを、レシピに加えることができる。(まだ未実装)",
            learned = "{itemname($1, 1)}を覚えた！",
         },
      },

      eat = {
         snatches = "{name($1)}は{name($2)}の食べ物を横取りした。",
      },

      zap = {
         execute = "{itemname($1, 1)}を振った。",
         fail = "{name($1)}は杖をうまく使えなかった。",
      },

      cast = {
         overcast_warning = "マナが足りないが、それでも詠唱を試みる？",
         confused = "{name($1)}は混乱しながらも魔法の詠唱を試みた。",

         self = "{name($1)}は{$2}の{$3}",
         other = "{name($1)}は{$2}",

         silenced = "沈黙の霧が詠唱を阻止した。",
         fail = "{name($1)}は詠唱に失敗した。",
      },

      drink = {
         potion = "{kare_wa($1)}{itemname($2, 1)}を飲み干した。",
         well = {
            is_dry = "{$1}は涸れている。",
            draw = "{name($1)}は{$2}の水をすくって飲んだ。",

            effect = {
               falls = {
                  text = "{name($1)}は井戸に落ちた！ ",
                  dialog = "{name($1)}「手を伸ばせー」",
                  floats = "しかしすぐに浮いてきた… ",
               },

               finds_gold = "{name($1)}は水の中に金貨を見つけた。",
               pregnancy = "{name($1)}は何かいけないものを飲み込んだ。",
               monster = "井戸から何かが出てきた！",
               wish_too_frequent = "ものすごい幸運が訪れた…ような気がしたが気のせいだった。",
               default = "この水は清涼だ。",
            },

            completely_dried_up = "{itemname($1)}は完全に干上がった。",
            dried_up = "{itemname($1)}は干上がった。",
         },
      },

      dip = {
         execute = "{itemname($2, 1)}を{itemname($1)}に浸した。",
         you_get = "{itemname($1, 1)}を手に入れた。",

         rots = "{itemname($1)}は腐ってしまった…",
         unchanged = "{itemname($1)}に変化はない。",
         rusts = "{itemname($1)}は錆びてしまった…",

         result = {
            love_food = {
               made = "{itemname($1)}に{itemname($2, 1)}を混入した！",
               guilty = "あなたはうしろめたさを感じた…",
               grin = "あなたはにやりと笑った。",
            },

            dyeing = "あなたは{itemname($1)}を染めた。",

            poisoned_food = "あなたはにやりと口元を歪めた。",

            put_on = "{itemname($1)}に{itemname($2, 1)}を塗りたくった。",
            good_idea_but = "いいアイデアだ！しかし…",
            gains_fireproof = "{itemname($1)}は熱から守られた。",
            gains_acidproof = "{itemname($1)}は酸から守られた。",

            bait_attachment = "{itemname($2, 1)}を{itemname($1)}に装着した。",

            blessed_item = "{itemname($2, 1)}を{itemname($1)}に降りかけた。",
            becomes_blessed = "{itemname($1)}は銀色に輝いた。",
            becomes_cursed = "{itemname($1)}は黒いオーラに包まれた。",

            well_refill = "{itemname($2, 1)}を{itemname($1)}に放り込んだ。",
            empty_bottle_shatters = "空き瓶の割れる音がした。",
            holy_well_polluted = "井戸は汚れた。",
            well_dry = "{itemname($1)}は完全に枯れている。",
            well_refilled = "{itemname($1)}は一瞬輝いた。",
            snow_melts = {
               dip = "こんな量では… ",
               blending = "しかしこんな量では… ",
            },

            natural_potion = "空き瓶に水をすくった。",
            natural_potion_dry = "{itemname($1)}は涸れている。",
            natural_potion_drop = "あっ！空き瓶を井戸に落としてしまった…",
         },
      },

      plant = {
         cannot_plant_it_here = "この場所には埋められない。",
         on_field = "畑に{itemname($1, 1)}を埋めた。",
         execute = "{itemname($1, 1)}を埋めた。",
         new_plant_grows = "新しい芽が息吹いている！",
         harvest = "{itemname($1, 1)}を収穫した。",
      },

      ally_joins = {
         party_full = "仲間の最大数に達しているため、仲間にできなかった…",
         success = "{basename($1)}が仲間に加わった！",
      },

      offer = {
         do_not_believe = "あなたは神を信仰していないが、試しに捧げてみた。",
         execute = "あなたは{itemname($1)}を{$2}に捧げ、その名を唱えた。",
         claim = "異世界で、{$1}が空白の祭壇の権利を主張した。",
         take_over = {
            attempt = "異様な霧が現れ、{$1}と{$2}の幻影がせめぎあった。",
            shadow = "あなたの神の幻影は、次第に色濃くなった。",
            succeed = "{$1}は{itemname($2)}を支配した。",
            fail = "{$1}は祭壇を守りきった。",
         },
         result = {
            best = "{itemname($1)}はまばゆく輝いて消えた。",
            good = "{itemname($1)}は輝いて消え、三つ葉のクローバーがふってきた。",
            okay = "{itemname($1)}は一瞬輝いて消えた。",
            poor = "{itemname($1)}は消えた。",
         },
      },

      shortcut = {
         unassigned = "そのキーにはショートカットが割り当てられていない。",
         cannot_use_anymore = "もうその行動はできない。",
         cannot_use_spell_anymore = "その魔法はもう使えない。",
      },

      equip = {
         you_change = "装備を変更した。",

         two_handed = {
            fits_well = "装備中の{itemname($1)}は両手にしっくりとおさまる。",
            too_light = "装備中の{itemname($1)}は両手持ちにはやや軽すぎる。",
            too_heavy = "装備中の{itemname($1)}は利手で扱うにも重すぎる。",
            too_heavy_other_hand = "装備中の{itemname($1)}は片手で扱うには重すぎる。",
            too_heavy_when_riding = "装備中の{itemname($1)}は乗馬中に扱うには重すぎる。",
         },
      },

      melee = {
         shield_bash = "{name($1)}は盾で{name($2)}を殴りつけた。",
      },

      gatcha = {
         prompt = "{$1}を使ってガシャガシャする？",
         do_not_have = "{$1}を持っていない…",
      },

      angband = {
         q = "え…",
         y = "まさか…",
         at = "うわぁぁぁ！！",
      },

      quicksave = " *保存* ",

      exit = {
         cannot_save_in_usermap = "ユーザーマップの中ではセーブできない。それでも終了する？",
         prompt = "これまでの冒険を記録して終了する？",

         choices = {
            exit = "はい",
            cancel = "いいえ",
            game_setting = "ゲーム設定",
         },

         saved = "無事に記録された。",
         you_close_your_eyes = "{name($1)}は静かに目を閉じた… (キーを押すと自動終了します)",
      },

      npc = {
         is_busy_now = "{name($1)}は忙しい。",
         sand_bag = {
            "「もっとぶって{yo($1, 2)}」",
            "「こんなことして、許さない{yo($1)}」",
            "「何をする{nda($1, 2)}」",
         },
         leash = {
            dialog = {
               "「痛っ！」",
               "「やめて！」",
            },
            untangle = "{name($1)}は巻きついていた紐をほどいた。",
         },
         arena = {
            "「いいぞ！」",
            "「もっとやれー」",
            "「血をみせろー」",
            "「頑張って！」",
            "「うぉぉぉぉ！」",
            "「行けぇ！」",
            "「頭を使えよ」",
            "「きゃー」",
         },
         drunk = {
            gets_the_worse = "{name($1)}は酔っ払って{name($2)}にからんだ。",
            dialog = {
               "「一杯どうだい？」",
               "「飲んでないよ」",
               "「何見てるのさ」",
               "「遊ぼうぜ」",
            },
            annoyed = {
               text = "{name($1)}はカチンときた。",
               dialog = "「酔っ払いにはうんざり！」",
            },
         },
      },

      autopick = {
         reloaded_autopick_file = "autopickファイルを再読み込みした。",
      },

      take_screenshot = "スクリーンショットを撮った。",
   },
}
