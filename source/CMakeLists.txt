
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
    glow
    glowutils
    glowwindow
    ${FMOD_LIBRARY}
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

if(WIN32)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_BINARY} $<TARGET_FILE_DIR:${target}>)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${FMOD_BINARY} $<TARGET_FILE_DIR:${target}>)    
endif()

install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

