#!/usr/local/bin/python3

from argparse import ArgumentParser
from pathlib import Path
import re



# /// @putit
STRUCT_MAGIC_COMMENT_PATTERN = re.compile(r"^/// @putit$")

#     /// @putit
FIELD_MAGIC_COMMENT_PATTERN = re.compile(r"^ +/// @putit$")

# struct Struct
# class Class
DEFINE_STRUCT_PATTERN = re.compile(r"^(?:struct|class) (\w+)$")

# type var;
# type var = value;
DEFINE_FIELD_PATTERN = re.compile(r"^ +([^= ][^=]*) (\w+)(?: = .*|{})?;$")

# #include "foo"
INCLUDE_PATTERN = re.compile(r'^#include "(.*)"$')



class StructInfo:
    def __init__(self, name, original_filepath):
        self.name = name
        self._original_filepath = original_filepath
        self.fields = []

    def define_field(self, field):
        self.fields.append(field)

    def include_filename(self, filename):
        self.filename = (Path(self._original_filepath).parent / filename).resolve()

    def __str__(self):
        return f"struct {self.name} {{ {', '.join(self.fields)} }} {self.filename}"

    def dump(self):
        parent_dir = self.filename.parent
        if not parent_dir.exists():
            parent_dir.mkdir(parents=True)

        with open(self.filename, "w") as file:
            file.write(f"""/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{{
""")
            for field in self.fields:
                file.write(f"    _putit_archive_(this->{field});")
                file.write("\n")
            file.write("""}
/* clang-format on */
""")



def iterate_all_headers():
    # /path/to/elonafoobar/src/putit
    this_file_dir = Path(__file__).parent.resolve()
    # /path/to/elonafoobar/src/elona
    source_root_dir = this_file_dir.parent / "elona"
    # Iterate all C++ header files under elona folder.
    for filepath in source_root_dir.glob("**/*.hpp"):
        yield filepath



def make_argparser():
    p = ArgumentParser(description='Generate serializer from magic comments.')
    return p



def main():
    parser = make_argparser()
    args = parser.parse_args()

    struct_table = []
    for filepath in iterate_all_headers():
        # Open the header file.
        print(f"Processing {filepath}...", end="")
        with open(filepath, 'r') as file:
            # Iterate each line.
            will_define_struct = False
            will_define_field = False
            will_include_impl = False
            for line in file.readlines():
                if will_define_struct:
                    will_define_struct = False
                    match = DEFINE_STRUCT_PATTERN.match(line)
                    name = match.group(1)
                    struct_table.append(StructInfo(name, filepath))
                    will_include_impl = True
                elif will_define_field:
                    will_define_field = False
                    match = DEFINE_FIELD_PATTERN.match(line)
                    name = match.group(2)
                    struct_table[-1].define_field(name)
                elif STRUCT_MAGIC_COMMENT_PATTERN.match(line):
                    will_define_struct = True
                elif FIELD_MAGIC_COMMENT_PATTERN.match(line):
                    will_define_field = True
                elif will_include_impl:
                    match = INCLUDE_PATTERN.match(line)
                    if match:
                        filename = match.group(1)
                        struct_table[-1].include_filename(filename)
        print("Done")

    for struct in struct_table:
        struct.dump()
        print(f"{struct.name}'s serializer has successfully been generated.")



if __name__ == '__main__':
    main()
