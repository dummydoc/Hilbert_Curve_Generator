#ifndef HILBERT_CURVE_GENERATOR_VERTEXARRAY_HPP
#define HILBERT_CURVE_GENERATOR_VERTEXARRAY_HPP

#include "glfw.hpp"


class VertexArray {
    GLuint id;

public:
    VertexArray();

    void bind() {glBindVertexArray(id);}

    ~VertexArray();
};


#endif //HILBERT_CURVE_GENERATOR_VERTEXARRAY_HPP
