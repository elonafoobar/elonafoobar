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

## Lua API features

1. Create a binding in `lua_api.cpp` inside the appropriate namespace.
  - Add overrides for functions taking `position_t` so two `int`s can be passed instead.
2. Set the binding on the correct table in `lua::init()`.
3. Update `.luacheckrc` with the new table value.
4. Add LDoc documentation in `doc/api`.
5. Add tests inside `tests/lua_api.cpp`.
6. Provide a playtest script demonstrating the API in the pull request.


# Branching rules

We use Git flow. See http://nvie.com/posts/a-successful-git-branching-model/ for details, and we recommend this tool: https://github.com/nvie/gitflow.



# Commit messages

Follow this format.

```
Fix aaa bbb ccc
```

* Neither `fix`, `Fixed` nor `fixing`.
* No period.
* Other appropriate verbs are allowed.
