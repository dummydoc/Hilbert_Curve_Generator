# Build file created by Ben Thomas, modified by Rowan Moul

CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(Hilbert_Curve_Generator CXX)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

FIND_PACKAGE(PkgConfig REQUIRED)

PKG_SEARCH_MODULE(OPENGL REQUIRED gl)
PKG_SEARCH_MODULE(GLFW3 REQUIRED glfw3)

FUNCTION(GLSL_GENERATE_CXX INPUT OUTPUT VAR_NAME)
    SET(GLSL_OUTPUTS ${GLSL_OUTPUTS} ${OUTPUT} PARENT_SCOPE)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${OUTPUT}
            COMMAND ${CMAKE_SOURCE_DIR}/gen_glsl_cpp.sh "${INPUT}" "${OUTPUT}" "${VAR_NAME}" "${CMAKE_SOURCE_DIR}/include/shaders.hpp"
            DEPENDS ${INPUT}
            ${CMAKE_SOURCE_DIR}/gen_glsl_cpp.sh
            VERBATIM
    )
ENDFUNCTION()

FILE(GLOB_RECURSE CXX_SOURCES src/*.cpp)
FILE(GLOB_RECURSE CXX_INCLUDES include/*.hpp)

#GLSL_GENERATE_CXX(${CMAKE_SOURCE_DIR}/shaders/geometry_triangle.glsl ${CMAKE_BINARY_DIR}/shader_gen/geometry_triangle.glsl.cpp "Hilbert_Curve_Generator::shaders::geometry_triangle_shader")
GLSL_GENERATE_CXX(${CMAKE_SOURCE_DIR}/shaders/fragment.glsl ${CMAKE_BINARY_DIR}/shader_gen/fragment.glsl.cpp "fragment_shader")
GLSL_GENERATE_CXX(${CMAKE_SOURCE_DIR}/shaders/vertex.glsl ${CMAKE_BINARY_DIR}/shader_gen/vertex.glsl.cpp "vertex_shader")

ADD_EXECUTABLE(Hilbert_Curve_Generator ${CXX_SOURCES} ${GLSL_OUTPUTS} ${CXX_INCLUDES})
TARGET_LINK_LIBRARIES(Hilbert_Curve_Generator ${OPENGL_LIBRARIES} ${GLFW3_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(Hilbert_Curve_Generator PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
TARGET_COMPILE_OPTIONS(Hilbert_Curve_Generator PUBLIC ${OPENGL_CFLAGS_OTHER} ${GLFW3_CFLAGS_OTHER})
