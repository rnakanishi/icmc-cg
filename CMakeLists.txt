project(CG2019ICMC)

cmake_minimum_required(VERSION 3.11)

include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external")
include( glfw )

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glad" "external/glad")
set(GLAD_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")

# add_subdirectory(src)

##################################################################
# EXECUTAVEL
add_executable( hello hello.cpp )
target_link_libraries( hello glad ${GLFW_LIBRARIES})
target_include_directories( hello PUBLIC 
                            ${GLFW_INCLUDE_DIR} 
                            ${CMAKE_CURRENT_SOURCE_DIR}/glad/include )
add_dependencies( hello glfw glad )