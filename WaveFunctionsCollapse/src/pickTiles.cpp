#include "pickTiles.h"

/* Variables */
std::vector<std::vector<int> > Tiles::pickMap(5,std::vector<int>(5));
void Tiles::InitTilesMap()
{
    /* Initi map */
    for(int row = 0; row< 5; row++)
    {
        for(int col = 0; col<5; col++)
        {
            Tiles::pickMap[row][col] = row;
        }
    }
}