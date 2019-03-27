file(GLOB HEADERS 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        )
file(GLOB SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(cg2019c STATIC ${SOURCES} ${HEADERS})
add_dependencies(cg2019c glfw)
add_dependencies(cg2019c glm)
target_link_libraries(cg2019c PUBLIC ${GLFW_LIBRARIES} glad)
set_target_properties(cg2019c PROPERTIES
        OUTPUT_NAME "cg2019c"
        FOLDER "CG2019c")
target_include_directories(cg2019c PUBLIC ${CG2019ICMC_SOURCE_DIR}/c_src
                                ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})


set(CG2019ICMC_CPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# add_library(glad STATIC "${GLAD_DIR}/glad.c")
# SET_TARGET_PROPERTIES(glad PROPERTIES LINKER_LANGUAGE CXX)
# target_include_directories(glad PRIVATE "${GLAD_DIR}/include/glad.h")