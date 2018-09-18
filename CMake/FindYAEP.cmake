# Try to find YAEP
# ================

# ~~~
# Once done this will define
#
#  YAEP_FOUND         System has YAEP
#  YAEP_INCLUDE_DIRS  The YAEP include directories
#  YAEP_LIBRARIES     The libraries needed to use YAEP
#
# This script is a modified version of the code available here:
# https://cmake.org/Wiki/CMake:How_To_Find_Libraries#Writing_find_modules
# ~~~

find_path(YAEP_INCLUDE_DIR NAMES yaep.h)

find_library(YAEP_LIBRARY NAMES yaep++)

include(FindPackageHandleStandardArgs)
# Handle the QUIETLY and REQUIRED arguments and set YAEP_FOUND to TRUE, if all
# listed variables are TRUE
find_package_handle_standard_args(YAEP
                                  REQUIRED_VARS
                                  YAEP_LIBRARY
                                  YAEP_INCLUDE_DIR)

mark_as_advanced(YAEP_INCLUDE_DIR YAEP_LIBRARY)

set(YAEP_LIBRARIES ${YAEP_LIBRARY})
set(YAEP_INCLUDE_DIRS ${YAEP_INCLUDE_DIR})
