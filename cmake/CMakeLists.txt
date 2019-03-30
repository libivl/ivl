## ivl (core library)
COMPUTE_INSTALL_CMAKE_DIR(ivl)

## -----------------------------------------------------------------------

# Install the header files
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ivl DESTINATION ${INSTALL_INCLUDE_DIR_POST} 
COMPONENT dev
PATTERN ".svn" EXCLUDE)

# add the header files to the library (useful for project generation)
file(GLOB_RECURSE HEADERS_PRE "${PROJECT_SOURCE_DIR}/include/*.h*")
PREG_REMOVE("${HEADERS_PRE}" "\\\\.svn" HEADERS)

#configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)
add_library(ivl SHARED dummy/ivl_dummy.cpp ${HEADERS})	# add a dummy library to generate export files
if(WIN32 AND NOT CYGWIN)
	SET_TARGET_PROPERTIES (ivl PROPERTIES DEFINE_SYMBOL  "_ivl_EXPORTS_" )
endif()

#add_custom_target(ivl)

target_link_libraries( ivl ${LIB_TARGETS} )

SET_TARGET_PROPERTIES(ivl PROPERTIES LINKER_LANGUAGE C)

#relative paths install
install(TARGETS ivl
  # IMPORTANT: Add the ivl library to the "export-set"
  EXPORT ivlLibraryDepends
  RUNTIME DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT bin #BIN_DIR
  LIBRARY DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT lib
   ##COMPONENT dev)
	)



# settings for pkgconfig export
set(PKG_CFLAGS "${STDINTIVL_INSTALL_CFLAGS}")
set(PKG_LIBS "${LIB_TARGETS}")

# export to local build directory, installation directory, pkgconfig
ALL_EXPORTS(ivl) 


# -----------------------------------------------------
# uninstall (not tested)
CONFIGURE_FILE(
  "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")


