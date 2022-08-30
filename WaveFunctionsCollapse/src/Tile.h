#ifndef TILE_H // include guard
#define TILE_H

#include <vector>
#include "image.h"

class Tile
{
public:
    /* data */
    image* imageObj = nullptr;
    int numOfPosNeig;
    std::vector<image*> ListOfPossNeigh;
    
    Tile();
    Tile(image* img): imageObj(img){};
    ~Tile()
    {
    }; 
};
#endif /* TILE */