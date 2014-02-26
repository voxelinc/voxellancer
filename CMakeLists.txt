cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

# PROJECT DESCRIPTION
set(META_PROJECT_NAME "voxellancer")
set(META_VERSION_MAJOR "0")
set(META_VERSION_MINOR "1")
set(META_VERSION_PATCH "0")
set(META_VERSION "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_AUTHOR_ORGANIZATION "voxelinc")
set(META_AUTHOR_DOMAIN "https://github.com/voxelinc/voxellancer/")


# OPTIONS
option(OPTION_LIMIT_CONFIGS "Generate limited configs (Release; Debug)" ON)
option(OPTION_ERRORS_AS_EXCEPTION "Throw exceptions" OFF)
option(OPTION_CREATE_SUB_TEST "Create sub tests" OFF)


# CMAKE CONFIGURATION
set(CMAKE_VERBOSE_MAKEFILE 1)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
# include(GetGitRevisionDescription)
# get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# Generate a shorter, googlelike variation for rev
# string(SUBSTRING ${GIT_SHA1} 0 12 GIT_REV)
# file(WRITE ${CMAKE_BINARY_DIR}/revision ${GIT_REV})


# DEPENDENCIES
# Find externals
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(SFML REQUIRED)
find_package(BANDIT REQUIRED)
find_package(LibOVR REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Lua52 REQUIRED)
find_package(Selene REQUIRED)

if(REGEX_USE_BOOST)
find_package(Boost REQUIRED regex)
endif()

if(OPENMP_FOUND)
    message(STATUS "OpenMP found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(WARNING "OpenMP not found")
endif()

set(GLOW_DIRECTORY glow)
include_directories(${LIB_DIR}/${GLOW_DIRECTORY}/include)
add_subdirectory(${LIB_DIR}/${GLOW_DIRECTORY})


# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    ${BANDIT_INCLUDE_DIR}
    ${LIBOVR_INCLUDE_DIRS}
    ${LUA52_INCLUDE_DIR}
    ${SELENE_INCLUDE_DIR}
)


# Compile voxellancer
set(target voxellancer)

message(STATUS "${target}")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADER_GROUP "Header Files")
set(SOURCE_GROUP "Source Files")
set(SHADER_GROUP "Shader Files")

file(GLOB_RECURSE SRC_FILES
    "src/*.h"
    "src/*.inl"
    "src/*.cpp"
)

set(SRC_FILES_EXCEPT_MAIN ${SRC_FILES})
list(REMOVE_ITEM SRC_FILES_EXCEPT_MAIN ${SRC_DIR}/main.cpp)

file(GLOB_RECURSE SHADER_FILES
    "data/*.vert"
    "data/*.frag"
    "data/*.geo"
)

source_group(${SHADER_GROUP} FILES ${SHADER_FILES})


source_group_by_path_function(${SOURCE_DIR} "\\.h$|\\.hpp$"
    ${HEADER_GROUP} ${SRC_FILES})
source_group_by_path_function(${SOURCE_DIR} "\\.cpp$|\\.c$|\\.inl$"
    ${SOURCE_GROUP} ${SRC_FILES})

add_executable(${target}
    ${SRC_FILES}
    ${SHADER_FILES}
)

add_definitions(-DGLM_FORCE_RADIANS)

set(LIBS_TO_LINK
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    ${SFML_LIBRARIES}
    ${Boost_LIBRARIES}
    ${LIBOVR_LIBRARIES}
    ${LUA52_LIBRARY}
    glow
    glowutils
    ${LIBS_TO_LINK}
)

target_link_libraries(${target}
    ${LIBS_TO_LINK}
)

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE CXX
    COMPILE_DEFINITIONS_DEBUG "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX "d${DEBUG_POSTFIX}"
)

set(BINARIES ${GLEW_BINARY} ${GLFW_BINARY} ${SFML_BINARIES} ${LUA52_BINARY})

if(WIN32)
    foreach( binary ${BINARIES})
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${binary} $<TARGET_FILE_DIR:${target}>)
    endforeach( binary )
endif()

install(TARGETS ${target}
        RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
        DESTINATION .
        PATTERN "*.png" EXCLUDE)
install(FILES ${BINARIES} DESTINATION .)

 set(CPACK_NSIS_CREATE_ICONS "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME}.lnk' '\$INSTDIR\\\\${PROJECT_NAME}.exe'")
 
include(CPack)

include_directories(${SOURCE_DIR})

add_subdirectory(test)

