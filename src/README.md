# Overview


## Files

### `main.cpp`

The main entry point of the game, Elona foobar.


### `launcher_main.cpp`

The main entry point of the launcher, Elona foobar Launcher.


### `version.hpp`/`version.cpp.in`

Defines Elona foobar's version. Variables enclosed by `@` in `version.cpp.in` like `@PROJECT_VERSION_MAJOR@` are injected by `CMake`.



## Folders

### `elona`

A folder contains core source codes.


### `snail`

SDL-based native audio and image library.


### `spider`

A library handling network-related things.


### `util`

Miscellaneous utilities.


### `tests`

Test cases and functionalities for testing.


### `bench`

Benchmark cases.


### `thirdparty`

Thirdparty libraries.
