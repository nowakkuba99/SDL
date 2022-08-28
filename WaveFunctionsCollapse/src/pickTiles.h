#ifndef PICKTILES_H // include guard
#define PICKTILES_H

#include <vector>
#include "Tile.h"
const int GRID_SIZE_H = 5;    //5x5
const int GRID_SIZE_W = 5;
namespace Tiles
{
    /* Variables */
    extern std::vector<std::vector<Tile*> > pickMap;
    /* Functions */
    void InitTilesMap();
}
#endif /* PICKTILES */