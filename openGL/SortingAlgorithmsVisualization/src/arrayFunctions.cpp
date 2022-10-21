#include "arrayFunctions.hpp"

void array::initArr(std::vector<std::shared_ptr<draw::Rectangle>> &RectVec)
{
    //std::vector<std::shared_ptr<draw::Rectangle>> RectVec;
    RectVec.clear();
    int n =  sett::numOfElems;
    for(int i = 0; i<n; i++)
    {
        float pos = -1 + sett::constWidth + (2 - sett::constWidth)/n*i;
        //float height = 1 - (2 - sett::constWidth)/n*i;  
        float height = 1 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2));
        RectVec.push_back(std::shared_ptr<draw::Rectangle> (new draw::Rectangle(pos,height)));
    }
}