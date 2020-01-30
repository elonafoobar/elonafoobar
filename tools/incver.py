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


def make_argparser():
    p = argparse.ArgumentParser(description='Increment Elona foobar version.')
    p.add_argument('mode', choices=['major', 'minor', 'patch'])
    p.add_argument('-n', '--dry-run', action='store_true')
    return p


def main():
    parser = make_argparser()
    args = parser.parse_args()

    with open('CMakeLists.txt', 'r') as file:
        cmakelist = file.read()

        ver = r'project\(Elona_foobar VERSION (\d+)\.(\d+)\.(\d+)\)'

        ver_match = re.search(ver, cmakelist)

        old_ver = Version(
            int(ver_match.group(1)),
            int(ver_match.group(2)),
            int(ver_match.group(3)))
        new_ver = old_ver.inc(args.mode)

        cmakelist = re.sub(
            ver,
            'project(Elona_foobar VERSION {}.{}.{})'.format(
                new_ver.major, new_ver.minor, new_ver.patch),
            cmakelist)

    if not args.dry_run:
        with open('CMakeLists.txt', 'w') as file:
            file.write(cmakelist)

        cmd = 'git commit -a -m "Increment {} version: {} -> {}"'.format(
            args.mode, old_ver, new_ver)
        subprocess.call(cmd, shell=True)

        print('Elona foobar''s {} version is successfully incremented: {} -> {}'.format(
            args.mode, old_ver, new_ver))
    else:
        print('Elona foobar''s {} version will be incremented: {} -> {}'.format(args.mode, old_ver, new_ver))


if __name__ == '__main__':
    main()
