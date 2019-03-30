# add include file stdint.h

#check_include_files(
#CHECK_INCLUDE_FILES("stdint.h"    CMAKE_HAVE_STDINT_H)

INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
CHECK_INCLUDE_FILE("stdint.h"    CMAKE_HAVE_STDINT_H)

set (STDINTIVL_FOUND TRUE)

if(CMAKE_HAVE_STDINT_H)
	set (STDINTIVL_INCLUDE_DIRS_)
	#set (STDINTIVL_DIR_ "/")
	set (STDINTIVL_DIR_ "${IVL_INCLUDE_DIR}")
	set (USE_STDINTIVL 0)
else(CMAKE_HAVE_STDINT_H)
	#set (STDINTIVL_INCLUDE_DIRS_ "${IVL_DIR}/include/ivl/details/depends/stdint")
	set (STDINTIVL_DIR_ "${IVL_INCLUDE_DIR}")
	set (USE_STDINTIVL 1)
endif(CMAKE_HAVE_STDINT_H)

set (STDINT_FROM_IVL ${USE_STDINTIVL} CACHE BOOL "Search for stdint.h in ivl")

if(STDINT_FROM_IVL)
	set (STDINTIVL_RELATIVE_DIR "ivl/details/depends/stdint")
	set (STDINTIVL_INSTALL_CFLAGS "-I ${INSTALL_INCLUDE_DIR}/ivl/details/depends/stdint")
	set (STDINTIVL_INCLUDE_DIRS "${IVL_INCLUDE_DIR}/${STDINTIVL_RELATIVE_DIR}")
	include_directories(${STDINTIVL_INCLUDE_DIRS})
else(STDINT_FROM_IVL)
	set (STDINTIVL_RELATIVE_DIR "")
	set (STDINTIVL_INSTALL_CFLAGS "")
	set (STDINTIVL_INCLUDE_DIRS)
endif(STDINT_FROM_IVL)

#
#include_directories(${STDINTIVL_INCLUDE_DIRS})

#set (STDINTIVL_INCLUDE_DIRS ${STDINTIVL_INCLUDE_DIRS_} CACHE PATH "Additional path to include stdint from")
#set (STDINTIVL_DIR ${STDINTIVL_DIR_} CACHE PATH "stdintivl package directory")

#set (STDINTIVL_INCLUDES "${STDINTIVL_INCLUDE_DIRS}")

