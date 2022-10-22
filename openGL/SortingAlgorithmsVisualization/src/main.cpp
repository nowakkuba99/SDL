#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include "drawFun.hpp"
#include "arrayFunctions.hpp"
#include "sortingFun.hpp"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Sorting Algorithms Visualizer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    std::vector<std::shared_ptr<draw::Rectangle>> RectVec;
    bool finished = false;
    int comps = 0, swaps = 0;
    std::string type = "mergesort";
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if(!finished)
        {
            if(type == "bubblesort")
            {
                /* Bubble sort */
                array::initArr(RectVec);
                comps = 0; swaps = 0;
                finished = sort::mainSortFun(window, &sort::bubbleSort,RectVec,swaps,comps);
                std::cout<<"----------------------------------------"<<"\n";
                std::cout<<"Finished Bubble Sort!"<<'\n';
                std::cout<<"Num of Comp: "<<comps<<"\n";
                std::cout<<"Num of Swaps: "<<swaps<<"\n";

                finished = false;
                type = "selectionsort";
            }
            else if (type == "quicksort")
            {
                /* Quick sort */
                array::initArr(RectVec);
                comps = 0; swaps = 0;
                finished = sort::mainSortFun(window, &sort::quickSort,RectVec, swaps, comps);
                std::cout<<"----------------------------------------"<<"\n";
                std::cout<<"Finished Quick Sort!"<<'\n';
                std::cout<<"Num of Comp: "<<comps<<"\n";
                std::cout<<"Num of Swaps: "<<swaps<<"\n";
            }
            else if (type == "selectionsort")
            {
                /* Selection sort */
                array::initArr(RectVec);
                comps = 0; swaps = 0;
                finished = sort::mainSortFun(window, &sort::selectionSort,RectVec, swaps, comps);
                std::cout<<"----------------------------------------"<<"\n";
                std::cout<<"Finished Selection Sort!"<<'\n';
                std::cout<<"Num of Comp: "<<comps<<"\n";
                std::cout<<"Num of Swaps: "<<swaps<<"\n";
            }
            else if (type == "mergesort")
            {
                /* Merge sort */
                array::initArr(RectVec);
                comps = 0; swaps = 0;
                finished = sort::mainSortFun(window, &sort::mergeSort,RectVec, swaps, comps);
                std::cout<<"----------------------------------------"<<"\n";
                std::cout<<"Finished merge Sort!"<<'\n';
                std::cout<<"Num of Comp: "<<comps<<"\n";
                std::cout<<"Num of Swaps: "<<"No swapping going on here!"<<"\n";
                std::cout<<"Num of Array accesses: "<<swaps<<"\n";
            }
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