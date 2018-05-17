Thank you for contributing!


# Bug report or new feature proposal

Create a new issue from [here](https://github.com/ElonaFoobar/ElonaFoobar/issues/new).



# Pull request

1. Create a new issue.
1. Fork this repository and clone the forked one.
1. Set up `upstream` branch. `git remote add upstream https:://github.com/YOUR_ACCOUNT/ElonaFoobar`.
1. Update local `develop`. `git checkout develop && git pull upstream develop`.
1. Create your working branch from `develop`. Naming conventions are as follows:
  * Prepend `feature/` to the short summary of your changes. For example,
    - `feature/import-XXX-from-omake`
1. Work and commit your changes. Small commits are prefered.
1. Update local `develop` again.
1. Rebase. `git checkout YOUR_WORKING_BRANCH && git rebase develop`.
1. Push to your remote branch. `git push origin YOUR_WORKING_BRANCH`.
1. Create a new pull request.
1. Your pull request is reviewed and fix problems if needed.
1. Your pull request is merged.


If your changes are big or you need help, you can send a pull request with prefix `[WIP]`. Pull requests marked as "work in progress" are not merged.

In all commits, the C++ source code should be formatted by `clang-format`.



# Branching rules

We use Git flow. See http://nvie.com/posts/a-successful-git-branching-model/ for details, and we recommend this tool: https://github.com/nvie/gitflow.


# Code format
## C++
The following is ideal; not all of these are being regarded at the moment.

- C++ source files use `.cpp`, header files use `.hpp`.
- Try to keep source files below 5,000SLoC. This makes a high-level overview of pieces of related functionality easier to parse.
- Break up large methods as much as possible, especially things like long `switch` statements.
  + Even better, see if there are ways to externalize data in declarative file formats, like item/character definitions.
- For large hunks of related code, split them up files named with a common prefix. For example, `action.cpp`, `action_dig.cpp` and `action_melee.cpp`.
- We use `snake_case` as it was inherited from the original HSP source.
- Prefix public methods inside C++ source files with the name of the file. For example, `enchantment.hpp` could contain `enchantment_add()` and `enchantment_remove()`. This makes it easier to work out where the functions come from. Of course this needn't always be the case, for example if a large group of related functionality is spread out throughout related files. In that case, use the prefix of the main file (for `action_dig.cpp`, use `action_`).
- Use names that make sense in English. Instead of `dmghp`, use `damage_hp`.
- Use `#pragma once` inside headers.
- Everything goes into the `elona` namespace. For major sections of the code, like the Lua functionality, an additional namespace could be added. For game logic, only `elona` should suffice.
- Avoid introducing new global variables in `variables.hpp` (there are already too many). If you absolutely must, consider encapsulating them inside an existing global variable.
- Prefer `enum class` to raw integers for internal enumerations.
- For data types that can be expanded with new members dynamically, like item IDs, use integers for legacy code or strings for new code with mods.
  + Ideally all such IDs should use strings, to give a uniform interface.
- Avoid the usage of raw pointers unless absolutely necessary (which, in the current state of the code, is never).
- Pass references to objects to modify them inside a method.
- Use `const` where appropriate (arguments, methods, etc.) to make it clear what is being modified.
- If you come across behavior that is correct but surprises you, be sure to leave a comment noting it, and bring it up in the respective PR.
- Run `clang-format` on your code by running `make format`.

## Lua
- Module/Table names should use `CamelCase`. Method names and variables should use `snake_case`. Classes exported from C++ should use `CamelCase` prefixed with `Lua`, like `LuaCharacter`.
- Anything related to the core API should go into a table inside the root `Elona` table.
- Limit the amount of things in the global namespace as much as possible.
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
- `map` - the actual tile data of the map, indexed by `(x, y, data_type)`. A `data_type` of `0` is the wall/floor state
- `cc` - global current character index into `cdata` for the character whose turn it is, the target of an action to a single character, etc. If this isn't passed in, it was implicitly set elsewhere.
- `tc` - global target character index into `cdata` for spell targets, etc.
- `ci` - global current item index into `inv`
- `x/y/sx/sy/dx/dy` - global variables used for positions.
- `tlocx/tlocy` - global target location for magic, etc.
- `mode` - global integer that changes the behavior of functions like `ctrl_inventory()` for querying the player's inventory, and various other things (there are lots of these, because HSP has no notion of local variables)
- `f` - global success/failure flag - 1 for success, 0 for failure
- `p` - global variable used for just about anything (indices, integer enumerations...). It's actually an integer array.
- `rtval` - global integer return value (HSP is weird)
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

# Commit messages

Follow this format.

```
Fix aaa bbb ccc
```

* Neither `fix`, `Fixed` nor `fixing`.
* No period.
* Other appropriate verbs are allowed.
