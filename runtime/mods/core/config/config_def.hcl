config def {
    screen = {
        type = "section"
        options = {
            fullscreen = {
                platform = "desktop"
                type = "enum"
                preload = true
                variants = ["windowed", "fullscreen", "desktop_fullscreen"]
                default = "windowed"
            }

            display_mode = {
                platform = "desktop"
                type = "runtime_enum"
                translate_variants = false
                preload = true
            }

            fullscreen_android = {
                platform = "android"
                default = false
            }

            fullscreen_scale = {
                platform = "android"
                dependencies = {
                    "core.config.screen.fullscreen_android" = true
                }

                default = 4
                min = 4 # * 0.25 = 1.00
                max = 8 # * 0.25 = 2.00
            }

            classic_display_mode = {
                platform = "android"
                dependencies = {
                    "core.config.screen.fullscreen_android" = false
                }

                type = "enum"
                preload = true
                # These are the screen resolutions that are supported by vanilla Elona.
                variants = ["800x600", "800x696", "1024x768",
                    "1152x864", "1280x768", "1280x1024"]
                default = "800x600"
            }

            music = {
                type = "enum"
                variants = ["none", "direct_music", "mci"]
                default = "direct_music"
                preload = true
            }

            sound = {
                default = true
                preload = true
            }

            high_quality_shadows = true
            object_shadows = true
            heartbeat = true
            skip_random_event_popups = true
        }
    }

    net = {
        type = "section"
        options = {
            enabled = false
            wish = {
                dependencies = {
                    "core.config.net.enabled" = true
                }
                default = false
            }
            chat = {
                dependencies = {
                    "core.config.net.enabled" = true
                }
                default = false
            }
            server_list = {
                dependencies = {
                    "core.config.net.enabled" = true
                }
                default = false
            }
        }
    }

    anime = {
        type = "section"
        options = {
            scroll = true
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
            }

            alert_wait = {
                default = 50
                min = 0
                max = 50
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
                default = 2
                min = 0
                max = 15
            }
        }
    }


    font = {
        type = "section"
        options = {
            japanese = "Kochi Gothic.ttf"
            english = "Bitstream Sans Vera Mono.ttf"

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
        }
    }

    game = {
        type = "section"
        options = {
            default_save = {
                type = "runtime_enum"
                default = ""
                preload = true
                translate_variants = false
            }

            attack_neutral_npcs = false
            story = true
            extra_help = true
            hide_autoidentify = false
            hide_shop_updates = false
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
            noa_debug = false
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

    input = {
        type = "section"
        options = {
            joypad = {
                default = false
                preload = true
            }
            autodisable_numlock = true

            walk_wait = {
                default = 5
                min = 0
                max = 10
            }

            start_run_wait = {
                default = 2
                min = 0
                max = 5
            }

            run_wait = {
                default = 2
                min = 0
                max = 10
            }

            attack_wait = {
                default = 4
                min = 0
                max = 10
            }

            key_wait = {
                default = 5
                min = 1
                max = 10
            }

            select_wait = {
                default = 10
                min = 1
                max = 20
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

    foobar = {
        type = "section"
        options = {
            hp_bar_position = {
                type = "enum"
                default = "right"
                variants = ["hide", "left", "right"]
            }

            leash_icon = true
            autopick = true
            autosave = true
            damage_popup = true

            startup_script = {
                default = ""
                visible = false
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

    ui = {
        type = "section"
        visible = false
        doc = <<DOC
These settings are for internal use.
Changing them may break things.
DOC
        options = {
            msg_line = {
                default = 4
                min = 0
                max = 8
                preload = true
            }
            tile_size = {
                default = 48
                min = 48
                max = 48
                preload = true
            }
            font_size = {
                default = 14
                min = 14
                max = 14
                preload = true
            }
            inf_ver_type = {
                default = 1
                min = 1
                max = 1
                preload = true
            }
            window_x = {
                default = 800
                min = 800
                max = 1600
                preload = true
            }
            window_y = {
                default = 800
                min = 800
                max = 1600
                preload = true
            }
            clock_x = {
                default = 0
                min = 0
                max = 10000
                preload = true
            }
            clock_w = {
                default = 120
                min = 0
                max = 800
                preload = true
            }
            clock_h = {
                default = 120
                min = 0
                max = 600
                preload = true
            }
        }
    }

    key = {
        type = "section"
        visible = false
        options = {
            north = "8 "
            south = "2 "
            west = "4 "
            east = "6 "
            northwest = "7 "
            northeast = "9 "
            southwest = "1 "
            southeast = "3 "
            wait = "5 "

            cancel = "\\"
            esc = "^"
            alter = "["
            pageup = "+"
            pagedown = "-"
            mode = "z"
            mode2 = "*"

            quick_menu = "z"
            zap = "Z"
            inventory = "X"
            quick_inventory = "x" # quickinv
            get = "g"
            get2 = "0 "
            drop = "d"
            chara_info = "c" # charainfo
            enter = " "
            eat = "e"
            wear = "w"
            cast = "v"
            drink = "q"
            read = "r"
            fire = "f"
            go_down = ">" # goDown
            go_up = "<" # goUp
            save = "S"
            search = "s"
            interact = "i"
            identify = "x"
            skill = "a"
            close = "C"
            rest = "R"
            target = "*"
            dig = "D"
            use = "t"
            bash = "b"
            open = "o"
            dip = "B"
            pray = "p"
            offer = "O"
            journal = "j"
            material = "m"
            trait = "F"
            look = "l"
            give = "G"
            throw = "T"
            ammo = "A"
            autodig = "H"

            quicksave = "F1"
            quickload = "F2"
            help = "?"
            message_log = "/"

            key_set = ["a", "b", "c", "d", "e",
                "f", "g", "h", "i", "j",
                "k", "l", "m", "n", "o",
                "p", "q", "r", "s"]
        }
    }

    android = {
        type = "section"
        platform = "android"
        options = {
            quick_action_scale = {
                default = 100
                min = 10
                max = 500
            }
        }
    }
}
