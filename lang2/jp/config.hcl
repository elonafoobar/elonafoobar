locale {
    config {
        common {
            menu = "項目"

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

                kougashitsu_teigatshitsu {
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
            language {
                name = "言語(Language)"

                language {
                    name = "言語*"
                    # Variants are injected at runtime.
                }
            }
            screen {
                name = "画面と音の設定"
                warning = "TODO"
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
                sound {
                    name = "サウンドの再生*"
                    yesno = core.locale.config.common.yes_no.ari_nashi
                }
                music {
                    name = "midiの再生*"
                    variants {
                        none = "なし"
                        direct_music = "direct music"
                        mci = "MCI"
                    }
                }
                high_quality_shadows {
                    name = "光源の描写"
                    yesno = core.locale.config.common.yes_no.kougashitsu_teigashitsu
                }
                object_shadow {
                    name = "アイテムの影描写"
                    yesno = core.locale.config.common.yes_no.ari_nashi_slow_fast
                }
                heartbeat {
                    name = "心臓の音"
                }
                skip_random_event_popups {
                    name = "イベントの短縮"
                }
            }
            net {
                name = "ネット機能の設定"
                enabled {
                    name = "ネットの使用"
                }
                wish {
                    name = "定期的に接続"
                }
                chat {
                    name = "チャットをフィルタ"
                }
                server_list {
                    name = "Use Custom Server"
                }
            }
            anime {
                name = "アニメ設定"
                scroll {
                    name = "スクロール"
                }
                always_center {
                    name = "主人公中心に描写"
                }
                scroll_when_run {
                    name = "走り時スクロール"
                }
                general_wait {
                    name = "General Wait"
                    formatter = core.locale.config.common.formatter.wait
                }
                anime_wait {
                    name = "アニメウェイト"
                    formatter = core.locale.config.common.formatter.wait
                }
                alert_wait {
                    name = "アラートウェイト"
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
                }
                weather_effect {
                    name = "天候エフェクト"
                }
                title_effect {
                    name = "タイトルの水の波紋"
                    yes_no = core.locale.config.common.yes_no.unsupported
                }
                window_anime {
                    name = "Window Animation"
                }
                screen_refresh {
                    name = "画面の更新頻度"
                    formatter = core.locale.config.common.formatter.wait
                }
            }

            font {
                name = "Font Setting"
                vertical_offset {
                    name = "Vertical Offset"
                }
                size_adjustment {
                    name = "Size Adjustment"
                }
            }

            game {
                name = "Game Setting"
                attack_neutral_npcs {
                    name = "Attack Netural NPCs"
                }
                story {
                    name = "Enable Cutscenes"
                }
                extra_help {
                    name = "ノルンの冒険ガイド"
                }
                hide_autoidentify {
                    name = "Hide Auto-Identify"
                }
                hide_shop_updates {
                    name = "Hide Show Updates"
                }
            }

            message {
                name = "メッセージとログ"
                add_timestamps {
                    name = "ﾒｯｾｰｼﾞに分表示追加"
                }
                transparency {
                    name = "過去のﾒｯｾｰｼﾞの透過"
                    formatter = "${_1}*10 %"#TODO export?
                }
            }

            input {
                name = "Input Setting"
                joypad {
                    name = "ゲームパッド"
                    yes_no = core.locale.config.common.yes_no.use_dont_use
                }
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
                    name = "Run Start Wait"
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
                    name = "Select Wait"
                    formatter = core.locale.config.common.formatter.wait
                }
                select_fast_start_wait {
                    name = "Select Fast Start Wait"
                    formatter = core.locale.config.common.formatter.wait
                }
                select_fast_wait {
                    name = "Select Fast Wait"
                    formatter = core.locale.config.common.formatter.wait
                }
            }

            balance {
                name = "Game Balance Setting"
                restock_interval {
                    name = "入荷頻度"
                    formatter = "${_1}日" # TODO export?
                }
                extra_race {
                    name = "Extra種族"
                }
                extra_class {
                    name = "Extra職業"
                }
            }

            foobar {
                name = "拡張設定(Foobar)"

                hp_bar_position {
                    name = "ペットのHPバー"
                    variants {
                        hide = "表示しない"
                        left = "左側に表示"
                        right = "右側に表示"
                    }
                }
                leash_icon {
                    name = "紐のアイコン表示"
                }
                autopick {
                    name = "Autopick"
                    yesno = core.locale.config.common.yes_no.tsukau_tsukawanai
                }
                autosave {
                    name = "オートセーブ"
                    yesno = core.locale.config.common.yes_no.yuukou_mukou
                }
                damage_popup {
                    name = "ダメージポップアップ"
                    yesno = core.locale.config.common.yes_no.ari_nashi
                }
                startup_script {
                }
            }
        }
    }
}
