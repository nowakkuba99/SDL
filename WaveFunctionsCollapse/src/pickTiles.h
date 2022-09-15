#ifndef PICKTILES_H // include guard
#define PICKTILES_H

#include <vector>
#include <set>
#include "Tile.h"
#include "graphics.h"
const int GRID_SIZE_H = 40;    //5x5
const int GRID_SIZE_W = 40;
namespace Tiles
{
    /* Variables */
    extern std::vector<std::vector<Tile*> > pickMap;
    extern std::vector<Tile*> ListOfTilesToCollapse;
    extern std::set<std::pair<int,int> > visitedSet;
    const std::vector<std::pair<int,int> > dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    /* Functions */
    void InitTilesMap();
    void PickFirstTile();
    void UpdateListOfTilesToCollapse(int row, int col);
    bool InBound(int row, int col);
    void UpdateListOfPoss(int row, int col);
    void CountPossForListOfTilesToCollapse();
    bool Solve(std::vector<Tile*> &ListOfTilesToCollapse);
    void DeleteFromListOfTilesToCollapse(int row, int col);
}
#endif /* PICKTILES */