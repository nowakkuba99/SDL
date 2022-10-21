#ifndef FD9B3ADE_172B_431C_B1C0_E8FFBF63892F
#define FD9B3ADE_172B_431C_B1C0_E8FFBF63892F
#include <GLFW/glfw3.h>
#include <vector>

#include "drawFun.hpp"

namespace array
{
    /* 
    Function to initialize array of pointers to rectangle objects
    Arguments: vector <shared_ptr <Rectangle>>
    Returns: -
     */
    void initArr(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec);
}

#endif /* FD9B3ADE_172B_431C_B1C0_E8FFBF63892F */
