cmake_minimum_required(VERSION 2.8)

#independant configuration file for the sample project
#try to find the ivl libraries package unless we are in the ivl build configuration
#(user projects do not require this check)
if(NOT (DEFINED ivl_BUILD))

	project(lina_sample)

	# find the ivl package
	# find_package(ivl) must be placed above the other ivl-modules
	find_package(ivl) 
	
	# find the ivl-lina package
    find_package(ivl-lina)
	
else()
	# case: this is not the top of the tree build. packages are already included
	if(NOT (${USE_LAPACK})) 
		return()
	endif()
endif()

add_executable(lina_sample lina_sample.cpp)
target_link_libraries(lina_sample ivl-lina)
