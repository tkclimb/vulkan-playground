cmake_minimum_required(VERSION 3.10)
project(vulkan-playground LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(print variable)
  message(STATUS "${ARGV0}: ${${variable}}")
endfunction()

find_package(PkgConfig REQUIRED)
find_package(VULKAN REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${Vulkan_INCLUDE_DIR})
message(STATUS ${Vulkan_INCLUDE_DIR})
link_libraries(${Vulkan_LIBRARY})

get_filename_component(GLFW_ROOT_DIR /usr/local/opt/glfw ABSOLUTE)
get_filename_component(GLFW_INCLUDE_DIR ${GLFW_ROOT_DIR}/include ABSOLUTE)
get_filename_component(GLFW_LIB_DIR ${GLFW_ROOT_DIR}/lib ABSOLUTE)
set(GLFW_LIBRARY glfw)
include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIB_DIR})
link_libraries(${GLFW_LIBRARY})

get_filename_component(GLM_ROOT_DIR /usr/local/opt/glm ABSOLUTE)
get_filename_component(GLM_INCLUDE_DIR ${GLM_ROOT_DIR}/include ABSOLUTE)
include_directories(${GLM_INCLUDE_DIR})

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

add_subdirectory(src)