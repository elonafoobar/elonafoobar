Thank you for contributing!


# Bug report or new feature

Create a new issue from [here](https://github.com/ElonaFoobar/ElonaFoobar/issues/new).


## For Japanese players

日本人プレイヤーの方へ。バグ報告及び機能要望は英語の方がありがたいです。どうしてもという場合には日本語でも構いませんが、最終的には英語に翻訳されます。
私も英語が得意ではありませんのでこのようなことをお願いするのは心苦しいのですが、Elona Foobarの発展のためご協力をお願い申し上げます。



# Pull request

GitHub flow like.

1. Create a new issue.
1. Fork this repository and clone the forked one.
1. Set up `upstream` branch. `git remote add upstream https:://github.com/YOUR_ACCOUNT/ElonaFoobar`.
1. Update local `master`. `git checkout master && git pull upstream master`.
1. Create your working branch. Naming conventions are as follows:
  * Do not use too general name like `master`, `develop`, or `feature`.
  * Prepend `fix/`, `refactor/`, or `feature/` to the short summary of your changes. For example,
    - `fix/crash-in-XXXing`
    - `refactor/delete-unused-functions`
    - `feature/import-XXX-from-omake`
1. Work and commit your changes. Small commits are prefered.
1. Update local `master` again.
1. Rebase. `git checkout YOUR_WORKING_BRANCH && git rebase master`.
1. Push to your remote branch. `git push origin YOUR_WORKING_BRANCH`.
1. Create a new pull request.
1. Your pull request is reviewed and fix problems if needed.
1. Your pull request is merged.


If your changes are big, you can send a pull request with prefix `[WIP]`. Pull requests marked as "work in progress" are not merged.

In all commits, the C++ source code should be formatted by `clang-format` except that your changes are so many.



## Commit messages

Follow this format.

```
Fix aaa bbb ccc #ISSUE
```

* Neither `fix`, `Fixed` nor `fixing`.
* No period.
* Other appropriate verbs are allowed.
