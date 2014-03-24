
"""
generates a documentation of all c++ methods available to lua
"""

import ConfigParser
import argparse
import sys
from collections import defaultdict
import os
import subprocess
import re


def output_api(out, dic):
    """
    @type out: file
    @type dic: dict[str, str]
    """
    for header, values in dic.iteritems():
        out.write("## {0}\n\n".format(header))
        for value in values:
            out.write("    {0}\n".format(value))
        out.write("\n\n")


def output_ini(out, dic):
    """
    @type out: file
    @type dic: dict[str, str]
    """
    for header, values in dic.iteritems():
        out.write("## {0}s\n\n".format(header))
        for value in values:
            out.write(" * {0}\n".format(value))
        out.write("\n\n")


def get_api_methods(folder):
    """
    @type folder: string
    """
    callback = lambda pat: " {0}".format(pat.group(1).lower())  # transforms apiFoo to foo

    methods = defaultdict(list)
    out = subprocess.check_output(["grep", r"api.*\(.*\);", "*.h",  "-H"], cwd=folder)

    for line in out.splitlines():
        line = re.sub(r"\sapi([A-Z])", callback, line)
        header, api = re.split(":\s+", line)
        methods[header].append(api)
    return methods


def get_ini_objects(folder):
    """
    @type folder: string
    """
    objects = defaultdict(list)

    for root, _, files in os.walk(folder):
        for filename in files:
            if filename.endswith(".ini"):
                config = ConfigParser.ConfigParser()
                config.read(os.path.join(root, filename))
                if config.has_option("general", "type"):
                    type = config.get("general", "type")
                    name = filename[:-4]
                    objects[type].append(name)
    return objects

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="this program generates an overview over the available lua bindings. "
                                                 "please call all methods exposed to lua 'api...'!")
    parser.add_argument("root", help="the root dir of voxellancer", default="..", nargs='?', type=str)
    parser.add_argument("output", help="The output file (default=sys.stdout)",
                        default=sys.stdout, nargs='?', type=argparse.FileType('w'))
    args = parser.parse_args()

    api_folder = os.path.abspath(os.path.join(args.root, "src/scripting/bindings"))
    print "Scanning binding folder: {0}".format(api_folder)
    ini_folder = os.path.abspath(os.path.join(args.root, "data"))
    print "Scanning ini folder: {0}".format(ini_folder)

    git_hash = subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD']).strip()

    args.output.write("Lua API bindings\n")
    args.output.write("================\n")
    args.output.write("generated from {0}\n\n".format(git_hash))

    api_methods = get_api_methods(api_folder)
    output_api(args.output, api_methods)

    args.output.write("Ini Objects\n")
    args.output.write("===========\n\n")

    ini_objects = get_ini_objects(ini_folder)
    output_ini(args.output, ini_objects)


    if args.output != sys.stdout:
        print "done"
