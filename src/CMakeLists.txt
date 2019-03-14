file(GLOB HEADERS 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        )
file(GLOB SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/*cpp
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(cg2019icmc STATIC ${SOURCES} ${HEADERS})
target_link_libraries(cg2019icmc PUBLIC ${GLFW_LIBRARIES} glad)
set_target_properties(cg2019icmc PROPERTIES
        OUTPUT_NAME "cg2019icmc"
        FOLDER "cg2019icmc")
target_include_directories(cg2019icmc PUBLIC ${CG2019ICMC_SOURCE_DIR}/CG2019ICMC)

set(cg2019_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# add_library(glad STATIC "${GLAD_DIR}/glad.c")
# SET_TARGET_PROPERTIES(glad PROPERTIES LINKER_LANGUAGE CXX)
# target_include_directories(glad PRIVATE "${GLAD_DIR}/include/glad.h")