# Elona Foobar

* One of the Elona variants.
* It is made of C++.
* It is derived from Elona v1.22.
* It is alpha version yet.
* It ~~has~~will have the highest extensibity with Lua. [####+]
* It ~~achieves~~will achieve truly internationalization. [####+]
* It works on multi-platform. [####+] (currently, support Windows and macOS)



# How To Play

1. Copy `graphic` and `sound` folders from vanilla v1.22 to `runtime/graphic` and `runtime/sound`.
1. Copy `graphic/face1.bmp` from vanilla v1.22 to `runtime/user/graphic/face1.bmp`.
1. Add your favorite font to `runtime/font` folder.
1. Edit `font1` and `font2` in `runtime/config.json` and set them to the above filename. Be sure to append the extension like .ttf.
1. Execute `runtime/ElonaFoobar` or `runtime/ElonaFoobar.exe`.


```json
{
  "font1": "Whatever font you like in Japanese",
  "font2": "Whatever font you like in Enligsh"
}
```



# How To Build

## Requirements

* `make`
* CMake
* C++ compiler which supports C++14
* Boost
* Lua 5.3
* SDL2, SDL2_image, SDL2_ttf and SDL2_mixer
* `clang-format`, `find` and `xargs`(Optional)


## Steps

### On macOS

1. `cd path/to/ElonaFoobar; make`

### On Windows

1. See Makefile and comment out CMake's options.
1. `cd path/to/ElonaFoobar; make`
1. Launch Visual Studio and build the generated solution.



# How To Contribute

See CONTRIBUTING.md for details.



# License

MIT License. See LICENSE for details. This license is applied for the
contents in this repository. Note that images and sounds are not included.

## Thirdparty libraries

* picojson: see thirdparty/picojson/LICENSE.
* cmake/FindXXX.cmake: see cmake/LICENSE.
