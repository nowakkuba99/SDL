#ifndef C1C51E18_B531_4C0E_B78E_FC516D0147DC
#define C1C51E18_B531_4C0E_B78E_FC516D0147DC
#define GL_SILENCE_DEPRECATION
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <GLFW/glfw3.h>
#include "drawFun.hpp"
#include "sortingFun.hpp"
namespace sort
{
    /* 
    Main Function which starts the process
    Arguments: Window to display in, pointer to sorting function
    Returns: Bool -> True when sort ended
    */
    bool mainSortFun(GLFWwindow* window, void (*sortFun) (std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps),std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, int &swaps, int &comps);
    /*
    Function which displays all rectangles with its height after each step
    Arguments: indexes to rerender (?), Array of shared_ptr<Rectangle> 
    */
    void renderFunction(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, GLFWwindow* window);
    /*
    Function which displays all rectangles with its height after each step
    Arguments: indexes to rerender, Array of shared_ptr<Rectangle> 
    */
    void renderChoosenFunction(GLFWwindow* window, std::shared_ptr<draw::Rectangle> index1, std::shared_ptr<draw::Rectangle> index2);
    /*
    Function which displays all rectangles with its height progressivly turning green
    Arguments: Array of shared_ptr<Rectangle>, window 
    */
    void endAnimation(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, GLFWwindow* window);
    /*
    Function used to swap two objects position - changes the height of objects
    Arguments: References to two pointers of objects to swap height
    */
    void swap(std::shared_ptr<draw::Rectangle> &index1, std::shared_ptr<draw::Rectangle> &index2,std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, GLFWwindow* window);
    /*
    ----------------------- Sorting functions -----------------------
    */

    /*
    Function: BubbleSort
    Time Complexity: O(n^2)
    */
    void bubbleSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps);

    /*
    Function: QuickSort
    Time Complexity O(n log(n)) 
    */
    void quickSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps);
    void quickSortHelper(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int low, int high, int &swaps, int &comps);
    int partition(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int low, int high, int &swaps, int &comps);

    /*
    Function: Selection sort
    Time Complexity O(n^2)
    */
    void selectionSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps);

    /*
    Function: Insertion sort
    Time Complexity O(n^2)
    */
    void insertionSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps);
}

#endif /* C1C51E18_B531_4C0E_B78E_FC516D0147DC */
