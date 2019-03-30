cmake_minimum_required(VERSION 2.8)

#independant configuration file for the sample project
#try to find the ivl libraries package unless we are in the ivl build configuration
#(user projects do not require this check)
if(NOT (DEFINED ivl_BUILD))

	project(full_ivl_sample)
	
	# find the ivl package
	# find_package(ivl) must be placed above the other ivl-modules
	find_package(ivl) 
	
	# find the ivl-lina package
    find_package(ivl-lina)

	# find the ivl-cv package
	find_package(ivl-cv)
	
	
else()
	# case: this is not the top of the tree build. packages are already included
	if(NOT (${USE_OPENCV}) OR NOT (${USE_LAPACK}))
			return()
	endif()
endif()


add_executable(full_ivl_sample full_ivl_sample.cpp)
target_link_libraries(full_ivl_sample ivl-cv ivl-lina)


