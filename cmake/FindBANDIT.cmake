# BANDIT_FOUND
# BANDIT_INCLUDE_DIR


FIND_PATH(BANDIT_INCLUDE_DIR bandit/bandit.h
    ${LIB_DIR}/bandit
    ${LIB_DIR}/bandit-1.1.4
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    DOC "The directory where bandit/bandit.h resides.")
    
IF(BANDIT_INCLUDE_DIR)
  SET(BANDIT_FOUND 1 CACHE STRING "Set to 1 if BANDIT is found, 0 otherwise")
ELSE()
  SET(BANDIT_FOUND 0 CACHE STRING "Set to 1 if BANDIT is found, 0 otherwise")
ENDIF()

MARK_AS_ADVANCED(BANDIT_FOUND)
