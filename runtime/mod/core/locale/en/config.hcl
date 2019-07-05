locale {
    config {
        common {
            menu = "Menu"
            require_restart = "Items marked with * require restart to apply changes."
            assign_button = "To assign a button, move the cursor to\nan item and press the button."
            no_desc = "(No description available.)"

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

                slow_fast {
                    yes = "Yes (Slow)"
                    no = "No (Fast)"
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
                every_minutes = "Every ${_1} min."
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
                    doc = <<DOC
Saved game to be loaded on startup.
These are calculated when the game loads.
If one is missing, restart the game to have it appear.
DOC
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
                    doc = "Enable or disable sound."
                }
                music {
                    name = "Music*"
                    yes_no = core.locale.config.common.yes_no.on_off
                    doc = "Enable or disable music."
                }
                stereo_sound {
                    name = "Stereo Sound"
                    doc = <<DOC
Whether or not to play certain sounds based on the position of the source.
Examples are magic casting, eating/drinking, and damage.
DOC
                }
                fullscreen {
                    name = "Screen Mode*"
                    variants {
                        windowed = "Window mode"
                        fullscreen = "Full screen"
                        desktop_fullscreen = "Desktop fullscr"
                    }
                    doc = <<DOC
Fullscreen mode.
'Full screen' will use a hardware fullscreen mode.
'Desktop fullscr' will create a borderless window the same size as the screen.
DOC
                }
                display_mode {
                    name = "Screen Resolution*"
                    doc = <<DOC
Screen resolution to use.
The available options may change depending on the graphics hardware you use.
DOC
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
                    doc = <<DOC
Screen orientation to use when running the app.
Portrait modes will display the game in a window at the top.
Landscape modes will fill the entire screen.
DOC
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
                    name = "Object Shadow"
                    doc = "Display shadows under items on the ground."
                    yes_no = core.locale.config.common.yes_no.slow_fast
                }
                heartbeat {
                    name = "Heartbeat Sound"
                    doc = <<DOC
Play heartbeat sound when health is low.
The threshold to play at is configurable.
DOC
                }
                heartbeat_threshold {
                    name = "Heartbeat Threshold"
                    doc = "% of HP remaining to play heartbeat sound at."
                }
                skip_random_event_popups {
                    name = "Skip Random Events"
                    doc = <<DOC
Skip displaying random event popup windows.
Random events will still occur. In most cases, a default option will be chosen.
DOC
                }
            }

            net {
                name = "Network Setting"
                is_enabled {
                    name = "Use Network"
                    doc = <<DOC
Enable or disable network-related features.
The following options are available only if the option is set to Yes.
DOC
                }
                chat {
                    name = "Chat Log"
                    variants {
                        "disabled" = "Disabled"
                        "receive" = "Only receive"
                        "send_receive" = "Send and receive"
                    }
                }
                death {
                    name = "Death Log"
                    variants {
                        "disabled" = "Disabled"
                        "receive" = "Only receive"
                        "send_receive" = "Send and receive"
                    }
                }
                wish {
                    name = "Wish Log"
                    variants {
                        "disabled" = "Disabled"
                        "receive" = "Only receive"
                        "send_receive" = "Send and receive"
                    }
                }
                news {
                    name = "Palmia Times"
                    variants {
                        "disabled" = "Disabled"
                        "receive" = "Only receive"
                        "send_receive" = "Send and receive"
                    }
                }
                is_alias_vote_enabled {
                    name = "Alias Vote"
                    yes_no = core.locale.config.common.yes_no.enable_disable
                }
                hide_your_name {
                    name = "Hide Your Name"
                    doc = <<DOC
If you set the option Yes, your character's name is replaced with a random name
when sending chat, death or wish log.
When you register your name, the converted one is used, too.
DOC
                }
                hide_your_alias {
                    name = "Hide Your Alias"
                    doc = <<DOC
If you set the option Yes, your character's alias is replaced with a random alias
when sending chat, death or wish log.
When you register your alias, the converted one is used, too.
DOC
                }
                chat_receive_interval {
                    name = "Chat Interval"
                    formatter = core.locale.config.common.formatter.every_minutes
                    doc = <<DOC
Set the interval between receiving chat, death and wish log.
DOC
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
                    doc = <<DOC
Number of frames to wait for most animations/actions.
For example, it controls the amount of delay for input polling.
DOC
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
This is also affected by 'Animation Wait'.
DOC
                }
                attack_anime {
                    name = "Attack Animation"
                    doc = "Play animations when melee/ranged attacking."
                }
                weather_effect {
                    name = "Weather Effect"
                    doc = "Play weather-related animations."
                }
                title_effect {
                    name = "Title Water Effect"
                    yes_no = core.locale.config.common.yes_no.on_off
                    doc = <<DOC
Play animations at the title screen.
DOC
                }
                window_anime {
                    name = "Window Animation"
                    doc = "Play window animations for certain character-related menus."
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
                    doc = <<DOC
If Numlock is on, turns off Numlock while playing and turns it back on again after exiting.
It can fix issues related to holding Shift and a numpad movement key at the same time.
This only has an effect on Windows.
DOC
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
                initial_key_repeat_wait {
                    name = "Initial key repeat wait"
                    doc = "Number of frames to wait between the first action and the second."
                    formatter = core.locale.config.common.formatter.wait
                }
                key_repeat_wait {
                    name = "Key repeat wait"
                    doc = "Number of frames to wait between any actions."
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
                    doc = <<DOC
Enable gamepads.
Currently unimplemented.
DOC
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
                    doc = <<DOC
Vertical text offset for certain menu titles.
DOC
                }
                size_adjustment {
                    name = "Size Adjustment"
                    doc = <<DOC
Size adjustment for certain pieces of text.
DOC
                }
                quality {
                    name = "Rendering Quality"
                    doc = <<DOC
Text rendering quality. High is beautiful, but slow. Low is cheap, but fast.
DOC
                    variants {
                        low = "Low"
                        high = "High"
                    }
                }
            }

            message {
                name = "Message & Log"
                add_timestamps {
                    name = "Add time info"
                    doc = <<DOC
Add a turn timestamp to each message received.
DOC
                }
                transparency {
                    name = "Transparency"
                    doc = "Controls the amount of transparency older message log messages receive."
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
                name = "Ex setting(foobar)"
                doc = "Extra config settings added in Elona foobar."

                hp_bar_position {
                    name = "Pets' HP bar"
                    variants {
                        hide = "Don't show"
                        left = "Show left side"
                        right = "Show right side"
                    }
                }
                allow_enhanced_skill_tracking {
                    name = "Allow enhanced skill tracking"
                    doc = <<DOC
Increases the number of trackable skills to 10 and colorizes potential.
DOC
                }
                enhanced_skill_tracking_lowerbound {
                    name = "Enhanced tracking lowerbound"
                    doc = <<DOC
Potential below this amount will be colored red in the skill tracker.
Only has an effect when used with 'Allow enhanced skill tracking'.
DOC
                }
                enhanced_skill_tracking_upperbound {
                    name = "Enhanced tracking upperbound"
                    doc = <<DOC
Potential above this amount will be colored green in the skill tracker.
Only has an effect when used with 'Allow enhanced skill tracking'.
DOC
                }
                leash_icon {
                    name = "Leash icon"
                    yes_no = core.locale.config.common.yes_no.show_dont_show
                    doc = <<DOC
Display a leash icon for leashed pets.
DOC
                }
                autopick {
                    name = "Autopick"
                    yes_no = core.locale.config.common.yes_no.use_dont_use
                    doc = "Automatically pick up items you pass over."
                }
                autosave {
                    name = "Autosave"
                    yes_no = core.locale.config.common.yes_no.enable_disable
                    doc = <<DOC
Automatically save the game at certain intervals.
These include (but are not limited to):
Using scrolls of create material.
Using potions of gain potential.
Opening chests/material boxes.
DOC
                }
                damage_popup {
                    name = "Damage popup"
                    yes_no = core.locale.config.common.yes_no.on_off
                    doc = "Show damage popups."
                }
                max_damage_popup {
                    name = "Max damage popup"
                    doc = <<DOC
Maximum amount of damage popups to render.
Only has an effect when used with 'Damage popup'.
DOC
                }
                startup_script {
                    doc = <<DOC
Run a script in the data/script/ folder at startup.
Provide a script's name, like 'my_script.lua' for 'data/script/my_script.lua'.
DOC
                }

                pcc_graphic_scale = {
                    name = "PCC Graphic"
                    variants {
                        shrinked = "Shrinked"
                        fullscale = "Full-scale"
                    }
                }

                show_fps {
                    name = "Show FPS"
                    yes_no = core.locale.config.common.yes_no.show_dont_show
                }

                skip_confirm_at_shop {
                    name = "Skip confirm at shop"
                    doc = "Skip confirm to buy or sell items at town shops."
                }

                skip_overcasting_warning {
                    name = "Skip over-casting warning"
                    doc = "Skip warning prompt displayed when you are going to over-cast spells."
                }
            }

            android {
                name = "Android Setting"

                vibrate {
                    name = "Vibrate"
                    doc = <<DOC
Vibrate on important events and low health.
DOC
                }

                vibrate_duration {
                    name = "Vibrate Duration"
                    doc = "Controls the duration of the vibration in 'Vibrate'."
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
                    doc = "Controls transparency of touch actions."
                }

                quick_action_size {
                    name = "Quick Action Size"
                    doc = "Controls size of touch actions."
                }
            }

            keybindings {
                name = "Keybindings"
                doc = "Configure game keybindings."
            }
            mods {
                name = "Mod Settings"
                doc = <<DOC
Settings provided by individual mods.
These can be created by editing the config_def.hcl file in the mod's folder.
DOC
            }
        }
    }
}
