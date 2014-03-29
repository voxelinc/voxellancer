"""
generates a documentation of all c++ methods available to lua
"""

try:
    import configparser
except ImportError:
    import ConfigParser as configparser
import argparse
import sys
from collections import defaultdict
import os
import subprocess
import re


def output_api(out, dic):
    """
    @type out: file
    @type dic: dict[str, list]
    """
    for header, values in dic.iteritems():
        out.write("## {0}\n\n".format(header))
        for value in values:
            out.write("    {0}\n".format(value))
        out.write("\n\n")


def output_ini(out, dic):
    """
    @type out: file
    @type dic: dict[str, list]
    """
    for header, values in dic.iteritems():
        out.write("## {0}s\n\n".format(header))
        for value in values:
            out.write(" * {0}\n".format(value))
        out.write("\n\n")


def get_api_methods(folder):
    """
    @type folder: string
    @rtype : dict[str,list]
    """
    callback = lambda pat: " {0}".format(pat.group(1).lower())  # transforms apiFoo to foo

    lines = []
    for root, dirs, files in os.walk(folder):
        for name in files:
            if name.endswith(".h"):
                f = os.path.join(root, name)
                code = file(f).read()
                matches = re.findall(r"[^ ]* api\w*\(.*\);", code)
                lines += [(name, line) for line in matches]

    methods = defaultdict(list)
    for header, line in lines:
        api = re.sub(r"\sapi([A-Z])", callback, line)
        methods[header].append(api)
    return methods


def get_ini_objects(folder):
    """
    @type folder: string
    @rtype : dict[str,list]
    """
    objects = defaultdict(list)

    for root, _, files in os.walk(folder):
        for filename in files:
            if filename.endswith(".ini"):
                config = configparser.ConfigParser()
                config.read(os.path.join(root, filename))
                if config.has_option("general", "type"):
                    object_type = config.get("general", "type")
                    name = filename[:-4]
                    objects[object_type].append(name)
    return objects


def get_color_codes(folder):
    """
    @type folder: string
    @rtype : dict[str, list]
    """
    config = configparser.ConfigParser()
    config.read(os.path.join(folder, "voxels.ini"))

    codes = []
    for section in config.sections():
        if config.has_option(section, "prefix"):
            codes.append("{0}: {1}".format(section, config.get(section, "prefix")))
    return {"colorcodes": codes}


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="this program generates an overview over the available lua bindings. "
                                                 "please call all methods exposed to lua 'api...'!")
    parser.add_argument("root", help="the root dir of voxellancer", default=".", nargs='?', type=str)
    parser.add_argument("output", help="The output file (default=sys.stdout)",
                        default=sys.stdout, nargs='?', type=argparse.FileType('w'))
    args = parser.parse_args()

    api_folder = os.path.abspath(os.path.join(args.root, "src/scripting/bindings"))
    print("Scanning binding folder: {0}".format(api_folder))
    ini_folder = os.path.abspath(os.path.join(args.root, "data"))
    print("Scanning ini folder: {0}".format(ini_folder))

    git_hash = subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD'], cwd=args.root).strip()

    args.output.write("Lua API bindings\n")
    args.output.write("================\n")
    args.output.write("generated from {0}\n\n".format(git_hash))

    api_methods = get_api_methods(api_folder)
    output_api(args.output, api_methods)

    args.output.write("Ini Objects\n")
    args.output.write("===========\n\n")

    ini_objects = get_ini_objects(ini_folder)
    output_ini(args.output, ini_objects)

    color_codes = get_color_codes(ini_folder)
    output_ini(args.output, color_codes)

    if args.output != sys.stdout:
        print("done")
