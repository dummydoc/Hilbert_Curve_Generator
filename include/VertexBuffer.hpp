//
// Created by rowan on 05/10/17.
//

#ifndef CPSC_453_ASSIGNMENT_1_VERTEXBUFFER_HPP
#define CPSC_453_ASSIGNMENT_1_VERTEXBUFFER_HPP

#include <string>
#include <vector>
#include <map>

#include "glfw.hpp"


class VertexBuffer {
    GLuint id;
    std::map<std::string, GLint> attributes;

public:
    VertexBuffer();
    VertexBuffer(std::vector<float> buffer);

    void bind(){glBindBuffer(GL_ARRAY_BUFFER, id);}
    void setBufferData(std::vector<float> buffer) {setBufferData(buffer, GL_STATIC_DRAW);}
    void setBufferData(std::vector<float> buffer, GLuint usage);
    void setVertexAttribute(GLuint shaderProgram, std::string attribute, GLint groupSize) {setVertexAttribute(shaderProgram, attribute, groupSize, GL_FLOAT, GL_FALSE, 0, 0);}
    void setVertexAttribute(GLuint shaderProgram, std::string attribute, GLint groupSize, GLenum dataType, GLboolean normalized, GLsizei stride, const GLvoid* offset);
    void enableVertexAttribute(std::string attribute);

    ~VertexBuffer();

};


#endif //CPSC_453_ASSIGNMENT_1_VERTEXBUFFER_HPP
