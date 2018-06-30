locale {
    talk {
        will_not_listen = "${name(_1)}は耳を貸さない。"
        is_sleeping = "${name(_1)}はぐっすり眠っている…"
        is_busy = "${name(_1)}はお取り込み中だ…"

        window {
            impress = "友好"
            attract = "興味"
            fame = " 名声 "
            shop_rank = " 店の規模:"
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

        visitor {
            wanted_to_say_hi = "まあ、とくに用もないんだけど${na()}"
            receive = "${name(_2)}に${itemname(_1, 1)}をもらった！"

            adventurer {
                new_year {
                    dialog_1 = "明けましておめでとう${da(2)}"
                    dialog_2 = "日ごろの感謝の意をこめてこれをあげる${yo()}"
                    throws = "${name(_1)}は${itemname(_2, 1)}を置いていった。"
                }
                hate {
                    dialog ="貴様！見つけた${yo(2)}"
                    text ="「これでも食らうがいい${yo(2)}」"
                    throws = "${name(_1)}は火炎瓶を投げた。"
                }
                like {
                    dialog ="これ、あげ${ru(2)}"
                    wonder_if ="友達100人できるかな♪"
                }
                trainer {
                    choices {
                        learn ="習得する"
                        train ="訓練する"
                        pass = "遠慮しとく"
                    }
                    learn {
                        dialog = "${_1}のスキルを、友達価格の${_2}で教えてあげてもいい${ga(3)}どう${kana(1)}"
                        after ="新しい技術をどうやら習得できたようだ${na()}"
                    }
                    train {
                        dialog = "${_1}のスキルを、友達価格の${_2}で訓練してもいい${ga(3)}どう${kana(1)}"
                        after ="よし、これで訓練は終わり${da()}かなり潜在能力が伸びた${yo(2)}"
                    }
                    pass = "わかった${yo()}またしばらくしてから尋ねてみ${ru()}"
                }
                friendship {
                    dialog ="友達の証としてこれをあげ${ru(2)}大事に使って${yo()}"
                    no_empty_spot ="部屋が一杯で置けなかった…"
                }
                souvenir {
                    dialog = "近くまで来たので寄ってみた${nda()}ついでだから、土産にこれをあげ${ru()}"
                    inventory_is_full ="所持品が一杯で受け取れなかった…"
                    receive = "${itemname(_1, 1)}を受け取った。"
                }
                materials {
                    dialog ="旅の途中にこんなものを拾った${nda()}${kimi(3)}の役に立つと思って持ってきた${yo()}"
                    receive = "${name(_1)}は色々なものが詰まった袋を、あなたに手渡した。"
                }
                favorite_skill {
                    dialog = "${_1}は${ore(3)}の得意なスキルの内の一つ${da()}"
                }
                favorite_stat {
                    dialog = "${ore(3)}は${_1}が自慢なの${da()}"
                }
                conversation {
                    dialog = "やあ。特に用はない${ga(3)}、なんだか暇を持てましていたら、${kimi(3)}と話がしたくなって${na(3)}、寄ってみた${nda()}"
                    hold = "あなたと${name(_1)}は愉快に語り合った！"
                }
                drink {
                    dialog ="酒でも飲んで親睦を深めよう${yo(2)}"
                    cheers ="あなたと${name(_1)}は乾杯した！"
                }
            }
            trainer {
                no_more_this_month ="今月はもう訓練は終わり${da()}"
                dialog {
                    member = "${_1}の一員足るもの、ギルドの名に恥じないよう、常に己の技量を磨き続けなければならない${yo()}ギルドの一員である${kimi(3)}には、たったのプラチナ${_2}枚で潜在能力を伸ばす訓練を施してあげる${yo()}"
                    nonmember = "鍛えている${kana(2)}冒険者として生き残るには、日ごろの鍛錬が大切${da(2)}わずかプラチナ${_1}枚で、潜在能力を伸ばす特別な訓練を施してあげる${yo(2)}"
                }

                choices {
                    not_today ="訓練しない"
                    improve = "${_1}を鍛える"
                }
                regret ="後悔する${yo(2)}"
                potential_expands = "${name(_1)}の${_2}の潜在能力が大きく上昇した。"
                after ="うむ、なかなか見所がある${yo()}"
            }
            beggar {
                no_money ="パンを買う金さえない${nda()}恵んで${kure(3)}、おねがい${da(2)}"
                spare = "あなたは${_1}goldを乞食に渡した。"
                after ="${thanks(2)}この恩は一生忘れない${yo()}"
                cheap ="ケチ！"
            }
            punk {
                choices {
                    yes ="いい"
                    no ="だめ"
                    come_on ="うふふ"
                }
                are_you_ready ="フッ。よく逃げ出さずに戻ってきた${na()}準備はいいか。"
                no_turning_back ="いく${yo(2)}"
                hump ="ふん！"
            }
            mysterious_producer {
                want_to_be_star ="スターになりたい${kana(1)}"
                no_turning_back ="よい心がけだ${na(2)}"
            }
            merchant {
                choices {
                    buy ="買いたい"
                    sell ="売りたい"
                    not_now ="今はいい"
                }
                dialog ="今日は${kimi(3)}の幸運な日${da()}普段は一般の客には売らない格安の品を、特別に見せてあげ${ru()}覚えておいて${kure(3)}、今日だけだ${yo()}"
                regret ="後になって後悔しても知らない${yo()}"
            }
        }
    }
}
