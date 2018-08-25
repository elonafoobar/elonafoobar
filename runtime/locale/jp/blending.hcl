locale {
    blending {
        rate_panel {
            success_rate = "成功率: ${_1}"
            turns = "${_1}ターン"
            and_hours = "と${_1}時間"
            required_time = "必要時間: ${_1}"
        }

        window {
            procedure = "調合の手順"
            choose_a_recipe = "レシピを選ぶ"
            chose_the_recipe_of = "${_1}のレシピを選んだ"
            add = "${_1}を加える(所持:${_2})"
            selected = "${itemname(_1)}を選んだ"
            start = "調合を始める！"
            the_recipe_of = "${_1}のレシピ"
            required_skills = "必要なスキル:"
            required_equipment = "必要な機材:"
            havent_identified = "このアイテムは鑑定されていない。"
            no_inherited_effects = "継承効果なし"
        }

        prompt {
            how_many = "幾つ作る？"
            start = "調合を始める"
            go_back = "前に戻る"
            from_the_start = "最初から"
        }

        recipe {
            title = "レシピの選択"
            name = "レシピの名称"
            hint = "[ページ切替]  "

            warning = "(製作中)だめまだ"
            which = "どのレシピを使う？"
            counter = "${_1} recipes"
            of = "${_1}のレシピ"
        }

        steps {
            add_ingredient = "${_1}を追加しよう。"
            add_ingredient_prompt = "${_1}を追加"
            item_name = "アイテムの名称"
            item_counter = "${_1} items"
            ground = "(地面)"
            you_add = "${itemname(_1)}を選んだ。"
        }

        you_lose = "${itemname(_1, 1)}を失った。"

        started = "${name(_1)}は${_2}の調合をはじめた。"
        succeeded = "${itemname(_1, 1)}の作成に成功した！"
        failed = "調合失敗！"

        required_material_not_found = "調合に必要な材料が見つからない。"

        sounds = [
            " *こねこね* ",
            " *トントン* "
        ]

        success_rate {
            perfect = "もう完璧！"
            piece_of_cake = "朝飯前！"
            very_likely = "かんたんね"
            no_problem = "まず大丈夫"
            probably_ok = "たぶんいける"
            maybe = "ちょっと不安"
            bad = "だめかも"
            very_bad = "やばい"
            almost_impossible = "まず無理"
            impossible = "絶対ムリ！"

            goes_up = "調合の成功率が上がった。"
            goes_down = "調合の成功率が下がった。"
        }

        recipe {
            _200 = "媚薬混入食品"
            _201 = "染色"
            _202 = "特製毒入り食品"
            _203 = "耐火コーティング"
            _204 = "耐酸コーティング"
            _205 = "釣り餌の装着"
            _206 = "アイテムの祝福"
            _207 = "井戸水の回復"
            _208 = "天然ポーション"
            _209 = "2種アーティファクト合成"
            _210 = "3種アーティファクト合成"
        }

        ingredient {
            _1 = "適当な調味料"
            _2 = "適当な鉱石"
            _3 = "木材を含む何か"
            _4 = "魚介類"
            _5 = "何か物体"
            corpse = "${_1}の死体"
        }
    }
}
