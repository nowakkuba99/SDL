#ifndef B0726C13_7480_403E_8594_FA5F9ABA905E
#define B0726C13_7480_403E_8594_FA5F9ABA905E
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace openGL
{
/* --Define functions for openGL-- */
/* -Callback functions- */
// Callback for resizing window
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// Callback for user input
void processInput(GLFWwindow *window);
/* Initialization functions */
void initGLFW();
int initGLAD();
void createVertexShader(unsigned int &vertexShader);
void createFragmentShader(unsigned int &fragmentShader);
void createShaderProgram(unsigned int &vertexShader, unsigned int &fragmentShader, unsigned int &shaderProgram);
}

#endif /* B0726C13_7480_403E_8594_FA5F9ABA905E */
