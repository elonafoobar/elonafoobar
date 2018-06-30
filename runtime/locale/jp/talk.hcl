locale {
    talk {
        will_not_listen = "${name(_1)} won't listen."
        is_sleeping = "${name(_1)} is sleeping."
        is_busy = "${name(_1)} is in the middle of something."

        window {
            impress = "Impress"
            attract = "Attract"
            fame = " Fame: "
            shop_rank = " Shop Rank:"
        }

        npc {
            common {
                choices {
                    talk = "話がしたい"
                    trade = "アイテム交換"
                    score = "成績を聞く"
                    sex = "気持ちいいことしない？"
                }

                thanks = "${thanks(2)}"
                you_kidding = "冷やかし${ka(1)}"

                sex {
                    prompt = "なかなかの体つき${dana()}よし、買${u(2)}"

                    choices {
                        accept = "はじめる"
                        go_back = "やめる"
                    }

                    start = "いく${yo(2)}"
                    response = "うふふ"
                }
            }

            quest_giver {
                choices {
                    about_the_work = "依頼について"
                    here_is_item = "${itemname(_1, 1)}を納入する"
                    here_is_delivery = "配達物を渡す"
                }

                hand_over = "${itemname(_1, 1)}を手渡した。"
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
                    ask_for_hand = "婚約を申し込む"
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
                    with_pleasure = "はい…喜んで。"
                }

                make_gene {
                    refuse = "こんな場所では嫌よ"
                    accept = "いやん、あなたったら…"
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
                    think_of_name = "家の名前を考えてくれ"
                    meet_guest = "客に会う"
                    do_not_meet = "追い返す"
                }

                think_of_name {
                    suffixes {
                        _0 = "の家"
                        _1 = "邸"
                        _2 = "城"
                        _3 = "ハーレム"
                        _4 = "の巣窟"
                        _5 = "ハウス"
                        _6 = "ホーム"
                        _7 = "の住処"
                        _8 = "宅"
                        _9 = "の隠れ家"
                        _10 = "ドーム"
                    }
                    come_up_with = "そう${dana()}これからこの家の名前は${_1}${da()}"
                }

                do_not_meet = "追い返す${yo()}"
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
                leave = "訓練が必要なときは、声をかけて${kure()}"
                cost {
                    training = "${_1}の能力を訓練するには${_2}かかるけどいい${kana(1)}"
                    learning = "${_1}の能力を習得するには${_2}かかるけどいい${kana(1)}"
                }
                finish {
                    training = "訓練は完了し${ta()}潜在能力が伸びているはずなので、後は自分で鍛えて${kure()}"
                    learning = "可能な限りの知識は教え${ta()}後は存分に訓練して${kure()}"
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

                criminal_buy = "犯罪者に売る物はない${yo()}"
                criminal_sell = "犯罪者から買う物はない${yo()}"

                ammo {
                    no_ammo = "充填する必要はないみたい${da()}"
                    cost = "そう${dana(3)}、全ての矢弾を補充すると${_1}${da()}"

                    choices {
                        pay = "頼む"
                        go_back = "やめる"
                    }
                }

                invest {
                    ask = "投資をしてくれる${noka(1)}${_2}かかるけどいいの${kana(1)}"

                    choices {
                        invest = "投資する"
                        reject = "やめる"
                    }
                }

                attack {
                    dialog = "${rob(2)}"

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
                    not_hungry = "腹が減っているようにはみえない${yo}"
                    here_you_are = "${dozo()}"
                }

                go_to_shelter = "悪天候時はシェルターを無料で開放している${nda()}すみやかに避難して${kure()}"
            }

            wizard {
                choices {
                    identify = "鑑定したい"
                    identify_all = "全て鑑定してほしい"
                    investigate = "調査したい"
                    return = "帰還したい"
                }

                identify {
                    already = "鑑定するアイテムはないみたい${da()}"
                    finished = "鑑定結果はこの通り${da()}"
                    need_investigate = "さらなる知識を求めるのなら、調査する必要が${aru()}"

                    count = "${_2}個の未判明のアイテムのうち、${_1}個のアイテムが完全に判明した。"
                }

                return = "ここからふもとに下りるのは不便だから、ボランティアで帰還サービスをやってい${ru()}${kimi(3)}も帰還サービスを希望${kana()}"

            }

            informer {
                choices {
                    show_adventurers = "冒険者の情報"
                    investigate_ally = "仲間の調査"
                }

                show_adventurers {
                    done = "お目当ての情報は見つかった${kana()}"
                }

                investigate_ally {
                    cost = "10000 goldかかるけどいい${ka(1)}"

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

                restore_attributes = "治療が完了し${ta()}"
            }

            bartender {
                choices {
                    call_back_allies = "仲間を呼び戻す"
                }

                call_back_allies {
                    no_need = "そいつは呼び戻す必要はないよう${da()}"
                    cost = "そいつを呼び戻すには、${_1}必要${da()}"

                    choices {
                        pay = "呼び戻す"
                        go_back = "やめる"
                    }

                    brings_back = "(バーテンが店の奥から${name(_2)}を連れてきた)${dozo()}"
                }
            }

            adventurer {
                choices {
                    hire = "護衛を依頼する"
                    join = "仲間に誘う"
                }

                hire {
                    cost = "${ore(3)}の剣が必要な${noka(1)}そう${dana(3)}、${_1}払うならば、7日間護衛を引き受け${ru()}"

                    choices {
                        pay = "頼む"
                        go_back = "やめる"
                    }

                    you_hired = "${name(_1)}を雇った。"
                }

                join {
                    too_weak = "${kimi(3)}の仲間になれと？あまりにも力の差がありすぎる${na()}"
                    not_known = "${kimi(3)}の仲間になれと？悪い${ga(3)}お断り${da()}"
                    party_full = "これ以上仲間を連れて行けないよう${da()}人数を調整してまた来て${kure()}"
                    accept = "${kimi(3)}となら上手くやっていけそう${da()}${yoro(2)}"
                }
            }

            arena_master {
                choices {
                    enter_duel = "試合に出る[決闘]"
                    enter_rumble = "試合に出る[ランブル]"
                }

                enter {
                    game_is_over = "残念だが、今日の試合はもう終了し${ta()}"
                    target = "今日の対戦相手は${_1}${da()}挑戦する${noka(1)}"
                    target_group = "対戦相手はレベル${_1}以下の相手複数${da()}挑戦する${noka(1)}"

                    choices {
                        enter = "挑戦する"
                        leave = "やめる"
                    }

                    leave = "用があるときは声をかけて${kure()}"
                }

                streak = "現在は${_1}連勝中${da()}5連勝,20連勝毎にボーナスを与え${ru()}"
            }

            pet_arena_master {
                choices {
                    register_duel = "ペットデュエル"
                    register_team = "チームバトル"
                }

                register {
                    target = "一対一の戦いで、対戦相手はレベル${_1}ぐらいの相手${da()}挑戦する${noka(1)}"
                    target_group = "人同士のチームバトルで、対戦相手はレベル${_2}以下の相手複数${da()}挑戦する${noka(1)}"

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

                sell {
                    price = "なかなかの身体つき${dana()}${_1}でどう${da(1)}"

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

                buy {
                    cost = "そう${dana()}${_1}を${_2}でどう${da(1)}"

                    choices {
                        pay = "買い取る"
                        go_back = "やめる"
                    }

                    you_buy = "${_1}を買い取った。"
                }
            }

            sister {
                choices {
                    buy = "免罪符を買いたい"
                }

                buy {
                    karma_is_not_low = "その程度の罪なら自分でなんとかしなさい。"
                    cost = "免罪符を希望する${noka(1)}${_1}かかるけどいいの${kana(1)}"

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
                    lost_suitcase = "落し物のカバンを届ける。"
                }

                where_is {
                    direction {
                        north = "北"
                        south = "南"
                        east = "東"
                        west = "西"
                    }

                    dead = "奴なら今は死んでいる${yo(2)}"
                    very_close = "${basename(_2)}ならすぐ近くにいる${yo()}${_1}の方を向いてごらん。"
                    close = "ちょっと前に${_2}の方で見かけた${yo()}"
                    moderate = "${basename(_2)}なら${_1}の方角を探してごらん。"
                    far = "${basename(_1)}に会いたいのなら、${_2}にかなり歩く必要があ${ru()}"
                    very_far = "${basename(_2)}${ka(3)}、ここから${_1}の物凄く離れた場所にいるはず${da()}"
                }

                lost {
                    empty {
                        dialog = "む…中身が空っぽ${dana(2)}"
                        response = "しまった…"

                    }
                    dialog = "わざわざ落し物を届けてくれた${noka()}${kimi(3)}は市民の模範${da()}${thanks()}"
                    response = "当然のことだ"

                    found_often {
                        dialog {
                            _0 = "む、また${kimi(3)}${ka()}随分と頻繁に財布を見つけられるもの${dana()}"
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

                buy {
                    price = "そう${dana()}金貨${_1}枚を前払いで${kure()}"
                }
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

        # TODO: organize
        visitor {
            wanted_to_say_hi = "I just wanted to say hi."

            adventurer {
                new_year {
                    dialog_1 = "Happy new year!"
                    dialog_2 = "I've brought you a gift today, here."
                    throws = "${name(_1)} throws you ${itemname(_1, 1)}."
                }
                hate {
                    dialog = "You scum! You won't get away from me now!"
                    text = "\"Eat this!\""
                    throws = "${name(_1)} throws molotov."
                }
                like {
                    dialog = "Here, take this!"
                    receive = "You receive ${itemname(_1, 1)}."
                    wonder_if = "Wonder if we can reach 100 friends? ♪"
                }
                trainer {
                    learn {
                        dialog = "I can teach you the art of ${_1} for a friendly price of ${_2} platinum pieces. Do you want me to train you?"
                        accept = "Teach me the skill."
                        after = "Fantastic! You've learned the skill in no time. I'm glad I could help."
                    }
                    train {
                        dialog = "I can train your ${_1} skill for a friendly price of ${_2} platinum pieces. Do you want me to train you?"
                        accept = "Train me."
                        after = "Marvelous! The training is now complete. I think you've improved some potential."
                    }
                    pass = "I think I'll pass."
                    ask_again = "I see. I'll ask you again at some time in the future."
                }
                friendship {
                    dialog = "As a pledge of friendship, here's something for you!"
                    no_empty_spot = "Your home has no empty spot..."
                    receive = "You receive ${itemname(_1, 1)}."
                }
                souvenir {
                    dialog = "I just stopped by to see you. Oh, I happen to have a gift for you too."
                    inventory_is_full = "Your inventory is full..."
                    receive = "You receive ${itemname(_1, 1)}."
                }
                materials {
                    dialog = "I found these during my journey. Thought you could find them useful."
                    receive = "${name(_1)} gives you a bag full of materials."
                }
                favorite_skill {
                    dialog = "${_1} is one of my favorite skills."
                }
                favorite_stat {
                    dialog = "I'm proud of my good ${_1}."
                }
                conversation {
                    dialog = "Hey ${basename(_1)}, how's your journey? I was bored to death so I decided to make a visit to you!"
                    hold = "You hold an amusing conversation with ${name(_1)}!"
                }
                drink {
                    dialog = "Let's have a drink and deepen our friendship!"
                    cheers = "\"Cheers!\""
                }
            }
            trainer {
                no_more_this_month = "No more training in this month."
                dialog {
                    member = "As a member of ${_1} you have to forge your talent to live up to our reputation. For only ${_2} platinum coins, I'll improve the potential of your talent."
                    nonmember = "Training! Training! At the end, only thing that saves your life is training! For only ${_1} platinum coins, I'll improve the potential of your talent."
                }

                choices {
                    not_today = "Not today."
                    improve = "I want to improve ${_1}."
                }
                regret = "You'll regret this!"
                potential_expands = "${name(_1)}${his_owned(_1)} potential of ${_2} greatly expands."
                after = "Good. You show a lot of potential."
            }
            beggar {
                no_money = "I got no money to buy food. Will you spare me some coins?"
                spare = "You spare ${_1} gold pieces"
                after = "Thanks! I'll never forget this."
                cheap = "You're so cheap!"
            }
            punk {
                choices {
                    yes = "Yes."
                    no = "No."
                    come_on = "Come on!"
                }
                are_you_ready = "So, are you ready?"
                no_turning_back = "Okay, no turning back now!"
                hump = "Hump!"
            }
            mysterious_producer {
                want_to_be_star = "You want to be a star?"
                no_turning_back = "Okay, no turning back now!"
            }
            merchant {
                choices {
                    buy = "I want to buy something."
                    sell = "I want to sell something."
                    not_now = "Not now."
                }
                dialog = "This is your lucky day. I wouldn't normally show my discounted goods to commoners but since I feel so good today..."
                regret = "I hope you won't regret it later."
            }
        }
    }
}
