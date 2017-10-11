#include "ProgramManager.hpp"

ProgramManager::ProgramManager() {
    n = 1;
    curves = new std::vector<std::vector<float>*>();
    colours = new std::vector<std::vector<float>*>();
    curveBuffer = new VertexBuffer();
    colourBuffer = new VertexBuffer();
    programs = new std::map<std::string, Program*>();

    // init n=1 data
    curves->push_back(new std::vector<float>());
    hilbert(curves->at(n-1), n);
    curveBuffer->setBufferData(curves->at(n-1));

    colours->push_back(new std::vector<float>());
    colourGen(colours->at(n-1), curves->at(n-1)->size()/2);
    colourBuffer->setBufferData(colours->at(n-1));
}

ProgramManager::~ProgramManager() {
    delete curves;
    delete colours;
    delete curveBuffer;
    delete colourBuffer;
    delete programs;
}

void ProgramManager::newProgram(std::string programName, std::string vertex_shader, std::string fragment_shader, std::string geometry_shader) {

    if (!geometry_shader.compare("NA")) {
        programs->insert({programName, new Program(vertex_shader, fragment_shader)});
    }
    else {
        programs->insert({programName, new Program(vertex_shader, geometry_shader, fragment_shader)});
    }
}

void ProgramManager::useProgram(std::string programName) {
    programs->at(programName)->useProgram();
}

void ProgramManager::setCurveBufferAttribute(std::string programName, std::string attributeName, GLint groupSize) {
    curveBuffer->setVertexAttribute(programs->at(programName)->getProgramId(), attributeName, groupSize);
    curveBuffer->enableVertexAttribute(attributeName);
}

void ProgramManager::setColourBufferAttribute(std::string programName, std::string attributeName, GLint groupSize) {
    colourBuffer->setVertexAttribute(programs->at(programName)->getProgramId(), attributeName, groupSize);
    colourBuffer->enableVertexAttribute(attributeName);
}

void ProgramManager::render() {
    // clear screen to a dark grey colour
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_LINE_STRIP, 0, curves->at(n-1)->size()/2);
}

void ProgramManager::increaseHilbert() {
    if (n < 12) { // if we haven't reached the curve limit (set because going higher will just cause the program to freeze up) then increase it.
        n++;
        std::vector<float>* curve;
        std::vector<float>* colour;

        // get curve and colour for new n
        if (curves->size() >= n) { // we have already calculated a curve for this n, so reuse it.
            curve = curves->at(n-1);
            colour = colours->at(n-1);
        } else { // calculate the new curve and colour for n.
            curve = new std::vector<float>();
            hilbert(curve, n);
            colour = new std::vector<float>();
            colourGen(colour, curve->size()/2);
            curves->push_back(curve);
            colours->push_back(colour);
        }
        // Update buffer data
        curveBuffer->setBufferData(curve);
        colourBuffer->setBufferData(colour);
    }
}

void ProgramManager::decreaseHilbert() {
    if (n > 1) { // if we haven't reached n=1, decrease level
        n--;
        std::vector<float>* curve;
        std::vector<float>* colour;

        // Get curve and colour for new n
        // Since the program starts at n=1, we know with confidence that a previously generated curve will be avilable when decreasing n.
        curve = curves->at(n-1);
        colour = colours->at(n-1);

        // Update buffer data
        curveBuffer->setBufferData(curve);
        colourBuffer->setBufferData(colour);
    }
}

void ProgramManager::hilbert(std::vector<float>* curve, int n, float x, float y, float xi, float xj, float yi, float yj) {
    if (n <= 0) {
        curve->push_back(x + (xi + yi)/2);
        curve->push_back(y + (xj + yj)/2);
    } else {
        hilbert(curve, n-1, x,           y,           yi/2, yj/2,  xi/2,  xj/2);
        hilbert(curve, n-1, x+xi/2,      y+xj/2 ,     xi/2, xj/2,  yi/2,  yj/2);
        hilbert(curve, n-1, x+xi/2+yi/2, y+xj/2+yj/2, xi/2, xj/2,  yi/2,  yj/2);
        hilbert(curve, n-1, x+xi/2+yi,   y+xj/2+yj,  -yi/2,-yj/2, -xi/2, -xj/2);
    }
}

void ProgramManager::colourGen(std::vector<float>* colour, int numColours) {
    for (int i = 1; i <= numColours; i++) {
        colour->push_back(i * (0.95/numColours));
    }
}

ProgramManager::Program::Program(std::string vertexShader, std::string fragmentShader) {
    shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    vertexArray = new VertexArray();
}

ProgramManager::Program::Program(std::string vertexShader, std::string geometryShader, std::string fragmentShader) {
    shaderProgram = new ShaderProgram(vertexShader, geometryShader, fragmentShader);
    vertexArray = new VertexArray();
}

void ProgramManager::Program::useProgram() {
    shaderProgram->use();
    vertexArray->bind();
}

GLuint ProgramManager::Program::getProgramId() {
    return shaderProgram->getId();
}