#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


#include "drawFun.hpp"
#include "arrayFunctions.hpp"
#include "sortingFun.hpp"

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
    array::initArr(RectVec);
    bool finished = false;
    int comps, swaps;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if(!finished)
        {
            //finished = sort::mainSortFun(window, &sort::bubbleSort,RectVec,swaps,comps);
            finished = sort::mainSortFun(window, &sort::quickSort,RectVec, swaps, comps);
            std::cout<<"----------------------------------------"<<"\n";
            std::cout<<"Finished!"<<'\n';
            std::cout<<"Num of Comp: "<<comps<<"\n";
            std::cout<<"Num of Swaps: "<<swaps<<"\n";
        }
        else
        {
            /* Swap front and back buffers */
            //glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}