# - Find BLAS library
# This module finds an installed fortran library that implements the BLAS
# linear-algebra interface (see http://www.netlib.org/blas/).
# The list of libraries searched for is taken
# from the autoconf macro file, acx_blas.m4 (distributed at
# http://ac-archive.sourceforge.net/ac-archive/acx_blas.html).
#
# This module sets the following variables:
#  BLAS_FOUND - set to true if a library implementing the BLAS interface
#    is found

#  BLAS_LINKER_FLAGS - uncached list of required linker flags (excluding -l
#    and -L).
#  BLAS_LIBRARIES - uncached list of libraries (using full path name) to
#    link against to use BLAS
#  BLAS95_LIBRARIES - uncached list of libraries (using full path name)
#    to link against to use BLAS95 interface
#  BLAS95_FOUND - set to true if a library implementing the BLAS f95 interface
#    is found
#  BLA_STATIC  if set on this determines what kind of linkage we do (static)
#  BLA_VENDOR  if set checks only the specified vendor, if not set checks
#     all the posibilities
#  BLA_F95     if set on tries to find the f95 interfaces for BLAS/LAPACK
##########
### List of vendors (BLA_VENDOR) valid in this module
##  ATLAS, PhiPACK,CXML,DXML,SunPerf,SCSL,SGIMATH,IBMESSL,Intel10_32 (intel mkl v10 32 bit),Intel10_64lp (intel mkl v10 64 bit,lp thread model, lp64 model),
##  Intel( older versions of mkl 32 and 64 bit), ACML,Apple, NAS, Generic

include(CheckFortranFunctionExists)

macro(Check_Fortran_Libraries LIBRARIES _prefix _name _flags _list _threads)
# This macro checks for the existence of the combination of fortran libraries
# given by _list.  If the combination is found, this macro checks (using the
# Check_Fortran_Function_Exists macro) whether can link against that library
# combination using the name of a routine given by _name using the linker
# flags given by _flags.  If the combination of libraries is found and passes
# the link test, LIBRARIES is set to the list of complete library paths that
# have been found.  Otherwise, LIBRARIES is set to FALSE.

# N.B. _prefix is the prefix applied to the names of all cached variables that
# are generated internally and marked advanced by this macro.

set(_libraries_work TRUE)
set(${LIBRARIES})
set(_combined_name)
foreach(_library ${_list})
  set(_combined_name ${_combined_name}_${_library})

  if(_libraries_work)
   if ( WIN32 )
    if(BLA_STATIC)
      set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.dll")
    endif(BLA_STATIC)
    find_library(${_prefix}_${_library}_LIBRARY
    NAMES ${_library}
    PATHS ENV LIB
    )
   endif ( WIN32 )

   if ( APPLE )
    if(BLA_STATIC)
     set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.dll")
    endif(BLA_STATIC)
    find_library(${_prefix}_${_library}_LIBRARY
    NAMES ${_library}
    PATHS /usr/local/lib /usr/lib /usr/local/lib64 /usr/lib64 ENV DYLD_LIBRARY_PATH
    )

   else ( APPLE )
    if(BLA_STATIC)
      set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
    endif(BLA_STATIC)
    find_library(${_prefix}_${_library}_LIBRARY
    NAMES ${_library}
    PATHS /usr/local/lib /usr/lib /usr/local/lib64 /usr/lib64 ENV LD_LIBRARY_PATH
    )
   endif( APPLE )
    mark_as_advanced(${_prefix}_${_library}_LIBRARY)
    set(${LIBRARIES} ${${LIBRARIES}} ${${_prefix}_${_library}_LIBRARY})
    set(_libraries_work ${${_prefix}_${_library}_LIBRARY})
  endif(_libraries_work)
endforeach(_library ${_list})
if(_libraries_work)
  # Test this combination of libraries.
  set(CMAKE_REQUIRED_LIBRARIES ${_flags} ${${LIBRARIES}} ${_threads})
# message("DEBUG: CMAKE_REQUIRED_LIBRARIES = ${CMAKE_REQUIRED_LIBRARIES}")
    get_property(_LANGUAGES_ GLOBAL PROPERTY ENABLED_LANGUAGES)
    if(_LANGUAGES_ MATCHES Fortran)
      check_fortran_function_exists(${_name} ${_prefix}${_combined_name}_WORKS)
    endif(_LANGUAGES_ MATCHES Fortran)
  set(CMAKE_REQUIRED_LIBRARIES)
  mark_as_advanced(${_prefix}${_combined_name}_WORKS)
  set(_libraries_work ${${_prefix}${_combined_name}_WORKS})
endif(_libraries_work)
if(NOT _libraries_work)
  set(${LIBRARIES} FALSE)
endif(NOT _libraries_work)
#message("DEBUG: ${LIBRARIES} = ${${LIBRARIES}}")
endmacro(Check_Fortran_Libraries)

set(BLAS_LINKER_FLAGS)
set(BLAS_LIBRARIES)
set(BLAS95_LIBRARIES)
if(BLAS_FIND_QUIETLY OR NOT BLAS_FIND_REQUIRED)
  find_package(Threads)
else(BLAS_FIND_QUIETLY OR NOT BLAS_FIND_REQUIRED)
  find_package(Threads REQUIRED)
endif(BLAS_FIND_QUIETLY OR NOT BLAS_FIND_REQUIRED)

if(NOT BLA_VENDOR)
  set(BLA_VENDOR "All")
endif(NOT BLA_VENDOR)

if (BLA_VENDOR STREQUAL "ATLAS" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  # BLAS in ATLAS library? (http://math-atlas.sourceforge.net/)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  cblas_dgemm
  ""
  "cblas;f77blas;atlas"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "ATLAS" OR BLA_VENDOR STREQUAL "All")

# BLAS in PhiPACK libraries? (requires generic BLAS lib, too)
if (BLA_VENDOR STREQUAL "PhiPACK" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "sgemm;dgemm;blas"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "PhiPACK" OR BLA_VENDOR STREQUAL "All")

# BLAS in Alpha CXML library?
if (BLA_VENDOR STREQUAL "CXML" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "cxml"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "CXML" OR BLA_VENDOR STREQUAL "All")

# BLAS in Alpha DXML library? (now called CXML, see above)
if (BLA_VENDOR STREQUAL "DXML" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "dxml"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "DXML" OR BLA_VENDOR STREQUAL "All")

# BLAS in Sun Performance library?
if (BLA_VENDOR STREQUAL "SunPerf" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  "-xlic_lib=sunperf"
  "sunperf;sunmath"
  ""
  )
  if(BLAS_LIBRARIES)
    set(BLAS_LINKER_FLAGS "-xlic_lib=sunperf")
  endif(BLAS_LIBRARIES)
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "SunPerf" OR BLA_VENDOR STREQUAL "All")


# BLAS in SCSL library?  (SGI/Cray Scientific Library)
if (BLA_VENDOR STREQUAL "SCSL" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "scsl"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "SCSL" OR BLA_VENDOR STREQUAL "All")

# BLAS in SGIMATH library?
if (BLA_VENDOR STREQUAL "SGIMATH" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "complib.sgimath"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "SGIMATH" OR BLA_VENDOR STREQUAL "All")

# BLAS in IBM ESSL library? (requires generic BLAS lib, too)
if (BLA_VENDOR STREQUAL "IBMESSL" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "essl;blas"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "IBMESSL" OR BLA_VENDOR STREQUAL "All")

#BLAS in intel mkl 10 library? (em64t 64bit)
if (BLA_VENDOR MATCHES "Intel*" OR BLA_VENDOR STREQUAL "All")
  if (WIN32)
  if(BLA_F95)
    if(NOT BLAS95_LIBRARIES)
    check_fortran_libraries(
    BLAS95_LIBRARIES
    BLAS
    sgemm
    ""
    "mkl_blas95;mkl_intel_c;mkl_intel_thread;mkl_core;libguide40"
    ""
    )
    endif(NOT BLAS95_LIBRARIES)
  else(BLA_F95)
    if(NOT BLAS_LIBRARIES)
    check_fortran_libraries(
    BLAS_LIBRARIES
    BLAS
    SGEMM
    ""
    "mkl_c_dll;mkl_intel_thread_dll;mkl_core_dll;libguide40"
    ""
    )
    endif(NOT BLAS_LIBRARIES)
  endif(BLA_F95)
  else(WIN32)
  if (BLA_VENDOR STREQUAL "Intel10_32" OR BLA_VENDOR STREQUAL "All")
    if(BLA_F95)
      if(NOT BLAS95_LIBRARIES)
      check_fortran_libraries(
      BLAS95_LIBRARIES
      BLAS
      sgemm
      ""
      "mkl_blas95;mkl_intel;mkl_intel_thread;mkl_core;guide"
      "${CMAKE_THREAD_LIBS_INIT}"
      )
      endif(NOT BLAS95_LIBRARIES)
    else(BLA_F95)
    if(NOT BLAS_LIBRARIES)
      check_fortran_libraries(
      BLAS_LIBRARIES
      BLAS
      sgemm
      ""
      "mkl_intel;mkl_intel_thread;mkl_core;guide"
      "${CMAKE_THREAD_LIBS_INIT}"
      )
      endif(NOT BLAS_LIBRARIES)
    endif(BLA_F95)
  endif (BLA_VENDOR STREQUAL "Intel10_32" OR BLA_VENDOR STREQUAL "All")
  if (BLA_VENDOR STREQUAL "Intel10_64lp" OR BLA_VENDOR STREQUAL "All")
   if(BLA_F95)
    if(NOT BLAS95_LIBRARIES)
      check_fortran_libraries(
      BLAS95_LIBRARIES
      BLAS
      sgemm
      ""
      "mkl_blas95;mkl_intel_lp64;mkl_intel_thread;mkl_core;guide"
      "${CMAKE_THREAD_LIBS_INIT}"
      )
    endif(NOT BLAS95_LIBRARIES)
   else(BLA_F95)
     if(NOT BLAS_LIBRARIES)
      check_fortran_libraries(
      BLAS_LIBRARIES
      BLAS
      sgemm
      ""
      "mkl_intel_lp64;mkl_intel_thread;mkl_core;guide"
      "${CMAKE_THREAD_LIBS_INIT}"
      )
     endif(NOT BLAS_LIBRARIES)
   endif(BLA_F95)
  endif (BLA_VENDOR STREQUAL "Intel10_64lp" OR BLA_VENDOR STREQUAL "All")
  endif (WIN32)
  #older vesions of intel mkl libs
  # BLAS in intel mkl library? (shared)
  if(NOT BLAS_LIBRARIES)
    check_fortran_libraries(
    BLAS_LIBRARIES
    BLAS
    sgemm
    ""
    "mkl;guide"
    "${CMAKE_THREAD_LIBS_INIT}"
    )
  endif(NOT BLAS_LIBRARIES)
  #BLAS in intel mkl library? (static, 32bit)
  if(NOT BLAS_LIBRARIES)
    check_fortran_libraries(
    BLAS_LIBRARIES
    BLAS
    sgemm
    ""
    "mkl_ia32;guide"
    "${CMAKE_THREAD_LIBS_INIT}"
    )
  endif(NOT BLAS_LIBRARIES)
  #BLAS in intel mkl library? (static, em64t 64bit)
  if(NOT BLAS_LIBRARIES)
    check_fortran_libraries(
    BLAS_LIBRARIES
    BLAS
    sgemm
    ""
    "mkl_em64t;guide"
    "${CMAKE_THREAD_LIBS_INIT}"
    )
  endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR MATCHES "Intel*" OR BLA_VENDOR STREQUAL "All")

#BLAS in acml library?
if (BLA_VENDOR STREQUAL "ACML" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "acml"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "ACML" OR BLA_VENDOR STREQUAL "All")

# Apple BLAS library?
if (BLA_VENDOR STREQUAL "Apple" OR BLA_VENDOR STREQUAL "All")
if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  cblas_dgemm
  ""
  "Accelerate"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "Apple" OR BLA_VENDOR STREQUAL "All")

if (BLA_VENDOR STREQUAL "NAS" OR BLA_VENDOR STREQUAL "All")
 if ( NOT BLAS_LIBRARIES )
    check_fortran_libraries(
    BLAS_LIBRARIES
    BLAS
    cblas_dgemm
    ""
    "vecLib"
    ""
    )
 endif ( NOT BLAS_LIBRARIES )
endif (BLA_VENDOR STREQUAL "NAS" OR BLA_VENDOR STREQUAL "All")
# Generic BLAS library?
if (BLA_VENDOR STREQUAL "Generic" OR BLA_VENDOR STREQUAL "All")
 if(NOT BLAS_LIBRARIES)
  check_fortran_libraries(
  BLAS_LIBRARIES
  BLAS
  sgemm
  ""
  "blas"
  ""
  )
 endif(NOT BLAS_LIBRARIES)
endif (BLA_VENDOR STREQUAL "Generic" OR BLA_VENDOR STREQUAL "All")

if(BLA_F95)
 if(BLAS95_LIBRARIES)
    set(BLAS95_FOUND TRUE)
  else(BLAS95_LIBRARIES)
    set(BLAS95_FOUND FALSE)
  endif(BLAS95_LIBRARIES)

  if(NOT BLAS_FIND_QUIETLY)
    if(BLAS95_FOUND)
      message(STATUS "A library with BLAS95 API found.")
    else(BLAS95_FOUND)
      if(BLAS_FIND_REQUIRED)
        message(FATAL_ERROR
        "A required library with BLAS95 API not found. Please specify library location.")
      else(BLAS_FIND_REQUIRED)
        message(STATUS
        "A library with BLAS95 API not found. Please specify library location.")
      endif(BLAS_FIND_REQUIRED)
    endif(BLAS95_FOUND)
  endif(NOT BLAS_FIND_QUIETLY)
  set(BLAS_FOUND TRUE)
  set(BLAS_LIBRARIES "${BLAS95_LIBRARIES}")
else(BLA_F95)
  if(BLAS_LIBRARIES)
    set(BLAS_FOUND TRUE)
  else(BLAS_LIBRARIES)
    set(BLAS_FOUND FALSE)
  endif(BLAS_LIBRARIES)

  if(NOT BLAS_FIND_QUIETLY)
    if(BLAS_FOUND)
      message(STATUS "A library with BLAS API found.")
    else(BLAS_FOUND)
      if(BLAS_FIND_REQUIRED)
        message(FATAL_ERROR
        "A required library with BLAS API not found. Please specify library location."
        )
      else(BLAS_FIND_REQUIRED)
        message(STATUS
        "A library with BLAS API not found. Please specify library location."
        )
      endif(BLAS_FIND_REQUIRED)
    endif(BLAS_FOUND)
  endif(NOT BLAS_FIND_QUIETLY)
endif(BLA_F95)

# - Find LAPACK library
# This module finds an installed fortran library that implements the LAPACK
# linear-algebra interface (see http://www.netlib.org/lapack/).
#
# The approach follows that taken for the autoconf macro file, acx_lapack.m4
# (distributed at http://ac-archive.sourceforge.net/ac-archive/acx_lapack.html).
#
# This module sets the following variables:
#  LAPACK_FOUND - set to true if a library implementing the LAPACK interface
#    is found
#  LAPACK_LINKER_FLAGS - uncached list of required linker flags (excluding -l
#    and -L).
#  LAPACK_LIBRARIES - uncached list of libraries (using full path name) to
#    link against to use LAPACK
#  LAPACK95_LIBRARIES - uncached list of libraries (using full path name) to
#    link against to use LAPACK95
#  LAPACK95_FOUND - set to true if a library implementing the LAPACK f95
#    interface is found
#  BLA_STATIC  if set on this determines what kind of linkage we do (static)
#  BLA_VENDOR  if set checks only the specified vendor, if not set checks
#     all the posibilities
#  BLA_F95     if set on tries to find the f95 interfaces for BLAS/LAPACK
### List of vendors (BLA_VENDOR) valid in this module
##  Intel(mkl), ACML,Apple, NAS, Generic
include(CheckFortranFunctionExists)
set(LAPACK_FOUND FALSE)
set(LAPACK95_FOUND FALSE)

macro(Check_Lapack_Libraries LIBRARIES _prefix _name _flags _list _blas _threads)
# This macro checks for the existence of the combination of fortran libraries
# given by _list.  If the combination is found, this macro checks (using the
# Check_Fortran_Function_Exists macro) whether can link against that library
# combination using the name of a routine given by _name using the linker
# flags given by _flags.  If the combination of libraries is found and passes
# the link test, LIBRARIES is set to the list of complete library paths that
# have been found.  Otherwise, LIBRARIES is set to FALSE.

# N.B. _prefix is the prefix applied to the names of all cached variables that
# are generated internally and marked advanced by this macro.

set(_libraries_work TRUE)
set(${LIBRARIES})
set(_combined_name)
foreach(_library ${_list})
  set(_combined_name ${_combined_name}_${_library})

  if(_libraries_work)
  IF (WIN32)
    if(BLA_STATIC)
      set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.dll")
    endif(BLA_STATIC)
    find_library(${_prefix}_${_library}_LIBRARY
    NAMES ${_library}
    PATHS ENV LIB
    )
  ENDIF (WIN32)

  if(APPLE)
    if(BLA_STATIC)
      set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so;.dylib")
    endif(BLA_STATIC)
    find_library(${_prefix}_${_library}_LIBRARY
    NAMES ${_library}
    PATHS /usr/local/lib /usr/lib /usr/local/lib64 /usr/lib64 ENV DYLD_LIBRARY_PATH
    )
    else(APPLE)
    if(BLA_STATIC)
     set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
    endif(BLA_STATIC)
    find_library(${_prefix}_${_library}_LIBRARY
    NAMES ${_library}
    PATHS /usr/local/lib /usr/lib /usr/local/lib64 /usr/lib64 ENV LD_LIBRARY_PATH
    )
    endif(APPLE)

    mark_as_advanced(${_prefix}_${_library}_LIBRARY)
    set(${LIBRARIES} ${${LIBRARIES}} ${${_prefix}_${_library}_LIBRARY})
    set(_libraries_work ${${_prefix}_${_library}_LIBRARY})
  endif(_libraries_work)
endforeach(_library ${_list})

if(_libraries_work)
  # Test this combination of libraries.
  if(UNIX AND BLA_STATIC)
    set(CMAKE_REQUIRED_LIBRARIES ${_flags} "-Wl,--start-group ${${LIBRARIES}} ${_blas};-Wl,--end-group" ${_threads})
  else(UNIX AND BLA_STATIC)
    set(CMAKE_REQUIRED_LIBRARIES ${_flags} ${${LIBRARIES}} ${_blas} ${_threads})
  endif(UNIX AND BLA_STATIC)
#  message("DEBUG: CMAKE_REQUIRED_LIBRARIES = ${CMAKE_REQUIRED_LIBRARIES}")
  get_property(_LANGUAGES_ GLOBAL PROPERTY ENABLED_LANGUAGES)
  if(_LANGUAGES_ MATCHES Fortran)
    check_fortran_function_exists(${_name} ${_prefix}${_combined_name}_WORKS)
  endif(_LANGUAGES_ MATCHES Fortran)
  set(CMAKE_REQUIRED_LIBRARIES)
  mark_as_advanced(${_prefix}${_combined_name}_WORKS)
  set(_libraries_work ${${_prefix}${_combined_name}_WORKS})
  #message("DEBUG: ${LIBRARIES} = ${${LIBRARIES}}")
endif(_libraries_work)

 if(_libraries_work)
   set(${LIBRARIES} ${${LIBRARIES}} ${_blas})
 else(_libraries_work)
    set(${LIBRARIES} FALSE)
 endif(_libraries_work)

endmacro(Check_Lapack_Libraries)


set(LAPACK_LINKER_FLAGS)
set(LAPACK_LIBRARIES)
set(LAPACK95_LIBRARIES)


if(LAPACK_FIND_QUIETLY OR NOT LAPACK_FIND_REQUIRED)
  find_package(BLAS)
  find_PACKAGE(Threads)
else(LAPACK_FIND_QUIETLY OR NOT LAPACK_FIND_REQUIRED)
  find_package(BLAS REQUIRED)
  find_package(Threads REQUIRED)
endif(LAPACK_FIND_QUIETLY OR NOT LAPACK_FIND_REQUIRED)


if(BLAS_FOUND)
  set(LAPACK_LINKER_FLAGS ${BLAS_LINKER_FLAGS})
  if(NOT BLA_VENDOR)
    set(BLA_VENDOR "All")
  endif(NOT BLA_VENDOR)
#intel lapack
  if (BLA_VENDOR MATCHES "Intel*" OR BLA_VENDOR STREQUAL "All")
   if (BLA_F95)
    if(NOT LAPACK95_LIBRARIES)
     check_lapack_libraries(
     LAPACK95_LIBRARIES
     LAPACK
     cheev
     ""
     "mkl_lapack95"
     "${BLAS95_LIBRARIES}"
     "${CMAKE_THREAD_LIBS_INIT}"
     )
    endif(NOT LAPACK95_LIBRARIES)
   else(BLA_F95)
    if(NOT LAPACK_LIBRARIES)
     check_lapack_libraries(
     LAPACK_LIBRARIES
     LAPACK
     cheev
     ""
     "mkl_lapack"
     "${BLAS_LIBRARIES}"
     "${CMAKE_THREAD_LIBS_INIT}"
     )
    endif(NOT LAPACK_LIBRARIES)
   endif(BLA_F95)
 endif(BLA_VENDOR MATCHES "Intel*" OR BLA_VENDOR STREQUAL "All")
#acml lapack
 if (BLA_VENDOR STREQUAL "ACML" OR BLA_VENDOR STREQUAL "All")
  if(NOT LAPACK_LIBRARIES)
   check_lapack_libraries(
    LAPACK_LIBRARIES
    LAPACK
    cheev
    ""
    "acml"
    ""
    ""
    )
  endif(NOT LAPACK_LIBRARIES)
 endif (BLA_VENDOR STREQUAL "ACML" OR BLA_VENDOR STREQUAL "All")

# Apple LAPACK library?
if (BLA_VENDOR STREQUAL "Apple" OR BLA_VENDOR STREQUAL "All")
 if(NOT LAPACK_LIBRARIES)
  check_lapack_libraries(
  LAPACK_LIBRARIES
  LAPACK
  cheev
  ""
  "Accelerate"
  "${BLAS_LIBRARIES}"
  ""
  )
 endif(NOT LAPACK_LIBRARIES)
endif (BLA_VENDOR STREQUAL "Apple" OR BLA_VENDOR STREQUAL "All")
if (BLA_VENDOR STREQUAL "NAS" OR BLA_VENDOR STREQUAL "All")
  if ( NOT LAPACK_LIBRARIES )
    check_lapack_libraries(
    LAPACK_LIBRARIES
    LAPACK
    cheev
    ""
    "vecLib"
    "${BLAS_LIBRARIES}"
    ""
    )
  endif ( NOT LAPACK_LIBRARIES )
endif (BLA_VENDOR STREQUAL "NAS" OR BLA_VENDOR STREQUAL "All")
# Generic LAPACK library?
if (BLA_VENDOR STREQUAL "Generic" OR BLA_VENDOR STREQUAL "All")
  if ( NOT LAPACK_LIBRARIES )
    check_lapack_libraries(
    LAPACK_LIBRARIES
    LAPACK
    cheev
    ""
    "lapack"
    "${BLAS_LIBRARIES}"
    ""
    )
  endif ( NOT LAPACK_LIBRARIES )
endif (BLA_VENDOR STREQUAL "Generic" OR BLA_VENDOR STREQUAL "All")
else(BLAS_FOUND)
  message(STATUS "LAPACK requires BLAS")
endif(BLAS_FOUND)

if(BLA_F95)
 if(LAPACK95_LIBRARIES)
  set(LAPACK95_FOUND TRUE)
 else(LAPACK95_LIBRARIES)
  set(LAPACK95_FOUND FALSE)
 endif(LAPACK95_LIBRARIES)
 if(NOT LAPACK_FIND_QUIETLY)
  if(LAPACK95_FOUND)
    message(STATUS "A library with LAPACK95 API found.")
  else(LAPACK95_FOUND)
    if(LAPACK_FIND_REQUIRED)
      message(FATAL_ERROR
      "A required library with LAPACK95 API not found. Please specify library location."
      )
    else(LAPACK_FIND_REQUIRED)
      message(STATUS
      "A library with LAPACK95 API not found. Please specify library location."
      )
    endif(LAPACK_FIND_REQUIRED)
  endif(LAPACK95_FOUND)
 endif(NOT LAPACK_FIND_QUIETLY)
 set(LAPACK_FOUND "${LAPACK95_FOUND}")
 set(LAPACK_LIBRARIES "${LAPACK95_LIBRARIES}")
else(BLA_F95)
 if(LAPACK_LIBRARIES)
  set(LAPACK_FOUND TRUE)
 else(LAPACK_LIBRARIES)
  set(LAPACK_FOUND FALSE)
 endif(LAPACK_LIBRARIES)

 if(NOT LAPACK_FIND_QUIETLY)
  if(LAPACK_FOUND)
    message(STATUS "A library with LAPACK API found.")
  else(LAPACK_FOUND)
    if(LAPACK_FIND_REQUIRED)
      message(FATAL_ERROR
      "A required library with LAPACK API not found. Please specify library location."
      )
    else(LAPACK_FIND_REQUIRED)
      message(STATUS
      "A library with LAPACK API not found. Please specify library location."
      )
    endif(LAPACK_FIND_REQUIRED)
  endif(LAPACK_FOUND)
 endif(NOT LAPACK_FIND_QUIETLY)
endif(BLA_F95)

