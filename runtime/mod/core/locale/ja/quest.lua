local I18N = ELONA.require("core.I18N")

I18N.add {
   quest = {
      journal_updated = "ジャーナルが更新された。",
      minutes_left = "クエスト[残り{$1}分]",
      completed = "クエストを達成した！",
      completed_taken_from = "{$1}から受けた依頼を完了した。",
      failed_taken_from = "{$1}から受けた依頼は失敗に終わった。",
      gain_fame = "{$1}の名声値を手に入れた。",
      lose_fame = "名声値を{$1}失った。",

      hunt = {
         complete = "エリアを制圧した！",
         remaining = "[殲滅依頼]残り{$1}体 ",
      },
      party = {
         is_over = "パーティーは終了した。",
         final_score = "最終得点は{$1}ポイントだった！",
         complete = "パーティーは大盛況だった！",
         fail = "パーティーはぐだぐだになった…",

         is_satisfied = "{basename($1)}は満足した。",
         total_bonus = "(合計ボーナス:{$1}%) ",
      },
      collect = {
         complete = "無事に納入を終えた！",
         fail = "納入は間に合わなかった…",
      },
      conquer = {
         complete = "討伐に成功した！",
         fail = "討伐に失敗した…",
      },
      deliver = {
         you_commit_a_serious_crime = "あなたは重大な罪を犯した!",
      },
      escort = {
         complete = "あなたは無事に護衛の任務を終えた。",
         you_failed_to_protect = "あなたは護衛の任務を果たせなかった。",
         you_left_your_client = "あなたはクライアントを置き去りにした。",

         failed = {
            assassin = "「おい、暗殺者が私の後ろにいるぞ」",
            poison = "「毒が、毒がー！」",
            deadline = "「時間切れだ。こうなったら…」{name($1)}は火をかぶった。",
         },
      },
      arena = {
         you_are_victorious = "あなたは勝利した！",
         your_team_is_victorious = "あなたのチームは勝利した！",
         your_team_is_defeated = "あなたのチームは敗北した。",
         stairs_appear = "外への階段が現れた。",
      },

      you_were_defeated = "あなたは敗北した。",

      giver = {
         have_something_to_ask = "{kimi($1, 3)}に頼みたいことがある{nda($1)}",
         days_to_perform = "期限は残り{$1}日{da($2)}",
         how_about_it = "依頼を受けてくれるの{kana($1, 1)}",

         complete = {
            done_well = "依頼を無事終わらせたよう{dana($1)}{thanks($1, 2)}",
            take_reward = "報酬の{$1}を受けとって{kure($1)}",
            extra_coins = "予想以上にいい働きだったから、幾らか色を付けておいた{yo($1)}",
            music_tickets = "予想以上の盛り上がりだったから、おまけをあげる{yo($1)}",
         },
      },

      info = {
         gold_pieces = "金貨{$1}枚",
         ["and"] = "と",
         no_deadline = "即時",
         days = "{$1}日",
         heavy = "(凄く重い)",
         now = "(現在{$1})",

         harvest = {
            text = "{$1}の作物の納入",
         },

         party = {
            text = "{$1}の獲得",
            points = "{$1}ポイント",
         },

         escort = {
            text = "クライアントを{$1}まで護衛",
         },

         hunt = {
            text = "全ての敵の殲滅",
         },

         supply = {
            text = "{$1}の納入",
         },

         deliver = {
            text = "{$2}に住む{$3}に{$1}",
            deliver = "を配達",
         },

         conquer = {
            text = "{$1}の討伐",
            unknown_monster = "正体不明の存在",
         },

         huntex = {
            text = "全ての敵の殲滅",
         },

         collect = {
            text = "依頼人のために{$2}から{$1}を調達",
            target = "{$1}に住む人物",
         },
      },

      journal = {
         complete = "依頼 完了",
         job = "依頼",
         client = "依頼: ",
         location = "場所: ",
         deadline = "期限: ",
         reward = "報酬: ",
         detail = "内容: ",
         remaining = "残り",
         report_to_the_client = "あとは報告するだけだ。",
      },
   },
}
