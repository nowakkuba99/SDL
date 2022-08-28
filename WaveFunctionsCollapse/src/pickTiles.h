// graphics.h
#ifndef PICKTILES_H // include guard
#define PICKTILES_H

#include <vector>
namespace Tiles
{
    /* Variables */
    extern std::vector<std::vector<int> > pickMap;
    /* Functions */
    void InitTilesMap();
}
#endif /* PICKTILES */