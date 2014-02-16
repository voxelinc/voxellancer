# LUA52_FOUND
# LUA52_INCLUDE_DIR
# LUA52_LIBRARY
# LUA52_BINARY


find_path(LUA52_INCLUDE_DIR lua5.2/lua.h
    /usr/include/
    DOC "The directory where lua5.2/lua.h resides")

find_library(LUA52_LIBRARY
    NAMES lua5.2 
    PATHS
    /usr/lib/i386-linux-gnu/
    DOC "The Lua5.2 library")


if(LUA52_INCLUDE_DIR AND LUA52_LIBRARY)
    set(LUA52_FOUND 1 CACHE STRING "Set to 1 if LUA52 is found, 0 otherwise")
else()
    set(LUA52_FOUND 0 CACHE STRING "Set to 1 if LUA52 is found, 0 otherwise")
endif()

mark_as_advanced( LUA52_FOUND )
