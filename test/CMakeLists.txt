
include_directories(${BANDIT_INCLUDE_DIR})

set(TEST_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp) 
include(maketest.cmake)


add_subdirectory(geometry)
add_subdirectory(worldtree)
add_subdirectory(property)
add_subdirectory(voxelcluster)


file(GLOB_RECURSE ALL_TEST_FILES
    "*/*.cpp"
)

make_test(all_tests ${ALL_TEST_FILES})