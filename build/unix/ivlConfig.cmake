# - Config file for the ivl package
# It defines the following variables
#  ivl_INCLUDE_DIRS - include directories for ivl
#  ivl_LIBS    - libraries to link against

# Include guard
if(NOT ("${ivl_INCLUDED}" STREQUAL ""))
        return()
else()
	set(ivl_INCLUDED 1)
endif()

# Compute paths
get_filename_component(ivl_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${ivl_CMAKE_DIR}/CMakeCache.txt")
   # In build tree
   include("${ivl_CMAKE_DIR}/ivlBuildTreeSettings.cmake")
else()
    # set(ivl_INCLUDE_DIRS "include")
	# Compute the installation prefix relative to this file.
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
	GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
	set(ivl_INCLUDE_DIRS "${_IMPORT_PREFIX}/include")
	set(ivl_LIB_DIR "${_IMPORT_PREFIX}/lib")
endif()

# add the link directory
LINK_DIRECTORIES(${ivl_LIB_DIR})

set(ivl_INCLUDE_DIR "${ivl_INCLUDE_DIRS}") # it is only one in our case. keep it for stdint

# Help windows find the rest ivl modules, if installed at the same directory
if(WIN32 AND NOT CYGWIN)
	set(ivl-cv_DIR ${ivl_CMAKE_DIR})
	set(ivl-lina_DIR ${ivl_CMAKE_DIR})
endif()

# -----------------------------------------------------------------------

# prerequisites, used by the library

include("${ivl_CMAKE_DIR}/ivlCommon.cmake")

# Dependency include directories

# stdint relative path, if used.
if(NOT ("" STREQUAL ""))
	list(APPEND ivl_INCLUDE_DIRS "${ivl_INCLUDE_DIR}/")
endif()

# -----------------------------------------------------------------------

# include the ivl directories
include_directories(${ivl_INCLUDE_DIRS})


# set flags
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
        ADD_DEFINITIONS(-D_DEBUG)
ENDIF()

IF(MSVC)
	ADD_DEFINITIONS("/EHsc")
ENDIF()



# Our library dependencies (contains definitions for IMPORTED targets)
include("${ivl_CMAKE_DIR}/ivlLibraryDepends.cmake")


 
