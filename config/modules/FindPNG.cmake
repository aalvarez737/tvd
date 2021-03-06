# - Find the native PNG includes and library
#
# This module defines
#  PNG_INCLUDE_DIR, where to find png.h, etc.
#  PNG_LIBRARIES, the libraries to link against to use PNG.
#  PNG_DEFINITIONS - You should add_definitons(${PNG_DEFINITIONS}) before compiling code that includes png library files.
#  PNG_FOUND, If false, do not try to use PNG.
# also defined, but not for general use are
#  PNG_LIBRARY, where to find the PNG library.
# None of the above will be defined unles zlib can be found.
# PNG depends on Zlib

#=============================================================================
# Copyright 2002-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

if(PNG_FIND_QUIETLY)
  set(_FIND_ZLIB_ARG QUIET)
endif(PNG_FIND_QUIETLY)

if(IOS)
  find_package( Zlib REQUIRED )
else(IOS)
  find_library(ZLIB_LIBRARIES NAMES zlib z HINTS $ENV{PNG_ROOT}/lib ${PNG_ROOT}/lib $ENV{PNG_DIR}/lib)
endif(IOS)

if(ZLIB_LIBRARIES)
  find_path(PNG_INCLUDE_DIRS png.h
  /usr/local/include/libpng             # OpenBSD
  $ENV{PNG_ROOT}/include
  ${PNG_ROOT}/include
  $ENV{PNG_DIR}/include
  )
  

  set(PNG_NAMES ${PNG_NAMES} png libpng png15 libpng15 png15d libpng15d png14 libpng14 png14d libpng14d png12 libpng12 png12d libpng12d)
  find_library(PNG_LIBRARIES NAMES ${PNG_NAMES} HINTS $ENV{PNG_ROOT}/lib ${PNG_ROOT}/lib $ENV{PNG_DIR}/lib)

  if (PNG_LIBRARIES AND PNG_INCLUDE_DIRS)
      # png.h includes zlib.h. Sigh.
      SET(PNG_INCLUDE_DIR ${PNG_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} )
      SET(PNG_LIBRARIES ${PNG_LIBRARIES} ${ZLIB_LIBRARIES})

      if (CYGWIN)
        if(BUILD_SHARED_LIBS)
           # No need to define PNG_USE_DLL here, because it's default for Cygwin.
        else(BUILD_SHARED_LIBS)
          SET (PNG_DEFINITIONS -DPNG_STATIC)
        endif(BUILD_SHARED_LIBS)
      endif (CYGWIN)

  endif (PNG_LIBRARIES AND PNG_INCLUDE_DIRS)

endif(ZLIB_LIBRARIES)

# handle the QUIETLY and REQUIRED arguments and set PNG_FOUND to TRUE if
# all listed variables are TRUE
#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PNG  DEFAULT_MSG  PNG_LIBRARIES PNG_INCLUDE_DIRS)

mark_as_advanced(PNG_INCLUDE_DIRS PNG_LIBRARIES )
