#ifndef HILBERT_CURVE_GENERATOR_SHADERPROGRAM_HPP
#define HILBERT_CURVE_GENERATOR_SHADERPROGRAM_HPP

#include <string>

#include "glfw.hpp"

class ShaderProgram {

    GLuint id;
    GLuint vertex_shader = 0;
    GLuint geometry_shader = 0;
    GLuint fragment_shader = 0;

public:

    ShaderProgram();
    ShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
    ShaderProgram(std::string vertexShaderSource, std::string geometryShaderSource, std::string fragmentShaderSource);

    void addShader(std::string shaderSource, GLuint type);
    void use() {glUseProgram(id);}
    GLuint getId() {return id;}

private:
    void updateShader(GLuint shader, std::string shaderSource);

public:
    ~ShaderProgram();
};


#endif //HILBERT_CURVE_GENERATOR_SHADERPROGRAM_HPP
