FIND_PATH(SELENE_INCLUDE_DIR selene.h
    ${LIB_DIR}/selene/include
    DOC "The directory where selene.h resides.")
    
IF(SELENE_INCLUDE_DIR)
  SET(SELENE_FOUND 1 CACHE STRING "Set to 1 if SELENE is found, 0 otherwise")
ELSE()
  SET(SELENE_FOUND 0 CACHE STRING "Set to 1 if SELENE is found, 0 otherwise")
ENDIF()

MARK_AS_ADVANCED(SELENE_FOUND)
