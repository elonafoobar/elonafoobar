config {
   section "game", {
      option "extra_help", true,

      option "attack_neutral_npcs", false,

      option "default_save", "",

      option "story", true,
      option "hide_autoidentify", false,
      option "hide_shop_updates", false,
   },

   section "screen", {
      option "sound", true,

      option "sound_volume", {
         default = 8,
         min = 0,
         max = 8,
      },

      option "music", true,

      option "music_volume", {
         default = 8,
         min = 0,
         max = 8,
      },

      option "stereo_sound", true,

      option "fullscreen", {
         enum = {"windowed", "fullscreen", "desktop_fullscreen"},
         default = "windowed",
      },

      option "display_mode", {
         type = "string",
      },

      option "high_quality_shadows", true,
      option "object_shadows", true,
      option "heartbeat", true,

      option "heartbeat_threshold", {
         default = 25,
         min = 1,
         max = 50,
         step = 5,
      },

      option "skip_random_event_popups", false,
   },

   section "net", {
      option "is_enabled", false,
      option "chat", {
         default = "disabled",
         enum = {"disabled", "receive", "send_receive"},
      },
      option "death", {
         default = "disabled",
         enum = {"disabled", "receive", "send_receive"},
      },
      option "wish", {
         default = "disabled",
         enum = {"disabled", "receive", "send_receive"},
      },
      option "news", {
         default = "disabled",
         enum = {"disabled", "receive", "send_receive"},
      },
      option "is_alias_vote_enabled", false,
      option "hide_your_name", false,
      option "hide_your_alias", false,
      option "chat_receive_interval", {
         default = 5,
         min = 1,
         max = 30,
      },
      -- option "language_blacklist", {
      --    type = "array",
      --    default = {},
      --    is_hidden = true,
      -- },
      -- option "word_blacklist", {
      --    type = "array",
      --    default = {},
      --    is_hidden = true,
      -- },
      -- option "player_blacklist", {
      --    type = "array",
      --    default = {},
      --    is_hidden = true,
      -- },
   },

   section "anime", {
      option "scroll", true,
      option "always_center", true,
      option "scroll_when_run", true,

      option "general_wait", {
         default = 30,
         min = 0,
         max = 50,
      },

      option "anime_wait", {
         default = 20,
         min = 0,
         max = 20,
      },

      option "alert_wait", {
         default = 50,
         min = 0,
         max = 50,
      },

      option "auto_turn_speed", {
         default = "normal",
         enum = {"normal", "high", "highest"},
      },

      option "attack_anime", true,
      option "weather_effect", true,
      option "title_effect", true,
      option "window_anime", false,

      option "screen_refresh", {
         default = 3,
         min = 0,
         max = 15,
      },
   },

   section "input", {
      option "autodisable_numlock", true,

      option "walk_wait", {
         default = 5,
         min = 1,
         max = 10,
      },

      option "start_run_wait", {
         default = 2,
         min = 0,
         max = 5,
      },

      option "run_wait", {
         default = 2,
         min = 1,
         max = 10,
      },

      option "attack_wait", {
         default = 4,
         min = 1,
         max = 10,
      },

      option "key_wait", {
         default = 5,
         min = 1,
         max = 10,
      },

      option "initial_key_repeat_wait", {
         default = 5,
         min = 1,
         max = 20,
      },

      option "key_repeat_wait", {
         default = 1,
         min = 1,
         max = 5,
      },

      option "select_wait", {
         default = 10,
         min = 1,
         max = 20,
      },

      option "select_fast_start_wait", {
         default = 2,
         min = 0,
         max = 10,
      },

      option "select_fast_wait", {
         default = 2,
         min = 1,
         max = 20,
      },

      option "joypad", false,
   },

   section "font", {
      option "file", "GenShinGothic/GenShinGothic-Monospace-Regular.ttf",

      option "vertical_offset", {
         default = -1,
         min = -10,
         max = 10,
      },
      option "size_adjustment", {
         default = 1,
         min = -5,
         max = 5,
      },
      option "quality", {
         default = "high",
         enum = {"low", "high"},
      },
   },

   section "message", {
      option "add_timestamps", false,

      option "transparency", {
         default = 4,
         min = 0,
         max = 10,
      },
   },

   section "balance", {
      option "restock_interval", {
         default = 7,
         min = 0,
         max = 10,
      },

      option "extra_race", false,
      option "extra_class", false,
   },

   section "language", {
      option "language", {
         type = "string",
      },
   },

   section "foobar", {
      option "hp_bar_position", {
         default = "hide",
         enum = {"hide", "left", "right"},
      },
      option "allow_enhanced_skill_tracking", false,
      option "enhanced_skill_tracking_lowerbound", {
         default = 50,
         min = 0,
         max = 390,
         step = 10,
      },
      option "enhanced_skill_tracking_upperbound", {
         default = 100,
         min = 10,
         max = 400,
         step = 10,
      },
      option "leash_icon", false,
      option "autopick", false,
      option "autosave", false,
      option "damage_popup", false,
      option "max_damage_popup", {
         default = 100,
         min = 10,
         max = 100,
         step = 10,
      },

      option "startup_script", {
         default = "",
         is_hidden = true,
      },

      option "run_script_in_save", {
         default = false,
         is_hidden = true,
      },

      option "pcc_graphic_scale", {
         default = "shrinked",
         enum = {"shrinked", "fullscale"},
      },

      option "show_fps", false,
      option "skip_confirm_at_shop", false,
      option "skip_overcasting_warning", false,
      option "digital_clock", false,
      option "auto_target", false,
   },

   -- Hidden sections

   section "debug", {
      option "wizard", false,

      is_hidden = true,
   },
}
