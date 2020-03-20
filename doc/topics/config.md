# Mod Configuration

Mods can define config sections, which will appear in the config section of the game. There are two primary locations things that need to be done:

- Add a `config-schema.lua` file to the root directory of the mod.
- Add translations for the config options within the `config` localization namespace.


## Quickstart

To allow your mod to be configurable, add a `config-schema.lua` file to the mod's root directory. The following can be used as a template.

```lua
config {
   -- Defines a config section.
   section "section_name", {
      -- Options in this section.
      option "option_name", {
         default = 50,
         min = 0,
         max = 100,
      }
   }
}
```

Then, add a corresponding translation file to `locale/en` or `locale/jp`.

```lua
ELONA.i18n:add {
   config = {
      menu = {
         -- Mod name
         name = "My Mod",

         section_name = {
            name = "Config Section",

            option_name = {
               name = "Config Option",
               doc = "Documentation for this option",
            }
         }
      }
   }
}
```

These two files correspond to each other. When you add config items to `config-schema.lua`, translations for the mod's config will be expected under the `<mod_name>.config` localization namespace.

When you start the game with at least one mod supporting config options, a `Mod Settings` section will appear as the last option in the game's config menu. From there you can configure each individual mod's settings. Test it out with the settings above.


## Config definition format

The following is an example `config-schema.lua` containing all the supported config options.

```lua
config {
   -- Defines a config section. Note that all config options in the top level (inside the root
   -- "config" object) must be sections.
   section "section", {
      -- Corresponds to "<mod_name>.section.section_option".
      -- Config.get("mymod.section.section_option")
      -- Config.set("mymod.section.section_option", false)
      option "section_option", true
   },

   section "option_types", {
      -- Boolean options can be declared as bare values. The value given is the default.
      option "skip_random_events", true,

      -- Options can be given an object instead of a value to configure more details about the
      -- option, like minimum/maximum value.
      option "story", {
         default = true
      },

      -- Integer values must be given a minimum/maximum value.
      option "heartbeat_threshold", {
         default = 25,
         min = 1,
         max = 50,
      },

      -- "Enums" allow selecting a string value from a list of values. They each have an
      -- individual localized string.
      option "fullscreen", {
         type = "string",
         enum = ["windowed", "fullscreen", "desktop_fullscreen"],
         default = "windowed",
      },
   }
}
```


## Translation format

The following is a translation file which corresponds to the `config-schema.lua` in the previous section.


```lua
ELONA.i18n:add {
   config = {
      menu = {
         name = "Example Config",

         section = {
            name = "Section",

            section_option = {
               name = "Section Option",

               -- Documentation is optional for all config options.
               doc = "An option nested in a section.",
            },
         },
         option_types = {
            name = "Option Types",

            skip_random_events = {
               name = "Skip Random Events",

               -- Strings in Lua can use "Heredoc" format, which allows writing multiline
               -- strings.
               doc = [[Skip displaying random event popup windows.
Random events will still occur. In most cases, a default option will be chosen.]],
            },

            story = {
               name = "Enable Cutscenes",
            },

            music = {
               name = "Music",
            },

            heartbeat_threshold = {
               name = "Heartbeat Threshold",
            },

            fullscreen = {
               name = "Screen Mode*",

               enum = {
                  windowed = "Window mode",
                  fullscreen = "Full screen",
                  desktop_fullscreen = "Desktop fullscr",
               }
            },

            window_modes = {
               name = "Screen Resolution*",
            },

            display_mode = {
               name = "Screen Orientation",
               enum = {
                  landscape = "Landscape",
                  portrait = "Portrait",
               }
            },

            scroll = {
               name = "Smooth Scroll",

               -- You can change which translation is used for "yes/no" options. It should have
               -- this format:
               on_off {
                  yes = "On",
                  no = "Off",
               },
               yes_no = "core.config.common.yes_no.on_off",
            },
         }
      }
   }
}
```

## Using Config Options

To access and change config options from mods, use the [Config](../modules/Config.html) API.

```lua
local Config = ELONA.require("core.Config")

print(Config.get("core.game.extra_help"))
print(Config.set("core.balance.restock_interval", 10))
Config.save()
```
