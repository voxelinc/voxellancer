
include_directories(${BANDIT_INCLUDE_DIR})

set(TEST_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
              ${CMAKE_CURRENT_SOURCE_DIR}/bandit_extension/vec3helper.cpp) 
include(maketest.cmake)

if(${OPTION_CREATE_SUB_TEST})
    add_subdirectory(ai)
    add_subdirectory(geometry)
    add_subdirectory(worldtree)
    add_subdirectory(damageforwarder)
    add_subdirectory(property)
    add_subdirectory(voxelcluster)
    add_subdirectory(voxeltree)
    add_subdirectory(collision)
    add_subdirectory(loader)
    add_subdirectory(worldobject)
    add_subdirectory(worldtransform)
    add_subdirectory(splitting)
endif()

add_subdirectory(perftest)


file(GLOB_RECURSE ALL_TEST_FILES
    "*/*.cpp"
)
list(REMOVE_ITEM ALL_TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/perftest//testperformance.cpp)


make_test(all_tests ${ALL_TEST_FILES})
