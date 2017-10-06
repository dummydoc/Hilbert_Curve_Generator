//
// Created by rowan on 05/10/17.
//

#ifndef CPSC_453_ASSIGNMENT_1_SHADERPROGRAM_HPP
#define CPSC_453_ASSIGNMENT_1_SHADERPROGRAM_HPP

#include <string>

#include "glfw.hpp"

class ShaderProgram {

    GLuint id;
    GLuint vertex_shader;
    GLuint geometry_shader;
    GLuint fragment_shader;

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


#endif //CPSC_453_ASSIGNMENT_1_SHADERPROGRAM_HPP
