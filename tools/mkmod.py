#!/usr/local/bin/python3

import re
import os
from pathlib import Path


class ModManifest:
    def __init__(self, mod_id, version, dir):
        self.mod_id = mod_id
        self.version = version
        self.dir = dir


def is_valid_mod_id(mod_id):
    return re.match('[a-z_][a-z_0-9]*', mod_id)


def is_valid_version(version):
    return re.match('[0-9]+\.[0-9]+\.[0-9]+', version)


def check_working_dir():
    cwd = Path(os.getcwd())
    for filename in ['.git', '.github', 'runtime/mod', 'Makefile']:
        if not (cwd / filename).exists():
            raise ValueError(
                f'This tool must be run in the root directory of Elona foobar')


def query_basic_information():
    mod_id = input('Mod ID: ')
    if not is_valid_mod_id(mod_id):
        raise ValueError(
            f'"{mod_id}" is invalid. A mod ID must be valid as a Lua variable.')

    mod_dir = Path(f'./runtime/mod/{mod_id}')
    if mod_dir.exists():
        raise ValueError(f'"{mod_dir}" already exists.')

    version = input('Version (default: 0.1.0): ')
    if len(version) == 0:
        version = '0.1.0'
    if not is_valid_version(version):
        raise ValueError(
            f'"{version}" cannot be parsed as version.')

    return ModManifest(mod_id, version, mod_dir)


def write_mod_files(manifest):
    manifest.dir.mkdir()

    with open(manifest.dir / 'mod.json', 'w') as f:
        print(f"""{{
  id: "{manifest.mod_id}",
  version: "{manifest.version}",
}}
""", file=f)


def main():
    check_working_dir()
    manifest = query_basic_information()
    write_mod_files(manifest)


if __name__ == '__main__':
    main()
