locale {
    god {
        indifferent = "あなたの信仰は既に限界まで高まっている。"
        enraged = "${_1}は激怒した。" # TODO duplicate?

        switch {
            unbeliever = "あなたは今や無信仰者だ。"
            follower = "あなたは今や${_1}の信者だ！"
        }

        pray {
            do_not_believe = "${you()}は神を信仰していないが、試しに祈ってみた。"
            prompt = "あなたの神に祈りを乞う？"
            you_pray_to = "${_1}に祈った。"
            indifferent = "${_1}はあなたに無関心だ。"

            servant {
                no_more ="神の使徒は2匹までしか仲間にできない。"
                party_is_full ="仲間が一杯で、神からの贈り物を受け取ることができなかった。"
                prompt_decline ="この贈り物を諦める？"

                desc {
                    mani ="このアンドロイドはブーストした時に恐るべき力を発揮するようだ。"
                    lulwy ="この黒天使はブーストした時に恐るべき力を発揮するようだ。"
                    itzpalt ="この追放者は連続魔法を使えるようだ。"
                    ehekatl ="この猫に舐められた武具は、エヘカトルの祝福を授かるようだ。祝福を受けた武具にはエンチャントが一つ付与される。"
                    opatos ="この騎士はある程度重いものをもたせても文句をいわないようだ。"
                    jure ="この防衛者は致死ダメージを受けた仲間をレイハンドで回復できるようだ。レイハンドは眠るたびに再使用可能になる。"
                    kumiromi ="この妖精は食後に種を吐き出すようだ。"
                }
            }
        }

        desc {
            window {
                title = "《 ${_1} 》"

                abandon = "信仰を捨てる"
                convert = "${_1}に改宗する"
                believe = "${_1}を信仰する"
                cancel = "やめる"
            }

            # NOTE: The extra whitespace is significant. These strings should have the same number
            # of characters each.
            offering = "　捧げ物"
            bonus    = "ボーナス"
            ability  = "特殊能力"

            # NOTE: These currently depend on manual line breaking (<br>, <p>) to fit in the
            # decription window. They should be checked manually.

            # Mani
            _1 {
                text ="マニは機械仕掛けの神です。マニを信仰した者は、機械や罠に対する膨大な知識を得、またそれらを効果的に利用する術を知ります。<p><p>"
                offering ="死体 / 銃器 / 機械<p>"
                bonus ="器用 / 感覚 / 銃 / 治癒 / 探知 / 宝石細工 / 鍵開け / 大工<p>"
                ability ="マニの分解術(自動:罠からマテリアルを取り出す)<p>"
            }

            # Lulwy
            _2 {
                text ="ルルウィは風を司る女神です。ルルウィを信仰した者は、風の恩恵を受け素早く動くことが可能になります。<p><p>"
                offering ="死体 / 弓<p>"
                bonus ="感覚 / 速度 / 弓 / クロスボウ / 隠密 / 魔道具<p>"
                ability ="ルルウィの憑依(スキル:瞬間的に高速になる)<p>"
            }

            # Itzpalt
            _3 {
                text ="イツパロトルは元素を司る神です。イツパロトルを信仰した者は、魔力を大気から吸収し、元素に対する保護を受けることができます。<p><p>"
                offering ="死体 / 杖<p>"
                bonus ="魔力 / 瞑想 / 火炎耐性 / 冷気耐性 / 電撃耐性<p>"
                ability ="魔力の吸収(スキル:周囲の空気からマナを吸い出す)<p>"
            }

            # Ehekatl
            _4 {
                text ="エヘカトルは幸運の女神です。エヘカトルを信仰した者は、運を味方につけます。<p><p>"
                offering ="死体 / 魚<p>"
                bonus ="魅力 / 運 / 回避 / 魔力の限界 / 釣り/ 鍵開け<p>"
                ability ="エヘカトル流魔術(自動:マナの消費がランダムになる)<p>"
            }

            # Opatos
            _5 {
                text ="オパートスは大地の神です。オパートスを信仰した者は、高い防御力と破壊力を身につけます。<p><p>"
                offering ="死体 / 鉱石<p>"
                bonus ="筋力 / 耐久 / 盾 / 重量挙げ / 採掘 / 魔道具<p>"
                ability ="オパートスの甲殻(自動:受ける物理ダメージを減らす)<p>"
            }

            # Jure
            _6 {
                text ="ジュアは癒しの女神です。ジュアを信仰した者は、傷ついた身体を癒すことができます。<p><p>"
                offering ="死体 / 鉱石<p>"
                bonus ="意思 / 治癒 / 瞑想 / 解剖学 / 料理 / 魔道具 / 魔力の限界<p>"
                ability ="ジュアの祈り(スキル:失った体力を回復)<p>"
            }

            # Kumiromi
            _7 {
                text ="クミロミは収穫の神です。クミロミを信仰した者は、大地の恵みを収穫し、それを加工する術を知ります。<p><p>"
                offering ="死体 / 野菜<p>"
                bonus ="感覚 / 器用 / 習得 / 栽培 / 錬金術 / 裁縫 / 読書<p>"
                ability ="生命の輪廻(自動：腐った作物から種を取り出す)<p>"
            }
        }
    }
}
