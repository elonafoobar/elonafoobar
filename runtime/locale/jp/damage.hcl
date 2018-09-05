locale {
    damage {
        miss {
            ally = "${kare_wa(_2)}${name(_1)}の攻撃を避けた。"
            other = "${kare_wa(_1)}攻撃をかわされた。"
        }
        evade {
            ally = "${kare_wa(_2)}${name(_1)}の攻撃を華麗に避けた。"
            other = "${kare_wa(_1)}攻撃を華麗にかわされた。"
        }
        furthermore = "さらに"

        is_frightened = "${name(_1)}は怖気づいた。"
        critical_hit = "会心の一撃！ "

        wields_proudly = "${name(_1)}は${_2}を誇らしげに構えた。"

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

        weapon {
            attacks_with = "${kare_wa(_3)}${name(_1)}に${_4}で${_2}。"
            attacks_and = "${kare_wa(_1)}${name(_3)}を${_2}"

            attacks_throwing = "${kare_wa(_1)}${name(_3)}に${_4}を${_2}"

            attacks_unarmed = "${kare_wa(_3)}${name(_1)}に${_2}"
            attacks_unarmed_and = "${kare_wa(_1)}${name(_3)}を${_2}"

            _108 {
                name = "弓"
                verb_and = "射撃し"
                verb = "撃たれた"
            }
            _109 {
                name = "クロスボウ"
                verb_and = "射撃し"
                verb = "撃たれた"
            }
            _110 {
                name = "銃"
                verb_and = "射撃し"
                verb = "撃たれた"
            }
            _100 {
                name = "長剣"
                verb_and = "切り払い"
                verb = "切られた"
            }
            _104 {
                name = "槍"
                verb_and = "突き刺して"
                verb = "刺された"
            }
            _101 {
                name = "短剣"
                verb_and = "突き刺して"
                verb = "刺された"
            }
            _105 {
                name = "杖"
                verb_and = "打って"
                verb = "打たれた"
            }
            _103 {
                name = "鈍器"
                verb_and = "打って"
                verb = "打たれた"
            }
            _102 {
                name = "斧"
                verb_and = "切り払い"
                verb = "切られた"
            }
            _107 {
                name = "鎌"
                verb_and = "切り払い"
                verb = "切られた"
            }
            _111 {
                verb_and = "投げ"
                verb = "攻撃された"
            }
        }

        reactive_attack {
            thorns = "棘が${name(_1)}に刺さった。"
            ether_thorns = "エーテルの棘が${name(_1)}に刺さった。"
            acids = "酸が飛び散った。"
        }

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

        vorpal {
            melee = " *シャキーン* "
            ranged = " *ズバシュッ* "
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
