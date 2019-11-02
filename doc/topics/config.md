# Mod Configuration
Mods can define config sections, which will appear in the config section of the game. There are two primary locations things that need to be done:

- Add a `config_def.hcl` file to the root directory of the mod.
- Add translations for the config options within the `config` localization namespace.

## Quickstart
To allow your mod to be configurable, add a `config_def.hcl` file to the mod's root directory. The following can be used as a template.

```hcl
config {
   # Defines a config section.
   section = {
       type = "section"

       # Options in this section.
       options = {

           # A config option.
           option = {
               default = 50
               min = 0
               max = 100
           }
       }
   }
}
```

Then, add a corresponding translation file to `locale/en` or `locale/jp`.

```hcl
locale {
    config {
        menu {
            # Mod name
            name = "My Mod"

            section {
                name = "Config Section"

                option {
                    name = "Config Option"
                    doc = "Documentation for this option"
                }
            }
        }
    }
}
```

These two files correspond to each other. When you add config items to `config_def.hcl`, translations for the mod's config will be expected under the `<mod_name>.config` localization namespace.

When you start the game with at least one mod supporting config options, a `Mod Settings` section will appear as the last option in the game's config menu. From there you can configure each individual mod's settings. Test it out with the settings above.

## Config definition format
The following is an example `config_def.hcl` containing all the supported config options.

```hcl
config {
    # Defines a config section. Note that all config options in the top level (inside the root
    # "config" object) must be sections.
    section = {
        type = "section"
        options = {
            # Corresponds to "<mod_name>.section.section_option".
            #
            # Config.get("mymod.section.section_option")
            # Config.set("mymod.section.section_option", false)
            section_option = true
        }
    }

    option_types = {
        type = "section"
        options = {
            # Boolean options can be declared as bare values. The value given is the default.
            skip_random_events = true

            # Options can be given an object instead of a value to configure more details about the
            # option, like minimum/maximum value.
            story = {
                default = true
            }

            # If preload is true, load the option before the game window has been initialized. Can
            # usually be ignored.
            music = {
                default = true
                preload = true
            }

            # Integer values must be given a minimum/maximum value.
            heartbeat_threshold {
                default = 25
                min = 1
                max = 50
            }

            # "Enums" allow selecting a string value from a list of values. They each have an
            # individual localized string.
            fullscreen = {
                type = "enum"
                variants = ["windowed", "fullscreen", "desktop_fullscreen"]
                default = "windowed"
            }

            # If the enum value should not be localized, set "translate_variants" to false. The
            # enum string itself will be the displayed value.
            window_modes = {
                type = "enum"
                variants = ["800x600", "1024x768", "1600x1200"]
                default = "800x600"
                translate_variants = false
            }

            # "platform" specifies valid platforms for this option. Only used internally, so it can
            # be ignored. Valid values are "desktop", "android" or "all".
            display_mode = {
                platform = "android"
                type = "enum"
                variants = ["landscape", "portrait"]
                default = "landscape"
            }

            # "platform_default" specifies a different default to use on the given platform. Valid
            # values are "desktop", "android" or "all.
            scroll = {
                default = true

                platform_default {
                    android = false
                }
            }
        }
    }
}
```

## Translation format
The following is a translation file which corresponds to the `config_def.hcl` in the previous section.

```hcl
locale {
    config {
        menu {
            name = "Example Config"

            section {
                name = "Section"

                section_option {
                    name = "Section Option"

                    # Documentation is optional for all config options.
                    doc = "An option nested in a section."
                }
            }
            option_types {
                name = "Option Types"

                skip_random_events {
                    name = "Skip Random Events"

                    # Strings in HCL can use "Heredoc" format, which allows writing multiline
                    # strings.
                    doc = <<DOC
Skip displaying random event popup windows.
Random events will still occur. In most cases, a default option will be chosen.
DOC
                }

                story {
                    name = "Enable Cutscenes"
                }

                music {
                    name = "Music"
                }

                heartbeat_threshold {
                    name = "Heartbeat Threshold"
                }

                fullscreen {
                    name = "Screen Mode*"

                    # Enum variants each get their own translations, unless "translate_variants" is
                    # set to false.
                    variants {
                        windowed = "Window mode"
                        fullscreen = "Full screen"
                        desktop_fullscreen = "Desktop fullscr"
                    }
                }

                window_modes {
                    name = "Screen Resolution*"
                }

                display_mode {
                    name = "Screen Orientation"
                    variants {
                        landscape = "Landscape"
                        portrait = "Portrait"
                    }
                }

                scroll {
                    name = "Smooth Scroll"

                    # You can change which translation is used for "yes/no" options. It should have
                    # this format:
                    #
                    # on_off {
                    #     yes = "On"
                    #     no = "Off"
                    # }
                    yes_no = core.config.common.yes_no.on_off
                }
            }
        }
    }
}
```

## Using Config Options
To access and change config options from mods, use the [Config](../modules/Config.html) API.
```lua
local Config = require("game.Config")

print(Config.get("core.game.extra_help"))
print(Config.set("core.balance.restock_interval", 10))
Config.save()
```

Note that the `Config` API will raise an error if the config option doesn't exist or the type differs.
