from glob import glob
import re

require_pattern = re.compile(r'\brequire\("(.*)"\)')

print("digraph require_graph {")

for path in glob("**/*.lua", recursive=True):
    with open(path) as f:
        caller = path.replace(".lua", "").replace("/", ".")
        caller_node = caller.replace(".", "__")
        print(f"  {caller_node} [label=\"{caller}\"];")
        for line in f.readlines():
            match = require_pattern.search(line)
            if match:
                calee = match.group(1)
                calee_node = calee.replace(".", "__")
                print(f"  {caller_node} -> {calee_node};")

print("}")
