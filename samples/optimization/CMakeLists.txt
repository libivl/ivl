cmake_minimum_required(VERSION 2.8)

#independant configuration file for the sample project
#try to find the ivl libraries package unless we are in the ivl build configuration
#(user projects do not require this check)
if(NOT (DEFINED ivl_BUILD))

	project(optimization_sample)
	
	# find the ivl package
    find_package(ivl)

endif()

set(SRC )
list(APPEND SRC
main.cpp
)

add_executable(optimization_sample ${SRC})
target_link_libraries(optimization_sample ivl)

