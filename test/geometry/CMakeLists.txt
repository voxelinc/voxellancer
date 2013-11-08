
add_executable(test_aabb
	testaabb.cpp	
	${SRC_FILES_EXCEPT_MAIN}
)


target_link_libraries(test_aabb
	${LIBS_TO_LINK}
)
