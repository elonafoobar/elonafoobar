# Elona foobar [![AppVeyor Build Status][appveyor-build-status-svg]][appveyor-build-status] [![Travis CI Build Status][travis-build-status-svg]][travis-build-status]

* Elonaのヴァリアントの一つだ
* それはC++で作られている
* それはElona v1.22から派生した
* それはまだアルファ版だ
* それはLuaによる高い拡張性を持つ(予定) [\*\*\*\*+]
* それは真の国際化を実現する(予定) [\*\*\*\*+]
* それはマルチプラットフォームで動く [\*\*\*\*+]


# How To Build

## 必要なもの

* `make`
* CMake
* C++14をサポートするC++コンパイラ
* Boost
* Lua 5.3
* SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
* `clang-format`, `find` and `xargs`(任意)

### Windows用

* Visual Studio 2017 x64
* 7-Zip または それに類するもの(自動的に依存ライブラリを解凍するのに`7z.exe`が必要です)

### Linux用

* SMPEG
* Timidity++


## 手順

1. `elona122.zip` ([ここ](http://ylvania.style.coocan.jp/file/elona122.zip)からDL)を`deps`フォルダに解凍してください。`deps\elona`フォルダができるはずです。必要な画像や音声はここからコピーされます。
2. 以下のプラットフォームごとの手順に従ってください。

### macOS

1. 依存ライブラリをインストールしてください。
```
brew install cmake boost sdl2 sdl2_ttf sdl2_mixer sdl2_image lua
```
2. `cd path/to/Elona_foobar; make`


### Linux

1. 依存ライブラリをインストールしてください。Arch Linux用:
```
sudo pacman -S cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer smpeg lua boost timidity++
```
`apt`のあるLinux用:
```
sudo apt-get install cmake liblua5.3-dev libboost-all-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-def smpeg timidity
```
2. `cd path/to/Elona_foobar; make`


### Windows

1. Boost `1.66` を[ここ](https://dl.bintray.com/boostorg/release/1.66.0/binaries/boost_1_66_0-msvc-14.1-64.exe)からDLし、インストールしてください。
2. `Makefile.win`を編集し、Boostをインストールしたフォルダを指定してください。
3. `deps\include`と`deps\lib`内に依存ライブラリを展開するために`deps`内にある`download.bat`を実行してください。(`7z.exe`を`PATH`が通ったフォルダに置いておく必要があります)
4. `Developer Command Prompt for VS 2017`を開いてください。
5. `cd path/to/Elona_foobar & nmake -f Makefile.win`

Visual Studioを使ってデバッグする場合は、`bin\Elona_foobar.sln`を開いてください。

# How To Play

1. `data`、`graphic`、`map`、`original`、`sound`、`user`フォルダを本家開発版(v1.22)から実行ファイルのあるフォルダへとコピーしてください。このとき、foobarに存在するファイルは上書きしないようにしてください。本家と同名のファイルはfoobarで更新されています。
2. `bin/Elona_foobar`(Linux)、`bin/Elona_foobar.app`(macOS)、`bin\Debug\Elona_foobar.exe`(Windows)を実行してください


# How To Contribute

詳細は[CONTRIBUTING.md](CONTRIBUTING.md)を参照してください。



# License

**注意:ここに書かれた日本語でのライセンス表記と英語でのライセンス表記が矛盾する場合、常に英語版が優先されます。あくまで参考程度であり、厳密なライセンスは\*必ず\*英語版のREADME.mdをご覧ください。**

MIT Licenseです。詳細はLICENSEを参照してください。このライセンスはこのリポジトリ内にあるものにのみ適用されます。
画像や音声は含まれないことに注意してください。

## サードパーティーライブラリ

* Catch2: src/thirdparty/catch2/LICENSEを参照してください。
* hayai: src/thirdparty/hayai/LICENSEを参照してください。
* sol2: src/thirdparty/sol2/LICENSEを参照してください。
* ordered_map: src/thirdparty/ordered_map/LICENSEを参照してください。
* cmake/FindXXX.cmake: cmake/LICENSEを参照してください。

## Luaライブラリ

* [inspect.lua](https://github.com/kikito/inspect.lua) (MIT)



<!-- Badges -->
[appveyor-build-status]: https://ci.appveyor.com/project/ki-foobar/elonafoobar/branch/develop
[appveyor-build-status-svg]: https://ci.appveyor.com/api/projects/status/jqhbtdkx86lool4t/branch/develop?svg=true
[travis-build-status]: https://travis-ci.org/ElonaFoobar/ElonaFoobar?branch=develop
[travis-build-status-svg]: https://travis-ci.org/ElonaFoobar/ElonaFoobar.svg?branch=develop
