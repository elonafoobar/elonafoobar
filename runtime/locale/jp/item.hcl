locale {
    item {
        chip {
            dryrock = "日干し岩"
            field = "畑"
        }

        desc {
            have_to_identify = "このアイテムに関する知識を得るには、鑑定する必要がある。"
            no_information = "特に情報はない"

            it_is_made_of = "それは${_1}で作られている"
            speeds_up_ether_disease = "それは装備している間、エーテルの病の進行を早める"

            weapon {
                it_can_be_wielded = "それは武器として扱うことができる"
                pierce = " 貫通 "
                light = "それは片手でも扱いやすい"
                heavy = "それは両手持ちに適している"
            }

            bonus = "それは攻撃修正に${_1}を加え、ダメージを${_2}増加させる"
            dv_pv = "それはDVを${_1}上昇させ、PVを${_2}上昇させる"
            deck = "集めたカード"

            bit {
                acidproof = "それは酸では傷つかない"
                fireproof = "それは炎では燃えない"
                precious = "それは貴重な品だ"
                blessed_by_ehekatl = "それはエヘカトルの祝福を受けている"
                stolen = "それは盗品だ"
                alive = "それは生きている"
                show_room_only = "それはショウルームでのみ使用できる。"
                handmade = "それは心温まる手作り品だ"
                eternal_force = "相手は死ぬ"
            }

            window {
                title = "アイテムの知識"
                error = "暫定エラー回避処置です。お手数ですが、どの持ち物メニュー(例えば飲む、振る、食べるなど）から調査(xキー)を押したか報告お願いします。"
            }
        }

        armor_class {
            heavy = "(重装備)"
            medium = "(中装備)"
            light = "(軽装備)"
        }

        filter_name {
            _60001 = "井戸"
            _57000 = "食べ物"
            _56000 = "杖"
            _53000 = "巻物"
            _52000 = "ポーション"
            _64000 = "ジャンク"
            _77000 = "鉱石"
            _60000 = "家具"
            _25000 = "矢弾"
            default = "不明"
        }

        something_falls_and_disappears = "何かが地面に落ちて消えた…"
        something_falls_from_backpack = "何かが地面に落ちた。"

        stacked = "${itemname(_1, 1)}をまとめた(計${_2}個) "

        acid {
            damaged = "${name(_1)}の${itemname(_2)}は酸で傷ついた。"
            immune = "${name(_1)}の${itemname(_2)}は酸では傷つかない。"
        }

        item_on_the_ground_get_broiled = "地面の${itemname(_1)}はこんがりと焼き上がった。"
        someones_item_get_broiled = "${name(_2)}の${itemname(_1)}はこんがりと焼き上がった。"
        fireproof_blanket_protects_item = "${itemname(_1, 1)}が{name(_2)}の持ち物を炎から守った。"
        fireproof_blanket_turns_to_dust = "${itemname(_1, 1)}は灰と化した。"
        item_someone_equips_turns_to_dust = "${name(_3)}の装備している${itemname(_1, _2)}は灰と化した。"
        someones_item_turns_to_dust = "${name(_3)}の${itemname(_1, _2)}は灰と化した。"
        item_on_the_ground_turns_to_dust = "地面の${itemname(_1, _2)}は灰と化した。"

        coldproof_blanket_protects_item = "${itemname(_1, 1)}が{name(_2)}の持ち物を冷気から守った。"
        coldproof_blanket_is_broken_to_pieces = "${itemname(_1, 1)}は粉々に砕けた。"
        someones_item_breaks_to_pieces = "${name(_3)}の${itemname(_1, _2)}は粉々に砕けた。"
        item_on_the_ground_breaks_to_pieces = "地面の${itemname(_1, _2)}は粉々に砕けた。"

        items_are_destroyed = "アイテム情報が多すぎる！幾つかのアイテムは破壊された。"

        unknown_item = "未知のアイテム(バージョン非互換)"

        miracle_paren = "『${_1}』"
        godly_paren = "《${_1}》"

        charges = "(残り${_1}回)"

        approximate_curse_state {
            cursed = "(恐ろしい)"
            doomed = "(禍々しい)"
        }

        gift_rank {
            _0 = "cheap"
            _1 = "so so"
            _2 = "exciting"
            _3 = "expensive"
            _4 = "hot and gorgeous"
            _5 = "crazy epic"
        }

        kitty_bank_rank {
            _0 = "(500 GP)"
            _1 = "(2k GP)"
            _2 = "(10K GP)"
            _3 = "(50K GP)"
            _4 = "(500K GP)"
            _5 = "(5M GP)"
            _6 = "(500M GP)"
        }

        bait_rank {
            _0 = "water flea"
            _1 = "grasshopper"
            _2 = "ladybug"
            _3 = "dragonfly"
            _4 = "locust"
            _5 = "beetle"
        }

        ancient_book_title {
            _0 = "Voynich Manuscript"
            _1 = "Dhol Chants"
            _2 = "Ponape Scripture"
            _3 = "Revelations of Glaaki"
            _4 = "G'harne Fragments"
            _5 = "Liber Damnatus"
            _6 = "Book of Dzyan"
            _7 = "Book of Eibon"
            _8 = "Grand Grimoire"
            _9 = "Celaeno Fragments"
            _10 = "Necronomicon"
            _11 = "The R'lyeh Text"
            _12 = "Eltdown Shards"
            _13 = "The Golden Bough"
            _14 = "Apocalypse"
        }
    }
}
