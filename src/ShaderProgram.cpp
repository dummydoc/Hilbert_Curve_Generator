//
// Created by rowan on 05/10/17.
//

#include <iostream>

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() {
    id = glCreateProgram();
    vertex_shader = 0;
    geometry_shader = 0;
    fragment_shader = 0;
}

ShaderProgram::ShaderProgram(std::string vertexShaderString, std::string fragmentShaderString) {
    id = glCreateProgram();
    addShader(vertexShaderString, GL_VERTEX_SHADER);
    addShader(vertexShaderString, GL_FRAGMENT_SHADER);

}

ShaderProgram::ShaderProgram(std::string vertexShaderString, std::string geometryShaderString, std::string fragmentShaderString) {
    id = glCreateProgram();
    addShader(vertexShaderString, GL_VERTEX_SHADER);
    addShader(geometryShaderString, GL_GEOMETRY_SHADER);
    addShader(vertexShaderString, GL_FRAGMENT_SHADER);
}

void ShaderProgram::addShader(std::string shaderString, GLuint type) {
    switch (type) {
        case GL_VERTEX_SHADER:
            if (vertex_shader == 0) {
                vertex_shader = glCreateShader(type);
                if (vertex_shader)
                    glAttachShader(id, vertex_shader);
            }
            updateShader(vertex_shader, shaderString);
            break;
        case GL_GEOMETRY_SHADER:
            if (geometry_shader == 0) {
                geometry_shader = glCreateShader(type);
                if (geometry_shader)
                    glAttachShader(id, geometry_shader);
            }
            updateShader(geometry_shader, shaderString);
            break;
        case GL_FRAGMENT_SHADER:
            if (fragment_shader == 0) {
                fragment_shader = glCreateShader(type);
                if (fragment_shader)
                    glAttachShader(id, fragment_shader);
            }
            updateShader(fragment_shader, shaderString);
    }
    glLinkProgram(id);
}

void ShaderProgram::updateShader(GLuint shader, std::string shaderString) {

    const char *buffer_array[] = { shaderString.c_str() }; // An array of ONE element, because glShaderSource takes an array of strings, not just one.

    glShaderSource(shader, 1, buffer_array, nullptr); // replaces the code of the indicated shader with the contents of the array of strings passed to it.
    glCompileShader(shader); // compiles the source code now contained within the shader object.

    // Get Compile results. Print out if there was an error.
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status); // This function gets a given parameter from a given shader.
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::string info(length, ' ');
        glGetShaderInfoLog(shader, info.length(), &length, &info[0]);
        std::cerr << "ERROR compiling shader:" << std::endl << std::endl;
        std::cerr << info << std::endl;
    }
}

ShaderProgram::~ShaderProgram() {
    glUseProgram(0);
    glDeleteProgram(id);
    glDeleteShader(vertex_shader);
    glDeleteShader(geometry_shader);
    glDeleteShader(fragment_shader);
}