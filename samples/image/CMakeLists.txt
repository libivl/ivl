cmake_minimum_required(VERSION 2.8)

#independant configuration file for the sample project
#try to find the ivl libraries package unless we are in the ivl build configuration
#(user projects do not require this check)
if(NOT (DEFINED ivl_BUILD))

	project(image_sample)
	
	# find the ivl package
	# find_package(ivl) must be placed above the other ivl-modules
	find_package(ivl) 
	
	# find the ivl-cv package
	find_package(ivl-cv)
	
else()
	# case: this is not the top of the tree build. packages are already included
    if(NOT (${USE_OPENCV}))
            return()
    endif()
endif()

add_executable(image_sample image_sample.cpp)
target_link_libraries(image_sample ivl-cv)


# obtain sample data
# the rest of the code below this point is the code to get the sample data:

# copy sample data from source dir if they exist
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/img")
file(GLOB IMFS "${CMAKE_CURRENT_SOURCE_DIR}/img/*")
set(IMF)
FOREACH(H ${IMFS})
	if(NOT H STREQUAL ".svn")
		list(APPEND IMF ${H})
	endif()
ENDFOREACH(H)
if ("${IMF}" STREQUAL "")
	if(NOT (DEFINED DOWNLOAD_SAMPLE_DATA))
		set(DOWNLOAD_SAMPLE_DATA TRUE CACHE BOOL "Try to download the sample test-data from the internet")
	endif()
	IF (${DOWNLOAD_SAMPLE_DATA})
		# download sample data from the internet
		
		FOREACH(A maimou.jpg maimoux.jpg spiti.bmp lena.jpg camera.bmp)
		FILE(DOWNLOAD "http://image.ntua.gr/ivl/resources/test-data/image-sample/img/${A}" "${CMAKE_CURRENT_BINARY_DIR}/img/${A}" INACTIVITY_TIMEOUT 5)
		ENDFOREACH(A)
	ELSE()
		message("test-data not found. Please download manually the image sample test images")
		message("by running the script which is placed in the related directory.")
	ENDIF()
else()
	file(COPY ${IMF} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/img")
endif()
# copy downloader bash script from source dir
file(GLOB S "${CMAKE_CURRENT_SOURCE_DIR}/*.sh")
file(COPY "${S}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

