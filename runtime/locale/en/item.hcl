locale {
    item {
        chip {
            dryrock = "a dryrock"
            field = "a field"
        }

        desc {
            have_to_identify = "You have to identify the item to gain knowledge."
            no_information = "There is no information about this object."

            it_is_made_of = "It is made of ${_1}."
            speeds_up_ether_disease = "It speeds up the ether disease while equipping."

            weapon {
                it_can_be_wielded = "It can be wielded as a weapon."
                pierce = " Pierce "
                light = "It is a light weapon."
                heavy = "It is a heavy weapon."
            }

            bonus = "It modifies hit bonus by ${_1} and damage bonus by ${_2}."
            dv_pv = "It modifies DV by ${_1} and PV by ${_2}."
            deck = "Collected cards"

            bit {
                acidproof = "It is acidproof."
                fireproof = "It is fireproof."
                precious = "It is precious."
                blessed_by_ehekatl = "It is blessed by Ehekatl."
                stolen = "It is a stolen item."
                alive = "It is alive."
                show_room_only = "It can be only used in a show room."
                handmade = "It is a hand-made item."
                eternal_force = "The enemy dies."
            }

            window {
                title = "Known Information"
                error = "Unknown item definition. If possible, please report which menu the \"Known info\" menu (x key) was opened from (e.g. Drink, Zap, Eat, etc.)."
            }
        }

        armor_class {
            heavy = "(Heavy)"
            medium = "(Medium)"
            light = "(Light)"
        }

        filter_name {
            _60001 = "well"
            _57000 = "food"
            _56000 = "rods"
            _53000 = "scrolls"
            _52000 = "potions"
            _64000 = "junks"
            _77000 = "ores"
            _60000 = "furniture"
            _25000 = "ammos"
            default = "Unknown"
        }

        something_falls_and_disappears = "Something falls to the ground and disappears..."
        something_falls_from_backpack = "Something falls to the ground from your backpack."

        stacked = "${itemname(_1, 1)} has been stacked. (Total:${_2})"

        acid {
            damaged = "${name(_1)}${his_owned(_1)} ${itemname(_2, 0, false)} is damaged by acid."
            immune = "${name(_1)}${his_owned(_1)} ${itemname(_2, 0, false)} is immune to acid."
        }

        item_on_the_ground_get_broiled = "${itemname(_1)} on the ground get${_s(_1)} perfectly broiled."
        someones_item_get_broiled = "${name(_2)}${his_owned(_2)} ${itemname(_1, 0, false)} get${_s(_1)} perfectly broiled."
        fireproof_blanket_protects_item = "${itemname(_1, 1)} protects {name(_2)}{his_owned(_2)} stuff from fire."
        fireproof_blanket_turns_to_dust = "${itemname(_1, 1)} turns to dust."
        item_someone_equips_turns_to_dust = "${itemname(_1, _2)} ${name(_3)} equip${s(_3)} turn${s2(_2)} to dust."
        someones_item_turns_to_dust = "${name(_3)}${his_owned(_3)} ${itemname(_1, _2, false)} turn${s2(_2)} to dust."
        item_on_the_ground_turns_to_dust = "${itemname(_1, _2)} on the ground turn${s2(_2)} to dust."

        coldproof_blanket_protects_item = "${itemname(_1, 1)} protects {name(_2)}{his_owned(_2)} stuff from cold."
        coldproof_blanket_is_broken_to_pieces = "${itemname(_1, 1)} is broken to pieces."
        someones_item_breaks_to_pieces = "${name(_3)}${his_owned(_3)} ${itemname(_1, _2, false)} break${s2(_2)} to pieces."
        item_on_the_ground_breaks_to_pieces = "${itemname(_1, _2)} on the ground break${s2(_2)} to pieces."

        items_are_destroyed = "Too many item data! Some items in this area are destroyed."

        unknown_item = "unknown item (incompatible version)"

        miracle_paren = "<${_1}>"
        godly_paren = "{${_1}}"

        charges = "(Charges: ${_1})"

        approximate_curse_state {
            cursed = "(Scary)"
            doomed = "(Dreadful)"
        }

        gift_rank {
            _0 = "つまらない"
            _1 = "普通の"
            _2 = "ちょっとドキドキする"
            _3 = "高価な"
            _4 = "気絶しそうなほど素晴らしい"
            _5 = "王様が羨むほどの"
        }

        kitty_bank_rank {
            _0 = "5百金貨"
            _1 = "2千金貨"
            _2 = "1万金貨"
            _3 = "5万金貨"
            _4 = "50万金貨"
            _5 = "500万金貨"
            _6 = "1億金貨"
        }

        bait_rank {
            _0 = "ミジンコ"
            _1 = "バッタ"
            _2 = "テントウ"
            _3 = "トンボ"
            _4 = "セミ"
            _5 = "ヘラクレス"
        }

        ancient_book_title {
            _0 = "ヴォイニッチ写本"
            _1 = "ドール賛歌"
            _2 = "ポナペ教教典"
            _3 = "グラーキ黙示録"
            _4 = "グ＝ハーン断章"
            _5 = "断罪の書"
            _6 = "ドジアンの書"
            _7 = "エイボンの書"
            _8 = "大いなる教書"
            _9 = "セラエノ断章"
            _10 = "ネクロノミコン"
            _11 = "ルルイエ異本"
            _12 = "エルトダウン・シャールズ"
            _13 = "金枝篇"
            _14 = "終焉の書"
        }
    }
}
