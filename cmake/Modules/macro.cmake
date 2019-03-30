
## -----------------------------------------------------------------------

# add prefix macro.
# adds the prefix 'prefix_in' to all the items of 'listvar_in'

MACRO(ADD_PREFIX prefix_in listvar_in result_out)
        SET(output)
        FOREACH (MEMBER ${listvar_in})
                SET(output ${output} "${prefix_in}${MEMBER}")
        ENDFOREACH(MEMBER)
        SET(${result_out} ${output})
ENDMACRO(ADD_PREFIX)

## -----------------------------------------------------------------------

MACRO(SET_DEFAULT_CONFIG T)
	IF(DEFINED CMAKE_BUILD_TYPE)
		SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
		build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
		Release RelWithDebInfo MinSizeRel.")
	ELSE()
		SET(CMAKE_BUILD_TYPE ${T} CACHE STRING "Choose the type of build,
		options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release
		RelWithDebInfo MinSizeRel.")
	ENDIF()
ENDMACRO(SET_DEFAULT_CONFIG)

## -----------------------------------------------------------------------

MACRO (COMPUTE_INSTALL_CMAKE_DIR I)
	if(${INSTALL_CMAKE_PREPEND_NAME})
		set(INSTALL_CMAKE_DIR "${INSTALL_CMAKE_DIR}${I}/${INSTALL_CMAKE_POST}")
		set(INSTALL_CMAKE_DIR_POST "${INSTALL_CMAKE_DIR_POST}${I}/${INSTALL_CMAKE_POST}")
	else()
		set(INSTALL_CMAKE_DIR "${INSTALL_CMAKE_DIR}${INSTALL_CMAKE_POST}")
		set(INSTALL_CMAKE_DIR_POST "${INSTALL_CMAKE_DIR_POST}${INSTALL_CMAKE_POST}")
	endif()
ENDMACRO(COMPUTE_INSTALL_CMAKE_DIR)


# Make relative installation paths absolute (INSTALL_*_DIR)
#MACRO(MAKE_ABSOLUTE_INSTALLATION_PATHS)
#	foreach(p LIB BIN INCLUDE CMAKE)
#	  set(var INSTALL_${p}_DIR)
#	  if(NOT IS_ABSOLUTE "${${var}}")
#	    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
#	  endif()
#	endforeach()
#ENDMACRO(MAKE_ABSOLUTE_INSTALLATION_PATHS)

## -----------------------------------------------------------------------

# Remove from the list 'lst' the items that match the regular expression 'expr'
MACRO(PREG_REMOVE lst expr out)
	set(o )
	foreach(h ${lst})
		string(REGEX MATCH "${expr}" MATCH "${h}")
		string(COMPARE EQUAL "${MATCH}" "" MATCH_NONE)
		if(MATCH_NONE)
			list(APPEND o "${h}")
		endif()
	endforeach(h)
	set(${out} ${o})
ENDMACRO(PREG_REMOVE)

# does all the possible exports from a library.
# assumes ${T}LibraryDepends
MACRO(ALL_EXPORTS T)
	# Add all targets to the build-tree export set
	export(TARGETS ${T}
	FILE "${PROJECT_BINARY_DIR}/${T}LibraryDepends.cmake")
 
	# Export the package for use from the build-tree
	# (this registers the build-tree with a global CMake-registry)
	# export to registry
	if(${EXPORT_PACKAGE_TO_REGISTRY})
		export(PACKAGE ${T})
	endif()
	 
	FILE(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/unix")
	FILE(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/win-cmake")
	#set(unix) # do not put the generated files to a seperate directory (for the time being)
	set(unix "unix/") # put the generated files to a seperate directory (for the time being)
	
	# Create a ${T}BuildTreeSettings.cmake file for the use from the build tree
	configure_file(${T}BuildTreeSettings.cmake.in
	  "${PROJECT_BINARY_DIR}/${unix}${T}BuildTreeSettings.cmake" @ONLY)
	# Create the ${T}Config.cmake and ${T}ConfigVersion files
	file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
	   "${INSTALL_INCLUDE_DIR}")
	configure_file(${T}Config.cmake.in
	  "${PROJECT_BINARY_DIR}/${unix}${T}Config.cmake" @ONLY)
	configure_file(${T}ConfigVersion.cmake.in
	  "${PROJECT_BINARY_DIR}/${unix}${T}ConfigVersion.cmake" @ONLY)

	# Install the export set for use with the install-tree
	#install(EXPORT ${T}LibraryDepends DESTINATION
	#  "${INSTALL_CMAKE_DIR}"
	#  COMPONENT dev)
	install(EXPORT ${T}LibraryDepends DESTINATION
	  "${INSTALL_CMAKE_DIR_POST}"
	  COMPONENT dev)
	
	install(FILES 
		"${PROJECT_BINARY_DIR}/${unix}${T}Config.cmake"
		"${PROJECT_BINARY_DIR}/${unix}${T}ConfigVersion.cmake"
		DESTINATION "${INSTALL_CMAKE_DIR_POST}" COMPONENT dev)

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${T}Common.cmake")
	install(FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/${T}Common.cmake"
		DESTINATION "${INSTALL_CMAKE_DIR_POST}" COMPONENT dev)
	else()
		#message(WARNING "not finding ${CMAKE_CURRENT_SOURCE_DIR}/${T}Common.cmake")
	endif()
	
	# -----------------------------------------------------
	# pkg-config
	configure_file(${T}.pc.cmake.in
	  "${PROJECT_BINARY_DIR}/${T}.pc" @ONLY)
	install(FILES "${PROJECT_BINARY_DIR}/${T}.pc" DESTINATION "${INSTALL_LIB_DIR_POST}/pkgconfig" COMPONENT pkgconfig)
ENDMACRO(ALL_EXPORTS)



