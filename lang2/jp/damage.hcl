locale {
    damage {
        is_healed = "${name(_1)}は回復した。"
        lay_hand = "${name(_1)}は叫んだ。「この者にジュアの加護を。レイハンド！」"

        runs_away_in_terror = "${name(_1)}は恐怖して逃げ出した。"
        sleep_is_disturbed = "${name(_1)}は眠りを妨げられた。"

        explode_click = " *カチッ* "
        splits = "${name(_1)}は分裂した！"
        is_engulfed_in_fury = "${name(_1)}は怒りに体を奮わせた！"

        you_feel_sad = "あなたは悲しくなった。"
        get_off_corpse = "${you()}は${name(_1)}の死体から降りた。"
        death_word_breaks = "死の宣告は無効になった。"

        magic_reaction_hurts = "マナの反動が${name(_1)}の精神を蝕んだ！"

        levels {
            scratch = "かすり傷をつけた。"
            slightly = "軽い傷を負わせた。"
            moderately = "傷つけた。"
            severely = "深い傷を負わせた。"
            critically = "致命傷を与えた。"
        }

        reactions {
            screams = "${name(_1)}は痛手を負った。"
            writhes_in_pain = "${name(_1)}は苦痛にもだえた。"
            is_severely_hurt = "${name(_1)}は悲痛な叫び声をあげた。"
        }

        element {
            default = "は傷ついた。"
            _50 = "${name(_1)}は燃え上がった。"
            _51 = "${name(_1)}は凍えた。"
            _52 = "${name(_1)}に電流が走った。"
            _53 = "${name(_1)}は闇の力で傷ついた。"
            _54 = "${name(_1)}は狂気に襲われた。"
            _55 = "${name(_1)}は吐き気を催した。"
            _56 = "${name(_1)}は冥界の冷気で傷ついた。"
            _57 = "${name(_1)}は轟音の衝撃を受けた。"
            _58 = "${name(_1)}の神経は傷ついた。"
            _59 = "${name(_1)}は混沌の渦で傷ついた。"
            # _60
            _61 = "${name(_1)}は切り傷を負った。"
            # _62
            _63 = "${name(_1)}は酸に焼かれた。"
        }

        death_by {
            chara {
                transformed_into_meat {
                    active = "粉々の肉片に変えた。"
                    passive = "${name(_1)}は粉々の肉片に変えられた。"
                }
                destroyed {
                    active = "破壊した。"
                    passive = "${name(_1)}は破壊された。"
                }
                minced {
                    active = "ミンチにした。"
                    passive = "${name(_1)}はミンチにされた。"
                }
                killed {
                    active = "殺した。"
                    passive = "${name(_1)}は殺された。"
                }
                death_cause = "${basename(_1)}に殺された。"
            }
            element {
                default {
                    active = "殺した。"
                    passive = "${name(_1)}は死んだ。"
                }
                _50 {
                    active = "燃やし尽くした。"
                    passive = "${name(_1)}は燃え尽きて灰になった。"
                }
                _51 {
                    active = "氷の塊に変えた。"
                    passive = "${name(_1)}は氷の彫像になった。"
                }
                _52 {
                    active = "焦げカスにした。"
                    passive = "${name(_1)}は雷に打たれ死んだ。"
                }
                _53 {
                    active = "闇に飲み込んだ。"
                    passive = "${name(_1)}は闇に蝕まれて死んだ。"
                }
                _54 {
                    active = "再起不能にした。"
                    passive = "${name(_1)}は発狂して死んだ。"
                }
                _55 {
                    active = "毒殺した。"
                    passive = "${name(_1)}は毒に蝕まれて死んだ。"
                }
                _56 {
                    active = "冥界に墜とした。"
                    passive = "${name(_1)}は冥界に墜ちた。"
                }
                _57 {
                    active = "聴覚を破壊し殺した。"
                    passive = "${name(_1)}は朦朧となって死んだ。"
                }
                _58 {
                    active = "神経を破壊した。"
                    passive = "${name(_1)}は神経を蝕まれて死んだ。"
                }
                _59 {
                    active = "混沌の渦に吸い込んだ。"
                    passive = "${name(_1)}は混沌の渦に吸収された。"
                }
                # _60
                _61 {
                    active = "千切りにした。"
                    passive = "${name(_1)}は千切りになった。"
                }
                # _62
                _63 {
                    active = "ドロドロに溶かした。"
                    passive = "${name(_1)}は酸に焼かれ溶けた。"
                }
            }
            other {
                _1 {
                    text = "${name(_1)}は罠にかかって死んだ。"
                    death_cause = "罠にかかって死んだ。"
                }
                _2 {
                    text = "${name(_1)}はマナの反動で死んだ。"
                    death_cause = "マナの反動で消滅した。"
                }
                _3 {
                    text = "${name(_1)}は餓死した。"
                    death_cause = "飢え死にした。"
                }
                _4 {
                    text = "${name(_1)}は毒に蝕まれ死んだ。"
                    death_cause = "毒にもがき苦しみながら死んだ。"
                }
                _5 {
                    text = "${name(_1)}は呪いの力で死んだ。"
                    death_cause = "呪い殺された。"
                }
                _6 {
                    text = "${name(_1)}は${_2}の重さに耐え切れず死んだ。"
                    death_cause = "${_1}の重さに耐え切れず潰れた。"
                    backpack = "荷物"
                }
                _7 {
                    text = "${name(_1)}は階段から転げ落ちて死んだ。"
                    death_cause = "階段から転げ落ちて亡くなった。"
                }
                _8 {
                    text = "${name(_1)}は聴衆に殺された。"
                    death_cause = "演奏中に激怒した聴衆に殺された。"
                }
                _9 {
                    text = "${name(_1)}は焼け死んだ。"
                    death_cause = "焼けて消滅した。"
                }
                # _10
                _11 {
                    text = "${name(_1)}は見えざる手に葬られた。"
                    death_cause = "見えざる手に葬られた。"
                }
                _12 {
                    text = "${name(_1)}は食中毒で死んだ。"
                    death_cause = "食中毒で倒れた。"
                }
                _13 {
                    text = "${name(_1)}は出血多量で死んだ。"
                    death_cause = "血を流しすぎて死んだ。"
                }
                _14 {
                    text = "${name(_1)}はエーテルに侵食され死んだ。"
                    death_cause = "エーテルの病に倒れた。"
                }
                _15 {
                    text = "${name(_1)}は溶けて液体になった。"
                    death_cause = "溶けて液体になった。"
                }
                _16 {
                    text = "${name(_1)}はバラバラになった。"
                    death_cause = "自殺した。"
                }
                _17 {
                    text = "${name(_1)}は核爆発に巻き込まれて塵となった。"
                    death_cause = "核爆発に巻き込まれて死んだ。"
                }
                _18 {
                    text = "${name(_1)}はアイアンメイデンの中で串刺しになって果てた。"
                    death_cause = "アイアンメイデンにはさまれて死んだ。"
                }
                _19 {
                    text = "${name(_1)}はギロチンで首をちょんぎられて死んだ。"
                    death_cause = "ギロチンで首を落とされて死んだ。"
                }
                _20 {
                    text = "${name(_1)}は首を吊った。"
                    death_cause = "首を吊った。"
                }
                _21 {
                    text = "${name(_1)}はもちを喉に詰まらせて死んだ。"
                    death_cause = "もちを喉に詰まらせて死んだ。"
                }
            }
        }

        sand_bag {
            _0 = "「くっ！」"
            _1 = "「まだまだ！」"
            _2 = "「もう限界…」"
            _3 = "「うぐぐ」"
            _4 = "「あう」"
            _5 = "「ああんっ」"
        }
    }
}
