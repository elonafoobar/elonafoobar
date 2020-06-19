Thank you for contributing!


# Bug report or new feature proposal

Create a new issue from [here](https://github.com/elonafoobar/elonafoobar/issues/new).



# Pull request



1. Create a new issue.
2. Fork this repository and clone the forked one.
3. Set up `upstream` branch: `git remote add upstream https:://github.com/YOUR_ACCOUNT/elonafoobar`.
4. Update local `develop`: `git checkout develop && git pull upstream develop`.
5. Create your working branch from `develop`. Naming conventions are as follows:
  * Prepend `feature/`, `fix/` or `refactor/` to the short summary of your changes. For example,
    - `feature/add-lua-module`
    - `fix/map-tile-glitch`
    - `refactor/remove-global-variables`
6. Work and commit your changes. Small commits are prefered.
7. Run `make format` or `nmake -f Makefile.win format` to format your changed source code.
  * **Note:** If your changed source code is not formatted consistently, continuous integration will not pass.
8. Update local `develop` again.
9. Rebase: `git checkout YOUR_WORKING_BRANCH && git rebase develop`.
10. Push to your remote branch. `git push origin YOUR_WORKING_BRANCH`.
11. Create a new pull request.
12. Your pull request is reviewed and fix problems if needed.
13. Your pull request is merged.


If your changes are big or you need help, you can send a pull request with prefix `WIP:`. Pull requests marked as "work in progress" are not merged.


## Lua API features

1. Create a new file named `lua_api_[module name here].cpp` under `src/elona/lua_env/lua_api`.
2. Add functions inside the appropriate namespace.
  - Add overrides for functions taking `position_t` so two `int`s can be passed instead.
3. Set the binding on the correct table in `elona::lua::LuaApi::bind()`.
4. Update `.luacheckrc` with the new table value.
5. Run `make docgen` to generate corresponding LDoc file. (Rust toolchains are required)
6. Add tests inside `tests/lua_api.cpp`.
7. Provide a playtest script demonstrating the API in the pull request.


# Branching rules

We use Git flow. See http://nvie.com/posts/a-successful-git-branching-model/ for details.


# Code style

See [CODE_STYLE.md](CODE_STYLE.md).


# Commit messages

Follow this format.

```
Fix crash when calling function xxx()
```

* Neither `fix`, `Fixed` nor `fixing`.
* No period.
* Other appropriate verbs are allowed.



# Versioning convention

## Application

Ignore Semantic Versioning.


## Built-in mods

Follow Semantic Versioning. Each mod has its own version, not synchronized with each other.
