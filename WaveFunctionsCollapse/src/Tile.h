#ifndef TILE_H // include guard
#define TILE_H

#include <vector>
#include<unordered_set>
#include "image.h"

class Tile
{
public:
    /* data */
    int row;
    int col;
    bool collapsed = false;
    image* imageObj = nullptr;
    int numOfPosImgs;
    std::vector<image*> ListOfPossImgs;
    std::unordered_set<image*> SetOfTriedImgs;
    std::unordered_set<Tile*> ListOfAddedNeighbours;
    /* Functions */
    Tile();
    Tile(int r,int c): row(r), col(c){};
    Tile(image* img): imageObj(img){};
    ~Tile()
    {
        imageObj = nullptr;
    }; 
};
#endif /* TILE */