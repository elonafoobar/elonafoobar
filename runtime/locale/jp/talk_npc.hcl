locale {
    talk {
        will_not_listen = "${name(_1)}は耳を貸さない。"
        is_sleeping = "${name(_1)}はぐっすり眠っている…"
        is_busy = "${name(_1)}はお取り込み中だ…"
        ignores_you = "…(あなたを無視している)"

        window {
            impress = "友好"
            attract = "興味"
            fame = "名声 ${_1}"
            shop_rank = "店の規模:${_1}"

            of = "${_2} ${_1}"
        }

        tag {
            ref = "${_1}"
        }

        npc {
            common {
                choices {
                    talk = "話がしたい"
                    trade = "アイテム交換"
                    sex = "気持ちいいことしない？"
                }

                thanks = "${thanks(_1, 2)}"
                you_kidding = "冷やかし${ka(_1, 1)}"
                hand_over = "${itemname(_1, 1)}を手渡した。"

                sex {
                    prompt = "なかなかの体つき${dana(_1)}よし、買${u(_1, 2)}"

                    choices {
                        accept = "はじめる"
                        go_back = "やめる"
                    }

                    start = "いく${yo(_1, 2)}"
                    response = "うふふ"
                }
            }

            quest_giver {
                choices {
                    about_the_work = "依頼について"
                    here_is_item = "${itemname(_1, 1)}を納入する"
                    here_is_delivery = "配達物を渡す"
                }

                about {
                    during = "頼んでいた依頼は順調${kana(_1, 1)}"

                    choices {
                        take = "受諾する"
                        leave = "やめる"
                    }

                    too_many_unfinished = "未完了の依頼が多すぎじゃない${kana(_1, 1)}この仕事は、安心してまかせられない${yo(_1)}"
                    backpack_full = "どうやらバックパックが一杯のよう${da(_1)}持ち物を整理してまた来て${kure(_1)}"
                    party_full = "これ以上仲間を連れて行けないよう${da(_1)}人数を調整してまた来て${kure(_1)}"

                    thanks = "${thanks(_1)}期待してい${ru(_1)}"
                    here_is_package = "これが依頼の品物${da(_1)}期限には十分気をつけて${kure(_1)}"
                }

                accept {
                    hunt = "では、早速案内するので、モンスターを一匹残らず退治して${kure(_1)}"
                    harvest = "畑までは案内するから、しっかりと期限内に作物を納入して${kure(_1)}"
                    party = "ついて来て${kure(_1)}パーティー会場まで案内する"
                }

                finish {
                    escort = "無事に到着できてほっとした${yo(_1)}${thanks(_1, 2)}"
                }
            }

            servant {
                choices {
                    fire = "解雇する"
                }

                fire {
                    prompt = "(${name(_1)}は悲しそうな目であなたを見ている。本当に縁を切る？)"

                    choices {
                        yes = "切る"
                        no = "やめる"
                    }

                    you_dismiss = "${name(_1)}を解雇した… "
                }
            }

            ally {
                choices {
                    wait_at_town = "街で待機しろ"
                    ask_for_marriage = "婚約を申し込む"
                    make_gene = "遺伝子を残す"
                    silence {
                        start = "黙らせる"
                        stop = "喋らせる"
                    }
                    abandon = "縁を切る"
                }

                wait_at_town = "(あなたは、${name(_1)}に街で待っているように指示した)"

                marriage {
                    refuses = "(${name(_1)}はやんわりと断った)"
                    accepts = "はい…喜んで。"
                }

                make_gene {
                    refuses = "こんな場所では嫌よ"
                    accepts = "いやん、あなたったら…"
                }

                silence {
                    start = "(${name(_1)}はしゅんとなった…)"
                    stop = "(${name(_1)}はあなたに抱きついた)"
                }

                abandon {
                    prompt = "(${name(_1)}は悲しそうな目であなたを見ている。本当に縁を切る？)"

                    choices {
                        yes = "切る"
                        no = "やめる"
                    }

                    you_abandoned = "${name(_1)}と別れた…"
                }
            }

            maid {
                choices {
                    think_of_house_name = "家の名前を考えてくれ"
                    meet_guest = "客に会う"
                    do_not_meet = "追い返す"
                }

                think_of_house_name {
                    suffixes = [
                        "${_1}の家",
                        "${_1}邸",
                        "${_1}城",
                        "${_1}ハーレム",
                        "${_1}の巣窟",
                        "${_1}ハウス",
                        "${_1}ホーム",
                        "${_1}の住処",
                        "${_1}宅",
                        "${_1}の隠れ家",
                        "${_1}ドーム"
                    ]
                    come_up_with = "そう${dana(_2)}これからこの家の名前は${_1}${da(_2)}"
                }

                do_not_meet = "追い返す${yo(_1)}"
            }

            trainer {
                choices {
                    train {
                        ask = "訓練したい"
                        accept = "訓練する"
                    }
                    learn {
                        ask = "新しい能力を覚えたい"
                        accept = "習得する"
                    }
                    go_back = "やめる"
                }
                leave = "訓練が必要なときは、声をかけて${kure(_1)}"
                cost {
                    training = "${_1}の能力を訓練するには${_2} platかかるけどいい${kana(_3, 1)}"
                    learning = "${_1}の能力を習得するには${_2} platかかるけどいい${kana(_3, 1)}"
                }
                finish {
                    training = "訓練は完了し${ta(_1)}潜在能力が伸びているはずなので、後は自分で鍛えて${kure(_1)}"
                    learning = "可能な限りの知識は教え${ta(_1)}後は存分に訓練して${kure(_1)}"
                }
            }

            shop {
                choices {
                    buy = "買いたい"
                    sell = "売りたい"
                    attack = "襲撃するよ"
                    invest = "投資したい"
                    ammo = "矢弾の充填"
                }

                criminal {
                    buy = "犯罪者に売る物はない${yo(_1)}"
                    sell = "犯罪者から買う物はない${yo(_1)}"
                }

                ammo {
                    no_ammo = "充填する必要はないみたい${da(_1)}"
                    cost = "そう${dana(_2, 3)}、全ての矢弾を補充すると${_1} gold${da(_2)}"

                    choices {
                        pay = "頼む"
                        go_back = "やめる"
                    }
                }

                invest {
                    ask = "投資をしてくれる${noka(_2, 1)}${_1} goldかかるけどいいの${kana(_2, 1)}"

                    choices {
                        invest = "投資する"
                        reject = "やめる"
                    }
                }

                attack {
                    dialog = "${rob(_1, 2)}"

                    choices {
                        attack = "神に祈れ"
                        go_back = "いや、冗談です"
                    }
                }
            }

            innkeeper {
                choices {
                    eat = "食事をとる"
                    go_to_shelter = "シェルターに入る"
                }

                eat {
                    not_hungry = "腹が減っているようにはみえない${yo(_1)}"
                    here_you_are = "${dozo(_1)}"

                    results = [
                        "なかなか美味しかった。",
                        "悪くない。",
                        "あなたは舌鼓をうった。"
                    ]
                }

                go_to_shelter = "悪天候時はシェルターを無料で開放している${nda(_1)}すみやかに避難して${kure(_1)}"
            }

            wizard {
                choices {
                    identify = "鑑定したい"
                    identify_all = "全て鑑定してほしい"
                    investigate = "調査したい"
                    return = "帰還したい"
                }

                identify {
                    already = "鑑定するアイテムはないみたい${da(_1)}"
                    finished = "鑑定結果はこの通り${da(_1)}"
                    need_investigate = "さらなる知識を求めるのなら、調査する必要が${aru(_1)}"

                    count = "${_2}個の未判明のアイテムのうち、${_1}個のアイテムが完全に判明した。"
                }

                return = "ここからふもとに下りるのは不便だから、ボランティアで帰還サービスをやってい${ru(_1)}${kimi(_1, 3)}も帰還サービスを希望${kana(_1)}"

            }

            informer {
                choices {
                    show_adventurers = "冒険者の情報"
                    investigate_ally = "仲間の調査"
                }

                show_adventurers = "お目当ての情報は見つかった${kana(_1)}"

                investigate_ally {
                    cost = "10000 goldかかるけどいい${ka(_1, 1)}"

                    choices {
                        pay = "調査する"
                        go_back = "やめる"
                    }
                }
            }

            healer {
                choices {
                    restore_attributes = "能力の復元"
                }

                restore_attributes = "治療が完了し${ta(_1)}"
            }

            bartender {
                choices {
                    call_ally = "仲間を呼び戻す"
                }

                call_ally {
                    no_need = "そいつは呼び戻す必要はないよう${da(_1)}"
                    cost = "そいつを呼び戻すには、${_1} gold必要${da(_2)}"

                    choices {
                        pay = "呼び戻す"
                        go_back = "やめる"
                    }

                    brings_back = "(バーテンが店の奥から${name(_2)}を連れてきた)${dozo(_1)}"
                }
            }

            adventurer {
                choices {
                    hire = "護衛を依頼する"
                    join = "仲間に誘う"
                }

                hire {
                    cost = "${ore(_2, 3)}の剣が必要な${noka(_2, 1)}そう${dana(_2, 3)}、${_1} gold払うならば、7日間護衛を引き受け${ru(_2)}"

                    choices {
                        pay = "頼む"
                        go_back = "やめる"
                    }

                    you_hired = "${name(_1)}を雇った。"
                }

                join {
                    too_weak = "${kimi(_1, 3)}の仲間になれと？あまりにも力の差がありすぎる${na(_1)}"
                    not_known = "${kimi(_1, 3)}の仲間になれと？悪い${ga(_1, 3)}お断り${da(_1)}"
                    party_full = "これ以上仲間を連れて行けないよう${da(_1)}人数を調整してまた来て${kure(_1)}"
                    accept = "${kimi(_1, 3)}となら上手くやっていけそう${da(_1)}${yoro(_1, 2)}"
                }
            }

            arena_master {
                choices {
                    enter_duel = "試合に出る[決闘]"
                    enter_rumble = "試合に出る[ランブル]"
                    score = "成績を聞く"
                }

                enter {
                    game_is_over = "残念だが、今日の試合はもう終了し${ta(_1)}"
                    target = "今日の対戦相手は${_1}${da(_2)}挑戦する${noka(_2, 1)}"
                    target_group = "対戦相手はレベル${_1}以下の相手複数${da(_2)}挑戦する${noka(_2, 1)}"

                    choices {
                        enter = "挑戦する"
                        leave = "やめる"
                    }

                    cancel = "用があるときは声をかけて${kure(_1)}"
                }

                streak = "現在は${_1}連勝中${da(_2)}5連勝,20連勝毎にボーナスを与え${ru(_2)}"
            }

            pet_arena_master {
                choices {
                    register_duel = "ペットデュエル"
                    register_team = "チームバトル"
                }

                register {
                    target = "一対一の戦いで、対戦相手はレベル${_1}ぐらいの相手${da(_2)}挑戦する${noka(_2, 1)}"
                    target_group = "人同士のチームバトルで、対戦相手はレベル${_2}以下の相手複数${da(_3)}挑戦する${noka(_3, 1)}"

                    choices {
                       enter = "挑戦する"
                       leave = "やめる"
                    }
                }
            }

            slave_trader {
                choices {
                    buy = "奴隷を買う"
                    sell = "奴隷を売る"
                }

                buy {
                    cost = "そう${dana(_3)}${_1}を${_2} goldでどう${da(_3, 1)}"

                    choices {
                        pay = "買い取る"
                        go_back = "やめる"
                    }

                    you_buy = "${_1}を買い取った。"
                }

                sell {
                    price = "なかなかの身体つき${dana(_2)}${_1} goldでどう${da(_2, 1)}"

                    choices {
                        deal = "売る"
                        go_back = "やめる"
                    }

                    you_sell_off = "${_1}を売り飛ばした。"
                }
            }

            horse_keeper {
                choices {
                    buy = "馬を買う"
                }
            }

            sister {
                choices {
                    buy_indulgence = "免罪符を買いたい"
                }

                buy_indulgence {
                    karma_is_not_low = "その程度の罪なら自分でなんとかしなさい。"
                    cost = "免罪符を希望する${noka(_2, 1)}${_1} goldかかるけどいいの${kana(_2, 1)}"

                    choices {
                        buy = "買う"
                        go_back = "やめる"
                    }
                }
            }

            guard {
                choices {
                    where_is = "${basename(_1)}の居場所を聞く"
                    lost_wallet = "落し物の財布を届ける"
                    lost_suitcase = "落し物のカバンを届ける"
                }

                where_is {
                    direction {
                        north = "北"
                        south = "南"
                        east = "東"
                        west = "西"
                    }

                    dead = "奴なら今は死んでいる${yo(_1, 2)}"
                    very_close = "${basename(_2)}ならすぐ近くにいる${yo(_3)}${_1}の方を向いてごらん。"
                    close = "ちょっと前に${_1}の方で見かけた${yo(_3)}"
                    moderate = "${basename(_2)}なら${_1}の方角を探してごらん。"
                    far = "${basename(_2)}に会いたいのなら、${_1}にかなり歩く必要があ${ru(_3)}"
                    very_far = "${basename(_2)}${ka(_3, 3)}、ここから${_1}の物凄く離れた場所にいるはず${da(_3)}"
                }

                lost {
                    empty {
                        dialog = "む…中身が空っぽ${dana(_1, 2)}"
                        response = "しまった…"

                    }
                    dialog = "わざわざ落し物を届けてくれた${noka(_1)}${kimi(_1, 3)}は市民の模範${da(_1)}${thanks(_1)}"
                    response = "当然のことだ"

                    found_often {
                        dialog {
                            _0 = "む、また${kimi(_1, 3)}${ka(_1)}随分と頻繁に財布を見つけられるもの${dana(_1)}"
                            _1 = "（…あやしい）"
                        }
                        response = "ぎくっ"
                    }
                }
            }

            spell_writer {
                choices {
                    reserve = "魔法書の予約"
                }
            }

            prostitute {
                choices {
                    buy = "暗い場所に移ろう"
                }

                buy = "そう${dana(_2)}金貨${_1}枚を前払いで${kure(_2)}"
            }

            caravan_master {
                choices {
                    hire = "キャラバンを雇う"
                }

                hire {
                    tset = "つぇｔ"

                    choices {
                        go_back = "やめる"
                    }
                }
            }

            moyer {
                choices {
                    sell_paels_mom = "パエルの母を売る"
                }

                sell_paels_mom {
                    prompt = "ほほう、モンスターの顔をした人間か。見世物としてなかなかいけそうだ。金貨50000枚で買い取ろう。"

                    choices {
                        sell = "売る"
                        go_back = "やめる"
                    }

                    you_sell = "パエルの母親を売った…"
                }
            }
        }
    }
}
