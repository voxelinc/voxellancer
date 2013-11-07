add_executable(test_worldtreenode
	testworldtreenode.cpp
	${SRC_FILES_EXCEPT_MAIN}
)

target_link_libraries(test_worldtreenode
    ${LIBS_TO_LINK}
)
