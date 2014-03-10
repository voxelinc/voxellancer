import argparse
import os
import subprocess
import re
import sys

parser = argparse.ArgumentParser(description="this program generates an overview over the available lua bindings. "
                                             "please call all methods exposed to lua 'api...'!")
parser.add_argument("folder", help="the folder with bindings", type=str)
parser.add_argument("output", help="The output file (default=sys.stdout)",
                    default=sys.stdout, nargs='?', type=argparse.FileType('w'))
args = parser.parse_args()

folder = os.path.abspath(args.folder)
print "Scanning folder: {0}".format(folder)

out = subprocess.check_output(["grep", r"api.*\(.*\);", "*.h",  "-H"], cwd=folder)

git_hash = subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD'])

args.output.write("#Lua API bindings\n")
args.output.write("generated from {0}\n\n".format(git_hash))


def callback(pat):
    return " {0}".format(pat.group(1).lower())

old_header = None
for line in out.splitlines():
    line = re.sub(r"\sapi([A-Z])", callback, line)
    header, api = re.split(":\s+", line)
    if old_header != header:
        if old_header is not None:
            args.output.write("```\n")
        args.output.write("## {0}\n".format(header))
        args.output.write("```c\n")
        old_header = header
    args.output.write("{0}\n".format(api))

if old_header is not None:
    args.output.write("```\n")
print "done"