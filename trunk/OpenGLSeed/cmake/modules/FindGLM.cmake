#############################################################
# Sets the following variables.
# GLM_FOUND
# GLM_LIBRARIES
# GLM_INCLUDE_DIRS
#############################################################

# Set up the search paths.
if (UNIX)
  set (_glm_HEADER_SEARCH_DIRS "/usr/local/include" "/usr/include")
elseif (WIN32)
  set (_glm_HEADER_SEARCH_DIRS "c:/include")
endif (UNIX)

# If the user has defined a root directory, search it first.
if (GLM_ROOT_DIR)
  set (_glm_HEADER_SEARCH_DIRS "${GLM_ROOT_DIR}/include" "${_glm_HEADER_SEARCH_DIRS}")
endif (GLM_ROOT_DIR)

# Find the actual glm header and library.
find_path (GLM_INCLUDE_DIR "glm/glm.hpp" paths ${_glm_HEADER_SEARCH_DIRS})
set (GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})

# This handles REQURED and QUITE, and sets <name>_FOUND.
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GLM DEFAULT_MSG GLM_INCLUDE_DIR)

