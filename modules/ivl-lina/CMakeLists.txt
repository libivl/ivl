# ivl-lina
COMPUTE_INSTALL_CMAKE_DIR(ivl-lina)

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
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/ivl" DESTINATION ${INSTALL_INCLUDE_DIR_POST} COMPONENT dev 
PATTERN ".svn" EXCLUDE PATTERN "_impl." EXCLUDE
)


# ------------------------------------------------------
# Add the library target and the files

	#set_target_properties(ivl-lina PROPERTIES PUBLIC_HEADER "${HEADERS}")
if(WIN32 AND NOT CYGWIN)
	add_library(ivl-lina STATIC ${SOURCES})
	#SET_TARGET_PROPERTIES (ivl-lina PROPERTIES DEFINE_SYMBOL  "_ivllina_EXPORTS_" )
	add_definitions("-D _ivllina_STATIC_")
else()
	add_library(ivl-lina SHARED ${SOURCES})

endif()

	
# ------------------------------------------------------

target_link_libraries(ivl-lina ${LIB_TARGETS} ${LAPACK_TARGETS})

# ------------------------------------------------------


# relative install

install(TARGETS ivl-lina 
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT ivl-linaLibraryDepends
  RUNTIME DESTINATION "${INSTALL_BIN_DIR_POST}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR_POST}" COMPONENT dev)

configure_file("lapack_include.cmake.in" "${PROJECT_BINARY_DIR}/lapack_include.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/lapack_include.cmake" DESTINATION "${INSTALL_CMAKE_DIR_POST}" COMPONENT dev)  

# -----------------------------------------------------
# pkg-config
ADD_PREFIX("-I" "${LAPACKIVL_INCLUDE_DIRS}" LAPACK_CFLAGS)
set(PKG_CFLAGS "${LAPACK_CFLAGS}")
set(PKG_LIBS "${LAPACKIVL_LIBS} -livl-lina")

ALL_EXPORTS(ivl-lina)


include(CPack)

