//
// Created by rowan on 05/10/17.
//

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer(std::vector<float> buffer) {
    glGenBuffers(1, &id);
    bind();
    setBufferData(buffer);
}

void VertexBuffer::setBufferData(std::vector<float> buffer, GLuint usage) {
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), usage);
}

void VertexBuffer::setVertexAttribute(GLuint shaderProgram, std::string attribute, GLint groupSize, GLenum dataType, GLboolean normalized, GLsizei stride, const GLvoid* offset) {
    GLint attribIndex = glGetAttribLocation(shaderProgram, attribute.c_str());
    attributes[attribute] = attribIndex;
    glVertexAttribPointer(attribIndex, groupSize, dataType, normalized, stride, offset);
}

void VertexBuffer::enableVertexAttribute(std::string attribute) {
    glEnableVertexAttribArray(attributes[attribute]);
}

VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &id);
}
