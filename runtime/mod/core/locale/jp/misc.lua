-- TODO
-- These text are unclassed. They should be moved to appropriate files.

i18n:add {
   misc = {
      ranking = {
         changed = "ランク変動({$1} {$2}位 → {$3}位) 《{$4}》",
         closer_to_next_rank = "着実に次のランクに近づいている。",
      },

      sound = {
         waken = "{name($1)}は物音に気付き目を覚ました。",
         get_anger = "{name($1)}はキレた。",
         can_no_longer_stand = "「もう我慢できない」",
      },

      hostile_action = {
         glares_at_you = "{name($1)}は嫌な顔をした。",
         gets_furious = "{name($1)}は激怒した。",
         get_excited = "家畜は興奮した！",
      },

      wet = {
         gets_wet = "{name($1)}は濡れた。",
         is_revealed = "{name($1)}の姿があらわになった。",
      },

      fail_to_cast = {
         mana_is_absorbed = "{name($1)}はマナを吸い取られた！",
         is_confused_more = "{name($1)}は余計に混乱した。",
         too_difficult = "難解だ！",
         dimension_door_opens = "{name($1)}は奇妙な力に捻じ曲げられた！",
         creatures_are_summoned = "魔力の渦が何かを召喚した！",
      },

      status_ailment = {
         choked = "「うぐぐ…！」",
         breaks_away_from_gravity = "{name($1)}は重力から抜け出した。",
         calms_down = "{name($1)}はやや落ち着いた。",
         sleepy = "あなたは眠りを必要としている。",
         insane = {
            "{name($1)}「キョキョキョ」",
            "{name($1)}「クワッ」",
            "{name($1)}「シャアァァ」",
            "{name($1)}「ばぶっふ！」",
            "{name($1)}「煮殺せ！」",
            "{name($1)}「許しなさい許しなさい！！」",
            "{name($1)}「フゥハハハー！」",
            "{name($1)}「あ、あ、あ、あ」",
            "{name($1)}「ぴ…ぴ…ぴか…」",
            "{name($1)}「お兄ちゃん！」",
            "{name($1)}「うみみやぁ」",
            "{name($1)}は突然踊りだした。",
            "{name($1)}は着ていたものを脱ぎだした。",
            "{name($1)}はぐるぐる回りだした。",
            "{name($1)}は奇声を発した。",
            "{name($1)}「ねうねう♪ねうねう♪」",
            "{name($1)}「ウージッムシ♪ウージッムシ♪」",
            "{name($1)}「じゃあ殺さなきゃ。うん♪」",
            "{name($1)}「このナメクジがっ」",
            "{name($1)}「おすわり！」",
            "{name($1)}「フーーーーン フーーーーン･･･ フーーーンフ」",
            "{name($1)}「このかたつむり野郎がっ」",
            "{name($1)}「うにゅみゅあ！」",
            "{name($1)}「ごめんなさいごめんなさい！」",
            "{name($1)}「もうすぐ生まれるよ♪」",
            "{name($1)}「フーーーーン フー…クワッ！」",
         },
      },

      death = {
         good_bye = "さようなら… ",
         you_leave_dying_message = "遺言は？",
         dying_message = "「{$1}」",
         date = "{$1}年{$2}月{$3}日",
         you_died = "{$2}で{$1}",
         rank = "{$1}位",
         you_are_about_to_be_buried = "あともう少しで埋葬される…",
         crawl_up = "這い上がる",
         lie_on_your_back = "埋まる",
         you_have_been_buried = "あなたは埋められた。さようなら…（キーを押すと終了します）",
      },

      score = {
         rank = "{$1}位",
         score = "{$1}点",
      },

      resurrect = "{$1}は復活した！",
      artifact_regeneration = "{$1}は{itemname($2)}に形を変えた。",
      black_cat_licks = "{name($1)}は{itemname($2)}をぺろぺろと舐めた。",
      corpse_is_dried_up = "{itemname($1)}は上手い具合に干された。",
      get_rotten = "{itemname($1)}は腐った。",
      extract_seed = "あなたは{itemname($1)}から種を取り出した。",

      curse = {
         gold_stolen = "悪意のある手が{name($1)}の財布から金貨を抜き去った。",
         blood_sucked = "何かが{name($1)}の血を吸った。",
         experience_reduced = "{name($1)}は未熟になった。",
         creature_summoned = "魔力の渦が何かを召喚した！",
      },

      identify = {
         fully_identified = "バックパックの中の{$1}は{itemname($2)}だと判明した。",
         almost_identified = "バックパックの中の{itemname($1)}は{$2}だという感じがする。",
      },

      love_miracle = {
         uh = "「あ…！」",
      },

      pregnant = {
         pukes_out = "しかしすぐに吐き出した。",
         gets_pregnant = "{name($1)}は寄生された。",

         pats_stomach = "{name($1)}は不安げに腹を押さえた。",
         something_is_wrong = {
            "「なにかが産まれそうだよ！」",
            "「腹になにかが…」",
         },
         something_breaks_out = "何かが{name($1)}の腹を破り飛び出した！",
      },

      walk_down_stairs = "階段を降りた。",
      walk_up_stairs = "階段を昇った。",

      quest = {
         kamikaze_attack = {
            message = "伝令「パルミア軍の撤退が完了しました！これ以上ここに留まる必要はありません。機を見て地下から退却してください！」",
            stairs_appear = "階段が現れた。",
         },
      },

      map = {
         jail = {
            repent_of_sin = "あなたは罪を悔いた。",
            guard_approaches = "あなたはガードの足音が近づいてくるのに気付いた。",
            leave_here = "「そこのお前、もう反省したころだろう。出てもいいぞ」",
            unlocks_your_cell = "ガードは面倒くさそうにあなたの牢の扉を開けた。",
         },

         shelter = {
            eat_stored_food = "シェルターの貯蔵食品を食べた。",
            no_longer_need_to_stay = "もうシェルターの中にいる必要は無い。",
         },

         museum = {
            chats = {
               " *ざわざわ* ",
               "「ふむ…悪くないな」",
               "「何だろう、これは」",
               "「ほほう…」",
               "「私も死んだらはく製に…」",
               "「ここが噂の…」",
            },
            chats2 = {
               " *がやがや* ",
               "「やだっ気持ち悪い」",
               "「ねーねーこれ死んでるんでしょ？」",
               "「かわ、いー♪」",
               "「今日はとことん見るぜ」",
               "「触ってもいいの？」",
            },
         },

         shop = {
            chats = {
               " *ざわざわ* ",
               "「これ欲しい〜」",
               "「何だろう、これは」",
               "「お買い物♪」",
               "「金が足りん…」",
               "「ここが噂の…」",
            },
         },
      },

      custom = {
         key_hint = "BackSpace [削除]  ",
         show_room = {
            which_show_room = "どのルームを訪問する？ ",
            list = "ルーム一覧",
            name = "ルームの名称",
         },
         pet_team = {
            which_team = "どのチームと対戦する？",
            list = "ペットチーム一覧",
            name = "チームの名称",
         },

         incompatible = "互換性のないバージョンのファイルです。",
         fail_to_retrieve_file = "ファイルの取得に失敗した。",
         do_you_want_to_delete = "本当に{$1}を削除する？ ",
      },

      no_target_around = "視界内にターゲットは存在しない。",

      ["return"] = {
         forbidden = "依頼請負中の帰還は法律で禁止されている。それでも帰還する？",
         no_location = "この大陸には帰還できる場所が無い。",
         where_do_you_want_to_go = "どの場所に帰還する？",
         air_becomes_charged = "周囲の大気がざわめきだした。",
         lord_of_dungeon_might_disappear = "このままダンジョンを出ると、この階のクエストは達成できない…",
      },

      dungeon_level = "階",

      save = {
         update = "Ver.{$1}のセーブデータをアップデートします。",
         need_to_save_in_town = "アップデートを行うには、街中でセーブしたセーブデータが必要です。",
         take_a_while = "次のプロセスの完了までには、しばらく時間がかかることがあります。",
         cannot_save_in_user_map = "ユーザーマップの中ではセーブできない。",
      },

      living_weapon_taste_blood = "{itemname($1)}は十分に血を味わった！",
      caught_by_assassins = "暗殺者につかまった。あなたはクライアントを守らなければならない。",
      finished_eating = "{kare_wa($1)}{itemname($2, 1)}を食べ終えた。",
      spell_passes_through = "{name($1)}は巻き込みを免れた。",
      shakes_head = "{name($1)}は頭を振った。",

      wields_proudly = {
         the = "",
      },

      ["and"] = "と",

      income = {
         sent_to_your_house = "{$1}goldが給料として振り込まれた。",
         sent_to_your_house2 = "{$1}goldと{$2}個のアイテムが給料として振り込まれた。",
      },

      tax = {
         bill = "請求書が送られてきた。",
         no_duty = "レベルが6に達していないので納税の義務はない。",
         caution = "注意！",
         warning = "警告！！",
         have_to_go_embassy = "早急にパルミア大使館まで行き、税金を納めなければならない。",
         left_bills = "税金を{$1}ヶ月分滞納している。",
         accused = "あなたは税金を{$1}ヶ月滞納した罪で訴えられた。",
         lose_fame = "名声値を{$1}失った。",
      },
   },
}
