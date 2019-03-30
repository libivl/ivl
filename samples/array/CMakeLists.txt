cmake_minimum_required(VERSION 2.8)

#independant configuration file for the sample project
#try to find the ivl libraries package unless we are in the ivl build configuration
#(user projects do not require this check)
if(NOT (DEFINED ivl_BUILD))

	project(array_sample)

	find_package(ivl)
endif()

set(SRC )
list(APPEND SRC
array_samples.cpp
array_nd_samples.cpp
array_2d_samples.cpp
other_array_samples.cpp
#set_samples.cpp
main.cpp
)

add_executable(array_sample ${SRC})
target_link_libraries(array_sample ivl)

