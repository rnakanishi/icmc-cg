project(CG2019ICMC)

cmake_minimum_required(VERSION 3.10)

include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external")
include( glfw )
include( glm )

find_package(OpenGL REQUIRED)
set(OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR} CACHE STRING "")
set(OPENGL_LIBRARIES ${OPENGL_LIBRARIES} CACHE STRING "")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glad" "external/glad")
set(GLAD_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")

set(CG2019ICMC_CPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp_src)
add_subdirectory(cpp_src)

set(CG2019ICMC_C_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/c_src)
add_subdirectory(c_src)

##################################################################
# EXECUTAVEIS

# Versao procedural
add_executable( projeto1C projeto_1.c )
target_link_libraries( projeto1C glad ${GLFW_LIBRARIES} cg2019c)
target_include_directories( projeto1C PUBLIC 
                            ${CG2019ICMC_C_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )

# Versao orientado a objetos
add_executable( projeto1CPP projeto_1.cpp )
target_link_libraries( projeto1CPP glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( projeto1CPP PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )

add_executable( demo demo.cpp )
target_link_libraries( demo glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( demo PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )

add_executable( color color.cpp )
target_link_libraries( color glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( color PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )

                                                        
add_executable( texture texture.cpp )
target_link_libraries( texture glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( texture PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )
                        
add_executable( loader loader.cpp )
target_link_libraries( loader glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( loader PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )
