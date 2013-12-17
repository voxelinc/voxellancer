
include_directories(${BANDIT_INCLUDE_DIR})

set(TEST_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
              ${CMAKE_CURRENT_SOURCE_DIR}/bandit_extension/vec3helper.cpp) 
include(maketest.cmake)

if(${OPTION_CREATE_SUB_TEST})
    add_subdirectory(geometry)
    add_subdirectory(worldtree)
    add_subdirectory(damageforwarder)
    add_subdirectory(property)
    add_subdirectory(voxelcluster)
    add_subdirectory(voxeltree)
    add_subdirectory(collision)
    add_subdirectory(loader)
    add_subdirectory(worldobject)
    add_subdirectory(splitting)
    add_subdirectory(perftest)
endif()


file(GLOB_RECURSE ALL_TEST_FILES
    "*/*.cpp"
)

make_test(all_tests ${ALL_TEST_FILES})
