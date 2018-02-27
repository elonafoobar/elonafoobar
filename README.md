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
* `clang-format`(only contributing)
* Some unix commands. `find` and `xargs`.
* `g++` which supports C++17 and `std::filesystem`.
* Lua 5.3
* SDL2, SDL2_image, SDL2_ttf and SDL2_mixer

## Steps

1. `cd path/to/ElonaFoobar; make`


# How To Play

1. Prepare `runtime` directory:
1. Execute `elonafoobar` in the directory.

```
runtime/
  elonafoobar # Excutable binary
  scene1.hsp
  scene2.hsp # Scene files from the original Elona v1.22
  config.json # Copy the below file
  font/
    APJapanesefontT.ttf # Sorry, but the filename of font is hard-coded now.
  graphic/ # Same as the original Elona v1.22
  sound/ # Same as the original Elona v1.22
  map/
    *.idx
    *.obj
    *.map # Please extend gzip file manually.
  data/ # Same as the original Elona v1.22
```

Important note: convert the encoding of all text files to UTF-8 from Shift-JIS.


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
  "msg_box": 1,
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
