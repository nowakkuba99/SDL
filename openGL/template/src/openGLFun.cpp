#include <iostream>

#include"openGLFun.h"


/* OpenGL specific function bodies */
/* ----------------------------------- */
/* Resize buffer size while window size changed */
void openGL::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height); // Set ViewPort to proper values
}

/* Process user input given by key presses */
void openGL::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // If ESC pressed
    {
        glfwSetWindowShouldClose(window, true); // Set flag to close window
    }
}

/* Initliazie OpenGL v. 3.3 */
void openGL::initGLFW()
{
    /* Initialize GLFW */
    glfwInit();                                                    // Initialize GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // Set openGL version to 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set openGL profile to core profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Set for MAC OS to set window forward
}

/* Initliaze GLAD */
int openGL::initGLAD()
{
    /* GLAD initialization */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    return 0;
}