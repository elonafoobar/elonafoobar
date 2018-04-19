# Elona Foobar

* One of the Elona variants.
* It is made of C++.
* It is derived from Elona v1.22.
* It is alpha version yet(note: binary file is not distributed yet).
* It ~~has~~will have the highest extensibity with Lua. [####+]
* It ~~achieves~~will achieve truely internationalization. [####+]
* It ~~works~~will work on multi-platform. [####+] (currently, macOS only)
* It decreases the compatibility by -10.



# How To Contribute

See CONTRIBUTING.md for details.



# How To Build

## Requirements

* `make`
* `clang-format`, `find` and `xargs`(Optional)
* C++ compiler which supports C++14.
* Boost
* Lua 5.3
* SDL2, SDL2_image, SDL2_ttf and SDL2_mixer

## Steps

1. `cd path/to/ElonaFoobar; make`


# How To Play

1. Copy `graphic` and `sound` folders from vanilla v1.22 to `runtime/graphic` and `runtime/sound`.
1. Copy `user/graphic/face1.bmp` from vanilla v1.22 to `runtime/user/graphic/face1.bmp`.
1. Add your favorite font to `runtime/font` folder.
1. Edit `font1` and `font2` in `runtime/config.json` and set them to the above filename. Be sure to append the extension like .ttf.
1. `cd path-to-elonafoobar`.
1. Execute `ElonaFoobar` or `ElonaFoobar.exe`.


```json
{
  "alert_wait": 50,
  "alwaysCenter": 1,
  "anime_wait": 0,
  "attackAnime": 1,
  "attackWait": 4,
  "autoNumlock": 1,
  "autoTurnType": 2,
  "charamake_wiz": 0,
  "clockH": 96,
  "clockW": 120,
  "clockX": 0,
  "defLoadFolder": "",
  "envEffect": 1,
  "extraClass": 1,
  "extraHelp": 0,
  "extraRace": 1,
  "font1": "ＭＳ ゴシック",
  "font2": "Courier New",
  "fontSfix1": 1,
  "fontSize": 14,
  "fontVfix1": -1,
  "fullscreen": 0,
  "heartbeat": 1,
  "hide_autoIdentify": 0,
  "hide_shopResult": 0,
  "ignoreDislike": 1,
  "infVerType": 1,
  "joypad": 0,
  "key_alter": "[",
  "key_ammo": "A",
  "key_apply": "a",
  "key_bash": "b",
  "key_cancel": "\\",
  "key_cast": "v",
  "key_charainfo": "c",
  "key_close": "C",
  "key_dig": "D",
  "key_dip": "B",
  "key_drink": "q",
  "key_drop": "d",
  "key_east": "6 ",
  "key_eat": "e",
  "key_enter": " ",
  "key_esc": "^",
  "key_fire": "f",
  "key_get": "g",
  "key_get2": "0",
  "key_give": "G",
  "key_goDown": ">",
  "key_goUp": "<",
  "key_help": "?",
  "key_identify": "x",
  "key_interact": "i",
  "key_inventory": "X",
  "key_journal": "j",
  "key_look": "l",
  "key_material": "m",
  "key_mode": "z",
  "key_mode2": "u",
  "key_msglog": "\/",
  "key_north": "8 ",
  "key_northeast": "9 ",
  "key_northwest": "7 ",
  "key_offer": "O",
  "key_open": "o",
  "key_pagedown": "-",
  "key_pageup": "+",
  "key_pray": "p",
  "key_quick": "z",
  "key_quickinv": "x",
  "key_quickload": "F2",
  "key_quicksave": "F1",
  "key_autodig": "H",
  "key_read": "r",
  "key_rest": "R",
  "key_sCancel": 1,
  "key_save": "S",
  "key_search": "s",
  "key_set": [
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u"
  ],
  "key_skill": "a",
  "key_south": "2 ",
  "key_southeast": "3 ",
  "key_southwest": "1 ",
  "key_target": "h",
  "key_throw": "T",
  "key_trait": "F",
  "key_use": "t",
  "key_wait": ".",
  "key_wear": "w",
  "key_west": "4 ",
  "key_wipe": "W",
  "key_zap": "Z",
  "language": 0,
  "msgLine": 4,
  "msg_addTime": 1,
  "msg_log": 16,
  "msg_trans": 4,
  "music": 0,
  "net": 0,
  "netChat": 0,
  "netWish": 0,
  "objectShadow": 1,
  "runWait": 2,
  "scr_sync": 2,
  "scroll": 1,
  "scroll_run": 1,
  "serverList": 0,
  "shadow": 0,
  "skipRandEvents": 0,
  "sound": 0,
  "startRun": 2,
  "story": 1,
  "tileSize": 48,
  "titleEffect": 1,
  "wait1": 30,
  "walkWait": 5,
  "windowAnime": 1,
  "windowH": 600,
  "windowW": 800,
  "windowX": 0,
  "windowY": 0,
  "xkey": 1,
  "zkey": 1
}
```




# License

MIT License. See LICENSE for details. This license is applied for the
contents in this repository. Note that images and sounds are not included.

## Thirdparty libraries

* picojson: see thirdparty/picojson/LICENSE.
* cmake/FindXXX.cmake: see cmake/LICENSE.
