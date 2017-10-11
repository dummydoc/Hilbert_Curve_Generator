#ifndef HILBERT_CURVE_GENERATOR_PROGRAMMANAGER_HPP
#define HILBERT_CURVE_GENERATOR_PROGRAMMANAGER_HPP

#include <vector>
#include <map>
#include <string>

#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "glfw.hpp"


class ProgramManager {
    class Program;

    uint n;
    std::vector<std::vector<float>*>* curves;
    std::vector<std::vector<float>*>* colours;
    VertexBuffer* colourBuffer;
    VertexBuffer* curveBuffer;
    std::map<std::string, Program*>* programs;

public:
    ProgramManager();
    ~ProgramManager();

    void newProgram(std::string programName, std::string vertex_shader, std::string fragment_shader, std::string geometry_shader = "NA");
    void useProgram(std::string programName);
    void setCurveBufferAttribute(std::string programName, std::string attributeName, GLint groupSize);
    void setColourBufferAttribute(std::string programName, std::string attributeName, GLint groupSize);
    void increaseHilbert();
    void decreaseHilbert();
    void render();

private:
    void hilbert(std::vector<float>* curve, int n, float x = -1, float y = -1, float xi = 0, float xj = 2, float yi = 2, float yj = 0);
    void colourGen(std::vector<float>* colours, int numColours);


    class Program {

        ShaderProgram* shaderProgram;
        VertexArray* vertexArray;

    public:
        Program(std::string vertexShader, std::string geometryShader, std::string fragmentShader);
        Program(std::string vertexShader, std::string fragmentShader);

        void useProgram();
        GLuint getProgramId();
    };

};


#endif //HILBERT_CURVE_GENERATOR_PROGRAMMANAGER_HPP