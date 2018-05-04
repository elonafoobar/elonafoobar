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


### Additional requirements for Windows

* Visual Studio 2017 x64
* 7-Zip or similar (for automated dependency extraction using `7z.exe`)

## Steps

### Unix

1. `cd path/to/ElonaFoobar; make`

### Windows

1. Download and install the binaries for Boost `1.66` from [here](https://dl.bintray.com/boostorg/release/1.66.0/binaries/boost_1_66_0-msvc-14.1-64.exe).
2. Edit `setenv.bat` to point to your Boost install directory.
3. Run `download.bat` inside the `deps` folder to download the other dependencies to `deps\include` and `deps\lib` (you have to have `7z.exe` on your `PATH`).
4. Extract `elona122.zip` (from [here](http://ylvania.style.coocan.jp/file/elona122.zip)) to the `deps` directory, so `deps\elona` exists. This will allow for automatically copying the required assets.
5. Run the following commands in the project root under the `Developer Command Prompt for VS 2017`:
```
setenv.bat
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" ..
```
6. Build the source:
```
cmake --build .
```
The executable, assets and required libraries will be output under `build\Debug`. To debug with Visual Studio, open `build\ElonaFoobar.sln`.

1. Copy `graphic` and `sound` folders from vanilla v1.22 to `runtime/graphic` and `runtime/sound`.
2. Copy `user/graphic/face1.bmp` from vanilla v1.22 to `runtime/user/graphic/face1.bmp`.
3. Add your favorite font to `runtime/font` folder.
4. Edit `font1` and `font2` in `runtime/config.json` and set them to the above filename. Be sure to append the extension like .ttf.
5. Execute `ElonaFoobar` or `ElonaFoobar.exe`.


# How To Contribute

See CONTRIBUTING.md for details.



# License

MIT License. See LICENSE for details. This license is applied for the
contents in this repository. Note that images and sounds are not included.

## Thirdparty libraries

* picojson: see thirdparty/picojson/LICENSE.
* cmake/FindXXX.cmake: see cmake/LICENSE.
