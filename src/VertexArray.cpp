//
// Created by rowan on 05/10/17.
//

#include "VertexArray.hpp"


VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &id);
}