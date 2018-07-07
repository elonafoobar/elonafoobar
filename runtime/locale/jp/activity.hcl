locale {
    activity {
        cancel {
            prompt = "${_1}を中断したほうがいいだろうか？ "
            normal = "${name(_1)}は${_2}を中断した。"
            item = "${name(_1)}は行動を中断した。"
        }

        eat {
            start {
                normal = "${name(_1)}は${itemname(_2, 1)}を口に運んだ。"
                in_secret = "${name(_1)}は${itemname(_2, 1)}をこっそりと口に運んだ。"

                mammoth = "「いただきマンモス」"
            }

            finish = "${kare_wa(_1)}${itemname(_2, 1)}を食べ終えた。"
        }

        perform {
            start = "${name(_1)}は${itemname(_2)}の演奏をはじめた。"

            sound {
                _0 = "ﾁｬﾗﾝ♪ "
                _1 = "ﾎﾟﾛﾝ♪ "
                _2 = "ﾀﾞｰﾝ♪ "
                _3 = "ｼﾞｬﾝ♪ "
            }

            gets_angry = "${name(_1)}は激怒した。"

            dialog {
                interest {
                    _0 = "${name(_1)}は歓声を上げた。"
                    _1 = "${name(_1)}は目を輝かせた。"
                    _2 = "「ブラボー」"
                    _3 = "「いいぞ！」"
                    _4 = "${name(_1)}はうっとりした。"
                    _5 = "${name(_1)}は${name(_2)}の演奏を褒め称えた。"
                }
                disinterest {
                    _0 = "「飽きた」"
                    _1 = "「前にも聴いたよ」"
                    _2 = "「またこの曲か…」"
                }
                angry {
                    _0 = "「引っ込め！」"
                    _1 = "「うるさい！」"
                    _2 = "「下手っぴ！」"
                    _3 = "「何のつもりだ！」"
                }
            }

            throws_rock = "${name(_1)}は石を投げた。"

            quality {
                _0 = "まるで駄目だ…"
                _1 = "不評だった…"
                _2 = "もっと練習しなくては…"
                _3 = "演奏を終えた。"
                _4 = "いまいちだ。"
                _5 = "手ごたえがあった。"
                _6 = "納得できる演奏ができた。"
                _7 = "大盛況だ！"
                _8 = "素晴らしい！"
                _9 = "歴史に残る名演だ！"
            }

            tip = "${name(_1)}は合計 ${_2}のおひねりを貰った。"
        }

        sex {
            take_clothes_off = "${name(_1)}は服を脱ぎ始めた。"
            spare_life = "「そ、その${_1}とは体だけの関係${da(_2)}${ore(_2, 3)}は何も知らないから、命だけは…！」"

            dialog {
                _0 = "「きくぅ」"
                _1 = "「もふもふ」"
                _2 = "「くやしい、でも…」"
                _3 = "「はぁはぁ！」"
                _4 = "「ウフフフ」"
            }

            after_dialog {
                _0 = "よかった${yo(_1, 3)}"
                _1 = "す、すごい${yo(_1, 3)}"
                _2 = "も、もうだめ${da(_1, 3)}"
                _3 = "は、激しかった${yo(_1, 3)}"
                _4 = "か、完敗${da(_1, 3)}"
            }

            take = "！さあ、小遣いを受け取って${kure(_1, 3)}"
            take_all_i_have = "！これが${ore(_1, 3)}の財布の中身の全て${da(_1)}"
            gets_furious = "${name(_1)}は激怒した。「なめてんの？」"

            # 「(after_dialog)(take/take_all_i_have)」
            format = "「${_1}${_2}」"
        }

        steal {
            start = "${itemname(_1, 1)}に目星をつけた。"
            notice {
                in_fov = "${name(_1)}は窃盗を見咎めた。"
                out_of_fov = "${name(_1)}は不振な物音に気づいた。"
                dialog {
                    guard = "「貴様、何をしている！」"
                    other = "「ガード！ガード！」"
                }
                you_are_found = "盗みを見咎められた！"
            }
            target_is_dead = "対象は死んでいる"
            cannot_be_stolen = "それは盗めない。"
            you_lose_the_target = "対象が見当たらない。"
            it_is_too_heavy = "重すぎて手に負えない。"
            someone_else_is_using = "そのアイテムは他の誰かが使用中だ。"
            abort = "行動を中断した。"
            succeed = "${itemname(_1)}を盗んだ。"
            guilt = "あなたは良心の呵責を感じた。"
        }

        rest {
            start = "あなたは横になった。"
            finish = "あなたは休息を終えた。"
            drop_off_to_sleep = "あなたはそのまま眠りにおちた…"
        }

        sleep {
            start {
                global = "露営の準備を始めた。"
                other = "寝る仕度を始めた。"
            }

            finish = "あなたは眠り込んだ。"
            but_you_cannot = "しかし、大事な用を思い出して飛び起きた。"

            new_gene {
                title = "遺伝子"
                text = "${name(_1)}とあなたは熱い一夜を供にした。新たな遺伝子が生成された。"

                choices {
                    _0 = "ふぅ"
                }
            }

            slept_for = "${_1}時間眠った。あなたはリフレッシュした。"

            wake_up {
                so_so = "まあまあの目覚めだ。"
                good = "心地よい目覚めだ。潜在能力が伸びた(計${_1}%)"
            }
        }

        construct {
            start = "${itemname(_1, 1)}の建設を始めた。"
            finish = "${itemname(_1, 1)}を作り終えた。"
        }

        pull_hatch {
            start = "${itemname(_1, 1)}のハッチを回し始めた。"
            finish = "${itemname(_1, 1)}のハッチを回し終えた。"
        }

        dig = "${itemname(_1, 1)}を掘り始めた。"

        study {
            start {
                bored = "もう飽きた。"
                studying = "${_1}の学習を始めた。"
                training = "トレーニングを始めた。"
                weather_is_bad = "外が悪天候なので、じっくりと取り組むことにした。"
            }
            finish {
                studying = "${_1}の学習を終えた。"
                training = "トレーニングを終えた。"
            }
        }

        read {
            start = "${kare_wa(_1)}${itemname(_2, 1)}を読み始めた。"
            finish = "${kare_wa(_1)}${itemname(_2, 1)}を読み終えた。"
        }

        harvest {
            sound {
                _0 = " *ザクッ* "
                _1 = " *♪* "
                _2 = " *ズシュ* "
                _3 = " *ジャリ* "
                _4 = " *ザクッ* "
            }
            finish = "${itemname(_1, 1)}を収穫した(${_2})"
        }

        fishing {
            start = "釣りを始めた。"
            fail = "何も釣れなかった…"
            get = "${itemname(_1, 1)}を釣り上げた！"
        }

        material {
            start = "採取を始めた。"
            get = "マテリアル:${_3}を${_2}個${_1}。"

            get_verb {
                dig_up = "掘り当てた"
                fish_up = "釣り上げた。"
                harvest = "採取した。"
                find = "見つけた。"
                get = "入手した"
            }

            lose = "マテリアル:${_1}を${_2}個失った"
            lose_total = "(残り ${_1}個) "

            digging {
                fails = "採掘に失敗した。"
                no_more = "鉱石を掘りつくした。"
            }
            fishing {
                fails = "釣りに失敗した。"
                no_more = "泉は干上がった。"
            }
            searching {
                fails = "採取に失敗した。"
                no_more = "もう何もない。"
            }
            harvesting {
                no_more = "もう目ぼしい植物は見当たらない。"
            }
        }

        dig_spot {
            start {
                global = "地面を掘り始めた。"
                other = "探索を始めた。"
            }

            sound {
                _0 = " *ざくっ* "
                _1 = " *カキン* "
                _2 = " *ごつっ* "
                _3 = " *じゃり* "
                _4 = " *♪* "
            }

            finish = "地面を掘り終えた。"
            something_is_there = " *ガチッ* …何かがある！"
        }

        dig_mining {
            start {
                wall = "壁を掘りはじめた。"
                spot = "鉱石を掘り始めた。"
                hard = "この壁はとても固そうだ！"
            }

            finish {
                wall = "壁を掘り終えた。"
                find = "何かを見つけた。"
            }

            fail = "背中が痛い…掘るのを諦めた。"
        }

        iron_maiden = "突然ふたが閉まった！"
        guillotine = "突然ギロチンが落ちてきた！"
    }
}
