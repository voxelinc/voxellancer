
set(target voxellancer)
message(STATUS "${target}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB SRC_FILES
    "*.h"
    "*.cpp"
)

file(GLOB SHADER_FILES
    "${DATA_DIR}/*.vert"
    "${DATA_DIR}/*.frag"
)

source_group("Shader Files" FILES ${SHADER_FILES})

add_executable(${target} 
    ${SRC_FILES}
    ${SHADER_FILES}
)

target_link_libraries(${target} 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLOW_LIBRARY}
    ${GLOW_UTILS_LIBRARY}
    ${GLOW_WINDOW_LIBRARY}
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

install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

