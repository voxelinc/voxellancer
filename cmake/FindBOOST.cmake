
# BOOST_FOUND
# BOOST_INCLUDE_DIR


FIND_PATH(BOOST_INCLUDE_DIR boost/test/included/unit_test.hpp
    ${LIB_DIR}/boost
    $ENV{BOOST_HOME}
    $ENV{BOOST_DIR}
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    DOC "The directory where boost/test/included/unit_test.hpp resides.")
    
IF(BOOST_INCLUDE_DIR)
  SET(BOOST_FOUND 1 CACHE STRING "Set to 1 if BOOST is found, 0 otherwise")
ELSE()
  SET(BOOST_FOUND 0 CACHE STRING "Set to 1 if BOOST is found, 0 otherwise")
  MESSAGE(WARNING "Note: an envvar BOOST_HOME assists this script to locate boost test headers.")
ENDIF()

MARK_AS_ADVANCED(BOOST_FOUND)
