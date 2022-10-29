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
    endAnimation(RectVec,window);
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
Function which displays all rectangles with its height progressivly turning green
Arguments: Array of shared_ptr<Rectangle>, window 
*/
void sort::endAnimation(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, GLFWwindow* window)
{
    float max = -2;
    /* Render here */
    for(const auto &rectToChangeColor: RectVec)
    {
        if(rectToChangeColor.get()->y2 > max)
        {
            rectToChangeColor.get()->ChangeColor(50,205,50);
            max = rectToChangeColor.get()->y2;
        }
        else
            rectToChangeColor.get()->ChangeColor(205,50,50);
        glClear(GL_COLOR_BUFFER_BIT);
        for(const auto & rect: RectVec)
        {
            rect.get()->Draw();
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        usleep(1000*10);
    }
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
    index1.get()->ChangeColor(256,0,0);
    index2.get()->ChangeColor(256,0,0);
    sort::renderFunction(RectVec, window);
    index1.get()->ChangeColor(169,169,169);
    index2.get()->ChangeColor(169,169,169);
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
            if (RectVec[j].get()->y2 > RectVec[j+1].get()->y2)      //If element at [j] is smaller than element at [i]
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
            // {
            //     GLdouble temp = RectVec[lowIndex].get()->y2;
            //     RectVec[lowIndex].get()->y2 = RectVec[i].get()->y2;
            //     RectVec[i].get()->y2 = temp;
            //     swaps++;
            // }
            sort::swap(RectVec[lowIndex], RectVec[i], RectVec, window);
            swaps++;
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


/*
Function: Selection sort
Time Complexity O(n^2)
*/
void sort::selectionSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps)
{
    for(int i = 0; i<RectVec.size(); i++)
    {
        int currMinIndex = i;
        for(int j = i; j<RectVec.size(); j++)
        {
            comps++;
            if(RectVec[currMinIndex].get()->y2 > RectVec[j].get()->y2)
            {
                swaps++;
                currMinIndex = j;
                sort::swap(RectVec[currMinIndex], RectVec[j], RectVec, window);
            }
        }
        swaps++;
        sort::swap(RectVec[i], RectVec[currMinIndex], RectVec, window);
    }
}


/*
Function: Insertion sort
Time Complexity O(n^2)
*/
void sort::insertionSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps)
{
    int keyIndex;       // Index of current key
    for(int i = 1; i<RectVec.size(); i++)
    {
        keyIndex = i;       //Set index to current object
        for(int j = i - 1; j >= 0; j--) //Iterate through all elements to the begining of an array
        {
            comps++;
            if(RectVec[keyIndex].get()->y2 < RectVec[j].get()->y2)  //Check if previous element is greater
            {
                swaps++;
                sort::swap(RectVec[keyIndex], RectVec[j], RectVec, window);     //If so swap
                keyIndex--;             //And move keyIndex
            }
            else
                break;      //If not than all elements on the left are greater so break the inside loop
        }
    }
}
/*
Function: Merge sort
Time Complexity O(n^2)
*/
void sort::mergeSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &arrayAccess, int &comps)
{
    std::vector<draw::Rectangle> RectVecDisplay, RectVecSorted;     //Create new vectors for Display and Sorted arrays
    for(const auto &rect: RectVec)
    {
        RectVecDisplay.push_back(*rect.get());      //Copy RectVec to RecVecDisplay
    }
    sort::mergeSortRecursion(RectVec,RectVecDisplay, RectVecSorted, window, arrayAccess, comps, 0, RectVec.size()-1);     //Perform Sorting on the whole array
}
/* Heleper function to call recursively */
void sort::mergeSortRecursion(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,std::vector<draw::Rectangle> &RectVecDisplay,std::vector<draw::Rectangle> &RectVecSorted, GLFWwindow* window, int &arrayAccess, int &comps, int left, int right)
{
    int mid = ((right - left) / 2) + left;  //Get the mid point
    if(left < right)    //If not base case
    {
        sort::mergeSortRecursion(RectVec,RectVecDisplay, RectVecSorted,window,arrayAccess,comps,left,mid);  //Left side recursive call
        sort::mergeSortRecursion(RectVec,RectVecDisplay, RectVecSorted,window,arrayAccess,comps,mid+1,right);   //Right side recursive call
    }
    else
        return;
    sort::mergeSortMerging(RectVec,RectVecDisplay, RectVecSorted, window,arrayAccess,comps,left,right);   //After sorting both left and right merge into one sorted array
    
}
/* Helper function to merge two sorted arrays */
void sort::mergeSortMerging(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec, std::vector<draw::Rectangle> &RectVecDisplay,std::vector<draw::Rectangle> &RectVecSorted, GLFWwindow* window, int &arrayAccess, int &comps, int left, int right)
{
    RectVecSorted.clear();                      //Clear sorted vector -> On the second thought it could not be passed, but declared here
    int mid = ((right - left) / 2) + left + 1;  //Calculate the mid point
    int beg = mid, begLeft = left;  //Define the begining for left and right arrays
    bool endReached = false;        //Check if the right array has gotten to the end
    while(left < beg && endReached == false)    //If both arrays (left/right) has some elements left
    {
        comps++; arrayAccess+=2;
        if(RectVec[left].get()->y2 < RectVec[mid].get()->y2)    //Check which element is greater
        {
            arrayAccess++;
            RectVecSorted.push_back(*RectVec[left].get());      //Push to sorted vector
            sort::mergeCompareVectors(RectVecDisplay,RectVecSorted,begLeft,window,arrayAccess,comps);     //Update Display vector based on sorted vector
            left++;     //Increment left pointer
        }
        else
        {
            arrayAccess++;
            RectVecSorted.push_back(*RectVec[mid].get());       //Push to sorted vector
            sort::mergeCompareVectors(RectVecDisplay,RectVecSorted,begLeft,window,arrayAccess,comps);     //Update Display vector based on sorted vector
            if(mid < right)     //If mid pointer smaller than the right boundary
                mid++;  //Increment mid pointer
            else
                endReached = true;  //If mid is greater or equal already to right boundary set endReached to true
        }
    }
    // Some array has ended -> Paste the array that stayed to the end of sorted array
    if(endReached == true)      //If second array ended
    {
        while(left < beg)       //While something is left in the first array paste it in sorted
        {
            arrayAccess++;
            RectVecSorted.push_back(*RectVec[left].get());      //Push to sorted
            sort::mergeCompareVectors(RectVecDisplay,RectVecSorted,begLeft,window,arrayAccess,comps);     //Upadate Dispaly vector based on sorted vector
            left++;     //Increment left pointer
        }
    }
    else    //If first array ended
    {
        while(mid < right)      //While something is left in the second array
        {
            arrayAccess++;
            RectVecSorted.push_back(*RectVec[mid].get());   //Push to sorted
            sort::mergeCompareVectors(RectVecDisplay,RectVecSorted,begLeft,window,arrayAccess,comps); //Update Display vector based on sorted vector
            mid++;      //Increment mid pointer
        }
    }
    for(int i = begLeft; i<=right; i++)     //Update RecVec (Original) vector based on sorted (Display) vector within given boundaries
    {
        arrayAccess++;
        RectVec[i].get()->y2 = RectVecDisplay[i].y2;
    }
}
/* Helper function to compare display and sorted vector in order to update Display vector*/
void sort::mergeCompareVectors(std::vector<draw::Rectangle> &RectVecDisplay, std::vector<draw::Rectangle> &RectVecSorted, int index,GLFWwindow* window, int &arrayAccess, int &comps)
{
    int n = RectVecSorted.size(); // Calculate sorted vector size
    arrayAccess+=2; comps++;
    if(RectVecDisplay[n-1+index].y2 != RectVecSorted[n-1].y2)   //Check if the height of objects is the same
    {
        arrayAccess+=2;
        RectVecDisplay[n-1+index].y2 = RectVecSorted[n-1].y2;   //If so update display vector
        mergeRenderFunction(RectVecDisplay,window,n-1+index);     //Render new display vector
    }
}
/* Helper function to display the RectVecDisplay vector updated based on new sorted vector*/
void sort::mergeRenderFunction(std::vector<draw::Rectangle> &RectVecDisplay, GLFWwindow* window, int whichRed)    
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    RectVecDisplay[whichRed].ChangeColor(256,0,0);
    for(auto & rect: RectVecDisplay)
    {
        rect.Draw();
    }
    RectVecDisplay[whichRed].ChangeColor(169,169,169);
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

/*
    Function: Heap sort
    Time Complexity O(n*log n)
    Space Comlexity O(1)
*/
void sort::heapSort(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps)
{
    sort::buildMaxHeap(RectVec,window,swaps,comps);
    int n = RectVec.size()-1;
    for(int i = n; i>0; i--)
    {
        swaps++;
        sort::swap(RectVec[0],RectVec[n],RectVec,window);
        sort::heapify(RectVec,window,0,n,swaps,comps);
        n-=1;
    }
}
void sort::buildMaxHeap(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int &swaps, int &comps)
{
    for(int i = RectVec.size()/2 - 1; i>=0; i--)
    {
        sort::heapify(RectVec,window,i,RectVec.size(),swaps,comps);
    }
}
void sort::heapify(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec,GLFWwindow* window, int curr, int length, int &swaps, int &comps)
{
    int largest = curr;
    int left = 2*curr+1;
    int right = 2*curr+2;
    comps++;
    if(left < length && RectVec[left].get()->y2 > RectVec[largest].get()->y2)
    {
        largest = left;
    }
    comps++;
    if(right < length && RectVec[right].get()->y2 > RectVec[largest].get()->y2)
    {
        largest = right;
    }

    if(largest != curr)
    {
        swaps++;
        sort::swap(RectVec[curr], RectVec[largest], RectVec, window);
        sort::heapify(RectVec,window,largest,length,swaps,comps);
    }
}
