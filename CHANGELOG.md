# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).



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
