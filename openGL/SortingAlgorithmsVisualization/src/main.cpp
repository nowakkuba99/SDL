#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include "drawFun.hpp"
#include <vector>

int main(void)
{
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::vector<std::shared_ptr<draw::Rectangle>> RectVec;
    int n =  sett::numOfElems;
    for(int i = 0; i<n; i++)
    {
        float pos = -1 + sett::constWidth + (2 - sett::constWidth)/n*i;
        float height = 1 - (2 - sett::constWidth)/n*i;  
        RectVec.push_back(std::shared_ptr<draw::Rectangle> (new draw::Rectangle(pos,height)));
    }
    
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        for(const auto & rect: RectVec)
        {
            rect.get()->Draw();
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}