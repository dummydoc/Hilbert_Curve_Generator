//
// Created by rowan on 05/10/17 with some code from the TA's boilerplate code.
//

#include <iostream>
#include <vector>

#include "glfw.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "shaders.hpp"

using std::cout;
using std::endl;

void render(GLuint numVerticies);
void hilbert(std::vector<float>& curve, int n, float x, float y, float xi, float xj, float yi, float yj);


int main(int argc, char *argv[]) {
    // initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return -1;
    }
    // This function sets the passed function (in this case, a lambda function) as a callback that should be called whenever GLFW encounters an error. basically it's an error handler function. In this case it prints out the error, but it could also be used to pass the error on to another service such as a logging system
    glfwSetErrorCallback([](int error, const char *description) {
        cout << "GLFW ERROR " << error << ":" << endl;
        cout << description << endl;
    });

    // Use OpenGL 4.1 - GLFW window hints are used to tell GLFW what sort of window to create. What is set here is used in glfwCreateWindow to build the specified window.
    GLFWwindow *window = 0; // set to zero to avoid ambiguity below.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Instruct GLFW to remove all APIs that were deprecated in the indicated version (4.1 here) as they will not be available in subsequent versions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the OpenGL Core profile, instead of some other one. Core is the main profile.
    window = glfwCreateWindow(512, 512, "CPSC 453 Assignment 1", 0, 0); // The first three arguments should be pretty obvious. The first is Width, followed by Height, and then window title. The last two are "monitor" and "share". Monitor refers to the display monitor to use if the window is going to be in full-screen mode. Share refers to another window that this window should share resources with.
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate(); // See below
        return -1;
    }

    glfwMakeContextCurrent(window); // this function makes the openGL context that we just created with our window "current" on this thread. That means that we can use it to draw to.

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0,0, width, height);
    });


    // Init stuff here
    auto shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    shaderProgram->use();

    auto vertexArray = new VertexArray();
    vertexArray->bind();

    auto curve = new std::vector<float>();
    hilbert(*curve, 6, -1, -1, 0, 2, 2, 0);

    auto vertexBuffer = new VertexBuffer(*curve);
    vertexBuffer->bind();
    vertexBuffer->setVertexAttribute(shaderProgram->getId(), "position", 2);
    vertexBuffer->enableVertexAttribute("position");

    auto colours = new std::vector<float>();
    for (int i = 1; i <= (curve->size()/2); i++) {
        colours->push_back(i * (0.9/(curve->size()/2)));
    }

    auto colourBuffer = new VertexBuffer(*colours);
    colourBuffer->bind();
    colourBuffer->setVertexAttribute(shaderProgram->getId(), "hue", 1);
    colourBuffer->enableVertexAttribute("hue");


    while (!glfwWindowShouldClose(window)) {
        // Render loop goes here
        render(curve->size()/2);

        glfwSwapInterval(1);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate(); // This is a GLFW cleanup function that acts like a destructor for GLFW and openGL

    cout << "The End" << endl;
    return 0;
}


void render(GLuint numVerticies) {
    // clear screen to a dark grey colour
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_LINE_STRIP, 0, numVerticies);
}

void hilbert(std::vector<float>& curve, int n, float x, float y, float xi, float xj, float yi, float yj) {
    if (n <= 0) {
        curve.push_back(x + (xi + yi)/2);
        curve.push_back(y + (xj + yj)/2);
    } else {
        hilbert(curve, n-1, x,           y,           yi/2, yj/2,  xi/2,  xj/2);
        hilbert(curve, n-1, x+xi/2,      y+xj/2 ,     xi/2, xj/2,  yi/2,  yj/2);
        hilbert(curve, n-1, x+xi/2+yi/2, y+xj/2+yj/2, xi/2, xj/2,  yi/2,  yj/2);
        hilbert(curve, n-1, x+xi/2+yi,   y+xj/2+yj,  -yi/2,-yj/2, -xi/2, -xj/2);
    }
}