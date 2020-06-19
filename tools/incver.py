#!/usr/local/bin/python3


import argparse
import re
import subprocess
import sys


class Version:
    def __init__(self, major, minor, patch):
        self.major = major
        self.minor = minor
        self.patch = patch

    def inc(self, mode):
        if mode == 'major':
            return Version(
                self.major + 1,
                0,
                0)
        elif mode == 'minor':
            return Version(
                self.major,
                self.minor + 1,
                0)
        elif mode == 'patch':
            return Version(
                self.major,
                self.minor,
                self.patch + 1)

    def __str__(self):
        return '{}.{}.{}'.format(
            self.major,
            self.minor,
            self.patch)


def inc_ver(mode, dry_run, filename, ver_re, ver_fmt, target):
    with open(filename, 'r') as file:
        file_content = file.read()

        ver_match = re.search(ver_re, file_content)

        old_ver = Version(
            int(ver_match.group(1)),
            int(ver_match.group(2)),
            int(ver_match.group(3)))
        new_ver = old_ver.inc(mode)

        file_content = re.sub(
            ver_re,
            ver_fmt.format(
                new_ver.major, new_ver.minor, new_ver.patch),
            file_content)

    if not dry_run:
        with open(filename, 'w') as file:
            file.write(file_content)

        cmd = 'git commit -a -m "Increment {}\'s {} version: {} -> {}"'.format(
            target, mode, old_ver, new_ver)
        subprocess.call(cmd, shell=True)

        print('{}\'s {} version is successfully incremented: {} -> {}'.format(
            target, mode, old_ver, new_ver))
    else:
        print('{}\'s {} version will be incremented: {} -> {}'.format(
            target, mode, old_ver, new_ver))


def inc_app_ver(args):
    inc_ver(
        args.mode,
        args.dry_run,
        'CMakeLists.txt',
        r'project\(Elona_foobar VERSION (\d+)\.(\d+)\.(\d+)\)',
        'project(Elona_foobar VERSION {}.{}.{})',
        'Elona foobar',
    )


def inc_mod_ver(args):
    mod = args.target
    inc_ver(
        args.mode,
        args.dry_run,
        'runtime/mod/{}/mod.json'.format(mod),
        r'version: "(\d+)\.(\d+)\.(\d+)",',
        'version: "{}.{}.{}",',
        'mod {}'.format(mod),
    )


def make_argparser():
    p = argparse.ArgumentParser(description='Increment Elona foobar version.')
    p.add_argument('target')
    p.add_argument('mode', choices=['major', 'minor', 'patch'])
    p.add_argument('-n', '--dry-run', action='store_true')
    return p


def main():
    parser = make_argparser()
    args = parser.parse_args()

    if args.target == 'APP':
        inc_app_ver(args)
    else:
        inc_mod_ver(args)


if __name__ == '__main__':
    main()
