//
// Created by rowan on 05/10/17.
//

#ifndef CPSC_453_ASSIGNMENT_1_VERTEXARRAY_HPP
#define CPSC_453_ASSIGNMENT_1_VERTEXARRAY_HPP

#include "glfw.hpp"
#include "VertexBuffer.hpp"


class VertexArray {
    GLuint id;

public:
    VertexArray();

    void bind() {glBindVertexArray(id);}

    ~VertexArray();
};


#endif //CPSC_453_ASSIGNMENT_1_VERTEXARRAY_HPP
