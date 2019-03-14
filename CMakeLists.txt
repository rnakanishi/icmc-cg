project(CG2019ICMC)

cmake_minimum_required(VERSION 3.11)

include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external")
include( glfw )

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glad" "external/glad")
set(GLAD_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")

set(CG2019ICMC_CPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp_src)
add_subdirectory(cpp_src)

# set(CG2019ICMC_C_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/c_src)
# add_subdirectory(c_src)

##################################################################
# EXECUTAVEIS

# Versao procedural
add_executable( test1 hello.cpp )
target_link_libraries( test1 glad ${GLFW_LIBRARIES})
target_include_directories( test1 PUBLIC 
                            ${CG2019ICMC_C_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )

# Versao orientado a objetos
add_executable( test2 hello_oo.cpp )
target_link_libraries( test2 glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( test2 PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )