locale {
    config {
        common {
            menu = "項目"
            require_restart = "* 印のついた項目は、ゲームの再起動後に適用されます"
            assign_button = "ボタンを割り当てたい項目にカーソルをあわせて\nゲームパッドのボタンを押してください。(L),(R)の付いている\n項目は、メニュー画面でタブの移動に使われます。"
            no_desc = "(説明はありません)"

            yes_no {
                # NOTE: This text is implicitly chosen for boolean values without an explicit
                # "yes_no" option.
                default {
                    yes = "する"
                    no = "しない"
                }

                ari_nashi {
                    yes = "あり"
                    no = "なし"
                }

                shiyou_suru_shinai {
                    yes = "使用する"
                    no = "使用しない"
                }

                kougashitsu_teigashitsu {
                    yes = "高画質"
                    no = "低画質"
                }

                saisei_suru_shinai {
                    yes = "再生する"
                    no = "再生しない"
                }

                anime_ari_nashi {
                    yes = "アニメあり"
                    no = "アニメなし"
                }

                ari_nashi_slow_fast {
                    yes = "あり（低速）"
                    no = "なし（高速）"
                }

                tsukau_tsukawanai {
                    yes = "使う"
                    no = "使わない"
                }

                yuukou_mukou {
                    yes = "有効"
                    no = "無効"
                }

                unsupported {
                    yes = "オフ(未実装)"
                    no = "オフ(未実装)"
                }
            }

            formatter {
                wait = "${_1} wait"
            }
        }

        menu {
            name = "オプション"

            game {
                name = "ゲーム設定"
                extra_help {
                    name = "ノルンの冒険ガイド"
                    doc = "Elonaに不慣れな冒険者に向けて妖精ノルンによる案内が表示されます。"
                }
                attack_neutral_npcs {
                    name = "非好戦的NPCを攻撃"
                    doc = "中立NPCに向かって歩いたとき、そのNPCに対して攻撃します。"
                }
                default_save {
                    name = "デフォルトセーブ"
                    variants {
                        "" = "使用しない"
                    }
                    doc = "Elonaを起動した際にデフォルトで読み込まれるセーブデータです。\nこれを設定するとタイトル画面を飛ばしてすぐにゲームを始めることができます。"
                }
                story {
                    name = "シーンの再生"
                    yes_no = core.locale.config.common.yes_no.saisei_suru_shinai
                    doc = "Elonaのメインストーリーを再生します。"
                }
                hide_autoidentify {
                    name = "自然鑑定ﾒｯｾｰｼﾞの非表示"
                    doc = "自然鑑定が行われた際のメッセージを非表示にします。"
                }
                hide_shop_updates {
                    name = "店ﾒｯｾｰｼﾞの非表示"
                    doc = "店の販売ログを非表示にします。"
                }
            }

            screen {
                name = "画面と音の設定"
                sound {
                    name = "サウンドの再生*"
                    yes_no = core.locale.config.common.yes_no.ari_nashi
                    doc = "SEを再生します。"
                }
                music {
                    name = "midiの再生*"
                    variants {
                        none = "なし"
                        direct_music = "direct music"
                        mci = "MCI"
                    }
                    doc = "BGMを再生します。"
                }
                stereo_sound {
                    name = "ステレオサウンド"
                    doc = "音が鳴った場所に応じてSEを再生します。\n例えば、画面左で鳴ったSEが左から聞こえるようになります。"
                }
                fullscreen {
                    name = "画面モード*"
                    variants {
                        windowed = "ウィンドウ"
                        fullscreen = "フルスクリーン"
                        desktop_fullscreen = "フルスクリーン2"
                    }
                }
                display_mode {
                    name = "画面の大きさ*"
                    # Variants are injected at runtime.
                }
                orientation {
                    name = "画面の向き"
                    variants {
                        sensor_landscape = "横向き (自動)"
                        sensor_portrait = "縦向き (自動)"
                        sensor = "自動回転"
                        landscape = "横向き"
                        portrait = "縦向き"
                        reverse_landscape = "横向き (反転)"
                        reverse_portrait = "縦向き (反転)"
                    }
                }
                window_mode {
                    name = "ウィンドウの大きさ*"
                }
                high_quality_shadows {
                    name = "光源の描写"
                    doc = "Render shadows at higher quality."
                    yes_no = core.locale.config.common.yes_no.kougashitsu_teigashitsu
                }
                object_shadows {
                    name = "アイテムの影描写"
                    doc = "Display shadows under items on the ground."
                    yes_no = core.locale.config.common.yes_no.ari_nashi_slow_fast
                }
                heartbeat {
                    name = "心臓の音"
                    yes_no = core.locale.config.common.yes_no.saisei_suru_shinai
                    doc = "HPが残り少ないとき、心拍音を再生します。"
                }
                heartbeat_threshold {
                    name = "心音再生の閾値"
                    doc = "HPがこのパーセンテージを下回っているとき心拍音が再生されます。"
                }
                skip_random_event_popups {
                    name = "イベントの短縮"
                    doc = "ランダムイベントのポップアップウィンドウをスキップします。\nスキップされた場合デフォルトの選択肢が選ばれます。"
                }
            }

            net {
                name = "ネット機能の設定"
                enabled {
                    name = "ネットの使用"
                    doc = "現在実装されていません。"
                }
                wish {
                    name = "定期的に接続"
                }
                chat {
                    name = "チャットをフィルタ"
                }
                server_list {
                    name = "カスタムサーバー"
                    yes_no = core.locale.config.common.yes_no.shiyou_suru_shinai
                }
            }

            anime {
                name = "アニメ設定"
                scroll {
                    name = "スクロール"
                    doc = "PCが動くときスクロールアニメーションを表示します。"
                }
                always_center {
                    name = "主人公中心に描写"
                    doc = "常にPCを中心として描写を行います。"
                }
                scroll_when_run {
                    name = "走り時スクロール"
                    doc = "走っているときもスクロールアニメーションを表示します。\nこれを切ることで若干の高速化が望めます。"
                }
                general_wait {
                    name = "キーウェイト"
                    formatter = core.locale.config.common.formatter.wait
                }
                anime_wait {
                    name = "アニメウェイト"
                    formatter = core.locale.config.common.formatter.wait
                    doc = "アニメーションの長さです。"
                }
                alert_wait {
                    name = "アラートウェイト"
                    doc = "重要なメッセージが表示された際のウェイトの長さです。"
                }
                auto_turn_speed {
                    name = "オートターンの挙動"
                    variants {
                        normal = "普通"
                        high = "速め"
                        highest = "省略"
                    }
                }
                attack_anime {
                    name = "攻撃時アニメ"
                    doc = "物理攻撃した際にアニメーションを表示します。"
                }
                weather_effect {
                    name = "天候エフェクト"
                    doc = "天候に関わるアニメーションを表示します。"
                }
                title_effect {
                    name = "タイトルの水の波紋"
                    yes_no = core.locale.config.common.yes_no.unsupported
                    doc = "現在実装されていません。"
                }
                window_anime {
                    name = "ウィンドウアニメ"
                    doc = "ゲーム内でウィンドウが表示される際アニメーションが表示されます。"
                }
                screen_refresh {
                    name = "画面の更新頻度"
                    formatter = core.locale.config.common.formatter.wait
                }
            }

            input {
                name = "入力設定"
                autodisable_numlock {
                    name = "numlockを自動制御"
                }
                walk_wait {
                    name = "歩きの速さ"
                    formatter = core.locale.config.common.formatter.wait
                }
                run_wait {
                    name = "走りの速さ"
                    formatter = core.locale.config.common.formatter.wait
                }
                start_run_wait {
                    name = "走り開始の速さ"
                    formatter = "${After } ${_1}+1 steps" # TODO
                }
                attack_wait {
                    name = "攻撃の間隔"
                    formatter = core.locale.config.common.formatter.wait
                }
                key_wait {
                    name = "キーウェイト"
                    formatter = core.locale.config.common.formatter.wait
                }
                select_wait {
                    name = "選択ウェイト"
                    formatter = core.locale.config.common.formatter.wait
                }
                select_fast_start_wait {
                    name = "選択ウェイト(早い,開始)"
                    formatter = core.locale.config.common.formatter.wait
                }
                select_fast_wait {
                    name = "選択ウェイト(早い)"
                    formatter = core.locale.config.common.formatter.wait
                }
                joypad {
                    name = "ゲームパッド"
                    yes_no = core.locale.config.common.yes_no.unsupported # core.locale.config.common.yes_no.shiyou_suru_shinai
                }
            }

            font {
                name = "フォント設定"
                vertical_offset {
                    name = "垂直オフセット"
                    doc = "テキストを表示する際、垂直方向にこの値だけずらして表示します。\nお使いのフォントに合わせて調整してください。"
                }
                size_adjustment {
                    name = "サイズの調整"
                }
            }

            message {
                name = "メッセージとログ"
                add_timestamps {
                    name = "ﾒｯｾｰｼﾞに分表示追加"
                    doc = "メッセージに現在の分を表示します。"
                }
                transparency {
                    name = "過去のﾒｯｾｰｼﾞの透過"
                    formatter = "${_1}*10 %" #TODO
                    doc = "古いメッセージをこのパーセンテージだけ透明にして表示します。"
                }
            }

            balance {
                name = "ゲームバランス設定"
                restock_interval {
                    name = "入荷頻度"
                    formatter = "${_1}日" # TODO
                    doc = "店主の品物が入荷する頻度を変更します。"
                }
                extra_race {
                    name = "Extra種族"
                }
                extra_class {
                    name = "Extra職業"
                }
            }

            language {
                name = "言語(Language)"

                language {
                    name = "言語*"
                    variants {
                        jp = "Japanese"
                        en = "English"
                    }
                }
            }

            foobar {
                name = "拡張設定(foobar)"

                hp_bar_position {
                    name = "ペットのHPバー"
                    variants {
                        hide = "表示しない"
                        left = "左側に表示"
                        right = "右側に表示"
                    }
                    doc = "聴診器を当てたペットのHPを表示します。\n[右側に表示]を推奨しています。"
                }
                allow_enhanced_skill_tracking {
                    name = "スキルトラック拡張"
                    doc = "スキルトラックに潜在能力を表示します。"
                }
                enhanced_skill_tracking_lowerbound {
                    name = "スキルトラック拡張(下限)"
                    doc = "この値よりも潜在能力が低い場合赤色で表示されます。\nスキルトラック拡張を[する]に設定している場合にのみ効果があります。"
                }
                enhanced_skill_tracking_upperbound {
                    name = "スキルトラック拡張(上限)"
                    doc = "この値よりも潜在能力が高い場合緑色で表示されます。\nスキルトラック拡張を[する]に設定している場合にのみ効果があります。"
                }
                leash_icon {
                    name = "紐のアイコン表示"
                    doc = "紐で繋がれているペットのHPバーの横に紐のアイコンを表示します。\nペットのHPバーを[左側に表示]か[右側に表示]にしている場合にのみ効果があります。"
                }
                autopick {
                    name = "Autopick"
                    yes_no = core.locale.config.common.yes_no.tsukau_tsukawanai
                    doc = "特定のアイテムの上に乗ったとき自動でそのアイテムを拾います。"
                }
                autosave {
                    name = "オートセーブ"
                    yes_no = core.locale.config.common.yes_no.yuukou_mukou
                    doc = "特定の行動をした後に自動でセーブされます。"
                }
                damage_popup {
                    name = "ダメージポップアップ"
                    yes_no = core.locale.config.common.yes_no.ari_nashi
                }
                max_damage_popup {
                    name = "ダメージポップアップ最大数"
                }
                startup_script {
                }

                pcc_graphic_scale = {
                    name = "PCC表示"
                    variants {
                        shrinked = "縮小(通常)"
                        fullscale = "原寸"
                    }
                }
            }

            android {
                name = "アンドロイド設定"

                vibrate {
                    name = "振動"
                }

                vibrate_duration {
                    name = "振動の期間"
                }

                hide_navigation {
                    name = "ナビゲーションバーの非表示*"
                }

                quicksave {
                    name = "中断した時のセーブ"
                }

                quick_action_transparency {
                    name = "ボタンの透明度"
                }

                quick_action_size {
                    name = "ボタンのサイズ"
                }
            }

            keybindings {
                name = "キーの割り当て"
            }
        }
    }
}
