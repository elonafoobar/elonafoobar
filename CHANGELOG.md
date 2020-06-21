# Changelog

## [0.7.3] - 2020-06-21

### Fixed

* [vanilla] Fix a position in the log window where this message is displayed: "You want to watch this event again?"
* [vanilla] Fix no-kill win in the arena or the pet arena.
  * In a town arena, you win battle in about 5% even if you didn't kill any monsters. It also happens in a pet arena.
* [vanilla] Fix issue where The Oracle records unexpected items.
  * When you wish "card" or "figure" of someone, unique artifacts the character usually has were recorded in The Oracle. For example, wishing "card mani" or "figure mani" appended "cat's tail" to The Oracle.
* Fix flickering in house design mode.
* Fix player's targeting routine when `core.auto_target` option is on.
* Fix golem's getting dimmed.
* Fix issues (including potential crashes) related to our internal system.
* Fix some routines related to damage by player's spells or rods.
* Fix the number of the items that rogue boss, \<The leopard warrior\> or \<Silvia\> drop.
* Fix typos.


### Added

* Add "Hang" option to `i` nteract menu to hang arbitrary NPCs. It is available only in Wizard mode.
* Improve performance in drawing character chips.
* Make it possible to assign shortcut to use cargo items.
  * You cannot use cargo items in Nefias and some other locations, as you cannot do so before.
* Add information to the save selection menu.
  * When you save an old save data in this version or newer, a new file, `header.json`, will be created. If a save has the file, its information is displayed in the save selection menu.
* Improve character shadow's rendering.
* [mod] Allow mods without `init.lua`.


### Changed

* Change inventory menu of "Steal" a bit.
  * When you try to steal items on the ground, in vanilla and old foobar, player's money is shown in the menu. As it is useless information, hide it since this version.
* Change the naming rule of the save folders.
  * Note that old save folders will not be renamed and you do not have to rename them.
  * As a side-effect, you can choose any name you like without worrying whether the name is already used or not.
* Remove unused parts of `.map` files. This change reduces file size 90% in average.
* Change the internal representation of map items. Due to this, the number of items whih can be stacked at one tile increases from 3 to 4. Also, a bag icon comes to mean "5 or more items stacked here"; 2 bags, "10 or more"; 3 bags, "15 or more"; 4 bags, "20 or more"
* Remove unnecessary save files, `mod_inv*` and `mod_cdata*`.
* [mod] Simplify definition of localization text associated with data instances.
* [mod] Move definition of blending recipe to Lua side.
* [mod] Move definition of god offerings to Lua side.


### Removed

* Remove "Toggle Console" action, which shows or hides the in-game console window.



## [0.7.2] - 2020-05-27

### Fixed

* Fix crash related to internal item management system.
  * It is a workaround: it prevents the crash, but item names in some game messages are replaced with "something". The bug will be fully fixed in the next version.
* Fix issue where a box or chest does not open when you fail to unlock it once and successfully unlock for the second time.
* Fix crash when you try unlocking many times.



## [0.7.1] - 2020-04-12

### Fixed

* Fix adventurer's favorite skill.
* Fix translation errors in blending recipe and more.
* Fix not being able to auto-pick foods.
* Fix that you may lose blending materials even on success.
* Fix text rendering in the log window.
* Fix some of Japanese text being cut in the middle.
* Improve digital clock's look on the top left.
* Fix typos.


### Added

* Add new options to configure sound/music volume (0-8). By default, 8 (maximum).
* Add new console commands.
  * `:wish`
  * `:gain_spell`
  * `:gain_exp`
  * `:gain_fame`


### Changed

* Re-design in-game console feature.


## [0.7.0] - 2020-03-22

The core system of modding has been changed much!


### Fixed

- Fix some sound effects not played.
- Fix drop items from some monsters.
  - Vesda did not drop the gloves.
  - Rich person, noble child and tourist did not drop wallets. Also they dropped more gems than vanilla.
- Re-enable the network feature temporarily disabled in v0.6.1.
- Fix main story text in Japanese.
- Fix mismatch between random item name and its color.


### Added

- Add application icon, atcat (Windows only so far).
- Partially support undo/redo in house design mode.
  - It is an experimental feature. The key bindings may be changed in a future version.
- [mod] Add global Lua functions/libraries available in mods.


### Changed

- [mod] Change the syntax of translation resources.
- [mod] Change the naming convention of Lua enums.
- [mod] Rename `require_relative()` to `require()`.
- [mod] Change the path finding rule of `require()` (old name: `require_relative()`). In v0.6.1, the function takes relative paths from the root directory of the mod. Since the release, it takes relative paths from the file where the caller function is defined.
  - If you want the previous behavior, you can pass paths starting with `/`.
  - Also, the function does not append `.lua` now. You have to specify extensions explicitly.
- [mod] Add entrypoint of translation loading, `i18n.lua` in each locale folder. Files under `locale/<current locale>/` are not automatically loaded.
- [mod] Change `require()` to `ELONA.require()`.
- [mod] Move `game` module to `core` mod.
  - Thus, you need call `ELONA.require("core.Chara")` instead of `require("game.Chara")`.
- [mod] Change the interface of `data`.
  - Rename `data:define_type()` to `data:define_prototype()`.
  - Unify `data:add()` and `data:add_mult()`.
  - Change the signature of `data:add()`. Instead of passing a array of table with `id` property, pass a table indexed by data id.
- [mod] Introduce "api" to define API like Data System.



## [0.6.1] - 2020-02-11

Windows only release


### Fixed

- Temporarily disable network feature on Windows to avoid crash.



## [0.6.0] - 2019-02-01

### Added

- Add digital clock option in "Ex setting (foobar)" seciton.
  - If it is set to "Yes", the clock on the top left is replaced by a simple 24 hours digital clock. It shows hour, minute and second.
  - Default: "No"
- Add party auto target option in "Ex setting (foobar)" section.
  - If it is set to "Yes", your party members (excluding you) will automatically attack enemies that are visible to you.
  - Default: "No"
- [mod] Implement mod list feature to enable or disable mods.
  - Add new file `profile/<current profile>/mods.json` to list mods you want to enable.
  - Add version number to the mod folder's name. E.g., `core-0.2.6`
  - You can edit the file directly, or enable/disable via GUI, "Mod List" menu.
- Show message prompt after creating a new mod from template.
- [mod] Add `Rand.rnd_capped(n)`, a `Rand.rnd`'s variant which returns an integer in `[0, n')` where `n'` is in `min(n, 32768)`.
- [mod] Add `JSON5` module. It has two functions, `JSON5.parse()` and `JSON5.stringify()`.


### Changed

- Migrate some of HCL files to Lua and JSON5.
  - `keybindings.hcl` -> `keybindings.json`
  - `config.hcl` -> `config.json`
  - [mod] `config_def.hcl` of each mod -> `config-schema.lua`
  - [mod] `mod.hcl` of each mod -> `mod.json`
- Limit some of random number's range in order to emulate vanilla's behavior. For example, the amount of money you will gain/lose in a random event is capped as it is in vanilla.
- Improve documentation for developers.
- Improve shadow rendering of player's sight.
- Abolish the upper limit of the number of bone file entries (80 bones, before).
  - The previous bone file (`bone.txt`) is *not* compatible with the new one.
- Change the default key bindings of "Toggle Console" and "Open Console".
  - Toggle Console: `F12`
  - Open Console: `Shift+F12`
  - Previously, `F12` is bound to "Enable Voldemort mode" (Voldemort mode is super wizard mode). In this version, there is no shortcut key for it, but you can run `voldemort` command in the console to enable the mode.
- Make it possible to open debug console in muggle mode (= non-wizard mode).
- Do not set quest-related data in quest target item.
  - With this change, quest items town villeggers have stack with other items.
- [mod] Unify `Config.get_{type}` and `Config.set_{type}`.
  - Use `Config.get()` instead of `Config.get_int()`, `Config.get_bool()` and `Config.get_string()`.
  - Use `Config.set()` instead of `Config.set_int()`, `Config.set_bool()` and `Config.set_string()`.
- Change welcome message shown on game starting.
  - The original one: "Lafrontier presents Elona ver 1.22. Welcome traveler!"
  - Because this variant is neither "Elona ver 1.22" nor developed by "Lafrontier", change the message to "Welcome traveler!"


### Removed

- Delete support of old save (foobar v0.4.x or older)
  - If you have such a save, please update it in v0.5.0 and then upgrade v0.6.0.
- Remove Android OS support. Because of,
  - Far away from mobile-friendly UI,
  - Too small text and too much information for mobile screen, and
  - Performance hit caused by mod feautre.
  - It costs too much to solve all problems above.
  - As Elona foobar is OSS, you can fork it as long as you follow the license if you want Android version still.


### Fixed

- [vanilla] Fix that some game events might cause "time reversal".
  - Some events such as God inside Ehekatl, marriage, reunion with pets are processed in somewhat wield way in vanilla. The most recently triggered event was processed first, but it should be last.
- [vanilla] Fix "duplicate map exit bug".
  - Bug: if you leave a quest map at the exact turn when time is up, you will go to the world map.
- [vanilla] Fix shadow rendering of player's sight. Some shadows did not connect with each other.
- Improve error handling in network connection.
- Fix that Tuwen does not drop anything.
- Fix crash due to DLL error on Windows.
- Fix crash in charamaking race menu.
- Fix that Wizard's Harvest spell is nerfed accidentally.
- Fix map generation algorithm (in the previous version, a shape of room might have differed a bit from vanilla).
- Fix cat sister/younger sister/maid talking different character's dialog.
- Fix rare crash when starting a hunting quest.
- Fix that you cannot run/attack fast.
- Fix that water ripples disappear in very short frames.
- [mod] Fix the manifest file of the mod which is created from a template.
  - The manifest file of the mod created from a template was just a copy of the template mod's. Now, the file is edited after copying with the name you input.
- Fix crash due to dylib error on macOS.
- Fix `*` (asterisk) key (not in numpad) being unbindable in JIS layout keyboard (a keyboard layout most common in Japan).
- Fix typo.



## [0.5.0] - 2019-08-12

### Added

- Support `README.markdown`, `README.txt` and `README` besides `README.md` in mod details menu.
- Add "Mods" menu to the main title menu.
- Experimental: Implement mod template which allows you to create a mod from template. You can try it through "Mods">"Develop" menu.
- Add new options to control key repeat.
  - `initial_key_repeat_wait`: Number of frames to wait between the first action and the second.
  - `key_repeat_wait`: Number of frames to wait between each action.
- Improve performance on change appearance menu. PCC images are loaded only if you change something.
- Improve change appearance menu: show 4 directions at once.
- Sort mods by name in mod config menu.
- Expand mod config if the mod has only one config section.
- Restore vanilla's chat and vote feature.
  - Add relevant options to configure what you want to send and receive.
- Experimental: Implement Plamia Times, advanced game play log.
- Experimental: Support mouse partially.
- Improve item name's plural rule in English.
- Check system-reserved path when foobar internally creates new file or folder.
- Experimental: Implement screenshot feature. You can take a screenshot via `Print Screen` (the key can be changed). Screenshots are saved in `profile/[current profile]/screenshot` folder.
  - For now, you can take a screenshot only when the player character can act.
- [mod] Add Lua API: `Wish` module. It allows you to add custom wish.
- [mod] Add Lua API: `Data` module to retrieve arbitrary data defined in `data.lua`.
- [mod] Support `data-update.lua` to modify existing data definition from mods.
- [mod] Don't save "volatile" data in store object. Top level fields of store starting  with `_` are considered as "volatile" and skipped on saving.
- [mod] Expand `<LANGUAGE>` in path string to the current language ID.
- [mod] Add `step` property to integer config options. The option which has the property is incremented/decremented by the amount of `step`.


### Changed

- Change random number generator from mt19937 to xoshiro256, an xorshift variant.
- Make random number generation deterministic in some degree.
- [mod] Rename some data IDs.
- [mod] Remove `locale` from locale resource IDs.
- [mod] Remove `exports:` prefix from exported function IDs.
- [mod] Change notation to refer to other mod's directory: `__mod_name_here__` to `<mod_name_here>`
  - [mod] Also change `BUILTIN` to `_builtin_`, a special pseudo-mod to refer to executable path.
- [mod] Change `Store` object to `mod.store`.
- [mod] Change how to export modules. See `mod/core/init.lua`.
- [mod] Change `Elona.require()` to `require()` and `require()` to `require_relative()`. See `core` mod for details.


### Removed

- Delete `gdatan.s1`, unused save file.
- Roll back some foobar's features.
  - Delete strange fish. They are replaced by whale.
  - Remove card collection feature.
  - Turn off some of newly-added options by default. You can manually enable them again.
    - `hp_bar_position`: right -> hide
    - `allow_enhanced_skill_tracking`: on -> off
    - `leash_icon`: on -> off
    - `autopick`: on -> off
    - `damage_popup`: on -> off
    - `restore_interval`: 3 -> 7


### Fixed

- [vanilla] Fix wield behavior when you present gift.
  - When you give present to NPC or to ally, your burden state won't be refreshed.
  - When you give present to NPC, the game turn does not pass unlike other items.
  - When you give present to ally, you cannot give other items continuously.
  - After you give present to ally, `x`, opening inventory menu most recently used, shows the ally's `G`ive menu.
- [vanilla] Fix wield message log "You see ." in global map.
- [vanilla] Fix that you cannot go back from detail submenu to change appearance menu by pressing ESC.
- [vanilla] Fix stack height and offset Y of simple rack's item chip.
- [vanilla] Fix one Easter Egg not working.
- [vanilla] Fix that Moyer says his line even if he is dead.
- Fix text color of damage popup of atomic bomb.
- Fix that you cannot close change appearance equipment menu by Enter key.
- Fix keyhint in `F`eat menu, which does not reflect keybinding settings.
- Fix crash on pressing F11.
- Fix PC's birth year. Newly created player character in v0.4.3 ages a lot.
- Fix main menu crash when unavailable menu item is selected.
- Fix some system messages not shown.
- Fix that Tuwen does not drop anything.
- Fix typos.


## [0.4.3] - 2019-05-31

### Added

- Don't autosave when NPC drinks potion of potential.
- Add Lock Picking skill to developer class.


### Fixed

- [vanilla] Fix that stacked wells dried out at the same time.
- Fix that you failed to search material spot if there are growing plants around you.
- Fix Poppy did not appear in puppy's cave 4th.
- Fix failure to launch foobar on Windows.
- Fix `core.all_mods_loaded` event not being fired.
- Fix a strange random nefia at (27, 47) in North Tyris.
  - Its tile set was wrong, the deepest level was the first floor, and also it won't disappear even after diastrophism.
  - The nefia will be removed when you update the old save data. NOTE: exit the nefia before updating foobar.
- Fix several text errors.



## [0.4.2] - 2019-05-24

### Added

- Make output of in-game console human-friendly.
- Implement water ripple effect in the title menu. Also make `title_effect` option available, which had no effect before.


### Fixed

- [vanilla] Change the time when the story begins: 01:10 -> 16:10
  - See [these tweet](https://twitter.com/ki_foobar/status/1105046955556724736) for details (in Japanese).
- Fix weather effect's glitch.
- Fix glitch of rendering of casino cards.
- Fix Stersha's portrait in the save updated from v0.3.3.
- Fix the bug that ghost monster ball (you can see, but cannot pick it up) appeared on throwing the ball.
- Fix error when you canceled a dialog window by pressing `Shift` or `ESC`.
- Fix failure to update the save from v0.4.0. The bug could break the save completely.
- Replace item `kiroku.counter` with gold pieces. `kiroku.counter` is a mod item defined by `kiroku` mod, one of the sample mods. `kiroku` was deleted in v0.4.0, which caused undefined item error.
- Fix snow field map not generated even if you enter field map from snow title.



## [0.4.1] - 2019-05-19

### Fixed

- Update old save files (`shop*.s2`). It often crashed Elona when you open any containers.
- Show loading screen which was implemented but not shown.
  - You cast Resurrection. Putit has been resurrected!



## [0.4.0] - 2019-05-18

### Added

- Add Lua module, `Env`, to get information about the environment.
- Add loading screen. (putit is rolling and rolling.)
- Add `README-en.txt` and `README-ja.txt`, the READMEs for players.
- Implement profile feature.
  - Add `profile` folder.
  - Move the save folder to `profile/<profile name>/save` to make it possible to separate save folders for each profile.
  - Mvoe the configuration file to `profile/<profile name>/config.hcl` to allow you to customize options for each profile.
- Implement asset system to allow mods to change the location of asset files.
- Add ability to create own configurations for mods.
- Implement dialog system based on Lua scripting. Almost all of the unique dialogs have already been replaced with the new system.
- Introduce version-based mod dependencies.
- Add Lua's `coroutine` library for modding.
- Implement in-game key macro and add related APIs.
- Implement vanilla-like console. Execute `help` command or its alias `?` to see the available commands.
- Add map generation system in Lua. Now, the Poppy Cave is generated by Lua-based generator.
- Save mod's data to the save It introduces several new save files:
  - `mod.s1`: global
  - `mod_cdata.s1`: global, references to characters
  - `mod_inv.s1`: global, references to items
  - `mod_map_<xxx>.s2`: map local
  - `mod_cdata_<xxx>.s2`: map local, references to characters
  - `mod_inv_<xxx>.s2`: map local, references to items
- Show "maintains XX" and "negates the effect of XX" enchantments in item list menus.
  - You can switch the mode via `z` in the same way to toggle resistance's visibility.
  - None -> Resistances -> Maintenance and status ailments -> None -> ...
- Add mod list menu to the main title menu. You can only see the installed mods so far.
- Improve performance of text rendering with shadow.


### Changed

- Reverse the displayed order of heirloom ranking. 1st comes first, 10th, last.
- Change "View Homepage" in main menu to "About". This menu contains the following submenu:
  - Vanilla Elona Homepage
  - Elona foobar Homepage
  - Elona foobar Changelog
  - License
  - Credits
- Change `music` option from string to boolean because there is no difference between `mci` and `direct_music` backends.
- Change the log format: `Elapsed Time LEVEL [tag] Message`.
- Remove `log.txt` and add `log` folder. The folder holds up to 10 recent log files. `0.log` is the latest and `9.log` is the oldest.
- Move map tile data to Lua.
- Make event callbacks in Lua scripting take a single table instead of arguments for future extension.


### Removed

- Remove unused map files in game.
- Delete some config options. They have no (less) effect, or are rarely set.
  - `ui.msg_line`
  - `ui.tile_size`
  - `ui.font_size`
  - `ui.inv_ver_type`
  - `ui.window_x`
  - `ui.window_y`
  - `ui.clock_x`
  - `ui.clock_w`
  - `ui.clock_h`
- Remove unused Lua scripts under `data/script` folder.
- Remove support of `musiclist.txt` completely. The feature will be substituted by mods.
- Delete `original` folder. You need no longer copy `original` folder from vanilla.


### Fixed

- [vanilla] Fix being unable to run in a certain configuration: scoll = Yes / scroll when running = No / running wait = 3 wait
- [vanilla] Fix `{sex}` tag being always substituted by "boy" regardless your PC's sex.
- [vanilla] Align resistance's text vertically in item list menus even if the font is propotional.
- [vanilla] Fix flickering when you move your cursor to the top left tile in house designing.
- [vanilla] Fix strange subcategories of 3 items.
  - Strawberry: others -> fruits
  - Hero cheese: fruits -> others
  - Rabbit tail: fruits -> others
- Add missing key help in housing: `Ctrl` + `Left Click` to fill tiles, imported from omake.
- Fix default key mappings of `x` and `X`. Now, `x` shows the inventory menu the most recently used, and `X` always shows the "Examine" menu as vanilla does.
- Fix \*win\* comment you selected not being shown in the \*win\* window.
- Fix the broken link to the vanilla Elona's homepage. It has been updated to http//ylvania.org.
- Fix lack of Git commit hash in the log on Windows.
- Fix crash when you Return if there are some random nefias in the current continent.
- Fix that Elona foobar APIs were not available in the in-game console.
- Fix quick menu not shining.
- Fix glitch of crossbow animation. Bullet image was wrongly used before, and now arrow animation is played.
- Fix message text's color in TCG.
- Fix game help text blurred.
- Fix that bug: When you try to Return on escort quest, the confirmation prompt appears: "It is prohibited. Are you sure?" If you choose "Yes", Return should be performed. However, in fact, if you said "Yes", Return was canceled, and if you answered "No", you would Return.
- Fix `x` key in feat menu not working.
- Fix that visibility of resistances was not shared between the inventory menu and the equipment menu.
- Fix mojibake in error messages if a filepath contains multibyte characters.
- Fix that prompt did not clear key repeating state.
- Fix typos.



## [0.3.3] - 2019-01-12

### Fixed

- Fix skill's and resistance's bonuses in character sheet being wrongly displayed.
- Fix not being able to blend more than one items at once regardless of your input number.
- Fix some of text colors.
- Fix crash on recruiting an ally under certain conditions.



## [0.3.2] - 2019-01-06

### Added

- Enhance autopick feature. These new features are almost omake-compatible.
  - Support category-based selector.
  - Support item modifiers.


### Changed

- Now, action "Enter" and action "Auto action" are unified.
- In autopick, use sound IDs instead of filename.
  - E.g., old: `atk_chaos.wav` new: `core.atk_chaos`
  - They are defined in `mods\core\data\sound.lua` in this version.


### Fixed

- [vanilla] Fix 3 continent border maps being regarded as indoor.
- Fix the previous data of item appearance of map remaining before and after Noyel Festival.
- Fix upstairs and downstairs position being saved reversely.
- Fix different item name being displayed after trading items for "I want it!" quest.
- Fix number input by +100/-100 via northwest/northeast key not working.
- Add missing map data for player-owned buildings. It caused a crash on Returning.
- Fix diagonal movement being bound to wrong keys.
- Restore an Easter egg command in vanilla which was unavailable in the previous version.
- Fix key to open portrait menu in character sheet, `p`, conflicts with the 16th menu selection key.
- Fix 1 page scrolling in log window skipping the top or bottom line.
- Fix crash when you try to remove debuffs (hexes) you have. E.g., spell of Holy Light, scroll of vanquish hex, etc.
- Fix typo.



## [0.3.1] - 2018-12-17

### Fixed

- Fix crash on launching.
- Fix crash if Elona foobar is placed in a folder which contains non-ASCII characters.



## [0.3.0] - 2018-12-15

### Added

- Add new shortcut key, `Ctrl+Tab`, to move to the previous (left) menu.
- Make possible to reload autopick definition file via `Shift+Backspace`.
- Prevent precious ally from being destroyed by gene machine. You can regard an ally as precious by using stethoscope to him/her.
- Implement keybinding. You can customize them through the keybinding menu in the bottom of the option menu.
- Add option to show the current FPS, frame per second (default: disable).
- Reimplement console by using lua. You can run any lua snippet in the console.
- Externalize data of character loots.
- Improve blackjack drawing.
  - Draw character image in full-scale.
  - Show each card's suit.
  - Render card's rank as image.
- Port English translation of the main scenario's cutscenes from E+C.
- Externalize almost all of map definition data.
- Externalize data of sold goods in town shops.
- Add option to skip prompt to confirm selling/buying items in town shops (default: disable).
- Make message log window scrollable, storing up to 1000 lines. Available shortcut keys are as follows:
  - `Up`: scroll 1 line up (to older)
  - `Down`: scroll 1 line down (to newer)
  - `Left`: scroll 1 page up (to older)
  - `Right`: scroll 1 page down (to newer)
- Give "yeek" (boss) to his own name, "\<Rodlob\> the boss of yeeks".
  - The name is the reverse spelling of "Boldor", the Angband monster, as his Japanese name is.
- Improve shadow graphics.
- Add option to enable text antialiasing (default: enabled). Also change the bundled font from KochiGothic to GenShinGochic to make text rendering more beautiful when antialiasing is on.
- Add option to skip overcast warning prompt (default: disable).
- Check whether the save data you are trying to load now is compatible or not, and report error if the running Elona foobar is not able to load the save.
- Load each mod in proper order using dependencies.
- Improve portrait system. Now, you can choose portraits prepared for different gender, and portraits for NPCs.
- Add application icon of putit to `Elona_foobar.exe` for Windows


### Changed

- Do not query direction on using dresser if there are no allies around you.
- Insert linebreak before message of changing ammo.
- Show adventurers name in news.
- Change the order of messages when you eat raw equipments.


### Fixed

- [vanilla] Do not show message "something falls down" if the item is on the ground.
- [vanilla] Fix aspect ratio of PCC in change appearance menu.
- [vanilla] Fix item chip of double bed and happy bed being cut off.
- [vanilla] Remove garbage displayed around selection keys.
- [vanilla] Remove strange spacing in the message log window when the weather changes.
- [vanilla] Fix item chip of chain mail stacking on too high position.
- [vanilla] Fix food not getting rotten sometimes if you believe in Kumiromi.
- [vanilla] Fix the progress of ether disease advancing over the upper limit.
- [vanilla] Replace ellipsis symbols with 3 periods in English text because some English fonts do not have the glyph.
- [vanilla] Move the position of the crypt of the damned in the global map right. The previous one was on the cliff, which was of course invalid, so that the crypt might be placed at different position in each save and rarely "moves" every time diastrophism occurs.
- Fix fading out in cutscenes not working.
- Fix skill tracker's overlap when your skill levels are very high (4 digits).
- Fix item names in crafting menu being colored wrong.
- Fix default music not being loaded correctly.
- Fix random number generator not generating the same result on 3 platforms.
- Prevent `Ctrl+V` key (to paste text from clipboard) in input box from repeating.
- Fix being unable to see IME-translated text in input box on macOS.
- Fix not being able to choose one of your allies correctly in ally selection menu.
- Fix item graphics being replaced with different one sometimes.
- Fix female rogue boss having a black-filled portrait.
- Fix being unable to cancel the talk with whom dwell in the vanity by pressing `Shift` or `ESC`.
- Fix typo.



## [0.2.8] - 2018-09-15

### Added

- Adjust tone of shadow in cutscenes.
- Show current minute zero-filled in log window like this `[05]`.
- Improve save data's portability especially for endianness.
  - Elona foobar always saves data in little endian. If your machine runs in big endian, foobar converts data on loading and saving.


### Removed

- Delete support of old vanilla's save(older than 1.22).
  - We have a plan to provide an importer/exporter in the future.
- Delete support of old foobar's save(v0.2.6 or earlier).
  - Please update your save in v0.2.7 before you load it in v0.2.8(this version).


### Fixed

- [vanilla] Fix shelter stacking when you build it on another shelter.
- [vanilla] Fix glitch of drawing bottom left of small map if the window size is large enough.
- Fix special ammo enchantment not being added.
- Fix living weapon not destroying the last enchantment when the weapon has 15 enchantments and sucks blood.
- Fix water dropped on an alter not getting blessed.
- Fix crashes when an item is burned/broken by fire or cold.
- Fix character's tone changing in one dialog(only in Japanese mode).
- Add a missing key hint to home rank window you can see via house board.
- Fix heirloom ranking listing only the most valuable item.
- Fix black pixels(`#000`) in portraits being transparent.
- Do not play breaking animation if you cannot see there.
- Fix shadow of window in selecting save menu disappearing once you change page.
- Fix being able to unacquirable feats. For example, you were able to acquire Negotiator feat even if you did not have Negotiation skill.
- Fix typos.



## [0.2.7] - 2018-09-05

### Added

- Rename ElonaFoobar to Elona foobar.
- Add many Lua APIs. See also docs/ folder for details.
- Add Android support experimentally.
- Speed up loading save data much.
- Implement vanilla's house design by using a house board.
  - Also implement tile filling via left-click with Ctrl key.
- Enhance damage popup feature.
  - Add an option to change the number of the popups.
  - Show popups when a buff is added/removed.
  - Highlight elemental damages and healing.
- Add option's descriptions in Options menu.
- Support full-scale PCC.
- Enhance skill tracker feature.
  - Increase the amount of the available skill trackers(3->10).
  - Show skill's potentials together.
  - Color high potentials in green and low potentials in red.
- Port English translation from omake EN, omake overhaul EN, and omake overhaul EN hack. Great thanks to Doorknob, the main translator of them.
- Migrate config file from JSON to HCL.
  - Almost all of options get available ingame now. You don't need touch it directly, maybe.
- Add a minute hand to the top left clock.


### Fixed

- [vanilla] Do not keep keys pressed during cards are dealt at casino.
- [vanilla] Fix overflow of gold and platinum.
- [vanilla] Fix crash when you eat an equipment which maintains your luck.
  - Newly add Luck Growth buff to avoid it.
- [vanilla] Fix overflow of harvest quest's reward.
- [vanilla] Fix Y position of recipe window when the Elona window size is other than 800x600.
- Add a missing map name for the player-owned dungeon.
- Fix Enter key repeating too fast sometimes.
- Fix a lot of text errors.
- Fix Lua's require() failing if the current directory is different from the executable path.
- Fix wrong item price shown in log window on selling.
- Fix garbage being shown below the top left clock.
- Fix number input not rotating in a certain case.
- Fix heart mark being drawn in wrong position in Japanese mode.
- Fix glitch of some UI parts in [w]ear menu.
- Fix crashes related to splitting creatures like bubble.
- Update links to CONTRIBUTING.md in READMEs.
- Fix cursed food not being removed after being eaten.
- Fix strange behaviors of damage by fire/cold and fire/coldproof blanket.
  - Fix blanket being separated even when no item is destroyed.
  - Fix messages saying about cold damage being displayed even if you cannot see the incident.
  - Fix fireproof blanket's behavior changing based on your vision.
- Fix not being able to walk diagonally in a certain condition.
- Fix typos, mainly in English.
- Fix being able to change your alias via wishing even if you are in wizard mode.
- Fix your karma changing via wishing even if you are a good citizen.



## [0.2.6] - 2018-06-19

### Added

- Validate and limit integer options.
- Now numpad 5 key works like other numpad keys.
- Implement "autonumlock" in vanilla. (only Windows)
- Implement extra number prompt like omake.
- Adjust key sensitivity of Enter/BackSpace key.
- Implement alias lock like omake.
  - You can lock aliases by `key_mode2`(default: `*`), and locked aliases do not change by rerolling.
- Selected alias is restored when you go back the alias rolling menu.
- Possible to go back the portrait menu at the final character making phase.
- You can now cancel the final name input box in character making.
- Stack goods at shop.
- Add Lua API: `LuaCharacter.experience`.


### Fixed

- Fix some of errors not being displayed.
- Fix README.md and README-jp.md to fit the current state.
- Fix overflow of character level experience.
- Fix being unable to sell/buy in Derphy if you are a criminal.
- Fix glitch of log window if you use the default font bundled in foobar.
- Fix foobar's version not being stored in save data.
- Fix items on the ground getting transparent when opening temporary inventory(5080-5480).
  - Such as blackjack and spell of 4-dimentional pocket.
  - Also fix the transparent items getting duplicate when the map is re-generated.
- Fix corrupted map data due to the above bug.
- Fix crash if foobar is placed in folder which contains non-ascii characters.
  - To avoid this issue, change the naming convention of save file, from `sav_{player name}` to random-generated name like `df04-0b4b-d0cc-a11b`.
- Fix infinite loop in AI routine.
- Fix autopick "to save" mark, `*`, conflicts with part of item name(in Japanese).
  - Change the mark from `*` to `%`.



## [0.2.5] - 2018-06-10

### Added

- Introduce Lua API for experimenting/playtesting.
- Increase rate of potion of cure corruption at casino.
  - Same as omake.
- Improve performance of damage popup.
- Improve key sensitivity.
- Improve shadow rendering.
- Add resolution switching options/fullscreen.
- Add unique portrait for some NPCs.
- Decrease animation wait depending on `animewait` setting.
- Show generation count to deck menu.
- Limit the length of user input text in input dialog.
- Add option to toggle damage popup(`damage_popup`).
- Adjust formula to calculate PC's weight.


### Removed

- Do not copy `original\config.txt`, no longer needed.
- Hide stair position markers in minimap in muggle mode.


### Fixed

- [vanilla] Fix known issues since vanilla in Elona Bugfix wiki.
  - Too many...
- [vanilla] Fix the lords of Chaos Castles not dropping rod of wishing.
- [vanilla] Fix PC dying in main scenario in a certain condition.
- [vanilla] Fix you cannot talk to your pet unique NPC like god's servant.
- [vanilla] Fix infinite loop when entering map filled with doors or walls.
- Fix not being to quit blackjack at casino.
- Fix story scene not being played even if enabled.
- Fix name cutting algorithm in Japanese.
- Fix being unable to run by pressing numpad keys and Shift key.
- Fix numpad Enter not working.
- Fix Enter key not working sometimes.
- Fix being able to wish "fame" even in muggle mode.
- Fix living weapon not gaining enchantments.
- Fix being unable to wish items/skills in wizard mode.
- Fix bone file mojibake in Japanese.
- Validate PC's name more strictly.
- Fix crash in using deck.
- Fix going back from PCC editor in character making, then skipping the editor.
- Fix typo(in Japanese).



## [0.2.4] - 2018-05-20

### Fixed

- Fix save data being gzip-compressed.
- Fix traits not being colored in trait menu.



## [0.2.3] - 2018-05-19

### Added

- You can now change some options in game.
  - Extra Race/Class
  - Animation Wait/Alert Wait
  - Initial Key Wait/Key Wait
- You can change how frequently shopkeepers restock their items.
  - 0-10 days(default: 3 days). If you set 0, sold items are updated every time you talk to the shopkeeper.


### Fixed

- Fix gaining performance experience by bard's performance.
- Fix being unable to read text file in UTF-8 with BOM.
- Fix performance hit by too many damage popups.
  - Limit the maximum number of popups like oomEx.
- Fix remaining of damage popups if you leave map.
- Fix some SEs not being played.
- Fix that BGM is re-played at the beginning sometimes.
- Fix stack overflow when PC is slow and there are many NPCs.
- Fix crash when trying to create PC whose name is invalid as file name/folder name.
  - Invalid name is now converted to valid name automatically.
- Fix infinite loop when inventory is filled with precious items and items are destroyed.
- Fix crash when items are destroyed.
- Fix typo in Japanese.
- Fix crash when opining journal.
- Fix too many blank lines in journal.
- Fix being unable to cancel number input prompt.
- Fix effect of ball/bolt spells not reflecting their element's color.
- Fix going back to stats roll menu resets lock count.
- Fix slow down in the front of quest board.
- Fix mojibake of in-game help in Japanese.
- Fix glitch about your pets' stats at PC's shop.
- Fix being unable to dig walls if your mining skill is low.



## [0.2.2] - 2018-05-05

### Added

- Disable autosave.
  - You can enable autosave again from option menu.
- Update README.md to fit current state.
- Add README-jp.md, Japanese version README.


### Fixed

- [vanilla] Fix not being able to leave the cave if you die in the cave without leaving there.
- Fix default value of `key_close` is "c", same as `key_charainfo`.
- Fix these crashes:
  - Crash when wizard's dream happens during sleeping.
  - Crash when reading uncursed/blessed scrolls of wonder.
  - Crash when hearing adventurer's favorite skill.
  - Crash when trying to train skill from adventurer.
  - Crash when eating the corpse of \<Little Sister\>.
  - Crash when speaking to trainer.
  - Crash when reading scrolls of growth.
  - Crash when reading scrolls of gain attribute.



## [0.2.1] - 2018-05-03

### Added

- Dump error log and some information to runtime/log.txt.


### Removed

- Remove support of vanilla's custom file format.
  - It is temporary. Of course, it will be implemented again.


### Fixed

- [vanilla] Fix employees' vanishing when building your home.
- [vanilla] Fix freeze when failing to create rewards at casino.
- Fix selected text being filled with black.
- Fix some library were not Unicode version.
- Fix some of save data being stored in wrong folder.
- Fix save folder's mojibake.
- Fix crashes if downloaded folder contains non-ASCII character.



## [0.2.0] - 2018-05-01

### Added

- Externalize fish data.
  - Add "strange fish" for testing.
- Implement autodig mode(compatible with oomEx).
- Introduce versioning.
- Store Foobar version in save data.
- Can wish items with cursed state in wizard mode.
  - Please prepend Blessed/Uncursed/Cursed/Doomed to item's name.
- Can delete wishing by [BackSpace] and paste by [Ctrl-V].
- Show pets' HP bars like omake.
- Show leash icon next to pet's HP bar if leashed.
- Detect executable path automatically.
- Improve matching algorithm of wishing.
- Support font style(bold, italic, and underline).
- Define default values of options.
  - You need not prepare long config.json any longer.
- Support number pad(experimental).
- Implement damage popup(experimental).
- Implement autopick(experimental).
- Card collection using deck.


### Removed

- Delete unavailable option, `cfg_msg_box`.
- Remove test NPCs(they are too strong in spite of their low level).
- Disable rendering high quality shadow temporarily.
- Disable Voldemort mode by default.
  - It is available and you can enable it via [F12].


### Fixed

- Fix Ainc drops fruits by bashing.
- Fix crash when wishing skills.
- Fix not being able to uncurse items.
- Fix Foobar quitting when rolling attributes.
- Fix glitch at casino.
- Fix not being able to draw tab character correctly.
- Fix crash when pickpocketing.
- Fix being able to dig long swords from walls.
- Fix non-centered Japanese text during scenario scene.
- Fix glitch of log window in Japanese mode.
- Fix selecting cursor not being rendered.
- Fix not being able to delete save data in game.
- Fix typo in English.



## [0.1.0] - 2018-04-08

### Added

- Introduce Lua.
- Externalize part of data to Lua scripts.
- Externalize part of text to Lua scripts.
- Internationalization.
- Use JSON file for configuration.
- Custom race.
- Custom class.
- Custom NPC.
- Specify number of wished items in wizard mode.
- Do not ask direction to close if there is only one door around you.
- Autodig.
- Highlight positions of upstairs/downstairs.
- Always show HP bars.
- Exchange position pressing Shift key.
- Quick save and quick load.
- Abolish upper limit of number of NPC's actions(10 -> unlimited).
- Minimum attribute roll in character making.


### Removed

- Delete F12 console commands.
- Remove compatibility with too old versions(older than 1.16).


### Fixed

too many...
