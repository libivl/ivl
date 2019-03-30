# ivl-qt
COMPUTE_INSTALL_CMAKE_DIR(ivl-qt)

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


file(GLOB_RECURSE MOC_SOURCES_PRE "src/ivl/qt-details/*")
PREG_REMOVE("${MOC_SOURCES_PRE}" "\\\\.svn" MOC_SOURCES_PRE2)
PREG_REMOVE("${MOC_SOURCES_PRE2}" "~" MOC_SOURCES_PRE3)
PREG_REMOVE("${MOC_SOURCES_PRE3}" "\\\\.svn-base" MOC_SOURCES_PRE4)
PREG_REMOVE("${MOC_SOURCES_PRE4}" "\\\\.cpp" MOC_SOURCES_PREQ)

set(MOC_SOURCES)
foreach(header ${MOC_SOURCES_PREQ})
    file(STRINGS "${header}" lines REGEX "Q_OBJECT")
    if(lines)
        list(APPEND MOC_SOURCES "${header}")
    endif()
endforeach()

qt4_wrap_cpp(MOC_CPP ${MOC_SOURCES})

#TODO
add_definitions(-DQT_NO_DEBUG)

# ------------------------------------------------------
# Add the library target and the files




add_library(ivl-qt SHARED ${SOURCES} ${MOC_CPP})
if(WIN32 AND NOT CYGWIN)
	SET_TARGET_PROPERTIES (ivl-qt PROPERTIES DEFINE_SYMBOL  "_ivlqt_EXPORTS_" )
endif()

	#set_target_properties(ivl-qt PROPERTIES PUBLIC_HEADER "${HEADERS}")

# ------------------------------------------------------
## todo
##TODO: add_definitions("-DIVL_QT")

include(${QT_USE_FILE})

target_link_libraries(ivl-qt ${LIB_TARGETS} ${QT_LIBRARIES}) #add Qt

# ------------------------------------------------------


 #relative install location
  install(TARGETS ivl-qt
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT ivl-qtLibraryDepends
  RUNTIME DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT bin #_bin_dir
  LIBRARY DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR_POST}" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR_POST}" COMPONENT dev
  )



set(PKG_CFLAGS)
set(PKG_LIBS)
ALL_EXPORTS(ivl-qt)



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

