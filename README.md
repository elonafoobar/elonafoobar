# Elona Foobar [![AppVeyor Build Status][appveyor-build-status-svg]][appveyor-build-status] [![Travis CI Build Status][travis-build-status-svg]][travis-build-status]

* One of the Elona variants.
* It is made of C++.
* It is derived from Elona v1.22.
* It is alpha version yet.
* It ~~has~~will have the highest extensibity with Lua. [####+]
* It ~~achieves~~will achieve truly internationalization. [####+]
* It works on multi-platform. [####+]


# How To Build

## Requirements

* `make`
* CMake
* C++ compiler which supports C++14
* Boost
* Lua 5.3
* SDL2, SDL2_image, SDL2_ttf and SDL2_mixer
* `clang-format`, `find` and `xargs`(Optional)

### Additional requirements for Windows

* Visual Studio 2017 x64
* 7-Zip or similar (for automated dependency extraction using `7z.exe`)

### Additional requirements for Linux

* SMPEG
* Timidity++


## Steps

1. Extract `elona122.zip` (from [here](http://ylvania.style.coocan.jp/file/elona122.zip)) to the `deps` directory, so `deps\elona` exists. This will allow for automatically copying the required assets.
2. Follow the platform-specific instructions below.

### macOS

1. Install the required dependencies.
```
brew install cmake boost sdl2 sdl2_ttf sdl2_mixer sdl2_image lua
```
2. `cd path/to/ElonaFoobar; make`


### Linux

1. Install the required dependencies. For Arch Linux:
```
sudo pacman -S cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer smpeg lua boost timidity++
```
For systems with `apt`:
```
sudo apt-get install cmake liblua5.3-dev libboost-all-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-def smpeg timidity
```
2. `cd path/to/ElonaFoobar; make`


### Windows

1. Download and install the binaries for Boost `1.66` from [here](https://dl.bintray.com/boostorg/release/1.66.0/binaries/boost_1_66_0-msvc-14.1-64.exe).
2. Edit `Makefile.win` to point to your Boost install directory.
3. Run `download.bat` inside the `deps` folder to download the other dependencies to `deps\include` and `deps\lib` (you have to have `7z.exe` on your `PATH`).
4. Open the `Developer Command Prompt for VS 2017`.
5. `cd path/to/ElonaFoobar & nmake -f Makefile.win`

To debug with Visual Studio, open `build\ElonaFoobar.sln`.

# How To Play

1. If not done already, copy the `data`, `graphic`, `map`, `original`, `sound` and `user` folders from vanilla v1.22 to the directory containing the executable.
2. Execute `bin/ElonaFoobar`, `bin/ElonaFoobar.app` or `bin/Debug/ElonaFoobar.exe`.


# How To Contribute

See [CONTRIBUTING.md](CONTRIBUTING.md) for details.



# License

MIT License. See LICENSE for details. This license is applied for the
contents in this repository. Note that images, sounds and fonts are not included.

## Thirdparty libraries

* picojson: see thirdparty/picojson/LICENSE.
* Catch2: see thirdparty/catch2/LICENSE.
* cmake/FindXXX.cmake: see cmake/LICENSE.



<!-- Badges -->
[appveyor-build-status]: https://ci.appveyor.com/project/ki-foobar/elonafoobar/branch/develop
[appveyor-build-status-svg]: https://ci.appveyor.com/api/projects/status/jqhbtdkx86lool4t/branch/develop?svg=true
[travis-build-status]: https://travis-ci.org/ElonaFoobar/ElonaFoobar?branch=develop
[travis-build-status-svg]: https://travis-ci.org/ElonaFoobar/ElonaFoobar.svg?branch=develop
