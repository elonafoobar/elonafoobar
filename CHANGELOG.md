# Changelog



## [0.3.1] - 2018-12-17

### Fixed

- Fix crash on launching.
- Fix crash if Elona foobar is placed in a folder which contains non-ASCII characters.



## [0.3.0] - 2018-12-15

### Added

- Add new shortcut key, `Ctrl+Tab`, to move to the previous (left) menu.
- Make possible to reload autopick definition file via `Shift+Backspace`.
- Prevent precious ally from being destroyed by gene machine. You can regard an ally as precious by using stethoscope to him/her.
- Implement keybinding. You can customize them throuth the keybinding menu in the bottom of the option menu.
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
- Add option to skip prompt to confirm selling/buying items in town shops (defualt: disable).
- Make message log window scrollable, storing up to 1000 lines. Available shortcut keys are as follows:
  - `Up`: scroll 1 line up (to older)
  - `Down`: scroll 1 line down (to newer)
  - `PageUp` or `Left`: scroll 1 page up (to older)
  - `PageDown` or `Right`: scroll 1 page down (to newer)
  - `Home`: jump to the top (to the oldest)
  - `End`: jump to the bottom (to the newest)
- Give "yeek" (boss) to his own name, "\<Rodlob\> the boss of yeeks".
  - The name is the reverse spelling of "Boldor", the Angband monster, as his Japanese name is.
- Improve shadow graphics.
- Add option to enable text antialiasing (default: enabled). Also change the bundled font from KochiGothic to GenShinGochic to make text rendering more beatiful when antialiasing is on.
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
- [vanilla] Fix aspect ratio of PCC in change apperance menu.
- [vanilla] Fix item chip of double bed and happy bed being cut off.
- [vanilla] Remove garbage displayed around selection keys.
- [vanilla] Remove strange spacing in the message log window when the weather changes.
- [vanilla] Fix item chip of chain mail stacking on too high position.
- [vanilla] Fix food not getting rotten sometimes if you believe in Kumiromi.
- [vanilla] Fix the progress of ether disase advancing over the upper limit.
- [vanilla] Replace ellipsis symbols with 3 periods in English text because some English fonts do not have the glyph.
- [vanilla] Move the position of the crypt of the damned in the grobal map right. The previous one was on the cliff, which was of course invalid, so that the crypt might be placed at different position in each save and rarely "moves" every time diastrophism occurs.
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


### Deleted

- Delete support of old vanilla's save(older than 1.22).
  - We have a plan to provide an importer/exporter in the future.
- Delete support of old foobar's save(v0.2.6 or earlier).
  - Please update your save in v0.2.7 before you load it in v0.2.8(this version).


### Fixed

- [vanilla] Fix shelter stacking when you build it on another shelter.
- [vanilla] Fix glitch of drawing bottom left of small map if the window size is large enough.
- Fix special ammo enchantment not being added.
- Fix living weapon not destroying the last enchantment when the weapon has 15 enchantments and sucks blood.
- Fix water dropped on an alter not geting blessed.
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
  - Almost all of options get avaiable ingame now. You don't need touch it directly, maybe.
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
- Fix not being able to walk diagonally in a certan condition.
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


### Deleted

- Do not copy `original\config.txt`, no longer needed.
- Hide stair position markers in minimap in muggle mode.


### Fixed

- [vanilla] Fix known issues since vanilla in Elona Bugfix wiki.
  - Too many...
- [vanilla] Fix the lords of Chaos Chastles not dropping rod of wishing.
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


### Deleted

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


### Deleted

- Delete unavailable option, `cfg_msg_box`.
- Remove test NPCs(they are too strong in spite of their low level).
- Disable rendering high quality shadow temporarily.
- Disable voldemort mode by default.
  - It is available and you can enable it via [F12].


### Fixed

- Fix Ainc drops fruits by bashing.
- Fix crash when wishing skills.
- Fix not being able to uncurse items.
- Fix Foobar quiting when rolling attributes.
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
- Highlight positions of upstaris/downstairs.
- Always show HP bars.
- Exchange position pressing Shift key.
- Quick save and quick load.
- Abolish upper limit of number of NPC's actions(10 -> unlimited).
- Minimum attribute roll in character making.


### Deleted

- Delete F12 console commands.
- Remove compatibility with too old versions(older than 1.16).


### Fixed

too many...
