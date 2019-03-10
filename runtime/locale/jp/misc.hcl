# TODO
# These text are unclassed. They should be moved to appropriate files.

locale {
    misc {
        ranking {
            changed = "ランク変動(${_1} ${_2}位 → ${_3}位) 《${_4}》"
            closer_to_next_rank = "着実に次のランクに近づいている。"
        }

        sound {
            waken = "${name(_1)}は物音に気付き目を覚ました。"
            get_anger = "${name(_1)}はキレた。"
            can_no_longer_stand = "「もう我慢できない」"
        }

        hostile_action {
            glares_at_you = "${name(_1)}は嫌な顔をした。"
            gets_furious = "${name(_1)}は激怒した。"
            get_excited = "家畜は興奮した！"
        }

        wet {
            gets_wet = "${name(_1)}は濡れた。"
            is_revealed = "${name(_1)}の姿があらわになった。"
        }

        fail_to_cast {
            mana_is_absorbed =  "${name(_1)}はマナを吸い取られた！"
            is_confused_more = "${name(_1)}は余計に混乱した。"
            too_difficult = "難解だ！"
            dimension_door_opens = "${name(_1)}は奇妙な力に捻じ曲げられた！"
            creatures_are_summoned = "魔力の渦が何かを召喚した！"
        }

        status_ailment {
            choked = "「うぐぐ…！」"
            breaks_away_from_gravity = "${name(_1)}は重力から抜け出した。"
            calms_down = "${name(_1)}はやや落ち着いた。"
            sleepy = "あなたは眠りを必要としている。"
            insane = [
                "${name(_1)}「キョキョキョ」",
                "${name(_1)}「クワッ」",
                "${name(_1)}「シャアァァ」",
                "${name(_1)}「ばぶっふ！」",
                "${name(_1)}「煮殺せ！」",
                "${name(_1)}「許しなさい許しなさい！！」",
                "${name(_1)}「フゥハハハー！」",
                "${name(_1)}「あ、あ、あ、あ」",
                "${name(_1)}「ぴ…ぴ…ぴか…」",
                "${name(_1)}「お兄ちゃん！」",
                "${name(_1)}「うみみやぁ」",
                "${name(_1)}は突然踊りだした。",
                "${name(_1)}は着ていたものを脱ぎだした。",
                "${name(_1)}はぐるぐる回りだした。",
                "${name(_1)}は奇声を発した。",
                "${name(_1)}「ねうねう♪ねうねう♪」",
                "${name(_1)}「ウージッムシ♪ウージッムシ♪」",
                "${name(_1)}「じゃあ殺さなきゃ。うん♪」",
                "${name(_1)}「このナメクジがっ」",
                "${name(_1)}「おすわり！」",
                "${name(_1)}「フーーーーン フーーーーン･･･ フーーーンフ」",
                "${name(_1)}「このかたつむり野郎がっ」",
                "${name(_1)}「うにゅみゅあ！」",
                "${name(_1)}「ごめんなさいごめんなさい！」",
                "${name(_1)}「もうすぐ生まれるよ♪」",
                "${name(_1)}「フーーーーン フー…クワッ！」",
            ]
        }

        death {
            good_bye = "さようなら… "
            you_leave_dying_message = "遺言は？"
            dying_message = "「${_1}」"
            date = "${_1}年${_2}月${_3}日"
            you_died = "${_2}で${_1}"
            rank = "{_1}位"
            you_are_about_to_be_buried = "あともう少しで埋葬される…"
            crawl_up = "這い上がる"
            lie_on_your_back = "埋まる"
            you_have_been_buried = "あなたは埋められた。さようなら…（キーを押すと終了します）"
            sent_message = "${_1}${_2}は${_4}で${_3}${_5}"
        }

        score {
            rank = "${_1}位"
            score = "${_1}点"
        }

        resurrect = "${_1}は復活した！"
        artifact_regeneration = "${_1}は${itemname(_2)}に形を変えた。"
        black_cat_licks = "${name(_1)}は${itemname(_2)}をぺろぺろと舐めた。"
        corpse_is_dried_up = "${itemname(_1)}は上手い具合に干された。"
        get_rotten = "${itemname(_1)}は腐った。"
        extract_seed = "あなたは${itemname(_1)}から種を取り出した。"

        curse {
            gold_stolen = "悪意のある手が${name(_1)}の財布から金貨を抜き去った。"
            blood_sucked = "何かが${name(_1)}の血を吸った。"
            experience_reduced = "${name(_1)}は未熟になった。"
            creature_summoned = "魔力の渦が何かを召喚した！"
        }

        identify {
            fully_identified = "バックパックの中の${_1}は${itemname(_2)}だと判明した。"
            almost_identified = "バックパックの中の${itemname(_1)}は${_2}だという感じがする。"
        }

        love_miracle {
            uh = "「あ…！」"
        }

        pregnant {
            pukes_out = "しかしすぐに吐き出した。"
            gets_pregnant = "${name(_1)}は寄生された。"

            pats_stomach = "${name(_1)}は不安げに腹を押さえた。"
            something_is_wrong = [
                "「なにかが産まれそうだよ！」",
                "「腹になにかが…」",
            ]
            something_breaks_out = "何かが${name(_1)}の腹を破り飛び出した！"
        }

        walk_down_stairs = "階段を降りた。"
        walk_up_stairs = "階段を昇った。"

        quest {
            kamikaze_attack {
                message = "伝令「パルミア軍の撤退が完了しました！これ以上ここに留まる必要はありません。機を見て地下から退却してください！」"
                stairs_appear = "階段が現れた。"
            }
        }

        map {
            jail {
                repent_of_sin = "あなたは罪を悔いた。"
                guard_approaches = "あなたはガードの足音が近づいてくるのに気付いた。"
                leave_here = "「そこのお前、もう反省したころだろう。出てもいいぞ」"
                unlocks_your_cell = "ガードは面倒くさそうにあなたの牢の扉を開けた。"
            }

            shelter {
                eat_stored_food = "シェルターの貯蔵食品を食べた。"
                no_longer_need_to_stay = "もうシェルターの中にいる必要は無い。"
            }

            museum {
                chats = [
                    " *ざわざわ* ",
                    "「ふむ…悪くないな」",
                    "「何だろう、これは」",
                    "「ほほう…」",
                    "「私も死んだらはく製に…」",
                    "「ここが噂の…」",
                ]
                chats2 = [
                    " *がやがや* ",
                    "「やだっ気持ち悪い」",
                    "「ねーねーこれ死んでるんでしょ？」",
                    "「かわ、いー♪」",
                    "「今日はとことん見るぜ」",
                    "「触ってもいいの？」",
                ]
            }

            shop {
                chats = [
                    " *ざわざわ* ",
                    "「これ欲しい〜」",
                    "「何だろう、これは」",
                    "「お買い物♪」",
                    "「金が足りん…」",
                    "「ここが噂の…」",
                ]
            }
        }

        custom {
            key_hint = "BackSpace [削除]  "
            show_room {
                which_show_room = "どのルームを訪問する？ "
                list = "ルーム一覧"
                name = "ルームの名称"
            }
            pet_team {
                which_team = "どのチームと対戦する？"
                list = "ペットチーム一覧"
                name = "チームの名称"
            }

            incompatible = "互換性のないバージョンのファイルです。"
            fail_to_retrieve_file = "ファイルの取得に失敗した。"
            do_you_want_to_delete = "本当に${_1}を削除する？ "
        }

        no_target_around = "視界内にターゲットは存在しない。"

        return {
            forbidden = "依頼請負中の帰還は法律で禁止されている。それでも帰還する？"
            no_location = "この大陸には帰還できる場所が無い。"
            where_do_you_want_to_go = "どの場所に帰還する？"
            air_becomes_charged = "周囲の大気がざわめきだした。"
            lord_of_dungeon_might_disappear = "このままダンジョンを出ると、この階のクエストは達成できない…"
        }

        dungeon_level = "階"

        save {
            update = "Ver.${_1}のセーブデータをアップデートします。"
            need_to_save_in_town = "アップデートを行うには、街中でセーブしたセーブデータが必要です。"
            take_a_while = "次のプロセスの完了までには、しばらく時間がかかることがあります。"
            cannot_save_in_user_map = "ユーザーマップの中ではセーブできない。"
        }

        living_weapon_taste_blood = "${itemname(_1)}は十分に血を味わった！"
        caught_by_assassins = "暗殺者につかまった。あなたはクライアントを守らなければならない。"
        finished_eating = "${kare_wa(_1)}${itemname(_2, 1)}を食べ終えた。"
        spell_passes_through = "${name(_1)}は巻き込みを免れた。"
        shakes_head = "${name(_1)}は頭を振った。"

        wields_proudly {
            the = ""
        }

        and = "と"

        income {
            sent_to_your_house = "${_1}goldが給料として振り込まれた。"
            sent_to_your_house2 = "${_1}goldと${_2}個のアイテムが給料として振り込まれた。"
        }

        tax {
            bill = "請求書が送られてきた。"
            no_duty = "レベルが6に達していないので納税の義務はない。"
            caution = "注意！"
            warning = "警告！！"
            have_to_go_embassy = "早急にパルミア大使館まで行き、税金を納めなければならない。"
            left_bills = "税金を${_1}ヶ月分滞納している。"
            accused = "あなたは税金を${_1}ヶ月滞納した罪で訴えられた。"
            lose_fame = "名声値を${_1}失った。"
        }
    }
}
