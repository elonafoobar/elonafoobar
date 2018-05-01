# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).



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
