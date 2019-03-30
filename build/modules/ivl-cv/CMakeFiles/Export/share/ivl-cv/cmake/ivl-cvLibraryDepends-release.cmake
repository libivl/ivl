#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "ivl-cv" for configuration "Release"
SET_PROPERTY(TARGET ivl-cv APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(ivl-cv PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "-lpthread;/usr/local/lib/libopencv_calib3d.so;/usr/local/lib/libopencv_contrib.so;/usr/local/lib/libopencv_core.so;/usr/local/lib/libopencv_features2d.so;/usr/local/lib/libopencv_flann.so;/usr/local/lib/libopencv_gpu.so;/usr/local/lib/libopencv_highgui.so;/usr/local/lib/libopencv_imgproc.so;/usr/local/lib/libopencv_legacy.so;/usr/local/lib/libopencv_ml.so;/usr/local/lib/libopencv_nonfree.so;/usr/local/lib/libopencv_objdetect.so;/usr/local/lib/libopencv_photo.so;/usr/local/lib/libopencv_stitching.so;/usr/local/lib/libopencv_ts.so;/usr/local/lib/libopencv_video.so;/usr/local/lib/libopencv_videostab.so"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libivl-cv.so"
  IMPORTED_SONAME_RELEASE "libivl-cv.so"
  )

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
