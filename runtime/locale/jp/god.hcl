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
            }
        }

        window {
            title = "《 ${_1} 》"

            abandon = "信仰を捨てる"
            convert = "${_1}に改宗する"
            believe = "${_1}を信仰する"
            cancel = "やめる"

            # NOTE: The extra whitespace is significant. These strings should have the same number
            # of characters each.
            offering = "　捧げ物"
            bonus    = "ボーナス"
            ability  = "特殊能力"
        }
    }
}
