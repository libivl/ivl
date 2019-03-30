# - Config file for the ivl-lina package
# It defines the following variables
#  ivl-lina_INCLUDE_DIRS - include directories for ivl-lina
#  ivl-lina_LIBS    - libraries to link against

# Include guard
if(NOT ("${ivl-lina_INCLUDED}" STREQUAL ""))
        return()
else()
        set(ivl-lina_INCLUDED 1)
endif()

# depends
find_package(ivl REQUIRED)
 
# Compute paths
get_filename_component(ivl-lina_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${ivl-lina_CMAKE_DIR}/CMakeCache.txt")
   # In build tree
   include("${ivl-lina_CMAKE_DIR}/ivl-linaBuildTreeSettings.cmake")
else()
    # set(ivl-lina_INCLUDE_DIRS "include")
	# Compute the installation prefix relative to this file.
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
	set(ivl-lina_INCLUDE_DIRS "${_IMPORT_PREFIX}/include")
	set(ivl-lina_LIB_DIR "${_IMPORT_PREFIX}/lib")
endif()

# add the link directory
LINK_DIRECTORIES(${ivl-lina_LIB_DIR})

# Add dependency include directories
if(NOT ("" STREQUAL ""))
	include_directories("")
endif()

include_directories(${ivl-lina_INCLUDE_DIRS})


# find LAPACK
include("${ivl-lina_CMAKE_DIR}/lapack_include.cmake")
if(lapack_not_found)
	message("Lapack library not found")
endif()

 
# Our library dependencies (contains definitions for IMPORTED targets)
include("${ivl-lina_CMAKE_DIR}/ivl-linaLibraryDepends.cmake")
 
# These are IMPORTED targets created by ivl-linaLibraryDepends.cmake
#set(IVL_LIBRARIES ivl)

