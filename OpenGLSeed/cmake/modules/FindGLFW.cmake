#############################################################
# Sets the following variables.
# GLFW_FOUND
# GLFW_LIBRARIES
# GLFW_INCLUDE_DIRS
#############################################################

# Set up the search paths.
if (UNIX)
  set (_glfw_HEADER_SEARCH_DIRS "/usr/local/include" "/usr/include")
  set (_glfw_LIBRARY_SEARCH_DIRS "/usr/local/lib" "/usr/lib" "/usr/lib/x86_64-linux-gnu")
elseif (WIN32)
  set (_glfw_HEADER_SEARCH_DIRS "c:/include")
  set (_glfw_LIBRARY_SEARCH_DIRS "c:/lib")
endif (UNIX)

# If the user has defined a root directory, search it first.
if (GLFW_ROOT_DIR)
  set (_glfw_HEADER_SEARCH_DIRS "${GLFW_ROOT_DIR}/include" "${_glfw_HEADER_SEARCH_DIRS}")
  set (_glfw_LIBRARY_SEARCH_DIRS "${GLFW_ROOT_DIR}/lib" "${_glfw_LIBRARY_SEARCH_DIRS}")
endif (GLFW_ROOT_DIR)

# Find the actual glfw header and library.
find_path (GLFW_INCLUDE_DIR "GLFW/glfw3.h" paths ${_glfw_HEADER_SEARCH_DIRS})
if (UNIX)
  find_library (GLFW_LIBRARY "glfw" paths ${_glfw_LIBRARY_SEARCH_DIRS})
elseif (WIN32)
  find_library (GLFW_LIBRARY "glfw3dll" paths ${_glfw_LIBRARY_SEARCH_DIRS}) # TODO: Maybe system32?
endif (UNIX)

set (GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
set (GLFW_LIBRARIES ${GLFW_LIBRARY})

# This handles REQUIRED and QUITE, and sets <name>_FOUND.
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GLFW DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_DIR)

