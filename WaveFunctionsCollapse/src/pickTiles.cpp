#include "pickTiles.h"
/* Variables */
std::vector<std::vector<Tile*> > Tiles::pickMap(GRID_SIZE_H,std::vector<Tile*>(GRID_SIZE_W));
void Tiles::InitTilesMap()
{
    /* Initi map */
    for(int row = 0; row<GRID_SIZE_H; row++)
    {
        for(int col = 0; col<GRID_SIZE_W; col++)
        {
            Tiles::pickMap[row][col] = new Tile(row,0);
        }
    }
}