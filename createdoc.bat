@echo off
python tools/compilemarkdown.py  doc/1_howto.md doc/howto.html
python tools/generateluadoc.py . doc/2_luaapi.md
python tools/compilemarkdown.py doc/2_luaapi.md doc/luaapi.html
pause