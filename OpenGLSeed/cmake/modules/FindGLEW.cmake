#############################################################
# Sets the following variables.
# GLEW_FOUND
# GLEW_LIBRARIES
# GLEW_INCLUDE_DIRS
#############################################################

# Set up the search paths.
if (UNIX)
  set (_glew_HEADER_SEARCH_DIRS "/usr/local/include" "/usr/include")
  set (_glew_LIBRARY_SEARCH_DIRS "/usr/local/lib" "/usr/lib" "/usr/lib/x86_64-linux-gnu")
elseif (WIN32)
  set (_glew_HEADER_SEARCH_DIRS "c:/include")
  set (_glew_LIBRARY_SEARCH_DIRS "c:/lib")
endif (UNIX)

# If the user has defined a root directory, search it first.
if (GLEW_ROOT_DIR)
  set (_glew_HEADER_SEARCH_DIRS "${GLEW_ROOT_DIR}/include" "${_glew_HEADER_SEARCH_DIRS}")
  set (_glew_LIBRARY_SEARCH_DIRS "${GLEW_ROOT_DIR}/lib" "${_glew_LIBRARY_SEARCH_DIRS}")
endif (GLEW_ROOT_DIR)

# Find the actual glew header and library.
find_path (GLEW_INCLUDE_DIR "GL/glew.h" paths ${_glew_HEADER_SEARCH_DIRS})
if (UNIX)
  find_library (GLEW_LIBRARY "GLEW" paths ${_glew_LIBRARY_SEARCH_DIRS})
elseif (WIN32)
  find_library (GLEW_LIBRARY "glew32" paths ${_glew_LIBRARY_SEARCH_DIRS})
endif (UNIX)

set (GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
set (GLEW_LIBRARIES ${GLEW_LIBRARY})

# This handles REQUIRED and QUITE, and sets <name>_FOUND.
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GLEW DEFAULT_MSG GLEW_LIBRARY GLEW_INCLUDE_DIR)

