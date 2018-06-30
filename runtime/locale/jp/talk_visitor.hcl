locale {
    talk {
        visitor {
            wanted_to_say_hi = "まあ、とくに用もないんだけど${na(_1)}"
            receive = "${name(_2)}に${itemname(_1, 1)}をもらった！"

            choices {
                yes ="いい"
                no ="だめ"
            }

            adventurer {
                new_year {
                    happy_new_year = "明けましておめでとう${da(_1, 2)}"
                    gift = "日ごろの感謝の意をこめてこれをあげる${yo(_1)}"
                    throws = "${name(_1)}は${itemname(_2, 1)}を置いていった。"
                }

                hate {
                    dialog ="貴様！見つけた${yo(_1, 2)}"
                    text ="「これでも食らうがいい${yo(_1, 2)}」"
                    throws = "${name(_1)}は火炎瓶を投げた。"
                }

                like {
                    dialog ="これ、あげ${ru(_1, 2)}"
                    wonder_if ="友達100人できるかな♪"
                }

                train {
                    choices {
                        learn ="習得する"
                        train ="訓練する"
                        pass = "遠慮しとく"
                    }

                    learn {
                        dialog = "${_1}のスキルを、友達価格の${_2}で教えてあげてもいい${ga(_3, 3)}どう${kana(_3, 1)}"
                        after ="新しい技術をどうやら習得できたようだ${na(_1)}"
                    }

                    train {
                        dialog = "${_1}のスキルを、友達価格の${_2}で訓練してもいい${ga(_3, 3)}どう${kana(_3, 1)}"
                        after ="よし、これで訓練は終わり${da(_1)}かなり潜在能力が伸びた${yo(_1, 2)}"
                    }

                    pass = "わかった${yo(_1)}またしばらくしてから尋ねてみ${ru(_1)}"
                }

                friendship {
                    dialog ="友達の証としてこれをあげ${ru(_1, 2)}大事に使って${yo(_1)}"
                    no_empty_spot ="部屋が一杯で置けなかった…"
                }

                souvenir {
                    dialog = "近くまで来たので寄ってみた${nda(_1)}ついでだから、土産にこれをあげ${ru(_1)}"
                    inventory_is_full ="所持品が一杯で受け取れなかった…"
                    receive = "${itemname(_1, 1)}を受け取った。"
                }

                materials {
                    dialog ="旅の途中にこんなものを拾った${nda(_1)}${kimi(_1, 3)}の役に立つと思って持ってきた${yo(_1)}"
                    receive = "${name(_1)}は色々なものが詰まった袋を、あなたに手渡した。"
                }

                favorite_skill {
                    dialog = "${_1}は${ore(_2, 3)}の得意なスキルの内の一つ${da(_2)}"
                }

                favorite_stat {
                    dialog = "${ore(_2, 3)}は${_1}が自慢なの${da(_2)}"
                }

                conversation {
                    dialog = "やあ。特に用はない${ga(_2, 3)}、なんだか暇を持てましていたら、${kimi(_2, 3)}と話がしたくなって${na(_2, 3)}、寄ってみた${nda(_2)}"
                    hold = "あなたと${name(_1)}は愉快に語り合った！"
                }

                drink {
                    dialog ="酒でも飲んで親睦を深めよう${yo(_1, 2)}"
                    cheers ="あなたと${name(_1)}は乾杯した！"
                }
            }

            trainer {
                no_more_this_month ="今月はもう訓練は終わり${da(_1)}"

                dialog {
                    member = "${_1}の一員足るもの、ギルドの名に恥じないよう、常に己の技量を磨き続けなければならない${yo(_3)}ギルドの一員である${kimi(_3, 3)}には、たったのプラチナ${_2}枚で潜在能力を伸ばす訓練を施してあげる${yo(_3)}"
                    nonmember = "鍛えている${kana(_1, 2)}冒険者として生き残るには、日ごろの鍛錬が大切${da(_1, 2)}わずかプラチナ${_1}枚で、潜在能力を伸ばす特別な訓練を施してあげる${yo(_1, 2)}"
                }

                choices {
                    not_today ="訓練しない"
                    improve = "${_1}を鍛える"
                }

                regret ="後悔する${yo(_1, 2)}"
                potential_expands = "${name(_1)}の${_2}の潜在能力が大きく上昇した。"
                after ="うむ、なかなか見所がある${yo(_1)}"
            }

            beggar {
                dialog ="パンを買う金さえない${nda(_1)}恵んで${kure(_1, 3)}、おねがい${da(_1, 2)}"
                spare = "あなたは${_1}goldを乞食に渡した。"
                after ="${thanks(_1, 2)}この恩は一生忘れない${yo(_1)}"
                cheap ="ケチ！"
            }

            punk {
                dialog ="フッ。よく逃げ出さずに戻ってきた${na(_1)}準備はいいか。"
                hump ="ふん！"
            }

            mysterious_producer {
                want_to_be_star ="スターになりたい${kana(_1, 1)}"
                no_turning_back ="よい心がけだ${na(_1, 2)}"
            }

            merchant {
                choices {
                    buy ="買いたい"
                    sell ="売りたい"
                    not_now ="今はいい"
                }

                dialog ="今日は${kimi(_1, 3)}の幸運な日${da(_1)}普段は一般の客には売らない格安の品を、特別に見せてあげ${ru(_1)}覚えておいて${kure(_1, 3)}、今日だけだ${yo(_1)}"
                regret ="後になって後悔しても知らない${yo(_1)}"
            }
        }
    }
}
