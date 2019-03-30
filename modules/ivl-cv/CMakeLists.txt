# ivl-cv
COMPUTE_INSTALL_CMAKE_DIR(ivl-cv)

# ------------------------------------------------------
# Gather the source and header files

# add the source files to variable SOURCES 
# (automatic file scan)
file(GLOB_RECURSE SOURCES_PRE "src/*")
PREG_REMOVE("${SOURCES_PRE}" "\\\\.svn" SOURCES)

# add the global header files to variable HEADERS
# (automatic file scan. exclude *_impl.h* files)
	#global headers use is commented-out because it's kinda weird
	#file(GLOB_RECURSE HEADERS_PRE "src/*.h*")
	#PREG_REMOVE("${HEADERS_PRE}" "_impl\\\\." HEADERS_)
	#PREG_REMOVE("${HEADERS_}" "\\\\.svn" HEADERS)
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/ivl" DESTINATION ${INSTALL_INCLUDE_DIR_POST} 
COMPONENT dev
PATTERN ".svn" EXCLUDE PATTERN "_impl." EXCLUDE
)


# ------------------------------------------------------
# Add the library target and the files

###TODO: check: add_definitions("-DIVL_OPENCV")

add_library(ivl-cv SHARED ${SOURCES})
if(WIN32 AND NOT CYGWIN)
	SET_TARGET_PROPERTIES (ivl-cv PROPERTIES DEFINE_SYMBOL  "_ivlcv_EXPORTS_" )
endif()

	#set_target_properties(ivl-cv PROPERTIES PUBLIC_HEADER "${HEADERS}")

# ------------------------------------------------------

target_link_libraries(ivl-cv ${LIB_TARGETS} ${OpenCV_LIBS}) #add opencv

# ------------------------------------------------------


 #relative install location
  install(TARGETS ivl-cv
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT ivl-cvLibraryDepends
  RUNTIME DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT bin #_bin_dir
  LIBRARY DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR_POST}" COMPONENT dev
  )



set(PKG_CFLAGS)
set(PKG_LIBS)
ALL_EXPORTS(ivl-cv)



#export(TARGETS ivl-cv 
#  FILE "${PROJECT_BINARY_DIR}/ivl-cvLibraryDepends.cmake")

# export to registry
#if(${EXPORT_PACKAGE_TO_REGISTRY})
#        export(PACKAGE ivl-cv)
#endif()
#

# Create a ivl-cvBuildTreeSettings.cmake file for the use from the build tree
#configure_file(ivl-cvBuildTreeSettings.cmake.in
#  "${PROJECT_BINARY_DIR}/ivl-cvBuildTreeSettings.cmake" @ONLY)
# 
## Create the ivl-cvConfig.cmake and ivl-cvConfigVersion files
#file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
#   "${INSTALL_INCLUDE_DIR}")
#configure_file(ivl-cvConfig.cmake.in
#  "${PROJECT_BINARY_DIR}/ivl-cvConfig.cmake" @ONLY)
#configure_file(ivl-cvConfigVersion.cmake.in
#  "${PROJECT_BINARY_DIR}/ivl-cvConfigVersion.cmake" @ONLY)
# 
## Install the export set for use with the install-tree
#install(EXPORT ivl-cvLibraryDepends DESTINATION
#  "${INSTALL_CMAKE_DIR}"
#  COMPONENT dev)

# -----------------------------------------------------
# pkg-config
#set(PKG_CFLAGS)
##set(PKG_LIBS)
##set(PKG_LIBS "-livl-cv")
#configure_file(ivl-cv.pc.cmake.in
#  "${PROJECT_BINARY_DIR}/ivl-cv.pc" @ONLY)
#install(FILES "${PROJECT_BINARY_DIR}/ivl-cv.pc" DESTINATION "${INSTALL_LIB_DIR}/pkgconfig")
#

