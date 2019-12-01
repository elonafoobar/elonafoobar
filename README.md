# Elona foobar [![AppVeyor Build Status][appveyor-build-status-svg]][appveyor-build-status] [![Travis CI Build Status][travis-build-status-svg]][travis-build-status]

* One of the Elona variants.
* It is made of C++.
* It is derived from Elona v1.22.
* It is still in an early stage of development.
* It features high extensibility through a mod system. [####+]
* It can be localized in multiple languages. [####+]
* It works on Windows, Linux and macOS. [####+]


# How To Build

## Requirements

* `make`
* CMake 3.2 or later
* C++ compiler which supports C++14
* Boost 1.69
* Lua 5.3
* SDL2, SDL2_image, SDL2_ttf and SDL2_mixer
* `clang-format`, `find` and `xargs`(Optional)

### Additional requirements for Windows

* Visual Studio 2017 x64

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
2. `cd path/to/Elona_foobar; make build`


### Linux

1. Install the required dependencies. For Arch Linux:
```
sudo pacman -S cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer gtk3 smpeg lua boost timidity++
```
For systems with `apt`:
```
sudo apt-get install cmake liblua5.3-dev libboost-all-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev gtk+-3.0 smpeg timidity
```
2. `cd path/to/Elona_foobar; make build`


### Windows

1. Download and install the binaries for Boost `1.69` from [here](https://dl.bintray.com/boostorg/release/1.69.0/binaries/boost_1_69_0-msvc-14.1-64.exe).
2. Edit `Makefile.win` to point to your Boost install directory.
3. Run `install.bat` inside the `deps` folder to move the other dependencies to `deps\include` and `deps\lib`.
4. Open the `Developer Command Prompt for VS 2017`.
5. `cd path/to/Elona_foobar & nmake build -f Makefile.win`

To debug with Visual Studio, open `bin\Elona_foobar.sln`.



# How To Play

1. Copy the `graphic` and `sound` folders from vanilla v1.22 to the directory containing the executable. Make sure not to overwrite any files that already exist, as they have been updated in this version.
2. Execute `bin/Elona_foobar`, `bin/Elona_foobar.app` or `bin/Debug/Elona_foobar.exe`.


# How To Contribute

See [CONTRIBUTING.md](.github/CONTRIBUTING.md) for details.



# License

MIT License. See [LICENSE.txt](LICENSE.txt) for details. This license is applied for the
contents in this repository. Note that images, sounds and fonts are not included.
For files under [runtime/graphic](runtime/graphic/) folder of the repository, see
[runtime/graphic/LICENSE.txt](runtime/graphic/LICENSE.txt).


## Thirdparty libraries

* microhcl: see [src/thirdparty/microhcl/LICENSE](src/thirdparty/microhcl/LICENSE).
* microhil: see [src/thirdparty/microhil/LICENSE](src/thirdparty/microhil/LICENSE).
* Catch2: see [src/thirdparty/catch2/LICENSE](src/thirdparty/catch2/LICENSE).
* hayai: see [src/thirdparty/hayai/LICENSE](src/thirdparty/hayai/LICENSE).
* sol2: see [src/thirdparty/sol2/LICENSE.txt](src/thirdparty/sol2/LICENSE.txt).
* ordered_map: see [src/thirdparty/ordered_map/LICENSE](src/thirdparty/ordered_map/LICENSE).
* boostrandom: see [src/thirdparty/boostrandom/LICENSE_1_0.txt](src/thirdparty/LICENSE_1_0.txt).
* cmake/FindXXX.cmake: see [cmake/LICENSE](cmake/LICENSE).
* nativefiledialog: see [src/thirdparty/nfd/LICENSE](src/thirdparty/nfd/LICENSE).
* cpp-netlib/uri: see [src/thirdparty/uri/LICENSE_1_0.txt](src/thirdparty/uri/LICENSE_1_0.txt).
* xxHash: see [src/thirdparty/xxHash/LICENSE](src/thirdparty/xxHash/LICENSE).
* zstr: see [src/thirdparty/zstr/LICENSE](src/thirdparty/zstr/LICENSE).
* minizip: see [src/thirdparty/minizip/LICENSE](src/thirdparty/minizip/LICENSE).
* json5: see [src/thirdparty/json5/LICENSE](src/thirdparty/json5/LICENSE).

## Lua libraries

* [inspect.lua](https://github.com/kikito/inspect.lua) (MIT)



<!-- Badges -->
[appveyor-build-status]: https://ci.appveyor.com/project/ki-foobar/elonafoobar/branch/develop
[appveyor-build-status-svg]: https://ci.appveyor.com/api/projects/status/jqhbtdkx86lool4t/branch/develop?svg=true
[travis-build-status]: https://travis-ci.org/ElonaFoobar/ElonaFoobar?branch=develop
[travis-build-status-svg]: https://travis-ci.org/ElonaFoobar/ElonaFoobar.svg?branch=develop
