# -----------------------------------------------------------------------------

find_package (Threads)

# -----------------------------------------------------------------------------

#TODO: endianness should not be in Common
# should check in ivl Builder but add a bool Cached variable with ability to 
# change. Then add the cached result somewhere in ivlConfig.cmake.in so that 
# it is passed through by the installer.
INCLUDE(TestBigEndian)

TEST_BIG_ENDIAN(BIGENDIAN)
IF(${BIGENDIAN})
     ADD_DEFINITIONS(-DIVL_BIG_ENDIAN)
ELSE()
     ADD_DEFINITIONS(-DIVL_LITTLE_ENDIAN)
ENDIF(${BIGENDIAN})
ADD_DEFINITIONS(-DIVL_ENDIANNESS_CHECKED)

# -----------------------------------------------------------------------------
