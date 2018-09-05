# Code style
The following is ideal; not all of these are being regarded at the moment.

## C++

- C++ formatting style is handled by the use of `clang-format`. It's best to set up `clang-format` to be run after saving a `.cpp`/`.hpp` file in your editor. If it can't be done, you'll have to remember to use `make format`/`nmake -f Makefile.win format` after finishing your changes. Continuous integration is set up so code with inconsistent formatting will fail the build.
- C++ source files use `.cpp`, header files use `.hpp`.
- Try to keep source files below 5,000SLoC. This makes a high-level overview of pieces of related functionality easier to parse.
- Break up large methods as much as possible, especially things like long `switch` statements.
  + Even better, see if there are ways to externalize data in declarative file formats, like item/character definitions.
- For large hunks of related code, split them up into files named with a common prefix. For example, `action.cpp`, `action_dig.cpp` and `action_melee.cpp`.
- We use `snake_case` for C++ code.
  - For struct/class/enum names, Use `PascaleCase` except for `std`-library-like types such as `iterator`.
- Prefix public methods inside C++ source files with the name of the file. For example, `enchantment.hpp` could contain `enchantment_add()` and `enchantment_remove()`. This makes it easier to work out where the functions come from. Of course this needn't always be the case, for example if a large group of related functionality is spread out throughout related files. In that case, use the prefix of the main file (for `action_dig.cpp`, use `action_`).
- Use names that make sense in English. Instead of `dmghp`, use `damage_hp`.
- Use `#pragma once` inside headers.
- Everything goes into the `elona` namespace. For major sections of the code, like the Lua functionality, an additional namespace could be added. For game logic, only `elona` should suffice.
- Avoid introducing new global variables in `variables.hpp` (there are already too many). If you absolutely must, consider encapsulating them inside an existing global variable.
- Prefer `enum class` to raw integers for internal enumerations.
- For data types that can be expanded with new members dynamically, like item IDs, use integers for legacy code or strings for new code with mods.
  + Ideally all such IDs should use strings, to give a uniform interface.
- Avoid the usage of raw pointers unless absolutely necessary (which, in the current state of the code, is never). The rationale for this is none of the code currently checks for null pointers as a valid argument, instead relying on integer variables like `character.state` for existence (which are zeroed out when the character is deleted). Any code that introduces pointer arguments would have to also ensure their validity.
- Avoid `new` and `delete` for game-related things. They aren't currently used there.
- Pass references to objects to modify them inside a method.
- Use `const` where appropriate (arguments, methods, etc.) to make it clear what is being modified.
- If you come across behavior that is correct but surprises you, be sure to leave a comment noting it, and bring it up in the respective PR.
- Run `clang-format` on your code by running `make format`.

## Lua
- Module/Table names should use `CamelCase`. Method names and variables should use `snake_case`. Classes exported from C++ should use `CamelCase` prefixed with `Lua`, like `LuaCharacter`.
- Anything related to the core API should go into a table inside the root `Elona` table.
- Limit the amount of things in the global namespace as much as possible.
- Methods that mutate the state of a C++ reference object should be defined as methods, like `character:damage_hp(100)`. Methods that do not modify a C++ reference object should be defined as functions in modules, like `Chara.is_ally(chara)`.
  + Methods that do not take a corresponding object as an argument, like map-related functions (whether or not they mutate anything) should also be defined as functions in modules.
- Constants should go into tables organized inside `Elona.Defines`.
- You can shorten the amount of typing by declaring local "imports" like `local Enums = Elona.Defines.Enums`.
- Be sure to document all public API methods/classes/definitions/etc., to make it easier for modders to understand how to use them. Remember that modders aren't necessarily programmers. Documentation for Lua uses the [LDoc](https://stevedonovan.github.io/ldoc/manual/doc.md.html) syntax.
  + Ideally, provide working examples of how to use API methods also.
  + You may have to look into the C++ source code to give accurate descriptions of how internal things like event callbacks work. If you change how things like events are triggered, be sure the corresponding Lua documentation is updated also.

## Legacy things
These shouldn't be used in new code, but are useful for figuring out what things do.

### Variables
- `cdata` - global character array (by character index)
- `sdata` - global skill/resistance array (by character index)
- `inv` - global item array (by item index), both for items on the ground and in character inventories
- `ibit` - global array of item bitflags (by item index)
- `qdata` - global quest data array
- `gdata` - miscellaneous global variables array (see `macro_gdata.hpp`)
- `mdata` - global map metadata array, like width/height (`mdata(0)/mdata(1)`), global map/local map (`mdata(2)`) and tileset (`mdata(12)`)
- `adata` - global map metadata array for things like quest completion, indexed by `(data_type, map_id)`
- `map` - the actual tile data of the map, indexed by `(x, y, data_type)`. A `data_type` of `0` is the wall/floor state.
- `cc` - global current character index into `cdata` for the character whose turn it is, the target of an action to a single character, etc. If this isn't passed in, it was implicitly set elsewhere.
- `tc` - global target character index into `cdata` for spell targets, etc.
- `ci` - global current item index into `inv`
- `x/y/sx/sy/dx/dy` - global variables used for positions.
- `tlocx/tlocy` - global target location for magic, etc.
- `mode` - global integer that changes the behavior of functions like `ctrl_inventory()` for querying the player's inventory, and various other things (there are lots of these, because HSP has no notion of local variables)
- `f` - global success/failure flag - 1 for success, 0 for failure
- `p` - global variable used for just about anything (indices, integer enumerations...). It's actually an integer array.
- `rtval` - global integer or array return value (HSP is weird)
- `fset<...>` - arrays of filter categories for quickly generating e.g. equipment, magic items, valuables like gems, etc.
- `flttypemajor/flttypeminor/fixlv` - item generation global variables.
- `dbid` - global integer ID for looking up item definitions for various purposes.
- `inf_<...>` - UI constants.

### Functions
- `flt()` - sets filters for random item creation with `itemcreate`.
- `DIM1, DIM2, DIM3` - macros for setting up integer arrays of dimension 1, 2, or 3.
- `SDIM1, SDIM2, SDIM3` - same, but for string arrays.

### Miscellaneous
- `elona_vectorX<T>` can be accessed by index to get references (`p(0)`), or just the array name can be given and a reference to the item at the 0th index is implicitly returned (`p`). The same works for assignment. HSP is weird.
- `elona_vectorX<T>` will automatically resize if an index greater than its size is assigned to.
