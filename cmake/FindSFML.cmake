
# SFML_FOUND
# SFML_INCLUDE_DIR
# SFML_LIBRARY
# SFML_BINARY


find_path(SFML_INCLUDE_DIR SFML/Audio.hpp
    ${LIB_DIR}/SFML-2.1/include
    DOC "The directory where SFML/Audio.hpp resides")

find_library(SFML_LIBRARY
    NAMES SFML sfml-system
    PATHS
    ${LIB_DIR}/SFML-2.1/lib
    ${LIB_DIR}/SFML-2.1/lib/Release
    DOC "The SFML library")

find_library(SFML_LIBRARY_AUDIO
    NAMES SFML sfml-audio
    PATHS
    ${LIB_DIR}/SFML-2.1/lib
    ${LIB_DIR}/SFML-2.1/lib/Release
    DOC "The SFML Audio library")

if(WIN32)
    find_library(SFML_D_LIBRARY
        NAMES SFML sfml-system-d
        PATHS
        ${LIB_DIR}/SFML-2.1/lib/Debug
        DOC "The SFML library (debug)")

    find_library(SFML_D_LIBRARY_AUDIO
        NAMES SFML sfml-audio-d
        PATHS
        ${LIB_DIR}/SFML-2.1/lib/Debug
        DOC "The SFML Audio library (debug)")
    set(SFML_LIBRARIES 
        optimized ${SFML_LIBRARY} optimized ${SFML_LIBRARY_AUDIO}
        debug ${SFML_D_LIBRARY} debug ${SFML_D_LIBRARY_AUDIO})
else()
    set(SFML_LIBRARIES ${SFML_LIBRARY} ${SFML_LIBRARY_AUDIO})
endif()

if(WIN32)
    find_file(SFML_BINARY
        NAMES sfml-system-2.dll
        PATHS ${LIB_DIR}/SFML-2.1/lib/Release
        DOC "The SFML binary")
    find_file(SFML_BINARY_AUDIO
        NAMES sfml-audio-2.dll
        PATHS ${LIB_DIR}/SFML-2.1/lib/Release
        DOC "The SFML Audio binary")
    find_file(SFML_D_BINARY
        NAMES sfml-system-d-2.dll
        PATHS ${LIB_DIR}/SFML-2.1/lib/Debug
        DOC "The SFML binary (debug)")
    find_file(SFML_D_BINARY_AUDIO
        NAMES sfml-audio-d-2.dll
        PATHS ${LIB_DIR}/SFML-2.1/lib/Debug
        DOC "The SFML Audio binary (debug)")
    find_file(OPENAL_BINARY
        NAMES openal32.dll
        PATHS ${LIB_DIR}/SFML-2.1/extlibs/bin/x64
        NO_SYSTEM_ENVIRONMENT_PATH 
        DOC "The OpenAL binary")
    find_file(SNDFILE_BINARY
        NAMES libsndfile-1.dll
        PATHS ${LIB_DIR}/SFML-2.1/extlibs/bin/x64
        DOC "The libsndfile binary")
    set(SFML_BINARIES ${SFML_BINARY} ${SFML_BINARY_AUDIO} ${OPENAL_BINARY} ${SNDFILE_BINARY})
    set(SFML_BINARIES ${SFML_BINARIES} ${SFML_D_BINARY} ${SFML_D_BINARY_AUDIO})
endif()

    
if(SFML_INCLUDE_DIR AND SFML_LIBRARY)
    set(SFML_FOUND 1 CACHE STRING "Set to 1 if SFML is found, 0 otherwise")
else()
    set(SFML_FOUND 0 CACHE STRING "Set to 1 if SFML is found, 0 otherwise")
    message(WARNING "Note: an envvar like SFML_HOME assists this script to locate sfml.")
endif()

mark_as_advanced( SFML_FOUND )
