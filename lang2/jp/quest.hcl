locale {
    quest {
        journal_updated = "ジャーナルが更新された。"

        monsters_remaining = "[殲滅依頼]残り${_1}体] "

        area_is_secured = "エリアを制圧した！"
        successfully_slay = "討伐に成功した！"
        you_are_victorious = "あなたは勝利した！"
        stairs_appear = "外への階段が現れた。"

        you_were_defeated = "あなたは敗北した。"
        you_commit_serious_crime = "あなたは重大な罪を犯した!"
        you_failed_to_protect = "あなたは護衛の任務を果たせなかった。"
        you_left_your_client = "あなたはクライアントを置き去りにした。"

        your_team_is_victorious = "あなたのチームは勝利した！"
        your_team_is_defeated = "あなたのチームは敗北した。"

        completed_the_quest = "${_1}から受けた依頼を完了した。"
        failed_the_quest = "${_1}から受けた依頼は失敗に終わった。"
        gain_fame = "${_1}の名声値を手に入れた。"
        lose_fame = "名声値を${_1}失った。"

        escort_failed {
            assassin = "「おい、暗殺者が私の後ろにいるぞ」"
            poison = "「毒が、毒がー！」"
            deadline = "「時間切れだ。こうなったら…」${name(_1)}は火をかぶった。"
        }

        giver {
            have_something_to_ask = "${kimi(3)}に頼みたいことがある${nda()}"
            days_to_perform = "期限は残り${_1}日${da()}"
            how_about_it = "依頼を受けてくれるの${kana(1)}"

            complete {
                done_well = "依頼を無事終わらせたよう${dana()}${thanks(2)}"
                take_reward = "報酬の${_1}を受けとって${kure()}"
                extra_coins = "予想以上にいい働きだったから、幾らか色を付けておいた${yo()}"
                music_tickets = "予想以上の盛り上がりだったから、おまけをあげる${yo()}"
            }
        }

        info {
            gold_pieces = "金貨${_1}枚"
            and = "と"
            no_deadline = "即時"
            days = "${_1}日"
            heavy = "(凄く重い)"
            now = "(現在${_1})"

            harvets {
                text = "${_1}の作物の納入"
            }

            party {
                text = "${_1}の獲得"
                points = "${_1}ポイント"
            }

            escort {
                text = "クライアントを${_1}まで護衛"
            }

            hunt {
                text = "全ての敵の殲滅"
            }

            supply {
                text = "${_1}の納入"
            }

            deliver {
                text = "${_2}に住む${_3}に${_1}を配達"
            }

            conquer {
                text = "${_1}の討伐"
                unknown_monster = "正体不明の存在"
            }

            huntex {
                text = "全ての敵の殲滅"
            }

            collect {
                text = "依頼人のために${_2}から${_1}を調達"
                target = "${_1}に住む人物"
            }
        }

        journal {
            complete = "依頼 完了"
            job = "依頼"
            client   = "依頼: "
            location = "場所: "
            deadline = "期限: "
            reward   = "報酬: "
            detail   = "内容: "
            remaining = "残り"
            report_to_the_client = "あとは報告するだけだ。"
        }
    }
}
