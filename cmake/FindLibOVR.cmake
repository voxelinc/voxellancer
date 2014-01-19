
# LIBOVR_FOUND
# LIBOVR_INCLUDE_DIR
# LIBOVR_LIBRARY


find_path(LIBOVR_INCLUDE_DIR OVR.h
    ${LIB_DIR}/OculusSDK/LibOVR/Include
    DOC "The directory where OVR.h resides")

find_library(LIBOVR_LIBRARY
    NAMES ovr libovr64
    PATHS
    ${LIB_DIR}/OculusSDK/LibOVR/Lib/x64
    DOC "The LIBOVR library")

    
if(LIBOVR_FOUND_INCLUDE_DIR AND LIBOVR_FOUND_LIBRARY)
    set(LIBOVR_FOUND 1 CACHE STRING "Set to 1 if LIBOVR_FOUND is found, 0 otherwise")
else()
    set(LIBOVR_FOUND 0 CACHE STRING "Set to 1 if LIBOVR_FOUND is found, 0 otherwise")
endif()

set(LIBOVR_LIBRARIES ${LIBOVR_LIBRARY})
set(LIBOVR_INCLUDE_DIRS ${LIBOVR_INCLUDE_DIR})

if(LINUX) 
    set(LIBOVR_LIBRARIES
        ${LIBOVR_LIBRARIES}
        Xinerama
        udev
    )
endif()

if(WIN32) 
    set(LIBOVR_LIBRARIES
        ${LIBOVR_LIBRARIES}
        winmm
    )
endif()

mark_as_advanced( LIBOVR_FOUND )
