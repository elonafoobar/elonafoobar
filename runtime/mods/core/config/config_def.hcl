config def {
    game = {
        type = "section"
        options = {
            extra_help = true
            attack_neutral_npcs = false

            default_save = {
                type = "runtime_enum"
                default = ""
                preload = true
                translate_variants = false
            }

            story = true
            hide_autoidentify = false
            hide_shop_updates = false
        }
    }

    screen = {
        type = "section"
        options = {
            sound = {
                default = true
                preload = true
            }

            music = {
                default = true
                preload = true
            }

            stereo_sound = true

            fullscreen = {
                type = "enum"
                platform = "desktop"
                preload = true
                variants = ["windowed", "fullscreen", "desktop_fullscreen"]
                default = "windowed"
            }

            display_mode = {
                type = "runtime_enum"
                platform = "desktop"
                translate_variants = false
                preload = true
            }

            window_mode = {
                platform = "android"
                preload = true

                type = "enum"
                translate_variants = false
                variants = ["800x600", "1024x600", "1280x720",
                    "800x696", "1024x768", "1152x864",
                    "1280x768", "1280x1024", "1366x768",
                    "1600x900", "1600x1200"]
                default = "1024x600"
            }

            orientation = {
                platform = "android"

                type = "enum"
                variants = ["sensor_landscape", "sensor_portrait", "sensor",
                    "landscape", "portrait",
                    "reverse_landscape", "reverse_portrait"]
                default = "sensor_landscape"
            }

            high_quality_shadows = true
            object_shadows = true
            heartbeat = true

            heartbeat_threshold {
                default = 25
                min = 1
                max = 50
            }

            skip_random_event_popups = false
        }
    }

    net = {
        type = "section"
        options = {
            enabled = false
            wish = false
            chat = false
            server_list = false
        }
    }

    anime = {
        type = "section"
        options = {
            scroll = {
                default = true

                platform_default {
                    android = false
                }
            }
            always_center = true
            scroll_when_run = true

            general_wait = {
                default = 30
                min = 0
                max = 50
            }

            anime_wait = {
                default = 20
                min = 0
                max = 20

                platform_default {
                    android = 10
                }
            }

            alert_wait = {
                default = 50
                min = 0
                max = 50

                platform_default {
                    android = 25
                }
            }

            auto_turn_speed = {
                type = "enum"
                default = "normal"
                variants = ["normal", "high", "highest"]
            }

            attack_anime = true
            weather_effect = true
            title_effect = false
            window_anime = false

            screen_refresh = {
                default = 3
                min = 0
                max = 15

                platform_default {
                    android = 5
                }
            }
        }
    }

    input = {
        type = "section"
        options = {
            autodisable_numlock = true

            walk_wait = {
                default = 5
                min = 1
                max = 10
            }

            start_run_wait = {
                default = 2
                min = 0
                max = 5
            }

            run_wait = {
                default = 2
                min = 1
                max = 10
            }

            attack_wait = {
                default = 4
                min = 1
                max = 10
            }

            key_wait = {
                preload = true # Needs to be available for language selection screen
                default = 5
                min = 1
                max = 10
            }

            select_wait = {
                default = 10
                min = 1
                max = 20

                platform_default {
                    android = 8
                }
            }

            select_fast_start_wait = {
                default = 2
                min = 0
                max = 10
            }

            select_fast_wait = {
                default = 2
                min = 1
                max = 20

                platform_default {
                    android = 2
                }
            }

            joypad = {
                default = false
                preload = true
            }
        }
    }

    font = {
        type = "section"
        options = {
            file = "GenShinGothic/GenShinGothic-Monospace-Regular.ttf"

            vertical_offset = {
                default = -1
                min = -10
                max = 10
            }
            size_adjustment = {
                default = 1
                min = -5
                max = 5
            }
            quality = {
                type = "enum"
                default = "high"
                variants = ["low", "high"]
            }
        }
    }

    message = {
        type = "section"
        options = {
            add_timestamps = false

            transparency = {
                default = 4
                min = 0
                max = 10
            }
        }
    }

    balance = {
        type = "section"
        options = {
            restock_interval = {
                default = 3
                min = 0
                max = 10
            }

            extra_race = {
                default = false
                preload = true
            }

            extra_class = {
                default = false
                preload = true
            }
        }
    }

    language = {
        type = "section"
        options = {
            language = {
                type = "runtime_enum"
                preload = true
            }
        }
    }

    foobar = {
        type = "section"
        options = {
            hp_bar_position = {
                type = "enum"
                default = "right"
                variants = ["hide", "left", "right"]
            }
            allow_enhanced_skill_tracking =true
            enhanced_skill_tracking_lowerbound = {
                default = 50
                min = 0
                max = 390
            }
            enhanced_skill_tracking_upperbound = {
                default = 100
                min = 10
                max = 400
            }
            leash_icon = true
            autopick = true
            autosave = false
            damage_popup = {
                default = true

                platform_default {
                    android = false
                }
            }
            max_damage_popup = {
                default = 100
                min = 10
                max = 100
            }

            startup_script = {
                default = ""
                visible = false
            }

            run_script_in_save = {
                default = false
                visible = false
            }

            pcc_graphic_scale = {
                type = "enum"
                default = "shrinked"
                variants = ["shrinked", "fullscale"]
            }

            show_fps = false

            skip_confirm_at_shop = false

            skip_overcasting_warning = false
        }
    }

    ### Hidden sections

    android = {
        type = "section"
        platform = "android"
        options = {
            quicksave = true
            vibrate = true

            vibrate_duration = {
                default = 8
                min = 1
                max = 40
            }

            hide_navigation = {
                preload = true
                default = false
            }

            quick_action_transparency = {
                default = 10
                min = 1
                max = 20
            }

            quick_action_size = {
                default = 24
                min = 20
                max = 40
            }
        }
    }

    debug = {
        type = "section"
        visible = false
        options = {
            wizard = {
                default = false
                preload = true
            }
        }
    }
}
