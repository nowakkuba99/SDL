#include "sortingFun.hpp"
/* 
Main Function which starts the process
Arguments: Window to display in, pointer to sorting function
Returns: Bool -> True when sort ended
*/
bool sort::mainSortFun(GLFWwindow* window, void (*sortFun) (std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps),std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, int &swaps, int &comps)
{
    renderFunction(RectVec,window);
    sortFun(RectVec,window,swaps,comps);    //Visualize the sorting
    renderFunction(RectVec,window);
    /*
    if(sortCheck(RectVec) == true)
    {
        sortEndAnimation(RectVec,window);
        return true;
    }
    else
        return false;
    */
    return true;
}
/*
Function which displays all rectangles with its height after each step
Arguments: indexes to rerender (?), Array of shared_ptr<Rectangle> 
 */
void sort::renderFunction(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, GLFWwindow* window)
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

void sort::renderChoosenFunction(GLFWwindow* window, std::shared_ptr<draw::Rectangle> index1, std::shared_ptr<draw::Rectangle> index2)
{
    index1.get()->Clear();
    index2.get()->Clear();
    index1.get()->Draw();
    index2.get()->Draw();
}

/*
Function used to swap two objects position - changes the height of objects
Arguments: References to two pointers of objects to swap height
*/
void sort::swap(std::shared_ptr<draw::Rectangle> &index1, std::shared_ptr<draw::Rectangle> &index2,std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, GLFWwindow* window)
{
    //index1.swap(index2);
    GLdouble temp = index1.get()->y2;
    index1.get()->y2 = index2.get()->y2;
    index2.get()->y2 = temp;
    //sort::renderChoosenFunction(window,index1,index2);
    index1.get()->ChangeColor(100,0,0);
    index2.get()->ChangeColor(100,0,0);
    sort::renderFunction(RectVec, window);
    index1.get()->ChangeColor(100,100,100);
    index2.get()->ChangeColor(100,100,100);
    //usleep(1000);
}


/*
----------------------- Sorting functions -----------------------
*/

/*
Function: BubbleSort
Time Complexity: O(n^2)
*/
void sort::bubbleSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps)
{
    int i, j,n = RectVec.size();
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            comps++;
            if (RectVec[j].get()->y2 > RectVec[j+1].get()->y2)
            {
                sort::swap(RectVec[j], RectVec[j+1],RectVec,window);    //Swap elements
                swaps++;
            }
        }
    }
}

/*
Function: QuickSort
Time Complexity O(n log(n)) 
*/
void sort::quickSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps)
{
    sort::quickSortHelper(RectVec,window, 0, RectVec.size() - 1,swaps,comps);
}
/* Helper function to quicksort*/
void sort::quickSortHelper(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int low, int high, int &swaps, int &comps)
{
    if(low < high)
    {
        int pivot = sort::partition(RectVec, window, low, high,swaps,comps);

        sort::quickSortHelper(RectVec, window, low, pivot - 1,swaps,comps);
        sort::quickSortHelper(RectVec, window, pivot + 1, high,swaps,comps);
    }
}
/* Helper function to quicksort to find pivot element and swap elements*/
int sort::partition(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int low, int high, int &swaps, int &comps)
{
    int lowIndex = low - 1;
    float pivot = RectVec[high].get()->y2;

    for(int i = low; i < high; ++i)
    {
        comps++;
        if(RectVec[i].get()->y2 <= pivot)
        {
            ++lowIndex;
            //std::swap(RectVec[lowIndex], RectVec[i]);
            {
                GLdouble temp = RectVec[lowIndex].get()->y2;
                RectVec[lowIndex].get()->y2 = RectVec[i].get()->y2;
                RectVec[i].get()->y2 = temp;
                swaps++;
            }
            //sort::swap(RectVec[lowIndex], RectVec[i], RectVec, window);
        }
    }

    ++lowIndex;
    //std::swap(a[lowIndex], a[high]);
    if(lowIndex != high)
    {
        sort::swap(RectVec[lowIndex], RectVec[high], RectVec, window);
        swaps++;
    }
    return lowIndex;
}



