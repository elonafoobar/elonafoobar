# TODO: autogenerate config menu from this structure
# TODO: localize doc strings

config_def {
    default_save = {
        default = ""
        visible = false
        preload = true
    }

    screen = {
        type = "section"
        visible = true
        options = {
            fullscreen = {
                type = "enum"
                preload = true
                variants = ["windowed", "fullscreen", "desktop_fullscreen"]
                default = "windowed"
                doc = "Fullscreen mode."
            }

            display_mode = {
                type = "display_mode"
                default = ""
                preload = true
            }

            enable_music = true
            enable_sound = true

            always_center = {
                default = ""
                doc = "Always keep the center of the screen near the player when walking near the edge of the screen."
            }

            high_quality_shadows = {
                default = true
                doc = "Render shadows at higher quality."
            }

            object_shadow = {
                default = true
                doc = "Render shadows at higher quality."
            }

            heartbeat = {
                default = true
                doc = "Play heartbeat sound when health is low."
            }

            skip_random_event_popups = {
                default = true
                doc = <<DOC
Skip displaying random event popup windows.
Random events will still occur.
DOC
            }
        }
    }

    anime = {
        type = "section"
        visible = true
        options = {
            scroll = {
                default = true
                doc = "Enable scrolling animations."
            }

            scroll_when_run = {
                default = true
                doc = <<DOC
Show scrolling animations when running.
Turning this off can speed up running somewhat.
DOC
            }

            general_wait = {
                default = 30
                min = 0
                max = 50
                doc = "Number of frames to wait for most animations/actions."
            }

            anime_wait = {
                default = 20
                min = 0
                max = 20
                doc = <<DOC
Number of frames to wait for animations.
This also acts as multiplier for the speed of auto-turn actions.
DOC
            }

            alert_wait = {
                default = 50
                min = 0
                max = 50
                doc = <<DOC
Number of frames to wait if an important message is received.
These are: leveling up, leveling up a skill, or having a change in hunger status.
DOC
            }

            auto_turn_speed = {
                type = "enum"
                default = "normal"
                variants = ["normal", "high", "highest"]
                doc = "Speed of auto-turn actions."
            }

            attack_anime = {
                default = true
                doc = "Play animations when melee attacking."
            }

            env_effect = {
                default = true
                doc = "Play weather-related animations."
            }

            title_effect = {
                default = false
                doc = <<DOC
Play animations at the title screen.
NOTE: Currently not implemented.
DOC
            }

            window_anime = {
                default = false
                doc = "Play window animations."
            }

            screen_refresh = {
                default = 2
                min = 0
                max = 15
                doc = <<DOC
Number of frames to wait between updates to animations in the screen, like rain/lighting.
This does not affect key delay or animations that block input.
DOC
            }
        }
    }

    net = {
        type = "section"
        visible = false
        options = {
            enabled = false
            wish = false
            chat = false
            server_list = false
        }
    }


    font = {
        type = "section"
        visible = true
        doc = <<DOC
Font-related settings.
Place fonts (TTF format) in data/font. Please ensure the fonts are monospaced to avoid issues.
DOC
        options = {
            japanese = "Kochi Gothic.ttf"
            english = "Bitstream Sans Vera Mono.ttf"

            vertical_offset = -1 # fontVfix1
            size_adjustment = 1 # fontSfix1
        }
    }

    game = {
        type = "section"
        visible = true
        options = {
            attack_neutral_npcs = {
                default = false # ignore_dislike
                doc = "Attack non-hostile, non-ally NPCs when running into them."
            }

            story = {
                default = true
                doc = "Enable playback of the story."
            }

            extra_help = {
                default = true
                doc = "Show extra help popups for new players."
            }

            show_autoidentify = {
                default = true
                doc = "Show identify status updates from Sense Quality."
            }

            show_shop_updates = {
                default = true # hide_shopResult
                doc = "Show daily shop reports of items sold for player-owned shops."
            }
        }
    }

    debug = {
        type = "section"
        visible = false
        options = {
            wizard = false
            noa_debug = false
        }
    }

    message = {
        type = "section"
        visible = true
        options = {
            add_timestamps = false

            transparency = {
                default = 4
                min = 0
                max = 10
                doc = "Message box transparency."
            }
        }
    }

    input = {
        type = "section"
        visible = true
        options = {
            joypad = false
            autodisable_numlock = true

            walk_wait = {
                default = 5
                min = 0
                max = 10
                doc = "Number of frames to wait between movement commands when walking."
            }

            start_run_wait = {
                default = 2
                min = 0
                max = 5
                doc = "Number of movement commands to run when walking before starting to run."
            }

            run_wait = {
                default = 2
                min = 0
                max = 10
                doc = "Number of frames to wait between movement commands when running."
            }

            attack_wait = {
                default = 4
                min = 0
                max = 10
                doc = "Number of frames to wait between consecutive attacks when running into enemies."
            }

            key_wait = {
                default = 5
                min = 1
                max = 10
                doc = "Number of frames to wait between presses of shortcut keys."
            }
        }
    }

    balance = {
        type = "section"
        visible = true
        doc = "These settings affect game balance."
        options = {
            restock_interval = {
                default = 3
                min = 0
                max = 10
                doc = <<DOC
Interval in days it takes shops to restock items.
If 0, the item selection will change each time you interact with a shopkeeper.
DOC
            }

            extra_race = {
                default = true
                doc = "Enable extra races in character creation."
            }

            extra_class = {
                default = true
                doc = "Enable extra classes in character creation."
            }
        }
    }

    foobar = {
        type = "section"
        visible = true
        doc = "Extra config settings added in ElonaFoobar."
        options = {
            hp_bar_position = {
                type = "enum"
                default = "right"
                variants = ["hide", "left", "right"]
                doc = "Position to display the HP bar at."
            }

            leash_icon = {
                default = true
                doc = "Shows an icon for pets that are leashed."
            }

            autopick = {
                default = true
                doc = "Automatically pick up items you pass over."
            }

            autosave = {
                default = false
                doc = "Automatically save the game at certain intervals."
            }

            startup_script = {
                default = ""
                doc = <<DOC
Run a script in the data/script/ folder at startup.
Provide a script's name, like "my_script.lua" for "data/script/my_script.lua".
DOC
            }

            damage_popup = {
                default = true
                doc = "Show damage popups."
            }
        }
    }

    language = {
        type = "section"
        visible = true
        options = {
            language = {
                type = "language"
                preload = true
                default = ""
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
}
