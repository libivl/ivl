###############################################################################

## stdint

FIND_PACKAGE(STDINTIVL REQUIRED)
#include_directories(${STDINTIVL_INCLUDE_DIRS}) done internally

###############################################################################

## pthread

# find_package (Threads REQUIRED)
# moved to common
# TODO: maybe the following should move too, and rename THREAD_LIBRARY to IVL_THREAD_LIBRARY
set(THREAD_LIBRARY "${CMAKE_THREAD_LIBS_INIT}" CACHE STRING "Library for multithreading")
LIST(APPEND LIB_TARGETS "${THREAD_LIBRARY}")
#mark_as_advanced(THREAD_LIBRARY)

###############################################################################

## opencv

FIND_PACKAGE(OpenCV)

IF (OpenCV_FOUND)
MESSAGE(STATUS "OpenCV found")
	IF(OpenCV_VERSION_MAJOR EQUAL 2)
		SET(USE_OPENCV 1 CACHE BOOL "Use OpenCv")
		MESSAGE(STATUS "Using OpenCV version ${OpenCV_VERSION}")
	ELSE(OpenCV_VERSION_MAJOR EQUAL 2)
		MESSAGE(WARNING "OpenCV version is not supported. Please use OpenCV 2.0 or greater.")
	ENDIF(OpenCV_VERSION_MAJOR EQUAL 2)
ENDIF(OpenCV_FOUND)
IF(USE_OPENCV)
	MESSAGE(STATUS "OpenCV support is enabled")
ELSE(USE_OPENCV)
	MESSAGE(STATUS "OpenCV support is disabled")
	ADD_DEFINITIONS(-DNO_OPENCV)
ENDIF(USE_OPENCV)

###############################################################################

## lapack

FIND_PACKAGE(clapack QUIET)

IF(clapack_FOUND)
	SET (USE_LAPACK 1 CACHE BOOL "Use lapack")
	set (LAPACK_TARGETS ${clapack_LIBS})
	set (LAPACKIVL_INCLUDE_DIRS ${clapack_INCLUDE_DIRS})
	set (LAPACKIVL_LIBS ${clapack_LIBS})
ELSE(clapack_FOUND)
	set (clapack_DIR CACHE INTERNAL "")
	#set (LAPACK_TARGETS lapack)

	FIND_LIBRARY(LAPACK_PATH lapack)
	string(COMPARE NOTEQUAL "${LAPACK_PATH}" "LAPACK_PATH-NOTFOUND" WASFOUND)
	if(WASFOUND)
		get_filename_component(LAPACKIVL_LIB_DIR "${LAPACK_PATH}" PATH)
		set (LAPACK_TARGETS "-L${LAPACKIVL_LIB_DIR} -llapack")
		SET (USE_LAPACK 1 CACHE BOOL "Use lapack")
		set (LAPACKIVL_INCLUDE_DIRS)
		set (LAPACKIVL_LIBS ${LAPACK_TARGETS})
	else(WASFOUND)
		FIND_PACKAGE(LAPACKIVL)
		IF(LAPACKIVL_FOUND)
			set (LAPACK_TARGETS ${LAPACKIVL_LIBS})
			SET (USE_LAPACK 1 CACHE BOOL "Use lapack")
		ELSE(LAPACKIVL_FOUND)
			set (lapack_not_found 1)
			set (use_lapack 0 CACHE INTERNAL "")
		endif(LAPACKIVL_FOUND)
	ENDIF(WASFOUND)
ENDIF(clapack_FOUND)
IF(USE_LAPACK)
	MESSAGE(STATUS "Lapack support is enabled")
ELSE(USE_LAPACK)
	MESSAGE(STATUS "Lapack support is disabled")
	ADD_DEFINITIONS(-DNO_LAPACK)
ENDIF(USE_LAPACK)

###############################################################################

## Qt

SET(SEARCH_FOR_QT 1 CACHE BOOL "Search for Qt package")

IF(SEARCH_FOR_QT)

find_package(Qt4)

IF(QT_USE_FILE)
	MESSAGE(STATUS "Qt4 found")
	SET(USE_QT 1 CACHE BOOL "Use Qt")
	MESSAGE(STATUS "Using Qt version ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
ENDIF(QT_USE_FILE)

IF(USE_QT)
	MESSAGE(STATUS "Qt support is enabled")
ELSE(USE_QT)
	MESSAGE(STATUS "Qt support is disabled")
	ADD_DEFINITIONS(-DNO_QT)
ENDIF(USE_QT)

ENDIF(SEARCH_FOR_QT)

###############################################################################

