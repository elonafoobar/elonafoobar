local I18N = require("core.I18N")

I18N.add {
   config = {
      common = {
         menu = "Menu",
         require_restart = "Items marked with * require restart to apply changes.",
         assign_button = "To assign a button, move the cursor to\nan item and press the button.",
         no_desc = "(No description available.)",

         yes_no = {
            -- NOTE: This text is implicitly chosen for boolean values without an explicit
            -- "yes_no" option.
            default = {
               yes = "Yes",
               no = "No",
            },

            play_dont_play = {
               yes = "Play",
               no = "Don't play",
            },

            slow_fast = {
               yes = "Yes (Slow)",
               no = "No (Fast)",
            },

            high_low = {
               yes = "High",
               no = "Low",
            },

            show_dont_show = {
               yes = "Show",
               no = "Don't show",
            },

            use_dont_use = {
               yes = "Use",
               no = "Don't use",
            },

            enable_disable = {
               yes = "Enable",
               no = "Disable",
            },

            on_off = {
               yes = "On",
               no = "Off",
            },

            unsupported = {
               yes = "No(unsupported)",
               no = "No(unsupported)",
            },
         },

         formatter = {
            wait = "{$1} wait",
            every_minutes = "Every {$1} min.",
         },
      },

      menu = {
         name = "Option",

         game = {
            name = "Game Setting",
            extra_help = {
               name = "Extra Help",
               doc = "Show extra help popups for new players.",
            },
            attack_neutral_npcs = {
               name = "Attack Netural NPCs",
               doc = "Attack non-hostile, non-ally NPCs when running into them.",
            },
            default_save = {
               name = "Default Save",
               doc = [=[
Saved game to be loaded on startup.
These are calculated when the game loads.
If one is missing, restart the game to have it appear.
]=],
               enum = {
                  [""] = "None",
               },
            },
            story = {
               name = "Enable Cutscenes",
               doc = "Enable playback of the story cutscenes.",
            },
            hide_autoidentify = {
               name = "Hide Auto-Identify",
               doc = "Hide identify status updates from Sense Quality.",
            },
            hide_shop_updates = {
               name = "Hide Shop Updates",
               doc = "Hide daily shop reports of items sold for shops you own.",
            },
         },

         screen = {
            name = "Screen & Sound",
            sound = {
               name = "Sound*",
               yes_no = "core.config.common.yes_no.on_off",
               doc = "Enable or disable sound.",
            },
            sound_volume = {
               name = "Sound Volume*",
               doc = "Set sound volume. It affects all sounds.",
            },
            music = {
               name = "Music*",
               yes_no = "core.config.common.yes_no.on_off",
               doc = "Enable or disable music.",
            },
            music_volume = {
               name = "Music Volume*",
               doc = "Set music volume. It affects all musics.",
            },
            stereo_sound = {
               name = "Stereo Sound",
               doc = [=[
Whether or not to play certain sounds based on the position of the source.
Examples are magic casting, eating/drinking, and damage.
]=],
            },
            fullscreen = {
               name = "Screen Mode*",
               enum = {
                  windowed = "Window mode",
                  fullscreen = "Full screen",
                  desktop_fullscreen = "Desktop fullscr",
               },
               doc = [=[
Fullscreen mode.
'Full screen' will use a hardware fullscreen mode.
'Desktop fullscr' will create a borderless window the same size as the screen.
]=],
            },
            display_mode = {
               name = "Screen Resolution*",
               doc = [=[
Screen resolution to use.
The available options may change depending on the graphics hardware you use.
]=],
               -- "enum" are injected at runtime.
            },
            high_quality_shadows = {
               name = "Shadow Quality",
               doc = "Render shadows at higher quality.",
               yes_no = "core.config.common.yes_no.high_low",
            },
            object_shadows = {
               name = "Object Shadow",
               doc = "Display shadows under items on the ground.",
               yes_no = "core.config.common.yes_no.slow_fast",
            },
            heartbeat = {
               name = "Heartbeat Sound",
               doc = [=[
Play heartbeat sound when health is low.
The threshold to play at is configurable.
]=],
            },
            heartbeat_threshold = {
               name = "Heartbeat Threshold",
               doc = "% of HP remaining to play heartbeat sound at.",
            },
            skip_random_event_popups = {
               name = "Skip Random Events",
               doc = [=[
Skip displaying random event popup windows.
Random events will still occur. In most cases, a default option will be chosen.
]=],
            },
         },

         net = {
            name = "Network Setting",
            is_enabled = {
               name = "Use Network",
               doc = [=[
Enable or disable network-related features.
The following options are available only if the option is set to Yes.
]=],
            },
            chat = {
               name = "Chat Log",
               enum = {
                  disabled = "Disable",
                  receive = "Only receive",
                  send_receive = "Send & receive",
               },
            },
            death = {
               name = "Death Log",
               enum = {
                  disabled = "Disable",
                  receive = "Only receive",
                  send_receive = "Send & receive",
               },
            },
            wish = {
               name = "Wish Log",
               enum = {
                  disabled = "Disable",
                  receive = "Only receive",
                  send_receive = "Send & receive",
               },
            },
            news = {
               name = "Palmia Times",
               enum = {
                  disabled = "Disable",
                  receive = "Only receive",
                  send_receive = "Send & receive",
               },
            },
            is_alias_vote_enabled = {
               name = "Alias Vote",
               yes_no = "core.config.common.yes_no.enable_disable",
            },
            hide_your_name = {
               name = "Hide Your Name",
               doc = [=[
If you set the option Yes, your character's name is replaced with a random name
when sending chat, death or wish log.
When you register your name, the converted one is used, too.
]=],
            },
            hide_your_alias = {
               name = "Hide Your Alias",
               doc = [=[
If you set the option Yes, your character's alias is replaced with a random alias
when sending chat, death or wish log.
When you register your alias, the converted one is used, too.
]=],
            },
            chat_receive_interval = {
               name = "Chat Interval",
               formatter = "core.config.common.formatter.every_minutes",
               doc = [=[
Set the interval between receiving chat, death wish and news log.
]=],
            },
         },

         anime = {
            name = "Animation Setting",
            scroll = {
               name = "Smooth Scroll",
               doc = "Enable scrolling animations.",
            },
            always_center = {
               name = "Always Center",
               doc = "Always keep the center of the screen near the player when walking near the edge of the screen.",
            },
            scroll_when_run = {
               name = "Scroll When Run",
               doc = [=[
Show scrolling animations when running.
Turning this off can speed up running somewhat.
]=],
            },
            general_wait = {
               name = "General Wait",
               formatter = "core.config.common.formatter.wait",
               doc = [=[
Number of frames to wait for most animations/actions.
For example, it controls the amount of delay for input polling.
]=],
            },
            anime_wait = {
               name = "Animation Wait",
               formatter = "core.config.common.formatter.wait",
               doc = [=[
Number of frames to wait for animations.
This also acts as multiplier for the speed of auto-turn actions.
]=],
            },
            alert_wait = {
               name = "Alert Wait",
               doc = [=[
Number of frames to wait if an important message is received.
These are: leveling up, leveling up a skill, or having a change in hunger status.
]=],
            },
            auto_turn_speed = {
               name = "Auto Turn Speed",
               enum = {
                  normal = "Normal",
                  high = "High",
                  highest = "Highest",
               },
               doc = [=[
Speed of auto-turn actions.
This is also affected by 'Animation Wait'.
]=],
            },
            attack_anime = {
               name = "Attack Animation",
               doc = "Play animations when melee/ranged attacking.",
            },
            weather_effect = {
               name = "Weather Effect",
               doc = "Play weather-related animations.",
            },
            title_effect = {
               name = "Title Water Effect",
               yes_no = "core.config.common.yes_no.on_off",
               doc = [=[
Play animations at the title screen.
]=],
            },
            window_anime = {
               name = "Window Animation",
               doc = "Play window animations for certain character-related menus.",
            },
            screen_refresh = {
               name = "Screen Refresh",
               formatter = "core.config.common.formatter.wait",
               doc = [=[
Number of frames to wait between updates to animations in the screen, like rain/lighting.
This does not affect key delay or animations that block input.
]=],
            },
         },

         input = {
            name = "Input Setting",
            autodisable_numlock = {
               name = "Auto-Disable Numlock",
               doc = [=[
If Numlock is on, turns off Numlock while playing and turns it back on again after exiting.
It can fix issues related to holding Shift and a numpad movement key at the same time.
This only has an effect on Windows.
]=],
            },
            walk_wait = {
               name = "Walk Speed",
               doc = "Number of frames to wait between movement commands when walking.",
               formatter = "core.config.common.formatter.wait",
            },
            run_wait = {
               name = "Run Speed",
               doc = "Number of frames to wait between movement commands when running.",
               formatter = "core.config.common.formatter.wait",
            },
            start_run_wait = {
               name = "Run Start Wait",
               doc = "Number of movement commands to play when walking before starting to run.",
               formatter = "After {add($1, 1)} steps",
            },
            attack_wait = {
               name = "Attack Interval",
               doc = "Number of frames to wait between consecutive attacks when running into enemies.",
               formatter = "core.config.common.formatter.wait",
            },
            key_wait = {
               name = "Key Wait",
               doc = "Number of frames to wait between presses of shortcut keys.",
               formatter = "core.config.common.formatter.wait",
            },
            initial_key_repeat_wait = {
               name = "Initial key repeat wait",
               doc = "Number of frames to wait between the first action and the second.",
               formatter = "core.config.common.formatter.wait",
            },
            key_repeat_wait = {
               name = "Key repeat wait",
               doc = "Number of frames to wait between any actions.",
               formatter = "core.config.common.formatter.wait",
            },
            select_wait = {
               name = "Select Wait",
               doc = "Number of frames to wait between item selection initially.",
               formatter = "core.config.common.formatter.wait",
            },
            select_fast_start_wait = {
               name = "Select Fast Start Wait",
               doc = "Number of selections to wait before selecting quickly.",
               formatter = "core.config.common.formatter.wait",
            },
            select_fast_wait = {
               name = "Select Fast Wait",
               doc = "Number of frames to wait between item selection when selecting quickly.",
               formatter = "core.config.common.formatter.wait",
            },
            joypad = {
               name = "Game Pad",
               yes_no = "core.config.common.yes_no.unsupported", -- core.config.common.yes_no.use_dont_use
               doc = [=[
Enable gamepads.
Currently unimplemented.
]=],
            },
         },

         font = {
            name = "Font Setting",
            doc = [=[
Font-related settings.
Place fonts (TTF format) in data/font. Please ensure the fonts are monospaced to avoid issues.
]=],
            vertical_offset = {
               name = "Vertical Offset",
               doc = [=[
Vertical text offset for certain menu titles.
]=],
            },
            size_adjustment = {
               name = "Size Adjustment",
               doc = [=[
Size adjustment for certain pieces of text.
]=],
            },
            quality = {
               name = "Rendering Quality",
               doc = [=[
Text rendering quality. High is beautiful, but slow. Low is cheap, but fast.
]=],
               enum = {
                  low = "Low",
                  high = "High",
               },
            },
         },

         message = {
            name = "Message & Log",
            add_timestamps = {
               name = "Add time info",
               doc = [=[
Add a turn timestamp to each message received.
]=],
            },
            transparency = {
               name = "Transparency",
               doc = "Controls the amount of transparency older message log messages receive.",
               formatter = "{$1}*10 %", -- TODO
            },
         },

         balance = {
            name = "Game Balance Setting",
            doc = "These settings affect game balance.",
            restock_interval = {
               name = "Restock Interval",
               formatter = "{$1} day{s($1)}", -- TODO
               doc = [=[
Interval in days it takes shops to restock items.
If 0, the item selection will change each time you interact with a shopkeeper.
]=],
            },
            extra_race = {
               name = "Extra Race",
               doc = "Enable extra races in character creation.",
            },
            extra_class = {
               name = "Extra Class",
               doc = "Enable extra classes in character creation.",
            },
         },

         language = {
            name = "Language",

            language = {
               name = "Language*",
               enum = {
                  ja = "Japanese",
                  en = "English",
               },
            },
         },

         foobar = {
            name = "Ex setting(foobar)",
            doc = "Extra config settings added in Elona foobar.",

            hp_bar_position = {
               name = "Pets' HP bar",
               enum = {
                  hide = "Don't show",
                  left = "Show left side",
                  right = "Show right side",
               },
            },
            allow_enhanced_skill_tracking = {
               name = "Allow enhanced skill tracking",
               doc = [=[
Increases the number of trackable skills to 10 and colorizes potential.
]=],
            },
            enhanced_skill_tracking_lowerbound = {
               name = "Enhanced tracking lowerbound",
               doc = [=[
Potential below this amount will be colored red in the skill tracker.
Only has an effect when used with 'Allow enhanced skill tracking'.
]=],
            },
            enhanced_skill_tracking_upperbound = {
               name = "Enhanced tracking upperbound",
               doc = [=[
Potential above this amount will be colored green in the skill tracker.
Only has an effect when used with 'Allow enhanced skill tracking'.
]=],
            },
            leash_icon = {
               name = "Leash icon",
               yes_no = "core.config.common.yes_no.show_dont_show",
               doc = [=[
Display a leash icon for leashed pets.
]=],
            },
            autopick = {
               name = "Autopick",
               yes_no = "core.config.common.yes_no.use_dont_use",
               doc = "Automatically pick up items you pass over.",
            },
            autosave = {
               name = "Autosave",
               yes_no = "core.config.common.yes_no.enable_disable",
               doc = [=[
Automatically save the game at certain intervals.
These include (but are not limited to):
Using scrolls of create material.
Using potions of gain potential.
Opening chests/material boxes.
]=],
            },
            damage_popup = {
               name = "Damage popup",
               yes_no = "core.config.common.yes_no.on_off",
               doc = "Show damage popups.",
            },
            max_damage_popup = {
               name = "Max damage popup",
               doc = [=[
Maximum amount of damage popups to render.
Only has an effect when used with 'Damage popup'.
]=],
            },
            startup_script = {
               doc = [=[
Run a script in the data/script/ folder at startup.
Provide a script's name, like 'my_script.lua' for 'data/script/my_script.lua'.
]=],
            },

            pcc_graphic_scale = {
               name = "PCC Graphic",
               enum = {
                  shrinked = "Shrinked",
                  fullscale = "Full-scale",
               },
            },

            show_fps = {
               name = "Show FPS",
               yes_no = "core.config.common.yes_no.show_dont_show",
            },

            skip_confirm_at_shop = {
               name = "Skip confirm at shop",
               doc = "Skip confirm to buy or sell items at town shops.",
            },

            skip_overcasting_warning = {
               name = "Skip over-casting warning",
               doc = "Skip warning prompt displayed when you are going to over-cast spells.",
            },

            digital_clock = {
               name = "Digital clock",
               doc = "Replace default clock with a simple 24 hours digital clock.",
            },

            auto_target = {
               name = "Party auto target",
               doc = "Party members will automatically attack enemies that are visible to you.",
            },
         },

         wizard = {
            name = "Wizard Mode Settings",

            no_hp_damage = {
               name = "No HP Damage",
               doc = "You don't receive any HP damage."
            },

            no_mp_damage = {
               name = "No MP Damage",
               doc = "You don't receive any MP damage."
            },

            no_sp_damage = {
               name = "No SP Damage",
               doc = "You don't receive any SP (stamina) damage."
            },

            no_spellstock_cost = {
               name = "No Spellstock Cost",
               doc = "You spend no spellstock."
            },

            no_hungry = {
               name = "No Hungry",
               doc = "You won't get hungry."
            },

            no_sleepy = {
               name = "No Sleepy",
               doc = "You won't get sleepy."
            },

            can_unlock_all_keys = {
               name = "Can Unlock All Keys",
               doc = "You can unlock all keys without failure."
            },

            can_cast_all_spells = {
               name = "Can Cast All Spells",
               doc = "You can cast all spells without failure. (Your success rates to cast spells become 100%.)"
            },

            skip_random_event = {
               name = "Skip Events",
               doc = "All random events every 1 hour are skipped."
            },
         },

         keybindings = {
            name = "Keybindings",
            doc = "Configure game keybindings.",
         },
         mods = {
            name = "Mod Settings",
            doc = [=[
Settings provided by individual mods.
These can be created by editing the config-schema.lua file in the mod's folder.
]=],
         },
      },
   },
}
