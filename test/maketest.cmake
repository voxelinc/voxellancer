macro(make_test TEST_TARGET) #TEST_FILES is second argument!
        
    set(TEST_FILES ${ARGV})
    list(REMOVE_AT TEST_FILES 0)
    
    source_group("Tests" FILES ${TEST_FILES} ${TEST_MAIN})

    source_group_by_path_function(${SOURCE_DIR} "\\.h$|\\.hpp$"
    ${HEADER_GROUP} ${SRC_FILES_EXCEPT_MAIN})
    source_group_by_path_function(${SOURCE_DIR} "\\.cpp$|\\.c$|\\.inl$"
    ${SOURCE_GROUP} ${SRC_FILES_EXCEPT_MAIN})

    add_executable(${TEST_TARGET}
        ${TEST_MAIN}
        ${TEST_FILES}
        ${SRC_FILES_EXCEPT_MAIN}
    )
    SET_PROPERTY(TARGET ${TEST_TARGET} PROPERTY FOLDER "UnitTest")

    target_link_libraries(${TEST_TARGET}
        ${LIBS_TO_LINK}
    )

    set_target_properties(${TEST_TARGET}
        PROPERTIES
        LINKER_LANGUAGE CXX
        COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
        COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
        COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
        LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
        LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
        DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    )

endmacro()