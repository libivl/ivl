cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0012 NEW)

# setup the custom cmake modules path
set(IVL_CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
set(IVL_CMAKE_COMMON_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${IVL_CMAKE_MODULE_PATH}")
include("${IVL_CMAKE_MODULE_PATH}/macro.cmake") #include useful macros

SET_DEFAULT_CONFIG(Release) # need to be done before project

## -----------------------------------------------------------------------

# Start of the project
project(ivl)

# Version info
# ----------------------------------------------------------------------------
#  Get actual version number from sources
# ----------------------------------------------------------------------------
SET(IVL_VERSION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/include/ivl/version.hpp")
FILE(STRINGS "${IVL_VERSION_FILE}" IVL_VERSION_PARTS REGEX "#define[ ]+IVL_VERSION_[A-Z]+[ ]+[0-9]+" )
foreach(V MAJOR MINOR PATCH)
	string(REGEX REPLACE ".+IVL_VERSION_${V}[ ]+([0-9]+).*" "\\1" IVL_${V}_VERSION "${IVL_VERSION_PARTS}")
endforeach(V)

# version macros
set(IVL_VERSION ${IVL_MAJOR_VERSION}.${IVL_MINOR_VERSION}.${IVL_PATCH_VERSION})
set(ivl_VERSION ${IVL_VERSION})
set(ivl_MAJOR_VERSION ${IVL_MAJOR_VERSION})
set(ivl_MINOR_VERSION ${IVL_MINOR_VERSION})
set(ivl_PATCH_VERSION ${IVL_PATCH_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${IVL_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${IVL_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${IVL_PATCH_VERSION})


# setup certain ivl dirs 
set(ivl_BUILD TRUE) # needed by samples
set(ivl_DIR "${CMAKE_SOURCE_DIR}") 
set(IVL_PREFIX_DIR "${CMAKE_SOURCE_DIR}")
set(IVL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include") # needed by stdintivl

# setup installation directories. sets absolute INSTALL_*_DIR paths.
include("${IVL_CMAKE_MODULE_PATH}/setup_dirs.cmake")

# setup external libraries that are required. (stdintivl needs install dirs)
include("${IVL_CMAKE_COMMON_PATH}/ivlCommon.cmake")
include("${IVL_CMAKE_MODULE_PATH}/external_depends.cmake")



## -----------------------------------------------------------------------
## -----------------------------------------------------------------------
## -----------------------------------------------------------------------

## build setup for all the modules

include_directories("${CMAKE_SOURCE_DIR}/include")

IF(UNIX)
#set(CMAKE_CXX_FLAGS "-Wall")
ENDIF()

IF(MSVC)
	ADD_DEFINITIONS("/EHsc")
ENDIF()

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	ADD_DEFINITIONS(-D_DEBUG)
ENDIF()

#set(CMAKE_REQUIRED_LIBRARIES stdintivl ivl lapack blas gfortran ${CMAKE_REQUIRED_LIBRARIES})

include_directories("${CMAKE_SOURCE_DIR}/include/ivl")
include_directories("${CMAKE_SOURCE_DIR}/include/ivl/details")


## -----------------------------------------------------------------------

# install the ivl core library
add_subdirectory(cmake)

# build and install the ivl modules (ivl-lina, ivl-cv)
include_directories("${CMAKE_SOURCE_DIR}/modules/ivl-lina/src")
include_directories("${CMAKE_SOURCE_DIR}/modules/ivl-cv/src")
include_directories("${CMAKE_SOURCE_DIR}/modules/ivl-qt/src")
add_subdirectory(modules)

# build the samples
set(BUILD_SAMPLES FALSE CACHE BOOL "Build the ivl samples together with the library")
if(${BUILD_SAMPLES})
	add_subdirectory(samples)
endif()

# Install the sample sources
set(INSTALL_SAMPLES FALSE CACHE BOOL "Install the ivl samples (the source files)")
if(${INSTALL_SAMPLES})
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/samples DESTINATION "${INSTALL_SAMPLES_DIR_POST}" COMPONENT samples PATTERN ".svn" EXCLUDE)
endif()

# test


##
## autoinstall
#if (MSVC10)
#    GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\10.0\\Setup\\VS;ProductDir] REALPATH CACHE)
#elseif (MSVC90)
#    GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\9.0\\Setup\\VS;ProductDir] REALPATH CACHE)
#elseif (MSVC80)
#    GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VS;ProductDir] REALPATH CACHE)
#endif()
#set (VS_DEVENV "${VS_DIR}/Common7/IDE/devenv.com")
#message("Compiler: ${VS_DIR}")



## -----------------------------------------------------------------------
## packing
if(WIN32)
	SET(CPACK_GENERATOR "NSIS" CACHE STRING "CPack generator. examples: deb;nsis;zip;tgz")
else()
	SET(CPACK_GENERATOR "TGZ" CACHE STRING "CPack generator. examples: deb;nsis;zip;tgz")
endif()
#debian info
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "iva") #required
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
mark_as_advanced(CPACK_GENERATOR)
INCLUDE(CPack)
## -----------------------------------------------------------------------

## end of file


