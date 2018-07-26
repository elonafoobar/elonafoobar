locale {
    config {
        common {
            menu = "Menu"
            require_restart = "Items marked with * require restart to apply changes."
            assign_button = "To assign a button, move the cursor to\nan item and press the button."

            yes_no {
                # NOTE: This text is implicitly chosen for boolean values without an explicit
                # "yes_no" option.
                default {
                    yes = "Yes"
                    no = "No"
                }

                play_dont_play {
                    yes = "Play"
                    no = "Don't play"
                }

                # NOTE: "Slow" and "Fast" were originally the opposite in English.
                slow_fast {
                    yes = "Yes(Slow)"
                    no = "No(Fast)"
                }

                high_low {
                    yes = "High"
                    no = "Low"
                }

                show_dont_show {
                    yes = "Show"
                    no = "Don't show"
                }

                use_dont_use {
                    yes = "Use"
                    no = "Don't use"
                }

                enable_disable {
                    yes = "Enable"
                    no = "Disable"
                }

                on_off {
                    yes = "On"
                    no = "Off"
                }

                unsupported {
                    yes = "No(unsupported)"
                    no = "No(unsupported)"
                }
            }

            formatter {
                wait = "${_1} wait"
            }
        }

        menu {
            name = "Option"

            game {
                name = "Game Setting"
                extra_help {
                    name = "Extra Help"
                    doc = "Show extra help popups for new players."
                }
                attack_neutral_npcs {
                    name = "Attack Netural NPCs"
                    doc = "Attack non-hostile, non-ally NPCs when running into them."
                }
                default_save {
                    name = "Default Save"
                    doc = "Saved game to be loaded on startup."
                    variants {
                        "" = "None"
                    }
                }
                story {
                    name = "Enable Cutscenes"
                    doc = "Enable playback of the story cutscenes."
                }
                hide_autoidentify {
                    name = "Hide Auto-Identify"
                    doc = "Hide identify status updates from Sense Quality."
                }
                hide_shop_updates {
                    name = "Hide Shop Updates"
                    doc = "Hide daily shop reports of items sold for shops you own."
                }
            }

            screen {
                name = "Screen & Sound"
                sound {
                    name = "Sound*"
                    yes_no = core.locale.config.common.yes_no.on_off
                }
                music {
                    name = "Music*"
                    variants {
                        none = "None"
                        direct_music = "Direct music"
                        mci = "MCI"
                    }
                }
                stereo_sound {
                  name = "Stereo Sound"
                }
                fullscreen {
                    name = "Screen Mode*"
                    variants {
                        windowed = "Window mode"
                        fullscreen = "Full screen"
                        desktop_fullscreen = "Desktop fullscr"
                    }
                    doc = "Fullscreen mode."
                }
                display_mode {
                    name = "Screen Resolution*"
                    # Variants are injected at runtime.
                }
                orientation {
                    name = "Screen Orientation"
                    variants {
                        sensor_landscape = "Landscape (Auto)"
                        sensor_portrait = "Portrait (Auto)"
                        sensor = "Any"
                        landscape = "Landscape"
                        portrait = "Portrait"
                        reverse_landscape = "Reverse Landscape"
                        reverse_portrait = "Reverse Portrait"
                    }
                }
                window_mode {
                    name = "Window Size*"
                }
                high_quality_shadows {
                    name = "Shadow Quality"
                    doc = "Render shadows at higher quality."
                    yes_no = core.locale.config.common.yes_no.high_low
                }
                object_shadows {
                    name = "object Shadow"
                    doc = "Display shadows under items on the ground."
                    yes_no = core.locale.config.common.yes_no.slow_fast
                }
                heartbeat {
                    name = "Heartbeat Sound"
                    doc = "Play heartbeat sound when health is low."
                }
                heartbeat_threshold {
                    name = "Heartbeat Threshold"
                    doc = "% of HP remaining to play heartbeat sound at."
                }
                skip_random_event_popups {
                    name = "Skip Random Events"
                    doc = <<DOC
Skip displaying random event popup windows.
Random events will still occur.
DOC
                }
            }

            net {
                name = "Network Setting"
                enabled {
                    name = "Use Network"
                }
                wish {
                    name = "Constantly Connect"
                }
                chat {
                    name = "Filter Chat"
                }
                server_list {
                    name = "Use Custom Server"
                }
            }

            anime {
                name = "Animation Setting"
                scroll {
                    name = "Smooth Scroll"
                    doc = "Enable scrolling animations."
                }
                always_center {
                    name = "Always Center"
                    doc = "Always keep the center of the screen near the player when walking near the edge of the screen."
                }
                scroll_when_run {
                    name = "Scroll When Run"
                    doc = <<DOC
Show scrolling animations when running.
Turning this off can speed up running somewhat.
DOC
                }
                general_wait {
                    name = "General Wait"
                    formatter = core.locale.config.common.formatter.wait
                    doc = "Number of frames to wait for most animations/actions."
                }
                anime_wait {
                    name = "Animation Wait"
                    formatter = core.locale.config.common.formatter.wait
                    doc = <<DOC
Number of frames to wait for animations.
This also acts as multiplier for the speed of auto-turn actions.
DOC
                }
                alert_wait {
                    name = "Alert Wait"
                    doc = <<DOC
Number of frames to wait if an important message is received.
These are: leveling up, leveling up a skill, or having a change in hunger status.
DOC
                }
                auto_turn_speed {
                    name = "Auto Turn Speed"
                    variants {
                        normal = "Normal"
                        high = "High"
                        highest = "Highest"
                    }
                    doc = <<DOC
Speed of auto-turn actions.
This is also affected by "Animation Wait".
DOC
                }
                attack_anime {
                    name = "Attack Animation"
                    doc = "Play animations when melee attacking."
                }
                weather_effect {
                    name = "Weather Effect"
                    doc = "Play weather-related animations."
                }
                title_effect {
                    name = "Title Water Effect"
                    yes_no = core.locale.config.common.yes_no.unsupported
                    doc = <<DOC
Play animations at the title screen.
NOTE: Currently not implemented.
DOC
                }
                window_anime {
                    name = "Window Animation"
                    doc = "Play window animations."
                }
                screen_refresh {
                    name = "Screen Refresh"
                    formatter = core.locale.config.common.formatter.wait
                    doc = <<DOC
Number of frames to wait between updates to animations in the screen, like rain/lighting.
This does not affect key delay or animations that block input.
DOC
                }
            }

            input {
                name = "Input Setting"
                autodisable_numlock {
                    name = "Auto-Disable Numlock"
                }
                assign_z_key {
                    name = "Assign z key"
                    variants {
                        quick_menu = "Quick menu"
                        zap = "Zap"
                        none = "Don't assign"
                    }
                }
                assign_x_key {
                    name = "Assign x key"
                    variants {
                        quick_inv = "Quick Inv"
                        identify = "Identify"
                        none = "Don't assign"
                    }
                }
                walk_wait {
                    name = "Walk Speed"
                    doc = "Number of frames to wait between movement commands when walking."
                    formatter = core.locale.config.common.formatter.wait
                }
                run_wait {
                    name = "Run Speed"
                    doc = "Number of frames to wait between movement commands when running."
                    formatter = core.locale.config.common.formatter.wait
                }
                start_run_wait {
                    name = "Run Start Wait"
                    doc = "Number of movement commands to play when walking before starting to run."
                    formatter = "${After } ${_1}+1 steps" # TODO
                }
                attack_wait {
                    name = "Attack Interval"
                    doc = "Number of frames to wait between consecutive attacks when running into enemies."
                    formatter = core.locale.config.common.formatter.wait
                }
                key_wait {
                    name = "Key Wait"
                    doc = "Number of frames to wait between presses of shortcut keys."
                    formatter = core.locale.config.common.formatter.wait
                }
                select_wait {
                    name = "Select Wait"
                    doc = "Number of frames to wait between item selection initially."
                    formatter = core.locale.config.common.formatter.wait
                }
                select_fast_start_wait {
                    name = "Select Fast Start Wait"
                    doc = "Number of selections to wait before selecting quickly."
                    formatter = core.locale.config.common.formatter.wait
                }
                select_fast_wait {
                    name = "Select Fast Wait"
                    doc = "Number of frames to wait between item selection when selecting quickly."
                    formatter = core.locale.config.common.formatter.wait
                }
                joypad {
                    name = "Game Pad"
                    yes_no = core.locale.config.common.yes_no.unsupported #core.locale.config.common.yes_no.use_dont_use
                }
            }

            font {
                name = "Font Setting"
                doc = <<DOC
Font-related settings.
Place fonts (TTF format) in data/font. Please ensure the fonts are monospaced to avoid issues.
DOC
                vertical_offset {
                    name = "Vertical Offset"
                }
                size_adjustment {
                    name = "Size Adjustment"
                }
            }

            message {
                name = "Message&Log"
                add_timestamps {
                    name = "Add time info"
                }
                transparency {
                    name = "Transparency"
                    doc = "Message box transparency."
                    formatter = "${_1}*10 %"#TODO
                }
            }

            balance {
                name = "Game Balance Setting"
                doc = "These settings affect game balance."
                restock_interval {
                    name = "Restock Interval"
                    formatter = "${_1} day${s(_1)}" # TODO
                    doc = <<DOC
Interval in days it takes shops to restock items.
If 0, the item selection will change each time you interact with a shopkeeper.
DOC
                }
                extra_race {
                    name = "Extra Race"
                    doc = "Enable extra races in character creation."
                }
                extra_class {
                    name = "Extra Class"
                    doc = "Enable extra classes in character creation."
                }
            }

            language {
                name = "Language"

                language {
                    name = "Language*"
                    variants {
                        jp = "Japanese"
                        en = "English"
                    }
                }
            }

            foobar {
                name = "Ex setting(Foobar)"
                doc = "Extra config settings added in ElonaFoobar."

                hp_bar_position {
                    name = "Pets' HP bar"
                    variants {
                        hide = "Don't show"
                        left = "Show left side"
                        right = "Show right side"
                    }
                }
                leash_icon {
                    name = "Leash icon"
                    yes_no = core.locale.config.common.yes_no.show_dont_show
                }
                autopick {
                    name = "Autopick"
                    doc = "Automatically pick up items you pass over."
                    yes_no = core.locale.config.common.yes_no.use_dont_use
                }
                autosave {
                    name = "Autosave"
                    doc = "Automatically save the game at certain intervals."
                    yes_no = core.locale.config.common.yes_no.enable_disable
                }
                damage_popup {
                    name = "Damage popup"
                    doc = "Show damage popups."
                    yes_no = core.locale.config.common.yes_no.on_off
                }
                startup_script {
                    doc = <<DOC
Run a script in the data/script/ folder at startup.
Provide a script's name, like "my_script.lua" for "data/script/my_script.lua".
DOC
                }
            }

            android {
                name = "Android Setting"

                vibrate {
                    name = "Vibrate"
                    doc = <<DOC
Vibrate on important events/low health.
DOC
                }

                vibrate_duration {
                    name = "Vibrate Duration"
                }

                hide_navigation {
                    name = "Hide Nav Buttons*"
                    doc = <<DOC
Hides the software navigation buttons for handsets without hardware navigation buttons.
DOC
                }

                quicksave {
                    name = "Save On Suspend"
                    doc = <<DOC
Quicksave the game if you're being queried for input and app focus is lost.
DOC
                }

                quick_action_transparency {
                    name = "Quick Action Transp."
                }

                quick_action_size {
                    name = "Quick Action Size"
                }

                quick_action_repeat_start_wait {
                    name = "Quick Action Repeat Wait"
                }

                quick_action_repeat_wait {
                    name = "Quick Action Wait"
                }
            }
        }
    }
}
