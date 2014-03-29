"""
convert markdown to styled html

requires markdown2
"""

import argparse
import markdown2
from pkg_resources import resource_filename
import re

template = """<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
  <!-- generated from {filename} -->
  <head>
    <title>{title}</title>
    <style>
    {css}
    </style>
  </head>
  <body>
    {content}
  </body>
</html>
"""

parser = argparse.ArgumentParser(description="this program converts markdown to nice html. ")
parser.add_argument("markdown", help="the markdown file", type=argparse.FileType("r"))
parser.add_argument("html", help="the html output", type=argparse.FileType("w"))
args = parser.parse_args()

css = open(resource_filename(__name__, "markdown.css")).read()
content = markdown2.markdown(args.markdown.read())
title = re.search(r"<h1>(.*?)<\/h1>", content).group(1)

html = template.format(title=title, css=css, content=content, filename=args.markdown.name)
args.html.write(html)

print("{0} compiled".format(args.markdown.name))