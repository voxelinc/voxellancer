cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)


# PROJECT DESCRIPTION

set(META_PROJECT_NAME        "voxellancer")
set(META_VERSION_MAJOR       "0")
set(META_VERSION_MINOR       "1")
set(META_VERSION_PATCH       "0")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_AUTHOR_ORGANIZATION "voxelinc")
set(META_AUTHOR_DOMAIN       "https://github.com/voxelinc/voxellancer/")


# OPTIONS

option(OPTION_LIMIT_CONFIGS  "Generate limited configs (Release; Debug)" ON)
option(OPTION_LOCAL_INSTALL  "Install to a local directory instead of the system" OFF)
option(OPTION_ERRORS_AS_EXCEPTION "Throw exceptions" OFF)


# CMAKE CONFIGURATION
set(CMAKE_VERBOSE_MAKEFILE 1)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Include cmake modules from ./cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Set configuration types
if(OPTION_LIMIT_CONFIGS)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited Configs" FORCE)
endif()

# Project
project(${META_PROJECT_NAME} C CXX)


# Generate folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Include custom cmake functions
include(cmake/Custom.cmake)


# PLATFORM AND ARCHITECTURE

# Architecture (32/64 bit)
set(X64 OFF)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(X64 ON)
endif()

# Check for linux
if(UNIX AND NOT APPLE)
    set(LINUX 1)
endif()

# Setup platform specifics (compile flags, etc., ...)
if(MSVC)
    message(STATUS "Configuring for platform Windows/MSVC.")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformWindowsMSVC.cmake)
elseif(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Configuring for platform Windows/GCC.")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformWindowsGCC.cmake)
elseif(LINUX AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Configuring for platform Linux/GCC.")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformLinuxGCC.cmake)
elseif(APPLE)
    message(STATUS "Configuring for platform MacOS.")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformMacOS.cmake)
else()
    # Unsupported system/compiler
    message(WARNING "Unsupported platform/compiler combination")
endif()

# GET REPOSITORY VERSION

# Add a revision file containing the git-head tag for cpack and install
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# Generate a shorter, googlelike variation for rev
string(SUBSTRING ${GIT_SHA1} 0 12 GIT_REV)
file(WRITE ${CMAKE_BINARY_DIR}/revision ${GIT_REV})

# DEPENDENCIES

# Find externals
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(FMOD REQUIRED)


set(GLOW_DIRECTORY glow)
include_directories(${LIB_DIR}/${GLOW_DIRECTORY}/include)
add_subdirectory(${LIB_DIR}/${GLOW_DIRECTORY})


# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${FMOD_INCLUDE_DIR}
)

set(target voxellancer)

message(STATUS "${target}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB_RECURSE SRC_FILES
    "source/*.h"
    "source/*.cpp"
)

set(SRC_FILES_EXCEPT_MAIN ${SRC_FILES})
list(REMOVE_ITEM SRC_FILES_EXCEPT_MAIN ${SRC_DIR}/main.cpp)

file(GLOB SHADER_FILES
    "data/*.vert"
    "data/*.frag"
)

source_group("Shader Files" FILES ${SHADER_FILES})

add_executable(${target} 
    ${SRC_FILES}
    ${SHADER_FILES}
)

set(LIBS_TO_LINK
	${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    ${FMOD_LIBRARY}
    glow
    glowutils
)

if(UNIX)
	set(LIBS_TO_LINK ${LIBS_TO_LINK} pthread Xxf86vm X11 Xrandr Xi )
endif()

target_link_libraries(${target} 
    ${LIBS_TO_LINK}
)



set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE CXX
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
)

set(BINARIES ${GLEW_BINARY} ${GLFW_BINARY} ${FMOD_BINARY})

if(WIN32)
    foreach( binary ${BINARIES})
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${binary} $<TARGET_FILE_DIR:${target}>)
    endforeach( file_i )   
endif()

install(TARGETS ${target} 
        RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data 
        DESTINATION . 
        PATTERN "*.png" EXCLUDE)
install(FILES ${BINARIES} DESTINATION .)

 set(CPACK_NSIS_CREATE_ICONS "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME}.lnk' '\$INSTDIR\\\\${PROJECT_NAME}.exe'") 
 
include(CPack)

include_directories(${SRC_DIR})

add_subdirectory(test)
