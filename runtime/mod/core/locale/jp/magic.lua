ELONA.i18n:add {
   magic = {
      common = {
         too_exhausted = "疲労し過ぎて失敗した！",
         it_is_cursed = "これは呪われている！",
         resists = "{name($1)}は抵抗した。",
         melts_alien_children = "{name($1)}の体内のエイリアンは溶けた。",
         cursed = "{name($1)}は悪魔が笑う声を聞いた。",
      },

      buff = {
         no_effect = "しかし、効果はなかった。",
         holy_veil_repels = "ホーリーヴェイルが呪いを防いだ。",
         resists = "{name($1)}は抵抗した。",
         ends = "{$1}の効果が切れた。",
      },

      slow = "{name($1)}の老化は遅くなった。",
      speed = "{name($1)}の老化は速くなった。",

      bolt = {
         ally = "ボルトが{name($1)}に命中した。",
         other = "ボルトは{name($1)}に命中し",
      },

      explosion = {
         begins = "{name($1)}は爆発した。",
         chain = "{name($1)}は誘爆した。",
         ally = "爆風が{name($1)}に命中した。",
         other = "爆風は{name($1)}に命中し",
      },

      ball = {
         ally = "ボールが{name($1)}に命中した。",
         other = "ボールは{name($1)}に命中し",
      },

      arrow = {
         ally = "矢が{name($1)}に命中した。",
         other = "矢は{name($1)}に命中し",
      },

      healed = {
         slightly = "{name($1)}の傷はふさがった。",
         normal = "{name($1)}は回復した。",
         greatly = "{name($1)}の身体に生命力がみなぎった。",
         completely = "{name($1)}は完全に回復した。",
      },

      rain_of_sanity = "{name($1)}の狂気は消え去った。",

      special_attack = {
         self = "{name($1)}は{$2}の{$3}",
         other = "{name($1)}は{$2}",
      },

      sucks_blood = {
         ally = "{name($1)}に血を吸われた。",
         other = "{kare_wa($1)}{name($2)}の血を吸い",
      },

      disassembly = "「余分な機能は削除してしまえ」",

      touch = {
         ally = "{name($1)}は{name($2)}に{$3}{$4}で{$5}",
         other = "{kare_wa($1)}{name($2)}を{$3}{$4}で{$5}",
      },

      hunger = "{name($1)}はお腹が減った。",
      weaken = "{name($1)}は弱くなった。",

      summon = "魔法でモンスターが召喚された。",

      teleport = {
         prevented = "魔法の力がテレポートを防いだ。",
         suspicious_hand = {
            succeeded = "{name($1)}は{name($2)}から{$3}枚の金貨を奪った。",
            prevented = "{name($1)}は自分の財布を守った。",
            after = "泥棒は笑って逃げた。",
         },
         shadow_step = "{name($1)}は{basename($2)}の元に移動した。",
         draw_shadow = "{name($1)}は引き寄せられた。",
         disappears = "{name($1)}は突然消えた。",
      },

      breath = {
         no_element = "",
         named = "{$1}の",
         bellows = "{name($1)}は{$2}ブレスを吐いた。",
         ally = "ブレスは{name($1)}に命中した。",
         other = "ブレスは{name($1)}に命中し",
      },

      insanity = {
         "{name($2)}は{name($1)}の腹の亀裂から蛆虫が沸き出るのを見た。",
         "{name($2)}は{name($1)}が屍を貪る姿を目撃した。",
         "{name($2)}は{name($1)}の恐ろしい瞳に震えた。",
         "{name($2)}は{name($1)}の触手に絡まる臓物に吐き気を感じた。",
      },

      map = {
         need_global_map = "それはグローバルマップで読む必要がある。",
         cursed = "呪われた地図は触れると崩れ落ちた。",
         apply = "何かの場所を記した地図のようだ…",
         mark = "○",
      },

      love_potion = {
         cursed = "媚薬は呪われていた。{name($1)}は{you()}を軽蔑のまなざしで見つめた。",
         spill = "{name($1)}は恋の予感がした。",
         self = "{name($1)}は興奮した！",
         other = "{name($1)}は{you()}を熱いまなざしで見つめた。",
      },

      pregnant = "{name($1)}は{name($2)}の口の中に何かを送り込んだ！",

      mirror = "あなたは自分の状態を調べた。",

      milk = {
         cursed = {
            self = "うわ、これは呪われている。なんだかやばい味だ…",
            other = "「ぺっぺっ、まずー」",
         },
         self = "濃厚で病み付きになりそうな味だ。",
         other = "「うまー」",
      },

      alcohol = {
         cursed = {
            "「うぃっ…」",
            "「まずいぜ」",
            "「げー♪」",
            "「腐ったミルクみたいな味だ」",
         },
         normal = {
            "「うぃっ！」",
            "「うまいぜ」",
            "「らららー♪」",
            "「ひっく」",
            "「ふぅ」",
            "「たまらないわ」",
            "「んまっ♪」",
         },
      },

      acid = {
         self = "ぐわぁぁ！",
         apply = "酸が{name($1)}を溶かした。",
      },

      water = {
         self = "*ごくっ* 綺麗な水だ。",
         other = " *ごくっ* ",
      },

      restore_stamina = {
         dialog = "*シュワワ* 刺激的！",
         apply = "{name($1)}のスタミナが少し回復した。",
      },

      restore_stamina_greater = {
         dialog = "*ごくり*",
         apply = "{name($1)}のスタミナはかなり回復した。",
      },

      salt = {
         snail = "塩だ！{name($1)}は溶けはじめた！",
         apply = "「しょっぱ〜」",
      },

      dirty_water = {
         self = "*ごくっ* まずい！",
         other = " *ごくっ* ",
      },

      steal = {
         in_quest = "そんなことをしている余裕はない！",
      },

      mount = {
         no_place_to_get_off = "降りるスペースがない。",

         dismount = "{name($1)}から降りた。",
         dismount_dialog = {
            "「ふぅ」",
            "「乗り心地はよかった？」",
            "「疲れた…」",
            "「またいつでも乗ってね♪」",
         },

         only_ally = "仲間にしか騎乗できない。",
         not_client = "護衛対象には騎乗できない。",
         ride_self = "{name($1)}は自分に乗ろうとした。",
         stays_in_area = "その仲間はこの場所に滞在中だ。",
         currently_riding = "現在{name($1)}は{name($2)}に騎乗している。",

         mount = {
            execute = "{name($1)}に騎乗した({name($1)}の速度: {$2}→",
            suitable = "この生物は乗馬用にちょうどいい！",
            unsuitable = "この生物はあなたを乗せるには非力すぎる。",
            dialog = {
               "「うぐぅ」",
               "「ダイエットしてよ…」",
               "「いくよ！」",
               "「やさしくしてね♪」",
            },
         },
      },

      perform = {
         do_not_know = "{name($1)}は演奏のやり方を知らない。",
      },

      cook = {
         do_not_know = "料理の仕方を知らない。",
      },

      fish = {
         do_not_know = "釣りの仕方を知らない。",
         need_bait = "釣竿には餌が付いていない。",
         not_good_place = "釣りをする場所が見当たらない。",
         cannot_during_swim = "水の中からは釣れない。",
      },

      prayer = "{name($1)}は黄金の輝きに包まれた！",

      create_material = {
         materials = "素材",
         junks = "クズ",
         apply = "たくさんの{$1}が降ってきた！",
      },

      mutation = {
         spell = "{name($1)}は{name($2)}を気の狂いそうな眼差しで見た。",
         resist = "あなたは変異を受け付けなかった。",
         apply = "あなたは変容した！ ",
      },

      cure_mutation = "あなたは元の自分に近づいた気がした。",

      resurrection = {
         cursed = "冥界から死霊が呼び出された！",
         fail = "{name($1)}の力は冥界に及ばなかった。",
         apply = "{$1}は復活した！",
         dialog = "「ありがとう！」",
      },

      uncurse = {
         apply = "{name($1)}の装備品は白い光に包まれた。",
         blessed = "{name($1)}は聖なる光に包み込まれた。",
         item = "幾つかのアイテムが浄化された。",
         equipment = "身に付けている装備の幾つかが浄化された。",
         resist = "幾つかのアイテムは抵抗した。",
      },

      oracle = {
         cursed = "何かがあなたの耳元でささやいたが、あなたは聞き取ることができなかった。",
         no_artifacts = "まだ特殊なアイテムは生成されていない。",

         was_held_by = "{$1}は{$6}年{$5}月に{$3}の{basename($2)}の手に渡った。",
         was_created_at = "{$1}は{$5}年{$4}月に{$2}で生成された。",
      },

      gain_knowledge = {
         suddenly = "突然、",
         furthermore = "さらに、",
         gain = "{you()}は{$1}の魔法の知識を得た。",
         lose = "突然、{you()}は{$1}の魔法の知識を失った。",
      },

      descent = "{name($1)}のレベルが下がった…",
      gain_skill = "{name($1)}は{$2}の技術を獲得した！",

      faith = {
         doubt = "あなたの神はあなたの信仰に疑問を抱いた。",
         apply = "あなたは{$1}の暖かい眼差しを感じた。",
         blessed = "空から三つ葉のクローバーがふってきた。",
      },

      gain_skill_potential = {
         the = "",
         furthermore_the = "さらに",
         increases = "{name($1)}の{$2}の技術の潜在能力が上昇した。",
         decreases = "{name($1)}の{$2}の技術の潜在能力が減少した。",
      },

      troll_blood = {
         apply = "{name($1)}の血は沸きあがるように熱くなった。",
         blessed = "あつつ！",
      },

      gain_potential = {
         blessed = "{name($1)}の全ての能力の潜在能力が上昇した。",
         increases = "{name($1)}の{$2}の潜在能力が上昇した。",
         decreases = "{name($1)}の{$2}の潜在能力が減少した。",
      },

      vanish = "{name($1)}は消え去った。",

      sense = {
         cursed = "あれ…？あなたは軽い記憶障害を受けた。",
         magic_mapping = "{name($1)}は周囲の地形を察知した。",
         sense_object = "{name($1)}は周囲の物質を感知した。",
      },

      vorpal = {
         sound = " *ブシュッ* ",
         ally = "{name($1)}は{name($2)}の首をちょんぎった。",
         other = "{name($1)}は{name($2)}の首をちょんぎり",
      },

      restore = {
         body = {
            apply = "{name($1)}の肉体は復活した。",
            cursed = "{name($1)}の肉体は蝕まれた。",
            blessed = "さらに、{name($1)}の肉体は強化された。",
         },
         mind = {
            apply = "{name($1)}の精神は復活した。",
            cursed = "{name($1)}の精神は蝕まれた。",
            blessed = "さらに、{name($1)}の精神は強化された。",
         },
      },

      escape = {
         cancel = "脱出を中止した。",
         during_quest = "依頼請負中の帰還は法律で禁止されている。それでも帰還する？",
         begin = "周囲の大気がざわめきだした。",
         lord_may_disappear = "このままダンジョンを出ると、この階のクエストは達成できない…",
      },

      ["return"] = {
         cancel = "帰還を中止した。",

         prevented = {
            normal = "不思議な力が帰還を阻止した。",
            ally = "今は帰還できない仲間を連れている。",
            overweight = "どこからか声が聞こえた。「悪いが重量オーバーだ」",
         },

         you_commit_a_crime = "あなたは法を犯した。",
         door_opens = "あなたは次元の扉を開けた。",
         destination_changed = "気まぐれな時の管理者により次元は歪められた！",
      },

      harvest_mana = "{name($1)}のマナが回復した。",
      absorb_magic = "{name($1)}は周囲からマナを吸い取った。",
      poison_attack = "{name($1)}は毒を浴びた！",
      ink_attack = "{name($1)}は墨を浴びた！",
      confusion = "{name($1)}はひどい頭痛におそわれた！",
      paralysis = "{name($1)}は痺れた！",
      sleep = "{name($1)}は甘い液体を浴びた！",

      curse = {
         spell = "{name($1)}は{name($2)}を指差して呪いの言葉を呟いた。",
         no_effect = "あなたは祈祷を捧げ呪いのつぶやきを無効にした。",
         apply = "{name($1)}の{$2}は黒く輝いた。",
      },

      weaken_resistance = {
         nothing_happens = "何も起こらなかったようだ。",
      },

      diary = {
         cat_sister = "なんと、あなたには生き別れた血の繋がっていないぬこの妹がいた！",
         younger_sister = "なんと、あなたには生き別れた血の繋がっていない妹がいた！",
         young_lady = "お嬢さんが空から降ってきた！",
      },

      domination = {
         does_not_work_in_area = "この場所では効果がない。",
         cannot_be_charmed = "{name($1)}は支配できない。",
      },

      map_effect = {
         web = "蜘蛛の巣が辺りを覆った。",
         fog = "辺りを濃い霧が覆った。",
         acid = "酸の水溜りが発生した。",
         fire = "火柱が発生した。",
         ether_mist = "エーテルの霧が発生した。",
      },

      name = {
         prompt = "アーティファクトの新しい銘は？",
         apply = "それは{$1}という銘になった。",
      },

      garoks_hammer = {
         no_effect = "そのアイテムに改良の余地はない。",
         apply = "それは{itemname($1, 1)}になった。",
      },

      change_material = {
         more_power_needed = "アーティファクトの再生成にはパワーが足りない。",
         artifact_reconstructed = "{name($1)}の{itemname($2, 1)}は再生成された。",
         apply = "{name($1)}の{$2}は{itemname($3, 1)}に変化した。",
      },

      deed_of_inheritance = {
         claim = "あなたは遺産相続人として認められた(+{$1})。",
         can_now_inherit = "今やあなたは{$1}個の遺産を相続できる。",
      },

      enchant = {
         apply = "{itemname($1)}は黄金の光に包まれた。",
         resist = "{itemname($1)}は抵抗した。",
      },

      fill_charge = {
         more_power_needed = "充填するには最低でも魔力の貯蓄が10必要だ。",
         spend = "魔力の貯蓄を10消費した(残り{$1})",
         cannot_recharge = "それは充填ができないようだ。",
         cannot_recharge_anymore = "{itemname($1)}はこれ以上充填できないようだ。",
         apply = "{itemname($1)}は充填された(+{$2})。",
         fail = "{itemname($1)}は破裂した。",
         explodes = "{itemname($1)}への充填は失敗した。",
      },

      draw_charge = "{itemname($1)}を破壊して{$2}の魔力を抽出した(計{$3})",

      change = {
         apply = "{name($1)}は変化した。",
         cannot_be_changed = "{name($1)}は変化できない。",
      },

      flying = {
         apply = "{itemname($1, 1)}は羽が生えたように軽くなった。",
         cursed = "{itemname($1, 1)}はずしりと重くなった。",
      },

      alchemy = "それは{itemname($1, 1)}に変容した。",

      create = {
         wall = "床が盛り上がってきた。",
         door = {
            resist = "この壁は魔法を受け付けないようだ。",
            apply = "扉が出現した。",
         },
      },

      swarm = "スウォーム！",
      drop_mine = "{name($1)}は何かを投下した。",
      gravity = "{name($1)}は重力を感じた。",
      mewmewmew = "うみみゃぁ！",
      meteor = "隕石が落ちてきた！",

      cheer = {
         apply = "{name($1)}は仲間を鼓舞した。",
         is_excited = "{name($1)}は興奮した！",
      },

      cure_corruption = {
         apply = "エーテルの抗体があなたの体内に行き渡った。",
         cursed = "エーテルの病菌があなたの体内に行き渡った。",
      },

      eye_of_ether = "{name($1)}に睨まれ、あなたはエーテルに侵食された。",

      insult = {
         apply = "{name($1)}は{name($2)}を罵倒した。",

         man = {
            "「すっこんでろ雑魚め」",
            "「オマエ程度が戦うだと？」",
            "「すぐに殺してやるよ」",
            "「消えろザコめ」",
            "「このかたつむり野郎」",
            "「すぐにミンチにしてやるよ」",
         },

         woman = {
            "「グシャグシャにしてやるわ」",
            "「地べたを這いずりなさい」",
            "「ウージッムシ♪ウージッムシ♪」",
            "「目障りよ」",
            "「もがけ。苦しめ！」",
            "「その下品な眼をくりぬくの」",
            "「このカタツムリが」",
            "「どうしたの？もう終わりなの？」",
            "「潔く、くたばりなさい」",
            "「生まれてきたことを後悔するのね」",
            "「このブタめ」",
            "「すぐにミンチにしてあげる」",
         },
      },

      gaze = "{name($1)}は{name($2)}を睨み付けた。",
      molotov = "{name($1)}は炎に包まれた。",

      scavenge = {
         apply = "{name($1)}は{name($2)}のバックパックを漁った。",
         rotten = "{name($1)}は{itemname($2, 1)}の異臭に気付き手をひっこめた。",
         eats = "{name($1)}は{itemname($2, 1)}を食べた！",
      },

      wizards_harvest = "{itemname($1)}が降ってきた！",
      four_dimensional_pocket = "あなたは四次元のポケットを召喚した。",
   },
}
