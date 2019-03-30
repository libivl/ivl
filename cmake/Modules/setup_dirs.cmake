
# setup installation directories
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR )
  set(INSTALL_CMAKE_POST "CMake/" )
  #set(INSTALL_CMAKE_POST "." )
  set(SMP_D ".")
  set(INSTALL_CMAKE_PREPEND_NAME FALSE)
  set(EXPORT_PACKAGE_TO_REGISTRY FALSE CACHE BOOL "Export the CMake package at the build path to the system registry")
else()
  set(DEF_INSTALL_CMAKE_DIR "share/")
  set(SMP_D "share/ivl/")
  set(INSTALL_CMAKE_POST "cmake/")
  set(INSTALL_CMAKE_PREPEND_NAME TRUE)
  set(EXPORT_PACKAGE_TO_REGISTRY FALSE CACHE BOOL "Export the CMake package at the build path to the system registry")
endif()
mark_as_advanced(EXPORT_PACKAGE_TO_REGISTRY)


set(DOWNLOAD_SAMPLE_DATA TRUE CACHE BOOL "Download the samples test-data from the internet")

if(0)
	# Offer the user the choice of overriding the installation directories
	set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
	set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
	set(INSTALL_SAMPLES_DIR ${SMP_D} CACHE PATH "Installation directory for samples")
	set(INSTALL_INCLUDE_DIR include CACHE PATH
	  "Installation directory for header files")
	set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
	  "Installation directory for CMake files")
else()
	set(INSTALL_LIB_DIR lib)
	set(INSTALL_BIN_DIR bin)
	set(INSTALL_SAMPLES_DIR ${SMP_D})
	set(INSTALL_INCLUDE_DIR include)
	set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR})
endif()

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE SAMPLES)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
	set(${var}_POST "${${var}}") #keep the old values as _POST
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

## -----------------------------------------------------------------------

