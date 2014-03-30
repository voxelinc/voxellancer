
# GLFW_FOUND
# GLFW_INCLUDE_DIR
# GLFW_LIBRARY
# GLFW_BINARY


find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h
    ${LIB_DIR}/glfw-3.0.3/include
    ${LIB_DIR}/glfw/include
    $ENV{GLFWDIR}/include
    $ENV{GLFW_HOME}/include
    $ENV{PROGRAMFILES}/GLFW/include
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    DOC "The directory where GLFW/glfw3.h resides")

find_library(GLFW_LIBRARY
    NAMES GLFW glfw3 glfw
    PATHS
    ${LIB_DIR}/glfw-3.0.3/lib-msvc110
    ${LIB_DIR}/glfw/lib
    ${LIB_DIR}/glfw/src
    $ENV{GLFWDIR}/lib
    $ENV{GLFW_HOME}/lib
    $ENV{GLFW_HOME}/lib/Release/x64
    /usr/lib64
    /usr/local/lib64
    /sw/lib64
    /opt/local/lib64
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    DOC "The GLFW library")

if(WIN32)
    find_file(GLFW_BINARY
        NAMES glfw3.dll
        PATHS
        ${LIB_DIR}/glfw-3.0.3/lib-msvc110
        $ENV{GLFWDIR}/bin
        $ENV{GLFW_HOME}/bin
        $ENV{GLFW_HOME}/bin/Release/x64
        DOC "The GLFW binary")
endif()
    
if(GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
    set(GLFW_FOUND 1 CACHE STRING "Set to 1 if GLFW is found, 0 otherwise")
else()
    set(GLFW_FOUND 0 CACHE STRING "Set to 1 if GLFW is found, 0 otherwise")
    message(WARNING "Note: an envvar like GLFW_HOME assists this script to locate glfw.")
endif()

mark_as_advanced( GLFW_FOUND )
