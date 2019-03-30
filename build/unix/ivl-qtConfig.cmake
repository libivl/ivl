# - Config file for the ivl-qt package
# It defines the following variables
#  ivl-qt_INCLUDE_DIRS - include directories for ivl-qt
#  ivl-qt_LIBS    - libraries to link against

# Include guard
if(NOT ("${ivl-qt_INCLUDED}" STREQUAL ""))
        return()
else()
        set(ivl-qt_INCLUDED 1)
endif()

# depends
find_package(ivl REQUIRED)
 
# Compute paths
get_filename_component(ivl-qt_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${ivl-qt_CMAKE_DIR}/CMakeCache.txt")
   # In build tree
   include("${ivl-qt_CMAKE_DIR}/ivl-qtBuildTreeSettings.cmake")
else()
    # set(ivl-qt_INCLUDE_DIRS "include")
	# Compute the installation prefix relative to this file.
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
	set(ivl-qt_INCLUDE_DIRS "${_IMPORT_PREFIX}/include")
	set(ivl-qt_LIB_DIR "${_IMPORT_PREFIX}/lib")
endif()

# add the link directory
LINK_DIRECTORIES(${ivl-qt_LIB_DIR})   

# add include directories
find_package(Qt4)

include(${QT_USE_FILE})

add_definitions("-DIVL_QT")
add_definitions(-DQT_NO_DEBUG)

# Our library dependencies (contains definitions for IMPORTED targets)
include("${ivl-qt_CMAKE_DIR}/ivl-qtLibraryDepends.cmake")
 

