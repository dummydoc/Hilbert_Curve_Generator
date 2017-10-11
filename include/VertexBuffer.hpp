#ifndef HILBERT_CURVE_GENERATOR_VERTEXBUFFER_HPP
#define HILBERT_CURVE_GENERATOR_VERTEXBUFFER_HPP

#include <string>
#include <vector>
#include <map>

#include "glfw.hpp"

class VertexBuffer {
    GLuint id;
    std::map<std::string, GLint> attributes;

public:
    VertexBuffer();
    VertexBuffer(std::vector<float>* buffer);

    void bind(){glBindBuffer(GL_ARRAY_BUFFER, id);}
    void setBufferData(std::vector<float>* buffer, GLuint usage = GL_STATIC_DRAW);
    void setVertexAttribute(GLuint shaderProgram, std::string attribute, GLint groupSize, GLenum dataType = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const GLvoid* offset = 0);
    void enableVertexAttribute(std::string attribute);

    ~VertexBuffer();

};


#endif //HILBERT_CURVE_GENERATOR_VERTEXBUFFER_HPP
