# - Config file for the ivl-cv package
# It defines the following variables
#  ivl-cv_INCLUDE_DIRS - include directories for ivl-cv
#  ivl-cv_LIBS    - libraries to link against

# Include guard
if(NOT ("${ivl-cv_INCLUDED}" STREQUAL ""))
        return()
else()
        set(ivl-cv_INCLUDED 1)
endif()

# depends
find_package(ivl REQUIRED)
 
# Compute paths
get_filename_component(ivl-cv_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${ivl-cv_CMAKE_DIR}/CMakeCache.txt")
   # In build tree
   include("${ivl-cv_CMAKE_DIR}/ivl-cvBuildTreeSettings.cmake")
else()
    # set(ivl-cv_INCLUDE_DIRS "include")
	# Compute the installation prefix relative to this file.
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
	set(ivl-cv_INCLUDE_DIRS "${_IMPORT_PREFIX}/include")
	set(ivl-cv_LIB_DIR "${_IMPORT_PREFIX}/lib")
endif()

# add the link directory
LINK_DIRECTORIES(${ivl-cv_LIB_DIR})   

# add include directories
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${ivl-cv_INCLUDE_DIRS})

add_definitions("-DIVL_OPENCV")

# Our library dependencies (contains definitions for IMPORTED targets)
include("${ivl-cv_CMAKE_DIR}/ivl-cvLibraryDepends.cmake")
 

